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

#ifdef LUA_VERSION
	TraceLog( LOG_INFO, "%s", LUA_VERSION );
#endif

#ifdef LUAJIT_VERSION
	TraceLog( LOG_INFO, "%s", LUAJIT_VERSION );
#endif
}

int main( int argn, const char** argc ) {
	char basePath[ STRING_LEN ] = { '\0' };
	bool interpret_mode = false;

	if ( 1 < argn ) {
		if ( strcmp( argc[1], "--version" ) == 0 || strcmp( argc[1], "-v" ) == 0 ) {
			printVersion();
			return 1;
		}
		else if ( strcmp( argc[1], "--help" ) == 0 || strcmp( argc[1], "-h" ) == 0 ) {
			printf( "Usage: ReiLua [Options] [Directory to main.lua or main]\nOptions:\n-h --help\tThis help\n-v --version\tShow ReiLua version\n-i --interpret\tInterpret mode [File name]\n" );
			return 1;
		}
		else if ( strcmp( argc[1], "--interpret" ) == 0 || strcmp( argc[1], "-i" ) == 0 ) {
			interpret_mode = true;

			if ( 2 < argn ) {
				sprintf( basePath, "%s/%s", GetWorkingDirectory(), argc[2] );
			}
		}
		else{
			sprintf( basePath, "%s/%s", GetWorkingDirectory(), argc[1] );
		}
	}
	/* If no argument given, assume main.lua is in exe directory. */
	else {
		sprintf( basePath, "%s", GetApplicationDirectory() );
	}

	if ( interpret_mode ) {
		stateInitInterpret( argn, argc );

		lua_State* L = state->luaState;
		lua_pushcfunction( L, luaTraceback );
		int tracebackidx = lua_gettop( L );

		luaL_loadfile( L, basePath );

		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			return false;
		}
	}
	else {
		printVersion();
		stateInit( argn, argc, basePath );
		state->run = luaCallMain();

		while ( state->run ) {
			if ( WindowShouldClose() ) {
				state->run = false;
			}
			luaCallUpdate();
			luaCallDraw();
		}
		luaCallExit();
	}
	stateFree();

	return 0;
}
