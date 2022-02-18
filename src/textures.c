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
		state->textures = realloc( state->textures, state->textureAlloc * sizeof( Texture2D* ) );

		for ( i = state->textureCount; i < state->textureAlloc; i++ ) {
			state->textures[i] = NULL;
		}
	}
}

static void checkRenderTextureRealloc( int i ) {
	if ( i == state->renderTextureCount ) {
		state->renderTextureCount++;
	}

	if ( state->renderTextureCount == state->renderTextureAlloc ) {
		state->renderTextureAlloc += ALLOC_PAGE_SIZE;
		state->renderTextures = realloc( state->renderTextures, state->renderTextureAlloc * sizeof( RenderTexture2D* ) );

		for ( i = state->renderTextureCount; i < state->renderTextureAlloc; i++ ) {
			state->renderTextures[i] = NULL;
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

bool validTexture( size_t id ) {
	if ( id < 0 || state->textureCount < id || state->textures[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid texture", id );
		return false;
	}
	else {
		return true;
	}
}

bool validRenderTexture( size_t id ) {
	if ( id < 0 || state->renderTextureCount < id || state->renderTextures[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid renderTexture", id );
		return false;
	}
	else {
		return true;
	}
}

bool validSourceTexture( size_t id ) {
	switch ( state->textureSource ) {
	case TEXTURE_SOURCE_TEXTURE:
		return validTexture( id );
	case TEXTURE_SOURCE_RENDER_TEXTURE:
		return validRenderTexture( id );
	default:
		return validTexture( id );
		break;
	}
}

Texture2D* texturesGetSourceTexture( size_t index ) {
	switch ( state->textureSource ) {
	case TEXTURE_SOURCE_TEXTURE:
		return state->textures[ index ];
	case TEXTURE_SOURCE_RENDER_TEXTURE:
		return &state->renderTextures[ index ]->texture;
	default:
		return state->textures[ index ];
		break;
	}
}

/*
## Textures - Load
*/

/*
> image = RL_LoadImage( string fileName )

Load image from file into CPU memory ( RAM )

- Failure return -1
- Success return int
*/
int ltexturesLoadImage( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadImage( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, -1 ) ) ) {
		int i = 0;

		for ( i = 0; i < state->imageCount; i++ ) {
			if ( state->images[i] == NULL ) {
				break;
			}
		}
		state->images[i] = malloc( sizeof( Image ) );
		*state->images[i] = LoadImage( lua_tostring( L, -1 ) );
		lua_pushinteger( L, i );
		checkImageRealloc( i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> image = RL_GenImageColor( int width, int height, Color color )

Generate image: plain color

- Failure return -1
- Success return int
*/
int ltexturesGenImageColor( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenImageColor( int width, int height, Color color )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int height = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int width = lua_tointeger( L, -1 );
	int i = 0;

	for ( i = 0; i < state->imageCount; i++ ) {
		if ( state->images[i] == NULL ) {
			break;
		}
	}
	state->images[i] = malloc( sizeof( Image ) );
	*state->images[i] = GenImageColor( width, height, color );
	lua_pushinteger( L, i );
	checkImageRealloc( i );

	return 1;
}

/*
> success = RL_UnloadImage( Image image )

Unload image from CPU memory ( RAM )

- Failure return false
- Success return true
*/
int ltexturesUnloadImage( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadImage( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

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
> texture = RL_LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return -1
- Success return int
*/
int ltexturesLoadTexture( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadTexture( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, -1 ) ) ) {
		int i = 0;

		for ( i = 0; i < state->textureCount; i++ ) {
			if ( state->textures[i] == NULL ) {
				break;
			}
		}
		state->textures[i] = malloc( sizeof( Texture2D ) );
		*state->textures[i] = LoadTexture( lua_tostring( L, -1 ) );
		lua_pushinteger( L, i );
		checkTextureRealloc( i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> texture = RL_LoadTextureFromImage( Image image )

Load texture from image data

- Failure return -1
- Success return int
*/
int ltexturesLoadTextureFromImage( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadTextureFromImage( Image image )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	int i = 0;

	for ( i = 0; i < state->textureCount; i++ ) {
		if ( state->textures[i] == NULL ) {
			break;
		}
	}
	state->textures[i] = malloc( sizeof( Texture2D ) );
	*state->textures[i] = LoadTextureFromImage( *state->images[ imageId ] );
	lua_pushinteger( L, i );
	checkTextureRealloc( i );

	return 1;
}

/*
> success = RL_UnloadTexture( Texture2D texture )

Unload texture from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int ltexturesUnloadTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadTexture( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validTexture( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadTexture( *state->textures[ id ] );
	state->textures[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> renderTexture = RL_LoadRenderTexture( Vector2 size )

Load texture for rendering ( framebuffer )

- Failure return -1
- Success return int
*/
int ltexturesLoadRenderTexture( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadRenderTexture( Vector2 size )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2( L );
	int i = 0;

	for ( i = 0; i < state->renderTextureCount; i++ ) {
		if ( state->renderTextures[i] == NULL ) {
			break;
		}
	}
	state->renderTextures[i] = malloc( sizeof( RenderTexture2D ) );
	*state->renderTextures[i] = LoadRenderTexture( (int)size.x, (int)size.y );
	lua_pushinteger( L, i );
	checkRenderTextureRealloc( i );

	return 1;
}

/*
> success = RL_UnloadRenderTexture( RenderTexture2D target )

Unload render texture from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int ltexturesUnloadRenderTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadRenderTexture( RenderTexture2D target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );
	
	if ( !validRenderTexture( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadRenderTexture( *state->renderTextures[ id ] );
	state->renderTextures[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
## Textures - Image Drawing
*/

/*
> success = RL_ImageClearBackground( Image dst, Color color )

Clear image background with given color

- Failure return false
- Success return true
*/
int ltexturesImageClearBackground( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageClearBackground( Image dst, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageClearBackground( state->images[ imageId ], color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawPixel( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDrawPixel( Image dst, Vector2 position, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 position = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawPixelV( state->images[ imageId ], position, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )

Draw line within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawLine( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 end = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 start = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawLineV( state->images[ imageId ], start, end, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawCircle( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int radius = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawCircleV( state->images[ imageId ], center, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawRectangle( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDrawRectangle( Image dst, Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawRectangleRec( state->images[ imageId ], rec, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image

- Failure return false
- Success return true
*/
int ltexturesImageDrawRectangleLines( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int thick = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Rectangle rec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawRectangleLines( state->images[ imageId ], rec, thick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image ( Tint applied to source )

- Failure return false
- Success return true
*/
int ltexturesImageDraw( lua_State *L ) {
	if ( !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle dstRec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle srcRec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t imageSrcId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t imageDstId = lua_tointeger( L, -1 );

	if ( !validImage( imageDstId ) || !validImage( imageSrcId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDraw( state->images[ imageDstId ], *state->images[ imageSrcId ], srcRec, dstRec, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text ( Custom sprite font ) within an image ( Destination )

- Failure return false
- Success return true
*/
int ltexturesImageDrawTextEx( lua_State *L ) {
	if ( !lua_isnumber( L, -7 ) || !lua_isnumber( L, -6 ) || !lua_isstring( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	float spacing = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float fontSize = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 position = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t fontId = lua_tointeger( L, -2 );
	size_t imageId = lua_tointeger( L, -3 );

	if ( !validImage( imageId ) || !validFont( fontId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	ImageDrawTextEx( state->images[ imageId ], *state->fonts[ fontId ], lua_tostring( L, -1 ), position, fontSize, spacing, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Textures - Texture Drawing
*/

/*
> success = RL_DrawTexture( Texture2D texture, Vector2 position, Color tint )

Draw a Texture2D

- Failure return false
- Success return true
*/
int ltexturesDrawTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTexture( Texture2D texture, Vector2 position, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 pos = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTexture( *texturesGetSourceTexture( texId ), pos.x, pos.y, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle

- Failure return false
- Success return true
*/
int ltexturesDrawTextureRec( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 )  || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 pos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle srcRect = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTextureRec( *texturesGetSourceTexture( texId ), srcRect, pos, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTextureTiled( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint )

Draw part of a texture ( defined by a rectangle ) with rotation and scale tiled into dest

- Failure return false
- Success return true
*/
int ltexturesDrawTextureTiled( lua_State *L ) {
	if ( !lua_isnumber( L, -7 ) || !lua_istable( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTextureTiled( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float scale = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float rot = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 origin = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle dstRect = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle srcRect = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTextureTiled( *texturesGetSourceTexture( texId ), srcRect, dstRect, origin, rot, scale, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters

- Failure return false
- Success return true
*/
int ltexturesDrawTexturePro( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float rot = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 origin = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle dstRect = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle srcRect = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTexturePro( *texturesGetSourceTexture( texId ), srcRect, dstRect, origin, rot, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture ( or part of it ) that stretches or shrinks nicely

- Failure return false
- Success return true
*/
int ltexturesDrawTextureNPatch( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 origin = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle dest = uluaGetRectangle( L );
	lua_pop( L, 1 );
	NPatchInfo nPatchInfo = uluaGetNPatchInfo( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawTextureNPatch( *texturesGetSourceTexture( texId ), nPatchInfo, dest, origin, rotation, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTexturePoly( Texture2D texture, Vector2 center, Vector2{} points, Vector2{} texcoords, int pointsCount, Color tint )

Draw a textured polygon ( Convex )

- Failure return false
- Success return true
*/
int ltexturesDrawTexturePoly( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTexturePoly( Texture2D texture, Vector2 center, Vector2 points{}, Vector2 texcoords{}, int pointsCount, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int pointsCount = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 texCoords[ pointsCount ];

	int t = lua_gettop( L ), i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		texCoords[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	Vector2 points[ pointsCount ];

	t = lua_gettop( L );
	i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawTexturePoly( *texturesGetSourceTexture( texId ), center, points, texCoords, pointsCount, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_BeginTextureMode( RenderTexture2D target )

Begin drawing to render texture

- Failure return false
- Success return true
*/
int ltexturesBeginTextureMode( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_BeginTextureMode( RenderTexture2D target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, -1 );

	if ( !validRenderTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	BeginTextureMode( *state->renderTextures[ texId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_EndTextureMode()

Ends drawing to render texture
*/
int ltexturesEndTextureMode( lua_State *L ) {
	EndTextureMode();

	return 1;
}

/*
> success = RL_SetTextureSource( int textureSource )

Set what texture source to use ( TEXTURE_SOURCE_TEXTURE or TEXTURE_SOURCE_RENDER_TEXTURE )

- Failure return false
- Success return true
*/
int ltexturesSetTextureSource( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetTextureSource( int textureSource )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int texSource = lua_tointeger( L, -1 );

	if ( texSource != TEXTURE_SOURCE_TEXTURE && texSource != TEXTURE_SOURCE_RENDER_TEXTURE ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid source texture", texSource );
		lua_pushboolean( L, false );
		return 1;
	}

	state->textureSource = texSource;
	lua_pushboolean( L, true );

	return 1;
}

/*
> textureSource = RL_GetTextureSource()

Get current texture source type ( TEXTURE_SOURCE_TEXTURE or TEXTURE_SOURCE_RENDER_TEXTURE )

- Success return int
*/
int ltexturesGetTextureSource( lua_State *L ) {
	lua_pushinteger( L, state->textureSource );

	return 1;
}

/*
## Textures - Configure
*/

/*
> success = RL_GenTextureMipmaps( Texture2D texture )

Generate GPU mipmaps for a texture

- Failure return false
- Success return true
*/
int ltexturesGenTextureMipmaps( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenTextureMipmaps( Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, -1 );

	if ( !validTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	GenTextureMipmaps( texturesGetSourceTexture( texId ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetTextureFilter( Texture2D texture, int filter )

Set texture scaling filter mode ( TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR... )

- Failure return false
- Success return true
*/
int ltexturesSetTextureFilter( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetTextureFilter( Texture2D texture, int filter )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, -2 );

	if ( !validTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetTextureFilter( *texturesGetSourceTexture( texId ), lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetTextureWrap( Texture2D texture, int wrap )

Set texture wrapping mode ( TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP... )

- Failure return false
- Success return true
*/
int ltexturesSetTextureWrap( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetTextureWrap( Texture2D texture, int wrap )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, -2 );

	if ( !validTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	
	SetTextureWrap( *state->textures[ texId ], lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> size = RL_GetTextureSize( Texture2D texture )

Get texture size

- Failure return nil
- Success return Vector2
*/
int ltexturesGetTextureSize( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetTextureSize( Texture2D texture )" );
		lua_pushnil( L );
		return 1;
	}
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	Texture2D texture = *texturesGetSourceTexture( texId );
	uluaPushVector2( L, (Vector2){ texture.width, texture.height } );

	return 1;
}
