util = require( "utillib" )
Rect = require( "rectangle" )
Vec2 = require( "vector2" )
Color = require( "color" )

-- NOTE!!! Work in progress! Do not use.

--[[
	To add repeat inputs to the keys pressed buffer, you could add GLFW_REPEAT in railib rcore.c in function "KeyCallback" by changing:

	if ((CORE.Input.Keyboard.keyPressedQueueCount < MAX_KEY_PRESSED_QUEUE) && (action == GLFW_PRESS))
	To
	if ((CORE.Input.Keyboard.keyPressedQueueCount < MAX_KEY_PRESSED_QUEUE) && (action == GLFW_PRESS || action == GLFW_REPEAT))

	Now GLFW_REPEAT can be read by "RL_GetKeyPressed".
]]

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

	mouseButton = MOUSE_BUTTON_LEFT,
	font = 0,
	fontSize = 30,
	padding = 2,
	spacing = 4,
	scrollbarWidth = 8,
	scrollAmount = 10,

	_cells = {},
	_mousePos = Vec2:new( 0, 0 ), -- Last mouse position that was passed to Gui.process.
	_heldCallback = nil,
	_inputElement = nil,
	_inputItem = nil, -- Must be type Text.
}

local readyToUnfocusInput = false -- Guard to not unfocus input immediately.

local function setProperty( set, property, default )
	if set ~= nil and set[ property ] ~= nil then
		return set[ property ]
	end

	return default
end

function Gui.setInputFocus( element, itemID )
	itemID = itemID or 1

	Gui._inputElement = element
	Gui._inputItem = element.items[ itemID ]

	if element.inputFocus ~= nil then
		element.inputFocus()
	end

	readyToUnfocusInput = false
end

function Gui.inputUnfocus()
	if Gui._inputElement ~= nil then
		Gui._inputElement.inputUnfocus()
	end

	Gui._inputElement = nil
	Gui._inputItem = nil
end

function Gui.getId( cell )
	for id, c in ipairs( Gui._cells ) do
		if cell == c then
			return id
		end
	end

	return nil
end

function Gui.delete( cell )
	local id = Gui.getId( cell )

	if id ~= nil then
		table.remove( Gui._cells, id )
	end
end

function Gui.set2Top( cell )
	util.tableMove( Gui._cells, Gui.getId( cell ), 1, #Gui._cells )
end

function Gui.set2Back( cell )
	util.tableMove( Gui._cells, Gui.getId( cell ), 1, 1 )
end

function Gui.process( mousePosition )
	local mouseWheel = RL_GetMouseWheelMove()

	Gui._mousePos = mousePosition

	if Gui._heldCallback ~= nil then
		if RL_IsMouseButtonDown( Gui.mouseButton ) then
			Gui._heldCallback()
		else
			Gui._heldCallback = nil
		end

		return
	end

	local foundFirst = false
	
	-- Go backwards on process check so we trigger the top most ui first and stop there.
	for i = #Gui._cells, 1, -1 do
		local cell = Gui._cells[i]

		if cell ~= nil then
			if not foundFirst and cell.isMouseOver ~= nil and cell:isMouseOver( mousePosition ) and not cell.disabled then
				-- On clicked.
				if RL_IsMouseButtonPressed( Gui.mouseButton ) and cell.onClicked ~= nil then
					cell:onClicked()
				end
				-- On held.
				if RL_IsMouseButtonDown( Gui.mouseButton ) and cell.onHeld ~= nil then
					cell:onHeld()
				end
				-- Mouse wheel scrolling.
				if mouseWheel ~= 0 then
					if cell._parent ~= nil and cell._parent.scrollable then
						cell = cell._parent
					end
	
					if cell.scrollable then
						local pos = Vec2:new( cell._scrollRect.x, cell._scrollRect.y )
						local scrollVec = Vec2:new( 0, cell.scrollAmount * mouseWheel )
			
						if RL_IsKeyDown( KEY_LEFT_SHIFT ) then
							scrollVec = Vec2:new( cell.scrollAmount * mouseWheel, 0 )
						end
			
						cell:scroll( pos - scrollVec )
					end
				end
	
				foundFirst = true
			elseif cell.notMouseOver ~= nil then
				cell:notMouseOver()
			end
		end
	end

	-- Text input.
	if Gui._inputItem ~= nil then
		repeat
			local char = RL_GetCharPressed()

			if 0 < char then
				if utf8.len( Gui._inputItem.text ) < Gui._inputItem.maxTextLen then
					Gui._inputItem.text = Gui._inputItem.text..utf8.char( char )
				end
			end

		until char == 0

		repeat
			local key = RL_GetKeyPressed()

			if 0 < key then
				if key == KEY_BACKSPACE then
					Gui._inputItem.text = util.utf8Sub( Gui._inputItem.text, 0, utf8.len( Gui._inputItem.text ) - 1 )
				elseif key == KEY_ENTER or key == KEY_KP_ENTER then
					if Gui._inputItem.allowLineBreak then
						Gui._inputItem.text = Gui._inputItem.text.."\n"
					else
						Gui.inputUnfocus()
					end
				elseif key == KEY_ESCAPE then
					Gui.inputUnfocus()
				end
			end
		until key == 0

		if readyToUnfocusInput and RL_IsMouseButtonPressed( Gui.mouseButton ) then
			Gui.inputUnfocus()
		end

		readyToUnfocusInput = true
	end
end

function Gui.draw()
	for _, element in ipairs( Gui._cells ) do
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
	local object = setmetatable( {}, Text )

	object.bounds = Rect:new( 0, 0, 0, 0 )
	object.HAling = setProperty( set, "HAling", Gui.ALING.LEFT )
	object.VAling = setProperty( set, "VAling", Gui.ALING.BOTTOM )

	object.font = setProperty( set, "font", Gui.font )
	object.text = setProperty( set, "text", "" )
	object.fontSize = setProperty( set, "fontSize", Gui.fontSize )
	object.spacing = setProperty( set, "spacing", Gui.spacing )
	object.color = setProperty( set, "color", Color:new( BLACK ) )
	object.maxTextLen = setProperty( set, "maxTextLen", nil )
	object.allowLineBreak = setProperty( set, "allowLineBreak", false )

	object.visible = setProperty( set, "visible", true )
	object._parent = nil

	object:set( object.text )

	return object
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

	RL_DrawText( self.font, self.text, { self._prante.bounds.x + self.bounds.x, self._prante.bounds.y + self.bounds.y }, self.fontSize, self.spacing, self.color )
end

-- Texture.

Texture = {}
Texture.__index = Texture

function Texture:new( set )
	local object = setmetatable( {}, Texture )

	object.bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) )
	object.HAling = setProperty( set, "HAling", Gui.ALING.LEFT )
	object.VAling = setProperty( set, "VAling", Gui.ALING.CENTER )

	object.texture = setProperty( set, "texture", nil )
	object.source = setProperty( set, "source", Rect:new( 0, 0, 0, 0 ) )
	object.origin = setProperty( set, "origin", Vec2:new( 0, 0 ) )
	object.rotation = setProperty( set, "rotation", 0 )
	object.color = setProperty( set, "color", Color:new( WHITE ) )

	object.visible = setProperty( set, "visible", true )
	object._parent = nil

	object:set( object.texture ) -- To measure bounds.

    return object
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
		self.bounds.x + self._prante.bounds.x,
		self.bounds.y + self._prante.bounds.y,
		self.bounds.width,
		self.bounds.height
	}

	RL_DrawTexturePro( self.texture, self.source, dst, self.origin, self.rotation, self.color )
end

-- Shape.

Shape = {}
Shape.__index = Shape

function Shape:new( set )
	local object = setmetatable( {}, Shape )

	object.bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) )
	object.HAling = setProperty( set, "HAling", Gui.ALING.LEFT )
	object.VAling = setProperty( set, "VAling", Gui.ALING.CENTER )

	object.shape = setProperty( set, "shape", Gui.SHAPE.RECTANGLE )
	-- Line.
	object.startPos = setProperty( set, "startPos", Vec2:new( 0, 0 ) )
	object.endPos = setProperty( set, "endPos", Vec2:new( 0, 0 ) )
	object.thickness = setProperty( set, "thickness", 3.0 )
	-- Circle.
	object.center = setProperty( set, "center", Vec2:new( 0, 0 ) )
	object.radius = setProperty( set, "radius", 0 )
	-- Ellipse.
	object.radiusH = setProperty( set, "radiusH", 0 )
	object.radiusV = setProperty( set, "radiusV", 0 )
	-- Rectangle rounded.
	object.roundness = setProperty( set, "roundness", 1 )
	object.segments = setProperty( set, "segments", 4 )

	object.color = setProperty( set, "color", Color:new( WHITE ) )

	object.visible = setProperty( set, "visible", true )
	object._parent = nil

	object:set( object.shape )

    return object
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

	local pos = Vec2:new( self._prante.bounds.x, self._prante.bounds.y )

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
	local object = setmetatable( {}, Element )

	-- object._ID = #Gui._cells + 1
	object.bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) )
	object.padding = setProperty( set, "padding", Gui.padding )
	object.visible = setProperty( set, "visible", true )
	object.disabled = setProperty( set, "disabled", false )
	object.drawBounds = setProperty( set, "drawBounds", false )
	object.color = setProperty( set, "color", Color:new( GRAY ) )

	object.items = {}
	
	object._visibilityBounds = nil
	-- Callbacks.
	object.onMouseOver = setProperty( set, "onMouseOver", nil )
	object.notMouseOver = setProperty( set, "notMouseOver", nil )
	object.onClicked = setProperty( set, "onClicked", nil )
	object.onHeld = setProperty( set, "onHeld", nil )
	object.inputFocus = setProperty( set, "inputFocus", nil )
	object.inputUnfocus = setProperty( set, "inputUnfocus", nil )
	object._parent = nil

	table.insert( Gui._cells, object )

    return object
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
	item._prante = self
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
	Gui.delete( self )
end

function Element:set2Top()
	Gui.set2Top( self )
end

function Element:set2Back()
	Gui.set2Back( self )
end

-- Container.

Container = {}
Container.__index = Container

function Container:new( set )
	local object = setmetatable( {}, Container )

	-- object._ID = #Gui._cells + 1
	object.bounds = setProperty( set, "bounds", Rect:new( 0, 0, 0, 0 ) )
	object.spacing = setProperty( set, "spacing", Gui.spacing )
	object.type = setProperty( set, "type", Gui.CONTAINER.VERTICAL )
	object.HAling = setProperty( set, "HAling", Gui.ALING.LEFT )
	object.VAling = setProperty( set, "VAling", Gui.ALING.TOP )

	object.visible = setProperty( set, "visible", true )
	object.disabled = setProperty( set, "disabled", false )
	object.scrollable = setProperty( set, "scrollable", false )
	object.showScrollbar = setProperty( set, "showScrollbar", false )
	object.scrollbarWidth = setProperty( set, "scrollbarWidth", Gui.scrollbarWidth )
	object.scrollAmount = setProperty( set, "scrollAmount", Gui.scrollAmount ) -- When using mouse scroll.
	object.drawScrollRect = setProperty( set, "drawScrollRect", false )
	
	object.cells = {}
	
	object._visibilityBounds = nil -- Will give this to it's children.
	object._scrollRect = Rect:new( 0, 0, 0, 0 )
	object._VScrollbarRect = Rect:new( 0, 0, 0, 0 )
	object._HScrollbarRect = Rect:new( 0, 0, 0, 0 )

	object._VScrollbar = nil
	object._HScrollbar = nil
	object._parent = nil

	table.insert( Gui._cells, object )

    return object
end

function Container:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	self:update()
end

function Container:add( cell )
	table.insert( self.cells, cell )

	self:update()

	-- Highest container becomes the parent.
	if self._parent ~= nil then
		cell._parent = self._parent
	else
		cell._parent = self
	end

	if cell.cells ~= nil then
		for _, sCell in ipairs( cell.cells ) do
			sCell._parent = cell._parent
		end
	end

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


-- //TODO Add this
function Container:isMouseOver( mousePosition )
	local over = RL_CheckCollisionPointRec( mousePosition, self.bounds )

	if over and self._visibilityBounds ~= nil then
		over = RL_CheckCollisionPointRec( mousePosition, self._visibilityBounds )
	end

	if over and self.onMouseOver ~= nil then
		self:onMouseOver()
	end

	return over
end

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
				onClicked = function() Gui._heldCallback = function() self:mouseScroll( Vec2:new( 0, 1 ) ) end end,
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
				onClicked = function() Gui._heldCallback = function() self:mouseScroll( Vec2:new( 1, 0 ) ) end end,
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

function Container:delete()
	for _, cell in ipairs( self.cells ) do
		cell:delete()
	end
	
	if self._VScrollbar ~= nil then
		Gui.delete( self._VScrollbar )
	end
	if self._HScrollbar ~= nil then
		Gui.delete( self._HScrollbar )
	end

	Gui.delete( self )
end

function Container:set2Top()
	Gui.set2Top( self )

	for _, cell in ipairs( self.cells ) do
		cell:set2Top()
	end
	
	if self._VScrollbar ~= nil then
		Gui.set2Top( self._VScrollbar )
	end
	if self._HScrollbar ~= nil then
		Gui.set2Top( self._HScrollbar )
	end
end

function Container:set2Back()
	if self._VScrollbar ~= nil then
		Gui.set2Back( self._VScrollbar )
	end
	if self._HScrollbar ~= nil then
		Gui.set2Back( self._HScrollbar )
	end
	
	for _, cell in ipairs( self.cells ) do
		cell:set2Back()
	end
	
	Gui.set2Back( self )
end

function Container:draw()
	if self.drawScrollRect then
		RL_DrawRectangleLines( {
			self.bounds.x - self._scrollRect.x,
			self.bounds.y - self._scrollRect.y,
			self._scrollRect.width,
			self._scrollRect.height,
		},
		RED )
	end
end

--Assingments.

Gui.text = Text
Gui.texture = Texture
Gui.shape = Shape

Gui.element = Element
Gui.container = Container

return Gui
