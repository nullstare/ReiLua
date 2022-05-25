Vector2 = {}
Vector2.meta = {
	__index = Vector2,
	__tostring = function( v )
		return "{"..tostring( v.x )..", "..tostring( v.y ).."}"
	end,
	__add = function( v1, v2 )
		return Vector2:new( v1.x + v2.x, v1.y + v2.y )
	end,
	__sub = function( v1, v2 )
		return Vector2:new( v1.x - v2.x, v1.y - v2.y )
	end,
	__mul = function( v1, v2 )
		return Vector2:new( v1.x * v2.x, v1.y * v2.y )
	end,
	__div = function( v1, v2 )
		return Vector2:new( v1.x / v2.x, v1.y / v2.y )
	end,
	__mod = function( v, value )
		return Vector2:new( math.fmod( v.x, value ), math.fmod( v.y, value ) )
	end,
	__pow = function( v, value )
		return Vector2:new( v.x ^ value, v.y ^ value )
	end,
	__unm = function( v )
		return Vector2:new( -v.x, -v.y )
	end,
	__idiv = function( v, value )
		return Vector2:new( v.x // value, v.y // value )
	end,
	__len = function( v )
		local len = 0

		for _, _ in pairs( v ) do
			len = len + 1
		end

		return len
	end,
	__eq = function( v1, v2 )
		return v1.x == v2.x and v1.y == v2.y
	end,
}

function Vector2:new( x, y )
	if type( x ) == "table" then
		x, y = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y = 0, 0
	end

    local o = {
		x = x,
		y = y,
	}
	setmetatable( o, Vector2.meta )
    return o
end

function Vector2:set( x, y )
	if type( x ) == "table" then
		x, y = table.unpack( x )
	end

	self.x = x
	self.y = y
end

function Vector2:arr()
	return { self.x, self.y }
end

function Vector2:unpack()
	return self.x, self.y
end

function Vector2:clone()
	return Vector2:new( self.x, self.y )
end

function Vector2:abs()
	return Vector2:new( math.abs( self.x ), math.abs( self.y ) )
end

function Vector2:min( v2 )
	return Vector2:new( math.min( self.x, v2.x ), math.min( self.y, v2.y ) )
end

function Vector2:max( v2 )
	return Vector2:new( math.max( self.x, v2.x ), math.max( self.y, v2.y ) )
end

function Vector2:addValue( value )
	return Vector2:new( RL_Vector2AddValue( self, value ) )
end

function Vector2:subValue( value )
	return Vector2:new( RL_Vector2SubtractValue( self, value ) )
end

function Vector2:length()
	return RL_Vector2Length( self )
end

function Vector2:lengthSqr()
	return RL_Vector2LengthSqr( self )
end

function Vector2:dot( v2 )
	return RL_Vector2DotProduct( self, v2 )
end

function Vector2:distance( v2 )
	return RL_Vector2Distance( self, v2 )
end

function Vector2:angle( v2 )
	return RL_Vector2Angle( self, v2 )
end

function Vector2:scale( scale )
	return Vector2:new( RL_Vector2Scale( self, scale ) )
end

function Vector2:normalize()
	return Vector2:new( RL_Vector2Normalize( self ) )
end

function Vector2:lerp( v2, value )
	return Vector2:new( RL_Vector2Lerp( self, v2, value ) )
end

function Vector2:reflect( normal )
	return Vector2:new( RL_Vector2Reflect( self, normal ) )
end

function Vector2:rotate( angle )
	return Vector2:new( RL_Vector2Rotate( self, angle ) )
end

function Vector2:moveTowards( target, maxDistance )
	return Vector2:new( RL_Vector2MoveTowards( self, target, maxDistance ) )
end

return Vector2
