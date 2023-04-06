--[[
	This example is translated from "raylib [shaders] example - Mesh instancing"
	-- https://github.com/raysan5/raylib/blob/master/examples/shaders/shaders_mesh_instancing.c

	Contributed by @seanpringle
	Reviewed by Max (@moliad) and Ramon Santamaria (@raysan5)

	Modified by Jussi Viitala (@nullstare) for ReiLua style.
]]

local MAX_INSTANCES = 10000

local cube
local transforms = {}
local camera

local shader
local matInstances
local matDefault

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL.SetWindowTitle( "Instancing" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	-- Define the camera to look into our 3d world
	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { -125.0, 125.0, -125.0 } )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )
	RL.SetCamera3DFovy( camera, 45 )
	RL.SetCameraMode( camera, RL.CAMERA_ORBITAL )

	-- Define mesh to be instanced
	cube = RL.GenMeshCube( { 1, 1, 1 } )

	-- Translate and rotate cubes randomly
	for i = 1, MAX_INSTANCES do
		local translation = RL.MatrixTranslate( { math.random( -50, 50 ), math.random( -50, 50 ), math.random( -50, 50 ) } )
		local axis = RL.Vector3Normalize( { math.random( 0, 360 ), math.random( 0, 360 ), math.random( 0, 360 ) } )
		local angle = math.rad( math.random( 0, 10 ) )
		local rotation = RL.MatrixRotate( axis, angle )

		table.insert( transforms, RL.MatrixMultiply( rotation, translation ) )
	end

	-- Load lighting shader
	shader = RL.LoadShader( RL.GetBasePath().."../resources/shaders/glsl330/lighting_instancing.vs",
							RL.GetBasePath().."../resources/shaders/glsl330/lighting.fs" )

	-- Get shader locations
	local mvpLoc = RL.GetShaderLocation( shader, "mvp" )
	local viewPosLoc = RL.GetShaderLocation( shader, "viewPos" )
	local instanceTransformLoc = RL.GetShaderLocationAttrib( shader, "instanceTransform" )
	RL.SetShaderLocationIndex( shader, RL.SHADER_LOC_MATRIX_MVP, mvpLoc )
	RL.SetShaderLocationIndex( shader, RL.SHADER_LOC_VECTOR_VIEW, viewPosLoc )
	RL.SetShaderLocationIndex( shader, RL.SHADER_LOC_MATRIX_MODEL, instanceTransformLoc )

	-- Set shader value: ambient light level
	local ambientLoc = RL.GetShaderLocation( shader, "ambient" )
	RL.SetShaderValue( shader, ambientLoc, { 0.2, 0.2, 0.2, 0.1 }, RL.SHADER_UNIFORM_VEC4 )

	-- Create one light
	RL.CreateLight( RL.LIGHT_DIRECTIONAL, { 50.0, 50.0, 0.0 }, RL.Vector3Zero(), RL.WHITE, shader )

	-- NOTE: We are assigning the intancing shader to material.shader
    -- to be used on mesh drawing with DrawMeshInstanced()
	matInstances = RL.LoadMaterialDefault()
	RL.SetMaterialShader( matInstances, shader )
	RL.SetMaterialColor( matInstances, RL.MATERIAL_MAP_DIFFUSE, RL.RED )

	-- Load default material (using raylib intenral default shader) for non-instanced mesh drawing
    -- WARNING: Default shader enables vertex color attribute BUT GenMeshCube() does not generate vertex colors, so,
    -- when drawing the color attribute is disabled and a default color value is provided as input for thevertex attribute
	matDefault = RL.LoadMaterialDefault()
	RL.SetMaterialColor( matDefault, RL.MATERIAL_MAP_DIFFUSE, RL.BLUE )
end

function RL.process( delta )
	RL.UpdateCamera3D( camera )

	-- Update the light shader with the camera view position
	local loc = RL.GetShaderLocationIndex( shader, RL.SHADER_LOC_VECTOR_VIEW )
	RL.SetShaderValue( shader, loc, RL.GetCamera3DPosition( camera ), RL.SHADER_UNIFORM_VEC3 )
end

function RL.draw()
	RL.ClearBackground( RL.DARKBLUE )

	RL.BeginMode3D( camera )
		-- Draw cube mesh with default material (BLUE)
		RL.DrawMesh( cube, matDefault, RL.MatrixTranslate( { -10.0, 0.0, 0.0 } ) )

		-- Draw meshes instanced using material containing instancing shader (RED + lighting),
		-- transforms[] for the instances should be provided, they are dynamically
		-- updated in GPU every frame, so we can animate the different mesh instances
		RL.DrawMeshInstanced( cube, matInstances, transforms, MAX_INSTANCES )

		-- Draw cube mesh with default material (BLUE)
		RL.DrawMesh( cube, matDefault, RL.MatrixTranslate( { 10.0, 0.0, 0.0 } ) )
	RL.EndMode3D()

	RL.DrawFPS( { 10, 10 } )
end
