package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Rect = require( "rectangle" )
Raygui = require( "raygui" )

require( "sprite_button" ):register( Raygui )
require( "property_list" ):register( Raygui )

Gui = Raygui:new()

local buttonTexture = nil
local winSize = Vec2:new( 1024, 720 )

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

local function addSpriteButtons()
	buttonTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/button.png" )
	
	local buttonSize = Vec2:new( 216, 32 )
	local bounds = Rect:new( winSize.x / 2 - buttonSize.x / 2, 200, 216, 32 )
	local gap = buttonSize.y + 2
	addButton( bounds, "Start New Game", function() print( "New Game!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Load Game", function() print( "Load Game!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Options", function() print( "Options!" ) end )
	bounds.y = bounds.y + gap
	addButton( bounds, "Quit", function() RL.CloseWindow() end )
end

local function addPropertyList()
	local propertyList = Gui:PropertyList(
		Rect:new( 20, 20, 214, 256 ),
		"Property List",
		Rect:new( 0, 0, 200, 400 ),
		-- Rect:new( 0, 0, 400, 400 ),
		Vec2:new( 0, 0 ),
		-- Callback.
		nil,
		-- Grab callback.
		function( self ) Gui:set2Top( self ) end
	)
	local bounds = Rect:new( 2, 2, 200 - 4, 22 )
	local gap = bounds.height + 2

	propertyList.gui:Button(
		bounds,
		"Button",
		function() print( "Button clicked" ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:CheckBox(
		Rect:new( bounds.x, bounds.y, 20, 20 ),
		"Visible",
		false,
		function() print( "Checked!" ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:Toggle(
		bounds,
		"Toggle",
		false,
		function( self ) print( "Toggled" ) end
	)
	-----
	bounds.y = bounds.y + gap
	local dropdown = propertyList.gui:DropdownBox(
		bounds,
		"Dog\nGiraffe\nLion\nHorse",
		0,
		false,
		function( self ) print( self:getItem( self.active ) ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:Spinner(
		Rect:new( bounds.x, bounds.y, 96, 20 ),
		"Health",
		0,
		0,
		100,
		false,
		function( self ) print( "Spinner value changed to "..self.value ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:TextBox(
		bounds,
		"Name",
		32,
		false,
		function( self ) print( "Set text "..self.text ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:ColorBarAlpha(
		bounds,
		"",
		1.0
	)
	-----
	bounds.y = bounds.y + gap
	local valueBox = propertyList.gui:ValueBox(
		Rect:new( bounds.x, bounds.y, 96, 20 ),
		"Mana",
		0,
		0,
		100,
		false,
		function( self ) print( "ValueBox value changed to "..self.value ) end
	)
	valueBox.styles = {
		{ RL.VALUEBOX, RL.TEXT_PADDING, 2 },
		{ RL.VALUEBOX, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_RIGHT },
	}
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:Label(
		bounds,
		"Label"
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:Line(
		bounds,
		"Divider"
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:Slider(
		Rect:new( bounds.x + 38, bounds.y, bounds.width - 80, bounds.height ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:SliderBar(
		Rect:new( bounds.x + 38, bounds.y, bounds.width - 80, bounds.height ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:ProgressBar(
		Rect:new( bounds.x + 38, bounds.y, bounds.width - 80, bounds.height ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:ToggleGroup(
		Rect:new( bounds.x, bounds.y, 64, bounds.height ),
		"Cat;Dog;Car",
		0,
		function( self ) print( self:getItem( self.active ) ) end
	)
	-----
	bounds.y = bounds.y + gap
	propertyList.gui:ColorPicker(
		Rect:new( bounds.x, bounds.y, 128, 128 ),
		"",
		Color:new()
	)

	propertyList.content.height = bounds.y + 130
	propertyList.gui:set2Top( dropdown )
end

function RL.init()
	local monitor = 0
	local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )
	RL.GuiSetStyle( RL.SPINNER, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_RIGHT )
	RL.GuiSetStyle( RL.SPINNER, RL.TEXT_PADDING, 2 )

	addSpriteButtons()
	addPropertyList()
end

function RL.process( delta )
	Gui:process()
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )
	Gui:draw()
end
