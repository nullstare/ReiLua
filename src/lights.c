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

static int newLight() {
	int i = 0;

	for ( i = 0; i < state->lightCount; i++ ) {
		if ( state->lights[i] == NULL ) {
			break;
		}
	}
	state->lights[i] = malloc( sizeof( Light ) );
	checkLightRealloc( i );

	return i;
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
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 ) || !lua_isnumber( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int type = lua_tointeger( L, 1 );
	Vector3 position = uluaGetVector3Index( L, 2 );
	Vector3 target = uluaGetVector3Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );
	size_t shaderId = lua_tointeger( L, 5 );

	int i = newLight();
	*state->lights[i] = CreateLight( type, position, target, color, *state->shaders[ shaderId ] );
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader

- Failure return false
- Success return true
*/
int llightsUpdateLightValues( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UpdateLightValues( Shader shader, Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	size_t lightId = lua_tointeger( L, 2 );

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

/*
> success = RL.SetLightType( Light light, int type )

Set light type

- Failure return false
- Success return true
*/
int llightsSetLightType( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetLightType( Light light, int type )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );
	int type = lua_tointeger( L, 2 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->lights[ lightId ]->type = type;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetLightPosition( Light light, Vector3 position )

Set light position

- Failure return false
- Success return true
*/
int llightsSetLightPosition( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetLightPosition( Light light, Vecto3 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );
	Vector3 position = uluaGetVector3Index( L, 2 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->lights[ lightId ]->position = position;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetLightTarget( Light light, Vector3 target )

Set light target

- Failure return false
- Success return true
*/
int llightsSetLightTarget( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetLightTarget( Light light, Vecto3 target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );
	Vector3 target = uluaGetVector3Index( L, 2 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->lights[ lightId ]->target = target;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetLightColor( Light light, Color color )

Set light color

- Failure return false
- Success return true
*/
int llightsSetLightColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetLightColor( Light light, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->lights[ lightId ]->color = color;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetLightEnabled( Light light, bool enabled )

Set light enabled

- Failure return false
- Success return true
*/
int llightsSetLightEnabled( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isboolean( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetLightEnabled( Light light, bool enabled )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );
	bool enabled = lua_toboolean( L, 2 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->lights[ lightId ]->enabled = enabled;
	lua_pushboolean( L, true );

	return 1;
}

/*
> type = RL.GetLightType( Light light )

Get light type

- Failure return false
- Success return int
*/
int llightsGetLightType( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetLightType( Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->lights[ lightId ]->type );

	return 1;
}

/*
> position = RL.GetLightPosition( Light light )

Get light position

- Failure return false
- Success return Vector3
*/
int llightsGetLightPosition( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetLightPosition( Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushVector3( L, state->lights[ lightId ]->position );

	return 1;
}

/*
> target = RL.GetLightTarget( Light light )

Get light target

- Failure return false
- Success return Vector3
*/
int llightsGetLightTarget( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetLightTarget( Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushVector3( L, state->lights[ lightId ]->target );

	return 1;
}

/*
> color = RL.GetLightColor( Light light )

Get light color

- Failure return false
- Success return Color
*/
int llightsGetLightColor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetLightColor( Light light )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );

	if ( !validLight( lightId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushColor( L, state->lights[ lightId ]->color );

	return 1;
}

/*
> enabled = RL.IsLightEnabled( Light light )

Get light enabled

- Failure return nil
- Success return boolean
*/
int llightsIsLightEnabled( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.IsLightEnabled( Light light )" );
		lua_pushnil( L );
		return 1;
	}
	size_t lightId = lua_tointeger( L, 1 );

	if ( !validLight( lightId ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, state->lights[ lightId ]->enabled );

	return 1;
}
