local SpriteButton = {}
SpriteButton.__index = SpriteButton

function SpriteButton:new( bounds, text, texture, nPatchNormal, nPatchPressed, callback )
    local object = setmetatable( {}, self )
	object._parent = nil

    object.bounds = bounds:clone()
    object.text = text
	object.buttonTexture = texture
	object.nPatchNormal = nPatchNormal
	object.nPatchPressed = nPatchPressed
    object.callback = callback

	object.visible = true
	object.disabled = false

	return object
end

function SpriteButton:process()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SpriteButton:draw()
	if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) and self:process() and not RL.GuiIsLocked() and not self._parent.scrolling then
		RL.DrawTextureNPatchRepeat( self.buttonTexture, self.nPatchPressed, self.bounds, { 0, 0 }, 0.0, RL.WHITE )
	else
		RL.DrawTextureNPatchRepeat( self.buttonTexture, self.nPatchNormal, self.bounds, { 0, 0 }, 0.0, RL.WHITE )
	end

	local result = RL.GuiLabelButton( self.bounds, self.text )

    if result == 1 and self.callback ~= nil and self._parent:clickedInBounds( self.bounds ) then
		self.callback( self )
    end
end

function SpriteButton:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function SpriteButton:register( gui )
	function gui:SpriteButton( bounds, text, texture, nPatchNormal, nPatchPressed, callback )
		return self:addElement( SpriteButton:new( bounds, text, texture, nPatchNormal, nPatchPressed, callback ) )
	end
end

return SpriteButton
