#include "main.h"
#include "lua_core.h"
#include "core.h"
#include "platforms/core_desktop_sdl2.h"

void platformDefineGlobals() {
	lua_State* L = state->luaState;

	lua_getglobal( L, "RL" );
/*DOC_DEFINES_START*/
	/* Keyboard events */
	assignGlobalInt( SDL_KEYDOWN, "SDL_KEYDOWN" ); // Key pressed
	assignGlobalInt( SDL_KEYUP, "SDL_KEYUP" ); // Key released
	/* Window events */
	assignGlobalInt( SDL_WINDOWEVENT, "SDL_WINDOWEVENT" ); // Window state change
	/* Mouse events */
	assignGlobalInt( SDL_MOUSEMOTION, "SDL_MOUSEMOTION" ); // Mouse moved
	assignGlobalInt( SDL_MOUSEBUTTONDOWN, "SDL_MOUSEBUTTONDOWN" ); // Mouse button pressed
	assignGlobalInt( SDL_MOUSEBUTTONUP, "SDL_MOUSEBUTTONUP" ); // Mouse button released
	assignGlobalInt( SDL_MOUSEWHEEL, "SDL_MOUSEWHEEL" ); // Mouse wheel motion
	/* Joystick events */
	assignGlobalInt( SDL_JOYAXISMOTION, "SDL_JOYAXISMOTION" ); // Joystick axis motion
	assignGlobalInt( SDL_JOYBALLMOTION, "SDL_JOYBALLMOTION" ); // Joystick trackball motion
	assignGlobalInt( SDL_JOYHATMOTION, "SDL_JOYHATMOTION" );
	assignGlobalInt( SDL_JOYBUTTONDOWN, "SDL_JOYBUTTONDOWN" ); // 	Joystick button pressed
	assignGlobalInt( SDL_JOYBUTTONUP, "SDL_JOYBUTTONUP" ); // Joystick button released
	assignGlobalInt( SDL_JOYDEVICEADDED, "SDL_JOYDEVICEADDED" ); // Joystick connected
	assignGlobalInt( SDL_JOYDEVICEREMOVED, "SDL_JOYDEVICEREMOVED" ); // Joystick disconnected
	/* Controller events */
	assignGlobalInt( SDL_CONTROLLERAXISMOTION, "SDL_CONTROLLERAXISMOTION" ); // Controller axis motion
	assignGlobalInt( SDL_CONTROLLERBUTTONDOWN, "SDL_CONTROLLERBUTTONDOWN" ); // Controller button pressed
	assignGlobalInt( SDL_CONTROLLERBUTTONUP, "SDL_CONTROLLERBUTTONUP" ); // Controller button released
	assignGlobalInt( SDL_CONTROLLERDEVICEADDED, "SDL_CONTROLLERDEVICEADDED" ); // Controller connected
	assignGlobalInt( SDL_CONTROLLERDEVICEREMOVED, "SDL_CONTROLLERDEVICEREMOVED" ); // Controller disconnected
	assignGlobalInt( SDL_CONTROLLERDEVICEREMAPPED, "SDL_CONTROLLERDEVICEREMAPPED" ); // Controller mapping updated
	/* Touch events */
	assignGlobalInt( SDL_FINGERDOWN, "SDL_FINGERDOWN" ); // User has touched input device
	assignGlobalInt( SDL_FINGERUP, "SDL_FINGERUP" ); // User stopped touching input device
	assignGlobalInt( SDL_FINGERMOTION, "SDL_FINGERMOTION" ); // User is dragging finger on input device
	/* Gesture events */
	assignGlobalInt( SDL_DOLLARGESTURE, "SDL_DOLLARGESTURE" );
	assignGlobalInt( SDL_DOLLARRECORD, "SDL_DOLLARRECORD" );
	assignGlobalInt( SDL_MULTIGESTURE, "SDL_MULTIGESTURE" );
	/* Window states */
	assignGlobalInt( SDL_WINDOWEVENT_SHOWN, "SDL_WINDOWEVENT_SHOWN" );
	assignGlobalInt( SDL_WINDOWEVENT_HIDDEN, "SDL_WINDOWEVENT_HIDDEN" );
	assignGlobalInt( SDL_WINDOWEVENT_EXPOSED, "SDL_WINDOWEVENT_EXPOSED" );
	assignGlobalInt( SDL_WINDOWEVENT_MOVED, "SDL_WINDOWEVENT_MOVED" );
	assignGlobalInt( SDL_WINDOWEVENT_RESIZED, "SDL_WINDOWEVENT_RESIZED" );
	assignGlobalInt( SDL_WINDOWEVENT_SIZE_CHANGED, "SDL_WINDOWEVENT_SIZE_CHANGED" );
	assignGlobalInt( SDL_WINDOWEVENT_MINIMIZED, "SDL_WINDOWEVENT_MINIMIZED" );
	assignGlobalInt( SDL_WINDOWEVENT_MAXIMIZED, "SDL_WINDOWEVENT_MAXIMIZED" );
	assignGlobalInt( SDL_WINDOWEVENT_RESTORED, "SDL_WINDOWEVENT_RESTORED" );
	assignGlobalInt( SDL_WINDOWEVENT_ENTER, "SDL_WINDOWEVENT_ENTER" );
	assignGlobalInt( SDL_WINDOWEVENT_LEAVE, "SDL_WINDOWEVENT_LEAVE" );
	assignGlobalInt( SDL_WINDOWEVENT_FOCUS_GAINED, "SDL_WINDOWEVENT_FOCUS_GAINED" );
	assignGlobalInt( SDL_WINDOWEVENT_FOCUS_LOST, "SDL_WINDOWEVENT_FOCUS_LOST" );
	assignGlobalInt( SDL_WINDOWEVENT_CLOSE, "SDL_WINDOWEVENT_CLOSE" );
	assignGlobalInt( SDL_WINDOWEVENT_TAKE_FOCUS, "SDL_WINDOWEVENT_TAKE_FOCUS" );
	assignGlobalInt( SDL_WINDOWEVENT_HIT_TEST, "SDL_WINDOWEVENT_HIT_TEST" );
	/* Keyboard and mouse states */
	assignGlobalInt( SDL_RELEASED, "SDL_RELEASED" );
	assignGlobalInt( SDL_PRESSED, "SDL_PRESSED" );
	/* Joystick hat motion */
	assignGlobalInt( SDL_HAT_LEFTUP, "SDL_HAT_LEFTUP" );
	assignGlobalInt( SDL_HAT_UP, "SDL_HAT_UP" );
	assignGlobalInt( SDL_HAT_RIGHTUP, "SDL_HAT_RIGHTUP" );
	assignGlobalInt( SDL_HAT_LEFT, "SDL_HAT_LEFT" );
	assignGlobalInt( SDL_HAT_CENTERED, "SDL_HAT_CENTERED" );
	assignGlobalInt( SDL_HAT_RIGHT, "SDL_HAT_RIGHT" );
	assignGlobalInt( SDL_HAT_LEFTDOWN, "SDL_HAT_LEFTDOWN" );
	assignGlobalInt( SDL_HAT_DOWN, "SDL_HAT_DOWN" );
	assignGlobalInt( SDL_HAT_RIGHTDOWN, "SDL_HAT_RIGHTDOWN" );
/*DOC_DEFINES_END*/
	lua_pop( L, -1 );
}

/* Functions. */

/*
## SDL Core - Input-related functions: keyboard.
*/

/*
> keyName = RL.GetKeyName( int key )

Use this function to get a human-readable name for a key. If the key doesn't have a name, this function returns an empty string ("").

- Success return string
*/
int lcoreGetKeyName( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushstring( L, SDL_GetKeyName( key ) );

	return 1;
}

/*
> keyName = RL.GetScancodeFromKey( int key )

Use this function to get the scancode corresponding to the given key code according to the current keyboard layout.

- Success return int
*/
int lcoreGetScancodeFromKey( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, SDL_GetScancodeFromKey( key ) );

	return 1;
}

/* Events. */

/*
## SDL Events
*/

/* This function is not thread safe so we don't use Lua inside it directly. It only adds events to another queue. */
static int SDLEventFilter( void* userdata, SDL_Event* event ) {
	/* SDL_EVENT_POLL_SENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */
	if ( event->type != SDL_QUIT && event->type != 0x7F00 && state->SDL_eventQueueLen < PLATFORM_SDL_EVENT_QUEUE_LEN ) {
		state->SDL_eventQueue[ state->SDL_eventQueueLen ] = *event;
		state->SDL_eventQueueLen++;

		// printf( "event %u state->SDL_eventQueueLen %d\n", event->type, state->SDL_eventQueueLen );
	}
}

static void platformRegisterEvents() {
	/* SDL Warning:	Be very careful of what you do in the event filter function, as it may run in a different thread! */
	SDL_AddEventWatch( SDLEventFilter, NULL );
}

static void platformSendEvents() {
	lua_State* L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	/* If RL.event is not defined, we don't need to proceed. */
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "event" );

	if ( !lua_isfunction( L, -1 ) ) {
		state->SDL_eventQueueLen = 0;
		return;
	}

	for ( int i = 0; i < state->SDL_eventQueueLen; i++ ) {
		bool call = false;
		lua_getglobal( L, "RL" );
		lua_getfield( L, -1, "event" );

		SDL_Event event = state->SDL_eventQueue[i];

		switch ( event.type ) {
/*
> SDL_KeyboardEvent = { int type, int timestamp, int state, int repeat, int scancode, int sym, int mod }

Event occurs whenever a user presses or releases a button on a keyboard. Type SDL_KEYUP or SDL_KEYDOWN
*/
		case SDL_KEYUP:
		case SDL_KEYDOWN:
		{
			lua_createtable( L, 7, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.key.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.key.state );
			lua_setfield( L, -2, "state" );
			lua_pushinteger( L, event.key.repeat );
			lua_setfield( L, -2, "repeating" ); /* repeat is Lua keyword. */
			lua_pushinteger( L, event.key.keysym.scancode );
			lua_setfield( L, -2, "scancode" );
			lua_pushinteger( L, event.key.keysym.sym );
			lua_setfield( L, -2, "sym" );
			lua_pushinteger( L, event.key.keysym.mod );
			lua_setfield( L, -2, "mod" );
			call = true;
		}
		break;
/*
> SDL_WindowEvent = { int type, int timestamp, int event, int data1, int data2 }

Event occurs when an event of type SDL_WINDOWEVENT is reported. Type SDL_WINDOWEVENT
*/
		case SDL_WINDOWEVENT:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.window.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.window.event );
			lua_setfield( L, -2, "event" );
			lua_pushinteger( L, event.window.data1 );
			lua_setfield( L, -2, "data1" );
			lua_pushinteger( L, event.window.data2 );
			lua_setfield( L, -2, "data2" );
			call = true;
		}
		break;
/*
> SDL_MouseMotionEvent = { int type, int timestamp, int which, int state, int x, int y, int xrel, int yrel }

Event occurs whenever a user moves the mouse within the application window or when SDL_WarpMouseInWindow() is called. Type SDL_MOUSEMOTION
*/
		case SDL_MOUSEMOTION:
		{
			lua_createtable( L, 8, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.motion.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.motion.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.motion.state );
			lua_setfield( L, -2, "state" );
			lua_pushinteger( L, event.motion.x );
			lua_setfield( L, -2, "x" );
			lua_pushinteger( L, event.motion.y );
			lua_setfield( L, -2, "y" );
			lua_pushinteger( L, event.motion.xrel );
			lua_setfield( L, -2, "xrel" );
			lua_pushinteger( L, event.motion.yrel );
			lua_setfield( L, -2, "yrel" );
			call = true;
		}
		break;
/*
> SDL_MouseButtonEvent = { int type, int timestamp, int which, int button, int state, int x, int y }

Event occurs whenever a user presses or releases a button on a mouse. Type SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP
*/
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			lua_createtable( L, 7, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.button.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.button.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.button.button );
			lua_setfield( L, -2, "button" );
			lua_pushinteger( L, event.button.state );
			lua_setfield( L, -2, "state" );
			lua_pushinteger( L, event.button.x );
			lua_setfield( L, -2, "x" );
			lua_pushinteger( L, event.button.y );
			lua_setfield( L, -2, "y" );
			call = true;
		}
		break;
/*
> SDL_MouseWheelEvent = { int type, int timestamp, int which, int x, int y }

Event occurs whenever a user moves the mouse wheel. Type SDL_MOUSEWHEEL
*/
		case SDL_MOUSEWHEEL:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.wheel.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.wheel.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.wheel.x );
			lua_setfield( L, -2, "x" );
			lua_pushinteger( L, event.wheel.y );
			lua_setfield( L, -2, "y" );
			call = true;
		}
		break;
/*
> SDL_JoyAxisEvent = { int type, int timestamp, int which, int axis, int value }

Event occurs whenever a user moves an axis on the joystick. Type SDL_JOYAXISMOTION
*/
		case SDL_JOYAXISMOTION:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jaxis.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jaxis.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.jaxis.axis );
			lua_setfield( L, -2, "axis" );
			lua_pushinteger( L, event.jaxis.value );
			lua_setfield( L, -2, "value" );
			call = true;
		}
		break;
/*
> SDL_JoyBallEvent = { int type, int timestamp, int which, int ball, int xrel, int yrel }

Event occurs when a user moves a trackball on the joystick. Type SDL_JOYBALLMOTION
*/
		case SDL_JOYBALLMOTION:
		{
			lua_createtable( L, 6, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jball.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jball.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.jball.ball );
			lua_setfield( L, -2, "ball" );
			lua_pushinteger( L, event.jball.xrel );
			lua_setfield( L, -2, "xrel" );
			lua_pushinteger( L, event.jball.yrel );
			lua_setfield( L, -2, "yrel" );
			call = true;
		}
		break;
/*
> SDL_JoyHatEvent = { int type, int timestamp, int which, int hat, int value }

Event occurs whenever a user moves a hat on the joystick. Type SDL_JOYHATMOTION
*/
		case SDL_JOYHATMOTION:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jhat.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jhat.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.jhat.hat );
			lua_setfield( L, -2, "hat" );
			lua_pushinteger( L, event.jhat.value );
			lua_setfield( L, -2, "value" );
			call = true;
		}
		break;
/*
> SDL_JoyButtonEvent = { int type, int timestamp, int which, int button, int state }

Event occurs whenever a user presses or releases a button on a joystick. Type SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP
*/
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jbutton.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jbutton.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.jbutton.button );
			lua_setfield( L, -2, "button" );
			lua_pushinteger( L, event.jbutton.state );
			lua_setfield( L, -2, "state" );
			call = true;
		}
		break;
/*
> SDL_JoyDeviceEvent = { int type, int timestamp, int which }

Event occurs whenever a user connects or disconnects a joystick. Type SDL_JOYDEVICEADDED or SDL_JOYDEVICEREMOVED
*/
		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
		{
			lua_createtable( L, 3, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jdevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jdevice.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_ControllerAxisEvent = { int type, int timestamp, int which, int axis, int value }

Event occurs whenever a user moves an axis on the controller. Type SDL_CONTROLLERAXISMOTION
*/
		case SDL_CONTROLLERAXISMOTION:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.caxis.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.caxis.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.caxis.axis );
			lua_setfield( L, -2, "axis" );
			lua_pushinteger( L, event.caxis.value );
			lua_setfield( L, -2, "value" );
			call = true;
		}
		break;
/*
> SDL_ControllerButtonEvent = { int type, int timestamp, int which, int button, int state }

Event occurs whenever a user presses or releases a button on a controller. Type SDL_CONTROLLERBUTTONDOWN or SDL_CONTROLLERBUTTONUP
*/
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.cbutton.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.cbutton.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.cbutton.button );
			lua_setfield( L, -2, "button" );
			lua_pushinteger( L, event.cbutton.state );
			lua_setfield( L, -2, "state" );
			call = true;
		}
		break;
/*
> SDL_ControllerDeviceEvent = { int type, int timestamp, int which }

Event occurs whenever a user connects, disconnects or remaps a controller. Type SDL_CONTROLLERDEVICEADDED, SDL_CONTROLLERDEVICEREMOVED or SDL_CONTROLLERDEVICEREMAPPED
*/
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
		case SDL_CONTROLLERDEVICEREMAPPED:
		{
			lua_createtable( L, 3, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.cdevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.cdevice.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_TouchFingerEvent = { int type, int timestamp, int touchId, int fingerId, float x, float y, float dx, float dy, float pressure }

Event occurs when an event of type SDL_FINGERMOTION, SDL_FINGERDOWN, or SDL_FINGERUP is reported. Type SDL_FINGERMOTION, SDL_FINGERDOWN or SDL_FINGERUP
*/
		case SDL_FINGERMOTION:
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.tfinger.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.tfinger.touchId );
			lua_setfield( L, -2, "touchId" );
			lua_pushinteger( L, event.tfinger.fingerId );
			lua_setfield( L, -2, "fingerId" );
			lua_pushnumber( L, event.tfinger.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.tfinger.y );
			lua_setfield( L, -2, "y" );
			lua_pushnumber( L, event.tfinger.dx );
			lua_setfield( L, -2, "dx" );
			lua_pushnumber( L, event.tfinger.dy );
			lua_setfield( L, -2, "dy" );
			lua_pushnumber( L, event.tfinger.pressure );
			lua_setfield( L, -2, "pressure" );
			call = true;
		}
		break;
/*
> SDL_MultiGestureEvent = { int type, int timestamp, int touchId, float dTheta, float dDist, float x, float y, int numFingers }

Event occurs when type SDL_MULTIGESTURE is reported. Type SDL_MULTIGESTURE
*/
		case SDL_MULTIGESTURE:
		{
			lua_createtable( L, 8, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.mgesture.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.mgesture.touchId );
			lua_setfield( L, -2, "touchId" );
			lua_pushnumber( L, event.mgesture.dTheta );
			lua_setfield( L, -2, "dTheta" );
			lua_pushnumber( L, event.mgesture.dDist );
			lua_setfield( L, -2, "dDist" );
			lua_pushnumber( L, event.mgesture.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.mgesture.y );
			lua_setfield( L, -2, "y" );
			lua_pushinteger( L, event.mgesture.numFingers );
			lua_setfield( L, -2, "numFingers" );
			call = true;
		}
		break;
/*
> SDL_DollarGestureEvent = { int type, int timestamp, int touchId, int gestureId, int numFingers, float error, float x, float y }

Event occurs an event of type SDL_DOLLARGESTURE or SDL_DOLLARRECORD is reported. Type SDL_DOLLARGESTURE or SDL_DOLLARRECORD
*/
		case SDL_DOLLARGESTURE:
		case SDL_DOLLARRECORD:
		{
			lua_createtable( L, 8, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.dgesture.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.dgesture.touchId );
			lua_setfield( L, -2, "touchId" );
			lua_pushinteger( L, event.dgesture.gestureId );
			lua_setfield( L, -2, "gestureId" );
			lua_pushinteger( L, event.dgesture.numFingers );
			lua_setfield( L, -2, "numFingers" );
			lua_pushnumber( L, event.dgesture.error );
			lua_setfield( L, -2, "error" );
			lua_pushnumber( L, event.dgesture.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.dgesture.y );
			lua_setfield( L, -2, "y" );
			call = true;
		}
		break;
/* End of events. */
		default:
		break;
		}

		if ( call ) {
			if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
				TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
				state->run = false;
			}
		}
		lua_pop( L, -1 );
	}
	state->SDL_eventQueueLen = 0;
}

void luaPlatformRegister() {
	lua_State* L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Input-related functions: keyboard. */
	assingGlobalFunction( "GetKeyName", lcoreGetKeyName );
	assingGlobalFunction( "GetScancodeFromKey", lcoreGetScancodeFromKey );

	lua_pop( L, -1 );

#ifdef LUA_EVENTS
	platformRegisterEvents();
#endif
}
