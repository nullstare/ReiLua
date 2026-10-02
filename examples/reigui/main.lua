package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )
Color = require( "color" )

local gui = nil
local buttonTex = nil
local borderTex = nil
local gradientTex = nil
local wabbitTex = nil
local sliderTex = nil

function RL.init()
	local monitor = 0
	local mPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local mSize = Vector2:newT( RL.GetMonitorSize( monitor ) )
	local winSize = Vector2:new( 1920, 1080 )

	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )

	InitGui()
end

function InitGui()
	-- RL.GuiLoadStyleDefault()
	RL.GuiLoadStyle( RL.GetBasePath().."../resources/styles/style_dark.rgs" )
	Gui = require( "reigui.gui" )
	Gui:include( require( "reigui.basic_controls" ) )
	Gui:include( require( "reigui.window" ) )
	Gui:include( require( "reigui.spinner" ) )
	Gui:include( require( "reigui.color_picker" ) )
	Gui:include( require( "reigui.container" ) )
	Gui:include( require( "reigui.dropdown" ) )
	Gui:include( require( "reigui.file_browser" ) )
	Gui:include( require( "reigui.message_window" ) )
	Gui:include( require( "reigui.check_box" ) )

	gui = Gui:new()

	local prefix = RL.GetBasePath().."../resources/images/"

	buttonTex = RL.LoadTexture( prefix.."button.png" )
	borderTex = RL.LoadTexture( prefix.."ui_border.png" )
	gradientTex = RL.LoadTexture( prefix.."gradient.png" )
	wabbitTex = RL.LoadTexture( prefix.."wabbit_alpha.png" )
	sliderTex = RL.LoadTexture( prefix.."slider.png" )

	local fontSize = RL.GetFontBaseSize( RL.GuiGetFont() )

	-- Button 1.

	local button = gui:newButton( {
		bounds = Rectangle:new( 32, 48, 128, 32 ),
		text = "Button 1",
		callbacks = {
			pressed = function() print( "Button clicked 1" ) end,
		},
		tooltip = "You should press this button",
	} )

	local button2Styles = Util.deepCopy( GUI_DEFAULT_STYLES )
	button2Styles.normal.base.gradient = "horizontal"
	button2Styles.normal.base.color = { RL.BLUE, RL.RED }
	button2Styles.normal.text.color = RL.BLACK
	button2Styles.normal.icons = {
		{
			iconId = RL.ICON_SCALE,
			offset = Vector2:new( 8, 0 ),
			pixelSize = 1,
			color = RL.BLACK,
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	}
	button2Styles.focused.icons = Util.deepCopy( button2Styles.normal.icons )
	button2Styles.focused.icons[1].color = RL.GREEN
	button2Styles.pressed.icons = Util.deepCopy( button2Styles.normal.icons )
	button2Styles.pressed.icons[1].color = RL.RED

	-- Button 2.

	local button2 = gui:newButton( {
		bounds = Rectangle:new( 16, 64, 256, 32 ),
		text = "Make tooltip larger",
		callbacks = {
			released = function( this )
				this.toggle = not this.toggle
				gui.tooltipStyles.text.fontSize = this.toggle and fontSize * 2 or fontSize
			end,
		},
		tooltip = "This button has also icon in it",
		styles = button2Styles,
		toggle = false, 
	} )

	-- Button 3.

	local button3Styles = Util.deepCopy( GUI_DEFAULT_STYLES )

	button3Styles.normal.text.color = RL.BLACK

	-- Gui:setForAllStyles( button3Styles, "text.fontSize", fontSize * 2 )
	Gui:setForAllStyles( button3Styles, "text.spacing", 2 )

	local textures = {
		{
			texture = gradientTex,
			source = Rectangle:new( 0, 0, 256, 64 ),
			color = Color:new(),
		},
		{
			texture = borderTex,
			color = Color:newT( RL.DARKGREEN ),
			nPatchInfo = {
				source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8,
				layout = RL.NPATCH_NINE_PATCH
			},
			nPatchRepeat = true,
		},
		{
			texture = wabbitTex,
			source = Rectangle:new( 0, 0, 32, 32 ),
			dest = Rectangle:new( 8, 64 / 2 - 16, 32, 32 ),
			color = Color:new(),
		},
	}
	button3Styles.normal.textures = textures
	button3Styles.pressed.textures = Util.deepCopy( textures )
	button3Styles.pressed.textures[1].color = Color:newT( RL.LIGHTGRAY )
	button3Styles.pressed.textures[3].color = Color:newT( RL.RED )
	button3Styles.focused.textures = textures
	button3Styles.focused.text.offset = Vector2:new( 8, 0 )
	button3Styles.pressed.text.offset = Vector2:new( 8, 0 )

	local button3 = gui:newButton( {
		bounds = Rectangle:new( 16, 128, 256, 64 ),
		text = "Textured Button",
		callbacks = {
			released = function() print( "Textured button clicked!" ) end,
		},
		tooltip = "This button has texture",
		styles = button3Styles,
	} )

	-- Label.

	local labelStyle = Util.deepCopy( gui.Label.DEFAULT_STYLES )
	labelStyle.normal.text.color = Color:newT( RL.BLACK )
	labelStyle.normal.text.fontSize = fontSize * 2
	labelStyle.normal.text.spacing = 2
	labelStyle.normal.text.alignH = RL.TEXT_ALIGN_LEFT

	local label = gui:newLabel( {
		bounds = Rectangle:new( 16, 4, 128, 32 ),
		text = "Label",
		styles = labelStyle,
	} )

	-- TextEdit.

	local textEditStyle = Util.deepCopy( gui.TextInputBox.DEFAULT_STYLES )
	local textStyle = Util.deepCopy( textEditStyle.normal.text )
	textStyle.fontSize = fontSize * 2
	textStyle.spacing = 2
	textStyle.alignH = RL.TEXT_ALIGN_LEFT

	gui:setForAllStyles( textEditStyle, "text", textStyle )

	local textInputBox = gui:newTextInputBox( {
		bounds = Rectangle:new( 16, 200, 256, 32 ),
		text = "Edit",
		callbacks = {
			pressed = function() print( "Start Editing!" ) end,
			edit = function( self ) label.text = self.text end,
		},
		styles = textEditStyle,
		tooltip = "This is single line text edit box"
	} )
	textInputBox.callbacks.set = function( self )
		textInputBox.tooltip = self.text

		if self.text == "wabbit" then
			button3Styles.normal.text.offset = Vector2:new( 8, 0 )
			button3Styles.normal.textures[3].color = Color:newT( RL.RED )
			button3.text = "Wabbit Angwy! (E:<=3"
		end
	end

	local panelStyles = Util.deepCopy( gui.Panel.DEFAULT_STYLES )
	panelStyles.normal.textures = {
		{
			texture = buttonTex,
			color = Color:newT( RL.LIGHTGRAY ),
			nPatchInfo = {
				source = { 0, 0, 48, 48 }, left = 16, top = 16, right = 16, bottom = 16,
				layout = RL.NPATCH_NINE_PATCH
			},
			nPatchRepeat = true,
		}
	}

	-- Panel.

	local panel = gui:newPanel( {
		bounds = Rectangle:new( 2, 2, 300, 400 ),
		styles = panelStyles,
	} )

	-- Slider.
	
	local slider = gui:newSlider( {
		bounds = Rectangle:new( 16, 248, 256, 16 ),
		-- valueStep = 1,
		-- minValue = 0,
		-- maxValue = 10,
		callbacks = {
			set = function( self ) label.text = "Value: "..self.value.x end,
		},
		tooltip = "Slide the slider",
	} )

	-- Textured Slider.

	local slider2Style = Util.deepCopy( gui.Slider.DEFAULT_STYLES )
	slider2Style.normal.textures = {
		{
			texture = sliderTex,
			color = Color:newT( RL.GRAY ),
			nPatchInfo = {
				source = { 0, 0, 48, 16 }, left = 16, top = 16, right = 16, bottom = 16,
				layout = RL.NPATCH_NINE_PATCH,
			},
			nPatchRepeat = true,
		}
	}
	slider2Style.normal.slider.width = 8
	slider2Style.normal.slider.textures = {
		{
			texture = sliderTex,
			color = Color:newT( RL.LIGHTGRAY ),
			source = Rectangle:new( 48, 0, 8, 16 ),
		}
	}
	slider2Style.disabled = slider2Style.normal
	slider2Style.pressed = slider2Style.normal
	slider2Style.focused = Util.deepCopy( slider2Style.normal )
	slider2Style.focused.slider.textures[1].color = RL.WHITE

	local slider2 = gui:newSlider( {
		bounds = Rectangle:new( 16, 280, 256, 16 ),
		valueStep = Vector2:new( 1, 0 ),
		maxValue = Vector2:new( 10, 0 ),
		callbacks = {
			set = function( self ) label.text = "Value: "..self.value.x end,
		},
		tooltip = "Slide the textured slider",
		styles = slider2Style,
	} )

	-- Handle.

	local handle = gui:newHandle( {
		bounds = Rectangle:new( 350, 32, 128, 32 ),
		text = "Handle",
		callbacks = {
			pressed = function( self ) self:setToTop() end,
			drag = function( self ) label.text = "Pos: "..self.bounds:getPosition() end,
		},
		tooltip = "You can drag this thing",
		-- clampBounds = Rectangle:new( -32, -16, 200, 64 ), -- Usefull for windows for example.
	} )

	-- Window.

	local window = gui:newWindow( {
		bounds = Rectangle:new( 360, 80, 256, 400 ),
		text = "Window",
		-- draggable = false,
		-- callbacks = {
			-- close = function( self ) self:setVisible( false ) end,
			-- grab = function( self ) self:setToTop() end,
		-- },
	} )

	-- Spinner.

	local spinnerStyle = Util.deepCopy( gui.Spinner.DEFAULT_STYLES )

	Gui:setForAllStyles( spinnerStyle.textInput, "text.fontSize", fontSize * 2 )

	local spinner = gui:newSpinner( {
		bounds = Rectangle:new( 16, 316, 96, 32 ),
		callbacks = {
		},
		styles = spinnerStyle
	} )

	-- Color panel.

	local colorPicker = gui:newColorPicker( {
		bounds = Rectangle:new(
			32, 450,
			gui.ColorPicker.DEFAULT_STYLES.colorPicker.size.x, gui.ColorPicker.DEFAULT_STYLES.colorPicker.size.y
		),
		callbacks = {
			apply = function( color ) button3Styles.normal.textures[3].color:setC( color ) end
		},
	} )

	-- Container.

	local container = gui:newContainer( {
		bounds = Rectangle:new(	650, 64, 160, 200 ),
	} )
	container.position = Vector2:new( 8, 32 )

	for i = 1, 12 do
		container:addControl(
			container.gui:newButton( {
				bounds = Rectangle:new( 0, 0, 120, 16 ),
				text = "Button "..i,
				callbacks = {
					pressed = function( this ) print( this.text ) end
				}
			} )
		)
	end

	-- Add container to window.
	window:_addControl( container, "container" )
	window:setPosition( window.bounds:getPosition() )

	-- Dropdown.

	local dropdown = gui:newDropdown( {
		bounds = Rectangle:new( 16, 360, 128, 32 ),
		text = "Dropdown",
		callbacks = {
		},
	} )

	local dropdown2 = container:addControl(
		container.gui:newDropdown( {
			bounds = Rectangle:new( 0, 0, 120, 24 ),
			text = "Group",
			mouseClose = false,
			callbacks = {
				released = function( this )
					container:updateControls()
				end
			}
		} )
	)
	local dropdownTexts = { "New", "Open", "Save", "Preferences", "Quit" }
	local dropdownIcons = { RL.ICON_FILE_ADD, RL.ICON_FILE_OPEN, RL.ICON_FILE_SAVE, RL.ICON_GEAR_BIG, RL.ICON_EXIT }

	for i = 1, 5 do
		local b = dropdown:addControl( gui:newButton( {
			bounds = Rectangle:new( 0, 0, 0, 20 ),
			text = dropdownTexts[i],
			visible = false,
			stylesOverlay = gui:getDummyStyles(),
			callbacks = {
				released = function( this )
					print( dropdownTexts[i] )
					dropdown:showContent( false )
				end
			}
		} )	)

		Gui:setForAllStyles( b.stylesOverlay, "icons", {
			{
				iconId = dropdownIcons[i],
				offset = Vector2:new( 0, 0 ),
				pixelSize = 1,
				color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
				alignH = RL.TEXT_ALIGN_LEFT,
				alignV = RL.TEXT_ALIGN_CENTER,
			},
		} )

		container:addControl( dropdown2:addControl(
			container.gui:newButton( {
				bounds = Rectangle:new( 0, 0, 120, 20 ),
				text = dropdownTexts[i],
				visible = false,
				callbacks = {
					released = function( this )
						print( dropdownTexts[i] )
					end
				}
			} )
		) )
	end

	dropdown:setButtonToTextWidth( 4, 4 )
	dropdown:setControlsToTextWidth( 20, 4 )

	container:addControl(
		container.gui:newLabel( {
			bounds = Rectangle:new( 0, 0, 120, 20 ),
			text = "Cat",
		} )
	)

	container:updateControls()

	local fileBrowser = gui:newFileBrowser( {
		callbacks = {
			apply = function( path )
				print( "File path: "..path )
			end
		},
	} )
	fileBrowser:setPosition( Vector2:new( 650, 32 ) )

	-- Create default message window. Popup will give it context.
	local messageWindow = gui:newMessageWindow( {} )

	container:addControl(
		container.gui:newButton( {
			bounds = Rectangle:new( 0, 0, 120, 20 ),
			text = "Load button tex",
			callbacks = {
				released = function()
					local function confirm( path )
						messageWindow:popup(
							"Confirm load",
							string.format( "Are you sure you want to load texture '%s'", path ),
							{ -- Buttons.
								{
									text = "No",
									callbacks = {
										released = function()
											messageWindow:setVisible( false )
										end
									}
								},
								{
									text = "Yes",
									callbacks = {
										released = function()
											local tex = RL.LoadTexture( path )
											
											if tex then
												Gui:setForAllStyles( button3Styles, "textures.3.texture", tex )
												fileBrowser:setVisible( false )
											end

											messageWindow:setVisible( false )
										end
									}
								},
							}
						)
					end

					local function loadTexture( path )
						if not RL.FileExists( path ) or not RL.IsFileExtension( path, ".png" ) then
							messageWindow:popup(
								"Invalid file",
								string.format( "'%s' is not an image file", path ),
								{ -- Buttons.
									{
										text = "Ok",
										callbacks = {
											released = function()
												messageWindow:setVisible( false )
											end
										}
									},
								}
							)
						else
							confirm( path )
						end
					end

					fileBrowser:popup( RL.GetBasePath(), loadTexture, { "DIRS*;.png", "*.*" } )
				end
			}
		} )
	)

	-- Hypertext.

	local hyperStyle = Util.deepCopy( Gui.TextBox.DEFAULT_STYLES )
	hyperStyle.normal.text.color = RL.DARKBLUE
	hyperStyle.focused.text.color = RL.BLUE

	local textBox = gui:newTextBox( {
		bounds = Rectangle:new( 400, 300, window.bounds.width - 16, 100 ),
		texts = {
			{
				string = "This is just ordinary text.",
			},
			{
				string = " This section is a hypertext",
				styles = hyperStyle,
				isHypertext = true,
			},
			{
				string = " and we continue with some more normal text.",
			},
			{
				string = " Another hypertext.",
				styles = hyperStyle,
				isHypertext = true,
			},
		},
		callbacks = {
			mouseOnChar = function( this, sec, charId )
				local text = this.texts[ sec ]

				if text.isHypertext then
					this.tooltip = "This text can be clicked"

					if gui._isMouseReleased then
						print( "Section "..sec, "Char is "..text.string:sub( charId, charId ) )
					end
				else
					this.tooltip = nil
				end
			end,
			mouseOut = function( this )
				this.tooltip = nil
			end,
		},
	} )

	-- Add hypertext to window.
	textBox.position = container.position + Vector2:temp( 0, container.bounds.height + 8 )
	window:_addControl( textBox, "textBox" )
	window:setPosition( window.bounds:getPosition() )

	-- Check box.

	local checkBox = gui:newCheckBox( {
		bounds = Rectangle:new( 150, 360, 128, 32 ),
		toggle = false,
		text = "Checkbox",
	} )

	gui:setToBack( panel )
end

function RL.update( delta )
	gui:update( delta )
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	gui:draw()
end
