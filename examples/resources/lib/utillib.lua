-- Define useful global stuff.

local utillib = {}

function utillib.tableClone( org )
	return { table.unpack( org ) }
end

function utillib.deepCopy( orig )
    local copy

    if type( orig ) == "table" then
        copy = {}

        for orig_key, orig_value in next, orig, nil do
			-- If object has clone method use that. Mainly for vector libraries.
			if type( orig_value ) == "table" and type( orig_value.clone ) == "function" then
				copy[ utillib.deep_copy( orig_key ) ] = orig_value:clone()
			else
				copy[ utillib.deep_copy( orig_key ) ] = utillib.deep_copy( orig_value )
			end
        end

        setmetatable( copy, utillib.deep_copy( getmetatable( orig ) ) )
    else -- number, string, boolean, etc.
        copy = orig
    end

    return copy
end

function utillib.sign( v )
	if 0 <= v then
		return 1
	elseif v < 0 then
		return -1
	end
end

function utillib.clamp( val, min, max )
	return math.max( min, math.min( val, max ) )
end

-- Returns changed value ( value to be changed, index, bit )
function utillib.setBit( v, i, b )
	if b then
		return v | 1 << i
	else 
		return v & ~( 1 << i )
	end
end

function utillib.toggleBit( v, i )
	return v ~ ( 1 << i )
end

function utillib.getBit( v, i )
	if v == nil then
		return false
	end

	return v & ( 1 << i ) > 0
end

function utillib.utf8Sub( s, i, j )
	assert( utillib.isstring( s ) )

	i = i or 1
	j = j or -1

	if i < 1 or j < 1 then
	   local n = utf8.len(s)
	   if not n then return nil end
	   if i < 0 then i = n + 1 + i end
	   if j < 0 then j = n + 1 + j end
	   if i < 0 then i = 1 elseif i > n then i = n end
	   if j < 0 then j = 1 elseif j > n then j = n end
	end

	if j < i then return "" end

	i = utf8.offset( s, i )
	j = utf8.offset( s, j + 1 )
	
	if i and j then
		return s:sub( i, j - 1 )
	elseif i then
		return s:sub( i )
	else
		return ""
	end
end

function utillib.round( v )
	return math.tointeger( v + 0.5 - ( v + 0.5 ) % 1 )
end

function utillib.tableLen( t )
	if not utillib.istable( t ) then
		return 0
	end

    local count = 0

	for _ in pairs(t) do
		count = count + 1
	end

    return count
end

function utillib.split( str, sep )
	assert( utillib.isstring( str ) )

	if sep == nil then
		sep = "%s"
	end

	local t = {}

	for str in string.gmatch( str, "([^"..sep.."]+)" ) do
		table.insert( t, str )
	end

	return t
end

function utillib.wrapAngleDeg( angle )
	assert( utillib.isnumber( angle ) )

	if angle < 0 then
		return math.fmod( angle, 360.0 ) + 360.0
	else
		return math.fmod( angle, 360.0 )
	end
end

function utillib.wrapAngleRad( angle )
	assert( utillib.isnumber( angle ) )

	if angle < 0 then
		return math.fmod( angle, PI * 2 ) + PI * 2
	else
		return math.fmod( angle, PI * 2 )
	end
end

function utillib.lerp( a, b, f )
	return ( a * ( 1.0 - f ) ) + ( b * f )
end

function utillib.toBoolean( v )
	if utillib.isstring( v ) then
		if v == "1" or string.lower( v ) == "true" then
			return true
		elseif v == "0" or string.lower( v ) == "false" then
			return false
		end
	elseif utillib.isnumber( v ) then
		return 0 < v
	end

	return false
end

return utillib
