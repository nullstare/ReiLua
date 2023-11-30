package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Raygui = require( "raygui" )

local grid = {}
local windowbox = {}
local tabBar = {}
local texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/gradient.png" )
local textureRect = Rect:new( 0, 0, RL.GetTextureSize( texture )[1], RL.GetTextureSize( texture )[2] )

local function closeTab( self, id )
	local splits = Util.split( tabBar.text, ";" )
	local newText = ""

	if #splits == 1 then
		Raygui.remove( tabBar )
	end
	table.remove( splits, id + 1 )

	for i, tab in ipairs( splits ) do
		newText = newText..tab

		if i < #splits then
			newText = newText..";"
		end
	end
	self.text = newText
end

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = { 1920, 1080 }

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )
	RL.GuiSetStyle( RL.SPINNER, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_RIGHT )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.RED ) )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.ORANGE ) )
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( RL.GREEN ) )

	local label = Raygui.Label:new(
		Rect:new( 16, 16, 64, 32 ),
		"Cat"
	)
	local toggleGroup = Raygui.ToggleGroup:new(
		Rect:new( 68, 16, 64, 32 ),
		"Cat\nDog",
		0,
		function( self ) print( self:getItem( self.active ) ) end
	)
	local button = Raygui.Button:new(
		Rect:new( 245, 188, 64, 32 ),
		"Dog",
		function() toggleGroup:setText( "Dog;Cat\nEagle" ) end,
		texture,
		textureRect
	)
	local checkbox = Raygui.CheckBox:new(
		Rect:new( 64, 128, 20, 20 ),
		"Dog",
		false,
		nil,
		texture,
		textureRect
	)
	local combobox = Raygui.ComboBox:new(
		Rect:new( 64, 256, 128, 32 ),
		"Dog\nCow\nDonkey",
		0
	)
	local dropdownbox = Raygui.DropdownBox:new(
		Rect:new( 256, 128, 128, 32 ),
		"Dog\nGiraffe\nLion\nHorse",
		0,
		false,
		function( self ) print( self:getItem( self.active ) ) end
	)
	local spinner = Raygui.Spinner:new(
		Rect:new( 464, 256, 128, 32 ),
		"Health",
		0,
		0,
		10,
		false,
		function( self ) print( "Spinner value changed to "..self.value ) end
	)
	local valuebox = Raygui.ValueBox:new(
		Rect:new( 464, 316, 128, 32 ),
		"Health",
		0,
		0,
		100,
		false,
		function( self ) print( "ValueBox value changed to "..self.value ) end
	)
	local textbox = Raygui.TextBox:new(
		Rect:new( 32, 316, 256, 32 ),
		"Name",
		32,
		false,
		function( self ) print( "Set text "..self.text ) end
	)
	local textbox2 = Raygui.TextBox:new(
		Rect:new( 32, 380, 256, 32 ),
		"Name",
		32,
		false,
		function( self ) print( "Set text "..self.text ) end
	)
	local slider = Raygui.Slider:new(
		Rect:new( 50, 500, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end,
		texture,
		textureRect
	)
	local sliderbar = Raygui.SliderBar:new(
		Rect:new( 50, 550, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end

	)
	local progressbar = Raygui.ProgressBar:new(
		Rect:new( 50, 600, 256, 32 ),
		"min",
		"max",
		20,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	)
	local statusbar = Raygui.StatusBar:new(
		Rect:new( 50, 650, 256, 32 ),
		"StatusBar"
	)
	local dummyrec = Raygui.DummyRec:new(
		Rect:new( 50, 700, 256, 32 ),
		"DummyRec"
	)
	grid = Raygui.Grid:new(
		Rect:new( 400, 400, 256, 256 ),
		"Grid",
		32,
		2
	)
	windowbox = Raygui.WindowBox:new(
		Rect:new( 720, 250, 256, 256 ),
		"WindowBox",
		-- Close callback.
		function( self ) self.visible = false end,
		-- Grab callback.
		function( self ) Raygui.set2Top( self ) end,
		nil,
		texture,
		textureRect
	)
	local groupbox = Raygui.GroupBox:new(
		Rect:new( 400, 700, 256, 256 ),
		"GroupBox"
	)
	local line = Raygui.Line:new(
		Rect:new( 400, 32, 256, 16 ),
		"Line"
	)
	local panel = Raygui.Panel:new(
		Rect:new( 400, 64, 256, 128 ),
		"Panel",
		-- Grab callback.
		function( self ) Raygui.set2Top( self ) end
	)
	tabBar = Raygui.GuiTabBar:new(
		Rect:new( 700, 520, 700, 32 ),
		"Cat;Dog;Horse;Cow",
		0,
		-- function( self ) Raygui.set2Top( self ) end
		nil,
		closeTab,
		texture,
		textureRect
	)
	local scrollpanel = Raygui.ScrollPanel:new(
		Rect:new( 800, 64, 256, 256 ),
		"ScrollPanel",
		Rect:new( 0, 0, 256, 600 ),
		Vec2:new( 0, 0 ),
		-- Callback.
		nil,
		-- Grab callback.
		function( self ) Raygui.set2Top( self ) end
	)
	local listview = Raygui.ListView:new(
		Rect:new( 1100, 64, 128, 80 ),
		"Cat;Dog;Horse;Cow;Pig;Eagle;Lion",
		0,
		0,
		function( self ) print( self:getItem( self.active ) ) end,
		texture,
		textureRect
	)
	local listviewex = Raygui.ListViewEx:new(
		Rect:new( 1300, 64, 128, 80 ),
		"Cat;Dog;Horse;Cow;Pig;Eagle;Lion",
		0,
		0,
		0,
		function( self ) print( self:getItem( self.active ) ) end,
		texture,
		textureRect
	)
	local messagebox = Raygui.MessageBox:new(
		Rect:new( 1100, 150, 300, 128 ),
		"Title",
		"Message",
		"Cancel;Ok",
		function( self )
			if 0 < self.buttonIndex then
				print( "You pressed "..self:getItem( self.buttonIndex ) )

				if self.buttonIndex == 1 then
					Raygui.set2Back( windowbox )
				elseif self.buttonIndex == 2 then
					Raygui.set2Top( windowbox )
				end
			end
		end,
		-- Grab callback.
		function( self ) Raygui.set2Top( self ) end
	)
	local textinputbox = Raygui.TextInputBox:new(
		Rect:new( 1100, 300, 300, 128 ),
		"Title",
		"Message",
		"Cancel;Ok",
		"Text",
		8,
		false,
		function( self )
			if 0 < self.buttonIndex then
				print( "You pressed "..self:getItem( self.buttonIndex ) )
			end
		end,
		-- Grab callback.
		function( self ) Raygui.set2Top( self ) end
	)
	local colorpicker = Raygui.ColorPicker:new(
		Rect:new( 1500, 32, 128, 128 ),
		"Color Picker",
		Color:new()
	)
	local colorpanel = Raygui.ColorPanel:new(
		Rect:new( 1700, 32, 128, 128 ),
		"Color Panel",
		Color:new()
	)
	local colorbaralpha = Raygui.ColorBarAlpha:new(
		Rect:new( 1700, 180, 128, 20 ),
		"Color Panel",
		1.0
	)
	local colorbarhue = Raygui.ColorBarHue:new(
		Rect:new( 1840, 32, 20, 128 ),
		"Color Panel",
		1.0
	)
end

function RL.process( delta )
	Raygui.process()
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	if 0 <= grid.mouseCell.x then
		RL.DrawRectangleLines(
			{
				grid.bounds.x + grid.mouseCell.x * 32,
				grid.bounds.y + grid.mouseCell.y * 32,
				32,
				32
			},
			RL.GREEN
		)
	end

    Raygui.draw()
end
