local TILE_SIZE = 32

local monitor = 0
local camera = -1
local groundTexture = -1
local tilesetTex = -1
local heigthImage = -1
local mesh = -1
local material = -1
local lightmap = -1

local grassRec = { 6 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtRec = { 4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtRightRec = { 5 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtLeftRec = { 5 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtTopRec = { 6 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE }
local dirtBottomRec = { 7 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE }

local matrix = {}

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetScreenSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { 0, 8, 16 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 1, 0 } )
	RL_SetCameraMode( camera, CAMERA_FREE )

	heigthImage = RL_LoadImage( RL_GetBasePath().."../resources/images/heightmap.png" )

	mesh = RL_GenMeshHeightmap( heigthImage, { 16, 4, 16 } )
	tilesetTex = RL_LoadTexture( RL_GetBasePath().."../resources/images/tiles.png" )
	groundTexture = RL_LoadRenderTexture( { TILE_SIZE * 16, TILE_SIZE * 16 } )

	-- Draw to ground texture.
	RL_BeginTextureMode( groundTexture )

	for x = 1, 16 do
		for y = 1, 16 do
			local pos = { x - 1, y - 1 }

			if 4 < x and x < 14 and 4 < y and y < 8 then
				RL_DrawTextureRec( tilesetTex, dirtRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			elseif 4 == x and 4 < y and y < 8 then
				RL_DrawTextureRec( tilesetTex, dirtRightRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			elseif 14 == x and 4 < y and y < 8 then
				RL_DrawTextureRec( tilesetTex, dirtLeftRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			elseif 4 < x and x < 14 and 4 == y then
				RL_DrawTextureRec( tilesetTex, dirtTopRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			elseif 4 < x and x < 14 and 8 == y then
				RL_DrawTextureRec( tilesetTex, dirtBottomRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			else
				RL_DrawTextureRec( tilesetTex, grassRec, { pos[1] * TILE_SIZE, pos[2] * TILE_SIZE }, WHITE )
			end 
		end
	end

	RL_EndTextureMode()

	material = RL_LoadMaterialDefault()
	RL_SetTextureSource( TEXTURE_SOURCE_RENDER_TEXTURE )
	-- RL_GenTextureMipmaps( groundTexture )
	-- RL_SetTextureFilter( groundTexture, TEXTURE_FILTER_TRILINEAR )
	RL_SetMaterialTexture( material, MATERIAL_MAP_ALBEDO, groundTexture )
	RL_SetTextureSource( TEXTURE_SOURCE_TEXTURE )

	matrix = RL_MatrixMultiply( RL_MatrixIdentity(), RL_MatrixTranslate( { -4, 0, -4 } ) )
end

function draw()
	RL_ClearBackground( { 100, 150, 100 } )
	RL_UpdateCamera3D( camera )
	
	RL_BeginMode3D( camera )
		RL_DrawMesh( mesh, material, matrix )
	RL_EndMode3D()
end
