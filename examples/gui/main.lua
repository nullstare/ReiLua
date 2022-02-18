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

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_GuiSetFont( 0 )
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
end

function process( delta )
end

function draw()
	RL_ClearBackground( { 50, 20, 75 } )

	if RL_GuiButton( { 112, 16, 96, 32 }, "Button" ) then
		print( "Button pressed!" )
	end

	if windowOpen and RL_GuiWindowBox( { 300, 16, 200, 320 }, "Window" ) then
		windowOpen = false
	end

	RL_GuiPanel( { 60, 260, 100, 100 } )

	toggled = RL_GuiToggle( { 200, 260, 64, 32 }, "Toggle", toggled )
	checkbox = RL_GuiCheckBox( { 200, 300, 16, 16 }, "CheckBox", checkbox )

	local textBoxToggle = false
	textBoxToggle, textBoxText = RL_GuiTextBox( { 32, 400, 120, 32 }, textBoxText, 32, textBoxActive )
	-- textBoxToggle, textBoxText = RL_GuiTextBoxMulti( { 32, 400, 120, 64 }, textBoxText, 120, textBoxActive )
	
	if textBoxToggle then
		textBoxActive = not textBoxActive
	end

	local spinnerToggle = false
	spinnerToggle, spinnerValue = RL_GuiSpinner( { 64, 450, 96, 32 }, "Value", spinnerValue, spinnerValueRange[1], spinnerValueRange[2], spinnerActive )
	-- spinnerToggle, spinnerValue = RL_GuiValueBox( { 64, 450, 96, 32 }, "Value", spinnerValue, spinnerValueRange[1], spinnerValueRange[2], spinnerActive )

	if spinnerToggle then
		spinnerActive = not spinnerActive
	end

	sliderValue = RL_GuiSliderBar( { 64, 510, 96, 32 }, "min", "max", sliderValue, sliderValueRange[1], sliderValueRange[2] )
	scrollbarValue = RL_GuiScrollBar( { 64, 550, 130, 32 }, scrollbarValue, 0, 10 )

	local dropdownToggle = false
	dropdownToggle, dropdownValue = RL_GuiDropdownBox( { 2, 2, 96, 16 }, "Cat\nDog\nMonkey", dropdownValue, dropdownActive )

	if dropdownToggle then
		dropdownActive = not dropdownActive
	end
end
