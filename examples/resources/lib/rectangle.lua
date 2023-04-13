Rectangle = {}
-- Rectangle.TYPE = "Rectangle"

Rectangle.meta = {
	__index = Rectangle,
	__tostring = function( r )
		return "{"..tostring( r.x )..", "..tostring( r.y )..", "..tostring( r.width )..", "..tostring( r.height ).."}"
	end,
	-- __add = function( v1, v2 )
	-- 	return Vector2:new( v1.x + v2.x, v1.y + v2.y )
	-- end,
	-- __sub = function( v1, v2 )
	-- 	return Vector2:new( v1.x - v2.x, v1.y - v2.y )
	-- end,
	-- __mul = function( v1, v2 )
	-- 	return Vector2:new( v1.x * v2.x, v1.y * v2.y )
	-- end,
	-- __div = function( v1, v2 )
	-- 	return Vector2:new( v1.x / v2.x, v1.y / v2.y )
	-- end,
	-- __mod = function( v, value )
	-- 	return Vector2:new( math.fmod( v.x, value ), math.fmod( v.y, value ) )
	-- end,
	-- __pow = function( v, value )
	-- 	return Vector2:new( v.x ^ value, v.y ^ value )
	-- end,
	-- __unm = function( v )
	-- 	return Vector2:new( -v.x, -v.y )
	-- end,
	-- __idiv = function( v, value )
	-- 	return Vector2:new( v.x // value, v.y // value )
	-- end,
	-- __len = function( v )
	-- 	local len = 0

	-- 	for _, _ in pairs( v ) do
	-- 		len = len + 1
	-- 	end

	-- 	return len
	-- end,
	-- __eq = function( v1, v2 )
	-- 	return v1.x == v2.x and v1.y == v2.y
	-- end,
}

function Rectangle:new( x, y, width, height )
	if type( x ) == "table" then
		x, y, width, height = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y, width, height = 0, 0, 0, 0
	end

	local object = setmetatable( {}, Rectangle.meta )

	object.x = x
	object.y = y
	object.width = width
	object.height = height

    return object
end

function Rectangle:set( x, y, width, height )
	if type( x ) == "table" then
		x, y, width, height = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y, width, height = 0, 0, 0, 0
	end

	self.x = x
	self.y = y
	self.width = width
	self.height = height
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

return Rectangle
