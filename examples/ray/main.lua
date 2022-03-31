local camera = -1
local sphereMesh = -1
local ray = { { 0.5, 0, 4 }, { 0.1, 0, -1 } }

local function setupWindow()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
end

function ray_collision()
	local rayCol = RL_GetRayCollisionMesh( ray, sphereMesh, RL_MatrixIdentity() )

	if rayCol ~= nil and rayCol.hit then
		print( "hit", rayCol.hit )
		print( "distance", rayCol.distance )
		print( "point", rayCol.point[1], rayCol.point[2], rayCol.point[3] )
		print( "normal", rayCol.normal[1], rayCol.normal[2], rayCol.normal[3] )
	end
end

function init()
	setupWindow()

	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { 0, 2, 4 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 2, 0 } )
	RL_SetCamera3DMode( camera, CAMERA_FREE )

	sphereMesh = RL_GenMeshSphere( 1.0, 8, 10 )

	ray_collision()
end

function process( delta )
	if RL_IsMouseButtonPressed( 0 ) then
		ray = RL_GetMouseRay( RL_GetMousePosition(), camera )
		ray_collision()
	end
end

function draw()
	RL_ClearBackground( { 100, 150, 100 } )
	RL_UpdateCamera3D( camera )
	
	RL_BeginMode3D( camera )
		RL_DrawGrid( 8, 1 )
		RL_DrawRay( ray, { 255, 100, 100 } )

		RL_DrawMesh( sphereMesh, 0, RL_MatrixIdentity() )
	RL_EndMode3D()
end
