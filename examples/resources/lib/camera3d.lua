Util = require( "utillib" )
Vec2 = require( "vector2" )
Vec3 = require( "vector3" )

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
	return Vec3:new( RL.GetCamera3DPosition( self.camera ) )
end

function Camera3D:getTarget()
	return Vec3:new( RL.GetCamera3DTarget( self.camera ) )
end

function Camera3D:getUp()
	return Vec3:new( RL.GetCamera3DUp( self.camera ) )
end

function Camera3D:getFoyv()
	return  RL.GetCamera3DFovy( self.camera )
end

function Camera3D:getProjection()
	return RL.GetCamera3DProjection( self.camera )
end

--- Returns the cameras forward vector ( normalized )
function Camera3D:getForward()
	return Vec3:new( RL.GetCamera3DForward( self.camera ) )
end

--- Returns the cameras up vector ( normalized ) Note: The up vector might not be perpendicular to the forward vector
function Camera3D:getUpward()
	return Vec3:new( RL.GetCamera3DUpNormalized( self.camera ) )
end

function Camera3D:process( delta )
	if self.mode == self.MODES.FREE then
		if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_MIDDLE ) then
			local mouseDelta = Vec2:new( RL.GetMouseDelta() )

			if RL.IsKeyDown( self.KEYS.PAN ) then
				mouseDelta = mouseDelta:scale( self.MOUSE_MOVE_SPEED * delta )
				local forward = RL.GetCamera3DForward( self.camera )[2]

				RL.Camera3DMoveRight( self.camera, -mouseDelta.x, true )
				RL.Camera3DMoveUp( self.camera, mouseDelta.y * -( ( 1 - math.abs( forward ) ) * Util.sign( forward ) ) )
				RL.Camera3DMoveForward( self.camera, mouseDelta.y * math.abs( forward ), true )
			else
				mouseDelta = mouseDelta:scale( self.TURN_SPEED * delta )

				RL.Camera3DYaw( self.camera, -mouseDelta.x, true )
				RL.Camera3DPitch( self.camera, -mouseDelta.y, false, true, false )
			end
		end

		local mouseScroll = RL.GetMouseWheelMove()

		if mouseScroll ~= 0 then
			RL.Camera3DMoveToTarget( self.camera, self.ZOOM_AMOUNT * self:getTargetDistance() * -mouseScroll )
		end
	elseif self.mode == self.MODES.FIRST_PERSON then
		local mouseDelta = Vec2:new( RL.GetMouseDelta() )

		mouseDelta = mouseDelta:scale( self.TURN_SPEED * delta )

		RL.Camera3DYaw( self.camera, -mouseDelta.x, false )
		RL.Camera3DPitch( self.camera, -mouseDelta.y, false, false, false )
		RL.SetMousePosition( Vec2:new( RL.GetScreenSize() ):scale( 0.5 ) )

		local distance = self.KEYBOARD_MOVE_SPEED * delta

		if RL.IsKeyDown( self.KEYS.FAST ) then
			distance = distance * self.KEYBOARD_MOVE_SPEED_MULTI
		end

		if RL.IsKeyDown( self.KEYS.FORWARD ) then
			RL.Camera3DMoveForward( self.camera, distance, false )
		elseif RL.IsKeyDown( self.KEYS.BACKWARD ) then
			RL.Camera3DMoveForward( self.camera, -distance, false )
		end

		if RL.IsKeyDown( self.KEYS.RIGHT ) then
			RL.Camera3DMoveRight( self.camera, distance, false )
		elseif RL.IsKeyDown( self.KEYS.LEFT ) then
			RL.Camera3DMoveRight( self.camera, -distance, false )
		end
	elseif self.mode == self.MODES.ORBITAL then
		RL.Camera3DYaw( self.camera, self.ORBITAL_SPEED * delta, true )
	end
end

--- Draw camera target.
function Camera3D:draw()
	local targetPos = self:getTarget()

	RL.DrawLine3D( targetPos + Vec3:new( -0.5, 0, 0 ), targetPos + Vec3:new( 0.5, 0, 0 ), RL.GREEN )
	RL.DrawLine3D( targetPos + Vec3:new( 0, -0.5, 0 ), targetPos + Vec3:new( 0, 0.5, 0 ), RL.BLUE )
	RL.DrawLine3D( targetPos + Vec3:new( 0, 0, -0.5 ), targetPos + Vec3:new( 0, 0, 0.5 ), RL.RED )
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
