#include "main.h"
#include "state.h"
#include "models.h"
#include "lua_core.h"
#include "rmath.h"
#include "textures.h"
#include "core.h"

static void checkMeshRealloc( int i ) {
	if ( i == state->meshCount ) {
		state->meshCount++;
	}

	if ( state->meshCount == state->meshAlloc ) {
		state->meshAlloc += ALLOC_PAGE_SIZE;
		state->meshes = realloc( state->meshes, state->meshAlloc * sizeof( Mesh* ) );

		for ( i = state->meshCount; i < state->meshAlloc; i++ ) {
			state->meshes[i] = NULL;
		}
	}
}

static void checkMaterialRealloc( int i ) {
	if ( i == state->materialCount ) {
		state->materialCount++;
	}

	if ( state->materialCount == state->materialAlloc ) {
		state->materialAlloc += ALLOC_PAGE_SIZE;
		state->materials = realloc( state->materials, state->materialAlloc * sizeof( Material* ) );

		for ( i = state->materialCount; i < state->materialAlloc; i++ ) {
			state->materials[i] = NULL;
		}
	}
}

static void checkModelRealloc( int i ) {
	if ( i == state->modelCount ) {
		state->modelCount++;
	}

	if ( state->modelCount == state->modelAlloc ) {
		state->modelAlloc += ALLOC_PAGE_SIZE;
		state->models = realloc( state->models, state->modelAlloc * sizeof( Model* ) );

		for ( i = state->modelCount; i < state->modelAlloc; i++ ) {
			state->models[i] = NULL;
		}
	}
}

static void checkAnimationRealloc( int i ) {
	if ( i == state->animationCount ) {
		state->animationCount++;
	}

	if ( state->animationCount == state->animationAlloc ) {
		state->animationAlloc += ALLOC_PAGE_SIZE;
		state->animations = realloc( state->animations, state->animationAlloc * sizeof( ModelAnimations* ) );

		for ( i = state->animationCount; i < state->animationAlloc; i++ ) {
			state->animations[i] = NULL;
		}
	}
}

static bool validMesh( size_t id ) {
	if ( id < 0 || state->meshCount < id || state->meshes[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid mesh", id );
		return false;
	}
	else {
		return true;
	}
}

static bool validMaterial( size_t id ) {
	if ( id < 0 || state->materialCount < id || state->materials[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid material", id );
		return false;
	}
	else {
		return true;
	}
}

static bool validModel( size_t id ) {
	if ( id < 0 || state->modelCount < id || state->models[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid model", id );
		return false;
	}
	else {
		return true;
	}
}

static bool validAnimation( size_t id ) {
	if ( id < 0 || state->animationCount < id || state->animations[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid animation", id );
		return false;
	}
	else {
		return true;
	}
}

static int newMesh() {
	int i = 0;

	for ( i = 0; i < state->meshCount; i++ ) {
		if ( state->meshes[i] == NULL ) {
			break;
		}
	}
	state->meshes[i] = malloc( sizeof( Mesh ) );
	checkMeshRealloc( i );

	return i;
}

/*
## Models - Basic
*/

/*
> success = RL_DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )

Draw a line in 3D world space

- Failure return false
- Success return true
*/
int lmodelsDrawLine3D( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 endPos = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 startPos = uluaGetVector3( L );

	DrawLine3D( startPos, endPos, color);
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPoint3D( Vector3 position, Color color )

Draw a point in 3D space, actually a small line

- Failure return false
- Success return true
*/
int lmodelsDrawPoint3D( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPoint3D( Vector3 position, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );

	DrawPoint3D( position, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )

Draw a circle in 3D world space

- Failure return false
- Success return true
*/
int lmodelsDrawCircle3D( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float rotationAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 rotationAxis = uluaGetVector3( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 center = uluaGetVector3( L );

	DrawCircle3D( center, radius, rotationAxis, rotationAngle, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true
*/
int lmodelsDrawTriangle3D( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 v3 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 v1 = uluaGetVector3( L );

	DrawTriangle3D( v1, v2, v3, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCube( Vector3 position, Vector3 size, Color color )

Draw cube

- Failure return false
- Success return true
*/
int lmodelsDrawCube( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCube( Vector3 position, Vector3 size, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 size = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 pos = uluaGetVector3( L );

	DrawCubeV( pos, size, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCubeWires( Vector3 position, Vector3 size, Color color )

Draw cube wires

- Failure return false
- Success return true
*/
int lmodelsDrawCubeWires( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCubeWires( Vector3 position, Vector3 size, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 size = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 pos = uluaGetVector3( L );

	DrawCubeWiresV( pos, size, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCubeTexture( Texture2D texture, Vector3 position, Vector3 size, Color color )

Draw cube textured

- Failure return false
- Success return true
*/
int lmodelsDrawCubeTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCubeTexture( Texture2D texture, Vector3 position, Vector3 size, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 size = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 pos = uluaGetVector3( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

 	DrawCubeTexture( *texturesGetSourceTexture( texId ), pos, size.x, size.y, size.z, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawSphere( Vector3 centerPos, float radius, Color color )

Draw sphere

- Failure return false
- Success return true
*/
int lmodelsDrawSphere( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawSphere( Vector3 centerPos, float radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 centerPos = uluaGetVector3( L );

	DrawSphere( centerPos, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere with extended parameters

- Failure return false
- Success return true
*/
int lmodelsDrawSphereEx( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int slices = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int rings = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 centerPos = uluaGetVector3( L );

	DrawSphereEx( centerPos, radius, rings, slices, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere wires

- Failure return false
- Success return true
*/
int lmodelsDrawSphereWires( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int slices = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int rings = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 centerPos = uluaGetVector3( L );

	DrawSphereWires( centerPos, radius, rings, slices, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone

- Failure return false
- Success return true
*/
int lmodelsDrawCylinder( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int slices = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float height = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusBottom = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusTop = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );

	DrawCylinder( position, radiusTop, radiusBottom, height, slices, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder with base at startPos and top at endPos

- Failure return false
- Success return true
*/
int lmodelsDrawCylinderEx( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int sides = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 endPos = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 startPos = uluaGetVector3( L );

	DrawCylinderEx( startPos, endPos, startRadius, endRadius, sides, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone wires

- Failure return false
- Success return true
*/
int lmodelsDrawCylinderWires( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int slices = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float height = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusBottom = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusTop = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );

	DrawCylinderWires( position, radiusTop, radiusBottom, height, slices, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder wires with base at startPos and top at endPos

- Failure return false
- Success return true
*/
int lmodelsDrawCylinderWiresEx( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int sides = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 endPos = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 startPos = uluaGetVector3( L );

	DrawCylinderWiresEx( startPos, endPos, startRadius, endRadius, sides, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPlane( Vector3 centerPos, Vector2 size, Color color )

Draw a plane XZ

- Failure return false
- Success return true
*/
int lmodelsDrawPlane( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPlane( Vector3 centerPos, Vector2 size, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 size = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector3 centerPos = uluaGetVector3( L );

	DrawPlane( centerPos, size, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawQuad3DTexture( texture, Vector3{} vertices, Vector2{} texCoords, Color color )

Draw 3D quad texture using vertices and texture coordinates. Texture coordinates opengl style 0.0 - 1.0.
Note! Could be replaced something like "DrawPlaneTextureRec"

- Failure return false
- Success return true
*/
int lmodelDrawQuad3DTexture( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawQuad3DTexture( texture, Vector3{} vertices, Vector2{} texCoords, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );

	/* TexCoords. */
	Vector2 texcoords[4] = { 0 };

	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_istable( L, -1 ) && i < 4 ) {
			texcoords[i] = uluaGetVector2( L );
        }
        i++;
        lua_pop( L, 1 );
    }
	lua_pop( L, 1 );

	/* Vertices. */
	Vector3 vertices[4] = { 0 };

	t = lua_gettop( L );
	i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_istable( L, -1 ) && i < 4 ) {
			vertices[i] = uluaGetVector3( L );
        }
        i++;
        lua_pop( L, 1 );
    }
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	// Draw.
	rlCheckRenderBatchLimit( 4 );
	rlSetTexture( texturesGetSourceTexture( texId )->id );

	//TODO Normals. maybe something like Vector3Normalize(Vector3CrossProduct(Vector3Subtract(vB, vA), Vector3Subtract(vC, vA)));

	rlBegin( RL_QUADS );
        rlColor4ub( color.r, color.g, color.b, color.a );

		for ( i = 0; i < 4; ++i ) {
			rlTexCoord2f( texcoords[i].x, texcoords[i].y );
			rlVertex3f( vertices[i].x, vertices[i].y, vertices[i].z );
		}
	rlEnd();
	rlSetTexture( 0 );

	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRay( Ray ray, Color color )

Draw a ray line

- Failure return false
- Success return true
*/
int lmodelsDrawRay( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRay( Ray ray, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	DrawRay( ray, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawGrid( int slices, float spacing )

Draw a grid ( Centered at ( 0, 0, 0 ) )

- Failure return false
- Success return true
*/
int lmodelsDrawGrid( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawGrid( int slices, float spacing )" );
		lua_pushboolean( L, false );
		return 1;
	}
	DrawGrid( lua_tointeger( L, -2 ), lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Models - Mesh
*/

/*
> mesh = RL_GenMeshPoly( int sides, float radius )

Generate polygonal mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshPoly( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshPoly( int sides, float radius )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	float radius = lua_tonumber( L, -1 );
	int sides = lua_tointeger( L, -2 );
	int i = newMesh();

	*state->meshes[i] = GenMeshPoly( sides, radius );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshPlane( float width, float length, int resX, int resZ )

Generate plane mesh ( With subdivisions )

- Failure return -1
- Success return int
*/
int lmodelsGenMeshPlane( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshPlane( float width, float length, int resX, int resZ )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int resZ = lua_tointeger( L, -1 );
	int resX = lua_tointeger( L, -2 );
	float length = lua_tonumber( L, -3 );
	float width = lua_tonumber( L, -4 );
	int i = newMesh();

	*state->meshes[i] = GenMeshPlane( width, length, resX, resZ );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshCube( Vector3 size )

Generate cuboid mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshCube( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshCube( Vector3 size )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector3 size = uluaGetVector3( L );
	int i = newMesh();

	*state->meshes[i] = GenMeshCube( size.x, size.y, size.z );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshSphere( float radius, int rings, int slices )

Generate sphere mesh ( Standard sphere )

- Failure return -1
- Success return int
*/
int lmodelsGenMeshSphere( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshSphere( float radius, int rings, int slices )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int slices = lua_tointeger( L, -1 );
	int rings = lua_tointeger( L, -2 );
	float radius = lua_tonumber( L, -3 );
	int i = newMesh();

	*state->meshes[i] = GenMeshSphere( radius, rings, slices );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshCylinder( float radius, float height, int slices )

Generate cylinder mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshCylinder( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshCylinder( float radius, float height, int slices )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int slices = lua_tointeger( L, -1 );
	float height = lua_tonumber( L, -2 );
	float radius = lua_tonumber( L, -3 );
	int i = newMesh();

	*state->meshes[i] = GenMeshCylinder( radius, height, slices);
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshCone( float radius, float height, int slices )

Generate cone/pyramid mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshCone( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshCone( float radius, float height, int slices )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int slices = lua_tointeger( L, -1 );
	float height = lua_tonumber( L, -2 );
	float radius = lua_tonumber( L, -3 );
	int i = newMesh();
	
	*state->meshes[i] = GenMeshCone( radius, height, slices);
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshTorus( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshTorus( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshTorus( float radius, float size, int radSeg, int sides )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int sides = lua_tointeger( L, -1 );
	int radSeg = lua_tointeger( L, -2 );
	float size = lua_tonumber( L, -3 );
	float radius = lua_tonumber( L, -4 );
	int i = newMesh();
	
	*state->meshes[i] = GenMeshTorus( radius, size, radSeg, sides );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshKnot( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int
*/
int lmodelsGenMeshKnot( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshKnot( float radius, float size, int radSeg, int sides )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int sides = lua_tointeger( L, -1 );
	int radSeg = lua_tointeger( L, -2 );
	float size = lua_tonumber( L, -3 );
	float radius = lua_tonumber( L, -4 );
	int i = newMesh();
	
	*state->meshes[i] = GenMeshKnot( radius, size, radSeg, sides );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshHeightmap( Image heightmap, Vector3 size )

Generate heightmap mesh from image data

- Failure return -1
- Success return int
*/
int lmodelsGenMeshHeightmap( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshHeightmap( Image heightmap, Vector3 size )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector3 size = uluaGetVector3( L );
	lua_pop( L, 1 );
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	Image *heightmap = state->images[ imageId ];
	int i = newMesh();
	
	*state->meshes[i] = GenMeshHeightmap( *heightmap, size );
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> mesh = RL_GenMeshCustom( Mesh{}, bool dynamic )

Generate custom mesh from vertex attribute data and uploads it into a VAO ( if supported ) and VBO

- Failure return -1
- Success return int
*/
int lmodelsGenMeshCustom( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshCustom( Mesh{}, bool dynamic )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Mesh mesh = { 0 };

	bool dynamic = lua_toboolean( L, -1 );
	lua_pop( L, 1 );

	int t = lua_gettop( L );
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "vertices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.vertexCount = len;
			mesh.triangleCount = len / 3;
			mesh.vertices = (float*)MemAlloc( len * 3 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector3 vec = uluaGetVector3( L );

				mesh.vertices[(i*3)+0] = vec.x;
				mesh.vertices[(i*3)+1] = vec.y;
				mesh.vertices[(i*3)+2] = vec.z;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "texcoords", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.texcoords = (float*)MemAlloc( len * 2 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector2 vec = uluaGetVector2( L );

				mesh.texcoords[(i*2)+0] = vec.x;
				mesh.texcoords[(i*2)+1] = vec.y;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "texcoords2", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.texcoords2 = (float*)MemAlloc( len * 2 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector2 vec = uluaGetVector2( L );

				mesh.texcoords2[(i*2)+0] = vec.x;
				mesh.texcoords2[(i*2)+1] = vec.y;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "normals", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.normals = (float*)MemAlloc( len * 3 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector3 vec = uluaGetVector3( L );

				mesh.normals[(i*3)+0] = vec.x;
				mesh.normals[(i*3)+1] = vec.y;
				mesh.normals[(i*3)+2] = vec.z;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "tangents", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.tangents = (float*)MemAlloc( len * 4 * sizeof(float) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Vector4 vec = uluaGetVector4( L );

				mesh.tangents[(i*4)+0] = vec.x;
				mesh.tangents[(i*4)+1] = vec.y;
				mesh.tangents[(i*4)+2] = vec.z;
				mesh.tangents[(i*4)+3] = vec.w;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "colors", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

			mesh.colors = (unsigned char*)MemAlloc( len * 4 * sizeof(unsigned char) );

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				Color color = uluaGetColor( L );

				mesh.colors[(i*4)+0] = color.r;
				mesh.colors[(i*4)+1] = color.g;
				mesh.colors[(i*4)+2] = color.b;
				mesh.colors[(i*4)+3] = color.a;
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "indices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );

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
	UploadMesh( &mesh, dynamic );

	int i = newMesh();
	
	*state->meshes[i] = mesh;
	lua_pushinteger( L, i );
	checkMeshRealloc( i );

	return 1;
}

/*
> success = RL_UpdateMesh( Mesh{} )

Update mesh vertex data in GPU. ( Mainly intented to be used with custom meshes )

- Failure return false
- Success return true
*/
int lmodelsUpdateMesh( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UpdateMesh( Mesh{} )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	Mesh *mesh = state->meshes[ meshId ];

	int t = lua_gettop( L );
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "vertices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Vector3 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 && i < mesh->vertexCount ) {
				data[i] = uluaGetVector3( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 0, (void*)data, len * 3 * sizeof( float ), 0 );
		}
		else if ( strcmp( "texcoords", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Vector2 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector2( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 1, (void*)data, len * 2 * sizeof( float ), 0 );
		}
		else if ( strcmp( "texcoords2", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Vector2 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector2( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 5, (void*)data, len * 2 * sizeof( float ), 0 );
		}
		else if ( strcmp( "normals", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Vector3 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector3( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 2, (void*)data, len * 3 * sizeof( float ), 0 );
		}
		else if ( strcmp( "tangents", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Vector4 data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetVector4( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 4, (void*)data, len * 4 * sizeof( float ), 0 );
		}
		else if ( strcmp( "colors", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
			Color data[ len ];

			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				data[i] = uluaGetColor( L );
				i++;
				lua_pop( L, 1 );
			}
			UpdateMeshBuffer( *mesh, 3, (void*)data, len * 4 * sizeof( unsigned char ), 0 );
		}
		else if ( strcmp( "indices", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			size_t len = uluaGetTableLen( L );
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
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_UnloadMesh( Mesh mesh )

Unload mesh data from CPU and GPU

- Failure return false
- Success return true
*/
int lmodelsUnloadMesh( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadMesh( Mesh mesh )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validMesh( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadMesh( *state->meshes[ id ] );
	state->meshes[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawMesh( Mesh mesh, Material material, Matrix transform )

Draw a 3d mesh with material and transform

- Failure return false
- Success return true
*/
int lmodelsDrawMesh( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawMesh( Mesh mesh, Material material, Matrix transform )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix matrix = uluaGetMatrix( L );
	lua_pop( L, 1 );
	size_t materialId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) || !validMaterial( materialId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawMesh( *state->meshes[ meshId ], *state->materials[ materialId ], matrix );
	lua_pushboolean( L, true );

	return 1;
}

/* TODO Not testet. */
/*
> success = RL_DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )

Draw multiple mesh instances with material and different transforms

- Failure return false
- Success return true
*/
int lmodelsDrawMeshInstanced( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int instances = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Matrix matrises[ instances ];

	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_istable( L, -1 ) ) {
			matrises[i] = uluaGetMatrix( L );
        }
        i++;
        lua_pop( L, 1 );
    }
	lua_pop( L, 1 );
	size_t materialId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) || !validMaterial( materialId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawMeshInstanced( *state->meshes[ meshId ], *state->materials[ materialId ], matrises, instances );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetMeshColor( Mesh mesh, Color color )

Updades mesh color vertex attribute buffer
NOTE: Currently only works on custom mesh

- Failure return false
- Success return true
*/
int lmodelsSetMeshColor( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMeshColor( Mesh mesh, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	Mesh *mesh = state->meshes[ meshId ];

	if ( mesh->colors == NULL ) {
		TraceLog( LOG_WARNING, "Mesh %d %s", meshId, "Mesh doesn't have vertex colors allocated" );
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
> success = RL_ExportMesh( Mesh mesh, string fileName )

Export mesh data to file, returns true on success

- Failure return false
- Success return true
*/
int lmodelsExportMesh( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ExportMesh( Mesh mesh, string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -2 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ExportMesh( *state->meshes[ meshId ], lua_tostring( L, -1 ) ) );

	return 1;
}

/*
> boundingBox = RL_GetMeshBoundingBox( Mesh mesh )

Compute mesh bounding box limits

- Failure return false
- Success return BoundingBox
*/
int lmodelsGetMeshBoundingBox( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMeshBoundingBox( Mesh mesh )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushBoundingBox( L, GetMeshBoundingBox( *state->meshes[ meshId ] ) );

	return 1;
}

/*
> success = RL_GenMeshTangents( Mesh mesh )

Compute mesh tangents

- Failure return false
- Success return true
*/
int lmodelsGenMeshTangents( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshTangents( Mesh mesh )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	GenMeshTangents( state->meshes[ meshId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_GenMeshBinormals( Mesh mesh )

Compute mesh binormals

- Failure return false
- Success return true
*/
int lmodelsGenMeshBinormals( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GenMeshBinormals( Mesh mesh )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	GenMeshBinormals( state->meshes[ meshId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Models - Material
*/

/*
> material = RL_LoadMaterialDefault()

Load default material

- Success return int
*/
int lmodelsLoadMaterialDefault( lua_State *L ) {
	int i = 0;

	for ( i = 0; i < state->materialCount; i++ ) {
		if ( state->materials[i] == NULL ) {
			break;
		}
	}
	state->materials[i] = malloc( sizeof( Material ) );
	*state->materials[i] = LoadMaterialDefault();
	lua_pushinteger( L, i );
	checkMaterialRealloc( i );

	return 1;
}

/*
> material = RL_CreateMaterial( material{} )

Load material from table. See material table definition

- Failure return false
- Success return int
*/
int lmodelsCreateMaterial( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CreateMaterial( material{} )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->materialCount; i++ ) {
		if ( state->materials[i] == NULL ) {
			break;
		}
	}
	state->materials[i] = malloc( sizeof( Material ) );
	*state->materials[i] = LoadMaterialDefault();

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
									if ( strcmp( "texture", (char*)lua_tostring( L, -2 ) ) == 0 && lua_isnumber( L, -1 ) ) {
										state->materials[i]->maps[map].texture = *state->textures[ lua_tointeger( L, -1 ) ];
									}
									else if ( strcmp( "color", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
										state->materials[i]->maps[map].color = uluaGetColor( L );
									}
									else if ( strcmp( "value", (char*)lua_tostring( L, -2 ) ) == 0 && lua_isnumber( L, -1 ) ) {
										state->materials[i]->maps[map].value = lua_tonumber( L, -1 );
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
		else if ( strcmp( "params", (char*)lua_tostring( L, -2 ) ) == 0 && lua_istable( L, -1 ) ) {
			int t2 = lua_gettop( L ), j = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				if ( j <= 3 ) {
					state->materials[i]->params[j] = lua_tonumber( L, -1 );
				}
				j++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "shader", (char*)lua_tostring( L, -2 ) ) == 0 && lua_isnumber( L, -1 ) ) {
			state->materials[i]->shader = *state->shaders[ lua_tointeger( L, -1 ) ];
		}
		lua_pop( L, 1 );
	}
	lua_pushinteger( L, i );
	checkMaterialRealloc( i );

	return 1;
}

/*
> success = RL_UnloadMaterial( Material material )

Unload material from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int lmodelsUnloadMaterial( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadMaterial( Material material )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validMaterial( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadMaterial( *state->materials[ id ] );
	state->materials[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetMaterialTexture( Material material, int mapType, Texture2D texture )

Set texture for a material map type ( MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS... )

- Failure return false
- Success return true
*/
int lmodelsSetMaterialTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMaterialTexture( Material material, int mapType, Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t texId = lua_tointeger( L, -1 );
	size_t materialId = lua_tointeger( L, -3 );

	if ( !validMaterial( materialId ) || !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	
	SetMaterialTexture( state->materials[ materialId ], lua_tointeger( L, -2 ), *texturesGetSourceTexture( texId ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetMaterialColor( Material material, int mapType, Color color )

Set color for a material map type

- Failure return false
- Success return true
*/
int lmodelsSetMaterialColor( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMaterialColor( Material material, int mapType, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	size_t mapType = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t materialId = lua_tointeger( L, -1 );

	if ( !validMaterial( materialId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->materials[ materialId ]->maps[ mapType ].color = color;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetMaterialValue( Material material, int mapType, float value )

Set value for a material map type

- Failure return false
- Success return true
*/
int lmodelsSetMaterialValue( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMaterialValue( Material material, int mapType, float value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	size_t mapType = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t materialId = lua_tointeger( L, -1 );

	if ( !validMaterial( materialId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->materials[ materialId ]->maps[ mapType ].value = value;
	lua_pushboolean( L, true );

	return 1;
}

/*
## Models - Model
*/

/*
> model = RL_LoadModel( string fileName )

Load model from files ( Meshes and materials )

- Failure return -1
- Success return int
*/
int lmodelsLoadModel( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadModel( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->modelCount; i++ ) {
		if ( state->models[i] == NULL ) {
			break;
		}
	}
	state->models[i] = malloc( sizeof( Model ) );
	*state->models[i] = LoadModel( lua_tostring( L, -1 ) );
	lua_pushinteger( L, i );
	checkModelRealloc( i );

	return 1;
}

/*
> model = RL_LoadModelFromMesh( Mesh mesh )

Load model from generated mesh ( Default material )

- Failure return -1
- Success return int
*/
int lmodelsLoadModelFromMesh( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadModelFromMesh( Mesh mesh )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t meshId = lua_tointeger( L, -1 );

	if ( !validMesh( meshId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->modelCount; i++ ) {
		if ( state->models[i] == NULL ) {
			break;
		}
	}
	state->models[i] = malloc( sizeof( Model ) );
	*state->models[i] = LoadModelFromMesh( *state->meshes[ meshId ] );
	lua_pushinteger( L, i );
	checkModelRealloc( i );

	return 1;
}

/*
> success = RL_UnloadModel( Model model )

Unload model ( Including meshes ) from memory ( RAM and/or VRAM )

- Failure return false
- Success return true
*/
int lmodelsUnloadModel( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadModel( Model model )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t modelId = lua_tointeger( L, -1 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadModel( *state->models[ modelId ] );
	state->models[ modelId ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawModel( Model model, Vector3 position, float scale, Color tint )

Draw a model ( With texture if set )

- Failure return false
- Success return true
*/
int lmodelsDrawModel( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawModel( Model model, Vector3 position, float scale, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	float scale = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );
	lua_pop( L, 1 );
	size_t modelId = lua_tointeger( L, -1 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawModel( *state->models[ modelId ], position, scale, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model with extended parameters

- Failure return false
- Success return true
*/
int lmodelsDrawModelEx( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector3 scale = uluaGetVector3( L );
	lua_pop( L, 1 );
	float rotationAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 rotationAxis = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );
	lua_pop( L, 1 );
	size_t modelId = lua_tointeger( L, -1 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	DrawModelEx( *state->models[ modelId ], position, rotationAxis, rotationAngle, scale, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetModelMaterial( Model model, Material modelMaterial, Material material )

Copies material to model material. ( Model material is the material id in models. Material can be deleted if not used elsewhere )

- Failure return false
- Success return true
*/
int lmodelsSetModelMaterial( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetModelMaterial( Model model, Material modelMaterial, Material material )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t materialId = lua_tointeger( L, -1 );
	size_t modelId = lua_tointeger( L, -3 );

	if ( !validModel( modelId ) || !validMaterial( materialId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	Model *model = state->models[ modelId ];
	int modelMaterialId = lua_tointeger( L, -2 );
	Material *material = state->materials[ materialId ];

	/* Copy material data instead of using pointer. Pointer would result in double free error. */
	model->materials[ modelMaterialId ].shader = material->shader;
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_ALBEDO ] = material->maps[ MATERIAL_MAP_ALBEDO ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_METALNESS ] = material->maps[ MATERIAL_MAP_METALNESS ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_NORMAL ] = material->maps[ MATERIAL_MAP_NORMAL ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_ROUGHNESS ] = material->maps[ MATERIAL_MAP_ROUGHNESS ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_OCCLUSION ] = material->maps[ MATERIAL_MAP_OCCLUSION ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_EMISSION ] = material->maps[ MATERIAL_MAP_EMISSION ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_HEIGHT ] = material->maps[ MATERIAL_MAP_HEIGHT ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_CUBEMAP ] = material->maps[ MATERIAL_MAP_CUBEMAP ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_IRRADIANCE ] = material->maps[ MATERIAL_MAP_IRRADIANCE ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_PREFILTER ] = material->maps[ MATERIAL_MAP_PREFILTER ];
	model->materials[ modelMaterialId ].maps[ MATERIAL_MAP_BRDF ] = material->maps[ MATERIAL_MAP_BRDF ];

	for ( int i = 0; i < 4; i++ ) {
		model->materials[ modelMaterialId ].params[i] = material->params[i];
	}
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetModelMeshMaterial( Model model, int meshId, int materialId )

Set material for a mesh ( Mesh and material on this model )

- Failure return false
- Success return true
*/
int lmodelsSetModelMeshMaterial( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetModelMeshMaterial( Model model, int meshId, int materialId )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int materialId = lua_tointeger( L, -1 );
	int meshId = lua_tointeger( L, -2 );
	size_t modelId = lua_tointeger( L, -3 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetModelMeshMaterial( state->models[ modelId ], meshId, materialId );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawBillboard( Camera camera, Texture2D texture, Vector3 position, float size, Color tint )

Draw a billboard texture

- Failure return false
- Success return true
*/
int lmodelsDrawBillboard( lua_State *L ) {
	if ( !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_istable( L, -3 )
	|| !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawBillboard( Camera camera, Texture2D texture, Vector3 position, float size, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	float size = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) || !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawBillboard( *state->camera3Ds[ cameraId ], *texturesGetSourceTexture( texId ), position, size, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawBillboardRec( Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint )

Draw a billboard texture defined by source

- Failure return false
- Success return true
*/
int lmodelsDrawBillboardRec( lua_State *L ) {
	if ( !lua_isnumber( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_istable( L, -4 )
	|| !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawBillboardRec( Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color tint = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 size = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );
	lua_pop( L, 1 );
	Rectangle source = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) || !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	DrawBillboardRec( *state->camera3Ds[ cameraId ], *texturesGetSourceTexture( texId ), source, position, size, tint );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetModelTransform( Model model, Matrix transform )

Set model transform matrix

- Failure return false
- Success return true
*/
int lmodelsSetModelTransform( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetModelTransform( Model model, Matrix transform )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix transform = uluaGetMatrix( L );
	lua_pop( L, 1 );
	size_t modelId = lua_tointeger( L, -1 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->models[ modelId ]->transform = transform;
	lua_pushboolean( L, true );

	return 1;
}

/*
> transform = RL_GetModelTransform( Model model )

Get model transform matrix

- Failure return false
- Success return Matrix
*/
int lmodelsGetModelTransform( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetModelTransform( Model model )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t modelId = lua_tointeger( L, -1 );

	if ( !validModel( modelId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushMatrix( L, state->models[ modelId ]->transform );

	return 1;
}

/*
## Model - Animations
*/

/*
> animations, animationCount = RL_LoadModelAnimations( string fileName )

Load model animations from file

- Failure return -1
- Success return int, int
*/
int lmodelsLoadModelAnimations( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadModelAnimations( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->animationCount; i++ ) {
		if ( state->animations[i] == NULL ) {
			break;
		}
	}
	state->animations[i] = malloc( sizeof( ModelAnimations ) );
	state->animations[i]->animations = LoadModelAnimations( lua_tostring( L, -1 ), &state->animations[i]->animCount );
	checkAnimationRealloc( i );

	lua_pushinteger( L, i );
	lua_pushinteger( L, state->animations[i]->animCount );

	return 2;
}

/*
> success = RL_UpdateModelAnimation( Model model, ModelAnimations animations, int animation, int frame )

Update model animation pose

- Failure return false
- Success return true
*/
int lmodelsUpdateModelAnimation( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UpdateModelAnimation( Model model, ModelAnimations animations, int animation, int frame )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int frame = imax( 0, lua_tointeger( L, -1 ) );
	size_t animId = lua_tointeger( L, -3 );
	size_t modelId = lua_tointeger( L, -4 );

	if ( !validModel( modelId ) || !validAnimation( animId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UpdateModelAnimation( *state->models[ modelId ], state->animations[ animId ]->animations[ lua_tointeger( L, -2 ) ], frame );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_UnloadModelAnimations( ModelAnimations animations )

Unload animation data

- Failure return false
- Success return true
*/
int lmodelsUnloadModelAnimations( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadModelAnimations( ModelAnimations animations )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t animId = lua_tointeger( L, -1 );

	if ( !validAnimation( animId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadModelAnimation( *state->animations[ animId ]->animations );
	state->animations[ animId ]->animCount = 0;
	state->animations[ animId ] = NULL;

	lua_pushboolean( L, true );

	return 1;
}

/*
> valid = RL_IsModelAnimationValid( Model model, ModelAnimations animations )

Check model animation skeleton match

- Failure return nil
- Success return bool
*/
int lmodelsIsModelAnimationValid( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsModelAnimationValid( Model model, ModelAnimations animations )" );
		lua_pushnil( L );
		return 1;
	}
	size_t animId = lua_tointeger( L, -1 );
	size_t modelId = lua_tointeger( L, -2 );

	if ( !validModel( modelId ) || !validAnimation( animId ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsModelAnimationValid( *state->models[ modelId ], *state->animations[ animId ]->animations ) );

	return 1;
}

/*
> boneCount = RL_GetModelAnimationBoneCount( ModelAnimations animations, int animation )

Return modelAnimation bone count

- Failure return false
- Success return int
*/
int lmodelsGetModelAnimationBoneCount( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetModelAnimationBoneCount( ModelAnimations animations, int animation )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t animId = lua_tointeger( L, -2 );

	if ( !validAnimation( animId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->animations[ animId ]->animations[ lua_tointeger( L, -1 ) ].boneCount );

	return 1;
}

/*
> frameCount = RL_GetModelAnimationFrameCount( ModelAnimations animations, int animation )

Return modelAnimation frame count

- Failure return false
- Success return int
*/
int lmodelsGetModelAnimationFrameCount( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetModelAnimationFrameCount( ModelAnimations animations, int animation )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t animId = lua_tointeger( L, -2 );

	if ( !validAnimation( animId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->animations[ animId ]->animations[ lua_tointeger( L, -1 ) ].frameCount );

	return 1;
}

/*
## Model - Collision
*/

/*
> collision = RL_CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )

Check collision between two spheres

- Failure return nil
- Success return bool
*/
int lmodelsCheckCollisionSpheres( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )" );
		lua_pushnil( L );
		return 1;
	}
	float radius2 = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 center2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	float radius1 = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 center1 = uluaGetVector3( L );

	lua_pushboolean( L, CheckCollisionSpheres( center1, radius1, center2, radius2 ) );

	return 1;
}

/*
> collision = RL_CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )

Check collision between two bounding boxes

- Failure return nil
- Success return bool
*/
int lmodelsCheckCollisionBoxes( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )" );
		lua_pushnil( L );
		return 1;
	}
	BoundingBox box2 = uluaGetBoundingBox( L );
	lua_pop( L, 1 );
	BoundingBox box1 = uluaGetBoundingBox( L );

	lua_pushboolean( L, CheckCollisionBoxes( box1, box2 ) );

	return 1;
}

/*
> collision = RL_CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )

Check collision between box and sphere

- Failure return nil
- Success return bool
*/
int lmodelsCheckCollisionBoxSphere( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )" );
		lua_pushnil( L );
		return 1;
	}
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 center = uluaGetVector3( L );
	lua_pop( L, 1 );
	BoundingBox box = uluaGetBoundingBox( L );

	lua_pushboolean( L, CheckCollisionBoxSphere( box, center, radius ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionSphere( Ray ray, Vector3 center, float radius )

Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionSphere( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionSphere( Ray ray, Vector3 center, float radius )" );
		lua_pushnil( L );
		return 1;
	}
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector3 center = uluaGetVector3( L );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	uluaPushRayCollision( L, GetRayCollisionSphere( ray, center, radius ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionBox( Ray ray, BoundingBox box )

Get collision info between ray and box

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionBox( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionBox( Ray ray, BoundingBox box )" );
		lua_pushnil( L );
		return 1;
	}
	BoundingBox box = uluaGetBoundingBox( L );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	uluaPushRayCollision( L, GetRayCollisionBox( ray, box ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionModel( Ray ray, Model model )

Get collision info between ray and model

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionModel( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionModel( Ray ray, Model model )" );
		lua_pushnil( L );
		return 1;
	}
	size_t modelId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	if ( !validModel( modelId ) ) {
		lua_pushnil( L );
		return 1;
	}
	uluaPushRayCollision( L, GetRayCollisionModel( ray, *state->models[ modelId ] ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )

Get collision info between ray and mesh

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionMesh( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )" );
		lua_pushnil( L );
		return 1;
	}
	Matrix transform = uluaGetMatrix( L );
	lua_pop( L, 1 );
	size_t meshId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	if ( !validMesh( meshId ) ) {
		lua_pushnil( L );
		return 1;
	}
	uluaPushRayCollision( L, GetRayCollisionMesh( ray, *state->meshes[ meshId ], transform ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )

Get collision info between ray and triangle

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionTriangle( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector3 p3 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p1 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	uluaPushRayCollision( L, GetRayCollisionTriangle( ray, p1, p2, p3 ) );

	return 1;
}

/*
> rayCollision = RL_GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )

Get collision info between ray and quad

- Failure return nil
- Success return RayCollision
*/
int lmodelsGetRayCollisionQuad( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_istable( L, -4 ) || !lua_istable( L, -3 )
	|| !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector3 p4 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p3 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p2 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Vector3 p1 = uluaGetVector3( L );
	lua_pop( L, 1 );
	Ray ray = uluaGetRay( L );

	uluaPushRayCollision( L, GetRayCollisionQuad( ray, p1, p2, p3, p4 ) );

	return 1;
}

