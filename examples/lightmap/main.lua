local PLANE_SIZE = 8

local monitor = 0
local camera = -1
local tileTexture = -1
local mesh = -1
local material = -1
local lightmap = -1
local shader = -1

local matrix = {}

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { 0, 8, 16 } )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )

	local ts = PLANE_SIZE
	local meshData = {
		vertices = { { 0, 0, 0 }, { 0, 0, PLANE_SIZE }, { PLANE_SIZE, 0, PLANE_SIZE },
					 { 0, 0, 0 }, { PLANE_SIZE, 0, PLANE_SIZE }, { PLANE_SIZE, 0, 0 } },
		texcoords = { { 0, 0 }, { 0, ts }, { ts, ts },
					  { 0, 0 }, { ts, ts }, { ts, 0 } },
		texcoords2 = { { 0, 0 }, { 0, 1 }, { 1, 1 },
					   { 0, 0 }, { 1, 1 }, { 1, 0 } },
		colors = { RL.WHITE, RL.WHITE, RL.WHITE,
				   RL.WHITE, RL.WHITE, RL.WHITE },
		normals = { { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 },
				    { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } },
	}
	mesh = RL.GenMeshCustom( meshData, true )

	tileTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/tile.png" )
	RL.GenTextureMipmaps( tileTexture )
	RL.SetTextureFilter( tileTexture, RL.TEXTURE_FILTER_TRILINEAR )
	lightmap = RL.LoadTexture( RL.GetBasePath().."../resources/images/lightmap.png" )
	RL.GenTextureMipmaps( lightmap )
	RL.SetTextureFilter( lightmap, RL.TEXTURE_FILTER_TRILINEAR )
	RL.SetTextureWrap( lightmap, RL.TEXTURE_WRAP_CLAMP )

	shader = RL.LoadShader( RL.GetBasePath().."../resources/shaders/glsl330/lightmap.vs",
						    RL.GetBasePath().."../resources/shaders/glsl330/lightmap.fs" )

	local materialData = {
		shader = shader,
		maps = {
			{
				RL.MATERIAL_MAP_ALBEDO,
				{
					texture = tileTexture,
					color = RL.WHITE,
					value = 1.0,
				},
			},
			{
				RL.MATERIAL_MAP_METALNESS,
				{
					texture = lightmap,
					color = RL.WHITE,
					value = 1.0,
				},
			},
		},
	}
	material = RL.CreateMaterial( materialData )

	matrix = RL.MatrixMultiply( RL.MatrixIdentity(), RL.MatrixTranslate( { -4, 0, -4 } ) )
end

function RL.draw()
	RL.ClearBackground( { 25, 50, 50 } )
	-- RL.UpdateCamera3D( camera, RL.CAMERA_ORBITAL )
	-- RL.UpdateCamera3D( camera, RL.CAMERA_FREE )
	RL.UpdateCamera3D( camera, RL.CAMERA_FIRST_PERSON )

	RL.BeginMode3D( camera )
		RL.DrawMesh( mesh, material, matrix )
	RL.EndMode3D()
end
