package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Vector3 = require( "vector3" )
Color = require( "color" )

-- Defines
local RESOLUTION = Vector2:new( 1280, 1024 )
local TILE_SIZE_PX = 32
local LIGHTRENDER_SIZE = 1024 -- Maxinum light size.
local SHADOW_FOV = 45 -- Camera fov for shadow rendering.
local WALL_MESH_HEIGHT = math.tan( RL.DEG2RAD * ( 90 - SHADOW_FOV / 2 ) ) * LIGHTRENDER_SIZE / TILE_SIZE_PX / 2

print( "WALL_MESH_HEIGHT", WALL_MESH_HEIGHT )

local monitor = 0
local monitorPos = Vector2:new( RL.GetMonitorPosition( monitor ) )
local monitorSize = Vector2:new( RL.GetMonitorSize( monitor ) )
local winScale = 1
local winSize = Vector2:new( RESOLUTION.x * winScale, RESOLUTION.y * winScale )

local tileTex = nil
local lightTex = nil
local lightTexSize = Vector2:new()
local framebuffer = nil
local lightMap = nil -- Final image of all lights.
local lightRender = nil -- RenderTexture for individual light and shadow rendering.
local ambientLight = Color:new( 40, 40, 40 )
local wallSegs = {}
local shadowMesh = nil
local lights = {}
local camera = nil -- 3D camera for shadow rendering.

-- Init.

local function addLight( pos, color, radius )
	table.insert( lights, {
		pos = pos,
		color = color,
		radius = radius
	} )
end

local function addWallSeg( p1, p2 )
	table.insert( wallSegs, {
		p1 = p1,
		p2 = p2
	} )
end

-- We will create 3D "wall" mesh for the shadows.
local function createShadowMesh()
	addWallSeg( Vector2:new( 0, 0 ), Vector2:new( 500, 160 ) )
	addWallSeg( Vector2:new( 200, 230 ), Vector2:new( 400, 320 ) )
	addWallSeg( Vector2:new( 600, 500 ), Vector2:new( 800, 360 ) )
	addWallSeg( Vector2:new( 800, 360 ), Vector2:new( 900, 500 ) )
	addWallSeg( Vector2:new( 500, 400 ), Vector2:new( 460, 600 ) )
	addWallSeg( Vector2:new( 300, 600 ), Vector2:new( 360, 800 ) )
	addWallSeg( Vector2:new( 360, 800 ), Vector2:new( 550, 900 ) )
	addWallSeg( Vector2:new( 760, 600 ), Vector2:new( 900, 500 ) )
	addWallSeg( Vector2:new( 960, 500 ), Vector2:new( 1200, 420 ) )
	addWallSeg( Vector2:new( 840, 800 ), Vector2:new( 960, 950 ) )

	-- Box.
	addWallSeg( Vector2:new( 4 * 32, 15 * 32 ), Vector2:new( 5 * 32, 15 * 32 ) )
	addWallSeg( Vector2:new( 4 * 32, 15 * 32 ), Vector2:new( 4 * 32, 16 * 32 ) )
	addWallSeg( Vector2:new( 4 * 32, 16 * 32 ), Vector2:new( 5 * 32, 16 * 32 ) )
	addWallSeg( Vector2:new( 5 * 32, 15 * 32 ), Vector2:new( 5 * 32, 16 * 32 ) )

	-- Create wall mesh.
	local meshData = { vertices = {} }

	for _, s in ipairs( wallSegs ) do
		local seg = {
			p1 = Vector2:new( s.p1.x / TILE_SIZE_PX, s.p1.y / TILE_SIZE_PX ),
			p2 = Vector2:new( s.p2.x / TILE_SIZE_PX, s.p2.y / TILE_SIZE_PX )
		}
		table.insert( meshData.vertices, Vector3:new( seg.p1.x, WALL_MESH_HEIGHT, seg.p1.y ) )
		table.insert( meshData.vertices, Vector3:new( seg.p1.x, 0, seg.p1.y ) )
		table.insert( meshData.vertices, Vector3:new( seg.p2.x, 0, seg.p2.y ) )
		table.insert( meshData.vertices, Vector3:new( seg.p1.x, WALL_MESH_HEIGHT, seg.p1.y ) )
		table.insert( meshData.vertices, Vector3:new( seg.p2.x, 0, seg.p2.y ) )
		table.insert( meshData.vertices, Vector3:new( seg.p2.x, WALL_MESH_HEIGHT, seg.p2.y ) )
	end
	shadowMesh = RL.GenMeshCustom( meshData, false )
end

function RL.init()
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )
	RL.SetWindowTitle( "2D Lights" )

	framebuffer = RL.LoadRenderTexture( RESOLUTION )
	lightMap = RL.LoadRenderTexture( RESOLUTION )
	lightRender = RL.LoadRenderTexture( { LIGHTRENDER_SIZE, LIGHTRENDER_SIZE } )
	tileTex = RL.LoadTexture( RL.GetBasePath().."../resources/images/tile.png" )
	lightTex = RL.LoadTexture( RL.GetBasePath().."../resources/images/light.png" )
	lightTexSize = Vector2:new( RL.GetTextureSize( lightTex ) )

	RL.SetTextureFilter( tileTex, RL.TEXTURE_FILTER_TRILINEAR )
	RL.SetTextureFilter( lightTex, RL.TEXTURE_FILTER_TRILINEAR )

	createShadowMesh()

	addLight( Vector2:new( 230, 480 ), Color:new( RL.ORANGE ), 512 )
	addLight( Vector2:new( 600, 200 ), Color:new( RL.RED ), 512 )
	addLight( Vector2:new( 384, 520 ), Color:new( RL.GREEN ), 400 )
	addLight( Vector2:new( 880, 750 ), Color:new( RL.BLUE ), 300 )
	addLight( Vector2:new( 800, 500 ), Color:new( RL.PURPLE ), 512 )
	addLight( Vector2:new( 200, 760 ), Color:new( RL.WHITE ), 400 )

	-- Stress test

	-- for i = 1, 300 do
	-- 	addLight( Vector2:new( math.random( 20, RESOLUTION.x - 20 ), math.random( 20, RESOLUTION.y - 20 ) ),
	-- 		Color:new( { math.random( 40, 255 ), math.random( 40, 255 ), math.random( 40, 255 ), 255 } ),
	-- 		128
	-- 	)
	-- end

	-- Camera for shadow rendering.
	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { 0, 5, 0 } )
	RL.SetCamera3DTarget( camera, { 0, 0, -0.001 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )
	RL.SetCamera3DFovy( camera, SHADOW_FOV )

	RL.SetMouseScale( { 1 / winScale, 1 / winScale } )
	-- Render both sides of the shadow. Could be usefull to set off to prevent self shadowing.
	RL.rlDisableBackfaceCulling()
end

-- Update.

function RL.update( delta )
	lights[1].pos:set( RL.GetMousePosition() )
end

-- Drawing.

local function drawLight( light )
	RL.BeginTextureMode( lightRender )
		RL.ClearBackground( RL.BLANK )
		RL.DrawTexturePro(
			lightTex,
			{ 0, 0, lightTexSize.x, lightTexSize.y },
			{ LIGHTRENDER_SIZE / 2, LIGHTRENDER_SIZE / 2, light.radius * 2, light.radius * 2 },
			{ light.radius, light.radius },
			0.0,
			light.color
		)
		-- Draw shadows.
		local cameraPos = Vector2:new( light.pos.x / TILE_SIZE_PX, light.pos.y / TILE_SIZE_PX )

		RL.SetCamera3DPosition( camera, { 0, WALL_MESH_HEIGHT, 0 } )
		RL.SetCamera3DTarget( camera, { 0, 0, -0.0001 } )

		RL.rlSetBlendFactors( RL.RL_ZERO, RL.RL_ONE_MINUS_SRC_COLOR, RL.RL_FUNC_ADD )
		RL.BeginBlendMode( RL.BLEND_CUSTOM )
		RL.BeginMode3D( camera )
			RL.DrawMesh(
				shadowMesh,
				RL.GetMaterialDefault(),
				RL.MatrixMultiply(
					RL.MatrixTranslate( { -cameraPos.x, 0, -cameraPos.y } ),
					RL.MatrixScale( { 1, 1, -1 } ) -- Flip mesh.
				)
			)
		RL.EndMode3D()
		RL.EndBlendMode()
	RL.EndTextureMode()
	-- Draw light to lightmap.
	RL.BeginTextureMode( lightMap )
	RL.BeginBlendMode( RL.BLEND_ADDITIVE )
		RL.DrawTexturePro(
			RL.GetRenderTextureTexture( lightRender ),
			{ 0, 0, LIGHTRENDER_SIZE, LIGHTRENDER_SIZE },
			{ light.pos.x, light.pos.y, LIGHTRENDER_SIZE, LIGHTRENDER_SIZE },
			{ LIGHTRENDER_SIZE / 2, LIGHTRENDER_SIZE / 2 },
			0.0,
			light.color
		)
	RL.EndBlendMode()
	RL.EndTextureMode()
end

local function drawLights()
	RL.BeginTextureMode( lightMap )
		RL.ClearBackground( ambientLight )
	RL.EndTextureMode()

	for _, light in ipairs( lights ) do
		drawLight( light )
	end
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )

	drawLights()
	-- Draw to framebuffer.
	RL.BeginTextureMode( framebuffer )
		RL.ClearBackground( RL.BLACK )
		-- Floor.
		RL.DrawTextureRec(
			tileTex,
			{ 0, 0, RESOLUTION.x, RESOLUTION.y },
			{ 0, 0 },
			RL.WHITE
		)
		-- Wall lines.
		for _, seg in ipairs( wallSegs ) do
			RL.DrawLine( seg.p1, seg.p2, 3.0, RL.BLACK )
		end
		-- Lightmap.
		RL.rlSetBlendFactors( RL.RL_DST_COLOR, RL.RL_SRC_COLOR, RL.RL_FUNC_ADD )
		RL.BeginBlendMode( RL.BLEND_CUSTOM )
			RL.DrawTexturePro(
				RL.GetRenderTextureTexture( lightMap ),
				{ 0, 0, RESOLUTION.x, -RESOLUTION.y },
				{ 0, 0, RESOLUTION.x, RESOLUTION.y },
				{ 0, 0 },
				0.0,
				RL.WHITE
			)
		RL.EndBlendMode()
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
	-- RL.DrawRectangle( { 0, 0, 96, 32 }, RL.BLACK )
	-- RL.DrawFPS( { 10, 10 } )
end
