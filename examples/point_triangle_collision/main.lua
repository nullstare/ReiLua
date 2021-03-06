package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

util = require "utillib"
Vec2 = require "vector2"
Vec3 = require "vector3"

local MOVE_SPEED = 0.5

local monitor = 0
local camera = -1
local texture = -1
local tri = {
	a = Vec3:new( 0, 0, 0 ),
	-- a = Vec3:new( 0, 1, 0 ),
	b = Vec3:new( 0, 0, 2 ),
	c = Vec3:new( 1, 0, 0 ),
	normal = Vec3:new( 0, 0, 0 ),
}
local point = {
	pos = Vec3:new( 0.2, 0.3, 0.2 ),
	radius = 0.05,
	lineLen = 0.5,
	color = RED,
}

local debugText = ""

local function calcNormal( tri )
	tri.normal = Vec3:new( RL_Vector3Normalize( RL_Vector3CrossProduct( tri.b - tri.a, tri.c - tri.a ) ) )
end

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = { 1920, 1080 }

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowSize( winSize )
	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { 0, 1, 2 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 1, 0 } )
	RL_SetCameraMode( camera, CAMERA_FREE )

	calcNormal( tri )
end

local function checkCollisionPointTriangle( p, a, b, c, n )
	local result = Vec3:new( 0, 0, 0 )

	local v0 = Vec3:new( b.x - a.x, b.y - a.y, b.z - a.z )   	-- Vector3Subtract( b, a )
	local v1 = Vec3:new( c.x - a.x, c.y - a.y, c.z - a.z )   	-- Vector3Subtract( c, a )
	local v2 = Vec3:new( p.x - a.x, p.y - a.y, p.z - a.z )   	-- Vector3Subtract( p, a )
	local d00 = v0.x * v0.x + v0.y * v0.y + v0.z * v0.z    		-- Vector3DotProduct( v0, v0 )
	local d01 = v0.x * v1.x + v0.y * v1.y + v0.z * v1.z    		-- Vector3DotProduct( v0, v1 )
	local d11 = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z    		-- Vector3DotProduct( v1, v1 )
	local d20 = v2.x * v0.x + v2.y * v0.y + v2.z * v0.z    		-- Vector3DotProduct( v2, v0 )
	local d21 = v2.x * v1.x + v2.y * v1.y + v2.z * v1.z    		-- Vector3DotProduct( v2, v1 )

	local denom = d00 * d11 - d01 * d01
	local distance = v2.x * n.x + v2.y * n.y + v2.z * n.z		-- Vector3DotProduct( v2, n )

	debugText = debugText.."distance "..distance.."\n"
	debugText = debugText.."v0 "..v0.x..", "..v0.y..", "..v0.z.."\n"
	debugText = debugText.."v1 "..v1.x..", "..v1.y..", "..v1.z.."\n"
	debugText = debugText.."v2 "..v2.x..", "..v2.y..", "..v2.z.."\n"

	result.y = ( d11 * d20 - d01 * d21) / denom
    result.z = ( d00 * d21 - d01 * d20) / denom
    result.x = 1.0 - ( result.z + result.y )

	debugText = debugText.."result "..result.x..", "..result.y..", "..result.z.."\n"

	return 0.0 < result.x and 0.0 < result.y and 0.0 < result.z and distance < 0.0, distance
end

function process( delta )
	debugText = ""

	if RL_IsKeyDown( string.byte( "D" ) ) then
		point.pos.x = point.pos.x + MOVE_SPEED * delta
	elseif RL_IsKeyDown( string.byte( "A" ) ) then
		point.pos.x = point.pos.x - MOVE_SPEED * delta
	end
	if RL_IsKeyDown( string.byte( "S" ) ) then
		point.pos.z = point.pos.z + MOVE_SPEED * delta
	elseif RL_IsKeyDown( string.byte( "W" ) ) then
		point.pos.z = point.pos.z - MOVE_SPEED * delta
	end
	if RL_IsKeyDown( string.byte( "R" ) ) then
		point.pos.y = point.pos.y + MOVE_SPEED * delta
	elseif RL_IsKeyDown( string.byte( "F" ) ) then
		point.pos.y = point.pos.y - MOVE_SPEED * delta
	end

	if checkCollisionPointTriangle( point.pos, tri.a, tri.b, tri.c, tri.normal ) then
		point.color = RED
	else
		point.color = GREEN
	end
end

function draw()
	RL_ClearBackground( { 100, 150, 100 } )
	RL_UpdateCamera3D( camera )
	
	RL_BeginMode3D( camera )
		RL_DrawGrid( 8, 1 )
		RL_DrawTriangle3D( tri.a, tri.b, tri.c, { 200, 100, 100 } )

		RL_DrawLine3D( { point.pos.x - point.lineLen, point.pos.y, point.pos.z },
					   { point.pos.x + point.lineLen, point.pos.y, point.pos.z }, BLUE )
		RL_DrawLine3D( { point.pos.x, point.pos.y - point.lineLen, point.pos.z },
					   { point.pos.x, point.pos.y + point.lineLen, point.pos.z }, BLUE )
		RL_DrawLine3D( { point.pos.x, point.pos.y, point.pos.z - point.lineLen },
					   { point.pos.x, point.pos.y, point.pos.z + point.lineLen }, BLUE )
		RL_DrawSphereWires( point.pos, point.radius, 3, 8, point.color )
	RL_EndMode3D()

	RL_DrawText( 0, debugText, { 10, 10 }, 30, 4, WHITE )
end
