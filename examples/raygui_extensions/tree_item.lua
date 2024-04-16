local TreeItem = {}
TreeItem.__index = TreeItem

function TreeItem:new( bounds, text, callbacks, styles, tooltip )
	local object = setmetatable( {}, self )
	object._gui = nil

	object.spacing = 4 -- Between controls.

	object.bounds = bounds:clone()
	object.text = text
	object.callbacks = callbacks -- select, open.

	object.controls = {}
	
	object.active = false
	object.open = false -- Show controls.
	object.visible = true
	object.disabled = false
	object.styles = styles
	object.tooltip = tooltip

	object._depth = 0
	object._indentation = 0
	object._id = 0 -- Id in treeView.
	object._parent = nil
	object._childId = 0 -- Id in parent controls.

	return object
end

function TreeItem:update()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function TreeItem:setOpenIcon()
	if self.open then
		return RL.GuiIconText( 120, "" )
	else
		return RL.GuiIconText( 119, "" )
	end
end

function TreeItem:draw()
	local buttonRect = Rect:new( 0, 0, 0, 0 )
	local hasContainer = 0 < #self.controls
	local lineCol = RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.LINE_COLOR ) )

	if hasContainer then
		buttonRect:set( self.bounds.x, self.bounds.y, self.bounds.height, self.bounds.height )
	end
	-- Draw indentation lines.
	for i = 0, self._depth - 1 do
		RL.DrawRectangle( {
			self.bounds.x - i * self._indentation - self._indentation / 2,
			self.bounds.y - self.spacing,
			1,
			self.bounds.height + self.spacing * 2
		}, lineCol )
	end

	local toggleRect = Rect:new( 
		self.bounds.x + buttonRect.width,
		self.bounds.y,
		self.bounds.width - buttonRect.width,
		self.bounds.height
	)
	local oldActive = self.active
	_, self.active = RL.GuiToggle( toggleRect, self.text, self.active )

	if self.callbacks.select and oldActive ~= self.active then
		self.callbacks.select( self )
	end

	if hasContainer then
		local pressed = RL.GuiLabelButton( buttonRect, self:setOpenIcon() )

		if self.callbacks.open and 0 < pressed then
			self.open = not self.open
			self.callbacks.open( self )
		end
	end
end

function TreeItem:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function TreeItem:register( gui )
	function gui:TreeItem( bounds, text, callbacks, styles, tooltip )
		return self:addControl( TreeItem:new( bounds, text, callbacks, styles, tooltip ) )
	end
end

return TreeItem
