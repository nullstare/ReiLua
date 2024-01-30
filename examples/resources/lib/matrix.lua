-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local function deepCopy( orig )
    local copy

    if type( orig ) == "table" then
        copy = {}

        for origKey, origValue in next, orig, nil do
			-- If object has clone method, use that.
			copy[ deepCopy( origKey ) ] = deepCopy( origValue )
        end

        -- setmetatable( copy, utillib.deepCopy( getmetatable( orig ) ) )
    else -- number, string, boolean, etc.
        copy = orig
    end

    return copy
end

local Matrix = {}
Matrix.meta = {
	__index = Matrix,
	__tostring = function( m )
		return "{\n"
		.."  {"..m.m[1][1]..", "..m.m[1][2]..", "..m.m[1][3]..", "..m.m[1][4].."},\n"
		.."  {"..m.m[2][1]..", "..m.m[2][2]..", "..m.m[2][3]..", "..m.m[2][4].."},\n"
		.."  {"..m.m[3][1]..", "..m.m[3][2]..", "..m.m[3][3]..", "..m.m[3][4].."},\n"
		.."  {"..m.m[3][1]..", "..m.m[3][2]..", "..m.m[3][3]..", "..m.m[3][4].."},\n"
		.."}"
	end,
	__add = function( m1, m2 )
		return Matrix:new( RL.MatrixAdd( m1, m2 ) )
	end,
	__sub = function( m1, m2 )
		return Matrix:new( RL.MatrixSubtract( m1, m2 ) )
	end,
	__mul = function( m1, m2 )
		return Matrix:new( RL.MatrixMultiply( m1, m2 ) )
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Matrix:new( m )
	local object = setmetatable( {}, Matrix.meta )

	if type( m ) == "table" then
		object.m = deepCopy( m )
	else
		object.m = RL.MatrixIdentity()
	end

	return object
end

function Matrix:set( m )
	if type( m ) == "table" then
		self.m = deepCopy( m )
	else
		self.m = RL.MatrixIdentity()
	end
end

-- function Matrix:arr()
-- 	return self.m
-- end

-- function Matrix:unpack()
-- 	return self.m
-- end

function Matrix:clone()
	return Matrix:new( self )
end

function Matrix:determinant()
	return RL.MatrixDeterminant( self )
end

function Matrix:trace()
	return RL.MatrixTranspose( self )
end

function Matrix:transpose()
	return Matrix:new( RL.MatrixTranspose( self ) )
end

function Matrix:multiply( m2 )
	return Matrix:new( RL.MatrixMultiply( self, m2 ) )
end

function Matrix:invert()
	return Matrix:new( RL.MatrixInvert( self ) )
end

function Matrix:identity()
	return Matrix:new( RL.MatrixIdentity() )
end

function Matrix:translate( translate )
	return Matrix:new( RL.MatrixTranslate( translate ) )
end

function Matrix:rotate( axis, angle )
	return Matrix:new( RL.MatrixRotate( axis, angle ) )
end

function Matrix:rotateX( angle )
	return Matrix:new( RL.MatrixRotateX( angle ) )
end

function Matrix:rotateY( angle )
	return Matrix:new( RL.MatrixRotateY( angle ) )
end

function Matrix:rotateZ( angle )
	return Matrix:new( RL.MatrixRotateZ( angle ) )
end

function Matrix:rotateXYZ( angles )
	return Matrix:new( RL.MatrixRotateXYZ( angles ) )
end

function Matrix:rotateZYX( angles )
	return Matrix:new( RL.MatrixRotateZYX( angles ) )
end

function Matrix:scale( scale )
	return Matrix:new( RL.MatrixScale( scale ) )
end

function Matrix:frustrum( left, right, bottom, top, near, far )
	return Matrix:new( RL.MatrixFrustum( left, right, bottom, top, near, far ) )
end

function Matrix:perspective( fovy, aspect, near, far )
	return Matrix:new( RL.MatrixPerspective( fovy, aspect, near, far ) )
end

function Matrix:ortho( left, right, bottom, top, near, far )
	return Matrix:new( RL.MatrixOrtho( left, right, bottom, top, near, far ) )
end

function Matrix:lookAt( eye, target, up )
	return Matrix:new( RL.MatrixLookAt( eye, target, up ) )
end

return Matrix
