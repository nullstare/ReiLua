-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

Rectangle = {}

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
	__idiv = function( r, v )
		return Rectangle:new( r.x // v, r.y // v, r.width // v, r.height // v )
	end,
	__len = function( _ )
		return 4
	end,
	__eq = function( r1, r2 )
		return RL.Vector2Equals( { r1.x, r1.y }, { r2.x, r2.y } ) and RL.Vector2Equals( { r1.width, r1.height }, { r2.width, r2.height } )
	end,
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

return Rectangle
