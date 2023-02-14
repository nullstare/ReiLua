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

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetScreenSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowTitle( "Instancing" )
	RL_SetWindowState( FLAG_VSYNC_HINT )

	-- Define the camera to look into our 3d world
	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { -125.0, 125.0, -125.0 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 1, 0 } )
	RL_SetCamera3DFovy( camera, 45 )
	RL_SetCameraMode( camera, CAMERA_ORBITAL )

	-- Define mesh to be instanced
	cube = RL_GenMeshCube( { 1, 1, 1 } )

	-- Translate and rotate cubes randomly
	for i = 1, MAX_INSTANCES do
		local translation = RL_MatrixTranslate( { math.random( -50, 50 ), math.random( -50, 50 ), math.random( -50, 50 ) } )
		local axis = RL_Vector3Normalize( { math.random( 0, 360 ), math.random( 0, 360 ), math.random( 0, 360 ) } )
		local angle = math.rad( math.random( 0, 10 ) )
		local rotation = RL_MatrixRotate( axis, angle )

		table.insert( transforms, RL_MatrixMultiply( rotation, translation ) )
	end

	-- Load lighting shader
	shader = RL_LoadShader( RL_GetBasePath().."../resources/shaders/glsl330/lighting_instancing.vs",
							RL_GetBasePath().."../resources/shaders/glsl330/lighting.fs" )

	-- Get shader locations
	local mvpLoc = RL_GetShaderLocation( shader, "mvp" )
	local viewPosLoc = RL_GetShaderLocation( shader, "viewPos" )
	local instanceTransformLoc = RL_GetShaderLocationAttrib( shader, "instanceTransform" )
	RL_SetShaderLocationIndex( shader, SHADER_LOC_MATRIX_MVP, mvpLoc )
	RL_SetShaderLocationIndex( shader, SHADER_LOC_VECTOR_VIEW, viewPosLoc )
	RL_SetShaderLocationIndex( shader, SHADER_LOC_MATRIX_MODEL, instanceTransformLoc )

	-- Set shader value: ambient light level
	local ambientLoc = RL_GetShaderLocation( shader, "ambient" )
	RL_SetShaderValue( shader, ambientLoc, { 0.2, 0.2, 0.2, 0.1 }, SHADER_UNIFORM_VEC4 )

	-- Create one light
	RL_CreateLight( LIGHT_DIRECTIONAL, { 50.0, 50.0, 0.0 }, RL_Vector3Zero(), WHITE, shader )

	-- NOTE: We are assigning the intancing shader to material.shader
    -- to be used on mesh drawing with DrawMeshInstanced()
	matInstances = RL_LoadMaterialDefault()
	RL_SetMaterialShader( matInstances, shader )
	RL_SetMaterialColor( matInstances, MATERIAL_MAP_DIFFUSE, RED )

	-- Load default material (using raylib intenral default shader) for non-instanced mesh drawing
    -- WARNING: Default shader enables vertex color attribute BUT GenMeshCube() does not generate vertex colors, so,
    -- when drawing the color attribute is disabled and a default color value is provided as input for thevertex attribute
	matDefault = RL_LoadMaterialDefault()
	RL_SetMaterialColor( matDefault, MATERIAL_MAP_DIFFUSE, BLUE )
end

function process( delta )
	RL_UpdateCamera3D( camera )

	-- Update the light shader with the camera view position
	local loc = RL_GetShaderLocationIndex( shader, SHADER_LOC_VECTOR_VIEW )
	RL_SetShaderValue( shader, loc, RL_GetCamera3DPosition( camera ), SHADER_UNIFORM_VEC3 )
end

function draw()
	RL_ClearBackground( DARKBLUE )

	RL_BeginMode3D( camera )
		-- Draw cube mesh with default material (BLUE)
		RL_DrawMesh( cube, matDefault, RL_MatrixTranslate( { -10.0, 0.0, 0.0 } ) )

		-- Draw meshes instanced using material containing instancing shader (RED + lighting),
		-- transforms[] for the instances should be provided, they are dynamically
		-- updated in GPU every frame, so we can animate the different mesh instances
		RL_DrawMeshInstanced( cube, matInstances, transforms, MAX_INSTANCES )

		-- Draw cube mesh with default material (BLUE)
		RL_DrawMesh( cube, matDefault, RL_MatrixTranslate( { 10.0, 0.0, 0.0 } ) )
	RL_EndMode3D()

	RL_DrawFPS( { 10, 10 } )
end
