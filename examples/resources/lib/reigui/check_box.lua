local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )
local Gui = Gui or require( "reigui/gui" )

-- CheckBox control.

local CheckBox = {}
local metatable = {
	__index = setmetatable( CheckBox, { __index = GuiControl } ),
}

CheckBox.DEFAULT_STYLES = {}

function CheckBox.DEFAULT_STYLES_UPDATE()
	CheckBox.DEFAULT_STYLES = {
		checkBox = {
			buttonSize = Vector2:new( 22 ),
			padding = 4,
			spacing = 4,
		},
		button = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
		label = Util.deepCopy( Gui.Label.DEFAULT_STYLES ),
	}

	CheckBox.DEFAULT_STYLES.button.pressed.icons = {
		{
			iconId = RL.ICON_OK_TICK,
			offset = Vector2:new( 0, 0 ),
			pixelSize = 1,
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_FOCUSED ) ) ),
			alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	}

	CheckBox.DEFAULT_STYLES.button.pressed.border.color = CheckBox.DEFAULT_STYLES.button.focused.border.color
	Gui:setForAllStyles( CheckBox.DEFAULT_STYLES.label, "text.alignH", RL.TEXT_ALIGN_LEFT )
end

CheckBox.DEFAULT_STYLES_UPDATE()

function CheckBox:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.toggle = Util.setWithDefault( t.toggle, false )
	object.text = t.text or ""

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.
	object.callbacks = t.callbacks or {} -- set, setPosition.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.stylesOverlay = t.stylesOverlay or {}

	object._controls = {
		-- button = nil,
		-- label = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object:createControls( t )
	object:setPosition( object.bounds:getPosition() )

	return object
end

function CheckBox:createControls( t )
	local styles = self.styles

	-- Add button.

	self._controls.button = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, styles.checkBox.buttonSize.x, styles.checkBox.buttonSize.y ),
		toggle = self.toggle,
		callbacks = {
			released = function( this )
				this.toggle = not this.toggle

				if self.callbacks.set then
					self.callbacks.set( self )
				end
			end,
		},
		styles = styles.button,
	} )
	self._controls.button.position = Vector2:new(
		styles.checkBox.padding,
		self.bounds.height / 2 - styles.checkBox.buttonSize.y / 2
	):round()

	table.insert( self._controlsArray, self._controls.button )

	-- Label.

	self._controls.label = self._gui:newLabel( {
		bounds = Rectangle:new( 0, 0, self.bounds.width - styles.checkBox.buttonSize.x - styles.checkBox.spacing, self.bounds.height ),
		text = self.text,
		styles = styles.label,
	} )
	self._controls.label.position = Vector2:new( styles.checkBox.padding + styles.checkBox.buttonSize.x + styles.checkBox.spacing, 0 )

	table.insert( self._controlsArray, self._controls.label )
end

function CheckBox:setSize( size )
	self.bounds:setSize( size )

	local styles = self.styles
	local ctrs = self._controls

	ctrs.label.bounds = Rectangle:new( 0, 0, self.bounds.width - styles.checkBox.buttonSize.x - styles.checkBox.spacing, self.bounds.height )

	ctrs.button.position = Vector2:new(
		styles.checkBox.padding,
		self.bounds.height / 2 - styles.checkBox.buttonSize.y / 2
	):round()

	ctrs.label.position = Vector2:new( styles.checkBox.padding + styles.checkBox.buttonSize.x + styles.checkBox.spacing, 0 )

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

return { CheckBox = CheckBox }
