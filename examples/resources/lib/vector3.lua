Vector3 = {}
Vector3.meta = {
	__index = Vector3,
	__tostring = function( v )
		return "{"..tostring( v.x )..", "..tostring( v.y )..", "..tostring( v.z ).."}"
	end,
	__add = function( v1, v2 )
		return Vector3:new( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z )
	end,
	__sub = function( v1, v2 )
		return Vector3:new( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z )
	end,
	__mul = function( v1, v2 )
		return Vector3:new( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z )
	end,
	__div = function( v1, v2 )
		return Vector3:new( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z )
	end,
	__mod = function( v, value )
		return Vector3:new( math.fmod( v.x, value ), math.fmod( v.y, value ), math.fmod( v.z, value ) )
	end,
	__pow = function( v, value )
		return Vector3:new( v.x ^ value, v.y ^ value, v.z ^ value )
	end,
	__unm = function( v )
		return Vector3:new( -v.x, -v.y, -v.z )
	end,
	__idiv = function( v, value )
		return Vector3:new( v.x // value, v.y // value, v.z // value )
	end,
	__len = function( v )
		local len = 0

		for _, _ in pairs( v ) do
			len = len + 1
		end

		return len
	end,
	__eq = function( v1, v2 )
		return v1.x == v2.x and v1.y == v2.y and v1.z == v2.z
	end,
}

function Vector3:new( x, y, z )
    local o = {
		x = x,
		y = y,
		z = z,
	}
	setmetatable( o, Vector3.meta )
    return o
end

function Vector3:set( vec )
	self.x = vec[1]
	self.y = vec[2]
	self.z = vec[3]
end

function Vector3:arr()
	return { self.x, self.y, self.z }
end

function Vector3:clone()
	return Vector3:new( self.x, self.y, self.z )
end

function Vector3:abs()
	return Vector3:new( math.abs( self.x ), math.abs( self.y ), math.abs( self.z ) )
end

function Vector3:cross( v2 )
	local r = RL_Vector3CrossProduct( self:arr(), v2:arr() )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:perpendicular()
	local r = RL_Vector3Perpendicular( self:arr() )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:length()
	return RL_Vector3Length( self:arr() )
end

function Vector3:lengthSqr()
	return RL_Vector3LengthSqr( self:arr() )
end

function Vector3:dot( v2 )
	return RL_Vector3DotProduct( self:arr(), v2:arr() )
end

function Vector3:distance( v2 )
	return RL_Vector3Distance( self:arr(), v2:arr() )
end

function Vector3:normalize()
	local r = RL_Vector3Normalize( self:arr() )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:orthoNormalize( v2 )
	local r1, r2 = RL_Vector3OrthoNormalize( self:arr(), v2:arr() )
	return Vector3:new( r1[1], r1[2], r1[3] ), Vector3:new( r2[1], r2[2], r2[3] )
end

function Vector3:transform( mat )
	local r = RL_Vector3Transform( self:arr(), mat )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:rotateByQuaternion( qua )
	local r = RL_Vector3RotateByQuaternion( self:arr(), qua )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:lerp( v2, value )
	local r = RL_Vector3Lerp( self:arr(), v2:arr(), value )
	return Vector3:new( r[1], r[2], r[3] )
end

function Vector3:reflect( normal )
	local r = RL_Vector3Reflect( self:arr(), normal:arr() )
	return Vector3:new( r[1], r[2], r[3] )
end

return Vector3
