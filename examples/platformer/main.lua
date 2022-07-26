package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

util = require "utillib"
Vec2 = require "vector2"

local TILE_SIZE = 16
local PLAYER_MAXSPEED = 1.5
local PLAYER_ACCELL = 5
local PLAYER_DEACCELL = 5
local GRAVITY = 6
local JUMP_STR = 3
local WALK_ANIM_SPEED = 12

local tex = RL_LoadTexture( RL_GetBasePath().."../resources/images/arcade_platformerV2.png" )
local res = Vec2:new( 160, 144 )
local winScale = 5
local winSize = res:scale( winScale )
local framebuffer = RL_LoadRenderTexture( res )
local monitor = 0
local tilemap = {
	size = Vec2:new( res.x / TILE_SIZE, res.y / TILE_SIZE ),
	tiles = {},
	tileRects = {
		{ 224, 112, TILE_SIZE, TILE_SIZE },
		{ 224, 48, TILE_SIZE, TILE_SIZE },
		{ 208, 48, TILE_SIZE, TILE_SIZE },
		{ 240, 48, TILE_SIZE, TILE_SIZE },
		{ 256, 96, TILE_SIZE, TILE_SIZE },
		{ 256, 112, TILE_SIZE, TILE_SIZE },
	},
}

local player = {
	vel = Vec2:new( 0, 0 ),
	pos = Vec2:new( 32, 32 ), -- Center down.
	colRect = { 0, 0, 12, 14 },
	onFloor = false,
	frames = {
		{ 6, 14, 20, 18 },
		{ 39, 13, 20, 19 },
		{ 70, 14, 20, 18 },
		{ 6, 45, 20, 18 },
		{ 38, 45, 20, 18 },
		{ 70, 45, 20, 18 },
	},
	walkAnimFrames = { 2, 3, 4, 3 },
	curFrame = 1,
	animPos = 0.0,
	facing = 1,
}

local kissa = { Vec2:new( 2, 4 ), 23 }

-- print( table.concat( kissa ) )
print( kissa[1] )

local function createMap()
	for x = 1, tilemap.size.x do
		table.insert( tilemap.tiles, {} )

		for y = 1, tilemap.size.y do
			if y == tilemap.size.y then
				table.insert( tilemap.tiles[x], 1 )
			else
				table.insert( tilemap.tiles[x], 0 )
			end
		end
	end

	tilemap.tiles[4][7] = 3
	tilemap.tiles[5][7] = 2
	tilemap.tiles[6][7] = 2
	tilemap.tiles[7][7] = 4
	tilemap.tiles[6][6] = 5

	tilemap.tiles[10][4] = 5
	tilemap.tiles[10][5] = 6
	tilemap.tiles[10][6] = 6
	tilemap.tiles[10][7] = 6
	tilemap.tiles[10][8] = 6

	tilemap.tiles[1][5] = 5
	tilemap.tiles[1][6] = 6
	tilemap.tiles[1][7] = 6
	tilemap.tiles[1][8] = 6
end

function log( logLevel, message )
	if logLevel == LOG_WARNING then
		error( "Terminated because of warning" )
	end
end

function init()
	local monitorPos = Vec2:new( RL_GetMonitorPosition( monitor ) )
	local monitorSize = Vec2:new( RL_GetMonitorSize( monitor ) )

	RL_SetWindowTitle( "Platformer" )
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )

	createMap()
end

local function isTileWall( pos )
	if RL_CheckCollisionPointRec( { pos.x, pos.y }, { 0, 0, tilemap.size.x - 1, tilemap.size.y - 1 } ) then
		return 0 < tilemap.tiles[ pos.x + 1 ][ pos.y + 1 ]
	else
		return false
	end
end

local function tileCollision( entity )
	local vPos = entity.pos + entity.vel -- Future pos with current vel.
	local vRect = util.tableClone( entity.colRect )
	local tinyGap = 0.001 -- Tiny gap between collisionRect and tile to prevent getting stuck on all seams.

	-- Move test rect to predicted position.
	vRect[1] = vPos.x - vRect[3] / 2

	-- Tile range where collision box is affecting.
	local tileRect = {
		math.floor( vRect[1] / TILE_SIZE ),
		math.floor( vRect[2] / TILE_SIZE ),
		math.floor( ( vRect[1] + vRect[3] ) / TILE_SIZE ),
		math.floor( ( vRect[2] + vRect[4] ) / TILE_SIZE ),
	}

	for y = tileRect[2], tileRect[4] do
		if 0 < entity.vel.x then
			if isTileWall( Vec2:new( tileRect[3], y ) ) then
				-- Use new_x to push out of tile.
				local new_x = tileRect[3] * TILE_SIZE - ( entity.colRect[1] + entity.colRect[3] )

				entity.vel.x = new_x - tinyGap

				break
			end
		elseif entity.vel.x < 0 then
			if isTileWall( Vec2:new( tileRect[1], y ) ) then
				local new_x = ( tileRect[1] * TILE_SIZE + TILE_SIZE ) - entity.colRect[1]
				entity.vel.x = new_x + tinyGap

				break
			end
		end
	end

	-- Calculate new tileRect for y.
	vRect[1] = entity.colRect[1] -- Reset to non predicted one.
	vRect[2] = vPos.y - vRect[4]

	tileRect = {
		math.floor( vRect[1] / TILE_SIZE ),
		math.floor( vRect[2] / TILE_SIZE ),
		math.floor( ( vRect[1] + vRect[3] ) / TILE_SIZE ),
		math.floor( ( vRect[2] + vRect[4] ) / TILE_SIZE ),
	}

	for x = tileRect[1], tileRect[3] do
		if 0 < entity.vel.y then
			if isTileWall( Vec2:new( x, tileRect[4] ) ) then
				local new_y = tileRect[4] * TILE_SIZE - ( entity.colRect[2] + entity.colRect[4] )
				-- math.max prevents bounce when hitting right on the corner.
				entity.vel.y = math.max( new_y - tinyGap, 0 )
				player.onFloor = true

				break
			end
		elseif entity.vel.y < 0 then
			if isTileWall( Vec2:new( x, tileRect[2] ) ) then
				local new_y = ( tileRect[2] * TILE_SIZE + TILE_SIZE ) - entity.colRect[2]
				entity.vel.y = new_y + tinyGap

				break
			end
		end
	end
end

local function playerMovement( delta )
	local moving = { false, false }

	if RL_IsKeyDown( KEY_RIGHT ) then
		player.vel.x = player.vel.x + PLAYER_ACCELL * delta
		moving[1] = true

		if 0 < player.vel.x then
			player.facing = 1
		end
	elseif RL_IsKeyDown( KEY_LEFT ) then
		player.vel.x = player.vel.x - PLAYER_ACCELL * delta
		moving[1] = true

		if player.vel.x < 0 then
			player.facing = -1
		end
	end

	-- Alternative top down movement.

	-- if RL_IsKeyDown( KEY_DOWN ) then
	-- 	player.vel.y = player.vel.y + PLAYER_ACCELL * delta
	-- 	moving[2] = true
	-- elseif RL_IsKeyDown( KEY_UP ) then
	-- 	player.vel.y = player.vel.y - PLAYER_ACCELL * delta
	-- 	moving[2] = true
	-- end

	if RL_IsKeyPressed( KEY_SPACE ) and player.onFloor then
		player.vel.y = -JUMP_STR
		player.onFloor = false
	end

	-- Deaccel.

	if not moving[1] then
		if delta * PLAYER_DEACCELL < player.vel.x then
			player.vel.x = player.vel.x - PLAYER_DEACCELL * delta
		elseif player.vel.x < -delta * PLAYER_DEACCELL then
			player.vel.x = player.vel.x + PLAYER_DEACCELL * delta
		else
			player.vel.x = 0.0
		end
	end

	-- if not moving[2] then
	-- 	if delta * PLAYER_DEACCELL < player.vel.y then
	-- 		player.vel.y = player.vel.y - PLAYER_DEACCELL * delta
	-- 	elseif player.vel.y < -delta * PLAYER_DEACCELL then
	-- 		player.vel.y = player.vel.y + PLAYER_DEACCELL * delta
	-- 	else
	-- 		player.vel.y = 0.0
	-- 	end
	-- end
	
	player.vel.x = util.clamp( player.vel.x, -PLAYER_MAXSPEED, PLAYER_MAXSPEED )
	-- player.vel.y = util.clamp( player.vel.y, -PLAYER_MAXSPEED, PLAYER_MAXSPEED )

	player.vel.y = player.vel.y + GRAVITY * delta

	-- Drop from platform.
	if player.onFloor and 0.5 < player.vel.y then
		player.onFloor = false
	end

	tileCollision( player )
	player.pos = player.pos + player.vel
	player.colRect[1] = player.pos.x - player.colRect[3] / 2
	player.colRect[2] = player.pos.y - player.colRect[4]
end

function process( delta )
	if RL_IsWindowResized() then
		winSize:set( RL_GetWindowSize() )
	end

	playerMovement( delta )
end

local function drawMap()
	RL_DrawTextureRec( tex, { 0, 160, res.x, res.y }, { 0, 0 }, WHITE )

	for x = 1, tilemap.size.x do
		for y = 1, tilemap.size.y do
			local tile = tilemap.tiles[x][y]
			local pos = Vec2:new( x - 1, y - 1 )

			if 0 < tile then
				RL_DrawTextureRec( tex, tilemap.tileRects[ tile ], { pos.x * TILE_SIZE, pos.y * TILE_SIZE }, WHITE )
			end
		end
	end
end

local function drawPlayer()
	-- Animation.

	if player.onFloor then
		if math.abs( player.vel.x ) < 0.1 then
			player.curFrame = 1
		else
			player.animPos = player.animPos + WALK_ANIM_SPEED * ( math.abs( player.vel.x ) / PLAYER_MAXSPEED ) * RL_GetFrameTime()
			local frame = math.ceil( player.animPos )

			if #player.walkAnimFrames < frame then
				frame = 1
				player.animPos = player.animPos - #player.walkAnimFrames
			end

			player.curFrame = frame
		end 
	else
		if 0 < player.vel.y then
			player.curFrame = 6
		elseif player.vel.y < 0 then
			player.curFrame = 5
		end
	end

	-- Draw rect.

	local src = util.tableClone( player.frames[ player.curFrame ] )
	local dst = {
		player.pos.x - src[3] / 2,
		player.pos.y - src[4],
		src[3],
		src[4],
	}

	if player.facing < 0 then
		src[3] = -src[3]
	end

	RL_DrawTexturePro( tex, src, dst, { 0, 0 }, 0.0, WHITE )
end

function draw()
	RL_ClearBackground( BLACK )

	RL_SetTextureSource( TEXTURE_SOURCE_TEXTURE )
	RL_BeginTextureMode( framebuffer )
		drawMap()
		drawPlayer()
	RL_EndTextureMode()

	RL_SetTextureSource( TEXTURE_SOURCE_RENDER_TEXTURE )
	RL_DrawTexturePro( framebuffer, { 0, 0, res.x, -res.y }, { 0, 0, winSize.x, winSize.y }, { 0, 0 }, 0.0, WHITE )
	RL_SetTextureSource( TEXTURE_SOURCE_TEXTURE )
end
