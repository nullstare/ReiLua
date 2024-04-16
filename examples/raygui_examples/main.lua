package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Raygui = require( "raygui" )
Calculator = require( "calculator" )
FileBrowser = require( "file_browser" )

Gui = Raygui:new()

local showAllButton = nil
local calculator = nil
local fileBrowser = nil

local function loadFile( path )
	print( "Load file: "..path )
end

local function showAll()
	calculator:setVisible( true )
	fileBrowser:setVisible( true )
end

function RL.init()
	local monitor = 0
	local mPos = Vec2:newT( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:newT( RL.GetMonitorSize( monitor ) )
	local winSize = Vec2:new( 1024, 800 )

	RL.SetWindowTitle( "Raygui examples" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )

	RL.GuiLoadStyle( RL.GetBasePath().."../resources/styles/style_dark.rgs" )

	showAllButton = Gui:Button(
		Rect:new( 0, 0, 108, 28 ),
		"Show All",
		{ -- callbacks.
			pressed = function() showAll() end
		}
	)

	calculator = Calculator:new( Vec2:new( 32, 32 ) )
	fileBrowser = FileBrowser:new(
		Vec2:new( 250, 100 )
	)

	fileBrowser:popup( fileBrowser.MODES.OPEN, RL.GetBasePath(), loadFile )
end

function RL.update( delta )
	Gui:update()
end

function RL.draw()
	RL.ClearBackground( RL.DARKBLUE )

	Gui:draw()
end
