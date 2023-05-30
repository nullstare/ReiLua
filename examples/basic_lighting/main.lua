-- Based on raylib [shaders] example - basic lighting by Chris Camacho (@codifies)
-- https://github.com/TSnake41/raylib-lua/blob/master/examples/textures_bunnymark.lua

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Vec3 = require( "vector3" )
Cam3D = require( "camera3d" )

local monitor = 0
local camera = {}

local plane = -1
local cube = -1
local material = -1
local shader = -1
local lights = {}

function RL.init()
	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
	local winSize = Vec2:new( 1028, 720 )

	RL.SetWindowTitle( "Simple Lighting" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	-- Define the camera to look into our 3d world.
	camera = Cam3D:new()

	camera:setPosition( { 0, 4, 12 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	-- camera.mode = camera.MODES.ORBITAL
	camera.mode = camera.MODES.FIRST_PERSON

	RL.HideCursor()

	-- Generate meshes.
	plane = RL.GenMeshPlane( 10, 10, 3, 3 )
	cube = RL.GenMeshCube( { 2, 4, 2 } )

	-- Load basic lighting shader.
	-- NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).

	-- Shader folders.
	local glslDir = {
		-- [ RL.RL_OPENGL_11 ] = "glsl100",
		-- [ RL.RL_OPENGL_21 ] = "glsl120",
		[ RL.RL_OPENGL_33 ] = "glsl330",
		[ RL.RL_OPENGL_43 ] = "glsl330",
		-- [ RL.RL_OPENGL_ES_20 ] = "glsl120",
	}
	local prefix = RL.GetBasePath().."../resources/shaders/"..glslDir[ RL.rlGetVersion() ].."/"

	shader = RL.LoadShader( prefix.."lighting.vs", prefix.."lighting.fs" )

	-- Get some required shader locations.
	local viewPosLoc = RL.GetShaderLocation( shader, "viewPos" )
	RL.SetShaderLocationIndex( shader, RL.SHADER_LOC_VECTOR_VIEW, viewPosLoc )
	--[[
		NOTE: "matModel" location name is automatically assigned on shader loading, 
		no need to get the location again if using that uniform name.
	]]--

	-- Ambient light level (some basic lighting).
	local ambientLoc = RL.GetShaderLocation( shader, "ambient" )
	RL.SetShaderValue( shader, ambientLoc, { 0.1, 0.1, 0.1, 1.0 }, RL.SHADER_UNIFORM_VEC4 )

	-- Create material.
	local materialData = {
		shader = shader,
		maps = {
			{
				RL.MATERIAL_MAP_ALBEDO,
				{
					color = RL.WHITE,
				},
			},
		},
	}
	material = RL.CreateMaterial( materialData )

	-- Create lights.
	table.insert( lights, RL.CreateLight( RL.LIGHT_POINT, { -2, 1, -2 }, RL.Vector3Zero(), RL.YELLOW, shader ) )
	table.insert( lights, RL.CreateLight( RL.LIGHT_POINT, { 2, 1, 2 }, RL.Vector3Zero(), RL.RED, shader ) )
	table.insert( lights, RL.CreateLight( RL.LIGHT_POINT, { -2, 1, 2 }, RL.Vector3Zero(), RL.GREEN, shader ) )
	table.insert( lights, RL.CreateLight( RL.LIGHT_POINT, { 2, 1, -2 }, RL.Vector3Zero(), RL.BLUE, shader ) )
end

function RL.process( delta )
	camera:process( delta )

	-- Check key inputs to enable/disable lights.
	if RL.IsKeyPressed( RL.KEY_Y ) then
		RL.SetLightEnabled( lights[1], not RL.IsLightEnabled( lights[1] ) )
	end
	if RL.IsKeyPressed( RL.KEY_R ) then
		RL.SetLightEnabled( lights[2], not RL.IsLightEnabled( lights[2] ) )
	end
	if RL.IsKeyPressed( RL.KEY_G ) then
		RL.SetLightEnabled( lights[3], not RL.IsLightEnabled( lights[3] ) )
	end
	if RL.IsKeyPressed( RL.KEY_B ) then
		RL.SetLightEnabled( lights[4], not RL.IsLightEnabled( lights[4] ) )
	end

	-- Update light values (actually, only enable/disable them).
	for _, light in ipairs( lights ) do
		RL.UpdateLightValues( shader, light )
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )

	-- Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f }).
	local loc = RL.GetShaderLocationIndex( shader, RL.SHADER_LOC_VECTOR_VIEW )
	RL.SetShaderValue( shader, loc, camera:getPosition():arr(), RL.SHADER_UNIFORM_VEC3 )

	camera:beginMode3D()
		RL.DrawMesh( plane, material, RL.MatrixIdentity() )
		RL.DrawMesh( cube, material, RL.MatrixIdentity() )

		-- Draw spheres to show where the lights are.
		for _, light in ipairs( lights ) do
			if RL.IsLightEnabled( light ) then
				RL.DrawSphereEx( RL.GetLightPosition( light ), 0.2, 8, 8, RL.GetLightColor( light ) )
			else
				RL.DrawSphereWires( RL.GetLightPosition( light ), 0.2, 8, 8, RL.ColorAlpha( RL.GetLightColor( light ), 0.3 ) )
			end
		end

	camera:endMode3D()

	RL.DrawText( 0, "Use keys [Y][R][G][B] to toggle lights", { 10, 10 }, 20, 4, RL.DARKGRAY )
end
