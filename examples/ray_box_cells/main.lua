package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Vector3 = require( "vector3" )
Rectangle = require( "rectangle" )
BoundinBox = require( "bounding_box" )
Cam3D = require( "camera3d" )

local monitor = 0
local camera = {}

local box = BoundinBox:new( { -8, 0, -8 }, { 16, 16, 16 } )
local cellSize = Vector3:new( 1, 1, 1 )
local drawCellSize = cellSize:clone()
local ray = nil
local rayCol = nil
local cells = {}
local exitPoint = {}

local guiMouseHover = false
local spinnerEdit = {
	x = false,
	y = false,
	z = false
}

function RL.init()
	local mPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local mSize = Vector2:newT( RL.GetMonitorSize( monitor ) )
	local winSize = Vector2:new( 1028, 720 )

	RL.SetWindowTitle( "Ray box cells" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )
	RL.SetTextLineSpacing( 26 )

	camera = Cam3D:new()

	camera:setPosition( { 0, 8, 16 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	camera.mode = camera.MODES.FREE

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 24 )
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

	-- Raycast.

	-- if not guiMouseHover then
	if not guiMouseHover and RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) then
		ray = RL.GetMouseRay( RL.GetMousePosition(), camera.camera )
		rayCol = box:getRayCollision( ray )

		cells, exitPoint = RL.GetRayBoxCells( ray, box:maxToPos(), cellSize )
		drawCellSize:setV( cellSize )
	end
end

local function drawSpinner( axis, pos )
	local result = 0
	local bounds = Rectangle:temp( pos.x, pos.y, 96, 24 )

	result, cellSize[ axis ] = RL.GuiSpinner( bounds, axis, cellSize[ axis ], 1, box.max[ axis ], spinnerEdit[ axis ] )

	if result == 1 then
		spinnerEdit[ axis ] = not spinnerEdit[ axis ]
	end

	if bounds:checkCollisionPoint( RL.GetMousePosition() ) then
		guiMouseHover = true
	end
end

function RL.draw()
	RL.ClearBackground( RL.LIGHTGRAY )

	camera:beginMode3D()
		RL.DrawGrid( 16, 1 )
		RL.DrawCubeWires( box.min + box.max:scale( 0.5 ), box.max, RL.WHITE )

		if ray then
			RL.DrawRay( ray, RL.BLUE )
			RL.DrawSphere( ray[1], 0.1, RL.GREEN )
		end
		if rayCol and rayCol.hit then
			RL.DrawSphere( rayCol.point, 0.1, RL.RED )
		end
		if exitPoint.hit then
			RL.DrawSphere( exitPoint.point, 0.1, RL.RED )
		end
		if cells then
			for _, cell in ipairs( cells ) do
				RL.DrawCubeWires( box.min + Vector3:tempT( cell ) * drawCellSize + drawCellSize:scale( 0.5 ), drawCellSize, RL.RED )
				RL.DrawCube( box.min + Vector3:tempT( cell ) * drawCellSize + drawCellSize:scale( 0.5 ), drawCellSize, { 150, 200, 150, 150 } )
			end
		end
	camera:endMode3D()

	guiMouseHover = false

	drawSpinner( "x", Vector2:temp( 16, 2 ) )
	drawSpinner( "y", Vector2:temp( 16, 22 ) )
	drawSpinner( "z", Vector2:temp( 16, 44 ) )
end
