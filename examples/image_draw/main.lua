local monitor = 0
local texture = nil
local image = nil
local catImage = nil
local catCopy = nil
local textImage = nil

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	image = RL.GenImageColor( winSize, RL.WHITE )
	-- Test changing working directory.
	RL.ChangeDirectory( RL.GetBasePath().."../resources" )
	catImage = RL.LoadImage( RL.GetWorkingDirectory().."/images/cat.png" )
	RL.ImageClearBackground( image, { 150, 60, 100 } )
	RL.ImageDrawPixel( image, { 32, 32 }, RL.WHITE )
	RL.ImageDrawLine( image, { 32, 45 }, { 100, 60 }, RL.GREEN )
	RL.ImageDrawCircle( image, { 64, 32 }, 16, RL.BLUE )
	RL.ImageDrawRectangle( image, { 120, 64, 32, 64 }, RL.BLUE )
	RL.ImageDrawRectangleLines( image, { 160, 64, 32, 64 }, 2.0, RL.BLUE )
	RL.ImageDraw( image, catImage, { 143, 25, 230, 250 }, { 200, 200, 230, 250 }, RL.WHITE )
	RL.ImageDrawTextEx( image, RL.GetFontDefault(), "Hello", { 300, 32 }, 48.0, 1.0, RL.WHITE )

	local src = { 80, 70, 96, 96 }
	catCopy = RL.ImageFromImage( catImage, src )

	RL.ImageDraw( image, catCopy, src, { 600, 200, src[3], src[4] }, RL.WHITE )

	textImage = RL.ImageText( RL.GetFontDefault(), "Cat", 10, 4, RL.WHITE )
	local imageSize = RL.GetImageSize( textImage )
	RL.ImageDraw( image, textImage, { 0, 0, imageSize[1], imageSize[2] }, { 250, 40, imageSize[1], imageSize[2] }, RL.WHITE )

	texture = RL.LoadTextureFromImage( image )
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )
	RL.DrawTexture( texture, { 0, 0 }, RL.WHITE )
end
