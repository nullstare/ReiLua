local PubSub = {}
PubSub.__index = PubSub

function PubSub:new()
	local object = setmetatable( {}, self )

	object.signals = {}

	return object
end

function PubSub:add( name )
	self.signals[ name ] = {}
end

function PubSub:subscribe( name, func )
	table.insert( self.signals[ name ], func )
end

function PubSub:unSubscribe( name, uFunc )
	for i, func in ipairs( self.signals[ name ] ) do
		if func == uFunc then
			table.remove( self.signals[ name ], i )
		end
	end
end

function PubSub:publish( name, ... )
	for _, func in ipairs( self.signals[ name ] ) do
		func( ... )
	end
end

return PubSub
