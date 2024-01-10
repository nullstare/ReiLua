local PropertyList = {}
PropertyList.__index = PropertyList

local RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT = 24

function PropertyList:new( bounds, text, callback, grabCallback, dragCallback, styles )
    local object = setmetatable( {}, self )
	object._parent = nil

	local scrollBarWidth = RL.GuiGetStyle( RL.LISTVIEW, RL.SCROLLBAR_WIDTH )
	local borderWidth = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH )
	object.padding = 4 -- Content edges.
	object.spacing = 4 -- Between controls.

    object.bounds = bounds:clone()
    object.text = text
    object.content = Rect:new( 
		0,
		RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT,
		bounds.width - scrollBarWidth - object.padding * 2 - borderWidth * 2,
		bounds.height - scrollBarWidth - object.padding * 2 - borderWidth * 2
	)
    object.scroll = Vec2:new()
	object.view = Rect:new()
    object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback
	object.styles = styles

	object.gui = Raygui:new() -- Contains full independent gui system.
	object.controls = {}

	-- Set initial view.
	local _, _, view = RL.GuiScrollPanel( object.bounds, object.text, object.content, object.scroll, object.view )
	object.view = Rect:new( view )

	object.gui.view = Rect:new( 0, 0, object.view.width, object.view.height )
	object.framebufferSize = Vec2:new( object.bounds.width, object.bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT )
	object.framebuffer = RL.LoadRenderTexture( object.framebufferSize )

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.mouseScale = 1 -- Set this if drawing in different size to render texture for example.
	object.defaultControlSize = Vec2:new( object.content.width, 22 )

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

function PropertyList:updateControl( control )
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

-- Leave control bounds size to 0 to use default. Optional group for parameter 2
function PropertyList:addControl( control, group, noYAdvance )
	control._noYAdvance = noYAdvance

	if control.bounds.width == 0 or control.bounds.height == 0 then
		control.bounds = self:getDefaultBounds()
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

local function setGroupText( text, active )
	if active then
		return RL.GuiIconText( 120, text )
	else
		return RL.GuiIconText( 119, text )
	end
end

function PropertyList:addGroup( name, active, group )
	if active == nil then
		active = false
	end

	local control = self.gui:Toggle(
		self:getDefaultBounds(),
		setGroupText( name, active ),
		active,
		function( this ) this.text = setGroupText( name, this.active ) self:updateContent() end,
		{
			{ RL.TOGGLE, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT }
		}
	)
	control._controls = {} -- Prefix _ to try to prevent clashing with control definition.

	if group ~= nil then
		table.insert( group._controls, control )
	else
		table.insert( self.controls, control )
	end

	self:updateContent()
	return control
end

function PropertyList:process()
	if not RL.CheckCollisionRecs( self.view, RL.GetMousePosition() ) then
		self.gui.locked = true
	else
		self.gui.locked = false
	end

	self.gui:process()

	RL.BeginTextureMode( self.framebuffer )
		RL.ClearBackground( RL.BLANK )
		RL.rlTranslatef( { self.scroll.x, self.scroll.y, 0 } )
		self.gui:draw()
	RL.EndTextureMode()

    return self._parent:drag( self )
end

function PropertyList:draw()
	local oldScroll = self.scroll:clone()
	local _, scroll, view = RL.GuiScrollPanel( self.bounds, self.text, self.content, self.scroll, self.view )
	self.view:set( view )
	self.scroll:set( scroll )

	if self.scroll ~= oldScroll or self._forceCheckScroll then
		if not self._forceCheckScroll then
			self._parent:checkScrolling()
		end
		self._forceCheckScroll = false

		self:updateMouseOffset()
		self.gui.view:set( -self.scroll.x, -self.scroll.y, self.view.width, self.view.height )

		if self.callback ~= nil then
			self.callback( self )
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

function PropertyList:register( gui )
	function gui:PropertyList( bounds, text, callback, grabCallback, dragCallback, styles )
		return self:addControl( PropertyList:new( bounds, text, callback, grabCallback, dragCallback, styles ) )
	end
end

return PropertyList
