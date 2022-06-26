local textColor = BLACK
local textPos = { 192, 200 }
local imageFont = -1
local text = "Congrats! You created your first window!"

function init()
	RL_SetWindowTitle( "First window" )
	RL_SetWindowState( FLAG_VSYNC_HINT )
end

function process( delta )
	if RL_IsKeyPressed( KEY_ENTER ) then
		local textSize = RL_MeasureText( 0, text, 20, 2 )
		local winSize = RL_GetWindowSize()

		textColor = BLUE
		textPos = { winSize[1] / 2 - textSize[1] / 2, winSize[2] / 2 - textSize[2] / 2 }
	end

	if RL_IsKeyPressed( KEY_SPACE ) then
		textColor = BLACK
		textPos = { 192, 200 }
	end
end

function draw()
	RL_ClearBackground( RAYWHITE )
    RL_DrawText( 0, text, textPos, 20, 2, textColor )
end
