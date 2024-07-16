local TreeView = {}
TreeView.__index = TreeView

TreeView.SINGLE_SELECT = 0
TreeView.MULTI_SELECT = 1
TreeView.RANGE_SELECT = 2

TreeView.MOVE_ITEM_NONE = 0
TreeView.MOVE_ITEM_IN = 1
TreeView.MOVE_ITEM_UP = 2
TreeView.MOVE_ITEM_DOWN = 3

function TreeView:new( bounds, text, callbacks, styles, tooltip )
    local object = setmetatable( {}, self )
	object._gui = nil

	object.padding = 4 -- Content edges.
	object.spacing = 4 -- Between controls.
	object.indentation = 14 -- Indentation for one depth level.

    object.bounds = bounds:clone()
    object.text = text
    object.scroll = Vector2:new( 0, 0 )
	object.view = Rectangle:new( 0, 0, 0, 0 )
    object.callbacks = callbacks -- select, grab, drag.
	object.styles = styles
	object.tooltip = tooltip

	object.gui = Raygui:new() -- Contains full independent gui system.
	object.controls = {}

	-- Set in setSize.
	-- object.framebufferSize = nil
	-- object.framebuffer = nil
	object.defaultControlSize = nil

	object.visible = true
	object.disabled = false
	object.draggable = true
	object.allowMove = true
	object.allowMultiselect = true
	object.defaultControlHeight = 22
	object.mouseScale = 1 -- Set this if drawing in different size to render texture for example.

	object.selectedItems = {}

	object:setSize( Vector2:new( object.bounds.width, object.bounds.height ) )

	object._forceCheckScroll = false
	object._posY = 0 -- In control list update.
	object._curDepth = 0 -- Current indentation.
	object._curId = 0 -- Running number to give id's for controls.
	object._idRange = { 1, 1 }
	object._lastActiveItem = nil
	object._clickedItem = nil
	object._movingItem = object.MOVE_ITEM_NONE

	object:updateMouseOffset()

	return object
end

function TreeView:getDefaultBounds()
	return Rectangle:new( self.padding, self.padding, self.defaultControlSize.x, self.defaultControlSize.y )
end

local function getControlBounds( control )
	return control.viewBounds or control.focusBounds or control.bounds
end

function TreeView:updateControl( control )
	control.bounds = self:getDefaultBounds()
	control._depth = self._curDepth
	control._indentation = self.indentation
	control._id = self._curId
	self._curId = self._curId + 1

	if control.visible then
		control:setPosition( Vector2:new( control.bounds.x, self._posY ) )
		local bounds = getControlBounds( control )

		bounds.x = bounds.x + self._curDepth * self.indentation
		bounds.width = bounds.width - self._curDepth * self.indentation

		if not control._noYAdvance then
			self._posY = self._posY + bounds.height + self.spacing
		end
		self.content = self.content:fit( bounds )
	end

	if 0 < #control.controls then
		self._curDepth = self._curDepth + 1

		for i, groupControl in ipairs( control.controls ) do
			groupControl.visible = control.open
			groupControl._parent = control
			groupControl._childId = i

			if not control.open and 0 < #control.controls then
				groupControl.open = false
				groupControl.active = false
			end

			self:updateControl( groupControl )
		end

		self._curDepth = self._curDepth - 1
	end
end

function TreeView:updateContent()
	self._posY = self.padding
	self._curId = 1

	self.content.width = 0
	self.content.height = 0

	for i, control in ipairs( self.controls ) do
		control._parent = nil -- Sets parent in updateControl if any.
		control._childId = i
		self:updateControl( control )
	end
	self.content:set(
		0, 0,
		self.content.width + self.padding,
		self.content.height + self.padding
	)
	self._forceCheckScroll = true
end

function TreeView:addItem( name, group )
	local control = self.gui:TreeItem(
		self:getDefaultBounds(),
		name,
		{ -- Callbacks.
			open = function( this ) self:updateContent() end,
			select = function( this ) self:itemSelect( this ) end,
		},
		{ -- Styles.
			properties = {
				{ RL.TOGGLE, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT },
				{ RL.TOGGLE, RL.BASE_COLOR_NORMAL, RL.ColorToInt( RL.BLANK ) },
				{ RL.TOGGLE, RL.BORDER_COLOR_NORMAL, RL.ColorToInt( RL.BLANK ) },
			}
		}
	)
	if group ~= nil then
		table.insert( group.controls, control )
	else
		table.insert( self.controls, control )
	end

	self:updateContent()

	return control
end

function TreeView:checkItem( controls, item, mode )
	for _, control in ipairs( controls ) do
		if mode == self.SINGLE_SELECT and control ~= item then
			control.active = false
		end
		if 0 < #control.controls then
			self:checkItem( control.controls, item, mode )
		end
		if mode == self.RANGE_SELECT and control.visible
		and self._idRange[1] <= control._id and control._id <= self._idRange[2] then
			control.active = true
		end
		if control.active then
			table.insert( self.selectedItems, control )
		end
	end
end

-- Check if trying to move parent to child.
function TreeView:isChild( item, newParent )
	local to = newParent

	while to ~= nil do
		to = to._parent

		if item == to then
			return true
		end
	end

	return false
end

function TreeView:itemSelect( item )
	-- Item move.

	local moveItems = {}

	if self.allowMove and self._movingItem ~= self.MOVE_ITEM_NONE then

		for i = #self.selectedItems, 1, -1 do
			local moveItem = self.selectedItems[i]

			if moveItem ~= item and not self:isChild( moveItem, item ) then
				local parentControls = self.controls

				if moveItem._parent ~= nil then
					parentControls = moveItem._parent.controls
				end

				table.insert( moveItems, table.remove( parentControls, moveItem._childId ) )
			end
			
			moveItem.active = false
		end

		for _, moveItem in ipairs( moveItems ) do
			local newParentControls = self.controls

			if item._parent ~= nil then
				newParentControls = item._parent.controls
			end

			local offset = 0

			if moveItem._parent == item._parent and moveItem._childId < item._childId then
				offset = -#moveItems
			end

			if self._movingItem == self.MOVE_ITEM_IN then
				table.insert( item.controls, 1, moveItem )
			elseif self._movingItem == self.MOVE_ITEM_UP then
				local pos = RL.Clamp( item._childId + offset, 1, #newParentControls + 1 )
				table.insert( newParentControls, pos, moveItem )
			elseif self._movingItem == self.MOVE_ITEM_DOWN then
				local pos = RL.Clamp( item._childId + offset + 1, 1, #newParentControls + 1 )
				table.insert( newParentControls, pos, moveItem )
			end
		end

		item.active = false
		self._movingItem = self.MOVE_ITEM_NONE
		self:updateContent()

		return
	end

	-- Item select.

	local mode = self.SINGLE_SELECT

	if self.allowMultiselect then
		if RL.IsKeyDown( RL.KEY_LEFT_CONTROL ) or RL.IsKeyDown( RL.KEY_RIGHT_CONTROL ) then
			mode = self.MULTI_SELECT
		elseif RL.IsKeyDown( RL.KEY_LEFT_SHIFT ) or RL.IsKeyDown( RL.KEY_RIGHT_SHIFT ) then
			mode = self.RANGE_SELECT
		end
	end

	if self._lastActiveItem ~= nil then
		self._idRange = { math.min( self._lastActiveItem._id, item._id ), math.max( self._lastActiveItem._id, item._id )  }
	end
	self.selectedItems = {}
	self:checkItem( self.controls, item, mode )

	if mode ~= self.RANGE_SELECT then
		self._lastActiveItem = item -- Old clicked.
	end

	if self.callbacks.select ~= nil then
		self.callbacks.select( self.selectedItems )
	end
end

function TreeView:update()
	local mousePos = Vector2:tempT( RL.GetMousePosition() )
	local mouseInView = self.view:checkCollisionPoint( mousePos )

	if not mouseInView then
		self.gui.locked = true
	else
		self.gui.locked = false
	end

	self.gui:update()

    return self._gui:drag( self )
end

function TreeView:draw()
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
	end

	local mousePos = Vector2:tempT( RL.GetMousePosition() )
	local guiMousePos = mousePos + self.gui.mouseOffset
	local mouseInView = self.view:checkCollisionPoint( mousePos )

	local mouseInClickedItem = false

	if RL.IsMouseButtonPressed( RL.MOUSE_BUTTON_LEFT ) then
		if 0 < self.gui.focused and mouseInView and self.gui.controls[ self.gui.focused ].active then
			self._clickedItem = self.gui.controls[ self.gui.focused ]
		else
			self._clickedItem = nil
		end
	end

	if self._clickedItem ~= nil then
		mouseInClickedItem = self._clickedItem.bounds:checkCollisionPoint( guiMousePos )
	end

	-- Lock if this gui not focused.
	self.gui.locked = not ( self._gui.controls[ self._gui.focused ] == self ) or self._gui.locked

	RL.BeginScissorMode( self.view )
		RL.rlPushMatrix()
		RL.rlTranslatef( { RL.Round( self.view.x + self.scroll.x ), RL.Round( self.view.y + self.scroll.y ), 0 } )

		self.gui:draw()

		if self.allowMove and RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) and self._clickedItem ~= nil
		and not mouseInClickedItem and 0 < self.gui.focused then
			local focusBounds = self.gui.controls[ self.gui.focused ].bounds
			local relY = ( guiMousePos.y - focusBounds.y ) / focusBounds.height

			if relY <= 0.35 then
				RL.DrawLine(
					{ focusBounds.x, focusBounds.y },
					{ focusBounds.x + focusBounds.width, focusBounds.y },
					6, RL.RED
				)
				self._movingItem = self.MOVE_ITEM_UP
			elseif 0.65 <= relY then
				RL.DrawLine(
					{ focusBounds.x, focusBounds.y + focusBounds.height },
					{ focusBounds.x + focusBounds.width, focusBounds.y + focusBounds.height },
					6, RL.RED
				)
				self._movingItem = self.MOVE_ITEM_DOWN
			else
				RL.DrawRectangleLines( focusBounds, RL.RED )
				self._movingItem = self.MOVE_ITEM_IN
			end
		elseif RL.IsMouseButtonReleased( RL.MOUSE_BUTTON_LEFT ) then
			self._clickedItem = nil
			self._movingItem = self.MOVE_ITEM_NONE
		end

		RL.rlPopMatrix()
	RL.EndScissorMode()
end

function TreeView:updateMouseOffset()
	self.gui.mouseOffset = Vector2:new( -self.view.x - self.scroll.x, -self.view.y - self.scroll.y ):scale( self.mouseScale )
end

function TreeView:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:updateMouseOffset()
end

function TreeView:setSize( size )
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

function TreeView:register( gui )
	function gui:TreeView( bounds, text, callbacks, styles, tooltip )
		return self:addControl( TreeView:new( bounds, text, callbacks, styles, tooltip ) )
	end
end

return TreeView
