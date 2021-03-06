-- Settings.
local winSize = { 800, 600 }
local monitor = 0

-- Constants.
local PLAYER_SPEED = 300
local BALL_SPEED = 330

-- Game objects.
local playerLeft = {
	pos = { 0, 0 },
	size = { 10, 70 },
	score = 0,
}
local playerRight = {
	pos = { 0, 0 },
	size = { 10, 70 },
	score = 0,
}
local ball = {
	pos = { 0, 0 },
	radius = 8.0,
	vel = { 0, 0 },
}

local function reset()
	-- Initialize player positions.
	playerLeft.pos[1] = playerLeft.size[1]
	playerLeft.pos[2] = winSize[2] / 2 - playerLeft.size[2] / 2
	
	playerRight.pos[1] = winSize[1] - playerRight.size[1] * 2
	playerRight.pos[2] = winSize[2] / 2 - playerRight.size[2] / 2

	-- Set ball to center.
	ball.pos = { winSize[1] / 2, winSize[2] / 2 }
	-- Short for if math random result 1, set BALL_SPEED otherwise set -BALL_SPEED.
	-- Could be replaced by normal if statement for easier readability.
	ball.vel[1] = math.random( 0, 1 ) == 1 and BALL_SPEED or -BALL_SPEED
	-- Start slow.
	ball.vel[2] = 0
end

local function ballHit( padPos, padSize )
	ball.vel[1] = -ball.vel[1]

	local padCenter = padPos[2] + padSize[2] / 2
	local relHitPos = ball.pos[2] - padCenter
	ball.vel[2] = BALL_SPEED * relHitPos / padSize[2] * 2
end

function init()
	-- Set window to center of monitor.
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )

	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowTitle( "Pong" )

	-- Initialize ball pos.
	math.randomseed( os.time() )
	reset()
end

function process( delta )
	-- Left player controls.
	if RL_IsKeyDown( string.byte( "W" ) ) and 0 < playerLeft.pos[2] then
		playerLeft.pos[2] = playerLeft.pos[2] - PLAYER_SPEED * delta
	elseif RL_IsKeyDown( string.byte( "S" ) ) and playerLeft.pos[2] + playerLeft.size[2] < winSize[2] then
		playerLeft.pos[2] = playerLeft.pos[2] + PLAYER_SPEED * delta
	end

	-- Right player controls.
	if RL_IsKeyDown( KEY_UP ) and 0 < playerRight.pos[2] then
		playerRight.pos[2] = playerRight.pos[2] - PLAYER_SPEED * delta
	elseif RL_IsKeyDown( KEY_DOWN ) and playerRight.pos[2] + playerRight.size[2] < winSize[2] then
		playerRight.pos[2] = playerRight.pos[2] + PLAYER_SPEED * delta
	end

	-- Move ball.
	ball.pos = { ball.pos[1] + ball.vel[1] * delta,
				 ball.pos[2] + ball.vel[2] * delta }

	-- Bounce from window edge.
	if ( ball.pos[2] < ball.radius and ball.vel[2] < 0 )
	or ( winSize[2] < ball.pos[2] + ball.radius and 0 < ball.vel[2] ) then
		ball.vel[2] = -ball.vel[2]
	end

	-- Bounce from players.
	local playerLeftRect = { playerLeft.pos[1], playerLeft.pos[2],
							 playerLeft.size[1], playerLeft.size[2] }
	local playerRightRect = { playerRight.pos[1], playerRight.pos[2],
							  playerRight.size[1], playerRight.size[2] }

	if RL_CheckCollisionCircleRec( ball.pos, ball.radius, playerLeftRect ) and ball.vel[1] < 0 then
		ballHit( playerLeft.pos, playerLeft.size )
	elseif RL_CheckCollisionCircleRec( ball.pos, ball.radius, playerRightRect ) and 0 < ball.vel[1] then
		ballHit( playerRight.pos, playerRight.size )
	end

	-- Score.
	if ball.pos[1] < 0 then
		playerRight.score = playerRight.score + 1
		reset()
	elseif winSize[1] < ball.pos[1] then
		playerLeft.score = playerLeft.score + 1
		reset()
	end
end

function draw()
	RL_ClearBackground( BLACK )

	-- Draw players.
	RL_DrawRectangle( { playerLeft.pos[1], playerLeft.pos[2], playerLeft.size[1], playerLeft.size[2] }, WHITE )
	RL_DrawRectangle( { playerRight.pos[1], playerRight.pos[2], playerRight.size[1], playerRight.size[2] }, WHITE )

	-- Draw ball. Ball position will be the center in drawCircle.
	RL_DrawCircle( ball.pos, ball.radius, WHITE )

	-- Draw scire
    RL_DrawText( 0, playerLeft.score, { 50, 10 }, 40, 2, WHITE )
	local rightTextSize = RL_MeasureText( 0, playerRight.score, 40, 2 )
    RL_DrawText( 0, playerRight.score, { winSize[1] - 50 - rightTextSize[1], 10 }, 40, 2, WHITE )
end
