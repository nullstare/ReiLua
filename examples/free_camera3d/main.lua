package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Vec3 = require( "vector3" )
Cam3D = require( "camera3d" )

local monitor = 0
local camera = {}
local targetVisible = false

function RL.init()
	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
	local winSize = Vec2:new( 1028, 720 )

	RL.SetWindowTitle( "Free Camera3D" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	camera = Cam3D:new()

	camera:setPosition( { 0, 8, 16 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	-- camera.mode = camera.MODES.ORBITAL
	camera.mode = camera.MODES.FREE
end

function RL.process( delta )
	camera:process( delta )

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		if camera.mode == camera.MODES.FREE then
			camera.mode = camera.MODES.FIRST_PERSON
		else
			camera.mode = camera.MODES.FREE
		end
	end

	if RL.IsKeyPressed( RL.KEY_T ) then
		targetVisible = not targetVisible
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )

	camera:beginMode3D()
		RL.DrawGrid( 16, 1 )
		RL.DrawCapsule( { 0, 0, 0 }, { 0, 2, 0 }, 1.0, 8, 6, RL.BLUE )
		RL.DrawCapsuleWires( { 0, -0.01, 0 }, { 0, 2.01, 0 }, 1.01, 8, 6, RL.RED )

		if targetVisible then
			camera:draw()
		end
	camera:endMode3D()

	local text = "Press space to toggle camera mode.\nCurrent mode: "

	if camera.mode == camera.MODES.FREE then
		text = text.."FREE"
	elseif camera.mode == camera.MODES.FIRST_PERSON then
		text = text.."FIRST_PERSON"
	end

	text = text.."\nPress T to toggle target visible.\nVisible: "..tostring( targetVisible )

	RL.DrawText( 0, text, { 16, 16 }, 30, 4, RL.WHITE )
end
