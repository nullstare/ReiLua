#pragma once

int imin( int a, int b );
int imax( int a, int b );

/* Vector2. */
int lmathVector2Add( lua_State *L );
int lmathVector2Subtract( lua_State *L );
int lmathVector2Multiply( lua_State *L );
int lmathVector2Length( lua_State *L );
int lmathVector2DotProduct( lua_State *L );
int lmathVector2Distance( lua_State *L );
int lmathVector2Angle( lua_State *L );
int lmathVector2Normalize( lua_State *L );
int lmathVector2Lerp( lua_State *L );
int lmathVector2Reflect( lua_State *L );
int lmathVector2Rotate( lua_State *L );
int lmathVector2MoveTowards( lua_State *L );
/* Vector3. */
int lmathVector3Add( lua_State *L );
int lmathVector3Subtract( lua_State *L );
int lmathVector3Multiply( lua_State *L );
int lmathVector3CrossProduct( lua_State *L );
int lmathVector3Perpendicular( lua_State *L );
int lmathVector3Length( lua_State *L );
int lmathVector3LengthSqr( lua_State *L );
int lmathVector3DotProduct( lua_State *L );
int lmathVector3Distance( lua_State *L );
int lmathVector3Normalize( lua_State *L );
int lmathVector3OrthoNormalize( lua_State *L );
int lmathVector3Transform( lua_State *L );
int lmathVector3RotateByQuaternion( lua_State *L );
int lmathVector3Lerp( lua_State *L );
int lmathVector3Reflect( lua_State *L );
/* Matrix. */
int lmathMatrixDeterminant( lua_State *L );
int lmathMatrixTranspose( lua_State *L );
int lmathMatrixInvert( lua_State *L );
int lmathMatrixNormalize( lua_State *L );
int lmathMatrixIdentity( lua_State *L );
int lmathMatrixAdd( lua_State *L );
int lmathMatrixSubtract( lua_State *L );
int lmathMatrixMultiply( lua_State *L );
int lmathMatrixTranslate( lua_State *L );
int lmathMatrixRotate( lua_State *L );
int lmathMatrixScale( lua_State *L );
int lmathMatrixFrustum( lua_State *L );
int lmathMatrixPerspective( lua_State *L );
int lmathMatrixOrtho( lua_State *L );
int lmathMatrixLookAt( lua_State *L );
