local textColor = RL.BLACK
local text = "Put data here"
local deCompressedText = ""
local editMode = false

function RL.init()
	RL.SetWindowTitle( "Buffer" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

local function compressDecompressData()
	local strT = {}

	for i = 1, #text do
		table.insert( strT, string.byte( text:sub( i, i ) ) )
	end

	local strBuffer = RL.LoadBuffer( strT, RL.BUFFER_UNSIGNED_CHAR )
	local compBuffer = RL.CompressData( strBuffer )
	local deCompBuffer = RL.DecompressData( compBuffer )

	deCompressedText = ""

	for _, c in ipairs( RL.GetBufferData( deCompBuffer, 0, RL.GetBufferLength( deCompBuffer ) ) ) do
		deCompressedText = deCompressedText..string.char( c )
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
    RL.DrawText( "Decompressed text: "..deCompressedText, { 20, 200 }, 20, textColor )

	if 0 < RL.GuiButton( { 20, 20, 168, 32 }, "Compress/Decompress Data" ) then
		compressDecompressData()
	end
	
	local pressed = false
	pressed, text = RL.GuiTextBox( { 220, 20, 400, 32 }, text, 64, editMode )

	if 0 < pressed then
		editMode = not editMode
	end
end
