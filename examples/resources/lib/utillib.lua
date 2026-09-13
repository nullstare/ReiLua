local load = load

-- Define useful global functions.

-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local utillib = {}

function utillib.deepCopy( orig )
	local copy

	if type( orig ) == "table" then
		copy = {}

		for origKey, origValue in next, orig, nil do
			-- If object has clone method, use that.
			if type( origValue ) == "table" and type( origValue.clone ) == "function" then
				-- Note! deepCopy key if using other types than just int or string.
				-- copy[ utillib.deepCopy( origKey ) ] = origValue:clone()
				copy[ origKey ] = origValue:clone()
			else
				-- copy[ utillib.deepCopy( origKey ) ] = utillib.deepCopy( origValue )
				copy[ origKey ] = utillib.deepCopy( origValue )
			end
		end

		setmetatable( copy, utillib.deepCopy( getmetatable( orig ) ) )
	else -- number, string, boolean, etc.
		copy = orig
	end

	return copy
end

-- //TODO Needs review.
-- function utillib.shallowCopy( orig )
-- 	local copy

-- 	if type( orig ) == "table" then
-- 		copy = {}

-- 		for origKey, origValue in next, orig, nil do
-- 			-- If object has clone method, use that.
-- 			if type( origValue ) == "table" then
-- 				if type( origValue.clone ) == "function" then
-- 					copy[ origKey ] = origValue:clone()
-- 				else
-- 					copy[ origKey ] = origValue
-- 					setmetatable( copy[ origKey ], utillib.deepCopy( getmetatable( origValue ) ) )
-- 				end
-- 			else -- number, string, boolean, etc.
-- 				copy[ origKey ] = origValue
-- 			end
-- 		end

-- 		setmetatable( copy, utillib.deepCopy( getmetatable( orig ) ) )
-- 	else -- number, string, boolean, etc.
-- 		copy = orig
-- 	end

-- 	return copy
-- end

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

function utillib.insertTable( to, from, pos )
	if from[1] then
		for i, v in ipairs( from ) do
			table.insert( to, pos + i - 1 or #to + 1, v )
		end
	else
		for key, v in pairs( from ) do
			to[ key ] = v
		end
	end
end

function utillib.slice( t, first, last )
    local sub = {}

    for i = first, last or #t do
        sub[ #sub + 1 ] = t[i]
    end

    return sub
end

function utillib.split( string, sep )
	if sep == nil then
		sep = "%s"
	end

	local t = {}

	for str in string.gmatch( string, "([^"..sep.."]+)" ) do
		table.insert( t, str )
	end

	return t
end

-- Wrap angle between 0 to 360.
function utillib.wrapAngleDeg( angle )
	-- With positive angles.
	angle = math.fmod( angle, 360 )

	if angle < 0 then
		angle = angle + 360
	end

	return angle
end

-- Wrap angle between -180 to 180.
function utillib.wrapAngleDegNeg( angle )
	if angle < 0 then
		return math.fmod( angle, 360.0 ) + 360.0
	elseif 0 < 360.0 then
		return math.fmod( angle, 360.0 ) - 360.0
	else
		return angle
	end
end

-- Wrap angle between 0 to PI*2.
function utillib.wrapAngleRad( angle )
	angle = math.fmod( angle, RL.PI * 2 )

	if angle < 0 then
		angle = angle + RL.PI * 2
	end

	return angle
end

-- Wrap angle between -PI to PI.
function utillib.wrapAngleRadNeg( angle )
	if angle < 0 then
		return math.fmod( angle, RL.PI * 2 ) + RL.PI * 2
	elseif 0 < RL.PI * 2 then
		return math.fmod( angle, RL.PI * 2 ) - RL.PI * 2
	else
		return angle
	end
end

function utillib.lerp( a, b, f )
	return ( a * ( 1.0 - f ) ) + ( b * f )
end

-- Wrap angle between 0 to 360.
function utillib.angleLerpDeg( a, b, f )
	a = utillib.wrapAngleDeg( a )
	b = utillib.wrapAngleDeg( b )

	local delta = b - a

	if delta > 180 then
		delta = delta - 360
	elseif delta < -180 then
		delta = delta + 360
	end

	return utillib.wrapAngleDeg( a + delta * f )
end

-- Wrap angle between -180 to 180.
function utillib.angleLerpDegNeg( a, b, f )
	local diff = b - a

	if diff < -180 then
		return utillib.wrapAngleDeg( utillib.lerp( a, b + 360, f ) )
	elseif 180 < diff then
		return utillib.wrapAngleDeg( utillib.lerp( a, b - 360, f ) )
	else
		return utillib.lerp( a, b, f )
	end
end

-- Wrap angle between 0 to PI*2.
function utillib.angleLerpRad( a, b, f )
	a = utillib.wrapAngleRad( a )
	b = utillib.wrapAngleRad( b )

	local delta = b - a

	if delta > RL.PI then
		delta = delta - RL.PI * 2
	elseif delta < -RL.PI then
		delta = delta + RL.PI * 2
	end

	return utillib.wrapAngleRad( a + delta * f )
end

-- Wrap angle between -PI to PI.
function utillib.angleLerpRadNeg( a, b, f )
	local diff = b - a

	if diff < -RL.PI / 2 then
		return utillib.wrapAngleRad( utillib.lerp( a, b + RL.PI, f ) )
	elseif RL.PI / 2 < diff then
		return utillib.wrapAngleRad( utillib.lerp( a, b - RL.PI, f ) )
	else
		return utillib.lerp( a, b, f )
	end
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

function utillib.boolToNumber( bool )
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

function utillib.reverseTable( t )
	for i = 1, math.floor( #t / 2 ), 1 do
		t[i], t[ #t - i + 1 ] = t[ #t - i + 1 ], t[i]
	end
end

function utillib.randomFloat( min, max )
	return min + math.random() * ( max - min );
end

function utillib.shuffle( arr )
	for i = #arr, 2, -1 do
		local j = math.random(i)
		arr[i], arr[j] = arr[j], arr[i]
	end
end

function utillib.printBin( v )
	for i = 63, 0, -1 do
		if RL.BitGet( v, i ) then
			io.write( "1" )
		else
			io.write( "0" )
		end
	end
	print()
end

function utillib.capitalize( str )
	return string.format( "%s%s", str:sub( 1, 1 ):upper(), str:sub( 2, -1 ) )
end

function utillib.doString( str )
	local func, err = load( str )

	if func then
		local success, result = pcall( func )

		if success then
			return result
		else
			RL.TraceLog( RL.LOG_WARNING, "Execution error: "..result )
		end
	else
		RL.TraceLog( RL.LOG_WARNING, "Compilation error: "..err )
	end
end

function utillib.stringToTable( str )
	str = "return "..str
	local func, err = load( str )

	if func then
		local success, result = pcall( func )

		if success then
			return result
		else
			RL.TraceLog( RL.LOG_WARNING, "Execution error: "..result )
		end
	else
		RL.TraceLog( RL.LOG_WARNING, "Compilation error: "..err )
	end
end

function utillib.getArrMin( t )
	local min = t[1]

	for _, v in ipairs( t ) do
		min = math.min( min, v )
	end

	return min
end

function utillib.getArrMax( t )
	local max = t[1]

	for _, v in ipairs( t ) do
		max = math.min( max, v )
	end

	return max
end

-- Get table value from key chaing ex. t = player, keyChain = "position.x"
-- Would be equivalent to player.position.x
function utillib.getNested( t, keyChain )
	for key in string.gmatch( keyChain, "[^.]+" ) do
		t = t[ key ]

		if t == nil then
			return nil
		end
	end

	return t
end

-- Set table value from key chaing ex. t = player, keyChain = "position.x"
-- Would be equivalent to player.position.x
function utillib.setNested( t, keyChain, value )
	local chain = utillib.split( keyChain, "." )

	for i, key in ipairs( chain ) do
		if i < #chain then
			if t[ key ] == nil then
				t[ key ] = {}
			end

			t = t[ key ]
		else
			t[ key ] = value
		end

		if t == nil then
			return nil
		end
	end
end

function utillib.getNestedRef( t, keyChain )
	local lastKey = keyChain:gsub( ".*%.", "" )

	keyChain = keyChain:sub( 0, #keyChain - #lastKey - 1 )

	return utillib.getNested( t, keyChain ), lastKey
end

local function isObject( t )
	local mt = getmetatable( t )

	return mt and mt.__index
end

-- Consider empty table as array.
local function isArray( t )
	return type( t ) == "table" and ( t[1] ~= nil or #t == 0 ) and utillib.tableLen( t ) == 0
end

local function isArrayEqual( a, b )
	if #a ~= #b then
		return false
	end

	for i, v in ipairs( a ) do
		if v ~= b[i] then
			return false
		end
	end

	return true
end

-- Set dst values from src.
function utillib.deepReplace( src, dst )
	for key, srcV in next, src, nil do
		-- Arrays should be replaced.
		if type( srcV ) == "table" and type( dst[ key ] ) == "table"
		and not isObject( srcV ) and not isObject( dst[ key ] )
		and not isArray( srcV ) then
			utillib.deepReplace( srcV, dst[ key ] )
		else
			dst[ key ] = utillib.deepCopy( srcV )
		end
	end
end

-- Compare src content to target and return table of differences.
-- So everything src has and target doesn't have.
function utillib.deepDifferences( difs, src, target )
	local keep = false

	for key, srcV in next, src, nil do
		-- Arrays should be replaced.
		if type( srcV ) == "table" and type( target[ key ] ) == "table"
		and not isObject( srcV ) and not isObject( target[ key ] )
		and not isArray( srcV ) and not isArray( target[ key ] ) then
			difs[ key ] = {}
			local keepThis = utillib.deepDifferences( difs[ key ], srcV, target[ key ] )

			if not keepThis then
				difs[ key ] = nil
			else
				keep = true
			end
		elseif ( isArray( srcV ) and isArray( target[ key ] ) and not isArrayEqual( srcV, target[ key ] ) )
		or srcV ~= target[ key ] then
			difs[ key ] = utillib.deepCopy( srcV )
			keep = true
		end
	end

	return keep
end

return utillib
