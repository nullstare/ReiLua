util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )

-- NOTE!!! Work in progress! Do not use.

Gui = {
	ALING = {
		NONE = 0,
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
	SHAPE = {
		LINE = 0,
		CIRCLE = 1,
		CIRCLE_LINES = 2,
		ELLIPSE = 3,
		ELLIPSE_LINES = 4,
		RECTANGLE = 5,
		RECTANGLE_LINES = 6,
		RECTANGLE_ROUNDED = 7,
		RECTANGLE_ROUNDED_LINES = 8,
	},

	font = 0,
	fontSize = 30,
	padding = 2,
	spacing = 4,
	scrollbarWidth = 8,
	scrollAmount = 10,

	_elements = {},
	_mousePos = Vec2:new( 0, 0 ), -- Last mouse position that was passed to Gui.process.
	heldCallback = nil,
}

local function setProperty( set, property, default )
	if set ~= nil and set[ property ] ~= nil then
		return set[ property ]
	end

	return default
end

function Gui.process( mousePosition )
	local mouseWheel = RL_GetMouseWheelMove()

	Gui._mousePos = mousePosition

	for _, element in ipairs( Gui._elements ) do
		if element.notMouseOver ~= nil then
			element:notMouseOver()
		end
		-- Mousewheel scrolling. Note this would be detected through other elements.
		if mouseWheel ~= 0 and element.scrollable and RL_CheckCollisionPointRec( mousePosition, element.bounds ) then
			local pos = Vec2:new( element._scrollRect.x, element._scrollRect.y )
			local scrollVec = Vec2:new( 0, element.scrollAmount * mouseWheel )

			if RL_IsKeyDown( KEY_LEFT_SHIFT ) then
				scrollVec = Vec2:new( element.scrollAmount * mouseWheel, 0 )
			end

			element:scroll( pos - scrollVec )
		end
	end
	
	if Gui.heldCallback ~= nil then
		if RL_IsMouseButtonDown( MOUSE_BUTTON_LEFT ) then
			Gui.heldCallback()
		else
			Gui.heldCallback = nil
		end

		return
	end
	-- Go backwards on process check so we trigger the top most ui first and stop there.
	for i = #Gui._elements, 1, -1 do
		local element = Gui._elements[i]

		if element.isMouseOver ~= nil and element:isMouseOver( mousePosition ) and not element.disabled then
			if RL_IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) and element.onClicked ~= nil then
				element:onClicked()
			end
			if RL_IsMouseButtonDown( MOUSE_BUTTON_LEFT ) and element.onHeld ~= nil then
				element:onHeld()
			end

			break
		end
	end
end

function Gui.draw()
	for _, element in ipairs( Gui._elements ) do
		if element.draw ~= nil and element.visible then
			element:draw()
		end
	end
end

-- Items.

-- Text.

Text = {}
Text.__index = Text

function Text:new( set )
    local o = {
		bounds = Rect:new( 0, 0, 0, 0 ),
		HAling = setProperty( set, "HAling", Gui.ALING.LEFT ),
		VAling = setProperty( set, "VAling", Gui.ALING.BOTTOM ),

		font = setProperty( set, "font", Gui.font ),
		text = setProperty( set, "text", "" ),
		fontSize = setProperty( set, "fontSize", Gui.fontSize ),
		spacing = setProperty( set, "spacing", Gui.spacing ),
		color = setProperty( set, "color", Color:new( BLACK ) ),
		maxTextLen = setProperty( set, "maxTextLen", nil ),

		visible = setProperty( set, "visible", true ),
		_parent = nil,
	}
	setmetatable( o, self )
	o:set( o.text ) -- To measure bounds.

    return o
end

function Text:set( text )
	if self.maxTextLen ~= nil then
		self.text = text:sub( 1, self.maxTextLen )
	else
		self.text = text
	end

	local textSize = Vec2:new( RL_MeasureText( self.font, self.text, self.fontSize, self.spacing ) )

	self.bounds.width = textSize.x
	self.bounds.height = textSize.y
end

function Text:draw()
	if not self.visible then
		return
	end

	RL_DrawText( self.font, self.text, { self.parent.bounds.x + self.bounds.x, self.parent.bounds.y + self.bounds.y }, self.fontSize, self.spacing, self.color )
end

-- Texture.

Texture = {}
Texture.__index = Texture

function Texture:new( set )
    local o = {
		bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) ),
		HAling = setProperty( set, "HAling", Gui.ALING.LEFT ),
		VAling = setProperty( set, "VAling", Gui.ALING.CENTER ),

		texture = setProperty( set, "texture", nil ),
		source = setProperty( set, "source", Rect:new( 0, 0, 0, 0 ) ),
		origin = setProperty( set, "origin", Vec2:new( 0, 0 ) ),
		rotation = setProperty( set, "rotation", 0 ),
		color = setProperty( set, "color", Color:new( WHITE ) ),

		visible = setProperty( set, "visible", true ),
		_parent = nil,
	}

	setmetatable( o, self )
	o:set( o.texture ) -- To measure bounds.

    return o
end

function Texture:set( texture )
	if texture == nil then
		return
	end

	local texSize = Vec2:new( RL_GetTextureSize( texture ) )

	if self.bounds.width == 0 or self.bounds.height == 0 then
		self.bounds.width = texSize.x
		self.bounds.height = texSize.y
	end
	if self.source.width == 0 or self.source.height == 0 then
		self.source.width = texSize.x
		self.source.height = texSize.y
	end

	self.texture = texture
end

function Texture:draw()
	if not self.visible or self.texture == nil then
		return
	end

	local dst = {
		self.bounds.x + self.parent.bounds.x,
		self.bounds.y + self.parent.bounds.y,
		self.bounds.width,
		self.bounds.height
	}

	RL_DrawTexturePro( self.texture, self.source, dst, self.origin, self.rotation, self.color )
end

-- Shape.

Shape = {}
Shape.__index = Shape

function Shape:new( set )
    local o = {
		bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) ),
		HAling = setProperty( set, "HAling", Gui.ALING.LEFT ),
		VAling = setProperty( set, "VAling", Gui.ALING.CENTER ),

		shape = setProperty( set, "shape", Gui.SHAPE.RECTANGLE ),
		-- Line.
		startPos = setProperty( set, "startPos", Vec2:new( 0, 0 ) ),
		endPos = setProperty( set, "endPos", Vec2:new( 0, 0 ) ),
		thickness = setProperty( set, "thickness", 3.0 ),
		-- Circle.
		center = setProperty( set, "center", Vec2:new( 0, 0 ) ),
		radius = setProperty( set, "radius", 0 ),
		-- Ellipse.
		radiusH = setProperty( set, "radiusH", 0 ),
		radiusV = setProperty( set, "radiusV", 0 ),
		-- Rectangle rounded.
		roundness = setProperty( set, "roundness", 1 ),
		segments = setProperty( set, "segments", 4 ),

		color = setProperty( set, "color", Color:new( WHITE ) ),

		visible = setProperty( set, "visible", true ),
		_parent = nil,
	}
	setmetatable( o, self )
	o:set( o.shape )

    return o
end

-- Set to default shape values.
function Shape:set( shape )
	if shape == Gui.SHAPE.LINE and self.startPos == Vec2:new( 0, 0 ) and self.endPos == Vec2:new( 0, 0 ) then
		self.startPos = Vec2:new( 0, self.bounds.height / 2 )
		self.endPos = Vec2:new( self.bounds.width, self.bounds.height / 2 )
	elseif ( shape == Gui.SHAPE.CIRCLE or shape == Gui.SHAPE.CIRCLE_LINES ) and self.radius == 0 then
		self.center = Vec2:new( self.bounds.width / 2, self.bounds.height / 2 )
		self.radius = math.min( self.bounds.width, self.bounds.height ) / 2
	elseif ( shape == Gui.SHAPE.ELLIPSE or shape == Gui.SHAPE.ELLIPSE_LINES ) and self.radiusH == 0 and self.radiusV == 0 then
		self.center = Vec2:new( self.bounds.width / 2, self.bounds.height / 2 )
		self.radiusH = self.bounds.width / 2
		self.radiusV = self.bounds.height / 2
	end
end

function Shape:draw()
	if not self.visible then
		return
	end

	local pos = Vec2:new( self.parent.bounds.x, self.parent.bounds.y )

	if self.shape == Gui.SHAPE.LINE then
		RL_DrawLine( self.startPos + pos, self.endPos + pos, self.thickness, self.color )
	elseif self.shape == Gui.SHAPE.CIRCLE then
		RL_DrawCircle( self.center + pos, self.radius, self.color )
	elseif self.shape == Gui.SHAPE.CIRCLE_LINES then
		RL_DrawCircleLines( self.center + pos, self.radius, self.color )
	elseif self.shape == Gui.SHAPE.ELLIPSE then
		RL_DrawEllipse( self.center + pos, self.radiusH, self.radiusV, self.color )
	elseif self.shape == Gui.SHAPE.ELLIPSE_LINES then
		RL_DrawEllipseLines( self.center + pos, self.radiusH, self.radiusV, self.color )
	elseif self.shape == Gui.SHAPE.RECTANGLE then
		RL_DrawRectangle( { self.bounds.x + pos.x, self.bounds.y + pos.y, self.bounds.width, self.bounds.height }, self.color )
	elseif self.shape == Gui.SHAPE.RECTANGLE_LINES then
		RL_DrawRectangleLines( { self.bounds.x + pos.x, self.bounds.y + pos.y, self.bounds.width, self.bounds.height }, self.color )
	elseif self.shape == Gui.SHAPE.RECTANGLE_ROUNDED then
		RL_DrawRectangleRounded( { self.bounds.x + pos.x, self.bounds.y + pos.y, self.bounds.width, self.bounds.height }, self.roundness, self.segments, self.color )
	elseif self.shape == Gui.SHAPE.RECTANGLE_ROUNDED_LINES then
		RL_DrawRectangleRoundedLines( { self.bounds.x + pos.x, self.bounds.y + pos.y, self.bounds.width, self.bounds.height }, self.roundness, self.segments, self.thickness, self.color )
	end
end

-- End of items.

-- Element.

Element = {}
Element.__index = Element

function Element:new( set )
    local o = {
		_ID = #Gui._elements + 1,
		bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) ),
		padding = setProperty( set, "padding", Gui.padding ),
		visible = setProperty( set, "visible", true ),
		disabled = setProperty( set, "disabled", false ),
		drawBounds = setProperty( set, "drawBounds", false ),
		color = setProperty( set, "color", Color:new( GRAY ) ),

		items = {},
		
		_visibilityBounds = nil,
		-- Callbacks.
		onMouseOver = setProperty( set, "onMouseOver", nil ),
		notMouseOver = setProperty( set, "notMouseOver", nil ),
		onClicked = setProperty( set, "onClicked", nil ),
		onHeld = setProperty( set, "onHeld", nil ),
	}
	setmetatable( o, self )
	table.insert( Gui._elements, o )

    return o
end

function Element:update()
	-- Horizontal aling.
	for _, item in ipairs( self.items ) do
		if item.HAling == Gui.ALING.CENTER then
			item.bounds.x = self.bounds.width / 2 - item.bounds.width / 2
		elseif item.HAling == Gui.ALING.LEFT then
			item.bounds.x = self.padding
		elseif item.HAling == Gui.ALING.RIGHT then
			item.bounds.x = self.bounds.width - item.bounds.width - self.padding
		end
		-- Vertical aling.
		if item.VAling == Gui.ALING.CENTER then
			item.bounds.y = self.bounds.height / 2 - item.bounds.height / 2
		elseif item.VAling == Gui.ALING.TOP then
			item.bounds.y = self.padding
		elseif item.VAling == Gui.ALING.BOTTOM then
			item.bounds.y = self.bounds.height - item.bounds.height - self.padding
		end
	end
end

function Element:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
	self:update()
end

function Element:add( item )
	table.insert( self.items, item )
	item.parent = self
	self:update()
end

function Element:isMouseOver( mousePosition )
	local over = RL_CheckCollisionPointRec( mousePosition, self.bounds )

	if over and self._visibilityBounds ~= nil then
		over = RL_CheckCollisionPointRec( mousePosition, self._visibilityBounds )
	end

	if over and self.onMouseOver ~= nil then
		self:onMouseOver()
	end

	return over
end

function Element:draw()
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
	
	if self.drawBounds then
		RL_DrawRectangle( self.bounds, self.color )
	end

	for _, item in ipairs( self.items ) do
		item:draw()
	end

	if usedScissor then
		RL_EndScissorMode()
	end

end

function Element:delete()
	table.remove( Gui._elements, self._ID )
end

function Element:set2Top()
	util.tableMove( Gui._elements, self._ID, 1, #Gui._elements )
end

function Element:set2Back()
	util.tableMove( Gui._elements, self._ID, 1, 1 )
end

-- Container.

Container = {}
Container.__index = Container

function Container:new( set )
    local o = {
		_ID = #Gui._elements + 1,
		bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) ),
		spacing = setProperty( set, "spacing", Gui.spacing ),
		type = setProperty( set, "type", Gui.CONTAINER.VERTICAL ),
		HAling = setProperty( set, "HAling", Gui.ALING.LEFT ),
		VAling = setProperty( set, "VAling", Gui.ALING.TOP ),

		visible = setProperty( set, "visible", true ),
		disabled = setProperty( set, "disabled", false ),
		-- drawBounds = setProperty( set, "drawBounds", false ),
		-- color = setProperty( set, "color", Color:new( DARKGRAY ) ),
		scrollable = setProperty( set, "scrollable", false ),
		showScrollbar = setProperty( set, "showScrollbar", false ),
		scrollbarWidth = setProperty( set, "scrollbarWidth", Gui.scrollbarWidth ),
		scrollAmount = setProperty( set, "scrollAmount", Gui.scrollAmount ), -- When using mouse scroll.
		
		cells = {},
		
		_visibilityBounds = nil, -- Will give this to it's children.
		_scrollRect = Rect:new( 0, 0, 0, 0 ),
		_VScrollbarRect = Rect:new( 0, 0, 0, 0 ),
		_HScrollbarRect = Rect:new( 0, 0, 0, 0 ),

		_VScrollbar = nil,
		_HScrollbar = nil,
	}
	setmetatable( o, self )
	table.insert( Gui._elements, o )

    return o
end

function Container:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:update()
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

	self:update()
end

function Container:mouseScroll( v )
	local handleBounds = Vec2:new( self._HScrollbar.items[1].bounds.width, self._VScrollbar.items[1].bounds.height )
	local mousePos = Gui._mousePos - Vec2:new( self.bounds.x, self.bounds.y ) - Vec2:new( handleBounds.x / 2, handleBounds.y / 2 )
	local ratio = Vec2:new( self._scrollRect.width / self.bounds.width, self._scrollRect.height / self.bounds.height )

	mousePos = mousePos * ratio * v

	if v.x == 0 then
		mousePos.x = self._scrollRect.x
	elseif v.y == 0 then
		mousePos.y = self._scrollRect.y
	end

	self:scroll( mousePos )
end

-- function Container:isMouseOver( mousePosition )
-- 	-- print( "Over container" )
-- 	local over = RL_CheckCollisionPointRec( mousePosition, self.bounds )

-- 	if over and self._visibilityBounds ~= nil then
-- 		over = RL_CheckCollisionPointRec( mousePosition, self._visibilityBounds )
-- 		print( "Over container" )
-- 	end

-- 	-- if over and self.onMouseOver ~= nil then
-- 	-- 	self:onMouseOver()
-- 	-- end

-- 	-- return over
-- end

function Container:updateScrollbar()
	if self.bounds.height < self._scrollRect.height then
		self._VScrollbar.bounds.width = self.scrollbarWidth
		self._VScrollbar.bounds.height = self.bounds.height
		self._VScrollbar.bounds.x = self.bounds.x + self.bounds.width
		self._VScrollbar.bounds.y = self.bounds.y
		-- Handle.
		self._VScrollbar.items[1].bounds.width = self.scrollbarWidth
		self._VScrollbar.items[1].bounds.height = self.bounds.height / self._scrollRect.height * self.bounds.height
		self._VScrollbar.items[1].bounds.y = self._scrollRect.y / self._scrollRect.height * self.bounds.height
	end
	
	if self.bounds.width < self._scrollRect.width then
		self._HScrollbar.bounds.width = self.bounds.width
		self._HScrollbar.bounds.height = self.scrollbarWidth
		self._HScrollbar.bounds.x = self.bounds.x
		self._HScrollbar.bounds.y = self.bounds.y + self.bounds.height
		-- Handle.
		self._HScrollbar.items[1].bounds.width = self.bounds.width / self._scrollRect.width * self.bounds.width
		self._HScrollbar.items[1].bounds.height = self.scrollbarWidth
		self._HScrollbar.items[1].bounds.x = self._scrollRect.x / self._scrollRect.width * self.bounds.width
	end
end

function Container:update()
	local pos = Vec2:new( self.bounds.x + self.spacing, self.bounds.y + self.spacing )

	if self.scrollable then
		self._visibilityBounds = self.bounds
		self._scrollRect.width = 0
		self._scrollRect.height = 0

		-- Create scrollbars if can scroll.

		if self._VScrollbar == nil then
			self._VScrollbar = Element:new( {
				padding = 0,
				drawBounds = true,
				color = Color:new( GRAY ),
				onClicked = function() Gui.heldCallback = function() self:mouseScroll( Vec2:new( 0, 1 ) ) end end,
			} )

			self._VScrollbar:add( Gui.shape:new( {
				HAling = Gui.ALING.CENTER,
				VAling = Gui.ALING.NONE,
				bounds = Rect:new( 0, 0, 0, 0 ),
				shape = Gui.SHAPE.RECTANGLE_ROUNDED,
				color = Color:new( LIGHTGRAY ),
			} ) )
		end

		if self._HScrollbar == nil then
			self._HScrollbar = Element:new( {
				padding = 0,
				drawBounds = true,
				color = Color:new( GRAY ),
				onClicked = function() Gui.heldCallback = function() self:mouseScroll( Vec2:new( 1, 0 ) ) end end,
			} )

			self._HScrollbar:add( Gui.shape:new( {
				HAling = Gui.ALING.NONE,
				VAling = Gui.ALING.CENTER,
				bounds = Rect:new( 0, 0, 0, 0 ),
				shape = Gui.SHAPE.RECTANGLE_ROUNDED,
				color = Color:new( LIGHTGRAY ),
			} ) )
		end
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

	if self.showScrollbar then
		self:updateScrollbar()
	end
end

function Container:draw()
	-- if self.drawBounds then
		-- RL_DrawRectangle( self.bounds, self.color )
		-- RL_DrawRectangleLines( {
		-- 	self.bounds.x - self._scrollRect.x,
		-- 	self.bounds.y - self._scrollRect.y,
		-- 	self._scrollRect.width,
		-- 	self._scrollRect.height,
		-- }, RED )
	-- end
end

function Container:delete()
	table.remove( Gui._elements, self._ID )
end

--Assingments.

Gui.text = Text
Gui.texture = Texture
Gui.shape = Shape

Gui.element = Element
Gui.container = Container

return Gui
