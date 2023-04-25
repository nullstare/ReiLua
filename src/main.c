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
	bool interpret_mode = false;

	if ( 1 < argn ) {
		if ( strcmp( argc[1], "--version" ) == 0 || strcmp( argc[1], "-v" ) == 0 ) {
			printVersion();
			return 1;
		}
		else if ( strcmp( argc[1], "--help" ) == 0 || strcmp( argc[1], "-h" ) == 0 ) {
			printf(
"Usage: ReiLua [Options] [Directory to main.lua or main]\nOptions:\n-h --help\tThis help\n-v --version\tShow ReiLua version\n-i --interpret\tInterpret mode [File name]\n" );

			return 1;
		}
		else if ( strcmp( argc[1], "--interpret" ) == 0 || strcmp( argc[1], "-i" ) == 0 ) {
			interpret_mode = true;

			if ( 2 < argn ) {
				sprintf( exePath, "%s/%s", GetWorkingDirectory(), argc[2] );
			}
		}
		else{
			sprintf( exePath, "%s/%s", GetWorkingDirectory(), argc[1] );
		}
	}
	else {
		sprintf( exePath, "%s/", GetWorkingDirectory() );
	}

	if ( interpret_mode ) {
		stateInitInterpret();

		lua_State *L = state->luaState;
		lua_pushcfunction( L, luaTraceback );
		int tracebackidx = lua_gettop( L );

		luaL_loadfile( L, exePath );

		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			return false;
		}
	}
	else {
		printVersion();
		stateInit( exePath );
		luaRegister();
		state->run = luaCallMain();

		while ( state->run ) {
			if ( WindowShouldClose() ) {
				state->run = false;
			}
			luaCallProcess();
			luaCallDraw();
		}
		luaCallExit();
	}
	stateFree();

	return 1;
}
