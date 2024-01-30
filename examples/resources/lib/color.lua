-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector3 = require( "vector3" )

local Color = {}
Color.meta = {
	__index = Color,
	__tostring = function( c )
		return "{"..math.floor( c.r )..", "..math.floor( c.g )..", "..math.floor( c.b )..", "..math.floor( c.a ).."}"
	end,
	__add = function( c1, c2 )
		return Color:new( c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a )
	end,
	__sub = function( c1, c2 )
		return Color:new( c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a )
	end,
	__mul = function( c1, c2 )
		return Color:new( c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a )
	end,
	__div = function( c1, c2 )
		return Color:new( c1.r / c2.r, c1.g / c2.g, c1.b / c2.b, c1.a / c2.a )
	end,
	__mod = function( c, v )
		return Color:new( c.r % v, c.g % v, c.b % v, c.a % v )
	end,
	__pow = function( c, v )
		return Color:new( c.r ^ v, c.g ^ v, c.b ^ v, c.a ^ v )
	end,
	__idiv = function( c, v )
		return Color:new( c.r // v, c.g // v, c.b // v, c.a // v )
	end,
	__len = function()
		return 4
	end,
	__eq = function( c1, c2 )
		return math.floor( c1.r ) == math.floor( c2.r )
		and math.floor( c1.g ) == math.floor( c2.g )
		and math.floor( c1.b ) == math.floor( c2.b )
		and math.floor( c1.a ) == math.floor( c2.a )
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Color:new( r, g, b, a )
	if type( r ) == "table" then
		r, g, b, a = table.unpack( r )
	elseif type( r ) == "nil" then
		r, g, b, a = 0, 0, 0, 255
	end

	if a == nil then
		a = 255
	end

	local object = setmetatable( {}, Color.meta )

	object.r = r
	object.g = g
	object.b = b
	object.a = a

    return object
end

function Color:set( r, g, b, a )
	if type( r ) == "table" then
		r, g, b, a = table.unpack( r )
	elseif type( r ) == "nil" then
		r, g, b, a = 0, 0, 0, 255
	end

	if a == nil then
		a = 255
	end

	self.r = r
	self.g = g
	self.b = b
	self.a = a
end

function Color:arr()
	return { self.r, self.g, self.b, self.a }
end

function Color:unpack()
	return self.r, self.g, self.b, self.a
end

function Color:clone()
	return Color:new( self.r, self.g, self.b, self.a )
end

function Color:scale( scalar )
	return Color:new( math.floor( self.r * scalar ), math.floor( self.g * scalar ), math.floor( self.b * scalar ), math.floor( self.a * scalar ) )
end

function Color:fade( alpha )
	return Color:new( RL.Fade( self, alpha ) )
end

function Color:toHex()
	return RL.ColorToInt( self )
end

function Color:fromHex( hexValue )
	return Color:new( RL.GetColor( hexValue ) )
end

function Color:getNormalized()
	return RL.ColorNormalize( self )
end

function Color:fromNormalized( normalized )
	return Color:new( RL.ColorFromNormalized( normalized ) )
end

function Color:toHSV()
	return Vector3:new( RL.ColorToHSV( self ) )
end

function Color:fromHSV( hue, saturation, value )
	return Color:new( RL.ColorFromHSV( hue, saturation, value ) )
end

function Color:tint( tint )
	return Color:new( RL.ColorTint( self, tint ) )
end

function Color:brightness( factor )
	return Color:new( RL.ColorBrightness( self, factor ) )
end

function Color:contrast( contrast )
	return Color:new( RL.ColorContrast( self, contrast ) )
end

function Color:alphaBlend( dst, src, tint )
	return Color:new( RL.ColorAlphaBlend( dst, src, tint ) )
end

return Color
