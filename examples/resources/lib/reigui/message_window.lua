local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

-- Spinner control.

local MessageWindow = {}
local metatable = {
	__index = setmetatable( MessageWindow, { __index = GuiControl } ),
}

MessageWindow.DEFAULT_STYLES = {
	messageWindow = {
		minBounds = Rectangle:new( 0, 0, 400, 162 ),
		maxBounds = Rectangle:new( 0, 0, RL.GetScreenSize()[1], RL.GetScreenSize()[2] ),
		buttonSize = Vector2:new( 96, 24 ),
		padding = 8,
		spacing = 4,
	},
	window = Util.deepCopy( Gui.Window.DEFAULT_STYLES ),
	label = Util.deepCopy( Gui.Label.DEFAULT_STYLES ),
	button = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
}

function MessageWindow:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or object.DEFAULT_STYLES.messageWindow.minBounds:clone()
	object.header = t.header
	object.text = t.text

	object.visible = Util.setWithDefault( t.visible, false ) -- Note. Will be invisible by default.
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.
	object.draggable = Util.setWithDefault( t.draggable, true )

	object.callbacks = { -- grab, drag, close, setPosition, apply.
		close = t.callbacks and t.callbacks.close or function() object:setVisible( false ) end,
		grab = t.callbacks and t.callbacks.grab or function() object:setToTop() end,
		drag = t.callbacks and t.callbacks.drag or function( this ) object:setPosition( this.bounds:getPosition() ) end,
	}
	object.styles = t.styles or object.DEFAULT_STYLES
	object.stylesOverlay = t.stylesOverlay or {}

	object._controls = {
		-- window = nil,
		-- label = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object.buttons = {} -- Create always new on popup.
	object.textRect = Rectangle:new()

	object:createControls( t )
	object:setPosition( object.bounds:getPosition() )
	object:setVisible( self.visible )

	return object
end

function MessageWindow:createControls( t )
	local styles = self.styles
	local padding = styles.messageWindow.padding
	local spacing = styles.messageWindow.spacing

	-- Window.

	self._controls.window = self._gui:newWindow( {
		bounds = Rectangle:new( 0, 0, self.bounds.width, self.bounds.height ),
		draggable = self.draggable,
		callbacks = {
			close = self.callbacks.close,
			grab = self.callbacks.grab,
			drag = self.callbacks.drag,
		},
		styles = styles.window,
	} )
	self._controls.window.position = Vector2:new()

	table.insert( self._controlsArray, self._controls.window )
	
	-- Label.

	local winPanelBounds = self._controls.window:getPanelBounds()

	self._controls.label = self._gui:newLabel( {
		text = "",
		bounds = Rectangle:new( 0, 0, winPanelBounds.width - padding * 2, winPanelBounds.height - padding * 2 ),
		styles = styles.label,
	} )
	self._controls.label.position = Vector2:new( padding, padding )

	table.insert( self._controlsArray, self._controls.label )
end

function MessageWindow:popup( header, text, buttons )
	self._controls.window:setText( header )
	self._controls.label.text = text

	local winStyles = self.styles.messageWindow
	local textSize = self._gui:measureText( text, self.styles.label.normal, self.stylesOverlay.label and self.stylesOverlay.label.normal )
	local buttonHeight = winStyles.buttonSize.y
	local padding = winStyles.padding
	local size = Vector2:new(
		RL.Clamp( textSize.x + padding * 2, winStyles.minBounds.width, winStyles.maxBounds.width ),
		RL.Clamp( textSize.y + buttonHeight + padding * 2, winStyles.minBounds.height, winStyles.maxBounds.height )
	):round()

	local winSize = Vector2:tempT( RL.GetScreenSize() )

	self:setSize( size )
	self:createButtons( buttons )
	self:setPosition( ( winSize:scale( 0.5 ) - self.bounds:getSize():scale( 0.5 ) ):round() )
	self:setVisible( true )
	self:setToTop()
end

function MessageWindow:createButtons( buttons )
	for _, button in ipairs( self.buttons ) do
		button:remove()
	end

	for _ = 1, #self.buttons do
		table.remove( self._controlsArray )
	end

	self.buttons = {}

	local winStyles = self.styles.messageWindow
	local buttonsWidth = #buttons * winStyles.buttonSize.x + ( #buttons - 1 ) * winStyles.spacing
	local pos = Vector2:new( self.bounds.width / 2 - buttonsWidth / 2, self.bounds.height - winStyles.buttonSize.y - winStyles.padding ):round()

	for i, b in ipairs( buttons ) do
		self.buttons[i] = self._gui:newButton( {
			text = b.text,
			bounds = Rectangle:new( 0, 0, winStyles.buttonSize.x, winStyles.buttonSize.y ),
			callbacks = b.callbacks,
			styles = self.styles.button,
		} )
		self.buttons[i].position = pos:clone()
		self.buttons[i].arrayId = #self._controlsArray

		table.insert( self._controlsArray, self.buttons[i] )

		pos.x = pos.x + winStyles.buttonSize.x + winStyles.spacing
	end
end

function MessageWindow:setSize( size )
	local winStyles = self.styles.messageWindow

	self.bounds:setSizeV( size )
	self._controls.window:setSize( size )

	local winPanelBounds = self._controls.window:getPanelBounds()
	winPanelBounds.width = winPanelBounds.width - winStyles.padding * 2
	winPanelBounds.height = winPanelBounds.height - winStyles.padding * 2

	self._controls.label:setSize( winPanelBounds:getSize() )
end

return { MessageWindow = MessageWindow }
