#include "main.h"
#include "lua_core.h"
#include "core.h"
#include "platforms/core_desktop.h"

static void platformDefineGlobals() {
	lua_State *L = state->luaState;

	lua_getglobal( L, "RL" );

		/* KeyboardKey */
	assignGlobalInt( GLFW_KEY_UNKNOWN, "GLFW_KEY_UNKNOWN" ); // Key: Unknown
		/* GLFW API tokens. */
	assignGlobalInt( GLFW_RELEASE, "GLFW_RELEASE" ); // The key or mouse button was released
	assignGlobalInt( GLFW_PRESS, "GLFW_PRESS" ); // The key or mouse button was pressed
	assignGlobalInt( GLFW_REPEAT, "GLFW_REPEAT" ); // The key was held down until it repeated
	assignGlobalInt( GLFW_CONNECTED, "GLFW_CONNECTED" ); // Joystick connected
	assignGlobalInt( GLFW_DISCONNECTED, "GLFW_DISCONNECTED" ); // Joystick disconnected
		/* Window Events. */
	assignGlobalInt( GLFW_WINDOW_SIZE_EVENT, "GLFW_WINDOW_SIZE_EVENT" ); // GLFW event window size changed
	assignGlobalInt( GLFW_WINDOW_MAXIMIZE_EVENT, "GLFW_WINDOW_MAXIMIZE_EVENT" ); // GLFW event window maximize
	assignGlobalInt( GLFW_WINDOW_ICONYFY_EVENT, "GLFW_WINDOW_ICONYFY_EVENT" ); // GLFW event window iconify
	assignGlobalInt( GLFW_WINDOW_FOCUS_EVENT, "GLFW_WINDOW_FOCUS_EVENT" ); // GLFW event window focus
	assignGlobalInt( GLFW_WINDOW_DROP_EVENT, "GLFW_WINDOW_DROP_EVENT" ); // GLFW event window drop
	/* Input Events. */
	assignGlobalInt( GLFW_KEY_EVENT, "GLFW_KEY_EVENT" ); // GLFW event keyboard key
	assignGlobalInt( GLFW_CHAR_EVENT, "GLFW_CHAR_EVENT" ); // GLFW event Unicode character
	assignGlobalInt( GLFW_MOUSE_BUTTON_EVENT, "GLFW_MOUSE_BUTTON_EVENT" ); // GLFW event mouse button
	assignGlobalInt( GLFW_MOUSE_CURSOR_POS_EVENT, "GLFW_MOUSE_CURSOR_POS_EVENT" ); // GLFW event cursor position
	assignGlobalInt( GLFW_MOUSE_SCROLL_EVENT, "GLFW_MOUSE_SCROLL_EVENT" ); // GLFW event mouse scroll
	assignGlobalInt( GLFW_CURSOR_ENTER_EVENT, "GLFW_CURSOR_ENTER_EVENT" ); // GLFW event cursor enter/leave
	assignGlobalInt( GLFW_JOYSTICK_EVENT, "GLFW_JOYSTICK_EVENT" ); // GLFW event joystick

	lua_pop( L, -1 );
}

/* Functions. */

/*
## Core - Input-related functions: keyboard.
*/

/*
> keyName = RL.GetKeyName( int key, int scancode )

This function returns the name of the specified printable key, encoded as UTF-8.
This is typically the character that key would produce without any modifier keys,
intended for displaying key bindings to the user. For dead keys, it is typically
the diacritic it would add to a character.

Do not use this function for text input. You will break text input for many
languages even if it happens to work for yours.

If the key is KEY_UNKNOWN, the scancode is used to identify the key,
otherwise the scancode is ignored. If you specify a non-printable key,
or KEY_UNKNOWN and a scancode that maps to a non-printable key,
this function returns nil but does not emit an error.

- Success return string or nil
*/
int lcoreGetKeyName( lua_State *L ) {
	int key = luaL_checkinteger( L, 1 );
	int scancode = luaL_checkinteger( L, 2 );

	const char *keyName = glfwGetKeyName( key, scancode );

	if ( keyName != NULL ) {
		lua_pushstring( L, keyName );
	}
	else {
		lua_pushnil( L );
	}

	return 1;
}

/*
> scancode = RL.GetKeyScancode( int key )

This function returns the platform-specific scancode of the specified key.
If the key is KEY_UNKNOWN or does not exist on the keyboard this method will return -1.

- Success return int
*/
int lcoreGetKeyScancode( lua_State *L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, glfwGetKeyScancode( key ) );

	return 1;
}

static void luaPlatformRegister() {
	lua_State *L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Input-related functions: keyboard. */
	assingGlobalFunction( "GetKeyName", lcoreGetKeyName );
	assingGlobalFunction( "GetKeyScancode", lcoreGetKeyScancode );

	lua_pop( L, -1 );
}

/* Events. */

/* Window events. */

static void windowSizeEvent( GLFWwindow *window, int width, int height ) {
	/* Pass through to raylib callback. */
	state->raylibWindowSizeCallback( window, width, height );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 3, 0 );
		lua_pushinteger( L, GLFW_WINDOW_SIZE_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, width );
		lua_setfield( L, -2, "width" );
		lua_pushinteger( L, height );
		lua_setfield( L, -2, "height" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

#if !defined( PLATFORM_WEB )

static void windowMaximizeEvent( GLFWwindow *window, int maximized ) {
	/* Pass through to raylib callback. */
	state->raylibWindowMaximizeCallback( window, maximized );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushinteger( L, GLFW_WINDOW_MAXIMIZE_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, maximized );
		lua_setfield( L, -2, "maximized" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

#endif

static void windowIconyfyEvent( GLFWwindow *window, int iconified ) {
	/* Pass through to raylib callback. */
	state->raylibWindowIconifyCallback( window, iconified );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushinteger( L, GLFW_WINDOW_ICONYFY_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, iconified );
		lua_setfield( L, -2, "iconified" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void windowFocusEvent( GLFWwindow *window, int focused ) {
	/* Pass through to raylib callback. */
	state->raylibWindowFocusCallback( window, focused );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushinteger( L, GLFW_WINDOW_FOCUS_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, focused );
		lua_setfield( L, -2, "focused" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void windowDropEvent( GLFWwindow *window, int count, const char **paths ) {
	/* Pass through to raylib callback. */
	state->raylibWindowDropCallback( window, count, paths );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 3, 0 );
		lua_pushinteger( L, GLFW_WINDOW_DROP_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, count );
		lua_setfield( L, -2, "count" );

		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; ++i ) {
			lua_pushstring( L, paths[i] );
			lua_rawseti( L, -2, i+1 );
		}
		lua_setfield( L, -2, "paths" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

/* Input events. */

static void keyInputEvent( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	/* Pass through to raylib callback. */
	state->raylibKeyCallback( window, key, scancode, action, mods );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 5, 0 );
		lua_pushinteger( L, GLFW_KEY_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, key );
		lua_setfield( L, -2, "key" );
		lua_pushinteger( L, scancode );
		lua_setfield( L, -2, "scancode" );
		lua_pushinteger( L, action );
		lua_setfield( L, -2, "action" );
		lua_pushinteger( L, mods );
		lua_setfield( L, -2, "mods" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void charInputEvent( GLFWwindow* window, unsigned int key ) {
	/* Pass through to raylib callback. */
	state->raylibCharCallback( window, key );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushinteger( L, GLFW_CHAR_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, key );
		lua_setfield( L, -2, "key" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void mouseButtonInputEvent( GLFWwindow* window, int button, int action, int mods ) {
	/* Pass through to raylib callback. */
	state->raylibMouseButtonCallback( window, button, action, mods );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 4, 0 );
		lua_pushinteger( L, GLFW_MOUSE_BUTTON_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, button );
		lua_setfield( L, -2, "button" );
		lua_pushinteger( L, action );
		lua_setfield( L, -2, "action" );
		lua_pushinteger( L, mods );
		lua_setfield( L, -2, "mods" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void mouseCursorPosInputEvent( GLFWwindow* window, double x, double y ) {
	/* Pass through to raylib callback. */
	state->raylibMouseCursorPosCallback( window, x, y );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 3, 0 );
		lua_pushinteger( L, GLFW_MOUSE_CURSOR_POS_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushnumber( L, x );
		lua_setfield( L, -2, "x" );
		lua_pushnumber( L, y );
		lua_setfield( L, -2, "y" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void mouseScrollInputEvent( GLFWwindow* window, double xoffset, double yoffset ) {
	/* Pass through to raylib callback. */
	state->raylibMouseScrollCallback( window, xoffset, yoffset );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 3, 0 );
		lua_pushinteger( L, GLFW_MOUSE_SCROLL_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushnumber( L, xoffset );
		lua_setfield( L, -2, "xoffset" );
		lua_pushnumber( L, yoffset );
		lua_setfield( L, -2, "yoffset" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void cursorEnterInputEvent( GLFWwindow* window, int enter ) {
	/* Pass through to raylib callback. */
	state->raylibCursorEnterCallback( window, enter );

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushinteger( L, GLFW_CURSOR_ENTER_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, enter );
		lua_setfield( L, -2, "enter" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void joystickInputEvent( int jid, int event ) {
	/* Pass through to raylib callback. */
	if ( state->raylibJoystickCallback != NULL ) {
		state->raylibJoystickCallback( jid, event );
	}

	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

    if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 3, 0 );
		lua_pushinteger( L, GLFW_JOYSTICK_EVENT );
		lua_setfield( L, -2, "type" );
		lua_pushinteger( L, jid );
		lua_setfield( L, -2, "jid" );
		lua_pushinteger( L, event );
		lua_setfield( L, -2, "event" );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
        }
    }
	lua_pop( L, -1 );
}

static void platformRegisterEvents() {
	/* Window events. */
	state->raylibWindowSizeCallback = glfwSetWindowSizeCallback( GetWindowHandle(), windowSizeEvent );
#if !defined( PLATFORM_WEB )
	state->raylibWindowMaximizeCallback = glfwSetWindowMaximizeCallback( GetWindowHandle(), windowMaximizeEvent );
#endif
	state->raylibWindowIconifyCallback = glfwSetWindowIconifyCallback( GetWindowHandle(), windowIconyfyEvent );
	state->raylibWindowFocusCallback = glfwSetWindowFocusCallback( GetWindowHandle(), windowFocusEvent );
	state->raylibWindowDropCallback = glfwSetDropCallback( GetWindowHandle(), windowDropEvent );

	/* Input events. */
	state->raylibKeyCallback = glfwSetKeyCallback( GetWindowHandle(), keyInputEvent );
	state->raylibCharCallback = glfwSetCharCallback( GetWindowHandle(), charInputEvent );
	state->raylibMouseButtonCallback = glfwSetMouseButtonCallback( GetWindowHandle(), mouseButtonInputEvent );
	state->raylibMouseCursorPosCallback = glfwSetCursorPosCallback( GetWindowHandle(), mouseCursorPosInputEvent );
	state->raylibMouseScrollCallback = glfwSetScrollCallback( GetWindowHandle(), mouseScrollInputEvent );
	state->raylibCursorEnterCallback = glfwSetCursorEnterCallback( GetWindowHandle(), cursorEnterInputEvent );
	state->raylibJoystickCallback = glfwSetJoystickCallback( joystickInputEvent );
}
