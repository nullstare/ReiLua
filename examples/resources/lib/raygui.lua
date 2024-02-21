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

function WindowBox:new( bounds, text, callback, grabCallback, dragCallback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function WindowBox:update()
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

function GroupBox:new( bounds, text, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	object.styles = styles
	object.tooltip = tooltip
	
	object.visible = true
	object.disabled = false

	return object
end

function GroupBox:update()
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

function Line:new( bounds, text, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Line:update()
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

function Panel:new( bounds, text, grabCallback, dragCallback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback
	
	object.visible = true
	object.disabled = false
	object.draggable = true
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Panel:update()
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

function GuiTabBar:new( bounds, text, active, callback, closeCallback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
	object.callback = callback
	object.closeCallback = closeCallback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function GuiTabBar:update()
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

function ScrollPanel:new( bounds, text, content, scroll, callback, grabCallback, dragCallback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ScrollPanel:update()
    return self._parent:drag( self )
end

function ScrollPanel:draw()
	local oldScroll = self.scroll:clone()
	local _, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view:set( view )
	self.scroll:set( scroll )

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

local Label = {}
Label.__index = Label

function Label:new( bounds, text, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Label:update()
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

function Button:new( bounds, text, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Button:update()
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

function LabelButton:new( bounds, text, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function LabelButton:update()
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

function Toggle:new( bounds, text, active, callback, styles, tooltip )
	local object = setmetatable( {}, self )
	object._parent = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Toggle:update()
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

function ToggleGroup:new( bounds, text, active, callback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip
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

function ToggleGroup:update()
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

function CheckBox:new( bounds, text, checked, callback, styles, tooltip )
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
	
	object._focusBoundsOffset = Vec2:new() -- Used in set position.
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function CheckBox:update()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.focusBounds )
end

function CheckBox:draw()
    local oldChecked = self.checked
	local textBounds = nil

	_, self.checked, textBounds = RL.GuiCheckBox( self.bounds, self.text, self.checked )
	self.textBounds:set( textBounds )
	self.focusBounds = self.bounds:fit( self.textBounds )
	self._focusBoundsOffset:set( self.focusBounds.x - self.bounds.x, self.focusBounds.y - self.bounds.y )

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
	self.focusBounds.x = self.bounds.x + self._focusBoundsOffset.x
	self.focusBounds.y = self.bounds.y + self._focusBoundsOffset.y
end

-- ComboBox.

--- Combo Box control
local ComboBox = {}
ComboBox.__index = ComboBox

function ComboBox:new( bounds, text, active, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.active = active
    object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ComboBox:update()
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

function DropdownBox:new( bounds, text, active, editMode, callback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
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

function DropdownBox:update()
	if self.editMode then
		self:updateEditModeBounds()
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

function Spinner:new( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip )
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
	
	object._viewBoundsOffset = Vec2:new()
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Spinner:setText( text )
    self.text = text
end

function Spinner:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Spinner:draw()
	local result = 0
	local oldValue = self.value
	local textBounds

	result, self.value, textBounds = RL.GuiSpinner( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )
	self.textBounds:set( textBounds )
	self.viewBounds = self.bounds:fit( self.textBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

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
	self.viewBounds.x = self.bounds.x + self._viewBoundsOffset.x
	self.viewBounds.y = self.bounds.y + self._viewBoundsOffset.y
end

-- ValueBox.

--- Value Box control
local ValueBox = {}
ValueBox.__index = ValueBox

function ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip )
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
	
	object._viewBoundsOffset = Vec2:new()
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ValueBox:setText( text )
	self.text = text
end

function ValueBox:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ValueBox:draw()
	local result = 0
	local oldValue = self.value
	local textBounds

	result, self.value, textBounds = RL.GuiValueBox( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )
	self.textBounds:set( textBounds )
	self.viewBounds = self.bounds:fit( self.textBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

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
	self.viewBounds.x = self.bounds.x + self._viewBoundsOffset.x
	self.viewBounds.y = self.bounds.y + self._viewBoundsOffset.y
end

-- TextBox.

--- Text Box control
local TextBox = {}
TextBox.__index = TextBox

function TextBox:new( bounds, text, textSize, editMode, callback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function TextBox:update()
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

function Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
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
	
	object._viewBoundsOffset = Vec2:new()
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Slider:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Slider:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiSlider( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

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
	self.viewBounds.x = self.bounds.x + self._viewBoundsOffset.x
	self.viewBounds.y = self.bounds.y + self._viewBoundsOffset.y
end

-- SliderBar.

--- Slider Bar control
local SliderBar = {}
SliderBar.__index = SliderBar

function SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
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
	
	object._viewBoundsOffset = Vec2:new()
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function SliderBar:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SliderBar:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiSliderBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

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
	self.viewBounds.x = self.bounds.x + self._viewBoundsOffset.x
	self.viewBounds.y = self.bounds.y + self._viewBoundsOffset.y
end

-- ProgressBar.

--- Progress Bar control, shows current progress value
local ProgressBar = {}
ProgressBar.__index = ProgressBar

function ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
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
	
	object._viewBoundsOffset = Vec2:new()
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ProgressBar:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ProgressBar:draw()
	local oldValue, textLeftBounds, textRightBounds = self.value, nil, nil

	_, self.value, textLeftBounds, textRightBounds = RL.GuiProgressBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:set( textLeftBounds )
	self.textRightBounds:set( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )
	
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
	self.viewBounds.x = self.bounds.x + self._viewBoundsOffset.x
	self.viewBounds.y = self.bounds.y + self._viewBoundsOffset.y
end

-- StatusBar.

--- Status Bar control, shows info text
local StatusBar = {}
StatusBar.__index = StatusBar

function StatusBar:new( bounds, text, styles, tooltip )
	local object = setmetatable( {}, self )
	object._parent = nil

	object.bounds = bounds:clone()
	object.text = text
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function StatusBar:update()
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

function DummyRec:new( bounds, text, styles, tooltip )
	local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function DummyRec:update()
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

function Grid:new( bounds, text, spacing, subdivs, callback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Grid:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Grid:draw()
	local oldCell = self.mouseCell:clone()
	local mouseCell = {}

	_, mouseCell = RL.GuiGrid( self.bounds, self.text, self.spacing, self.subdivs, self.mouseCell )
	self.mouseCell:set( mouseCell )

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

function ListView:new( bounds, text, scrollIndex, active, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.scrollIndex = scrollIndex
    object.active = active
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ListView:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function ListView:update()
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

function ListViewEx:new( bounds, text, scrollIndex, active, focus, callback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ListViewEx:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function ListViewEx:update()
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

function MessageBox:new( bounds, title, message, buttons, callback, grabCallback, dragCallback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function MessageBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function MessageBox:update()
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

function TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback, styles, tooltip )
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
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function TextInputBox:getItem( id )
	return getItems( self.buttons )[ id ]
end

function TextInputBox:update()
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

function ColorPicker:new( bounds, text, color, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.focusBounds = Rect:new()
	object.styles = styles
	object.tooltip = tooltip
	
	object:updateFocusBounds()

	return object
end

function ColorPicker:update()
	-- self:updateFocusBounds()
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
	self:updateFocusBounds()
end

-- ColorPanel.

--- Color Panel control
local ColorPanel = {}
ColorPanel.__index = ColorPanel

function ColorPanel:new( bounds, text, color, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.color = color
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ColorPanel:update()
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

function ColorBarAlpha:new( bounds, text, alpha, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.alpha = alpha
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ColorBarAlpha:update()
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

function ColorBarHue:new( bounds, text, value, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.value = value
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ColorBarHue:update()
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

function GuiScrollBar:new( bounds, value, minValue, maxValue, callback, styles, tooltip )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.value = value
    object.minValue = minValue
    object.maxValue = maxValue
	object.callback = callback
	
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function GuiScrollBar:update()
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
	object.controls = {}
	object.focused = 0
	object.dragging = nil
	object.grabPos = Vec2:new()
	object.scrolling = false
	object.textEdit = false
	object.defaultTexture = RL.GetTextureDefault()
	object.defaultRect = Rect:new( 0, 0, 1, 1 ) -- For texture.
	object.defaultFont = RL.GetFontDefault()
	object.mouseOffset = Vec2:new()
	object.view = Rect:new() -- Active if larger than 0. Then only controls in view will be updated and drawn.
	object.tooltip = {
		text = nil,
		offset = Vec2:new( 12, 24 ),
		delay = 0.5,
		timer = 0.0,
		focused = 0
	}

	object._lastProperties = {}
	object._mousePressPos = Vec2:new( -1, -1 ) -- Use to check if release and check are inside bounds.

	return object
end

function Raygui:inView( control )
	-- CheckBox for example uses focusBounds and sliders viewBounds.
	return self.view.width == 0 or self.view.height == 0 or self.view:checkCollisionRec( control.viewBounds or control.focusBounds or control.bounds )
end

function Raygui:update()
	if self.disabled or self.locked then
		return
	end
	-- If dragging, don't update control masking.
	if self.dragging ~= nil then
		self:drag( self.dragging )
		return
	end
	-- Set mouse ofset if gui is for example embedded to some control.
	RL.SetMouseOffset( self.mouseOffset )

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) then
		self._mousePressPos:set( RL.GetMousePosition() )
	end
	-- Focused is 0 if not over any control.
	self.focused = 0
	self.tooltip.text = nil

	for i = #self.controls, 1, -1 do
		local control = self.controls[i]

		if control.visible and control.update ~= nil and self:inView( control ) then
			if control:update() then
				self.focused = i
				
				if i ~= self.tooltip.focused then
					self.tooltip.focused = -1 -- Note that we don't want it to be 0, same as self.focus.
					self.tooltip.timer = 0.0
				end
				
				if control.tooltip ~= nil then
					self.tooltip.focused = i

					if self.tooltip.timer < self.tooltip.delay then
						self.tooltip.timer = self.tooltip.timer + RL.GetFrameTime()
					else
						self.tooltip.text = control.tooltip
						self.tooltip.position = Vec2:new( RL.GetMousePosition() ) + self.tooltip.offset
					end
				end

				break
			end
		end
	end

	if self.focused == 0 then
		self.tooltip.focused = -1 -- Note that we don't want it to be 0, same as self.focus.
		self.tooltip.timer = 0.0
	end

	RL.SetMouseOffset( { 0, 0 } )
end

function Raygui:drag( control )
	local mousePos = Vec2:new( RL.GetMousePosition() )
	local mouseOver = RL.CheckCollisionPointRec( mousePos, control.bounds )

	if not control.disabled and control.draggable and control ~= self.dragging and RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT )
	and mouseOver and mousePos.y - control.bounds.y <= self.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT then
		self.grabPos = mousePos - Vec2:new( control.bounds.x, control.bounds.y )

		if control.grabCallback ~= nil then
			control.grabCallback( control )
		end
		self.dragging = control
	end

	if control == self.dragging then
		if not RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) then
			self.dragging = nil
		end
		control:setPosition( mousePos - self.grabPos )

		if control.dragCallback ~= nil then
			control.dragCallback( control )
		end
	end

    return mouseOver
end

-- Add property before current draw that we can then return them.
function Raygui:_addLastProperty( property )
	local lastProperty = { property[1], property[2], RL.GuiGetStyle( property[1], property[2] ) }

	for i, slot in ipairs( self._lastProperties ) do
		if slot == 0 then
			self._lastProperties[i] = lastProperty
			return
		end
	end
	table.insert( self._lastProperties, lastProperty )
end

function Raygui:drawTooltip()
	local textSize = Vec2:new( RL.MeasureText(
		self.defaultFont,
		self.tooltip.text,
		RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SIZE ),
		RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING )
	) )
	local tooltipRect = Rect:new( self.tooltip.position.x, self.tooltip.position.y, textSize.x, textSize.y )
	local view = self.view:clone()
	-- If no view size, clamp to window size.
	if view.width == 0 or view.height == 0 then
		local screenSize = Vec2:new( RL.GetScreenSize() )
		view.width = screenSize.x
		view.height = screenSize.y
	end

	RL.GuiDummyRec( tooltipRect:clampInside( view ), self.tooltip.text )
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
	-- Set mouse offset if gui is for example embedded to some control.
	RL.SetMouseOffset( self.mouseOffset )

	for i, control in ipairs( self.controls ) do
		if not self.locked and not self.disabled and i == self.focused then
			RL.GuiUnlock()
		end

		if control.visible and control.draw ~= nil and self:inView( control ) then
			if control.disabled then
				RL.GuiDisable()
			else
				RL.GuiEnable()
			end

			self:drawControl( control )
		end
	end

	if self.tooltip.text ~= nil and self.controls[ self.tooltip.focused ]:update()
	and self.tooltip.delay <= self.tooltip.timer then
		self:drawTooltip()
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

function Raygui:set2Top( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			Util.tableMove( self.controls, i, 1, #self.controls )

			return
		end
	end
end

function Raygui:set2Back( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			Util.tableMove( self.controls, i, 1, 1 )

			return
		end
	end
end

function Raygui:remove( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			table.remove( self.controls, i )

			return
		end
	end
end

function Raygui:editMode( editMode )
	if not editMode then
		for _, control in ipairs( self.controls ) do
			if control.editMode then
				control.editMode = false
	
				if control.callback ~= nil then
					control.callback( control )
				end
			end
		end
	end
	self.textEdit = not editMode
end

function Raygui:drawControl( control )
	if control == nil or control.draw == nil then
		return
	end

	if control.styles ~= nil then
		for name, style in pairs( control.styles ) do
			if name == "properties" then
				for _, property in ipairs( style ) do
					self:_addLastProperty( property )
					RL.GuiSetStyle( property[1], property[2], property[3] )
				end
			elseif name == "texture" then
				RL.SetShapesTexture( style.texture, style.rect )
			elseif name == "font" then
				RL.GuiSetFont( style )
			end
		end
	end

	control:draw()

	if control.styles ~= nil then
		for name, _ in pairs( control.styles ) do
			if name == "properties" then
				for j, property in ipairs( self._lastProperties ) do
					if type( property ) == "table" then
						RL.GuiSetStyle( property[1], property[2], property[3] )
						self._lastProperties[j] = 0
					end
				end
			elseif name == "texture" then
				RL.SetShapesTexture( self.defaultTexture, self.defaultRect )
			elseif name == "font" then
				RL.GuiSetFont( self.defaultFont )
			end
		end
	end
end

-- Control add functions.

function Raygui:addControl( control )
	control._parent = self
	-- self:applyStyles( control )
	self:drawControl( control )
	table.insert( self.controls, control )
	return control
end

---@alias Rectangle table
---@alias Vector2 table
---@alias Color table

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@param styles table|nil
---@return table WindowBox
function Raygui:WindowBox( bounds, text, callback, grabCallback, dragCallback, styles, tooltip )
	return self:addControl( WindowBox:new( bounds, text, callback, grabCallback, dragCallback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param styles table|nil
---@return table GroupBox
function Raygui:GroupBox( bounds, text, styles, tooltip )
	return self:addControl( GroupBox:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param styles table|nil
---@return table Line
function Raygui:Line( bounds, text, styles, tooltip )
	return self:addControl( Line:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param grabCallback function|nil
---@param dragCallback function|nil
---@param styles table|nil
---@return table Panel
function Raygui:Panel( bounds, text, grabCallback, dragCallback, styles, tooltip )
	return self:addControl( Panel:new( bounds, text, grabCallback, dragCallback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active boolean
---@param callback function|nil
---@param closeCallback function|nil
---@param styles table|nil
---@return table GuiTabBar
function Raygui:GuiTabBar( bounds, text, active, callback, closeCallback, styles, tooltip )
	return self:addControl( GuiTabBar:new( bounds, text, active, callback, closeCallback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param content Rectangle
---@param scroll Vector2
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@param styles table|nil
---@return table ScrollPanel
function Raygui:ScrollPanel( bounds, text, content, scroll, callback, grabCallback, dragCallback, styles, tooltip )
	return self:addControl( ScrollPanel:new( bounds, text, content, scroll, callback, grabCallback, dragCallback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param styles table|nil
---@return table Label
function Raygui:Label( bounds, text, styles, tooltip )
	return self:addControl( Label:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@param styles table|nil
---@return table Button
function Raygui:Button( bounds, text, callback, styles, tooltip )
	return self:addControl( Button:new( bounds, text, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param callback function|nil
---@param styles table|nil
---@return table LabelButton
function Raygui:LabelButton( bounds, text, callback, styles, tooltip )
	return self:addControl( LabelButton:new( bounds, text, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active boolean
---@param callback function|nil
---@param styles table|nil
---@return table Toggle
function Raygui:Toggle( bounds, text, active, callback, styles, tooltip )
	return self:addControl( Toggle:new( bounds, text, active, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param callback function|nil
---@param styles table|nil
---@return table ToggleGroup
function Raygui:ToggleGroup( bounds, text, active, callback, styles, tooltip )
	return self:addControl( ToggleGroup:new( bounds, text, active, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param checked boolean
---@param callback function|nil
---@param styles table|nil
---@return table CheckBox
function Raygui:CheckBox( bounds, text, checked, callback, styles, tooltip )
	return self:addControl( CheckBox:new( bounds, text, checked, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param callback function|nil
---@param styles table|nil
---@return table ComboBox
function Raygui:ComboBox( bounds, text, active, callback, styles, tooltip )
	return self:addControl( ComboBox:new( bounds, text, active, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param editMode boolean
---@param callback function|nil
---@param styles table|nil
---@return table DropdownBox
function Raygui:DropdownBox( bounds, text, active, editMode, callback, styles, tooltip )
	return self:addControl( DropdownBox:new( bounds, text, active, editMode, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callback function|nil
---@param styles table|nil
---@return table Spinner
function Raygui:Spinner( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip )
	return self:addControl( Spinner:new( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callback function|nil
---@param styles table|nil
---@return table ValueBox
function Raygui:ValueBox( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip )
	return self:addControl( ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param textSize integer
---@param editMode boolean
---@param callback function|nil
---@param styles table|nil
---@return table TextBox
function Raygui:TextBox( bounds, text, textSize, editMode, callback, styles, tooltip )
	return self:addControl( TextBox:new( bounds, text, textSize, editMode, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@param styles table|nil
---@return table Slider
function Raygui:Slider( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
	return self:addControl( Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@param styles table|nil
---@return table SliderBar
function Raygui:SliderBar( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
	return self:addControl( SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callback function|nil
---@param styles table|nil
---@return table ProgressBar
function Raygui:ProgressBar( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip )
	return self:addControl( ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param styles table|nil
---@return table StatusBar
function Raygui:StatusBar( bounds, text, styles, tooltip )
	return self:addControl( StatusBar:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param styles table|nil
---@return table DummyRec
function Raygui:DummyRec( bounds, text, styles, tooltip )
	return self:addControl( DummyRec:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param spacing number
---@param subdivs integer
---@param callback function|nil
---@param styles table|nil
---@return table Grid
function Raygui:Grid( bounds, text, spacing, subdivs, callback, styles, tooltip )
	return self:addControl( Grid:new( bounds, text, spacing, subdivs, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param scrollIndex integer
---@param active integer
---@param callback function|nil
---@param styles table|nil
---@return table ListView
function Raygui:ListView( bounds, text, scrollIndex, active, callback, styles, tooltip )
	return self:addControl( ListView:new( bounds, text, scrollIndex, active, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param scrollIndex integer
---@param active integer
---@param focus integer
---@param callback function|nil
---@param styles table|nil
---@return table ListViewEx
function Raygui:ListViewEx( bounds, text, scrollIndex, active, focus, callback, styles, tooltip )
	return self:addControl( ListViewEx:new( bounds, text, scrollIndex, active, focus, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param title string
---@param message string
---@param buttons string
---@param callback function|nil
---@param grabCallback function|nil
---@param dragCallback function|nil
---@param styles table|nil
---@return table MessageBox
function Raygui:MessageBox( bounds, title, message, buttons, callback, grabCallback, dragCallback, styles, tooltip )
	return self:addControl( MessageBox:new( bounds, title, message, buttons, callback, grabCallback, dragCallback, styles, tooltip ) )
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
---@param styles table|nil
---@return table TextInputBox
function Raygui:TextInputBox( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback, styles, tooltip )
	return self:addControl( TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callback, grabCallback, dragCallback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param color Color
---@param callback function|nil
---@param styles table|nil
---@return table ColorPicker
function Raygui:ColorPicker( bounds, text, color, callback, styles, tooltip )
	return self:addControl( ColorPicker:new( bounds, text, color, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param color Color
---@param callback function|nil
---@param styles table|nil
---@return table ColorPanel
function Raygui:ColorPanel( bounds, text, color, callback, styles, tooltip )
	return self:addControl( ColorPanel:new( bounds, text, color, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param alpha number
---@param callback function|nil
---@param styles table|nil
---@return table ColorBarAlpha
function Raygui:ColorBarAlpha( bounds, text, alpha, callback, styles, tooltip )
	return self:addControl( ColorBarAlpha:new( bounds, text, alpha, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param value number
---@param callback function|nil
---@param styles table|nil
---@return table ColorBarHue
function Raygui:ColorBarHue( bounds, text, value, callback, styles, tooltip )
	return self:addControl( ColorBarHue:new( bounds, text, value, callback, styles, tooltip ) )
end

---@param bounds Rectangle
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param callback function|nil
---@param styles table|nil
---@return table ColorBarHue
function Raygui:GuiScrollBar( bounds, value, minValue, maxValue, callback, styles, tooltip )
	return self:addControl( GuiScrollBar:new( bounds, value, minValue, maxValue, callback, styles, tooltip ) )
end

return Raygui
