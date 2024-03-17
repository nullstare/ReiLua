local textColor = RL.BLACK
local textPos = { 192, 200 }
local textSize = 20
local text = "Congrats! You created your first window!"

function RL.init()
	RL.SetWindowTitle( "First window" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

function RL.update( delta )
	if RL.IsKeyPressed( RL.KEY_ENTER ) then
		local winSize = RL.GetScreenSize()
		local measuredSize = RL.MeasureTextEx( RL.GetFontDefault(), text, textSize, 2 )
		
		textColor = RL.BLUE
		textPos = { winSize[1] / 2 - measuredSize[1] / 2, winSize[2] / 2 - measuredSize[2] / 2 }
	end

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		textColor = RL.RED
		textPos = { 192, 200 }
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.DrawText( text, textPos, textSize, textColor )
end
