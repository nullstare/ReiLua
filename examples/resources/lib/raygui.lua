-- Wrapper for raygui.

local Util = require( "utillib" )
local Rect = require( "rectangle" )
local Vec2 = require( "vector2" )
local Color = require( "color" )

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

--[[
	Container/separator controls, useful for controls organization
]]--

-- WindowBox.

local WindowBox = {}
WindowBox.__index = WindowBox

function WindowBox:new( bounds, text, callback, grabCallback, dragCallback )
	local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback
	
	object.visible = true
	object.disabled = false
	object.draggable = true

	return object
end

function WindowBox:process()
	return self._parent:drag( self )
end

function WindowBox:draw()
	local result = RL.GuiWindowBox( self.bounds, self.text )

	if result == 1 then
		-- //TODO Could add self._parent:clickedInBounds( closeButtonBounds )
		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function WindowBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- GroupBox.

local GroupBox = {}
GroupBox.__index = GroupBox

function GroupBox:new( bounds, text )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	
	object.visible = true
	object.disabled = false

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
local Line = {}
Line.__index = Line

function Line:new( bounds, text )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true
	object.disabled = false

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
local Panel = {}
Panel.__index = Panel

function Panel:new( bounds, text, grabCallback, dragCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback
	
	object.visible = true
	object.disabled = false
	object.draggable = true

	return object
end

function Panel:process()
    return self._parent:drag( self )
end

function Panel:draw()
	RL.GuiPanel( self.bounds, self.text )
end

function Panel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- GuiTabBar.

--- Tab Bar control, returns TAB to be closed or -1
local GuiTabBar = {}
GuiTabBar.__index = GuiTabBar

function GuiTabBar:new( bounds, text, active, callback, closeCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active

	object.visible = true
	object.disabled = false
	object.callback = callback
	object.closeCallback = closeCallback

	return object
end

function GuiTabBar:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function GuiTabBar:draw()
	local oldActive = self.active
	local result = -1

	result, self.active = RL.GuiTabBar( self.bounds, self.text, self.active )

	if self.active ~= oldActive then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.active = oldActive
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
	end
	if 0 <= result and self.closeCallback ~= nil and self._parent:clickedInBounds( self.bounds ) then
		self.closeCallback( self, result )
	end
end

function GuiTabBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ScrollPanel.

--- Scroll Panel control
local ScrollPanel = {}
ScrollPanel.__index = ScrollPanel

function ScrollPanel:new( bounds, text, content, scroll, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.content = content:clone()
    object.scroll = scroll:clone()
	object.view = Rect:new()
    object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.visible = true
	object.disabled = false
	object.draggable = true

	return object
end

function ScrollPanel:process()
    return self._parent:drag( self )
end

function ScrollPanel:draw()
	local oldScroll = self.scroll:clone()

	local _, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )

	self.view = Rect:new( view )
	self.scroll = Vec2:new( scroll )

	if self.scroll ~= oldScroll then
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function ScrollPanel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- --[[
-- 	Basic controls set
-- ]]--

-- Label.

--- Label control, shows text
local Label = {}
Label.__index = Label

function Label:new( bounds, text )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true
	object.disabled = false

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
local Button = {}
Button.__index = Button

function Button:new( bounds, text, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function Button:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Button:draw()
    local result = RL.GuiButton( self.bounds, self.text )

    if result == 1 and self.callback ~= nil and self._parent:clickedInBounds( self.bounds ) then
        self.callback( self )
    end
end

function Button:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- LabelButton.

--- Label button control
local LabelButton = {}
LabelButton.__index = LabelButton

function LabelButton:new( bounds, text, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function LabelButton:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function LabelButton:draw()
    local result = RL.GuiLabelButton( self.bounds, self.text )

    if result == 1 and self.callback ~= nil and self._parent:clickedInBounds( self.bounds ) then
        self.callback( self )
    end
end

function LabelButton:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Toggle.

--- Toggle Button control
local Toggle = {}
Toggle.__index = Toggle

function Toggle:new( bounds, text, active, callback )
	local object = setmetatable( {}, self )
	object._parent = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function Toggle:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Toggle:draw()
    local oldActive = self.active

	_, self.active = RL.GuiToggle( self.bounds, self.text, self.active )

    if self.active ~= oldActive then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.active = oldActive
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function Toggle:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ToggleGroup.

--- Toggle Group control
local ToggleGroup = {}
ToggleGroup.__index = ToggleGroup

function ToggleGroup:new( bounds, text, active, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true
	object.disabled = false
	object.focusBounds = {}
	object.viewBounds = bounds:clone()
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

	local _, rowItemCounts = getItemCount( self.text )

	self.focusBounds = {}
	self.viewBounds = self.bounds:clone()

	for y, rowItemCount in ipairs( rowItemCounts ) do
		for x = 1, rowItemCount do
			local pos = Vec2:new( x - 1, y - 1 )
			local focusBound = Rect:new(
				self.bounds.x + pos.x * ( self.bounds.width + RL.GuiGetStyle( RL.TOGGLE, RL.GROUP_PADDING ) ),
				self.bounds.y + pos.y * ( self.bounds.height + RL.GuiGetStyle( RL.TOGGLE, RL.GROUP_PADDING ) ),
				self.bounds.width,
				self.bounds.height
			)

			table.insert( self.focusBounds, focusBound )
			self.viewBounds = self.viewBounds:fit( focusBound )
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

	_, self.active = RL.GuiToggleGroup( self.bounds, self.text, self.active )

    if self.active ~= oldActive then
		local inBounds = false
	
		for _, bounds in ipairs( self.focusBounds ) do
			if self._parent:clickedInBounds( bounds ) then
				inBounds = true
				break
			end
		end

		if not inBounds then
			self.active = oldActive
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function ToggleGroup:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateFocusBounds()
end

-- CheckBox.

--- Check Box control
local CheckBox = {}
CheckBox.__index = CheckBox

function CheckBox:new( bounds, text, checked, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.checked = checked
    object.callback = callback

	object.visible = true
	object.disabled = false
	object.textBounds = Rect:new()
    object.focusBounds = bounds:clone()

	return object
end

function CheckBox:setText( text )
    self.text = text
end

function CheckBox:process()
	self.focusBounds = self.bounds:fit( self.textBounds )
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.focusBounds )
end

function CheckBox:draw()
    local oldChecked = self.checked
	local textBounds = nil

	_, self.checked, textBounds = RL.GuiCheckBox( self.bounds, self.text, self.checked )
	self.textBounds:set( textBounds )

    if self.checked ~= oldChecked then
		if not self._parent:clickedInBounds( self.focusBounds ) then
			self.checked = oldChecked
		end

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function CheckBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ComboBox.

--- Combo Box control
local ComboBox = {}
ComboBox.__index = ComboBox

function ComboBox:new( bounds, text, active, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function ComboBox:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ComboBox:draw()
    local oldActive = self.active

	_, self.active = RL.GuiComboBox( self.bounds, self.text, self.active )

    if self.active ~= oldActive then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.active = oldActive
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function ComboBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- DropdownBox.

--- Dropdown Box control
local DropdownBox = {}
DropdownBox.__index = DropdownBox

function DropdownBox:new( bounds, text, active, editMode, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.editMode = editMode
    object.callback = callback

	object.visible = true
	object.disabled = false
	object.editModeBounds = bounds:clone()
	object:updateEditModeBounds()

	return object
end

function DropdownBox:setText( text )
    self.text = text

	self:updateEditModeBounds()
end

function DropdownBox:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function DropdownBox:updateEditModeBounds()
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
	local result = 0

	result, self.active = RL.GuiDropdownBox( self.bounds, self.text, self.active, self.editMode )

    if result == 1 then
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
local Spinner = {}
Spinner.__index = Spinner

function Spinner:new( bounds, text, value, minValue, maxValue, editMode, callback )
	local object = setmetatable( {}, self )
	object._parent = nil
	
	object.bounds = bounds:clone()
	object.text = text
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.editMode = editMode
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.textBounds = Rect:new()
	object.viewBounds = bounds:clone()

	return object
end

function Spinner:setText( text )
    self.text = text
end

function Spinner:process()
	self.viewBounds = self.bounds:fit( self.textBounds )
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Spinner:draw()
	local result = 0
	local oldValue = self.value
	local textBounds

	result, self.value, textBounds = RL.GuiSpinner( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )
	self.textBounds:set( textBounds )

    if result == 1 then
		self._parent:editMode( self.editMode )
		self.editMode = not self.editMode
    end
	if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function Spinner:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ValueBox.

--- Value Box control
local ValueBox = {}
ValueBox.__index = ValueBox

function ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callback )
    local object = setmetatable( {}, self )
	object._parent = nil
	
	object.bounds = bounds:clone()
	object.text = text
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.editMode = editMode
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.textBounds = Rect:new()
	object.viewBounds = bounds:clone()

	return object
end

function ValueBox:setText( text )
	self.text = text
end

function ValueBox:process()
	self.viewBounds = self.bounds:fit( self.textBounds )
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ValueBox:draw()
	local result = 0
	local oldValue = self.value
	local textBounds

	result, self.value, textBounds = RL.GuiValueBox( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )
	self.textBounds:set( textBounds )

    if result == 1 then
		self._parent:editMode( self.editMode )
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
local TextBox = {}
TextBox.__index = TextBox

function TextBox:new( bounds, text, textSize, editMode, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.textSize = textSize
    object.editMode = editMode
    object.callback = callback
	-- Option for preventing text to be drawn outside bounds.
	object.scissorMode = false
	object.visible = true
	object.disabled = false

	return object
end

function TextBox:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function TextBox:draw()
	local result = 0

	if self.scissorMode then
		RL.BeginScissorMode( self.bounds )
	end

	result, self.text = RL.GuiTextBox( self.bounds, self.text, self.textSize, self.editMode )

	if self.scissorMode then
		RL.EndScissorMode()
	end
    if result == 1 then
		self._parent:editMode( self.editMode )
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

-- Slider.

--- Slider control
local Slider = {}
Slider.__index = Slider

function Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, self )
	object._parent = nil
	
	object.bounds = bounds:clone()
	object.textLeft = textLeft
	object.textRight = textRight
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rect:new()
	object.textRightBounds = Rect:new()
	object.viewBounds = bounds:clone()

	return object
end

function Slider:process()
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Slider:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiSlider( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )

    if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function Slider:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- SliderBar.

--- Slider Bar control
local SliderBar = {}
SliderBar.__index = SliderBar

function SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.textLeft = textLeft
    object.textRight = textRight
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.callback = callback

	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rect:new()
	object.textRightBounds = Rect:new()
	object.viewBounds = bounds:clone()

	return object
end

function SliderBar:process()
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SliderBar:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiSliderBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )

	if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function SliderBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ProgressBar.

--- Progress Bar control, shows current progress value
local ProgressBar = {}
ProgressBar.__index = ProgressBar

function ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.textLeft = textLeft
    object.textRight = textRight
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
    object.callback = callback

	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rect:new()
	object.textRightBounds = Rect:new()
	object.viewBounds = bounds:clone()

	return object
end

function ProgressBar:process()
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ProgressBar:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiProgressBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )
	
    if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
    end
end

function ProgressBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- StatusBar.

--- Status Bar control, shows info text
local StatusBar = {}
StatusBar.__index = StatusBar

function StatusBar:new( bounds, text )
	local object = setmetatable( {}, self )
	object._parent = nil

	object.bounds = bounds:clone()
	object.text = text

	object.visible = true
	object.disabled = false

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
local DummyRec = {}
DummyRec.__index = DummyRec

function DummyRec:new( bounds, text )
	local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text

	object.visible = true
	object.disabled = false

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
local Grid = {}
Grid.__index = Grid

function Grid:new( bounds, text, spacing, subdivs, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.spacing = spacing
    object.subdivs = subdivs
	object.callback = callback

	object.mouseCell = Vec2:new()
	object.visible = true
	object.disabled = false

	return object
end

function Grid:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Grid:draw()
	local oldCell = self.mouseCell:clone()
	local mouseCell = {}

	_, mouseCell = RL.GuiGrid( self.bounds, self.text, self.spacing, self.subdivs, self.mouseCell )
	self.mouseCell = Vec2:new( mouseCell )

	if oldCell ~= self.mouseCell and self.callback ~= nil then
		self.callback( self )
	end
end

function Grid:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- --[[
-- 	Advance controls set
-- ]]--

-- ListView.

--- List View control
local ListView = {}
ListView.__index = ListView

function ListView:new( bounds, text, scrollIndex, active, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.scrollIndex = scrollIndex
    object.active = active
	object.callback = callback

	object.visible = true
	object.disabled = false

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
	local oldScrollIndex = self.scrollIndex

	_, self.scrollIndex, self.active = RL.GuiListView( self.bounds, self.text, self.scrollIndex, self.active )

	if self.scrollIndex ~= oldScrollIndex then
		self._parent:checkScrolling()
	end
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
local ListViewEx = {}
ListViewEx.__index = ListViewEx

function ListViewEx:new( bounds, text, scrollIndex, active, focus, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.scrollIndex = scrollIndex
    object.active = active
    object.focus = focus
	object.callback = callback

	object.visible = true
	object.disabled = false

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
	local oldScrollIndex = self.scrollIndex

	_, self.scrollIndex, self.active, self.focus = RL.GuiListViewEx( self.bounds, self.text, self.scrollIndex, self.active, self.focus )

	if self.scrollIndex ~= oldScrollIndex then
		self._parent:checkScrolling()
	end
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
local MessageBox = {}
MessageBox.__index = MessageBox

function MessageBox:new( bounds, title, message, buttons, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.title = title
    object.message = message
    object.buttons = buttons
	object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.buttonIndex = -1
	object.visible = true
	object.disabled = false
	object.draggable = true

	return object
end

function MessageBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function MessageBox:process()
	return self._parent:drag( self )
end

function MessageBox:draw()
	self.buttonIndex = RL.GuiMessageBox( self.bounds, self.title, self.message, self.buttons )

	if 0 <= self.buttonIndex and self.callback ~= nil and self._parent:clickedInBounds( self.bounds ) then
		self.callback( self )
	end
end

function MessageBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- TextInputBox.

--- Text Input Box control, ask for text, supports secret
local TextInputBox = {}
TextInputBox.__index = TextInputBox

function TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

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
	object.disabled = false
	object.draggable = true

	return object
end

function TextInputBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function TextInputBox:process()
	return self._parent:drag( self )
end

function TextInputBox:draw()
	self.buttonIndex, self.text, self.secretViewActive = RL.GuiTextInputBox( self.bounds, self.title, self.message, self.buttons, self.text, self.textMaxSize, self.secretViewActive )

	if 0 <= self.buttonIndex and self.callback ~= nil and self._parent:clickedInBounds( self.bounds ) then
		self.callback( self )
	end
end

function TextInputBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorPicker.

--- Color Picker control ( multiple color controls )
local ColorPicker = {}
ColorPicker.__index = ColorPicker

function ColorPicker:new( bounds, text, color, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true
	object.disabled = false
	object.focusBounds = Rect:new()

	object:updateFocusBounds()

	return object
end

function ColorPicker:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.focusBounds )
end

function ColorPicker:updateFocusBounds()
	local boundsHue = Rect:new(
		self.bounds.x + self.bounds.width + RL.GuiGetStyle( RL.COLORPICKER, RL.HUEBAR_PADDING ),
		self.bounds.y,
		RL.GuiGetStyle( RL.COLORPICKER, RL.HUEBAR_WIDTH ),
		self.bounds.height
	)

	self.focusBounds = self.bounds:fit( boundsHue )
end

function ColorPicker:draw()
	local oldColor = self.color:clone()
	local _, color = RL.GuiColorPicker( self.bounds, self.text, self.color )

	self.color = Color:new( color )

	if self.color ~= oldColor then
		if not self._parent:clickedInBounds( self.focusBounds ) then
			self.color = oldColor
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function ColorPicker:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorPanel.

--- Color Panel control
local ColorPanel = {}
ColorPanel.__index = ColorPanel

function ColorPanel:new( bounds, text, color, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function ColorPanel:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorPanel:draw()
	local oldColor = self.color:clone()
	local _, color = RL.GuiColorPanel( self.bounds, self.text, self.color )

	self.color = Color:new( color )

	if oldColor ~= self.color then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.color = oldColor
			return
		end

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function ColorPanel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorBarAlpha.

--- Color Bar Alpha control
local ColorBarAlpha = {}
ColorBarAlpha.__index = ColorBarAlpha

function ColorBarAlpha:new( bounds, text, alpha, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.alpha = alpha
	object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function ColorBarAlpha:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorBarAlpha:draw()
	local oldAlpha = self.alpha
	_, self.alpha = RL.GuiColorBarAlpha( self.bounds, self.text, self.alpha )

	if self.alpha ~= oldAlpha then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.alpha = oldAlpha
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function ColorBarAlpha:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorBarHue.

--- Color Bar Hue control
local ColorBarHue = {}
ColorBarHue.__index = ColorBarHue

function ColorBarHue:new( bounds, text, value, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
	object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function ColorBarHue:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ColorBarHue:draw()
	local oldValue = self.value
	_, self.value = RL.GuiColorBarHue( self.bounds, self.text, self.value )

	if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function ColorBarHue:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- ColorBarHue.

--- Color Bar Hue control
local GuiScrollBar = {}
GuiScrollBar.__index = GuiScrollBar

function GuiScrollBar:new( bounds, value, minValue, maxValue, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
	object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function GuiScrollBar:process()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function GuiScrollBar:draw()
	local oldValue = self.value
	-- Note. Scrollbar style should be determined by the control that uses it.
	self.value = RL.GuiScrollBar( self.bounds, self.value, self.minValue, self.maxValue )

	if self.value ~= oldValue then
		if not self._parent:clickedInBounds( self.bounds ) then
			self.value = oldValue
			return
		end
		self._parent:checkScrolling()

		if self.callback ~= nil then
			self.callback( self )
		end
	end
end

function GuiScrollBar:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Raygui class.

local Raygui = {}
Raygui.__index = Raygui

function Raygui:new()
	local object = setmetatable( {}, self )

	object.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT = 24

	object.disabled = false
	object.locked = false
	object.elements = {}
	object.focused = 0
	object.dragging = nil
	object.grabPos = Vec2:new()
	object.scrolling = false
	object.textEdit = false
	object.defaultTexture = RL.GetTextureDefault()
	object.defaultRect = Rect:new( 0, 0, 1, 1 ) -- For texture.
	object.mouseOffset = Vec2:new()
	object.view = Rect:new() -- Active if larger than 0. Then only elements in view will be processed and drawn.

	object._lastDisabled = false -- Last element disabled state in draw.
	object._lastStyles = {}
	object._mousePressPos = Vec2:new( -1, -1 ) -- Use to check if release and check are inside bounds.

	return object
end

function Raygui:inView( element )
	-- CheckBox for example uses focusBounds and sliders viewBounds.
	return self.view.width == 0 or self.view.height == 0 or self.view:checkCollisionRec( element.viewBounds or element.focusBounds or element.bounds )
end

function Raygui:process()
	if self.disabled or self.locked then
		return
	end
	-- If dragging, don't process element masking.
	if self.dragging ~= nil then
		self:drag( self.dragging )
		return
	end
	-- Set mouse ofset if gui is for example embedded to some element.
	RL.SetMouseOffset( self.mouseOffset )

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) then
		self._mousePressPos:set( RL.GetMousePosition() )
	end
	-- Focused is 0 if not over any element.
	self.focused = 0

	for i = #self.elements, 1, -1 do
		local element = self.elements[i]

        if element.visible and element.process ~= nil and self:inView( element ) then
            if element:process() then
                self.focused = i
                return
            end
        end
    end
	RL.SetMouseOffset( { 0, 0 } )
end

function Raygui:drag( element )
	local mousePos = Vec2:new( RL.GetMousePosition() )
	local mouseOver = RL.CheckCollisionPointRec( mousePos, element.bounds )

	if not element.disabled and element.draggable and element ~= self.dragging and RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT )
	and mouseOver and mousePos.y - element.bounds.y <= self.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT then
		self.grabPos = mousePos - Vec2:new( element.bounds.x, element.bounds.y )

		if element.grabCallback ~= nil then
			element.grabCallback( element )
		end
		self.dragging = element
	end

	if element == self.dragging then
		if not RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) then
			self.dragging = nil
		end

		element:setPosition( mousePos - self.grabPos )

		if element.dragCallback ~= nil then
			element.dragCallback( element )
		end
	end

    return mouseOver
end

-- Add style before current draw that we can then return them.
function Raygui:_addLastStyle( style )
	local lastStyle = { style[1], style[2], RL.GuiGetStyle( style[1], style[2] ) }

	for i, slot in ipairs( self._lastStyles ) do
		if slot == 0 then
			self._lastStyles[i] = lastStyle
			return
		end
	end
	table.insert( self._lastStyles, lastStyle )
end

function Raygui:draw()
	if self.locked then
		RL.GuiLock()
	end
	if self.disabled then
		RL.GuiDisable()
	end
	if not self.locked and not self.disabled then
		if not self.scrolling and not self.textEdit then
			RL.GuiLock()
		elseif RL.IsMouseButtonReleased( RL.MOUSE_BUTTON_LEFT ) then
			self.scrolling = false
		end
	end

	RL.SetMouseOffset( self.mouseOffset )

    for i, element in ipairs( self.elements ) do
        if not self.locked and not self.disabled and i == self.focused then
            RL.GuiUnlock()
        end

        if element.visible and element.draw ~= nil and self:inView( element ) then
			if self._lastDisabled ~= element.disabled then
				if element.disabled then
					RL.GuiDisable()
				else
					RL.GuiEnable()
				end
				self._lastDisabled = element.disabled
			end
			if element.styles ~= nil then
				for _, style in ipairs( element.styles ) do
					self:_addLastStyle( style )
					RL.GuiSetStyle( style[1], style[2], style[3] )
				end
			end
			if element.texture ~= nil then
				RL.SetShapesTexture( element.texture, element.textureRect )
			end

			element:draw()

			if element.texture ~= nil then
				RL.SetShapesTexture( self.defaultTexture, self.defaultRect )
			end
			-- Set previous styles back.
			if 0 < #self._lastStyles then
				for j, style in ipairs( self._lastStyles ) do
					if type( style ) == "table" then
						RL.GuiSetStyle( style[1], style[2], style[3] )
					end
					self._lastStyles[j] = 0
				end
			end
        end
    end
	RL.GuiUnlock()
	RL.GuiEnable()
	RL.SetMouseOffset( { 0, 0 } )
end

function Raygui:checkScrolling()
	-- Don't set if scrolling with mouse wheel.
	if RL.GetMouseWheelMove() == 0.0 then
		self.scrolling = true
	end
end

function Raygui:clickedInBounds( bounds )
	return RL.CheckCollisionPointRec( self._mousePressPos, bounds )
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

function Raygui:remove( element )
	for i, curElement in ipairs( self.elements ) do
		if element == curElement then
			table.remove( self.elements, i )

			return
		end
	end
end

function Raygui:editMode( editMode )
	if not editMode then
		for _, element in ipairs( self.elements ) do
			if element.editMode then
				element.editMode = false
	
				if element.callback ~= nil then
					element.callback( element )
				end
			end
		end
	end
	self.textEdit = not editMode
end

-- Element creation functions.

function Raygui:addElement( object )
	object._parent = self
	table.insert( self.elements, object )
	return object
end

---@alias Rectangle table
---@alias Vector2 table
---@alias Color table

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table WindowBox
function Raygui:WindowBox( bounds, text, callback, grabCallback, dragCallback )
	return self:addElement( WindowBox:new( bounds, text, callback, grabCallback, dragCallback ) )
end

---@param bounds Rectangle
---@param text string
---@return table GroupBox
function Raygui:GroupBox( bounds, text )
	return self:addElement( GroupBox:new( bounds, text ) )
end

---@param bounds Rectangle
---@param text string
---@return table Line
function Raygui:Line( bounds, text )
	return self:addElement( Line:new( bounds, text ) )
end

---@param bounds Rectangle
---@param text string
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table Panel
function Raygui:Panel( bounds, text, grabCallback, dragCallback )
	return self:addElement( Panel:new( bounds, text, grabCallback, dragCallback ) )
end

---@param bounds Rectangle
---@param text string
---@param active boolean
---@param callback function|nil
---@param closeCallback function|nil
---@return table GuiTabBar
function Raygui:GuiTabBar( bounds, text, active, callback, closeCallback )
	return self:addElement( GuiTabBar:new( bounds, text, active, callback, closeCallback ) )
end

---@param bounds Rectangle
---@param text string
---@param content Rectangle
---@param scroll Vector2
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table ScrollPanel
function Raygui:ScrollPanel( bounds, text, content, scroll, callback, grabCallback, dragCallback )
	return self:addElement( ScrollPanel:new( bounds, text, content, scroll, callback, grabCallback, dragCallback ) )
end

---@param bounds Rectangle
---@param text string
---@return table Label
function Raygui:Label( bounds, text )
	return self:addElement( Label:new( bounds, text ) )
end

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@return table Button
function Raygui:Button( bounds, text, callback )
	return self:addElement( Button:new( bounds, text, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@return table LabelButton
function Raygui:LabelButton( bounds, text, callback )
	return self:addElement( LabelButton:new( bounds, text, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param active boolean
---@param callback function|nil
---@return table Toggle
function Raygui:Toggle( bounds, text, active, callback )
	return self:addElement( Toggle:new( bounds, text, active, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param callback function|nil
---@return table ToggleGroup
function Raygui:ToggleGroup( bounds, text, active, callback )
	return self:addElement( ToggleGroup:new( bounds, text, active, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param checked boolean
---@param callback function|nil
---@return table CheckBox
function Raygui:CheckBox( bounds, text, checked, callback )
	return self:addElement( CheckBox:new( bounds, text, checked, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param callback function|nil
---@return table ComboBox
function Raygui:ComboBox( bounds, text, active, callback )
	return self:addElement( ComboBox:new( bounds, text, active, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param editMode boolean
---@param callback function|nil
---@return table DropdownBox
function Raygui:DropdownBox( bounds, text, active, editMode, callback )
	return self:addElement( DropdownBox:new( bounds, text, active, editMode, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callback function|nil
---@return table Spinner
function Raygui:Spinner( bounds, text, value, minValue, maxValue, editMode, callback )
	return self:addElement( Spinner:new( bounds, text, value, minValue, maxValue, editMode, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callback function|nil
---@return table ValueBox
function Raygui:ValueBox( bounds, text, value, minValue, maxValue, editMode, callback )
	return self:addElement( ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param textSize integer
---@param editMode boolean
---@param callback function|nil
---@return table TextBox
function Raygui:TextBox( bounds, text, textSize, editMode, callback )
	return self:addElement( TextBox:new( bounds, text, textSize, editMode, callback ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@return table Slider
function Raygui:Slider( bounds, textLeft, textRight, value, minValue, maxValue, callback )
	return self:addElement( Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callback ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@return table SliderBar
function Raygui:SliderBar( bounds, textLeft, textRight, value, minValue, maxValue, callback )
	return self:addElement( SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@return table ProgressBar
function Raygui:ProgressBar( bounds, textLeft, textRight, value, minValue, maxValue, callback )
	return self:addElement( ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback ) )
end

---@param bounds Rectangle
---@param text string
---@return table StatusBar
function Raygui:StatusBar( bounds, text )
	return self:addElement( StatusBar:new( bounds, text ) )
end

---@param bounds Rectangle
---@param text string
---@return table DummyRec
function Raygui:DummyRec( bounds, text )
	return self:addElement( DummyRec:new( bounds, text ) )
end

---@param bounds Rectangle
---@param text string
---@param spacing number
---@param subdivs integer
---@param callback function|nil
---@return table Grid
function Raygui:Grid( bounds, text, spacing, subdivs, callback )
	return self:addElement( Grid:new( bounds, text, spacing, subdivs, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param scrollIndex integer
---@param active integer
---@param callback function|nil
---@return table ListView
function Raygui:ListView( bounds, text, scrollIndex, active, callback )
	return self:addElement( ListView:new( bounds, text, scrollIndex, active, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param scrollIndex integer
---@param active integer
---@param focus integer
---@param callback function|nil
---@return table ListViewEx
function Raygui:ListViewEx( bounds, text, scrollIndex, active, focus, callback )
	return self:addElement( ListViewEx:new( bounds, text, scrollIndex, active, focus, callback ) )
end

---@param bounds Rectangle
---@param title string
---@param message string
---@param buttons string
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table MessageBox
function Raygui:MessageBox( bounds, title, message, buttons, callback, grabCallback, dragCallback )
	return self:addElement( MessageBox:new( bounds, title, message, buttons, callback, grabCallback, dragCallback ) )
end

---@param bounds Rectangle
---@param title string
---@param message string
---@param buttons string
---@param text string
---@param textMaxSize integer
---@param secretViewActive boolean
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@return table TextInputBox
function Raygui:TextInputBox( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback )
	return self:addElement( TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback ) )
end

---@param bounds Rectangle
---@param text string
---@param color Color
---@param callback function|nil
---@return table ColorPicker
function Raygui:ColorPicker( bounds, text, color, callback )
	return self:addElement( ColorPicker:new( bounds, text, color, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param color Color
---@param callback function|nil
---@return table ColorPanel
function Raygui:ColorPanel( bounds, text, color, callback )
	return self:addElement( ColorPanel:new( bounds, text, color, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param alpha number
---@param callback function|nil
---@return table ColorBarAlpha
function Raygui:ColorBarAlpha( bounds, text, alpha, callback )
	return self:addElement( ColorBarAlpha:new( bounds, text, alpha, callback ) )
end

---@param bounds Rectangle
---@param text string
---@param value number
---@param callback function|nil
---@return table ColorBarHue
function Raygui:ColorBarHue( bounds, text, value, callback )
	return self:addElement( ColorBarHue:new( bounds, text, value, callback ) )
end

---@param bounds Rectangle
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param callback function|nil
---@return table ColorBarHue
function Raygui:GuiScrollBar( bounds, value, minValue, maxValue, callback )
	return self:addElement( GuiScrollBar:new( bounds, value, minValue, maxValue, callback ) )
end

return Raygui
