-- Based on JeffM2501 stencil_reflection example for Raylib https://github.com/raylib-extras/examples-cpp/blob/main/stencil_reflection/main.cpp

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vec2 = require( "vector2" )
Cam3D = require( "camera3d" )

local monitor = 0
local camera = Cam3D:new()

function RL.init()
	RL.SetWindowTitle( "Stencil Reflection" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )

	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
	local winSize = Vec2:new( RL.GetScreenSize() )

	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	camera:setPosition( { 0, 2, 6 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	camera.mode = camera.MODES.ORBITAL
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
	RL.ClearBackground( RL.BLACK )

	camera:beginMode3D()
		RL.DrawCube( { 0, 0.5, 0 }, { 1, 1, 1 }, RL.DARKGREEN )
		RL.rlDrawRenderBatchActive()

		RL.glEnable( RL.GL_STENCIL_TEST )

		RL.glStencilFunc( RL.GL_ALWAYS, 1, 0xFF ) -- Set any stencil to 1
		RL.glStencilOp( RL.GL_KEEP, RL.GL_KEEP, RL.GL_REPLACE )
		RL.glStencilMask( 0xFF ) -- Write to stencil buffer.
		RL.rlDisableDepthMask()
		RL.glClear( RL.GL_STENCIL_BUFFER_BIT ) -- Clear stencil buffer (0 by default)

		RL.DrawPlane( { 0, 0, 0 }, { 3, 3 }, RL.DARKBLUE )
		RL.rlDrawRenderBatchActive()

		RL.glStencilFunc( RL.GL_EQUAL, 1, 0xFF ) -- Pass test if stencil value is 1.
		RL.glStencilMask( 0x00 ) -- Don't write anything to stencil buffer.
		RL.rlEnableDepthMask()

		RL.DrawCube( { 0, -0.5, 0 }, { 1, 1, 1 }, RL.ColorAlpha( RL.DARKGREEN, 0.5 ) )
		RL.rlDrawRenderBatchActive()

		RL.glDisable( RL.GL_STENCIL_TEST )
	camera:endMode3D()
end
