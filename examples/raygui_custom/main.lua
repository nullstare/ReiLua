package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Rect = require( "rectangle" )
Raygui = require( "raygui" )

Gui = Raygui:new()
SpriteButton = require( "spriteButton" )
SpriteButton:register( Gui )
local buttonTexture = nil

local resolution = Vec2:new( 640, 480 )
local winSize = Vec2:new()
local framebuffer = nil

local function addButton( bounds, text, callback )
	local button = Gui:SpriteButton(
		bounds,
		text,
		buttonTexture,
		{ source = { 0, 0, 48, 48 }, left = 16, top = 16, right = 16, bottom = 16, layout = RL.NPATCH_NINE_PATCH },
		{ source = { 48, 0, 48, 48 }, left = 16, top = 16, right = 16, bottom = 16, layout = RL.NPATCH_NINE_PATCH },
		callback
	)
	button.styles = {
		{ RL.LABEL, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_CENTER },
		{ RL.LABEL, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( { 84, 59, 22 } ) },
		{ RL.LABEL, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( { 84/2, 59/2, 22/2 } ) },
		{ RL.LABEL, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.GREEN ) },
	}
end

function RL.init()
	local monitor = 0
	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
	local winScale = 2
	winSize = resolution:scale( winScale )

	framebuffer = RL.LoadRenderTexture( resolution )

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( resolution:scale( winScale ) )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	RL.SetMouseScale( { 1/winScale, 1/winScale } )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )

	buttonTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/button.png" )
	
	local buttonSize = Vec2:new( 216, 32 )
	local bounds = Rect:new( resolution.x / 2 - buttonSize.x / 2, 200, buttonSize.x, buttonSize.y )
	local gap = buttonSize.y + 2
	addButton( bounds, "Start New Game", function() print( "New Game!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Load Game", function() print( "Load Game!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Options", function() print( "Options!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Quit", function() RL.CloseWindow() end )
end

function RL.process( delta )
	Gui:process()
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )
	RL.BeginTextureMode( framebuffer )
		RL.ClearBackground( { 50, 20, 75 } )
		Gui:draw()
	RL.EndTextureMode()

	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( framebuffer ),
		{ 0, 0, resolution.x, -resolution.y },
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0 },
		0.0,
		RL.WHITE
	)
end
