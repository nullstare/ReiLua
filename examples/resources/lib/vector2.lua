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
    local o = {
		x = x,
		y = y,
	}
	setmetatable( o, Vector2.meta )
    return o
end

function Vector2:set( vec )
	self.x = vec[1]
	self.y = vec[2]
end

function Vector2:arr()
	return { self.x, self.y }
end

function Vector2:clone()
	return Vector2:new( self.x, self.y )
end

function Vector2:abs()
	return Vector2:new( math.abs( self.x ), math.abs( self.y ) )
end

function Vector2:length()
	return RL_Vector2Length( self:arr() )
end

function Vector2:dot( v2 )
	return RL_Vector2DotProduct( self:arr(), v2:arr() )
end

function Vector2:distance( v2 )
	return RL_Vector2Distance( self:arr(), v2:arr() )
end

function Vector2:angle( v2 )
	return RL_Vector2Angle( self:arr(), v2:arr() )
end

function Vector2:normalize()
	local r = RL_Vector2Normalize( self:arr() )
	return Vector2:new( r[1], r[2] )
end

function Vector2:lerp( v2, value )
	local r = RL_Vector2Lerp( self:arr(), v2:arr(), value )
	return Vector2:new( r[1], r[2] )
end

function Vector2:reflect( normal )
	local r = RL_Vector2Reflect( self:arr(), normal:arr() )
	return Vector2:new( r[1], r[2] )
end

function Vector2:rotate( angle )
	local r = RL_Vector2Rotate( self:arr(), angle )
	return Vector2:new( r[1], r[2] )
end

function Vector2:moveTowards( target, maxDistance )
	local r = RL_Vector2MoveTowards( self:arr(), target:arr(), maxDistance )
	return Vector2:new( r[1], r[2] )
end

return Vector2
