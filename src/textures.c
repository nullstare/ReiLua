#include "main.h"
#include "state.h"
#include "textures.h"
#include "text.h"
#include "lua_core.h"

/*
## Textures - Image loading functions
*/

/*
> image = RL.LoadImage( string fileName )

Load image from file into CPU memory (RAM)

- Failure return nil
- Success return Image
*/
int ltexturesLoadImage( lua_State* L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushImage( L, LoadImage( luaL_checkstring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> image = RL.LoadImageRaw( string fileName, Vector2 size, int format, int headerSize )

Load image from RAW file data

- Failure return nil
- Success return Image
*/
int ltexturesLoadImageRaw( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );
	int format = luaL_checkinteger( L, 3 );
	int headerSize = luaL_checkinteger( L, 4 );

	if ( FileExists( fileName ) ) {
		uluaPushImage( L, LoadImageRaw( fileName, (int)size.x, (int)size.y, format, headerSize ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", fileName );
	lua_pushnil( L );

	return 1;
}

/*
> image, frameCount = RL.LoadImageAnim( string fileName )

Load image sequence from file (frames appended to image.data). All frames are returned in RGBA format

- Failure return nil
- Success return Image, int
*/
int ltexturesLoadImageAnim( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );

	if ( FileExists( fileName ) ) {
		int frameCount = 0;
		uluaPushImage( L, LoadImageAnim( fileName, &frameCount ) );
		lua_pushinteger( L, frameCount );

		return 2;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", fileName );
	lua_pushnil( L );

	return 1;
}

/*
> image, frameCount = RL.LoadImageAnimFromMemory( string fileType, Buffer fileData )

Load image sequence from memory buffer. All frames are returned in RGBA format

- Success return Image, int
*/
int ltexturesLoadImageAnimFromMemory( lua_State* L ) {
	const char* fileType = luaL_checkstring( L, 1 );
	Buffer* buffer = uluaGetBuffer( L, 2 );

	int frameCount = 0;
	uluaPushImage( L, LoadImageAnimFromMemory( fileType, buffer->data, buffer->size, &frameCount ) );
	lua_pushinteger( L, frameCount );

	return 2;
}

/*
> image, frameCount = RL.LoadImageFromMemory( string fileType, Buffer data )

Load image from memory buffer, fileType refers to extension: i.e. '.png'

- Success return Image
*/
int ltexturesLoadImageFromMemory( lua_State* L ) {
	const char* fileType = luaL_checkstring( L, 1 );
	Buffer* data = uluaGetBuffer( L, 2 );

	uluaPushImage( L, LoadImageFromMemory( fileType, data->data, data->size ) );

	return 1;
}

/*
> image, frameCount = RL.LoadImageFromData( Buffer data, Vector2 size, int mipmaps, int format )

Load image from data

- Success return Image
*/
int ltexturesLoadImageFromData( lua_State* L ) {
	Buffer* data = uluaGetBuffer( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );
	int mipmaps = luaL_checkinteger( L, 3 );
	int format = luaL_checkinteger( L, 4 );

	Image image = {
		.width = size.x,
		.height = size.y,
		.mipmaps = mipmaps,
		.format = format
	};
	size_t dataSize = GetPixelDataSize( size.x, size.y, format );
	image.data = malloc( dataSize * sizeof( unsigned char ) );
	memcpy( image.data, data->data, dataSize );

	uluaPushImage( L, image );

	return 1;
}

/*
> image = RL.LoadImageFromTexture( Texture texture )

Load image from GPU texture data

- Success return Image
*/
int ltexturesLoadImageFromTexture( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	uluaPushImage( L, LoadImageFromTexture( *texture ) );

	return 1;
}

/*
> image = RL.LoadImageFromScreen()

Load image from screen buffer and (screenshot)

- Success return Image
*/
int ltexturesLoadImageFromScreen( lua_State* L ) {
	uluaPushImage( L, LoadImageFromScreen() );

	return 1;
}

/*
> isValid = RL.IsImageValid( Image image )

Check if an image is valid (data and parameters)

- Success return bool
*/
int ltextureIsImageValid( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	lua_pushboolean( L, IsImageValid( *image ) );

	return 1;
}

/*
> RL.UnloadImage( Image image )

Unload image from CPU memory (RAM)
*/
int ltextureUnloadImage( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	UnloadImage( *image );
	memset( image, 0, sizeof( Image ) );

	return 0;
}

/*
> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Success return bool
*/
int ltexturesExportImage( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	lua_pushboolean( L, ExportImage( *image, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> buffer = RL.ExportImageToMemory( Image image, string fileType )

Export image to memory buffer

- Success return Buffer
*/
int ltexturesExportImageToMemory( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	const char* fileType = luaL_checkstring( L, 2 );

	Buffer buffer = {
		.type = BUFFER_UNSIGNED_CHAR
	};
	buffer.data = ExportImageToMemory( *image, fileType, (int*)&buffer.size );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Success return bool
*/
int ltexturesExportImageAsCode( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	lua_pushboolean( L, ExportImageAsCode( *image, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Textures - Image generation functions
*/

/*
> image = RL.GenImageColor( Vector2 size, Color color )

Generate image: plain color

- Success return Image
*/
int ltexturesGenImageColor( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	Color color = uluaGetColor( L, 2 );

	uluaPushImage( L, GenImageColor( size.x, size.y, color ) );

	return 1;
}

/*
> image = RL.GenImageGradientLinear( Vector2 size, int direction, Color a, Color b )

Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient

- Success return Image
*/
int ltexturesGenImageGradientLinear( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	int direction = luaL_checkinteger( L, 2 );
	Color start = uluaGetColor( L, 3 );
	Color end = uluaGetColor( L, 4 );

	uluaPushImage( L, GenImageGradientLinear( (int)size.x, (int)size.y, direction, start, end ) );

	return 1;
}

/*
> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Success return Image
*/
int ltexturesGenImageGradientRadial( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	float density = luaL_checknumber( L, 2 );
	Color inner = uluaGetColor( L, 3 );
	Color outer = uluaGetColor( L, 4 );

	uluaPushImage( L, GenImageGradientRadial( (int)size.x, (int)size.y, density, inner, outer ) );

	return 1;
}

/*
> image = RL.GenImageGradientSquare( Vector2 size, float density, Color inner, Color outer )

Generate image: square gradient

- Success return Image
*/
int ltexturesGenImageGradientSquare( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	float density = luaL_checknumber( L, 2 );
	Color inner = uluaGetColor( L, 3 );
	Color outer = uluaGetColor( L, 4 );

	uluaPushImage( L, GenImageGradientSquare( (int)size.x, (int)size.y, density, inner, outer ) );

	return 1;
}

/*
> image = RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Success return Image
*/
int ltexturesGenImageChecked( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	Vector2 checks = uluaGetVector2( L, 2 );
	Color col1 = uluaGetColor( L, 3 );
	Color col2 = uluaGetColor( L, 4 );

	uluaPushImage( L, GenImageChecked( (int)size.x, (int)size.y, (int)checks.x, (int)checks.y, col1, col2 ) );

	return 1;
}

/*
> image = RL.GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Success return Image
*/
int ltexturesGenImageWhiteNoise( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	float factor = luaL_checknumber( L, 2 );

	uluaPushImage( L, GenImageWhiteNoise( (int)size.x, (int)size.y, factor ) );

	return 1;
}

/*
> image = RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )

Generate image: perlin noise

- Success return Image
*/
int ltexturesGenImagePerlinNoise( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	Vector2 offset = uluaGetVector2( L, 2 );
	float factor = luaL_checknumber( L, 3 );

	uluaPushImage( L, GenImagePerlinNoise( (int)size.x, (int)size.y, (int)offset.x, (int)offset.y, factor ) );

	return 1;
}

/*
> image = RL.GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Success return Image
*/
int ltexturesGenImageCellular( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	int tileSize = luaL_checkinteger( L, 2 );

	uluaPushImage( L, GenImageCellular( (int)size.x, (int)size.y, tileSize ) );

	return 1;
}

/*
> image = RL.GenImageText( Vector2 size, string text )

Generate image: grayscale image from text data

- Success return Image
*/
int ltexturesGenImageText( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );

	uluaPushImage( L, GenImageText( (int)size.x, (int)size.y, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Textures - Image manipulation functions
*/

/*
> image = RL.ImageCopy( Image image )

Create an image duplicate (useful for transformations)

- Success return Image
*/
int ltexturesImageCopy( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	uluaPushImage( L, ImageCopy( *image ) );

	return 1;
}

/*
> image = RL.ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Success return Image
*/
int ltexturesImageFromImage( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Rectangle rec = uluaGetRectangle( L, 2 );

	uluaPushImage( L, ImageFromImage( *image, rec ) );

	return 1;
}

/*
> image = RL.ImageFromChannel( Image image, int selectedChannel )

Create an image from a selected channel of another image (GRAYSCALE)

- Success return Image
*/
int ltexturesImageFromChannel( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int selectedChannel = luaL_checkinteger( L, 2 );

	uluaPushImage( L, ImageFromChannel( *image, selectedChannel ) );

	return 1;
}

/*
> image = RL.ImageText( string text, int fontSize, Color tint )

Create an image from text (default font)

- Success return Image
*/
int ltexturesImageText( lua_State* L ) {
	const char* text = luaL_checkstring( L, 1 );
	int fontSize = luaL_checkinteger( L, 2 );
	Color tint = uluaGetColor( L, 3 );

	uluaPushImage( L, ImageText( text, fontSize, tint ) );

	return 1;
}

/*
> image = RL.ImageTextEx( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text (custom sprite font)

- Success return Image
*/
int ltexturesImageTextEx( lua_State* L ) {
	Font* font = uluaGetFont( L, 1 );
	const char* text = luaL_checkstring( L, 2 );
	float fontSize = luaL_checknumber( L, 3 );
	float spacing = luaL_checknumber( L, 4 );
	Color tint = uluaGetColor( L, 5 );

	uluaPushImage( L, ImageTextEx( *font, text, fontSize, spacing, tint ) );

	return 1;
}

/*
> RL.ImageFormat( Image image, int newFormat )

Convert image data to desired format
*/
int ltexturesImageFormat( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int newFormat = luaL_checkinteger( L, 2 );

	ImageFormat( image, newFormat );

	return 0;
}

/*
> RL.ImageToPOT( Image image, Color fill )

Convert image to POT (power-of-two)
*/
int ltexturesImageToPOT( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color fill = uluaGetColor( L, 2 );

	ImageToPOT( image, fill );

	return 0;
}

/*
> RL.ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle
*/
int ltexturesImageCrop( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Rectangle crop = uluaGetRectangle( L, 2 );

	ImageCrop( image, crop );

	return 0;
}

/*
> RL.ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value
*/
int ltexturesImageAlphaCrop( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	float threshold = luaL_checknumber( L, 2 );

	ImageAlphaCrop( image, threshold );

	return 0;
}

/*
> RL.ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color
*/
int ltexturesImageAlphaClear( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color color = uluaGetColor( L, 2 );
	float threshold = luaL_checknumber( L, 3 );

	ImageAlphaClear( image, color, threshold );

	return 0;
}

/*
> RL.ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image
*/
int ltexturesImageAlphaMask( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Image* alphaMask = uluaGetImage( L, 2 );

	ImageAlphaMask( image, *alphaMask );

	return 0;
}

/*
> RL.ImageAlphaPremultiply( Image image )

Premultiply alpha channel
*/
int ltexturesImageAlphaPremultiply( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageAlphaPremultiply( image );

	return 0;
}

/*
> RL.ImageBlurGaussian( Image image, int blurSize )

Apply Gaussian blur using a box blur approximation
*/
int ltexturesImageBlurGaussian( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int blurSize = luaL_checkinteger( L, 2 );

	ImageBlurGaussian( image, blurSize );

	return 0;
}

/*
> RL.ImageKernelConvolution( Image image, float{} kernel )

Apply custom square convolution kernel to image
*/
int ltexturesImageKernelConvolution( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	int kernelSize = uluaGetTableLen( L, 2 );
	float kernel[ kernelSize ];

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		kernel[i] = lua_tonumber( L, -1 );
		i++;
		lua_pop( L, 1 );
	}

	ImageKernelConvolution( image, kernel, kernelSize );

	return 0;
}

/*
> RL.ImageResize( Image image, Vector2 size )

Resize image (Bicubic scaling algorithm)
*/
int ltexturesImageResize( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );

	ImageResize( image, (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.ImageResizeNN( Image image, Vector2 size )

Resize image (Nearest-Neighbor scaling algorithm)
*/
int ltexturesImageResizeNN( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );

	ImageResizeNN( image, (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color
*/
int ltexturesImageResizeCanvas( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );
	Vector2 offset = uluaGetVector2( L, 3 );
	Color fill = uluaGetColor( L, 4 );

	ImageResizeCanvas( image, (int)size.x, (int)size.y, (int)offset.x, (int)offset.y, fill );

	return 0;
}

/*
> RL.ImageMipmaps( Image image )

Generate all mipmap levels for a provided image
*/
int ltexturesImageMipmaps( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageMipmaps( image );

	return 0;
}

/*
> RL.ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
*/
int ltexturesImageDither( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color bpp = uluaGetColor( L, 2 );

	ImageDither( image, bpp.r, bpp.g, bpp.b, bpp.a );

	return 0;
}

/*
> RL.ImageFlipVertical( Image image )

Flip image vertically
*/
int ltexturesImageFlipVertical( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageFlipVertical( image );

	return 0;
}

/*
> RL.ImageFlipHorizontal( Image image )

Flip image horizontally
*/
int ltexturesImageFlipHorizontal( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageFlipHorizontal( image );

	return 0;
}

/*
> RL.ImageRotate( Image image, int degrees )

Rotate image by input angle in degrees (-359 to 359)
*/
int ltexturesImageRotate( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int degrees = luaL_checkinteger( L, 2 );

	ImageRotate( image, degrees );

	return 0;
}

/*
> RL.ImageRotateCW( Image image )

Rotate image clockwise 90deg
*/
int ltexturesImageRotateCW( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageRotateCW( image );

	return 0;
}

/*
> RL.ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg
*/
int ltexturesImageRotateCCW( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageRotateCCW( image );

	return 0;
}

/*
> RL.ImageColorTint( Image image, Color color )

Modify image color: tint
*/
int ltexturesImageColorTint( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color color = uluaGetColor( L, 2 );

	ImageColorTint( image, color );

	return 0;
}

/*
> RL.ImageColorInvert( Image image )

Modify image color: invert
*/
int ltexturesImageColorInvert( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageColorInvert( image );

	return 0;
}

/*
> RL.ImageColorGrayscale( Image image )

Modify image color: grayscale
*/
int ltexturesImageColorGrayscale( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	ImageColorGrayscale( image );

	return 0;
}

/*
> RL.ImageColorContrast( Image image, float contrast )

Modify image color: contrast (-100 to 100)
*/
int ltexturesImageColorContrast( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	float contrast = luaL_checkinteger( L, 2 );

	ImageColorContrast( image, contrast );

	return 0;
}

/*
> RL.ImageColorBrightness( Image image, int brightness )

Modify image color: brightness (-255 to 255)
*/
int ltexturesImageColorBrightness( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int brightness = luaL_checkinteger( L, 2 );

	ImageColorBrightness( image, brightness );

	return 0;
}

/*
> RL.ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color
*/
int ltexturesImageColorReplace( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color color = uluaGetColor( L, 2 );
	Color replace = uluaGetColor( L, 3 );

	ImageColorReplace( image, color, replace );

	return 0;
}

/*
> colors = RL.LoadImageColors( Image image )

Load color data from image as a Color array (RGBA - 32bit)

- Success return Color{}
*/
int ltexturesLoadImageColors( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	int colorCount = image->width * image->height;
	Color* colors = LoadImageColors( *image );

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
int ltexturesLoadImagePalette( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int maxPaletteSize = luaL_checkinteger( L, 2 );

	int colorCount = 0;
	Color* colors = LoadImagePalette( *image, maxPaletteSize, &colorCount );

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
int ltexturesGetImageAlphaBorder( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	float threshold = luaL_checknumber( L, 2 );

	uluaPushRectangle( L, GetImageAlphaBorder( *image, threshold ) );

	return 1;
}

/*
> color = RL.GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at (x, y) position

- Success return Color
*/
int ltexturesGetImageColor( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 pixelPos = uluaGetVector2( L, 2 );

	uluaPushColor( L, GetImageColor( *image, pixelPos.x, pixelPos.y ) );

	return 1;
}

/*
## Textures - Image configuration functions
*/

/*
> imageData = RL.GetImageData( Image image )

Get image data as Buffer

- Success return Buffer
*/
int ltexturesGetImageData( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	Buffer buffer = (Buffer){
		.type = BUFFER_UNSIGNED_CHAR,
		.size = GetPixelDataSize( image->width, image->height, image->format ),
	};
	buffer.data = malloc( buffer.size * sizeof( unsigned char ) );
	memcpy( buffer.data, image->data, buffer.size );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> size = RL.GetImageSize( Image image )

Get image size

- Success return Vector2
*/
int ltexturesGetImageSize( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	uluaPushVector2( L, (Vector2){ image->width, image->height } );

	return 1;
}

/*
> mipmaps = RL.GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Success return int
*/
int ltexturesGetImageMipmaps( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	lua_pushinteger( L, image->mipmaps );

	return 1;
}

/*
> format = RL.GetImageFormat( Image image )

Get image data format (PixelFormat type)

- Success return int
*/
int ltexturesGetImageFormat( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	lua_pushinteger( L, image->format );

	return 1;
}

/*
## Textures - Image drawing functions
*/

/*
> RL.ImageClearBackground( Image dst, Color color )

Clear image background with given color
*/
int ltexturesImageClearBackground( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Color color = uluaGetColor( L, 2 );

	ImageClearBackground( image, color );

	return 0;
}

/*
> RL.ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image
*/
int ltexturesImageDrawPixel( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 position = uluaGetVector2( L, 2 );
	Color color = uluaGetColor( L, 3 );

	ImageDrawPixelV( image, position, color );

	return 0;
}

/*
> RL.ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )

Draw line within an image
*/
int ltexturesImageDrawLine( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 start = uluaGetVector2( L, 2 );
	Vector2 end = uluaGetVector2( L, 3 );
	Color color = uluaGetColor( L, 4 );

	ImageDrawLineV( image, start, end, color );

	return 0;
}

/*
> RL.ImageDrawLineEx( Image dst, Vector2 start, Vector2 end, int thick, Color color )

Draw a line defining thickness within an image
*/
int ltexturesImageDrawLineEx( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 start = uluaGetVector2( L, 2 );
	Vector2 end = uluaGetVector2( L, 3 );
	int thick = luaL_checkinteger( L, 4 );
	Color color = uluaGetColor( L, 5 );

	ImageDrawLineEx( image, start, end, thick, color );

	return 0;
}

/*
> RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image
*/
int ltexturesImageDrawCircle( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 center = uluaGetVector2( L, 2 );
	int radius = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	ImageDrawCircleV( image, center, radius, color );

	return 0;
}

/*
> RL.ImageDrawCircleLines( Image dst, Vector2 center, int radius, Color color )

Draw circle outline within an image
*/
int ltexturesImageDrawCircleLines( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 center = uluaGetVector2( L, 2 );
	int radius = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	ImageDrawCircleLinesV( image, center, radius, color );

	return 0;
}

/*
> RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image
*/
int ltexturesImageDrawRectangle( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Rectangle rec = uluaGetRectangle( L, 2 );
	Color color = uluaGetColor( L, 3 );

	ImageDrawRectangleRec( image, rec, color );

	return 0;
}

/*
> RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image
*/
int ltexturesImageDrawRectangleLines( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Rectangle rec = uluaGetRectangle( L, 2 );
	int thick = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	ImageDrawRectangleLines( image, rec, thick, color );

	return 0;
}

/*
> RL.ImageDrawTriangle( Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle within an image
*/
int ltexturesImageDrawTriangle( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 v1 = uluaGetVector2( L, 2 );
	Vector2 v2 = uluaGetVector2( L, 3 );
	Vector2 v3 = uluaGetVector2( L, 4 );
	Color color = uluaGetColor( L, 5 );

	ImageDrawTriangle( image, v1, v2, v3, color );

	return 0;
}

/*
> RL.ImageDrawTriangleEx( Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3 )

Draw triangle with interpolated colors within an image
*/
int ltexturesImageDrawTriangleEx( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 v1 = uluaGetVector2( L, 2 );
	Vector2 v2 = uluaGetVector2( L, 3 );
	Vector2 v3 = uluaGetVector2( L, 4 );
	Color c1 = uluaGetColor( L, 5 );
	Color c2 = uluaGetColor( L, 6 );
	Color c3 = uluaGetColor( L, 7 );

	ImageDrawTriangleEx( image, v1, v2, v3, c1, c2, c3 );

	return 0;
}

/*
> RL.ImageDrawTriangleLines( Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline within an image
*/
int ltexturesImageDrawTriangleLines( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Vector2 v1 = uluaGetVector2( L, 2 );
	Vector2 v2 = uluaGetVector2( L, 3 );
	Vector2 v3 = uluaGetVector2( L, 4 );
	Color color = uluaGetColor( L, 5 );

	ImageDrawTriangleLines( image, v1, v2, v3, color );

	return 0;
}

/*
> RL.ImageDrawTriangleFan( Image *dst, Vector2{} points, Color color )

Draw a triangle fan defined by points within an image (first vertex is the center)
*/
int ltexturesImageDrawTriangleFan( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int pointCount = uluaGetTableLen( L, 2 );
	Vector2 points[ pointCount ];
	getVector2Array( L, 2, points );
	Color color = uluaGetColor( L, 3 );

	ImageDrawTriangleFan( image, points, pointCount, color );

	return 0;
}

/*
> RL.ImageDrawTriangleStrip( Image *dst, Vector2{} points, Color color )

Draw a triangle strip defined by points within an image
*/
int ltexturesImageDrawTriangleStrip( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int pointCount = uluaGetTableLen( L, 2 );
	Vector2 points[ pointCount ];
	getVector2Array( L, 2, points );
	Color color = uluaGetColor( L, 3 );

	ImageDrawTriangleStrip( image, points, pointCount, color );

	return 0;
}

/*
> RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image (Tint applied to source)
*/
int ltexturesImageDraw( lua_State* L ) {
	Image* imageDst = uluaGetImage( L, 1 );
	Image* imageSrc = uluaGetImage( L, 2 );
	Rectangle srcRec = uluaGetRectangle( L, 3 );
	Rectangle dstRec = uluaGetRectangle( L, 4 );
	Color tint = uluaGetColor( L, 5 );

	ImageDraw( imageDst, *imageSrc, srcRec, dstRec, tint );

	return 0;
}

/*
> RL.ImageDrawText( Image dst, string text, Vector2 position, float fontSize, Color tint )

Draw text (using default font) within an image (destination)
*/
int ltexturesImageDrawText( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	const char* text = luaL_checkstring( L, 2 );
	Vector2 position = uluaGetVector2( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	Color tint = uluaGetColor( L, 5 );

	ImageDrawText( image, text, position.x, position.y, fontSize, tint );

	return 0;
}

/*
> RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text (Custom sprite font) within an image (Destination)
*/
int ltexturesImageDrawTextEx( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	Font* font = uluaGetFont( L, 2 );
	const char* text = luaL_checkstring( L, 3 );
	Vector2 position = uluaGetVector2( L, 4 );
	float fontSize = luaL_checknumber( L, 5 );
	float spacing = luaL_checknumber( L, 6 );
	Color tint = uluaGetColor( L, 7 );

	ImageDrawTextEx( image, *font, text, position, fontSize, spacing, tint );

	return 0;
}

/*
## Textures - Texture loading functions
*/

/*
> texture = RL.GetTextureDefault()

Get default texture. Return as lightuserdata

- Success return Texture
*/
int ltexturesGetTextureDefault( lua_State* L ) {
	lua_pushlightuserdata( L, &state->defaultTexture );

	return 1;
}

/*
> texture = RL.LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return nil
- Success return Texture
*/
int ltexturesLoadTexture( lua_State* L ) {
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
int ltexturesLoadTextureFromImage( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	uluaPushTexture( L, LoadTextureFromImage( *image ) );

	return 1;
}

/*
> texture = RL.LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Success return Texture
*/
int ltexturesLoadTextureCubemap( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );
	int layout = luaL_checkinteger( L, 2 );

	uluaPushTexture( L, LoadTextureCubemap( *image, layout ) );

	return 1;
}

/*
> texture = RL.LoadTextureFromData( Texture{} textureData )

Load Texture from data

- Success return Texture
*/
int ltexturesLoadTextureFromData( lua_State* L ) {
	luaL_checktype( L, 1, LUA_TTABLE );

	Texture texture = { 0 };

	int t = 1;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "id", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			texture.id = (unsigned int)luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "width", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			texture.width = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "height", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			texture.height = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "mipmaps", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			texture.mipmaps = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "format", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			texture.format = luaL_checkinteger( L, -1 );
		}
		lua_pop( L, 1 );
	}
	uluaPushTexture( L, texture );

	return 1;
}

/*
> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering (framebuffer)

- Success return RenderTexture
*/
int ltexturesLoadRenderTexture( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );

	uluaPushRenderTexture( L, LoadRenderTexture( (int)size.x, (int)size.y ) );

	return 1;
}

/*
> renderTexture = RL.LoadRenderTextureFromData( Texture{} renderTextureData )

Load RenderTexture from data (framebuffer)

- Success return RenderTexture
*/
int ltexturesLoadRenderTextureFromData( lua_State* L ) {
	luaL_checktype( L, 1, LUA_TTABLE );

	RenderTexture renTexture = { 0 };

	int t = 1;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "id", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			renTexture.id = (unsigned int)luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "texture", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			Texture* texture = uluaGetTexture( L, -1 );
			renTexture.texture = *texture;
		}
		else if ( strcmp( "depth", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			Texture* depth = uluaGetTexture( L, -1 );
			renTexture.depth = *depth;
		}
		lua_pop( L, 1 );
	}
	uluaPushRenderTexture( L, renTexture );

	return 1;
}

/*
> isValid = RL.IsTextureValid( Texture texture )

Check if a texture is valid (loaded in GPU)

- Success return bool
*/
int ltexturesIsTextureValid( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	lua_pushboolean( L, IsTextureValid( *texture ) );

	return 1;
}

/*
> RL.UnloadTexture( Texture texture )

Unload texture from GPU memory (VRAM)
*/
int ltextureUnloadTexture( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	UnloadTexture( *texture );
	memset( texture, 0, sizeof( Texture ) );

	return 0;
}

/*
> isValid = RL.IsRenderTextureValid( RenderTexture target )

Check if a render texture is valid (loaded in GPU)

- Success return bool
*/
int ltexturesIsRenderTextureValid( lua_State* L ) {
	RenderTexture* target = uluaGetRenderTexture( L, 1 );

	lua_pushboolean( L, IsRenderTextureValid( *target ) );

	return 1;
}

/*
> RL.UnloadRenderTexture( RenderTexture target )

Unload render texture from GPU memory (VRAM)
*/
int ltextureUnloadRenderTexture( lua_State* L ) {
	RenderTexture* target = uluaGetRenderTexture( L, 1 );

	UnloadRenderTexture( *target );
	memset( target, 0, sizeof( RenderTexture ) );

	return 0;
}

/*
> RL.UpdateTexture( Texture texture, Buffer pixels )

Update GPU texture with new data
*/
int ltexturesUpdateTexture( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Buffer* pixels = uluaGetBuffer( L, 2 );

	UpdateTexture( *texture, pixels->data );

	return 0;
}

/*
> RL.UpdateTextureRec( Texture texture, Rectangle rec, Buffer pixels )

Update GPU texture rectangle with new data.
*/
int ltexturesUpdateTextureRec( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Rectangle rec = uluaGetRectangle( L, 2 );
	Buffer* pixels = uluaGetBuffer( L, 3 );

	UpdateTextureRec( *texture, rec, pixels->data );

	return 0;
}

/*
## Textures - Texture configuration functions
*/

/*
> RL.GenTextureMipmaps( Texture texture )

Generate GPU mipmaps for a texture
*/
int ltexturesGenTextureMipmaps( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	GenTextureMipmaps( texture );

	return 0;
}

/*
> RL.SetTextureFilter( Texture texture, int filter )

Set texture scaling filter mode (TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR...)
*/
int ltexturesSetTextureFilter( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	int filter = luaL_checkinteger( L, 2 );

	SetTextureFilter( *texture, filter );

	return 0;
}

/*
> RL.SetTextureWrap( Texture texture, int wrap )

Set texture wrapping mode (TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP...)
*/
int ltexturesSetTextureWrap( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	int wrap = luaL_checkinteger( L, 2 );

	SetTextureWrap( *texture, wrap );

	return 0;
}

/*
> id = RL.GetTextureId( Texture texture )

Get OpenGL texture id

- Success return int
*/
int ltexturesGetTextureId( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	lua_pushinteger( L, texture->id );

	return 1;
}

/*
> size = RL.GetTextureSize( Texture texture )

Get texture size

- Success return Vector2
*/
int ltexturesGetTextureSize( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	uluaPushVector2( L, (Vector2){ texture->width, texture->height } );

	return 1;
}

/*
> mipmaps = RL.GetTextureMipmaps( Texture texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Success return int
*/
int ltexturesGetTextureMipmaps( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	lua_pushinteger( L, texture->mipmaps );

	return 1;
}

/*
> format = RL.GetTextureFormat( Texture texture )

Get texture data format (PixelFormat type)

- Success return int
*/
int ltexturesGetTextureFormat( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	lua_pushinteger( L, texture->format );

	return 1;
}

/*
## Textures - Texture drawing functions
*/

/*
> RL.DrawTexture( Texture texture, Vector2 position, Color tint )

Draw a Texture2D
*/
int ltexturesDrawTexture( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Vector2 position = uluaGetVector2( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawTexture( *texture, position.x, position.y, color );
	return 0;
}

/*
> RL.DrawTextureEx( Texture texture, Vector2 position, float rotation, float scale, Color tint )

Draw a Texture2D with extended parameters
*/
int ltexturesDrawTextureEx( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Vector2 position = uluaGetVector2( L, 2 );
	float rotation = luaL_checknumber( L, 3 );
	float scale = luaL_checknumber( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawTextureEx( *texture, position, rotation, scale, color );
	return 0;
}

/*
> RL.DrawTextureRec( Texture texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle
*/
int ltexturesDrawTextureRec( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Rectangle srcRect = uluaGetRectangle( L, 2 );
	Vector2 position = uluaGetVector2( L, 3 );
	Color tint = uluaGetColor( L, 4 );

	DrawTextureRec( *texture, srcRect, position, tint );
	return 0;
}

/*
> RL.DrawTexturePro( Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters
*/
int ltexturesDrawTexturePro( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	Rectangle srcRect = uluaGetRectangle( L, 2 );
	Rectangle dstRect = uluaGetRectangle( L, 3 );
	Vector2 origin = uluaGetVector2( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawTexturePro( *texture, srcRect, dstRect, origin, rotation, color );

	return 0;
}

/*
> RL.DrawTextureNPatch( Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture (or part of it) that stretches or shrinks nicely
*/
int ltexturesDrawTextureNPatch( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	NPatchInfo nPatchInfo = uluaGetNPatchInfo( L, 2 );
	Rectangle dest = uluaGetRectangle( L, 3 );
	Vector2 origin = uluaGetVector2( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	DrawTextureNPatch( *texture, nPatchInfo, dest, origin, rotation, tint );

	return 0;
}

/*
> RL.DrawTextureNPatchRepeat( Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture (or part of it) that repeats nicely
*/
inline static void drawNPatchTile( Vector4 src, Vector4 dst, Vector2 texSize ) {
	rlTexCoord2f( src.x / texSize.x, src.w / texSize.y ); rlVertex2f( dst.x, dst.w ); // Bottom-left corner for texture and quad
	rlTexCoord2f( src.z / texSize.x, src.w / texSize.y ); rlVertex2f( dst.z, dst.w ); // Bottom-right corner for texture and quad
	rlTexCoord2f( src.z / texSize.x, src.y / texSize.y ); rlVertex2f( dst.z, dst.y ); // Top-right corner for texture and quad
	rlTexCoord2f( src.x / texSize.x, src.y / texSize.y ); rlVertex2f( dst.x, dst.y ); // Top-left corner for texture and quad
}

inline static void drawNPatchArea( Vector4 src, Vector4 dst, Vector2 texSize ) {
	Vector2 tileSize = { src.z - src.x, src.w - src.y };
	Vector2 areaSize = { dst.z - dst.x, dst.w - dst.y };
	int width = ceil( areaSize.x / tileSize.x );
	int height = ceil( areaSize.y / tileSize.y );

	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			Vector2 rTileSize = {
				fmin( tileSize.x, areaSize.x - x * tileSize.x ),
				fmin( tileSize.y, areaSize.y - y * tileSize.y )
			};
			Vector4 tileSrc = {
				src.x,
				src.y,
				src.x + rTileSize.x,
				src.y + rTileSize.y
			};
			Vector4 tileDst = {
				dst.x + x * tileSize.x,
				dst.y + y * tileSize.y,
				dst.x + x * tileSize.x + rTileSize.x,
				dst.y + y * tileSize.y + rTileSize.y
			};
			drawNPatchTile( tileSrc, tileDst, texSize );
		}
	}
}

int ltexturesDrawTextureNPatchRepeat( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );
	NPatchInfo nPatchInfo = uluaGetNPatchInfo( L, 2 );
	Rectangle dest = uluaGetRectangle( L, 3 );
	Vector2 origin = uluaGetVector2( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	if ( texture->id < 0 || dest.width <= 0 || dest.height <= 0 ) {
		return 0;
	}
	Vector2 texSize = { texture->width, texture->height };
	float leftBorder = (float)nPatchInfo.left;
	float topBorder = (float)nPatchInfo.top;
	float rightBorder = (float)nPatchInfo.right;
	float bottomBorder = (float)nPatchInfo.bottom;
	bool drawHMiddle = leftBorder + rightBorder <= dest.width;
	bool drawVMiddle = topBorder + bottomBorder <= dest.height;
	bool drawCenter = drawHMiddle && drawVMiddle;

	if ( !drawHMiddle ) {
		leftBorder = ( leftBorder / ( leftBorder + rightBorder ) ) * dest.width;
		rightBorder = dest.width - leftBorder;
	}
	if ( !drawVMiddle ) {
		topBorder = ( topBorder / ( topBorder + bottomBorder ) ) * dest.height;
		bottomBorder = dest.height - topBorder;
	}
	Vector2 vertA, vertB, vertC, vertD;
	vertA.x = 0.0f;                             // outer left
	vertA.y = 0.0f;                             // outer top
	vertB.x = leftBorder;                       // inner left
	vertB.y = topBorder;                        // inner top
	vertC.x = dest.width - rightBorder;         // inner right
	vertC.y = dest.height - bottomBorder;       // inner bottom
	vertD.x = dest.width;                       // outer right
	vertD.y = dest.height;                      // outer bottom

	Vector2 coordA, coordB, coordC, coordD;
	coordA.x = nPatchInfo.source.x;
	coordA.y = nPatchInfo.source.y;
	coordB.x = nPatchInfo.source.x + leftBorder;
	coordB.y = nPatchInfo.source.y + topBorder;
	coordC.x = nPatchInfo.source.x + nPatchInfo.source.width - rightBorder;
	coordC.y = nPatchInfo.source.y + nPatchInfo.source.height - bottomBorder;
	coordD.x = nPatchInfo.source.x + nPatchInfo.source.width;
	coordD.y = nPatchInfo.source.y + nPatchInfo.source.height;

	rlSetTexture( texture->id );

	rlPushMatrix();
		rlTranslatef( dest.x, dest.y, 0.0f );
		rlRotatef( rotation, 0.0f, 0.0f, 1.0f );
		rlTranslatef( -origin.x, -origin.y, 0.0f );

		rlBegin( RL_QUADS );
			rlColor4ub( tint.r, tint.g, tint.b, tint.a );
			rlNormal3f( 0.0f, 0.0f, 1.0f );               // Normal vector pointing towards viewer

			switch ( nPatchInfo.layout ) {
			case NPATCH_NINE_PATCH:
				if ( drawCenter ) {
					// MIDDLE-CENTER QUAD
					drawNPatchArea(
						(Vector4){ coordB.x, coordB.y, coordC.x, coordC.y },
						(Vector4){ vertB.x, vertB.y, vertC.x, vertC.y },
						texSize
					);
				}
				if ( drawHMiddle ) {
					// TOP-CENTER QUAD
					drawNPatchArea(
						(Vector4){ coordB.x, coordA.y, coordC.x, coordB.y },
						(Vector4){ vertB.x, vertA.y, vertC.x, vertB.y },
						texSize
					);
					// BOTTOM-CENTER QUAD
					drawNPatchArea(
						(Vector4){ coordB.x, coordC.y, coordC.x, coordD.y },
						(Vector4){ vertB.x, vertC.y, vertC.x, vertD.y },
						texSize
					);
				}
				if ( drawVMiddle ) {
					// LEFT-CENTER QUAD
					drawNPatchArea(
						(Vector4){ coordA.x, coordB.y, coordB.x, coordC.y },
						(Vector4){ vertA.x, vertB.y, vertB.x, vertC.y },
						texSize
					);
					// RIGHT-CENTER QUAD
					drawNPatchArea(
						(Vector4){ coordC.x, coordB.y, coordD.x, coordC.y },
						(Vector4){ vertC.x, vertB.y, vertD.x, vertC.y },
						texSize
					);
				}
				// TOP-LEFT QUAD
				drawNPatchTile(
					(Vector4){ coordA.x, coordA.y, coordB.x, coordB.y },
					(Vector4){ vertA.x, vertA.y, vertB.x, vertB.y },
					texSize
				);
				// TOP-RIGHT QUAD
				drawNPatchTile(
					(Vector4){ coordC.x, coordA.y, coordD.x, coordB.y },
					(Vector4){ vertC.x, vertA.y, vertD.x, vertB.y },
					texSize
				);
				// BOTTOM-LEFT QUAD
				drawNPatchTile(
					(Vector4){ coordA.x, coordC.y, coordB.x, coordD.y },
					(Vector4){ vertA.x, vertC.y, vertB.x, vertD.y },
					texSize
				);
				// BOTTOM-RIGHT QUAD
				drawNPatchTile(
					(Vector4){ coordC.x, coordC.y, coordD.x, coordD.y },
					(Vector4){ vertC.x, vertC.y, vertD.x, vertD.y },
					texSize
				);
				break;
			case NPATCH_THREE_PATCH_VERTICAL:
				// TOP QUAD
				drawNPatchArea(
					(Vector4){ coordA.x, coordA.y, coordD.x, coordB.y },
					(Vector4){ vertA.x, vertA.y, vertD.x, vertB.y },
					texSize
				);
				if ( drawVMiddle ) {
					// MIDDLE QUAD
					drawNPatchArea(
						(Vector4){ coordA.x, coordB.y, coordD.x, coordC.y },
						(Vector4){ vertA.x, vertB.y, vertD.x, vertC.y },
						texSize
					);
				}
				// BOTTOM QUAD
				drawNPatchArea(
					(Vector4){ coordA.x, coordC.y, coordD.x, coordD.y },
					(Vector4){ vertA.x, vertC.y, vertD.x, vertD.y },
					texSize
				);
				break;
			case NPATCH_THREE_PATCH_HORIZONTAL:
				// LEFT QUAD
				drawNPatchArea(
					(Vector4){ coordA.x, coordA.y, coordB.x, coordD.y },
					(Vector4){ vertA.x, vertA.y, vertB.x, vertD.y },
					texSize
				);
				if ( drawHMiddle ) {
					// MIDDLE QUAD
					drawNPatchArea(
						(Vector4){ coordB.x, coordA.y, coordC.x, coordD.y },
						(Vector4){ vertB.x, vertA.y, vertC.x, vertD.y },
						texSize
					);
				}
				// RIGHT QUAD
				drawNPatchArea(
					(Vector4){ coordC.x, coordA.y, coordD.x, coordD.y },
					(Vector4){ vertC.x, vertA.y, vertD.x, vertD.y },
					texSize
				);
				break;
			default:
				break;
			}

		rlEnd();
	rlPopMatrix();
	rlSetTexture(0);

	return 0;
}

/*
## Textures - RenderTexture configuration functions
*/

/*
> id = RL.GetRenderTextureId( RenderTexture renderTexture )

Get OpenGL framebuffer object id

- Success return int
*/
int ltexturesGetRenderTextureId( lua_State* L ) {
	RenderTexture* renderTexture = uluaGetRenderTexture( L, 1 );

	lua_pushinteger( L, renderTexture->id );

	return 1;
}

/*
> texture = RL.GetRenderTextureTexture( RenderTexture renderTexture )

Get color buffer attachment texture. Returns as lightuserdata

- Success return Texture
*/
int ltexturesGetRenderTextureTexture( lua_State* L ) {
	RenderTexture* renderTexture = uluaGetRenderTexture( L, 1 );

	lua_pushlightuserdata( L, &renderTexture->texture );

	return 1;
}

/*
> texture = RL.GetRenderTextureDepthTexture( RenderTexture renderTexture )

Get depth buffer attachment texture. Returns as lightuserdata

- Success return Texture
*/
int ltexturesGetRenderTextureDepthTexture( lua_State* L ) {
	RenderTexture* renderTexture = uluaGetRenderTexture( L, 1 );

	lua_pushlightuserdata( L, &renderTexture->depth );

	return 1;
}

/*
## Textures - Color/pixel related functions
*/

/*
> isEqual = RL.ColorIsEqual( Color col1, Color col2 )

Check if two colors are equal

- Success return bool
*/
int ltexturesColorIsEqual( lua_State* L ) {
	Color col1 = uluaGetColor( L, 1 );
	Color col2 = uluaGetColor( L, 2 );

	lua_pushboolean( L, ColorIsEqual( col1, col2 ) );

	return 1;
}

/*
> color = RL.Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color
*/
int ltexturesFade( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );
	float alpha = luaL_checknumber( L, 2 );

	uluaPushColor( L, Fade( color, alpha ) );

	return 1;
}

/*
> value = RL.ColorToInt( Color color )

Returns hexadecimal value for a Color

- Success return int
*/
int ltexturesColorToInt( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );

	lua_pushinteger( L, (unsigned int)ColorToInt( color ) );

	return 1;
}

/*
> color = RL.ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Success return Vector4
*/
int ltexturesColorNormalize( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );

	uluaPushVector4( L, ColorNormalize( color ) );

	return 1;
}

/*
> color = RL.ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Success return Color
*/
int ltexturesColorFromNormalized( lua_State* L ) {
	Vector4 normalized = uluaGetVector4( L, 1 );

	uluaPushColor( L, ColorFromNormalized( normalized ) );

	return 1;
}

/*
> HSV = RL.ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Success return Vector3
*/
int ltexturesColorToHSV( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );

	uluaPushVector3( L, ColorToHSV( color ) );

	return 1;
}

/*
> color = RL.ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Success return Color
*/
int ltexturesColorFromHSV( lua_State* L ) {
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
int ltexturesColorTint( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );
	Color tint = uluaGetColor( L, 2 );

	uluaPushColor( L, ColorTint( color, tint ) );

	return 1;
}

/*
> color = RL.ColorBrightness( Color color, float factor )

Get color with brightness correction, brightness factor goes from -1.0f to 1.0f

- Success return Color
*/
int ltexturesColorBrightness( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );
	float factor = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorBrightness( color, factor ) );

	return 1;
}

/*
> color = RL.ColorContrast( Color color, float contrast )

Get color with contrast correction, contrast values between -1.0f and 1.0f

- Success return Color
*/
int ltexturesColorContrast( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );
	float contrast = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorContrast( color, contrast ) );

	return 1;
}

/*
> color = RL.ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color
*/
int ltexturesColorAlpha( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );
	float alpha = luaL_checknumber( L, 2 );

	uluaPushColor( L, ColorAlpha( color, alpha ) );

	return 1;
}

/*
> color = RL.ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Success return Color
*/
int ltexturesColorAlphaBlend( lua_State* L ) {
	Color dst = uluaGetColor( L, 1 );
	Color src = uluaGetColor( L, 2 );
	Color tint = uluaGetColor( L, 3 );

	uluaPushColor( L, ColorAlphaBlend( dst, src, tint ) );

	return 1;
}

/*
> color = RL.ColorLerp( Color color1, Color color2, float factor )

Get color lerp interpolation between two colors, factor [0.0f..1.0f]

- Success return Color
*/
int ltexturesColorLerp( lua_State* L ) {
	Color color1 = uluaGetColor( L, 1 );
	Color color2 = uluaGetColor( L, 2 );
	float factor = luaL_checknumber( L, 3 );

	uluaPushColor( L, ColorLerp( color1, color2, factor ) );

	return 1;
}

/*
> color = RL.GetColor( int hexValue )

Get Color structure from hexadecimal value

- Success return Color
*/
int ltexturesGetColor( lua_State* L ) {
	unsigned int hexValue = (unsigned int)luaL_checkinteger( L, 1 );

	uluaPushColor( L, GetColor( hexValue ) );

	return 1;
}

/*
> size = RL.GetPixelDataSize( Vector2 size, int format )

Get pixel data size in bytes for certain format

- Success return int
*/
int ltexturesGetPixelDataSize( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );
	int format = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, GetPixelDataSize( size.x, size.y, format ) );

	return 1;
}
