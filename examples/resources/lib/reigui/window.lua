local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )

-- Window control.

local Window = {}
Window.__index = Window

-- Window.DEFAULT_STYLES = {
-- 	handle = Gui.Handle,
-- 	closeButton = Gui.Button,
-- 	panel = Gui.Panel,
-- }

-- Window.DEFAULT_STYLES = Util.deepCopy( GUI_DEFAULT_STYLES )
Window.DEFAULT_STYLES = {
	handleHeight = 20,
	closeButtonWidth = 20,
}

function Window:new( gui, t )
	if not gui.Window.DEFAULT_STYLES_CLOSE_BUTTON then
		gui.Window.DEFAULT_STYLES_CLOSE_BUTTON = Util.deepCopy( gui.Button.DEFAULT_STYLES )

		gui.Window.DEFAULT_STYLES_CLOSE_BUTTON.normal.icons = {
			{
				iconId = RL.ICON_CROSS,
				offset = Vector2:new( 0, 0 ),
				pixelSize = 1,
				color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
				alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
				alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
			}
		}
		local icons = gui.Window.DEFAULT_STYLES_CLOSE_BUTTON.normal.icons

		gui.Window.DEFAULT_STYLES_CLOSE_BUTTON.focused.icons = icons
		gui.Window.DEFAULT_STYLES_CLOSE_BUTTON.disabled.icons = icons
		gui.Window.DEFAULT_STYLES_CLOSE_BUTTON.pressed.icons = icons
	end

	local object = setmetatable( {}, self )

	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.text = t.text

	object.visible = t.visible or true
	object.disabled = t.disabled or false
	object.locked = t.locked or false
	object.callbacks = t.callbacks -- grab, drag, close, setPosition.
	object.styles = t.styles or {
		window = object.DEFAULT_STYLES,
		handle = gui.Handle.DEFAULT_STYLES,
		closeButton = gui.Window.DEFAULT_STYLES_CLOSE_BUTTON,
		panel = gui.Panel.DEFAULT_STYLES,
	}
	-- object.tooltip = t.tooltip
	
	object.controls = {
		-- handle = nil,
		-- closeButton = nil,
		-- panel = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object:createControls( t )
	object:setPosition( object.bounds:getPosition() )
	
	-- object._isMouseOver = false

	return object
end

function Window:createControls( t )
	local styles = self.styles

	-- Handle.

	local clampBounds = Rectangle:newR( self.bounds )
	clampBounds:setPosition()

	self.controls.handle = self._gui:newHandle( {
		bounds = Rectangle:new( 0, 0, self.bounds.width - styles.window.closeButtonWidth, styles.window.handleHeight ),
		text = self.text,
		callbacks = {
			pressed = function()
				if self.callbacks.grab then
					self.callbacks.grab( self )
				end
			end,
			drag = function( this )
				self:setPosition( this.bounds:getPosition() )

				if self.callbacks.drag then
					self.callbacks.drag( self )
				end
			end,
		},
		styles = styles.handle,
		clampBounds = clampBounds,
	} )
	self.controls.handle.position = Vector2:new()

	-- Close button.

	self.controls.closeButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, styles.window.closeButtonWidth, self.controls.handle.bounds.height ),
		-- text = "Button 1",
		callbacks = {
			released = function()
				if self.callbacks.close then
					self.callbacks.close( self )
				end
			end,
		},
		styles = styles.closeButton,
	} )
	self.controls.closeButton.position = Vector2:new( self.controls.handle.bounds.width, 0 )

	-- Panel.

	self.controls.panel = self._gui:newPanel( {
		bounds = Rectangle:new( 0, 0, self.bounds.width, self.bounds.height - self.controls.handle.bounds.height ),
		styles = styles.panel,
	} )
	self.controls.panel.position = Vector2:new( 0, styles.window.handleHeight )

	self._controlsArray = {
		self.controls.handle,
		self.controls.closeButton,
		self.controls.panel,
	}
end

function Window:setPosition( pos )
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

function Window:setSize( size )
	self.bounds:setSize( size )

	local ctrs = self.controls

	ctrs.handle.bounds.width = size.x - ctrs.closeButton.bounds.width
	ctrs.closeButton.position.x = ctrs.handle.bounds.width
	ctrs.panel.bounds.width = size.x
	ctrs.panel.bounds.height = size.y - ctrs.handle.bounds.height

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

function Window:addControl( control, name )
	self.controls[ name ] = control
	table.insert( self._controlsArray, control )
end

function Window:setToTop()
	for _, control in ipairs( self._controlsArray ) do
		control:setToTop()
	end
end

function Window:setVisible( visible )
	for _, control in ipairs( self._controlsArray ) do
		control.visible = visible
	end
end

function Window:setDisabled( disabled )
	for _, control in ipairs( self._controlsArray ) do
		control.disabled = disabled
	end
end

function Window:setLocked( locked )
	for _, control in ipairs( self._controlsArray ) do
		control.locked = locked
	end
end

function Window:remove()
	for _, control in ipairs( self._controlsArray ) do
		control:remove()
	end

	self = nil
end

return { Window = Window }
