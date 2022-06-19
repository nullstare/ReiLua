#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "lrlgl.h"

/*
## RLGL - General render state
*/

/*
> success = RL_rlSetLineWidth( float width )

Set the line drawing width

- Failure return false
- Success return true
*/
int lrlglSetLineWidth( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_rlSetLineWidth( float width )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlSetLineWidth( lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> width = RL_rlGetLineWidth()

Get the line drawing width

- Success return float
*/
int lrlglGetLineWidth( lua_State *L ) {
	lua_pushnumber( L, rlGetLineWidth() );

	return 1;
}
