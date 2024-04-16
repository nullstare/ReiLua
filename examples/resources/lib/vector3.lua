-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector2 = require( "vector2" )

local Vector3 = {}
local metatable = {
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
	__len = function()
		return 3
	end,
	__eq = function( v1, v2 )
		return RL.Vector3Equals( v1, v2 ) == 1
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Vector3:new( x, y, z )
	local object = setmetatable( {}, metatable )

	object.x = x or 0
	object.y = y or 0
	object.z = z or 0

	return object
end

function Vector3:newT( t )
	local object = setmetatable( {}, metatable )

	object.x, object.y, object.z = table.unpack( t )

	return object
end

function Vector3:set( x, y, z )
	self.x = x or 0
	self.y = y or 0
	self.z = z or 0
end

function Vector3:setT( t )
	self.x, self.y, self.z = table.unpack( t )
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

function Vector3:getVectorXY()
	return Vector2:new( self.x, self.y )
end

function Vector3:getVectorXZ()
	return Vector2:new( self.x, self.z )
end

function Vector3:getVectorZY()
	return Vector2:new( self.z, self.y )
end

function Vector3:abs()
	return Vector3:new( math.abs( self.x ), math.abs( self.y ), math.abs( self.z ) )
end

function Vector3:min( v2 )
	return Vector3:newT( RL.Vector3Min( self, v2 ) )
end

function Vector3:max( v2 )
	return Vector3:newT( RL.Vector3Max( self, v2 ) )
end

function Vector3:floor()
	return Vector3:new( math.floor( self.x ), math.floor( self.y ), math.floor( self.z ) )
end

function Vector3:ceil()
	return Vector3:new( math.ceil( self.x ), math.ceil( self.y ), math.ceil( self.z ) )
end

function Vector3:addValue( value )
	return Vector3:newT( RL.Vector3AddValue( self, value ) )
end

function Vector3:subValue( value )
	return Vector3:newT( RL.Vector3SubtractValue( self, value ) )
end

function Vector3:scale( scalar )
	return Vector3:newT( RL.Vector3Scale( self, scalar ) )
end

function Vector3:cross( v2 )
	return Vector3:newT( RL.Vector3CrossProduct( self, v2 ) )
end

function Vector3:perpendicular()
	return Vector3:newT( RL.Vector3Perpendicular( self ) )
end

function Vector3:length()
	return RL.Vector3Length( self )
end

function Vector3:lengthSqr()
	return RL.Vector3LengthSqr( self )
end

function Vector3:dot( v2 )
	return RL.Vector3DotProduct( self, v2 )
end

function Vector3:distance( v2 )
	return RL.Vector3Distance( self, v2 )
end

function Vector3:distanceSqr( v2 )
	return RL.Vector3DistanceSqr( self, v2 )
end

function Vector3:angle( v2 )
	return RL.Vector3Angle( self, v2 )
end

function Vector3:negate()
	return Vector3:newT( RL.Vector3Negate( self ) )
end

function Vector3:normalize()
	return Vector3:newT( RL.Vector3Normalize( self ) )
end

function Vector3:orthoNormalize( v2 )
	local r1, r2 = RL.Vector3OrthoNormalize( self, v2 )
	return Vector3:new( r1[1], r1[2], r1[3] ), Vector3:new( r2[1], r2[2], r2[3] )
end

function Vector3:transform( mat )
	return Vector3:newT( RL.Vector3Transform( self, mat ) )
end

function Vector3:rotateByQuaternion( q )
	return Vector3:newT( RL.Vector3RotateByQuaternion( self, q ) )
end

function Vector3:rotateByAxisAngle( axis, angle )
	return Vector3:newT( RL.Vector3RotateByAxisAngle( self, axis, angle ) )
end

function Vector3:lerp( v2, value )
	return Vector3:newT( RL.Vector3Lerp( self, v2, value ) )
end

function Vector3:reflect( normal )
	return Vector3:newT( RL.Vector3Reflect( self, normal ) )
end

function Vector3:invert()
	return Vector3:newT( RL.Vector3Invert( self ) )
end

function Vector3:clamp( min, max )
	return Vector3:newT( RL.Vector3Clamp( self, min, max ) )
end

function Vector3:clampValue( min, max )
	return Vector3:newT( RL.Vector3ClampValue( self, min, max ) )
end

function Vector3:equals( v2 )
	return RL.Vector3Equals( self, v2 )
end

function Vector3:addEq( v2 )
	self.x = self.x + v2.x
	self.y = self.y + v2.y
	self.z = self.z + v2.z
end

function Vector3:subEq( v2 )
	self.x = self.x - v2.x
	self.y = self.y - v2.y
	self.z = self.z - v2.z
end

function Vector3:mulEq( v2 )
	self.x = self.x * v2.x
	self.y = self.y * v2.y
	self.z = self.z * v2.z
end

function Vector3:divEq( v2 )
	self.x = self.x / v2.x
	self.y = self.y / v2.y
	self.z = self.z / v2.z
end

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, Vector3:new( 0, 0, 0 ) )
end

-- Uses pre generated objects to avoid "slow" table generation.
function Vector3:temp( x, y, z )
	local object = tempPool[ curTemp ]
	curTemp = curTemp + 1

	if TEMP_COUNT < curTemp then
		curTemp = 1
	end

	object.x = x or 0
	object.y = y or 0
	object.z = z or 0

	return object
end

-- Uses pre generated objects to avoid "slow" table generation.
function Vector3:tempT( t )
	local object = tempPool[ curTemp ]
	curTemp = curTemp + 1

	if TEMP_COUNT < curTemp then
		curTemp = 1
	end

	object.x, object.y, object.z = table.unpack( t )

	return object
end

function Vector3:getTempId()
	return curTemp
end

return Vector3
