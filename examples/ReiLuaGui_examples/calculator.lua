Calculator = {}
Calculator.__index = Calculator

function Calculator:new( pos )
	pos = pos or Vec2:new( 0, 0 )

	local object = setmetatable( {}, self )

	object.HANDLE_HIGHT = 32
	object.DISPLAY_HIGHT = 40
	object.OPERATIONS = { ADD = 0, SUB = 1, MUL = 2, DIV = 3 }

	object.windowRect = Rect:new( pos.x, pos.y, 196, 244 )
	object.dragPos = Vec2:new( 0, 0 )

	-- Handle.

	object.handle = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width, object.HANDLE_HIGHT ),
		padding = 10,
		onClicked = function()
			object:set2Top()
			object.dragPos = Vec2:new( RL_GetMousePosition() ) - Vec2:new( object.handle.bounds.x, object.handle.bounds.y )
			Gui.heldCallback = function() object:drag() end
		end,
	} )

	object.handle:add( Gui.texture:new( {
		bounds = object.handle.bounds:clone(),
		texture = bgrTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( LIGHTGRAY ),
	} ) )
	
	object.handle:add( Gui.texture:new( {
		bounds = object.handle.bounds:clone(),
		texture = borderTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( LIGHTGRAY ),
		nPatchInfo = { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH },
	} ) )

	object.handle:add( Gui.text:new( { text = "Calculator", fontSize = 20, VAling = Gui.ALING.CENTER } ) )

	-- Close button.

	object.closeButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.HANDLE_HIGHT, object.HANDLE_HIGHT ),
		onClicked = function()
			object:setVisible( false )
		end,
		onMouseOver = function( self ) self.items[1].color = Color:new( WHITE ) end,
		notMouseOver = function( self ) self.items[1].color = Color:new( BLACK ) end,
	} )

	object.closeButton:add( Gui.texture:new( {
		bounds = object.closeButton.bounds:clone(),
		texture = cancelTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
	} ) )

	-- Panel.

	object.panel = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width, object.windowRect.height - object.HANDLE_HIGHT ),
	} )

	object.panel:add( Gui.texture:new( {
		bounds = object.panel.bounds:clone(),
		texture = bgrTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( GRAY ),
	} ) )

	object.panel:add( Gui.texture:new( {
		bounds = object.panel.bounds:clone(),
		texture = borderTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( LIGHTGRAY ),
		nPatchInfo = { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH },
	} ) )

	-- Display.

	object.display = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width - 16, object.DISPLAY_HIGHT ),
		padding = 10,
		drawBounds = true,
		color = Color:new( WHITE )
	} )

	object.display:add( Gui.text:new( { text = "", fontSize = 30, VAling = Gui.ALING.CENTER, maxTextLen = 8 } ) )

	-- Buttons.
	
	local buttonStrings = { "7", "8", "9", "/", "4", "5", "6", "*", "1", "2", "3", "-", "0", "C", "=", "+" }
	object.buttons = {}

	for y = 0, 3 do
		for x = 0, 3 do
			local i = x + y * 4

			table.insert( object.buttons, Gui.element:new( {
				bounds = Rect:new( 0, 0, 40, 32 ),
				drawBounds = true,
				onMouseOver = function( self ) self.color = Color:new( WHITE ) end,
				notMouseOver = function( self ) self.color = Color:new( LIGHTGRAY ) end,
			} ) )

			object.buttons[ #object.buttons ].pos = Vec2:new( 8 + x * 46, object.HANDLE_HIGHT + object.DISPLAY_HIGHT + 16 + y * 38 )
			object.buttons[ #object.buttons ]:add( Gui.text:new( { text = buttonStrings[i+1], fontSize = 30, HAling = Gui.ALING.CENTER, VAling = Gui.ALING.CENTER } ) )

			if buttonStrings[i+1] == "/" then
				object.buttons[ #object.buttons ].onClicked = function() object:setOperation( object.OPERATIONS.DIV ) end
			elseif buttonStrings[i+1] == "*" then
				object.buttons[ #object.buttons ].onClicked = function() object:setOperation( object.OPERATIONS.MUL ) end
			elseif buttonStrings[i+1] == "-" then
				object.buttons[ #object.buttons ].onClicked = function() object:setOperation( object.OPERATIONS.SUB ) end
			elseif buttonStrings[i+1] == "+" then
				object.buttons[ #object.buttons ].onClicked = function() object:setOperation( object.OPERATIONS.ADD ) end
			elseif buttonStrings[i+1] == "C" then
				object.buttons[ #object.buttons ].onClicked = function() object:clear() end
			elseif buttonStrings[i+1] == "=" then
				object.buttons[ #object.buttons ].onClicked = function() object:equals() end
			else
				object.buttons[ #object.buttons ].onClicked = function() object:addValue( tonumber( buttonStrings[i+1] ) ) end
			end
		end
	end

	-- Calculator variables.

	object.value1 = ""
	object.value2 = ""
	object.operation = nil

	-- Set position.

	object:setPosition( Vec2:new( object.windowRect.x, object.windowRect.y ) )

    return object
end

function Calculator:setPosition( pos )
	self.windowRect.x = pos.x
	self.windowRect.y = pos.y

	self.handle:setPosition( pos )
	self.closeButton:setPosition( Vec2:new( pos.x + self.windowRect.width - self.HANDLE_HIGHT, pos.y ) )
	self.panel:setPosition( Vec2:new( pos.x, pos.y + self.HANDLE_HIGHT ) )
	self.display:setPosition( Vec2:new( pos.x + 8, pos.y + self.HANDLE_HIGHT + 8 ) )

	for _, button in ipairs( self.buttons ) do
		button:setPosition( pos + button.pos )
	end
end

function Calculator:drag()
	local mousePos = Vec2:new( RL_GetMousePosition() )
	local winPos = Vec2:new( self.handle.bounds.x, self.handle.bounds.y )

	self:setPosition( mousePos - self.dragPos )
end

function Calculator:setVisible( visible )
	self.handle.visible = visible
	self.handle.disabled = not visible

	self.closeButton.visible = visible
	self.closeButton.disabled = not visible
	
	self.panel.visible = visible
	self.panel.disabled = not visible

	self.display.visible = visible
	self.display.disabled = not visible
	
	for _, button in ipairs( self.buttons ) do
		button.visible = visible
		button.disabled = not visible
	end
end

function Calculator:set2Top()
	self.panel:set2Top()
	
	for _, button in ipairs( self.buttons ) do
		button:set2Top()
	end

	self.handle:set2Top()
	self.closeButton:set2Top()
	self.display:set2Top()
end

function Calculator:addValue( value )
	if self.operation == nil then
		self.value1 = self.value1..value
	else
		self.value2 = self.value2..value
	end

	self:updateDisplay()
end

function Calculator:setOperation( operation )
	if self.value1 ~= "" then
		self.operation = operation
	end

	if self.value2 ~= "" then
		self:equals()
	end

	self:updateDisplay()
end

function Calculator:clear()
	self.value1 = ""
	self.value2 = ""
	self.operation = nil

	self:updateDisplay()
end

function Calculator:updateDisplay( setText )
	local text = setText or ""

	if self.value1 ~= "" then
		text = self.value1
	end

	if self.operation ~= nil then
		if self.operation == self.OPERATIONS.ADD then
			text = text.." + "
		elseif self.operation == self.OPERATIONS.SUB then
			text = text.." - "
		elseif self.operation == self.OPERATIONS.MUL then
			text = text.." * "
		elseif self.operation == self.OPERATIONS.DIV then
			text = text.." / "
		end
	end

	if self.value2 ~= "" then
		text = text..self.value2
	end

	self.display.items[1]:set( text )
end

function Calculator:equals()
	local result = 0

	if self.operation == self.OPERATIONS.ADD then
		result = tonumber( self.value1 ) + tonumber( self.value2 )
	elseif self.operation == self.OPERATIONS.SUB then
		result = tonumber( self.value1 ) - tonumber( self.value2 )
	elseif self.operation == self.OPERATIONS.MUL then
		result = tonumber( self.value1 ) * tonumber( self.value2 )
	elseif self.operation == self.OPERATIONS.DIV then
		if tonumber( self.value2 ) == 0 then
			self:clear()
			self:updateDisplay( "Error" )

			return
		else
			result = tonumber( self.value1 ) / tonumber( self.value2 )
		end
	end

	self:clear()
	self.value1 = tostring( result )
	self:updateDisplay()
end

return Calculator
