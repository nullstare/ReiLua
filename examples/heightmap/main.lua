package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Vec3 = require( "vector3" )
Cam3D = require( "camera3d" )

local TILE_SIZE = 32

local monitor = 0
local camera = {}
local groundRenderTexture = nil
local groundTexture = nil
local tilesetTex = nil
local heigthImage = nil
local mesh = nil
local material = nil

local grassRec = { 6 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtRec = { 4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtRightRec = { 5 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtLeftRec = { 5 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtTopRec = { 6 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtBottomRec = { 7 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }

local matrix = {}

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	camera = Cam3D:new()

	camera:setPosition( { 0, 8, 16 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	camera.mode = camera.MODES.ORBITAL

	heigthImage = RL.LoadImage( RL.GetBasePath().."../resources/images/heightmap.png" )

	mesh = RL.GenMeshHeightmap( heigthImage, { 16, 4, 16 } )
	tilesetTex = RL.LoadTexture( RL.GetBasePath().."../resources/images/tiles.png" )
	groundRenderTexture = RL.LoadRenderTexture( { TILE_SIZE * 16, TILE_SIZE * 16 } )
	groundTexture = RL.GetRenderTextureTexture( groundRenderTexture )

	-- Draw to ground texture.
	RL.BeginTextureMode( groundRenderTexture )

	for x = 1, 16 do
		for y = 1, 16 do
			local pos = { x - 1, y - 1 }

			if 4 < x and x < 14 and 4 < y and y < 8 then
				RL.DrawTextureRec( tilesetTex, dirtRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			elseif 4 == x and 4 < y and y < 8 then
				RL.DrawTextureRec( tilesetTex, dirtRightRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			elseif 14 == x and 4 < y and y < 8 then
				RL.DrawTextureRec( tilesetTex, dirtLeftRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			elseif 4 < x and x < 14 and 4 == y then
				RL.DrawTextureRec( tilesetTex, dirtTopRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			elseif 4 < x and x < 14 and 8 == y then
				RL.DrawTextureRec( tilesetTex, dirtBottomRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			else
				RL.DrawTextureRec( tilesetTex, grassRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, RL.WHITE )
			end
		end
	end

	RL.EndTextureMode()

	material = RL.LoadMaterialDefault()
	RL.SetMaterialTexture( material, RL.MATERIAL_MAP_ALBEDO, groundTexture )

	matrix = RL.MatrixTranslate( { -4, 0, -4 } )
end

function RL.update( delta )
	camera:update( delta )

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		if camera.mode == camera.MODES.FREE then
			camera.mode = camera.MODES.FIRST_PERSON
		else
			camera.mode = camera.MODES.FREE
		end
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )

	camera:beginMode3D()
		RL.DrawMesh( mesh, material, matrix )
	camera:endMode3D()
end
