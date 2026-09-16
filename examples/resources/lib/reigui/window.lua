local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )
local Gui = Gui or require( "reigui/gui" )

-- Window control.

local Window = {}
Window.__index = Window

Window.DEFAULT_STYLES = {
	window = {
		handleHeight = 20,
		closeButtonWidth = 20,
	},
	handle = Gui.Handle.DEFAULT_STYLES,
	closeButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	panel = Gui.Panel.DEFAULT_STYLES,
}

Window.DEFAULT_STYLES.closeButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES )

Window.DEFAULT_STYLES.closeButton.normal.icons = {
	{
		iconId = RL.ICON_CROSS,
		offset = Vector2:new( 0, 0 ),
		pixelSize = 1,
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
		alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
	}
}
Gui:setForAllStyles( Window.DEFAULT_STYLES.closeButton, "icons", Window.DEFAULT_STYLES.closeButton.normal.icons )

function Window:new( gui, t )
	local object = setmetatable( {}, self )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.text = t.text

	object.visible = t.visible == nil and true or t.visible
	object.locked = t.locked == nil and false or t.locked
	object.disabled = t.disabled == nil and false or t.disabled -- Same as locked but also uses style.
	object.draggable = t.draggable == nil and true or t.draggable
	object.callbacks = { -- grab, drag, close, setPosition.
		close = t.callbacks and t.callbacks.close or function() object:setVisible( false ) end,
		grab = t.callbacks and t.callbacks.grab or function() object:setToTop() end,
		drag = t.callbacks and t.callbacks.drag or function( this ) object:setPosition( this.bounds:getPosition() ) end,
	}
	object.styles = t.styles or object.DEFAULT_STYLES
	
	object._controls = {
		-- handle = nil,
		-- closeButton = nil,
		-- panel = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object:createControls()
	object:setPosition( object.bounds:getPosition() )

	return object
end

function Window:createControls()
	local styles = self.styles

	-- Handle.

	local clampBounds = Rectangle:newR( self.bounds )
	clampBounds:setPosition()

	self._controls.handle = self._gui:newHandle( {
		bounds = Rectangle:new( 0, 0, self.bounds.width - styles.window.closeButtonWidth, styles.window.handleHeight ),
		text = self.text,
		draggable = self.draggable,
		callbacks = {
			pressed = function()
				if self.callbacks.grab then
					self.callbacks.grab( self )
				end
			end,
			drag = function( this )
				if self.draggable then
					self:setPosition( this.bounds:getPosition() )

					if self.callbacks.drag then
						self.callbacks.drag( self )
					end
				end
			end,
		},
		styles = styles.handle,
		clampBounds = clampBounds,
	} )
	self._controls.handle.position = Vector2:new()

	-- Close button.

	self._controls.closeButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, styles.window.closeButtonWidth, self._controls.handle.bounds.height ),
		callbacks = {
			released = function()
				if self.callbacks.close then
					self.callbacks.close( self )
				end
			end,
		},
		styles = styles.closeButton,
	} )
	self._controls.closeButton.position = Vector2:new( self._controls.handle.bounds.width, 0 )

	-- Panel.

	self._controls.panel = self._gui:newPanel( {
		bounds = Rectangle:new( 0, 0, self.bounds.width, self.bounds.height - self._controls.handle.bounds.height ),
		styles = styles.panel,
	} )
	self._controls.panel.position = Vector2:new( 0, styles.window.handleHeight )

	self._controlsArray = {
		self._controls.handle,
		self._controls.closeButton,
		self._controls.panel,
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
	self.bounds:setSizeV( size )

	local ctrs = self._controls

	ctrs.handle.bounds.width = size.x - ctrs.closeButton.bounds.width
	ctrs.closeButton.position.x = ctrs.handle.bounds.width
	ctrs.panel.bounds.width = size.x
	ctrs.panel.bounds.height = size.y - ctrs.handle.bounds.height

	if ctrs.handle.clampBounds then
		ctrs.handle.clampBounds:setR( self.bounds )
	end

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

function Window:_addControl( control, name )
	self._controls[ name ] = control
	table.insert( self._controlsArray, control )
end

function Window:setDraggable( draggable )
	self.draggable = draggable
	self._controls.handle.draggable = self.draggable
end

function Window:setToTop()
	for _, control in ipairs( self._controlsArray ) do
		control:setToTop()
	end
end

function Window:setVisible( visible )
	self.visible = visible

	for _, control in ipairs( self._controlsArray ) do
		control.visible = visible
	end
end

function Window:setDisabled( disabled )
	self.disabled = disabled

	for _, control in ipairs( self._controlsArray ) do
		control.disabled = disabled
	end
end

function Window:setLocked( locked )
	self.locked = locked

	for _, control in ipairs( self._controlsArray ) do
		control.locked = locked
	end
end

function Window:remove()
	for _, control in ipairs( self._controlsArray ) do
		control:remove()
	end

	self._gui:remove( self )
end

return { Window = Window }
