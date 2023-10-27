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
	state->guiFont = 0;
	state->logLevelInvalid = LOG_ERROR;
	/* Fonts. */
	state->fontAlloc = ALLOC_PAGE_SIZE;
	state->fontCount = 1;
	state->fonts = malloc( state->fontAlloc * sizeof( Font* ) );
	/* Waves. */
	state->waveAlloc = ALLOC_PAGE_SIZE;
	state->waveCount = 0;
	state->waves = malloc( state->waveAlloc * sizeof( Wave* ) );
	/* Sounds. */
	state->soundAlloc = ALLOC_PAGE_SIZE;
	state->soundCount = 0;
	state->sounds = malloc( state->soundAlloc * sizeof( Sound* ) );
	/* Musics. */
	state->musicAlloc = ALLOC_PAGE_SIZE;
	state->musicCount = 0;
	state->musics = malloc( state->musicAlloc * sizeof( Music* ) );
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
	/* Lights. */
	state->lightAlloc = ALLOC_PAGE_SIZE;
	state->lightCount = 0;
	state->lights = malloc( state->lightAlloc * sizeof( Light* ) );

	for ( int i = 0; i < ALLOC_PAGE_SIZE; i++ ) {
		state->waves[i] = NULL;
		state->sounds[i] = NULL;
		state->meshes[i] = NULL;
		state->models[i] = NULL;
		state->animations[i] = NULL;
		state->lights[i] = NULL;

		/* The ones we want to save the first. */
		if ( 0 < i ) {
			state->fonts[i] = NULL;
			state->materials[i] = NULL;
		}
	}
    InitWindow( state->resolution.x, state->resolution.y, "ReiLua" );
	/* Has to be after InitWindod where opengl context is created. */
	state->materials[0] = malloc( sizeof( Material ) );
	*state->materials[0] = LoadMaterialDefault();
	state->fonts[0] = malloc( sizeof( Font ) );
	*state->fonts[0] = GetFontDefault();

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
	for ( int i = 0; i < state->fontCount; ++i ) {
		if ( state->fonts[i] != NULL ) {
			UnloadFont( *state->fonts[i] );
			free( state->fonts[i] );
		}
	}
	for ( int i = 0; i < state->waveCount; ++i ) {
		if ( state->waves[i] != NULL ) {
			UnloadWave( *state->waves[i] );
			free( state->waves[i] );
		}
	}
	for ( int i = 0; i < state->soundCount; ++i ) {
		if ( state->sounds[i] != NULL ) {
			UnloadSound( *state->sounds[i] );
			free( state->sounds[i] );
		}
	}
	for ( int i = 0; i < state->musicCount; ++i ) {
		if ( state->musics[i] != NULL ) {
			UnloadMusicStream( *state->musics[i] );
			free( state->musics[i] );
		}
	}
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
	
#if !defined( PLATFORM_RPI ) || !defined( PLATFORM_DRM )
	for ( int i = 0; i < state->lightCount; ++i ) {
		if ( state->lights[i] != NULL ) {
			free( state->lights[i] );
		}
	}
#endif
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
	free( state->fonts );
	free( state->waves );
	free( state->sounds );
	free( state->musics );
	free( state->meshes );
	free( state->materials );
	free( state->models );
	free( state->animations );
	free( state->lights );
	free( state->exePath );
	free( state );
}
