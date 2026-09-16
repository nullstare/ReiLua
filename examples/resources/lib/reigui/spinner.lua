local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )
local Gui = Gui or require( "reigui/gui" )

-- Spinner control.

local Spinner = {}
Spinner.__index = Spinner

Spinner.DEFAULT_STYLES = {
	spinner = {
		buttonWidth = 20,
		spacing = 2,
	},
	subButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	-- addButton = gui.Spinner.DEFAULT_STYLES_BUTTON_ADD,
	-- textInput = gui.Spinner.DEFAULT_STYLES_TEXT_INPUT_BOX,
}

Spinner.DEFAULT_STYLES.subButton.normal.icons = {
	{
		iconId = RL.ICON_ARROW_LEFT,
		offset = Vector2:new( 0, 0 ),
		pixelSize = 1,
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
		alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
	}
}
Gui:setForAllStyles( Spinner.DEFAULT_STYLES.subButton, "icons", Spinner.DEFAULT_STYLES.subButton.normal.icons )

-- Button add.

Spinner.DEFAULT_STYLES.addButton = Util.deepCopy( Spinner.DEFAULT_STYLES.subButton )
Spinner.DEFAULT_STYLES.addButton.normal.icons[1].iconId = RL.ICON_ARROW_RIGHT
Gui:setForAllStyles( Spinner.DEFAULT_STYLES.addButton, "icons", Spinner.DEFAULT_STYLES.addButton.normal.icons )

-- Text input.

Spinner.DEFAULT_STYLES.textInput = Util.deepCopy( Gui.TextInputBox.DEFAULT_STYLES )
Gui:setForAllStyles( Spinner.DEFAULT_STYLES.textInput, "text.alignH", RL.TEXT_ALIGN_CENTER )
Gui:setForAllStyles( Spinner.DEFAULT_STYLES.textInput, "cursor.draw", false )

function Spinner:new( gui, t )
	local object = setmetatable( {}, self )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.value = t.value or 0
	object.minValue = t.minValue or 0
	object.maxValue = t.maxValue or 100
	object.valueStep = t.valueStep

	object.visible = t.visible or true
	object.disabled = t.disabled or false
	object.locked = t.locked or false
	object.callbacks = t.callbacks -- set, setPosition.
	object.styles = t.styles or object.DEFAULT_STYLES

	object._controls = {
		-- subButton = nil,
		-- addButton = nil,
		-- textInput = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object:createControls( t )
	object:setPosition( object.bounds:getPosition() )

	return object
end

function Spinner:createControls( t )
	local styles = self.styles

	-- Sub button.

	self._controls.subButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, styles.spinner.buttonWidth, self.bounds.height ),
		callbacks = {
			released = function()
				self:setValue( self.value - ( self.valueStep or 1 ) )

				if self.callbacks.set then
					self.callbacks.set( self )
				end
			end,
		},
		styles = styles.subButton,
	} )
	self._controls.subButton.position = Vector2:new()

	-- Add button.

	self._controls.addButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, styles.spinner.buttonWidth, self.bounds.height ),
		callbacks = {
			released = function()
				self:setValue( self.value + ( self.valueStep or 1 ) )

				if self.callbacks.set then
					self.callbacks.set( self )
				end
			end,
		},
		styles = styles.addButton,
	} )
	self._controls.addButton.position = Vector2:new( self.bounds.width - styles.spinner.buttonWidth, 0 )

	-- Text Field.

	local spacing = styles.spinner.spacing

	self._controls.textInput = self._gui:newTextInputBox( {
		bounds = Rectangle:new( 0, 0, self.bounds.width - styles.spinner.buttonWidth * 2 - spacing * 2, self.bounds.height ),
		text = tostring( self.value ),
		callbacks = {
			set = function( this )
				self:setValue( tonumber( this.text ) )

				if self.callbacks.set then
					self.callbacks.set( self )
				end
			end,
		},
		styles = styles.textInput,
	} )
	self._controls.textInput.position = Vector2:new( styles.spinner.buttonWidth + spacing, 0 )

	self._controlsArray = {
		self._controls.subButton,
		self._controls.addButton,
		self._controls.textInput,
	}
end

function Spinner:setValue( value )
	value = value or self.minValue

	if self.valueStep then
		value = RL.Round( value / self.valueStep ) * self.valueStep
	end

	self.value = Util.clamp( value, self.minValue, self.maxValue )

	self._controls.textInput.text = tostring( self.value )

end

function Spinner:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	for _, control in ipairs( self._controlsArray ) do
		if control.setPosition then
			control:setPosition( pos + control.position or Vector2:temp() )
		else
			control.bounds:setPositionV( self.bounds:getPosition() + control.position or Vector2:temp() )
		end
	end

	if self.callbacks.setPosition then
		self.callbacks.setPosition( self )
	end
end

function Spinner:setSize( size )
	self.bounds:setSize( size )

	local ctrs = self._controls

	ctrs.handle.bounds.width = size.x - ctrs.closeButton.bounds.width
	ctrs.closeButton.position.x = ctrs.handle.bounds.width
	ctrs.panel.bounds.width = size.x
	ctrs.panel.bounds.height = size.y - ctrs.handle.bounds.height

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

function Spinner:_addControl( control, name )
	self._controls[ name ] = control
	table.insert( self._controlsArray, control )
end

function Spinner:setToTop()
	for _, control in ipairs( self._controlsArray ) do
		control:setToTop()
	end
end

function Spinner:setVisible( visible )
	for _, control in ipairs( self._controlsArray ) do
		control.visible = visible
	end
end

function Spinner:setDisabled( disabled )
	for _, control in ipairs( self._controlsArray ) do
		control.disabled = disabled
	end
end

function Spinner:setLocked( locked )
	for _, control in ipairs( self._controlsArray ) do
		control.locked = locked
	end
end

function Spinner:remove()
	for _, control in ipairs( self._controlsArray ) do
		control:remove()
	end

	self._gui:remove( self )
end

return { Spinner = Spinner }
