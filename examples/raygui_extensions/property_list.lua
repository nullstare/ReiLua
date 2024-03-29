local PropertyList = {}
PropertyList.__index = PropertyList

function PropertyList:new( bounds, text, callbacks, styles, tooltip )
    local object = setmetatable( {}, self )
	object._gui = nil

	object.padding = 4 -- Content edges.
	object.spacing = 4 -- Between controls.

    object.bounds = bounds:clone()
    object.text = text
    object.scroll = Vec2:new()
	object.view = Rect:new()
    object.callbacks = callbacks -- scroll, grab, drag.
	object.styles = styles
	object.tooltip = tooltip

	object.gui = Raygui:new() -- Contains full independent gui system.
	object.controls = {}

	-- Set in setSize.
	object.framebufferSize = nil
	object.framebuffer = nil
	object.defaultControlSize = nil

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.defaultControlHeight = 22
	object.mouseScale = 1 -- Set this if drawing in different size to render texture for example.

	object:setSize( Vec2:new( object.bounds.width, object.bounds.height ) )

	object._forceCheckScroll = false
	object._posY = 0 -- In control list update.

	object:updateMouseOffset()

	return object
end

function PropertyList:getDefaultBounds()
	return Rect:new( self.padding, self.padding, self.defaultControlSize.x, self.defaultControlSize.y )
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
		control:setPosition( Vec2:new( control.bounds.x, self._posY ) )
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
	self.gui:set2Back( control )
end

function PropertyList:updateContent()
	self._posY = self.padding

	self.content.width = 0
	self.content.height = 0

	for _, control in ipairs( self.controls ) do
		self:updateControl( control )
	end
	self.content.x = 0
	self.content.y = 0
	self.content.height = self.content.height + self.padding + self.view.height - self.defaultControlSize.y - self.spacing
	self.content.width = self.content.width + self.padding
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

	RL.BeginTextureMode( self.framebuffer )
		RL.ClearBackground( RL.BLANK )
		RL.rlTranslatef( { self.scroll.x, self.scroll.y, 0 } )
		self.gui:draw()
	RL.EndTextureMode()

    return self._gui:drag( self )
end

function PropertyList:draw()
	local oldScroll = self.scroll:clone()
	local _, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view:set( view )
	self.scroll:set( scroll )

	if self.scroll ~= oldScroll or self._forceCheckScroll then
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

	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( self.framebuffer ),
		{ 0, self.framebufferSize.y - self.view.height, self.view.width, -self.view.height },
		{ math.floor( self.view.x ), math.floor( self.view.y ), self.view.width, self.view.height },
		{ 0, 0 },
		0.0,
		RL.WHITE 
	)
end

function PropertyList:updateMouseOffset()
	self.gui.mouseOffset = Vec2:new( -self.view.x - self.scroll.x, -self.view.y - self.scroll.y ):scale( self.mouseScale )
end

function PropertyList:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateMouseOffset()
end

function PropertyList:setSize( size )
	self.bounds.width = size.x
	self.bounds.height = size.y

	local scrollBarWidth = RL.GuiGetStyle( RL.LISTVIEW, RL.SCROLLBAR_WIDTH )
	local borderWidth = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH )

	self.content = Rect:new( 
		0,
		self.gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT,
		self.bounds.width - scrollBarWidth - self.padding * 2 - borderWidth * 2,
		self.bounds.height - scrollBarWidth - self.padding * 2 - borderWidth * 2
	)
	self.defaultControlSize = Vec2:new( self.content.width, self.defaultControlHeight )

	local _, _, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view = Rect:new( view )

	self.gui.view = Rect:new( 0, 0, self.view.width, self.view.height )
	self.framebufferSize = Vec2:new( self.bounds.width, self.bounds.height - self.gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT )

	if self.framebuffer ~= nil and not RL.IsGCUnloadEnabled() then
		RL.UnloadRenderTexture( self.framebuffer )
	end
	self.framebuffer = RL.LoadRenderTexture( self.framebufferSize )

	self:updateContent()
end

function PropertyList:register( gui )
	function gui:PropertyList( bounds, text, callbacks, styles, tooltip )
		return self:addControl( PropertyList:new( bounds, text, callbacks, styles, tooltip ) )
	end
end

return PropertyList
