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
> result = RL.Clamp( float value, float min, float max )

Clamp float value

- Failure return false
- Success return float
*/
int lmathClamp( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Clamp( float value, float min, float max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, 1 );
	float min = lua_tonumber( L, 2 );
	float max = lua_tonumber( L, 3 );

	lua_pushnumber( L, Clamp( value, min, max ) );

	return 1;
}

/*
> result = RL.Lerp( float start, float end, float amount )

Calculate linear interpolation between two floats

- Failure return false
- Success return float
*/
int lmathLerp( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Lerp( float start, float end, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float start = lua_tonumber( L, 1 );
	float end = lua_tonumber( L, 2 );
	float amount = lua_tonumber( L, 3 );

	lua_pushnumber( L, Lerp( start, end, amount ) );

	return 1;
}

/*
> result = RL.Normalize( float value, float start, float end )

Normalize input value within input range

- Failure return false
- Success return float
*/
int lmathNormalize( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Normalize( float value, float start, float end )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, 1 );
	float start = lua_tonumber( L, 2 );
	float end = lua_tonumber( L, 3 );

	lua_pushnumber( L, Normalize( value, start, end ) );

	return 1;
}

/*
> result = RL.Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )

Remap input value within input range to output range

- Failure return false
- Success return float
*/
int lmathRemap( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, 1 );
	float inputStart = lua_tonumber( L, 2 );
	float inputEnd = lua_tonumber( L, 3 );
	float outputStart = lua_tonumber( L, 4 );
	float outputEnd = lua_tonumber( L, 5 );

	lua_pushnumber( L, Remap( value, inputStart, inputEnd, outputStart, outputEnd ) );

	return 1;
}

/*
> result = RL.Wrap( float value, float min, float max )

Wrap input value from min to max

- Failure return false
- Success return float
*/
int lmathWrap( lua_State *L ) {
	if ( !lua_isnumber( L, 1 )	|| !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Wrap( float value, float min, float max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, 1 );
	float min = lua_tonumber( L, 2 );
	float max = lua_tonumber( L, 3 );

	lua_pushnumber( L, Wrap( value, min, max ) );

	return 1;
}

/*
> result = RL.FloatEquals( float x, float y )

Check whether two given floats are almost equal

- Failure return false
- Success return int
*/
int lmathFloatEquals( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.FloatEquals( float x, float y )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float x = lua_tonumber( L, 1 );
	float y = lua_tonumber( L, 2 );

	lua_pushinteger( L, FloatEquals( x, y ) );

	return 1;
}

/*
## Math - Vector2
*/

/*
> result = RL.Vector2Zero()

Vector with components value 0.0f

- Success return Vector2
*/
int lmathVector2Zero( lua_State *L ) {
	uluaPushVector2( L, Vector2Zero() );

	return 1;
}

/*
> result = RL.Vector2One()

Vector with components value 1.0f

- Success return Vector2
*/
int lmathVector2One( lua_State *L ) {
	uluaPushVector2( L, Vector2One() );

	return 1;
}

/*
> result = RL.Vector2Add( Vector2 v1, Vector2 v2 )

Add two vectors (v1 + v2)

- Failure return false
- Success return Vector2
*/
int lmathVector2Add( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Add( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	uluaPushVector2( L, Vector2Add( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2AddValue( Vector2 v, float add )

Add vector and float value

- Failure return false
- Success return Vector2
*/
int lmathVector2AddValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2AddValue( Vector2 v, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	float add = lua_tonumber( L, 2 );

	uluaPushVector2( L, Vector2AddValue( v, add ) );

	return 1;
}

/*
> result = RL.Vector2Subtract( Vector2 v1, Vector2 v2 )

Subtract two vectors (v1 - v2)

- Failure return false
- Success return Vector2
*/
int lmathVector2Subtract( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Subtract( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	uluaPushVector2( L, Vector2Subtract( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2SubtractValue( Vector2 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector2
*/
int lmathVector2SubtractValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2SubtractValue( Vector2 v, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	float sub = lua_tonumber( L, 2 );

	uluaPushVector2( L, Vector2SubtractValue( v, sub ) );

	return 1;
}

/*
> result = RL.Vector2Length( vector2 v )

Calculate vector length

- Failure return false
- Success return float
*/
int lmathVector2Length( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Length( vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );

	lua_pushnumber( L, Vector2Length( v ) );

	return 1;
}

/*
> result = RL.Vector2LengthSqr( vector2 v )

Calculate vector square length

- Failure return false
- Success return float
*/
int lmathVector2LengthSqr( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2LengthSqr( vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );

	lua_pushnumber( L, Vector2LengthSqr( v ) );

	return 1;
}

/*
> result = RL.Vector2DotProduct( Vector2 v1, Vector2 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float
*/
int lmathVector2DotProduct( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2DotProduct( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	lua_pushnumber( L, Vector2DotProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2Distance( Vector2 v1, Vector2 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector2Distance( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Distance( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	lua_pushnumber( L, Vector2Distance( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2DistanceSqr( Vector2 v1, Vector2 v2 )

Calculate square distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector2DistanceSqr( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2DistanceSqr( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	lua_pushnumber( L, Vector2DistanceSqr( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2Angle( Vector2 v1, Vector2 v2 )

Calculate angle from two vectors

- Failure return false
- Success return float
*/
int lmathVector2Angle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Angle( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	lua_pushnumber( L, Vector2Angle( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2LineAngle( Vector2 start, Vector2 end )

Calculate angle defined by a two vectors line.
NOTE: Parameters need to be normalized.
Current implementation should be aligned with glm::angle.

- Failure return false
- Success return float
*/
int lmathVector2LineAngle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2LineAngle( Vector2 start, Vector2 end )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 start = uluaGetVector2Index( L, 1 );
	Vector2 end = uluaGetVector2Index( L, 2 );

	lua_pushnumber( L, Vector2LineAngle( start, end ) );

	return 1;
}

/*
> result = RL.Vector2Scale( Vector2 v, float scale )

Scale vector ( multiply by value )

- Failure return false
- Success return Vector2
*/
int lmathVector2Scale( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Scale( Vector2 v, float scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	float scale = lua_tonumber( L, 2 );

	uluaPushVector2( L, Vector2Scale( v, scale ) );

	return 1;
}

/*
> result = RL.Vector2Multiply( Vector2 v1, Vector2 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Multiply( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Multiply( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	uluaPushVector2( L, Vector2Multiply( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2Negate( Vector2 v )

Negate vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Negate( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Negate( Vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );

	uluaPushVector2( L, Vector2Negate( v ) );

	return 1;
}

/*
> result = RL.Vector2Divide( Vector2 v1, Vector2 v2 )

Divide vector by vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Divide( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Divide( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	uluaPushVector2( L, Vector2Divide( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2Normalize( Vector2 v )

Normalize provided vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Normalize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Normalize( Vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );

	uluaPushVector2( L, Vector2Normalize( v ) );

	return 1;
}

/*
> result = RL.Vector2Transform( Vector2 v, Matrix mat )

Transforms a Vector2 by a given Matrix

- Failure return false
- Success return Vector2
*/
int lmathVector2Transform( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Transform( Vector2 v, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	Matrix mat = uluaGetMatrixIndex( L, 2 );

	uluaPushVector2( L, Vector2Transform( v, mat ) );

	return 1;
}

/*
> result = RL.Vector2Lerp( Vector2 v1, Vector2 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector2
*/
int lmathVector2Lerp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Lerp( Vector2 v1, Vector2 v2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );
	float amount = lua_tonumber( L, 3 );

	uluaPushVector2( L, Vector2Lerp( v1, v2, amount ) );

	return 1;
}

/*
> result = RL.Vector2Reflect( Vector2 v, Vector2 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector2
*/
int lmathVector2Reflect( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Reflect( Vector2 v, Vector2 normal )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	uluaPushVector2( L, Vector2Reflect( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector2Rotate( Vector2 v, float angle )

Rotate vector by angle

- Failure return false
- Success return Vector2
*/
int lmathVector2Rotate( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Rotate( Vector2 v, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	float degs = lua_tonumber( L, 2 );

	uluaPushVector2( L, Vector2Rotate( v, degs ) );

	return 1;
}

/*
> result = RL.Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )

Move Vector towards target

- Failure return false
- Success return Vector2
*/
int lmathVector2MoveTowards( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );
	float maxDistance = lua_tonumber( L, 3 );

	uluaPushVector2( L, Vector2MoveTowards( v1, v2, maxDistance ) );

	return 1;
}

/*
> result = RL.Vector2Invert( Vector2 v )

Invert the given vector

- Failure return false
- Success return Vector2
*/
int lmathVector2Invert( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Invert( Vector2 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );

	uluaPushVector2( L, Vector2Invert( v ) );

	return 1;
}

/*
> result = RL.Vector2Clamp( Vector2 v, Vector2 min, Vector2 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Failure return false
- Success return Vector2
*/
int lmathVector2Clamp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Clamp( Vector2 v, Vector2 min, Vector2 max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	Vector2 min = uluaGetVector2Index( L, 2 );
	Vector2 max = uluaGetVector2Index( L, 3 );

	uluaPushVector2( L, Vector2Clamp( v, min, max ) );

	return 1;
}

/*
> result = RL.Vector2ClampValue( Vector2 v, float min, float max )

Clamp the magnitude of the vector between two min and max values

- Failure return false
- Success return Vector2
*/
int lmathVector2ClampValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2ClampValue( Vector2 v, float min, float max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v = uluaGetVector2Index( L, 1 );
	float min = lua_tonumber( L, 2 );
	float max = lua_tonumber( L, 3 );

	uluaPushVector2( L, Vector2ClampValue( v, min, max ) );

	return 1;
}

/*
> result = RL.Vector2Equals( Vector2 v1, Vector2 v2 )

Check whether two given vectors are almost equal

- Failure return false
- Success return int
*/
int lmathVector2Equals( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector2Equals( Vector2 v1, Vector2 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );

	lua_pushinteger( L, Vector2Equals( v1, v2 ) );

	return 1;
}

/*
## Math - Vector 3
*/

/*
> result = RL.Vector3Zero()

Vector with components value 0.0f

- Success return Vector3
*/
int lmathVector3Zero( lua_State *L ) {
	uluaPushVector3( L, Vector3Zero() );

	return 1;
}

/*
> result = RL.Vector3One()

Vector with components value 1.0f

- Success return Vector3
*/
int lmathVector3One( lua_State *L ) {
	uluaPushVector3( L, Vector3One() );

	return 1;
}

/*
> result = RL.Vector3Add( Vector3 v1, Vector3 v2 )

Add two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Add( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Add( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Add( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3AddValue( Vector3 v, float add )

Add vector and float value

- Failure return false
- Success return Vector3
*/
int lmathVector3AddValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3AddValue( Vector3 v, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	float add = lua_tonumber( L, 2 );

	uluaPushVector3( L, Vector3AddValue( v, add ) );

	return 1;
}

/*
> result = RL.Vector3Subtract( Vector3 v1, Vector3 v2 )

Subtract two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Subtract( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Subtract( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Subtract( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3SubtractValue( Vector3 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector3
*/
int lmathVector3SubtractValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3SubtractValue( Vector3 v, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	float sub = lua_tonumber( L, 2 );

	uluaPushVector3( L, Vector3SubtractValue( v, sub ) );

	return 1;
}

/*
> result = RL.Vector3Scale( Vector3 v, float scalar )

Multiply vector by scalar

- Failure return false
- Success return Vector3
*/
int lmathVector3Scale( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Scale( Vector3 v, float scalar )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	float scalar = lua_tonumber( L, 2 );

	uluaPushVector3( L, Vector3Scale( v, scalar ) );

	return 1;
}

/*
> result = RL.Vector3Multiply( Vector3 v1, Vector3 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Multiply( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Multiply( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Multiply( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3CrossProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors cross product

- Failure return false
- Success return Vector3
*/
int lmathVector3CrossProduct( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3CrossProduct( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3CrossProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Perpendicular( Vector3 v )

Calculate one vector perpendicular vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Perpendicular( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Perpendicular( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushVector3( L, Vector3Perpendicular( v ) );

	return 1;
}

/*
> result = RL.Vector3Length( Vector3 v )

Calculate vector length

- Failure return false
- Success return float
*/
int lmathVector3Length( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Length( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	lua_pushnumber( L, Vector3Length( v ) );

	return 1;
}

/*
> result = RL.Vector3LengthSqr( Vector3 v )

Calculate vector square length

- Failure return false
- Success return float
*/
int lmathVector3LengthSqr( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3LengthSqr( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	lua_pushnumber( L, Vector3LengthSqr( v ) );

	return 1;
}

/*
> result = RL.Vector3DotProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float
*/
int lmathVector3DotProduct( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3DotProduct( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	lua_pushnumber( L, Vector3DotProduct( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Distance( Vector3 v1, Vector3 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector3Distance( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Distance( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	lua_pushnumber( L, Vector3Distance( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3DistanceSqr( Vector3 v1, Vector3 v2 )

Calculate square distance between two vectors

- Failure return false
- Success return float
*/
int lmathVector3DistanceSqr( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3DistanceSqr( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	lua_pushnumber( L, Vector3DistanceSqr( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Angle( Vector3 v1, Vector3 v2 )

Calculate angle between two vectors

- Failure return false
- Success return float
*/
int lmathVector3Angle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Angle( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	lua_pushnumber( L, Vector3Angle( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Negate( Vector3 v )

Negate provided vector ( invert direction )

- Failure return false
- Success return Vector3
*/
int lmathVector3Negate( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Negate( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushVector3( L, Vector3Negate( v ) );

	return 1;
}

/*
> result = RL.Vector3Divide( Vector3 v1, Vector3 v2 )

Divide vector by vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Divide( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Divide( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Divide( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Normalize( Vector3 v )

Normalize provided vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Normalize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Normalize( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushVector3( L, Vector3Normalize( v ) );

	return 1;
}

/*
> v1, v2 = RL.Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )

Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
Gram-Schmidt function implementation

- Failure return false
- Success return Vector3, Vector3
*/
int lmathVector3OrthoNormalize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	Vector3OrthoNormalize( &v1, &v2 );

	uluaPushVector3( L, v1 );
	uluaPushVector3( L, v2 );

	return 2;
}

/*
> result = RL.Vector3Transform( Vector3 v, Matrix mat )

Transforms a Vector3 by a given Matrix

- Failure return false
- Success return Vector3
*/
int lmathVector3Transform( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Transform( Vector3 v, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Matrix mat = uluaGetMatrixIndex( L, 2 );

	uluaPushVector3( L, Vector3Transform( v, mat ) );

	return 1;
}

/*
> result = RL.Vector3RotateByQuaternion( Vector3 v, Quaternion q )

Transform a vector by quaternion rotation

- Failure return false
- Success return Vector3
*/
int lmathVector3RotateByQuaternion( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3RotateByQuaternion( Vector3 v, Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Quaternion q = uluaGetQuaternionIndex( L, 2 );

	uluaPushVector3( L, Vector3RotateByQuaternion( v, q ) );

	return 1;
}

/*
> result = RL.Vector3RotateByAxisAngle( Vector3 v, Vector3 axis, float angle )

Rotates a vector around an axis

- Failure return false
- Success return Vector3
*/
int lmathVector3RotateByAxisAngle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3RotateByAxisAngle( Vector3 v, Vector3 axis, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Vector3 axis = uluaGetVector3Index( L, 2 );
	float angle = lua_tonumber( L, 3 );

	uluaPushVector3( L, Vector3RotateByAxisAngle( v, axis, angle ) );

	return 1;
}

/*
> result = RL.Vector3Lerp( Vector3 v1, Vector3 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Lerp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Lerp( Vector3 v1, Vector3 v2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );
	float amount = lua_tonumber( L, 3 );

	uluaPushVector3( L, Vector3Lerp( v1, v2, amount ) );

	return 1;
}

/*
> result = RL.Vector3Reflect( Vector3 v, Vector3 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector3
*/
int lmathVector3Reflect( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Reflect( Vector3 v, Vector3 normal )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Vector3 normal = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Reflect( v, normal ) );

	return 1;
}

/*
> result = RL.Vector3Min( Vector3 v1, Vector3 v2 )

Get min value for each pair of components

- Failure return false
- Success return Vector3
*/
int lmathVector3Min( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Min( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Min( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Max( Vector3 v1, Vector3 v2 )

Get max value for each pair of components

- Failure return false
- Success return Vector3
*/
int lmathVector3Max( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Max( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	uluaPushVector3( L, Vector3Max( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )

Compute barycenter coordinates ( u, v, w ) for point p with respect to triangle ( a, b, c )
NOTE: Assumes P is on the plane of the triangle

- Failure return false
- Success return Vector3
*/
int lmathVector3Barycenter( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 p = uluaGetVector3Index( L, 1 );
	Vector3 a = uluaGetVector3Index( L, 2 );
	Vector3 b = uluaGetVector3Index( L, 3 );
	Vector3 c = uluaGetVector3Index( L, 4 );

	uluaPushVector3( L, Vector3Barycenter( p, a, b, c ) );

	return 1;
}

/*
> result = RL.Vector3Unproject( Vector3 source, Matrix projection, Matrix view )

Projects a Vector3 from screen space into object space
NOTE: We are avoiding calling other raymath functions despite available

- Failure return false
- Success return Vector3
*/
int lmathVector3Unproject( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Unproject( Vector3 source, Matrix projection, Matrix view )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 source = uluaGetVector3Index( L, 1 );
	Matrix projection = uluaGetMatrixIndex( L, 2 );
	Matrix view = uluaGetMatrixIndex( L, 3 );

	uluaPushVector3( L, Vector3Unproject( source, projection, view ) );

	return 1;
}

/*
> result = RL.Vector3Invert( Vector3 v )

Invert the given vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Invert( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Invert( Vector3 v )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushVector3( L, Vector3Invert( v ) );

	return 1;
}

/*
> result = RL.Vector3Clamp( Vector3 v, Vector3 min, Vector3 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Failure return false
- Success return Vector3
*/
int lmathVector3Clamp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Clamp( Vector3 v, Vector3 min, Vector3 max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Vector3 min = uluaGetVector3Index( L, 2 );
	Vector3 max = uluaGetVector3Index( L, 3 );

	uluaPushVector3( L, Vector3Clamp( v, min, max ) );

	return 1;
}

/*
> result = RL.Vector3ClampValue( Vector3 v, float min, float max )

Clamp the magnitude of the vector between two values

- Failure return false
- Success return Vector3
*/
int lmathVector3ClampValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3ClampValue( Vector3 v, float min, float max )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	float min = lua_tonumber( L, 2 );
	float max = lua_tonumber( L, 3 );

	uluaPushVector3( L, Vector3ClampValue( v, min, max ) );

	return 1;
}

/*
> result = RL.Vector3Equals( Vector3 v1, Vector3 v2 )

Check whether two given vectors are almost equal

- Failure return false
- Success return int
*/
int lmathVector3Equals( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Equals( Vector3 v1, Vector3 v2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v1 = uluaGetVector3Index( L, 1 );
	Vector3 v2 = uluaGetVector3Index( L, 2 );

	lua_pushinteger( L, Vector3Equals( v1, v2 ) );

	return 1;
}

/*
> result = RL.Vector3Refract( Vector3 v, Vector3 n, float r )

Compute the direction of a refracted ray where v specifies the
normalized direction of the incoming ray, n specifies the
normalized normal vector of the interface of two optical media,
and r specifies the ratio of the refractive index of the medium
from where the ray comes to the refractive index of the medium
on the other side of the surface

- Failure return false
- Success return Vector3
*/
int lmathVector3Refract( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Vector3Refract( Vector3 v, Vector3 n, float r )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );
	Vector3 n = uluaGetVector3Index( L, 2 );
	float r = lua_tonumber( L, 3 );

	uluaPushVector3( L, Vector3Refract( v, n, r ) );

	return 1;
}

/*
## Math - Matrix
*/

/*
> result = RL.MatrixDeterminant( Matrix mat )

Compute matrix determinant

- Failure return false
- Success return float
*/
int lmathMatrixDeterminant( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixDeterminant( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrixIndex( L, 1 );

	lua_pushnumber( L, MatrixDeterminant( mat ) );

	return 1;
}

/*
> result = RL.MatrixTrace( Matrix mat )

Get the trace of the matrix ( sum of the values along the diagonal )

- Failure return false
- Success return float
*/
int lmathMatrixTrace( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixTrace( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrixIndex( L, 1 );

	lua_pushnumber( L, MatrixTrace( mat ) );

	return 1;
}

/*
> result = RL.MatrixTranspose( Matrix mat )

Transposes provided matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixTranspose( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixTranspose( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrixIndex( L, 1 );

	uluaPushMatrix( L, MatrixTranspose( mat ) );

	return 1;
}

/*
> result = RL.MatrixInvert( Matrix mat )

Invert provided matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixInvert( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixInvert( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrixIndex( L, 1 );

	uluaPushMatrix( L, MatrixInvert( mat ) );

	return 1;
}

/*
> result = RL.MatrixIdentity()

Get identity matrix

- Success return Matrix
*/
int lmathMatrixIdentity( lua_State *L ) {
	uluaPushMatrix( L, MatrixIdentity() );

	return 1;
}

/*
> result = RL.MatrixAdd( Matrix left, Matrix right )

Add two matrices

- Failure return false
- Success return Matrix
*/
int lmathMatrixAdd( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixAdd( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat1 = uluaGetMatrixIndex( L, 1 );
	Matrix mat2 = uluaGetMatrixIndex( L, 2 );

	uluaPushMatrix( L, MatrixAdd( mat1, mat2 ) );

	return 1;
}

/*
> result = RL.MatrixSubtract( Matrix left, Matrix right )

Subtract two matrices (left - right)

- Failure return false
- Success return Matrix
*/
int lmathMatrixSubtract( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixSubtract( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat1 = uluaGetMatrixIndex( L, 1 );
	Matrix mat2 = uluaGetMatrixIndex( L, 2 );

	uluaPushMatrix( L, MatrixSubtract( mat1, mat2 ) );

	return 1;
}

/*
> result = RL.MatrixMultiply( Matrix left, Matrix right )

Get two matrix multiplication

- Failure return false
- Success return Matrix
*/
int lmathMatrixMultiply( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixMultiply( Matrix left, Matrix right )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat1 = uluaGetMatrixIndex( L, 1 );
	Matrix mat2 = uluaGetMatrixIndex( L, 2 );

	uluaPushMatrix( L, MatrixMultiply( mat1, mat2 ) );

	return 1;
}

/*
> result = RL.MatrixTranslate( Vector3 translate )

Get translation matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixTranslate( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixTranslate( Vector3 translate )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushMatrix( L, MatrixTranslate( v.x, v.y, v.z ) );

	return 1;
}

/*
> result = RL.MatrixRotate( Vector3 axis, float angle )

Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotate( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotate( Vector3 axis, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 axis = uluaGetVector3Index( L, 1 );
	float angle = lua_tonumber( L, 2 );

	uluaPushMatrix( L, MatrixRotate( axis, angle ) );

	return 1;
}

/*
> result = RL.MatrixRotateX( float angle )

Get x-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateX( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotateX( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, 1 );

	uluaPushMatrix( L, MatrixRotateX( angle ) );

	return 1;
}

/*
> result = RL.MatrixRotateY( float angle )

Get y-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateY( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotateY( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, 1 );

	uluaPushMatrix( L, MatrixRotateY( angle ) );

	return 1;
}

/*
> result = RL.MatrixRotateZ( float angle )

Get z-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateZ( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotateZ( float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float angle = lua_tonumber( L, 1 );

	uluaPushMatrix( L, MatrixRotateZ( angle ) );

	return 1;
}

/*
> result = RL.MatrixRotateXYZ( Vector3 angle )

Get xyz-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateXYZ( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotateXYZ( Vector3 angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 angle = uluaGetVector3Index( L, 1 );

	uluaPushMatrix( L, MatrixRotateXYZ( angle ) );

	return 1;
}

/*
> result = RL.MatrixRotateZYX( Vector3 angle )

Get zyx-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix
*/
int lmathMatrixRotateZYX( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixRotateZYX( Vector3 angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 angle = uluaGetVector3Index( L, 1 );

	uluaPushMatrix( L, MatrixRotateZYX( angle ) );

	return 1;
}

/*
> result = RL.MatrixScale( Vector3 scale )

Get scaling matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixScale( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixScale( Vector3 scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 v = uluaGetVector3Index( L, 1 );

	uluaPushMatrix( L, MatrixScale( v.x, v.y, v.z ) );

	return 1;
}

/*
> result = RL.MatrixFrustum( double left, double right, double bottom, double top, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixFrustum( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixFrustum( double left, double right, double bottom, double top, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float left = lua_tonumber( L, 1 );
	float right = lua_tonumber( L, 2);
	float bottom = lua_tonumber( L, 3 );
	float top = lua_tonumber( L, 4 );
	float near = lua_tonumber( L, 5 );
	float far = lua_tonumber( L, 6 );

	uluaPushMatrix( L, MatrixFrustum( left, right, bottom, top, near, far ) );

	return 1;
}

/*
> result = RL.MatrixPerspective( double fovy, double aspect, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixPerspective( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixPerspective( double fovy, double aspect, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float fovy = lua_tonumber( L, 1 );
	float aspect = lua_tonumber( L, 2 );
	float near = lua_tonumber( L, 3 );
	float far = lua_tonumber( L, 4 );

	uluaPushMatrix( L, MatrixPerspective( fovy, aspect, near, far ) );

	return 1;
}

/*
> result = RL.MatrixOrtho( double left, double right, double bottom, double top, double near, double far )

Get orthographic projection matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixOrtho( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixOrtho( double left, double right, double bottom, double top, double near, double far )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float left = lua_tonumber( L, 1 );
	float right = lua_tonumber( L, 2 );
	float bottom = lua_tonumber( L, 3 );
	float top = lua_tonumber( L, 4 );
	float near = lua_tonumber( L, 5 );
	float far = lua_tonumber( L, 6 );

	uluaPushMatrix( L, MatrixOrtho( left, right, bottom, top, near, far ) );

	return 1;
}

/*
> result = RL.MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )

Get camera look-at matrix ( View matrix )

- Failure return false
- Success return Matrix
*/
int lmathMatrixLookAt( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 eye = uluaGetVector3Index( L, 1 );
	Vector3 target = uluaGetVector3Index( L, 2 );
	Vector3 up = uluaGetVector3Index( L, 3 );

	uluaPushMatrix( L, MatrixLookAt( eye, target, up ) );

	return 1;
}

/*
## Math - Quaternion
*/

/*
> result = RL.QuaternionAdd( Quaternion q1, Quaternion q2 )

Add two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionAdd( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionAdd( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );

	uluaPushQuaternion( L, QuaternionAdd( q1, q2 ) );

	return 1;
}

/*
> result = RL.QuaternionAddValue( Quaternion q, float add )

Add quaternion and float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionAddValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionAddValue( Quaternion q, float add )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );
	float add = lua_tonumber( L, 2 );

	uluaPushQuaternion( L, QuaternionAddValue( q, add ) );

	return 1;
}

/*
> result = RL.QuaternionSubtract( Quaternion q1, Quaternion q2 )

Subtract two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSubtract( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionSubtract( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );

	uluaPushQuaternion( L, QuaternionSubtract( q1, q2 ) );

	return 1;
}

/*
> result = RL.QuaternionSubtractValue( Quaternion q, float sub )

Subtract quaternion and float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSubtractValue( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionSubtractValue( Quaternion q, float sub )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );
	float sub = lua_tonumber( L, 2 );

	uluaPushQuaternion( L, QuaternionSubtractValue( q, sub ) );

	return 1;
}

/*
> result = RL.QuaternionIdentity()

Get identity quaternion

- Success return Quaternion
*/
int lmathQuaternionIdentity( lua_State *L ) {
	uluaPushQuaternion( L, QuaternionIdentity() );

	return 1;
}

/*
> result = RL.QuaternionLength( Quaternion q )

Computes the length of a quaternion

- Failure return false
- Success return float
*/
int lmathQuaternionLength( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionLength( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );

	lua_pushnumber( L, QuaternionLength( q ) );

	return 1;
}

/*
> result = RL.QuaternionNormalize( Quaternion q )

Normalize provided quaternion

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionNormalize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionNormalize( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );

	uluaPushQuaternion( L, QuaternionNormalize( q ) );

	return 1;
}

/*
> result = RL.QuaternionInvert( Quaternion q )

Invert provided quaternion

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionInvert( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionInvert( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );

	uluaPushQuaternion( L, QuaternionInvert( q ) );

	return 1;
}

/*
> result = RL.QuaternionMultiply( Quaternion q1, Quaternion q2 )

Calculate two quaternion multiplication

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionMultiply( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionMultiply( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );

	uluaPushQuaternion( L, QuaternionMultiply( q1, q2 ) );

	return 1;
}

/*
> result = RL.QuaternionScale( Quaternion q, float mul )

Scale quaternion by float value

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionScale( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionScale( Quaternion q, float mul )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );
	float mul = lua_tonumber( L, 2 );

	uluaPushQuaternion( L, QuaternionScale( q, mul ) );

	return 1;
}

/*
> result = RL.QuaternionDivide( Quaternion q1, Quaternion q2 )

Divide two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionDivide( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionDivide( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );

	uluaPushQuaternion( L, QuaternionDivide( q1, q2 ) );

	return 1;
}

/*
> result = RL.QuaternionLerp( Quaternion q1, Quaternion q2, float amount )

Calculate linear interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionLerp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionLerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );
	float amount = lua_tonumber( L, 3 );

	uluaPushQuaternion( L, QuaternionLerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL.QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )

Calculate slerp-optimized interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionNlerp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );
	float amount = lua_tonumber( L, 3 );

	uluaPushQuaternion( L, QuaternionNlerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL.QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )

Calculates spherical linear interpolation between two quaternions

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionSlerp( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );
	float amount = lua_tonumber( L, 3 );

	uluaPushQuaternion( L, QuaternionSlerp( q1, q2, amount ) );

	return 1;
}

/*
> result = RL.QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )

Calculate quaternion based on the rotation from one vector to another

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromVector3ToVector3( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 from = uluaGetVector3Index( L, 1 );
	Vector3 to = uluaGetVector3Index( L, 2 );

	uluaPushQuaternion( L, QuaternionFromVector3ToVector3( from, to ) );

	return 1;
}

/*
> result = RL.QuaternionFromMatrix( Matrix mat )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromMatrix( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionFromMatrix( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrixIndex( L, 1 );

	uluaPushQuaternion( L, QuaternionFromMatrix( mat ) );

	return 1;
}

/*
> result = RL.QuaternionToMatrix( Quaternion q )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Matrix
*/
int lmathQuaternionToMatrix( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionToMatrix( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );

	uluaPushMatrix( L, QuaternionToMatrix( q ) );

	return 1;
}

/*
> result = RL.QuaternionFromAxisAngle( Vector3 axis, float angle )

Get rotation quaternion for an angle and axis
NOTE: angle must be provided in radians

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromAxisAngle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionFromAxisAngle( Vector3 axis, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 axis = uluaGetVector3Index( L, 1 );
	float angle = lua_tonumber( L, 2 );

	uluaPushQuaternion( L, QuaternionFromAxisAngle( axis, angle ) );

	return 1;
}

/*
> axis, angle = RL.QuaternionToAxisAngle( Quaternion q )

Get the rotation angle and axis for a given quaternion

- Failure return false
- Success return Vector3, float
*/
int lmathQuaternionToAxisAngle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionToAxisAngle( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );
	float angle = 0.0;
	Vector3 axis = { 0.0 };

	QuaternionToAxisAngle( q, &axis, &angle );

	uluaPushVector3( L, axis );
	lua_pushnumber( L, angle );

	return 2;
}

/*
> result = RL.QuaternionFromEuler( float pitch, float yaw, float roll )

Get the quaternion equivalent to Euler angles
NOTE: Rotation order is ZYX

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionFromEuler( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionFromEuler( float pitch, float yaw, float roll )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float pitch = lua_tonumber( L, 1 );
	float yaw = lua_tonumber( L, 2 );
	float roll = lua_tonumber( L, 3 );

	uluaPushQuaternion( L, QuaternionFromEuler( pitch, yaw, roll ) );

	return 1;
}

/*
> result = RL.QuaternionToEuler( Quaternion q )

Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
NOTE: Angles are returned in a Vector3 struct in radians

- Failure return false
- Success return Vector3
*/
int lmathQuaternionToEuler( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionToEuler( Quaternion q )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );

	uluaPushVector3( L, QuaternionToEuler( q ) );

	return 1;
}

/*
> result = RL.QuaternionTransform( Quaternion q, Matrix mat )

Transform a quaternion given a transformation matrix

- Failure return false
- Success return Quaternion
*/
int lmathQuaternionTransform( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionTransform( Quaternion q, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q = uluaGetQuaternionIndex( L, 1 );
	Matrix mat = uluaGetMatrixIndex( L, 2 );

	uluaPushQuaternion( L, QuaternionTransform( q, mat ) );

	return 1;
}

/*
> result = RL.QuaternionEquals( Quaternion q1, Quaternion q2 )

Check whether two given quaternions are almost equal

- Failure return false
- Success return int
*/
int lmathQuaternionEquals( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.QuaternionEquals( Quaternion q1, Quaternion q2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Quaternion q1 = uluaGetQuaternionIndex( L, 1 );
	Quaternion q2 = uluaGetQuaternionIndex( L, 2 );

	lua_pushinteger( L, QuaternionEquals( q1, q2 ) );

	return 1;
}
