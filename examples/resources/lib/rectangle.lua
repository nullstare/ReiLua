-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector2 = require( "vector2" )

local Rectangle = {}
Rectangle.meta = {
	__index = Rectangle,
	__tostring = function( r )
		return "{"..tostring( r.x )..", "..tostring( r.y )..", "..tostring( r.width )..", "..tostring( r.height ).."}"
	end,
	__add = function( r1, r2 )
		return Rectangle:new( r1.x + r2.x, r1.y + r2.y, r1.width + r2.width, r1.height + r2.height )
	end,
	__sub = function( r1, r2 )
		return Rectangle:new( r1.x - r2.x, r1.y - r2.y, r1.width - r2.width, r1.height - r2.height )
	end,
	__mul = function( r1, r2 )
		return Rectangle:new( r1.x * r2.x, r1.y * r2.y, r1.width * r2.width, r1.height * r2.height )
	end,
	__div = function( r1, r2 )
		return Rectangle:new( r1.x / r2.x, r1.y / r2.y, r1.width / r2.width, r1.height / r2.height )
	end,
	__mod = function( r, v )
		return Rectangle:new( math.fmod( r.x, v ), math.fmod( r.y, v ), math.fmod( r.width, v ), math.fmod( r.height, v ) )
	end,
	__pow = function( r, v )
		return Rectangle:new( r.x ^ v, r.y ^ v, r.width ^ v, r.height ^ v )
	end,
	__unm = function( r )
		return Rectangle:new( -r.x, -r.y, -r.width, -r.height )
	end,
	__len = function()
		return 4
	end,
	__eq = function( r1, r2 )
		return RL.Vector2Equals( { r1.x, r1.y }, { r2.x, r2.y } ) and RL.Vector2Equals( { r1.width, r1.height }, { r2.width, r2.height } )
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Rectangle:new( x, y, width, height )
	local object = setmetatable( {}, Rectangle.meta )

	object.x = x or 0
	object.y = y or 0
	object.width = width or 0
	object.height = height or 0

	return object
end

function Rectangle:newT( t )
	local object = setmetatable( {}, Rectangle.meta )

	object.x, object.y, object.width, object.height = table.unpack( t )

	return object
end

function Rectangle:set( x, y, width, height )
	self.x = x or 0
	self.y = y or 0
	self.width = width or 0
	self.height = height or 0
end

function Rectangle:setT( t )
	self.x, self.y, self.width, self.height = table.unpack( t )
end

function Rectangle:arr()
	return { self.x, self.y, self.width, self.height }
end

function Rectangle:unpack()
	return self.x, self.y, self.width, self.height
end

function Rectangle:clone()
	return Rectangle:new( self.x, self.y, self.width, self.height )
end

function Rectangle:scale( scalar )
	return Rectangle:new( self.x, self.y, self.width * scalar, self.height * scalar )
end

function Rectangle:min( rec )
	return Rectangle:new( self.x, self.y, math.min( self.width, rec.width ), math.min( self.height, rec.height ) )
end

function Rectangle:max( rec )
	return Rectangle:new( self.x, self.y, math.max( self.width, rec.width ), math.max( self.height, rec.height ) )
end

function Rectangle:floor()
	return Rectangle:new( math.floor( self.x ), math.floor( self.y ), math.floor( self.width ), math.floor( self.height ) )
end

function Rectangle:ceil()
	return Rectangle:new( math.ceil( self.x ), math.ceil( self.y ), math.ceil( self.width ), math.ceil( self.height ) )
end

function Rectangle:area()
	return self.width * self.height
end

-- Returns rectangle that fits both rectangles inside it
function Rectangle:fit( rec )
	local pos = Vector2:new( math.min( self.x, rec.x ), math.min( self.y, rec.y ) )

	return Rectangle:new(
		pos.x,
		pos.y,
		math.max( self.x + self.width - pos.x, rec.x + rec.width - pos.x ),
		math.max( self.y + self.height - pos.y, rec.y + rec.height - pos.y )
	)
end

-- If rectangle is fully inside another rectangle
function Rectangle:isInside( rec )
	return rec.x <= self.x and self.x + self.width <= rec.x + rec.width
	and rec.y <= self.y and self.y + self.height <= rec.y + rec.height
end

-- Returns clamped rectangle that is inside another rectangle.
function Rectangle:clampInside( rec )
	return Rectangle:new(
		math.max( rec.x, math.min( self.x, rec.x + rec.width - self.width ) ),
		math.max( rec.y, math.min( self.y, rec.y + rec.height - self.height ) ),
		self.width,
		self.height
	)
end

function Rectangle:checkCollisionRec( rec )
	return RL.CheckCollisionRecs( self, rec )
end

function Rectangle:checkCollisionCircle( center, radius )
	return RL.CheckCollisionCircleRec( center, radius, self )
end

function Rectangle:checkCollisionPoint( point )
	return RL.CheckCollisionPointRec( point, self )
end

function Rectangle:getCollisionRec( rec )
	return Rectangle:new( RL.GetCollisionRec( self, rec ) )
end

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, Rectangle:new( 0, 0, 0, 0 ) )
end

-- Uses pre generated objects to avoid "slow" table generation.
function Rectangle:temp( x, y, width, height )
	local object = tempPool[ curTemp ]
	curTemp = curTemp + 1

	if TEMP_COUNT < curTemp then
		curTemp = 1
	end

	object.x = x or 0
	object.y = y or 0
	object.width = width or 0
	object.height = height or 0

	return object
end

-- Uses pre generated objects to avoid "slow" table generation.
function Rectangle:tempT( t )
	local object = tempPool[ curTemp ]
	curTemp = curTemp + 1

	if TEMP_COUNT < curTemp then
		curTemp = 1
	end

	object.x, object.y, object.width, object.height = table.unpack( t )

	return object
end

function Rectangle:getTempId()
	return curTemp
end

return Rectangle
