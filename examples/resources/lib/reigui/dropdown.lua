local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

local Dropdown = {}
local metatable = {
	__index = setmetatable( Dropdown, { __index = GuiControl } ),
}

Dropdown.DEFAULT_STYLES = {}

function Dropdown.DEFAULT_STYLES_UPDATE()
	Dropdown.DEFAULT_STYLES = {
		dropdown = {
			spacing = 0,
			trimToTextWidth = false,
			trimMarginLeft = 4,
			trimMarginRight = 4,
			alignH = RL.TEXT_ALIGN_LEFT,
			accumPosY = true,
		},
		button = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	}
end

Dropdown.DEFAULT_STYLES_UPDATE()

function Dropdown:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new( 0, 0, 20, 20 )
	object.text = t.text
	object.toggle = Util.setWithDefault( t.toggle, false )
	object.mouseClose = Util.setWithDefault( t.mouseClose, true )
	object.callbacks = t.callbacks or {} -- pressed, released.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.stylesOverlay = t.stylesOverlay or {}
	object.tooltip = t.tooltip

	object.contentBounds = Rectangle:new()

	-- Implementation controls.
	object._controls = {
		-- button = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	-- Dropdown controls.
	object.controls = {}

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.

	object._ctrPos = Vector2:new()

	object:createControls()
	object:setPosition( object.bounds:getPosition() )

	return object
end

function Dropdown:createControls()
	local styles = self.styles

	-- Button.

	self._controls.button = self._gui:newButton( {
		bounds = self.bounds:clone(),
		text = self.text,
		toggle = self.toggle,
		styles = styles.button,
		tooltip = self.tooltip,
		callbacks = {
			released = function( this )
				this.toggle = not this.toggle
				self:showContent( this.toggle )

				if self.callbacks.released then
					self.callbacks.released( this )
				end
			end
		},
	} )
	self._controls.button.position = Vector2:new()

	table.insert( self._controlsArray, self._controls.button )
end

function Dropdown:updateControls()
	self._ctrPos:set( 0, self.bounds.height )

	for _, control in ipairs( self.controls ) do
		self:setControlPos( control )
	end
end

-- Note! GridFills expect that controls are the same size.
function Dropdown:setControlPos( control )
	local styles = self.styles.dropdown

	-- control.position = self._ctrPos:clone()
	-- control.position = Vector2:new()
	control.position = styles.accumPosY and self._ctrPos:clone() or Vector2:new()

	self._ctrPos.y = self._ctrPos.y + control.bounds.height + styles.spacing

	if styles.alignH == RL.TEXT_ALIGN_RIGHT then
		control.position.x = self.bounds.width - control.bounds.width
	elseif styles.alignH == RL.TEXT_ALIGN_CENTER then
		control.position.x = RL.Round( self.bounds.width / 2 - control.bounds.width / 2 )
	end
end

function Dropdown:addControl( control, index )
	index = RL.Clamp( index or #self.controls + 1, 1, #self.controls + 1 )
	control._parent = self
	table.insert( self.controls, index, control )

	self:setControlPos( control )

	return control
end

function Dropdown:setButtonToTextWidth( leftMargin, rightMargin )
	local button = self._controls.button
	local textSize = self._gui:measureText( button.text, button.styles.normal, button.stylesOverlay.normal )
	local size = Vector2:new( textSize.x + ( leftMargin or 0 ) + ( rightMargin or 0 ), button.bounds.height )

	if Util.tableLen( button.stylesOverlay ) == 0 then
		button.stylesOverlay = self._gui:getDummyStyles()
	end

	self._gui:setForAllStyles( button.stylesOverlay, "text.alignH", RL.TEXT_ALIGN_LEFT )
	self._gui:setForAllStyles( button.stylesOverlay, "text.offset", Vector2:new( leftMargin or 0, 0 ) )

	self:setSize( size )
end

function Dropdown:setControlsToTextWidth( leftMargin, rightMargin )
	local maxWidth = 0
	-- Measure widest.
	for _, control in ipairs( self.controls ) do
		if control.text then
			local textSize = self._gui:measureText( control.text, control.styles.normal, control.stylesOverlay.normal )

			maxWidth = math.max(
				maxWidth,
				textSize.x + ( leftMargin or 0 ) + ( rightMargin or 0 )
			)
		end
	end
	-- Set widths.
	for _, control in ipairs( self.controls ) do
		control:setSize( Vector2:new( maxWidth, control.bounds.height ) )
		
		if Util.tableLen( control.stylesOverlay ) == 0 then
			control.stylesOverlay = self._gui:getDummyStyles()
		end

		self._gui:setForAllStyles( control.stylesOverlay, "text.alignH", RL.TEXT_ALIGN_LEFT )
		self._gui:setForAllStyles( control.stylesOverlay, "text.offset", Vector2:new( leftMargin or 0, 0 ) )
	end
end

function Dropdown:updateMouseOffset()
	if self._gui then
		self.gui.mouseScale = self._gui.mouseScale
		local mouseScale = Vector2:temp( 1, 1 ) / self.gui.mouseScale

		self.gui.mouseOffset = self._gui.mouseOffset + ( -Vector2:temp( self.bounds.x, self.bounds.y ) ) * mouseScale
	end
end

function Dropdown:update( delta )
	if not self.toggle then
		return
	end

	if self.mouseClose and not self._controls.button._isMouseOver
	and self._gui._isMousePressed and not self.contentBounds:checkCollisionPoint( self._gui._mousePos ) then
		self:showContent( false )
	end
end

function Dropdown:showContent( visible )
	self._controls.button.toggle = visible
	self.toggle = visible

	if visible then
		self:setPosition( self.bounds:getPosition() )
	end

	for _, control in ipairs( self.controls ) do
		control:setVisible( visible )
		control:setToTop()
	end
end

function Dropdown:clear()
	for _, control in ipairs( self.controls ) do
		control:remove()
	end

	self.controls = {}
end

function Dropdown:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateControls()
	self.contentBounds:set(	self.bounds.x, self.bounds.y + self.bounds.height, 0, 0	)

	for _, control in ipairs( self._controlsArray ) do
		control:setPosition( pos + control.position or Vector2:temp() )
	end
	for _, control in pairs( self.controls ) do
		control:setPosition( pos + control.position or Vector2:temp() )

		if self.mouseClose then
			self.contentBounds = self.contentBounds:fit( control.bounds )
		end
	end

	if self.callbacks.setPosition then
		self.callbacks.setPosition( self )
	end
end

function Dropdown:setSize( size )
	self.bounds:setSizeV( size )

	if self._controlsArray then
		for _, control in ipairs( self._controlsArray ) do
			control:setSize( size )
		end
	end

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	-- self:setPosition( self.bounds:getPosition() )
end

return { Dropdown = Dropdown }
