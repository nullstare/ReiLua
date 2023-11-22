#include "main.h"
#include "lua_core.h"
#include "core.h"
#include "platforms/core_desktop_sdl.h"

static void definePlatformGlobals() {
	lua_State *L = state->luaState;

	lua_getglobal( L, "RL" );

		/* KeyboardKey */
	assignGlobalInt( SDL_KEYDOWN, "SDL_KEYDOWN" ); // key pressed
	assignGlobalInt( SDL_KEYUP, "SDL_KEYUP" ); // key released
	assignGlobalInt( SDL_PRESSED, "SDL_PRESSED" ); // key pressed
	assignGlobalInt( SDL_RELEASED, "SDL_RELEASED" ); // key released
		/* Keyboard Events. */
	assignGlobalInt( SDL_WINDOW_EVENT, "SDL_WINDOW_EVENT" ); // SDL Window Event
	assignGlobalInt( SDL_KEYBOARD_EVENT, "SDL_KEYBOARD_EVENT" ); // SDL Keyboard Event

	lua_pop( L, -1 );
}

/* Functions. */

/*
## Core - Input-related functions: keyboard.
*/

/*
> keyName = RL.GetKeyName( int key )

Use this function to get a human-readable name for a key. If the key doesn't have a name, this function returns an empty string ("").

- Success return string
*/
int lcoreGetKeyName( lua_State *L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushstring( L, SDL_GetKeyName( key ) );

	return 1;
}

/*
> keyName = RL.GetScancodeFromKey( int key )

Use this function to get the scancode corresponding to the given key code according to the current keyboard layout.

- Success return int
*/
int lcoreGetScancodeFromKey( lua_State *L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, SDL_GetScancodeFromKey( key ) );

	return 1;
}

static void luaPlatformRegister() {
	lua_State *L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Input-related functions: keyboard. */
	assingGlobalFunction( "GetKeyName", lcoreGetKeyName );
	assingGlobalFunction( "GetScancodeFromKey", lcoreGetScancodeFromKey );

	lua_pop( L, -1 );
}

/* Events. */

//TODO Thinking of different implementation since this could run on different thread than Lua.
static int SDLEventFilter( void *userdata, SDL_Event *event ) {
	/* Don't handle events if exiting. Prevent segfault. */
	if ( event->type == SDL_QUIT || !state->run ) {
		return 0;
	}
	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

	if ( !lua_isfunction( L, -1 ) ) {
		return 0;
	}

	switch ( event->type ) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			lua_createtable( L, 7, 0 );
			lua_pushinteger( L, SDL_KEYBOARD_EVENT );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event->key.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event->key.state );
			lua_setfield( L, -2, "state" );
			lua_pushinteger( L, event->key.repeat );
			lua_setfield( L, -2, "repeat" );
			lua_pushinteger( L, event->key.keysym.scancode );
			lua_setfield( L, -2, "scancode" );
			lua_pushinteger( L, event->key.keysym.sym );
			lua_setfield( L, -2, "sym" );
			lua_pushinteger( L, event->key.keysym.mod );
			lua_setfield( L, -2, "mod" );

			if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
				TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
				state->run = false;
			}
			lua_pop( L, -1 );
		}
		break;
		default:
		break;
	}
}

static void platformRegisterEvents() {
	/* Probably sould not use this since. SDL Warning:
	Be very careful of what you do in the event filter function, as it may run in a different thread!
	There has already being some undefined behavior with Lua! :o */
	// SDL_AddEventWatch( SDLEventFilter, NULL );
}
