#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "core.h"
#include "lights.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

static void checkLightRealloc( int i ) {
	if ( i == state->lightCount ) {
		state->lightCount++;
	}

	if ( state->lightCount == state->lightAlloc ) {
		state->lightAlloc += ALLOC_PAGE_SIZE;
		state->lights = realloc( state->lights, state->lightAlloc * sizeof( Light* ) );

		for ( i = state->lightCount; i < state->lightAlloc; i++ ) {
			state->lights[i] = NULL;
		}
	}
}

bool validLight( size_t id ) {
	if ( id < 0 || state->lightCount < id || state->lights[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid light", id );
		return false;
	}
	else {
		return true;
	}
}

/*
## Lights - Basics
*/

/*
> light = RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )

Create a light and get shader locations

- Failure return -1
- Success return int
*/
int llightsCreateLight( lua_State *L ) {
	if ( !lua_isnumber( L, -5 ) || !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 target = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );
	lua_pop( L, 1 );
	int type = lua_tointeger( L, -1 );

	int i = 0;

	for ( i = 0; i < state->lightCount; i++ ) {
		if ( state->lights[i] == NULL ) {
			break;
		}
	}
	state->lights[i] = malloc( sizeof( Light ) );
	*state->lights[i] = CreateLight( type, position, target, color, *state->shaders[ shaderId ] );
	lua_pushinteger( L, i );
	checkLightRealloc( i );

	return 1;
}

/*
> success = RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader

- Failure return false
- Success return true
*/
int llightsUpdateLightValues( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UpdateLightValues( Shader shader, Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t shaderId = lua_tointeger( L, -1 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UpdateLightValues( *state->shaders[ shaderId ], *state->lights[ lightId ] );
	lua_pushboolean( L, true );

	return 1;
}
