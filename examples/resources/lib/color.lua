-- For luaJit compatibility.
if table.unpack == nil then
	table.unpack = unpack
end

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
		return RL.FloatEquals( c1.r, c2.r )
		and RL.FloatEquals( c1.g, c2.g )
		and RL.FloatEquals( c1.b, c2.b )
		and RL.FloatEquals( c1.a, c2.a )
	end,
	__concat = function( a, b )
		return tostring( a )..tostring( b )
	end,
}

function Color:new( r, g, b, a )
	local object = setmetatable( {}, metatable )

	object.r = r or 255
	object.g = g or 255
	object.b = b or 255
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
	self.g = g or 255
	self.b = b or 255
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
	return RL.ColorNormalize( self )
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

function Color:lerp( color, amount )
	return Color:temp(
		RL.Lerp( self.r, color.r, amount ),
		RL.Lerp( self.g, color.g, amount ),
		RL.Lerp( self.b, color.b, amount ),
		RL.Lerp( self.a, color.a, amount )
	):round()
end

function Color:round()
	return Color:new(
		RL.Round( self.r ),
		RL.Round( self.g ),
		RL.Round( self.b ),
		RL.Round( self.a )
	)
end

function Color:invert()
	return Color:new( 255 - self.r, 255 - self.g, 255 - self.b, self.a )
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
	object.g = g or 255
	object.b = b or 255
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
