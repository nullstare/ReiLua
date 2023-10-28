#include "main.h"
#include "state.h"
#include "textures.h"
#include "text.h"
#include "lua_core.h"

/*
## Textures - Image Loading
*/

/*
> image = RL.LoadImage( string fileName )

Load image from file into CPU memory (RAM)

- Success return Image
*/
int ltexturesLoadImage( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushImage( L, LoadImage( luaL_checkstring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> image = RL.LoadImageFromTexture( Texture2D texture )

Load image from GPU texture data

- Success return Image
*/
int ltexturesLoadImageFromTexture( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	uluaPushImage( L, LoadImageFromTexture( *texture ) );

	return 1;
}

/*
> image = RL.LoadImageFromScreen()

Load image from screen buffer and (screenshot)

- Success return Image
*/
int ltexturesLoadImageFromScreen( lua_State *L ) {
	uluaPushImage( L, LoadImageFromScreen() );

	return 1;
}

/*
> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Success return bool
*/
int ltexturesExportImage( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	lua_pushboolean( L, ExportImage( *image, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Success return bool
*/
int ltexturesExportImageAsCode( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	lua_pushboolean( L, ExportImageAsCode( *image, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Textures - Image Generation
*/

/*
> image = RL.GenImageColor( Vector2 size, Color color )

Generate image: plain color

- Success return Image
*/
int ltexturesGenImageColor( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	Color color = uluaGetColorIndex( L, 1 );

	uluaPushImage( L, GenImageColor( size.x, size.y, color ) );

	return 1;
}

/*
> image = RL.GenImageGradientV( Vector2 size, Color top, Color bottom )

Generate image: vertical gradient

- Success return Image
*/
int ltexturesGenImageGradientV( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	Color top = uluaGetColorIndex( L, 2 );
	Color bottom = uluaGetColorIndex( L, 3 );

	uluaPushImage( L, GenImageGradientV( (int)size.x, (int)size.y, top, bottom ) );

	return 1;
}

/*
> image = RL.GenImageGradientH( Vector2 size, Color left, Color right )

Generate image: horizontal gradient

- Success return Image
*/
int ltexturesGenImageGradientH( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	Color left = uluaGetColorIndex( L, 2 );
	Color right = uluaGetColorIndex( L, 3 );

	uluaPushImage( L, GenImageGradientH( (int)size.x, (int)size.y, left, right ) );

	return 1;
}

/*
> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Success return Image
*/
int ltexturesGenImageGradientRadial( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	float density = luaL_checknumber( L, 2 );
	Color inner = uluaGetColorIndex( L, 3 );
	Color outer = uluaGetColorIndex( L, 4 );

	uluaPushImage( L, GenImageGradientRadial( (int)size.x, (int)size.y, density, inner, outer ) );

	return 1;
}

/*
> image = RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Success return Image
*/
int ltexturesGenImageChecked( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	Vector2 checks = uluaGetVector2Index( L, 2 );
	Color col1 = uluaGetColorIndex( L, 3 );
	Color col2 = uluaGetColorIndex( L, 4 );

	uluaPushImage( L, GenImageChecked( (int)size.x, (int)size.y, (int)checks.x, (int)checks.y, col1, col2 ) );

	return 1;
}

/*
> image = RL.GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Success return Image
*/
int ltexturesGenImageWhiteNoise( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	float factor = luaL_checknumber( L, 2 );

	uluaPushImage( L, GenImageWhiteNoise( (int)size.x, (int)size.y, factor ) );

	return 1;
}

/*
> image = RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )

Generate image: perlin noise

- Success return Image
*/
int ltexturesGenImagePerlinNoise( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	Vector2 offset = uluaGetVector2Index( L, 2 );
	float factor = luaL_checknumber( L, 3 );

	uluaPushImage( L, GenImagePerlinNoise( (int)size.x, (int)size.y, (int)offset.x, (int)offset.y, factor ) );

	return 1;
}

/*
> image = RL.GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Success return Image
*/
int ltexturesGenImageCellular( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	int tileSize = luaL_checkinteger( L, 2 );

	uluaPushImage( L, GenImageCellular( (int)size.x, (int)size.y, tileSize ) );

	return 1;
}

/*
> image = RL.GenImageText( Vector2 size, string text )

Generate image: grayscale image from text data

- Success return Image
*/
int ltexturesGenImageText( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );

	uluaPushImage( L, GenImageText( (int)size.x, (int)size.y, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Textures - Image Manipulation Functions
*/

/*
> image = RL.ImageCopy( Image image )

Create an image duplicate (useful for transformations)

- Success return Image
*/
int ltexturesImageCopy( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	uluaPushImage( L, ImageCopy( *image ) );

	return 1;
}

/*
> image = RL.ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Success return Image
*/
int ltexturesImageFromImage( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );

	uluaPushImage( L, ImageFromImage( *image, rec ) );

	return 1;
}

/*
> image = RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text (custom sprite font)

- Failure return -1
- Success return int
*/
int ltexturesImageText( lua_State *L ) {
	// if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 )
	// || !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
	// 	TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )" );
	// 	lua_pushinteger( L, -1 );
	// 	return 1;
	// }
	// size_t fontId = lua_tointeger( L, 1 );
	// float fontSize = lua_tonumber( L, 3 );
	// float spacing = lua_tonumber( L, 4 );
	// Color tint = uluaGetColorIndex( L, 5 );

	// if ( !validFont( fontId ) ) {
	// 	lua_pushinteger( L, -1 );
	// 	return 1;
	// }
	// int i = newImage();
	// *state->images[i] = ImageTextEx( *state->fonts[ fontId ], lua_tostring( L, 2 ), fontSize, spacing, tint );
	// lua_pushinteger( L, i );

	return 0;
}

/*
> RL.ImageFormat( Image image, int newFormat )

Convert image data to desired format
*/
int ltexturesImageFormat( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	int newFormat = luaL_checkinteger( L, 2 );

	ImageFormat( image, newFormat );

	return 0;
}

/*
> RL.ImageToPOT( Image image, Color fill )

Convert image to POT (power-of-two)
*/
int ltexturesImageToPOT( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color fill = uluaGetColorIndex( L, 2 );

	ImageToPOT( image, fill );

	return 0;
}

/*
> RL.ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle
*/
int ltexturesImageCrop( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Rectangle crop = uluaGetRectangleIndex( L, 2 );

	ImageCrop( image, crop );

	return 0;
}

/*
> RL.ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value
*/
int ltexturesImageAlphaCrop( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	float threshold = lua_tonumber( L, 2 );

	ImageAlphaCrop( image, threshold );

	return 0;
}

/*
> RL.ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color
*/
int ltexturesImageAlphaClear( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color color = uluaGetColorIndex( L, 2 );
	float threshold = lua_tonumber( L, 3 );

	ImageAlphaClear( image, color, threshold );

	return 0;
}

/*
> RL.ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image
*/
int ltexturesImageAlphaMask( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Image *alphaMask = luaL_checkudata( L, 2, "Image" );

	ImageAlphaMask( image, *alphaMask );

	return 0;
}

/*
> RL.ImageAlphaPremultiply( Image image )

Premultiply alpha channel
*/
int ltexturesImageAlphaPremultiply( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageAlphaPremultiply( image );

	return 0;
}

/*
> RL.ImageBlurGaussian( Image image, int blurSize )

Apply Gaussian blur using a box blur approximation
*/
int ltexturesImageBlurGaussian( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	int blurSize = luaL_checkinteger( L, 2 );

	ImageBlurGaussian( image, blurSize );

	return 0;
}

/*
> RL.ImageResize( Image image, Vector2 size )

Resize image (Bicubic scaling algorithm)
*/
int ltexturesImageResize( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 size = uluaGetVector2Index( L, 2 );

	ImageResize( image, (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.ImageResizeNN( Image image, Vector2 size )

Resize image (Nearest-Neighbor scaling algorithm)
*/
int ltexturesImageResizeNN( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 size = uluaGetVector2Index( L, 2 );

	ImageResizeNN( image, (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color
*/
int ltexturesImageResizeCanvas( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 size = uluaGetVector2Index( L, 2 );
	Vector2 offset = uluaGetVector2Index( L, 3 );
	Color fill = uluaGetColorIndex( L, 4 );

	ImageResizeCanvas( image, (int)size.x, (int)size.y, (int)offset.x, (int)offset.y, fill );

	return 0;
}

/*
> RL.ImageMipmaps( Image image )

Generate all mipmap levels for a provided image
*/
int ltexturesImageMipmaps( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageMipmaps( image );

	return 0;
}

/*
> RL.ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
*/
int ltexturesImageDither( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color bpp = uluaGetColorIndex( L, 2 );

	ImageDither( image, bpp.r, bpp.g, bpp.b, bpp.a );

	return 0;
}

/*
> RL.ImageFlipVertical( Image image )

Flip image vertically
*/
int ltexturesImageFlipVertical( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageFlipVertical( image );

	return 0;
}

/*
> RL.ImageFlipHorizontal( Image image )

Flip image horizontally
*/
int ltexturesImageFlipHorizontal( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageFlipHorizontal( image );

	return 0;
}

/*
> RL.ImageRotateCW( Image image )

Rotate image clockwise 90deg
*/
int ltexturesImageRotateCW( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageRotateCW( image );

	return 0;
}

/*
> RL.ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg
*/
int ltexturesImageRotateCCW( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageRotateCCW( image );

	return 0;
}

/*
> RL.ImageColorTint( Image image, Color color )

Modify image color: tint
*/
int ltexturesImageColorTint( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color color = uluaGetColorIndex( L, 2 );

	ImageColorTint( image, color );

	return 0;
}

/*
> RL.ImageColorInvert( Image image )

Modify image color: invert
*/
int ltexturesImageColorInvert( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageColorInvert( image );

	return 0;
}

/*
> RL.ImageColorGrayscale( Image image )

Modify image color: grayscale
*/
int ltexturesImageColorGrayscale( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	ImageColorGrayscale( image );

	return 0;
}

/*
> RL.ImageColorContrast( Image image, float contrast )

Modify image color: contrast (-100 to 100)
*/
int ltexturesImageColorContrast( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	float contrast = luaL_checkinteger( L, 2 );

	ImageColorContrast( image, contrast );

	return 0;
}

/*
> RL.ImageColorBrightness( Image image, int brightness )

Modify image color: brightness (-255 to 255)
*/
int ltexturesImageColorBrightness( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	int brightness = luaL_checkinteger( L, 2 );

	ImageColorBrightness( image, brightness );

	return 0;
}

/*
> RL.ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color
*/
int ltexturesImageColorReplace( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color color = uluaGetColorIndex( L, 2 );
	Color replace = uluaGetColorIndex( L, 3 );

	ImageColorReplace( image, color, replace );

	return 0;
}

/*
> colors = RL.LoadImageColors( Image image )

Load color data from image as a Color array (RGBA - 32bit)

- Success return Color{}
*/
int ltexturesLoadImageColors( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	int colorCount = image->width * image->height;
	Color *colors = LoadImageColors( *image );

	lua_createtable( L, colorCount, 0 );

	for ( int i = 0; i < colorCount; ++i ) {
		uluaPushColor( L, colors[i] );
    	lua_rawseti( L, -2, i + 1 );
	}
	UnloadImageColors( colors );

	return 1;
}

/*
> colors = RL.LoadImagePalette( Image image, int maxPaletteSize )

Load colors palette from image as a Color array (RGBA - 32bit)

- Success return Color{}
*/
int ltexturesLoadImagePalette( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	int maxPaletteSize = luaL_checkinteger( L, 2 );

	int colorCount = 0;
	Color *colors = LoadImagePalette( *image, maxPaletteSize, &colorCount );

	lua_createtable( L, colorCount, 0 );

	for ( int i = 0; i < colorCount; ++i ) {
		uluaPushColor( L, colors[i] );
    	lua_rawseti( L, -2, i + 1 );
	}
	UnloadImagePalette( colors );

	return 1;
}

/*
> rectangle = RL.GetImageAlphaBorder( Image image, float threshold )

Get image alpha border rectangle

- Success return Rectangle
*/
int ltexturesGetImageAlphaBorder( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	float threshold = luaL_checknumber( L, 2 );

	uluaPushRectangle( L, GetImageAlphaBorder( *image, threshold ) );

	return 1;
}

/*
> color = RL.GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at (x, y) position

- Success return Color
*/
int ltexturesGetImageColor( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 pixelPos = uluaGetVector2Index( L, 2 );

	uluaPushColor( L, GetImageColor( *image, pixelPos.x, pixelPos.y ) );

	return 1;
}

/*
## Textures - Image Drawing
*/

/*
> RL.ImageClearBackground( Image dst, Color color )

Clear image background with given color
*/
int ltexturesImageClearBackground( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Color color = uluaGetColorIndex( L, 2 );

	ImageClearBackground( image, color );

	return 0;
}

/*
> RL.ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image
*/
int ltexturesImageDrawPixel( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 position = uluaGetVector2Index( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	ImageDrawPixelV( image, position, color );

	return 0;
}

/*
> RL.ImageDrawLine( Image dst, Vector2 a, Vector2 b, Color color )

Draw line within an image
*/
int ltexturesImageDrawLine( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 start = uluaGetVector2Index( L, 2 );
	Vector2 end = uluaGetVector2Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	ImageDrawLineV( image, start, end, color );

	return 0;
}

/*
> RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image
*/
int ltexturesImageDrawCircle( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 center = uluaGetVector2Index( L, 2 );
	int radius = luaL_checkinteger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	ImageDrawCircleV( image, center, radius, color );

	return 0;
}

/*
> RL.ImageDrawCircleLines( Image dst, Vector2 center, int radius, Color color )

Draw circle outline within an image
*/
int ltexturesImageDrawCircleLines( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Vector2 center = uluaGetVector2Index( L, 2 );
	int radius = luaL_checkinteger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	ImageDrawCircleLinesV( image, center, radius, color );

	return 0;
}

/*
> RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image
*/
int ltexturesImageDrawRectangle( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	ImageDrawRectangleRec( image, rec, color );

	return 0;
}

/*
> RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image
*/
int ltexturesImageDrawRectangleLines( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );
	int thick = luaL_checkinteger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	ImageDrawRectangleLines( image, rec, thick, color );

	return 0;
}

/*
> RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image (Tint applied to source)
*/
int ltexturesImageDraw( lua_State *L ) {
	Image *imageDstId = luaL_checkudata( L, 1, "Image" );
	Image *imageSrcId = luaL_checkudata( L, 2, "Image" );
	Rectangle srcRec = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRec = uluaGetRectangleIndex( L, 4 );
	Color tint = uluaGetColorIndex( L, 5 );

	ImageDraw( imageDstId, *imageSrcId, srcRec, dstRec, tint );

	return 0;
}

/*
> success = RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text ( Custom sprite font ) within an image ( Destination )

- Failure return false
- Success return true
*/
int ltexturesImageDrawTextEx( lua_State *L ) {
	// if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isstring( L, 3 ) || !lua_istable( L, 4 )
	// || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) || !lua_istable( L, 7 ) ) {
	// 	TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )" );
	// 	lua_pushboolean( L, false );
	// 	return 1;
	// }
	// size_t imageId = lua_tointeger( L, 1 );
	// size_t fontId = lua_tointeger( L, 2 );
	// Vector2 position = uluaGetVector2Index( L, 4 );
	// float fontSize = lua_tonumber( L, 5 );
	// float spacing = lua_tonumber( L, 6 );
	// Color tint = uluaGetColorIndex( L, 7 );

	// if ( !validImage( imageId ) || !validFont( fontId ) ) {
	// 	lua_pushboolean( L, false );
	// 	return 1;
	// }
	// ImageDrawTextEx( state->images[ imageId ], *state->fonts[ fontId ], lua_tostring( L, 3 ), position, fontSize, spacing, tint );
	// lua_pushboolean( L, true );

	return 1;
}

/*
## Textures - Image Configuration
*/

/*
> size = RL.GetImageSize( Image image )

Get image size

- Success return Vector2
*/
int ltexturesGetImageSize( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	uluaPushVector2( L, (Vector2){ image->width, image->height } );

	return 1;
}

/*
> mipmaps = RL.GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Success return int
*/
int ltexturesGetImageMipmaps( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	lua_pushinteger( L, image->mipmaps );

	return 1;
}

/*
> format = RL.GetImageFormat( Image image )

Get image data format (PixelFormat type)

- Success return int
*/
int ltexturesGetImageFormat( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	lua_pushinteger( L, image->format );

	return 1;
}

/*
## Textures - Texture Loading
*/

/*
> texture = RL.LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return nil
- Success return Texture
*/
int ltexturesLoadTexture( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushTexture( L, LoadTexture( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> texture = RL.LoadTextureFromImage( Image image )

Load texture from image data

- Success return Texture
*/
int ltexturesLoadTextureFromImage( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	uluaPushTexture( L, LoadTextureFromImage( *image ) );

	return 1;
}

/*
> texture = RL.LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Success return Texture
*/
int ltexturesLoadTextureCubemap( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );
	int layout = luaL_checkinteger( L, 2 );

	uluaPushTexture( L, LoadTextureCubemap( *image, layout ) );

	return 1;
}

/*
> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering (framebuffer)

- Success return RenderTexture
*/
int ltexturesLoadRenderTexture( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );

	uluaPushRenderTexture( L, LoadRenderTexture( (int)size.x, (int)size.y ) );

	return 1;
}

/*
> isReady = RL.IsTextureReady( Texture texture )

Check if a texture is ready

- Success return bool
*/
int ltexturesIsTextureReady( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	lua_pushboolean( L, IsTextureReady( *texture ) );

	return 1;
}

/*
> RL.UpdateTexture( Texture texture, int{} pixels )

Update GPU texture with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
*/
int ltexturesUpdateTexture( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	size_t len = uluaGetTableLenIndex( L, 2 );

	unsigned char *pixels = malloc( len * 4 * sizeof( unsigned char ) );

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		size_t colLen = uluaGetTableLen( L );

		int t2 = lua_gettop( L );
		int j = 0;
		lua_pushnil( L );

		while ( lua_next( L, t2 ) != 0 ) {
			*( pixels + ( i * colLen ) + j ) = lua_tointeger( L, -1 );

			j++;
			lua_pop( L, 1 );
		}
		i++;
		lua_pop( L, 1 );
	}
	UpdateTexture( *texture, pixels );
	free( pixels );

	return 0;
}

/*
> RL.UpdateTextureRec( Texture texture, Rectangle rec, int{} pixels )

Update GPU texture rectangle with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
*/
int ltexturesUpdateTextureRec( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );
	size_t len = uluaGetTableLenIndex( L, 3 );

	unsigned char *pixels = malloc( len * 4 * sizeof( unsigned char ) );

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		size_t colLen = uluaGetTableLen( L );

		int t2 = lua_gettop( L );
		int j = 0;
		lua_pushnil( L );

		while ( lua_next( L, t2 ) != 0 ) {
			*( pixels + ( i * colLen ) + j ) = lua_tointeger( L, -1 );

			j++;
			lua_pop( L, 1 );
		}
		i++;
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 ); /* Pixels arg. */

	UpdateTextureRec( *texture, rec, pixels );
	free( pixels );

	return 0;
}

/*
## Textures - Texture Drawing
*/

/*
> RL.DrawTexture( Texture texture, Vector2 position, Color tint )

Draw a Texture2D
*/
int ltexturesDrawTexture( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	Vector2 pos = uluaGetVector2Index( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	DrawTexture( *texture, pos.x, pos.y, color );
	return 0;
}

/*
> RL.DrawTextureRec( Texture texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle
*/
int ltexturesDrawTextureRec( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	Rectangle srcRect = uluaGetRectangleIndex( L, 2 );
	Vector2 pos = uluaGetVector2Index( L, 3 );
	Color tint = uluaGetColorIndex( L, 4 );

	DrawTextureRec( *texture, srcRect, pos, tint );
	return 0;
}

/*
> RL.DrawTexturePro( Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters
*/
int ltexturesDrawTexturePro( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	Rectangle srcRect = uluaGetRectangleIndex( L, 2 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 3 );
	Vector2 origin = uluaGetVector2Index( L, 4 );
	float rot = luaL_checknumber( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	DrawTexturePro( *texture, srcRect, dstRect, origin, rot, color );

	return 0;
}

/*
> RL.DrawTextureNPatch( Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture (or part of it) that stretches or shrinks nicely
*/
int ltexturesDrawTextureNPatch( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	NPatchInfo nPatchInfo = uluaGetNPatchInfoIndex( L, 2 );
	Rectangle dest = uluaGetRectangleIndex( L, 3 );
	Vector2 origin = uluaGetVector2Index( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	Color tint = uluaGetColorIndex( L, 6 );

	DrawTextureNPatch( *texture, nPatchInfo, dest, origin, rotation, tint );

	return 0;
}

/*
> RL.BeginTextureMode( RenderTexture target )

Begin drawing to render texture
*/
int ltexturesBeginTextureMode( lua_State *L ) {
	RenderTexture *renderTexture = luaL_checkudata( L, 1, "RenderTexture" );

	BeginTextureMode( *renderTexture );

	return 0;
}

/*
> RL.EndTextureMode()

Ends drawing to render texture
*/
int ltexturesEndTextureMode( lua_State *L ) {
	EndTextureMode();

	return 0;
}

/*
## Textures - Texture Configuration
*/

/*
> RL.GenTextureMipmaps( Texture texture )

Generate GPU mipmaps for a texture
*/
int ltexturesGenTextureMipmaps( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	GenTextureMipmaps( texture );

	return 0;
}

/*
> RL.SetTextureFilter( Texture texture, int filter )

Set texture scaling filter mode (TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR...)
*/
int ltexturesSetTextureFilter( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	int filter = luaL_checkinteger( L, 2 );

	SetTextureFilter( *texture, filter );

	return 0;
}

/*
> RL.SetTextureWrap( Texture texture, int wrap )

Set texture wrapping mode (TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP...)
*/
int ltexturesSetTextureWrap( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	int wrap = luaL_checkinteger( L, 2 );

	SetTextureWrap( *texture, wrap );

	return 0;
}

/*
> id = RL.GetTextureId( Texture texture )

Get OpenGL texture id

- Success return int
*/
int ltexturesGetTextureId( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	lua_pushinteger( L, texture->id );

	return 1;
}

/*
> size = RL.GetTextureSize( Texture texture )

Get texture size

- Success return Vector2
*/
int ltexturesGetTextureSize( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	uluaPushVector2( L, (Vector2){ texture->width, texture->height } );

	return 1;
}

/*
> mipmaps = RL.GetTextureMipmaps( Texture texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Success return int
*/
int ltexturesGetTextureMipmaps( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	lua_pushinteger( L, texture->mipmaps );

	return 1;
}

/*
> format = RL.GetTextureFormat( Texture texture )

Get texture data format (PixelFormat type)

- Success return int
*/
int ltexturesGetTextureFormat( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	lua_pushinteger( L, texture->format );

	return 1;
}

/*
## Textures - RenderTexture Configuration
*/

/*
> id = RL.GetRenderTextureId( RenderTexture renderTexture )

Get OpenGL framebuffer object id

- Success return int
*/
int ltexturesGetRenderTextureId( lua_State *L ) {
	RenderTexture *renderTexture = luaL_checkudata( L, 1, "RenderTexture" );

	lua_pushinteger( L, renderTexture->id );

	return 1;
}

/*
> texture = RL.GetRenderTextureTexture( RenderTexture renderTexture )

Get color buffer attachment texture

- Success return Texture
*/
int ltexturesGetRenderTextureTexture( lua_State *L ) {
	RenderTexture *renderTexture = luaL_checkudata( L, 1, "RenderTexture" );

	uluaPushTexture( L, renderTexture->texture );

	return 1;
}

/*
> texture = RL.GetRenderTextureDepthTexture( RenderTexture renderTexture )

Get depth buffer attachment texture

- Success return Texture
*/
int ltexturesGetRenderTextureDepthTexture( lua_State *L ) {
	RenderTexture *renderTexture = luaL_checkudata( L, 1, "RenderTexture" );

	uluaPushTexture( L, renderTexture->depth );

	return 1;
}

/*
## Textures - Color/pixel
*/

/*
> color = RL.Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color
*/
int ltexturesFade( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );
	float alpha = luaL_checknumber( L, 2 );

	uluaPushColor( L, Fade( color, alpha ) );

	return 1;
}

/*
> value = RL.ColorToInt( Color color )

Returns hexadecimal value for a Color

- Success return int
*/
int ltexturesColorToInt( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );

	lua_pushinteger( L, ColorToInt( color ) );

	return 1;
}

/*
> color = RL.ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Success return Vector4
*/
int ltexturesColorNormalize( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );

	uluaPushVector4( L, ColorNormalize( color ) );

	return 1;
}

/*
> color = RL.ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Success return Color
*/
int ltexturesColorFromNormalized( lua_State *L ) {
	Vector4 normalized = uluaGetVector4Index( L, 1 );

	uluaPushColor( L, ColorFromNormalized( normalized ) );

	return 1;
}

/*
> HSV = RL.ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Success return Vector3
*/
int ltexturesColorToHSV( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );

	uluaPushVector3( L, ColorToHSV( color ) );

	return 1;
}

/*
> color = RL.ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Success return Color
*/
int ltexturesColorFromHSV( lua_State *L ) {
	float hue = luaL_checknumber( L, 1 );
	float saturation = luaL_checknumber( L, 2 );
	float value = luaL_checknumber( L, 3 );

	uluaPushColor( L, ColorFromHSV( hue, saturation, value ) );

	return 1;
}

/*
> color = RL.ColorTint( Color color, Color tint )

Get color multiplied with another color

- Success return Color
*/
int ltexturesColorTint( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );
	Color tint = uluaGetColorIndex( L, 2 );

	uluaPushColor( L, ColorTint( color, tint ) );

	return 1;
}

/*
> color = RL.ColorBrightness( Color color, float factor )

Get color with brightness correction, brightness factor goes from -1.0f to 1.0f

- Success return Color
*/
int ltexturesColorBrightness( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );
	float factor = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorBrightness( color, factor ) );

	return 1;
}

/*
> color = RL.ColorContrast( Color color, float contrast )

Get color with contrast correction, contrast values between -1.0f and 1.0f

- Success return Color
*/
int ltexturesColorContrast( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );
	float contrast = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorContrast( color, contrast ) );

	return 1;
}

/*
> color = RL.ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color
*/
int ltexturesColorAlpha( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );
	float alpha = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorAlpha( color, alpha ) );

	return 1;
}

/*
> color = RL.ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Success return Color
*/
int ltexturesColorAlphaBlend( lua_State *L ) {
	Color dst = uluaGetColorIndex( L, 1 );
	Color src = uluaGetColorIndex( L, 2 );
	Color tint = uluaGetColorIndex( L, 3 );

	uluaPushColor( L, ColorAlphaBlend( dst, src, tint ) );

	return 1;
}

/*
> color = RL.GetColor( int hexValue )

Get Color structure from hexadecimal value

- Success return Color
*/
int ltexturesGetColor( lua_State *L ) {
	unsigned int hexValue = (unsigned int)luaL_checkinteger( L, 1 );

	uluaPushColor( L, GetColor( hexValue ) );

	return 1;
}

/*
> color = RL.GetPixelColor( Texture texture, Vector2 position )

Get pixel color from source texture

- Success return Color
*/
int ltexturesGetPixelColor( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );
	Vector2 pos = uluaGetVector2Index( L, 2 );
	Image srcImage = LoadImageFromTexture( *texture );

	uluaPushColor( L, GetImageColor( srcImage, pos.x, pos.y ) );
	UnloadImage( srcImage );

	return 1;
}

/*
> size = RL.GetPixelDataSize( int width, int height, int format )

Get pixel data size in bytes for certain format

- Success return int
*/
int ltexturesGetPixelDataSize( lua_State *L ) {
	int width = luaL_checkinteger( L, 1 );
	int height = luaL_checkinteger( L, 2 );
	int format = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GetPixelDataSize( width, height, format ) );

	return 1;
}
