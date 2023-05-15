#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "lrlgl.h"

/*
## RLGL - General render state
*/

/*
> RL.rlEnableColorBlend()

Enable color blending
*/
int lrlglEnableColorBlend( lua_State *L ) {
	rlEnableColorBlend();

	return 0;
}

/*
> RL.rlDisableColorBlend()

Disable color blending
*/
int lrlglDisableColorBlend( lua_State *L ) {
	rlDisableColorBlend();

	return 0;
}

/*
> RL.rlEnableDepthTest()

Enable depth test
*/
int lrlglEnableDepthTest( lua_State *L ) {
	rlEnableDepthTest();

	return 0;
}

/*
> RL.rlDisableDepthTest()

Disable depth test
*/
int lrlglDisableDepthTest( lua_State *L ) {
	rlDisableDepthTest();

	return 0;
}

/*
> RL.rlEnableDepthMask()

Enable depth write
*/
int lrlglEnableDepthMask( lua_State *L ) {
	rlEnableDepthMask();

	return 0;
}

/*
> RL.rlDisableDepthMask()

Disable depth write
*/
int lrlglDisableDepthMask( lua_State *L ) {
	rlDisableDepthMask();

	return 0;
}

/*
> RL.rlEnableBackfaceCulling()

Enable backface culling
*/
int lrlglEnableBackfaceCulling( lua_State *L ) {
	rlEnableBackfaceCulling();

	return 0;
}

/*
> RL.rlDisableBackfaceCulling()

Disable backface culling
*/
int lrlglDisableBackfaceCulling( lua_State *L ) {
	rlDisableBackfaceCulling();

	return 0;
}

/*
> success = RL.rlSetCullFace( int mode )

Set face culling mode

- Failure return false
- Success return true
*/
int lrlglSetCullFace( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlSetCullFace( int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlSetCullFace( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.rlSetLineWidth( float width )

Set the line drawing width

- Failure return false
- Success return true
*/
int lrlglSetLineWidth( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlSetLineWidth( float width )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlSetLineWidth( lua_tonumber( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> width = RL.rlGetLineWidth()

Get the line drawing width

- Success return float
*/
int lrlglGetLineWidth( lua_State *L ) {
	lua_pushnumber( L, rlGetLineWidth() );

	return 1;
}

/*
> RL.rlEnableSmoothLines()

Enable line aliasing
*/
int lrlglEnableSmoothLines( lua_State *L ) {
	rlEnableSmoothLines();

	return 0;
}

/*
> RL.rlDisableSmoothLines()

Disable line aliasing
*/
int lrlglDisableSmoothLines( lua_State *L ) {
	rlDisableSmoothLines();

	return 0;
}

/*
## RLGL - Initialization functions
*/

/*
> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int
*/
int lrlglGetVersion( lua_State *L ) {
	lua_pushinteger( L, rlGetVersion() );

	return 1;
}
