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
		Vector3:new( self.max.x, self.min.y, self.min.z ),		-- Down back right.
		Vector3:new( self.min.x, self.min.y, self.max.z ),		-- Down front left.
		Vector3:new( self.max.x, self.min.y, self.max.z ),		-- Down front right.
		Vector3:new( self.min.x, self.max.y, self.min.z ),		-- Up back left.
		Vector3:new( self.max.x, self.max.y, self.min.z ),		-- Up back right.
		Vector3:new( self.min.x, self.max.y, self.max.z ),		-- Up front left.
		self.max:clone(),									-- Up front right.
	}
end

function BoundingBox:checkCollisionBox( b )
	return RL.CheckCollisionBoxes( self:maxToPos(), b:maxToPos() )
end

function BoundingBox:checkCollisionSphere( center, radius )
	return RL.CheckCollisionBoxSphere( self:maxToPos(), center, radius )
end

function BoundingBox:getRayCollision( ray )
	return RL.GetRayCollisionBox( ray, self:maxToPos() )
end

-- Max to position from size.
function BoundingBox:maxToPos()
	return BoundingBox:new( self.min, self.min + self.max )
end

-- Max to size from position.
function BoundingBox:maxToSize()
	return BoundingBox:new( self.min, self.max - self.min )
end

return BoundingBox
