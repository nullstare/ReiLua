-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector2 = {}
local metatable = {
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
	__len = function()
		return 2
	end,
	__eq = function( v1, v2 )
		return RL.Vector2Equals( v1, v2 ) == 1
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Vector2:new( x, y )
	if type( x ) == "table" then
		x, y = table.unpack( x )
	elseif type( x ) == "nil" then
		x, y = 0, 0
	end

	local object = setmetatable( {}, metatable )

	object.x = x
	object.y = y

	return object
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

function Vector2:floor()
	return Vector2:new( math.floor( self.x ), math.floor( self.y ) )
end

function Vector2:ceil()
	return Vector2:new( math.ceil( self.x ), math.ceil( self.y ) )
end

function Vector2:addValue( value )
	return Vector2:new( RL.Vector2AddValue( self, value ) )
end

function Vector2:subValue( value )
	return Vector2:new( RL.Vector2SubtractValue( self, value ) )
end

function Vector2:length()
	return RL.Vector2Length( self )
end

function Vector2:lengthSqr()
	return RL.Vector2LengthSqr( self )
end

function Vector2:dot( v2 )
	return RL.Vector2DotProduct( self, v2 )
end

function Vector2:distance( v2 )
	return RL.Vector2Distance( self, v2 )
end

function Vector2:distanceSqr( v2 )
	return RL.Vector2DistanceSqr( self, v2 )
end

function Vector2:angle( v2 )
	return RL.Vector2Angle( self, v2 )
end

function Vector2:lineAngle( v2 )
	return RL.Vector2LineAngle( self, v2 )
end

function Vector2:atan2()
	return math.atan( self.y, self.x )
end

function Vector2:scale( scale )
	return Vector2:new( RL.Vector2Scale( self, scale ) )
end

function Vector2:normalize()
	return Vector2:new( RL.Vector2Normalize( self ) )
end

function Vector2:transform( mat )
	return Vector2:new( RL.Vector2Transform( self, mat ) )
end

function Vector2:lerp( v2, value )
	return Vector2:new( RL.Vector2Lerp( self, v2, value ) )
end

function Vector2:reflect( normal )
	return Vector2:new( RL.Vector2Reflect( self, normal ) )
end

function Vector2:rotate( angle )
	return Vector2:new( RL.Vector2Rotate( self, angle ) )
end

function Vector2:moveTowards( target, maxDistance )
	return Vector2:new( RL.Vector2MoveTowards( self, target, maxDistance ) )
end

function Vector2:invert()
	return Vector2:new( RL.Vector2Invert( self ) )
end

function Vector2:clamp( min, max )
	return Vector2:new( RL.Vector2Clamp( self, min, max ) )
end

function Vector2:clampValue( min, max )
	return Vector2:new( RL.Vector2ClampValue( self, min, max ) )
end

function Vector2:equals( v2 )
	return RL.Vector2Equals( self, v2 )
end

function Vector2:addEq( v2 )
	self.x = self.x + v2.x
	self.y = self.y + v2.y
end

function Vector2:subEq( v2 )
	self.x = self.x - v2.x
	self.y = self.y - v2.y
end

function Vector2:mulEq( v2 )
	self.x = self.x * v2.x
	self.y = self.y * v2.y
end

function Vector2:divEq( v2 )
	self.x = self.x / v2.x
	self.y = self.y / v2.y
end

return Vector2
