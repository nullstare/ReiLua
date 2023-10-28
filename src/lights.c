#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "core.h"
#include "lights.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

/*
## Lights - Basics
*/

/*
> light = RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )

Create a light and get shader locations

- Success return Light
*/
int llightsCreateLight( lua_State *L ) {
	int type = luaL_checkinteger( L, 1 );
	Vector3 position = uluaGetVector3Index( L, 2 );
	Vector3 target = uluaGetVector3Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );
	Shader *shader = luaL_checkudata( L, 5, "Shader" );

	uluaPushLight( L, CreateLight( type, position, target, color, *shader ) );

	return 1;
}

/*
> RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader
*/
int llightsUpdateLightValues( lua_State *L ) {
	Shader *shader = luaL_checkudata( L, 1, "Shader" );
	Light *light = luaL_checkudata( L, 2, "Light" );

	UpdateLightValues( *shader, *light );

	return 0;
}

/*
> RL.SetLightType( Light light, int type )

Set light type
*/
int llightsSetLightType( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );
	int type = luaL_checkinteger( L, 2 );

	light->type = type;

	return 0;
}

/*
> RL.SetLightPosition( Light light, Vector3 position )

Set light position
*/
int llightsSetLightPosition( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );
	Vector3 position = uluaGetVector3Index( L, 2 );

	light->position = position;

	return 0;
}

/*
> RL.SetLightTarget( Light light, Vector3 target )

Set light target
*/
int llightsSetLightTarget( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );
	Vector3 target = uluaGetVector3Index( L, 2 );

	light->target = target;

	return 0;
}

/*
> RL.SetLightColor( Light light, Color color )

Set light color
*/
int llightsSetLightColor( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );
	Color color = uluaGetColorIndex( L, 2 );

	light->color = color;

	return 0;
}

/*
> RL.SetLightEnabled( Light light, bool enabled )

Set light enabled
*/
int llightsSetLightEnabled( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );
	bool enabled = uluaGetBoolean( L, 2 );

	light->enabled = enabled;

	return 0;
}

/*
> type = RL.GetLightType( Light light )

Get light type

- Success return int
*/
int llightsGetLightType( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );

	lua_pushinteger( L, light->type );

	return 1;
}

/*
> position = RL.GetLightPosition( Light light )

Get light position

- Success return Vector3
*/
int llightsGetLightPosition( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );

	uluaPushVector3( L, light->position );

	return 1;
}

/*
> target = RL.GetLightTarget( Light light )

Get light target

- Success return Vector3
*/
int llightsGetLightTarget( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );

	uluaPushVector3( L, light->target );

	return 1;
}

/*
> color = RL.GetLightColor( Light light )

Get light color

- Success return Color
*/
int llightsGetLightColor( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );

	uluaPushColor( L, light->color );

	return 1;
}

/*
> enabled = RL.IsLightEnabled( Light light )

Get light enabled

- Success return boolean
*/
int llightsIsLightEnabled( lua_State *L ) {
	Light *light = luaL_checkudata( L, 1, "Light" );

	lua_pushboolean( L, light->enabled );

	return 1;
}
