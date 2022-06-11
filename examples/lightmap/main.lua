local PLANE_SIZE = 8

local monitor = 0
local camera = -1
local tileTexture = -1
local mesh = -1
local material = -1
local lightmap = -1
local shader = -1

local matrix = {}

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { 0, 8, 16 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 1, 0 } )
	RL_SetCamera3DMode( camera, CAMERA_FREE )

	local ts = PLANE_SIZE
	local meshData = {
		vertices = { { 0, 0, 0 }, { 0, 0, PLANE_SIZE }, { PLANE_SIZE, 0, PLANE_SIZE },
					 { 0, 0, 0 }, { PLANE_SIZE, 0, PLANE_SIZE }, { PLANE_SIZE, 0, 0 } },
		texcoords = { { 0, 0 }, { 0, ts }, { ts, ts },
					  { 0, 0 }, { ts, ts }, { ts, 0 } },
		texcoords2 = { { 0, 0 }, { 0, 1 }, { 1, 1 },
					   { 0, 0 }, { 1, 1 }, { 1, 0 } },
		colors = { WHITE, WHITE, WHITE,
				   WHITE, WHITE, WHITE },
		normals = { { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 },
				    { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } },
	}
	mesh = RL_GenMeshCustom( meshData, true )

	-- local meshEdit = {
	-- 	vertices = { { 0, 1, 0 }, { 0, 0, PLANE_SIZE }, { PLANE_SIZE, 0, PLANE_SIZE },
	-- 				 { 0, 1, 0 }, { PLANE_SIZE, 0, PLANE_SIZE }, { PLANE_SIZE, 0, 0 } },
	-- }
	-- RL_UpdateMesh( mesh, meshEdit )
	
	tileTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/tile.png" )
	RL_GenTextureMipmaps( tileTexture )
	RL_SetTextureFilter( tileTexture, TEXTURE_FILTER_TRILINEAR )
	lightmap = RL_LoadTexture( RL_GetBasePath().."../resources/images/lightmap.png" )
	RL_GenTextureMipmaps( lightmap )
	RL_SetTextureFilter( lightmap, TEXTURE_FILTER_TRILINEAR )
	RL_SetTextureWrap( lightmap, TEXTURE_WRAP_CLAMP )

	shader = RL_LoadShader( RL_GetBasePath().."../resources/shaders/glsl330/lightmap.vs",
						    RL_GetBasePath().."../resources/shaders/glsl330/lightmap.fs" )

	local materialData = {
		shader = shader,
		maps = {
			{
				MATERIAL_MAP_ALBEDO,
				{
					texture = tileTexture,
					color = WHITE,
					value = 1.0,
				},
			},
			{
				MATERIAL_MAP_METALNESS,
				{
					texture = lightmap,
					color = WHITE,
					value = 1.0,
				},
			},
		},
	}
	material = RL_CreateMaterial( materialData )

	matrix = RL_MatrixMultiply( RL_MatrixIdentity(), RL_MatrixTranslate( { -4, 0, -4 } ) )
end

function draw()
	RL_ClearBackground( { 25, 50, 50 } )
	RL_UpdateCamera3D( camera )
	
	RL_BeginMode3D( camera )
		RL_DrawMesh( mesh, material, matrix )
	RL_EndMode3D()
end
