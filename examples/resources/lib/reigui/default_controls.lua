local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )

-- Label control.

local Label = {}
Label.__index = Label

Label.DEFAULT_STYLES = {
	normal = GUI_DEFAULT_STYLES.normal,
	disabled = GUI_DEFAULT_STYLES.disabled,
}

function Label:new( t )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.text = t.text

	object.visible = t.visible or true
	object.disabled = t.disabled or false
	object.styles = t.styles or object.DEFAULT_STYLES
	object.tooltip = t.tooltip
	
	-- object._isMouseOver = false

	return object
end

-- function Label:update( delta )
-- end

function Label:draw()
	local style = self.disabled and "disabled" or "normal"
	local styles = self.styles[ style ]
	
	Gui:drawText( self.text, self.bounds, styles )

	if styles.icons then
		self._gui:drawIcons( self.bounds, styles )
	end
end

function Label:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Button control.

local Button = {}
Button.__index = Button

Button.DEFAULT_STYLES = GUI_DEFAULT_STYLES

function Button:new( t )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.text = t.text
	object.callbacks = t.callbacks or {} -- pressed.

	object.visible = t.visible or true
	object.locked = t.locked or false
	object.disabled = t.disabled or false -- Same as locked but also uses style.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.tooltip = t.tooltip
	
	object._isMouseOver = false

	return object
end

function Button:update( delta )
	if self.locked or self.disabled then
		return
	end

	if self.callbacks.pressed and self._gui._isMouseReleased and self._gui.mouseOver == self and self._gui.controlPressed == self then
		self.callbacks.pressed( self )
	end
end

function Button:draw()
	local pressed = not self.locked and not self.disabled and self._gui._isMouseDown and self._gui.mouseOver == self and self._gui.controlPressed == self
	local style = pressed and "pressed" or self.disabled and "disabled" or self._isMouseOver and "focused" or "normal"
	local styles = self.styles[ style ]

	if styles.textures then
		self._gui:drawTexturedRectangle( self.bounds, styles )
	else
		self._gui:drawRectangle( self.bounds, styles )
	end

	if self.text then
		self._gui:drawText( self.text, self.bounds, styles )
	end

	if styles.icons then
		self._gui:drawIcons( self.bounds, styles )
	end
end

function Button:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- TextInputBox control. Single line text box.

local TextInputBox = {}
TextInputBox.__index = TextInputBox

TextInputBox.DEFAULT_STYLES = GUI_DEFAULT_STYLES

function TextInputBox:new( t )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.text = t.text
	object.charLimit = t.charLimit or 64
	object.callbacks = t.callbacks or {} -- pressed, edit, set.

	object.visible = t.visible or true
	object.locked = t.locked or false
	object.disabled = t.disabled or false -- Same as locked but also uses style.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.tooltip = t.tooltip
	
	object.view = object.bounds:clone()

	object._isMouseOver = false
	object._editMode = false
	object._cursor = {
		pos = 1,
		rect = Rectangle:new( 0, 0, 2, object.bounds.height ),
		scrollPos = 0,
	}
	object._eraceTimer = {
		timer = 0,
		threshold = 0.5,
		intervall = 0.05,
	}

	return object
end

function TextInputBox:getStyles()
	local pressed = not self.locked and not self.disabled
	and ( self._gui._isMouseDown and self._gui.mouseOver == self and self._gui.controlPressed == self )
	or self._editMode
	local style = pressed and "pressed" or self.disabled and "disabled" or self._isMouseOver and "focused" or "normal"
	return self.styles[ style ]
end

function TextInputBox:updateText( cpt )
	if 0 < #cpt then
		self.text = RL.LoadUTF8( cpt )
	else
		self.text = ""
	end

	self:updateView()

	local len = #cpt

	for _ = 1, len - self._cursor.pos + 1 do
		table.remove( cpt )
	end

	-- table.move(  )

	-- print( "self._cursor.pos", self._cursor.pos )

	if 0 < #cpt then
		local styles = self:getStyles()
		-- local borderW = styles.border.width
		local ts = styles.text
		local cursorText = RL.LoadUTF8( cpt )
		local textSize = Vector2:tempT( RL.MeasureTextEx( ts.font, cursorText, ts.fontSize, ts.spacing ) )

		self._cursor.rect:setPosition( textSize.x, 0 )
		self._cursor.scrollPos = math.max( 0, self._cursor.rect.x + self._cursor.rect.width + 8 - self.view.width )
	else
		self._cursor.rect:setPosition( 0 )
		self._cursor.scrollPos = 0
	end
end

function TextInputBox:textEditErase( cpt, offset )
	offset = offset or 0

	table.remove( cpt, self._cursor.pos - 1 + offset )

	if offset == 0 then
		self._cursor.pos = RL.Clamp( self._cursor.pos - 1, 1, #cpt + 1 )
	end

	self:updateText( cpt )
end

function TextInputBox:moveCursor( cpt, pos )
	self._cursor.pos = RL.Clamp( pos, 1, #cpt + 1 )
	self:updateText( cpt )
end

function TextInputBox:startEditMode()
	local cpt = RL.LoadCodepoints( self.text )
	local styles = self:getStyles()
	local ts = styles.text
	
	if self._gui.textEditControl == self then
		local pos = #cpt + 1
		local clickPos = self._gui._mousePressPos - self.view:getPosition() + Vector2:temp( self._cursor.scrollPos, 0 )
		local len = 0

		for i, cp in ipairs( cpt ) do
			local s = RL.CodepointToUTF8( cp )
			local textSize = Vector2:tempT( RL.MeasureTextEx( ts.font, s, ts.fontSize, ts.spacing ) )

			len = len + textSize.x + ts.spacing

			if clickPos.x <= len then
				pos = i
				break
			end
		end

		self._cursor.pos = RL.Clamp( pos, 1, #cpt + 1 )
	else
		self._cursor.pos = RL.GetCodepointCount( self.text ) + 1
	end

	self._gui.controlTextEdit = self
	self._editMode = true
	self:updateText( cpt )
end

function TextInputBox:endEditMode()
	self.textEditControl = nil
	self._editMode = false
	self._cursor.scrollPos = 0
	self._gui.controlTextEdit = nil

	if self.callbacks.set then
		self.callbacks.set( self )
	end
end

function TextInputBox:textEdit( delta )
	local edited = false

	repeat
		local char = RL.GetCharPressed()

		if 0 < char then
			local cpt = RL.LoadCodepoints( self.text )

			if self.charLimit == nil or #cpt < self.charLimit then
				table.insert( cpt, self._cursor.pos, char )
				self._cursor.pos = RL.Clamp( self._cursor.pos + 1, 0, #cpt + 1 )

				self:updateText( cpt )
				edited = true
			end
		end
	until char == 0

	repeat
		local key = RL.GetKeyPressed()

		if 0 < key then
			local cpt = RL.LoadCodepoints( self.text )

			if key == RL.KEY_BACKSPACE and 0 < #cpt then
				self:textEditErase( cpt )
				edited = true
			elseif key == RL.KEY_DELETE and 0 < #cpt then
				self:textEditErase( cpt, 1 )
				edited = true
			elseif key == RL.KEY_ENTER or key == RL.KEY_KP_ENTER then
				self:endEditMode()
			elseif key == RL.KEY_ESCAPE then
				self:endEditMode()
			elseif key == RL.KEY_LEFT then
				self:moveCursor( cpt, self._cursor.pos - 1 )
			elseif key == RL.KEY_RIGHT then
				self:moveCursor( cpt, self._cursor.pos + 1 )
			end
		end
	until key == 0

	if RL.IsKeyDown( RL.KEY_BACKSPACE ) or RL.IsKeyDown( RL.KEY_LEFT ) or RL.IsKeyDown( RL.KEY_RIGHT )
	or RL.IsKeyDown( RL.KEY_DELETE ) then
		self._eraceTimer.timer = self._eraceTimer.timer + delta

		if self._eraceTimer.threshold + self._eraceTimer.intervall <= self._eraceTimer.timer then
			local cpt = RL.LoadCodepoints( self.text )

			self._eraceTimer.timer = self._eraceTimer.timer - self._eraceTimer.intervall

			if RL.IsKeyDown( RL.KEY_BACKSPACE ) then
				self:textEditErase( cpt )
				edited = true
			elseif RL.IsKeyDown( RL.KEY_DELETE ) then
				self:textEditErase( cpt, 1 )
				edited = true
			elseif RL.IsKeyDown( RL.KEY_LEFT ) then
				self:moveCursor( cpt, self._cursor.pos - 1 )
			elseif RL.IsKeyDown( RL.KEY_RIGHT ) then
				self:moveCursor( cpt, self._cursor.pos + 1 )
			end
		end
	else
		self._eraceTimer.timer = 0
	end

	if edited and self.callbacks.edit then
		self.callbacks.edit( self )
	end
end

function TextInputBox:updateView()
	local styles = self:getStyles()
	local borderW = styles.border.width

	self.view = self.bounds:addPosition( Vector2:temp( borderW ) ):subSize( Vector2:temp( borderW * 2 ) )
end

function TextInputBox:update( delta )
	if self.locked or self.disabled then
		return
	end

	if self._gui._isMouseReleased then
		if self._gui.mouseOver == self and self._gui.controlPressed == self then
			if self.callbacks.pressed then
				self.callbacks.pressed( self )
			end

			self:startEditMode()
		else
			self:endEditMode()
		end
	end

	if self._editMode then
		self:textEdit( delta )
	end
end

function TextInputBox:draw()
	local styles = self:getStyles()

	if styles.textures then
		self._gui:drawTexturedRectangle( self.bounds, styles )
	else
		self._gui:drawRectangle( self.bounds, styles )
	end

	local borderW = styles.border.width

	RL.BeginScissorMode( self.view )
		if self.text then
			self._gui:drawText( self.text, self.bounds:addPosition( Vector2:temp( borderW - self._cursor.scrollPos, 0 ) ), styles )
		end

		if self._editMode then
			RL.DrawRectangle( self._cursor.rect:addPosition( Vector2:temp( borderW + self.bounds.x - self._cursor.scrollPos, self.bounds.y ) ), RL.BLUE )
		end
	RL.EndScissorMode()
end

function TextInputBox:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateView()
end

-- Panel control.

local Panel = {}
Panel.__index = Panel

Panel.DEFAULT_STYLES = {
	normal = GUI_DEFAULT_STYLES.normal,
	disabled = GUI_DEFAULT_STYLES.disabled,
}

function Panel:new( t )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()

	object.visible = t.visible or true
	object.disabled = t.disabled or false
	object.styles = t.styles or object.DEFAULT_STYLES
	object.tooltip = t.tooltip

	object._isMouseOver = false

	return object
end

-- function Panel:update( delta )
-- end

function Panel:draw()
	local style = self.disabled and "disabled" or "normal"
	local styles = self.styles[ style ]
	
	if styles.textures then
		self._gui:drawTexturedRectangle( self.bounds, styles )
	else
		self._gui:drawRectangle( self.bounds, styles )
	end

	if styles.icons then
		self._gui:drawIcons( self.bounds, styles )
	end
end

function Panel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

-- Slider control.

local Slider = {}
Slider.__index = Slider

Slider.DEFAULT_STYLES = Util.deepCopy( GUI_DEFAULT_STYLES )
Slider.DEFAULT_STYLES.normal.slider = {
	width = RL.GuiGetStyle( RL.SLIDER, RL.SLIDER_WIDTH ),
	base = {
		-- color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BASE_COLOR_NORMAL ) ) ),
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BORDER_COLOR_NORMAL ) ) ),
	},
	border = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BORDER_COLOR_NORMAL ) ) ),
		width = RL.GuiGetStyle( RL.SLIDER, RL.BORDER_WIDTH ),
	},
}
Slider.DEFAULT_STYLES.focused.slider = {
	width = RL.GuiGetStyle( RL.SLIDER, RL.SLIDER_WIDTH ),
	base = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BASE_COLOR_FOCUSED ) ) ),
	},
	border = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BORDER_COLOR_FOCUSED ) ) ),
		width = RL.GuiGetStyle( RL.SLIDER, RL.BORDER_WIDTH ),
	},
}
Slider.DEFAULT_STYLES.disabled.slider = {
	width = RL.GuiGetStyle( RL.SLIDER, RL.SLIDER_WIDTH ),
	base = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BASE_COLOR_DISABLED ) ) ),
	},
	border = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BORDER_COLOR_DISABLED ) ) ),
		width = RL.GuiGetStyle( RL.SLIDER, RL.BORDER_WIDTH ),
	},
}
Slider.DEFAULT_STYLES.pressed.slider = {
	width = RL.GuiGetStyle( RL.SLIDER, RL.SLIDER_WIDTH ),
	base = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BASE_COLOR_PRESSED ) ) ),
	},
	border = {
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.SLIDER, RL.BORDER_COLOR_PRESSED ) ) ),
		width = RL.GuiGetStyle( RL.SLIDER, RL.BORDER_WIDTH ),
	},
}

function Slider:new( t )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.callbacks = t.callbacks or {} -- pressed, edit and set.
	object.value = t.value or 0
	object.minValue = t.minValue or 0
	object.maxValue = t.maxValue or 100
	object.valueStep = t.valueStep

	object.visible = t.visible or true
	object.locked = t.locked or false
	object.disabled = t.disabled or false -- Same as locked but also uses style.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.tooltip = t.tooltip

	object._isMouseOver = false

	return object
end

function Slider:getStyles()
	local pressed = not self.locked and not self.disabled and self._gui._isMouseDown and self._gui.mouseOver == self and self._gui.controlPressed == self
	local style = pressed and "pressed" or self.disabled and "disabled" or self._isMouseOver and "focused" or "normal"

	return self.styles[ style ]
end

function Slider:update( delta )
	if self.locked or self.disabled then
		return
	end

	if self._gui.controlPressed == self then
		if self._gui.mouseOver == self or self._gui.controlDragged == self then
			if self._gui._isMousePressed then
				self._gui.controlDragged = self

				if self.callbacks.pressed then
					self.callbacks.pressed( self )
				end
			end

			if self._gui._isMouseDown then
				local styles = self:getStyles()
				local sliderW = styles.slider.width

				self.value = RL.Remap(
					self._gui._mousePos.x - self.bounds.x - sliderW / 2,
					0, self.bounds.width - sliderW,
					self.minValue, self.maxValue
				)
				if self.valueStep then
					self.value = RL.Round( self.value / self.valueStep ) * self.valueStep
				end

				self.value = Util.clamp( self.value, self.minValue, self.maxValue )

				if self.callbacks.edit then
					self.callbacks.edit( self )
				end
			end
		end

		if self._gui._isMouseReleased then
			self._gui.controlDragged = nil

			if self.callbacks.set then
				self.callbacks.set( self )
			end
		end
	end

	if self._gui.mouseOver == self and not self._gui.controlDragged then
		local mouseWheel = RL.GetMouseWheelMove()

		if mouseWheel ~= 0 then
			self.value = self.value + ( self.valueStep or 1 ) * mouseWheel
			self.value = Util.clamp( self.value, self.minValue, self.maxValue )

			if self.callbacks.set then
				self.callbacks.set( self )
			end
		end
	end
end

function Slider:draw()
	local styles = self:getStyles()
	
	if styles.textures then
		self._gui:drawTexturedRectangle( self.bounds, styles )
	else
		self._gui:drawRectangle( self.bounds, styles )
	end
	
	if styles.slider.textures then
		local rect = Rectangle:new(
			RL.Remap( self.value, self.minValue, self.maxValue,
				self.bounds.x, self.bounds.x + self.bounds.width - styles.slider.width
			),
			self.bounds.y,
			styles.slider.width, self.bounds.height
		)
		self._gui:drawTexturedRectangle( rect, styles.slider )
	else
		local rect = Rectangle:new(
			RL.Remap( self.value, self.minValue, self.maxValue,
				self.bounds.x, self.bounds.x + self.bounds.width - styles.slider.width
			),
			self.bounds.y,
			styles.slider.width, self.bounds.height
		)

		self._gui:drawRectangle( rect, styles.slider )
	end

	if styles.icons then
		self._gui:drawIcons( self.bounds, styles )
	end
end

function Slider:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

return {
	Label = Label,
	Button = Button,
	TextInputBox = TextInputBox,
	Panel = Panel,
	Slider = Slider,
}
