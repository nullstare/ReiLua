local windowOpen = true
local toggled = false
local checkbox = false
local textBoxText = "Edit"
local textBoxActive = false
local spinnerValue = 3
local spinnerActive = false
local spinnerValueRange = { 0, 10 }
local sliderValue = 5.0
local sliderValueRange = { 0.0, 10.0 }
local scrollbarValue = 0.0
local dropdownValue = 0
local dropdownActive = false
local index = 0
local listView = { item = 0, scroll = 0 }
local listViewEx = { item = 0, scroll = 0, focus = 0 }
local messageBox = { buttonIndex = -1 }
local textInputBox = { buttonIndex = 0, text = "", secretViewActive = 1 }
local colorPicker = { color = { 255, 255, 255 } }
local colorPanel = { color = { 255, 255, 255 }, alpha = 1.0, hue = 1.0, oldHue = 1.0 }
local comboBoxActive = 0

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = { 1920, 1080 }

	RL.GuiSetFont( RL.defaultFont )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 10 )

	if RL.GuiButton( { 112, 16, 96, 32 }, RL.GuiIconText( 113, "Exit" ) ) then
		RL.CloseWindow()
	end

	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 20 )
	RL.GuiButton( { 112, 64, 96, 32 }, RL.GuiIconText( 113, "Cat" ) )
	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 10 )

	if windowOpen and RL.GuiWindowBox( { 300, 16, 200, 320 }, "Window" ) then
		windowOpen = false
	end

	RL.GuiPanel( { 60, 260, 100, 100 }, "Panel" )

	toggled = RL.GuiToggle( { 200, 260, 64, 32 }, "Toggle", toggled )
	index = RL.GuiToggleGroup( { 520, 30, 64, 32 }, "Cat\nDog\nMonkey", index )
	checkbox = RL.GuiCheckBox( { 200, 300, 16, 16 }, "CheckBox", checkbox )

	local textBoxToggle = false
	textBoxToggle, textBoxText = RL.GuiTextBox( { 32, 400, 120, 32 }, textBoxText, 32, textBoxActive )
	-- textBoxToggle, textBoxText = RL.GuiTextBoxMulti( { 32, 400, 120, 64 }, textBoxText, 120, textBoxActive )

	if textBoxToggle then
		textBoxActive = not textBoxActive
	end

	local spinnerToggle = false
	spinnerToggle, spinnerValue = RL.GuiSpinner( { 64, 450, 96, 32 }, "Value", spinnerValue, spinnerValueRange[1], spinnerValueRange[2], spinnerActive )
	-- spinnerToggle, spinnerValue = RL.GuiValueBox( { 64, 450, 96, 32 }, "Value", spinnerValue, spinnerValueRange[1], spinnerValueRange[2], spinnerActive )

	if spinnerToggle then
		spinnerActive = not spinnerActive
	end

	sliderValue = RL.GuiSliderBar( { 64, 510, 96, 32 }, "min", "max", sliderValue, sliderValueRange[1], sliderValueRange[2] )
	scrollbarValue = RL.GuiScrollBar( { 64, 550, 130, 32 }, scrollbarValue, 0, 10 )

	local dropdownToggle = false
	dropdownToggle, dropdownValue = RL.GuiDropdownBox( { 2, 2, 96, 16 }, "Cat\nDog\nMonkey", dropdownValue, dropdownActive )

	if dropdownToggle then
		dropdownActive = not dropdownActive
	end

	listView.item, listView.scroll = RL.GuiListView( { 200, 400, 200, 200 }, "Cat\nElefant\nSquirrel", listView.scroll, listView.item )
	messageBox.buttonIndex = RL.GuiMessageBox( { 420, 400, 200, 100 }, "Message", "Are you sure about this?", "Yes\nNo" )

	if 0 <= messageBox.buttonIndex then
		print( "messageBox.buttonIndex", messageBox.buttonIndex )
	end

	textInputBox.buttonIndex, textInputBox.text, textInputBox.secretViewActive
	= RL.GuiTextInputBox( { 420, 510, 300, 150 }, "Input Box", "Put text here", "Button", textInputBox.text, 200, textInputBox.secretViewActive )

	if 0 <= textInputBox.buttonIndex then
		print( "textInputBox.buttonIndex", textInputBox.buttonIndex )
	end

	colorPicker.color = RL.GuiColorPicker( { 620, 20, 150, 150 }, "Color Picker", colorPicker.color )

	colorPanel.color = RL.GuiColorPanel( { 820, 20, 150, 150 }, "Color Panel", colorPanel.color )
	colorPanel.alpha = RL.GuiColorBarAlpha( { 820, 180, 150, 20 }, "Color alpha", colorPanel.alpha )
	colorPanel.hue = RL.GuiColorBarHue( { 980, 20, 20, 150 }, "Color hue", colorPanel.hue )

	if colorPanel.hue ~= colorPanel.oldHue then
		colorPanel.oldHue = colorPanel.hue

		colorPanel.color = RL.ColorFromHSV( colorPanel.hue, 1.0, 1.0 )
	end

	RL.GuiDrawIcon( 121, { 6, 20 }, 2, RL.WHITE )

	comboBoxActive = RL.GuiComboBox( { 5, 50, 80, 20 }, "One\nTwo\nThree", comboBoxActive )
end
