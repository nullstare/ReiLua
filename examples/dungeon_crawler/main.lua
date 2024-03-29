local pos = { 2, 0.5, 6 }
local speed = 5.0
local camera = -1
local texture = -1
local textureSize = { 256, 96 }
local res = { 384, 216 }
local winSize = RL.GetScreenSize()
local winScale = 4
local framebuffer = nil

local TILE_SIZE = 32
local TILE_VERTEX_COLORS = { RL.WHITE, RL.WHITE, RL.WHITE, RL.WHITE }

local FLOOR = 1
local CEILING = 2
local WALL_N = 3
local WALL_S = 4
local WALL_W = 5
local WALL_E = 6

local sprites = {
	{ pos = { 0.5, 0.5 }, tile = { 0, 1 }, dis = 0, size = 0.7 },
	{ pos = { 3.5, 0.5 }, tile = { 0, 1 }, dis = 0, size = 0.7 },
}

local function getTexCoords( x, y )
	return {
		{ x * TILE_SIZE / textureSize[1], y * TILE_SIZE / textureSize[2] },
		{ x * TILE_SIZE / textureSize[1], ( y * TILE_SIZE + TILE_SIZE ) / textureSize[2] },
		{ ( x * TILE_SIZE + TILE_SIZE ) / textureSize[1], ( y * TILE_SIZE + TILE_SIZE ) / textureSize[2] },
		{ ( x * TILE_SIZE + TILE_SIZE ) / textureSize[1], y * TILE_SIZE / textureSize[2] },
	}
end

local function getTileVer( x, y, type )
	local types = {
		{ { 0, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 0, 0 } }, -- Floor.
		{ { 1, 1, 0 }, { 1, 1, 1 }, { 0, 1, 1 }, { 0, 1, 0 } }, -- Ceiling.
		{ { 0, 1, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, { 1, 1, 0 } }, -- Wall North.
		{ { 1, 1, 1 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 1 } }, -- Wall South.
		{ { 0, 1, 1 }, { 0, 0, 1 }, { 0, 0, 0 }, { 0, 1, 0 } }, -- Wall West.
		{ { 1, 1, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 1 } }, -- Wall East.
	}
	local verts = types[ type ]

	for i = 1, 4 do
		verts[i][1] = verts[i][1] + x
		verts[i][3] = verts[i][3] + y
	end

	return verts
end

local function drawSprites()
	for _, sprite in ipairs( sprites ) do
		sprite.dis = RL.Vector2Distance( { pos[1], pos[3] }, { sprite.pos[1], sprite.pos[2] } )
	end

	table.sort( sprites, function( a, b ) return a.dis > b.dis end )

	for _, sprite in ipairs( sprites ) do
		RL.DrawBillboardRec( camera, texture, { sprite.tile[1] * TILE_SIZE, sprite.tile[2] * TILE_SIZE, TILE_SIZE, TILE_SIZE },
							 { sprite.pos[1], 0.5 * sprite.size, sprite.pos[2] }, { sprite.size, sprite.size }, RL.WHITE )
	end
end

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )

	winSize = { res[1] * winScale, res[2] * winScale }
	RL.SetWindowSize( winSize )
	RL.SetExitKey( RL.KEY_ESCAPE )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/tiles.png" )
	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, pos )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )

	table.insert( sprites, { pos = { 2.5, 2.5 }, tile = { 1, 1 }, dis = 0, size = 0.8 } )
	table.insert( sprites, { pos = { 1.5, 3.5 }, tile = { 3, 1 }, dis = 0, size = 0.5 } )
	table.insert( sprites, { pos = { 0.5, 3.5 }, tile = { 3, 0 }, dis = 0, size = 0.7 } )
end

function RL.draw()
	RL.UpdateCamera3D( camera, RL.CAMERA_FIRST_PERSON )
	pos = RL.GetCamera3DPosition( camera )

	RL.ClearBackground( { 100, 150, 150 } )

	RL.BeginMode3D( camera )
		-- Floor and ceiling.
		for x = 0, 3 do
			for y = 0, 10 do
				RL.DrawQuad3DTexture( texture, getTileVer( x, y, FLOOR ), getTexCoords( 1, 0 ), TILE_VERTEX_COLORS )
				RL.DrawQuad3DTexture( texture, getTileVer( x, y, CEILING ), getTexCoords( 2, 0 ), TILE_VERTEX_COLORS )
			end
		end
		-- Walls.
		RL.DrawQuad3DTexture( texture, getTileVer( 0, 0, WALL_N ), getTexCoords( 0, 0 ), TILE_VERTEX_COLORS )
		RL.DrawQuad3DTexture( texture, getTileVer( 1, 0, WALL_N ), getTexCoords( 0, 2 ), TILE_VERTEX_COLORS )
		RL.DrawQuad3DTexture( texture, getTileVer( 2, 0, WALL_N ), getTexCoords( 2, 2 ), TILE_VERTEX_COLORS )
		RL.DrawQuad3DTexture( texture, getTileVer( 3, 0, WALL_N ), getTexCoords( 0, 0 ), TILE_VERTEX_COLORS )

		for x = 0, 3 do
			RL.DrawQuad3DTexture( texture, getTileVer( x, 10, WALL_S ), getTexCoords( 0, 0 ), TILE_VERTEX_COLORS )
		end
		for y = 0, 10 do
			RL.DrawQuad3DTexture( texture, getTileVer( 0, y, WALL_W ), getTexCoords( 0, 0 ), TILE_VERTEX_COLORS )
			RL.DrawQuad3DTexture( texture, getTileVer( 3, y, WALL_E ), getTexCoords( 0, 0 ), TILE_VERTEX_COLORS )
		end

		drawSprites()
	RL.EndMode3D()
end
