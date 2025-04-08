package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )

local atlasTexture = nil
local atlasRects = {}
local atlasSize = Vector2:new()
local atlasPadding = 1
local imgPaths = {
	"tile.png",
	"apple.png",
	"snake.png",
	"wabbit_alpha.png",
	"nPatch.png",
	"open-folder.png",
	"cat.png",
	"tiles.png",
	"monkey_tex.png",
}

local function makeAtlas()
	local images = {}
	local pathPrefix = RL.GetBasePath().."../resources/images/"

	for i, path in ipairs( imgPaths ) do
		images[i] = RL.LoadImage( pathPrefix..path )
		local imgSize = Vector2:newT( RL.GetImageSize( images[i] ) )
		atlasRects[i] = Rectangle:new( 0, 0, imgSize.x, imgSize.y )
	end

	atlasSize:setT( RL.GetScreenSize() )
	atlasRects = RL.RectPack( atlasRects, atlasSize, atlasPadding )

	local atlasImg = RL.GenImageColor( atlasSize, RL.BLANK )

	for i, rect in ipairs( atlasRects ) do
		print( "Rect", i, Rectangle:tempT( rect ) )
		RL.ImageDraw( atlasImg, images[i],
			{ 0, 0, rect[3], rect[4] },
			rect,
			RL.WHITE
		)
	end

	RL.ImageAlphaCrop( atlasImg, 0 )
	print( "Cropped size", Vector2:tempT( RL.GetImageSize( atlasImg ) ) )

	atlasTexture = RL.LoadTextureFromImage( atlasImg )
end

function RL.init()
	RL.SetWindowTitle( "Texture Atlas" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	makeAtlas()
end

function RL.update( delta )
end

function RL.draw()
	RL.ClearBackground( RL.DARKBLUE )

	if atlasTexture then
		RL.DrawTexture( atlasTexture, { 0, 0 }, RL.WHITE )
	end
end
