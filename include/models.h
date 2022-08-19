#pragma once

/* Basic. */
int lmodelsDrawLine3D( lua_State *L );
int lmodelsDrawPoint3D( lua_State *L );
int lmodelsDrawCircle3D( lua_State *L );
int lmodelsDrawTriangle3D( lua_State *L );
int lmodelsDrawCube( lua_State *L );
int lmodelsDrawCubeWires( lua_State *L );
int lmodelsDrawCubeTexture( lua_State *L );
int lmodelsDrawSphere( lua_State *L );
int lmodelsDrawSphereEx( lua_State *L );
int lmodelsDrawSphereWires( lua_State *L );
int lmodelsDrawCylinder( lua_State *L );
int lmodelsDrawCylinderEx( lua_State *L );
int lmodelsDrawCylinderWires( lua_State *L );
int lmodelsDrawCylinderWiresEx( lua_State *L );
int lmodelsDrawPlane( lua_State *L );
int lmodelDrawQuad3DTexture( lua_State *L );
int lmodelsDrawRay( lua_State *L );
int lmodelsDrawGrid( lua_State *L );
/* Mesh. */
int lmodelsGenMeshPoly( lua_State *L );
int lmodelsGenMeshPlane( lua_State *L );
int lmodelsGenMeshCube( lua_State *L );
int lmodelsGenMeshSphere( lua_State *L );
int lmodelsGenMeshCylinder( lua_State *L );
int lmodelsGenMeshCone( lua_State *L );
int lmodelsGenMeshTorus( lua_State *L );
int lmodelsGenMeshKnot( lua_State *L );
int lmodelsGenMeshHeightmap( lua_State *L );
int lmodelsGenMeshCustom( lua_State *L );
int lmodelsUpdateMesh( lua_State *L );
int lmodelsUnloadMesh( lua_State *L );
int lmodelsDrawMesh( lua_State *L );
int lmodelsDrawMeshInstanced( lua_State *L );
int lmodelsSetMeshColor( lua_State *L );
int lmodelsExportMesh( lua_State *L );
int lmodelsGetMeshBoundingBox( lua_State *L );
int lmodelsGenMeshTangents( lua_State *L );
/* Material. */
int lmodelsLoadMaterialDefault( lua_State *L );
int lmodelsCreateMaterial( lua_State *L );
int lmodelsUnloadMaterial( lua_State *L );
int lmodelsSetMaterialTexture( lua_State *L );
int lmodelsSetMaterialColor( lua_State *L );
int lmodelsSetMaterialValue( lua_State *L );
/* Model. */
int lmodelsLoadModel( lua_State *L );
int lmodelsLoadModelFromMesh( lua_State *L );
int lmodelsUnloadModel( lua_State *L );
int lmodelsDrawModel( lua_State *L );
int lmodelsDrawModelEx( lua_State *L );
int lmodelsSetModelMaterial( lua_State *L );
int lmodelsSetModelMeshMaterial( lua_State *L );
int lmodelsDrawBillboard( lua_State *L );
int lmodelsDrawBillboardRec( lua_State *L );
int lmodelsSetModelTransform( lua_State *L );
int lmodelsGetModelTransform( lua_State *L );
/* Animations. */
int lmodelsLoadModelAnimations( lua_State *L );
int lmodelsUpdateModelAnimation( lua_State *L );
int lmodelsUnloadModelAnimations( lua_State *L );
int lmodelsIsModelAnimationValid( lua_State *L );
int lmodelsGetModelAnimationBoneCount( lua_State *L );
int lmodelsGetModelAnimationFrameCount( lua_State *L );
/* Collision. */
int lmodelsCheckCollisionSpheres( lua_State *L );
int lmodelsCheckCollisionBoxes( lua_State *L );
int lmodelsCheckCollisionBoxSphere( lua_State *L );
int lmodelsGetRayCollisionSphere( lua_State *L );
int lmodelsGetRayCollisionBox( lua_State *L );
int lmodelsGetRayCollisionMesh( lua_State *L );
int lmodelsGetRayCollisionTriangle( lua_State *L );
int lmodelsGetRayCollisionQuad( lua_State *L );
