package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )
Color = require( "color" )

local textSize = 10
local spacing = 1
local rect = Rectangle:new( 100, 64, 200, 200 )
local wordwrap = true
local linkColor = RL.BLUE
local limitHeight = false
local mouseCharId = 0
local textOffset = Vector2:new( 0, 0 )
local measuredBox = Rectangle:new()

local texts = {
	{
		text = "\tYou can change the size of the box by pressing right mouse and toggle the wordwrap by pressing space. First we will write some text before the hyperlink to show that it is indeed is as powerful feature as adverticed.",
		color = RL.RED,
	},
	{
		text = " Hyperlink.",
		color = linkColor,
		hyperlink = true,
	},
	{
		text = " Then we demonstrate this further by writin more text after the link. Isn't this just amazing! Don't forget to press left mouse to print text to your console when hovering mouse over the hyperlink.",
		color = RL.RED,
	},
	{
		text = " \a#D28484FF Also supports \a#0000FFFF changing text \a#CCD834FF color in the \a#00FFFFFF middle of \a#B623A3FF the \a#00FF00FF text draw.",
		color = RL.WHITE,
	},
}

function RL.init()
	RL.SetWindowTitle( "Text boxed" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

function RL.update( delta )
	if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_RIGHT ) then
		local mousePos = Vector2:newT( RL.GetMousePosition() )

		rect:setSizeV( mousePos - rect:getPosition() )
	end

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) and 0 < mouseCharId then
		print( "Pressed link on char "..mouseCharId )
	end

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		wordwrap = not wordwrap
	end

	measuredBox = Rectangle:new( rect.x, rect.y, 0, 0 )
	textOffset = Vector2:new()
	local measuredSize, measuredOffset

	for _, text in ipairs( texts ) do
		measuredSize, measuredOffset = RL.MeasureTextBoxed(
			RL.GetFontDefault(),
			text.text,
			rect,
			textSize, spacing, wordwrap, text.color, limitHeight, textOffset
		)
		textOffset:setT( measuredOffset )
		measuredBox:setSizeT( measuredSize )
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.DrawRectangleLines( rect, RL.GREEN )
	RL.DrawRectangleLines( measuredBox, RL.BLUE )
	textOffset = Vector2:new()
	mouseCharId = 0

	for _, text in ipairs( texts ) do
		local mouseId = 0

		mouseId, textOffset = RL.DrawTextBoxed(
			RL.GetFontDefault(),
			text.text,
			rect,
			textSize, spacing, wordwrap, text.color, limitHeight, textOffset
		)

		if text.hyperlink and 0 < mouseId then
			mouseCharId = mouseId
		end
	end

	if 0 < mouseCharId then
		linkColor = RL.GREEN
	else
		linkColor = RL.BLUE
	end
end
