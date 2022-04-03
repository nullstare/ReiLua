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
## Math - Vector2
*/

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
> result = RL_Vector2Length( vector2 vector )

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
	Vector2 v = Vector2Normalize( uluaGetVector2( L ) );

	uluaPushVector2( L, v );

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
> result = RL_Vector3CrossProduct( Vector3 v1, Vector3 v2 )

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
> result = RL_Vector3Normalize( Vector3 v )

Normalize provided vector

- Failure return false
- Success return Vector3
*/
int lmathVector3Normalize( lua_State *L ) {
	/* Vector. */
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
> result = RL_MatrixNormalize( Matrix mat )

Normalize provided matrix

- Failure return false
- Success return Matrix
*/
int lmathMatrixNormalize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_MatrixNormalize( Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );

	uluaPushMatrix( L, MatrixNormalize( mat ) );

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
