Color = {}
Color.meta = {
	__index = Color,
	__tostring = function( r )
		return "{"..tostring( r.r )..", "..tostring( r.g )..", "..tostring( r.b )..", "..tostring( r.a ).."}"
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

function Color:new( r, g, b, a )
	if type( r ) == "table" then
		r, g, b, a = table.unpack( r )
	elseif type( r ) == "nil" then
		r, g, b, a = 0, 0, 0, 255
	end

	if a == nil then
		a = 255
	end

	local object = setmetatable( {}, Color.meta )

	object.r = r
	object.g = g
	object.b = b
	object.a = a

    return object
end

function Color:set( r, g, b, a )
	if type( r ) == "table" then
		r, g, b, a = table.unpack( r )
	elseif type( r ) == "nil" then
		r, g, b, a = 0, 0, 0, 0
	end

	if a == nil then
		a = 255
	end

	self.r = r
	self.g = g
	self.b = b
	self.a = a
end

function Color:arr()
	return { self.r, self.g, self.b, self.a }
end

function Color:unpack()
	return self.r, self.g, self.b, self.a
end

function Color:clone()
	return Color:new( self.r, self.g, self.b, self.a )
end

return Color
