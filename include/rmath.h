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
/* Quaternion. */
int lmathQuaternionAdd( lua_State *L );
int lmathQuaternionAddValue( lua_State *L );
int lmathQuaternionSubtract( lua_State *L );
int lmathQuaternionSubtractValue( lua_State *L );
int lmathQuaternionIdentity( lua_State *L );
int lmathQuaternionLength( lua_State *L );
int lmathQuaternionNormalize( lua_State *L );
int lmathQuaternionInvert( lua_State *L );
int lmathQuaternionMultiply( lua_State *L );
int lmathQuaternionScale( lua_State *L );
int lmathQuaternionDivide( lua_State *L );
int lmathQuaternionLerp( lua_State *L );
int lmathQuaternionNlerp( lua_State *L );
int lmathQuaternionSlerp( lua_State *L );
int lmathQuaternionFromVector3ToVector3( lua_State *L );
int lmathQuaternionFromMatrix( lua_State *L );
int lmathQuaternionToMatrix( lua_State *L );
int lmathQuaternionFromAxisAngle( lua_State *L );
int lmathQuaternionToAxisAngle( lua_State *L );
int lmathQuaternionFromEuler( lua_State *L );
int lmathQuaternionToEuler( lua_State *L );
int lmathQuaternionTransform( lua_State *L );
