#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "core.h"
#include "shapes.h"
#include "textures.h"
#include "models.h"
#include "text.h"
#include "audio.h"
#include "rmath.h"
#include "rgui.h"
#include "lights.h"
#include "lrlgl.h"
#include "lgl.h"
#include "reasings.h"

/* Define types. */

	/* Buffer. */
static int gcBuffer( lua_State *L ) {
	Buffer *buffer = luaL_checkudata( L, 1, "Buffer" );

	unloadBuffer( buffer );
}

static void defineBuffer() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Buffer" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcBuffer );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Image */
static int gcImage( lua_State *L ) {
	Image *image = luaL_checkudata( L, 1, "Image" );

	UnloadImage( *image );
}

static void defineImage() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Image" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcImage );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Texture */
static int gcTexture( lua_State *L ) {
	Texture *texture = luaL_checkudata( L, 1, "Texture" );

	UnloadTexture( *texture );
}

static void defineTexture() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Texture" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcTexture );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* RenderRexture. */
static int gcRenderTexture( lua_State *L ) {
	RenderTexture *renderTexture = luaL_checkudata( L, 1, "RenderTexture" );

	UnloadRenderTexture( *renderTexture );
}

static void defineRenderTexture() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "RenderTexture" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcRenderTexture );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Camera2D. */
static void defineCamera2D() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Camera2D" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Camera3D. */
static void defineCamera3D() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Camera3D" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Shader. */
static int gcShader( lua_State *L ) {
	Shader *shader = luaL_checkudata( L, 1, "Shader" );

	UnloadShader( *shader );
}

static void defineShader() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Shader" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcShader );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Font. */
static int gcFont( lua_State *L ) {
	Font *font = luaL_checkudata( L, 1, "Font" );

	UnloadFont( *font );
}

static void defineFont() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Font" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcFont );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Wave. */
static int gcWave( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );

	UnloadWave( *wave );
}

static void defineWave() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Wave" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcWave );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Sound. */
static int gcSound( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	UnloadSound( *sound );
}

static void defineSound() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Sound" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcSound );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Music. */
static int gcMusic( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	UnloadMusicStream( *music );
}

static void defineMusic() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Music" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcMusic );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Light. */
static void defineLight() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Light" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Material. */
static int gcMaterial( lua_State *L ) {
	Material *material = luaL_checkudata( L, 1, "Material" );

	/* Custom UnloadMaterial since we don't want to free Shaders or Textures. */
	unloadMaterial( material );

	// UnloadMaterial( *material );
}

static void defineMaterial() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Material" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcMaterial );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Mesh. */
static int gcMesh( lua_State *L ) {
	Mesh *mesh = luaL_checkudata( L, 1, "Mesh" );

	UnloadMesh( *mesh );
}

static void defineMesh() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Mesh" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcMesh );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* Model. */
static int gcModel( lua_State *L ) {
	Model *model = luaL_checkudata( L, 1, "Model" );

	UnloadModel( *model );
	// UnloadModelKeepMeshes( *model );
}

static void defineModel() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "Model" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcModel );
	lua_setfield( L, -2, "__gc" );
#endif
}

	/* ModelAnimation. */
static int gcModelAnimation( lua_State *L ) {
	ModelAnimation *modelAnimation = luaL_checkudata( L, 1, "ModelAnimation" );

	UnloadModelAnimation( *modelAnimation );
}

static void defineModelAnimation() {
	lua_State *L = state->luaState;

	luaL_newmetatable( L, "ModelAnimation" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
#ifdef GC_UNLOAD
	lua_pushcfunction( L, gcModelAnimation );
	lua_setfield( L, -2, "__gc" );
#endif
}

/* Assing globals. */

static void assignGlobalInt( int value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushinteger( L, value );
	lua_setfield( L, -2, name );
}

static void assignGlobalFloat( float value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushnumber( L, value );
	lua_setfield( L, -2, name );
}

static void assignGlobalDouble( double value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushnumber( L, value );
	lua_setfield( L, -2, name );
}

static void assignGlobalColor( Color color, const char *name ) {
	lua_State *L = state->luaState;
	uluaPushColor( L, color );
	lua_setfield( L, -2, name );
}

static void assingGlobalFunction( const char *name, int ( *functionPtr )( lua_State* ) ) {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, functionPtr );
	lua_setfield( L, -2, name );
}

static void defineGlobals() {
	lua_State *L = state->luaState;

	lua_newtable( L );
	lua_setglobal( L, "RL" );
	lua_getglobal( L, "RL" );

/* Note! Docgen relyes on this line format. Splits info based on spaces. */
/*DOC_START*/
	/* ConfigFlags */
	assignGlobalInt( FLAG_VSYNC_HINT, "FLAG_VSYNC_HINT" ); // Set to try enabling V-Sync on GPU
	assignGlobalInt( FLAG_FULLSCREEN_MODE, "FLAG_FULLSCREEN_MODE" ); // Set to run program in fullscreen
	assignGlobalInt( FLAG_WINDOW_RESIZABLE, "FLAG_WINDOW_RESIZABLE" ); // Set to allow resizable window
	assignGlobalInt( FLAG_WINDOW_UNDECORATED, "FLAG_WINDOW_UNDECORATED" ); // Set to disable window decoration (frame and buttons)
	assignGlobalInt( FLAG_WINDOW_HIDDEN, "FLAG_WINDOW_HIDDEN" ); // Set to hide window
	assignGlobalInt( FLAG_WINDOW_MINIMIZED, "FLAG_WINDOW_MINIMIZED" ); // Set to minimize window (iconify)
	assignGlobalInt( FLAG_WINDOW_MAXIMIZED, "FLAG_WINDOW_MAXIMIZED" ); // Set to maximize window (expanded to monitor)
	assignGlobalInt( FLAG_WINDOW_UNFOCUSED, "FLAG_WINDOW_UNFOCUSED" ); // Set to window non focused
	assignGlobalInt( FLAG_WINDOW_TOPMOST, "FLAG_WINDOW_TOPMOST" ); // Set to window always on top
	assignGlobalInt( FLAG_WINDOW_ALWAYS_RUN, "FLAG_WINDOW_ALWAYS_RUN" ); // Set to allow windows running while minimized
	assignGlobalInt( FLAG_WINDOW_TRANSPARENT, "FLAG_WINDOW_TRANSPARENT" ); // Set to allow transparent framebuffer
	assignGlobalInt( FLAG_WINDOW_HIGHDPI, "FLAG_WINDOW_HIGHDPI" ); // Set to support HighDPI
	assignGlobalInt( FLAG_WINDOW_MOUSE_PASSTHROUGH, "FLAG_WINDOW_MOUSE_PASSTHROUGH" ); // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
	assignGlobalInt( FLAG_MSAA_4X_HINT, "FLAG_MSAA_4X_HINT" ); // Set to try enabling MSAA 4X
	assignGlobalInt( FLAG_INTERLACED_HINT, "FLAG_INTERLACED_HINT" ); // Set to try enabling interlaced video format (for V3D)
	/* TraceLogLevel */
	assignGlobalInt( LOG_ALL, "LOG_ALL" ); // Display all logs
	assignGlobalInt( LOG_TRACE, "LOG_TRACE" ); // Trace logging, intended for internal use only
	assignGlobalInt( LOG_DEBUG, "LOG_DEBUG" ); // Debug logging, used for internal debugging, it should be disabled on release builds
	assignGlobalInt( LOG_INFO, "LOG_INFO" ); // Info logging, used for program execution info
	assignGlobalInt( LOG_WARNING, "LOG_WARNING" ); // Warning logging, used on recoverable failures
	assignGlobalInt( LOG_ERROR, "LOG_ERROR" ); // Error logging, used on unrecoverable failures
	assignGlobalInt( LOG_FATAL, "LOG_FATAL" ); // Fatal logging, used to abort program: exit(EXIT_FAILURE)
	assignGlobalInt( LOG_NONE, "LOG_NONE" ); // Disable logging
	/* KeyboardKey */
	assignGlobalInt( GLFW_KEY_UNKNOWN, "KEY_UNKNOWN" ); // Key: Unknown
	assignGlobalInt( KEY_NULL, "KEY_NULL" ); // Key: NULL, used for no key pressed
	assignGlobalInt( KEY_APOSTROPHE, "KEY_APOSTROPHE" ); // Key: '
	assignGlobalInt( KEY_COMMA, "KEY_COMMA" ); // Key: ,
	assignGlobalInt( KEY_MINUS, "KEY_MINUS" ); // Key: -
	assignGlobalInt( KEY_PERIOD, "KEY_PERIOD" ); // Key: .
	assignGlobalInt( KEY_SLASH, "KEY_SLASH" ); // Key: /
	assignGlobalInt( KEY_ZERO, "KEY_ZERO" ); // Key: 0
	assignGlobalInt( KEY_ONE, "KEY_ONE" ); // Key: 1
	assignGlobalInt( KEY_TWO, "KEY_TWO" ); // Key: 2
	assignGlobalInt( KEY_THREE, "KEY_THREE" ); // Key: 3
	assignGlobalInt( KEY_FOUR, "KEY_FOUR" ); // Key: 4
	assignGlobalInt( KEY_FIVE, "KEY_FIVE" ); // Key: 5
	assignGlobalInt( KEY_SIX, "KEY_SIX" ); // Key: 6
	assignGlobalInt( KEY_SEVEN, "KEY_SEVEN" ); // Key: 7
	assignGlobalInt( KEY_EIGHT, "KEY_EIGHT" ); // Key: 8
	assignGlobalInt( KEY_NINE, "KEY_NINE" ); // Key: 9
	assignGlobalInt( KEY_SEMICOLON, "KEY_SEMICOLON" ); // Key: ;
	assignGlobalInt( KEY_EQUAL, "KEY_EQUAL" ); // Key: =
	assignGlobalInt( KEY_A, "KEY_A" ); // Key: A | a
	assignGlobalInt( KEY_B, "KEY_B" ); // Key: B | b
	assignGlobalInt( KEY_C, "KEY_C" ); // Key: C | c
	assignGlobalInt( KEY_D, "KEY_D" ); // Key: D | d
	assignGlobalInt( KEY_E, "KEY_E" ); // Key: E | e
	assignGlobalInt( KEY_F, "KEY_F" ); // Key: F | f
	assignGlobalInt( KEY_G, "KEY_G" ); // Key: G | g
	assignGlobalInt( KEY_H, "KEY_H" ); // Key: H | h
	assignGlobalInt( KEY_I, "KEY_I" ); // Key: I | i
	assignGlobalInt( KEY_J, "KEY_J" ); // Key: J | j
	assignGlobalInt( KEY_K, "KEY_K" ); // Key: K | k
	assignGlobalInt( KEY_L, "KEY_L" ); // Key: L | l
	assignGlobalInt( KEY_M, "KEY_M" ); // Key: M | m
	assignGlobalInt( KEY_N, "KEY_N" ); // Key: N | n
	assignGlobalInt( KEY_O, "KEY_O" ); // Key: O | o
	assignGlobalInt( KEY_P, "KEY_P" ); // Key: P | p
	assignGlobalInt( KEY_Q, "KEY_Q" ); // Key: Q | q
	assignGlobalInt( KEY_R, "KEY_R" ); // Key: R | r
	assignGlobalInt( KEY_S, "KEY_S" ); // Key: S | s
	assignGlobalInt( KEY_T, "KEY_T" ); // Key: T | t
	assignGlobalInt( KEY_U, "KEY_U" ); // Key: U | u
	assignGlobalInt( KEY_V, "KEY_V" ); // Key: V | v
	assignGlobalInt( KEY_W, "KEY_W" ); // Key: W | w
	assignGlobalInt( KEY_X, "KEY_X" ); // Key: X | x
	assignGlobalInt( KEY_Y, "KEY_Y" ); // Key: Y | y
	assignGlobalInt( KEY_Z, "KEY_Z" ); // Key: Z | z
	assignGlobalInt( KEY_LEFT_BRACKET, "KEY_LEFT_BRACKET" ); // Key: [
	assignGlobalInt( KEY_BACKSLASH, "KEY_BACKSLASH" ); // Key: '\'
	assignGlobalInt( KEY_RIGHT_BRACKET, "KEY_RIGHT_BRACKET" ); // Key: ]
	assignGlobalInt( KEY_GRAVE, "KEY_GRAVE" ); // Key: `
	assignGlobalInt( KEY_SPACE, "KEY_SPACE" ); // Key: Space
	assignGlobalInt( KEY_ESCAPE, "KEY_ESCAPE" ); // Key: Esc
	assignGlobalInt( KEY_ENTER, "KEY_ENTER" ); // Key: Enter
	assignGlobalInt( KEY_TAB, "KEY_TAB" ); // Key: Tab
	assignGlobalInt( KEY_BACKSPACE, "KEY_BACKSPACE" ); // Key: Backspace
	assignGlobalInt( KEY_INSERT, "KEY_INSERT" ); // Key: Ins
	assignGlobalInt( KEY_DELETE, "KEY_DELETE" ); // Key: Del
	assignGlobalInt( KEY_RIGHT, "KEY_RIGHT" ); // Key: Cursor right
	assignGlobalInt( KEY_LEFT, "KEY_LEFT" ); // Key: Cursor left
	assignGlobalInt( KEY_DOWN, "KEY_DOWN" ); // Key: Cursor down
	assignGlobalInt( KEY_UP, "KEY_UP" ); // Key: Cursor up
	assignGlobalInt( KEY_PAGE_UP, "KEY_PAGE_UP" ); // Key: Page up
	assignGlobalInt( KEY_PAGE_DOWN, "KEY_PAGE_DOWN" ); // Key: Page down
	assignGlobalInt( KEY_HOME, "KEY_HOME" ); // Key: Home
	assignGlobalInt( KEY_END, "KEY_END" ); // Key: End
	assignGlobalInt( KEY_CAPS_LOCK, "KEY_CAPS_LOCK" ); // Key: Caps lock
	assignGlobalInt( KEY_SCROLL_LOCK, "KEY_SCROLL_LOCK" ); // Key: Scroll down
	assignGlobalInt( KEY_NUM_LOCK, "KEY_NUM_LOCK" ); // Key: Num lock
	assignGlobalInt( KEY_PRINT_SCREEN, "KEY_PRINT_SCREEN" ); // Key: Print screen
	assignGlobalInt( KEY_PAUSE, "KEY_PAUSE" ); // Key: Pause
	assignGlobalInt( KEY_F1, "KEY_F1" ); // Key: F1
	assignGlobalInt( KEY_F2, "KEY_F2" ); // Key: F2
	assignGlobalInt( KEY_F3, "KEY_F3" ); // Key: F3
	assignGlobalInt( KEY_F4, "KEY_F4" ); // Key: F4
	assignGlobalInt( KEY_F5, "KEY_F5" ); // Key: F5
	assignGlobalInt( KEY_F6, "KEY_F6" ); // Key: F6
	assignGlobalInt( KEY_F7, "KEY_F7" ); // Key: F7
	assignGlobalInt( KEY_F8, "KEY_F8" ); // Key: F8
	assignGlobalInt( KEY_F9, "KEY_F9" ); // Key: F9
	assignGlobalInt( KEY_F10, "KEY_F10" ); // Key: F10
	assignGlobalInt( KEY_F11, "KEY_F11" ); // Key: F11
	assignGlobalInt( KEY_F12, "KEY_F12" ); // Key: F12
	assignGlobalInt( KEY_LEFT_SHIFT, "KEY_LEFT_SHIFT" ); // Key: Shift left
	assignGlobalInt( KEY_LEFT_CONTROL, "KEY_LEFT_CONTROL" ); // Key: Control left
	assignGlobalInt( KEY_LEFT_ALT, "KEY_LEFT_ALT" ); // Key: Alt left
	assignGlobalInt( KEY_LEFT_SUPER, "KEY_LEFT_SUPER" ); // Key: Super left
	assignGlobalInt( KEY_RIGHT_SHIFT, "KEY_RIGHT_SHIFT" ); // Key: Shift right
	assignGlobalInt( KEY_RIGHT_CONTROL, "KEY_RIGHT_CONTROL" ); // Key: Control right
	assignGlobalInt( KEY_RIGHT_ALT, "KEY_RIGHT_ALT" ); // Key: Alt right
	assignGlobalInt( KEY_RIGHT_SUPER, "KEY_RIGHT_SUPER" ); // Key: Super right
	assignGlobalInt( KEY_KB_MENU, "KEY_KB_MENU" ); // Key: KB menu
	assignGlobalInt( KEY_KP_0, "KEY_KP_0" ); // Key: Keypad 0
	assignGlobalInt( KEY_KP_1, "KEY_KP_1" ); // Key: Keypad 1
	assignGlobalInt( KEY_KP_2, "KEY_KP_2" ); // Key: Keypad 2
	assignGlobalInt( KEY_KP_3, "KEY_KP_3" ); // Key: Keypad 3
	assignGlobalInt( KEY_KP_4, "KEY_KP_4" ); // Key: Keypad 4
	assignGlobalInt( KEY_KP_5, "KEY_KP_5" ); // Key: Keypad 5
	assignGlobalInt( KEY_KP_6, "KEY_KP_6" ); // Key: Keypad 6
	assignGlobalInt( KEY_KP_7, "KEY_KP_7" ); // Key: Keypad 7
	assignGlobalInt( KEY_KP_8, "KEY_KP_8" ); // Key: Keypad 8
	assignGlobalInt( KEY_KP_9, "KEY_KP_9" ); // Key: Keypad 9
	assignGlobalInt( KEY_KP_DECIMAL, "KEY_KP_DECIMAL" ); // Key: Keypad .
	assignGlobalInt( KEY_KP_DIVIDE, "KEY_KP_DIVIDE" ); // Key: Keypad /
	assignGlobalInt( KEY_KP_MULTIPLY, "KEY_KP_MULTIPLY" ); // Key: Keypad *
	assignGlobalInt( KEY_KP_SUBTRACT, "KEY_KP_SUBTRACT" ); // Key: Keypad -
	assignGlobalInt( KEY_KP_ADD, "KEY_KP_ADD" ); // Key: Keypad +
	assignGlobalInt( KEY_KP_ENTER, "KEY_KP_ENTER" ); // Key: Keypad Enter
	assignGlobalInt( KEY_KP_EQUAL, "KEY_KP_EQUAL" ); // Key: Keypad =
	assignGlobalInt( KEY_BACK, "KEY_BACK" ); // Key: Android back button
	assignGlobalInt( KEY_MENU, "KEY_MENU" ); // Key: Android menu button
	assignGlobalInt( KEY_VOLUME_UP, "KEY_VOLUME_UP" ); // Key: Android volume up button
	assignGlobalInt( KEY_VOLUME_DOWN, "KEY_VOLUME_DOWN" ); // Key: Android volume down button
	/* MouseButtons */
	assignGlobalInt( MOUSE_BUTTON_LEFT, "MOUSE_BUTTON_LEFT" ); // Mouse button left
	assignGlobalInt( MOUSE_BUTTON_RIGHT, "MOUSE_BUTTON_RIGHT" ); // Mouse button right
	assignGlobalInt( MOUSE_BUTTON_MIDDLE, "MOUSE_BUTTON_MIDDLE" ); // Mouse button middle (pressed wheel)
	assignGlobalInt( MOUSE_BUTTON_SIDE, "MOUSE_BUTTON_SIDE" ); // Mouse button side (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_EXTRA, "MOUSE_BUTTON_EXTRA" ); // Mouse button extra (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_FORWARD, "MOUSE_BUTTON_FORWARD" ); // Mouse button forward (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_BACK, "MOUSE_BUTTON_BACK" ); // Mouse button back (advanced mouse device)
	/* MouseCursor */
	assignGlobalInt( MOUSE_CURSOR_DEFAULT, "MOUSE_CURSOR_DEFAULT" ); // Default pointer shape
	assignGlobalInt( MOUSE_CURSOR_ARROW, "MOUSE_CURSOR_ARROW" ); // Arrow shape
	assignGlobalInt( MOUSE_CURSOR_IBEAM, "MOUSE_CURSOR_IBEAM" ); // Text writing cursor shape
	assignGlobalInt( MOUSE_CURSOR_CROSSHAIR, "MOUSE_CURSOR_CROSSHAIR" ); // Cross shape
	assignGlobalInt( MOUSE_CURSOR_POINTING_HAND, "MOUSE_CURSOR_POINTING_HAND" ); // Pointing hand cursor
	assignGlobalInt( MOUSE_CURSOR_RESIZE_EW, "MOUSE_CURSOR_RESIZE_EW" ); // Horizontal resize/move arrow shape
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NS, "MOUSE_CURSOR_RESIZE_NS" ); // Vertical resize/move arrow shape
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NWSE, "MOUSE_CURSOR_RESIZE_NWSE" ); // Top-left to bottom-right diagonal resize/move arrow shape
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NESW, "MOUSE_CURSOR_RESIZE_NESW" ); // The top-right to bottom-left diagonal resize/move arrow shape
	assignGlobalInt( MOUSE_CURSOR_RESIZE_ALL, "MOUSE_CURSOR_RESIZE_ALL" ); // The omnidirectional resize/move cursor shape
	assignGlobalInt( MOUSE_CURSOR_NOT_ALLOWED, "MOUSE_CURSOR_NOT_ALLOWED" ); // The operation-not-allowed shape
	/* GamepadButtons */
	assignGlobalInt( GAMEPAD_BUTTON_UNKNOWN, "GAMEPAD_BUTTON_UNKNOWN" ); // Unknown button, just for error checking
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_UP, "GAMEPAD_BUTTON_LEFT_FACE_UP" ); // Gamepad left DPAD up button
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_RIGHT, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT" ); // Gamepad left DPAD right button
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_DOWN, "GAMEPAD_BUTTON_LEFT_FACE_DOWN" ); // Gamepad left DPAD down button
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_LEFT, "GAMEPAD_BUTTON_LEFT_FACE_LEFT" ); // Gamepad left DPAD left button
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_UP, "GAMEPAD_BUTTON_RIGHT_FACE_UP" ); // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT" ); // Gamepad right button right (i.e. PS3: Square, Xbox: X)
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_DOWN, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN" ); // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_LEFT, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT" ); // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_TRIGGER_1, "GAMEPAD_BUTTON_LEFT_TRIGGER_1" ); // Gamepad top/back trigger left (first), it could be a trailing button
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_TRIGGER_2, "GAMEPAD_BUTTON_LEFT_TRIGGER_2" ); // Gamepad top/back trigger left (second), it could be a trailing button
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_TRIGGER_1, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1" ); // Gamepad top/back trigger right (one), it could be a trailing button
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_TRIGGER_2, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2" ); // Gamepad top/back trigger right (second), it could be a trailing button
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE_LEFT, "GAMEPAD_BUTTON_MIDDLE_LEFT" ); // Gamepad center buttons, left one (i.e. PS3: Select)
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE, "GAMEPAD_BUTTON_MIDDLE" ); // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE_RIGHT, "GAMEPAD_BUTTON_MIDDLE_RIGHT" ); // Gamepad center buttons, right one (i.e. PS3: Start)
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_THUMB, "GAMEPAD_BUTTON_LEFT_THUMB" ); // Gamepad joystick pressed button left
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_THUMB, "GAMEPAD_BUTTON_RIGHT_THUMB" ); // Gamepad joystick pressed button right
	/* GamepadAxis */
	assignGlobalInt( GAMEPAD_AXIS_LEFT_X, "GAMEPAD_AXIS_LEFT_X" ); // Gamepad left stick X axis
	assignGlobalInt( GAMEPAD_AXIS_LEFT_Y, "GAMEPAD_AXIS_LEFT_Y" ); // Gamepad left stick Y axis
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_X, "GAMEPAD_AXIS_RIGHT_X" ); // Gamepad right stick X axis
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_Y, "GAMEPAD_AXIS_RIGHT_Y" ); // Gamepad right stick Y axis
	assignGlobalInt( GAMEPAD_AXIS_LEFT_TRIGGER, "GAMEPAD_AXIS_LEFT_TRIGGER" ); // Gamepad back trigger left, pressure level: [1..-1]
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_TRIGGER, "GAMEPAD_AXIS_RIGHT_TRIGGER" ); // Gamepad back trigger right, pressure level: [1..-1]
	/* MapTypes */
	assignGlobalInt( MATERIAL_MAP_ALBEDO, "MATERIAL_MAP_ALBEDO" ); // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
	assignGlobalInt( MATERIAL_MAP_METALNESS, "MATERIAL_MAP_METALNESS" ); // Metalness material (same as: MATERIAL_MAP_SPECULAR)
	assignGlobalInt( MATERIAL_MAP_NORMAL, "MATERIAL_MAP_NORMAL" ); // Normal material
	assignGlobalInt( MATERIAL_MAP_ROUGHNESS, "MATERIAL_MAP_ROUGHNESS" ); // Roughness material
	assignGlobalInt( MATERIAL_MAP_OCCLUSION, "MATERIAL_MAP_OCCLUSION" ); // Ambient occlusion material
	assignGlobalInt( MATERIAL_MAP_EMISSION, "MATERIAL_MAP_EMISSION" ); // Emission material
	assignGlobalInt( MATERIAL_MAP_HEIGHT, "MATERIAL_MAP_HEIGHT" ); // Heightmap material
	assignGlobalInt( MATERIAL_MAP_CUBEMAP, "MATERIAL_MAP_CUBEMAP" ); // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
	assignGlobalInt( MATERIAL_MAP_IRRADIANCE, "MATERIAL_MAP_IRRADIANCE" ); // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
	assignGlobalInt( MATERIAL_MAP_PREFILTER, "MATERIAL_MAP_PREFILTER" ); // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
	assignGlobalInt( MATERIAL_MAP_BRDF, "MATERIAL_MAP_BRDF" ); // Brdf material
	assignGlobalInt( MATERIAL_MAP_DIFFUSE, "MATERIAL_MAP_DIFFUSE" ); // Diffuce material (same as: MATERIAL_MAP_ALBEDO)
	assignGlobalInt( MATERIAL_MAP_SPECULAR, "MATERIAL_MAP_SPECULAR" ); // Specular material (same as: MATERIAL_MAP_METALNESS)
	/* ShaderLocationIndex */
	assignGlobalInt( SHADER_LOC_VERTEX_POSITION, "SHADER_LOC_VERTEX_POSITION" ); // Shader location: vertex attribute: position
	assignGlobalInt( SHADER_LOC_VERTEX_TEXCOORD01, "SHADER_LOC_VERTEX_TEXCOORD01" ); // Shader location: vertex attribute: texcoord01
	assignGlobalInt( SHADER_LOC_VERTEX_TEXCOORD02, "SHADER_LOC_VERTEX_TEXCOORD02" ); // Shader location: vertex attribute: texcoord02
	assignGlobalInt( SHADER_LOC_VERTEX_NORMAL, "SHADER_LOC_VERTEX_NORMAL" ); // Shader location: vertex attribute: normal
	assignGlobalInt( SHADER_LOC_VERTEX_TANGENT, "SHADER_LOC_VERTEX_TANGENT" ); // Shader location: vertex attribute: tangent
	assignGlobalInt( SHADER_LOC_VERTEX_COLOR, "SHADER_LOC_VERTEX_COLOR" ); // Shader location: vertex attribute: color
	assignGlobalInt( SHADER_LOC_MATRIX_MVP, "SHADER_LOC_MATRIX_MVP" ); // Shader location: matrix uniform: model-view-projection
	assignGlobalInt( SHADER_LOC_MATRIX_VIEW, "SHADER_LOC_MATRIX_VIEW" ); // Shader location: matrix uniform: view (camera transform)
	assignGlobalInt( SHADER_LOC_MATRIX_PROJECTION, "SHADER_LOC_MATRIX_PROJECTION" ); // Shader location: matrix uniform: projection
	assignGlobalInt( SHADER_LOC_MATRIX_MODEL, "SHADER_LOC_MATRIX_MODEL" ); // Shader location: matrix uniform: model (transform)
	assignGlobalInt( SHADER_LOC_MATRIX_NORMAL, "SHADER_LOC_MATRIX_NORMAL" ); // Shader location: matrix uniform: normal
	assignGlobalInt( SHADER_LOC_VECTOR_VIEW, "SHADER_LOC_VECTOR_VIEW" ); // Shader location: vector uniform: view
	assignGlobalInt( SHADER_LOC_COLOR_DIFFUSE, "SHADER_LOC_COLOR_DIFFUSE" ); // Shader location: vector uniform: diffuse color
	assignGlobalInt( SHADER_LOC_COLOR_SPECULAR, "SHADER_LOC_COLOR_SPECULAR" ); // Shader location: vector uniform: specular color
	assignGlobalInt( SHADER_LOC_COLOR_AMBIENT, "SHADER_LOC_COLOR_AMBIENT" ); // Shader location: vector uniform: ambient color
	assignGlobalInt( SHADER_LOC_MAP_ALBEDO, "SHADER_LOC_MAP_ALBEDO" ); // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
	assignGlobalInt( SHADER_LOC_MAP_METALNESS, "SHADER_LOC_MAP_METALNESS" ); // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
	assignGlobalInt( SHADER_LOC_MAP_NORMAL, "SHADER_LOC_MAP_NORMAL" ); // Shader location: sampler2d texture: normal
	assignGlobalInt( SHADER_LOC_MAP_ROUGHNESS, "SHADER_LOC_MAP_ROUGHNESS" ); // Shader location: sampler2d texture: roughness
	assignGlobalInt( SHADER_LOC_MAP_OCCLUSION, "SHADER_LOC_MAP_OCCLUSION" ); // Shader location: sampler2d texture: occlusion
	assignGlobalInt( SHADER_LOC_MAP_EMISSION, "SHADER_LOC_MAP_EMISSION" ); // Shader location: sampler2d texture: emission
	assignGlobalInt( SHADER_LOC_MAP_HEIGHT, "SHADER_LOC_MAP_HEIGHT" ); // Shader location: sampler2d texture: height
	assignGlobalInt( SHADER_LOC_MAP_CUBEMAP, "SHADER_LOC_MAP_CUBEMAP" ); // Shader location: samplerCube texture: cubemap
	assignGlobalInt( SHADER_LOC_MAP_IRRADIANCE, "SHADER_LOC_MAP_IRRADIANCE" ); // Shader location: samplerCube texture: irradiance
	assignGlobalInt( SHADER_LOC_MAP_PREFILTER, "SHADER_LOC_MAP_PREFILTER" ); // Shader location: samplerCube texture: prefilter
	assignGlobalInt( SHADER_LOC_MAP_BRDF, "SHADER_LOC_MAP_BRDF" ); // Shader location: sampler2d texture: brdf
	assignGlobalInt( SHADER_LOC_MAP_DIFFUSE, "SHADER_LOC_MAP_DIFFUSE" ); // Shader location: sampler2d texture: diffuce (same as: SHADER_LOC_MAP_ALBEDO)
	assignGlobalInt( SHADER_LOC_MAP_SPECULAR, "SHADER_LOC_MAP_SPECULAR" ); // Shader location: sampler2d texture: specular (same as: SHADER_LOC_MAP_METALNESS)
	/* ShaderUniformDataType */
	assignGlobalInt( SHADER_UNIFORM_FLOAT, "SHADER_UNIFORM_FLOAT" ); // Shader uniform type: float
	assignGlobalInt( SHADER_UNIFORM_VEC2, "SHADER_UNIFORM_VEC2" ); // Shader uniform type: vec2 (2 float)
	assignGlobalInt( SHADER_UNIFORM_VEC3, "SHADER_UNIFORM_VEC3" ); // Shader uniform type: vec3 (3 float)
	assignGlobalInt( SHADER_UNIFORM_VEC4, "SHADER_UNIFORM_VEC4" ); // Shader uniform type: vec4 (4 float)
	assignGlobalInt( SHADER_UNIFORM_INT, "SHADER_UNIFORM_INT" ); // Shader uniform type: int
	assignGlobalInt( SHADER_UNIFORM_IVEC2, "SHADER_UNIFORM_IVEC2" ); // Shader uniform type: ivec2 (2 int)
	assignGlobalInt( SHADER_UNIFORM_IVEC3, "SHADER_UNIFORM_IVEC3" ); // Shader uniform type: ivec3 (3 int)
	assignGlobalInt( SHADER_UNIFORM_IVEC4, "SHADER_UNIFORM_IVEC4" ); // Shader uniform type: ivec4 (4 int)
	assignGlobalInt( SHADER_UNIFORM_SAMPLER2D, "SHADER_UNIFORM_SAMPLER2D" ); // Shader uniform type: sampler2d
	/* ShaderAttributeDataTypes */
	assignGlobalInt( SHADER_ATTRIB_FLOAT, "SHADER_ATTRIB_FLOAT" ); // Shader attribute type: float
	assignGlobalInt( SHADER_ATTRIB_VEC2, "SHADER_ATTRIB_VEC2" ); // Shader attribute type: vec2 (2 float)
	assignGlobalInt( SHADER_ATTRIB_VEC3, "SHADER_ATTRIB_VEC3" ); // Shader attribute type: vec3 (3 float)
	assignGlobalInt( SHADER_ATTRIB_VEC4, "SHADER_ATTRIB_VEC4" ); // Shader attribute type: vec4 (4 float)
	/* PixelFormats */
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE" ); // 8 bit per pixel (no alpha)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA" ); // 8*2 bpp (2 channels)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R5G6B5, "PIXELFORMAT_UNCOMPRESSED_R5G6B5" ); // 16 bpp
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R8G8B8, "PIXELFORMAT_UNCOMPRESSED_R8G8B8" ); // 24 bpp
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R5G5B5A1, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1" ); // 16 bpp (1 bit alpha)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R4G4B4A4, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4" ); // 16 bpp (4 bit alpha)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8" ); // 32 bpp
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32, "PIXELFORMAT_UNCOMPRESSED_R32" ); // 32 bpp (1 channel - float)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32G32B32, "PIXELFORMAT_UNCOMPRESSED_R32G32B32" ); // 32*3 bpp (3 channels - float)
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32G32B32A32, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32" ); // 32*4 bpp (4 channels - float)
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT1_RGB, "PIXELFORMAT_COMPRESSED_DXT1_RGB" ); // 4 bpp (no alpha)
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT1_RGBA, "PIXELFORMAT_COMPRESSED_DXT1_RGBA" ); // 4 bpp (1 bit alpha)
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT3_RGBA, "PIXELFORMAT_COMPRESSED_DXT3_RGBA" ); // 8 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT5_RGBA, "PIXELFORMAT_COMPRESSED_DXT5_RGBA" ); // 8 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC1_RGB, "PIXELFORMAT_COMPRESSED_ETC1_RGB" ); // 4 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC2_RGB, "PIXELFORMAT_COMPRESSED_ETC2_RGB" ); // 4 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA" ); // 8 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_PVRT_RGB, "PIXELFORMAT_COMPRESSED_PVRT_RGB" ); // 4 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_PVRT_RGBA, "PIXELFORMAT_COMPRESSED_PVRT_RGBA" ); // 4 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA" ); // 8 bpp
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA" ); // 2 bpp
	/* TextureFilters */
	assignGlobalInt( TEXTURE_FILTER_POINT, "TEXTURE_FILTER_POINT" ); // No filter, just pixel approximation
	assignGlobalInt( TEXTURE_FILTER_BILINEAR, "TEXTURE_FILTER_BILINEAR" ); // Linear filtering
	assignGlobalInt( TEXTURE_FILTER_TRILINEAR, "TEXTURE_FILTER_TRILINEAR" ); // Trilinear filtering (linear with mipmaps)
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_4X, "TEXTURE_FILTER_ANISOTROPIC_4X" ); // Anisotropic filtering 4x
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_8X, "TEXTURE_FILTER_ANISOTROPIC_8X" ); // Anisotropic filtering 8x
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_16X, "TEXTURE_FILTER_ANISOTROPIC_16X" ); // Anisotropic filtering 16x
	/* TextureWrap */
	assignGlobalInt( TEXTURE_WRAP_REPEAT, "TEXTURE_WRAP_REPEAT" ); // Repeats texture in tiled mode
	assignGlobalInt( TEXTURE_WRAP_CLAMP, "TEXTURE_WRAP_CLAMP" ); // Clamps texture to edge pixel in tiled mode
	assignGlobalInt( TEXTURE_WRAP_MIRROR_REPEAT, "TEXTURE_WRAP_MIRROR_REPEAT" ); // Mirrors and repeats the texture in tiled mode
	assignGlobalInt( TEXTURE_WRAP_MIRROR_CLAMP, "TEXTURE_WRAP_MIRROR_CLAMP" ); // Mirrors and clamps to border the texture in tiled mode
	/* CubemapLayout */
	assignGlobalInt( CUBEMAP_LAYOUT_AUTO_DETECT, "CUBEMAP_LAYOUT_AUTO_DETECT" ); // Automatically detect layout type
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_VERTICAL, "CUBEMAP_LAYOUT_LINE_VERTICAL" ); // Layout is defined by a vertical line with faces
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_HORIZONTAL, "CUBEMAP_LAYOUT_LINE_HORIZONTAL" ); // Layout is defined by a horizontal line with faces
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR" ); // Layout is defined by a 3x4 cross with cubemap faces
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE" ); // Layout is defined by a 4x3 cross with cubemap faces
	assignGlobalInt( CUBEMAP_LAYOUT_PANORAMA, "CUBEMAP_LAYOUT_PANORAMA" ); // Layout is defined by a panorama image (equirrectangular map)
	/* FontType */
	assignGlobalInt( FONT_DEFAULT, "FONT_DEFAULT" ); // Default font generation, anti-aliased
	assignGlobalInt( FONT_BITMAP, "FONT_BITMAP" ); // Bitmap font generation, no anti-aliasing
	assignGlobalInt( FONT_SDF, "FONT_SDF" ); // SDF font generation, requires external shader
	/* BlendModes */
	assignGlobalInt( BLEND_ALPHA, "BLEND_ALPHA" ); // Blend textures considering alpha (default)
	assignGlobalInt( BLEND_ADDITIVE, "BLEND_ADDITIVE" ); // Blend textures adding colors
	assignGlobalInt( BLEND_MULTIPLIED, "BLEND_MULTIPLIED" ); // Blend textures multiplying colors
	assignGlobalInt( BLEND_ADD_COLORS, "BLEND_ADD_COLORS" ); // Blend textures adding colors (alternative)
	assignGlobalInt( BLEND_SUBTRACT_COLORS, "BLEND_SUBTRACT_COLORS" ); // Blend textures subtracting colors (alternative)
	assignGlobalInt( BLEND_ALPHA_PREMULTIPLY, "BLEND_ALPHA_PREMULTIPLY" ); // Blend premultiplied textures considering alpha
	assignGlobalInt( BLEND_CUSTOM, "BLEND_CUSTOM" ); // Blend textures using custom src/dst factors (use rlSetBlendFactors())
	assignGlobalInt( BLEND_CUSTOM_SEPARATE, "BLEND_CUSTOM_SEPARATE" ); // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
	/* Gesture */
	assignGlobalInt( GESTURE_NONE, "GESTURE_NONE" ); // No gesture
	assignGlobalInt( GESTURE_TAP, "GESTURE_TAP" ); // Tap gesture
	assignGlobalInt( GESTURE_DOUBLETAP, "GESTURE_DOUBLETAP" ); // Double tap gesture
	assignGlobalInt( GESTURE_HOLD, "GESTURE_HOLD" ); // Hold gesture
	assignGlobalInt( GESTURE_DRAG, "GESTURE_DRAG" ); // Drag gesture
	assignGlobalInt( GESTURE_SWIPE_RIGHT, "GESTURE_SWIPE_RIGHT" ); // Swipe right gesture
	assignGlobalInt( GESTURE_SWIPE_LEFT, "GESTURE_SWIPE_LEFT" ); // Swipe left gesture
	assignGlobalInt( GESTURE_SWIPE_UP, "GESTURE_SWIPE_UP" ); // Swipe up gesture
	assignGlobalInt( GESTURE_SWIPE_DOWN, "GESTURE_SWIPE_DOWN" ); // Swipe down gesture
	assignGlobalInt( GESTURE_PINCH_IN, "GESTURE_PINCH_IN" ); // Pinch in gesture
	assignGlobalInt( GESTURE_PINCH_OUT, "GESTURE_PINCH_OUT" ); // Pinch out gesture
	/* CameraMode */
	assignGlobalInt( CAMERA_CUSTOM, "CAMERA_CUSTOM" ); // Custom camera
	assignGlobalInt( CAMERA_FREE, "CAMERA_FREE" ); // Free camera
	assignGlobalInt( CAMERA_ORBITAL, "CAMERA_ORBITAL" ); // Orbital camera
	assignGlobalInt( CAMERA_FIRST_PERSON, "CAMERA_FIRST_PERSON" ); // First person camera
	assignGlobalInt( CAMERA_THIRD_PERSON, "CAMERA_THIRD_PERSON" ); // Third person camera
	/* CameraProjections */
	assignGlobalInt( CAMERA_PERSPECTIVE, "CAMERA_PERSPECTIVE" ); // Perspective projection
	assignGlobalInt( CAMERA_ORTHOGRAPHIC, "CAMERA_ORTHOGRAPHIC" ); // Orthographic projection
	/* N-patchLayout */
	assignGlobalInt( NPATCH_NINE_PATCH, "NPATCH_NINE_PATCH" ); // Npatch layout: 3x3 tiles
	assignGlobalInt( NPATCH_THREE_PATCH_VERTICAL, "NPATCH_THREE_PATCH_VERTICAL" ); // Npatch layout: 1x3 tiles
	assignGlobalInt( NPATCH_THREE_PATCH_HORIZONTAL, "NPATCH_THREE_PATCH_HORIZONTAL" ); // Npatch layout: 3x1 tiles
	/* Colors */
	assignGlobalColor( LIGHTGRAY, "LIGHTGRAY" ); // Light Gray
	assignGlobalColor( GRAY, "GRAY" ); // Gray
	assignGlobalColor( DARKGRAY, "DARKGRAY" ); // Dark Gray
	assignGlobalColor( YELLOW, "YELLOW" ); // Yellow
	assignGlobalColor( GOLD, "GOLD" ); // Gold
	assignGlobalColor( ORANGE, "ORANGE" ); // Orange
	assignGlobalColor( PINK, "PINK" ); // Pink
	assignGlobalColor( RED, "RED" ); // Red
	assignGlobalColor( MAROON, "MAROON" ); // Maroon
	assignGlobalColor( GREEN, "GREEN" ); // Green
	assignGlobalColor( LIME, "LIME" ); // Lime
	assignGlobalColor( DARKGREEN, "DARKGREEN" ); // Dark Green
	assignGlobalColor( SKYBLUE, "SKYBLUE" ); // Sky Blue
	assignGlobalColor( BLUE, "BLUE" ); // Blue
	assignGlobalColor( DARKBLUE, "DARKBLUE" ); // Dark Blue
	assignGlobalColor( PURPLE, "PURPLE" ); // Purple
	assignGlobalColor( VIOLET, "VIOLET" ); // Violet
	assignGlobalColor( DARKPURPLE, "DARKPURPLE" ); // Dark Purple
	assignGlobalColor( BEIGE, "BEIGE" ); // Beige
	assignGlobalColor( BROWN, "BROWN" ); // Brown
	assignGlobalColor( DARKBROWN, "DARKBROWN" ); // Dark Brown
	assignGlobalColor( WHITE, "WHITE" ); // White
	assignGlobalColor( BLACK, "BLACK" ); // Black
	assignGlobalColor( BLANK, "BLANK" ); // Blank (Transparent)
	assignGlobalColor( MAGENTA, "MAGENTA" ); // Magenta
	assignGlobalColor( RAYWHITE, "RAYWHITE" ); // My own White (raylib logo)
	/* Math */
	assignGlobalFloat( PI, "PI" ); // Pi
	assignGlobalFloat( DEG2RAD, "DEG2RAD" ); // Degrees to radians
	assignGlobalFloat( RAD2DEG, "RAD2DEG" ); // Radians to degrees
	/* GuiControlState */
	assignGlobalInt( STATE_NORMAL, "STATE_NORMAL" );
	assignGlobalInt( STATE_FOCUSED, "STATE_FOCUSED" );
	assignGlobalInt( STATE_PRESSED, "STATE_PRESSED" );
	assignGlobalInt( STATE_DISABLED, "STATE_DISABLED" );
	/* GuiTextAlignment */
	assignGlobalInt( TEXT_ALIGN_LEFT, "TEXT_ALIGN_LEFT" );
	assignGlobalInt( TEXT_ALIGN_CENTER, "TEXT_ALIGN_CENTER" );
	assignGlobalInt( TEXT_ALIGN_RIGHT, "TEXT_ALIGN_RIGHT" );
	/* GuiControl */
	assignGlobalInt( DEFAULT, "DEFAULT" );
	assignGlobalInt( LABEL, "LABEL" ); // Used also for: LABELBUTTON
	assignGlobalInt( BUTTON, "BUTTON" );
	assignGlobalInt( TOGGLE, "TOGGLE" ); // Used also for: TOGGLEGROUP
	assignGlobalInt( SLIDER, "SLIDER" ); // Used also for: SLIDERBAR
	assignGlobalInt( PROGRESSBAR, "PROGRESSBAR" );
	assignGlobalInt( CHECKBOX, "CHECKBOX" );
	assignGlobalInt( COMBOBOX, "COMBOBOX" );
	assignGlobalInt( DROPDOWNBOX, "DROPDOWNBOX" );
	assignGlobalInt( TEXTBOX, "TEXTBOX" ); // Used also for: TEXTBOXMULTI
	assignGlobalInt( VALUEBOX, "VALUEBOX" );
	assignGlobalInt( SPINNER, "SPINNER" ); // Uses: BUTTON, VALUEBOX
	assignGlobalInt( LISTVIEW, "LISTVIEW" );
	assignGlobalInt( COLORPICKER, "COLORPICKER" );
	assignGlobalInt( SCROLLBAR, "SCROLLBAR" );
	assignGlobalInt( STATUSBAR, "STATUSBAR" );
	/* GuiControlProperty */
	assignGlobalInt( BORDER_COLOR_NORMAL, "BORDER_COLOR_NORMAL" );
	assignGlobalInt( BASE_COLOR_NORMAL, "BASE_COLOR_NORMAL" );
	assignGlobalInt( TEXT_COLOR_NORMAL, "TEXT_COLOR_NORMAL" );
	assignGlobalInt( BORDER_COLOR_FOCUSED, "BORDER_COLOR_FOCUSED" );
	assignGlobalInt( BASE_COLOR_FOCUSED, "BASE_COLOR_FOCUSED" );
	assignGlobalInt( TEXT_COLOR_FOCUSED, "TEXT_COLOR_FOCUSED" );
	assignGlobalInt( BORDER_COLOR_PRESSED, "BORDER_COLOR_PRESSED" );
	assignGlobalInt( BASE_COLOR_PRESSED, "BASE_COLOR_PRESSED" );
	assignGlobalInt( TEXT_COLOR_PRESSED, "TEXT_COLOR_PRESSED" );
	assignGlobalInt( BORDER_COLOR_DISABLED, "BORDER_COLOR_DISABLED" );
	assignGlobalInt( BASE_COLOR_DISABLED, "BASE_COLOR_DISABLED" );
	assignGlobalInt( TEXT_COLOR_DISABLED, "TEXT_COLOR_DISABLED" );
	assignGlobalInt( BORDER_WIDTH, "BORDER_WIDTH" );
	assignGlobalInt( TEXT_PADDING, "TEXT_PADDING" );
	assignGlobalInt( TEXT_ALIGNMENT, "TEXT_ALIGNMENT" );
	assignGlobalInt( RESERVED, "RESERVED" );
	/* GuiDefaultProperty */
	assignGlobalInt( TEXT_SIZE, "TEXT_SIZE" ); // Text size (glyphs max height)
	assignGlobalInt( TEXT_SPACING, "TEXT_SPACING" ); // Text spacing between glyphs
	assignGlobalInt( LINE_COLOR, "LINE_COLOR" ); // Line control color
	assignGlobalInt( BACKGROUND_COLOR, "BACKGROUND_COLOR" ); // Background color
	/* GuiToggleProperty */
	assignGlobalInt( GROUP_PADDING, "GROUP_PADDING" ); // ToggleGroup separation between toggles
	/* GuiSliderProperty */
	assignGlobalInt( SLIDER_WIDTH, "SLIDER_WIDTH" ); // Slider size of internal bar
	assignGlobalInt( SLIDER_PADDING, "SLIDER_PADDING" ); // Slider/SliderBar internal bar padding
	/* GuiProgressBarProperty */
	assignGlobalInt( PROGRESS_PADDING, "PROGRESS_PADDING" ); // ProgressBar internal padding
	/* GuiScrollBarProperty */
	assignGlobalInt( ARROWS_SIZE, "ARROWS_SIZE" );
	assignGlobalInt( ARROWS_VISIBLE, "ARROWS_VISIBLE" );
	assignGlobalInt( SCROLL_SLIDER_PADDING, "SCROLL_SLIDER_PADDING" ); // (SLIDERBAR, SLIDER_PADDING)
	assignGlobalInt( SCROLL_SLIDER_SIZE, "SCROLL_SLIDER_SIZE" );
	assignGlobalInt( SCROLL_PADDING, "SCROLL_PADDING" );
	assignGlobalInt( SCROLL_SPEED, "SCROLL_SPEED" );
	/* GuiCheckBoxProperty */
	assignGlobalInt( CHECK_PADDING, "CHECK_PADDING" ); // CheckBox internal check padding
	/* GuiComboBoxProperty */
	assignGlobalInt( COMBO_BUTTON_WIDTH, "COMBO_BUTTON_WIDTH" ); // ComboBox right button width
	assignGlobalInt( COMBO_BUTTON_SPACING, "COMBO_BUTTON_SPACING" ); // ComboBox button separation
	/* GuiDropdownBoxProperty */
	assignGlobalInt( ARROW_PADDING, "ARROW_PADDING" ); // DropdownBox arrow separation from border and items
	assignGlobalInt( DROPDOWN_ITEMS_SPACING, "DROPDOWN_ITEMS_SPACING" ); // DropdownBox items separation
	/* GuiTextBoxProperty */
	assignGlobalInt( TEXT_INNER_PADDING, "TEXT_INNER_PADDING" ); // TextBox/TextBoxMulti/ValueBox/Spinner inner text padding
	assignGlobalInt( TEXT_LINES_SPACING, "TEXT_LINES_SPACING" ); // TextBoxMulti lines separation
	/* GuiSpinnerProperty */
	assignGlobalInt( SPIN_BUTTON_WIDTH, "SPIN_BUTTON_WIDTH" ); // Spinner left/right buttons width
	assignGlobalInt( SPIN_BUTTON_SPACING, "SPIN_BUTTON_SPACING" ); // Spinner buttons separation
	/* GuiListViewProperty */
	assignGlobalInt( LIST_ITEMS_HEIGHT, "LIST_ITEMS_HEIGHT" ); // ListView items height
	assignGlobalInt( LIST_ITEMS_SPACING, "LIST_ITEMS_SPACING" ); // ListView items separation
	assignGlobalInt( SCROLLBAR_WIDTH, "SCROLLBAR_WIDTH" ); // ListView scrollbar size (usually width)
	assignGlobalInt( SCROLLBAR_SIDE, "SCROLLBAR_SIDE" ); // ListView scrollbar side (0-left, 1-right)
	/* GuiColorPickerProperty */
	assignGlobalInt( COLOR_SELECTOR_SIZE, "COLOR_SELECTOR_SIZE" );
	assignGlobalInt( HUEBAR_WIDTH, "HUEBAR_WIDTH" ); // ColorPicker right hue bar width
	assignGlobalInt( HUEBAR_PADDING, "HUEBAR_PADDING" ); // ColorPicker right hue bar separation from panel
	assignGlobalInt( HUEBAR_SELECTOR_HEIGHT, "HUEBAR_SELECTOR_HEIGHT" ); // ColorPicker right hue bar selector height
	assignGlobalInt( HUEBAR_SELECTOR_OVERFLOW, "HUEBAR_SELECTOR_OVERFLOW" ); // ColorPicker right hue bar selector overflow
	/* LightType */
	assignGlobalInt( LIGHT_DIRECTIONAL, "LIGHT_DIRECTIONAL" ); // Directional light
	assignGlobalInt( LIGHT_POINT, "LIGHT_POINT" ); // Point light
	/* RLGL Default internal render batch elements limits */
	assignGlobalInt( RL_DEFAULT_BATCH_BUFFER_ELEMENTS, "RL_DEFAULT_BATCH_BUFFER_ELEMENTS" ); // Default internal render batch elements limits
	assignGlobalInt( RL_DEFAULT_BATCH_BUFFERS, "RL_DEFAULT_BATCH_BUFFERS" ); // Default number of batch buffers (multi-buffering)
	assignGlobalInt( RL_DEFAULT_BATCH_DRAWCALLS, "RL_DEFAULT_BATCH_DRAWCALLS" ); // Default number of batch draw calls (by state changes: mode, texture)
	assignGlobalInt( RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS, "RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS" ); // Maximum number of textures units that can be activated on batch drawing (SetShaderValueTexture())
	/* RLGL Internal Matrix stack */
	assignGlobalInt( RL_MAX_MATRIX_STACK_SIZE, "RL_MAX_MATRIX_STACK_SIZE" ); // Maximum size of internal Matrix stack
	/* RLGL Shader limits */
	assignGlobalInt( RL_MAX_SHADER_LOCATIONS, "RL_MAX_SHADER_LOCATIONS" ); // Maximum number of shader locations supported
	/* RLGL Projection matrix culling */
	assignGlobalDouble( RL_CULL_DISTANCE_NEAR, "RL_CULL_DISTANCE_NEAR" ); // Default projection matrix near cull distance
	assignGlobalDouble( RL_CULL_DISTANCE_FAR, "RL_CULL_DISTANCE_FAR" ); // Default projection matrix far cull distance
	/* RLGL Texture parameters */
	assignGlobalInt( RL_TEXTURE_WRAP_S, "RL_TEXTURE_WRAP_S" ); // GL_TEXTURE_WRAP_S
	assignGlobalInt( RL_TEXTURE_WRAP_T, "RL_TEXTURE_WRAP_T" ); // GL_TEXTURE_WRAP_T
	assignGlobalInt( RL_TEXTURE_MAG_FILTER, "RL_TEXTURE_MAG_FILTER" ); // GL_TEXTURE_MAG_FILTER
	assignGlobalInt( RL_TEXTURE_MIN_FILTER, "RL_TEXTURE_MIN_FILTER" ); // GL_TEXTURE_MIN_FILTER
	assignGlobalInt( RL_TEXTURE_FILTER_NEAREST, "RL_TEXTURE_FILTER_NEAREST" ); // GL_NEAREST
	assignGlobalInt( RL_TEXTURE_FILTER_LINEAR, "RL_TEXTURE_FILTER_LINEAR" ); // GL_LINEAR
	assignGlobalInt( RL_TEXTURE_FILTER_MIP_NEAREST, "RL_TEXTURE_FILTER_MIP_NEAREST" ); // GL_NEAREST_MIPMAP_NEAREST
	assignGlobalInt( RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR, "RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR" ); // GL_NEAREST_MIPMAP_LINEAR
	assignGlobalInt( RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST, "RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST" ); // GL_LINEAR_MIPMAP_NEAREST
	assignGlobalInt( RL_TEXTURE_FILTER_MIP_LINEAR, "RL_TEXTURE_FILTER_MIP_LINEAR" ); // GL_LINEAR_MIPMAP_LINEAR
	assignGlobalInt( RL_TEXTURE_FILTER_ANISOTROPIC, "RL_TEXTURE_FILTER_ANISOTROPIC" ); // Anisotropic filter (custom identifier)
	assignGlobalInt( RL_TEXTURE_MIPMAP_BIAS_RATIO, "RL_TEXTURE_MIPMAP_BIAS_RATIO" ); // Texture mipmap bias, percentage ratio (custom identifier)
	assignGlobalInt( RL_TEXTURE_WRAP_REPEAT, "RL_TEXTURE_WRAP_REPEAT" ); // GL_REPEAT
	assignGlobalInt( RL_TEXTURE_WRAP_CLAMP, "RL_TEXTURE_WRAP_CLAMP" ); // GL_CLAMP_TO_EDGE
	assignGlobalInt( RL_TEXTURE_WRAP_MIRROR_REPEAT, "RL_TEXTURE_WRAP_MIRROR_REPEAT" ); // GL_MIRRORED_REPEAT
	assignGlobalInt( RL_TEXTURE_WRAP_MIRROR_CLAMP, "RL_TEXTURE_WRAP_MIRROR_CLAMP" ); // GL_MIRROR_CLAMP_EXT
	/* RLGL Matrix modes (equivalent to OpenGL) */
	assignGlobalInt( RL_MODELVIEW, "RL_MODELVIEW" ); // GL_MODELVIEW
	assignGlobalInt( RL_PROJECTION, "RL_PROJECTION" ); // GL_PROJECTION
	assignGlobalInt( RL_TEXTURE, "RL_TEXTURE" ); // GL_TEXTURE
	/* RLGL Primitive assembly draw modes */
	assignGlobalInt( RL_LINES, "RL_LINES" ); // GL_LINES
	assignGlobalInt( RL_TRIANGLES, "RL_TRIANGLES" ); // GL_TRIANGLES
	assignGlobalInt( RL_QUADS, "RL_QUADS" ); // GL_QUADS
	/* RLGL GL equivalent data types */
	assignGlobalInt( RL_UNSIGNED_BYTE, "RL_UNSIGNED_BYTE" ); // GL_UNSIGNED_BYTE
	assignGlobalInt( RL_FLOAT, "RL_FLOAT" ); // GL_FLOAT
	/* RLGL GL buffer usage hint */
	assignGlobalInt( RL_STREAM_DRAW, "RL_STREAM_DRAW" ); // GL_STREAM_DRAW
	assignGlobalInt( RL_STREAM_READ, "RL_STREAM_READ" ); // GL_STREAM_READ
	assignGlobalInt( RL_STREAM_COPY, "RL_STREAM_COPY" ); // GL_STREAM_COPY
	assignGlobalInt( RL_STATIC_DRAW, "RL_STATIC_DRAW" ); // GL_STATIC_DRAW
	assignGlobalInt( RL_STATIC_READ, "RL_STATIC_READ" ); // GL_STATIC_READ
	assignGlobalInt( RL_STATIC_COPY, "RL_STATIC_COPY" ); // GL_STATIC_COPY
	assignGlobalInt( RL_DYNAMIC_DRAW, "RL_DYNAMIC_DRAW" ); // GL_DYNAMIC_DRAW
	assignGlobalInt( RL_DYNAMIC_READ, "RL_DYNAMIC_READ" ); // GL_DYNAMIC_READ
	assignGlobalInt( RL_DYNAMIC_COPY, "RL_DYNAMIC_COPY" ); // GL_DYNAMIC_COPY
	/* RLGL Shader type */
	assignGlobalInt( RL_FRAGMENT_SHADER, "RL_FRAGMENT_SHADER" ); // GL_FRAGMENT_SHADER
	assignGlobalInt( RL_VERTEX_SHADER, "RL_VERTEX_SHADER" ); // GL_VERTEX_SHADER
	assignGlobalInt( RL_COMPUTE_SHADER, "RL_COMPUTE_SHADER" ); // GL_COMPUTE_SHADER
	/* RLGL GlVersion */
	assignGlobalInt( RL_ZERO, "RL_ZERO" ); // GL_ZERO
	assignGlobalInt( RL_ONE, "RL_ONE" ); // GL_ONE
	assignGlobalInt( RL_SRC_COLOR, "RL_SRC_COLOR" ); // GL_SRC_COLOR
	assignGlobalInt( RL_ONE_MINUS_SRC_COLOR, "RL_ONE_MINUS_SRC_COLOR" ); // GL_ONE_MINUS_SRC_COLOR
	assignGlobalInt( RL_SRC_ALPHA, "RL_SRC_ALPHA" ); // GL_SRC_ALPHA
	assignGlobalInt( RL_ONE_MINUS_SRC_ALPHA, "RL_ONE_MINUS_SRC_ALPHA" ); // GL_ONE_MINUS_SRC_ALPHA
	assignGlobalInt( RL_DST_ALPHA, "RL_DST_ALPHA" ); // GL_DST_ALPHA
	assignGlobalInt( RL_ONE_MINUS_DST_ALPHA, "RL_ONE_MINUS_DST_ALPHA" ); // GL_ONE_MINUS_DST_ALPHA
	assignGlobalInt( RL_DST_COLOR, "RL_DST_COLOR" ); // GL_DST_COLOR
	assignGlobalInt( RL_ONE_MINUS_DST_COLOR, "RL_ONE_MINUS_DST_COLOR" ); // GL_ONE_MINUS_DST_COLOR
	assignGlobalInt( RL_SRC_ALPHA_SATURATE, "RL_SRC_ALPHA_SATURATE" ); // GL_SRC_ALPHA_SATURATE
	assignGlobalInt( RL_CONSTANT_COLOR, "RL_CONSTANT_COLOR" ); // GL_CONSTANT_COLOR
	assignGlobalInt( RL_ONE_MINUS_CONSTANT_COLOR, "RL_ONE_MINUS_CONSTANT_COLOR" ); // GL_ONE_MINUS_CONSTANT_COLOR
	assignGlobalInt( RL_CONSTANT_ALPHA, "RL_CONSTANT_ALPHA" ); // GL_CONSTANT_ALPHA
	assignGlobalInt( RL_ONE_MINUS_CONSTANT_ALPHA, "RL_ONE_MINUS_CONSTANT_ALPHA" ); // GL_ONE_MINUS_CONSTANT_ALPHA
	/* RLGL GL blending functions/equations */
	assignGlobalInt( RL_FUNC_ADD, "RL_FUNC_ADD" ); // GL_FUNC_ADD
	assignGlobalInt( RL_MIN, "RL_MIN" ); // GL_MIN
	assignGlobalInt( RL_MAX, "RL_MAX" ); // GL_MAX
	assignGlobalInt( RL_FUNC_SUBTRACT, "RL_FUNC_SUBTRACT" ); // GL_FUNC_SUBTRACT
	assignGlobalInt( RL_FUNC_REVERSE_SUBTRACT, "RL_FUNC_REVERSE_SUBTRACT" ); // GL_FUNC_REVERSE_SUBTRACT
	assignGlobalInt( RL_BLEND_EQUATION, "RL_BLEND_EQUATION" ); // GL_BLEND_EQUATION
	assignGlobalInt( RL_BLEND_EQUATION_RGB, "RL_BLEND_EQUATION_RGB" ); // GL_BLEND_EQUATION_RGB   // (Same as BLEND_EQUATION)
	assignGlobalInt( RL_BLEND_EQUATION_ALPHA, "RL_BLEND_EQUATION_ALPHA" ); // GL_BLEND_EQUATION_ALPHA
	assignGlobalInt( RL_BLEND_DST_RGB, "RL_BLEND_DST_RGB" ); // GL_BLEND_DST_RGB
	assignGlobalInt( RL_BLEND_SRC_RGB, "RL_BLEND_SRC_RGB" ); // GL_BLEND_SRC_RGB
	assignGlobalInt( RL_BLEND_DST_ALPHA, "RL_BLEND_DST_ALPHA" ); // GL_BLEND_DST_ALPHA
	assignGlobalInt( RL_BLEND_SRC_ALPHA, "RL_BLEND_SRC_ALPHA" ); // GL_BLEND_SRC_ALPHA
	assignGlobalInt( RL_BLEND_COLOR, "RL_BLEND_COLOR" ); // GL_BLEND_COLOR
	/* RLGL GlVersion */
	assignGlobalInt( RL_OPENGL_11, "RL_OPENGL_11" ); // OpenGL 1.1
	assignGlobalInt( RL_OPENGL_21, "RL_OPENGL_21" ); // OpenGL 2.1 (GLSL 120)
	assignGlobalInt( RL_OPENGL_33, "RL_OPENGL_33" ); // OpenGL 3.3 (GLSL 330)
	assignGlobalInt( RL_OPENGL_43, "RL_OPENGL_43" ); // OpenGL 4.3 (using GLSL 330)
	assignGlobalInt( RL_OPENGL_ES_20, "RL_OPENGL_ES_20" ); // OpenGL ES 2.0 (GLSL 100)
	/* RLGL Framebuffer attachment type */
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL0, "RL_ATTACHMENT_COLOR_CHANNEL0" ); // Framebuffer attachment type: color 0
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL1, "RL_ATTACHMENT_COLOR_CHANNEL1" ); // Framebuffer attachment type: color 1
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL2, "RL_ATTACHMENT_COLOR_CHANNEL2" ); // Framebuffer attachment type: color 2
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL3, "RL_ATTACHMENT_COLOR_CHANNEL3" ); // Framebuffer attachment type: color 3
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL4, "RL_ATTACHMENT_COLOR_CHANNEL4" ); // Framebuffer attachment type: color 4
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL5, "RL_ATTACHMENT_COLOR_CHANNEL5" ); // Framebuffer attachment type: color 5
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL6, "RL_ATTACHMENT_COLOR_CHANNEL6" ); // Framebuffer attachment type: color 6
	assignGlobalInt( RL_ATTACHMENT_COLOR_CHANNEL7, "RL_ATTACHMENT_COLOR_CHANNEL7" ); // Framebuffer attachment type: color 7
	assignGlobalInt( RL_ATTACHMENT_DEPTH, "RL_ATTACHMENT_DEPTH" ); // Framebuffer attachment type: depth
	assignGlobalInt( RL_ATTACHMENT_STENCIL, "RL_ATTACHMENT_STENCIL" ); // Framebuffer attachment type: stencil
	/* RLGL Framebuffer texture attachment type */
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_POSITIVE_X, "RL_ATTACHMENT_CUBEMAP_POSITIVE_X" ); // Framebuffer texture attachment type: cubemap, +X side
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_NEGATIVE_X, "RL_ATTACHMENT_CUBEMAP_NEGATIVE_X" ); // Framebuffer texture attachment type: cubemap, -X side
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_POSITIVE_Y, "RL_ATTACHMENT_CUBEMAP_POSITIVE_Y" ); // Framebuffer texture attachment type: cubemap, +Y side
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y, "RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y" ); // Framebuffer texture attachment type: cubemap, -Y side
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_POSITIVE_Z, "RL_ATTACHMENT_CUBEMAP_POSITIVE_Z" ); // Framebuffer texture attachment type: cubemap, +Z side
	assignGlobalInt( RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z, "RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z" ); // Framebuffer texture attachment type: cubemap, -Z side
	assignGlobalInt( RL_ATTACHMENT_TEXTURE2D, "RL_ATTACHMENT_TEXTURE2D" ); // Framebuffer texture attachment type: texture2d
	assignGlobalInt( RL_ATTACHMENT_RENDERBUFFER, "RL_ATTACHMENT_RENDERBUFFER" ); // Framebuffer texture attachment type: renderbuffer
	/* RLGL CullMode */
	assignGlobalInt( RL_CULL_FACE_FRONT, "RL_CULL_FACE_FRONT" );
	assignGlobalInt( RL_CULL_FACE_BACK, "RL_CULL_FACE_BACK" );
	/* OpenGL */
	assignGlobalInt( GL_COLOR_BUFFER_BIT, "GL_COLOR_BUFFER_BIT" );
	assignGlobalInt( GL_DEPTH_BUFFER_BIT, "GL_DEPTH_BUFFER_BIT" );
	assignGlobalInt( GL_STENCIL_BUFFER_BIT, "GL_STENCIL_BUFFER_BIT" );
	assignGlobalInt( GL_NEAREST, "GL_NEAREST" );
	assignGlobalInt( GL_LINEAR, "GL_LINEAR" );
	/* GLFW API tokens. */
	assignGlobalInt( GLFW_RELEASE, "GLFW_RELEASE" ); // The key or mouse button was released
	assignGlobalInt( GLFW_PRESS, "GLFW_PRESS" ); // The key or mouse button was pressed
	assignGlobalInt( GLFW_REPEAT, "GLFW_REPEAT" ); // The key was held down until it repeated
	/* CBuffer Data Types */
	assignGlobalInt( BUFFER_UNSIGNED_CHAR, "BUFFER_UNSIGNED_CHAR" ); // C type unsigned char
	assignGlobalInt( BUFFER_UNSIGNED_SHORT, "BUFFER_UNSIGNED_SHORT" ); // C type unsigned short
	assignGlobalInt( BUFFER_UNSIGNED_INT, "BUFFER_UNSIGNED_INT" ); // C type unsigned int
	assignGlobalInt( BUFFER_CHAR, "BUFFER_CHAR" ); // C type char
	assignGlobalInt( BUFFER_SHORT, "BUFFER_SHORT" ); // C type short
	assignGlobalInt( BUFFER_INT, "BUFFER_INT" ); // C type int
	assignGlobalInt( BUFFER_FLOAT, "BUFFER_FLOAT" ); // C type float
	assignGlobalInt( BUFFER_DOUBLE, "BUFFER_DOUBLE" ); // C type double
	/* Window Events. */
	assignGlobalInt( EVENT_WINDOW_SIZE, "EVENT_WINDOW_SIZE" ); // GLFW event window size changed
	assignGlobalInt( EVENT_WINDOW_MAXIMIZE, "EVENT_WINDOW_MAXIMIZE" ); // GLFW event window maximize
	assignGlobalInt( EVENT_WINDOW_ICONYFY, "EVENT_WINDOW_ICONYFY" ); // GLFW event window iconify
	assignGlobalInt( EVENT_WINDOW_FOCUS, "EVENT_WINDOW_FOCUS" ); // GLFW event window focus
	assignGlobalInt( EVENT_WINDOW_DROP, "EVENT_WINDOW_DROP" ); // GLFW event window drop
	/* Input Events. */
	assignGlobalInt( EVENT_KEY, "EVENT_KEY" ); // GLFW event keyboard key
	assignGlobalInt( EVENT_CHAR, "EVENT_CHAR" ); // GLFW event Unicode character
	assignGlobalInt( EVENT_MOUSE_BUTTON, "EVENT_MOUSE_BUTTON" ); // GLFW event mouse button
	assignGlobalInt( EVENT_MOUSE_CURSOR_POS, "EVENT_MOUSE_CURSOR_POS" ); // GLFW event cursor position
	assignGlobalInt( EVENT_MOUSE_SCROLL, "EVENT_MOUSE_SCROLL" ); // GLFW event mouse scroll
	assignGlobalInt( EVENT_CURSOR_ENTER, "EVENT_CURSOR_ENTER" ); // GLFW event cursor enter/leave
/*DOC_END*/

	lua_pop( L, -1 );
}

// Custom logging funtion.
static void logCustom( int logLevel, const char *text, va_list args ) {
	char string[ STRING_LEN ] = {'\0'};
	char msg[ STRING_LEN ] = {'\0'};

	vsprintf( string, text, args );

    switch ( logLevel ) {
        case LOG_ALL: sprintf( msg, "ALL: %s", string ); break;
        case LOG_TRACE: sprintf( msg, "TRACE: %s", string ); break;
        case LOG_DEBUG: sprintf( msg, "DEBUG: %s", string ); break;
        case LOG_INFO: sprintf( msg, "INFO: %s", string ); break;
        case LOG_WARNING: sprintf( msg, "WARNING: %s", string ); break;
        case LOG_ERROR: sprintf( msg, "ERROR: %s", string ); break;
        case LOG_FATAL: sprintf( msg, "FATAL: %s", string ); break;
        default: break;
    }
	printf( "%s\n", msg );

	/* Call Lua log function if exists. */
	lua_State *L = state->luaState;

	/* Prevent calling lua log function when lua is already shutdown. */
	if ( L != NULL ) {
		lua_pushcfunction( L, luaTraceback );
		int tracebackidx = lua_gettop( L );

		lua_getglobal( L, "RL" );
		lua_getfield( L, -1, "log" );

		if ( lua_isfunction( L, -1 ) ) {
			lua_pushinteger( L, logLevel );
			lua_pushstring( L, msg );

			if ( lua_pcall( L, 2, 0, tracebackidx ) != 0 ) {
				TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
				state->run = false;
				lua_pop( L, -1 );
				return;
			}
		}
		lua_pop( L, -1 );
	}
}

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
		lua_pushinteger( L, EVENT_WINDOW_SIZE );
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
		lua_pushinteger( L, EVENT_WINDOW_MAXIMIZE );
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
		lua_pushinteger( L, EVENT_WINDOW_ICONYFY );
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
		lua_pushinteger( L, EVENT_WINDOW_FOCUS );
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
		lua_pushinteger( L, EVENT_WINDOW_DROP );
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
		lua_pushinteger( L, EVENT_KEY );
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
		lua_pushinteger( L, EVENT_CHAR );
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
		lua_pushinteger( L, EVENT_MOUSE_BUTTON );
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
		lua_pushinteger( L, EVENT_MOUSE_CURSOR_POS );
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
		lua_pushinteger( L, EVENT_MOUSE_SCROLL );
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
		lua_pushinteger( L, EVENT_CURSOR_ENTER );
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

bool luaInit( int argn, const char **argc ) {
	state->luaState = luaL_newstate();
	lua_State *L = state->luaState;

    luaL_openlibs( L );

	if ( L == NULL ) {
		TraceLog( LOG_WARNING, "%s", "Failed to init Lua" );
		return false;
	}
	/* Define object types. */
	defineBuffer();
	defineImage();
	defineTexture();
	defineRenderTexture();
	defineCamera2D();
	defineCamera3D();
	defineShader();
	defineFont();
	defineWave();
	defineSound();
	defineMusic();
	defineLight();
	defineMaterial();
	defineMesh();
	defineModel();
	defineModelAnimation();
	/* Define globals. */
	defineGlobals();

	/* Set arguments. */
	lua_getglobal( L, "RL" );
	lua_newtable( L );
	lua_setfield( L, -2, "arg" );
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "arg" );

	for ( int i = 0; i < argn; i++ ) {
		lua_pushstring( L, argc[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	lua_pop( L, -1 );

	return true;
}

int luaTraceback( lua_State *L ) {
	lua_getglobal( L, "debug" );

	if ( !lua_istable( L, -1 ) ) {
		lua_pop( L, 1 );
		return 1;
	}
	lua_getfield( L, -1, "traceback" );

	if ( !lua_isfunction( L, -1 ) ) {
		lua_pop( L, 2 );
		return 1;
	}
	lua_pushvalue( L, 1 ); // pass error message
	lua_pushinteger( L, 2 ); // skip this function and traceback
	lua_call( L, 2, 1 ); // call debug.traceback

	return 1;
}

bool luaCallMain() {
	lua_State *L = state->luaState;

	char path[ STRING_LEN ] = { '\0' };

/* If web, set path to resources folder. */
#ifdef EMSCRIPTEN
	sprintf( path, "resources/main.lua" );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		sprintf( path, "resources/main" );
	}
#else
	sprintf( path, "%smain.lua", state->exePath );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		sprintf( path, "%smain", state->exePath );
	}
#endif
    luaL_dofile( L, path );

	/* Check errors in main.lua */
	if ( lua_tostring( state->luaState, -1 ) ) {
		TraceLog( LOG_ERROR, "Lua error: %s\n", lua_tostring( state->luaState, -1 ) );
	}
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	/* Apply custom callback here. */
	SetTraceLogCallback( logCustom );

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

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "init" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			return false;
		}
	}
	//TODO Should this be removed?
	else {
		TraceLog( LOG_ERROR, "%s", "No Lua init found!" );
        return false;
    }
	lua_pop( L, -1 );

	return state->run;
}

void luaCallProcess() {
    lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "process" );

    if ( lua_isfunction( L, -1 ) ) {
        lua_pushnumber( L, GetFrameTime() );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
			lua_pop( L, -1 );
 	    	return;
        }
    }
	lua_pop( L, -1 );
}

void luaCallDraw() {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "draw" );

    if ( lua_isfunction( L, -1 ) ) {
		BeginDrawing();

        if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }

		EndDrawing();
    }
	lua_pop( L, -1 );
}

void luaCallExit() {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "exit" );

    if ( lua_isfunction( L, -1 ) ) {
        if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }
    }
	lua_pop( L, -1 );
}

void luaRegister() {
	lua_State *L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Core. */
		/* Window-related functions. */
	assingGlobalFunction( "IsWindowReady", lcoreIsWindowReady );
	assingGlobalFunction( "IsWindowFullscreen", lcoreIsWindowFullscreen );
	assingGlobalFunction( "IsWindowHidden", lcoreIsWindowHidden );
	assingGlobalFunction( "IsWindowMinimized", lcoreIsWindowMinimized );
	assingGlobalFunction( "IsWindowMaximized", lcoreIsWindowMaximized );
	assingGlobalFunction( "IsWindowFocused", lcoreIsWindowFocused );
	assingGlobalFunction( "SetWindowMonitor", lcoreSetWindowMonitor );
	assingGlobalFunction( "SetWindowPosition", lcoreSetWindowPosition );
	assingGlobalFunction( "SetWindowSize", lcoreSetWindowSize );
	assingGlobalFunction( "SetWindowOpacity", lcoreSetWindowOpacity );
	assingGlobalFunction( "GetWindowHandle", lcoreGetWindowHandle );
	assingGlobalFunction( "SetWindowMinSize", lcoreSetWindowMinSize );
	assingGlobalFunction( "GetMonitorPosition", lcoreGetMonitorPosition );
	assingGlobalFunction( "GetMonitorSize", lcoreGetMonitorSize );
	assingGlobalFunction( "GetWindowPosition", lcoreGetWindowPosition );
	assingGlobalFunction( "GetScreenSize", lcoreGetScreenSize );
	assingGlobalFunction( "SetWindowState", lcoreSetWindowState );
	assingGlobalFunction( "IsWindowState", lcoreIsWindowState );
	assingGlobalFunction( "ClearWindowState", lcoreClearWindowState );
	assingGlobalFunction( "IsWindowResized", lcoreIsWindowResized );
	assingGlobalFunction( "SetWindowIcon", lcoreSetWindowIcon );
	assingGlobalFunction( "SetWindowIcons", lcoreSetWindowIcons );
	assingGlobalFunction( "SetWindowTitle", lcoreSetWindowTitle );
	assingGlobalFunction( "GetMonitorCount", lcoreGetMonitorCount );
	assingGlobalFunction( "GetCurrentMonitor", lcoreGetCurrentMonitor );
	assingGlobalFunction( "GetMonitorPhysicalSize", lcoreGetMonitorPhysicalSize );
	assingGlobalFunction( "GetMonitorRefreshRate", lcoreGetMonitorRefreshRate );
	assingGlobalFunction( "GetWindowScaleDPI", lcoreGetWindowScaleDPI );
	assingGlobalFunction( "GetMonitorName", lcoreGetMonitorName );
	assingGlobalFunction( "CloseWindow", lcoreCloseWindow );
	assingGlobalFunction( "SetClipboardText", lcoreSetClipboardText );
	assingGlobalFunction( "GetClipboardText", lcoreGetClipboardText );
		/* Cursor-related functions. */
	assingGlobalFunction( "ShowCursor", lcoreShowCursor );
	assingGlobalFunction( "HideCursor", lcoreHideCursor );
	assingGlobalFunction( "IsCursorHidden", lcoreIsCursorHidden );
	assingGlobalFunction( "EnableCursor", lcoreEnableCursor );
	assingGlobalFunction( "DisableCursor", lcoreDisableCursor );
	assingGlobalFunction( "IsCursorOnScreen", lcoreIsCursorOnScreen );
		/* Drawing-related functions. */
	assingGlobalFunction( "ClearBackground", lcoreClearBackground );
	assingGlobalFunction( "BeginDrawing", lcoreBeginDrawing );
	assingGlobalFunction( "EndDrawing", lcoreEndDrawing );
	assingGlobalFunction( "BeginMode2D", lcoreBeginMode2D );
	assingGlobalFunction( "EndMode2D", lcoreEndMode2D );
	assingGlobalFunction( "BeginMode3D", lcoreBeginMode3D );
	assingGlobalFunction( "EndMode3D", lcoreEndMode3D );
	assingGlobalFunction( "BeginTextureMode", lcoreBeginTextureMode );
	assingGlobalFunction( "EndTextureMode", lcoreEndTextureMode );
	assingGlobalFunction( "BeginShaderMode", lcoreBeginShaderMode );
	assingGlobalFunction( "EndShaderMode", lcoreEndShaderMode );
	assingGlobalFunction( "BeginBlendMode", lcoreBeginBlendMode );
	assingGlobalFunction( "EndBlendMode", lcoreEndBlendMode );
	assingGlobalFunction( "BeginScissorMode", lcoreBeginScissorMode );
	assingGlobalFunction( "EndScissorMode", lcoreEndScissorMode );
		/* Shader management functions. */
	assingGlobalFunction( "LoadShader", lcoreLoadShader );
	assingGlobalFunction( "LoadShaderFromMemory", lcoreLoadShaderFromMemory );
	assingGlobalFunction( "IsShaderReady", lcoreIsShaderReady );
	assingGlobalFunction( "GetShaderLocation", lcoreGetShaderLocation );
	assingGlobalFunction( "GetShaderLocationAttrib", lcoreGetShaderLocationAttrib );
	assingGlobalFunction( "SetShaderLocationIndex", lcoreSetShaderLocationIndex );
	assingGlobalFunction( "GetShaderLocationIndex", lcoreGetShaderLocationIndex );
	assingGlobalFunction( "SetShaderValueMatrix", lcoreSetShaderValueMatrix );
	assingGlobalFunction( "SetShaderValueTexture", lcoreSetShaderValueTexture );
	assingGlobalFunction( "SetShaderValue", lcoreSetShaderValue );
	assingGlobalFunction( "SetShaderValueV", lcoreSetShaderValueV );
	assingGlobalFunction( "UnloadShader", lcoreUnloadShader );
		/* Screen-space-related functions. */
	assingGlobalFunction( "GetMouseRay", lcoreGetMouseRay );
	assingGlobalFunction( "GetCameraMatrix", lcoreGetCameraMatrix );
	assingGlobalFunction( "GetCameraMatrix2D", lcoreGetCameraMatrix2D );
	assingGlobalFunction( "GetWorldToScreen", lcoreGetWorldToScreen );
	assingGlobalFunction( "GetWorldToScreenEx", lcoreGetWorldToScreenEx );
	assingGlobalFunction( "GetWorldToScreen2D", lcoreGetWorldToScreen2D );
	assingGlobalFunction( "GetScreenToWorld2D", lcoreGetScreenToWorld2D );
		/* Timing-related functions. */
	assingGlobalFunction( "SetTargetFPS", lcoreSetTargetFPS );
	assingGlobalFunction( "GetFPS", lcoreGetFPS );
	assingGlobalFunction( "GetFrameTime", lcoreGetFrameTime );
	assingGlobalFunction( "GetTime", lcoreGetTime );
		/* Misc. functions. */
	assingGlobalFunction( "TakeScreenshot", lcoreTakeScreenshot );
	assingGlobalFunction( "SetConfigFlags", lcoreSetConfigFlags );
	assingGlobalFunction( "TraceLog", lcoreTraceLog );
	assingGlobalFunction( "SetTraceLogLevel", lcoreSetTraceLogLevel );
	assingGlobalFunction( "SetLogLevelInvalid", lcoreSetLogLevelInvalid );
	assingGlobalFunction( "GetLogLevelInvalid", lcoreGetLogLevelInvalid );
	assingGlobalFunction( "OpenURL", lcoreOpenURL );
	assingGlobalFunction( "IsGCUnloadEnabled", lcoreIsGCUnloadEnabled );
		/* Files management functions. */
	assingGlobalFunction( "GetBasePath", lcoreGetBasePath );
	assingGlobalFunction( "FileExists", lcoreFileExists );
	assingGlobalFunction( "DirectoryExists", lcoreDirectoryExists );
	assingGlobalFunction( "IsFileExtension", lcoreIsFileExtension );
	assingGlobalFunction( "GetFileLength", lcoreGetFileLength );
	assingGlobalFunction( "GetFileExtension", lcoreGetFileExtension );
	assingGlobalFunction( "GetFileName", lcoreGetFileName );
	assingGlobalFunction( "GetFileNameWithoutExt", lcoreGetFileNameWithoutExt );
	assingGlobalFunction( "GetDirectoryPath", lcoreGetDirectoryPath );
	assingGlobalFunction( "GetPrevDirectoryPath", lcoreGetPrevDirectoryPath );
	assingGlobalFunction( "GetWorkingDirectory", lcoreGetWorkingDirectory );
	assingGlobalFunction( "LoadDirectoryFiles", lcoreLoadDirectoryFiles );
	assingGlobalFunction( "LoadDirectoryFilesEx", lcoreLoadDirectoryFilesEx );
	assingGlobalFunction( "ChangeDirectory", lcoreChangeDirectory );
	assingGlobalFunction( "IsPathFile", lcoreIsPathFile );
	assingGlobalFunction( "IsFileDropped", lcoreIsFileDropped );
	assingGlobalFunction( "LoadDroppedFiles", lcoreLoadDroppedFiles );
	assingGlobalFunction( "GetFileModTime", lcoreGetFileModTime );
		/* Compression/Encoding functionality. */
	assingGlobalFunction( "CompressData", lcoreCompressData );
	assingGlobalFunction( "DecompressData", lcoreDecompressData );
	assingGlobalFunction( "EncodeDataBase64", lcoreEncodeDataBase64 );
	assingGlobalFunction( "DecodeDataBase64", lcoreDecodeDataBase64 );
		/* Input-related functions: keyboard. */
	assingGlobalFunction( "IsKeyPressed", lcoreIsKeyPressed );
	assingGlobalFunction( "IsKeyDown", lcoreIsKeyDown );
	assingGlobalFunction( "IsKeyReleased", lcoreIsKeyReleased );
	assingGlobalFunction( "IsKeyUp", lcoreIsKeyUp );
	assingGlobalFunction( "GetKeyPressed", lcoreGetKeyPressed );
	assingGlobalFunction( "GetCharPressed", lcoreGetCharPressed );
	assingGlobalFunction( "SetExitKey", lcoreSetExitKey );
	assingGlobalFunction( "GetKeyName", lcoreGetKeyName );
	assingGlobalFunction( "GetKeyScancode", lcoreGetKeyScancode );
		/* Input-related functions: gamepads. */
	assingGlobalFunction( "IsGamepadAvailable", lcoreIsGamepadAvailable );
	assingGlobalFunction( "IsGamepadButtonPressed", lcoreIsGamepadButtonPressed );
	assingGlobalFunction( "IsGamepadButtonDown", lcoreIsGamepadButtonDown );
	assingGlobalFunction( "IsGamepadButtonReleased", lcoreIsGamepadButtonReleased );
	assingGlobalFunction( "GetGamepadAxisCount", lcoreGetGamepadAxisCount );
	assingGlobalFunction( "GetGamepadAxisMovement", lcoreGetGamepadAxisMovement );
	assingGlobalFunction( "GetGamepadName", lcoreGetGamepadName );
		/* Input-related functions: mouse. */
	assingGlobalFunction( "IsMouseButtonPressed", lcoreIsMouseButtonPressed );
	assingGlobalFunction( "IsMouseButtonDown", lcoreIsMouseButtonDown );
	assingGlobalFunction( "IsMouseButtonReleased", lcoreIsMouseButtonReleased );
	assingGlobalFunction( "IsMouseButtonUp", lcoreIsMouseButtonUp );
	assingGlobalFunction( "GetMousePosition", lcoreGetMousePosition );
	assingGlobalFunction( "GetMouseDelta", lcoreGetMouseDelta );
	assingGlobalFunction( "SetMousePosition", lcoreSetMousePosition );
	assingGlobalFunction( "SetMouseOffset", lcoreSetMouseOffset );
	assingGlobalFunction( "SetMouseScale", lcoreSetMouseScale );
	assingGlobalFunction( "GetMouseWheelMove", lcoreGetMouseWheelMove );
	assingGlobalFunction( "SetMouseCursor", lcoreSetMouseCursor );
		/* Input-related functions: touch */
	assingGlobalFunction( "GetTouchPosition", lcoreGetTouchPosition );
	assingGlobalFunction( "GetTouchPointId", lcoreGetTouchPointId );
	assingGlobalFunction( "GetTouchPointCount", lcoreGetTouchPointCount );
		/* Input-related functions: gestures. */
	assingGlobalFunction( "SetGesturesEnabled", lcoreSetGesturesEnabled );
	assingGlobalFunction( "IsGestureDetected", lcoreIsGestureDetected );
	assingGlobalFunction( "GetGestureDetected", lcoreGetGestureDetected );
	assingGlobalFunction( "GetGestureHoldDuration", lcoreGetGestureHoldDuration );
	assingGlobalFunction( "GetGestureDragVector", lcoreGetGestureDragVector );
	assingGlobalFunction( "GetGestureDragAngle", lcoreGetGestureDragAngle );
	assingGlobalFunction( "GetGesturePinchVector", lcoreGetGesturePinchVector );
	assingGlobalFunction( "GetGesturePinchAngle", lcoreGetGesturePinchAngle );
		/* Camera2D System functions. */
	assingGlobalFunction( "CreateCamera2D", lcoreCreateCamera2D );
	assingGlobalFunction( "SetCamera2DTarget", lcoreSetCamera2DTarget );
	assingGlobalFunction( "SetCamera2DOffset", lcoreSetCamera2DOffset );
	assingGlobalFunction( "SetCamera2DRotation", lcoreSetCamera2DRotation );
	assingGlobalFunction( "SetCamera2DZoom", lcoreSetCamera2DZoom );
	assingGlobalFunction( "GetCamera2DTarget", lcoreGetCamera2DTarget );
	assingGlobalFunction( "GetCamera2DOffset", lcoreGetCamera2DOffset );
	assingGlobalFunction( "GetCamera2DRotation", lcoreGetCamera2DRotation );
	assingGlobalFunction( "GetCamera2DZoom", lcoreGetCamera2DZoom );
		/* Camera3D System functions. */
	assingGlobalFunction( "CreateCamera3D", lcoreCreateCamera3D );
	assingGlobalFunction( "SetCamera3DPosition", lcoreSetCamera3DPosition );
	assingGlobalFunction( "SetCamera3DTarget", lcoreSetCamera3DTarget );
	assingGlobalFunction( "SetCamera3DUp", lcoreSetCamera3DUp );
	assingGlobalFunction( "SetCamera3DFovy", lcoreSetCamera3DFovy );
	assingGlobalFunction( "SetCamera3DProjection", lcoreSetCamera3DProjection );
	assingGlobalFunction( "GetCamera3DPosition", lcoreGetCamera3DPosition );
	assingGlobalFunction( "GetCamera3DTarget", lcoreGetCamera3DTarget );
	assingGlobalFunction( "GetCamera3DUp", lcoreGetCamera3DUp );
	assingGlobalFunction( "GetCamera3DFovy", lcoreGetCamera3DFovy );
	assingGlobalFunction( "GetCamera3DProjection", lcoreGetCamera3DProjection );
	assingGlobalFunction( "GetCamera3DForward", lcoreGetCamera3DForward );
	assingGlobalFunction( "GetCamera3DUpNormalized", lcoreGetCamera3DUpNormalized );
	assingGlobalFunction( "GetCamera3DRight", lcoreGetCamera3DRight );
	assingGlobalFunction( "Camera3DMoveForward", lcoreCamera3DMoveForward );
	assingGlobalFunction( "Camera3DMoveUp", lcoreCamera3DMoveUp );
	assingGlobalFunction( "Camera3DMoveRight", lcoreCamera3DMoveRight );
	assingGlobalFunction( "Camera3DMoveToTarget", lcoreCamera3DMoveToTarget );
	assingGlobalFunction( "Camera3DYaw", lcoreCamera3DYaw );
	assingGlobalFunction( "Camera3DPitch", lcoreCamera3DPitch );
	assingGlobalFunction( "Camera3DRoll", lcoreCamera3DRoll );
	assingGlobalFunction( "GetCamera3DViewMatrix", lcoreGetCamera3DViewMatrix );
	assingGlobalFunction( "GetCamera3DProjectionMatrix", lcoreGetCamera3DProjectionMatrix );
	assingGlobalFunction( "UpdateCamera3D", lcoreUpdateCamera3D );
	assingGlobalFunction( "UpdateCamera3DPro", lcoreUpdateCamera3DPro );
		/* Buffer management functions. */
	assingGlobalFunction( "LoadBuffer", lcoreLoadBuffer );
	assingGlobalFunction( "UnloadBuffer", lcoreUnloadBuffer );
	assingGlobalFunction( "GetBufferData", lcoreGetBufferData );
	assingGlobalFunction( "GetBufferType", lcoreGetBufferType );
	assingGlobalFunction( "GetBufferSize", lcoreGetBufferSize );
	assingGlobalFunction( "ExportBuffer", lcoreExportBuffer );
	assingGlobalFunction( "LoadBufferFromFile", lcoreLoadBufferFromFile );

	/* Shapes. */
		/* Basic shapes drawing functions. */
	assingGlobalFunction( "SetShapesTexture", lshapesSetShapesTexture );
	assingGlobalFunction( "DrawPixel", lshapesDrawPixel );
	assingGlobalFunction( "DrawLine", lshapesDrawLine );
	assingGlobalFunction( "DrawLineBezier", lshapesDrawLineBezier );
	assingGlobalFunction( "DrawLineBezierQuad", lshapesDrawLineBezierQuad );
	assingGlobalFunction( "DrawLineBezierCubic", lshapesDrawLineBezierCubic );
	assingGlobalFunction( "DrawLineStrip", lshapesDrawLineStrip );
	assingGlobalFunction( "DrawCircle", lshapesDrawCircle );
	assingGlobalFunction( "DrawCircleSector", lshapesDrawCircleSector );
	assingGlobalFunction( "DrawCircleSectorLines", lshapesDrawCircleSectorLines );
	assingGlobalFunction( "DrawCircleGradient", lshapesDrawCircleGradient );
	assingGlobalFunction( "DrawCircleLines", lshapesDrawCircleLines );
	assingGlobalFunction( "DrawEllipse", lshapesDrawEllipse );
	assingGlobalFunction( "DrawEllipseLines", lshapesDrawEllipseLines );
	assingGlobalFunction( "DrawRing", lshapesDrawRing );
	assingGlobalFunction( "DrawRingLines", lshapesDrawRingLines );
	assingGlobalFunction( "DrawRectangle", lshapesDrawRectangle );
	assingGlobalFunction( "DrawRectanglePro", lshapesDrawRectanglePro );
	assingGlobalFunction( "DrawRectangleGradientV", lshapesDrawRectangleGradientV );
	assingGlobalFunction( "DrawRectangleGradientH", lshapesDrawRectangleGradientH );
	assingGlobalFunction( "DrawRectangleGradientEx", lshapesDrawRectangleGradientEx );
	assingGlobalFunction( "DrawRectangleLines", lshapesDrawRectangleLines );
	assingGlobalFunction( "DrawRectangleLinesEx", lshapesDrawRectangleLinesEx );
	assingGlobalFunction( "DrawRectangleRounded", lshapesDrawRectangleRounded );
	assingGlobalFunction( "DrawRectangleRoundedLines", lshapesDrawRectangleRoundedLines );
	assingGlobalFunction( "DrawTriangle", lshapesDrawTriangle );
	assingGlobalFunction( "DrawTriangleLines", lshapesDrawTriangleLines );
	assingGlobalFunction( "DrawTriangleFan", lshapesDrawTriangleFan );
	assingGlobalFunction( "DrawTriangleStrip", lshapesDrawTriangleStrip );
	assingGlobalFunction( "DrawPoly", lshapesDrawPoly );
	assingGlobalFunction( "DrawPolyLines", lshapesDrawPolyLines );
	assingGlobalFunction( "DrawPolyLinesEx", lshapesDrawPolyLinesEx );
		/* Basic shapes collision detection functions. */
	assingGlobalFunction( "CheckCollisionRecs", lshapesCheckCollisionRecs );
	assingGlobalFunction( "CheckCollisionCircles", lshapesCheckCollisionCircles );
	assingGlobalFunction( "CheckCollisionCircleRec", lshapesCheckCollisionCircleRec );
	assingGlobalFunction( "CheckCollisionPointRec", lshapesCheckCollisionPointRec );
	assingGlobalFunction( "CheckCollisionPointCircle", lshapesCheckCollisionPointCircle );
	assingGlobalFunction( "CheckCollisionPointTriangle", lshapesCheckCollisionPointTriangle );
	assingGlobalFunction( "CheckCollisionPointPoly", lshapesCheckCollisionPointPoly );
	assingGlobalFunction( "CheckCollisionLines", lshapesCheckCollisionLines );
	assingGlobalFunction( "CheckCollisionPointLine", lshapesCheckCollisionPointLine );
	assingGlobalFunction( "GetCollisionRec", lshapesGetCollisionRec );

	/* Textures. */
		/* Image loading functions. */
	assingGlobalFunction( "LoadImage", ltexturesLoadImage );
	assingGlobalFunction( "LoadImageFromTexture", ltexturesLoadImageFromTexture );
	assingGlobalFunction( "LoadImageFromScreen", ltexturesLoadImageFromScreen );
	assingGlobalFunction( "IsImageReady", ltextureIsImageReady );
	assingGlobalFunction( "UnloadImage", ltextureUnloadImage );
	assingGlobalFunction( "ExportImage", ltexturesExportImage );
	assingGlobalFunction( "ExportImageAsCode", ltexturesExportImageAsCode );
		/* Image generation functions. */
	assingGlobalFunction( "GenImageColor", ltexturesGenImageColor );
	assingGlobalFunction( "GenImageGradientV", ltexturesGenImageGradientV );
	assingGlobalFunction( "GenImageGradientH", ltexturesGenImageGradientH );
	assingGlobalFunction( "GenImageGradientRadial", ltexturesGenImageGradientRadial );
	assingGlobalFunction( "GenImageChecked", ltexturesGenImageChecked );
	assingGlobalFunction( "GenImageWhiteNoise", ltexturesGenImageWhiteNoise );
	assingGlobalFunction( "GenImagePerlinNoise", ltexturesGenImagePerlinNoise );
	assingGlobalFunction( "GenImageCellular", ltexturesGenImageCellular );
	assingGlobalFunction( "GenImageText", ltexturesGenImageText );
		/* Image manipulation functions. */
	assingGlobalFunction( "ImageCopy", ltexturesImageCopy );
	assingGlobalFunction( "ImageFromImage", ltexturesImageFromImage );
	assingGlobalFunction( "ImageText", ltexturesImageText );
	assingGlobalFunction( "ImageFormat", ltexturesImageFormat );
	assingGlobalFunction( "ImageToPOT", ltexturesImageToPOT );
	assingGlobalFunction( "ImageCrop", ltexturesImageCrop );
	assingGlobalFunction( "ImageAlphaCrop", ltexturesImageAlphaCrop );
	assingGlobalFunction( "ImageAlphaClear", ltexturesImageAlphaClear );
	assingGlobalFunction( "ImageAlphaMask", ltexturesImageAlphaMask );
	assingGlobalFunction( "ImageAlphaPremultiply", ltexturesImageAlphaPremultiply );
	assingGlobalFunction( "ImageBlurGaussian", ltexturesImageBlurGaussian );
	assingGlobalFunction( "ImageResize", ltexturesImageResize );
	assingGlobalFunction( "ImageResizeNN", ltexturesImageResizeNN );
	assingGlobalFunction( "ImageResizeCanvas", ltexturesImageResizeCanvas );
	assingGlobalFunction( "ImageMipmaps", ltexturesImageMipmaps );
	assingGlobalFunction( "ImageDither", ltexturesImageDither );
	assingGlobalFunction( "ImageFlipVertical", ltexturesImageFlipVertical );
	assingGlobalFunction( "ImageFlipHorizontal", ltexturesImageFlipHorizontal );
	assingGlobalFunction( "ImageRotateCW", ltexturesImageRotateCW );
	assingGlobalFunction( "ImageRotateCCW", ltexturesImageRotateCCW );
	assingGlobalFunction( "ImageColorTint", ltexturesImageColorTint );
	assingGlobalFunction( "ImageColorInvert", ltexturesImageColorInvert );
	assingGlobalFunction( "ImageColorGrayscale", ltexturesImageColorGrayscale );
	assingGlobalFunction( "ImageColorContrast", ltexturesImageColorContrast );
	assingGlobalFunction( "ImageColorBrightness", ltexturesImageColorBrightness );
	assingGlobalFunction( "ImageColorReplace", ltexturesImageColorReplace );
	assingGlobalFunction( "LoadImageColors", ltexturesLoadImageColors );
	assingGlobalFunction( "LoadImagePalette", ltexturesLoadImagePalette );
	assingGlobalFunction( "GetImageAlphaBorder", ltexturesGetImageAlphaBorder );
	assingGlobalFunction( "GetImageColor", ltexturesGetImageColor );
		/* Image configuration functions. */
	assingGlobalFunction( "GetImageSize", ltexturesGetImageSize );
	assingGlobalFunction( "GetImageMipmaps", ltexturesGetImageMipmaps );
	assingGlobalFunction( "GetImageFormat", ltexturesGetImageFormat );
		/* Image drawing functions. */
	assingGlobalFunction( "ImageClearBackground", ltexturesImageClearBackground );
	assingGlobalFunction( "ImageDrawPixel", ltexturesImageDrawPixel );
	assingGlobalFunction( "ImageDrawLine", ltexturesImageDrawLine );
	assingGlobalFunction( "ImageDrawCircle", ltexturesImageDrawCircle );
	assingGlobalFunction( "ImageDrawCircleLines", ltexturesImageDrawCircleLines );
	assingGlobalFunction( "ImageDrawRectangle", ltexturesImageDrawRectangle );
	assingGlobalFunction( "ImageDrawRectangleLines", ltexturesImageDrawRectangleLines );
	assingGlobalFunction( "ImageDraw", ltexturesImageDraw );
	assingGlobalFunction( "ImageDrawTextEx", ltexturesImageDrawTextEx );
		/* Texture loading functions. */
	assingGlobalFunction( "LoadTexture", ltexturesLoadTexture );
	assingGlobalFunction( "LoadTextureFromImage", ltexturesLoadTextureFromImage );
	assingGlobalFunction( "LoadTextureCubemap", ltexturesLoadTextureCubemap );
	assingGlobalFunction( "LoadTextureFromData", ltexturesLoadTextureFromData );
	assingGlobalFunction( "LoadRenderTexture", ltexturesLoadRenderTexture );
	assingGlobalFunction( "LoadRenderTextureFromData", ltexturesLoadRenderTextureFromData );
	assingGlobalFunction( "IsTextureReady", ltexturesIsTextureReady );
	assingGlobalFunction( "UnloadTexture", ltextureUnloadTexture );
	assingGlobalFunction( "IsRenderTextureReady", ltexturesIsRenderTextureReady );
	assingGlobalFunction( "UnloadRenderTexture", ltextureUnloadRenderTexture );
	assingGlobalFunction( "UpdateTexture", ltexturesUpdateTexture );
	assingGlobalFunction( "UpdateTextureRec", ltexturesUpdateTextureRec );
		/* Texture configuration functions. */
	assingGlobalFunction( "GenTextureMipmaps", ltexturesGenTextureMipmaps );
	assingGlobalFunction( "SetTextureFilter", ltexturesSetTextureFilter );
	assingGlobalFunction( "SetTextureWrap", ltexturesSetTextureWrap );
	assingGlobalFunction( "GetTextureId", ltexturesGetTextureId );
	assingGlobalFunction( "GetTextureSize", ltexturesGetTextureSize );
	assingGlobalFunction( "GetTextureMipmaps", ltexturesGetTextureMipmaps );
	assingGlobalFunction( "GetTextureFormat", ltexturesGetTextureFormat );
		/* Texture drawing functions. */
	assingGlobalFunction( "DrawTexture", ltexturesDrawTexture );
	assingGlobalFunction( "DrawTextureRec", ltexturesDrawTextureRec );
	assingGlobalFunction( "DrawTexturePro", ltexturesDrawTexturePro );
	assingGlobalFunction( "DrawTextureNPatch", ltexturesDrawTextureNPatch );
		/* RenderTexture configuration functions. */
	assingGlobalFunction( "GetRenderTextureId", ltexturesGetRenderTextureId );
	assingGlobalFunction( "GetRenderTextureTexture", ltexturesGetRenderTextureTexture );
	assingGlobalFunction( "GetRenderTextureDepthTexture", ltexturesGetRenderTextureDepthTexture );
		/* Color/pixel related functions */
	assingGlobalFunction( "Fade", ltexturesFade );
	assingGlobalFunction( "ColorToInt", ltexturesColorToInt );
	assingGlobalFunction( "ColorNormalize", ltexturesColorNormalize );
	assingGlobalFunction( "ColorFromNormalized", ltexturesColorFromNormalized );
	assingGlobalFunction( "ColorToHSV", ltexturesColorToHSV );
	assingGlobalFunction( "ColorFromHSV", ltexturesColorFromHSV );
	assingGlobalFunction( "ColorTint", ltexturesColorTint );
	assingGlobalFunction( "ColorBrightness", ltexturesColorBrightness );
	assingGlobalFunction( "ColorContrast", ltexturesColorContrast );
	assingGlobalFunction( "ColorAlpha", ltexturesColorAlpha );
	assingGlobalFunction( "ColorAlphaBlend", ltexturesColorAlphaBlend );
	assingGlobalFunction( "GetColor", ltexturesGetColor );
	assingGlobalFunction( "GetPixelColor", ltexturesGetPixelColor );
	assingGlobalFunction( "GetPixelDataSize", ltexturesGetPixelDataSize );

	/* Models. */
		/* Basic geometric 3D shapes drawing functions. */
	assingGlobalFunction( "DrawLine3D", lmodelsDrawLine3D );
	assingGlobalFunction( "DrawPoint3D", lmodelsDrawPoint3D );
	assingGlobalFunction( "DrawCircle3D", lmodelsDrawCircle3D );
	assingGlobalFunction( "DrawTriangle3D", lmodelsDrawTriangle3D );
	assingGlobalFunction( "DrawCube", lmodelsDrawCube );
	assingGlobalFunction( "DrawCubeWires", lmodelsDrawCubeWires );
	assingGlobalFunction( "DrawSphere", lmodelsDrawSphere );
	assingGlobalFunction( "DrawSphereEx", lmodelsDrawSphereEx );
	assingGlobalFunction( "DrawSphereWires", lmodelsDrawSphereWires );
	assingGlobalFunction( "DrawCylinder", lmodelsDrawCylinder );
	assingGlobalFunction( "DrawCylinderEx", lmodelsDrawCylinderEx );
	assingGlobalFunction( "DrawCylinderWires", lmodelsDrawCylinderWires );
	assingGlobalFunction( "DrawCylinderWiresEx", lmodelsDrawCylinderWiresEx );
	assingGlobalFunction( "DrawCapsule", lmodelsDrawCapsule );
	assingGlobalFunction( "DrawCapsuleWires", lmodelsDrawCapsuleWires );
	assingGlobalFunction( "DrawPlane", lmodelsDrawPlane );
	assingGlobalFunction( "DrawQuad3DTexture", lmodelDrawQuad3DTexture );
	assingGlobalFunction( "DrawRay", lmodelsDrawRay );
	assingGlobalFunction( "DrawGrid", lmodelsDrawGrid );
		/* Model management functions. */
	assingGlobalFunction( "LoadModel", lmodelsLoadModel );
	assingGlobalFunction( "LoadModelFromMesh", lmodelsLoadModelFromMesh );
	assingGlobalFunction( "IsModelReady", lmodelsIsModelReady );
	assingGlobalFunction( "UnloadModel", lmodelsUnloadModel );
	assingGlobalFunction( "GetModelBoundingBox", lmodelsGetModelBoundingBox );
	assingGlobalFunction( "SetModelMaterial", lmodelsSetModelMaterial );
	assingGlobalFunction( "SetModelMeshMaterial", lmodelsSetModelMeshMaterial );
	assingGlobalFunction( "SetModelTransform", lmodelsSetModelTransform );
	assingGlobalFunction( "GetModelTransform", lmodelsGetModelTransform );
		/* Model drawing functions. */
	assingGlobalFunction( "DrawModel", lmodelsDrawModel );
	assingGlobalFunction( "DrawModelEx", lmodelsDrawModelEx );
	assingGlobalFunction( "DrawModelWires", lmodelsDrawModelWires );
	assingGlobalFunction( "DrawModelWiresEx", lmodelsDrawModelWiresEx );
	assingGlobalFunction( "DrawBoundingBox", lmodelsDrawBoundingBox );
	assingGlobalFunction( "DrawBillboard", lmodelsDrawBillboard );
	assingGlobalFunction( "DrawBillboardRec", lmodelsDrawBillboardRec );
	assingGlobalFunction( "DrawBillboardPro", lmodelsDrawBillboardPro );
		/* Mesh management functions. */
	assingGlobalFunction( "UpdateMesh", lmodelsUpdateMesh );
	assingGlobalFunction( "UnloadMesh", lmodelsUnloadMesh );
	assingGlobalFunction( "DrawMesh", lmodelsDrawMesh );
	assingGlobalFunction( "DrawMeshInstanced", lmodelsDrawMeshInstanced );
	assingGlobalFunction( "SetMeshColor", lmodelsSetMeshColor );
	assingGlobalFunction( "ExportMesh", lmodelsExportMesh );
	assingGlobalFunction( "GetMeshBoundingBox", lmodelsGetMeshBoundingBox );
	assingGlobalFunction( "GenMeshTangents", lmodelsGenMeshTangents );
		/* Mesh generation functions. */
	assingGlobalFunction( "GenMeshPoly", lmodelsGenMeshPoly );
	assingGlobalFunction( "GenMeshPlane", lmodelsGenMeshPlane );
	assingGlobalFunction( "GenMeshCube", lmodelsGenMeshCube );
	assingGlobalFunction( "GenMeshSphere", lmodelsGenMeshSphere );
	assingGlobalFunction( "GenMeshCylinder", lmodelsGenMeshCylinder );
	assingGlobalFunction( "GenMeshCone", lmodelsGenMeshCone );
	assingGlobalFunction( "GenMeshTorus", lmodelsGenMeshTorus );
	assingGlobalFunction( "GenMeshKnot", lmodelsGenMeshKnot );
	assingGlobalFunction( "GenMeshHeightmap", lmodelsGenMeshHeightmap );
	assingGlobalFunction( "GenMeshCustom", lmodelsGenMeshCustom );
		/* Material management functions. */
	assingGlobalFunction( "LoadMaterials", lmodelsLoadMaterials );
	assingGlobalFunction( "GetMaterialDefault", lmodelsGetMaterialDefault );
	assingGlobalFunction( "LoadMaterialDefault", lmodelsLoadMaterialDefault );
	assingGlobalFunction( "CreateMaterial", lmodelsCreateMaterial );
	assingGlobalFunction( "IsMaterialReady", lmodelsIsMaterialReady );
	assingGlobalFunction( "UnloadMaterial", lmodelsUnloadMaterial );
	assingGlobalFunction( "SetMaterialTexture", lmodelsSetMaterialTexture );
	assingGlobalFunction( "SetMaterialColor", lmodelsSetMaterialColor );
	assingGlobalFunction( "SetMaterialValue", lmodelsSetMaterialValue );
	assingGlobalFunction( "SetMaterialShader", lmodelsSetMaterialShader );
	assingGlobalFunction( "SetMaterialParams", lmodelsSetMaterialParams );
	assingGlobalFunction( "GetMaterialTexture", lmodelsGetMaterialTexture );
	assingGlobalFunction( "GetMaterialColor", lmodelsGetMaterialColor );
	assingGlobalFunction( "GetMaterialValue", lmodelsGetMaterialValue );
	assingGlobalFunction( "GetMaterialShader", lmodelsGetMaterialShader );
	assingGlobalFunction( "GetMaterialParams", lmodelsGetMaterialParams );
		/* Model animations management functions. */
	assingGlobalFunction( "LoadModelAnimations", lmodelsLoadModelAnimations );
	assingGlobalFunction( "UpdateModelAnimation", lmodelsUpdateModelAnimation );
	assingGlobalFunction( "IsModelAnimationValid", lmodelsIsModelAnimationValid );
	assingGlobalFunction( "GetModelAnimationBoneCount", lmodelsGetModelAnimationBoneCount );
	assingGlobalFunction( "GetModelAnimationFrameCount", lmodelsGetModelAnimationFrameCount );
		/* Collision detection functions. */
	assingGlobalFunction( "CheckCollisionSpheres", lmodelsCheckCollisionSpheres );
	assingGlobalFunction( "CheckCollisionBoxes", lmodelsCheckCollisionBoxes );
	assingGlobalFunction( "CheckCollisionBoxSphere", lmodelsCheckCollisionBoxSphere );
	assingGlobalFunction( "GetRayCollisionSphere", lmodelsGetRayCollisionSphere );
	assingGlobalFunction( "GetRayCollisionBox", lmodelsGetRayCollisionBox );
	assingGlobalFunction( "GetRayCollisionMesh", lmodelsGetRayCollisionMesh );
	assingGlobalFunction( "GetRayCollisionTriangle", lmodelsGetRayCollisionTriangle );
	assingGlobalFunction( "GetRayCollisionQuad", lmodelsGetRayCollisionQuad );

	/* Text. */
		/* Font loading/unloading functions. */
	assingGlobalFunction( "GetFontDefault", ltextGetFontDefault );
	assingGlobalFunction( "LoadFont", ltextLoadFont );
	assingGlobalFunction( "LoadFontEx", ltextLoadFontEx );
	assingGlobalFunction( "LoadFontFromImage", ltextLoadFontFromImage );
	assingGlobalFunction( "IsFontReady", ltextIsFontReady );
	assingGlobalFunction( "UnloadFont", ltextUnloadFont );
		/* Text drawing functions. */
	assingGlobalFunction( "DrawFPS", ltextDrawFPS );
	assingGlobalFunction( "DrawText", ltextDrawText );
	assingGlobalFunction( "DrawTextEx", ltextDrawTextEx );
	assingGlobalFunction( "DrawTextPro", ltextDrawTextPro );
	assingGlobalFunction( "DrawTextCodepoint", ltextDrawTextCodepoint );
	assingGlobalFunction( "DrawTextCodepoints", ltextDrawTextCodepoints );
	assingGlobalFunction( "DrawTextBoxed", ltextDrawTextBoxed );
	assingGlobalFunction( "DrawTextBoxedTinted", ltextDrawTextBoxedTinted );
		/* Text font info functions. */
	assingGlobalFunction( "MeasureText", ltextMeasureText );
	assingGlobalFunction( "GetGlyphIndex", ltextGetGlyphIndex );
	assingGlobalFunction( "GetGlyphInfo", ltextGetGlyphInfo );
	assingGlobalFunction( "GetGlyphAtlasRec", ltextGetGlyphAtlasRec );
	assingGlobalFunction( "GetFontBaseSize", ltextGetFontBaseSize );
	assingGlobalFunction( "GetFontGlyphCount", ltextGetFontGlyphCount );
	assingGlobalFunction( "GetFontGlyphPadding", ltextGetFontGlyphPadding );
	assingGlobalFunction( "GetFontTexture", ltextGetFontTexture );

	/* Audio. */
		/* Audio device management functions. */
	assingGlobalFunction( "SetMasterVolume", laudioSetMasterVolume );
		/* Wave/Sound loading/unloading functions. */
	assingGlobalFunction( "LoadSound", laudioLoadSound );
	assingGlobalFunction( "LoadWave", laudioLoadWave );
	assingGlobalFunction( "IsWaveReady", laudioIsWaveReady );
	assingGlobalFunction( "LoadSoundFromWave", laudioLoadSoundFromWave );
	assingGlobalFunction( "IsSoundReady", laudioIsSoundReady );
	assingGlobalFunction( "UnloadWave", laudioUnloadWave );
	assingGlobalFunction( "UnloadSound", laudioUnloadSound );
	assingGlobalFunction( "ExportWave", laudioExportWave );
	assingGlobalFunction( "ExportWaveAsCode", laudioExportWaveAsCode );
		/* Wave/Sound management functions. */
	assingGlobalFunction( "PlaySound", laudioPlaySound );
	assingGlobalFunction( "StopSound", laudioStopSound );
	assingGlobalFunction( "PauseSound", laudioPauseSound );
	assingGlobalFunction( "ResumeSound", laudioResumeSound );
	assingGlobalFunction( "IsSoundPlaying", laudioIsSoundPlaying );
	assingGlobalFunction( "SetSoundVolume", laudioSetSoundVolume );
	assingGlobalFunction( "SetSoundPitch", laudioSetSoundPitch );
	assingGlobalFunction( "SetSoundPan", laudioSetSoundPan );
	assingGlobalFunction( "WaveFormat", laudioWaveFormat );
	assingGlobalFunction( "WaveCopy", laudioWaveCopy );
	assingGlobalFunction( "WaveCrop", laudioWaveCrop );
		/* Music management functions. */
	assingGlobalFunction( "LoadMusicStream", laudioLoadMusicStream );
	assingGlobalFunction( "IsMusicReady", laudioIsMusicReady );
	assingGlobalFunction( "UnloadMusicStream", laudioUnloadMusicStream );
	assingGlobalFunction( "PlayMusicStream", laudioPlayMusicStream );
	assingGlobalFunction( "IsMusicStreamPlaying", laudioIsMusicStreamPlaying );
	assingGlobalFunction( "UpdateMusicStream", laudioUpdateMusicStream );
	assingGlobalFunction( "StopMusicStream", laudioStopMusicStream );
	assingGlobalFunction( "PauseMusicStream", laudioPauseMusicStream );
	assingGlobalFunction( "ResumeMusicStream", laudioResumeMusicStream );
	assingGlobalFunction( "SetMusicVolume", laudioSetMusicVolume );
	assingGlobalFunction( "SetMusicPitch", laudioSetMusicPitch );
	assingGlobalFunction( "SetMusicPan", laudioSetMusicPan );
	assingGlobalFunction( "SetMusicLooping", laudioSetMusicLooping );
	assingGlobalFunction( "GetMusicLooping", laudioGetMusicLooping );
	assingGlobalFunction( "GetMusicTimeLength", laudioGetMusicTimeLength );
	assingGlobalFunction( "GetMusicTimePlayed", laudioGetMusicTimePlayed );

	/* Math. */
		/* Utils. */
	assingGlobalFunction( "Clamp", lmathClamp );
	assingGlobalFunction( "Lerp", lmathLerp );
	assingGlobalFunction( "Normalize", lmathNormalize );
	assingGlobalFunction( "Remap", lmathRemap );
	assingGlobalFunction( "Wrap", lmathWrap );
	assingGlobalFunction( "FloatEquals", lmathFloatEquals );
		/* Vector2. */
	assingGlobalFunction( "Vector2Zero", lmathVector2Zero );
	assingGlobalFunction( "Vector2One", lmathVector2One );
	assingGlobalFunction( "Vector2Add", lmathVector2Add );
	assingGlobalFunction( "Vector2AddValue", lmathVector2AddValue );
	assingGlobalFunction( "Vector2Subtract", lmathVector2Subtract );
	assingGlobalFunction( "Vector2SubtractValue", lmathVector2SubtractValue );
	assingGlobalFunction( "Vector2Length", lmathVector2Length );
	assingGlobalFunction( "Vector2LengthSqr", lmathVector2LengthSqr );
	assingGlobalFunction( "Vector2DotProduct", lmathVector2DotProduct );
	assingGlobalFunction( "Vector2Distance", lmathVector2Distance );
	assingGlobalFunction( "Vector2DistanceSqr", lmathVector2DistanceSqr );
	assingGlobalFunction( "Vector2Angle", lmathVector2Angle );
	assingGlobalFunction( "Vector2LineAngle", lmathVector2LineAngle );
	assingGlobalFunction( "Vector2Scale", lmathVector2Scale );
	assingGlobalFunction( "Vector2Multiply", lmathVector2Multiply );
	assingGlobalFunction( "Vector2Negate", lmathVector2Negate );
	assingGlobalFunction( "Vector2Divide", lmathVector2Divide );
	assingGlobalFunction( "Vector2Normalize", lmathVector2Normalize );
	assingGlobalFunction( "Vector2Transform", lmathVector2Transform );
	assingGlobalFunction( "Vector2Lerp", lmathVector2Lerp );
	assingGlobalFunction( "Vector2Reflect", lmathVector2Reflect );
	assingGlobalFunction( "Vector2Rotate", lmathVector2Rotate );
	assingGlobalFunction( "Vector2MoveTowards", lmathVector2MoveTowards );
	assingGlobalFunction( "Vector2Invert", lmathVector2Invert );
	assingGlobalFunction( "Vector2Clamp", lmathVector2Clamp );
	assingGlobalFunction( "Vector2ClampValue", lmathVector2ClampValue );
	assingGlobalFunction( "Vector2Equals", lmathVector2Equals );
		/* Vector3. */
	assingGlobalFunction( "Vector3Zero", lmathVector3Zero );
	assingGlobalFunction( "Vector3One", lmathVector3One );
	assingGlobalFunction( "Vector3Add", lmathVector3Add );
	assingGlobalFunction( "Vector3AddValue", lmathVector3AddValue );
	assingGlobalFunction( "Vector3Subtract", lmathVector3Subtract );
	assingGlobalFunction( "Vector3SubtractValue", lmathVector3SubtractValue );
	assingGlobalFunction( "Vector3Scale", lmathVector3Scale );
	assingGlobalFunction( "Vector3Multiply", lmathVector3Multiply );
	assingGlobalFunction( "Vector3CrossProduct", lmathVector3CrossProduct );
	assingGlobalFunction( "Vector3Perpendicular", lmathVector3Perpendicular );
	assingGlobalFunction( "Vector3Length", lmathVector3Length );
	assingGlobalFunction( "Vector3LengthSqr", lmathVector3LengthSqr );
	assingGlobalFunction( "Vector3DotProduct", lmathVector3DotProduct );
	assingGlobalFunction( "Vector3Distance", lmathVector3Distance );
	assingGlobalFunction( "Vector3DistanceSqr", lmathVector3DistanceSqr );
	assingGlobalFunction( "Vector3Angle", lmathVector3Angle );
	assingGlobalFunction( "Vector3Negate", lmathVector3Negate );
	assingGlobalFunction( "Vector3Divide", lmathVector3Divide );
	assingGlobalFunction( "Vector3Normalize", lmathVector3Normalize );
	assingGlobalFunction( "Vector3OrthoNormalize", lmathVector3OrthoNormalize );
	assingGlobalFunction( "Vector3Transform", lmathVector3Transform );
	assingGlobalFunction( "Vector3RotateByQuaternion", lmathVector3RotateByQuaternion );
	assingGlobalFunction( "Vector3RotateByAxisAngle", lmathVector3RotateByAxisAngle );
	assingGlobalFunction( "Vector3Lerp", lmathVector3Lerp );
	assingGlobalFunction( "Vector3Reflect", lmathVector3Reflect );
	assingGlobalFunction( "Vector3Min", lmathVector3Min );
	assingGlobalFunction( "Vector3Max", lmathVector3Max );
	assingGlobalFunction( "Vector3Barycenter", lmathVector3Barycenter );
	assingGlobalFunction( "Vector3Unproject", lmathVector3Unproject );
	assingGlobalFunction( "Vector3Invert", lmathVector3Invert );
	assingGlobalFunction( "Vector3Clamp", lmathVector3Clamp );
	assingGlobalFunction( "Vector3ClampValue", lmathVector3ClampValue );
	assingGlobalFunction( "Vector3Equals", lmathVector3Equals );
	assingGlobalFunction( "Vector3Refract", lmathVector3Refract );
		/* Matrix. */
	assingGlobalFunction( "MatrixDeterminant", lmathMatrixDeterminant );
	assingGlobalFunction( "MatrixTrace", lmathMatrixTrace );
	assingGlobalFunction( "MatrixTranspose", lmathMatrixTranspose );
	assingGlobalFunction( "MatrixInvert", lmathMatrixInvert );
	assingGlobalFunction( "MatrixIdentity", lmathMatrixIdentity );
	assingGlobalFunction( "MatrixAdd", lmathMatrixAdd );
	assingGlobalFunction( "MatrixSubtract", lmathMatrixSubtract );
	assingGlobalFunction( "MatrixMultiply", lmathMatrixMultiply );
	assingGlobalFunction( "MatrixTranslate", lmathMatrixTranslate );
	assingGlobalFunction( "MatrixRotate", lmathMatrixRotate );
	assingGlobalFunction( "MatrixRotateX", lmathMatrixRotateX );
	assingGlobalFunction( "MatrixRotateY", lmathMatrixRotateY );
	assingGlobalFunction( "MatrixRotateZ", lmathMatrixRotateZ );
	assingGlobalFunction( "MatrixRotateXYZ", lmathMatrixRotateXYZ );
	assingGlobalFunction( "MatrixRotateZYX", lmathMatrixRotateZYX );
	assingGlobalFunction( "MatrixScale", lmathMatrixScale );
	assingGlobalFunction( "MatrixFrustum", lmathMatrixFrustum );
	assingGlobalFunction( "MatrixPerspective", lmathMatrixPerspective );
	assingGlobalFunction( "MatrixOrtho", lmathMatrixOrtho );
	assingGlobalFunction( "MatrixLookAt", lmathMatrixLookAt );
		/* Quaternion. */
	assingGlobalFunction( "QuaternionAdd", lmathQuaternionAdd );
	assingGlobalFunction( "QuaternionAddValue", lmathQuaternionAddValue );
	assingGlobalFunction( "QuaternionSubtract", lmathQuaternionSubtract );
	assingGlobalFunction( "QuaternionSubtractValue", lmathQuaternionSubtractValue );
	assingGlobalFunction( "QuaternionIdentity", lmathQuaternionIdentity );
	assingGlobalFunction( "QuaternionLength", lmathQuaternionLength );
	assingGlobalFunction( "QuaternionNormalize", lmathQuaternionNormalize );
	assingGlobalFunction( "QuaternionInvert", lmathQuaternionInvert );
	assingGlobalFunction( "QuaternionMultiply", lmathQuaternionMultiply );
	assingGlobalFunction( "QuaternionScale", lmathQuaternionScale );
	assingGlobalFunction( "QuaternionDivide", lmathQuaternionDivide );
	assingGlobalFunction( "QuaternionLerp", lmathQuaternionLerp );
	assingGlobalFunction( "QuaternionNlerp", lmathQuaternionNlerp );
	assingGlobalFunction( "QuaternionSlerp", lmathQuaternionSlerp );
	assingGlobalFunction( "QuaternionFromVector3ToVector3", lmathQuaternionFromVector3ToVector3 );
	assingGlobalFunction( "QuaternionFromMatrix", lmathQuaternionFromMatrix );
	assingGlobalFunction( "QuaternionToMatrix", lmathQuaternionToMatrix );
	assingGlobalFunction( "QuaternionFromAxisAngle", lmathQuaternionFromAxisAngle );
	assingGlobalFunction( "QuaternionToAxisAngle", lmathQuaternionToAxisAngle );
	assingGlobalFunction( "QuaternionFromEuler", lmathQuaternionFromEuler );
	assingGlobalFunction( "QuaternionToEuler", lmathQuaternionToEuler );
	assingGlobalFunction( "QuaternionTransform", lmathQuaternionTransform );
	assingGlobalFunction( "QuaternionEquals", lmathQuaternionEquals );

	/* Gui. */
		/* Global. */
	assingGlobalFunction( "GuiEnable", lguiGuiEnable );
	assingGlobalFunction( "GuiDisable", lguiGuiDisable );
	assingGlobalFunction( "GuiLock", lguiGuiLock );
	assingGlobalFunction( "GuiUnlock", lguiGuiUnlock );
	assingGlobalFunction( "GuiIsLocked", lguiGuiIsLocked );
	assingGlobalFunction( "GuiFade", lguiGuiFade );
	assingGlobalFunction( "GuiSetState", lguiGuiSetState );
	assingGlobalFunction( "GuiGetState", lguiGuiGetState );
		/* Font. */
	assingGlobalFunction( "GuiSetFont", lguiGuiSetFont );
	assingGlobalFunction( "GuiGetFont", lguiGuiGetFont );
		/* Style. */
	assingGlobalFunction( "GuiSetStyle", lguiGuiSetStyle );
	assingGlobalFunction( "GuiGetStyle", lguiGuiGetStyle );
		/* Container. */
	assingGlobalFunction( "GuiWindowBox", lguiGuiWindowBox );
	assingGlobalFunction( "GuiGroupBox", lguiGuiGroupBox );
	assingGlobalFunction( "GuiLine", lguiGuiLine );
	assingGlobalFunction( "GuiPanel", lguiGuiPanel );
	assingGlobalFunction( "GuiScrollPanel", lguiGuiScrollPanel );
		/* Basic. */
	assingGlobalFunction( "GuiLabel", lguiGuiLabel );
	assingGlobalFunction( "GuiButton", lguiGuiButton );
	assingGlobalFunction( "GuiLabelButton", lguiGuiLabelButton );
	assingGlobalFunction( "GuiToggle", lguiGuiToggle );
	assingGlobalFunction( "GuiToggleGroup", lguiGuiToggleGroup );
	assingGlobalFunction( "GuiCheckBox", lguiGuiCheckBox );
	assingGlobalFunction( "GuiComboBox", lguiGuiComboBox );
	assingGlobalFunction( "GuiTextBox", lguiGuiTextBox );
	assingGlobalFunction( "GuiTextBoxMulti", lguiGuiTextBoxMulti );
	assingGlobalFunction( "GuiSpinner", lguiGuiSpinner );
	assingGlobalFunction( "GuiValueBox", lguiGuiValueBox );
	assingGlobalFunction( "GuiSlider", lguiGuiSlider );
	assingGlobalFunction( "GuiSliderBar", lguiGuiSliderBar );
	assingGlobalFunction( "GuiProgressBar", lguiGuiProgressBar );
	assingGlobalFunction( "GuiScrollBar", lguiGuiScrollBar );
	assingGlobalFunction( "GuiDropdownBox", lguiGuiDropdownBox );
	assingGlobalFunction( "GuiStatusBar", lguiGuiStatusBar );
	assingGlobalFunction( "GuiDummyRec", lguiGuiDummyRec );
	assingGlobalFunction( "GuiGrid", lguiGuiGrid );
		/* Advanced. */
	assingGlobalFunction( "GuiListView", lguiGuiListView );
	assingGlobalFunction( "GuiListViewEx", lguiGuiListViewEx );
	assingGlobalFunction( "GuiMessageBox", lguiGuiMessageBox );
	assingGlobalFunction( "GuiTextInputBox", lguiGuiTextInputBox );
	assingGlobalFunction( "GuiColorPicker", lguiGuiColorPicker );
	assingGlobalFunction( "GuiColorPanel", lguiGuiColorPanel );
	assingGlobalFunction( "GuiColorBarAlpha", lguiGuiColorBarAlpha );
	assingGlobalFunction( "GuiColorBarHue", lguiGuiColorBarHue );
		/* Styles loading functions */
	assingGlobalFunction( "GuiLoadStyle", lguiGuiLoadStyle );
	assingGlobalFunction( "GuiLoadStyleDefault", lguiGuiLoadStyleDefault );
		/* Icons. */
	assingGlobalFunction( "GuiIconText", lguiGuiIconText );
	assingGlobalFunction( "GuiDrawIcon", lguiGuiDrawIcon );
	assingGlobalFunction( "GuiSetIconScale", lguiGuiSetIconScale );
	assingGlobalFunction( "GuiSetIconPixel", lguiGuiSetIconPixel );
	assingGlobalFunction( "GuiClearIconPixel", lguiGuiClearIconPixel );
	assingGlobalFunction( "GuiCheckIconPixel", lguiGuiCheckIconPixel );

	/* Lights */
		/* Light management functions. */
	assingGlobalFunction( "CreateLight", llightsCreateLight );
	assingGlobalFunction( "UpdateLightValues", llightsUpdateLightValues );
	assingGlobalFunction( "SetLightType", llightsSetLightType );
	assingGlobalFunction( "SetLightPosition", llightsSetLightPosition );
	assingGlobalFunction( "SetLightTarget", llightsSetLightTarget );
	assingGlobalFunction( "SetLightColor", llightsSetLightColor );
	assingGlobalFunction( "SetLightEnabled", llightsSetLightEnabled );
	assingGlobalFunction( "GetLightType", llightsGetLightType );
	assingGlobalFunction( "GetLightPosition", llightsGetLightPosition );
	assingGlobalFunction( "GetLightTarget", llightsGetLightTarget );
	assingGlobalFunction( "GetLightColor", llightsGetLightColor );
	assingGlobalFunction( "IsLightEnabled", llightsIsLightEnabled );

	/* RLGL */
		/* Matrix operations. */
	assingGlobalFunction( "rlMatrixMode", lrlglMatrixMode );
	assingGlobalFunction( "rlPushMatrix", lrlglPushMatrix );
	assingGlobalFunction( "rlPopMatrix", lrlglPopMatrix );
	assingGlobalFunction( "rlLoadIdentity", lrlglLoadIdentity );
	assingGlobalFunction( "rlTranslatef", lrlglTranslatef );
	assingGlobalFunction( "rlRotatef", lrlglRotatef );
	assingGlobalFunction( "rlScalef", lrlglScalef );
	assingGlobalFunction( "rlMultMatrixf", lrlglMultMatrixf );
	assingGlobalFunction( "rlFrustum", lrlglFrustum );
	assingGlobalFunction( "rlOrtho", lrlglOrtho );
	assingGlobalFunction( "rlViewport", lrlglViewport );
		/* Vertex level operations. */
	assingGlobalFunction( "rlBegin", lrlglBegin );
	assingGlobalFunction( "rlEnd", lrlglEnd );
	assingGlobalFunction( "rlVertex2f", lrlglVertex2f );
	assingGlobalFunction( "rlVertex3f", lrlglVertex3f );
	assingGlobalFunction( "rlTexCoord2f", lrlglTexCoord2f );
	assingGlobalFunction( "rlNormal3f", lrlglNormal3f );
	assingGlobalFunction( "rlColor4ub", lrlglColor4ub );
	assingGlobalFunction( "rlColor3f", lrlglColor3f );
	assingGlobalFunction( "rlColor4f", lrlglColor4f );
		/* Vertex buffers state. */
	assingGlobalFunction( "rlEnableVertexArray", lrlglEnableVertexArray );
	assingGlobalFunction( "rlDisableVertexArray", lrlglDisableVertexArray );
	assingGlobalFunction( "rlEnableVertexBuffer", lrlglEnableVertexBuffer );
	assingGlobalFunction( "rlDisableVertexBuffer", lrlglDisableVertexBuffer );
	assingGlobalFunction( "rlEnableVertexBufferElement", lrlglEnableVertexBufferElement );
	assingGlobalFunction( "rlDisableVertexBufferElement", lrlglDisableVertexBufferElement );
	assingGlobalFunction( "rlEnableVertexAttribute", lrlglEnableVertexAttribute );
	assingGlobalFunction( "rlDisableVertexAttribute", lrlglDisableVertexAttribute );
		/* Textures state. */
	assingGlobalFunction( "rlActiveTextureSlot", lrlglActiveTextureSlot );
	assingGlobalFunction( "rlEnableTexture", lrlglEnableTexture );
	assingGlobalFunction( "rlDisableTexture", lrlglDisableTexture );
	assingGlobalFunction( "rlEnableTextureCubemap", lrlglEnableTextureCubemap );
	assingGlobalFunction( "rlDisableTextureCubemap", lrlglDisableTextureCubemap );
	assingGlobalFunction( "rlTextureParameters", lrlglTextureParameters );
	assingGlobalFunction( "rlCubemapParameters", lrlglCubemapParameters );
		/* Shader state. */
	assingGlobalFunction( "rlEnableShader", lrlglEnableShader );
	assingGlobalFunction( "rlDisableShader", lrlglDisableShader );
		/* Framebuffer state. */
	assingGlobalFunction( "rlEnableFramebuffer", lrlglEnableFramebuffer );
	assingGlobalFunction( "rlDisableFramebuffer", lrlglDisableFramebuffer );
	assingGlobalFunction( "rlActiveDrawBuffers", lrlglActiveDrawBuffers );
		/* General render state. */
	assingGlobalFunction( "rlEnableColorBlend", lrlglEnableColorBlend );
	assingGlobalFunction( "rlDisableColorBlend", lrlglDisableColorBlend );
	assingGlobalFunction( "rlEnableDepthTest", lrlglEnableDepthTest );
	assingGlobalFunction( "rlDisableDepthTest", lrlglDisableDepthTest );
	assingGlobalFunction( "rlEnableDepthMask", lrlglEnableDepthMask );
	assingGlobalFunction( "rlDisableDepthMask", lrlglDisableDepthMask );
	assingGlobalFunction( "rlEnableBackfaceCulling", lrlglEnableBackfaceCulling );
	assingGlobalFunction( "rlDisableBackfaceCulling", lrlglDisableBackfaceCulling );
	assingGlobalFunction( "rlSetCullFace", lrlglSetCullFace );
	assingGlobalFunction( "rlEnableScissorTest", lrlglEnableScissorTest );
	assingGlobalFunction( "rlDisableScissorTest", lrlglDisableScissorTest );
	assingGlobalFunction( "rlScissor", lrlglScissor );
	assingGlobalFunction( "rlEnableWireMode", lrlglEnableWireMode );
	assingGlobalFunction( "rlDisableWireMode", lrlglDisableWireMode );
	assingGlobalFunction( "rlSetLineWidth", lrlglSetLineWidth );
	assingGlobalFunction( "rlGetLineWidth", lrlglGetLineWidth );
	assingGlobalFunction( "rlEnableSmoothLines", lrlglEnableSmoothLines );
	assingGlobalFunction( "rlDisableSmoothLines", lrlglDisableSmoothLines );
	assingGlobalFunction( "rlEnableStereoRender", lrlglEnableStereoRender );
	assingGlobalFunction( "rlDisableStereoRender", lrlglDisableStereoRender );
	assingGlobalFunction( "rlIsStereoRenderEnabled", lrlglIsStereoRenderEnabled );
	assingGlobalFunction( "rlClearColor", lrlglClearColor );
	assingGlobalFunction( "rlClearScreenBuffers", lrlglClearScreenBuffers );
	assingGlobalFunction( "rlCheckErrors", lrlglCheckErrors );
	assingGlobalFunction( "rlSetBlendMode", lrlglSetBlendMode );
	assingGlobalFunction( "rlSetBlendFactors", lrlglSetBlendFactors );
	assingGlobalFunction( "rlSetBlendFactorsSeparate", lrlglSetBlendFactorsSeparate );
		/* Initialization functions. */
	assingGlobalFunction( "rlGetVersion", lrlglGetVersion );
	assingGlobalFunction( "rlSetFramebufferWidth", lrlglSetFramebufferWidth );
	assingGlobalFunction( "rlGetFramebufferWidth", lrlglGetFramebufferWidth );
	assingGlobalFunction( "rlSetFramebufferHeight", lrlglSetFramebufferHeight );
	assingGlobalFunction( "rlGetFramebufferHeight", lrlglGetFramebufferHeight );
	assingGlobalFunction( "rlGetTextureIdDefault", lrlglGetTextureIdDefault );
	assingGlobalFunction( "rlGetShaderIdDefault", lrlglGetShaderIdDefault );
	assingGlobalFunction( "rlGetShaderLocsDefault", lrlglGetShaderLocsDefault );
		/* Render batch management. */
	assingGlobalFunction( "rlDrawRenderBatchActive", lrlglDrawRenderBatchActive );
	assingGlobalFunction( "rlCheckRenderBatchLimit", lrlglCheckRenderBatchLimit );
	assingGlobalFunction( "rlSetTexture", lrlglSetTexture );
		/* Vertex buffers management. */
	assingGlobalFunction( "rlLoadVertexArray", lrlglLoadVertexArray );
	assingGlobalFunction( "rlLoadVertexBuffer", lrlglLoadVertexBuffer );
	assingGlobalFunction( "rlLoadVertexBufferElement", lrlglLoadVertexBufferElement );
	assingGlobalFunction( "rlUpdateVertexBuffer", lrlglUpdateVertexBuffer );
	assingGlobalFunction( "rlUpdateVertexBufferElements", lrlglUpdateVertexBufferElements );
	assingGlobalFunction( "rlUnloadVertexArray", lrlglUnloadVertexArray );
	assingGlobalFunction( "rlUnloadVertexBuffer", lrlglUnloadVertexBuffer );
	assingGlobalFunction( "rlSetVertexAttribute", lrlglSetVertexAttribute );
	assingGlobalFunction( "rlSetVertexAttributeDivisor", lrlglSetVertexAttributeDivisor );
	assingGlobalFunction( "rlSetVertexAttributeDefault", lrlglSetVertexAttributeDefault );
	assingGlobalFunction( "rlDrawVertexArray", lrlglDrawVertexArray );
	assingGlobalFunction( "rlDrawVertexArrayElements", lrlglDrawVertexArrayElements );
	assingGlobalFunction( "rlDrawVertexArrayInstanced", lrlglDrawVertexArrayInstanced );
	assingGlobalFunction( "rlDrawVertexArrayElementsInstanced", lrlglDrawVertexArrayElementsInstanced );
		/* Textures management. */
	assingGlobalFunction( "rlLoadTexture", lrlglLoadTexture );
	assingGlobalFunction( "rlLoadTextureDepth", lrlglLoadTextureDepth );
	assingGlobalFunction( "rlUnloadTexture", lrlglUnloadTexture );
		/* Framebuffer management (fbo). */
	assingGlobalFunction( "rlLoadFramebuffer", lrlglLoadFramebuffer );
	assingGlobalFunction( "rlFramebufferAttach", lrlglFramebufferAttach );
	assingGlobalFunction( "rlFramebufferComplete", lrlglFramebufferComplete );
	assingGlobalFunction( "rlUnloadFramebuffer", lrlglUnloadFramebuffer );
		/* Shaders management */
	assingGlobalFunction( "rlLoadShaderCode", lrlglLoadShaderCode );
	assingGlobalFunction( "rlCompileShader", lrlglCompileShader );
	assingGlobalFunction( "rlLoadShaderProgram", lrlglLoadShaderProgram );
	assingGlobalFunction( "rlUnloadShaderProgram", lrlglUnloadShaderProgram );
	assingGlobalFunction( "rlGetLocationUniform", lrlglGetLocationUniform );
	assingGlobalFunction( "rlGetLocationAttrib", lrlglGetLocationAttrib );
	assingGlobalFunction( "rlSetUniform", lrlglSetUniform );
	assingGlobalFunction( "rlSetUniformMatrix", lrlglSetUniformMatrix );
	assingGlobalFunction( "rlSetUniformSampler", lrlglSetUniformSampler );
	assingGlobalFunction( "rlSetShader", lrlglSetShader );
		/* Compute shader management */
	assingGlobalFunction( "rlLoadComputeShaderProgram", lrlglLoadComputeShaderProgram );
	assingGlobalFunction( "rlComputeShaderDispatch", lrlglComputeShaderDispatch );
		/* Buffer management */
	assingGlobalFunction( "rlBindImageTexture", lrlglBindImageTexture );
		/* Matrix state management. */
	assingGlobalFunction( "rlGetMatrixModelview", lrlglGetMatrixModelview );
	assingGlobalFunction( "rlGetMatrixProjection", lrlglGetMatrixProjection );
	assingGlobalFunction( "rlGetMatrixTransform", lrlglGetMatrixTransform );
	assingGlobalFunction( "rlGetMatrixProjectionStereo", lrlglGetMatrixProjectionStereo );
	assingGlobalFunction( "rlGetMatrixViewOffsetStereo", lrlglGetMatrixViewOffsetStereo );
	assingGlobalFunction( "rlSetMatrixProjection", lrlglSetMatrixProjection );
	assingGlobalFunction( "rlSetMatrixModelview", lrlglSetMatrixModelview );
	assingGlobalFunction( "rlSetMatrixProjectionStereo", lrlglSetMatrixProjectionStereo );
	assingGlobalFunction( "rlSetMatrixViewOffsetStereo", lrlglSetMatrixViewOffsetStereo );

	/* OpenGL */
		/* Framebuffer management. */
	assingGlobalFunction( "glBlitFramebuffer", lglBlitFramebuffer );

	/* Easings */
		/* Linear Easing functions. */
	assingGlobalFunction( "EaseLinear", leasingsEaseLinear );
		/* Sine Easing functions. */
	assingGlobalFunction( "EaseSineIn", leasingsEaseSineIn );
	assingGlobalFunction( "EaseSineOut", leasingsEaseSineOut );
	assingGlobalFunction( "EaseSineInOut", leasingsEaseSineInOut );
		/* Circular Easing functions. */
	assingGlobalFunction( "EaseCircIn", leasingsEaseCircIn );
	assingGlobalFunction( "EaseCircOut", leasingsEaseCircOut );
	assingGlobalFunction( "EaseCircInOut", leasingsEaseCircInOut );
		/* Cubic Easing functions. */
	assingGlobalFunction( "EaseCubicIn", leasingsEaseCubicIn );
	assingGlobalFunction( "EaseCubicOut", leasingsEaseCubicOut );
	assingGlobalFunction( "EaseCubicInOut", leasingsEaseCubicInOut );
		/* Quadratic Easing functions. */
	assingGlobalFunction( "EaseQuadIn", leasingsEaseQuadIn );
	assingGlobalFunction( "EaseQuadOut", leasingsEaseQuadOut );
	assingGlobalFunction( "EaseQuadInOut", leasingsEaseQuadInOut );
		/* Exponential Easing functions. */
	assingGlobalFunction( "EaseExpoIn", leasingsEaseExpoIn );
	assingGlobalFunction( "EaseExpoOut", leasingsEaseExpoOut );
	assingGlobalFunction( "EaseExpoInOut", leasingsEaseExpoInOut );
		/* Back Easing functions. */
	assingGlobalFunction( "EaseBackIn", leasingsEaseBackIn );
	assingGlobalFunction( "EaseBackOut", leasingsEaseBackOut );
	assingGlobalFunction( "EaseBackInOut", leasingsEaseBackInOut );
		/* Bounce Easing functions. */
	assingGlobalFunction( "EaseBounceIn", leasingsEaseBounceIn );
	assingGlobalFunction( "EaseBounceOut", leasingsEaseBounceOut );
	assingGlobalFunction( "EaseBounceInOut", leasingsEaseBounceInOut );
		/* Elastic Easing functions. */
	assingGlobalFunction( "EaseElasticIn", leasingsEaseElasticIn );
	assingGlobalFunction( "EaseElasticOut", leasingsEaseElasticOut );
	assingGlobalFunction( "EaseElasticInOut", leasingsEaseElasticInOut );

	lua_pop( L, -1 );
}

/* Lua util functions. */

bool uluaGetBoolean( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TBOOLEAN );

	return lua_toboolean( L, index );
}

Color uluaGetColor( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Color color = { 0, 0, 0, 255 };

	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						color.r = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 1:
						color.g = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 2:
						color.b = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 3:
						color.a = (uint8_t)lua_tointeger( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "r", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.r = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "g", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.g = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "b", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.b = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "a", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.a = (uint8_t)lua_tointeger( L, -1 );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }
    return color;
}

Vector2 uluaGetVector2( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Vector2 vector = { 0.0f, 0.0f };

	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }
    return vector;
}

Vector3 uluaGetVector3( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Vector3 vector = { 0.0f, 0.0f, 0.0f };

	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					case 2:
						vector.z = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.z = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return vector;
}

Vector4 uluaGetVector4( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Vector4 vector = { 0.0f, 0.0f, 0.0f, 0.0f };

	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					case 2:
						vector.z = lua_tonumber( L, -1 );
						break;
					case 3:
						vector.w = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.z = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "w", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.w = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return vector;
}

Rectangle uluaGetRectangle( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Rectangle rect = { 0.0f, 0.0f, 0.0f, 0.0f };

	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						rect.x = lua_tonumber( L, -1 );
						break;
					case 1:
						rect.y = lua_tonumber( L, -1 );
						break;
					case 2:
						rect.width = lua_tonumber( L, -1 );
						break;
					case 3:
						rect.height = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "width", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.width = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "height", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.height = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return rect;
}

Quaternion uluaGetQuaternion( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
    Quaternion quaternion = { 0.0f, 0.0f, 0.0f, 0.0f };

	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						quaternion.x = lua_tonumber( L, -1 );
						break;
					case 1:
						quaternion.y = lua_tonumber( L, -1 );
						break;
					case 2:
						quaternion.z = lua_tonumber( L, -1 );
						break;
					case 3:
						quaternion.w = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.z = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "w", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.w = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return quaternion;
}

Matrix uluaGetMatrix( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Matrix matrix = { 0.0f };
	float m[4][4];

	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_istable( L, -1 ) ) {
			int t2 = lua_gettop( L ), j = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				if ( lua_isnumber( L, -1 ) ) {
					m[i][j] = lua_tonumber( L, -1 );
				}
				j++;
				lua_pop( L, 1 );
			}
        }
        i++;
        lua_pop( L, 1 );
    }
	matrix.m0 = m[0][0]; 	matrix.m1 = m[0][1]; 	matrix.m2 = m[0][2]; 	matrix.m3 = m[0][3];
	matrix.m4 = m[1][0]; 	matrix.m5 = m[1][1]; 	matrix.m6 = m[1][2]; 	matrix.m7 = m[1][3];
	matrix.m8 = m[2][0]; 	matrix.m9 = m[2][1]; 	matrix.m10 = m[2][2]; 	matrix.m11 = m[2][3];
	matrix.m12 = m[3][0]; 	matrix.m13 = m[3][1]; 	matrix.m14 = m[3][2]; 	matrix.m15 = m[3][3];

	return matrix;
}

BoundingBox uluaGetBoundingBox( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	BoundingBox box = { .min = { 0.0, 0.0, 0.0 }, .max = { 0.0, 0.0, 0.0 } };

	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						box.min = uluaGetVector3( L, lua_gettop( L ) );
						break;
					case 1:
						box.max = uluaGetVector3( L, lua_gettop( L ) );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "min", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					box.min = uluaGetVector3( L, lua_gettop( L ) );
				}
				else if ( strcmp( "max", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					box.max = uluaGetVector3( L, lua_gettop( L ) );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }

	return box;
}

Ray uluaGetRay( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Ray ray = { .position = { 0.0, 0.0, 0.0 }, .direction = { 0.0, 0.0, 0.0 } };

	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						ray.position = uluaGetVector3( L, lua_gettop( L ) );
						break;
					case 1:
						ray.direction = uluaGetVector3( L, lua_gettop( L ) );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "position", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					ray.position = uluaGetVector3( L, lua_gettop( L ) );
				}
				else if ( strcmp( "direction", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					ray.direction = uluaGetVector3( L, lua_gettop( L ) );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }

	return ray;
}

NPatchInfo uluaGetNPatchInfo( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	NPatchInfo npatch = { .source = { 0.0, 0.0, 0.0, 0.0 }, .left = 0, .top = 0, .right = 0, .bottom = 0, .layout = NPATCH_NINE_PATCH };

	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		/* Do not check type since there should be table and ints. */
		if ( lua_isnumber( L, -2 ) ) {
			switch ( i ) {
				case 0:
					npatch.source = uluaGetRectangle( L, lua_gettop( L ) );
					break;
				case 1:
					npatch.left = lua_tointeger( L, -1 );
					break;
				case 2:
					npatch.top = lua_tointeger( L, -1 );
					break;
				case 3:
					npatch.right = lua_tointeger( L, -1 );
					break;
				case 4:
					npatch.bottom = lua_tointeger( L, -1 );
					break;
				case 5:
					npatch.layout = lua_tointeger( L, -1 );
					break;
				default:
					break;
			}
		}
		else if ( lua_isstring( L, -2 ) ) {
			if ( strcmp( "source", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.source = uluaGetRectangle( L, lua_gettop( L ) );
			}
			else if ( strcmp( "left", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.left = lua_tointeger( L, -1 );
			}
			else if ( strcmp( "top", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.top = lua_tointeger( L, -1 );
			}
			else if ( strcmp( "right", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.right = lua_tointeger( L, -1 );
			}
			else if ( strcmp( "bottom", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.bottom = lua_tointeger( L, -1 );
			}
			else if ( strcmp( "layout", (char*)lua_tostring( L, -2 ) ) == 0 ) {
				npatch.layout = lua_tointeger( L, -1 );
			}
		}
		i++;
		lua_pop( L, 1 );
    }
	return npatch;
}

Buffer* uluaGetBuffer( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Buffer*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Buffer" );
}

Image* uluaGetImage( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Image*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Image" );
}

Texture* uluaGetTexture( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Texture*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Texture" );
}

RenderTexture* uluaGetRenderTexture( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (RenderTexture*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "RenderTexture" );
}

Shader* uluaGetShader( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Shader*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Shader" );
}

Mesh* uluaGetMesh( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Mesh*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Mesh" );
}

Camera2D* uluaGetCamera2D( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Camera2D*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Camera2D" );
}

Camera3D* uluaGetCamera3D( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Camera3D*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Camera3D" );
}

Font* uluaGetFont( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Font*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Font" );
}

Wave* uluaGetWave( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Wave*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Wave" );
}

Sound* uluaGetSound( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Sound*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Sound" );
}

Music* uluaGetMusic( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Music*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Music" );
}

Light* uluaGetLight( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Light*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Light" );
}

Material* uluaGetMaterial( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Material*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Material" );
}

Model* uluaGetModel( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (Model*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "Model" );
}

ModelAnimation* uluaGetModelAnimation( lua_State *L, int index ) {
	if ( lua_islightuserdata( L, index ) ) {
		return (ModelAnimation*)lua_touserdata( L, index );
	}
	return luaL_checkudata( L, index, "ModelAnimation" );
}

/* Push types. */

void uluaPushColor( lua_State *L, Color color ) {
	lua_createtable( L, 3, 0 );
    lua_pushnumber( L, color.r );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, color.g );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, color.b );
    lua_rawseti( L, -2, 3 );
    lua_pushnumber( L, color.a );
    lua_rawseti( L, -2, 4 );
}

void uluaPushVector2( lua_State *L, Vector2 vector ) {
	lua_createtable( L, 2, 0 );
    lua_pushnumber( L, vector.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, vector.y );
    lua_rawseti( L, -2, 2 );
}

void uluaPushVector3( lua_State *L, Vector3 vector ) {
	lua_createtable( L, 3, 0 );
    lua_pushnumber( L, vector.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, vector.y );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, vector.z );
    lua_rawseti( L, -2, 3 );
}

void uluaPushVector4( lua_State *L, Vector4 vector ) {
	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, vector.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, vector.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, vector.z );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, vector.w );
	lua_rawseti( L, -2, 4 );
}

void uluaPushRectangle( lua_State *L, Rectangle rect ) {
	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, rect.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, rect.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, rect.width );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, rect.height );
	lua_rawseti( L, -2, 4 );
}

void uluaPushQuaternion( lua_State *L, Quaternion quaternion ) {
	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, quaternion.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, quaternion.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, quaternion.z );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, quaternion.w );
	lua_rawseti( L, -2, 4 );
}

void uluaPushMatrix( lua_State *L, Matrix matrix ) {
	lua_createtable( L, 4, 0 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m0 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m1 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m2 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m3 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m4 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m5 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m6 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m7 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 2 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m8 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m9 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m10 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m11 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 3 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m12 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m13 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m14 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m15 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 4 );
}

void uluaPushRay( lua_State *L, Ray ray ) {
	lua_createtable( L, 2, 0 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, ray.position.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, ray.position.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, ray.position.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, ray.direction.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, ray.direction.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, ray.direction.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 2 );
}

void uluaPushRayCollision( lua_State *L, RayCollision rayCol ) {
	lua_createtable( L, 4, 0 );
	lua_pushboolean( L, rayCol.hit );
	lua_setfield( L, -2, "hit" );
	lua_pushnumber( L, rayCol.distance );
	lua_setfield( L, -2, "distance" );
	uluaPushVector3( L, rayCol.point );
	lua_setfield( L, -2, "point" );
	uluaPushVector3( L, rayCol.normal );
	lua_setfield( L, -2, "normal" );
}

void uluaPushBoundingBox( lua_State *L, BoundingBox box ) {
	lua_createtable( L, 2, 0 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, box.min.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, box.min.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, box.min.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, box.max.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, box.max.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, box.max.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 2 );
}

void uluaPushGlyphInfo( lua_State *L, GlyphInfo glyphInfo, Image *image ) {
	lua_createtable( L, 4, 0 );
	lua_pushinteger( L, glyphInfo.value );
	lua_setfield( L, -2, "value" );
	lua_pushinteger( L, glyphInfo.offsetX );
	lua_setfield( L, -2, "offsetX" );
	lua_pushinteger( L, glyphInfo.offsetY );
	lua_setfield( L, -2, "offsetY" );
	lua_pushinteger( L, glyphInfo.advanceX );
	lua_setfield( L, -2, "advanceX" );
	lua_pushlightuserdata( L, image );
	lua_setfield( L, -2, "image" );
}

void uluaPushBuffer( lua_State *L, Buffer buffer ) {
	Buffer *bufferP = lua_newuserdata( L, sizeof( Buffer ) );
	*bufferP = buffer;
	luaL_setmetatable( L, "Buffer" );
}

void uluaPushImage( lua_State *L, Image image ) {
	Image *imageP = lua_newuserdata( L, sizeof( Image ) );
	*imageP = image;
	luaL_setmetatable( L, "Image" );
}

void uluaPushTexture( lua_State *L, Texture texture ) {
	Texture *textureP = lua_newuserdata( L, sizeof( Texture ) );
	*textureP = texture;
	luaL_setmetatable( L, "Texture" );
}

void uluaPushRenderTexture( lua_State *L, RenderTexture renderTexture ) {
	RenderTexture *renderTextureP = lua_newuserdata( L, sizeof( RenderTexture ) );
	*renderTextureP = renderTexture;
	luaL_setmetatable( L, "RenderTexture" );
}

void uluaPushCamera2D( lua_State *L, Camera2D camera ) {
	Camera2D *cameraP = lua_newuserdata( L, sizeof( Camera2D ) );
	*cameraP = camera;
	luaL_setmetatable( L, "Camera2D" );
}

void uluaPushCamera3D( lua_State *L, Camera3D camera ) {
	Camera3D *cameraP = lua_newuserdata( L, sizeof( Camera3D ) );
	*cameraP = camera;
	luaL_setmetatable( L, "Camera3D" );
}

void uluaPushShader( lua_State *L, Shader shader ) {
	Shader *shaderP = lua_newuserdata( L, sizeof( Shader ) );
	*shaderP = shader;
	luaL_setmetatable( L, "Shader" );
}

void uluaPushFont( lua_State *L, Font font ) {
	Font *fontP = lua_newuserdata( L, sizeof( Font ) );
	*fontP = font;
	luaL_setmetatable( L, "Font" );
}

void uluaPushWave( lua_State *L, Wave wave ) {
	Wave *waveP = lua_newuserdata( L, sizeof( Wave ) );
	*waveP = wave;
	luaL_setmetatable( L, "Wave" );
}

void uluaPushSound( lua_State *L, Sound sound ) {
	Sound *soundP = lua_newuserdata( L, sizeof( Sound ) );
	*soundP = sound;
	luaL_setmetatable( L, "Sound" );
}

void uluaPushMusic( lua_State *L, Music music ) {
	Music *musicP = lua_newuserdata( L, sizeof( Music ) );
	*musicP = music;
	luaL_setmetatable( L, "Music" );
}

void uluaPushLight( lua_State *L, Light light ) {
	Light *lightP = lua_newuserdata( L, sizeof( Light ) );
	*lightP = light;
	luaL_setmetatable( L, "Light" );
}

void uluaPushMaterial( lua_State *L, Material material ) {
	Material *materialP = lua_newuserdata( L, sizeof( Material ) );
	*materialP = material;
	luaL_setmetatable( L, "Material" );
}

void uluaPushMesh( lua_State *L, Mesh mesh ) {
	Mesh *meshP = lua_newuserdata( L, sizeof( Mesh ) );
	*meshP = mesh;
	luaL_setmetatable( L, "Mesh" );
}

void uluaPushModel( lua_State *L, Model model ) {
	Model *modelP = lua_newuserdata( L, sizeof( Model ) );
	*modelP = model;
	luaL_setmetatable( L, "Model" );
}

void uluaPushModelAnimation( lua_State *L, ModelAnimation modelAnimation ) {
	ModelAnimation *modelAnimationP = lua_newuserdata( L, sizeof( ModelAnimation ) );
	*modelAnimationP = modelAnimation;
	luaL_setmetatable( L, "ModelAnimation" );
}

int uluaGetTableLen( lua_State *L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        i++;
        lua_pop( L, 1 );
    }
    return i;
}
