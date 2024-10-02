-- Wrapper for raygui.

local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )

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

function WindowBox:new( bounds, text, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.callbacks = callbacks -- close, grab, drag.

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function WindowBox:update()
	return self._gui:drag( self )
end

function WindowBox:draw()
	local result = RL.GuiWindowBox( self.bounds, self.text )

	if result == 1 then
		-- //TODO Could add self._gui:clickedInBounds( closeButtonBounds )
		if self.callbacks.close then
			self.callbacks.close( self )
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
	object._gui = nil

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
	object._gui = nil

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

function Panel:new( bounds, text, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.callbacks = callbacks -- grab, drag.

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Panel:update()
	return self._gui:drag( self )
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

function GuiTabBar:new( bounds, text, active, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callbacks = callbacks -- select, close, grab, drag.

	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function GuiTabBar:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function GuiTabBar:getItem( id )
	return getItems( self.text )[ id + 1 ]
end

function GuiTabBar:draw()
	local result, active = RL.GuiTabBar( self.bounds, self.text, self.active )

	if self.active ~= active then
		if self._gui:clickedInBounds( self.bounds ) then
			self.active = active

			if self.callbacks.select then
				self.callbacks.select( self )
			end
		end
	end

	if 0 <= result and self.callbacks.close and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.close( self, result )
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

function ScrollPanel:new( bounds, text, content, scroll, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.content = content:clone()
	object.scroll = scroll:clone()
	object.view = Rectangle:new( 0, 0, 0, 0 )
	object.callbacks = callbacks -- scroll, grab, drag.

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ScrollPanel:update()
	return self._gui:drag( self )
end

function ScrollPanel:draw()
	local result, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view:setT( view )
	self.scroll:setT( scroll )

	if 0 < result then
		if self.callbacks.scroll then
			self.callbacks.scroll( self )
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
	object._gui = nil

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

function Button:new( bounds, text, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.callbacks = callbacks -- pressed.

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

	if result == 1 and self.callbacks.pressed and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.pressed( self )
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

function LabelButton:new( bounds, text, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.callbacks = callbacks -- pressed.

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

	if result == 1 and self.callbacks.pressed and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.pressed( self )
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

function Toggle:new( bounds, text, active, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callbacks = callbacks -- pressed.

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
	local result, active = RL.GuiToggle( self.bounds, self.text, self.active )

	if 0 < result and self._gui:clickedInBounds( self.bounds ) then
		self.active = active

		if self.callbacks.pressed then
			self.callbacks.pressed( self )
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

function ToggleGroup:new( bounds, text, active, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callbacks = callbacks -- select.

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
			local pos = Vector2:new( x - 1, y - 1 )
			local focusBound = Rectangle:new(
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
	local result, active = RL.GuiToggleGroup( self.bounds, self.text, self.active )

	if 0 < result then
		local inBounds = false

		for _, bounds in ipairs( self.focusBounds ) do
			if self._gui:clickedInBounds( bounds ) then
				inBounds = true
				break
			end
		end
		if inBounds then
			self.active = active

			if self.callbacks.select then
				self.callbacks.select( self )
			end
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

function CheckBox:new( bounds, text, checked, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.checked = checked
	object.callbacks = callbacks -- pressed.

	object.visible = true
	object.disabled = false
	object.textBounds = Rectangle:new( 0, 0, 0, 0 )
	object.focusBounds = bounds:clone()

	object._focusBoundsOffset = Vector2:new( 0, 0 ) -- Used in set position.
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function CheckBox:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.focusBounds )
end

function CheckBox:draw()
	local result, checked, textBounds = RL.GuiCheckBox( self.bounds, self.text, self.checked )
	self.textBounds:setT( textBounds )
	self.focusBounds = self.bounds:fit( self.textBounds )
	self._focusBoundsOffset:set( self.focusBounds.x - self.bounds.x, self.focusBounds.y - self.bounds.y )

	if 0 < result then
		if self._gui:clickedInBounds( self.focusBounds ) then
			self.checked = checked

			if self.callbacks.pressed then
				self.callbacks.pressed( self )
			end
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

function ComboBox:new( bounds, text, active, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.callbacks = callbacks -- select.

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
	local result, active = RL.GuiComboBox( self.bounds, self.text, self.active )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.active = active

			if self.callbacks.select then
				self.callbacks.select( self )
			end
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

function DropdownBox:new( bounds, text, active, editMode, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.active = active
	object.editMode = editMode
	object.callbacks = callbacks -- select.

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
		self:updateEditModeBounds()

		if not self.editMode and self.callbacks.select then
			self.callbacks.select( self )
		end
		if self.callbacks.pressed then
			self.callbacks.pressed( self )
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

function Spinner:new( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.editMode = editMode
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.textBounds = Rectangle:new( 0, 0, 0, 0 )
	object.viewBounds = bounds:clone()

	object._viewBoundsOffset = Vector2:new( 0, 0 )
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
	local result, value, textBounds = RL.GuiSpinner( self.bounds, self.text, self.value, self.minValue, self.maxValue, self.editMode )
	self.textBounds:setT( textBounds )
	self.viewBounds = self.bounds:fit( self.textBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

	if result == 1 then
		self._gui:editMode( self )
		self.editMode = not self.editMode
	end
	if self.value ~= value then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.editMode = editMode
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.textBounds = Rectangle:new( 0, 0, 0, 0 )
	object.viewBounds = bounds:clone()

	object._viewBoundsOffset = Vector2:new( 0, 0 )
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
	self.textBounds:setT( textBounds )
	self.viewBounds = self.bounds:fit( self.textBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

	if result == 1 then
		self._gui:editMode( self )
		self.editMode = not self.editMode
	end
	if self.value ~= oldValue and self.callbacks.edit then
		self.callbacks.edit( self )
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

function TextBox:new( bounds, text, bufferSize, editMode, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.bufferSize = bufferSize
	object.editMode = editMode
	object.callbacks = callbacks -- edit.
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

	result, self.text = RL.GuiTextBox( self.bounds, self.text, self.bufferSize, self.editMode )

	if self.scissorMode then
		RL.EndScissorMode()
	end
	if result == 1 then
		self._gui:editMode( self )
		self.editMode = not self.editMode

		if not self.editMode and self.callbacks.edit then
			self.callbacks.edit( self )
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

function Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.textLeft = textLeft
	object.textRight = textRight
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rectangle:new( 0, 0, 0, 0 )
	object.textRightBounds = Rectangle:new( 0, 0, 0, 0 )
	object.viewBounds = bounds:clone()

	object._viewBoundsOffset = Vector2:new( 0, 0 )
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function Slider:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function Slider:draw()
	local result, value, textLeftBounds, textRightBounds = RL.GuiSlider( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:setT( textLeftBounds )
	self.textRightBounds:setT( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.textLeft = textLeft
	object.textRight = textRight
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rectangle:new( 0, 0, 0, 0 )
	object.textRightBounds = Rectangle:new( 0, 0, 0, 0 )
	object.viewBounds = bounds:clone()

	object._viewBoundsOffset = Vector2:new( 0, 0 )
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function SliderBar:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SliderBar:draw()
	local result, value, textLeftBounds, textRightBounds = RL.GuiSliderBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:setT( textLeftBounds )
	self.textRightBounds:setT( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.textLeft = textLeft
	object.textRight = textRight
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.textLeftBounds = Rectangle:new( 0, 0, 0, 0 )
	object.textRightBounds = Rectangle:new( 0, 0, 0, 0 )
	object.viewBounds = bounds:clone()

	object._viewBoundsOffset = Vector2:new( 0, 0 )
	object.styles = styles
	object.tooltip = tooltip

	return object
end

function ProgressBar:update()
	return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function ProgressBar:draw()
	local result, value, textLeftBounds, textRightBounds = RL.GuiProgressBar( self.bounds, self.textLeft, self.textRight, self.value, self.minValue, self.maxValue )
	self.textLeftBounds:setT( textLeftBounds )
	self.textRightBounds:setT( textRightBounds )
	self.viewBounds = self.bounds:fit( self.textLeftBounds ):fit( self.textRightBounds )
	self._viewBoundsOffset:set( self.viewBounds.x - self.bounds.x, self.viewBounds.y - self.bounds.y )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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
	object._gui = nil

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
	object._gui = nil

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

function Grid:new( bounds, text, spacing, subdivs, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.spacing = spacing
	object.subdivs = subdivs
	object.callbacks = callbacks -- cellChange.

	object.mouseCell = Vector2:new( 0, 0 )
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
	local result, mouseCell = RL.GuiGrid( self.bounds, self.text, self.spacing, self.subdivs, self.mouseCell )
	self.mouseCell:setT( mouseCell )

	if 0 < result and self.callbacks.cellChange then
		self.callbacks.cellChange( self )
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

function ListView:new( bounds, text, scrollIndex, active, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.scrollIndex = scrollIndex
	object.active = active
	object.callbacks = callbacks -- select.

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
	local result, oldScrollIndex = 0, self.scrollIndex

	result, self.scrollIndex, self.active = RL.GuiListView( self.bounds, self.text, self.scrollIndex, self.active )

	if 0 < result and self.callbacks.select then
		self.callbacks.select( self )
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

function ListViewEx:new( bounds, text, scrollIndex, active, focus, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.scrollIndex = scrollIndex
	object.active = active
	object.focus = focus
	object.callbacks = callbacks -- select.

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
	local result, oldScrollIndex = 0, self.scrollIndex

	result, self.scrollIndex, self.active, self.focus = RL.GuiListViewEx( self.bounds, self.text, self.scrollIndex, self.active, self.focus )

	if 0 < result and self.callbacks.select then
		self.callbacks.select( self )
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

function MessageBox:new( bounds, title, message, buttons, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.title = title
	object.message = message
	object.buttons = buttons
	object.callbacks = callbacks -- pressed, grab, drag.

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
	return self._gui:drag( self )
end

function MessageBox:draw()
	self.buttonIndex = RL.GuiMessageBox( self.bounds, self.title, self.message, self.buttons )

	if 0 <= self.buttonIndex and self.callbacks.pressed and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.pressed( self )
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

function TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.title = title
	object.message = message
	object.buttons = buttons
	object.text = text
	object.textMaxSize = textMaxSize
	object.secretViewActive = secretViewActive
	object.callbacks = callbacks -- pressed, grab, drag.

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
	return self._gui:drag( self )
end

function TextInputBox:draw()
	self.buttonIndex, self.text, self.secretViewActive = RL.GuiTextInputBox( self.bounds, self.title, self.message, self.buttons, self.text, self.textMaxSize, self.secretViewActive )

	if 0 <= self.buttonIndex and self.callbacks.pressed and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.pressed( self )
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

function ColorPicker:new( bounds, text, color, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.color = color
	object.callbacks = callbacks -- edit.

	object.visible = true
	object.disabled = false
	object.focusBounds = Rectangle:new( 0, 0, 0, 0 )
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
	local boundsHue = Rectangle:new(
		self.bounds.x + self.bounds.width + RL.GuiGetStyle( RL.COLORPICKER, RL.HUEBAR_PADDING ),
		self.bounds.y,
		RL.GuiGetStyle( RL.COLORPICKER, RL.HUEBAR_WIDTH ),
		self.bounds.height
	)
	self.focusBounds = self.bounds:fit( boundsHue )
end

function ColorPicker:draw()
	local result, color = RL.GuiColorPicker( self.bounds, self.text, self.color )

	if 0 < result then
		if self._gui:clickedInBounds( self.focusBounds ) then
			self.color = Color:newT( color )
		end

		if self.callbacks.edit then
			self.callbacks.edit( self )
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

function ColorPanel:new( bounds, text, color, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.color = color
	object.callbacks = callbacks -- edit.

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
	local result, color = RL.GuiColorPanel( self.bounds, self.text, self.color )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.color:setT( color )

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function ColorBarAlpha:new( bounds, text, alpha, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.alpha = alpha
	object.callbacks = callbacks -- edit.

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
	local result, alpha = RL.GuiColorBarAlpha( self.bounds, self.text, self.alpha )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.alpha = alpha

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function ColorBarHue:new( bounds, text, value, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.text = text
	object.value = value
	object.callbacks = callbacks -- edit.

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
	local result, value = RL.GuiColorBarHue( self.bounds, self.text, self.value )

	if 0 < result then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.edit then
				self.callbacks.edit( self )
			end
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

function GuiScrollBar:new( bounds, value, minValue, maxValue, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = bounds:clone()
	object.value = value
	object.minValue = minValue
	object.maxValue = maxValue
	object.callbacks = callbacks -- scroll.

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
	-- Note. Scrollbar style should be determined by the control that uses it.
	local value = RL.GuiScrollBar( self.bounds, self.value, self.minValue, self.maxValue )

	if self.value ~= value then
		if self._gui:clickedInBounds( self.bounds ) then
			self.value = value

			if self.callbacks.scroll then
				self.callbacks.scroll( self )
			end
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
	object.grabPos = Vector2:new( 0, 0 )
	object.textEdit = false
	object.textEditControl = nil
	object.defaultTexture = RL.GetTextureDefault()
	object.defaultRect = Rectangle:new( 0, 0, 1, 1 ) -- For texture.
	object.defaultFont = {
		font = RL.GuiGetFont(),
		size = RL.GetFontBaseSize( RL.GuiGetFont() ),
	}
	object.mouseOffset = Vector2:new( 0, 0 )
	object.mouseScale = Vector2:new( 1, 1 )
	object.view = Rectangle:new( 0, 0, 0, 0 ) -- Active if larger than 0. Then only controls in view will be updated and drawn.
	object.tooltip = {
		text = nil,
		offset = Vector2:new( 12, 24 ),
		delay = 0.5,
		timer = 0.0,
		focused = 0
	}
	object._lastProperties = {}
	object._mousePressPos = Vector2:new( -1, -1 ) -- Use to check if release and check are inside bounds.

	return object
end

function Raygui:inView( control )
	-- CheckBox for example uses focusBounds and sliders viewBounds.
	return self.view.width == 0 or self.view.height == 0 or self.view:checkCollisionRec( control.viewBounds or control.focusBounds or control.bounds )
end

function Raygui:update( delta )
	if self.disabled or self.locked then
		self.focused = 0
		return
	end
	-- If dragging, don't update control masking.
	if self.dragging ~= nil then
		self:drag( self.dragging )
		return
	end
	-- Set mouse offset if gui is for example embedded to some control.
	local mouseOffset = RL.GetMouseOffset()
	local mouseScale = RL.GetMouseScale()
	RL.SetMouseOffset( self.mouseOffset )
	RL.SetMouseScale( self.mouseScale )

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) then
		self._mousePressPos:setT( RL.GetMousePosition() )
	end
	-- Focused is 0 if not over any control.
	self.focused = 0
	self.tooltip.text = nil

	for i = #self.controls, 1, -1 do
		local control = self.controls[i]

		if control.visible and not control.noUpdate and control.update ~= nil and self:inView( control ) then
			if control:update( delta ) then
				self.focused = i

				if i ~= self.tooltip.focused then
					self.tooltip.focused = -1 -- Note that we don't want it to be 0, same as self.focus.
					self.tooltip.timer = 0.0
				end

				if control.tooltip ~= nil then
					self.tooltip.focused = i

					if self.tooltip.timer < self.tooltip.delay then
						self.tooltip.timer = self.tooltip.timer + delta
					else
						self.tooltip.text = control.tooltip
						self.tooltip.position = Vector2:newT( RL.GetMousePosition() ) + self.tooltip.offset
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

	RL.SetMouseOffset( mouseOffset )
	RL.SetMouseScale( mouseScale )
end

function Raygui:drag( control )
	local mousePos = Vector2:tempT( RL.GetMousePosition() )
	local mouseOver = RL.CheckCollisionPointRec( mousePos, control.bounds )

	if not control.disabled and control.draggable and control ~= self.dragging and RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT )
	and mouseOver and mousePos.y - control.bounds.y <= self.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT then
		self.grabPos = mousePos - Vector2:temp( control.bounds.x, control.bounds.y )

		if control.callbacks.grab then
			control.callbacks.grab( control )
		end
		self.dragging = control
	end

	if control == self.dragging then
		if not RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) then
			self.dragging = nil
		end
		control:setPosition( mousePos - self.grabPos )

		if control.callbacks.drag then
			control.callbacks.drag( control )
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
	local textSize = Vector2:tempT( RL.MeasureTextEx(
		self.defaultFont.font,
		self.tooltip.text,
		RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SIZE ),
		RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING )
	) )
	local tooltipRect = Rectangle:new(
		RL.Round( self.tooltip.position.x ),
		RL.Round( self.tooltip.position.y ),
		textSize.x,
		textSize.y
	)
	local view = self.view:clone()
	-- If no view size, clamp to window size.
	if view.width == 0 or view.height == 0 then
		local screenSize = Vector2:tempT( RL.GetScreenSize() )
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
	else
		RL.GuiEnable()
	end
	-- Drawing is done from back to front so we want to lock the ui on begin.
	if not self.textEdit then
		RL.GuiLock()
	end

	local oldTextEditText = "" -- For checking if text has changed so we can call input callback.

	if self.textEdit then
		oldTextEditText = self.textEditControl.text
	end

	-- Set mouse offset if gui is for example embedded to some control.
	local mouseOffset = RL.GetMouseOffset()
	local mouseScale = RL.GetMouseScale()
	RL.SetMouseOffset( self.mouseOffset )
	RL.SetMouseScale( self.mouseScale )

	if self.defaultFont.font ~= RL.GuiGetFont() then
		RL.GuiSetFont( self.defaultFont.font )
		RL.GuiSetStyle( RL.DEFAULT, RL.TEXT_SIZE, self.defaultFont.size )
	end

	for i, control in ipairs( self.controls ) do
		if not self.locked and not self.disabled
		and i == self.focused and not control.locked then
			RL.GuiUnlock()
		end

		if control.visible and control.draw ~= nil and self:inView( control ) then
			if control.disabled then
				RL.GuiDisable()
			elseif not self.disabled then
				RL.GuiEnable()
			end

			self:drawControl( control )
		end
	end

	if not self.locked and not self.disabled and self.tooltip.text ~= nil
	and self.controls[ self.tooltip.focused ]:update()
	and self.tooltip.delay <= self.tooltip.timer then
		self:drawTooltip()
	end

	if self.textEdit and oldTextEditText ~= self.textEditControl.text and self.textEditControl.callbacks.textEdit ~= nil then
		self.textEditControl.callbacks.textEdit( self.textEditControl )
	end

	RL.SetMouseOffset( mouseOffset )
	RL.SetMouseScale( mouseScale )
end

function Raygui:clickedInBounds( bounds )
	return RL.CheckCollisionPointRec( self._mousePressPos, bounds )
end

function Raygui:setToTop( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			Util.tableMove( self.controls, i, 1, #self.controls )

			return
		end
	end
end

function Raygui:setToBack( control )
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

function Raygui:getId( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			return i
		end
	end
end

function Raygui:setDefaultFont( font )
	self.defaultFont.font = font
	self.defaultFont.size = RL.GetFontBaseSize( font )
end

function Raygui:setProperties( properties )
	for _, property in ipairs( properties ) do
		RL.GuiSetStyle( property[1], property[2], property[3] )
	end
end

function Raygui:clear()
	for _, control in ipairs( self.controls ) do
		table.remove( control )
	end
end

function Raygui:editMode( control )
	if self.textEditControl ~= nil and not control.editMode then
		self.textEditControl.editMode = false

		if self.textEditControl.callbacks.edit ~= nil then
			self.textEditControl.callbacks.edit( self.textEditControl )
		end
	end
	self.textEdit = not control.editMode

	if self.textEdit then
		self.textEditControl = control
	else
		self.textEditControl = nil
	end
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
				RL.GuiSetFont( self.defaultFont.font )
			end
		end
	end
end

-- Control add functions.

function Raygui:addControl( control )
	control._gui = self
	self:drawControl( control )
	table.insert( self.controls, control )
	return control
end

---@alias Rectangle table
---@alias Vector2 table
---@alias Color table

---@param bounds Rectangle
---@param title string|nil
---@param callbacks table close, grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table WindowBox
function Raygui:WindowBox( bounds, title, callbacks, styles, tooltip )
	return self:addControl( WindowBox:new( bounds, title, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param styles table|nil
---@param tooltip string|nil
---@return table GroupBox
function Raygui:GroupBox( bounds, text, styles, tooltip )
	return self:addControl( GroupBox:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param styles table|nil
---@param tooltip string|nil
---@return table Line
function Raygui:Line( bounds, text, styles, tooltip )
	return self:addControl( Line:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param callbacks table grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table Panel
function Raygui:Panel( bounds, text, callbacks, styles, tooltip )
	return self:addControl( Panel:new( bounds, text, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param active integer
---@param callbacks table select, close, grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table GuiTabBar
function Raygui:GuiTabBar( bounds, text, active, callbacks, styles, tooltip )
	return self:addControl( GuiTabBar:new( bounds, text, active, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param content Rectangle
---@param scroll Vector2
---@param callbacks table scroll, grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table ScrollPanel
function Raygui:ScrollPanel( bounds, text, content, scroll, callbacks, styles, tooltip )
	return self:addControl( ScrollPanel:new( bounds, text, content, scroll, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param styles table|nil
---@param tooltip string|nil
---@return table Label
function Raygui:Label( bounds, text, styles, tooltip )
	return self:addControl( Label:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param callbacks table pressed.
---@param styles table|nil
---@param tooltip string|nil
---@return table Button
function Raygui:Button( bounds, text, callbacks, styles, tooltip )
	return self:addControl( Button:new( bounds, text, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param callbacks table pressed.
---@param styles table|nil
---@param tooltip string|nil
---@return table LabelButton
function Raygui:LabelButton( bounds, text, callbacks, styles, tooltip )
	return self:addControl( LabelButton:new( bounds, text, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param active boolean
---@param callbacks table pressed.
---@param styles table|nil
---@param tooltip string|nil
---@return table Toggle
function Raygui:Toggle( bounds, text, active, callbacks, styles, tooltip )
	return self:addControl( Toggle:new( bounds, text, active, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param active integer
---@param callbacks table select.
---@param styles table|nil
---@param tooltip string|nil
---@return table ToggleGroup
function Raygui:ToggleGroup( bounds, text, active, callbacks, styles, tooltip )
	return self:addControl( ToggleGroup:new( bounds, text, active, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param checked boolean
---@param callbacks table pressed.
---@param styles table|nil
---@param tooltip string|nil
---@return table CheckBox
function Raygui:CheckBox( bounds, text, checked, callbacks, styles, tooltip )
	return self:addControl( CheckBox:new( bounds, text, checked, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param active integer
---@param callbacks table select.
---@param styles table|nil
---@param tooltip string|nil
---@return table ComboBox
function Raygui:ComboBox( bounds, text, active, callbacks, styles, tooltip )
	return self:addControl( ComboBox:new( bounds, text, active, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param active integer
---@param editMode boolean
---@param callbacks table select.
---@param styles table|nil
---@param tooltip string|nil
---@return table DropdownBox
function Raygui:DropdownBox( bounds, text, active, editMode, callbacks, styles, tooltip )
	return self:addControl( DropdownBox:new( bounds, text, active, editMode, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table Spinner
function Raygui:Spinner( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip )
	return self:addControl( Spinner:new( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ValueBox
function Raygui:ValueBox( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip )
	return self:addControl( ValueBox:new( bounds, text, value, minValue, maxValue, editMode, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param bufferSize integer
---@param editMode boolean
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table TextBox
function Raygui:TextBox( bounds, text, bufferSize, editMode, callbacks, styles, tooltip )
	return self:addControl( TextBox:new( bounds, text, bufferSize, editMode, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table Slider
function Raygui:Slider( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	return self:addControl( Slider:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table SliderBar
function Raygui:SliderBar( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	return self:addControl( SliderBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ProgressBar
function Raygui:ProgressBar( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip )
	return self:addControl( ProgressBar:new( bounds, textLeft, textRight, value, minValue, maxValue, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param styles table|nil
---@param tooltip string|nil
---@return table StatusBar
function Raygui:StatusBar( bounds, text, styles, tooltip )
	return self:addControl( StatusBar:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param styles table|nil
---@param tooltip string|nil
---@return table DummyRec
function Raygui:DummyRec( bounds, text, styles, tooltip )
	return self:addControl( DummyRec:new( bounds, text, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param spacing number
---@param subdivs integer
---@param callbacks table cellChange.
---@param styles table|nil
---@param tooltip string|nil
---@return table Grid
function Raygui:Grid( bounds, text, spacing, subdivs, callbacks, styles, tooltip )
	return self:addControl( Grid:new( bounds, text, spacing, subdivs, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param scrollIndex integer
---@param active integer
---@param callbacks table select.
---@param styles table|nil
---@param tooltip string|nil
---@return table ListView
function Raygui:ListView( bounds, text, scrollIndex, active, callbacks, styles, tooltip )
	return self:addControl( ListView:new( bounds, text, scrollIndex, active, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string
---@param scrollIndex integer
---@param active integer
---@param focus integer
---@param callbacks table select.
---@param styles table|nil
---@param tooltip string|nil
---@return table ListViewEx
function Raygui:ListViewEx( bounds, text, scrollIndex, active, focus, callbacks, styles, tooltip )
	return self:addControl( ListViewEx:new( bounds, text, scrollIndex, active, focus, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param title string
---@param message string
---@param buttons string
---@param callbacks table pressed, grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table MessageBox
function Raygui:MessageBox( bounds, title, message, buttons, callbacks, styles, tooltip )
	return self:addControl( MessageBox:new( bounds, title, message, buttons, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param title string
---@param message string
---@param buttons string
---@param text string
---@param textMaxSize integer
---@param secretViewActive boolean
---@param callbacks table pressed, grab, drag.
---@param styles table|nil
---@param tooltip string|nil
---@return table TextInputBox
function Raygui:TextInputBox( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callbacks, styles, tooltip )
	return self:addControl( TextInputBox:new( bounds, title, message, buttons, text, textMaxSize, secretViewActive, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param color Color
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ColorPicker
function Raygui:ColorPicker( bounds, text, color, callbacks, styles, tooltip )
	return self:addControl( ColorPicker:new( bounds, text, color, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param color Color
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ColorPanel
function Raygui:ColorPanel( bounds, text, color, callbacks, styles, tooltip )
	return self:addControl( ColorPanel:new( bounds, text, color, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param alpha number
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ColorBarAlpha
function Raygui:ColorBarAlpha( bounds, text, alpha, callbacks, styles, tooltip )
	return self:addControl( ColorBarAlpha:new( bounds, text, alpha, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param text string|nil
---@param value number
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ColorBarHue
function Raygui:ColorBarHue( bounds, text, value, callbacks, styles, tooltip )
	return self:addControl( ColorBarHue:new( bounds, text, value, callbacks, styles, tooltip ) )
end

---@param bounds Rectangle
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param callbacks table edit.
---@param styles table|nil
---@param tooltip string|nil
---@return table ColorBarHue
function Raygui:GuiScrollBar( bounds, value, minValue, maxValue, callbacks, styles, tooltip )
	return self:addControl( GuiScrollBar:new( bounds, value, minValue, maxValue, callbacks, styles, tooltip ) )
end

return Raygui
