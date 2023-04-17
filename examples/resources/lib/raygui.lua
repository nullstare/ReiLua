-- Wrapper for raygui that should make using it a bit more convenient.

Util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )

---@param text string
---@return integer count, table rowItemCounts
local function getItemCount( text )
	local count, rowItemCounts = 1, { 1 }

	for i = 1, #text do
		if text:sub( i, i ) == "\n" then
			table.insert( rowItemCounts, 1 )

			count = count + 1
		elseif text:sub( i, i ) == ";" then
			rowItemCounts[ #rowItemCounts ] = rowItemCounts[ #rowItemCounts ] + 1

			count = count + 1
		end
	end

	return count, rowItemCounts
end

local function getItems( text )
	if text == "" then
		return {}
	end

	local items = {}
	local startChar = 1

	for i = 1, #text do
		if text:sub( i, i ) == "\n" or text:sub( i, i ) == ";" then
			table.insert( items, text:sub( startChar, i - 1 ) )
			startChar = i + 1
		end
	end
	-- Last one.
	table.insert( items, text:sub( startChar, #text ) )

	return items
end

-- Raygui.

Raygui = {
	RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT = 24,

	elements = {},
	focused = 0,
	dragging = nil,
	grabPos = Vec2:new(),
}

function Raygui.process()
	-- If dragging, don't process element masking.
	if Raygui.dragging ~= nil then
		Raygui.drag( Raygui.dragging )

		return
	end

	for i = #Raygui.elements, 1, -1 do
		local element = Raygui.elements[i]

        if element.visible and element.process ~= nil then
            if element:process() then
                Raygui.focused = i

                return
            end
        end
    end
end

function Raygui.drag( element )
	local mousePos = Vec2:new( RL.GetMousePosition() )
	local mouseOver = RL.CheckCollisionPointRec( mousePos, element.bounds )

	if element.draggable and element ~= Raygui.dragging and RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT )
	and mouseOver and mousePos.y - element.bounds.y <= Raygui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT then
		Raygui.grabPos = mousePos - Vec2:new( element.bounds.x, element.bounds.y )

		if element.grabCallback ~= nil then
			element.grabCallback( element )
		end
		Raygui.dragging = element
	end

	if element == Raygui.dragging then
		if not RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) then
			Raygui.dragging = nil
		end

		element:setPosition( mousePos - Raygui.grabPos )

		if element.dragCallback ~= nil then
			element.dragCallback( element )
		end
	end

    return mouseOver
end

function Raygui.draw()
	RL.GuiLock()

    for i, element in ipairs( Raygui.elements ) do
        if i == Raygui.focused then
            RL.GuiUnlock()
        end

        if element.visible and element.draw ~= nil then
            element:draw()
        end
    end
end

function Raygui.set2Top( element )
	for i, curElement in ipairs( Raygui.elements ) do
		if element == curElement then
			Util.tableMove( Raygui.elements, i, 1, #Raygui.elements )

			return
		end
	end
end

function Raygui.set2Back( element )
	for i, curElement in ipairs( Raygui.elements ) do
		if element == curElement then
			Util.tableMove( Raygui.elements, i, 1, 1 )

			return
		end
	end
end

--[[
	Container/separator controls, useful for controls organization
]]--

-- WindowBox.

--- Window Box control, shows a window that can be closed
---@class WindowBox
---@field bounds table Rect
---@field text string
---@field callback function|nil
---@field grabCallback function|nil
---@field dragCallback function|nil
---@field visible boolean
---@field draggable boolean
WindowBox = {}
WindowBox.__index = WindowBox

---@param bounds table Rect
---@param text string
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table object
function WindowBox:new( bounds, text, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, WindowBox )

    object.bounds = bounds:clone()
    object.text = text
	object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.visible = true
	object.draggable = true

	table.insert( Raygui.elements, object )

	return object
end

function WindowBox:process()
	return Raygui.drag( self )
end

function WindowBox:draw()
	if RL.GuiWindowBox( self.bounds, self.text ) and self.callback ~= nil then
        self.callback( self )
    end
end

function WindowBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- GroupBox.

--- Group Box control with text name
---@class GroupBox
---@field bounds table Rect
---@field text string
---@field visible boolean
GroupBox = {}
GroupBox.__index = GroupBox

---@param bounds table Rect
---@param text string
function GroupBox:new( bounds, text )
    local object = setmetatable( {}, GroupBox )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function GroupBox:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function GroupBox:draw()
	RL.GuiGroupBox( self.bounds, self.text )
end

function GroupBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Line.

--- Line separator control, could contain text
Line = {}
Line.__index = Line

function Line:new( bounds, text )
    local object = setmetatable( {}, Line )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Line:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Line:draw()
	RL.GuiLine( self.bounds, self.text )
end

function Line:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Panel.

--- Panel control, useful to group controls
Panel = {}
Panel.__index = Panel

function Panel:new( bounds, text, grabCallback, dragCallback )
    local object = setmetatable( {}, Panel )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true
	object.draggable = true
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	table.insert( Raygui.elements, object )

	return object
end

function Panel:process()
    return Raygui.drag( self )
end

function Panel:draw()
	RL.GuiPanel( self.bounds, self.text )
end

function Panel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ScrollPanel.

--- Scroll Panel control
ScrollPanel = {}
ScrollPanel.__index = ScrollPanel

function ScrollPanel:new( bounds, text, content, scroll, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, ScrollPanel )

    object.bounds = bounds:clone()
    object.text = text
    object.content = content:clone()
    object.scroll = scroll:clone()
	object.view = Rect:new()
    object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.visible = true
	object.draggable = true

	table.insert( Raygui.elements, object )

	return object
end

function ScrollPanel:process()
    return Raygui.drag( self )
end

function ScrollPanel:draw()
	local oldScroll = self.scroll:clone()

	local view, scroll = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll )

	self.view = Rect:new( view )
	self.scroll = Vec2:new( scroll )

	if self.scroll ~= oldScroll and self.callback ~= nil then
		self.callback( self )
	end
end

function ScrollPanel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

--[[
	Basic controls set
]]--

-- Label.

--- Label control, shows text
Label = {}
Label.__index = Label

function Label:new( bounds, text )
    local object = setmetatable( {}, Label )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Label:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Label:draw()
    RL.GuiLabel( self.bounds, self.text )
end

function Label:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Button.

--- Button control
Button = {}
Button.__index = Button

function Button:new( bounds, text, callback )
    local object = setmetatable( {}, Button )

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

    object.clicked = false
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Button:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Button:draw()
    self.clicked = RL.GuiButton( self.bounds, self.text )

    if self.clicked and self.callback ~= nil then
        self.callback( self )
    end
end

function Button:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- LabelButton.

--- Label button control
LabelButton = {}
LabelButton.__index = LabelButton

function LabelButton:new( bounds, text, callback )
    local object = setmetatable( {}, LabelButton )

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

    object.clicked = false
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function LabelButton:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function LabelButton:draw()
    self.clicked = RL.GuiLabelButton( self.bounds, self.text )

    if self.clicked and self.callback ~= nil then
        self.callback( self )
    end
end

function LabelButton:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Toggle.

--- Toggle Button control
Toggle = {}
Toggle.__index = Toggle

function Toggle:new( bounds, text, active, callback )
    local object = setmetatable( {}, Toggle )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Toggle:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Toggle:draw()
    local oldActive = self.active

    self.active = RL.GuiToggle( self.bounds, self.text, self.active )

    if self.active ~= oldActive and self.callback ~= nil then
        self.callback( self )
    end
end

function Toggle:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ToggleGroup.

--- Toggle Group control
ToggleGroup = {}
ToggleGroup.__index = ToggleGroup

function ToggleGroup:new( bounds, text, active, callback )
    local object = setmetatable( {}, ToggleGroup )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true
	object.focusBounds = {}
    object:updateFocusBounds()

	table.insert( Raygui.elements, object )

	return object
end

function ToggleGroup:setText( text )
    self.text = text

    self:updateFocusBounds()
end

function ToggleGroup:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function ToggleGroup:updateFocusBounds()
	if self.text == "" then
		return
	end

	local count, rowItemCounts = getItemCount( self.text )

	self.focusBounds = {}

	for y, rowItemCount in ipairs( rowItemCounts ) do
		for x = 1, rowItemCount do
			local pos = Vec2:new( x - 1, y - 1 )

			table.insert( self.focusBounds, Rect:new(
				self.bounds.x + pos.x * ( self.bounds.width + RL.GuiGetStyle( RL.TOGGLE, RL.GROUP_PADDING ) ),
				self.bounds.y + pos.y * ( self.bounds.height + RL.GuiGetStyle( RL.TOGGLE, RL.GROUP_PADDING ) ),
				self.bounds.width,
				self.bounds.height
			) )
		end
	end
end

function ToggleGroup:process()
	for _, bounds in ipairs( self.focusBounds ) do
		if RL.CheckCollisionPointRec( RL.GetMousePosition(), bounds ) then
			return true
		end
	end

	return false
end

function ToggleGroup:draw()
    local oldActive = self.active

    self.active = RL.GuiToggleGroup( self.bounds, self.text, self.active )

    if self.active ~= oldActive and self.callback ~= nil then
        self.callback( self )
    end

	-- for _, rect in ipairs( self.focusBounds ) do
	-- 	RL.DrawRectangleLines( rect, RL.RED )
	-- end
end

function ToggleGroup:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateFocusBounds()
end

-- CheckBox.

--- Check Box control
CheckBox = {}
CheckBox.__index = CheckBox

function CheckBox:new( bounds, text, checked, callback )
    local object = setmetatable( {}, CheckBox )

    object.bounds = bounds:clone()
    object.text = text
    object.checked = checked
    object.callback = callback

	object.visible = true
    object.focusBounds = bounds:clone()
    object:updateFocusBounds()

	table.insert( Raygui.elements, object )

	return object
end

function CheckBox:setText( text )
    self.text = text

    self:updateFocusBounds()
end

function CheckBox:updateFocusBounds()
    if self.text == "" then
        return
    end

    local textSize = Vec2:new( RL.MeasureText(
        RL.GuiGetFont(),
        self.text,
        RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SIZE ),
        RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING )
    ) )

    local textBounds = Rect:new()

	textBounds.width = textSize.x
	textBounds.height = textSize.y
	textBounds.x = self.bounds.x + self.bounds.width + RL.GuiGetStyle( RL.CHECKBOX, RL.TEXT_PADDING )
	textBounds.x = self.bounds.y + self.bounds.height / 2 - RL.GuiGetStyle( RL.CHECKBOX, RL.TEXT_SIZE ) / 2

	if RL.GuiGetStyle( RL.CHECKBOX, RL.TEXT_ALIGNMENT ) == RL.TEXT_ALIGN_LEFT then
		textBounds.x = self.bounds.x - textBounds.width - RL.GuiGetStyle( RL.CHECKBOX, RL.TEXT_PADDING )
		self.focusBounds.x = textBounds.x
	else
		self.focusBounds.x = self.bounds.x
	end

	self.focusBounds.y = self.bounds.y
	self.focusBounds.width = self.bounds.width + textBounds.width + RL.GuiGetStyle( RL.CHECKBOX, RL.TEXT_PADDING )
	self.focusBounds.height = self.bounds.height
end

function CheckBox:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.focusBounds )
end

function CheckBox:draw()
    local oldChecked = self.checked

    self.checked = RL.GuiCheckBox( self.bounds, self.text, self.checked )

    if self.checked ~= oldChecked and self.callback ~= nil then
        self.callback( self )
    end

    -- RL.DrawRectangleLines( self.focusBounds, RL.RED )
end

function CheckBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateFocusBounds()
end

-- ComboBox.

--- Combo Box control
ComboBox = {}
ComboBox.__index = ComboBox

function ComboBox:new( bounds, text, active, callback )
    local object = setmetatable( {}, ComboBox )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ComboBox:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ComboBox:draw()
    local oldActive = self.active

    self.active = RL.GuiComboBox( self.bounds, self.text, self.active )

    if self.active ~= oldActive and self.callback ~= nil then
        self.callback( self )
    end
end

function ComboBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- DropdownBox.

--- Dropdown Box control
DropdownBox = {}
DropdownBox.__index = DropdownBox

function DropdownBox:new( bounds, text, active, editMode, callback )
    local object = setmetatable( {}, DropdownBox )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.editMode = editMode
    object.callback = callback

	object.visible = true
	object.editModeBounds = bounds:clone()
	object:updateFocusBounds()

	table.insert( Raygui.elements, object )

	return object
end

function DropdownBox:setText( text )
    self.text = text

	self:updateFocusBounds()
end

function DropdownBox:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function DropdownBox:updateFocusBounds()
	if self.text == "" then
		return
	end

	local count = getItemCount( self.text )

	self.editModeBounds = self.bounds:clone()
	self.editModeBounds.height = ( 1 + count ) * ( self.bounds.height + RL.GuiGetStyle( RL.DROPDOWNBOX, RL.DROPDOWN_ITEMS_SPACING ) )
end

function DropdownBox:process()
	if self.editMode then
		return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.editModeBounds )
	else
		return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
	end
end

function DropdownBox:draw()
	local pressed = false

    pressed, self.active = RL.GuiDropdownBox( self.bounds, self.text, self.active, self.editMode )

    if pressed then
		self.editMode = not self.editMode

		if not self.editMode and self.callback ~= nil then
			self.callback( self )
		end
    end
end

function DropdownBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Spinner.

--- Spinner control
Spinner = {}
Spinner.__index = Spinner

function Spinner:new( bounds, text, value, minValue, maxValue, editMode, callback )
    local object = setmetatable( {}, Spinner )

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.editMode = editMode
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Spinner:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Spinner:draw()
	local pressed = false
	local oldValue = self.value

    pressed, self.value = RL.GuiSpinner( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )

    if pressed then
		self.editMode = not self.editMode
    end

	if self.value ~= oldValue and self.callback ~= nil then
		self.callback( self )
	end
end

function Spinner:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ValueBox.

--- Value Box control
ValueBox = {}
ValueBox.__index = ValueBox

function ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callback )
    local object = setmetatable( {}, ValueBox )

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.editMode = editMode
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ValueBox:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ValueBox:draw()
	local pressed = false
	local oldValue = self.value

    pressed, self.value = RL.GuiValueBox( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )

    if pressed then
		self.editMode = not self.editMode
    end

	if self.value ~= oldValue and self.callback ~= nil then
		self.callback( self )
	end
end

function ValueBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- TextBox.

--- Text Box control
TextBox = {}
TextBox.__index = TextBox

function TextBox:new( bounds, text, textSize, editMode, callback )
    local object = setmetatable( {}, TextBox )

    object.bounds = bounds:clone()
    object.text = text
    object.textSize = textSize
    object.editMode = editMode
    object.callback = callback
	-- Option for preventing text to be drawn outside bounds.
	object.scissorMode = false
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function TextBox:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function TextBox:draw()
	local pressed = false

	if self.scissorMode then
		RL.BeginScissorMode( self.bounds )
	end

    pressed, self.text = RL.GuiTextBox( self.bounds, self.text, self.textSize, self.editMode )

	if self.scissorMode then
		RL.EndScissorMode()
	end

    if pressed then
		self.editMode = not self.editMode

		if not self.editMode and self.callback ~= nil then
			self.callback( self )
		end
    end
end

function TextBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- TextBoxMulti.

-- Text Box control with multiple lines
TextBoxMulti = {}
TextBoxMulti.__index = TextBoxMulti

function TextBoxMulti:new( bounds, text, textSize, editMode, callback )
    local object = setmetatable( {}, TextBoxMulti )

    object.bounds = bounds:clone()
    object.text = text
    object.textSize = textSize
    object.editMode = editMode
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function TextBoxMulti:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function TextBoxMulti:draw()
	local pressed = false

    pressed, self.text = RL.GuiTextBoxMulti( self.bounds, self.text, self.textSize, self.editMode )

    if pressed then
		self.editMode = not self.editMode

		if not self.editMode and self.callback ~= nil then
			self.callback( self )
		end
    end
end

function TextBoxMulti:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Slider.

--- Slider control
Slider = {}
Slider.__index = Slider

function Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, Slider )

    object.bounds = bounds:clone()
    object.textLeft = textLeft
    object.textRight = textRight
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Slider:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Slider:draw()
	local oldValue = self.value

    self.value = RL.GuiSlider( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )

    if self.value ~= oldValue then
		self.callback( self )
    end
end

function Slider:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- SliderBar.

--- Slider Bar control
SliderBar = {}
SliderBar.__index = SliderBar

function SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, SliderBar )

    object.bounds = bounds:clone()
    object.textLeft = textLeft
    object.textRight = textRight
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function SliderBar:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SliderBar:draw()
	local oldValue = self.value

    self.value = RL.GuiSliderBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )

    if self.value ~= oldValue then
		self.callback( self )
    end
end

function SliderBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ProgressBar.

--- Progress Bar control, shows current progress value
ProgressBar = {}
ProgressBar.__index = ProgressBar

function ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, ProgressBar )

    object.bounds = bounds:clone()
    object.textLeft = textLeft
    object.textRight = textRight
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ProgressBar:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ProgressBar:draw()
	local oldValue = self.value

    self.value = RL.GuiProgressBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )

    if self.value ~= oldValue then
		self.callback( self )
    end
end

function ProgressBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- StatusBar.

--- Status Bar control, shows info text
StatusBar = {}
StatusBar.__index = StatusBar

function StatusBar:new( bounds, text )
    local object = setmetatable( {}, StatusBar )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function StatusBar:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function StatusBar:draw()
    RL.GuiStatusBar( self.bounds, self.text )
end

function StatusBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- DummyRec.

--- Dummy control for placeholders
DummyRec = {}
DummyRec.__index = DummyRec

function DummyRec:new( bounds, text )
    local object = setmetatable( {}, DummyRec )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function DummyRec:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function DummyRec:draw()
    RL.GuiDummyRec( self.bounds, self.text )
end

function DummyRec:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Grid.

--- Grid control
Grid = {}
Grid.__index = Grid

function Grid:new( bounds, text, spacing, subdivs, callback )
    local object = setmetatable( {}, Grid )

    object.bounds = bounds:clone()
    object.text = text
    object.spacing = spacing
    object.subdivs = subdivs
	object.callback = callback

	object.cell = Vec2:new()
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function Grid:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Grid:draw()
	local oldCell = self.cell:clone()

	self.cell = Vec2:new( RL.GuiGrid( self.bounds, self.text, self.spacing, self.subdivs ) )

	if oldCell ~= self.cell and self.callback ~= nil then
		self.callback( self )
	end
end

function Grid:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

--[[
	Advance controls set
]]--

-- ListView.

--- List View control
ListView = {}
ListView.__index = ListView

function ListView:new( bounds, text, scrollIndex, active, callback )
    local object = setmetatable( {}, ListView )

    object.bounds = bounds:clone()
    object.text = text
    object.scrollIndex = scrollIndex
    object.active = active
	object.callback = callback
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ListView:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function ListView:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ListView:draw()
	local oldActive = self.active

	self.active, self.scrollIndex = RL.GuiListView( self.bounds, self.text, self.scrollIndex, self.active )

	if oldActive ~= self.active and self.callback ~= nil then
		self.callback( self )
	end
end

function ListView:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ListViewEx.

--- List View with extended parameters
ListViewEx = {}
ListViewEx.__index = ListViewEx

function ListViewEx:new( bounds, text, focus, scrollIndex, active, callback )
    local object = setmetatable( {}, ListViewEx )

    object.bounds = bounds:clone()
    object.text = text
    object.focus = focus
    object.scrollIndex = scrollIndex
    object.active = active
	object.callback = callback
	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ListViewEx:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function ListViewEx:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ListViewEx:draw()
	local oldActive = self.active

	self.active, self.scrollIndex, self.focus = RL.GuiListViewEx( self.bounds, self.text, self.focus, self.scrollIndex, self.active )

	if oldActive ~= self.active and self.callback ~= nil then
		self.callback( self )
	end
end

function ListViewEx:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- MessageBox.

--- Message Box control, displays a message
MessageBox = {}
MessageBox.__index = MessageBox

function MessageBox:new( bounds, title, message, buttons, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, MessageBox )

    object.bounds = bounds:clone()
    object.title = title
    object.message = message
    object.buttons = buttons
	object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.buttonIndex = -1
	object.visible = true
	object.draggable = true

	table.insert( Raygui.elements, object )

	return object
end

function MessageBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function MessageBox:process()
	return Raygui.drag( self )
end

function MessageBox:draw()
	self.buttonIndex = RL.GuiMessageBox( self.bounds, self.title, self.message, self.buttons )

	if 0 <= self.buttonIndex and self.callback ~= nil then
		self.callback( self )
	end
end

function MessageBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- TextInputBox.

--- Text Input Box control, ask for text, supports secret
TextInputBox = {}
TextInputBox.__index = TextInputBox

function TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, TextInputBox )

    object.bounds = bounds:clone()
    object.title = title
    object.message = message
    object.buttons = buttons
    object.text = text
    object.textMaxSize = textMaxSize
    object.secretViewActive = secretViewActive
	object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.buttonIndex = -1
	object.visible = true
	object.draggable = true

	table.insert( Raygui.elements, object )

	return object
end

function TextInputBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function TextInputBox:process()
	return Raygui.drag( self )
end

function TextInputBox:draw()
	self.buttonIndex, self.text, self.secretViewActive = RL.GuiTextInputBox( self.bounds, self.title, self.message, self.buttons, self.text, self.textMaxSize, self.secretViewActive )

	if 0 <= self.buttonIndex and self.callback ~= nil then
		self.callback( self )
	end
end

function TextInputBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorPicker.

--- Color Picker control ( multiple color controls )
ColorPicker = {}
ColorPicker.__index = ColorPicker

function ColorPicker:new( bounds, text, color, callback )
    local object = setmetatable( {}, ColorPicker )

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ColorPicker:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorPicker:draw()
	local oldColor = self.color:clone()
	local color = RL.GuiColorPicker( self.bounds, self.text, self.color )

	self.color = Color:new( color )

	if oldColor ~= self.color and self.callback ~= nil then
		self.callback( self )
	end
end

function ColorPicker:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorPanel.

--- Color Panel control
ColorPanel = {}
ColorPanel.__index = ColorPanel

function ColorPanel:new( bounds, text, color, callback )
    local object = setmetatable( {}, ColorPanel )

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ColorPanel:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorPanel:draw()
	local oldColor = self.color:clone()
	local color = RL.GuiColorPanel( self.bounds, self.text, self.color )

	self.color = Color:new( color )

	if oldColor ~= self.color and self.callback ~= nil then
		self.callback( self )
	end
end

function ColorPanel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorBarAlpha.

--- Color Bar Alpha control
ColorBarAlpha = {}
ColorBarAlpha.__index = ColorBarAlpha

function ColorBarAlpha:new( bounds, text, alpha, callback )
    local object = setmetatable( {}, ColorBarAlpha )

    object.bounds = bounds:clone()
    object.text = text
    object.alpha = alpha
	object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ColorBarAlpha:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorBarAlpha:draw()
	local oldAlpha = self.alpha
	self.alpha = RL.GuiColorBarAlpha( self.bounds, self.text, self.alpha )

	if self.alpha ~= oldAlpha and self.callback ~= nil then
		self.callback( self )
	end
end

function ColorBarAlpha:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorBarHue.

--- Color Bar Hue control
ColorBarHue = {}
ColorBarHue.__index = ColorBarHue

function ColorBarHue:new( bounds, text, value, callback )
    local object = setmetatable( {}, ColorBarHue )

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
	object.callback = callback

	object.visible = true

	table.insert( Raygui.elements, object )

	return object
end

function ColorBarHue:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorBarHue:draw()
	local oldValue = self.value
	self.value = RL.GuiColorBarHue( self.bounds, self.text, self.value )

	if self.value ~= oldValue and self.callback ~= nil then
		self.callback( self )
	end
end

function ColorBarHue:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

--Assingments.

Raygui.WindowBox = WindowBox
Raygui.GroupBox = GroupBox
Raygui.Line = Line
Raygui.Panel = Panel
Raygui.ScrollPanel = ScrollPanel

Raygui.Label = Label
Raygui.Button = Button
Raygui.LabelButton = LabelButton
Raygui.Toggle = Toggle
Raygui.ToggleGroup = ToggleGroup
Raygui.CheckBox = CheckBox
Raygui.ComboBox = ComboBox
Raygui.DropdownBox = DropdownBox
Raygui.Spinner = Spinner
Raygui.ValueBox = ValueBox
Raygui.TextBox = TextBox
Raygui.TextBoxMulti = TextBoxMulti
Raygui.Slider = Slider
Raygui.SliderBar = SliderBar
Raygui.ProgressBar = ProgressBar
Raygui.StatusBar = StatusBar
Raygui.DummyRec = DummyRec
Raygui.Grid = Grid

Raygui.ListView = ListView
Raygui.ListViewEx = ListViewEx
Raygui.MessageBox = MessageBox
Raygui.TextInputBox = TextInputBox
Raygui.ColorPicker = ColorPicker
Raygui.ColorPanel = ColorPanel
Raygui.ColorBarAlpha = ColorBarAlpha
Raygui.ColorBarHue = ColorBarHue

return Raygui
