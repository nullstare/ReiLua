local textSize = 10
local spacing = 1
local rect = { 100, 64, 200, 200 }
local wordwrap = true
local linkColor = RL.BLUE
local mouseCharId = 0
local textOffset = { 0, 0 }

function RL.init()
	RL.SetWindowTitle( "Text boxed" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

function RL.update( delta )
	if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_RIGHT ) then
		local mousePos = RL.GetMousePosition()

		rect[3] = mousePos[1] - rect[1]
		rect[4] = mousePos[2] - rect[2]
	end

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) and 0 < mouseCharId then
		print( "Pressed link on char "..mouseCharId )
	end

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		wordwrap = not wordwrap
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.DrawRectangleLines( rect, RL.GREEN )

	mouseCharId, textOffset = RL.DrawTextBoxedEx(
		RL.GetFontDefault(),
		"You can change the size of the box by pressing right mouse and toggle the wordwrap by pressing space. First we will write some text before the hyperlink to show that it is indeed is as powerful feature as adverticed.",
		rect,
		textSize, spacing, wordwrap, RL.RED, { 0, 0 }
	)
	mouseCharId, textOffset = RL.DrawTextBoxedEx(
		RL.GetFontDefault(),
		" Hyperlink.",
		rect,
		textSize, spacing, wordwrap, linkColor, textOffset
	)
	RL.DrawTextBoxedEx(
		RL.GetFontDefault(),
		" Then we demonstrate this further by writin more text after the link. Isn't this just amazing! Don't forget to press left mouse to print text to your console when hovering mouse over the hyperlink.",
		rect,
		textSize, spacing, wordwrap, RL.RED, textOffset
	)

	if 0 < mouseCharId then
		linkColor = RL.GREEN
	else
		linkColor = RL.BLUE
	end
end

