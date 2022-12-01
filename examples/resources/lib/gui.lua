util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )

-- NOTE!!! Work in progress! Do not use.

Gui = {
	ALING = {
		LEFT = 1,
		RIGHT = 2,
		CENTER = 3,
		TOP = 1,
		BOTTOM = 2,
	},
	CONTAINER = {
		HORIZONTAL = 1,
		VERTICAL = 2,
	},

	font = 0,
	fontSize = 30,
	textSpacing = 1,
	padding = 2,
	spacing = 4,

	_elements = {},
}

function Gui.process( mousePosition )
	for _, element in ipairs( Gui._elements ) do
		if element.notMouseOver ~= nil then
			element:notMouseOver()
		end
	end
	
	-- Go backwards on process check so we trigger the top most ui first and stop there.
	for i = #Gui._elements, 1, -1 do
		local element = Gui._elements[i]

		if element:isMouseOver( mousePosition ) and not element.disabled then
			if element.isClicked ~= nil then
				element:isClicked()
			end

			break
		end
	end
end

function Gui.draw()
	for _, element in ipairs( Gui._elements ) do
		if element.draw ~= nil and element.visible then
			-- //TODO Check here if needs scrissor mode.
			-- if element

			element:draw()
		end
	end
end

-- Label

Label = {}
Label.__index = Label

function Label:new( set )
    local o = {
		_ID = #Gui._elements + 1,
		bounds = set ~= nil and set.bounds ~= nil and set.bounds or Rect:new( 0, 0, 0, 0 ),
		font = set ~= nil and set.font ~= nil and set.font or Gui.font,
		text = set ~= nil and set.text ~= nil and set.text or "",
		fontSize = set ~= nil and set.fontSize ~= nil and set.fontSize or Gui.fontSize,
		textSpacing = set ~= nil and set.textSpacing ~= nil and set.textSpacing or Gui.textSpacing,
		color = set ~= nil and set.color ~= nil and set.color or BLACK,
		maxTextLen = set ~= nil and set.maxTextLen ~= nil and set.maxTextLen or nil,
		padding = set ~= nil and set.padding ~= nil and set.padding or Gui.padding,
		HAling = set ~= nil and set.HAling ~= nil and set.HAling or Gui.ALING.LEFT,
		VAling = set ~= nil and set.VAling ~= nil and set.VAling or Gui.ALING.BOTTOM,

		visible = set ~= nil and set.visible ~= nil and set.visible or true,
		disabled = set ~= nil and set.disabled ~= nil and set.disabled or false,
		drawBounds = set ~= nil and set.drawBounds ~= nil and set.drawBounds or false,
		
		_textRect = Rect:new( 0, 0, 0, 0 ),
		_visibilityBounds = nil,
		-- Callbacks.
		onMouseOver = set ~= nil and set.onMouseOver ~= nil and set.onMouseOver or nil,
		notMouseOver = set ~= nil and set.notMouseOver ~= nil and set.notMouseOver or nil,
		onClicked = set ~= nil and set.onClicked ~= nil and set.onClicked or nil,
	}
	setmetatable( o, self )

	o:setText( o.text ) -- To measure bounds.
	table.insert( Gui._elements, o )
    return o
end

function Label:setText( text )
	if self.maxTextLen ~= nil then
		self.text = text:sub( 1, self.maxTextLen )
	else
		self.text = text
	end

	local textSize = Vec2:new( RL_MeasureText( self.font, self.text, self.fontSize, self.textSpacing ) )

	-- Set bounds to text size if not given.
	if self.bounds.width == nil then
		self.bounds.width = textSize.x
	end
	if self.bounds.height == nil then
		self.bounds.height = textSize.y
	end

	-- Horizontal aling.
	if self.HAling == Gui.ALING.CENTER then
		self._textRect.x = self.bounds.width / 2 - textSize.x / 2
	elseif self.HAling == Gui.ALING.LEFT then
		self._textRect.x = self.padding
	elseif self.HAling == Gui.ALING.RIGHT then
		self._textRect.x = self.bounds.width - textSize.x - self.padding
	end
	-- Vertical aling.
	if self.VAling == Gui.ALING.CENTER then
		self._textRect.y = self.bounds.height / 2 - textSize.y / 2
	elseif self.VAling == Gui.ALING.TOP then
		self._textRect.y = self.padding
	elseif self.VAling == Gui.ALING.BOTTOM then
		self._textRect.y = self.bounds.height - textSize.y - self.padding
	end

	self._textRect.width = textSize.x
	self._textRect.height = textSize.y
end

function Label:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function Label:isMouseOver( mousePosition )
	local over = RL_CheckCollisionPointRec( mousePosition, self.bounds )

	if over and self._visibilityBounds ~= nil then
		over = RL_CheckCollisionPointRec( mousePosition, self._visibilityBounds )
	end

	if over and self.onMouseOver ~= nil then
		self:onMouseOver()
	end

	return over
end

function Label:isClicked()
	local clicked = RL_IsMouseButtonPressed( MOUSE_BUTTON_LEFT )

	if clicked and self.onClicked ~= nil then
		self:onClicked()
	end

	return clicked
end

function Label:draw()
	local usedScissor = false

	if self._visibilityBounds ~= nil then
		local rect = Rect:new( RL_GetCollisionRec( self.bounds, self._visibilityBounds ) )

		-- Use scissor mode only on partyally visible.
		if rect.width == 0 and rect.height == 0 then
			return
		elseif math.floor( rect.width ) ~= math.floor( self.bounds.width )
		or math.floor( rect.height ) ~= math.floor( self.bounds.height ) then
			usedScissor = true
			RL_BeginScissorMode( self._visibilityBounds )
		end
	end
	
	RL_DrawText( self.font, self.text, { self.bounds.x + self._textRect.x, self.bounds.y + self._textRect.y }, self.fontSize, self.textSpacing, self.color )
	
	if self.drawBounds then
		RL_DrawRectangleLines( self.bounds, self.color )
	end

	if usedScissor then
		RL_EndScissorMode()
	end

end

function Label:delete()
	table.remove( Gui._elements, self._ID )
end

function Label:set2Top()
	util.tableMove( Gui._elements, self._ID, 1, #Gui._elements )
end

function Label:set2Back()
	util.tableMove( Gui._elements, self._ID, 1, 1 )
end

-- Panel.

Panel = {}
Panel.__index = Panel

function Panel:new( set )
    local o = {
		_ID = #Gui._elements + 1,
		bounds = set ~= nil and set.bounds ~= nil and set.bounds or Rect:new( 0, 0, 0, 0 ),
		color = set ~= nil and set.color ~= nil and set.color or LIGHTGRAY,

		visible = set ~= nil and set.visible ~= nil and set.visible or true,
		disabled = set ~= nil and set.disabled ~= nil and set.disabled or false,
	}
	setmetatable( o, self )
	table.insert( Gui._elements, o )

    return o
end

function Panel:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function Panel:isMouseOver( mousePosition )
	return RL_CheckCollisionPointRec( mousePosition, self.bounds )
end

function Panel:draw()
	RL_DrawRectangle( self.bounds, self.color )
end

function Panel:delete()
	table.remove( Gui._elements, self._ID )
end

function Panel:set2Top()
	util.tableMove( Gui._elements, self._ID, 1, #Gui._elements )
end

function Panel:set2Back()
	util.tableMove( Gui._elements, self._ID, 1, 1 )
end

-- Container.

Container = {}
Container.__index = Container

function Container:new( set )
    local o = {
		_ID = #Gui._elements + 1,
		bounds = set ~= nil and set.bounds ~= nil and set.bounds or Rect:new( 0, 0, 0, 0 ),
		color = set ~= nil and set.color ~= nil and set.color or LIGHTGRAY,
		spacing = set ~= nil and set.spacing ~= nil and set.spacing or Gui.spacing,
		type = set ~= nil and set.type ~= nil and set.type or Gui.CONTAINER.VERTICAL,
		HAling = set ~= nil and set.HAling ~= nil and set.HAling or Gui.ALING.LEFT,
		VAling = set ~= nil and set.VAling ~= nil and set.VAling or Gui.ALING.TOP,

		visible = set ~= nil and set.visible ~= nil and set.visible or true,
		disabled = set ~= nil and set.disabled ~= nil and set.disabled or false,
		drawBounds = set ~= nil and set.drawBounds ~= nil and set.drawBounds or false,
		scrollable = set ~= nil and set.scrollable ~= nil and set.scrollable or false,
		
		cells = {},
		
		_visibilityBounds = nil, -- Will give this to it's children.
		_scrollRect = Rect:new( 0, 0, 0, 0 ),
	}
	setmetatable( o, self )
	table.insert( Gui._elements, o )
    return o
end

function Container:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function Container:isMouseOver( mousePosition )
	return RL_CheckCollisionPointRec( mousePosition, self.bounds )
end

function Container:add( cell )
	table.insert( self.cells, cell )

	self:update()

	if cell.update ~= nil then
		cell:update()
	end
end

function Container:scroll( pos )
	if not self.scrollable then
		return
	end

	self._scrollRect.x = util.clamp( pos.x, 0, self._scrollRect.width - self.bounds.width )
	self._scrollRect.y = util.clamp( pos.y, 0, self._scrollRect.height - self.bounds.height )
	-- self._scrollRect.x = pos.x
	-- self._scrollRect.y = pos.y

	self:update()
end

function Container:update()
	local pos = Vec2:new( self.bounds.x + self.spacing, self.bounds.y + self.spacing )

	if self.scrollable then
		self._visibilityBounds = self.bounds
		self._scrollRect.width = 0
		self._scrollRect.height = 0
	end

	for i, cell in ipairs( self.cells ) do
		if self._visibilityBounds ~= nil then
			cell._visibilityBounds = self._visibilityBounds
		end

		if self.type == Gui.CONTAINER.VERTICAL then
			if self.HAling == Gui.ALING.CENTER then
				pos.x = self.bounds.x + self.bounds.width / 2 - cell.bounds.width / 2
			elseif self.HAling == Gui.ALING.RIGHT then
				pos.x = self.bounds.x + self.bounds.width - cell.bounds.width - self.spacing
			end
			
			cell.bounds.x = pos.x - self._scrollRect.x
			cell.bounds.y = pos.y - self._scrollRect.y

			self._scrollRect.width = math.max( self._scrollRect.width, pos.x + cell.bounds.width + self.spacing - self.bounds.x )
			self._scrollRect.height = math.max( self._scrollRect.height, pos.y + cell.bounds.height + self.spacing - self.bounds.y )

			pos.y = pos.y + cell.bounds.height + self.spacing
		elseif self.type == Gui.CONTAINER.HORIZONTAL then
			if self.VAling == Gui.ALING.CENTER then
				pos.y = self.bounds.y + self.bounds.height / 2 - cell.bounds.height / 2
			elseif self.VAling == Gui.ALING.BOTTOM then
				pos.y = self.bounds.y + self.bounds.height - cell.bounds.height - self.spacing
			end

			cell.bounds.x = pos.x - self._scrollRect.x
			cell.bounds.y = pos.y - self._scrollRect.y

			self._scrollRect.width = math.max( self._scrollRect.width, pos.x + cell.bounds.width + self.spacing - self.bounds.x )
			self._scrollRect.height = math.max( self._scrollRect.height, pos.y + cell.bounds.height + self.spacing - self.bounds.y )

			pos.x = pos.x + cell.bounds.width + self.spacing
		end

		if cell.update ~= nil then
			cell:update()
		end
	end
end

function Container:draw()
	if self.drawBounds then
		RL_DrawRectangleLines( self.bounds, self.color )
		RL_DrawRectangleLines( {
			self.bounds.x - self._scrollRect.x,
			self.bounds.y - self._scrollRect.y,
			self._scrollRect.width,
			self._scrollRect.height,
		}, RED )
	end
end

function Container:delete()
	table.remove( Gui._elements, self._ID )
end

--Assingments.

Gui.label = Label
Gui.panel = Panel
Gui.container = Container

return Gui
