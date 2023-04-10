#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "easings.h"
#include "reasings.h"

/*
## Easings - Linear Easing functions
*/

/*
> value = RL.EaseLinear( float t, float b, float c, float d )

Ease linear

- Failure return false
- Success return float
*/
int leasingsEaseLinear( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseLinear( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseLinearNone( t, b, c, d ) );

	return 1;
}

/*
## Easings - Sine Easing functions
*/

/*
> value = RL.EaseSineIn( float t, float b, float c, float d )

Ease sine in

- Failure return false
- Success return float
*/
int leasingsEaseSineIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseSineIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseSineIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseSineOut( float t, float b, float c, float d )

Ease sine out

- Failure return false
- Success return float
*/
int leasingsEaseSineOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseSineOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseSineOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseSineInOut( float t, float b, float c, float d )

Ease sine in out

- Failure return false
- Success return float
*/
int leasingsEaseSineInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseSineInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseSineInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Circular Easing functions
*/

/*
> value = RL.EaseCircIn( float t, float b, float c, float d )

Ease circle in

- Failure return false
- Success return float
*/
int leasingsEaseCircIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCircIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseCircIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseCircOut( float t, float b, float c, float d )

Ease circle out

- Failure return false
- Success return float
*/
int leasingsEaseCircOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCircOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseCircOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseCircInOut( float t, float b, float c, float d )

Ease circle in out

- Failure return false
- Success return float
*/
int leasingsEaseCircInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCircInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseCircInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Cubic Easing functions
*/

/*
> value = RL.EaseCubicIn( float t, float b, float c, float d )

Ease cubic in

- Failure return false
- Success return float
*/
int leasingsEaseCubicIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCubicIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseCubicIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseCubicOut( float t, float b, float c, float d )

Ease cubic out

- Failure return false
- Success return float
*/
int leasingsEaseCubicOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCubicOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );

	lua_pushnumber( L, EaseCubicOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseCubicInOut( float t, float b, float c, float d )

Ease cubic in out

- Failure return false
- Success return float
*/
int leasingsEaseCubicInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseCubicInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseCubicInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Quadratic Easing functions
*/

/*
> value = RL.EaseQuadIn( float t, float b, float c, float d )

Ease quadratic in

- Failure return false
- Success return float
*/
int leasingsEaseQuadIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseQuadIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseQuadIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseQuadOut( float t, float b, float c, float d )

Ease quadratic out

- Failure return false
- Success return float
*/
int leasingsEaseQuadOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseQuadOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseQuadOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseQuadInOut( float t, float b, float c, float d )

Ease quadratic in out

- Failure return false
- Success return float
*/
int leasingsEaseQuadInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseQuadInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseQuadInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Exponential Easing functions
*/

/*
> value = RL.EaseExpoIn( float t, float b, float c, float d )

Ease exponential in

- Failure return false
- Success return float
*/
int leasingsEaseExpoIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseExpoIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseExpoIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseExpoOut( float t, float b, float c, float d )

Ease exponential out

- Failure return false
- Success return float
*/
int leasingsEaseExpoOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseExpoOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseExpoOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseExpoInOut( float t, float b, float c, float d )

Ease exponential in out

- Failure return false
- Success return float
*/
int leasingsEaseExpoInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseExpoInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseExpoInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Back Easing functions
*/

/*
> value = RL.EaseBackIn( float t, float b, float c, float d )

Ease back in

- Failure return false
- Success return float
*/
int leasingsEaseBackIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBackIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBackIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseBackOut( float t, float b, float c, float d )

Ease back out

- Failure return false
- Success return float
*/
int leasingsEaseBackOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBackOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBackOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseBackInOut( float t, float b, float c, float d )

Ease back in out

- Failure return false
- Success return float
*/
int leasingsEaseBackInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBackInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBackInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Bounce Easing functions
*/

/*
> value = RL.EaseBounceIn( float t, float b, float c, float d )

Ease bounce in

- Failure return false
- Success return float
*/
int leasingsEaseBounceIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBounceIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBounceIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseBounceOut( float t, float b, float c, float d )

Ease bounce out

- Failure return false
- Success return float
*/
int leasingsEaseBounceOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBounceOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBounceOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseBounceInOut( float t, float b, float c, float d )

Ease bounce in out

- Failure return false
- Success return float
*/
int leasingsEaseBounceInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseBounceInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseBounceInOut( t, b, c, d ) );

	return 1;
}

/*
## Easings - Elastic Easing functions
*/

/*
> value = RL.EaseElasticIn( float t, float b, float c, float d )

Ease elastic in

- Failure return false
- Success return float
*/
int leasingsEaseElasticIn( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseElasticIn( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseElasticIn( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseElasticOut( float t, float b, float c, float d )

Ease elastic out

- Failure return false
- Success return float
*/
int leasingsEaseElasticOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseElasticOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseElasticOut( t, b, c, d ) );

	return 1;
}

/*
> value = RL.EaseElasticInOut( float t, float b, float c, float d )

Ease elastic in out

- Failure return false
- Success return float
*/
int leasingsEaseElasticInOut( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.EaseElasticInOut( float t, float b, float c, float d )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float t = lua_tonumber( L, 1 );
	float b = lua_tonumber( L, 2 );
	float c = lua_tonumber( L, 3 );
	float d = lua_tonumber( L, 4 );
	
	lua_pushnumber( L, EaseElasticInOut( t, b, c, d ) );

	return 1;
}
