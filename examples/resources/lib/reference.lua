local Reference = {}
local metatable = {
	__index = Reference,
	__tostring = function( r )
		return tostring( r.t[ r.k ] )
	end,
	__add = function( r, v )
		return r.t[ r.k ] + v
	end,
	__sub = function( r, v )
		return r.t[ r.k ] - v
	end,
	__mul = function( r, v )
		return r.t[ r.k ] * v
	end,
	__div = function( r, v )
		return r.t[ r.k ] / v
	end,
	__mod = function( r, v )
		return math.fmod( r.t[ r.k ], v )
	end,
	__pow = function( r, v )
		return r.t[ r.k ] ^ v
	end,
	__unm = function( r )
		return -r.t[ r.k ]
	end,
	__eq = function( r, v )
		return r.t[ r.k ] == v
	end,
	__len = function( r )
		return #r.t[ r.k ]
	end,
	__lt = function( r, v )
		return r.t[ r.k ] < v
	end,
	__le = function( r, v )
		return r.t[ r.k ] <= v
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
	__call = function( r, ... )
		return r.t[ r.k ]( ... )
	end,
}

-- Table and key. Note that k should be name of the variable so the type must be string.
function Reference:new( t, k )
	local object = setmetatable( {}, metatable )

	object.t = t
	object.k = k

	return object
end

-- Set new reference. Table and key. Note that k should be name of the variable so the type must be string.
function Reference:ref( t, k )
	self.t = t
	self.k = k
end

function Reference:set( v )
	self.t[ self.k ] = v
end

function Reference:get()
	return self.t[ self.k ]
end

function Reference:unpack()
	return self.t, self.k
end

function Reference:clone()
	return Reference:new( self.t, self.k )
end

function Reference:addEq( v )
	self.t[ self.k ] = self.t[ self.k ] + v
end

function Reference:subEq( v )
	self.t[ self.k ] = self.t[ self.k ] - v
end

function Reference:mulEq( v )
	self.t[ self.k ] = self.t[ self.k ] * v
end

function Reference:divEq( v )
	self.t[ self.k ] = self.t[ self.k ] / v
end

return Reference
