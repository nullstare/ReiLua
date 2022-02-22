#include "main.h"
#include "state.h"
#include "text.h"
#include "lua_core.h"

static void checkFontRealloc( int i ) {
	if ( i == state->fontCount ) {
		state->fontCount++;
	}

	if ( state->fontCount == state->fontAlloc ) {
		state->fontAlloc += ALLOC_PAGE_SIZE;
		state->fonts = realloc( state->fonts, state->fontAlloc * sizeof( Font* ) );

		for ( i = state->fontCount; i < state->fontAlloc; i++ ) {
			state->fonts[i] = NULL;
		}
	}
}

bool validFont( size_t id ) {
	if ( id < 0 || state->fontCount < id || state->fonts[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid font", id );
		return false;
	}
	else {
		return true;
	}
}

/*
## Text - Loading
*/

/*
> font = RL_LoadFont( string fileName )

Load font from file into GPU memory ( VRAM )

- Failure return -1
- Success return int
*/
int ltextLoadFont( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadFont( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->fontCount; i++ ) {
		if ( state->fonts[i] == NULL ) {
			break;
		}
	}
	state->fonts[i] = malloc( sizeof( Font ) );
	*state->fonts[i] = LoadFont( lua_tostring( L, -1 ) );
	lua_pushinteger( L, i );
	checkFontRealloc( i );

	return 1;
}

/*
> success = RL_UnloadFont( Font font )

Unload Font from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int ltextUnloadFont( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadFont( Font font )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validFont( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadFont( *state->fonts[ id ] );
	state->fonts[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
## Text - Draw
*/

/*
> success = RL_DrawFPS( Vector2 pos )

Draw current FPS

- Failure return false
- Success return true
*/
int ltextDrawFPS( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawFPS( Vector2 pos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2( L );

	DrawFPS( pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawText( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters

- Failure return false
- Success return true
*/
int ltextDrawText( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_isstring( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawText( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float spacing = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float fontSize = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 position = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t fontId = lua_tointeger( L, -2 );

	if ( !validFont( fontId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawTextEx( *state->fonts[ fontId ], lua_tostring( L, -1 ), position, fontSize, spacing, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTextPro( Font font, const char text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters ( rotation )

- Failure return false
- Success return true
*/
int ltextDrawTextPro( lua_State *L ) {
	if ( !lua_isnumber( L, -8 ) || !lua_isstring( L, -7 ) || !lua_istable( L, -6 ) || !lua_istable( L, -5 )
	|| !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTextPro( Font font, const char text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float spacing = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float fontSize = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 origin = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 position = uluaGetVector2( L );
	lua_pop( L, 1 );
	size_t fontId = lua_tointeger( L, -2 );

	if ( !validFont( fontId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawTextPro( *state->fonts[ fontId ], lua_tostring( L, -1 ), position, origin, rotation, fontSize, spacing, color );
	lua_pushboolean( L, true );

	return 1;
}
