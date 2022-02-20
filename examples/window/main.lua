local textColor = BLACK
local textPos = { 192, 200 }

function init()
	RL_SetWindowTitle( "First window" )
end

function process( delta )
	if RL_IsKeyPressed( KEY_ENTER ) then
		textColor = BLUE
		textPos = { 230, 230 }
	end

	if RL_IsKeyPressed( KEY_SPACE ) then
		textColor = BLACK
		textPos = { 192, 200 }
	end
end

function draw()
	RL_ClearBackground( RAYWHITE );
    RL_DrawText( 0, "Congrats! You created your first window!", textPos, 20, 2, textColor );
end
