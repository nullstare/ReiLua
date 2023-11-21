package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"


Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Raygui = require( "raygui" )
Calculator = require( "calculator" )

local calculator = nil
local calculator2 = nil

function RL.init()
	local monitor = 0
	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
	local winSize = Vec2:new( 1024, 800 )

	RL.SetWindowTitle( "Raygui examples" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )

	calculator = Calculator:new( Vec2:new( 32, 32 ) )
	calculator2 = Calculator:new( Vec2:new( 64, 65 ) )
end

function RL.process( delta )
	Raygui:process()
end

function RL.draw()
	RL.ClearBackground( RL.DARKBLUE )

	Raygui:draw()
end
