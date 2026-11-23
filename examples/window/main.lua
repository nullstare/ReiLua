local textColor = RL.BLACK
local textPos = { 192, 200 }
local textSize = 20
local text = "Congrats! You created your first window!"

function RL.init()
	RL.SetWindowTitle( "First window" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	local sb = RL.LoadBufferFromString( "kissala" )
	local b = RL.LoadBuffer( { 42, 12, 3 }, RL.BUFFER_INT )

	local sbSize = RL.GetBufferSize( sb )
	local bSize = RL.GetBufferSize( b )

	print( "sbSize", sbSize, "bSize", bSize )

	local compB = RL.LoadBufferFormatted( sbSize + bSize, RL.BUFFER_UNSIGNED_CHAR, 0 )

	local head = 0
	RL.CopyBufferData( compB, sb, head, 0, sbSize )
	head = head + sbSize
	RL.CopyBufferData( compB, b, head, 0, bSize )

	local strT = RL.GetBufferDataAs( compB, RL.BUFFER_UNSIGNED_CHAR, 0, 7 )

	for _, c in ipairs( strT ) do
		io.write( string.char( c ) )
	end

	print()

	local ints = RL.GetBufferDataAs( compB, RL.BUFFER_INT, sbSize, 3 )

	for i, int in ipairs( ints ) do
		print( i, int )
	end
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
