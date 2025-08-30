-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Matrix = {}
local metatable = {
	__index = Matrix,
	__tostring = function( m )
		return "{\n"
		.."  {"..m[1][1]..", "..m[1][2]..", "..m[1][3]..", "..m[1][4].."},\n"
		.."  {"..m[2][1]..", "..m[2][2]..", "..m[2][3]..", "..m[2][4].."},\n"
		.."  {"..m[3][1]..", "..m[3][2]..", "..m[3][3]..", "..m[3][4].."},\n"
		.."  {"..m[4][1]..", "..m[4][2]..", "..m[4][3]..", "..m[4][4].."},\n"
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

function Matrix:copyMatrix( orig )
	if orig ~= nil then
		for y = 1, 4 do
			for x = 1, 4 do
				if orig[x][y] ~= nil then
					self[x][y] = orig[x][y]
				end
			end
		end
	end
end

function Matrix:new( m )
	local object = setmetatable( {}, metatable )

	-- Raylib style transposed matrix.
	for x = 1, 4 do
		object[x] = {}
		for y = 1, 4 do
			table.insert( object[x], m[x][y] )
		end
	end

	return object
end

function Matrix:set( m )
	self:copyMatrix( m )
end

function Matrix:arr()
	return {
		self[1][1], self[2][1], self[3][1], self[4][1],
		self[1][2], self[2][2], self[3][2], self[4][2],
		self[1][3], self[2][3], self[3][3], self[4][3],
		self[1][4], self[2][4], self[3][4], self[4][4],
	}
end

function Matrix:serialize()
	local str = { "Matrix:new({" }

	for i, row in ipairs( self ) do
		table.insert( str, "{" )

		for c, v in ipairs( row ) do
			table.insert( str, v )
			if c < 4 then
				table.insert( str, "," )
			end
		end
		table.insert( str, "}" )
		if i < 4 then
			table.insert( str, "," )
		end
	end
	table.insert( str, "})" )

	return table.concat( str )
end

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

-- Temp pre generated objects to avoid "slow" table generation.

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, Matrix:new( RL.MatrixIdentity() ) )
end

function Matrix:temp( m )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object:copyMatrix( m )

	return object
end

function Matrix:getTempId()
	return curTemp
end

return Matrix
