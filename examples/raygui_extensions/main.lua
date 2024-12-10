package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Color = require( "color" )
Rectangle = require( "rectangle" )
Raygui = require( "raygui" )

require( "sprite_button" ):register( Raygui )
require( "property_list" ):register( Raygui )
require( "tree_view" ):register( Raygui )
require( "tree_item" ):register( Raygui )

Gui = Raygui:new()

local buttonTexture = nil
local winSize = Vector2:new( 1024, 720 )
local cat = {
	texture = nil,
	source = Rectangle:new( 0, 0, 0, 0 ),
	dest = Rectangle:new( 0, 0, 0, 0 ),
	origin = Vector2:new( 0, 0 ),
	rotation = 0.0,
	tint = Color:newT( RL.WHITE ),
	visible = true,
	flipped = false
}

local function addButton( bounds, text, callback )
	Gui:SpriteButton(
		bounds,
		text,
		buttonTexture,
		{ source = { 0, 0, 48, 48 }, left = 16, top = 16, right = 16, bottom = 16, layout = RL.NPATCH_NINE_PATCH },
		{ source = { 48, 0, 48, 48 }, left = 16, top = 16, right = 16, bottom = 16, layout = RL.NPATCH_NINE_PATCH },
		callback,
		{
			properties = {
				{ RL.LABEL, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_CENTER },
				{ RL.DEFAULT, RL.TEXT_SIZE, 32 },
				{ RL.LABEL, RL.TEXT_COLOR_NORMAL, RL.ColorToInt( { 84, 59, 22 } ) },
				{ RL.LABEL, RL.TEXT_COLOR_PRESSED, RL.ColorToInt( { 84/2, 59/2, 22/2 } ) },
				{ RL.LABEL, RL.TEXT_COLOR_FOCUSED, RL.ColorToInt( RL.GREEN ) },
				{ RL.BUTTON, RL.BASE_COLOR_PRESSED, RL.ColorToInt( RL.WHITE ) },
				{ RL.BUTTON, RL.BASE_COLOR_NORMAL, RL.ColorToInt( RL.WHITE ) },
			},
		},
		text
	)
end

local function addSpriteButtons()
	buttonTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/button.png" )
	
	local buttonSize = Vector2:new( 216, 32 )
	local bounds = Rectangle:new( winSize.x / 2 - buttonSize.x / 2, 200, 216, 32 )
	local gap = buttonSize.y + 2
	addButton( bounds, "Start New Game", { pressed = function() print( "New Game!" ) end } )
	bounds.y = bounds.y + gap
	addButton( bounds, "Load Game", { pressed = function() print( "Load Game!" ) end } )
	bounds.y = bounds.y + gap
	addButton( bounds, "Options", { pressed = function() print( "Options!" ) end } )
	bounds.y = bounds.y + gap
	addButton( bounds, "Quit", { pressed = function() RL.CloseWindow() end } )
end

local function getTextValue( text )
	local value = tonumber( text )
	if value == nil then value = 0 end
	return value
end

local function addPropertyList()
	PropertyList = Gui:PropertyList(
		Rectangle:new( 20, 20, 256, 328 ),
		"Property List",
		{ -- Callbacks.
			grab = function( self ) Gui:setToTop( self ) end,
		},
		{ -- Styles.
			properties = {
				-- { RL.SCROLLBAR, RL.ARROWS_VISIBLE, RL.ARROWS_VISIBLE },
				{ RL.LISTVIEW, RL.BORDER_COLOR_FOCUSED, RL.GuiGetStyle( RL.LISTVIEW, RL.BORDER_COLOR_NORMAL ) },
				{ RL.LISTVIEW, RL.BORDER_COLOR_PRESSED, RL.GuiGetStyle( RL.LISTVIEW, RL.BORDER_COLOR_NORMAL ) },
			}
		}
	)
	RL.GuiSetStyle( RL.SPINNER, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT )
	PropertyList.contentPadding.x = PropertyList.bounds.height -- Room for dropdown.

	PropertyList:addControl( PropertyList.gui:Line(
		Rectangle:new( 0, 0, 0, 0 ),
		"Cat Texture"
	) )

	--Transform.

	local transformGroup = PropertyList:addGroup( "Transform", false )

	-- Position.
	PropertyList:addControl( PropertyList.gui:Label(
		Rectangle:new( 0, 0, 0, 0 ),
		"Position:"
	), transformGroup )
	PropertyList:addControl( PropertyList.gui:TextBox(
		Rectangle:new( 0, 0, 64, 22 ),
		cat.dest.x,
		32,
		false,
		{ -- Callbacks.
			edit = function( self )
				self.value = getTextValue( self.text )
				self.text = tostring( self.value )
				cat.dest.x = self.value
			end
		},
		nil,
		"Position X"
	), transformGroup, true )
	PropertyList:addControl( PropertyList.gui:TextBox(
		Rectangle:new( 74, 0, 64, 22 ),
		cat.dest.y,
		32,
		false,
		{ -- Callbacks.
			edit = function( self )
				self.value = getTextValue( self.text )
				self.text = tostring( self.value )
				cat.dest.y = self.value
			end
		},
		nil,
		"Position Y"
	), transformGroup )
	-- Origin.
	PropertyList:addControl( PropertyList.gui:Label(
		Rectangle:new( 0, 0, 0, 0 ),
		"Origin:"
	), transformGroup )
	PropertyList:addControl( PropertyList.gui:TextBox(
		Rectangle:new( 0, 0, 64, 22 ),
		cat.dest.x,
		32,
		false,
		{ -- Callbacks.
			edit = function( self )
				self.value = getTextValue( self.text )
				self.text = tostring( self.value )
				cat.origin.x = self.value
			end
		},
		nil,
		"Origin X"
	), transformGroup, true )
	PropertyList:addControl( PropertyList.gui:TextBox(
		Rectangle:new( 74, 0, 64, 22 ),
		cat.dest.y,
		32,
		false,
		{ -- Callbacks.
			edit = function( self )
				self.value = getTextValue( self.text )
				self.text = tostring( self.value )
				cat.origin.y = self.value
			end
		},
		nil,
		"Origin Y"
	), transformGroup )
	-- Rotation.
	PropertyList:addControl( PropertyList.gui:Slider(
		Rectangle:new( 60, 0, PropertyList.defaultControlSize.x - 150, 22 ),
		"Rotation",
		"0",
		0,
		0,
		360,
		{ -- Callbacks.
			edit = function( self )
				self.value = Util.round( self.value )
				cat.rotation = self.value
				self.textRight = self.value
			end
		},
		nil,
		"Rotation angle"
	), transformGroup )
	-- Flipped.
	PropertyList:addControl( PropertyList.gui:CheckBox(
		Rectangle:new( 0, 0, 20, 20 ),
		"Flipped",
		cat.flipped,
		{ -- Callbacks.
			pressed = function( self ) cat.flipped = self.checked end
		},
		nil,
		"Flips the image"
	), transformGroup )

	-- Visibility.

	local visibilityGroup = PropertyList:addGroup( "Visibility", false )

	PropertyList:addControl( PropertyList.gui:CheckBox(
		Rectangle:new( 0, 0, 20, 20 ),
		"Visible",
		cat.visible,
		{ -- Callbacks.
			pressed = function( self ) cat.visible = self.checked end
		},
		{
			properties = {
				{ RL.CHECKBOX, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_RIGHT },
			}
		}
	), visibilityGroup )

	local tintGroup = PropertyList:addGroup( "Tint", false, visibilityGroup )

	PropertyList:addControl( PropertyList.gui:ColorPicker(
		Rectangle:new( 0, 0, 128, 128 ),
		"Color Picker",
		Color:new( 255, 255, 255, 255 ),
		{ -- Callbacks.
			edit = function( self ) cat.tint = self.color end
		}
	), tintGroup )

	PropertyList:addControl( PropertyList.gui:Line(
		Rectangle:new( 0, 0, 0, 0 ),
		"Testing"
	) )

	PropertyList:addControl( PropertyList.gui:DropdownBox(
		Rectangle:new( 0, 0, 0, 0 ),
		"Dog\nGiraffe\nLion\nHorse",
		0,
		false,
		{ -- Callbacks.
			select = function( self ) print( self:getItem( self.active ) ) end
		}
	) )

	local test = PropertyList:addGroup( "Test", false )

	for i = 1, 5 do
		PropertyList:addControl( PropertyList.gui:CheckBox(
			Rectangle:new( 128, 0, 20, 20 ),
			i.."_Visible",
			false,
			{ -- Callbacks.
				pressed = function( self ) print( "Checked" ) end
			},
			{
				properties = {
					-- { RL.CHECKBOX, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT },
					{ RL.DEFAULT, RL.TEXT_SIZE, 32 }
				}
			}
		), test )
	end
end

local function selected( controls )
	for i, control in ipairs( controls ) do
		print( i, control.text, control._id )
	end
end

local function addTreeView()
	TreeView = Gui:TreeView(
		Rectangle:new( 600, 20, 256, 328 ),
		"Tree View",
		{ -- Callbacks.
			select = function( controls ) selected( controls ) end,
			grab = function( self ) Gui:setToTop( self ) end,
		},
		{ -- Styles.
			properties = {
				-- { RL.SCROLLBAR, RL.ARROWS_VISIBLE, RL.ARROWS_VISIBLE },
				{ RL.LISTVIEW, RL.BORDER_COLOR_FOCUSED, RL.GuiGetStyle( RL.LISTVIEW, RL.BORDER_COLOR_NORMAL ) },
				{ RL.LISTVIEW, RL.BORDER_COLOR_PRESSED, RL.GuiGetStyle( RL.LISTVIEW, RL.BORDER_COLOR_NORMAL ) },
			}
		}
	)
	-- Items.
	
	local folder = TreeView:addItem( RL.GuiIconText( RL.ICON_FOLDER_FILE_OPEN, "Images" ) )
	local folderEmpty = TreeView:addItem( RL.GuiIconText( RL.ICON_FOLDER_FILE_OPEN, "Empty Folder" ) )
	local folder2 = TreeView:addItem( RL.GuiIconText( RL.ICON_FOLDER_FILE_OPEN, "More images" ), folder )
	TreeView:addItem( RL.GuiIconText( RL.ICON_FILETYPE_IMAGE, "Cat.png" ), folder )
	TreeView:addItem( RL.GuiIconText( RL.ICON_FILETYPE_IMAGE, "Dog.png" ), folder2 )
	TreeView:addItem( RL.GuiIconText( RL.ICON_FILETYPE_IMAGE, "Horse.png" ), folder2 )

	for i = 0, 10 do
		TreeView:addItem( RL.GuiIconText( RL.ICON_FILETYPE_IMAGE, "Duck"..i..".png" ), folder2 )
	end
end

function RL.init()
	local monitor = 0
	local mPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local mSize = Vector2:newT( RL.GetMonitorSize( monitor ) )

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SPACING, 4 )
	-- RL.GuiSetStyle( RL.SPINNER, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_RIGHT )
	-- RL.GuiSetStyle( RL.SPINNER, RL.TEXT_PADDING, 2 )

	cat.texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/cat.png" )
	local texSize = Vector2:newT( RL.GetTextureSize( cat.texture ) )
	cat.source:set( 0, 0, texSize.x, texSize.y )
	cat.dest = cat.source:clone()

	RL.GuiLoadStyle( RL.GetBasePath().."../resources/styles/style_dark.rgs" )

	addSpriteButtons()
	addPropertyList()
	addTreeView()
end

function RL.update( delta )
	Gui:update( delta )
end

function RL.draw()
	RL.ClearBackground( RL.DARKBLUE )

	if cat.visible then
		if cat.flipped then
			RL.DrawTexturePro(
				cat.texture,
				{ cat.source.x, cat.source.y, -cat.source.width, cat.source.height },
				cat.dest,
				cat.origin,
				cat.rotation,
				cat.tint
			)
		else
			RL.DrawTexturePro(
				cat.texture,
				cat.source,
				cat.dest,
				cat.origin,
				cat.rotation,
				cat.tint
			)
		end
	end
	Gui:draw()
end
