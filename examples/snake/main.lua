package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )

-- Defines
local RESOLUTION = Vec2:new( 128, 128 )
local TILE_SIZE = 8
local LEVEL_SIZE = RESOLUTION.x / TILE_SIZE
local STATE = { TITLE = 0, GAME = 1, OVER = 2 } -- Enum.

-- Resources
local framebuffer = nil
local monitor = 0
local monitorPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
local monitorSize = Vec2:new( RL.GetMonitorSize( monitor ) )
local winScale = 6
local winSize = Vec2:new( RESOLUTION.x * winScale, RESOLUTION.y * winScale )
local gameState = STATE.GAME
local grassTexture = nil
local snakeTexture = nil
local appleTexture = nil
local gameSpeed = 7.0
local moveTimer = 1.0
local snake = {}
local applePos = {}

local function setSnake()
	snake = {
		heading = Vec2:new( 1, 0 ),
		control = Vec2:new( 1, 0 ),
		headPos = Vec2:new( LEVEL_SIZE / 2, LEVEL_SIZE / 2 ),
		segments = {}, -- { pos Vec2, heading Vec2 }
		grow = 2,
	}
end

local function addSegment()
	-- If first segment, grow from head and otherwise from tail. New segments are inserted firts.
	if #snake.segments == 0 then
		table.insert( snake.segments, 1, {
			pos = snake.headPos:clone(),
			heading = snake.heading:clone()
		} )
	else
		table.insert( snake.segments, 1, {
			pos = snake.segments[ #snake.segments ].pos:clone(),
			heading = snake.segments[ #snake.segments ].heading:clone()
		} )
	end
end

local function setApplePos()
	applePos = Vec2:new( math.random( 0, LEVEL_SIZE - 1 ), math.random( 0, LEVEL_SIZE - 1 ) )
	local search = true

	while search do
		search = false
		applePos = Vec2:new( math.random( 0, LEVEL_SIZE - 1 ), math.random( 0, LEVEL_SIZE - 1 ) )

		for _, seg in ipairs( snake.segments ) do
			search = applePos == seg.pos

			if search then
				break
			end
		end
	end
end

-- Init.

function RL.init()
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )
	RL.SetWindowTitle( "Snake" )
	RL.SetWindowIcon( RL.LoadImage( RL.GetBasePath().."../resources/images/apple.png" ) )

	framebuffer = RL.LoadRenderTexture( RESOLUTION )
	grassTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/grass.png" )
	snakeTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/snake.png" )
	appleTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/apple.png" )

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
			seg.pos = snake.segments[ i+1 ].pos:clone()
			seg.heading = snake.segments[ i+1 ].heading:clone()
		else
			seg.pos = snake.headPos:clone()
			seg.heading = snake.heading:clone()
		end
	end
	-- Move head.
	snake.heading = Vec2:new( snake.control.x, snake.control.y )
	snake.headPos = Vec2:new( snake.headPos.x + snake.heading.x, snake.headPos.y + snake.heading.y )

	-- Check appple eating.
	if snake.headPos == applePos then
		snake.grow = snake.grow + 1
		setApplePos()
	end
	-- Check if hit to body.
	for _, seg in ipairs( snake.segments ) do
		if snake.headPos == seg.pos then
			gameState = STATE.OVER
		end
	end
	-- Check if outside or level.
	if snake.headPos.x < 0 or LEVEL_SIZE <= snake.headPos.x or snake.headPos.y < 0 or LEVEL_SIZE <= snake.headPos.y then
		gameState = STATE.OVER
	end

	moveTimer = moveTimer + 1.0
end

function RL.update( delta )
	if gameState == STATE.GAME then -- Run game.
		-- Controls.
		if RL.IsKeyPressed( RL.KEY_RIGHT ) and 0 <= snake.heading.x then
			snake.control = Vec2:new( 1, 0 )
		elseif RL.IsKeyPressed( RL.KEY_LEFT ) and snake.heading.x <= 0 then
			snake.control = Vec2:new( -1, 0 )
		elseif RL.IsKeyPressed( RL.KEY_DOWN ) and 0 <= snake.heading.y then
			snake.control = Vec2:new( 0, 1 )
		elseif RL.IsKeyPressed( RL.KEY_UP ) and snake.heading.y <= 0 then
			snake.control = Vec2:new( 0, -1 )
		end

		moveTimer = moveTimer - gameSpeed * delta

		if moveTimer <= 0.0 then
			moveSnake()
		end
	elseif gameState == STATE.OVER and RL.IsKeyPressed( RL.KEY_ENTER ) then -- Reset game.
		setSnake()
		setApplePos()
		gameState = STATE.GAME
	end
end

-- Drawing.

local function drawGrass()
	for y = 0, LEVEL_SIZE - 1 do
		for x = 0, LEVEL_SIZE - 1 do
			RL.DrawTexture( grassTexture, { x * TILE_SIZE, y * TILE_SIZE }, RL.WHITE )
		end
	end
end

--[[ Check if next segment is on left side. There are more mathematically elegant solution to this, but there is
only four possibilities so we can just check them all. ]]--
local function onLeft( this, nextSeg )
	return ( this == Vec2:new( 0, -1 ) and nextSeg == Vec2:new( -1, 0 ) )
		or ( this == Vec2:new( -1, 0 ) and nextSeg == Vec2:new( 0, 1 ) )
		or ( this == Vec2:new( 0, 1 ) and nextSeg == Vec2:new( 1, 0 ) )
		or ( this == Vec2:new( 1, 0 ) and nextSeg == Vec2:new( 0, -1 ) )
end

local function drawSnake()
	for i, seg in ipairs( snake.segments ) do
		local angle = seg.heading:atan2()
		local source = Rect:new( 16, 0, 8, 8 )

		if i == 1 then -- Tail segment. Yes tail is actually the 'first' segment.
			source.x = 8

			if 1 < #snake.segments then
				angle = snake.segments[ 2 ].heading:atan2()
			end
		elseif i < #snake.segments and seg.heading ~= snake.segments[ i+1 ].heading then -- Turned middle segments.
			source.x = 0
			-- Mirror turned segment to other way.
			if onLeft( seg.heading, snake.segments[ i+1 ].heading ) then
				source.height = -8
			end
		elseif i == #snake.segments and seg.heading ~= snake.heading then -- Turned segment before head.
			source.x = 0

			if onLeft( seg.heading, snake.heading ) then
				source.height = -8
			end
		end

		-- Notice that we set the origin to center { 4, 4 } that acts as pivot point. We also have to adjust our dest position by 4.
		RL.DrawTexturePro(
			snakeTexture,
			source,
			{ seg.pos.x * TILE_SIZE + 4, seg.pos.y * TILE_SIZE + 4, 8, 8 },
			{ 4, 4 },
			angle * RL.RAD2DEG,
			RL.WHITE
		)
	end
	-- Let's draw the head last to keep it on top.
	local angle = snake.heading:atan2()
	RL.DrawTexturePro(
		snakeTexture,
		{ 24, 0, 8, 8 },
		{ snake.headPos.x * TILE_SIZE + 4, snake.headPos.y * TILE_SIZE + 4, 8, 8 },
		{ 4, 4 },
		angle * RL.RAD2DEG,
		RL.WHITE
	)
end

local function drawApple()
	RL.DrawTexture( appleTexture, { applePos.x * TILE_SIZE, applePos.y * TILE_SIZE }, RL.WHITE )
end

function RL.draw()
	-- Clear the window to black.
	RL.ClearBackground( RL.BLACK )
	-- Draw to framebuffer.
	RL.BeginTextureMode( framebuffer )
		RL.ClearBackground( RL.BLACK )
		drawGrass()
		drawSnake()
		drawApple()

		if gameState == STATE.OVER then
			RL.DrawText( "Press Enter to\nrestart", { 10, 10 }, 10, RL.WHITE )
		end
	RL.EndTextureMode()

	-- Draw framebuffer to window.
	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( framebuffer ),
		{ 0, 0, RESOLUTION.x, -RESOLUTION.y },
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0 },
		0.0,
		RL.WHITE
	)
end
