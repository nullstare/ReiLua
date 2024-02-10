-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector3 = require( "vector3" )
local Matrix = require( "matrix" )

local Quaternion = {}
local metatable = {
	__index = Quaternion,
	__tostring = function( q )
		return "{"..tostring( q.x )..", "..tostring( q.y )..", "..tostring( q.z )..", "..tostring( q.w ).."}"
	end,
	__add = function( q1, q2 )
		return Quaternion:new( RL.QuaternionAdd( q1, q2 ) )
	end,
	__sub = function( q1, q2 )
		return Quaternion:new( RL.QuaternionSubtract( q1, q2 ) )
	end,
	__mul = function( q1, q2 )
		return Quaternion:new( RL.QuaternionMultiply( q1, q2 ) )
	end,
	__div = function( q1, q2 )
		return Quaternion:new( RL.QuaternionDivide( q1, q2 ) )
	end,
	__unm = function( q )
		return Quaternion:new( RL.QuaternionInvert( q ) )
	end,
	__len = function()
		return 4
	end,
	__eq = function( q1, q2 )
		return RL.QuaternionEquals( q1, q2 ) == 1
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Quaternion:new( x, y, z, w )
	if type( x ) == "table" then
		x, y, z, w = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y, z, w = 0, 0, 0, 1 -- QuaternionIdentity.
	end

	local object = setmetatable( {}, metatable )

	object.x = x
	object.y = y
	object.z = z
	object.w = w

	return object
end

function Quaternion:set( x, y, z, w )
	if type( x ) == "table" then
		x, y, z, w = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y, z, w = 0, 0, 0, 1 -- QuaternionIdentity.
	end

	self.x = x
	self.y = y
	self.z = z
	self.w = w
end

function Quaternion:arr()
	return { self.x, self.y, self.z, self.w }
end

function Quaternion:unpack()
	return self.x, self.y, self.z, self.w
end

function Quaternion:clone()
	return Quaternion:new( self.x, self.y, self.z, self.w )
end

function Quaternion:addValue( value )
	return Quaternion:new( RL.QuaternionAddValue( self, value ) )
end

function Quaternion:subValue( value )
	return Quaternion:new( RL.QuaternionSubtractValue( self, value ) )
end

function Quaternion:identity()
	return Quaternion:new( RL.QuaternionIdentity() )
end

function Quaternion:length()
	return RL.QuaternionLength( self )
end

function Quaternion:normalize()
	return Quaternion:new( RL.QuaternionNormalize( self ) )
end

function Quaternion:invert()
	return Quaternion:new( RL.QuaternionInvert( self ) )
end

function Quaternion:scale( scalar )
	return Quaternion:new( RL.QuaternionScale( self, scalar ) )
end

function Quaternion:lerp( q2, value )
	return Quaternion:new( RL.QuaternionLerp( self, q2, value ) )
end

function Quaternion:nLerp( q2, value )
	return Quaternion:new( RL.QuaternionNLerp( self, q2, value ) )
end

function Quaternion:sLerp( q2, value )
	return Quaternion:new( RL.QuaternionSLerp( self, q2, value ) )
end

function Quaternion:fromVector3ToVector3( from, to )
	return Vector3:new( RL.QuaternionFromVector3ToVector3( from, to ) )
end

function Quaternion:fromMatrix( mat )
	return Quaternion:new( RL.QuaternionFromMatrix( mat ) )
end

function Quaternion:toMatrix()
	return Matrix:new( RL.QuaternionToMatrix( self ) )
end

function Quaternion:fromAxisAngle( axis, angle )
	return Quaternion:new( RL.QuaternionFromAxisAngle( axis, angle ) )
end

function Quaternion:toAxisAngle()
	local axis, angle = Quaternion:new( RL.QuaternionToAxisAngle( self ) )
	return Vector3:new( axis ), angle
end

function Quaternion:fromEuler( pitch, yaw, roll )
	return Quaternion:new( RL.QuaternionFromEuler( pitch, yaw, roll ) )
end

function Quaternion:toEuler()
	return Vector3:new( RL.QuaternionToEuler( self ) )
end

function Quaternion:transform( mat )
	return Quaternion:new( RL.QuaternionTransform( self, mat ) )
end

return Quaternion
