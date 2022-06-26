-- Defines
local RESOLUTION = { 128, 128 }
local TILE_SIZE = 8
local LEVEL_SIZE = RESOLUTION[1] / TILE_SIZE
local STATE = { TITLE = 0, GAME = 1, OVER = 2 } -- Enum wannabe.

-- Resources
local framebuffer = -1
local monitor = 0
local monitorPos = RL_GetMonitorPosition( monitor )
local monitorSize = RL_GetMonitorSize( monitor )
local winScale = 6
local winSize = { RESOLUTION[1] * winScale, RESOLUTION[2] * winScale }
local gameState = STATE.GAME
local grassTexture = -1
local snakeTexture = -1
local appleTexture = -1
local gameSpeed = 7.0
local moveTimer = 1.0
local snake = {}
local applePos = {}

local function setSnake()
	snake = {
		heading = { 1, 0 },
		control = { 1, 0 },
		headPos = { LEVEL_SIZE / 2, LEVEL_SIZE / 2 },
		segments = {},
		grow = 2,
	}
end

local function vector2IsEqual( v1, v2 )
	return v1[1] == v2[1] and v1[2] == v2[2]
end

local function addSegment()
	-- If first segment, grow from head and otherwise from tail. New segments are inserted firts.
	if #snake.segments == 0 then
		table.insert( snake.segments, 1, { pos = snake.headPos, heading = snake.heading } )
	else
		table.insert( snake.segments, 1, { pos = snake.segments[ #snake.segments ].pos,
										heading = snake.segments[ #snake.segments ].heading } )
	end
end

local function setApplePos()
	applePos = { math.random( 0, LEVEL_SIZE - 1 ), math.random( 0, LEVEL_SIZE - 1 ) }
	local search = true

	while search do
		search = false
		applePos = { math.random( 0, LEVEL_SIZE - 1 ), math.random( 0, LEVEL_SIZE - 1 ) }

		for _, seg in ipairs( snake.segments ) do
			search = vector2IsEqual( applePos, seg.pos )

			if search then
				break
			end
		end
	end
end

-- Init.

function init()
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { monitorPos[1] + monitorSize[1] / 2 - winSize[1] / 2, monitorPos[2] + monitorSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowTitle( "Snake" )
	RL_SetWindowIcon( RL_LoadImage( RL_GetBasePath().."../resources/images/apple.png" ) )

	framebuffer = RL_LoadRenderTexture( RESOLUTION )
	grassTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/grass.png" )
	snakeTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/snake.png" )
	appleTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/apple.png" )

	setSnake()
	setApplePos()
end

-- Process.

local function moveSnake()
	-- Check if snake has eaten and should grow.
	if 0 < snake.grow then
		addSegment()
		snake.grow = snake.grow - 1
	end
	-- Move body.
	for i, seg in ipairs( snake.segments ) do
		if i < #snake.segments then
			seg.pos = snake.segments[ i+1 ].pos
			seg.heading = snake.segments[ i+1 ].heading
		else
			seg.pos = snake.headPos
			seg.heading = snake.heading
		end
	end
	-- Move head.
	snake.heading = { snake.control[1], snake.control[2] }
	snake.headPos = { snake.headPos[1] + snake.heading[1], snake.headPos[2] + snake.heading[2] }

	-- Check appple eating.
	if vector2IsEqual( snake.headPos, applePos ) then
		snake.grow = snake.grow + 1
		setApplePos()
	end
	-- Check if hit to body.
	for _, seg in ipairs( snake.segments ) do
		if vector2IsEqual( snake.headPos, seg.pos ) then
			gameState = STATE.OVER
		end
	end
	-- Check if outside or level.
	if snake.headPos[1] < 0 or LEVEL_SIZE <= snake.headPos[1] or snake.headPos[2] < 0 or LEVEL_SIZE <= snake.headPos[2] then
		gameState = STATE.OVER
	end

	moveTimer = moveTimer + 1.0
end

function process( delta )
	if gameState == STATE.GAME then -- Run game.
		-- Controls.
		if RL_IsKeyPressed( KEY_RIGHT ) and 0 <= snake.heading[1] then
			snake.control = { 1, 0 }
		elseif RL_IsKeyPressed( KEY_LEFT ) and snake.heading[1] <= 0 then
			snake.control = { -1, 0 }
		elseif RL_IsKeyPressed( KEY_DOWN ) and 0 <= snake.heading[2] then
			snake.control = { 0, 1 }
		elseif RL_IsKeyPressed( KEY_UP ) and snake.heading[2] <= 0 then
			snake.control = { 0, -1 }
		end
	
		moveTimer = moveTimer - gameSpeed * delta
	
		if moveTimer <= 0.0 then
			moveSnake()
		end
	elseif gameState == STATE.OVER and RL_IsKeyPressed( KEY_ENTER ) then -- Reset game.
		setSnake()
		setApplePos()
		gameState = STATE.GAME
	end
end

-- Drawing.

local function drawGrass()
	for y = 0, LEVEL_SIZE - 1 do
		for x = 0, LEVEL_SIZE - 1 do
			RL_DrawTexture( grassTexture, { x * TILE_SIZE, y * TILE_SIZE }, WHITE )
		end
	end
end

--[[ Check if next segment is on left side. There are more mathematically elegant solution to this, but there is
only four possibilities so we can just check them all. ]]--
local function onLeft( this, nextSeg )
	return ( vector2IsEqual( this, { 0, -1 } ) and vector2IsEqual( nextSeg, { -1, 0 } ) )
		or ( vector2IsEqual( this, { -1, 0 } ) and vector2IsEqual( nextSeg, { 0, 1 } ) )
		or ( vector2IsEqual( this, { 0, 1 } ) and vector2IsEqual( nextSeg, { 1, 0 } ) )
		or ( vector2IsEqual( this, { 1, 0 } ) and vector2IsEqual( nextSeg, { 0, -1 } ) )
end

local function drawSnake()
	for i, seg in ipairs( snake.segments ) do
		local angle = math.deg( RL_Vector2Angle( { 0, 0 }, seg.heading ) )
		local source = { 16, 0, 8, 8 }

		if i == 1 then -- Tail segment. Yes tail is actually the 'first' segment.
			source[1] = 8

			if 1 < #snake.segments then
				angle = math.deg( RL_Vector2Angle( { 0, 0 }, snake.segments[ 2 ].heading ) )
			end
		elseif i < #snake.segments and not vector2IsEqual( seg.heading, snake.segments[ i+1 ].heading ) then -- Turned middle segments.
			source[1] = 0
			-- Mirror turned segment to other way.
			if onLeft( seg.heading, snake.segments[ i+1 ].heading ) then
				source[4] = -8
			end
		elseif i == #snake.segments and not vector2IsEqual( seg.heading, snake.heading ) then -- Turned segment before head.
			source[1] = 0

			if onLeft( seg.heading, snake.heading ) then
				source[4] = -8
			end
		end
		-- Notice that we set the origin to center { 4, 4 } that acts as pivot point. We also have to adjust our dest position by 4.
		RL_DrawTexturePro( snakeTexture, source, { seg.pos[1] * TILE_SIZE + 4, seg.pos[2] * TILE_SIZE + 4, 8, 8 }, { 4, 4 }, angle, WHITE )
	end
	-- Let's draw the head last to keep it on top.
	local angle = math.deg( RL_Vector2Angle( { 0, 0 }, snake.heading ) )
	RL_DrawTexturePro( snakeTexture, { 24, 0, 8, 8 }, { snake.headPos[1] * TILE_SIZE + 4, snake.headPos[2] * TILE_SIZE + 4, 8, 8 }, { 4, 4 }, angle, WHITE )
end

local function drawApple()
	RL_DrawTexture( appleTexture, { applePos[1] * TILE_SIZE, applePos[2] * TILE_SIZE }, WHITE )
end

function draw()
	-- Clear the window to black.
	RL_ClearBackground( BLACK )
	-- Draw to framebuffer.
	RL_BeginTextureMode( framebuffer )
		RL_ClearBackground( BLACK )
		drawGrass()
		drawSnake()
		drawApple()

		if gameState == STATE.OVER then
			RL_DrawText( 0, "Press Enter to\nrestart", { 10, 10 }, 10, 2, WHITE )
		end
	RL_EndTextureMode()
	
	-- Draw framebuffer to window.
	RL_SetTextureSource( TEXTURE_SOURCE_RENDER_TEXTURE )
	RL_DrawTexturePro( framebuffer, { 0, 0, RESOLUTION[1], -RESOLUTION[2] }, { 0, 0, winSize[1], winSize[2] }, { 0, 0 }, 0.0, WHITE )
	RL_SetTextureSource( TEXTURE_SOURCE_TEXTURE )
end
