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

function PubSub:remove( name )
	if self.signals[ name ] ~= nil then
		table.remove( self.signals, name )
	end
end

function PubSub:subscribe( name, func )
	if self.signals[ name ] ~= nil then
		table.insert( self.signals[ name ], func )
	end
end

function PubSub:unSubscribe( name, uFunc )
	if self.signals[ name ] ~= nil then
		for i, func in ipairs( self.signals[ name ] ) do
			if func == uFunc then
				table.remove( self.signals[ name ], i )
			end
		end
	end
end

function PubSub:publish( name, ... )
	if self.signals[ name ] ~= nil then
		for _, func in ipairs( self.signals[ name ] ) do
			func( ... )
		end
	end
end

return PubSub
