package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )
Color = require( "color" )
-- Gui = require( "reigui/gui" )

local gui = nil
local button = nil
local buttonTex = nil
local borderTex = nil
local gradientTex = nil
local wabbitTex = nil

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
	gui = Gui:new()

	local prefix = RL.GetBasePath().."../resources/images/"
	buttonTex = RL.LoadTexture( prefix.."button.png" )
	borderTex = RL.LoadTexture( prefix.."ui_border.png" )
	gradientTex = RL.LoadTexture( prefix.."gradient.png" )
	wabbitTex = RL.LoadTexture( prefix.."wabbit_alpha.png" )

	-- Button 1.

	button = gui:newButton( {
		bounds = Rectangle:new( 32, 32, 128, 32 ),
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

	-- Util.printt( button2Styles.normal.border )

	-- print( button2Styles.normal.border.width )

	-- Button 2.

	button2 = gui:newButton( {
		bounds = Rectangle:new( 48, 48, 128, 32 ),
		text = "Button 2",
		callbacks = {
			pressed = function() print( "Button clicked 2" ) end,
		},
		tooltip = "This button is also alright",
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

	button3 = gui:newButton( {
		bounds = Rectangle:new( 32, 128, 256, 64 ),
		text = "Textured Button",
		callbacks = {
			pressed = function() print( "Textured button clicked!" ) end,
		},
		tooltip = "This button has texture",
		styles = button3Styles,
	} )

	-- Label.

	local labelStyle = Util.deepCopy( GUI_DEFAULT_STYLES )
	labelStyle.normal.text.fontSize = 20
	labelStyle.normal.text.spacing = 2

	label = gui:newLabel( {
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

	textInputBox = gui:newTextInputBox( {
		bounds = Rectangle:new( 32, 200, 256, 32 ),
		text = "Edit",
		callbacks = {
			pressed = function() print( "Start Editing!" ) end,
		},
		styles = textEditStyle,
		tooltip = "This is single line text edit box"
	} )
end

function RL.update( delta )
	gui:update( delta )
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	gui:draw()
end
