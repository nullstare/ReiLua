-- Pong example using Vector2 library.

package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

Vec2 = require "vector2"

-- Settings.
local winSize = Vec2:new( 800, 600 )
local monitor = 0

-- Constants.
local PLAYER_SPEED = 300
local BALL_SPEED = 330

-- Game objects.
local playerLeft = {
	pos = Vec2:new( 0, 0 ),
	size = Vec2:new( 10, 70 ),
	score = 0,
}
local playerRight = {
	pos = Vec2:new( 0, 0 ),
	size = Vec2:new( 10, 70 ),
	score = 0,
}
local ball = {
	pos = Vec2:new( 0, 0 ),
	radius = 8.0,
	vel = Vec2:new( 0, 0 ),
}

local function reset()
	-- Initialize player positions.
	playerLeft.pos.x = playerLeft.size.x
	playerLeft.pos.y = winSize.y / 2 - playerLeft.size.y / 2
	
	playerRight.pos.x = winSize.x - playerRight.size.x * 2
	playerRight.pos.y = winSize.y / 2 - playerRight.size.y / 2

	-- Set ball to center.
	ball.pos:set( winSize.x / 2, winSize.y / 2 )
	-- Short for if math random result 1, set BALL_SPEED otherwise set -BALL_SPEED.
	-- Could be replaced by normal if statement for easier readability.
	ball.vel.x = math.random( 0, 1 ) == 1 and BALL_SPEED or -BALL_SPEED
	-- Start slow.
	ball.vel.y = 0
end

local function ballHit( padPos, padSize )
	ball.vel.x = -ball.vel.x

	local padCenter = padPos.y + padSize.y / 2
	local relHitPos = ball.pos.y - padCenter
	ball.vel.y = BALL_SPEED * relHitPos / padSize.y * 2
end

function init()
	-- Set window to center of monitor.
	local mPos = Vec2:new( RL_GetMonitorPosition( monitor ) )
	local mSize = Vec2:new( RL_GetMonitorSize( monitor ) )

	RL_SetConfigFlags( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )
	RL_SetWindowTitle( "Pong" )

	-- Initialize ball pos.
	math.randomseed( os.time() )
	reset()
end

function process( delta )
	-- Left player controls.
	if RL_IsKeyDown( KEY_W ) and 0 < playerLeft.pos.y then
		playerLeft.pos.y = playerLeft.pos.y - PLAYER_SPEED * delta
	elseif RL_IsKeyDown( KEY_S ) and playerLeft.pos.y + playerLeft.size.y < winSize.y then
		playerLeft.pos.y = playerLeft.pos.y + PLAYER_SPEED * delta
	end

	-- Right player controls.
	if RL_IsKeyDown( KEY_UP ) and 0 < playerRight.pos.y then
		playerRight.pos.y = playerRight.pos.y - PLAYER_SPEED * delta
	elseif RL_IsKeyDown( KEY_DOWN ) and playerRight.pos.y + playerRight.size.y < winSize.y then
		playerRight.pos.y = playerRight.pos.y + PLAYER_SPEED * delta
	end

	-- Move ball.
	ball.pos = ball.pos + ball.vel:scale( delta )

	-- Bounce from window edge.
	if ( ball.pos.y < ball.radius and ball.vel.y < 0 )
	or ( winSize.y < ball.pos.y + ball.radius and 0 < ball.vel.y ) then
		ball.vel.y = -ball.vel.y
	end

	-- Bounce from players.
	local playerLeftRect = { playerLeft.pos.x, playerLeft.pos.y,
							 playerLeft.size.x, playerLeft.size.y }
	local playerRightRect = { playerRight.pos.x, playerRight.pos.y,
							  playerRight.size.x, playerRight.size.y }

	if RL_CheckCollisionCircleRec( ball.pos, ball.radius, playerLeftRect ) and ball.vel.x < 0 then
		ballHit( playerLeft.pos, playerLeft.size )
	elseif RL_CheckCollisionCircleRec( ball.pos, ball.radius, playerRightRect ) and 0 < ball.vel.x then
		ballHit( playerRight.pos, playerRight.size )
	end

	-- Score.
	if ball.pos.x < 0 then
		playerRight.score = playerRight.score + 1
		reset()
	elseif winSize.x < ball.pos.x then
		playerLeft.score = playerLeft.score + 1
		reset()
	end
end

function draw()
	RL_ClearBackground( BLACK )

	-- Draw players.
	RL_DrawRectangle( { playerLeft.pos.x, playerLeft.pos.y, playerLeft.size.x, playerLeft.size.y }, WHITE )
	RL_DrawRectangle( { playerRight.pos.x, playerRight.pos.y, playerRight.size.x, playerRight.size.y }, WHITE )

	-- Draw ball. Ball position will be the center in drawCircle.
	RL_DrawCircle( ball.pos, ball.radius, WHITE )

	-- Draw score.
    RL_DrawText( 0, playerLeft.score, { 50, 10 }, 40, 2, WHITE )
	local rightTextSize = Vec2:new( RL_MeasureText( 0, playerRight.score, 40, 2 ) )
    RL_DrawText( 0, playerRight.score, { winSize.x - 50 - rightTextSize.x, 10 }, 40, 2, WHITE )
end
