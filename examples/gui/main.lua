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
local dropdownValue = 0
local dropdownActive = false
local index = 0
local listView = { item = 0, scroll = 0 }
local textInputBox = { buttonIndex = 0, text = "", secretViewActive = false }
local colorPicker = { color = { 255, 255, 255 } }
local colorPanel = { color = { 255, 255, 255 }, alpha = 1.0, hue = 1.0, oldHue = 1.0 }
local comboBoxActive = 0
local scrollPanel = { scroll = { 0, 0 }, view = { 0, 0, 320, 200 } }
local guiTabBarActive = 0
local colorPickerHSV = { 0, 0, 0 }
local colorPanelHSV = { 0, 0, 0 }

local value = 0

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = { 1920, 1080 }

	RL.GuiSetFont( RL.GetFontDefault() )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	RL.GuiSetStyle( RL.LISTVIEW, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT )
end

function RL.draw()
	RL.ClearBackground( { 50, 20, 75 } )

	local result = 0
	-- RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, 10 )

	if RL.GuiButton( { 112, 16, 96, 32 }, RL.GuiIconText( RL.ICON_CROSS, "Exit" ) ) == 1 then
		RL.CloseWindow()
	end

	RL.GuiButton( { 112, 64, 96, 32 }, RL.GuiIconText( RL.ICON_FOUR_BOXES, "Cat" ) )

	if windowOpen and RL.GuiWindowBox( { 300, 16, 200, 320 }, "Window" ) == 1 then
		windowOpen = false
	end
	
	RL.GuiPanel( { 60, 260, 100, 100 }, "Panel" )

	_, toggled = RL.GuiToggle( { 200, 260, 64, 32 }, "Toggle", toggled )

	_, index = RL.GuiToggleGroup( { 520, 30, 64, 32 }, "Cat\nDog\nMonkey", index )
	
	_, checkbox = RL.GuiCheckBox( { 200, 300, 16, 16 }, "CheckBox", checkbox )

	result, textBoxText = RL.GuiTextBox( { 32, 400, 120, 32 }, textBoxText, 32, textBoxActive )
	if result == 1 then
		textBoxActive = not textBoxActive
	end

	result, spinnerValue = RL.GuiSpinner( { 64, 450, 96, 32 }, "Value", spinnerValue, spinnerValueRange[1], spinnerValueRange[2], spinnerActive )
	if result == 1 then
		spinnerActive = not spinnerActive
	end

	_, sliderValue = RL.GuiSliderBar( { 64, 510, 96, 32 }, "min", "max", sliderValue, sliderValueRange[1], sliderValueRange[2] )

	result, dropdownValue = RL.GuiDropdownBox( { 2, 2, 96, 16 }, "Cat\nDog\nMonkey", dropdownValue, dropdownActive )
	if result == 1 then
		dropdownActive = not dropdownActive
	end
	
	_, listView.scroll, listView.item = RL.GuiListView( { 200, 400, 200, 200 }, "Cat\nElefant\nSquirrel", listView.scroll, listView.item )

	result = RL.GuiMessageBox( { 420, 400, 200, 100 }, "Message", "Are you sure about this?", "Yes;No" )
	if 0 <= result then
		print( "messageBox.buttonIndex", result )
	end

	result, textInputBox.text, textInputBox.secretViewActive
	= RL.GuiTextInputBox( { 420, 510, 300, 150 }, "Input Box", "Put text here", "Button", textInputBox.text, 200, textInputBox.secretViewActive )
	if 0 <= result then
		print( "textInputBox.buttonIndex", result )
	end

	_, colorPicker.color = RL.GuiColorPicker( { 620, 20, 150, 150 }, "Color Picker", colorPicker.color )

	_, colorPanel.color = RL.GuiColorPanel( { 820, 20, 150, 150 }, "Color Panel", colorPanel.color )
	_, colorPanel.alpha = RL.GuiColorBarAlpha( { 820, 180, 150, 20 }, "Color alpha", colorPanel.alpha )
	_, colorPanel.hue = RL.GuiColorBarHue( { 980, 20, 20, 150 }, "Color hue", colorPanel.hue )

	if colorPanel.hue ~= colorPanel.oldHue then
		colorPanel.oldHue = colorPanel.hue
		colorPanel.color = RL.ColorFromHSV( colorPanel.hue, 1.0, 1.0 )
	end

	RL.GuiDrawIcon( 121, { 6, 80 }, 2, RL.BLACK )

	_, comboBoxActive = RL.GuiComboBox( { 5, 150, 80, 20 }, "One;Two;Three", comboBoxActive )

	_, scrollPanel.scroll, scrollPanel.view = RL.GuiScrollPanel(
		{ 64, 640, 320, 200 },
		"Scroll panel",
		{ 0, 0, 640, 400 },
		scrollPanel.scroll,
		scrollPanel.view
	)

	_, guiTabBarActive = RL.GuiTabBar(
		{ 420, 680, 320, 32 },
		RL.GuiIconText( RL.ICON_FILETYPE_PLAY, "Play" )..";"..RL.GuiIconText( RL.ICON_FILETYPE_IMAGE, "Cat.png" )..";"..RL.GuiIconText( RL.ICON_FILE_COPY, "Files" ),
		guiTabBarActive
	)

	_, colorPickerHSV = RL.GuiColorPickerHSV( { 1024, 20, 150, 150 }, "GuiColorPuckerHSV", colorPickerHSV )
	_, colorPanelHSV =  RL.GuiColorPanelHSV( { 1230, 20, 150, 150 }, "GuiColorPuckerHSV", colorPanelHSV )

	value = RL.GuiScrollBar( { 0, 0, 10, 200 }, value, 0, 100 )
end
