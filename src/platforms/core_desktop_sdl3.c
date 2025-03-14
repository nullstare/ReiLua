#include "main.h"
#include "lua_core.h"
#include "core.h"
#include "platforms/core_desktop_sdl3.h"

void platformDefineGlobals() {
	lua_State* L = state->luaState;

	lua_getglobal( L, "RL" );
/*DOC_DEFINES_START*/
	/* Application events */
	assignGlobalInt( SDL_EVENT_QUIT, "SDL_EVENT_QUIT" ); // User-requested quit
	/* Display events */
	assignGlobalInt( SDL_EVENT_DISPLAY_ORIENTATION, "SDL_EVENT_DISPLAY_ORIENTATION" ); // Display orientation has changed to data1
	assignGlobalInt( SDL_EVENT_DISPLAY_ADDED, "SDL_EVENT_DISPLAY_ADDED" ); // Display has been added to the system
	assignGlobalInt( SDL_EVENT_DISPLAY_REMOVED, "SDL_EVENT_DISPLAY_REMOVED" ); // Display has been removed from the system
	assignGlobalInt( SDL_EVENT_DISPLAY_MOVED, "SDL_EVENT_DISPLAY_MOVED" ); // Display has changed position
	assignGlobalInt( SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, "SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED" ); // Display has changed desktop mode
	assignGlobalInt( SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, "SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED" ); // Display has changed current mode
	assignGlobalInt( SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, "SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED" ); // Display has changed content scale
	assignGlobalInt( SDL_EVENT_DISPLAY_FIRST, "SDL_EVENT_DISPLAY_FIRST" );
	assignGlobalInt( SDL_EVENT_DISPLAY_LAST, "SDL_EVENT_DISPLAY_LAST" );
	/* Window events */
	assignGlobalInt( SDL_EVENT_WINDOW_SHOWN, "SDL_EVENT_WINDOW_SHOWN" ); // Window has been shown
	assignGlobalInt( SDL_EVENT_WINDOW_HIDDEN, "SDL_EVENT_WINDOW_HIDDEN" ); // Window has been hidden
	assignGlobalInt( SDL_EVENT_WINDOW_EXPOSED, "SDL_EVENT_WINDOW_EXPOSED" ); // Window has been exposed and should be redrawn, and can be redrawn directly from event watchers for this event
	assignGlobalInt( SDL_EVENT_WINDOW_MOVED, "SDL_EVENT_WINDOW_MOVED" ); // Window has been moved to data1, data2
	assignGlobalInt( SDL_EVENT_WINDOW_RESIZED, "SDL_EVENT_WINDOW_RESIZED" ); // Window has been resized to data1xdata2
	assignGlobalInt( SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, "SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED" ); // The pixel size of the window has changed to data1xdata2
	assignGlobalInt( SDL_EVENT_WINDOW_METAL_VIEW_RESIZED, "SDL_EVENT_WINDOW_METAL_VIEW_RESIZED" ); // The pixel size of a Metal view associated with the window has changed
	assignGlobalInt( SDL_EVENT_WINDOW_MINIMIZED, "SDL_EVENT_WINDOW_MINIMIZED" ); // Window has been minimized
	assignGlobalInt( SDL_EVENT_WINDOW_MAXIMIZED, "SDL_EVENT_WINDOW_MAXIMIZED" ); // Window has been maximized
	assignGlobalInt( SDL_EVENT_WINDOW_RESTORED, "SDL_EVENT_WINDOW_RESTORED" ); // Window has been restored to normal size and position
	assignGlobalInt( SDL_EVENT_WINDOW_MOUSE_ENTER, "SDL_EVENT_WINDOW_MOUSE_ENTER" ); // Window has gained mouse focus
	assignGlobalInt( SDL_EVENT_WINDOW_MOUSE_LEAVE, "SDL_EVENT_WINDOW_MOUSE_LEAVE" ); // Window has lost mouse focus
	assignGlobalInt( SDL_EVENT_WINDOW_FOCUS_GAINED, "SDL_EVENT_WINDOW_FOCUS_GAINED" ); // Window has gained keyboard focus
	assignGlobalInt( SDL_EVENT_WINDOW_FOCUS_LOST, "SDL_EVENT_WINDOW_FOCUS_LOST" ); // Window has lost keyboard focus
	assignGlobalInt( SDL_EVENT_WINDOW_CLOSE_REQUESTED, "SDL_EVENT_WINDOW_CLOSE_REQUESTED" ); // The window manager requests that the window be closed
	assignGlobalInt( SDL_EVENT_WINDOW_HIT_TEST, "SDL_EVENT_WINDOW_HIT_TEST" ); // Window had a hit test that wasn't SDL_HITTEST_NORMAL
	assignGlobalInt( SDL_EVENT_WINDOW_ICCPROF_CHANGED, "SDL_EVENT_WINDOW_ICCPROF_CHANGED" ); // The ICC profile of the window's display has changed
	assignGlobalInt( SDL_EVENT_WINDOW_DISPLAY_CHANGED, "SDL_EVENT_WINDOW_DISPLAY_CHANGED" ); // Window has been moved to display data1
	assignGlobalInt( SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, "SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED" ); // Window display scale has been changed
	assignGlobalInt( SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, "SDL_EVENT_WINDOW_SAFE_AREA_CHANGED" ); // The window safe area has been changed
	assignGlobalInt( SDL_EVENT_WINDOW_OCCLUDED, "SDL_EVENT_WINDOW_OCCLUDED" ); // The window has been occluded
	assignGlobalInt( SDL_EVENT_WINDOW_ENTER_FULLSCREEN, "SDL_EVENT_WINDOW_ENTER_FULLSCREEN" ); // The window has entered fullscreen mode
	assignGlobalInt( SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, "SDL_EVENT_WINDOW_LEAVE_FULLSCREEN" ); // The window has left fullscreen mode
	assignGlobalInt( SDL_EVENT_WINDOW_DESTROYED, "SDL_EVENT_WINDOW_DESTROYED" ); // The window with the associated ID is being or has been destroyed. If this message is being handled in an event watcher, the window handle is still valid and can still be used to retrieve any properties associated with the window. Otherwise, the handle has already been destroyed and all resources associated with it are invalid
	assignGlobalInt( SDL_EVENT_WINDOW_HDR_STATE_CHANGED, "SDL_EVENT_WINDOW_HDR_STATE_CHANGED" ); // Window HDR properties have changed
	assignGlobalInt( SDL_EVENT_WINDOW_FIRST, "SDL_EVENT_WINDOW_FIRST" );
	assignGlobalInt( SDL_EVENT_WINDOW_LAST, "SDL_EVENT_WINDOW_LAST" );
	/* Keyboard events */
	assignGlobalInt( SDL_EVENT_KEY_DOWN, "SDL_EVENT_KEY_DOWN" ); // Key pressed
	assignGlobalInt( SDL_EVENT_KEY_UP, "SDL_EVENT_KEY_UP" ); // Key released
	assignGlobalInt( SDL_EVENT_TEXT_EDITING, "SDL_EVENT_TEXT_EDITING" ); // Keyboard text editing (composition)
	assignGlobalInt( SDL_EVENT_TEXT_INPUT, "SDL_EVENT_TEXT_INPUT" ); // Keyboard text input
	assignGlobalInt( SDL_EVENT_KEYMAP_CHANGED, "SDL_EVENT_KEYMAP_CHANGED" ); // Keymap changed due to a system event such as an	input language or keyboard layout change.
	assignGlobalInt( SDL_EVENT_KEYBOARD_ADDED, "SDL_EVENT_KEYBOARD_ADDED" ); // A new keyboard has been inserted into the system
	assignGlobalInt( SDL_EVENT_KEYBOARD_REMOVED, "SDL_EVENT_KEYBOARD_REMOVED" ); // A keyboard has been removed
	assignGlobalInt( SDL_EVENT_TEXT_EDITING_CANDIDATES, "SDL_EVENT_TEXT_EDITING_CANDIDATES" ); // Keyboard text editing candidates
	/* Mouse events */
	assignGlobalInt( SDL_EVENT_MOUSE_MOTION, "SDL_EVENT_MOUSE_MOTION" ); // Mouse moved
	assignGlobalInt( SDL_EVENT_MOUSE_BUTTON_DOWN, "SDL_EVENT_MOUSE_BUTTON_DOWN" ); // Mouse button pressed
	assignGlobalInt( SDL_EVENT_MOUSE_BUTTON_UP, "SDL_EVENT_MOUSE_BUTTON_UP" ); // Mouse button released
	assignGlobalInt( SDL_EVENT_MOUSE_WHEEL, "SDL_EVENT_MOUSE_WHEEL" ); // Mouse wheel motion
	assignGlobalInt( SDL_EVENT_MOUSE_ADDED, "SDL_EVENT_MOUSE_ADDED" ); // A new mouse has been inserted into the system
	assignGlobalInt( SDL_EVENT_MOUSE_REMOVED, "SDL_EVENT_MOUSE_REMOVED" ); // A mouse has been removed
	/* Joystick events */
	assignGlobalInt( SDL_EVENT_JOYSTICK_AXIS_MOTION, "SDL_EVENT_JOYSTICK_AXIS_MOTION" ); // Joystick axis motion
	assignGlobalInt( SDL_EVENT_JOYSTICK_BALL_MOTION, "SDL_EVENT_JOYSTICK_BALL_MOTION" ); // Joystick trackball motion
	assignGlobalInt( SDL_EVENT_JOYSTICK_HAT_MOTION, "SDL_EVENT_JOYSTICK_HAT_MOTION" ); // Joystick hat position change
	assignGlobalInt( SDL_EVENT_JOYSTICK_BUTTON_DOWN, "SDL_EVENT_JOYSTICK_BUTTON_DOWN" ); // Joystick button pressed
	assignGlobalInt( SDL_EVENT_JOYSTICK_BUTTON_UP, "SDL_EVENT_JOYSTICK_BUTTON_UP" ); // Joystick button released
	assignGlobalInt( SDL_EVENT_JOYSTICK_ADDED, "SDL_EVENT_JOYSTICK_ADDED" ); // A new joystick has been inserted into the system
	assignGlobalInt( SDL_EVENT_JOYSTICK_REMOVED, "SDL_EVENT_JOYSTICK_REMOVED" ); // An opened joystick has been removed
	assignGlobalInt( SDL_EVENT_JOYSTICK_BATTERY_UPDATED, "SDL_EVENT_JOYSTICK_BATTERY_UPDATED" ); // Joystick battery level change
	assignGlobalInt( SDL_EVENT_JOYSTICK_UPDATE_COMPLETE, "SDL_EVENT_JOYSTICK_UPDATE_COMPLETE" ); // Joystick update is complete
	/* Gamepad events */
	assignGlobalInt( SDL_EVENT_GAMEPAD_AXIS_MOTION, "SDL_EVENT_GAMEPAD_AXIS_MOTION" ); // Gamepad axis motion
	assignGlobalInt( SDL_EVENT_GAMEPAD_BUTTON_DOWN, "SDL_EVENT_GAMEPAD_BUTTON_DOWN" ); // Gamepad button pressed
	assignGlobalInt( SDL_EVENT_GAMEPAD_BUTTON_UP, "SDL_EVENT_GAMEPAD_BUTTON_UP" ); // Gamepad button released
	assignGlobalInt( SDL_EVENT_GAMEPAD_ADDED, "SDL_EVENT_GAMEPAD_ADDED" ); // A new gamepad has been inserted into the system
	assignGlobalInt( SDL_EVENT_GAMEPAD_REMOVED, "SDL_EVENT_GAMEPAD_REMOVED" ); // A gamepad has been removed
	assignGlobalInt( SDL_EVENT_GAMEPAD_REMAPPED, "SDL_EVENT_GAMEPAD_REMAPPED" ); // The gamepad mapping was updated
	assignGlobalInt( SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN, "SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN" ); // Gamepad touchpad was touched
	assignGlobalInt( SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION, "SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION" ); // Gamepad touchpad finger was moved
	assignGlobalInt( SDL_EVENT_GAMEPAD_TOUCHPAD_UP, "SDL_EVENT_GAMEPAD_TOUCHPAD_UP" ); // Gamepad touchpad finger was lifted
	assignGlobalInt( SDL_EVENT_GAMEPAD_SENSOR_UPDATE, "SDL_EVENT_GAMEPAD_SENSOR_UPDATE" ); // Gamepad sensor was updated
	assignGlobalInt( SDL_EVENT_GAMEPAD_UPDATE_COMPLETE, "SDL_EVENT_GAMEPAD_UPDATE_COMPLETE" ); // Gamepad update is complete
	assignGlobalInt( SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED, "SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED" ); // Gamepad Steam handle has changed
	/* Touch events */
	assignGlobalInt( SDL_EVENT_FINGER_DOWN, "SDL_EVENT_FINGER_DOWN" );
	assignGlobalInt( SDL_EVENT_FINGER_UP, "SDL_EVENT_FINGER_UP" );
	assignGlobalInt( SDL_EVENT_FINGER_MOTION, "SDL_EVENT_FINGER_MOTION" );
	// assignGlobalInt( SDL_EVENT_FINGER_CANCELED, "SDL_EVENT_FINGER_CANCELED" );
	/* Clipboard events */
	assignGlobalInt( SDL_EVENT_CLIPBOARD_UPDATE, "SDL_EVENT_CLIPBOARD_UPDATE" ); // The clipboard or primary selection changed
	/* Drag and drop events */
	assignGlobalInt( SDL_EVENT_DROP_FILE, "SDL_EVENT_DROP_FILE" ); // The system requests a file open
	assignGlobalInt( SDL_EVENT_DROP_TEXT, "SDL_EVENT_DROP_TEXT" ); // text/plain drag-and-drop event
	assignGlobalInt( SDL_EVENT_DROP_BEGIN, "SDL_EVENT_DROP_BEGIN" ); // A new set of drops is beginning (NULL filename)
	assignGlobalInt( SDL_EVENT_DROP_COMPLETE, "SDL_EVENT_DROP_COMPLETE" ); // Current set of drops is now complete (NULL filename)
	assignGlobalInt( SDL_EVENT_DROP_POSITION, "SDL_EVENT_DROP_POSITION" ); // Position while moving over the window
	/* Audio hotplug events */
	assignGlobalInt( SDL_EVENT_AUDIO_DEVICE_ADDED, "SDL_EVENT_AUDIO_DEVICE_ADDED" ); // A new audio device is available
	assignGlobalInt( SDL_EVENT_AUDIO_DEVICE_REMOVED, "SDL_EVENT_AUDIO_DEVICE_REMOVED" ); // An audio device has been removed
	assignGlobalInt( SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED, "SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED" ); // An audio device's format has been changed by the system
	/* Sensor events */
	assignGlobalInt( SDL_EVENT_SENSOR_UPDATE, "SDL_EVENT_SENSOR_UPDATE" ); // A sensor was updated
	/* Pressure-sensitive pen events */
	assignGlobalInt( SDL_EVENT_PEN_PROXIMITY_IN, "SDL_EVENT_PEN_PROXIMITY_IN" ); // Pressure-sensitive pen has become available
	assignGlobalInt( SDL_EVENT_PEN_PROXIMITY_OUT, "SDL_EVENT_PEN_PROXIMITY_OUT" ); // Pressure-sensitive pen has become unavailable
	assignGlobalInt( SDL_EVENT_PEN_DOWN, "SDL_EVENT_PEN_DOWN" ); // Pressure-sensitive pen touched drawing surface
	assignGlobalInt( SDL_EVENT_PEN_UP, "SDL_EVENT_PEN_UP" ); // Pressure-sensitive pen stopped touching drawing surface
	assignGlobalInt( SDL_EVENT_PEN_BUTTON_DOWN, "SDL_EVENT_PEN_BUTTON_DOWN" ); // Pressure-sensitive pen button pressed
	assignGlobalInt( SDL_EVENT_PEN_BUTTON_UP, "SDL_EVENT_PEN_BUTTON_UP" ); // Pressure-sensitive pen button released
	assignGlobalInt( SDL_EVENT_PEN_MOTION, "SDL_EVENT_PEN_MOTION" ); // Pressure-sensitive pen is moving on the tablet
	assignGlobalInt( SDL_EVENT_PEN_AXIS, "SDL_EVENT_PEN_AXIS" ); // Pressure-sensitive pen angle/pressure/etc changed
	/* Camera hotplug events */
	assignGlobalInt( SDL_EVENT_CAMERA_DEVICE_ADDED, "SDL_EVENT_CAMERA_DEVICE_ADDED" ); // A new camera device is available
	assignGlobalInt( SDL_EVENT_CAMERA_DEVICE_REMOVED, "SDL_EVENT_CAMERA_DEVICE_REMOVED" ); // A camera device has been removed
	assignGlobalInt( SDL_EVENT_CAMERA_DEVICE_APPROVED, "SDL_EVENT_CAMERA_DEVICE_APPROVED" ); // A camera device has been approved for use by the user
	assignGlobalInt( SDL_EVENT_CAMERA_DEVICE_DENIED, "SDL_EVENT_CAMERA_DEVICE_DENIED" ); // A camera device has been denied for use by the user
	/* Render events */
	assignGlobalInt( SDL_EVENT_RENDER_TARGETS_RESET, "SDL_EVENT_RENDER_TARGETS_RESET" ); // The render targets have been reset and their contents need to be updated
	assignGlobalInt( SDL_EVENT_RENDER_DEVICE_RESET, "SDL_EVENT_RENDER_DEVICE_RESET" ); // The device has been reset and all textures need to be recreated
	// assignGlobalInt( SDL_EVENT_RENDER_DEVICE_LOST, "SDL_EVENT_RENDER_DEVICE_LOST" ); // The device has been lost and can't be recovered
/*DOC_DEFINES_END*/
	lua_pop( L, -1 );
}

/* Events. */

/*
## SDL Events
*/

/* This function is not thread safe so we don't use Lua inside it directly. It only adds events to another queue. */
static bool SDLEventFilter( void* userdata, SDL_Event* event ) {
	/* SDL_EVENT_POLL_SENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */
	if ( event->type != SDL_EVENT_QUIT && event->type != 0x7F00 && state->SDL_eventQueueLen < PLATFORM_SDL_EVENT_QUEUE_LEN ) {
		state->SDL_eventQueue[ state->SDL_eventQueueLen ] = *event;
		state->SDL_eventQueueLen++;

		// printf( "event %u state->SDL_eventQueueLen %d\n", event->type, state->SDL_eventQueueLen );
	}
	// return true;
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
> SDL_AudioDeviceEvent = { int type, int timestamp, int which, bool recording }

Audio device event SDL_EVENT_AUDIO_DEVICE_ADDED or SDL_EVENT_AUDIO_DEVICE_REMOVED
or SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED
*/
		case SDL_EVENT_AUDIO_DEVICE_ADDED:
		case SDL_EVENT_AUDIO_DEVICE_REMOVED:
		case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
		{
			lua_createtable( L, 4, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.adevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.adevice.which );
			lua_setfield( L, -2, "which" );
			lua_pushboolean( L, event.adevice.recording );
			lua_setfield( L, -2, "recording" );
			call = true;
		}
		break;
/*
> SDL_CameraDeviceEvent = { int type, int timestamp, int which }

Camera device event SDL_EVENT_CAMERA_DEVICE_ADDED, SDL_EVENT_CAMERA_DEVICE_REMOVED,
SDL_EVENT_CAMERA_DEVICE_APPROVED,SDL_EVENT_CAMERA_DEVICE_DENIED
*/
		case SDL_EVENT_CAMERA_DEVICE_ADDED:
		case SDL_EVENT_CAMERA_DEVICE_REMOVED:
		case SDL_EVENT_CAMERA_DEVICE_APPROVED:
		case SDL_EVENT_CAMERA_DEVICE_DENIED:
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
> SDL_ClipboardEvent = { int type, int timestamp, bool owner, string{} mime_types }

An event triggered when the clipboard contents have changed SDL_EVENT_CLIPBOARD_UPDATE
*/
		case SDL_EVENT_CLIPBOARD_UPDATE:
		{
			lua_createtable( L, 4, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.clipboard.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushboolean( L, event.clipboard.owner );
			lua_setfield( L, -2, "owner" );

			lua_createtable( L, event.clipboard.n_mime_types, 0 );
			for ( int i = 0; i < event.clipboard.n_mime_types; i++ ) {
				lua_pushstring( L, event.clipboard.mime_types[i] );
				lua_rawseti( L, -2, i + 1 );
			}
			lua_setfield( L, -2, "mime_types" );
			call = true;
		}
		break;
/*
> SDL_DisplayEvent = { int type, int timestamp, int displayID, int data1, int data2 }

Display state change event SDL_EVENT_DISPLAY_*
*/
		case SDL_EVENT_DISPLAY_ORIENTATION:
		case SDL_EVENT_DISPLAY_ADDED:
		case SDL_EVENT_DISPLAY_REMOVED:
		case SDL_EVENT_DISPLAY_MOVED:
		case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED:
		case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED:
		case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.display.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.display.displayID );
			lua_setfield( L, -2, "displayID" );
			lua_pushinteger( L, event.display.data1 );
			lua_setfield( L, -2, "data1" );
			lua_pushinteger( L, event.display.data2 );
			lua_setfield( L, -2, "data2" );
			call = true;
		}
		break;
/*
> SDL_DropEvent = { int type, int timestamp, int windowID, number x, number y, string source, string data }

An event used to drop text or request a file open by the system SDL_EVENT_DROP_BEGIN
or SDL_EVENT_DROP_FILE or SDL_EVENT_DROP_TEXT or SDL_EVENT_DROP_COMPLETE or SDL_EVENT_DROP_POSITION
*/
		case SDL_EVENT_DROP_BEGIN:
		case SDL_EVENT_DROP_FILE:
		case SDL_EVENT_DROP_TEXT:
		case SDL_EVENT_DROP_COMPLETE:
		case SDL_EVENT_DROP_POSITION:
		{
			lua_createtable( L, 7, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.drop.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.drop.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushnumber( L, event.drop.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.drop.y );
			lua_setfield( L, -2, "y" );
			lua_pushstring( L, event.drop.source );
			lua_setfield( L, -2, "source" );
			lua_pushstring( L, event.drop.data );
			lua_setfield( L, -2, "data" );
			call = true;
		}
		break;
/*
> SDL_GamepadAxisEvent = { int type, int timestamp, int which, int axis, int value }

Gamepad axis motion event SDL_EVENT_GAMEPAD_AXIS_MOTION
*/
		case SDL_EVENT_GAMEPAD_AXIS_MOTION:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.gaxis.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.gaxis.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.gaxis.axis );
			lua_setfield( L, -2, "axis" );
			lua_pushinteger( L, event.gaxis.value );
			lua_setfield( L, -2, "value" );
			call = true;
		}
		break;
/*
> SDL_GamepadButtonEvent = { int type, int timestamp, int which, int button, bool down }

Gamepad button event SDL_EVENT_GAMEPAD_BUTTON_DOWN or SDL_EVENT_GAMEPAD_BUTTON_UP
*/
		case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
		case SDL_EVENT_GAMEPAD_BUTTON_UP:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.gbutton.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.gbutton.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.gbutton.button );
			lua_setfield( L, -2, "button" );
			lua_pushboolean( L, event.gbutton.down );
			lua_setfield( L, -2, "down" );
			call = true;
		}
		break;
/*
> SDL_GamepadDeviceEvent = { int type, int timestamp, int which }

Gamepad device event SDL_EVENT_GAMEPAD_ADDED, SDL_EVENT_GAMEPAD_REMOVED, or SDL_EVENT_GAMEPAD_REMAPPED,
SDL_EVENT_GAMEPAD_UPDATE_COMPLETE or SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED
*/
		case SDL_EVENT_GAMEPAD_ADDED:
		case SDL_EVENT_GAMEPAD_REMOVED:
		case SDL_EVENT_GAMEPAD_REMAPPED:
		case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
		case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
		{
			lua_createtable( L, 3, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.gdevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.gdevice.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_GamepadSensorEvent = { int type, int timestamp, int which, int sensor, number{} data, int sensor_timestamp }

Gamepad sensor event SDL_EVENT_GAMEPAD_SENSOR_UPDATE
*/
		case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
		{
			lua_createtable( L, 6, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.gsensor.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.gsensor.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.gsensor.sensor );
			lua_setfield( L, -2, "sensor" );

			lua_createtable( L, 3, 0 );
			for ( int i = 0; i < 3; i++ ) {
				lua_pushnumber( L, event.gsensor.data[i] );
				lua_rawseti( L, -2, i + 1 );
			}
			lua_setfield( L, -2, "data" );

			lua_pushinteger( L, event.gsensor.sensor_timestamp );
			lua_setfield( L, -2, "sensor_timestamp" );
			call = true;
		}
		break;
/*
> SDL_GamepadTouchpadEvent = { int type, int timestamp, int which, int touchpad, int finger, number x, number y, number pressure }

Gamepad touchpad event SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN or SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION or SDL_EVENT_GAMEPAD_TOUCHPAD_UP
*/
		case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
		case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
		case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
		{
			lua_createtable( L, 8, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.gtouchpad.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.gtouchpad.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.gtouchpad.touchpad );
			lua_setfield( L, -2, "touchpad" );
			lua_pushinteger( L, event.gtouchpad.finger );
			lua_setfield( L, -2, "finger" );
			lua_pushnumber( L, event.gtouchpad.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.gtouchpad.y );
			lua_setfield( L, -2, "y" );
			lua_pushnumber( L, event.gtouchpad.pressure );
			lua_setfield( L, -2, "pressure" );
			call = true;
		}
		break;
/*
> SDL_JoyAxisEvent = { int type, int timestamp, int which, int axis, int value }

Joystick axis motion event SDL_EVENT_JOYSTICK_AXIS_MOTION
*/
		case SDL_EVENT_JOYSTICK_AXIS_MOTION:
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

Joystick trackball motion event SDL_EVENT_JOYSTICK_BALL_MOTION
*/
		case SDL_EVENT_JOYSTICK_BALL_MOTION:
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
> SDL_JoyBatteryEvent = { int type, int timestamp, int which, int state, int percent }

Joystick battery level change event SDL_EVENT_JOYSTICK_BATTERY_UPDATED
*/
		case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.jbattery.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.jbattery.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.jbattery.state );
			lua_setfield( L, -2, "state" );
			lua_pushinteger( L, event.jbattery.percent );
			lua_setfield( L, -2, "percent" );
			call = true;
		}
		break;
/*
> SDL_JoyButtonEvent = { int type, int timestamp, int which, int button, bool down }

Joystick button event SDL_EVENT_JOYSTICK_BUTTON_DOWN or SDL_EVENT_JOYSTICK_BUTTON_UP
*/
		case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
		case SDL_EVENT_JOYSTICK_BUTTON_UP:
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
			lua_pushboolean( L, event.jbutton.down );
			lua_setfield( L, -2, "down" );
			call = true;
		}
		break;
/*
> SDL_JoyDeviceEvent = { int type, int timestamp, int which }

Joystick device event SDL_EVENT_JOYSTICK_ADDED or SDL_EVENT_JOYSTICK_REMOVED or SDL_EVENT_JOYSTICK_UPDATE_COMPLETE
*/
		case SDL_EVENT_JOYSTICK_ADDED:
		case SDL_EVENT_JOYSTICK_REMOVED:
		case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
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
> SDL_JoyHatEvent = { int type, int timestamp, int which, int hat, int value }

Joystick hat position change event SDL_EVENT_JOYSTICK_HAT_MOTION
*/
		case SDL_EVENT_JOYSTICK_HAT_MOTION:
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
> SDL_KeyboardDeviceEvent = { int type, int timestamp, int which }

Keyboard device event SDL_EVENT_KEYBOARD_ADDED or SDL_EVENT_KEYBOARD_REMOVED
*/
		case SDL_EVENT_KEYBOARD_ADDED:
		case SDL_EVENT_KEYBOARD_REMOVED:
		{
			lua_createtable( L, 3, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.kdevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.kdevice.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_KeyboardEvent = { int type, int timestamp, int windowID, int which, int scancode, int key, int mod, int raw, bool down, bool repeating }

Keyboard button event SDL_EVENT_KEY_DOWN or SDL_EVENT_KEY_UP
*/
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
		{
			lua_createtable( L, 10, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.key.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.key.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.key.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.key.scancode );
			lua_setfield( L, -2, "scancode" );
			lua_pushinteger( L, event.key.key );
			lua_setfield( L, -2, "key" );
			lua_pushinteger( L, event.key.mod );
			lua_setfield( L, -2, "mod" );
			lua_pushinteger( L, event.key.raw );
			lua_setfield( L, -2, "raw" );
			lua_pushboolean( L, event.key.down );
			lua_setfield( L, -2, "down" );
			lua_pushboolean( L, event.key.repeat );
			lua_setfield( L, -2, "repeating" ); /* repeat is Lua keyword. */
			call = true;
		}
		break;
/*
> SDL_MouseButtonEvent = { int type, int timestamp, int windowID, int which, int button, bool down, int clicks, number x, number y }

Mouse button event SDL_EVENT_MOUSE_BUTTON_DOWN or SDL_EVENT_MOUSE_BUTTON_UP
*/
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.button.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.button.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.button.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.button.button );
			lua_setfield( L, -2, "button" );
			lua_pushboolean( L, event.button.down );
			lua_setfield( L, -2, "down" );
			lua_pushinteger( L, event.button.clicks );
			lua_setfield( L, -2, "clicks" );
			lua_pushnumber( L, event.button.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.button.y );
			lua_setfield( L, -2, "y" );
			call = true;
		}
		break;
/*
> SDL_MouseDeviceEvent = { int type, int timestamp, int which }

Mouse device event SDL_EVENT_MOUSE_ADDED or SDL_EVENT_MOUSE_REMOVED
*/
		case SDL_EVENT_MOUSE_ADDED:
		case SDL_EVENT_MOUSE_REMOVED:
		{
			lua_createtable( L, 3, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.mdevice.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.mdevice.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_MouseMotionEvent = { int type, int timestamp, int windowID, int which, int state, number x, number y, number xrel, number yrel }

Mouse motion event SDL_EVENT_MOUSE_MOTION
*/
		case SDL_EVENT_MOUSE_MOTION:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.motion.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.motion.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.motion.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.motion.state );
			lua_setfield( L, -2, "state" );
			lua_pushnumber( L, event.motion.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.motion.y );
			lua_setfield( L, -2, "y" );
			lua_pushnumber( L, event.motion.xrel );
			lua_setfield( L, -2, "xrel" );
			lua_pushnumber( L, event.motion.yrel );
			lua_setfield( L, -2, "yrel" );
			call = true;
		}
		break;
/*
> SDL_MouseWheelEvent = { int type, int timestamp, int windowID, int which, number x, number y, int direction, number mouse_x, number mouse_y }

Mouse wheel event SDL_EVENT_MOUSE_WHEEL
*/
		case SDL_EVENT_MOUSE_WHEEL:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.wheel.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.wheel.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.wheel.which );
			lua_setfield( L, -2, "which" );
			lua_pushnumber( L, event.wheel.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.wheel.y );
			lua_setfield( L, -2, "y" );
			lua_pushinteger( L, event.wheel.direction );
			lua_setfield( L, -2, "direction" );
			lua_pushnumber( L, event.wheel.mouse_x );
			lua_setfield( L, -2, "mouse_x" );
			lua_pushnumber( L, event.wheel.mouse_y );
			lua_setfield( L, -2, "mouse_y" );
			call = true;
		}
		break;
/*
> SDL_PenAxisEvent = { int type, int timestamp, int windowID, int which, int pen_state, number x, number y, int axis, number value }

Pressure-sensitive pen pressure / angle event SDL_EVENT_PEN_AXIS
*/
		case SDL_EVENT_PEN_AXIS:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.paxis.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.paxis.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.paxis.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.paxis.pen_state );
			lua_setfield( L, -2, "pen_state" );
			lua_pushnumber( L, event.paxis.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.paxis.y );
			lua_setfield( L, -2, "y" );
			lua_pushinteger( L, event.paxis.axis );
			lua_setfield( L, -2, "axis" );
			lua_pushnumber( L, event.paxis.value );
			lua_setfield( L, -2, "value" );
			call = true;
		}
		break;
/*
> SDL_PenButtonEvent = { int type, int timestamp, int windowID, int which, int pen_state, number x, number y, int button, bool down }

Pressure-sensitive pen button event SDL_EVENT_PEN_BUTTON_DOWN or SDL_EVENT_PEN_BUTTON_UP
*/
		case SDL_EVENT_PEN_BUTTON_DOWN:
		case SDL_EVENT_PEN_BUTTON_UP:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.pbutton.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.pbutton.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.pbutton.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.pbutton.pen_state );
			lua_setfield( L, -2, "pen_state" );
			lua_pushnumber( L, event.pbutton.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.pbutton.y );
			lua_setfield( L, -2, "y" );
			lua_pushinteger( L, event.pbutton.button );
			lua_setfield( L, -2, "button" );
			lua_pushboolean( L, event.pbutton.down );
			lua_setfield( L, -2, "down" );
			call = true;
		}
		break;
/*
> SDL_PenMotionEvent = { int type, int timestamp, int windowID, int which, int pen_state, number x, number y }

Pressure-sensitive pen motion event SDL_EVENT_PEN_MOTION
*/
		case SDL_EVENT_PEN_MOTION:
		{
			lua_createtable( L, 7, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.ptouch.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.ptouch.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.ptouch.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.ptouch.pen_state );
			lua_setfield( L, -2, "pen_state" );
			lua_pushnumber( L, event.ptouch.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.ptouch.y );
			lua_setfield( L, -2, "y" );
			call = true;
		}
		break;
/*
> SDL_PenProximityEvent = { int type, int timestamp, int windowID, int which }

Pressure-sensitive pen proximity event SDL_EVENT_PEN_PROXIMITY_IN or SDL_EVENT_PEN_PROXIMITY_OUT
*/
		case SDL_EVENT_PEN_PROXIMITY_IN:
		case SDL_EVENT_PEN_PROXIMITY_OUT:
		{
			lua_createtable( L, 4, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.pproximity.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.pproximity.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.pproximity.which );
			lua_setfield( L, -2, "which" );
			call = true;
		}
		break;
/*
> SDL_PenTouchEvent = { int type, int timestamp, int windowID, int which, int pen_state, number x, number y, bool eraser, bool down }

Pressure-sensitive pen touched event SDL_EVENT_PEN_DOWN or SDL_EVENT_PEN_UP
*/
		case SDL_EVENT_PEN_DOWN:
		case SDL_EVENT_PEN_UP:
		{
			lua_createtable( L, 9, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.ptouch.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.ptouch.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.ptouch.which );
			lua_setfield( L, -2, "which" );
			lua_pushinteger( L, event.ptouch.pen_state );
			lua_setfield( L, -2, "pen_state" );
			lua_pushnumber( L, event.ptouch.x );
			lua_setfield( L, -2, "x" );
			lua_pushnumber( L, event.ptouch.y );
			lua_setfield( L, -2, "y" );
			lua_pushboolean( L, event.ptouch.eraser );
			lua_setfield( L, -2, "eraser" );
			lua_pushboolean( L, event.ptouch.down );
			lua_setfield( L, -2, "down" );
			call = true;
		}
		break;
/*
> SDL_QuitEvent = { int type, int timestamp }

The "quit requested" event SDL_EVENT_QUIT
*/
		case SDL_EVENT_QUIT:
		{
			lua_createtable( L, 2, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.quit.timestamp );
			lua_setfield( L, -2, "timestamp" );
			call = true;
		}
		break;
/*
> SDL_SensorEvent = { int type, int timestamp, int which, number{} data, int sensor_timestamp }

Sensor event SDL_EVENT_SENSOR_UPDATE
*/
		case SDL_EVENT_SENSOR_UPDATE:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.sensor.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.sensor.which );
			lua_setfield( L, -2, "which" );

			lua_createtable( L, 6, 0 );
			for ( int i = 0; i < 6; i++ ) {
				lua_pushnumber( L, event.sensor.data[i] );
				lua_rawseti( L, -2, i + 1 );
			}
			lua_setfield( L, -2, "data" );

			lua_pushinteger( L, event.sensor.sensor_timestamp );
			lua_setfield( L, -2, "sensor_timestamp" );
			call = true;
		}
		break;
/*
> SDL_TextEditingCandidatesEvent = { int type, int timestamp, int windowID, string{} candidates, int selected_candidate, bool horizontal }

Keyboard IME candidates event SDL_EVENT_TEXT_EDITING_CANDIDATES
*/
		case SDL_EVENT_TEXT_EDITING_CANDIDATES:
		{
			lua_createtable( L, 6, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.edit_candidates.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.edit_candidates.windowID );
			lua_setfield( L, -2, "windowID" );

			lua_createtable( L, event.edit_candidates.num_candidates, 0 );
			for ( int i = 0; i < event.edit_candidates.num_candidates; i++ ) {
				lua_pushstring( L, event.edit_candidates.candidates[i] );
				lua_rawseti( L, -2, i + 1 );
			}
			lua_setfield( L, -2, "candidates" );

			lua_pushinteger( L, event.edit_candidates.selected_candidate );
			lua_setfield( L, -2, "selected_candidate" );
			lua_pushboolean( L, event.edit_candidates.horizontal );
			lua_setfield( L, -2, "horizontal" );
			call = true;
		}
		break;
/*
> SDL_TextEditingEvent = { int type, int timestamp, int windowID, string text, int start, int length }

Keyboard text editing event SDL_EVENT_TEXT_EDITING
*/
		case SDL_EVENT_TEXT_EDITING:
		{
			lua_createtable( L, 6, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.edit.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.edit.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushstring( L, event.edit.text );
			lua_setfield( L, -2, "text" );
			lua_pushinteger( L, event.edit.start );
			lua_setfield( L, -2, "start" );
			lua_pushinteger( L, event.edit.length );
			lua_setfield( L, -2, "length" );
			call = true;
		}
		break;
/*
> SDL_TextInputEvent = { int type, int timestamp, int windowID, string text }

Keyboard text input event SDL_EVENT_TEXT_INPUT
*/
		case SDL_EVENT_TEXT_INPUT:
		{
			lua_createtable( L, 4, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.text.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.text.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushstring( L, event.text.text );
			lua_setfield( L, -2, "text" );
			call = true;
		}
		break;
/*
> SDL_TouchFingerEvent = { int type, int timestamp, int touchID, int fingerID, number x, number y, number dx, number dy, number pressure, int windowID }

Touch finger event SDL_EVENT_FINGER_DOWN, SDL_EVENT_FINGER_UP, SDL_EVENT_FINGER_MOTION, or SDL_EVENT_FINGER_CANCELED
*/
		case SDL_EVENT_FINGER_DOWN:
		case SDL_EVENT_FINGER_UP:
		case SDL_EVENT_FINGER_MOTION:
		// case SDL_EVENT_FINGER_CANCELED:
		{
			lua_createtable( L, 10, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.tfinger.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.tfinger.touchID );
			lua_setfield( L, -2, "touchID" );
			lua_pushinteger( L, event.tfinger.fingerID );
			lua_setfield( L, -2, "fingerID" );
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
			lua_pushinteger( L, event.tfinger.windowID );
			lua_setfield( L, -2, "windowID" );
			call = true;
		}
		break;
/*
> SDL_WindowEvent = { int type, int timestamp, int windowID, int data1, int data2 }

Window state change event SDL_EVENT_WINDOW_*
*/
		case SDL_EVENT_WINDOW_SHOWN:
		case SDL_EVENT_WINDOW_HIDDEN:
		case SDL_EVENT_WINDOW_EXPOSED:
		case SDL_EVENT_WINDOW_MOVED:
		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
		case SDL_EVENT_WINDOW_MINIMIZED:
		case SDL_EVENT_WINDOW_MAXIMIZED:
		case SDL_EVENT_WINDOW_RESTORED:
		case SDL_EVENT_WINDOW_MOUSE_ENTER:
		case SDL_EVENT_WINDOW_MOUSE_LEAVE:
		case SDL_EVENT_WINDOW_FOCUS_GAINED:
		case SDL_EVENT_WINDOW_FOCUS_LOST:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		case SDL_EVENT_WINDOW_HIT_TEST:
		case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
		case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
		case SDL_EVENT_WINDOW_OCCLUDED:
		case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
		case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
		case SDL_EVENT_WINDOW_DESTROYED:
		case SDL_EVENT_WINDOW_HDR_STATE_CHANGED:
		{
			lua_createtable( L, 5, 0 );
			lua_pushinteger( L, event.type );
			lua_setfield( L, -2, "type" );
			lua_pushinteger( L, event.window.timestamp );
			lua_setfield( L, -2, "timestamp" );
			lua_pushinteger( L, event.window.windowID );
			lua_setfield( L, -2, "windowID" );
			lua_pushinteger( L, event.window.data1 );
			lua_setfield( L, -2, "data1" );
			lua_pushinteger( L, event.window.data2 );
			lua_setfield( L, -2, "data2" );
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
	// lua_State* L = state->luaState;
	// lua_getglobal( L, "RL" );

	// lua_pop( L, -1 );
#ifdef LUA_EVENTS
	platformRegisterEvents();
#endif
}
