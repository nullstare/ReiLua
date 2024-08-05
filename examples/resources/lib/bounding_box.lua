-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector3 = Vector3 or require( "vector3" )

local BoundingBox = {}
local metatable = {
	__index = BoundingBox,
	__tostring = function( b )
		return "{{"..tostring( b.min.x )..", "..tostring( b.min.y )..", "..tostring( b.min.z ).."}, {"
		..tostring( b.max.x )..", "..tostring( b.max.y )..", "..tostring( b.max.z ).."}}"
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
	__eq = function( b1, b2 )
		return b1.min == b2.min and b1.max == b2.max
	end,
}

--- Expects format { ... }, { ... }
function BoundingBox:new( min, max )
	local object = setmetatable( {}, metatable )

	object.min = Vector3:newT( min )
	object.max = Vector3:newT( max )

    return object
end

--- Expects format { { ... }, { ... } }
function BoundingBox:newT( t )
	local object = setmetatable( {}, metatable )

	object.min = Vector3:newT( t[1] )
	object.max = Vector3:newT( t[2] )

    return object
end

--- Expects format { Vector3, Vector3 }
function BoundingBox:newV( min, max )
	local object = setmetatable( {}, metatable )

	object.min = min:clone()
	object.max = max:clone()

    return object
end

--- Expects format BoundingBox
function BoundingBox:newB( b )
	local object = setmetatable( {}, metatable )

	object.min = b.min:clone()
	object.max = b.max:clone()

    return object
end

function BoundingBox:serialize()
	return table.concat( { "BoundingBox:new({", self.min.x, ",", self.min.y, ",", self.min.z, "},{", self.max.x, ",", self.max.y, ",", self.max.z, "})" } )
end

--- Expects format { ... }, { ... }
function BoundingBox:set( min, max )
	self.min:setT( min )
	self.max:setT( max )
end

--- Expects format { { ... }, { ... } }
function BoundingBox:setT( t )
	self.min:setT( t[1] )
	self.max:setT( t[2] )
end

--- Expects format { Vector3, Vector3 }
function BoundingBox:setV( min, max )
	self.min:setV( min )
	self.max:setV( max )
end

--- Expects format BoundingBox
function BoundingBox:setB( b )
	self.min:setV( b.min )
	self.max:setV( b.max )
end

function BoundingBox:arr()
	return { { self.min.x, self.min.y, self.min.z }, { self.max.x, self.max.y, self.max.z } }
end

function BoundingBox:unpack()
	return self.min, self.max
end

function BoundingBox:clone()
	return BoundingBox:newB( self )
end

function BoundingBox:scale( scalar )
	return BoundingBox:newV( self.min, self.max:scale( scalar ) )
end

function BoundingBox:getPoints()
	return {
		self.min:clone(),									-- Down back left.
		Vector3:new( self.max.x, self.min.y, self.min.z ),	-- Down back right.
		Vector3:new( self.min.x, self.min.y, self.max.z ),	-- Down front left.
		Vector3:new( self.max.x, self.min.y, self.max.z ),	-- Down front right.
		Vector3:new( self.min.x, self.max.y, self.min.z ),	-- Up back left.
		Vector3:new( self.max.x, self.max.y, self.min.z ),	-- Up back right.
		Vector3:new( self.min.x, self.max.y, self.max.z ),	-- Up front left.
		self.max:clone(),									-- Up front right.
	}
end

function BoundingBox:checkCollisionBox( b )
	return RL.CheckCollisionBoxes( self, b )
end

function BoundingBox:checkCollisionSphere( center, radius )
	return RL.CheckCollisionBoxSphere( self, center, radius )
end

function BoundingBox:checkCollisionPoint( point )
	return self.min.x <= point.x
	and self.min.y <= point.y
	and self.min.z <= point.z
	and point.x <= self.max.x
	and point.y <= self.max.y
	and point.z <= self.max.z
end

function BoundingBox:getRayCollision( ray )
	return RL.GetRayCollisionBox( ray, self )
end

-- Max to position from size.
function BoundingBox:maxToPos()
	return BoundingBox:newV( self.min, self.min + self.max )
end

-- Max to size from position.
function BoundingBox:maxToSize()
	return BoundingBox:newV( self.min, self.max - self.min )
end

-- MAS stands for max as size. These functions handles max as size instead of position.

function BoundingBox:checkCollisionBoxMASBox( b )
	return RL.CheckCollisionBoxes( self:tempMaxToPos(), b )
end

function BoundingBox:checkCollisionBoxMAS( b )
	return RL.CheckCollisionBoxes( self:tempMaxToPos(), b:tempMaxToPos() )
end

function BoundingBox:checkCollisionSphereMAS( center, radius )
	return RL.CheckCollisionBoxSphere( self:tempMaxToPos(), center, radius )
end

function BoundingBox:checkCollisionPointMAS( point )
	local max = self.min + self.max

	return self.min.x <= point.x
	and self.min.y <= point.y
	and self.min.z <= point.z
	and point.x <= max.x
	and point.y <= max.y
	and point.z <= max.z
end

function BoundingBox:getRayCollisionMAS( ray )
	return RL.GetRayCollisionBox( ray, self:tempMaxToPos() )
	-- return RL.GetRayCollisionBox( ray, self:maxToPos() )
end

-- Temp pre generated objects to avoid "slow" table generation.

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, BoundingBox:new( { 0, 0, 0 }, { 0, 0, 0 } ) )
end

--- Expects format { ... }, { ... }
function BoundingBox:temp( min, max )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.min = Vector3:tempT( min )
	object.max = Vector3:tempT( max )

	return object
end

--- Expects format { { ... }, { ... } }
function BoundingBox:tempT( t )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.min = Vector3:tempT( t[1] )
	object.max = Vector3:tempT( t[2] )

	return object
end

--- Expects format { Vector3, Vector3 }
function BoundingBox:tempV( min, max )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.min = Vector3:tempV( min )
	object.max = Vector3:tempV( max )

	return object
end

--- Expects format BoundingBox
function BoundingBox:tempB( b )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.min = Vector3:tempV( b.min )
	object.max = Vector3:tempV( b.max )

	return object
end

-- Max to position from size.
function BoundingBox:tempMaxToPos()
	return BoundingBox:tempV( self.min, Vector3:tempT( RL.Vector3Add( self.min, self.max ) ) )
end

-- Max to size from position.
function BoundingBox:tempMaxToSize()
	return BoundingBox:tempV( self.min, Vector3:tempT( RL.Vector3Subtract( self.max, self.min ) ) )
end

function BoundingBox:getTempId()
	return curTemp
end

return BoundingBox
