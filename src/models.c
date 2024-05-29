#include "main.h"
#include "state.h"
#include "models.h"
#include "lua_core.h"
#include "rmath.h"
#include "textures.h"
#include "core.h"

void unloadMaterial( Material* material ) {
	free( material->maps );
}

void DrawBillboardProNoRatio( Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint ) {
	// NOTE: Billboard size will maintain source rectangle aspect ratio, size will represent billboard width
	// Vector2 sizeRatio = { size.x*(float)source.width/source.height, size.y };
	Vector2 sizeRatio = { size.x, size.y };

	Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);

	Vector3 right = { matView.m0, matView.m4, matView.m8 };
	//Vector3 up = { matView.m1, matView.m5, matView.m9 };

	Vector3 rightScaled = Vector3Scale(right, sizeRatio.x/2);
	Vector3 upScaled = Vector3Scale(up, sizeRatio.y/2);

	Vector3 p1 = Vector3Add(rightScaled, upScaled);
	Vector3 p2 = Vector3Subtract(rightScaled, upScaled);

	Vector3 topLeft = Vector3Scale(p2, -1);
	Vector3 topRight = p1;
	Vector3 bottomRight = p2;
	Vector3 bottomLeft = Vector3Scale(p1, -1);

	if (rotation != 0.0f)
	{
		float sinRotation = sinf(rotation*DEG2RAD);
		float cosRotation = cosf(rotation*DEG2RAD);

		// NOTE: (-1, 1) is the range where origin.x, origin.y is inside the texture
		float rotateAboutX = sizeRatio.x*origin.x/2;
		float rotateAboutY = sizeRatio.y*origin.y/2;

		float xtvalue, ytvalue;
		float rotatedX, rotatedY;

		xtvalue = Vector3DotProduct(right, topLeft) - rotateAboutX; // Project points to x and y coordinates on the billboard plane
		ytvalue = Vector3DotProduct(up, topLeft) - rotateAboutY;
		rotatedX = xtvalue*cosRotation - ytvalue*sinRotation + rotateAboutX; // Rotate about the point origin
		rotatedY = xtvalue*sinRotation + ytvalue*cosRotation + rotateAboutY;
		topLeft = Vector3Add(Vector3Scale(up, rotatedY), Vector3Scale(right, rotatedX)); // Translate back to cartesian coordinates

		xtvalue = Vector3DotProduct(right, topRight) - rotateAboutX;
		ytvalue = Vector3DotProduct(up, topRight) - rotateAboutY;
		rotatedX = xtvalue*cosRotation - ytvalue*sinRotation + rotateAboutX;
		rotatedY = xtvalue*sinRotation + ytvalue*cosRotation + rotateAboutY;
		topRight = Vector3Add(Vector3Scale(up, rotatedY), Vector3Scale(right, rotatedX));

		xtvalue = Vector3DotProduct(right, bottomRight) - rotateAboutX;
		ytvalue = Vector3DotProduct(up, bottomRight) - rotateAboutY;
		rotatedX = xtvalue*cosRotation - ytvalue*sinRotation + rotateAboutX;
		rotatedY = xtvalue*sinRotation + ytvalue*cosRotation + rotateAboutY;
		bottomRight = Vector3Add(Vector3Scale(up, rotatedY), Vector3Scale(right, rotatedX));

		xtvalue = Vector3DotProduct(right, bottomLeft)-rotateAboutX;
		ytvalue = Vector3DotProduct(up, bottomLeft)-rotateAboutY;
		rotatedX = xtvalue*cosRotation - ytvalue*sinRotation + rotateAboutX;
		rotatedY = xtvalue*sinRotation + ytvalue*cosRotation + rotateAboutY;
		bottomLeft = Vector3Add(Vector3Scale(up, rotatedY), Vector3Scale(right, rotatedX));
	}

	// Translate points to the draw center (position)
	topLeft = Vector3Add(topLeft, position);
	topRight = Vector3Add(topRight, position);
	bottomRight = Vector3Add(bottomRight, position);
	bottomLeft = Vector3Add(bottomLeft, position);

	rlSetTexture(texture.id);

	rlBegin(RL_QUADS);
		rlColor4ub(tint.r, tint.g, tint.b, tint.a);

		// Bottom-left corner for texture and quad
		rlTexCoord2f((float)source.x/texture.width, (float)source.y/texture.height);
		rlVertex3f(topLeft.x, topLeft.y, topLeft.z);

		// Top-left corner for texture and quad
		rlTexCoord2f((float)source.x/texture.width, (float)(source.y + source.height)/texture.height);
		rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);

		// Top-right corner for texture and quad
		rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height);
		rlVertex3f(bottomRight.x, bottomRight.y, bottomRight.z);

		// Bottom-right corner for texture and quad
		rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)source.y/texture.height);
		rlVertex3f(topRight.x, topRight.y, topRight.z);
	rlEnd();

	rlSetTexture(0);
}

void DrawBillboardRecNoRatio( Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint ) {
	// NOTE: Billboard locked on axis-Y
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	DrawBillboardProNoRatio(camera, texture, source, position, up, size, Vector2Zero(), 0.0f, tint);
}

/*
## Models - Basic geometric 3D shapes drawing functions
*/

/*
> RL.DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )

Draw a line in 3D world space
*/
int lmodelsDrawLine3D( lua_State* L ) {
	Vector3 startPos = uluaGetVector3( L, 1 );
	Vector3 endPos = uluaGetVector3( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawLine3D( startPos, endPos, color);

	return 0;
}

/*
> RL.DrawPoint3D( Vector3 position, Color color )

Draw a point in 3D space, actually a small line
*/
int lmodelsDrawPoint3D( lua_State* L ) {
	Vector3 position = uluaGetVector3( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawPoint3D( position, color );

	return 0;
}

/*
> RL.DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )

Draw a circle in 3D world space
*/
int lmodelsDrawCircle3D( lua_State* L ) {
	Vector3 center = uluaGetVector3( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Vector3 rotationAxis = uluaGetVector3( L, 3 );
	float rotationAngle = luaL_checknumber( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawCircle3D( center, radius, rotationAxis, rotationAngle, color );

	return 0;
}

/*
> RL.DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )

Draw a color-filled triangle (Vertex in counter-clockwise order!)
*/
int lmodelsDrawTriangle3D( lua_State* L ) {
	Vector3 v1 = uluaGetVector3( L, 1 );
	Vector3 v2 = uluaGetVector3( L, 2 );
	Vector3 v3 = uluaGetVector3( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawTriangle3D( v1, v2, v3, color );

	return 0;
}

/*
> RL.DrawTriangleStrip3D( Vector3{} points, Color color )

Draw a triangle strip defined by points
*/
int lmodelsDrawTriangleStrip3D( lua_State* L ) {
	int pointCount = uluaGetTableLen( L, 1 ); 
	Color color = uluaGetColor( L, 2 );

	Vector3 points[ pointCount ];

	int t = 1, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) ) {
			points[i] = uluaGetVector3( L, lua_gettop( L ) );
		}
		i++;
		lua_pop( L, 1 );
	}
	DrawTriangleStrip3D( points, pointCount, color );

	return 0;
}

/*
> RL.DrawCube( Vector3 position, Vector3 size, Color color )

Draw cube
*/
int lmodelsDrawCube( lua_State* L ) {
	Vector3 pos = uluaGetVector3( L, 1 );
	Vector3 size = uluaGetVector3( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawCubeV( pos, size, color );

	return 0;
}

/*
> RL.DrawCubeWires( Vector3 position, Vector3 size, Color color )

Draw cube wires
*/
int lmodelsDrawCubeWires( lua_State* L ) {
	Vector3 pos = uluaGetVector3( L, 1 );
	Vector3 size = uluaGetVector3( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawCubeWiresV( pos, size, color );

	return 0;
}

/*
> RL.DrawSphere( Vector3 centerPos, float radius, Color color )

Draw sphere
*/
int lmodelsDrawSphere( lua_State* L ) {
	Vector3 centerPos = uluaGetVector3( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawSphere( centerPos, radius, color );

	return 0;
}

/*
> RL.DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere with extended parameters
*/
int lmodelsDrawSphereEx( lua_State* L ) {
	Vector3 centerPos = uluaGetVector3( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	int rings = luaL_checkinteger( L, 3 );
	int slices = luaL_checkinteger( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawSphereEx( centerPos, radius, rings, slices, color );

	return 0;
}

/*
> RL.DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere wires
*/
int lmodelsDrawSphereWires( lua_State* L ) {
	Vector3 centerPos = uluaGetVector3( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	int rings = luaL_checkinteger( L, 3 );
	int slices = luaL_checkinteger( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawSphereWires( centerPos, radius, rings, slices, color );

	return 0;
}

/*
> RL.DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone
*/
int lmodelsDrawCylinder( lua_State* L ) {
	Vector3 position = uluaGetVector3( L, 1 );
	float radiusTop = luaL_checknumber( L, 2 );
	float radiusBottom = luaL_checknumber( L, 3 );
	float height = luaL_checknumber( L, 4 );
	int slices = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCylinder( position, radiusTop, radiusBottom, height, slices, color );

	return 0;
}

/*
> RL.DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder with base at startPos and top at endPos
*/
int lmodelsDrawCylinderEx( lua_State* L ) {
	Vector3 startPos = uluaGetVector3( L, 1 );
	Vector3 endPos = uluaGetVector3( L, 2 );
	float startRadius = luaL_checknumber( L, 3 );
	float endRadius = luaL_checknumber( L, 4 );
	int sides = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCylinderEx( startPos, endPos, startRadius, endRadius, sides, color );

	return 0;
}

/*
> RL.DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone wires
*/
int lmodelsDrawCylinderWires( lua_State* L ) {
	Vector3 position = uluaGetVector3( L, 1 );
	float radiusTop = luaL_checknumber( L, 2 );
	float radiusBottom = luaL_checknumber( L, 3 );
	float height = luaL_checknumber( L, 4 );
	int slices = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCylinderWires( position, radiusTop, radiusBottom, height, slices, color );

	return 0;
}

/*
> RL.DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder wires with base at startPos and top at endPos
*/
int lmodelsDrawCylinderWiresEx( lua_State* L ) {
	Vector3 startPos = uluaGetVector3( L, 1 );
	Vector3 endPos = uluaGetVector3( L, 2 );
	float startRadius = luaL_checknumber( L, 3 );
	float endRadius = luaL_checknumber( L, 4 );
	int sides = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCylinderWiresEx( startPos, endPos, startRadius, endRadius, sides, color );

	return 0;
}

/*
> RL.DrawCapsule( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw a capsule with the center of its sphere caps at startPos and endPos
*/
int lmodelsDrawCapsule( lua_State* L ) {
	Vector3 startPos = uluaGetVector3( L, 1 );
	Vector3 endPos = uluaGetVector3( L, 2 );
	float radius = luaL_checknumber( L, 3 );
	int slices = luaL_checkinteger( L, 4 );
	int rings = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCapsule( startPos, endPos, radius, slices, rings, color );

	return 0;
}

/*
> RL.DrawCapsuleWires( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw capsule wireframe with the center of its sphere caps at startPos and endPos
*/
int lmodelsDrawCapsuleWires( lua_State* L ) {
	Vector3 startPos = uluaGetVector3( L, 1 );
	Vector3 endPos = uluaGetVector3( L, 2 );
	float radius = luaL_checknumber( L, 3 );
	int slices = luaL_checkinteger( L, 4 );
	int rings = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCapsuleWires( startPos, endPos, radius, slices, rings, color );

	return 0;
}

/*
> RL.DrawPlane( Vector3 centerPos, Vector2 size, Color color )

Draw a plane XZ
*/
int lmodelsDrawPlane( lua_State* L ) {
	Vector3 centerPos = uluaGetVector3( L, 1 );
	Vector2 size = uluaGetVector2( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawPlane( centerPos, size, color );

	return 0;
}

/*
> RL.DrawQuad3DTexture( Texture texture, Vector3{} vertices, Vector2{} texCoords, Color{} colors )

Draw 3D textured quad. (Texture coordinates opengl style 0.0 - 1.0)
*/
int lmodelDrawQuad3DTexture( lua_State* L ) {
	Texture* texture = uluaGetTexture( L, 1 );

	/* Vertices. */
	Vector3 vertices[4] = { 0 };

	int t = 2, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) && i < 4 ) {
			vertices[i] = uluaGetVector3( L, lua_gettop( L ) );
		}
		i++;
		lua_pop( L, 1 );
	}

	/* TexCoords. */
	Vector2 texcoords[4] = { 0 };

	t = 3, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) && i < 4 ) {
			texcoords[i] = uluaGetVector2( L, lua_gettop( L ) );
		}
		i++;
		lua_pop( L, 1 );
	}

	/* Colors. */
	Color colors[4] = { 0 };

	t = 4, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) && i < 4 ) {
			colors[i] = uluaGetColor( L, lua_gettop( L ) );
		}
		i++;
		lua_pop( L, 1 );
	}

	//TODO Normals. maybe something like Vector3Normalize(Vector3CrossProduct(Vector3Subtract(vB, vA), Vector3Subtract(vC, vA)));

	/* Draw. */
	rlCheckRenderBatchLimit( 4 );
	rlSetTexture( texture->id );

	rlBegin( RL_QUADS );
		for ( i = 0; i < 4; ++i ) {
			rlTexCoord2f( texcoords[i].x, texcoords[i].y );
			rlColor4ub( colors[i].r, colors[i].g, colors[i].b, colors[i].a );
			rlVertex3f( vertices[i].x, vertices[i].y, vertices[i].z );
		}
	rlEnd();
	rlSetTexture( 0 );

	return 0;
}

/*
> RL.DrawRay( Ray ray, Color color )

Draw a ray line
*/
int lmodelsDrawRay( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawRay( ray, color );

	return 0;
}

/*
> RL.DrawGrid( int slices, float spacing )

Draw a grid (Centered at ( 0, 0, 0 ))
*/
int lmodelsDrawGrid( lua_State* L ) {
	int slices = luaL_checkinteger( L, 1 );
	float spacing = luaL_checknumber( L, 2 );

	DrawGrid( slices, spacing );

	return 0;
}

/*
## Models - Model management functions
*/

/*
> model = RL.LoadModel( string fileName )

Load model from files (Meshes and materials)

- Failure return nil
- Success return Model
*/
int lmodelsLoadModel( lua_State* L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushModel( L, LoadModel( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> model = RL.LoadModelFromMesh( Mesh mesh )

Load model from generated mesh (Default material)

- Success return Model
*/
int lmodelsLoadModelFromMesh( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	uluaPushModel( L, LoadModelFromMesh( *mesh ) );

	return 1;
}

/*
> isReady = RL.IsModelReady( Model model )

Check if a model is ready

- Success return bool
*/
int lmodelsIsModelReady( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	lua_pushboolean( L, IsModelReady( *model ) );

	return 1;
}

/*
> RL.UnloadModel( Model model )

Unload model (including meshes) from memory (RAM and/or VRAM)
*/
int lmodelsUnloadModel( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	UnloadModel( *model );
	memset( model, 0, sizeof( Model ) );

	return 0;
}

/*
> boundingBox = RL.GetModelBoundingBox( Model model )

Compute model bounding box limits (considers all meshes)

- Success return BoundingBox
*/
int lmodelsGetModelBoundingBox( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	uluaPushBoundingBox( L, GetModelBoundingBox( *model ) );

	return 1;
}

/*
> RL.SetModelTransform( Model model, Matrix transform )

Set model transform matrix
*/
int lmodelsSetModelTransform( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	Matrix transform = uluaGetMatrix( L, 2 );

	model->transform = transform;

	return 0;
}

/*
> success = RL.SetModelMesh( Model model, int meshId, Mesh mesh )

Set model mesh.

- Failure return false
- Success return true
*/
int lmodelsSetModelMesh( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int meshId = luaL_checkinteger( L, 2 );
	Mesh* mesh = uluaGetMesh( L, 3 );

	if ( 0 <= meshId && meshId < model->meshCount ) {
		model->meshes[ meshId ] = *mesh;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelMesh meshId %d out of bounds", meshId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> success = RL.SetModelMaterial( Model model, int materialId, Material material )

Set material to model material

- Failure return false
- Success return true
*/
int lmodelsSetModelMaterial( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int materialId = luaL_checkinteger( L, 2 );
	Material* material = uluaGetMaterial( L, 3 );

	if ( 0 <= materialId && materialId < model->materialCount ) {
		model->materials[ materialId ] = *material;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelMaterial materialId %d out of bounds", materialId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> RL.SetModelMeshMaterial( Model model, int meshId, int materialId )

Set material for a mesh (Mesh and material on this model)
*/
int lmodelsSetModelMeshMaterial( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int meshId = luaL_checkinteger( L, 2 );
	int materialId = luaL_checkinteger( L, 3 );

	if ( 0 <= meshId && meshId < model->meshCount && 0 <= materialId && materialId < model->materialCount ) {
		SetModelMeshMaterial( model, meshId, materialId );
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelMaterial meshId %d or materialId %d out of bounds", meshId, materialId );
		lua_pushboolean( L, false );
	}
	return 0;
}

/*
> success = RL.SetModelBone( Model model, int boneId, BoneInfo bone )

Set model bone information (skeleton)

- Failure return false
- Success return true
*/
int lmodelsSetModelBone( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );
	BoneInfo bone = uluaGetBoneInfo( L, 3 );

	if ( 0 <= boneId && boneId < model->boneCount ) {
		model->bones[ boneId ] = bone;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelBone boneId %d out of bounds", boneId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> success = RL.SetModelBindPose( Model model, int boneId, Transform pose )

Set model bones base transformation (pose)

- Failure return false
- Success return true
*/
int lmodelsSetModelBindPose( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );
	Transform pose = uluaGetTransform( L, 3 );

	if ( 0 <= boneId && boneId < model->boneCount ) {
		model->bindPose[ boneId ] = pose;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelBindPose boneId %d out of bounds", boneId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> transform = RL.GetModelTransform( Model model )

Get model transform matrix

- Success return Matrix
*/
int lmodelsGetModelTransform( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	uluaPushMatrix( L, model->transform );

	return 1;
}

/*
> meshCount = RL.GetModelMeshCount( Model model )

Get model number of meshes

- Success return int
*/
int lmodelsGetModelMeshCount( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	lua_pushinteger( L, model->meshCount );

	return 1;
}

/*
> meshCount = RL.GetModelMaterialCount( Model model )

Get model number of materials

- Success return int
*/
int lmodelsGetModelMaterialCount( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	lua_pushinteger( L, model->materialCount );

	return 1;
}

/*
> mesh = RL.GetModelMesh( Model model, int meshId )

Get model mesh. Return as lightuserdata

- Failure return nil
- Success return Mesh
*/
int lmodelsGetModelMesh( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int meshId = luaL_checkinteger( L, 2 );

	if ( 0 <= meshId && meshId < model->meshCount ) {
		lua_pushlightuserdata( L, &model->meshes[ meshId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelMesh meshId %d out of bounds", meshId );
		lua_pushnil( L );
	}
	return 1;
}

/*
> material = RL.GetModelMaterial( Model model, int materialId )

Get model material. Return as lightuserdata

- Failure return nil
- Success return Material
*/
int lmodelsGetModelMaterial( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int materialId = luaL_checkinteger( L, 2 );

	if ( 0 <= materialId && materialId < model->materialCount ) {
		lua_pushlightuserdata( L, &model->materials[ materialId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelMaterial materialId %d out of bounds", materialId );
		lua_pushnil( L );
	}
	return 1;
}

/*
> boneCount = RL.GetModelBoneCount( Model model )

Get model number of bones

- Success return int
*/
int lmodelsGetModelBoneCount( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );

	lua_pushinteger( L, model->boneCount );

	return 1;
}

/*
> bone = RL.GetModelBone( Model model, int boneId )

Get model bones information (skeleton)

- Failure return nil
- Success return BoneInfo
*/
int lmodelsGetModelBone( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );

	if ( 0 <= boneId && boneId < model->boneCount ) {
		uluaPushBoneInfo( L, model->bones[ boneId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelBone boneId %d out of bounds", boneId );
		lua_pushnil( L );
	}
	return 1;
}

/*
> pose = RL.GetModelBindPose( Model model, int boneId )

Get models bones base transformation (pose)

- Failure return nil
- Success return Transform
*/
int lmodelsGetModelBindPose( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );

	if ( 0 <= boneId && boneId < model->boneCount ) {
		uluaPushTransform( L, model->bindPose[ boneId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelBindPose boneId %d out of bounds", boneId );
		lua_pushnil( L );
	}
	return 1;
}

/*
## Models - Model drawing functions
*/

/*
> RL.DrawModel( Model model, Vector3 position, float scale, Color tint )

Draw a model (With texture if set)
*/
int lmodelsDrawModel( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	Vector3 position = uluaGetVector3( L, 2 );
	float scale = luaL_checknumber( L, 3 );
	Color tint = uluaGetColor( L, 4 );

	DrawModel( *model, position, scale, tint );

	return 0;
}

/*
> RL.DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model with extended parameters
*/
int lmodelsDrawModelEx( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	Vector3 position = uluaGetVector3( L, 2 );
	Vector3 rotationAxis = uluaGetVector3( L, 3 );
	float rotationAngle = luaL_checknumber( L, 4 );
	Vector3 scale = uluaGetVector3( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	DrawModelEx( *model, position, rotationAxis, rotationAngle, scale, tint );

	return 0;
}

/*
> RL.DrawModelWires( Model model, Vector3 position, float scale, Color tint )

Draw a model wires (with texture if set)
*/
int lmodelsDrawModelWires( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	Vector3 position = uluaGetVector3( L, 2 );
	float scale = luaL_checknumber( L, 3 );
	Color tint = uluaGetColor( L, 4 );

	DrawModelWires( *model, position, scale, tint );

	return 0;
}

/*
> RL.DrawModelWiresEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model wires (with texture if set) with extended parameters
*/
int lmodelsDrawModelWiresEx( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	Vector3 position = uluaGetVector3( L, 2 );
	Vector3 rotationAxis = uluaGetVector3( L, 3 );
	float rotationAngle = luaL_checknumber( L, 4 );
	Vector3 scale = uluaGetVector3( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	DrawModelWiresEx( *model, position, rotationAxis, rotationAngle, scale, tint );

	return 0;
}

/*
> RL.DrawBoundingBox( BoundingBox box, Color color )

Draw bounding box (wires)
*/
int lmodelsDrawBoundingBox( lua_State* L ) {
	BoundingBox box = uluaGetBoundingBox( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawBoundingBox( box, color );

	return 0;
}

/*
> RL.DrawBillboard( Camera3D camera, Texture texture, Vector3 position, float size, Color tint )

Draw a billboard texture
*/
int lmodelsDrawBillboard( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Texture* texture = uluaGetTexture( L, 2 );
	Vector3 position = uluaGetVector3( L, 3 );
	float size = luaL_checknumber( L, 4 );
	Color tint = uluaGetColor( L, 5 );

	DrawBillboard( *camera, *texture, position, size, tint );

	return 0;
}

/*
> RL.DrawBillboardRec( Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector2 size, Color tint )

Draw a billboard texture defined by source
*/
int lmodelsDrawBillboardRec( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Texture* texture = uluaGetTexture( L, 2 );
	Rectangle source = uluaGetRectangle( L, 3 );
	Vector3 position = uluaGetVector3( L, 4 );
	Vector2 size = uluaGetVector2( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	DrawBillboardRecNoRatio( *camera, *texture, source, position, size, tint );

	return 0;
}

/*
> RL.DrawBillboardPro( Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint )

Draw a billboard texture defined by source and rotation
*/
int lmodelsDrawBillboardPro( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Texture* texture = uluaGetTexture( L, 2 );
	Rectangle source = uluaGetRectangle( L, 3 );
	Vector3 position = uluaGetVector3( L, 4 );
	Vector3 up = uluaGetVector3( L, 5 );
	Vector2 size = uluaGetVector2( L, 6 );
	Vector2 origin = uluaGetVector2( L, 7 );
	float rotation = luaL_checknumber( L, 8 );
	Color tint = uluaGetColor( L, 9 );

	DrawBillboardProNoRatio( *camera, *texture, source, position, up, size, origin, rotation, tint );

	return 0;
}

/*
## Models - Mesh management functions
*/

/*
> RL.UpdateMesh( Mesh mesh, Mesh{} meshData )

Update mesh vertex data in GPU.
NOTE: Mainly intented to be used with custom meshes.
*/
int lmodelsUpdateMesh( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );
	luaL_checktype( L, 2, LUA_TTABLE );

	int t = 2;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "vertices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Vector3 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 && i < mesh->vertexCount ) {
				data[i] = uluaGetVector3( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 0, (void*)data, len * 3 * sizeof( float ), 0 );
		}
		else if ( strcmp( "texcoords", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Vector2 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector2( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 1, (void*)data, len * 2 * sizeof( float ), 0 );
		}
		else if ( strcmp( "texcoords2", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Vector2 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector2( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 5, (void*)data, len * 2 * sizeof( float ), 0 );
		}
		else if ( strcmp( "normals", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Vector3 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector3( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 2, (void*)data, len * 3 * sizeof( float ), 0 );
		}
		else if ( strcmp( "tangents", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Vector4 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector4( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 4, (void*)data, len * 4 * sizeof( float ), 0 );
		}
		else if ( strcmp( "colors", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			Color data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetColor( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 3, (void*)data, len * 4 * sizeof( unsigned char ), 0 );
		}
		else if ( strcmp( "indices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			unsigned short data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = (unsigned short)lua_tointeger( L, -1 );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 6, (void*)data, len * sizeof( unsigned short ), 0 );
		}
		lua_pop( L, 1 );
	}

	return 0;
}

/*
> RL.UnloadMesh( Mesh mesh )

Unload mesh data from CPU and GPU
*/
int lmodelsUnloadMesh( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	UnloadMesh( *mesh );
	memset( mesh, 0, sizeof( Mesh ) );

	return 0;
}

/*
> RL.DrawMesh( Mesh mesh, Material material, Matrix transform )

Draw a 3d mesh with material and transform
*/
int lmodelsDrawMesh( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );
	Material* material = uluaGetMaterial( L, 2 );
	Matrix matrix = uluaGetMatrix( L, 3 );

	DrawMesh( *mesh, *material, matrix );

	return 0;
}

/*
> RL.DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )

Draw multiple mesh instances with material and different transforms
*/
int lmodelsDrawMeshInstanced( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );
	Material* material = uluaGetMaterial( L, 2 );
	luaL_checktype( L, 3, LUA_TTABLE );
	int instances = luaL_checkinteger( L, 4 );

	Matrix transforms[ instances ];

	int t = 3, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) ) {
			transforms[i] = uluaGetMatrix( L, lua_gettop( L ) );
		}
		i++;
		lua_pop( L, 1 );
	}
	DrawMeshInstanced( *mesh, *material, transforms, instances );

	return 0;
}

/*
> success = RL.SetMeshColor( Mesh mesh, Color color )

Updades mesh color vertex attribute buffer
NOTE: Currently only works on custom mesh

- Failure return false
- Success return true
*/
int lmodelsSetMeshColor( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );
	Color color = uluaGetColor( L, 2 );

	if ( mesh->colors == NULL ) {
		TraceLog( state->logLevelInvalid, "Mesh doesn't have vertex colors allocated" );
		lua_pushboolean( L, false );
		return 1;
	}

	for ( int i = 0; i < mesh->vertexCount; ++i ) {
		mesh->colors[(i*4)+0] = (unsigned char)color.r;
		mesh->colors[(i*4)+1] = (unsigned char)color.g;
		mesh->colors[(i*4)+2] = (unsigned char)color.b;
		mesh->colors[(i*4)+3] = (unsigned char)color.a;
	}
	/* Update vertex attribute: color */
	rlUpdateVertexBuffer( mesh->vboId[3], mesh->colors, mesh->vertexCount * 4 * sizeof( unsigned char ), 0 );

	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ExportMesh( Mesh mesh, string fileName )

Export mesh data to file, returns true on success

- Success return bool
*/
int lmodelsExportMesh( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	lua_pushboolean( L, ExportMesh( *mesh, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> boundingBox = RL.GetMeshBoundingBox( Mesh mesh )

Compute mesh bounding box limits

- Success return BoundingBox
*/
int lmodelsGetMeshBoundingBox( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	uluaPushBoundingBox( L, GetMeshBoundingBox( *mesh ) );

	return 1;
}

/*
> RL.GenMeshTangents( Mesh mesh )

Compute mesh tangents
*/
int lmodelsGenMeshTangents( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	GenMeshTangents( mesh );

	return 0;
}

/*
> meshData = RL.GetMeshData( Mesh mesh )

Get mesh data as table.

- Success return Mesh{}
*/
int lmodelsGetMeshData( lua_State* L ) {
	Mesh* mesh = uluaGetMesh( L, 1 );

	lua_createtable( L, 2, 0 );

	/* Vertices. */

	if ( mesh->vertices != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 3, 0 );
			lua_pushnumber( L, mesh->vertices[i * 3 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushnumber( L, mesh->vertices[i * 3 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_pushnumber( L, mesh->vertices[i * 3 + 2] );
			lua_rawseti( L, -2, 3 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "vertices" );
	}

	/* Texcoords. */

	if ( mesh->texcoords != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 2, 0 );
			lua_pushnumber( L, mesh->texcoords[i * 2 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushnumber( L, mesh->texcoords[i * 2 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "texcoords" );
	}

	if ( mesh->texcoords2 != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 2, 0 );
			lua_pushnumber( L, mesh->texcoords2[i * 2 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushnumber( L, mesh->texcoords2[i * 2 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "texcoords2" );
	}

	/* Normals. */

	if ( mesh->normals != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 3, 0 );
			lua_pushnumber( L, mesh->normals[i * 3 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushnumber( L, mesh->normals[i * 3 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_pushnumber( L, mesh->normals[i * 3 + 2] );
			lua_rawseti( L, -2, 3 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "normals" );
	}

	/* Tangents. */

	if ( mesh->tangents != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 4, 0 );
			lua_pushnumber( L, mesh->tangents[i * 4 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushnumber( L, mesh->tangents[i * 4 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_pushnumber( L, mesh->tangents[i * 4 + 2] );
			lua_rawseti( L, -2, 3 );
			lua_pushnumber( L, mesh->tangents[i * 4 + 3] );
			lua_rawseti( L, -2, 4 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "tangents" );
	}

	/* Colors. */

	if ( mesh->colors != NULL ) {
		lua_createtable( L, mesh->vertexCount, 0 );

		for ( int i = 0; i < mesh->vertexCount; i++ ) {
			lua_createtable( L, 4, 0 );
			lua_pushinteger( L, mesh->colors[i * 4 + 0] );
			lua_rawseti( L, -2, 1 );
			lua_pushinteger( L, mesh->colors[i * 4 + 1] );
			lua_rawseti( L, -2, 2 );
			lua_pushinteger( L, mesh->colors[i * 4 + 2] );
			lua_rawseti( L, -2, 3 );
			lua_pushinteger( L, mesh->colors[i * 4 + 3] );
			lua_rawseti( L, -2, 4 );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "colors" );
	}

	/* Indices. */

	if ( mesh->indices != NULL ) {
		lua_createtable( L, mesh->triangleCount * 3, 0 );

		for ( int i = 0; i < mesh->triangleCount * 3; i++ ) {
			lua_pushinteger( L, mesh->indices[i] );
			lua_rawseti( L, -2, i + 1 );
		}
		lua_setfield( L, -2, "indices" );
	}

	return 1;
}

/*
## Models - Mesh generation functions
*/

/*
> mesh = RL.GenMeshPoly( int sides, float radius )

Generate polygonal mesh

- Success return Mesh
*/
int lmodelsGenMeshPoly( lua_State* L ) {
	int sides = luaL_checkinteger( L, 1 );
	float radius = luaL_checknumber( L, 2 );

	uluaPushMesh( L, GenMeshPoly( sides, radius ) );

	return 1;
}

/*
> mesh = RL.GenMeshPlane( float width, float length, int resX, int resZ )

Generate plane mesh (With subdivisions)

- Success return Mesh
*/
int lmodelsGenMeshPlane( lua_State* L ) {
	float width = luaL_checknumber( L, 1 );
	float length = luaL_checknumber( L, 2 );
	int resX = luaL_checkinteger( L, 3 );
	int resZ = luaL_checkinteger( L, 4 );

	uluaPushMesh( L, GenMeshPlane( width, length, resX, resZ ) );

	return 1;
}

/*
> mesh = RL.GenMeshCube( Vector3 size )

Generate cuboid mesh

- Success return Mesh
*/
int lmodelsGenMeshCube( lua_State* L ) {
	Vector3 size = uluaGetVector3( L, 1 );

	uluaPushMesh( L, GenMeshCube( size.x, size.y, size.z ) );

	return 1;
}

/*
> mesh = RL.GenMeshSphere( float radius, int rings, int slices )

Generate sphere mesh (Standard sphere)

- Success return Mesh
*/
int lmodelsGenMeshSphere( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	int rings = luaL_checkinteger( L, 2 );
	int slices = luaL_checkinteger( L, 3 );

	uluaPushMesh( L, GenMeshSphere( radius, rings, slices ) );

	return 1;
}

/*
> mesh = RL.GenMeshHemiSphere( float radius, int rings, int slices )

Generate half-sphere mesh (no bottom cap)

- Success return Mesh
*/
int lmodelsGenMeshHemiSphere( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	int rings = luaL_checkinteger( L, 2 );
	int slices = luaL_checkinteger( L, 3 );

	uluaPushMesh( L, GenMeshHemiSphere( radius, rings, slices ) );

	return 1;
}

/*
> mesh = RL.GenMeshCylinder( float radius, float height, int slices )

Generate cylinder mesh

- Success return Mesh
*/
int lmodelsGenMeshCylinder( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	float height = luaL_checknumber( L, 2 );
	int slices = luaL_checkinteger( L, 3 );

	uluaPushMesh( L, GenMeshCylinder( radius, height, slices ) );

	return 1;
}

/*
> mesh = RL.GenMeshCone( float radius, float height, int slices )

Generate cone/pyramid mesh

- Success return Mesh
*/
int lmodelsGenMeshCone( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	float height = luaL_checknumber( L, 2 );
	int slices = luaL_checkinteger( L, 3 );

	uluaPushMesh( L, GenMeshCone( radius, height, slices ) );

	return 1;
}

/*
> mesh = RL.GenMeshTorus( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Success return Mesh
*/
int lmodelsGenMeshTorus( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	float size = luaL_checknumber( L, 2 );
	int radSeg = luaL_checkinteger( L, 3 );
	int sides = luaL_checkinteger( L, 4 );

	uluaPushMesh( L, GenMeshTorus( radius, size, radSeg, sides ) );

	return 1;
}

/*
> mesh = RL.GenMeshKnot( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Success return Mesh
*/
int lmodelsGenMeshKnot( lua_State* L ) {
	float radius = luaL_checknumber( L, 1 );
	float size = luaL_checknumber( L, 2 );
	int radSeg = luaL_checkinteger( L, 3 );
	int sides = luaL_checkinteger( L, 4 );

	uluaPushMesh( L, GenMeshKnot( radius, size, radSeg, sides ) );

	return 1;
}

/*
> mesh = RL.GenMeshHeightmap( Image heightmap, Vector3 size )

Generate heightmap mesh from image data

- Success return Mesh
*/
int lmodelsGenMeshHeightmap( lua_State* L ) {
	Image* heightmap = uluaGetImage( L, 1 );
	Vector3 size = uluaGetVector3( L, 2 );

	uluaPushMesh( L, GenMeshHeightmap( *heightmap, size ) );

	return 1;
}

/*
> mesh = RL.GenMeshCubicmap( Image cubicmap, Vector3 cubeSize )

Generate cubes-based map mesh from image data

- Success return Mesh
*/
int lmodelsGenMeshCubicmap( lua_State* L ) {
	Image* cubicmap = uluaGetImage( L, 1 );
	Vector3 cubeSize = uluaGetVector3( L, 2 );

	uluaPushMesh( L, GenMeshCubicmap( *cubicmap, cubeSize ) );

	return 1;
}

/*
> mesh = RL.GenMeshCustom( Mesh{} meshData, bool dynamic )

Generate custom mesh from vertex attribute data and uploads it into a VAO (if supported) and VBO

- Success return Mesh
*/
int lmodelsGenMeshCustom( lua_State* L ) {
	luaL_checktype( L, 1, LUA_TTABLE );
	bool dynamic = uluaGetBoolean( L, 2 );

	Mesh mesh = { 0 };
	int indiceCount = 0;

	int t = 1;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "vertices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.vertexCount = len;
			mesh.triangleCount = len / 3;
			mesh.vertices = (float*)MemAlloc( len * 3 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector3 vec = uluaGetVector3( L, lua_gettop( L ) );

				mesh.vertices[(i*3)+0] = vec.x;
				mesh.vertices[(i*3)+1] = vec.y;
				mesh.vertices[(i*3)+2] = vec.z;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "texcoords", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.texcoords = (float*)MemAlloc( len * 2 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector2 vec = uluaGetVector2( L, lua_gettop( L ) );

				mesh.texcoords[(i*2)+0] = vec.x;
				mesh.texcoords[(i*2)+1] = vec.y;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "texcoords2", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.texcoords2 = (float*)MemAlloc( len * 2 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector2 vec = uluaGetVector2( L, lua_gettop( L ) );

				mesh.texcoords2[(i*2)+0] = vec.x;
				mesh.texcoords2[(i*2)+1] = vec.y;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "normals", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.normals = (float*)MemAlloc( len * 3 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector3 vec = uluaGetVector3( L, lua_gettop( L ) );

				mesh.normals[(i*3)+0] = vec.x;
				mesh.normals[(i*3)+1] = vec.y;
				mesh.normals[(i*3)+2] = vec.z;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "tangents", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.tangents = (float*)MemAlloc( len * 4 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector4 vec = uluaGetVector4( L, lua_gettop( L ) );

				mesh.tangents[(i*4)+0] = vec.x;
				mesh.tangents[(i*4)+1] = vec.y;
				mesh.tangents[(i*4)+2] = vec.z;
				mesh.tangents[(i*4)+3] = vec.w;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "colors", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );

			mesh.colors = (unsigned char*)MemAlloc( len * 4 * sizeof(unsigned char) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Color color = uluaGetColor( L, lua_gettop( L ) );

				mesh.colors[(i*4)+0] = color.r;
				mesh.colors[(i*4)+1] = color.g;
				mesh.colors[(i*4)+2] = color.b;
				mesh.colors[(i*4)+3] = color.a;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "indices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L, lua_gettop( L ) );
			indiceCount = len;

			mesh.indices = (unsigned short*)MemAlloc( len * sizeof(unsigned short) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				mesh.indices[i] = (unsigned short)lua_tointeger( L, -1 );
				i++;
				lua_pop( L, 1 );
			}
		}
		lua_pop( L, 1 );
	}

	/* We have to set this here since it's not known if vertices or indices are set first. */
	if ( 0 < indiceCount ) {
		mesh.triangleCount = indiceCount / 3;
	}

	UploadMesh( &mesh, dynamic );
	uluaPushMesh( L, mesh );

	return 1;
}

/*
## Models - Material management functions
*/

/*
> materials = RL.LoadMaterials( string fileName )

Load materials from model file

- Success return Material{}
*/
int lmodelsLoadMaterials( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );

	int materialCount = 0;
	Material* materials = LoadMaterials( fileName, &materialCount );
	lua_createtable( L, materialCount, 0 );

	for ( int i = 0; i < materialCount; i++ ) {
		uluaPushMaterial( L, materials[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	return 1;
}

/*
> material = RL.GetMaterialDefault()

Default material for reference. Return as lightuserdata

- Success return Material
*/
int lmodelsGetMaterialDefault( lua_State* L ) {
	lua_pushlightuserdata( L, &state->defaultMaterial );

	return 1;
}

/*
> material = RL.LoadMaterialDefault()

Load default material as new object

- Success return Material
*/
int lmodelsLoadMaterialDefault( lua_State* L ) {
	uluaPushMaterial( L, LoadMaterialDefault() );

	return 1;
}

/*
> material = RL.CreateMaterial( Material{} materialData )

Load material from table. See material table definition

- Success return Material
*/
int lmodelsCreateMaterial( lua_State* L ) {
	luaL_checktype( L, 1, LUA_TTABLE );

	Material material = LoadMaterialDefault();

	int t = lua_gettop( L );
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "maps", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			int t2 = lua_gettop( L );
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				/* Loop maps. Array where we don't care about the index value. */
				if ( lua_istable( L, -1 ) ) {
					int t3 = lua_gettop( L ), j = 0, map = 0;
					lua_pushnil( L );

					while ( lua_next( L, t3 ) != 0 ) {
						switch ( j ) {
							case 0:	/* Map */
								map = lua_tointeger( L, -1 );
								break;
							case 1: /* Parameters */
							{
								int t4 = lua_gettop( L );
								lua_pushnil( L );

								while ( lua_next( L, t4 ) != 0 ) {
									if ( strcmp( "texture", (char*)lua_tostring( L, -2 ) ) == 0 ) {
										Texture* texture = uluaGetTexture( L, lua_gettop( L ) );
										material.maps[map].texture = *texture;
									}
									else if ( strcmp( "color", (char*)lua_tostring( L, -2 ) ) == 0 ) {
										material.maps[map].color = uluaGetColor( L, lua_gettop( L ) );
									}
									else if ( strcmp( "value", (char*)lua_tostring( L, -2 ) ) == 0 ) {
										material.maps[map].value = luaL_checkinteger( L, -1 );
									}
									lua_pop( L, 1 );
								}
							}
								break;
							default:
								break;
						}
					j++;
					lua_pop( L, 1 );
					}
				}
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "params", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			int t2 = lua_gettop( L ), j = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				if ( j <= 3 ) {
					material.params[j] = luaL_checknumber( L, -1 );
				}
				j++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "shader", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			Shader* shader = uluaGetShader( L, lua_gettop( L ) );
			material.shader = *shader;
		}
		lua_pop( L, 1 );
	}
	uluaPushMaterial( L, material );

	return 1;
}

/*
> isReady = RL.IsMaterialReady( Material material )

Check if a material is ready

- Success return bool
*/
int lmodelsIsMaterialReady( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );

	lua_pushboolean( L, IsMaterialReady( *material ) );

	return 1;
}

/*
> RL.UnloadMaterial( Material material )

Unload material from GPU memory (VRAM)
*/
int lmodelsUnloadMaterial( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );

	/* Custom UnloadMaterial since we don't want to free Shaders or Textures. */
	unloadMaterial( material );
	memset( material, 0, sizeof( Material ) );

	// UnloadMaterial( *material );

	return 0;
}

/*
> RL.SetMaterialTexture( Material material, int mapType, Texture texture )

Set texture for a material map type (MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS...)
*/
int lmodelsSetMaterialTexture( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );
	Texture* texture = uluaGetTexture( L, 3 );

	SetMaterialTexture( material, mapType, *texture );

	return 0;
}

/*
> RL.SetMaterialColor( Material material, int mapType, Color color )

Set color for a material map type
*/
int lmodelsSetMaterialColor( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );
	Color color = uluaGetColor( L, 3 );

	material->maps[ mapType ].color = color;

	return 0;
}

/*
> RL.SetMaterialValue( Material material, int mapType, float value )

Set value for a material map type
*/
int lmodelsSetMaterialValue( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );
	float value = luaL_checknumber( L, 3 );

	material->maps[ mapType ].value = value;

	return 0;
}

/*
> RL.SetMaterialShader( Material material, Shader shader )

Set shader for material
*/
int lmodelsSetMaterialShader( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	Shader* shader = uluaGetShader( L, 2 );

	material->shader = *shader;

	return 0;
}

/*
> RL.SetMaterialParams( Material material, float{} params )

Set material generic parameters (if required)
*/
int lmodelsSetMaterialParams( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );

	size_t len = uluaGetTableLen( L, 2 );

	float params[ len ];

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		params[i] = lua_tonumber( L, -1 );
		i++;
		lua_pop( L, 1 );
	}
	int paramCount = ( len > 4 ) ? 4 : len;

	for ( int i = 0; i < paramCount; i++ ) {
		material->params[i] = params[i];
	}

	return 0;
}

/*
> texture = RL.GetMaterialTexture( Material material, int mapType )

Get texture from material map type. Return as lightuserdata

- Success return Texture
*/
int lmodelsGetMaterialTexture( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );

	lua_pushlightuserdata( L, &material->maps[ mapType ].texture );

	return 1;
}

/*
> color = RL.GetMaterialColor( Material material, int mapType )

Get color from material map type

- Success return Color
*/
int lmodelsGetMaterialColor( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );

	uluaPushColor( L, material->maps[ mapType ].color );

	return 1;
}

/*
> value = RL.GetMaterialValue( Material material, int mapType )

Get color from material map type

- Success return float
*/
int lmodelsGetMaterialValue( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );
	int mapType = luaL_checkinteger( L, 2 );

	lua_pushnumber( L, material->maps[ mapType ].value );

	return 1;
}

/*
> shader = RL.GetMaterialShader( Material material )

Get material shader. Return as lightuserdata

- Success return Shader
*/
int lmodelsGetMaterialShader( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );

	lua_pushlightuserdata( L, &material->shader );

	return 1;
}

/*
> params = RL.GetMaterialParams( Material material )

Get material parameters

- Success return float{}
*/
int lmodelsGetMaterialParams( lua_State* L ) {
	Material* material = uluaGetMaterial( L, 1 );

	Vector4 params = {
		material->params[0],
		material->params[1],
		material->params[2],
		material->params[3]
	};
	uluaPushVector4( L, params );

	return 1;
}

/*
## Model - Model animations management functions
*/

/*
> animations = RL.LoadModelAnimations( string fileName )

Load model animations from file

- Failure return nil
- Success return ModelAnimations{}
*/
int lmodelsLoadModelAnimations( lua_State* L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		int animationCount = 0;
		ModelAnimation* anims = LoadModelAnimations( lua_tostring( L, 1 ), &animationCount );

		lua_createtable( L, animationCount, 0 );

		for ( int i = 0; i < animationCount; i++ ) {
			uluaPushModelAnimation( L, anims[i] );
			lua_rawseti( L, -2, i+1 );
		}
		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> RL.UpdateModelAnimation( Model model, ModelAnimation animation, int frame )

Update model animation pose
*/
int lmodelsUpdateModelAnimation( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	ModelAnimation* animation = uluaGetModelAnimation( L, 2 );
	int frame = luaL_checkinteger( L, 3 );

	UpdateModelAnimation( *model, *animation, frame );

	return 0;
}

/*
> RL.UnloadModelAnimation( ModelAnimation animation )

Unload animation data
*/
int lmodelsUnloadModelAnimation( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );

	UnloadModelAnimation( *animation );
	memset( animation, 0, sizeof( ModelAnimation ) );

	return 0;
}

/*
> RL.UnloadModelAnimations( ModelAnimation{} animations )

Unload animation table data
*/
int lmodelsUnloadModelAnimations( lua_State* L ) {
	int t = 1, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isuserdata( L, -1 ) ) {
			ModelAnimation* animation = uluaGetModelAnimation( L, lua_gettop( L ) );
			UnloadModelAnimation( *animation );
			memset( animation, 0, sizeof( ModelAnimation ) );
		}
		i++;
		lua_pop( L, 1 );
	}
	return 0;
}

/*
> valid = RL.IsModelAnimationValid( Model model, ModelAnimation animation )

Check model animation skeleton match

- Success return bool
*/
int lmodelsIsModelAnimationValid( lua_State* L ) {
	Model* model = uluaGetModel( L, 1 );
	ModelAnimation* animation = uluaGetModelAnimation( L, 2 );

	lua_pushboolean( L, IsModelAnimationValid( *model, *animation ) );

	return 1;
}

/*
> success = RL.SetModelAnimationBone( ModelAnimation animation, int boneId, BoneInfo bone )

Set modelAnimation bones information (skeleton)

- Failure return false
- Success return true
*/
int lmodelsSetModelAnimationBone( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );
	BoneInfo bone = uluaGetBoneInfo( L, 3 );

	if ( 0 <= boneId && boneId < animation->boneCount ) {
		animation->bones[ boneId ] = bone;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelAnimationBone boneId %d out of bounds", boneId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> success = RL.SetModelAnimationFramePose( ModelAnimation animation, int frame, int boneId, Transform pose )

Set modelAnimation bones base transformation (pose)

- Failure return false
- Success return true
*/
int lmodelsSetModelAnimationFramePose( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );
	int frame = luaL_checkinteger( L, 2 );
	int boneId = luaL_checkinteger( L, 3 );
	Transform pose = uluaGetTransform( L, 4 );

	if ( 0 <= frame && frame < animation->frameCount && 0 <= boneId && boneId < animation->boneCount ) {
		animation->framePoses[ frame ][ boneId ] = pose;
		lua_pushboolean( L, true );
	}
	else {
		TraceLog( LOG_WARNING, "SetModelAnimationFramePose frame %d or BoneId %d out of bounds", frame, boneId );
		lua_pushboolean( L, false );
	}
	return 1;
}

/*
> RL.SetModelAnimationName( ModelAnimation animation, string name )

Set modelAnimation name
*/
int lmodelsSetModelAnimationName( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );
	const char* name = luaL_checkstring( L, 2 );

	strncpy( animation->name, name, 32 );

	return 0;
}

/*
> boneCount = RL.GetModelAnimationBoneCount( ModelAnimation animation )

Return modelAnimation bone count

- Success return int
*/
int lmodelsGetModelAnimationBoneCount( lua_State* L ) {
	ModelAnimation* modelAnimation = uluaGetModelAnimation( L, 1 );

	lua_pushinteger( L, modelAnimation->boneCount );

	return 1;
}

/*
> frameCount = RL.GetModelAnimationFrameCount( ModelAnimation animation )

Return modelAnimation frame count

- Success return int
*/
int lmodelsGetModelAnimationFrameCount( lua_State* L ) {
	ModelAnimation* modelAnimation = uluaGetModelAnimation( L, 1 );

	lua_pushinteger( L, modelAnimation->frameCount );

	return 1;
}

/*
> bone = RL.GetModelAnimationBone( ModelAnimation animation, int boneId )

Get modelAnimation bones information (skeleton)

- Failure return nil
- Success return BoneInfo
*/
int lmodelsGetModelAnimationBone( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );
	int boneId = luaL_checkinteger( L, 2 );

	if ( 0 <= boneId && boneId < animation->boneCount ) {
		uluaPushBoneInfo( L, animation->bones[ boneId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelAnimationBone boneId %d out of bounds", boneId );
		lua_pushnil( L );
	}
	return 1;
}

/*
> pose = RL.GetModelAnimationFramePose( ModelAnimation animation, int frame, int boneId )

Get modelAnimation bones base transformation (pose)

- Failure return nil
- Success return Transform
*/
int lmodelsGetModelAnimationFramePose( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );
	int frame = luaL_checkinteger( L, 2 );
	int boneId = luaL_checkinteger( L, 3 );

	if ( 0 <= frame && frame < animation->frameCount && 0 <= boneId && boneId < animation->boneCount ) {
		uluaPushTransform( L, animation->framePoses[ frame ][ boneId ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetModelAnimationFramePose frame %d or BoneId %d out of bounds", frame, boneId );
		lua_pushnil( L );
	}
	return 1;
}

/*
> name = RL.GetModelAnimationName( ModelAnimation animation )

Get modelAnimation name

- Success return string
*/
int lmodelsGetModelAnimationName( lua_State* L ) {
	ModelAnimation* animation = uluaGetModelAnimation( L, 1 );

	lua_pushstring( L, animation->name );

	return 1;
}

/*
## Model - Collision detection functions
*/

/*
> collision = RL.CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )

Check collision between two spheres

- Success return bool
*/
int lmodelsCheckCollisionSpheres( lua_State* L ) {
	Vector3 center1 = uluaGetVector3( L, 1 );
	float radius1 = luaL_checknumber( L, 2 );
	Vector3 center2 = uluaGetVector3( L, 3 );
	float radius2 = luaL_checknumber( L, 4 );

	lua_pushboolean( L, CheckCollisionSpheres( center1, radius1, center2, radius2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )

Check collision between two bounding boxes

- Success return bool
*/
int lmodelsCheckCollisionBoxes( lua_State* L ) {
	BoundingBox box1 = uluaGetBoundingBox( L, 1 );
	BoundingBox box2 = uluaGetBoundingBox( L, 2 );

	lua_pushboolean( L, CheckCollisionBoxes( box1, box2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )

Check collision between box and sphere

- Success return bool
*/
int lmodelsCheckCollisionBoxSphere( lua_State* L ) {
	BoundingBox box = uluaGetBoundingBox( L, 1 );
	Vector3 center = uluaGetVector3( L, 2 );
	float radius = luaL_checknumber( L, 3 );

	lua_pushboolean( L, CheckCollisionBoxSphere( box, center, radius ) );

	return 1;
}

/*
> rayCollision = RL.GetRayCollisionSphere( Ray ray, Vector3 center, float radius )

Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )

- Success return RayCollision
*/
int lmodelsGetRayCollisionSphere( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	Vector3 center = uluaGetVector3( L, 2 );
	float radius = luaL_checknumber( L, 3 );

	uluaPushRayCollision( L, GetRayCollisionSphere( ray, center, radius ) );

	return 1;
}

/*
> rayCollision = RL.GetRayCollisionBox( Ray ray, BoundingBox box )

Get collision info between ray and box

- Success return RayCollision
*/
int lmodelsGetRayCollisionBox( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	BoundingBox box = uluaGetBoundingBox( L, 2 );

	uluaPushRayCollision( L, GetRayCollisionBox( ray, box ) );

	return 1;
}

/*
> rayCollision = RL.GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )

Get collision info between ray and mesh

- Success return RayCollision
*/
int lmodelsGetRayCollisionMesh( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	Mesh* mesh = uluaGetMesh( L, 2 );
	Matrix transform = uluaGetMatrix( L, 3 );

	uluaPushRayCollision( L, GetRayCollisionMesh( ray, *mesh, transform ) );

	return 1;
}

/*
> rayCollision = RL.GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )

Get collision info between ray and triangle

- Success return RayCollision
*/
int lmodelsGetRayCollisionTriangle( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	Vector3 p1 = uluaGetVector3( L, 2 );
	Vector3 p2 = uluaGetVector3( L, 3 );
	Vector3 p3 = uluaGetVector3( L, 4 );

	uluaPushRayCollision( L, GetRayCollisionTriangle( ray, p1, p2, p3 ) );

	return 1;
}

/*
> rayCollision = RL.GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )

Get collision info between ray and quad

- Success return RayCollision
*/
int lmodelsGetRayCollisionQuad( lua_State* L ) {
	Ray ray = uluaGetRay( L, 1 );
	Vector3 p1 = uluaGetVector3( L, 2 );
	Vector3 p2 = uluaGetVector3( L, 3 );
	Vector3 p3 = uluaGetVector3( L, 4 );
	Vector3 p4 = uluaGetVector3( L, 5 );

	uluaPushRayCollision( L, GetRayCollisionQuad( ray, p1, p2, p3, p4 ) );

	return 1;
}
