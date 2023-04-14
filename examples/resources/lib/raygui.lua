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

Raygui = {}
Raygui.__index = Raygui

function Raygui:new()
    local object = setmetatable( {}, Raygui )

    object.elements = {}
    object.focused = 0

	return object
end

function Raygui:add( element )
	table.insert( self.elements, element )

    return element
end

function Raygui:process()
    for i = #self.elements, 1, -1 do
		local element = self.elements[i]

        if element.visible and element.process ~= nil then
            if element:process() then
                self.focused = i

                return
            end
        end
    end
end

function Raygui:draw()
    RL.GuiLock()

    for i, element in ipairs( self.elements ) do
        if i == self.focused then
            RL.GuiUnlock()
        end

        if element.visible and element.draw ~= nil then
            element:draw()
        end
    end
end

function Raygui:set2Top( element )
	for i, curElement in ipairs( self.elements ) do
		if element == curElement then
			Util.tableMove( self.elements, i, 1, #self.elements )

			return
		end
	end
end

function Raygui:set2Back( element )
	for i, curElement in ipairs( self.elements ) do
		if element == curElement then
			Util.tableMove( self.elements, i, 1, 1 )

			return
		end
	end
end

--[[
	Container/separator controls, useful for controls organization
]]--

-- WindowBox.

WindowBox = {}
WindowBox.__index = WindowBox

function WindowBox:new( bounds, text, callback )
    local object = setmetatable( {}, WindowBox )

    object.bounds = bounds:clone()
    object.text = text
	object.callback = callback

	object.visible = true

	return object
end

function WindowBox:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
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

GroupBox = {}
GroupBox.__index = GroupBox

function GroupBox:new( bounds, text )
    local object = setmetatable( {}, GroupBox )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

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

Line = {}
Line.__index = Line

function Line:new( bounds, text )
    local object = setmetatable( {}, Line )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

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

Panel = {}
Panel.__index = Panel

function Panel:new( bounds, text )
    local object = setmetatable( {}, Panel )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

	return object
end

function Panel:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Panel:draw()
	RL.GuiPanel( self.bounds, self.text )
end

function Panel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ScrollPanel.

ScrollPanel = {}
ScrollPanel.__index = ScrollPanel

function ScrollPanel:new( bounds, text, content, scroll, callback )
    local object = setmetatable( {}, ScrollPanel )

    object.bounds = bounds:clone()
    object.text = text
    object.content = content:clone()
    object.scroll = scroll:clone()
	object.view = Rect:new()
    object.callback = callback

	object.visible = true

	return object
end

function ScrollPanel:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
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

Label = {}
Label.__index = Label

function Label:new( bounds, text )
    local object = setmetatable( {}, Label )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

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

Button = {}
Button.__index = Button

function Button:new( bounds, text, callback )
    local object = setmetatable( {}, Button )

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

    object.clicked = false
	object.visible = true

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

LabelButton = {}
LabelButton.__index = LabelButton

function LabelButton:new( bounds, text, callback )
    local object = setmetatable( {}, LabelButton )

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

    object.clicked = false
	object.visible = true

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

Toggle = {}
Toggle.__index = Toggle

function Toggle:new( bounds, text, active, callback )
    local object = setmetatable( {}, Toggle )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true

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

ComboBox = {}
ComboBox.__index = ComboBox

function ComboBox:new( bounds, text, active, callback )
    local object = setmetatable( {}, ComboBox )

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true

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

StatusBar = {}
StatusBar.__index = StatusBar

function StatusBar:new( bounds, text )
    local object = setmetatable( {}, StatusBar )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

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

DummyRec = {}
DummyRec.__index = DummyRec

function DummyRec:new( bounds, text )
    local object = setmetatable( {}, DummyRec )

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true

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

MessageBox = {}
MessageBox.__index = MessageBox

function MessageBox:new( bounds, title, message, buttons, callback )
    local object = setmetatable( {}, MessageBox )

    object.bounds = bounds:clone()
    object.title = title
    object.message = message
    object.buttons = buttons
	object.callback = callback

	object.buttonIndex = -1
	object.visible = true

	return object
end

function MessageBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function MessageBox:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
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

TextInputBox = {}
TextInputBox.__index = TextInputBox

function TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback )
    local object = setmetatable( {}, TextInputBox )

    object.bounds = bounds:clone()
    object.title = title
    object.message = message
    object.buttons = buttons
    object.text = text
    object.textMaxSize = textMaxSize
    object.secretViewActive = secretViewActive
	object.callback = callback

	object.buttonIndex = -1
	object.visible = true

	return object
end

function TextInputBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function TextInputBox:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
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

ColorPicker = {}
ColorPicker.__index = ColorPicker

function ColorPicker:new( bounds, text, color, callback )
    local object = setmetatable( {}, ColorPicker )

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true

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

ColorPanel = {}
ColorPanel.__index = ColorPanel

function ColorPanel:new( bounds, text, color, callback )
    local object = setmetatable( {}, ColorPanel )

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true

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

ColorBarAlpha = {}
ColorBarAlpha.__index = ColorBarAlpha

function ColorBarAlpha:new( bounds, text, alpha, callback )
    local object = setmetatable( {}, ColorBarAlpha )

    object.bounds = bounds:clone()
    object.text = text
    object.alpha = alpha
	object.callback = callback

	object.visible = true

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

ColorBarHue = {}
ColorBarHue.__index = ColorBarHue

function ColorBarHue:new( bounds, text, value, callback )
    local object = setmetatable( {}, ColorBarHue )

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
	object.callback = callback

	object.visible = true

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
