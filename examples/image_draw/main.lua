local monitor = 0
local texture = -1
local image = -1
local catImage = -1
local catCopy = -1
local textImage = -1

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	image = RL_GenImageColor( winSize[1], winSize[2], WHITE )
	-- Test changing working directory.
	RL_ChangeDirectory( RL_GetBasePath().."../resources" )
	catImage = RL_LoadImage( RL_GetWorkingDirectory().."/images/cat.png" )
	RL_ImageClearBackground( image, { 150, 60, 100 } )
	RL_ImageDrawPixel( image, { 32, 32 }, WHITE )
	RL_ImageDrawLine( image, { 32, 45 }, { 100, 60 }, GREEN )
	RL_ImageDrawCircle( image, { 64, 32 }, 16, BLUE )
	RL_ImageDrawRectangle( image, { 120, 64, 32, 64 }, BLUE )
	RL_ImageDrawRectangleLines( image, { 160, 64, 32, 64 }, 2.0, BLUE )
	RL_ImageDraw( image, catImage, { 143, 25, 230, 250 }, { 200, 200, 230, 250 }, WHITE )
	RL_ImageDrawTextEx( image, 0, "Hello", { 300, 32 }, 48.0, 1.0, WHITE )

	local src = { 80, 70, 96, 96 }
	catCopy = RL_ImageFromImage( catImage, src )

	RL_ImageDraw( image, catCopy, src, { 600, 200, src[3], src[4] }, WHITE )

	textImage = RL_ImageText( 0, "Cat", 10, 4, WHITE )
	local imageSize = RL_GetImageSize( textImage )
	RL_ImageDraw( image, textImage, { 0, 0, imageSize[1], imageSize[2] }, { 250, 40, imageSize[1], imageSize[2] }, WHITE )

	texture = RL_LoadTextureFromImage( image )
end

function draw()
	RL_ClearBackground( { 100, 150, 100 } )
	RL_DrawTexture( texture, { 0, 0 }, WHITE )
end
