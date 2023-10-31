-- Define useful global functions.

local utillib = {}

function utillib.tableClone( org )
	return { table.unpack( org ) }
end

function utillib.deepCopy( orig )
    local copy

    if type( orig ) == "table" then
        copy = {}

        for origKey, origValue in next, orig, nil do
			-- If object has clone method, use that.
			if type( origValue ) == "table" and type( origValue.clone ) == "function" then
				copy[ utillib.deepCopy( origKey ) ] = origValue:clone()
			else
				copy[ utillib.deepCopy( origKey ) ] = utillib.deepCopy( origValue )
			end
        end

        setmetatable( copy, utillib.deepCopy( getmetatable( orig ) ) )
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

function utillib.utf8Sub( s, i, j )
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

-- Use with dictionary style tables.
function utillib.tableLen( t )
    local count = 0

	for _ in pairs(t) do
		count = count + 1
	end

    return count
end

function utillib.split( str, sep )
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
	if angle < 0 then
		return math.fmod( angle, 360.0 ) + 360.0
	else
		return math.fmod( angle, 360.0 )
	end
end

function utillib.wrapAngleRad( angle )
	if angle < 0 then
		return math.fmod( angle, RL.PI * 2 ) + RL.PI * 2
	else
		return math.fmod( angle, RL.PI * 2 )
	end
end

function utillib.lerp( a, b, f )
	return ( a * ( 1.0 - f ) ) + ( b * f )
end

function utillib.toBoolean( v )
	if type( v ) == "string" then
		if v == "1" or string.lower( v ) == "true" then
			return true
		elseif v == "0" or string.lower( v ) == "false" then
			return false
		end
	elseif type( v ) == "number" then
		return 0 < v
	end

	return false
end

function utillib.bool2Number( bool )
	return bool and 1 or 0
end

-- Print table content.
function utillib.printt( t )
	print( tostring(t).." = {" )

	for i, item in pairs( t ) do
		print( "\t"..tostring(i).." = "..tostring( item ) )
	end

	print( "}" )
end

-- Move secuence of elements inside table.
function utillib.tableMove( t, src, len, dest )
    local copy = table.move( t, src, src + len - 1, 1, {} )

    if src >= dest then
        table.move( t, dest, src - 1, dest + len )
    else 
        table.move( t, src + len, dest + len - 1, src )
    end

    table.move( copy, 1, len, dest, t )
end

return utillib
