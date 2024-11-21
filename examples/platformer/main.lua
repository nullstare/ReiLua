package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )

local TILE_SIZE = 16
local PLAYER_MAXSPEED = 1.5
local PLAYER_ACCELL = 5
local PLAYER_DEACCELL = 5
local GRAVITY = 6
local JUMP_STR = 3
local WALK_ANIM_SPEED = 12

local tex = nil
local res = Vec2:new( 160, 144 )
local winScale = 5
local winSize = res:scale( winScale )
local framebuffer = nil
local monitor = 0
local tilemap = {
	size = Vec2:new( res.x / TILE_SIZE, res.y / TILE_SIZE ),
	tiles = {},
	tileRects = {
		Rect:new( 224, 112, TILE_SIZE, TILE_SIZE ),
		Rect:new( 224, 48, TILE_SIZE, TILE_SIZE ),
		Rect:new( 208, 48, TILE_SIZE, TILE_SIZE ),
		Rect:new( 240, 48, TILE_SIZE, TILE_SIZE ),
		Rect:new( 256, 96, TILE_SIZE, TILE_SIZE ),
		Rect:new( 256, 112, TILE_SIZE, TILE_SIZE ),
	},
}
local player = {
	vel = Vec2:new( 0, 0 ),
	pos = Vec2:new( 32, 32 ), -- Center bottom.
	colRect = Rect:new( 0, 0, 12, 14 ),
	onFloor = false,
	frames = {
		Rect:new( 6, 14, 20, 18 ),
		Rect:new( 39, 13, 20, 19 ),
		Rect:new( 70, 14, 20, 18 ),
		Rect:new( 6, 45, 20, 18 ),
		Rect:new( 38, 45, 20, 18 ),
		Rect:new( 70, 45, 20, 18 ),
	},
	walkAnimFrames = { 2, 3, 4, 3 },
	curFrame = 1,
	animPos = 0.0,
	facing = 1,
}

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

function RL.config()
	RL.SetConfigFlags( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetConfigFlags( RL.FLAG_VSYNC_HINT )
	RL.InitWindow( winSize, "Platformer" )

	local monitorPos = Vec2:newT( RL.GetMonitorPosition( monitor ) )
	local monitorSize = Vec2:newT( RL.GetMonitorSize( monitor ) )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )
end

function RL.init()
	createMap()

	tex = RL.LoadTexture( RL.GetBasePath().."../resources/images/arcade_platformerV2.png" )
	framebuffer = RL.LoadRenderTexture( res )
end

local function isTileWall( pos )
	if RL.CheckCollisionPointRec( { pos.x, pos.y }, { 0, 0, tilemap.size.x, tilemap.size.y } ) then
		return 0 < tilemap.tiles[ pos.x + 1 ][ pos.y + 1 ]
	else
		return false
	end
end

local function tileCollision( entity )
	local vPos = entity.pos + entity.vel -- Future pos with current vel.
	local vRect = Rect:tempR( entity.colRect )
	local tinyGap = 0.001 -- Tiny gap between collisionRect and tile to prevent getting stuck on all seams.

	-- Move test rect to predicted position.
	vRect.x = vPos.x - vRect.width / 2

	-- Tile range where collision box is affecting.
	local tileRect = Rect:temp(
		math.floor( vRect.x / TILE_SIZE ),
		math.floor( vRect.y / TILE_SIZE ),
		math.floor( ( vRect.x + vRect.width ) / TILE_SIZE ),
		math.floor( ( vRect.y + vRect.height ) / TILE_SIZE )
	)

	for y = tileRect.y, tileRect.height do
		if 0 < entity.vel.x then
			if isTileWall( Vec2:temp( tileRect.width, y ) ) then
				-- Use new_x to push out of tile.
				local new_x = tileRect.width * TILE_SIZE - ( entity.colRect.x + entity.colRect.width )

				entity.vel.x = new_x - tinyGap

				break
			end
		elseif entity.vel.x < 0 then
			if isTileWall( Vec2:temp( tileRect.x, y ) ) then
				local new_x = ( tileRect.x * TILE_SIZE + TILE_SIZE ) - entity.colRect.x
				entity.vel.x = new_x + tinyGap

				break
			end
		end
	end

	-- Calculate new tileRect for y.
	vRect.x = entity.colRect.x -- Reset to non predicted one.
	vRect.y = vPos.y - vRect.height

	tileRect:set(
		math.floor( vRect.x / TILE_SIZE ),
		math.floor( vRect.y / TILE_SIZE ),
		math.floor( ( vRect.x + vRect.width ) / TILE_SIZE ),
		math.floor( ( vRect.y + vRect.height ) / TILE_SIZE )
	)

	for x = tileRect.x, tileRect.width do
		if 0 < entity.vel.y then
			if isTileWall( Vec2:temp( x, tileRect.height ) ) then
				local new_y = tileRect.height * TILE_SIZE - ( entity.colRect.y + entity.colRect.height )
				-- math.max prevents bounce when hitting right on the corner.
				entity.vel.y = math.max( new_y - tinyGap, 0 )
				player.onFloor = true

				break
			end
		elseif entity.vel.y < 0 then
			if isTileWall( Vec2:temp( x, tileRect.y ) ) then
				local new_y = ( tileRect.y * TILE_SIZE + TILE_SIZE ) - entity.colRect.y
				entity.vel.y = new_y + tinyGap

				break
			end
		end
	end
end

local function playerMovement( delta )
	local moving = { false, false }

	if RL.IsKeyDown( RL.KEY_RIGHT ) then
		player.vel.x = player.vel.x + PLAYER_ACCELL * delta
		moving[1] = true

		if 0 < player.vel.x then
			player.facing = 1
		end
	elseif RL.IsKeyDown( RL.KEY_LEFT ) then
		player.vel.x = player.vel.x - PLAYER_ACCELL * delta
		moving[1] = true

		if player.vel.x < 0 then
			player.facing = -1
		end
	end

	if RL.IsKeyPressed( RL.KEY_SPACE ) and player.onFloor then
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

	player.vel.x = Util.clamp( player.vel.x, -PLAYER_MAXSPEED, PLAYER_MAXSPEED )
	player.vel.y = player.vel.y + GRAVITY * delta

	-- Drop from platform.
	if player.onFloor and 0.5 < player.vel.y then
		player.onFloor = false
	end

	tileCollision( player )
	player.pos:addEq( player.vel )
	player.colRect.x = player.pos.x - player.colRect.width / 2
	player.colRect.y = player.pos.y - player.colRect.height
end

function RL.update( delta )
	if RL.IsWindowResized() then
		winSize:setT( RL.GetScreenSize() )
	end

	playerMovement( delta )
end

local function drawMap()
	RL.DrawTextureRec( tex, { 0, 160, res.x, res.y }, { 0, 0 }, RL.WHITE )

	for x = 1, tilemap.size.x do
		for y = 1, tilemap.size.y do
			local tile = tilemap.tiles[x][y]
			local pos = Vec2:temp( x - 1, y - 1 )

			if 0 < tile then
				RL.DrawTextureRec( tex, tilemap.tileRects[ tile ], { pos.x * TILE_SIZE, pos.y * TILE_SIZE }, RL.WHITE )
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
			player.animPos = player.animPos + WALK_ANIM_SPEED * ( math.abs( player.vel.x ) / PLAYER_MAXSPEED ) * RL.GetFrameTime()
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

	local src = player.frames[ player.curFrame ]:clone()
	local dst = Rect:temp(
		player.pos.x - src.width / 2,
		player.pos.y - src.height,
		src.width,
		src.height
	)

	if player.facing < 0 then
		src.width = -src.width
	end

	RL.DrawTexturePro( tex, src, dst, { 0, 0 }, 0.0, RL.WHITE )
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )

	RL.BeginTextureMode( framebuffer )
		drawMap()
		drawPlayer()
	RL.EndTextureMode()

	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( framebuffer ),
		{ 0, 0, res.x, -res.y },
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0 },
		0.0,
		RL.WHITE
	)
end
