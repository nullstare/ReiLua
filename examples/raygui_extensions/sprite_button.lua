local SpriteButton = {}
SpriteButton.__index = SpriteButton

function SpriteButton:new( bounds, text, texture, nPatchNormal, nPatchPressed, callbacks, styles, tooltip )
    local object = setmetatable( {}, self )
	object._gui = nil

    object.bounds = bounds:clone()
    object.text = text
	object.buttonTexture = texture
	object.nPatchNormal = nPatchNormal
	object.nPatchPressed = nPatchPressed
    object.callbacks = callbacks -- pressed.
	object.styles = styles
	object.tooltip = tooltip

	object.visible = true
	object.disabled = false

	return object
end

function SpriteButton:update()
    return RL.CheckCollisionPointRec( RL.GetMousePosition(), self.bounds )
end

function SpriteButton:draw()
	if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) and self:update() and not RL.GuiIsLocked() and not self._gui.scrolling then
		RL.DrawTextureNPatchRepeat( self.buttonTexture, self.nPatchPressed, self.bounds, { 0, 0 }, 0.0, RL.WHITE )
	else
		RL.DrawTextureNPatchRepeat( self.buttonTexture, self.nPatchNormal, self.bounds, { 0, 0 }, 0.0, RL.WHITE )
	end

	local result = RL.GuiLabelButton( self.bounds, self.text )

    if result == 1 and self.callbacks.pressed ~= nil and self._gui:clickedInBounds( self.bounds ) then
		self.callbacks.pressed( self )
    end
end

function SpriteButton:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y
end

function SpriteButton:register( gui )
	function gui:SpriteButton( bounds, text, texture, nPatchNormal, nPatchPressed, callbacks, styles, tooltip )
		return self:addControl( SpriteButton:new( bounds, text, texture, nPatchNormal, nPatchPressed, callbacks, styles, tooltip ) )
	end
end

return SpriteButton
