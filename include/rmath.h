#pragma once

int imin( int a, int b );
int imax( int a, int b );

/* Utils. */
int lmathClamp( lua_State *L );
int lmathLerp( lua_State *L );
int lmathNormalize( lua_State *L );
int lmathRemap( lua_State *L );
int lmathWrap( lua_State *L );
int lmathFloatEquals( lua_State *L );
/* Vector2. */
int lmathVector2Zero( lua_State *L );
int lmathVector2One( lua_State *L );
int lmathVector2Add( lua_State *L );
int lmathVector2AddValue( lua_State *L );
int lmathVector2Subtract( lua_State *L );
int lmathVector2SubtractValue( lua_State *L );
int lmathVector2Length( lua_State *L );
int lmathVector2LengthSqr( lua_State *L );
int lmathVector2DotProduct( lua_State *L );
int lmathVector2Distance( lua_State *L );
int lmathVector2DistanceSqr( lua_State *L );
int lmathVector2Angle( lua_State *L );
int lmathVector2Scale( lua_State *L );
int lmathVector2Multiply( lua_State *L );
int lmathVector2Negate( lua_State *L );
int lmathVector2Divide( lua_State *L );
int lmathVector2Normalize( lua_State *L );
int lmathVector2Transform( lua_State *L );
int lmathVector2Lerp( lua_State *L );
int lmathVector2Reflect( lua_State *L );
int lmathVector2Rotate( lua_State *L );
int lmathVector2MoveTowards( lua_State *L );
int lmathVector2Invert( lua_State *L );
int lmathVector2Clamp( lua_State *L );
int lmathVector2ClampValue( lua_State *L );
int lmathVector2Equals( lua_State *L );
/* Vector3. */
int lmathVector3Zero( lua_State *L );
int lmathVector3One( lua_State *L );
int lmathVector3Add( lua_State *L );
int lmathVector3AddValue( lua_State *L );
int lmathVector3Subtract( lua_State *L );
int lmathVector3SubtractValue( lua_State *L );
int lmathVector3Scale( lua_State *L );
int lmathVector3Multiply( lua_State *L );
int lmathVector3CrossProduct( lua_State *L );
int lmathVector3Perpendicular( lua_State *L );
int lmathVector3Length( lua_State *L );
int lmathVector3LengthSqr( lua_State *L );
int lmathVector3DotProduct( lua_State *L );
int lmathVector3Distance( lua_State *L );
int lmathVector3DistanceSqr( lua_State *L );
int lmathVector3Angle( lua_State *L );
int lmathVector3Negate( lua_State *L );
int lmathVector3Divide( lua_State *L );
int lmathVector3Normalize( lua_State *L );
int lmathVector3OrthoNormalize( lua_State *L );
int lmathVector3Transform( lua_State *L );
int lmathVector3RotateByQuaternion( lua_State *L );
int lmathVector3Lerp( lua_State *L );
int lmathVector3Reflect( lua_State *L );
int lmathVector3Min( lua_State *L );
int lmathVector3Max( lua_State *L );
int lmathVector3Barycenter( lua_State *L );
int lmathVector3Unproject( lua_State *L );
int lmathVector3Invert( lua_State *L );
int lmathVector3Clamp( lua_State *L );
int lmathVector3ClampValue( lua_State *L );
int lmathVector3Equals( lua_State *L );
int lmathVector3Refract( lua_State *L );
/* Matrix. */
int lmathMatrixDeterminant( lua_State *L );
int lmathMatrixTrace( lua_State *L );
int lmathMatrixTranspose( lua_State *L );
int lmathMatrixInvert( lua_State *L );
int lmathMatrixIdentity( lua_State *L );
int lmathMatrixAdd( lua_State *L );
int lmathMatrixSubtract( lua_State *L );
int lmathMatrixMultiply( lua_State *L );
int lmathMatrixTranslate( lua_State *L );
int lmathMatrixRotate( lua_State *L );
int lmathMatrixRotateX( lua_State *L );
int lmathMatrixRotateY( lua_State *L );
int lmathMatrixRotateZ( lua_State *L );
int lmathMatrixRotateXYZ( lua_State *L );
int lmathMatrixRotateZYX( lua_State *L );
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
int lmathQuaternionEquals( lua_State *L );
