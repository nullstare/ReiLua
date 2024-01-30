-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Rune = {}
Rune.meta = {
	__index = Rune,
	__tostring = function( r )
		return r.string
	end,
	__len = function( r )
		return RL.GetCodepointCount( r.string )
	end,
	__eq = function( r1, r2 )
		return r1.string == r2.string
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Rune:new( string )
	if type( string ) == "table" then
		string = RL.LoadUTF8( string )
	elseif type( string ) == "nil" then
		string = ""
	end

	local object = setmetatable( {}, Rune.meta )

	object.string = string

	return object
end

function Rune:set( string )
	if type( string ) == "table" then
		string = RL.LoadUTF8( string )
	elseif type( string ) == "nil" then
		string = ""
	end

	self.string = string
end

function Rune:clone()
	return Rune:new( self.string )
end

function Rune:len()
	return RL.GetCodepointCount( self.string )
end

function Rune:getCodepoints()
	return RL.LoadCodepoints( self.string )
end

function Rune:getCodepoint( index )
	local codepoint = RL.GetCodepoint( self:sub( index, index ) )
	return codepoint
end

function Rune:getCodepointSize( index )
	local _, codepointSize = RL.GetCodepoint( self:sub( index, index ) )
	return codepointSize
end

function Rune:insert( pos, string )
	local codepoints = self:getCodepoints()

	for i, codepoint in ipairs( RL.LoadCodepoints( string ) ) do
		table.insert( codepoints, pos + i - 1, codepoint )
	end
	self.string = RL.LoadUTF8( codepoints )
end

function Rune:sub( i, j )
	local codepoints = self:getCodepoints()
	return RL.LoadUTF8( { table.unpack( codepoints, i, j ) } )
end

function Rune:gsub( pattern, repl )
	return string.gsub( self.string, pattern, repl )
end

function Rune:split( delimiter )
	local splits = {}

	for str in string.gmatch( self.string, "([^"..delimiter.."]+)" ) do
		table.insert( splits, str )
	end

	return splits
end

return Rune
