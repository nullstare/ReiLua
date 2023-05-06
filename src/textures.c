#include "main.h"
#include "state.h"
#include "textures.h"
#include "text.h"
#include "lua_core.h"

static void checkImageRealloc( int i ) {
	if ( i == state->imageCount ) {
		state->imageCount++;
	}

	if ( state->imageCount == state->imageAlloc ) {
		state->imageAlloc += ALLOC_PAGE_SIZE;
		state->images = realloc( state->images, state->imageAlloc * sizeof( Image* ) );

		for ( i = state->imageCount; i < state->imageAlloc; i++ ) {
			state->images[i] = NULL;
		}
	}
}

static void checkTextureRealloc( int i ) {
	if ( i == state->textureCount ) {
		state->textureCount++;
	}

	if ( state->textureCount == state->textureAlloc ) {
		state->textureAlloc += ALLOC_PAGE_SIZE;
		state->textures = realloc( state->textures, state->textureAlloc * sizeof( ReiTexture* ) );

		for ( i = state->textureCount; i < state->textureAlloc; i++ ) {
			state->textures[i] = NULL;
		}
	}
}

bool validImage( size_t id ) {
	if ( id < 0 || state->imageCount < id || state->images[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid image", id );
		return false;
	}
	else {
		return true;
	}
}

bool validTexture( size_t id, int type ) {
	if ( id < 0 || state->textureCount < id || state->textures[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid texture", id );
		return false;
	}
	else if ( type != TEXTURE_TYPE_ALL && type != state->textures[ id ]->type ) {
		TraceLog( LOG_WARNING, "%s %d", "Wrong texture type", type );
		return false;
	}
	else {
		return true;
	}
}

static int newImage() {
	int i = 0;

	for ( i = 0; i < state->imageCount; i++ ) {
		if ( state->images[i] == NULL ) {
			break;
		}
	}
	state->images[i] = malloc( sizeof( Image ) );
	checkImageRealloc( i );

	return i;
}

static int newTexture( int type ) {
	int i = 0;

	for ( i = 0; i < state->textureCount; i++ ) {
		if ( state->textures[i] == NULL ) {
			break;
		}
	}
	state->textures[i] = malloc( sizeof( ReiTexture ) );
	state->textures[i]->type = type;

	checkTextureRealloc( i );

	return i;
}

Texture2D* texturesGetSourceTexture( size_t id ) {
	if ( state->textures[id] != NULL ) {
		switch ( state->textures[id]->type ) {
		case TEXTURE_TYPE_TEXTURE:
			return &state->textures[id]->texture;
			break;
		case TEXTURE_TYPE_RENDER_TEXTURE:
			return &state->textures[id]->renderTexture.texture;
			break;
		}
	}
}

void texturesFreeTexture( size_t id ) {
	if ( state->textures[id] != NULL ) {
		switch ( state->textures[id]->type ) {
		case TEXTURE_TYPE_TEXTURE:
			UnloadTexture( state->textures[id]->texture );
			break;
		case TEXTURE_TYPE_RENDER_TEXTURE:
			UnloadRenderTexture( state->textures[id]->renderTexture );
			break;
		}
	}
}
/*
## Textures - Image Loading
*/

/*
> image = RL.LoadImage( string fileName )

Load image from file into CPU memory ( RAM )

- Failure return -1
- Success return int
*/
int ltexturesLoadImage( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadImage( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		int i = newImage();
		*state->images[i] = LoadImage( lua_tostring( L, 1 ) );
		lua_pushinteger( L, i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> image = RL.LoadImageFromTexture( Texture2D texture )

Load image from GPU texture data

- Failure return -1
- Success return int
*/
int ltexturesLoadImageFromTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadImageFromTexture( Texture2D texture )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newImage();
	*state->images[i] = LoadImageFromTexture( *texturesGetSourceTexture( texId ) );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.LoadImageFromScreen()

Load image from screen buffer and ( screenshot )

- Success return int
*/
int ltexturesLoadImageFromScreen( lua_State *L ) {
	int i = newImage();
	*state->images[i] = LoadImageFromScreen();
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.UnloadImage( Image image )

Unload image from CPU memory ( RAM )

- Failure return false
- Success return true
*/
int ltexturesUnloadImage( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UnloadImage( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, 1 );

	if ( !validImage( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadImage( *state->images[ id ] );
	state->images[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Failure return nil
- Success return bool
*/
int ltexturesExportImage( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ExportImage( Image image, string fileName )" );
		lua_pushnil( L );
		return 1;
	}
	size_t id = lua_tointeger( L, 1 );

	if ( !validImage( id ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, ExportImage( *state->images[ id ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Failure return nil
- Success return bool
*/
int ltexturesExportImageAsCode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ExportImageAsCode( Image image, string fileName )" );
		lua_pushnil( L );
		return 1;
	}
	size_t id = lua_tointeger( L, 1 );

	if ( !validImage( id ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, ExportImageAsCode( *state->images[ id ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
## Textures - Image Generation
*/

/*
> image = RL.GenImageColor( int width, int height, Color color )

Generate image: plain color

- Failure return -1
- Success return int
*/
int ltexturesGenImageColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageColor( int width, int height, Color color )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int width = lua_tointeger( L, 1 );
	int height = lua_tointeger( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	int i = newImage();
	*state->images[i] = GenImageColor( width, height, color );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageGradientV( Vector2 size, Color top, Color bottom )

Generate image: vertical gradient

- Failure return -1
- Success return int
*/
int ltexturesGenImageGradientV( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageGradientV( Vector2 size, Color top, Color bottom )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	Color top = uluaGetColorIndex( L, 2 );
	Color bottom = uluaGetColorIndex( L, 3 );
	
	int i = newImage();
	*state->images[i] = GenImageGradientV( (int)size.x, (int)size.y, top, bottom );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageGradientH( Vector2 size, Color left, Color right )

Generate image: horizontal gradient

- Failure return -1
- Success return int
*/
int ltexturesGenImageGradientH( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageGradientH( Vector2 size, Color left, Color right )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	Color left = uluaGetColorIndex( L, 2 );
	Color right = uluaGetColorIndex( L, 3 );
	
	int i = newImage();
	*state->images[i] = GenImageGradientH( (int)size.x, (int)size.y, left, right );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Failure return -1
- Success return int
*/
int ltexturesGenImageGradientRadial( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	float density = lua_tonumber( L, 2 );
	Color inner = uluaGetColorIndex( L, 3 );
	Color outer = uluaGetColorIndex( L, 4 );
	
	int i = newImage();
	*state->images[i] = GenImageGradientRadial( (int)size.x, (int)size.y, density, inner, outer );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Failure return -1
- Success return int
*/
int ltexturesGenImageChecked( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	Vector2 checks = uluaGetVector2Index( L, 2 );
	Color col1 = uluaGetColorIndex( L, 3 );
	Color col2 = uluaGetColorIndex( L, 4 );
	
	int i = newImage();
	*state->images[i] = GenImageChecked( (int)size.x, (int)size.y, (int)checks.x, (int)checks.y, col1, col2 );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Failure return -1
- Success return int
*/
int ltexturesGenImageWhiteNoise( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageWhiteNoise( Vector2 size, float factor )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	float factor = lua_tonumber( L, 2 );
	
	int i = newImage();
	*state->images[i] = GenImageWhiteNoise( (int)size.x, (int)size.y, factor );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )

Generate image: perlin noise

- Failure return -1
- Success return int
*/
int ltexturesGenImagePerlinNoise( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	Vector2 offset = uluaGetVector2Index( L, 2 );
	
	int i = newImage();
	*state->images[i] = GenImagePerlinNoise( (int)size.x, (int)size.y, (int)offset.x, (int)offset.y, lua_tonumber( L, 3 ) );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Failure return -1
- Success return int
*/
int ltexturesGenImageCellular( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageCellular( Vector2 size, int tileSize )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	int tileSize = lua_tointeger( L, 2 );
	
	int i = newImage();
	*state->images[i] = GenImageCellular( (int)size.x, (int)size.y, tileSize );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.GenImageText( Vector2 size, string text )

Generate image: grayscale image from text data

- Failure return -1
- Success return int
*/
int ltexturesGenImageText( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenImageText( Vector2 size, string text )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );

	int i = newImage();
	*state->images[i] = GenImageText( (int)size.x, (int)size.y, lua_tostring( L, 2 ) );
	lua_pushinteger( L, i );

	return 1;
}

/*
## Textures - Image Manipulation Functions
*/

/*
> image = RL.ImageCopy( Image image )

Create an image duplicate ( useful for transformations )

- Failure return -1
- Success return int
*/
int ltexturesImageCopy( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageCopy( Image image )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newImage();
	*state->images[i] = ImageCopy( *state->images[ imageId ] );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Failure return -1
- Success return int
*/
int ltexturesImageFromImage( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageFromImage( Image image, Rectangle rec )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newImage();
	*state->images[i] = ImageFromImage( *state->images[ imageId ], rec );
	lua_pushinteger( L, i );

	return 1;
}

/*
> image = RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text ( custom sprite font )

- Failure return -1
- Success return int
*/
int ltexturesImageText( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t fontId = lua_tointeger( L, 1 );
	float fontSize = lua_tonumber( L, 3 );
	float spacing = lua_tonumber( L, 4 );
	Color tint = uluaGetColorIndex( L, 5 );

	if ( !validFont( fontId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newImage();
	*state->images[i] = ImageTextEx( *state->fonts[ fontId ], lua_tostring( L, 2 ), fontSize, spacing, tint );
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.ImageFormat( Image image, int newFormat )

Convert image data to desired format

- Failure return false
- Success return true
*/
int ltexturesImageFormat( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageFormat( Image image, int newFormat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	int newFormat = lua_tointeger( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageFormat( state->images[ imageId ], newFormat );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageToPOT( Image image, Color fill )

Convert image to POT ( power-of-two )

- Failure return false
- Success return true
*/
int ltexturesImageToPOT( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageToPOT( Image image, Color fill )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color fill = uluaGetColorIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageToPOT( state->images[ imageId ], fill );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle

- Failure return false
- Success return true
*/
int ltexturesImageCrop( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageCrop( Image image, Rectangle crop )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Rectangle crop = uluaGetRectangleIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageCrop( state->images[ imageId ], crop );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value

- Failure return false
- Success return true
*/
int ltexturesImageAlphaCrop( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageAlphaCrop( Image image, float threshold )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	float threshold = lua_tonumber( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageAlphaCrop( state->images[ imageId ], threshold );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color

- Failure return false
- Success return true
*/
int ltexturesImageAlphaClear( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageAlphaClear( Image image, Color color, float threshold )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );
	float threshold = lua_tonumber( L, 3 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageAlphaClear( state->images[ imageId ], color, threshold );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image

- Failure return false
- Success return true
*/
int ltexturesImageAlphaMask( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageAlphaMask( Image image, Image alphaMask )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	size_t alphaMaskId = lua_tonumber( L, 2 );

	if ( !validImage( imageId ) || !validImage( alphaMaskId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageAlphaMask( state->images[ imageId ], *state->images[ alphaMaskId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageAlphaPremultiply( Image image )

Premultiply alpha channel

- Failure return false
- Success return true
*/
int ltexturesImageAlphaPremultiply( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageAlphaPremultiply( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageAlphaPremultiply( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageResize( Image image, Vector2 size )

Resize image ( Bicubic scaling algorithm )

- Failure return false
- Success return true
*/
int ltexturesImageResize( lua_State *L ) {
	if ( !lua_isnumber( L, 1) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageResize( Image image, Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 size = uluaGetVector2Index( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageResize( state->images[ imageId ], size.x, size.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageResizeNN( Image image, Vector2 size )

Resize image ( Nearest-Neighbor scaling algorithm )

- Failure return false
- Success return true
*/
int ltexturesImageResizeNN( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageResizeNN( Image image, Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 size = uluaGetVector2Index( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageResizeNN( state->images[ imageId ], size.x, size.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color

- Failure return false
- Success return true
*/
int ltexturesImageResizeCanvas( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 size = uluaGetVector2Index( L, 2 );
	Vector2 offset = uluaGetVector2Index( L, 3 );
	Color fill = uluaGetColorIndex( L, 4 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageResizeCanvas( state->images[ imageId ], size.x, size.y, offset.x, offset.y, fill );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageMipmaps( Image image )

Generate all mipmap levels for a provided image

- Failure return false
- Success return true
*/
int ltexturesImageMipmaps( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageMipmaps( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageMipmaps( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower ( Floyd-Steinberg dithering )

- Failure return false
- Success return true
*/
int ltexturesImageDither( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDither( Image image, Color bpp )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color bpp = uluaGetColorIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageDither( state->images[ imageId ], bpp.r, bpp.g, bpp.b, bpp.a );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageFlipVertical( Image image )

Flip image vertically

- Failure return false
- Success return true
*/
int ltexturesImageFlipVertical( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageFlipVertical( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageFlipVertical( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageFlipHorizontal( Image image )

Flip image horizontally

- Failure return false
- Success return true
*/
int ltexturesImageFlipHorizontal( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageFlipHorizontal( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageFlipHorizontal( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageRotateCW( Image image )

Rotate image clockwise 90deg

- Failure return false
- Success return true
*/
int ltexturesImageRotateCW( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageRotateCW( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageRotateCW( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg

- Failure return false
- Success return true
*/
int ltexturesImageRotateCCW( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageRotateCCW( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageRotateCCW( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorTint( Image image, Color color )

Modify image color: tint

- Failure return false
- Success return true
*/
int ltexturesImageColorTint( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorTint( Image image, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorTint( state->images[ imageId ], color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorInvert( Image image )

Modify image color: invert

- Failure return false
- Success return true
*/
int ltexturesImageColorInvert( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorInvert( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorInvert( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorGrayscale( Image image )

Modify image color: grayscale

- Failure return false
- Success return true
*/
int ltexturesImageColorGrayscale( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorGrayscale( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorGrayscale( state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorContrast( Image image, float contrast )

Modify image color: contrast ( -100 to 100 )

- Failure return false
- Success return true
*/
int ltexturesImageColorContrast( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorContrast( Image image, float contrast )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	float contrast = lua_tonumber( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorContrast( state->images[ imageId ], contrast );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorBrightness( Image image, int brightness )

Modify image color: brightness ( -255 to 255 )

- Failure return false
- Success return true
*/
int ltexturesImageColorBrightness( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorBrightness( Image image, int brightness )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	int brightness = lua_tointeger( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorBrightness( state->images[ imageId ], brightness );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color

- Failure return false
- Success return true
*/
int ltexturesImageColorReplace( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageColorReplace( Image image, Color color, Color replace )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );
	Color replace = uluaGetColorIndex( L, 3 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ImageColorReplace( state->images[ imageId ], color, replace );
	lua_pushboolean( L, true );

	return 1;
}

/*
> colors = RL.LoadImageColors( Image image )

Load color data from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}
*/
int ltexturesLoadImageColors( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadImageColors( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	int colorCount = state->images[ imageId ]->width * state->images[ imageId ]->height;

	Color *colors = LoadImageColors( *state->images[ imageId ] );

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

Load colors palette from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}
*/
int ltexturesLoadImagePalette( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadImagePalette( Image image, int maxPaletteSize )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	int maxPaletteSize = lua_tointeger( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	int colorCount = 0;

	Color *colors = LoadImagePalette( *state->images[ imageId ], maxPaletteSize, &colorCount );

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

- Failure return false
- Success return Rectangle
*/
int ltexturesGetImageAlphaBorder( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetImageAlphaBorder( Image image, float threshold )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	float threshold = lua_tonumber( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushRectangle( L, GetImageAlphaBorder( *state->images[ imageId ], threshold ) );

	return 1;
}

/*
> color = RL.GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at ( x, y ) position

- Failure return false
- Success return Color
*/
int ltexturesGetImageColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetImageColor( Image image, Vector2 pixelPos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 pixelPos = uluaGetVector2Index( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushColor( L, GetImageColor( *state->images[ imageId ], pixelPos.x, pixelPos.y ) );

	return 1;
}

/*
## Textures - Image Drawing
*/

/*
> success = RL.ImageClearBackground( Image dst, Color color )

Clear image background with given color

- Failure return false
- Success return true
*/
int ltexturesImageClearBackground( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageClearBackground( Image dst, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageClearBackground( state->images[ imageId ], color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawPixel( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawPixel( Image dst, Vector2 position, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 position = uluaGetVector2Index( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawPixelV( state->images[ imageId ], position, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )

Draw line within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawLine( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 start = uluaGetVector2Index( L, 2 );
	Vector2 end = uluaGetVector2Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawLineV( state->images[ imageId ], start, end, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawCircle( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Vector2 center = uluaGetVector2Index( L, 2 );
	int radius = lua_tointeger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawCircleV( state->images[ imageId ], center, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawRectangle( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawRectangleRec( state->images[ imageId ], rec, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawRectangleLines( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );
	int thick = lua_tointeger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawRectangleLines( state->images[ imageId ], rec, thick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image ( Tint applied to source )

- Failure return false
- Success return true
*/
int ltexturesImageDraw( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageDstId = lua_tointeger( L, 1 );
	size_t imageSrcId = lua_tointeger( L, 2);
	Rectangle srcRec = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRec = uluaGetRectangleIndex( L, 4 );
	Color tint = uluaGetColorIndex( L, 5 );

	if ( !validImage( imageDstId ) || !validImage( imageSrcId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDraw( state->images[ imageDstId ], *state->images[ imageSrcId ], srcRec, dstRec, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text ( Custom sprite font ) within an image ( Destination )

- Failure return false
- Success return true
*/
int ltexturesImageDrawTextEx( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isstring( L, 3 ) || !lua_istable( L, 4 )
	|| !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) || !lua_istable( L, 7 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	size_t fontId = lua_tointeger( L, 2 );
	Vector2 position = uluaGetVector2Index( L, 4 );
	float fontSize = lua_tonumber( L, 5 );
	float spacing = lua_tonumber( L, 6 );
	Color tint = uluaGetColorIndex( L, 7 );

	if ( !validImage( imageId ) || !validFont( fontId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawTextEx( state->images[ imageId ], *state->fonts[ fontId ], lua_tostring( L, 3 ), position, fontSize, spacing, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Textures - Image Configuration
*/

/*
> size = RL.GetImageSize( Image image )

Get image size

- Failure return nil
- Success return Vector2
*/
int ltexturesGetImageSize( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetImageSize( Image image )" );
		lua_pushnil( L );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushnil( L );
		return 1;
	}

	Image *image = state->images[ imageId ];
	uluaPushVector2( L, (Vector2){ image->width, image->height } );

	return 1;
}

/*
> mipmaps = RL.GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int
*/
int ltexturesGetImageMipmaps( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetImageMipmaps( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->images[ imageId ]->mipmaps );

	return 1;
}

/*
> format = RL.GetImageFormat( Image image )

Get image data format ( PixelFormat type )

- Failure return false
- Success return int
*/
int ltexturesGetImageFormat( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetImageFormat( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->images[ imageId ]->format );

	return 1;
}

/*
## Textures - Texture Loading
*/

/*
> texture = RL.LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return -1
- Success return int
*/
int ltexturesLoadTexture( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadTexture( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		int i = newTexture( TEXTURE_TYPE_TEXTURE );
		state->textures[i]->texture = LoadTexture( lua_tostring( L, 1 ) );
		lua_pushinteger( L, i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> texture = RL.LoadTextureFromImage( Image image )

Load texture from image data

- Failure return -1
- Success return int
*/
int ltexturesLoadTextureFromImage( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadTextureFromImage( Image image )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	int i = newTexture( TEXTURE_TYPE_TEXTURE );
	state->textures[i]->texture = LoadTextureFromImage( *state->images[ imageId ] );
	lua_pushinteger( L, i );

	return 1;
}

/*
> texture = RL.LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Failure return -1
- Success return int
*/
int ltexturesLoadTextureCubemap( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadTextureCubemap( Image image, int layout )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );
	int layout = lua_tointeger( L, 2 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	int i = newTexture( TEXTURE_TYPE_TEXTURE );
	state->textures[i]->texture = LoadTextureCubemap( *state->images[ imageId ], layout );
	lua_pushinteger( L, i );

	return 1;
}

/*
> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering ( framebuffer )

- Failure return -1
- Success return int
*/
int ltexturesLoadRenderTexture( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadRenderTexture( Vector2 size )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );

	int i = newTexture( TEXTURE_TYPE_RENDER_TEXTURE );
	state->textures[i]->renderTexture = LoadRenderTexture( (int)size.x, (int)size.y );
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.UnloadTexture( Texture2D texture )

Unload texture from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int ltexturesUnloadTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UnloadTexture( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	// UnloadTexture( *state->textures[ id ] );
	texturesFreeTexture( texId );
	// state->textures[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> isReady = RL.IsTextureReady( Texture2D texture )

Check if a texture is ready

- Failure return nil
- Success return true
*/
int ltexturesIsTextureReady( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.IsTextureReady( Texture2D texture )" );
		lua_pushnil( L );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_TEXTURE ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsTextureReady( state->textures[ texId ]->texture) );

	return 1;
}

/*
> success = RL.UpdateTexture( Texture2D texture, int{} pixels )

Update GPU texture with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true
*/
int ltexturesUpdateTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UpdateTexture( Texture2D texture, int{} pixels )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	
	if ( !validTexture( texId, TEXTURE_TYPE_TEXTURE ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
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
	// UpdateTexture( *state->textures[ texId ], pixels );
	UpdateTexture( state->textures[ texId ]->texture, pixels );
	lua_pushboolean( L, true );

	free( pixels );

	return 1;
}

/*
> success = RL.UpdateTextureRec( Texture2D texture, Rectangle rec, int{} pixels )

Update GPU texture rectangle with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true
*/
int ltexturesUpdateTextureRec( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UpdateTextureRec( Texture2D texture, Rectangle rec, int{} pixels )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	
	if ( !validTexture( texId, TEXTURE_TYPE_TEXTURE ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
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

	Rectangle rec = uluaGetRectangleIndex( L, 2 );

	UpdateTextureRec( state->textures[ texId ]->texture, rec, pixels );
	lua_pushboolean( L, true );

	free( pixels );

	return 1;
}

/*
## Textures - Texture Drawing
*/

/*
> success = RL.DrawTexture( Texture2D texture, Vector2 position, Color tint )

Draw a Texture2D

- Failure return false
- Success return true
*/
int ltexturesDrawTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTexture( Texture2D texture, Vector2 position, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTexture( *texturesGetSourceTexture( texId ), pos.x, pos.y, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle

- Failure return false
- Success return true
*/
int ltexturesDrawTextureRec( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 )  || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	Rectangle srcRect = uluaGetRectangleIndex( L, 2 );
	Vector2 pos = uluaGetVector2Index( L, 3 );
	Color tint = uluaGetColorIndex( L, 4 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTextureRec( *texturesGetSourceTexture( texId ), srcRect, pos, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters

- Failure return false
- Success return true
*/
int ltexturesDrawTexturePro( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	Rectangle srcRect = uluaGetRectangleIndex( L, 2 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 3 );
	Vector2 origin = uluaGetVector2Index( L, 4 );
	float rot = lua_tonumber( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTexturePro( *texturesGetSourceTexture( texId ), srcRect, dstRect, origin, rot, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture ( or part of it ) that stretches or shrinks nicely

- Failure return false
- Success return true
*/
int ltexturesDrawTextureNPatch( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	NPatchInfo nPatchInfo = uluaGetNPatchInfoIndex( L, 2 );
	Rectangle dest = uluaGetRectangleIndex( L, 3 );
	Vector2 origin = uluaGetVector2Index( L, 4 );
	float rotation = lua_tonumber( L, 5 );
	Color tint = uluaGetColorIndex( L, 6 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawTextureNPatch( *texturesGetSourceTexture( texId ), nPatchInfo, dest, origin, rotation, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.BeginTextureMode( RenderTexture2D target )

Begin drawing to render texture

- Failure return false
- Success return true
*/
int ltexturesBeginTextureMode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.BeginTextureMode( RenderTexture2D target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_RENDER_TEXTURE ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	BeginTextureMode( state->textures[ texId ]->renderTexture );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndTextureMode()

Ends drawing to render texture
*/
int ltexturesEndTextureMode( lua_State *L ) {
	EndTextureMode();

	return 1;
}

/*
> type = RL.GetTextureType( Texture2D texture )

Get texture type ( TEXTURE_TYPE_TEXTURE or TEXTURE_TYPE_RENDER_TEXTURE )

- Failure return false
- Success return int
*/
int ltexturesGetTextureType( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetTextureType( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->textures[ texId ]->type );

	return 1;
}

/*
## Textures - Texture Configuration
*/

/*
> success = RL.GenTextureMipmaps( Texture2D texture )

Generate GPU mipmaps for a texture

- Failure return false
- Success return true
*/
int ltexturesGenTextureMipmaps( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GenTextureMipmaps( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	GenTextureMipmaps( texturesGetSourceTexture( texId ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetTextureFilter( Texture2D texture, int filter )

Set texture scaling filter mode ( TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR... )

- Failure return false
- Success return true
*/
int ltexturesSetTextureFilter( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetTextureFilter( Texture2D texture, int filter )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	int filter = lua_tointeger( L, 2 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetTextureFilter( *texturesGetSourceTexture( texId ), filter );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetTextureWrap( Texture2D texture, int wrap )

Set texture wrapping mode ( TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP... )

- Failure return false
- Success return true
*/
int ltexturesSetTextureWrap( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetTextureWrap( Texture2D texture, int wrap )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	int wrap = lua_tointeger( L, 2 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	
	SetTextureWrap( *texturesGetSourceTexture( texId ), wrap );
	lua_pushboolean( L, true );

	return 1;
}

/*
> size = RL.GetTextureSize( Texture2D texture )

Get texture size

- Failure return nil
- Success return Vector2
*/
int ltexturesGetTextureSize( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetTextureSize( Texture2D texture )" );
		lua_pushnil( L );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushnil( L );
		return 1;
	}
	Texture2D texture = *texturesGetSourceTexture( texId );
	uluaPushVector2( L, (Vector2){ texture.width, texture.height } );

	return 1;
}

/*
> mipmaps = RL.GetTextureMipmaps( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int
*/
int ltexturesGetTextureMipmaps( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetTextureMipmaps( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validImage( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	Texture2D texture = *texturesGetSourceTexture( texId );
	lua_pushinteger( L, texture.mipmaps );

	return 1;
}

/*
> format = RL.GetTextureFormat( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int
*/
int ltexturesGetTextureFormat( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetTextureFormat( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );

	if ( !validImage( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	Texture2D texture = *texturesGetSourceTexture( texId );
	lua_pushinteger( L, texture.format );

	return 1;
}

/*
## Textures - Color/pixel
*/

/*
> color = RL.Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color
*/
int ltexturesFade( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.Fade( Color color, float alpha )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );
	float alpha = lua_tonumber( L, 2 );

	uluaPushColor( L, Fade( color, alpha ) );

	return 1;
}

/*
> value = RL.ColorToInt( Color color )

Returns hexadecimal value for a Color

- Failure return false
- Success return int
*/
int ltexturesColorToInt( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorToInt( Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );

	lua_pushinteger( L, ColorToInt( color ) );

	return 1;
}

/*
> color = RL.ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Failure return false
- Success return Vector4
*/
int ltexturesColorNormalize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorNormalize( Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );

	uluaPushVector4( L, ColorNormalize( color ) );

	return 1;
}

/*
> color = RL.ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Failure return false
- Success return Color
*/
int ltexturesColorFromNormalized( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorFromNormalized( Vector4 normalized )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector4 normalized = uluaGetVector4Index( L, 1 );

	uluaPushColor( L, ColorFromNormalized( normalized ) );

	return 1;
}

/*
> HSV = RL.ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Vector3
*/
int ltexturesColorToHSV( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorToHSV( Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );

	uluaPushVector3( L, ColorToHSV( color ) );

	return 1;
}

/*
> color = RL.ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Color
*/
int ltexturesColorFromHSV( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorFromHSV( float hue, float saturation, float value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float hue = lua_tonumber( L, 1 );
	float saturation = lua_tonumber( L, 2 );
	float value = lua_tonumber( L, 3 );

	uluaPushColor( L, ColorFromHSV( hue, saturation, value ) );

	return 1;
}

/*
> color = RL.ColorTint( Color color, Color tint )

Get color multiplied with another color

- Failure return false
- Success return Color
*/
int ltexturesColorTint( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorTint( Color color, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );
	Color tint = uluaGetColorIndex( L, 2 );

	uluaPushColor( L, ColorTint( color, tint ) );

	return 1;
}

/*
> color = RL.ColorBrightness( Color color, float factor )

Get color with brightness correction, brightness factor goes from -1.0f to 1.0f

- Failure return false
- Success return Color
*/
int ltexturesColorBrightness( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorBrightness( Color color, float factor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );
	float factor = lua_tonumber( L, 2 );

	uluaPushColor( L, ColorBrightness( color, factor ) );

	return 1;
}

/*
> color = RL.ColorContrast( Color color, float contrast )

Get color with contrast correction, contrast values between -1.0f and 1.0f

- Failure return false
- Success return Color
*/
int ltexturesColorContrast( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorContrast( Color color, float contrast )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );
	float contrast = lua_tonumber( L, 2 );

	uluaPushColor( L, ColorContrast( color, contrast ) );

	return 1;
}

/*
> color = RL.ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color
*/
int ltexturesColorAlpha( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorAlpha( Color color, float alpha )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );
	float alpha = lua_tonumber( L, 2 );

	uluaPushColor( L, ColorAlpha( color, alpha ) );

	return 1;
}

/*
> color = RL.ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Failure return false
- Success return Color
*/
int ltexturesColorAlphaBlend( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ColorAlphaBlend( Color dst, Color src, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color dst = uluaGetColorIndex( L, 1 );
	Color src = uluaGetColorIndex( L, 2 );
	Color tint = uluaGetColorIndex( L, 3 );

	uluaPushColor( L, ColorAlphaBlend( dst, src, tint ) );

	return 1;
}

/*
> color = RL.GetColor( unsigned int hexValue )

Get Color structure from hexadecimal value

- Failure return false
- Success return Color
*/
int ltexturesGetColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetColor( unsigned int hexValue )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int hexValue = (unsigned int)lua_tointeger( L, 1 );

	uluaPushColor( L, GetColor( hexValue ) );

	return 1;
}

/*
> color = RL.GetPixelColor( Texture2D texture, Vector2 position )

Get pixel color from source texture

- Failure return false
- Success return Color
*/
int ltexturesGetPixelColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetPixelColor( Texture2D texture, Vector2 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );

	if ( !validTexture( texId, TEXTURE_TYPE_ALL ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	Texture2D *texture = texturesGetSourceTexture( texId );
	Image srcImage = LoadImageFromTexture( *texture );

	uluaPushColor( L, GetImageColor( srcImage, pos.x, pos.y ) );
	UnloadImage( srcImage );

	return 1;
}

/*
> size = RL.GetPixelDataSize( int width, int height, int format )

Get pixel data size in bytes for certain format

- Failure return false
- Success return int
*/
int ltexturesGetPixelDataSize( lua_State *L ) {
	if ( !lua_isnumber( L, 1) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetPixelDataSize( int width, int height, int format )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int width = lua_tointeger( L, 1 );
	int height = lua_tointeger( L, 2 );
	int format = lua_tointeger( L, 3 );

	lua_pushinteger( L, GetPixelDataSize( width, height, format ) );

	return 1;
}
