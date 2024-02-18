local textColor = RL.BLACK
local textPos = { 192, 200 }
local text = "Congrats! You created your first window!"

function RL.init()
	RL.SetWindowTitle( "First window" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

function RL.update( delta )
	if RL.IsKeyPressed( RL.KEY_ENTER ) then
		local textSize = RL.MeasureText( RL.GetFontDefault(), text, 20, 2 )
		local winSize = RL.GetScreenSize()

		textColor = RL.BLUE
		textPos = { winSize[1] / 2 - textSize[1] / 2, winSize[2] / 2 - textSize[2] / 2 }
	end

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		textColor = RL.RED
		textPos = { 192, 200 }
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
    RL.DrawText( text, textPos, 20, textColor )
end
