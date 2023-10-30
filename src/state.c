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

#ifdef GC_UNLOAD
	state->gcUnload = true;
#else
	state->gcUnload = false;
#endif

    InitWindow( state->resolution.x, state->resolution.y, "ReiLua" );

	if ( !IsWindowReady() ) {
		state->hasWindow = false;
		state->run = false;
	}
	if ( state->run ) {
		InitAudioDevice();
		state->run = luaInit( argn, argc );
	}
	state->defaultFont = GetFontDefault();
	state->defaultMaterial = LoadMaterialDefault();

	return state->run;
}

void stateInitInterpret( int argn, const char **argc ) {
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
	free( state->exePath );
	free( state );
}
