package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Rectangle = require( "rectangle" )

local textColor = RL.BLACK
local glyphBgrCol = { 255, 255, 255, 1 }
local textBox = { 8, 300, 800 - 8, 500 }
local textSize = 13 * 2
local text = "Font sharing atlas with other stuff! Why would you want to do that you may wonder. Well you could optimize draw calls with other UI stuff for example."
local font = nil
local atlas = {
	image = nil,
	texture = nil,
	rects = {},
	size = Vector2:new( 512 ),
	padding = 1,
}
local imgNames = {
	"tile.png",
	"apple.png",
	"grass.png",
	"snake.png",
	"wabbit_alpha.png",
	"open-folder.png",
}
local atlasTextures = {}
local fontTexture = nil

function RL.init()
	RL.SetWindowTitle( "Custom font atlas" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	local pathPrefix = RL.GetBasePath().."../resources/images/"
	local fontPath = pathPrefix.."font.png"
	-- local glyphImages = {}
	-- local glyphRects = {}
	local images = {}
	local rects = {}
	local glyphIds = {}

	-- Load images.

	font = RL.LoadFont( fontPath )

	-- Font glyphs.
	for i = 0, RL.GetFontGlyphCount( font ) - 1 do
		local glyph = RL.GetGlyphInfoByIndex( font, i )
		-- table.insert( glyphImages, RL.GetGlyphInfoImage( glyph ) )
		-- table.insert( glyphRects, RL.GetGlyphAtlasRecByIndex( font, i ) )
		table.insert( images, RL.GetGlyphInfoImage( glyph ) )
		table.insert( rects, RL.GetGlyphAtlasRecByIndex( font, i ) )
		table.insert( glyphIds, { glyphId = i, rectId = #rects } )
	end

	-- Other images.
	for _, name in ipairs( imgNames ) do
		local image = RL.LoadImage( pathPrefix..name )
		local imgSize = Vector2:newT( RL.GetImageSize( image ) )

		table.insert( images, image )
		table.insert( rects, Rectangle:new( 0, 0, imgSize.x, imgSize.y ) )
		atlasTextures[ RL.GetFileNameWithoutExt( name ) ] = { rectId = #rects }
	end

	-- Generate atlas.

	atlas.rects = RL.RectPack( rects, atlas.size, atlas.padding )
	atlas.image = RL.GenImageColor( atlas.size, RL.BLANK )

	for i, dstRect in ipairs( atlas.rects ) do
		local srcRect = Rectangle:new( 0, 0, dstRect[3], dstRect[4] )
		-- We draw rect so ImageAlphaCrop doesn't crop alpha of the glyphs.
		RL.ImageDrawRectangleLines( atlas.image, dstRect, 1, glyphBgrCol )
		RL.ImageDraw( atlas.image, images[i], srcRect, dstRect, RL.WHITE )
	end

	RL.ImageAlphaCrop( atlas.image, 0 )
	RL.ImageColorReplace( atlas.image, glyphBgrCol, RL.BLANK ) -- Remove rects.
	atlas.size:setT( RL.GetImageSize( atlas.image ) )
	atlas.texture = RL.LoadTextureFromImage( atlas.image )
	RL.UnloadImage( atlas.image )

	-- Set new font data.

	-- We may want to store font texture to free it with font later to avoid issues.
	-- Here it doesn't really matter but in real project it might.
	fontTexture = RL.GetFontTexture( font )
	RL.SetFontTexture( font, atlas.texture )

	for _, ids in ipairs( glyphIds ) do
		RL.SetGlyphAtlasRec( font, ids.glyphId, atlas.rects[ ids.rectId ] )
	end

	-- Set other texture rects.

	for name, data in pairs( atlasTextures ) do
		data.rect = atlas.rects[ data.rectId ]
		-- print( name, Rectangle:tempT( data.rect ) )
	end
end

function RL.update( delta )
end

function RL.draw()
	RL.SetTextLineSpacing( textSize )

	RL.ClearBackground( RL.GRAY )
	-- Other textures.
	RL.DrawTextureRec( atlas.texture, atlasTextures.wabbit_alpha.rect, { 40, 240 }, RL.WHITE )
	RL.DrawTextureRec( atlas.texture, atlasTextures.tile.rect, { 100, 240 }, RL.WHITE )
	-- Text.
	RL.DrawTextBoxed( font, text, textBox, textSize, 1, true, textColor, false )
	RL.DrawRectangleLines( { 0, 0, atlas.size.x, atlas.size.y }, RL.RED )
	-- Atlas.
	RL.DrawTexture( atlas.texture, { 0, 0 }, RL.WHITE )
end

function RL.exit()
	RL.SetFontTexture( font, fontTexture )
end
