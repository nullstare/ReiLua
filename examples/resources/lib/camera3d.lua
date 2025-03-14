local Vector2 = Vector2 or require( "vector2" )
local Vector3 = Vector3 or require( "vector3" )

Camera3D = {}
Camera3D.meta = {
	__index = Camera3D,
}
Camera3D.MODES = {
	CUSTOM = 0,
	FREE = 1,
	FIRST_PERSON = 2,
	ORBITAL = 3,
}
Camera3D.KEYS = {
	FORWARD = RL.KEY_W,
	BACKWARD = RL.KEY_S,
	RIGHT = RL.KEY_D,
	LEFT = RL.KEY_A,
	UP = RL.KEY_R,
	DOWN = RL.KEY_F,
	PAN = RL.KEY_LEFT_SHIFT,
	FAST = RL.KEY_LEFT_SHIFT,
}
Camera3D.MOUSE_MOVE_SPEED = 0.5
Camera3D.KEYBOARD_MOVE_SPEED = 10
Camera3D.KEYBOARD_MOVE_SPEED_MULTI = 3
Camera3D.TURN_SPEED = 0.15
Camera3D.ORBITAL_SPEED = 0.5
Camera3D.ZOOM_AMOUNT = 0.1

function Camera3D:new()
	local object = setmetatable( {}, Camera3D.meta )

	object.camera = RL.CreateCamera3D()
	object.mode = object.MODES.CUSTOM

	object:setPosition( { 0, 0, 0 } )
	object:setTarget( { 0, 0, 0 } )
	object:setUp( { 0, 1, 0 } )

	return object
end

function Camera3D:setPosition( pos )
	RL.SetCamera3DPosition( self.camera, pos )
end

function Camera3D:setTarget( target )
	RL.SetCamera3DTarget( self.camera, target )
end

function Camera3D:setUp( up )
	RL.SetCamera3DUp( self.camera, up )
end

function Camera3D:setFoyv( foyv )
	RL.SetCamera3DFovy( self.camera, foyv )
end

function Camera3D:setProjection( projection )
	RL.SetCamera3DProjection( self.camera, projection )
end

function Camera3D:getPosition()
	return Vector3:newT( RL.GetCamera3DPosition( self.camera ) )
end

function Camera3D:getTarget()
	return Vector3:newT( RL.GetCamera3DTarget( self.camera ) )
end

function Camera3D:getUp()
	return Vector3:newT( RL.GetCamera3DUp( self.camera ) )
end

function Camera3D:getFoyv()
	return  RL.GetCamera3DFovy( self.camera )
end

function Camera3D:getProjection()
	return RL.GetCamera3DProjection( self.camera )
end

--- Returns the cameras forward vector ( normalized )
function Camera3D:getForward()
	return Vector3:newT( RL.GetCamera3DForward( self.camera ) )
end

--- Returns the cameras up vector ( normalized ) Note: The up vector might not be perpendicular to the forward vector
function Camera3D:getUpward()
	return Vector3:newT( RL.GetCamera3DUpNormalized( self.camera ) )
end

function Camera3D:update( delta )
	if self.mode == self.MODES.FREE then
		if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_MIDDLE ) then
			local mouseDelta = Vector2:newT( RL.GetMouseDelta() )
			
			if RL.IsKeyDown( self.KEYS.PAN ) then
				mouseDelta = mouseDelta:scale( self.MOUSE_MOVE_SPEED * delta )
				local forward = RL.GetCamera3DForward( self.camera )[2]

				RL.Camera3DMoveRight( self.camera, -mouseDelta.x, true )
				RL.Camera3DMoveUp( self.camera, mouseDelta.y * ( 1 - math.abs( forward ) ) )
				RL.Camera3DMoveForward( self.camera, mouseDelta.y * -forward, true )
			else
				mouseDelta = mouseDelta:scale( self.TURN_SPEED * delta )

				RL.Camera3DYaw( self.camera, -mouseDelta.x, true )
				RL.Camera3DPitch( self.camera, -mouseDelta.y, true, true, false )
			end
		end

		local mouseScroll = RL.GetMouseWheelMove()

		if mouseScroll ~= 0 then
			RL.Camera3DMoveToTarget( self.camera, self.ZOOM_AMOUNT * self:getTargetDistance() * -mouseScroll )
		end
	elseif self.mode == self.MODES.FIRST_PERSON then
		local mouseDelta = Vector2:newT( RL.GetMouseDelta() )

		mouseDelta = mouseDelta:scale( self.TURN_SPEED * delta )

		RL.Camera3DYaw( self.camera, -mouseDelta.x, false )
		RL.Camera3DPitch( self.camera, -mouseDelta.y, true, false, false )
		RL.SetMousePosition( Vector2:newT( RL.GetScreenSize() ):scale( 0.5 ) )

		local distance = self.KEYBOARD_MOVE_SPEED * delta
		local forward = RL.GetCamera3DForward( self.camera )[2]

		if RL.IsKeyDown( self.KEYS.FAST ) then
			distance = distance * self.KEYBOARD_MOVE_SPEED_MULTI
		end

		if RL.IsKeyDown( self.KEYS.FORWARD ) then
			RL.Camera3DMoveForward( self.camera, distance, false )
		elseif RL.IsKeyDown( self.KEYS.BACKWARD ) then
			RL.Camera3DMoveForward( self.camera, -distance, false )
		end
		
		if RL.IsKeyDown( self.KEYS.RIGHT ) then
			RL.Camera3DMoveRight( self.camera, distance, true )
		elseif RL.IsKeyDown( self.KEYS.LEFT ) then
			RL.Camera3DMoveRight( self.camera, -distance, true )
		end

		if RL.IsKeyDown( self.KEYS.UP ) then
			RL.Camera3DMoveUp( self.camera, distance * ( 1 - math.abs( forward ) ) )
			RL.Camera3DMoveForward( self.camera, distance * -forward, true )
		elseif RL.IsKeyDown( self.KEYS.DOWN ) then
			RL.Camera3DMoveUp( self.camera, -distance * ( 1 - math.abs( forward ) ) )
			RL.Camera3DMoveForward( self.camera, -distance * -forward, true )
		end
	elseif self.mode == self.MODES.ORBITAL then
		RL.Camera3DYaw( self.camera, self.ORBITAL_SPEED * delta, true )
	end
end

--- Draw camera target.
function Camera3D:draw()
	local targetPos = self:getTarget()

	RL.DrawLine3D( targetPos + Vector3:new( -0.5, 0, 0 ), targetPos + Vector3:new( 0.5, 0, 0 ), RL.GREEN )
	RL.DrawLine3D( targetPos + Vector3:new( 0, -0.5, 0 ), targetPos + Vector3:new( 0, 0.5, 0 ), RL.BLUE )
	RL.DrawLine3D( targetPos + Vector3:new( 0, 0, -0.5 ), targetPos + Vector3:new( 0, 0, 0.5 ), RL.RED )
end

function Camera3D:getTargetDistance()
	return RL.Vector3Distance( self:getPosition(), self:getTarget() )
end

function Camera3D:beginMode3D()
	RL.BeginMode3D( self.camera )
end

function Camera3D:endMode3D()
	RL.EndMode3D()
end

return Camera3D
