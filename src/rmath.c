#include "main.h"
#include "state.h"
#include "rmath.h"
#include "lua_core.h"

inline int imin( int a, int b ) {
    return a < b ? a : b;
}

inline int imax( int a, int b ) {
    return a > b ? a : b;
}

/*
## Math - Utils
*/

/*
> result = RL_Clamp( float value, float min, float max )

Clamp float value

- Failure return false
- Success return float
*/
int lmathClamp( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Clamp( float value, float min, float max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float max = lua_tonumber( L, -1 );
	float min = lua_tonumber( L, -2 );
	float value = lua_tonumber( L, -3 );

	lua_pushnumber( L, Clamp( value, min, max ) );

	return 1;
}

/*
> result = RL_Lerp( float start, float end, float amount )

Calculate linear interpolation between two floats

- Failure return false
- Success return float
*/
int lmathLerp( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Lerp( float start, float end, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	float end = lua_tonumber( L, -2 );
	float start = lua_tonumber( L, -3 );

	lua_pushnumber( L, Lerp( start, end, amount ) );

	return 1;
}

/*
> result = RL_Normalize( float value, float start, float end )

Normalize input value within input range

- Failure return false
- Success return float
*/
int lmathNormalize( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Normalize( float value, float start, float end )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float end = lua_tonumber( L, -1 );
	float start = lua_tonumber( L, -2 );
	float value = lua_tonumber( L, -3 );

	lua_pushnumber( L, Normalize( value, start, end ) );

	return 1;
}

/*
> result = RL_Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )

Remap input value within input range to output range

- Failure return false
- Success return float
*/
int lmathRemap( lua_State *L ) {
	if ( !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 )
	|| !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float outputEnd = lua_tonumber( L, -1 );
	float outputStart = lua_tonumber( L, -2 );
	float inputEnd = lua_tonumber( L, -3 );
	float inputStart = lua_tonumber( L, -4 );
	float value = lua_tonumber( L, -5 );

	lua_pushnumber( L, Remap( value, inputStart, inputEnd, outputStart, outputEnd ) );

	return 1;
}

/*
## Math - Vector2
*/

/*
> result = RL_Vector2Zero()

Vector with components value 0.0f

- Success return Vector2
*/
int lmathVector2Zero( lua_State *L ) {
	uluaPushVector2( L, Vector2Zero() );

	return 1;
}

/*
> result = RL_Vector2One()

Vector with components value 1.0f

- Success return Vector2
*/
int lmathVector2One( lua_State *L ) {
	uluaPushVector2( L, Vector2One() );

	return 1;
}

/*
> result = RL_Vector2Add( Vector2 v1, Vector2 v2 )

Add two vectors (v1 + v2)

- Failure return false
- Success return Vector2
*/
int lmathVector2Add( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Add( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Add( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2AddValue( Vector2 v, float add )

Add vector and float value

- Failure return false
- Success return Vector2
*/
int lmathVector2AddValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2AddValue( Vector2 v, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float add = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2AddValue( v, add ) );

	return 1;
}

/*
> result = RL_Vector2Subtract( Vector2 v1, Vector2 v2 )

Subtract two vectors (v1 - v2)

- Failure return false
- Success return Vector2
*/
int lmathVector2Subtract( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Subtract( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Subtract( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2SubtractValue( Vector2 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector2
*/
int lmathVector2SubtractValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2SubtractValue( Vector2 v, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float sub = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2SubtractValue( v, sub ) );

	return 1;
}

/*
> result = RL_Vector2Length( vector2 v )

Calculate vector length

- Failure return false
- Success return float
*/
int lmathVector2Length( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Length( vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2( L );

	lua_pushnumber( L, Vector2Length( v ) );

	return 1;
}

/*
> result = RL_Vector2LengthSqr( vector2 v )

Calculate vector square length

- Failure return false
- Success return float
*/
int lmathVector2LengthSqr( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2LengthSqr( vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2( L );

	lua_pushnumber( L, Vector2LengthSqr( v ) );

	return 1;
}

/*
> result = RL_Vector2DotProduct( Vector2 v1, Vector2 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float
*/
int lmathVector2DotProduct( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2DotProduct( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	lua_pushnumber( L, Vector2DotProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Distance( Vector2 v1, Vector2 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector2Distance( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Distance( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	lua_pushnumber( L, Vector2Distance( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Angle( Vector2 v1, Vector2 v2 )

Calculate angle from two vectors

- Failure return false
- Success return float
*/
int lmathVector2Angle( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Angle( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	lua_pushnumber( L, Vector2Angle( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Scale( Vector2 v, float scale )

Scale vector ( multiply by value )

- Failure return false
- Success return Vector2
*/
int lmathVector2Scale( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Scale( Vector2 v, float scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float scale = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Scale( v, scale ) );

	return 1;
}

/*
> result = RL_Vector2Multiply( Vector2 v1, Vector2 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Multiply( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Multiply( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Multiply( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Negate( Vector2 v )

Negate vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Negate( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Negate( Vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Negate( v ) );

	return 1;
}

/*
> result = RL_Vector2Divide( Vector2 v1, Vector2 v2 )

Divide vector by vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Divide( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Divide( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Divide( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Normalize( Vector2 v )

Normalize provided vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Normalize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Normalize( Vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Normalize( v ) );

	return 1;
}

/*
> result = RL_Vector2Lerp( Vector2 v1, Vector2 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector2
*/
int lmathVector2Lerp( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Lerp( Vector2 v1, Vector2 v2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Lerp( v1, v2, amount ) );

	return 1;
}

/*
> result = RL_Vector2Reflect( Vector2 v, Vector2 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector2
*/
int lmathVector2Reflect( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Reflect( Vector2 v, Vector2 normal )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Reflect( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector2Rotate( Vector2 v, float angle )

Rotate vector by angle

- Failure return false
- Success return Vector2
*/
int lmathVector2Rotate( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2Rotate( Vector2 v, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float degs = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v = uluaGetVector2( L );

	uluaPushVector2( L, Vector2Rotate( v, degs ) );

	return 1;
}

/*
> result = RL_Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )

Move Vector towards target

- Failure return false
- Success return Vector2
*/
int lmathVector2MoveTowards( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float maxDistance = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	uluaPushVector2( L, Vector2MoveTowards( v1, v2, maxDistance ) );

	return 1;
}

/*
## Math - Vector 3
*/

/*
> result = RL_Vector3Zero()

Vector with components value 0.0f

- Success return Vector3
*/
int lmathVector3Zero( lua_State *L ) {
	uluaPushVector3( L, Vector3Zero() );

	return 1;
}

/*
> result = RL_Vector3One()

Vector with components value 1.0f

- Success return Vector3
*/
int lmathVector3One( lua_State *L ) {
	uluaPushVector3( L, Vector3One() );

	return 1;
}

/*
> result = RL_Vector3Add( Vector3 v1, Vector3 v2 )

Add two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Add( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Add( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Add( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3AddValue( Vector3 v, float add )

Add vector and float value

- Failure return false
- Success return Vector3
*/
int lmathVector3AddValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3AddValue( Vector3 v, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float add = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3AddValue( v, add ) );

	return 1;
}

/*
> result = RL_Vector3Subtract( Vector3 v1, Vector3 v2 )

Subtract two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Subtract( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Subtract( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Subtract( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3SubtractValue( Vector3 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector3
*/
int lmathVector3SubtractValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3SubtractValue( Vector3 v, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float sub = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3SubtractValue( v, sub ) );

	return 1;
}

/*
> result = RL_Vector3Scale( Vector3 v, float scalar )

Multiply vector by scalar

- Failure return false
- Success return Vector3
*/
int lmathVector3Scale( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Scale( Vector3 v, float scalar )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float scalar = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Scale( v, scalar ) );

	return 1;
}

/*
> result = RL_Vector3Multiply( Vector3 v1, Vector3 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Multiply( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Multiply( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Multiply( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3CrossProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors cross product

- Failure return false
- Success return Vector3
*/
int lmathVector3CrossProduct( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3CrossProduct( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3CrossProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Perpendicular( Vector3 v )

Calculate one vector perpendicular vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Perpendicular( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Perpendicular( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Perpendicular( v ) );

	return 1;
}

/*
> result = RL_Vector3Length( Vector3 v )

Calculate vector length

- Failure return false
- Success return float
*/
int lmathVector3Length( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Length( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	lua_pushnumber( L, Vector3Length( v ) );

	return 1;
}

/*
> result = RL_Vector3LengthSqr( Vector3 v )

Calculate vector square length

- Failure return false
- Success return float
*/
int lmathVector3LengthSqr( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3LengthSqr( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	lua_pushnumber( L, Vector3LengthSqr( v ) );

	return 1;
}

/*
> result = RL_Vector3DotProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float
*/
int lmathVector3DotProduct( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3DotProduct( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	lua_pushnumber( L, Vector3DotProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Distance( Vector3 v1, Vector3 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector3Distance( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Distance( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	lua_pushnumber( L, Vector3Distance( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Angle( Vector3 v1, Vector3 v2 )

Calculate angle between two vectors

- Failure return false
- Success return float
*/
int lmathVector3Angle( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Angle( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	lua_pushnumber( L, Vector3Angle( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Negate( Vector3 v )

Negate provided vector ( invert direction )

- Failure return false
- Success return Vector3
*/
int lmathVector3Negate( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Negate( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Negate( v ) );

	return 1;
}

/*
> result = RL_Vector3Divide( Vector3 v1, Vector3 v2 )

Divide vector by vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Divide( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Divide( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Divide( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Normalize( Vector3 v )

Normalize provided vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Normalize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Normalize( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Normalize( v ) );

	return 1;
}

/*
> v1, v2 = RL_Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )

Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
Gram-Schmidt function implementation

- Failure return false
- Success return Vector3, Vector3
*/
int lmathVector3OrthoNormalize( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	Vector3OrthoNormalize( &v1, &v2 );

	uluaPushVector3( L, v1 );
	uluaPushVector3( L, v2 );

	return 2;
}

/*
> result = RL_Vector3Transform( Vector3 v, Matrix mat )

Transforms a Vector3 by a given Matrix

- Failure return false
- Success return Vector3
*/
int lmathVector3Transform( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Transform( Vector3 v, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Transform( v, mat ) );

	return 1;
}

/*
> result = RL_Vector3RotateByQuaternion( Vector3 v, Quaternion q )

Transform a vector by quaternion rotation

- Failure return false
- Success return Vector3
*/
int lmathVector3RotateByQuaternion( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3RotateByQuaternion( Vector3 v, Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Vector3 v = uluaGetVector3( L );

	uluaPushVector3( L, Vector3RotateByQuaternion( v, q ) );

	return 1;
}

/*
> result = RL_Vector3Lerp( Vector3 v1, Vector3 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Lerp( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Lerp( Vector3 v1, Vector3 v2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Lerp( v1, v2, amount ) );

	return 1;
}

/*
> result = RL_Vector3Reflect( Vector3 v, Vector3 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector3
*/
int lmathVector3Reflect( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Reflect( Vector3 v, Vector3 normal )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 normal = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Reflect( v1, normal ) );

	return 1;
}

/*
> result = RL_Vector3Min( Vector3 v1, Vector3 v2 )

Get min value for each pair of components

- Failure return false
- Success return Vector3
*/
int lmathVector3Min( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Min( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Min( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Max( Vector3 v1, Vector3 v2 )

Get max value for each pair of components

- Failure return false
- Success return Vector3
*/
int lmathVector3Max( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Max( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Max( v1, v2 ) );

	return 1;
}

/*
> result = RL_Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )

Compute barycenter coordinates ( u, v, w ) for point p with respect to triangle ( a, b, c )
NOTE: Assumes P is on the plane of the triangle

- Failure return false
- Success return Vector3
*/
int lmathVector3Barycenter( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 c = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 b = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 a = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Barycenter( p, a, b, c ) );

	return 1;
}

/*
> result = RL_Vector3Unproject( Vector3 source, Matrix projection, Matrix view )

Projects a Vector3 from screen space into object space
NOTE: We are avoiding calling other raymath functions despite available

- Failure return false
- Success return Vector3
*/
int lmathVector3Unproject( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_Vector3Unproject( Vector3 source, Matrix projection, Matrix view )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix view = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Matrix projection = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Vector3 source = uluaGetVector3( L );

	uluaPushVector3( L, Vector3Unproject( source, projection, view ) );

	return 1;
}

/*
## Math - Matrix
*/

/*
> result = RL_MatrixDeterminant( Matrix mat )

Compute matrix determinant

- Failure return false
- Success return float
*/
int lmathMatrixDeterminant( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixDeterminant( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	lua_pushnumber( L, MatrixDeterminant( mat ) );

	return 1;
}

/*
> result = RL_MatrixTrace( Matrix mat )

Get the trace of the matrix ( sum of the values along the diagonal )

- Failure return false
- Success return float
*/
int lmathMatrixTrace( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixTrace( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	lua_pushnumber( L, MatrixTrace( mat ) );

	return 1;
}

/*
> result = RL_MatrixTranspose( Matrix mat )

Transposes provided matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixTranspose( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixTranspose( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixTranspose( mat ) );

	return 1;
}

/*
> result = RL_MatrixInvert( Matrix mat )

Invert provided matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixInvert( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixInvert( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixInvert( mat ) );

	return 1;
}

/*
> result = MatrixIdentity()

Get identity matrix

- Success return Matrix
*/
int lmathMatrixIdentity( lua_State *L ) {
	uluaPushMatrix( L, MatrixIdentity() );

	return 1;
}

/*
> result = RL_MatrixAdd( Matrix left, Matrix right )

Add two matrices

- Failure return false
- Success return Matrix
*/
int lmathMatrixAdd( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixAdd( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat2 = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Matrix mat1 = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixAdd( mat1, mat2 ) );

	return 1;
}

/*
> result = RL_MatrixSubtract( Matrix left, Matrix right )

Subtract two matrices (left - right)

- Failure return false
- Success return Matrix
*/
int lmathMatrixSubtract( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixSubtract( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat2 = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Matrix mat1 = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixSubtract( mat1, mat2 ) );

	return 1;
}

/*
> result = RL_MatrixMultiply( Matrix left, Matrix right )

Get two matrix multiplication

- Failure return false
- Success return Matrix
*/
int lmathMatrixMultiply( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixMultiply( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat2 = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Matrix mat1 = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixMultiply( mat1, mat2 ) );

	return 1;
}

/*
> result = RL_MatrixTranslate( Vector3 translate )

Get translation matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixTranslate( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixTranslate( Vector3 translate )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixTranslate( v.x, v.y, v.z ) );

	return 1;
}

/*
> result = RL_MatrixRotate( Vector3 axis, float angle )

Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotate( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotate( Vector3 axis, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 axis = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixRotate( axis, angle ) );

	return 1;
}

/*
> result = RL_MatrixRotateX( float angle )

Get x-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateX( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotateX( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, -1 );

	uluaPushMatrix( L, MatrixRotateX( angle ) );

	return 1;
}

/*
> result = RL_MatrixRotateY( float angle )

Get y-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateY( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotateY( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, -1 );

	uluaPushMatrix( L, MatrixRotateY( angle ) );

	return 1;
}

/*
> result = RL_MatrixRotateZ( float angle )

Get z-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateZ( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotateZ( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, -1 );

	uluaPushMatrix( L, MatrixRotateZ( angle ) );

	return 1;
}

/*
> result = RL_MatrixRotateXYZ( Vector3 angle )

Get xyz-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateXYZ( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotateXYZ( Vector3 angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 angle = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixRotateXYZ( angle ) );

	return 1;
}

/*
> result = RL_MatrixRotateZYX( Vector3 angle )

Get zyx-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateZYX( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixRotateZYX( Vector3 angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 angle = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixRotateZYX( angle ) );

	return 1;
}

/*
> result = RL_MatrixScale( Vector3 scale )

Get scaling matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixScale( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixScale( Vector3 scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixScale( v.x, v.y, v.z ) );

	return 1;
}

/*
> result = RL_MatrixFrustum( double left, double right, double bottom, double top, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixFrustum( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixFrustum( double left, double right, double bottom, double top, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float far = lua_tonumber( L, -1 );
	float near = lua_tonumber( L, -2 );
	float top = lua_tonumber( L, -3 );
	float bottom = lua_tonumber( L, -4 );
	float right = lua_tonumber( L, -5 );
	float left = lua_tonumber( L, -6 );

	uluaPushMatrix( L, MatrixFrustum( left, right, bottom, top, near, far ) );

	return 1;
}

/*
> result = RL_MatrixPerspective( double fovy, double aspect, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixPerspective( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixPerspective( double fovy, double aspect, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float far = lua_tonumber( L, -1 );
	float near = lua_tonumber( L, -2 );
	float aspect = lua_tonumber( L, -3 );
	float fovy = lua_tonumber( L, -4 );

	uluaPushMatrix( L, MatrixPerspective( fovy, aspect, near, far ) );

	return 1;
}

/*
> result = RL_MatrixOrtho( double left, double right, double bottom, double top, double near, double far )

Get orthographic projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixOrtho( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixOrtho( double left, double right, double bottom, double top, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float far = lua_tonumber( L, -1 );
	float near = lua_tonumber( L, -2 );
	float top = lua_tonumber( L, -3 );
	float bottom = lua_tonumber( L, -4 );
	float right = lua_tonumber( L, -5 );
	float left = lua_tonumber( L, -6 );

	uluaPushMatrix( L, MatrixOrtho( left, right, bottom, top, near, far ) );

	return 1;
}

/*
> result = RL_MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )

Get camera look-at matrix ( View matrix )

- Failure return false
- Success return Matrix
*/
int lmathMatrixLookAt( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 up = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 target = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 eye = uluaGetVector3( L );

	uluaPushMatrix( L, MatrixLookAt( eye, target, up ) );

	return 1;
}

/*
## Math - Quaternion
*/

/*
> result = RL_QuaternionAdd( Quaternion q1, Quaternion q2 )

Add two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionAdd( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionAdd( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionAdd( q1, q2 ) );

	return 1;
}

/*
> result = RL_QuaternionAddValue( Quaternion q, float add )

Add quaternion and float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionAddValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionAddValue( Quaternion q, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float add = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionAddValue( q, add ) );

	return 1;
}

/*
> result = RL_QuaternionSubtract( Quaternion q1, Quaternion q2 )

Subtract two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSubtract( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionSubtract( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionSubtract( q1, q2 ) );

	return 1;
}

/*
> result = RL_QuaternionSubtractValue( Quaternion q, float sub )

Subtract quaternion and float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSubtractValue( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionSubtractValue( Quaternion q, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float sub = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionSubtractValue( q, sub ) );

	return 1;
}

/*
> result = RL_QuaternionIdentity()

Get identity quaternion

- Success return Quaternion
*/
int lmathQuaternionIdentity( lua_State *L ) {
	uluaPushQuaternion( L, QuaternionIdentity() );

	return 1;
}

/*
> result = RL_QuaternionLength( Quaternion q )

Computes the length of a quaternion

- Failure return false
- Success return float
*/
int lmathQuaternionLength( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionLength( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );

	lua_pushnumber( L, QuaternionLength( q ) );

	return 1;
}

/*
> result = RL_QuaternionNormalize( Quaternion q )

Normalize provided quaternion

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionNormalize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionNormalize( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionNormalize( q ) );

	return 1;
}

/*
> result = RL_QuaternionInvert( Quaternion q )

Invert provided quaternion

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionInvert( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionInvert( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionInvert( q ) );

	return 1;
}

/*
> result = RL_QuaternionMultiply( Quaternion q1, Quaternion q2 )

Calculate two quaternion multiplication

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionMultiply( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionMultiply( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionMultiply( q1, q2 ) );

	return 1;
}

/*
> result = RL_QuaternionScale( Quaternion q, float mul )

Scale quaternion by float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionScale( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionScale( Quaternion q, float mul )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float mul = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionScale( q, mul ) );

	return 1;
}

/*
> result = RL_QuaternionDivide( Quaternion q1, Quaternion q2 )

Divide two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionDivide( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionDivide( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionDivide( q1, q2 ) );

	return 1;
}

/*
> result = RL_QuaternionLerp( Quaternion q1, Quaternion q2, float amount )

Calculate linear interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionLerp( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionLerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionLerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL_QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )

Calculate slerp-optimized interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionNlerp( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionNlerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL_QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )

Calculates spherical linear interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSlerp( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float amount = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Quaternion q2 = uluaGetQuaternion( L );
	lua_pop( L, 1 );
	Quaternion q1 = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionSlerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL_QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )

Calculate quaternion based on the rotation from one vector to another

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromVector3ToVector3( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 to = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 from = uluaGetVector3( L );

	uluaPushQuaternion( L, QuaternionFromVector3ToVector3( from, to ) );

	return 1;
}

/*
> result = RL_QuaternionFromMatrix( Matrix mat )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromMatrix( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionFromMatrix( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	uluaPushQuaternion( L, QuaternionFromMatrix( mat ) );

	return 1;
}

/*
> result = RL_QuaternionToMatrix( Quaternion q )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Matrix
*/
int lmathQuaternionToMatrix( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionToMatrix( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );

	uluaPushMatrix( L, QuaternionToMatrix( q ) );

	return 1;
}

/*
> result = RL_QuaternionFromAxisAngle( Vector3 axis, float angle )

Get rotation quaternion for an angle and axis
NOTE: angle must be provided in radians

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromAxisAngle( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionFromAxisAngle( Vector3 axis, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 axis = uluaGetVector3( L );

	uluaPushQuaternion( L, QuaternionFromAxisAngle( axis, angle ) );

	return 1;
}

/*
> axis, angle = RL_QuaternionToAxisAngle( Quaternion q )

Get the rotation angle and axis for a given quaternion

- Failure return false
- Success return Vector3, float
*/
int lmathQuaternionToAxisAngle( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionToAxisAngle( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );
	float angle = 0.0;
	Vector3 axis = { 0.0 };

	QuaternionToAxisAngle( q, &axis, &angle );

	uluaPushVector3( L, axis );
	lua_pushnumber( L, angle );

	return 2;
}

/*
> result = RL_QuaternionFromEuler( float pitch, float yaw, float roll )

Get the quaternion equivalent to Euler angles
NOTE: Rotation order is ZYX

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromEuler( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionFromEuler( float pitch, float yaw, float roll )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float roll = lua_tonumber( L, -1 );
	float yaw = lua_tonumber( L, -2 );
	float pitch = lua_tonumber( L, -3 );

	uluaPushQuaternion( L, QuaternionFromEuler( pitch, yaw, roll ) );

	return 1;
}

/*
> result = RL_QuaternionToEuler( Quaternion q )

Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
NOTE: Angles are returned in a Vector3 struct in radians

- Failure return false
- Success return Vector3
*/
int lmathQuaternionToEuler( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionToEuler( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternion( L );

	uluaPushVector3( L, QuaternionToEuler( q ) );

	return 1;
}

/*
> result = RL_QuaternionTransform( Quaternion q, Matrix mat )

Transform a quaternion given a transformation matrix

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionTransform( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_QuaternionTransform( Quaternion q, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );
	lua_pop( L, 1 );
	Quaternion q = uluaGetQuaternion( L );

	uluaPushQuaternion( L, QuaternionTransform( q, mat ) );

	return 1;
}
