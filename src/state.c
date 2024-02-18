#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "models.h"

State *state;

bool stateInit( int argn, const char** argc, const char* exePath ) {
	state = malloc( sizeof( State ) );

	state->exePath = malloc( STRING_LEN * sizeof( char ) );
	strncpy( state->exePath, exePath, STRING_LEN - 1 );

	state->hasWindow = true;
	state->run = true;
	state->resolution = (Vector2){ 800, 600 };
	state->luaState = NULL;
	state->logLevelInvalid = LOG_ERROR;
	state->gcUnload = true;

    InitWindow( state->resolution.x, state->resolution.y, "ReiLua" );

	if ( !IsWindowReady() ) {
		state->hasWindow = false;
		state->run = false;
	}
	if ( state->run ) {
		state->run = luaInit( argn, argc );
	}
	state->defaultFont = GetFontDefault();
	state->defaultMaterial = LoadMaterialDefault();
	state->defaultTexture = (Texture){ 1, 1, 1, 1, 7 };
	state->RLGLcurrentShaderLocs = malloc( RL_MAX_SHADER_LOCATIONS * sizeof( int ) );
	int* defaultShaderLocs = rlGetShaderLocsDefault();

	for ( int i = 0; i < RL_MAX_SHADER_LOCATIONS; i++ ) {
		state->RLGLcurrentShaderLocs[i] = defaultShaderLocs[i];
	}
#ifdef PLATFORM_DESKTOP_SDL
	state->SDL_eventQueue = malloc( PLATFORM_SDL_EVENT_QUEUE_LEN * sizeof( SDL_Event ) );
	state->SDL_eventQueueLen = 0;
#endif

	return state->run;
}

void stateInitInterpret( int argn, const char** argc ) {
	state = malloc( sizeof( State ) );
	luaInit( argn, argc );
}

void stateFree() {
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
#ifdef PLATFORM_DESKTOP_SDL
	free( state->SDL_eventQueue );
#endif
	free( state->exePath );
	free( state->RLGLcurrentShaderLocs );
	free( state );
}
