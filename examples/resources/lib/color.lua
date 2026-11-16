-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

local Vector3 = Vector3 or require( "vector3" )

local Color = {}
local metatable = {
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
	__len = function()
		return 4
	end,
	__eq = function( c1, c2 )
		return c1.r == c2.r
		and c1.g == c2.g
		and c1.b == c2.b
		and c1.a == c2.a
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Color:new( r, g, b, a )
	local object = setmetatable( {}, metatable )

	object.r = r or 255
	object.g = g or object.r
	object.b = b or object.g
	object.a = a or 255

	return object
end

function Color:newT( t )
	local object = setmetatable( {}, metatable )

	object.r, object.g, object.b, object.a = table.unpack( t )

	return object
end

function Color:newC( c )
	local object = setmetatable( {}, metatable )

	object.r = c.r
	object.g = c.g
	object.b = c.b
	object.a = c.a

	return object
end

function Color:set( r, g, b, a )
	self.r = r or 255
	self.g = g or self.r
	self.b = b or self.g
	self.a = a or 255
end

function Color:setT( t )
	self.r, self.g, self.b, self.a = table.unpack( t )
end

function Color:setC( c )
	self.r = c.r
	self.g = c.g
	self.b = c.b
	self.a = c.a
end

function Color:serialize()
	return "Color:new("..RL.Round( self.r )..","..RL.Round( self.g )..","..RL.Round( self.b )..","..RL.Round( self.a )..")"
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
	return Color:newT( RL.Fade( self, alpha ) )
end

function Color:toHex()
	return RL.ColorToInt( self )
end

function Color:fromHex( hexValue )
	return Color:newT( RL.GetColor( hexValue ) )
end

function Color:getNormalized()
	return Color:newT( RL.ColorNormalize( self ) )
end

function Color:fromNormalized( normalized )
	return Color:newT( RL.ColorFromNormalized( normalized ) )
end

function Color:toHSV()
	return Vector3:newT( RL.ColorToHSV( self ) )
end

function Color:fromHSV( hue, saturation, value )
	return Color:newT( RL.ColorFromHSV( hue, saturation, value ) )
end

function Color:tint( tint )
	return Color:newT( RL.ColorTint( self, tint ) )
end

function Color:brightness( factor )
	return Color:newT( RL.ColorBrightness( self, factor ) )
end

function Color:contrast( contrast )
	return Color:newT( RL.ColorContrast( self, contrast ) )
end

function Color:alphaBlend( dst, src, tint )
	return Color:newT( RL.ColorAlphaBlend( dst, src, tint ) )
end

function Color:getWithFullAlpha()
	return Color:new( self.r, self.g, self.b, 255 )
end

function Color:getWithZeroAlpha()
	return Color:new( self.r, self.g, self.b, 0 )
end

function Color:lerp( color, amount )
	return Color:new(
		RL.Round( RL.Lerp( self.r, color.r, amount ) ),
		RL.Round( RL.Lerp( self.g, color.g, amount ) ),
		RL.Round( RL.Lerp( self.b, color.b, amount ) ),
		RL.Round( RL.Lerp( self.a, color.a, amount ) )
	)
end

function Color:round()
	return Color:new(
		RL.Round( self.r ),
		RL.Round( self.g ),
		RL.Round( self.b ),
		RL.Round( self.a )
	)
end

function Color:floor()
	return Color:new(
		math.floor( self.r ),
		math.floor( self.g ),
		math.floor( self.b ),
		math.floor( self.a )
	)
end

function Color:ceil()
	return Color:new(
		math.ceil( self.r ),
		math.ceil( self.g ),
		math.ceil( self.b ),
		math.ceil( self.a )
	)
end

function Color:min( c )
	return Color:new(
		math.min( self.r, c.r ),
		math.min( self.g, c.g ),
		math.min( self.b, c.b ),
		math.min( self.a, c.a )
	)
end

function Color:max( c )
	return Color:new(
		math.max( self.r, c.r ),
		math.max( self.g, c.g ),
		math.max( self.b, c.b ),
		math.max( self.a, c.a )
	)
end

function Color:mix( c )
	return Color:temp(
		( self.r + c.r ) / 2,
		( self.g + c.g ) / 2,
		( self.b + c.b ) / 2,
		( self.a + c.a ) / 2
	):round()
end

function Color:invert()
	return Color:new( 255 - self.r, 255 - self.g, 255 - self.b, self.a )
end

function Color:maxValue()
	return math.max( math.max( self.r, self.g ), math.max( self.b, self.a ) )
end

function Color:minValue()
	return math.min( math.min( self.r, self.g ), math.min( self.b, self.a ) )
end

function Color:clamp( c, min, max )
	return Color:temp(
		RL.Clamp( c.r, min.r, max.r ),
		RL.Clamp( c.g, min.g, max.g ),
		RL.Clamp( c.b, min.b, max.b ),
		RL.Clamp( c.a, min.a, max.a )
	):round()
end

-- Temp pre generated objects to avoid "slow" table generation.

local TEMP_COUNT = 100
local tempPool = {}
local curTemp = 1

for _ = 1, TEMP_COUNT do
	table.insert( tempPool, Color:new( 255, 255, 255, 255 ) )
end

function Color:temp( r, g, b, a )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.r = r or 255
	object.g = g or object.r
	object.b = b or object.g
	object.a = a or 255

	return object
end

function Color:tempT( t )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.r, object.g, object.b, object.a = table.unpack( t )

	return object
end

function Color:tempC( c )
	local object = tempPool[ curTemp ]

	curTemp = curTemp < TEMP_COUNT and curTemp + 1 or 1

	object.r = c.r
	object.g = c.g
	object.b = c.b
	object.a = c.a

	return object
end

function Color:getTempId()
	return curTemp
end

return Color
