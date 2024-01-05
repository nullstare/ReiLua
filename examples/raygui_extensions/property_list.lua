local PropertyList = {}
PropertyList.__index = PropertyList

function PropertyList:new( bounds, text, content, scroll, callback, grabCallback, dragCallback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
    object.content = content:clone()
    object.scroll = scroll:clone()
	object.view = Rect:new()
    object.callback = callback
	object.grabCallback = grabCallback
	object.dragCallback = dragCallback

	object.gui = Raygui:new() -- Contains full independent gui system.

	-- Set initial view and scroll.
	local _, scrollP, view = RL.GuiScrollPanel( object.bounds, object.text, object.content, object.scroll, object.view )
	object.scroll = Vec2:new( scrollP )
	object.view = Rect:new( view )

	object.gui.view = Rect:new( 0, 0, object.view.width, object.view.height )
	object.framebuffer = RL.LoadRenderTexture( { object.view.width, object.view.height } )

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.mouseScale = 1

	object:updateMouseOffset()

	return object
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

	self.view = Rect:new( view )
	self.scroll = Vec2:new( scroll )

	if self.scroll ~= oldScroll then
		self._parent:checkScrolling()

		self.gui.view:set( -self.scroll.x, -self.scroll.y, self.view.width, self.view.height )
		self:updateMouseOffset()

		if self.callback ~= nil then
			self.callback( self )
		end
	end

	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( self.framebuffer ),
		{ 0, 0, self.view.width, -self.view.height },
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
	function gui:PropertyList( bounds, text, texture, nPatchNormal, nPatchPressed, callback )
		return self:addElement( PropertyList:new( bounds, text, texture, nPatchNormal, nPatchPressed, callback ) )
	end
end

return PropertyList
