local bitlib = {}

function bitlib.setBit( v, i, b )
	if b then
		return v | 1 << i
	else
		return v & ~( 1 << i )
	end
end

function bitlib.toggleBit( v, i )
	return v ~ ( 1 << i )
end

function bitlib.getBit( v, i )
	if v == nil then
		return false
	end

	return 0 < v & ( 1 << i )
end

return bitlib
