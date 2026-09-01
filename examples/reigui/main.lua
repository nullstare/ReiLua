package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )
Color = require( "color" )
-- Gui = require( "reigui/gui" )

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
	RL.GuiLoadStyleDefault()
	Gui = require( "reigui/gui" )
	Gui:include( require( "reigui.default_controls" ) )
	Gui:include( require( "reigui.window" ) )
	gui = Gui:new()

	local prefix = RL.GetBasePath().."../resources/images/"

	buttonTex = RL.LoadTexture( prefix.."button.png" )
	borderTex = RL.LoadTexture( prefix.."ui_border.png" )
	gradientTex = RL.LoadTexture( prefix.."gradient.png" )
	wabbitTex = RL.LoadTexture( prefix.."wabbit_alpha.png" )
	sliderTex = RL.LoadTexture( prefix.."slider.png" )

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
			pressed = function()
				print( "Button clicked 2" )
				gui.tooltipStyles.text.fontSize = 20
			end,
		},
		tooltip = "This button has also icon in it",
		styles = button2Styles,
	} )

	-- Button 3.

	local button3Styles = Util.deepCopy( GUI_DEFAULT_STYLES )
	button3Styles.normal.text.color = RL.BLACK
	button3Styles.normal.text.fontSize = 20
	button3Styles.normal.text.spacing = 2
	button3Styles.focused.text.fontSize = 20
	button3Styles.focused.text.spacing = 2
	button3Styles.pressed.text.fontSize = 20
	button3Styles.pressed.text.spacing = 2

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
	labelStyle.normal.text.fontSize = 20
	labelStyle.normal.text.spacing = 2
	labelStyle.normal.text.alignH = RL.TEXT_ALIGN_LEFT

	local label = gui:newLabel( {
		bounds = Rectangle:new( 16, 4, 128, 32 ),
		text = "Label",
		styles = labelStyle,
	} )

	-- TextEdit.

	local textEditStyle = Util.deepCopy( GUI_DEFAULT_STYLES )
	local textStyle = Util.deepCopy( textEditStyle.normal.text )
	textStyle.fontSize = 20
	textStyle.spacing = 2
	textStyle.alignH = RL.TEXT_ALIGN_LEFT

	textEditStyle.normal.text = textStyle
	textEditStyle.pressed.text = textStyle
	textEditStyle.focused.text = textStyle
	textEditStyle.disabled.text = textStyle

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

	local panel = gui:newPanel( {
		bounds = Rectangle:new( 2, 2, 300, 324 ),
		styles = panelStyles,
	} )

	local slider = gui:newSlider( {
		bounds = Rectangle:new( 16, 248, 256, 16 ),
		valueStep = 1,
		minValue = 0,
		maxValue = 10,
		callbacks = {
			set = function( self ) label.text = "Value: "..self.value end,
		},
		tooltip = "Slide the slider",
	} )

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
	-- slider2Style.focused = slider2Style.normal
	slider2Style.focused = Util.deepCopy( slider2Style.normal )
	slider2Style.focused.slider.textures[1].color = RL.WHITE

	local slider2 = gui:newSlider( {
		bounds = Rectangle:new( 16, 280, 256, 16 ),
		valueStep = 0.1,
		minValue = 0,
		maxValue = 10,
		callbacks = {
			set = function( self ) label.text = "Value: "..self.value end,
		},
		tooltip = "Slide the slider",
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

	gui:setToBack( panel )

	-- Window.

	local window = gui:newWindow( {
		bounds = Rectangle:new( 60, 400, 256, 400 ),
		text = "Window",
		callbacks = {
			close = function( self ) self:setVisible( false ) end,
			grab = function( self ) self:setToTop() end,
		},
	} )
	-- window.callbacks.close = function( self ) window:setVisible( false ) end
end

function RL.update( delta )
	gui:update( delta )
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	gui:draw()
end
