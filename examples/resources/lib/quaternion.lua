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
		return Quaternion:newT( RL.QuaternionAdd( q1, q2 ) )
	end,
	__sub = function( q1, q2 )
		return Quaternion:newT( RL.QuaternionSubtract( q1, q2 ) )
	end,
	__mul = function( q1, q2 )
		return Quaternion:newT( RL.QuaternionMultiply( q1, q2 ) )
	end,
	__div = function( q1, q2 )
		return Quaternion:newT( RL.QuaternionDivide( q1, q2 ) )
	end,
	__unm = function( q )
		return Quaternion:newT( RL.QuaternionInvert( q ) )
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
	local object = setmetatable( {}, metatable )

	object.x = x or 0
	object.y = y or 0
	object.z = z or 0
	object.w = w or 1

	return object
end

function Quaternion:newT( t )
	local object = setmetatable( {}, metatable )

	object.x, object.y, object.z, object.w = table.unpack( t )

	return object
end

function Quaternion:newQ( q )
	local object = setmetatable( {}, metatable )

	object.x = q.x
	object.y = q.y
	object.z = q.z
	object.w = q.w

	return object
end

function Quaternion:set( x, y, z, w )
	self.x = x or 0
	self.y = y or 0
	self.z = z or 0
	self.w = w or 1
end

function Quaternion:setT( t )
	self.x, self.y, self.z, self.w = table.unpack( t )
end

function Quaternion:setQ( q )
	self.x = q.x
	self.y = q.y
	self.z = q.z
	self.w = q.w
end

function Quaternion:serialize()
	return "Quaternion:new("..self.x..","..self.y..","..self.z..","..self.w..")"
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
	return Quaternion:newT( RL.QuaternionAddValue( self, value ) )
end

function Quaternion:subValue( value )
	return Quaternion:newT( RL.QuaternionSubtractValue( self, value ) )
end

function Quaternion:identity()
	return Quaternion:newT( RL.QuaternionIdentity() )
end

function Quaternion:length()
	return RL.QuaternionLength( self )
end

function Quaternion:normalize()
	return Quaternion:newT( RL.QuaternionNormalize( self ) )
end

function Quaternion:invert()
	return Quaternion:newT( RL.QuaternionInvert( self ) )
end

function Quaternion:scale( scalar )
	return Quaternion:newT( RL.QuaternionScale( self, scalar ) )
end

function Quaternion:lerp( q2, value )
	return Quaternion:newT( RL.QuaternionLerp( self, q2, value ) )
end

function Quaternion:nLerp( q2, value )
	return Quaternion:newT( RL.QuaternionNLerp( self, q2, value ) )
end

function Quaternion:sLerp( q2, value )
	return Quaternion:newT( RL.QuaternionSLerp( self, q2, value ) )
end

function Quaternion:fromVector3ToVector3( from, to )
	return Vector3:newT( RL.QuaternionFromVector3ToVector3( from, to ) )
end

function Quaternion:fromMatrix( mat )
	return Quaternion:newT( RL.QuaternionFromMatrix( mat ) )
end

function Quaternion:toMatrix()
	return Matrix:newT( RL.QuaternionToMatrix( self ) )
end

function Quaternion:fromAxisAngle( axis, angle )
	return Quaternion:newT( RL.QuaternionFromAxisAngle( axis, angle ) )
end

function Quaternion:toAxisAngle()
	local axis, angle = Quaternion:newT( RL.QuaternionToAxisAngle( self ) )
	return Vector3:new( axis ), angle
end

function Quaternion:fromEuler( pitch, yaw, roll )
	return Quaternion:newT( RL.QuaternionFromEuler( pitch, yaw, roll ) )
end

function Quaternion:toEuler()
	return Vector3:newT( RL.QuaternionToEuler( self ) )
end

function Quaternion:transform( mat )
	return Quaternion:newT( RL.QuaternionTransform( self, mat ) )
end

-- Temp pre generated objects to avoid "slow" table generation.

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, Quaternion:new( 0, 0, 0, 1 ) )
end

function Quaternion:temp( x, y, z, w )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.x = x or 0
	object.y = y or 0
	object.z = z or 0
	object.w = w or 1

	return object
end

function Quaternion:tempT( t )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.x, object.y, object.z, object.w = table.unpack( t )

	return object
end

function Quaternion:tempQ( q )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.x = q.x
	object.y = q.y
	object.z = q.z
	object.w = q.w

	return object
end

function Quaternion:getTempId()
	return curTemp
end

return Quaternion
