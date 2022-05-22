#include "main.h"
#include "state.h"
#include "lua_core.h"

inline static void printVersion() {
	if ( VERSION_DEV ) {
		TraceLog( LOG_INFO, "ReiLua %d.%d.%d-Dev", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH );
	}
	else {
		TraceLog( LOG_INFO, "ReiLua %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH );
	}
}

int main( int argn, const char **argc ) {
	char exePath[ STRING_LEN ] = { '\0' };

	if ( 1 < argn ) {
		if ( strcmp( argc[1], "--version" ) == 0 || strcmp( argc[1], "-v" ) == 0 ) {
			printVersion();
			return 1;
		}
		else{
			sprintf( exePath, "%s/%s", GetWorkingDirectory(), argc[1] );
		}
	}
	else {
		sprintf( exePath, "%s/", GetWorkingDirectory() );
	}
	printVersion();
	stateInit( exePath );

	while ( state->run ) {
		if ( WindowShouldClose() ) {
			state->run = false;
		}
		if ( IsAudioDeviceReady() ) {
			UpdateMusicStream( state->music );
		}
		luaCallProcess();
		luaCallDraw();
	}
	stateFree();

	return 1;
}
