package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )
Raygui = require( "raygui" )

Gui = Raygui:new()

local grid = {}
local windowbox = {}
local tabBar = {}
local texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/gradient.png" )
local textureRect = Rect:new( 0, 0, RL.GetTextureSize( texture )[1], RL.GetTextureSize( texture )[2] )

local function closeTab( self, id )
	local splits = Util.split( tabBar.text, ";" )
	local newText = ""

	if #splits == 1 then
		Gui:remove( tabBar )
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
	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT )

	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.RED ) )
	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.ORANGE ) )
	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( RL.GREEN ) )

	RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_LINE_SPACING, 20 )

	local label = Gui:Label(
		Rect:new( 16, 16, 64, 32 ),
		"Cat"
	)
	local toggleGroup = Gui:ToggleGroup(
		Rect:new( 68, 16, 64, 32 ),
		"Cat\nDog",
		0,
		{ -- Callbacks.
			select = function( self ) print( self:getItem( self.active ) ) end
		}
	)
	local button = Gui:Button(
		Rect:new( 245, 188, 64, 32 ),
		"Dog",
		{ -- Callbacks.
			pressed = function() toggleGroup:setText( "Dog;Cat\nEagle" ) end
		},
		{
			properties = {
				{ RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.RED ) },
				{ RL.DEFAULT, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.ORANGE ) },
				{ RL.DEFAULT, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( RL.GREEN ) },
			},
			texture = { texture = texture, rect = textureRect },
		}
	)
	local checkbox = Gui:CheckBox(
		Rect:new( 116, 128, 20, 20 ),
		"Visible",
		toggleGroup.visible,
		{ -- Callbacks.
			pressed = function( self ) toggleGroup.visible = self.checked end
		}
	)
	local toggle = Gui:Toggle(
		Rect:new( 32, 160, 100, 32 ),
		"Toggle",
		false,
		{} -- Callbacks.
	)
	local combobox = Gui:ComboBox(
		Rect:new( 64, 256, 128, 32 ),
		"Dog\nCow\nDonkey",
		0,
		{} -- Callbacks.
	)
	local dropdownbox = Gui:DropdownBox(
		Rect:new( 256, 128, 128, 32 ),
		"Dog\nGiraffe\nLion\nHorse",
		0,
		false,
		{ -- Callbacks.
			select = function( self ) print( self:getItem( self.active ) ) end
		}
	)
	local spinner = Gui:Spinner(
		Rect:new( 464, 256, 128, 32 ),
		"Health",
		0,
		0,
		10,
		false,
		{ -- Callbacks.
			edit = function( self ) print( "Spinner value changed to "..self.value ) end
		}
	)
	local valuebox = Gui:ValueBox(
		Rect:new( 464, 316, 128, 32 ),
		"Health",
		0,
		0,
		100,
		false,
		{ -- Callbacks.
			edit = function( self ) print( "ValueBox value changed to "..self.value ) end
		}
	)
	local textbox = Gui:TextBox(
		Rect:new( 32, 316, 256, 32 ),
		"Name",
		32,
		false,
		{ -- Callbacks.
			edit = function( self ) print( "Set text "..self.text ) end,
			-- editMode = function( self ) print( "Entered edit mode" ) end
		}
	)
	local textbox2 = Gui:TextBox(
		Rect:new( 32, 380, 256, 32 ),
		"Name",
		32,
		false,
		{ -- Callbacks.
			edit = function( self ) print( "Set text 2 "..self.text ) end
		}
	)
	local slider = Gui:Slider(
		Rect:new( 50, 500, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		{ -- Callbacks.
			edit = function( self ) print( "Changed value "..self.value ) end,
		},
		{ -- Styles.
			texture = { texture = texture, rect = textureRect },
		}
	)
	local sliderbar = Gui:SliderBar(
		Rect:new( 50, 550, 256, 32 ),
		"min",
		"max",
		0,
		0,
		100,
		{ -- Callbacks.
			edit = function( self ) print( "Changed value "..self.value ) end
		}
	)
	local progressbar = Gui:ProgressBar(
		Rect:new( 50, 600, 256, 32 ),
		"min",
		"max",
		20,
		0,
		100,
		{ -- Callbacks.
			edit = function( self ) print( "Changed value "..self.value ) end
		}
	)
	local statusbar = Gui:StatusBar(
		Rect:new( 50, 650, 256, 32 ),
		"StatusBar"
	)
	local dummyrec = Gui:DummyRec(
		Rect:new( 50, 700, 256, 32 ),
		"DummyRec"
	)
	grid = Gui:Grid(
		Rect:new( 400, 400, 256, 256 ),
		"Grid",
		32,
		2,
		{} -- Callbacks.
	)
	windowbox = Gui:WindowBox(
		Rect:new( 720, 250, 256, 256 ),
		"WindowBox",
		{ -- Callbacks.
			close = function( self ) self.visible = false end,
			grab = function( self ) Gui:setToTop( self ) end,
		},
		{ -- Styles.
			properties = {
				{ RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.RED ) },
			},
			texture = { texture = texture, rect = textureRect },
		}
	)

	local groupbox = Gui:GroupBox(
		Rect:new( 400, 700, 256, 256 ),
		"GroupBox"
	)
	local line = Gui:Line(
		Rect:new( 400, 32, 256, 16 ),
		"Line"
	)
	local panel = Gui:Panel(
		Rect:new( 400, 64, 256, 128 ),
		"Panel",
		{ -- Callbacks.
			grab = function( self ) Gui:setToTop( self ) end
		},
		{ -- Styles.
			properties = {
				{ RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.MAGENTA ) },
				{ RL.DEFAULT, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_CENTER },
				{ RL.DEFAULT, RL.BACKGROUND_COLOR, RL.ColorToInt( RL.DARKBLUE ) },
			}
		}
	)
	tabBar = Gui:GuiTabBar(
		Rect:new( 700, 520, 700, 32 ),
		"Cat;Dog;Horse;Cow;Dog;Horse;Cow",
		0,
		{ -- Callbacks.
			close = closeTab,
			select = function( self ) print( self:getItem( self.active ) ) end
		}
	)
	local scrollpanel = Gui:ScrollPanel(
		Rect:new( 800, 64, 256, 256 ),
		"ScrollPanel",
		Rect:new( 0, 0, 300, 600 ),
		Vec2:new( 0, 0 ),
		{ -- Callbacks.
			scroll = function( self ) print( self.scroll ) end,
			grab = function( self ) Gui:setToTop( self ) end
		}
	)
	local listview = Gui:ListView(
		Rect:new( 1100, 64, 128, 128 ),
		"Cat;Dog;Horse;Cow;Pig;Eagle;Lion",
		0,
		0,
		{ -- Callbacks.
			select = function( self ) print( self:getItem( self.active ) ) end
		}
	)
	local listviewex = Gui:ListViewEx(
		Rect:new( 1300, 64, 128, 128 ),
		"Cat;Dog;Horse;Cow;Pig;Eagle;Lion",
		0,
		0,
		0,
		{ -- Callbacks.
			select = function( self ) print( self:getItem( self.active ) ) end
		},
		{ -- Styles.
			properties = {
				{ RL.DEFAULT, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( RL.RED ) },
				{ RL.DEFAULT, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.ORANGE ) },
				{ RL.DEFAULT, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( RL.GREEN ) },
			},
			texture = { texture = texture, rect = textureRect },
		}
	)
	local messagebox = Gui:MessageBox(
		Rect:new( 1100, 150, 300, 128 ),
		"Title",
		"Should we disable\nwindow box?",
		"No;Yes",
		{ -- Callbacks.
			pressed = function( self )
				if 0 < self.buttonIndex then
					if self.buttonIndex == 1 then
						windowbox.disabled = false
					elseif self.buttonIndex == 2 then
						windowbox.disabled = true
					end
				end
			end,
			grab = function( self ) Gui:setToTop( self ) end
		}
	)
	local textinputbox = Gui:TextInputBox(
		Rect:new( 1100, 300, 300, 128 ),
		"Title",
		"Message",
		"Cancel;Ok",
		"Text",
		8,
		false,
		{ -- Callbacks.
			pressed = function( self )
				if 0 < self.buttonIndex then
					print( "You pressed "..self:getItem( self.buttonIndex ) )
				end
			end,
			grab = function( self ) Gui:setToTop( self ) end
		}
	)
	local colorpicker = Gui:ColorPicker(
		Rect:new( 1500, 32, 128, 128 ),
		"Color Picker",
		Color:new( 255, 255, 255, 255 ),
		{} -- Callbacks.
	)
	local colorpanel = Gui:ColorPanel(
		Rect:new( 1700, 32, 128, 128 ),
		"Color Panel",
		Color:new( 255, 255, 255, 255 ),
		{} -- Callbacks.
	)
	local colorbaralpha = Gui:ColorBarAlpha(
		Rect:new( 1700, 180, 128, 20 ),
		"Color Panel",
		1.0,
		{} -- Callbacks.
	)
	local colorbarhue = Gui:ColorBarHue(
		Rect:new( 1840, 32, 20, 128 ),
		"Color Panel",
		1.0,
		{} -- Callbacks.
	)
	local scrollbar = Gui:GuiScrollBar(
		Rect:new( 50, 760, 256, 16 ),
		0,
		0,
		256,
		{ -- Callbacks.
			scroll = function( self ) print( "Scrollbar value: ", self.value ) end
		} 
	)
end

function RL.update( delta )
	Gui:update()
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
    Gui:draw()
end
