#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "models.h"

State *state;

bool stateInit( int argn, const char **argc, const char *exePath ) {
	state = malloc( sizeof( State ) );

	state->exePath = malloc( STRING_LEN * sizeof( char ) );
	strncpy( state->exePath, exePath, STRING_LEN - 1 );

	state->hasWindow = true;
	state->run = true;
	state->resolution = (Vector2){ 800, 600 };
	state->luaState = NULL;
	state->logLevelInvalid = LOG_ERROR;
	/* Meshes. */
	state->meshAlloc = ALLOC_PAGE_SIZE;
	state->meshCount = 0;
	state->meshes = malloc( state->meshAlloc * sizeof( Mesh* ) );
	/* Materials. */
	state->materialAlloc = ALLOC_PAGE_SIZE;
	state->materialCount = 1;
	state->materials = malloc( state->materialAlloc * sizeof( Material* ) );
	/* Models. */
	state->modelAlloc = ALLOC_PAGE_SIZE;
	state->modelCount = 0;
	state->models = malloc( state->modelAlloc * sizeof( Model* ) );
	/* ModelsAnimations. */
	state->animationAlloc = ALLOC_PAGE_SIZE;
	state->animationCount = 0;
	state->animations = malloc( state->animationAlloc * sizeof( ModelAnimations* ) );

	for ( int i = 0; i < ALLOC_PAGE_SIZE; i++ ) {
		state->meshes[i] = NULL;
		state->models[i] = NULL;
		state->animations[i] = NULL;

		/* The ones we want to save the first. */
		if ( 0 < i ) {
			state->materials[i] = NULL;
		}
	}
    InitWindow( state->resolution.x, state->resolution.y, "ReiLua" );
	/* Has to be after InitWindod where opengl context is created. */
	state->materials[0] = malloc( sizeof( Material ) );
	*state->materials[0] = LoadMaterialDefault();

	if ( !IsWindowReady() ) {
		state->hasWindow = false;
		state->run = false;
	}
	if ( state->run ) {
		InitAudioDevice();
		state->run = luaInit( argn, argc );
	}

	return state->run;
}

void stateInitInterpret( int argn, const char **argc ) {
	state = malloc( sizeof( State ) );
	luaInit( argn, argc );
}

void stateFree() {
	for ( int i = 0; i < state->modelCount; ++i ) {
		if ( state->models[i] != NULL ) {
			//TODO Test if UnloadModel causes segfaults on exit.
			UnloadModelKeepMeshes( *state->models[i] );
			// UnloadModel( *state->models[i] );
			free( state->models[i] );
		}
	}
	for ( int i = 0; i < state->meshCount; ++i ) {
		if ( state->meshes[i] != NULL ) {
			UnloadMesh( *state->meshes[i] );
			free( state->meshes[i] );
		}
	}
	for ( int i = 0; i < state->materialCount; ++i ) {
		if ( state->materials[i] != NULL ) {
			/* Prevent unloading shader that would result in double free when freeing shaders. */
			state->materials[i]->shader.id = rlGetShaderIdDefault();

			UnloadMaterial( *state->materials[i] );
			free( state->materials[i] );
		}
	}
	for ( int i = 0; i < state->animationCount; ++i ) {
		if ( state->animations[i] != NULL ) {
			UnloadModelAnimations( state->animations[i]->animations, state->animations[i]->animCount );
			free( state->animations[i] );
		}
	}
	
	if ( IsAudioDeviceReady() ) {
		CloseAudioDevice();
	}
	if ( state->luaState != NULL ) {
		lua_close( state->luaState );
		state->luaState = NULL;
	}
	if ( state->hasWindow ) {
		CloseWindow();
	}
	free( state->meshes );
	free( state->materials );
	free( state->models );
	free( state->animations );
	free( state->exePath );
	free( state );
}
