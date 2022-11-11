#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "easings.h"
#include "reasings.h"

/*
## Easings - Linear Easing functions
*/

/*
> value = RL_EaseLinear( float t, float b, float c, float d )

Ease linear

- Failure return false
- Success return float
*/
int leasingsEaseLinear( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseLinear( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseLinearNone( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Sine Easing functions
*/

/*
> value = RL_EaseSineIn( float t, float b, float c, float d )

Ease sine in

- Failure return false
- Success return float
*/
int leasingsEaseSineIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseSineIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseSineIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseSineOut( float t, float b, float c, float d )

Ease sine out

- Failure return false
- Success return float
*/
int leasingsEaseSineOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseSineOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseSineOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseSineInOut( float t, float b, float c, float d )

Ease sine in out

- Failure return false
- Success return float
*/
int leasingsEaseSineInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseSineInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseSineInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Circular Easing functions
*/

/*
> value = RL_EaseCircIn( float t, float b, float c, float d )

Ease circle in

- Failure return false
- Success return float
*/
int leasingsEaseCircIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCircIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCircIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseCircOut( float t, float b, float c, float d )

Ease circle out

- Failure return false
- Success return float
*/
int leasingsEaseCircOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCircOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCircOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseCircInOut( float t, float b, float c, float d )

Ease circle in out

- Failure return false
- Success return float
*/
int leasingsEaseCircInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCircInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCircInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Cubic Easing functions
*/

/*
> value = RL_EaseCubicIn( float t, float b, float c, float d )

Ease cubic in

- Failure return false
- Success return float
*/
int leasingsEaseCubicIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCubicIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCubicIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseCubicOut( float t, float b, float c, float d )

Ease cubic out

- Failure return false
- Success return float
*/
int leasingsEaseCubicOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCubicOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCubicOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseCubicInOut( float t, float b, float c, float d )

Ease cubic in out

- Failure return false
- Success return float
*/
int leasingsEaseCubicInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseCubicInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseCubicInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Quadratic Easing functions
*/

/*
> value = RL_EaseQuadIn( float t, float b, float c, float d )

Ease quadratic in

- Failure return false
- Success return float
*/
int leasingsEaseQuadIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseQuadIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseQuadIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseQuadOut( float t, float b, float c, float d )

Ease quadratic out

- Failure return false
- Success return float
*/
int leasingsEaseQuadOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseQuadOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseQuadOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseQuadInOut( float t, float b, float c, float d )

Ease quadratic in out

- Failure return false
- Success return float
*/
int leasingsEaseQuadInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseQuadInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseQuadInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Exponential Easing functions
*/

/*
> value = RL_EaseExpoIn( float t, float b, float c, float d )

Ease exponential in

- Failure return false
- Success return float
*/
int leasingsEaseExpoIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseExpoIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseExpoIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseExpoOut( float t, float b, float c, float d )

Ease exponential out

- Failure return false
- Success return float
*/
int leasingsEaseExpoOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseExpoOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseExpoOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseExpoInOut( float t, float b, float c, float d )

Ease exponential in out

- Failure return false
- Success return float
*/
int leasingsEaseExpoInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseExpoInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseExpoInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Back Easing functions
*/

/*
> value = RL_EaseBackIn( float t, float b, float c, float d )

Ease back in

- Failure return false
- Success return float
*/
int leasingsEaseBackIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBackIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBackIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseBackOut( float t, float b, float c, float d )

Ease back out

- Failure return false
- Success return float
*/
int leasingsEaseBackOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBackOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBackOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseBackInOut( float t, float b, float c, float d )

Ease back in out

- Failure return false
- Success return float
*/
int leasingsEaseBackInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBackInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBackInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Bounce Easing functions
*/

/*
> value = RL_EaseBounceIn( float t, float b, float c, float d )

Ease bounce in

- Failure return false
- Success return float
*/
int leasingsEaseBounceIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBounceIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBounceIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseBounceOut( float t, float b, float c, float d )

Ease bounce out

- Failure return false
- Success return float
*/
int leasingsEaseBounceOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBounceOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBounceOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseBounceInOut( float t, float b, float c, float d )

Ease bounce in out

- Failure return false
- Success return float
*/
int leasingsEaseBounceInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseBounceInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseBounceInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
## Easings - Elastic Easing functions
*/

/*
> value = RL_EaseElasticIn( float t, float b, float c, float d )

Ease elastic in

- Failure return false
- Success return float
*/
int leasingsEaseElasticIn( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseElasticIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseElasticIn( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseElasticOut( float t, float b, float c, float d )

Ease elastic out

- Failure return false
- Success return float
*/
int leasingsEaseElasticOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseElasticOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseElasticOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}

/*
> value = RL_EaseElasticInOut( float t, float b, float c, float d )

Ease elastic in out

- Failure return false
- Success return float
*/
int leasingsEaseElasticInOut( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_EaseElasticInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, EaseElasticInOut( lua_tonumber( L, -4 ), lua_tonumber( L, -3 ), lua_tonumber( L, -2 ), lua_tonumber( L, -1 ) ) );

	return 1;
}
