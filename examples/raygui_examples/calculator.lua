Calculator = {}
Calculator.__index = Calculator

Calculator.OPERATIONS = {
	ADD = 0,
	SUB = 1,
	DIV = 2,
	MUL = 3,
	EQUAL = 4,
	CLEAR = 5,
}

function Calculator:new( pos )
    local object = setmetatable( {}, Calculator )

    object.window = Raygui.WindowBox:new(
		Rect:new( pos.x, pos.y, 188, 216 ),
		"Calculator",
		-- Close callback.
		function() object:setVisible( false ) end,
		-- Grab callback.
		function() object:set2Top() end,
		-- Drag callback.
		function( self ) object:setPosition( Vec2:new( self.bounds.x, self.bounds.y ) ) end
	)
	object.display = Raygui.Label:new(
		Rect:new( 0, 0, 180, 20 ),
		""
	)
	object.display.position = Vec2:new( 10, 32 )
	object.buttons = {}

	local buttons = {
		{ "7", function() object:addNumber( 7 ) end },
		{ "8", function() object:addNumber( 8 ) end },
		{ "9", function() object:addNumber( 9 ) end },
		{ "/", function() object:addOperation( self.OPERATIONS.DIV ) end },
		{ "4", function() object:addNumber( 4 ) end },
		{ "5", function() object:addNumber( 5 ) end },
		{ "6", function() object:addNumber( 6 ) end },
		{ "*", function() object:addOperation( self.OPERATIONS.MUL ) end },
		{ "1", function() object:addNumber( 1 ) end },
		{ "2", function() object:addNumber( 2 ) end },
		{ "3", function() object:addNumber( 3 ) end },
		{ "-", function() object:addOperation( self.OPERATIONS.SUB ) end },
		{ "0", function() object:addNumber( 0 ) end },
		{ "C", function() object:addOperation( self.OPERATIONS.CLEAR ) end },
		{ "=", function() object:addOperation( self.OPERATIONS.EQUAL ) end },
		{ "+", function() object:addOperation( self.OPERATIONS.ADD ) end },
	}
	local rowCount = 4
	local buttonRect = Rect:new( 5, 64, 40, 32 )
	local startPos = Vec2:new( buttonRect.x, buttonRect.y )
	local buttonSpacing = 6

	for i, button in ipairs( buttons ) do
		table.insert( object.buttons, Raygui.Button:new(
			buttonRect:clone(),
			button[1],
			button[2]
		) )
		-- Set position in window.
		object.buttons[i].position = Vec2:new( buttonRect.x, buttonRect.y )

		if i % rowCount == 0 then
			buttonRect.x = startPos.x
			buttonRect.y = buttonRect.y + buttonRect.height + buttonSpacing
		else
			buttonRect.x = buttonRect.x + buttonRect.width + buttonSpacing
		end
	end

	object.visible = true
	object.numbers = { "", "" }
	object.op = nil

	object:setPosition( pos )

	return object
end

function Calculator:addNumber( num )
	if self.op == nil then
		self.numbers[1] = self.numbers[1]..tostring( num )
	else
		self.numbers[2] = self.numbers[2]..tostring( num )
	end

	self:updateDisplay()
end

function Calculator:addOperation( op )
	if op == self.OPERATIONS.EQUAL then
		if self.op == self.OPERATIONS.ADD then
			self.numbers[1] = tonumber( self.numbers[1] ) + tonumber( self.numbers[2] )
		elseif self.op == self.OPERATIONS.SUB then
			self.numbers[1] = tonumber( self.numbers[1] ) - tonumber( self.numbers[2] )
		elseif self.op == self.OPERATIONS.MUL then
			self.numbers[1] = tonumber( self.numbers[1] ) * tonumber( self.numbers[2] )
		elseif self.op == self.OPERATIONS.DIV then
			self.numbers[1] = tonumber( self.numbers[1] ) / tonumber( self.numbers[2] )
		end

		self.numbers[2] = ""
		self.op = nil
	elseif op == self.OPERATIONS.CLEAR then
		self.numbers[1] = ""
		self.numbers[2] = ""
		self.op = nil
	else
		self.op = op
	end

	self:updateDisplay()
end

function Calculator:updateDisplay()
	self.display.text = self.numbers[1]

	if self.op == self.OPERATIONS.ADD then
		self.display.text = self.display.text.."+"
	elseif self.op == self.OPERATIONS.SUB then
		self.display.text = self.display.text.."-"
	elseif self.op == self.OPERATIONS.MUL then
		self.display.text = self.display.text.."*"
	elseif self.op == self.OPERATIONS.DIV then
		self.display.text = self.display.text.."/"
	end

	self.display.text = self.display.text..self.numbers[2]
end

function Calculator:setPosition( pos )
	self.display:setPosition( pos + self.display.position )

	for _, button in ipairs( self.buttons ) do
		button:setPosition( pos + button.position )
	end
end

function Calculator:set2Top()
	Raygui.set2Top( self.window )
	Raygui.set2Top( self.display )

	for _, button in ipairs( self.buttons ) do
		Raygui.set2Top( button )
	end
end

function Calculator:setVisible( visible )
	self.visible = visible
	self.window.visible = visible
	self.display.visible = visible

	for _, button in ipairs( self.buttons ) do
		button.visible = visible
	end
end

return Calculator