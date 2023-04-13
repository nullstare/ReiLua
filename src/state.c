#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "models.h"

State *state;

bool stateInit( const char *exePath ) {
	state = malloc( sizeof( State ) );

	state->exePath = malloc( STRING_LEN * sizeof( char ) );
	strncpy( state->exePath, exePath, STRING_LEN - 1 );

	state->hasWindow = true;
	state->run = true;
	state->resolution = (Vector2){ 800, 600 };
	state->luaState = NULL;
	state->textureSource = TEXTURE_SOURCE_TEXTURE;
	state->guiFont = 0;
	/* Images. */
	state->imageAlloc = ALLOC_PAGE_SIZE;
	state->imageCount = 0;
	state->images = malloc( state->imageAlloc * sizeof( Image* ) );
	/* Textures. */
	state->textureAlloc = ALLOC_PAGE_SIZE;
	state->textureCount = 0;
	state->textures = malloc( state->textureAlloc * sizeof( Texture2D* ) );
	/* RenderTextures. */
	state->renderTextureAlloc = ALLOC_PAGE_SIZE;
	state->renderTextureCount = 0;
	state->renderTextures = malloc( state->renderTextureAlloc * sizeof( RenderTexture2D* ) );
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
	/* Camera2D's. */
	state->camera2DAlloc = ALLOC_PAGE_SIZE;
	state->camera2DCount = 0;
	state->camera2Ds = malloc( state->camera2DAlloc * sizeof( Camera2D* ) );
	/* Camera3D's. */
	state->camera3DAlloc = ALLOC_PAGE_SIZE;
	state->camera3DCount = 0;
	state->camera3Ds = malloc( state->camera3DAlloc * sizeof( Camera3D* ) );
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
	/* Shaders. */
	state->shaderAlloc = ALLOC_PAGE_SIZE;
	state->shaderCount = 0;
	state->shaders = malloc( state->shaderAlloc * sizeof( Shader* ) );
	/* Lights. */
	state->lightAlloc = ALLOC_PAGE_SIZE;
	state->lightCount = 0;
	state->lights = malloc( state->lightAlloc * sizeof( Light* ) );

	for ( int i = 0; i < ALLOC_PAGE_SIZE; i++ ) {
		state->images[i] = NULL;
		state->textures[i] = NULL;
		state->renderTextures[i] = NULL;
		state->waves[i] = NULL;
		state->sounds[i] = NULL;
		state->camera2Ds[i] = NULL;
		state->camera3Ds[i] = NULL;
		state->meshes[i] = NULL;
		state->models[i] = NULL;
		state->animations[i] = NULL;
		state->shaders[i] = NULL;
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
		state->run = luaInit();
	}

	return state->run;
}

bool stateInitInterpret() {
	state = malloc( sizeof( State ) );
	luaInit();
}

void stateFree() {
	for ( int i = 0; i < state->imageCount; ++i ) {
		if ( state->images[i] != NULL ) {
			UnloadImage( *state->images[i] );
			free( state->images[i] );
		}
	}	
	for ( int i = 0; i < state->textureCount; ++i ) {
		if ( state->textures[i] != NULL ) {
			UnloadTexture( *state->textures[i] );
			free( state->textures[i] );
		}
	}
	for ( int i = 0; i < state->renderTextureCount; ++i ) {
		if ( state->renderTextures[i] != NULL ) {
			UnloadRenderTexture( *state->renderTextures[i] );
			free( state->renderTextures[i] );
		}
	}
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
	for ( int i = 0; i < state->camera2DCount; ++i ) {
		if ( state->camera2Ds[i] != NULL ) {
			free( state->camera2Ds[i] );
		}
	}
	for ( int i = 0; i < state->camera3DCount; ++i ) {
		if ( state->camera3Ds[i] != NULL ) {
			free( state->camera3Ds[i] );
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
	for ( int i = 0; i < state->shaderCount; ++i ) {
		if ( state->shaders[i] != NULL ) {
			UnloadShader( *state->shaders[i] );
			free( state->shaders[i] );
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
		UnloadMusicStream( state->music );
	}
	if ( state->hasWindow ) {
		CloseWindow();
	}
	if ( state->luaState != NULL ) {
		lua_close( state->luaState );
	}
	free( state->images );
	free( state->textures );
	free( state->renderTextures );
	free( state->fonts );
	free( state->waves );
	free( state->sounds );
	free( state->camera2Ds );
	free( state->camera3Ds );
	free( state->meshes );
	free( state->materials );
	free( state->models );
	free( state->animations );
	free( state->shaders );
	free( state->lights );
	free( state->exePath );
	free( state );
}
