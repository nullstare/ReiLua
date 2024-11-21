local camera = -1
local sphereMesh = -1
local ray = { { 0.5, 0, 4 }, { 0.1, 0, -1 } }
local rayCol = {}

local function setupWindow()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
end

local function ray_collision()
	rayCol = RL.GetRayCollisionMesh( ray, sphereMesh, RL.MatrixIdentity() )

	if rayCol ~= nil and rayCol.hit then
		print( "hit", rayCol.hit )
		print( "distance", rayCol.distance )
		print( "point", rayCol.point[1], rayCol.point[2], rayCol.point[3] )
		print( "normal", rayCol.normal[1], rayCol.normal[2], rayCol.normal[3] )
	end
end

function RL.init()
	setupWindow()

	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { 0, 2, 4 } )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )

	sphereMesh = RL.GenMeshSphere( 1.0, 8, 10 )

	ray_collision()
end

function RL.update( delta )
	if RL.IsMouseButtonPressed( 0 ) then
		ray = RL.GetScreenToWorldRay( RL.GetMousePosition(), camera )
		ray_collision()
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )
	RL.UpdateCamera3D( camera, RL.CAMERA_FIRST_PERSON )

	RL.BeginMode3D( camera )
		RL.DrawGrid( 8, 1 )
		RL.DrawRay( ray, { 255, 100, 100 } )

		RL.DrawMesh( sphereMesh, RL.GetMaterialDefault(), RL.MatrixIdentity() )
		RL.DrawSphereWires( rayCol.point, 0.05, 4, 8, RL.BLUE )
		RL.DrawLine3D( rayCol.point, RL.Vector3Add( rayCol.point, rayCol.normal ), RL.GREEN )
	RL.EndMode3D()
end
