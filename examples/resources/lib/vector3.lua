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
		return RL_Vector3Equals( v1, v2 ) == 1
	end,
}

function Vector3:new( x, y, z )
	if type( x ) == "table" then
		x, y, z = table.unpack( x )
	end

    local o = {
		x = x,
		y = y,
		z = z,
	}
	setmetatable( o, Vector3.meta )
    return o
end

function Vector3:set( x, y, z )
	if type( x ) == "table" then
		x, y, z = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y, z = 0, 0, 0
	end

	self.x = x
	self.y = y
	self.z = z
end

function Vector3:arr()
	return { self.x, self.y, self.z }
end

function Vector3:unpack()
	return self.x, self.y, self.z
end

function Vector3:clone()
	return Vector3:new( self.x, self.y, self.z )
end

function Vector3:abs()
	return Vector3:new( math.abs( self.x ), math.abs( self.y ), math.abs( self.z ) )
end

function Vector3:min( v2 )
	return Vector3:new( RL_Vector3Min( self, v2 ) )
end

function Vector3:max( v2 )
	return Vector3:new( RL_Vector3Max( self, v2 ) )
end

function Vector3:addValue( value )
	return Vector3:new( RL_Vector3AddValue( self, value ) )
end

function Vector3:subValue( value )
	return Vector3:new( RL_Vector3SubtractValue( self, value ) )
end

function Vector3:scale( scalar )
	return Vector3:new( RL_Vector3Scale( self, scalar ) )
end

function Vector3:cross( v2 )
	return Vector3:new( RL_Vector3CrossProduct( self, v2 ) )
end

function Vector3:perpendicular()
	return Vector3:new( RL_Vector3Perpendicular( self ) )
end

function Vector3:length()
	return RL_Vector3Length( self )
end

function Vector3:lengthSqr()
	return RL_Vector3LengthSqr( self )
end

function Vector3:dot( v2 )
	return RL_Vector3DotProduct( self, v2 )
end

function Vector3:distance( v2 )
	return RL_Vector3Distance( self, v2 )
end

function Vector3:distanceSqr( v2 )
	return RL_Vector3DistanceSqr( self, v2 )
end

function Vector3:angle( v2 )
	return RL_Vector3Angle( self, v2 )
end

function Vector3:negate()
	return Vector3:new( RL_Vector3Negate( self ) )
end

function Vector3:normalize()
	return Vector3:new( RL_Vector3Normalize( self ) )
end

function Vector3:orthoNormalize( v2 )
	local r1, r2 = RL_Vector3OrthoNormalize( self, v2 )
	return Vector3:new( r1[1], r1[2], r1[3] ), Vector3:new( r2[1], r2[2], r2[3] )
end

function Vector3:transform( mat )
	return Vector3:new( RL_Vector3Transform( self, mat ) )
end

function Vector3:rotateByQuaternion( q )
	return Vector3:new( RL_Vector3RotateByQuaternion( self, q ) )
end

function Vector3:rotateByAxisAngle( axis, angle )
	return Vector3:new( RL_Vector3RotateByAxisAngle( self, axis, angle ) )
end

function Vector3:lerp( v2, value )
	return Vector3:new( RL_Vector3Lerp( self, v2, value ) )
end

function Vector3:reflect( normal )
	return Vector3:new( RL_Vector3Reflect( self, normal ) )
end

function Vector3:invert()
	return Vector3:new( RL_Vector3Invert( self ) )
end

function Vector3:clamp( min, max )
	return Vector3:new( RL_Vector3Clamp( self, min, max ) )
end

function Vector3:clampValue( min, max )
	return Vector3:new( RL_Vector3ClampValue( self, min, max ) )
end

function Vector3:equals( v2 )
	return RL_Vector3Equals( self, v2 )
end

return Vector3
