package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Cam3D = require( "camera3d" )

local PLANE_SIZE = 8

local GLSL_VERSION = "330" -- PLATFORM_DESKTOP
-- local GLSL_VERSION = "100" -- PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB

local monitor = 0
local camera = {}
local tileTexture = nil
local mesh = nil
local material = nil
local lightmap = nil
local shader = nil

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

	local meshData = {
		vertices = { { 0, 0, 0 }, { 0, 0, PLANE_SIZE }, { PLANE_SIZE, 0, PLANE_SIZE },
					 { 0, 0, 0 }, { PLANE_SIZE, 0, PLANE_SIZE }, { PLANE_SIZE, 0, 0 } },
		texcoords = { { 0, 0 }, { 0, PLANE_SIZE }, { PLANE_SIZE, PLANE_SIZE },
					  { 0, 0 }, { PLANE_SIZE, PLANE_SIZE }, { PLANE_SIZE, 0 } },
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
	RL.SetTextureFilter( lightmap, RL.TEXTURE_FILTER_TRILINEAR )

	shader = RL.LoadShader( RL.GetBasePath().."../resources/shaders/glsl"..GLSL_VERSION.."/lightmap.vs",
						    RL.GetBasePath().."../resources/shaders/glsl"..GLSL_VERSION.."/lightmap.fs" )

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
	matrix = RL.MatrixTranslate( { -PLANE_SIZE / 2, 0, -PLANE_SIZE / 2 } )
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
	RL.ClearBackground( { 25, 50, 50 } )

	camera:beginMode3D()
		RL.DrawMesh( mesh, material, matrix )
	camera:endMode3D()
end
