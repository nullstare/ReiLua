local PropertyList = {}
PropertyList.__index = PropertyList

function PropertyList:new( bounds, text, callbacks, styles, tooltip )
    local object = setmetatable( {}, self )
	object._gui = nil

	object.padding = 4 -- Content edges.
	object.spacing = 4 -- Between controls.
	object.contentPadding = Vector2:new( 0, 0 ) -- Extra padding for content rect.

    object.bounds = bounds:clone()
    object.text = text
    object.scroll = Vector2:new( 0, 0 )
	object.view = Rectangle:new( 0, 0, 0, 0 )
    object.callbacks = callbacks -- scroll, grab, drag.
	object.styles = styles
	object.tooltip = tooltip

	object.gui = Raygui:new() -- Contains full independent gui system.
	object.controls = {}
	object.content = Rectangle:new()

	-- Set in setSize.
	object.defaultControlSize = nil

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.defaultControlHeight = 22

	object:setSize( Vector2:new( object.bounds.width, object.bounds.height ) )

	object._forceCheckScroll = false
	object._posY = 0 -- In control list update.

	object:updateMouseOffset()

	return object
end

function PropertyList:getDefaultBounds()
	return Rectangle:new( self.padding, self.padding, self.defaultControlSize.x, self.defaultControlSize.y )
end

local function getControlBounds( control )
	return control.viewBounds or control.focusBounds or control.bounds
end

local function setGroupText( text, active )
	if active then
		return RL.GuiIconText( 120, text )
	else
		return RL.GuiIconText( 119, text )
	end
end

function PropertyList:updateControl( control )
	if control._defaultWidth then
		control.bounds.width = self:getDefaultBounds().width
	end
	if control._defaultHeight then
		control.bounds.height = self:getDefaultBounds().height
	end

	if control.visible then
		control:setPosition( Vector2:new( control.bounds.x, self._posY ) )
		local bounds = getControlBounds( control )

		if not control._noYAdvance then
			self._posY = self._posY + bounds.height + self.spacing
		end
		self.content = self.content:fit( bounds )
	end

	if type( control._controls ) == "table" then
		for _, groupControl in ipairs( control._controls ) do
			groupControl.visible = control.active
			-- Deactivate any subgroups.
			if not control.active and type( groupControl._controls ) == "table" then
				groupControl.active = false
			end

			self:updateControl( groupControl )
		end

		control.text = setGroupText( control.text:sub( 6 ), control.active ) -- Sub skips icon.
	end
	self.gui:setToBack( control )
end

function PropertyList:updateContent()
	self._posY = self.padding

	self.content.width = 0
	self.content.height = 0

	for _, control in ipairs( self.controls ) do
		self:updateControl( control )
	end
	self.content:set(
		0, 0,
		self.content.width + self.padding + self.contentPadding.y,
		self.content.height + self.padding + self.contentPadding.x
	)
	self._forceCheckScroll = true
end

-- Leave control bounds size to 0 to use default. Optional group for parameter 2.
function PropertyList:addControl( control, group, noYAdvance )
	control._noYAdvance = noYAdvance

	if control.bounds.width == 0 then
		control._defaultWidth = true -- Set defaultWidth on updateControl.
	end
	if control.bounds.height == 0 then
		control._defaultHeight = true -- Set defaultHeight on updateControl.
	end
	if control.bounds.x == 0 then
		control.bounds.x = self.padding
	end

	if group ~= nil then
		table.insert( group._controls, control )
	else
		table.insert( self.controls, control )
	end

	self:updateContent()
	return control
end

function PropertyList:addGroup( name, active, group )
	if active == nil then
		active = false
	end

	local control = self.gui:Toggle(
		self:getDefaultBounds(),
		setGroupText( name, active ),
		active,
		{ -- Callbacks.
			pressed = function( this ) this.text = setGroupText( name, this.active ) self:updateContent() end,
		},
		{ -- Styles.
			properties = {
				{ RL.TOGGLE, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT },
			}
		}
	)
	control._controls = {} -- Prefix _ to try to prevent clashing with control definition.
	control._defaultWidth = true -- Set defaultWidth on updateControl.
	control._defaultHeight = true -- Set defaultHeight on updateControl.

	if group ~= nil then
		table.insert( group._controls, control )
	else
		table.insert( self.controls, control )
	end

	self:updateContent()
	return control
end

function PropertyList:update()
	if not self.view:checkCollisionPoint( RL.GetMousePosition() ) then
		self.gui.locked = true
	else
		self.gui.locked = false
	end

	self.gui:update()

    return self._gui:drag( self )
end

function PropertyList:draw()
	local result, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view:setT( view )
	self.scroll:setT( scroll )

	if 0 < result or self._forceCheckScroll then
		if not self._forceCheckScroll then
			self._gui:checkScrolling()
		end
		self._forceCheckScroll = false

		self:updateMouseOffset()
		self.gui.view:set( -self.scroll.x, -self.scroll.y, self.view.width, self.view.height )

		if self.callbacks.scroll ~= nil then
			self.callbacks.scroll( self )
		end
	end
	-- Lock if this gui not focused.
	self.gui.locked = not ( self._gui.controls[ self._gui.focused ] == self ) or self._gui.locked

	RL.BeginScissorMode( self.view )
		RL.rlPushMatrix()
		RL.rlTranslatef( { RL.Round( self.view.x + self.scroll.x ), RL.Round( self.view.y + self.scroll.y ), 0 } )
		self.gui:draw()
		RL.rlPopMatrix()
	RL.EndScissorMode()
end

function PropertyList:updateMouseOffset()
	if self._gui then
		self.gui.mouseScale = self._gui.mouseScale
		local mouseScale = Vector2:temp( 1, 1 ) / self.gui.mouseScale

		self.gui.mouseOffset = self._gui.mouseOffset + ( -Vector2:temp( self.view.x, self.view.y ) - self.scroll ) * mouseScale
	end
end

function PropertyList:setPosition( pos )
	self.bounds.x = RL.Round( pos.x )
	self.bounds.y = RL.Round( pos.y )

	if self.visible then
		self:draw() -- Update self.view.
	end
	self:updateMouseOffset()
end

function PropertyList:setSize( size )
	self.bounds.width = size.x
	self.bounds.height = size.y

	local scrollBarWidth = RL.GuiGetStyle( RL.LISTVIEW, RL.SCROLLBAR_WIDTH )
	local borderWidth = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH )

	self.content = Rectangle:new(
		0,
		self.gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT,
		self.bounds.width - scrollBarWidth - self.padding * 2 - borderWidth * 2,
		self.bounds.height - scrollBarWidth - self.padding * 2 - borderWidth * 2
	)
	self.defaultControlSize = Vector2:new( self.content.width, self.defaultControlHeight )

	local _, _, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )

	self.view = Rectangle:newT( view )
	self.gui.view = Rectangle:new( 0, 0, self.view.width, self.view.height )

	self:updateContent()
end

function PropertyList:register( gui )
	function gui:PropertyList( bounds, text, callbacks, styles, tooltip )
		return self:addControl( PropertyList:new( bounds, text, callbacks, styles, tooltip ) )
	end
end

return PropertyList
