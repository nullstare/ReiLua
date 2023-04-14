package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Raygui = require( "raygui" )

local raygui = Raygui:new()

local grid = {}
local windowbox = {}
local winOpen = true

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

	local label = raygui:add( raygui.Label:new(
		Rect:new( 16, 16, 64, 32 ),
		"Cat"
	) )
	local toggleGroup = raygui:add( raygui.ToggleGroup:new(
		Rect:new( 68, 16, 64, 32 ),
		"Cat\nDog",
		0,
		function( self ) print( self:getItem( self.active ) ) end
	) )
	local button = raygui:add( raygui.Button:new(
		Rect:new( 245, 188, 64, 32 ),
		"Dog",
		function() toggleGroup:setText( "Dog;Cat\nEagle" ) end
	) )
	local checkbox = raygui:add( raygui.CheckBox:new(
		Rect:new( 64, 128, 20, 20 ),
		"Dog",
		false
	) )
	local combobox = raygui:add( raygui.ComboBox:new(
		Rect:new( 64, 256, 128, 32 ),
		"Dog\nCow\nDonkey",
		0
	) )
	local dropdownbox = raygui:add( raygui.DropdownBox:new(
		Rect:new( 256, 128, 128, 32 ),
		"Dog\nGiraffe\nLion\nHorse",
		0,
		false,
		function( self ) print( self:getItem( self.active ) ) end
	) )
	local spinner = raygui:add( raygui.Spinner:new(
		Rect:new( 464, 256, 128, 32 ),
		"Health",
		0,
		0,
		10,
		false,
		function( self ) print( "Spinner value changed to "..self.value ) end
	) )
	local valuebox = raygui:add( raygui.ValueBox:new(
		Rect:new( 464, 316, 128, 32 ),
		"Health",
		0,
		0,
		100,
		false,
		function( self ) print( "ValueBox value changed to "..self.value ) end
	) )
	local textbox = raygui:add( raygui.TextBox:new(
		Rect:new( 32, 316, 256, 32 ),
		"Name",
		32,
		false,
		function( self ) print( "Set text "..self.text ) end
	) )
	local textboxmulti = raygui:add( raygui.TextBoxMulti:new(
		Rect:new( 32, 400, 256, 64 ),
		"Buggy?",
		32,
		false,
		function( self ) print( "Set text "..self.text ) end
	) )
	local slider = raygui:add( raygui.Slider:new(
		Rect:new( 50, 500, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	) )
	local sliderbar = raygui:add( raygui.SliderBar:new(
		Rect:new( 50, 550, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	) )
	local progressbar = raygui:add( raygui.ProgressBar:new(
		Rect:new( 50, 600, 256, 32 ),
		"min",
		"max",
		20,
		0,
		100,
		function( self ) print( "Changed value "..self.value ) end
	) )
	local statusbar = raygui:add( raygui.StatusBar:new(
		Rect:new( 50, 650, 256, 32 ),
		"StatusBar"
	) )
	local dummyrec = raygui:add( raygui.DummyRec:new(
		Rect:new( 50, 700, 256, 32 ),
		"DummyRec"
	) )
	grid = raygui:add( raygui.Grid:new(
		Rect:new( 400, 400, 256, 256 ),
		"Grid",
		32,
		2
	) )
	windowbox = raygui:add( raygui.WindowBox:new(
		Rect:new( 720, 250, 256, 256 ),
		"WindowBox",
		function( self ) self.visible = false end
	) )
	local groupbox = raygui:add( raygui.GroupBox:new(
		Rect:new( 400, 700, 256, 256 ),
		"GroupBox"
	) )
	local line = raygui:add( raygui.Line:new(
		Rect:new( 400, 32, 256, 16 ),
		"Line"
	) )
	local panel = raygui:add( raygui.Panel:new(
		Rect:new( 400, 64, 256, 128 ),
		"Panel"
	) )
	local scrollpanel = raygui:add( raygui.ScrollPanel:new(
		Rect:new( 800, 64, 256, 256 ),
		"ScrollPanel",
		Rect:new( 0, 0, 256, 600 ),
		Vec2:new( 0, 0 )
	) )
	local listview = raygui:add( raygui.ListView:new(
		Rect:new( 1100, 64, 128, 80 ),
		"Cat\nDog\nHorse\nCow\nPig\nEagle\nLion",
		0,
		0,
		function( self ) print( self:getItem( self.active ) ) end
	) )
	local listviewex = raygui:add( raygui.ListViewEx:new(
		Rect:new( 1300, 64, 128, 80 ),
		"Cat\nDog\nHorse\nCow\nPig\nEagle\nLion",
		0,
		0,
		0,
		function( self ) print( self:getItem( self.active ) ) end
	) )
	local messagebox = raygui:add( raygui.MessageBox:new(
		Rect:new( 1100, 150, 300, 128 ),
		"Title",
		"Message",
		"Cancel\nOk",
		function( self )
			if 0 < self.buttonIndex then
				print( "You pressed "..self:getItem( self.buttonIndex ) )

				if self.buttonIndex == 1 then
					raygui:set2Back( windowbox )
				elseif self.buttonIndex == 2 then
					raygui:set2Top( windowbox )
				end
			end
		end
	) )
	local textinputbox = raygui:add( raygui.TextInputBox:new(
		Rect:new( 1100, 300, 300, 128 ),
		"Title",
		"Message",
		"Cancel\nOk",
		"Text",
		8,
		0,
		function( self )
			if 0 < self.buttonIndex then
				print( "You pressed "..self:getItem( self.buttonIndex ) )
			end
		end
	) )
	local colorpicker = raygui:add( raygui.ColorPicker:new(
		Rect:new( 1500, 32, 128, 128 ),
		"Color Picker",
		Color:new()
	) )
	local colorpanel = raygui:add( raygui.ColorPanel:new(
		Rect:new( 1700, 32, 128, 128 ),
		"Color Panel",
		Color:new()
	) )
	local colorbaralpha = raygui:add( raygui.ColorBarAlpha:new(
		Rect:new( 1700, 180, 128, 20 ),
		"Color Panel",
		1.0
	) )
	local colorbarhue = raygui:add( raygui.ColorBarHue:new(
		Rect:new( 1840, 32, 20, 128 ),
		"Color Panel",
		1.0
	) )
end

function RL.process( delta )
	if RL.IsKeyPressed( RL.KEY_R ) then
		raygui:set2Top( windowbox )
	end

	if RL.IsKeyPressed( RL.KEY_F ) then
		raygui:set2Back( windowbox )
	end

	raygui:process()
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	if 0 <= grid.cell.x then
		RL.DrawRectangleLines(
			{
				grid.bounds.x + grid.cell.x * 32,
				grid.bounds.y + grid.cell.y * 32,
				32,
				32
			},
			RL.GREEN
		)
	end

    raygui:draw()
end
