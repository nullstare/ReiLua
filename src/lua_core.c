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
#include "bitwiseOp.h"

#ifdef PLATFORM_DESKTOP
	#include "platforms/core_desktop_glfw.c"
#elif PLATFORM_DESKTOP_SDL2
	#include "platforms/core_desktop_sdl2.c"
#elif PLATFORM_DESKTOP_SDL3
	#include "platforms/core_desktop_sdl3.c"
#elif PLATFORM_WEB
	#include "platforms/core_web.c"
#endif

/* Custom implementation since LuaJIT doesn't have lua_geti. */
static void lua_getiCustom( lua_State* L, int index, int i ) {
    lua_pushinteger( L, i ); // Push the index onto the stack
    lua_gettable( L, index ); // Get the value at the index
}

/* Define types. */

	/* Buffer. */
static int gcBuffer( lua_State* L ) {
	if ( state->gcUnload ) {
		Buffer* buffer = luaL_checkudata( L, 1, "Buffer" );
		uluaUnloadBuffer( buffer );
	}
	return 0;
}

static void defineBuffer() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Buffer" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcBuffer );
	lua_setfield( L, -2, "__gc" );
}

	/* Image */
static int gcImage( lua_State* L ) {
	if ( state->gcUnload ) {
		Image* image = luaL_checkudata( L, 1, "Image" );
		uluaUnloadImage( image );
	}
	return 0;
}

static void defineImage() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Image" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcImage );
	lua_setfield( L, -2, "__gc" );
}

	/* Texture */
static int gcTexture( lua_State* L ) {
	if ( state->gcUnload ) {
		Texture* texture = luaL_checkudata( L, 1, "Texture" );
		uluaUnloadTexture( texture );
	}
	return 0;
}

static void defineTexture() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Texture" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcTexture );
	lua_setfield( L, -2, "__gc" );
}

	/* RenderRexture. */
static int gcRenderTexture( lua_State* L ) {
	if ( state->gcUnload ) {
		RenderTexture* renderTexture = luaL_checkudata( L, 1, "RenderTexture" );
		uluaUnloadRenderTexture( renderTexture );
	}
	return 0;
}

static void defineRenderTexture() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "RenderTexture" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcRenderTexture );
	lua_setfield( L, -2, "__gc" );
}

	/* Camera2D. */
static void defineCamera2D() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Camera2D" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Camera3D. */
static void defineCamera3D() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Camera3D" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Shader. */
static int gcShader( lua_State* L ) {
	if ( state->gcUnload ) {
		Shader* shader = luaL_checkudata( L, 1, "Shader" );
		uluaUnloadShader( shader );
	}
	return 0;
}

static void defineShader() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Shader" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcShader );
	lua_setfield( L, -2, "__gc" );
}

	/* Font. */
static int gcFont( lua_State* L ) {
	if ( state->gcUnload ) {
		Font* font = luaL_checkudata( L, 1, "Font" );
		uluaUnloadFont( font );
	}
	return 0;
}

static void defineFont() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Font" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcFont );
	lua_setfield( L, -2, "__gc" );
}

	/* GlyphInfo. */
static int gcGlyphInfo( lua_State* L ) {
	if ( state->gcUnload ) {
		GlyphInfo* glyph = luaL_checkudata( L, 1, "GlyphInfo" );
		uluaUnloadGlyphInfo( glyph );
	}
	return 0;
}

static void defineGlyphInfo() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "GlyphInfo" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcGlyphInfo );
	lua_setfield( L, -2, "__gc" );
}

	/* Wave. */
static int gcWave( lua_State* L ) {
	if ( state->gcUnload ) {
		Wave* wave = luaL_checkudata( L, 1, "Wave" );
		uluaUnloadWave( wave );
	}
	return 0;
}

static void defineWave() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Wave" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcWave );
	lua_setfield( L, -2, "__gc" );
}

	/* Sound. */
static int gcSound( lua_State* L ) {
	if ( state->gcUnload ) {
		Sound* sound = luaL_checkudata( L, 1, "Sound" );
		uluaUnloadSound( sound );
	}
	return 0;
}

static void defineSound() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Sound" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcSound );
	lua_setfield( L, -2, "__gc" );
}

	/* SoundAlias. */
static int gcSoundAlias( lua_State* L ) {
	if ( state->gcUnload ) {
		Sound* sound = luaL_checkudata( L, 1, "SoundAlias" );
		uluaUnloadSoundAlias( sound );
	}
	return 0;
}

static void defineSoundAlias() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "SoundAlias" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcSoundAlias );
	lua_setfield( L, -2, "__gc" );
}

	/* Music. */
static int gcMusic( lua_State* L ) {
	if ( state->gcUnload ) {
		Music* music = luaL_checkudata( L, 1, "Music" );
		uluaUnloadMusic( music );
	}
	return 0;
}

static void defineMusic() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Music" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcMusic );
	lua_setfield( L, -2, "__gc" );
}

	/* AudioStream. */
static int gcAudioStream( lua_State* L ) {
	if ( state->gcUnload ) {
		AudioStream* stream = luaL_checkudata( L, 1, "AudioStream" );
		uluaUnloadAudioStream( stream );
	}
	return 0;
}

static void defineAudioStream() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "AudioStream" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcAudioStream );
	lua_setfield( L, -2, "__gc" );
}

	/* Light. */
static void defineLight() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Light" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* Material. */
static int gcMaterial( lua_State* L ) {
	if ( state->gcUnload ) {
		Material* material = luaL_checkudata( L, 1, "Material" );
		uluaUnloadMaterial( material, true );
	}
	return 0;
}

static void defineMaterial() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Material" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcMaterial );
	lua_setfield( L, -2, "__gc" );
}

	/* Mesh. */
static int gcMesh( lua_State* L ) {
	if ( state->gcUnload ) {
		Mesh* mesh = luaL_checkudata( L, 1, "Mesh" );
		uluaUnloadMesh( mesh );
	}
	return 0;
}

static void defineMesh() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Mesh" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcMesh );
	lua_setfield( L, -2, "__gc" );
}

	/* Model. */
static int gcModel( lua_State* L ) {
	if ( state->gcUnload ) {
		Model* model = luaL_checkudata( L, 1, "Model" );
		uluaUnloadModel( model, true );
	}
	return 0;
}

static void defineModel() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "Model" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcModel );
	lua_setfield( L, -2, "__gc" );
}

	/* ModelAnimation. */
static int gcModelAnimation( lua_State* L ) {
	if ( state->gcUnload ) {
		ModelAnimation* modelAnimation = luaL_checkudata( L, 1, "ModelAnimation" );
		uluaUnloadModelAnimation( modelAnimation );
	}
	return 0;
}

static void defineModelAnimation() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "ModelAnimation" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcModelAnimation );
	lua_setfield( L, -2, "__gc" );
}

	/* ModelSkeleton. */
static int gcModelSkeleton( lua_State* L ) {
	if ( state->gcUnload ) {
		ModelSkeleton* modelSkeleton = luaL_checkudata( L, 1, "ModelSkeleton" );
		uluaUnloadModelSkeleton( modelSkeleton );
	}
	return 0;
}

static void defineModelSkeleton() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "ModelSkeleton" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcModelSkeleton );
	lua_setfield( L, -2, "__gc" );
}

	/* rlRenderBatch. */
static int gcRLRenderBatch( lua_State* L ) {
	if ( state->gcUnload ) {
		rlRenderBatch* renderBatch = luaL_checkudata( L, 1, "rlRenderBatch" );
		uluaUnloadRLRenderBatch( renderBatch );
	}
	return 0;
}

static void defineRLRenderBatch() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "rlRenderBatch" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcRLRenderBatch );
	lua_setfield( L, -2, "__gc" );
}

	/* AutomationEvent. */
static void defineAutomationEvent() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "AutomationEvent" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
}

	/* AutomationEventList. */
static int gcAutomationEventList( lua_State* L ) {
	if ( state->gcUnload ) {
		AutomationEventList* automationEventList = luaL_checkudata( L, 1, "AutomationEventList" );
		uluaUnloadAutomationEventList( automationEventList );
	}
	return 0;
}

static void defineAutomationEventList() {
	lua_State* L = state->luaState;

	luaL_newmetatable( L, "AutomationEventList" );
	lua_pushvalue( L, -1 );
	lua_setfield( L, -2, "__index" );
	lua_pushcfunction( L, gcAutomationEventList );
	lua_setfield( L, -2, "__gc" );
}

/* Assign globals. */

void assignGlobalInt( int value, const char* name ) {
	lua_State* L = state->luaState;
	lua_pushinteger( L, value );
	lua_setfield( L, -2, name );
}

void assignGlobalFloat( float value, const char* name ) {
	lua_State* L = state->luaState;
	lua_pushnumber( L, value );
	lua_setfield( L, -2, name );
}

void assignGlobalDouble( double value, const char* name ) {
	lua_State* L = state->luaState;
	lua_pushnumber( L, value );
	lua_setfield( L, -2, name );
}

void assignGlobalColor( Color color, const char* name ) {
	lua_State* L = state->luaState;
	uluaPushColor( L, color );
	lua_setfield( L, -2, name );
}

void assignGlobalFunction( const char* name, int ( *functionPtr )( lua_State* ) ) {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, functionPtr );
	lua_setfield( L, -2, name );
}

void assignGlobalString( const char* value, const char* name ) {
	lua_State* L = state->luaState;
	lua_pushstring( L, value );
	lua_setfield( L, -2, name );
}

static void defineGlobals() {
	lua_State* L = state->luaState;

	lua_newtable( L );
	lua_setglobal( L, "RL" );
	lua_getglobal( L, "RL" );

/* Note! Docgen rely on this line format. */
/*DOC_DEFINES_START*/
	/* System/Window config flags */
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
	/* Trace log level */
	assignGlobalInt( LOG_ALL, "LOG_ALL" ); // Display all logs
	assignGlobalInt( LOG_TRACE, "LOG_TRACE" ); // Trace logging, intended for internal use only
	assignGlobalInt( LOG_DEBUG, "LOG_DEBUG" ); // Debug logging, used for internal debugging, it should be disabled on release builds
	assignGlobalInt( LOG_INFO, "LOG_INFO" ); // Info logging, used for program execution info
	assignGlobalInt( LOG_WARNING, "LOG_WARNING" ); // Warning logging, used on recoverable failures
	assignGlobalInt( LOG_ERROR, "LOG_ERROR" ); // Error logging, used on unrecoverable failures
	assignGlobalInt( LOG_FATAL, "LOG_FATAL" ); // Fatal logging, used to abort program: exit(EXIT_FAILURE)
	assignGlobalInt( LOG_NONE, "LOG_NONE" ); // Disable logging
	/* Keyboard keys (US keyboard layout) */
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
	/* Mouse buttons */
	assignGlobalInt( MOUSE_BUTTON_LEFT, "MOUSE_BUTTON_LEFT" ); // Mouse button left
	assignGlobalInt( MOUSE_BUTTON_RIGHT, "MOUSE_BUTTON_RIGHT" ); // Mouse button right
	assignGlobalInt( MOUSE_BUTTON_MIDDLE, "MOUSE_BUTTON_MIDDLE" ); // Mouse button middle (pressed wheel)
	assignGlobalInt( MOUSE_BUTTON_SIDE, "MOUSE_BUTTON_SIDE" ); // Mouse button side (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_EXTRA, "MOUSE_BUTTON_EXTRA" ); // Mouse button extra (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_FORWARD, "MOUSE_BUTTON_FORWARD" ); // Mouse button forward (advanced mouse device)
	assignGlobalInt( MOUSE_BUTTON_BACK, "MOUSE_BUTTON_BACK" ); // Mouse button back (advanced mouse device)
	/* Mouse cursor */
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
	/* Gamepad buttons */
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
	/* Gamepad axis */
	assignGlobalInt( GAMEPAD_AXIS_LEFT_X, "GAMEPAD_AXIS_LEFT_X" ); // Gamepad left stick X axis
	assignGlobalInt( GAMEPAD_AXIS_LEFT_Y, "GAMEPAD_AXIS_LEFT_Y" ); // Gamepad left stick Y axis
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_X, "GAMEPAD_AXIS_RIGHT_X" ); // Gamepad right stick X axis
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_Y, "GAMEPAD_AXIS_RIGHT_Y" ); // Gamepad right stick Y axis
	assignGlobalInt( GAMEPAD_AXIS_LEFT_TRIGGER, "GAMEPAD_AXIS_LEFT_TRIGGER" ); // Gamepad back trigger left, pressure level: [1..-1]
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_TRIGGER, "GAMEPAD_AXIS_RIGHT_TRIGGER" ); // Gamepad back trigger right, pressure level: [1..-1]
	/* Material map index */
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
	/* Shader location index */
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
	assignGlobalInt( SHADER_LOC_VERTEX_BONEIDS, "SHADER_LOC_VERTEX_BONEIDS" ); // Shader location: vertex attribute: boneIds
	assignGlobalInt( SHADER_LOC_VERTEX_BONEWEIGHTS, "SHADER_LOC_VERTEX_BONEWEIGHTS" ); // Shader location: vertex attribute: boneWeights
	// assignGlobalInt( SHADER_LOC_BONE_MATRICES, "SHADER_LOC_BONE_MATRICES" ); // Shader location: array of matrices uniform: boneMatrices
	assignGlobalInt( SHADER_LOC_MAP_DIFFUSE, "SHADER_LOC_MAP_DIFFUSE" ); // Shader location: sampler2d texture: diffuce (same as: SHADER_LOC_MAP_ALBEDO)
	assignGlobalInt( SHADER_LOC_MAP_SPECULAR, "SHADER_LOC_MAP_SPECULAR" ); // Shader location: sampler2d texture: specular (same as: SHADER_LOC_MAP_METALNESS)
	/* Shader uniform data type */
	assignGlobalInt( SHADER_UNIFORM_FLOAT, "SHADER_UNIFORM_FLOAT" ); // Shader uniform type: float
	assignGlobalInt( SHADER_UNIFORM_VEC2, "SHADER_UNIFORM_VEC2" ); // Shader uniform type: vec2 (2 float)
	assignGlobalInt( SHADER_UNIFORM_VEC3, "SHADER_UNIFORM_VEC3" ); // Shader uniform type: vec3 (3 float)
	assignGlobalInt( SHADER_UNIFORM_VEC4, "SHADER_UNIFORM_VEC4" ); // Shader uniform type: vec4 (4 float)
	assignGlobalInt( SHADER_UNIFORM_INT, "SHADER_UNIFORM_INT" ); // Shader uniform type: int
	assignGlobalInt( SHADER_UNIFORM_IVEC2, "SHADER_UNIFORM_IVEC2" ); // Shader uniform type: ivec2 (2 int)
	assignGlobalInt( SHADER_UNIFORM_IVEC3, "SHADER_UNIFORM_IVEC3" ); // Shader uniform type: ivec3 (3 int)
	assignGlobalInt( SHADER_UNIFORM_IVEC4, "SHADER_UNIFORM_IVEC4" ); // Shader uniform type: ivec4 (4 int)
	assignGlobalInt( SHADER_UNIFORM_SAMPLER2D, "SHADER_UNIFORM_SAMPLER2D" ); // Shader uniform type: sampler2d
	/* Shader attribute data types */
	assignGlobalInt( SHADER_ATTRIB_FLOAT, "SHADER_ATTRIB_FLOAT" ); // Shader attribute type: float
	assignGlobalInt( SHADER_ATTRIB_VEC2, "SHADER_ATTRIB_VEC2" ); // Shader attribute type: vec2 (2 float)
	assignGlobalInt( SHADER_ATTRIB_VEC3, "SHADER_ATTRIB_VEC3" ); // Shader attribute type: vec3 (3 float)
	assignGlobalInt( SHADER_ATTRIB_VEC4, "SHADER_ATTRIB_VEC4" ); // Shader attribute type: vec4 (4 float)
	/* Pixel formats */
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
	/* Texture parameters: filter mode */
	assignGlobalInt( TEXTURE_FILTER_POINT, "TEXTURE_FILTER_POINT" ); // No filter, just pixel approximation
	assignGlobalInt( TEXTURE_FILTER_BILINEAR, "TEXTURE_FILTER_BILINEAR" ); // Linear filtering
	assignGlobalInt( TEXTURE_FILTER_TRILINEAR, "TEXTURE_FILTER_TRILINEAR" ); // Trilinear filtering (linear with mipmaps)
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_4X, "TEXTURE_FILTER_ANISOTROPIC_4X" ); // Anisotropic filtering 4x
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_8X, "TEXTURE_FILTER_ANISOTROPIC_8X" ); // Anisotropic filtering 8x
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_16X, "TEXTURE_FILTER_ANISOTROPIC_16X" ); // Anisotropic filtering 16x
	/* Texture parameters: wrap mode */
	assignGlobalInt( TEXTURE_WRAP_REPEAT, "TEXTURE_WRAP_REPEAT" ); // Repeats texture in tiled mode
	assignGlobalInt( TEXTURE_WRAP_CLAMP, "TEXTURE_WRAP_CLAMP" ); // Clamps texture to edge pixel in tiled mode
	assignGlobalInt( TEXTURE_WRAP_MIRROR_REPEAT, "TEXTURE_WRAP_MIRROR_REPEAT" ); // Mirrors and repeats the texture in tiled mode
	assignGlobalInt( TEXTURE_WRAP_MIRROR_CLAMP, "TEXTURE_WRAP_MIRROR_CLAMP" ); // Mirrors and clamps to border the texture in tiled mode
	/* Cubemap layouts */
	assignGlobalInt( CUBEMAP_LAYOUT_AUTO_DETECT, "CUBEMAP_LAYOUT_AUTO_DETECT" ); // Automatically detect layout type
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_VERTICAL, "CUBEMAP_LAYOUT_LINE_VERTICAL" ); // Layout is defined by a vertical line with faces
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_HORIZONTAL, "CUBEMAP_LAYOUT_LINE_HORIZONTAL" ); // Layout is defined by a horizontal line with faces
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR" ); // Layout is defined by a 3x4 cross with cubemap faces
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE" ); // Layout is defined by a 4x3 cross with cubemap faces
	/* Font type, defines generation method */
	assignGlobalInt( FONT_DEFAULT, "FONT_DEFAULT" ); // Default font generation, anti-aliased
	assignGlobalInt( FONT_BITMAP, "FONT_BITMAP" ); // Bitmap font generation, no anti-aliasing
	assignGlobalInt( FONT_SDF, "FONT_SDF" ); // SDF font generation, requires external shader
	/* Color blending modes (pre-defined) */
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
	/* Camera system modes */
	assignGlobalInt( CAMERA_CUSTOM, "CAMERA_CUSTOM" ); // Custom camera
	assignGlobalInt( CAMERA_FREE, "CAMERA_FREE" ); // Free camera
	assignGlobalInt( CAMERA_ORBITAL, "CAMERA_ORBITAL" ); // Orbital camera
	assignGlobalInt( CAMERA_FIRST_PERSON, "CAMERA_FIRST_PERSON" ); // First person camera
	assignGlobalInt( CAMERA_THIRD_PERSON, "CAMERA_THIRD_PERSON" ); // Third person camera
	/* Camera projection */
	assignGlobalInt( CAMERA_PERSPECTIVE, "CAMERA_PERSPECTIVE" ); // Perspective projection
	assignGlobalInt( CAMERA_ORTHOGRAPHIC, "CAMERA_ORTHOGRAPHIC" ); // Orthographic projection
	/* N-patch layout */
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
	assignGlobalFloat( EPSILON, "EPSILON" ); // Epsilon
	assignGlobalFloat( DEG2RAD, "DEG2RAD" ); // Degrees to radians
	assignGlobalFloat( RAD2DEG, "RAD2DEG" ); // Radians to degrees
	/* Gui control state */
	assignGlobalInt( STATE_NORMAL, "STATE_NORMAL" );
	assignGlobalInt( STATE_FOCUSED, "STATE_FOCUSED" );
	assignGlobalInt( STATE_PRESSED, "STATE_PRESSED" );
	assignGlobalInt( STATE_DISABLED, "STATE_DISABLED" );
	/* Gui control text alignment */
	assignGlobalInt( TEXT_ALIGN_LEFT, "TEXT_ALIGN_LEFT" );
	assignGlobalInt( TEXT_ALIGN_CENTER, "TEXT_ALIGN_CENTER" );
	assignGlobalInt( TEXT_ALIGN_RIGHT, "TEXT_ALIGN_RIGHT" );
	/* Gui control text alignment vertical */
	assignGlobalInt( TEXT_ALIGN_TOP, "TEXT_ALIGN_TOP" );
	assignGlobalInt( TEXT_ALIGN_MIDDLE, "TEXT_ALIGN_MIDDLE" );
	assignGlobalInt( TEXT_ALIGN_BOTTOM, "TEXT_ALIGN_BOTTOM" );
	/* Gui control text wrap mode */
	assignGlobalInt( TEXT_WRAP_NONE, "TEXT_WRAP_NONE" );
	assignGlobalInt( TEXT_WRAP_CHAR, "TEXT_WRAP_CHAR" );
	assignGlobalInt( TEXT_WRAP_WORD, "TEXT_WRAP_WORD" );
	/* Gui controls */
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
	/* Gui base properties for every control */
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
	/* Gui extended properties depend on control */
	assignGlobalInt( TEXT_SIZE, "TEXT_SIZE" ); // Text size (glyphs max height)
	assignGlobalInt( TEXT_SPACING, "TEXT_SPACING" ); // Text spacing between glyphs
	assignGlobalInt( LINE_COLOR, "LINE_COLOR" ); // Line control color
	assignGlobalInt( BACKGROUND_COLOR, "BACKGROUND_COLOR" ); // Background color
	assignGlobalInt( TEXT_LINE_SPACING, "TEXT_LINE_SPACING" ); // Text spacing between lines
	assignGlobalInt( TEXT_ALIGNMENT_VERTICAL, "TEXT_ALIGNMENT_VERTICAL" ); // Text vertical alignment inside text bounds (after border and padding)
	assignGlobalInt( TEXT_WRAP_MODE, "TEXT_WRAP_MODE" ); // Text wrap-mode inside text bounds
	/* Gui Toggle/ToggleGroup */
	assignGlobalInt( GROUP_PADDING, "GROUP_PADDING" ); // ToggleGroup separation between toggles
	/* Gui Slider/SliderBar */
	assignGlobalInt( SLIDER_WIDTH, "SLIDER_WIDTH" ); // Slider size of internal bar
	assignGlobalInt( SLIDER_PADDING, "SLIDER_PADDING" ); // Slider/SliderBar internal bar padding
	/* Gui ProgressBar */
	assignGlobalInt( PROGRESS_PADDING, "PROGRESS_PADDING" ); // ProgressBar internal padding
	/* Gui ScrollBar */
	assignGlobalInt( ARROWS_SIZE, "ARROWS_SIZE" );
	assignGlobalInt( ARROWS_VISIBLE, "ARROWS_VISIBLE" );
	assignGlobalInt( SCROLL_SLIDER_PADDING, "SCROLL_SLIDER_PADDING" ); // (SLIDERBAR, SLIDER_PADDING)
	assignGlobalInt( SCROLL_SLIDER_SIZE, "SCROLL_SLIDER_SIZE" );
	assignGlobalInt( SCROLL_PADDING, "SCROLL_PADDING" );
	assignGlobalInt( SCROLL_SPEED, "SCROLL_SPEED" );
	/* Gui CheckBox */
	assignGlobalInt( CHECK_PADDING, "CHECK_PADDING" ); // CheckBox internal check padding
	/* Gui ComboBox */
	assignGlobalInt( COMBO_BUTTON_WIDTH, "COMBO_BUTTON_WIDTH" ); // ComboBox right button width
	assignGlobalInt( COMBO_BUTTON_SPACING, "COMBO_BUTTON_SPACING" ); // ComboBox button separation
	/* Gui DropdownBox */
	assignGlobalInt( ARROW_PADDING, "ARROW_PADDING" ); // DropdownBox arrow separation from border and items
	assignGlobalInt( DROPDOWN_ITEMS_SPACING, "DROPDOWN_ITEMS_SPACING" ); // DropdownBox items separation
	/* Gui TextBox/TextBoxMulti/ValueBox/Spinner */
	assignGlobalInt( TEXT_READONLY, "TEXT_READONLY" ); // TextBox in read-only mode: 0-text editable, 1-text no-editable
	/* Gui Spinner */
	assignGlobalInt( SPIN_BUTTON_WIDTH, "SPIN_BUTTON_WIDTH" ); // Spinner left/right buttons width
	assignGlobalInt( SPIN_BUTTON_SPACING, "SPIN_BUTTON_SPACING" ); // Spinner buttons separation
	/* Gui ListView */
	assignGlobalInt( LIST_ITEMS_HEIGHT, "LIST_ITEMS_HEIGHT" ); // ListView items height
	assignGlobalInt( LIST_ITEMS_SPACING, "LIST_ITEMS_SPACING" ); // ListView items separation
	assignGlobalInt( SCROLLBAR_WIDTH, "SCROLLBAR_WIDTH" ); // ListView scrollbar size (usually width)
	assignGlobalInt( SCROLLBAR_SIDE, "SCROLLBAR_SIDE" ); // ListView scrollbar side (0-left, 1-right)
	/* Gui ColorPicker */
	assignGlobalInt( COLOR_SELECTOR_SIZE, "COLOR_SELECTOR_SIZE" );
	assignGlobalInt( HUEBAR_WIDTH, "HUEBAR_WIDTH" ); // ColorPicker right hue bar width
	assignGlobalInt( HUEBAR_PADDING, "HUEBAR_PADDING" ); // ColorPicker right hue bar separation from panel
	assignGlobalInt( HUEBAR_SELECTOR_HEIGHT, "HUEBAR_SELECTOR_HEIGHT" ); // ColorPicker right hue bar selector height
	assignGlobalInt( HUEBAR_SELECTOR_OVERFLOW, "HUEBAR_SELECTOR_OVERFLOW" ); // ColorPicker right hue bar selector overflow
	/* Gui Icons enumeration */
	assignGlobalInt( ICON_NONE, "ICON_NONE" );
	assignGlobalInt( ICON_FOLDER_FILE_OPEN, "ICON_FOLDER_FILE_OPEN" );
	assignGlobalInt( ICON_FILE_SAVE_CLASSIC, "ICON_FILE_SAVE_CLASSIC" );
	assignGlobalInt( ICON_FOLDER_OPEN, "ICON_FOLDER_OPEN" );
	assignGlobalInt( ICON_FOLDER_SAVE, "ICON_FOLDER_SAVE" );
	assignGlobalInt( ICON_FILE_OPEN, "ICON_FILE_OPEN" );
	assignGlobalInt( ICON_FILE_SAVE, "ICON_FILE_SAVE" );
	assignGlobalInt( ICON_FILE_EXPORT, "ICON_FILE_EXPORT" );
	assignGlobalInt( ICON_FILE_ADD, "ICON_FILE_ADD" );
	assignGlobalInt( ICON_FILE_DELETE, "ICON_FILE_DELETE" );
	assignGlobalInt( ICON_FILETYPE_TEXT, "ICON_FILETYPE_TEXT" );
	assignGlobalInt( ICON_FILETYPE_AUDIO, "ICON_FILETYPE_AUDIO" );
	assignGlobalInt( ICON_FILETYPE_IMAGE, "ICON_FILETYPE_IMAGE" );
	assignGlobalInt( ICON_FILETYPE_PLAY, "ICON_FILETYPE_PLAY" );
	assignGlobalInt( ICON_FILETYPE_VIDEO, "ICON_FILETYPE_VIDEO" );
	assignGlobalInt( ICON_FILETYPE_INFO, "ICON_FILETYPE_INFO" );
	assignGlobalInt( ICON_FILE_COPY, "ICON_FILE_COPY" );
	assignGlobalInt( ICON_FILE_CUT, "ICON_FILE_CUT" );
	assignGlobalInt( ICON_FILE_PASTE, "ICON_FILE_PASTE" );
	assignGlobalInt( ICON_CURSOR_HAND, "ICON_CURSOR_HAND" );
	assignGlobalInt( ICON_CURSOR_POINTER, "ICON_CURSOR_POINTER" );
	assignGlobalInt( ICON_CURSOR_CLASSIC, "ICON_CURSOR_CLASSIC" );
	assignGlobalInt( ICON_PENCIL, "ICON_PENCIL" );
	assignGlobalInt( ICON_PENCIL_BIG, "ICON_PENCIL_BIG" );
	assignGlobalInt( ICON_BRUSH_CLASSIC, "ICON_BRUSH_CLASSIC" );
	assignGlobalInt( ICON_BRUSH_PAINTER, "ICON_BRUSH_PAINTER" );
	assignGlobalInt( ICON_WATER_DROP, "ICON_WATER_DROP" );
	assignGlobalInt( ICON_COLOR_PICKER, "ICON_COLOR_PICKER" );
	assignGlobalInt( ICON_RUBBER, "ICON_RUBBER" );
	assignGlobalInt( ICON_COLOR_BUCKET, "ICON_COLOR_BUCKET" );
	assignGlobalInt( ICON_TEXT_T, "ICON_TEXT_T" );
	assignGlobalInt( ICON_TEXT_A, "ICON_TEXT_A" );
	assignGlobalInt( ICON_SCALE, "ICON_SCALE" );
	assignGlobalInt( ICON_RESIZE, "ICON_RESIZE" );
	assignGlobalInt( ICON_FILTER_POINT, "ICON_FILTER_POINT" );
	assignGlobalInt( ICON_FILTER_BILINEAR, "ICON_FILTER_BILINEAR" );
	assignGlobalInt( ICON_CROP, "ICON_CROP" );
	assignGlobalInt( ICON_CROP_ALPHA, "ICON_CROP_ALPHA" );
	assignGlobalInt( ICON_SQUARE_TOGGLE, "ICON_SQUARE_TOGGLE" );
	assignGlobalInt( ICON_SYMMETRY, "ICON_SYMMETRY" );
	assignGlobalInt( ICON_SYMMETRY_HORIZONTAL, "ICON_SYMMETRY_HORIZONTAL" );
	assignGlobalInt( ICON_SYMMETRY_VERTICAL, "ICON_SYMMETRY_VERTICAL" );
	assignGlobalInt( ICON_LENS, "ICON_LENS" );
	assignGlobalInt( ICON_LENS_BIG, "ICON_LENS_BIG" );
	assignGlobalInt( ICON_EYE_ON, "ICON_EYE_ON" );
	assignGlobalInt( ICON_EYE_OFF, "ICON_EYE_OFF" );
	assignGlobalInt( ICON_FILTER_TOP, "ICON_FILTER_TOP" );
	assignGlobalInt( ICON_FILTER, "ICON_FILTER" );
	assignGlobalInt( ICON_TARGET_POINT, "ICON_TARGET_POINT" );
	assignGlobalInt( ICON_TARGET_SMALL, "ICON_TARGET_SMALL" );
	assignGlobalInt( ICON_TARGET_BIG, "ICON_TARGET_BIG" );
	assignGlobalInt( ICON_TARGET_MOVE, "ICON_TARGET_MOVE" );
	assignGlobalInt( ICON_CURSOR_MOVE, "ICON_CURSOR_MOVE" );
	assignGlobalInt( ICON_CURSOR_SCALE, "ICON_CURSOR_SCALE" );
	assignGlobalInt( ICON_CURSOR_SCALE_RIGHT, "ICON_CURSOR_SCALE_RIGHT" );
	assignGlobalInt( ICON_CURSOR_SCALE_LEFT, "ICON_CURSOR_SCALE_LEFT" );
	assignGlobalInt( ICON_UNDO, "ICON_UNDO" );
	assignGlobalInt( ICON_REDO, "ICON_REDO" );
	assignGlobalInt( ICON_REREDO, "ICON_REREDO" );
	assignGlobalInt( ICON_MUTATE, "ICON_MUTATE" );
	assignGlobalInt( ICON_ROTATE, "ICON_ROTATE" );
	assignGlobalInt( ICON_REPEAT, "ICON_REPEAT" );
	assignGlobalInt( ICON_SHUFFLE, "ICON_SHUFFLE" );
	assignGlobalInt( ICON_EMPTYBOX, "ICON_EMPTYBOX" );
	assignGlobalInt( ICON_TARGET, "ICON_TARGET" );
	assignGlobalInt( ICON_TARGET_SMALL_FILL, "ICON_TARGET_SMALL_FILL" );
	assignGlobalInt( ICON_TARGET_BIG_FILL, "ICON_TARGET_BIG_FILL" );
	assignGlobalInt( ICON_TARGET_MOVE_FILL, "ICON_TARGET_MOVE_FILL" );
	assignGlobalInt( ICON_CURSOR_MOVE_FILL, "ICON_CURSOR_MOVE_FILL" );
	assignGlobalInt( ICON_CURSOR_SCALE_FILL, "ICON_CURSOR_SCALE_FILL" );
	assignGlobalInt( ICON_CURSOR_SCALE_RIGHT_FILL, "ICON_CURSOR_SCALE_RIGHT_FILL" );
	assignGlobalInt( ICON_CURSOR_SCALE_LEFT_FILL, "ICON_CURSOR_SCALE_LEFT_FILL" );
	assignGlobalInt( ICON_UNDO_FILL, "ICON_UNDO_FILL" );
	assignGlobalInt( ICON_REDO_FILL, "ICON_REDO_FILL" );
	assignGlobalInt( ICON_REREDO_FILL, "ICON_REREDO_FILL" );
	assignGlobalInt( ICON_MUTATE_FILL, "ICON_MUTATE_FILL" );
	assignGlobalInt( ICON_ROTATE_FILL, "ICON_ROTATE_FILL" );
	assignGlobalInt( ICON_REPEAT_FILL, "ICON_REPEAT_FILL" );
	assignGlobalInt( ICON_SHUFFLE_FILL, "ICON_SHUFFLE_FILL" );
	assignGlobalInt( ICON_EMPTYBOX_SMALL, "ICON_EMPTYBOX_SMALL" );
	assignGlobalInt( ICON_BOX, "ICON_BOX" );
	assignGlobalInt( ICON_BOX_TOP, "ICON_BOX_TOP" );
	assignGlobalInt( ICON_BOX_TOP_RIGHT, "ICON_BOX_TOP_RIGHT" );
	assignGlobalInt( ICON_BOX_RIGHT, "ICON_BOX_RIGHT" );
	assignGlobalInt( ICON_BOX_BOTTOM_RIGHT, "ICON_BOX_BOTTOM_RIGHT" );
	assignGlobalInt( ICON_BOX_BOTTOM, "ICON_BOX_BOTTOM" );
	assignGlobalInt( ICON_BOX_BOTTOM_LEFT, "ICON_BOX_BOTTOM_LEFT" );
	assignGlobalInt( ICON_BOX_LEFT, "ICON_BOX_LEFT" );
	assignGlobalInt( ICON_BOX_TOP_LEFT, "ICON_BOX_TOP_LEFT" );
	assignGlobalInt( ICON_BOX_CENTER, "ICON_BOX_CENTER" );
	assignGlobalInt( ICON_BOX_CIRCLE_MASK, "ICON_BOX_CIRCLE_MASK" );
	assignGlobalInt( ICON_POT, "ICON_POT" );
	assignGlobalInt( ICON_ALPHA_MULTIPLY, "ICON_ALPHA_MULTIPLY" );
	assignGlobalInt( ICON_ALPHA_CLEAR, "ICON_ALPHA_CLEAR" );
	assignGlobalInt( ICON_DITHERING, "ICON_DITHERING" );
	assignGlobalInt( ICON_MIPMAPS, "ICON_MIPMAPS" );
	assignGlobalInt( ICON_BOX_GRID, "ICON_BOX_GRID" );
	assignGlobalInt( ICON_GRID, "ICON_GRID" );
	assignGlobalInt( ICON_BOX_CORNERS_SMALL, "ICON_BOX_CORNERS_SMALL" );
	assignGlobalInt( ICON_BOX_CORNERS_BIG, "ICON_BOX_CORNERS_BIG" );
	assignGlobalInt( ICON_FOUR_BOXES, "ICON_FOUR_BOXES" );
	assignGlobalInt( ICON_GRID_FILL, "ICON_GRID_FILL" );
	assignGlobalInt( ICON_BOX_MULTISIZE, "ICON_BOX_MULTISIZE" );
	assignGlobalInt( ICON_ZOOM_SMALL, "ICON_ZOOM_SMALL" );
	assignGlobalInt( ICON_ZOOM_MEDIUM, "ICON_ZOOM_MEDIUM" );
	assignGlobalInt( ICON_ZOOM_BIG, "ICON_ZOOM_BIG" );
	assignGlobalInt( ICON_ZOOM_ALL, "ICON_ZOOM_ALL" );
	assignGlobalInt( ICON_ZOOM_CENTER, "ICON_ZOOM_CENTER" );
	assignGlobalInt( ICON_BOX_DOTS_SMALL, "ICON_BOX_DOTS_SMALL" );
	assignGlobalInt( ICON_BOX_DOTS_BIG, "ICON_BOX_DOTS_BIG" );
	assignGlobalInt( ICON_BOX_CONCENTRIC, "ICON_BOX_CONCENTRIC" );
	assignGlobalInt( ICON_BOX_GRID_BIG, "ICON_BOX_GRID_BIG" );
	assignGlobalInt( ICON_OK_TICK, "ICON_OK_TICK" );
	assignGlobalInt( ICON_CROSS, "ICON_CROSS" );
	assignGlobalInt( ICON_ARROW_LEFT, "ICON_ARROW_LEFT" );
	assignGlobalInt( ICON_ARROW_RIGHT, "ICON_ARROW_RIGHT" );
	assignGlobalInt( ICON_ARROW_DOWN, "ICON_ARROW_DOWN" );
	assignGlobalInt( ICON_ARROW_UP, "ICON_ARROW_UP" );
	assignGlobalInt( ICON_ARROW_LEFT_FILL, "ICON_ARROW_LEFT_FILL" );
	assignGlobalInt( ICON_ARROW_RIGHT_FILL, "ICON_ARROW_RIGHT_FILL" );
	assignGlobalInt( ICON_ARROW_DOWN_FILL, "ICON_ARROW_DOWN_FILL" );
	assignGlobalInt( ICON_ARROW_UP_FILL, "ICON_ARROW_UP_FILL" );
	assignGlobalInt( ICON_AUDIO, "ICON_AUDIO" );
	assignGlobalInt( ICON_FX, "ICON_FX" );
	assignGlobalInt( ICON_WAVE, "ICON_WAVE" );
	assignGlobalInt( ICON_WAVE_SINUS, "ICON_WAVE_SINUS" );
	assignGlobalInt( ICON_WAVE_SQUARE, "ICON_WAVE_SQUARE" );
	assignGlobalInt( ICON_WAVE_TRIANGULAR, "ICON_WAVE_TRIANGULAR" );
	assignGlobalInt( ICON_CROSS_SMALL, "ICON_CROSS_SMALL" );
	assignGlobalInt( ICON_PLAYER_PREVIOUS, "ICON_PLAYER_PREVIOUS" );
	assignGlobalInt( ICON_PLAYER_PLAY_BACK, "ICON_PLAYER_PLAY_BACK" );
	assignGlobalInt( ICON_PLAYER_PLAY, "ICON_PLAYER_PLAY" );
	assignGlobalInt( ICON_PLAYER_PAUSE, "ICON_PLAYER_PAUSE" );
	assignGlobalInt( ICON_PLAYER_STOP, "ICON_PLAYER_STOP" );
	assignGlobalInt( ICON_PLAYER_NEXT, "ICON_PLAYER_NEXT" );
	assignGlobalInt( ICON_PLAYER_RECORD, "ICON_PLAYER_RECORD" );
	assignGlobalInt( ICON_MAGNET, "ICON_MAGNET" );
	assignGlobalInt( ICON_LOCK_CLOSE, "ICON_LOCK_CLOSE" );
	assignGlobalInt( ICON_LOCK_OPEN, "ICON_LOCK_OPEN" );
	assignGlobalInt( ICON_CLOCK, "ICON_CLOCK" );
	assignGlobalInt( ICON_TOOLS, "ICON_TOOLS" );
	assignGlobalInt( ICON_GEAR, "ICON_GEAR" );
	assignGlobalInt( ICON_GEAR_BIG, "ICON_GEAR_BIG" );
	assignGlobalInt( ICON_BIN, "ICON_BIN" );
	assignGlobalInt( ICON_HAND_POINTER, "ICON_HAND_POINTER" );
	assignGlobalInt( ICON_LASER, "ICON_LASER" );
	assignGlobalInt( ICON_COIN, "ICON_COIN" );
	assignGlobalInt( ICON_EXPLOSION, "ICON_EXPLOSION" );
	assignGlobalInt( ICON_1UP, "ICON_1UP" );
	assignGlobalInt( ICON_PLAYER, "ICON_PLAYER" );
	assignGlobalInt( ICON_PLAYER_JUMP, "ICON_PLAYER_JUMP" );
	assignGlobalInt( ICON_KEY, "ICON_KEY" );
	assignGlobalInt( ICON_DEMON, "ICON_DEMON" );
	assignGlobalInt( ICON_TEXT_POPUP, "ICON_TEXT_POPUP" );
	assignGlobalInt( ICON_GEAR_EX, "ICON_GEAR_EX" );
	assignGlobalInt( ICON_CRACK, "ICON_CRACK" );
	assignGlobalInt( ICON_CRACK_POINTS, "ICON_CRACK_POINTS" );
	assignGlobalInt( ICON_STAR, "ICON_STAR" );
	assignGlobalInt( ICON_DOOR, "ICON_DOOR" );
	assignGlobalInt( ICON_EXIT, "ICON_EXIT" );
	assignGlobalInt( ICON_MODE_2D, "ICON_MODE_2D" );
	assignGlobalInt( ICON_MODE_3D, "ICON_MODE_3D" );
	assignGlobalInt( ICON_CUBE, "ICON_CUBE" );
	assignGlobalInt( ICON_CUBE_FACE_TOP, "ICON_CUBE_FACE_TOP" );
	assignGlobalInt( ICON_CUBE_FACE_LEFT, "ICON_CUBE_FACE_LEFT" );
	assignGlobalInt( ICON_CUBE_FACE_FRONT, "ICON_CUBE_FACE_FRONT" );
	assignGlobalInt( ICON_CUBE_FACE_BOTTOM, "ICON_CUBE_FACE_BOTTOM" );
	assignGlobalInt( ICON_CUBE_FACE_RIGHT, "ICON_CUBE_FACE_RIGHT" );
	assignGlobalInt( ICON_CUBE_FACE_BACK, "ICON_CUBE_FACE_BACK" );
	assignGlobalInt( ICON_CAMERA, "ICON_CAMERA" );
	assignGlobalInt( ICON_SPECIAL, "ICON_SPECIAL" );
	assignGlobalInt( ICON_LINK_NET, "ICON_LINK_NET" );
	assignGlobalInt( ICON_LINK_BOXES, "ICON_LINK_BOXES" );
	assignGlobalInt( ICON_LINK_MULTI, "ICON_LINK_MULTI" );
	assignGlobalInt( ICON_LINK, "ICON_LINK" );
	assignGlobalInt( ICON_LINK_BROKE, "ICON_LINK_BROKE" );
	assignGlobalInt( ICON_TEXT_NOTES, "ICON_TEXT_NOTES" );
	assignGlobalInt( ICON_NOTEBOOK, "ICON_NOTEBOOK" );
	assignGlobalInt( ICON_SUITCASE, "ICON_SUITCASE" );
	assignGlobalInt( ICON_SUITCASE_ZIP, "ICON_SUITCASE_ZIP" );
	assignGlobalInt( ICON_MAILBOX, "ICON_MAILBOX" );
	assignGlobalInt( ICON_MONITOR, "ICON_MONITOR" );
	assignGlobalInt( ICON_PRINTER, "ICON_PRINTER" );
	assignGlobalInt( ICON_PHOTO_CAMERA, "ICON_PHOTO_CAMERA" );
	assignGlobalInt( ICON_PHOTO_CAMERA_FLASH, "ICON_PHOTO_CAMERA_FLASH" );
	assignGlobalInt( ICON_HOUSE, "ICON_HOUSE" );
	assignGlobalInt( ICON_HEART, "ICON_HEART" );
	assignGlobalInt( ICON_CORNER, "ICON_CORNER" );
	assignGlobalInt( ICON_VERTICAL_BARS, "ICON_VERTICAL_BARS" );
	assignGlobalInt( ICON_VERTICAL_BARS_FILL, "ICON_VERTICAL_BARS_FILL" );
	assignGlobalInt( ICON_LIFE_BARS, "ICON_LIFE_BARS" );
	assignGlobalInt( ICON_INFO, "ICON_INFO" );
	assignGlobalInt( ICON_CROSSLINE, "ICON_CROSSLINE" );
	assignGlobalInt( ICON_HELP, "ICON_HELP" );
	assignGlobalInt( ICON_FILETYPE_ALPHA, "ICON_FILETYPE_ALPHA" );
	assignGlobalInt( ICON_FILETYPE_HOME, "ICON_FILETYPE_HOME" );
	assignGlobalInt( ICON_LAYERS_VISIBLE, "ICON_LAYERS_VISIBLE" );
	assignGlobalInt( ICON_LAYERS, "ICON_LAYERS" );
	assignGlobalInt( ICON_WINDOW, "ICON_WINDOW" );
	assignGlobalInt( ICON_HIDPI, "ICON_HIDPI" );
	assignGlobalInt( ICON_FILETYPE_BINARY, "ICON_FILETYPE_BINARY" );
	assignGlobalInt( ICON_HEX, "ICON_HEX" );
	assignGlobalInt( ICON_SHIELD, "ICON_SHIELD" );
	assignGlobalInt( ICON_FILE_NEW, "ICON_FILE_NEW" );
	assignGlobalInt( ICON_FOLDER_ADD, "ICON_FOLDER_ADD" );
	assignGlobalInt( ICON_ALARM, "ICON_ALARM" );
	assignGlobalInt( ICON_CPU, "ICON_CPU" );
	assignGlobalInt( ICON_ROM, "ICON_ROM" );
	assignGlobalInt( ICON_STEP_OVER, "ICON_STEP_OVER" );
	assignGlobalInt( ICON_STEP_INTO, "ICON_STEP_INTO" );
	assignGlobalInt( ICON_STEP_OUT, "ICON_STEP_OUT" );
	assignGlobalInt( ICON_RESTART, "ICON_RESTART" );
	assignGlobalInt( ICON_BREAKPOINT_ON, "ICON_BREAKPOINT_ON" );
	assignGlobalInt( ICON_BREAKPOINT_OFF, "ICON_BREAKPOINT_OFF" );
	assignGlobalInt( ICON_BURGER_MENU, "ICON_BURGER_MENU" );
	assignGlobalInt( ICON_CASE_SENSITIVE, "ICON_CASE_SENSITIVE" );
	assignGlobalInt( ICON_REG_EXP, "ICON_REG_EXP" );
	assignGlobalInt( ICON_FOLDER, "ICON_FOLDER" );
	assignGlobalInt( ICON_FILE, "ICON_FILE" );
	assignGlobalInt( ICON_SAND_TIMER, "ICON_SAND_TIMER" );
	/* Light type */
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
	/* RLGL GL blending factors */
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
	assignGlobalInt( RL_READ_FRAMEBUFFER, "RL_READ_FRAMEBUFFER" ); // GL_READ_FRAMEBUFFER
	assignGlobalInt( RL_DRAW_FRAMEBUFFER, "RL_DRAW_FRAMEBUFFER" ); // GL_DRAW_FRAMEBUFFER
	/* RLGL Default shader vertex attribute locations */
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_POSITION, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_POSITION" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_NORMAL, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_NORMAL" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_COLOR, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_COLOR" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_TANGENT, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_TANGENT" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD2, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD2" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_INDICES, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_INDICES" );
#ifdef RL_SUPPORT_MESH_GPU_SKINNING
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_BONEIDS, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_BONEIDS" );
	assignGlobalInt( RL_DEFAULT_SHADER_ATTRIB_LOCATION_BONEWEIGHTS, "RL_DEFAULT_SHADER_ATTRIB_LOCATION_BONEWEIGHTS" );
	assignGlobalInt( RL_SUPPORT_MESH_GPU_SKINNING, "SUPPORT_GPU_SKINNING" );
#endif
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
	/* OpenGL Bitfield mask */
	assignGlobalInt( GL_COLOR_BUFFER_BIT, "GL_COLOR_BUFFER_BIT" );
	assignGlobalInt( GL_DEPTH_BUFFER_BIT, "GL_DEPTH_BUFFER_BIT" );
	assignGlobalInt( GL_STENCIL_BUFFER_BIT, "GL_STENCIL_BUFFER_BIT" );
	/* OpenGL Texture parameter */
	assignGlobalInt( GL_NEAREST, "GL_NEAREST" );
	assignGlobalInt( GL_LINEAR, "GL_LINEAR" );
	/* OpenGL Capability */
	assignGlobalInt( GL_BLEND, "GL_BLEND" ); // If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc
	assignGlobalInt( GL_CULL_FACE, "GL_CULL_FACE" ); // If enabled, cull polygons based on their winding in window coordinates. See glCullFace
	assignGlobalInt( GL_DEPTH_TEST, "GL_DEPTH_TEST" ); // If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled. See glDepthFunc and glDepthRangef
	assignGlobalInt( GL_DITHER, "GL_DITHER" ); // If enabled, dither color components or indices before they are written to the color buffer
	assignGlobalInt( GL_POLYGON_OFFSET_FILL, "GL_POLYGON_OFFSET_FILL" ); // If enabled, an offset is added to depth values of a polygon's fragments produced by rasterization. See glPolygonOffset
	assignGlobalInt( GL_POLYGON_OFFSET_LINE, "GL_POLYGON_OFFSET_LINE" );
	assignGlobalInt( GL_POLYGON_OFFSET_POINT, "GL_POLYGON_OFFSET_POINT" );
	assignGlobalInt( GL_SAMPLE_ALPHA_TO_COVERAGE, "GL_SAMPLE_ALPHA_TO_COVERAGE" ); // If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value
	assignGlobalInt( GL_SAMPLE_COVERAGE, "GL_SAMPLE_COVERAGE" ); // If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage
	assignGlobalInt( GL_SCISSOR_TEST, "GL_SCISSOR_TEST" ); // If enabled, discard fragments that are outside the scissor rectangle. See glScissor
	assignGlobalInt( GL_STENCIL_TEST, "GL_STENCIL_TEST" ); // If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp
	/* OpenGL Test function */
	assignGlobalInt( GL_NEVER, "GL_NEVER" ); // Always fails
	assignGlobalInt( GL_LESS, "GL_LESS" ); // Passes if ( ref & mask ) < ( stencil & mask )
	assignGlobalInt( GL_LEQUAL, "GL_LEQUAL" ); // Passes if ( ref & mask ) <= ( stencil & mask )
	assignGlobalInt( GL_GREATER, "GL_GREATER" ); // Passes if ( ref & mask ) > ( stencil & mask )
	assignGlobalInt( GL_GEQUAL, "GL_GEQUAL" ); // Passes if ( ref & mask ) >= ( stencil & mask )
	assignGlobalInt( GL_EQUAL, "GL_EQUAL" ); // Passes if ( ref & mask ) = ( stencil & mask )
	assignGlobalInt( GL_NOTEQUAL, "GL_NOTEQUAL" ); // Passes if ( ref & mask ) != ( stencil & mask )
	assignGlobalInt( GL_ALWAYS, "GL_ALWAYS" ); // Always passes
	/* OpenGL Face */
	assignGlobalInt( GL_FRONT, "GL_FRONT" );
	assignGlobalInt( GL_BACK, "GL_BACK" );
	assignGlobalInt( GL_FRONT_AND_BACK, "GL_FRONT_AND_BACK" );
	/* OpenGL Stencil test */
	assignGlobalInt( GL_KEEP, "GL_KEEP" ); // Keeps the current value
	assignGlobalInt( GL_ZERO, "GL_ZERO" ); // Sets the stencil buffer value to 0
	assignGlobalInt( GL_REPLACE, "GL_REPLACE" ); // Sets the stencil buffer value to ref, as specified by glStencilFunc
	assignGlobalInt( GL_INCR, "GL_INCR" ); // Increments the current stencil buffer value. Clamps to the maximum representable unsigned value
	assignGlobalInt( GL_INCR_WRAP, "GL_INCR_WRAP" ); // Increments the current stencil buffer value. Wraps stencil buffer value to zero when incrementing the maximum representable unsigned value
	assignGlobalInt( GL_DECR, "GL_DECR" ); // Decrements the current stencil buffer value. Clamps to 0
	assignGlobalInt( GL_DECR_WRAP, "GL_DECR_WRAP" ); // Decrements the current stencil buffer value. Wraps stencil buffer value to the maximum representable unsigned value when decrementing a stencil buffer value of zero
	assignGlobalInt( GL_INVERT, "GL_INVERT" ); // Bitwise inverts the current stencil buffer value
	/* OpenGL Connection */
	assignGlobalInt( GL_VENDOR, "GL_VENDOR" ); // Returns the company responsible for this GL implementation. This name does not change from release to release
	assignGlobalInt( GL_RENDERER, "GL_RENDERER" ); // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release
	assignGlobalInt( GL_VERSION, "GL_VERSION" ); // Returns a version or release number of the form OpenGLES
	assignGlobalInt( GL_SHADING_LANGUAGE_VERSION, "GL_SHADING_LANGUAGE_VERSION" ); // Returns a version or release number for the shading language of the form OpenGLESGLSLES
	assignGlobalInt( GL_EXTENSIONS, "GL_EXTENSIONS" ); // Returns a space-separated list of supported extensions to GL
	/* CBuffer Data type */
	assignGlobalInt( BUFFER_UNSIGNED_CHAR, "BUFFER_UNSIGNED_CHAR" ); // C type unsigned char
	assignGlobalInt( BUFFER_UNSIGNED_SHORT, "BUFFER_UNSIGNED_SHORT" ); // C type unsigned short
	assignGlobalInt( BUFFER_UNSIGNED_INT, "BUFFER_UNSIGNED_INT" ); // C type unsigned int
	assignGlobalInt( BUFFER_UNSIGNED_LONG, "BUFFER_UNSIGNED_LONG" ); // C type unsigned long
	assignGlobalInt( BUFFER_CHAR, "BUFFER_CHAR" ); // C type char
	assignGlobalInt( BUFFER_SHORT, "BUFFER_SHORT" ); // C type short
	assignGlobalInt( BUFFER_INT, "BUFFER_INT" ); // C type int
	assignGlobalInt( BUFFER_LONG, "BUFFER_LONG" ); // C type long
	assignGlobalInt( BUFFER_FLOAT, "BUFFER_FLOAT" ); // C type float
	assignGlobalInt( BUFFER_DOUBLE, "BUFFER_DOUBLE" ); // C type double
/*DOC_DEFINES_END*/
	lua_pop( L, -1 );
}

// Custom logging funtion.
static void logCustom( int logLevel, const char* text, va_list args ) {
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
	lua_State* L = state->luaState;

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

bool luaInit( int argn, const char** argc ) {
	state->luaState = luaL_newstate();
	lua_State* L = state->luaState;

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
	defineGlyphInfo();
	defineWave();
	defineSound();
	defineSoundAlias();
	defineMusic();
	defineAudioStream();
	defineLight();
	defineMaterial();
	defineMesh();
	defineModel();
	defineModelAnimation();
	defineModelSkeleton();
	defineRLRenderBatch();
	defineAutomationEvent();
	defineAutomationEventList();
	/* Define globals. */
	defineGlobals();
	platformDefineGlobals();

	/* Register functions. */
	luaRegister();
	luaPlatformRegister();

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

	/* Alloc counter test. */
	// lua_getglobal( L, "RL" );
	// lua_newtable( L );
	// lua_pushnumber( L, 0 );
	// lua_setfield( L, -2, "alloc" );
	// lua_getglobal( L, "RL" );
	// lua_getfield( L, -1, "alloc" );
	// lua_pushnumber( L, 0 );
	// lua_pop( L, -1 );

	return true;
}

int luaTraceback( lua_State* L ) {
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

void luaCallMain() {
	lua_State* L = state->luaState;

	char path[ STRING_LEN ] = { '\0' };

/* If web, set path to resources folder. */
#ifdef PLATFORM_WEB
	snprintf( path, STRING_LEN, "main.lua" );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		snprintf( path, STRING_LEN, "main" );
	}
#else
	snprintf( path, STRING_LEN, "%smain.lua", state->basePath );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		snprintf( path, STRING_LEN, "%smain", state->basePath );
	}
#endif
	if ( !FileExists( path ) ) {
		TraceLog( LOG_ERROR, "Cannot find file: %s\n", path );
		state->run = false;
		return;
	}
	luaL_dofile( L, path );

	/* Check errors in main.lua */
	if ( lua_tostring( L, -1 ) ) {
		TraceLog( LOG_ERROR, "Lua error: %s\n", lua_tostring( L, -1 ) );
		state->run = false;
		return;
	}
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );
	/* Apply custom callback here. */
	SetTraceLogCallback( logCustom );

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "config" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
			return;
		}
	}
	lua_pop( L, -1 );
	/* If InitWindow is not called in RL.config, call it here. */
	if ( !IsWindowReady() ) {
		InitWindow( 800, 600, "ReiLua" );
	}
	if ( IsWindowReady() ) {
		stateContextInit();
	}
	else {
		state->run = false;
	}
}

void luaCallInit() {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "init" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
	}
	lua_pop( L, -1 );
}


void luaCallUpdate() {
// #if defined PLATFORM_DESKTOP_SDL2 && defined LUA_EVENTS
#if ( defined PLATFORM_DESKTOP_SDL2 || defined PLATFORM_DESKTOP_SDL3 ) && defined LUA_EVENTS
	platformSendEvents();
#endif
	lua_State* L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "update" );

	if ( lua_isfunction( L, -1 ) ) {
		lua_pushnumber( L, GetFrameTime() );

		if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
	}
	lua_pop( L, -1 );
}

void luaCallDraw() {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "draw" );

	if ( lua_isfunction( L, -1 ) ) {
		BeginDrawing();

		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
		EndDrawing();
	}
	lua_pop( L, -1 );
}

void luaCallExit() {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "exit" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
	}
	lua_pop( L, -1 );
}

void luaCallLoad( const char* type, void* object ) {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);

	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "load" );

	if ( lua_isfunction( L, -1 ) ) {
		lua_Debug ar;
		lua_getstack( L, 1, &ar );
		lua_getinfo( L, "Sl", &ar );

		lua_createtable( L, 5, 0 );
		lua_pushstring( L, type );
		lua_setfield( L, -2, "type" );
		lua_pushlightuserdata( L, object );
		lua_setfield( L, -2, "object" );
		lua_pushstring( L, ar.source );
		lua_setfield( L, -2, "source" );
		lua_pushstring( L, ar.short_src );
		lua_setfield( L, -2, "short_src" );
		lua_pushinteger( L, ar.currentline );
		lua_setfield( L, -2, "currentline" );

		if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
		lua_pop( L, 2 );
	}
	else {
		lua_pop( L, 3 );
	}
}

void luaCallUnload( const char* type, void* object ) {
	lua_State* L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
	lua_getglobal( L, "RL" );
	lua_getfield( L, -1, "unload" );

	if ( lua_isfunction( L, -1 ) ) {
		lua_createtable( L, 2, 0 );
		lua_pushstring( L, type );
		lua_setfield( L, -2, "type" );
		lua_pushlightuserdata( L, object );
		lua_setfield( L, -2, "object" );

		if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
		}
		lua_pop( L, 2 );
	}
	else {
		lua_pop( L, 3 );
	}
}

void luaRegister() {
	lua_State* L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Core. */
		/* Window-related functions. */
	assignGlobalFunction( "InitWindow", lcoreInitWindow );
	assignGlobalFunction( "CloseWindow", lcoreCloseWindow );
	assignGlobalFunction( "WindowShouldClose", lcoreWindowShouldClose );
	assignGlobalFunction( "IsWindowReady", lcoreIsWindowReady );
	assignGlobalFunction( "IsWindowFullscreen", lcoreIsWindowFullscreen );
	assignGlobalFunction( "IsWindowHidden", lcoreIsWindowHidden );
	assignGlobalFunction( "IsWindowMinimized", lcoreIsWindowMinimized );
	assignGlobalFunction( "IsWindowMaximized", lcoreIsWindowMaximized );
	assignGlobalFunction( "IsWindowFocused", lcoreIsWindowFocused );
	assignGlobalFunction( "IsWindowResized", lcoreIsWindowResized );
	assignGlobalFunction( "IsWindowState", lcoreIsWindowState );
	assignGlobalFunction( "SetWindowState", lcoreSetWindowState );
	assignGlobalFunction( "ClearWindowState", lcoreClearWindowState );
	assignGlobalFunction( "ToggleFullscreen", lcoreToggleFullscreen );
	assignGlobalFunction( "ToggleBorderlessWindowed", lcoreToggleBorderlessWindowed );
	assignGlobalFunction( "MaximizeWindow", lcoreMaximizeWindow );
	assignGlobalFunction( "MinimizeWindow", lcoreMinimizeWindow );
	assignGlobalFunction( "RestoreWindow", lcoreRestoreWindow );
	assignGlobalFunction( "SetWindowIcon", lcoreSetWindowIcon );
	assignGlobalFunction( "SetWindowIcons", lcoreSetWindowIcons );
	assignGlobalFunction( "SetWindowTitle", lcoreSetWindowTitle );
	assignGlobalFunction( "SetWindowPosition", lcoreSetWindowPosition );
	assignGlobalFunction( "SetWindowMonitor", lcoreSetWindowMonitor );
	assignGlobalFunction( "SetWindowMinSize", lcoreSetWindowMinSize );
	assignGlobalFunction( "SetWindowMaxSize", lcoreSetWindowMaxSize );
	assignGlobalFunction( "SetWindowSize", lcoreSetWindowSize );
	assignGlobalFunction( "SetWindowOpacity", lcoreSetWindowOpacity );
	assignGlobalFunction( "SetWindowFocused", lcoreSetWindowFocused );
	assignGlobalFunction( "GetWindowHandle", lcoreGetWindowHandle );
	assignGlobalFunction( "GetScreenSize", lcoreGetScreenSize );
	assignGlobalFunction( "GetRenderSize", lcoreGetRenderSize );
	assignGlobalFunction( "GetMonitorCount", lcoreGetMonitorCount );
	assignGlobalFunction( "GetCurrentMonitor", lcoreGetCurrentMonitor );
	assignGlobalFunction( "GetMonitorPosition", lcoreGetMonitorPosition );
	assignGlobalFunction( "GetMonitorSize", lcoreGetMonitorSize );
	assignGlobalFunction( "GetMonitorPhysicalSize", lcoreGetMonitorPhysicalSize );
	assignGlobalFunction( "GetMonitorRefreshRate", lcoreGetMonitorRefreshRate );
	assignGlobalFunction( "GetWindowPosition", lcoreGetWindowPosition );
	assignGlobalFunction( "GetWindowScaleDPI", lcoreGetWindowScaleDPI );
	assignGlobalFunction( "GetMonitorName", lcoreGetMonitorName );
	assignGlobalFunction( "SetClipboardText", lcoreSetClipboardText );
	assignGlobalFunction( "GetClipboardText", lcoreGetClipboardText );
	assignGlobalFunction( "GetClipboardImage", lcoreGetClipboardImage );
	assignGlobalFunction( "EnableEventWaiting", lcoreEnableEventWaiting );
	assignGlobalFunction( "DisableEventWaiting", lcoreDisableEventWaiting );
		/* Cursor-related functions. */
	assignGlobalFunction( "ShowCursor", lcoreShowCursor );
	assignGlobalFunction( "HideCursor", lcoreHideCursor );
	assignGlobalFunction( "IsCursorHidden", lcoreIsCursorHidden );
	assignGlobalFunction( "EnableCursor", lcoreEnableCursor );
	assignGlobalFunction( "DisableCursor", lcoreDisableCursor );
	assignGlobalFunction( "IsCursorOnScreen", lcoreIsCursorOnScreen );
		/* Drawing-related functions. */
	assignGlobalFunction( "ClearBackground", lcoreClearBackground );
	assignGlobalFunction( "BeginDrawing", lcoreBeginDrawing );
	assignGlobalFunction( "EndDrawing", lcoreEndDrawing );
	assignGlobalFunction( "BeginMode2D", lcoreBeginMode2D );
	assignGlobalFunction( "EndMode2D", lcoreEndMode2D );
	assignGlobalFunction( "BeginMode3D", lcoreBeginMode3D );
	assignGlobalFunction( "EndMode3D", lcoreEndMode3D );
	assignGlobalFunction( "BeginTextureMode", lcoreBeginTextureMode );
	assignGlobalFunction( "EndTextureMode", lcoreEndTextureMode );
	assignGlobalFunction( "BeginShaderMode", lcoreBeginShaderMode );
	assignGlobalFunction( "EndShaderMode", lcoreEndShaderMode );
	assignGlobalFunction( "BeginBlendMode", lcoreBeginBlendMode );
	assignGlobalFunction( "EndBlendMode", lcoreEndBlendMode );
	assignGlobalFunction( "BeginScissorMode", lcoreBeginScissorMode );
	assignGlobalFunction( "EndScissorMode", lcoreEndScissorMode );
		/* Shader management functions. */
	assignGlobalFunction( "LoadShader", lcoreLoadShader );
	assignGlobalFunction( "LoadShaderFromMemory", lcoreLoadShaderFromMemory );
	assignGlobalFunction( "IsShaderValid", lcoreIsShaderValid );
	assignGlobalFunction( "GetShaderId", lcoreGetShaderId );
	assignGlobalFunction( "GetShaderLocation", lcoreGetShaderLocation );
	assignGlobalFunction( "GetShaderLocationAttrib", lcoreGetShaderLocationAttrib );
	assignGlobalFunction( "SetShaderLocationIndex", lcoreSetShaderLocationIndex );
	assignGlobalFunction( "GetShaderLocationIndex", lcoreGetShaderLocationIndex );
	assignGlobalFunction( "SetShaderValueMatrix", lcoreSetShaderValueMatrix );
	assignGlobalFunction( "SetShaderValueTexture", lcoreSetShaderValueTexture );
	assignGlobalFunction( "SetShaderValue", lcoreSetShaderValue );
	assignGlobalFunction( "SetShaderValueV", lcoreSetShaderValueV );
	assignGlobalFunction( "SetShaderValueWithBuffer", lcoreSetShaderValueWithBuffer );
	assignGlobalFunction( "SetShaderValueVWithBuffer", lcoreSetShaderValueVWithBuffer );
	assignGlobalFunction( "UnloadShader", lcoreUnloadShader );
		/* Screen-space-related functions. */
	assignGlobalFunction( "GetScreenToWorldRay", lcoreGetScreenToWorldRay );
	assignGlobalFunction( "GetScreenToWorldRayEx", lcoreGetScreenToWorldRayEx );
	assignGlobalFunction( "GetWorldToScreen", lcoreGetWorldToScreen );
	assignGlobalFunction( "GetWorldToScreenEx", lcoreGetWorldToScreenEx );
	assignGlobalFunction( "GetWorldToScreen2D", lcoreGetWorldToScreen2D );
	assignGlobalFunction( "GetScreenToWorld2D", lcoreGetScreenToWorld2D );
	assignGlobalFunction( "GetCameraMatrix", lcoreGetCameraMatrix );
	assignGlobalFunction( "GetCameraMatrix2D", lcoreGetCameraMatrix2D );
		/* Timing-related functions. */
	assignGlobalFunction( "SetTargetFPS", lcoreSetTargetFPS );
	assignGlobalFunction( "GetFrameTime", lcoreGetFrameTime );
	assignGlobalFunction( "GetTime", lcoreGetTime );
	assignGlobalFunction( "GetFPS", lcoreGetFPS );
		/* Custom frame control functions. */
	assignGlobalFunction( "SwapScreenBuffer", lcoreSwapScreenBuffer );
	assignGlobalFunction( "PollInputEvents", lcorePollInputEvents );
	assignGlobalFunction( "WaitTime", lcoreWaitTime );
		/* Random values generation functions. */
	assignGlobalFunction( "SetRandomSeed", lcoreSetRandomSeed );
	assignGlobalFunction( "GetRandomValue", lcoreGetRandomValue );
	assignGlobalFunction( "LoadRandomSequence", lcoreLoadRandomSequence );
		/* Misc. functions. */
	assignGlobalFunction( "TakeScreenshot", lcoreTakeScreenshot );
	assignGlobalFunction( "SetConfigFlags", lcoreSetConfigFlags );
	assignGlobalFunction( "TraceLog", lcoreTraceLog );
	assignGlobalFunction( "SetTraceLogLevel", lcoreSetTraceLogLevel );
	assignGlobalFunction( "SetLogLevelInvalid", lcoreSetLogLevelInvalid );
	assignGlobalFunction( "GetLogLevelInvalid", lcoreGetLogLevelInvalid );
	assignGlobalFunction( "OpenURL", lcoreOpenURL );
	assignGlobalFunction( "IsGCUnloadEnabled", lcoreIsGCUnloadEnabled );
	assignGlobalFunction( "SetGCUnload", lcoreSetGCUnload );
	assignGlobalFunction( "GetPlatform", lcoreGetPlatform );
		/* Files management functions. */
	assignGlobalFunction( "LoadFileData", lcoreLoadFileData );
	assignGlobalFunction( "SaveFileData", lcoreSaveFileData );
	assignGlobalFunction( "ExportDataAsCode", lcoreExportDataAsCode );
	assignGlobalFunction( "LoadFileText", lcoreLoadFileText );
	assignGlobalFunction( "SaveFileText", lcoreSaveFileText );
		/* Files system functions. */
	assignGlobalFunction( "GetBasePath", lcoreGetBasePath );
	assignGlobalFunction( "FileRename", lcoreFileRename );
	assignGlobalFunction( "FileRemove", lcoreFileRemove );
	assignGlobalFunction( "FileCopy", lcoreFileCopy );
	assignGlobalFunction( "FileMove", lcoreFileMove );
	assignGlobalFunction( "FileTextReplace", lcoreFileTextReplace );
	assignGlobalFunction( "FileTextFindIndex", lcoreFileTextFindIndex );
	assignGlobalFunction( "FileExists", lcoreFileExists );
	assignGlobalFunction( "DirectoryExists", lcoreDirectoryExists );
	assignGlobalFunction( "IsFileExtension", lcoreIsFileExtension );
	assignGlobalFunction( "GetFileLength", lcoreGetFileLength );
	assignGlobalFunction( "GetFileModTime", lcoreGetFileModTime );
	assignGlobalFunction( "GetFileExtension", lcoreGetFileExtension );
	assignGlobalFunction( "GetFileName", lcoreGetFileName );
	assignGlobalFunction( "GetFileNameWithoutExt", lcoreGetFileNameWithoutExt );
	assignGlobalFunction( "GetDirectoryPath", lcoreGetDirectoryPath );
	assignGlobalFunction( "GetPrevDirectoryPath", lcoreGetPrevDirectoryPath );
	assignGlobalFunction( "GetWorkingDirectory", lcoreGetWorkingDirectory );
	assignGlobalFunction( "GetApplicationDirectory", lcoreGetApplicationDirectory );
	assignGlobalFunction( "MakeDirectory", lcoreMakeDirectory );
	assignGlobalFunction( "ChangeDirectory", lcoreChangeDirectory );
	assignGlobalFunction( "IsPathFile", lcoreIsPathFile );
	assignGlobalFunction( "IsFileNameValid", lcoreIsFileNameValid );
	assignGlobalFunction( "LoadDirectoryFiles", lcoreLoadDirectoryFiles );
	assignGlobalFunction( "LoadDirectoryFilesEx", lcoreLoadDirectoryFilesEx );
	assignGlobalFunction( "IsFileDropped", lcoreIsFileDropped );
	assignGlobalFunction( "LoadDroppedFiles", lcoreLoadDroppedFiles );
	assignGlobalFunction( "GetDirectoryFileCount", lcoreGetDirectoryFileCount );
	assignGlobalFunction( "GetDirectoryFileCountEx", lcoreGetDirectoryFileCountEx );
		/* Compression/Encoding functionality. */
	assignGlobalFunction( "CompressData", lcoreCompressData );
	assignGlobalFunction( "DecompressData", lcoreDecompressData );
	assignGlobalFunction( "EncodeDataBase64", lcoreEncodeDataBase64 );
	assignGlobalFunction( "DecodeDataBase64", lcoreDecodeDataBase64 );
	assignGlobalFunction( "ComputeCRC32", lcoreComputeCRC32 );
	assignGlobalFunction( "ComputeMD5", lcoreComputeMD5 );
	assignGlobalFunction( "ComputeSHA1", lcoreComputeSHA1 );
	assignGlobalFunction( "ComputeSHA256", lcoreComputeSHA256 );
		/* Automation events functionality. */
	assignGlobalFunction( "LoadAutomationEventList", lcoreLoadAutomationEventList );
	assignGlobalFunction( "UnloadAutomationEventList", lcoreUnloadAutomationEventList );
	assignGlobalFunction( "ExportAutomationEventList", lcoreExportAutomationEventList );
	assignGlobalFunction( "SetAutomationEventList", lcoreSetAutomationEventList );
	assignGlobalFunction( "SetAutomationEventBaseFrame", lcoreSetAutomationEventBaseFrame );
	assignGlobalFunction( "StartAutomationEventRecording", lcoreStartAutomationEventRecording );
	assignGlobalFunction( "StopAutomationEventRecording", lcoreStopAutomationEventRecording );
	assignGlobalFunction( "PlayAutomationEvent", lcorePlayAutomationEvent );
	assignGlobalFunction( "GetAutomationEventListCapacity", lcoreGetAutomationEventListCapacity );
	assignGlobalFunction( "GetAutomationEventListCount", lcoreGetAutomationEventListCount );
	assignGlobalFunction( "GetAutomationEvent", lcoreGetAutomationEvent );
	assignGlobalFunction( "GetAutomationEventFrame", lcoreGetAutomationEventFrame );
	assignGlobalFunction( "GetAutomationEventType", lcoreGetAutomationEventType );
	assignGlobalFunction( "GetAutomationEventParams", lcoreGetAutomationEventParams );
		/* Input-related functions: keyboard. */
	assignGlobalFunction( "IsKeyPressed", lcoreIsKeyPressed );
	assignGlobalFunction( "IsKeyPressedRepeat", lcoreIsKeyPressedRepeat );
	assignGlobalFunction( "IsKeyDown", lcoreIsKeyDown );
	assignGlobalFunction( "IsKeyReleased", lcoreIsKeyReleased );
	assignGlobalFunction( "IsKeyUp", lcoreIsKeyUp );
	assignGlobalFunction( "GetKeyPressed", lcoreGetKeyPressed );
	assignGlobalFunction( "GetCharPressed", lcoreGetCharPressed );
	assignGlobalFunction( "SetExitKey", lcoreSetExitKey );
		/* Input-related functions: gamepads. */
	assignGlobalFunction( "IsGamepadAvailable", lcoreIsGamepadAvailable );
	assignGlobalFunction( "GetGamepadName", lcoreGetGamepadName );
	assignGlobalFunction( "IsGamepadButtonPressed", lcoreIsGamepadButtonPressed );
	assignGlobalFunction( "IsGamepadButtonDown", lcoreIsGamepadButtonDown );
	assignGlobalFunction( "IsGamepadButtonReleased", lcoreIsGamepadButtonReleased );
	assignGlobalFunction( "IsGamepadButtonUp", lcoreIsGamepadButtonUp );
	assignGlobalFunction( "GetGamepadButtonPressed", lcoreGetGamepadButtonPressed );
	assignGlobalFunction( "GetGamepadAxisCount", lcoreGetGamepadAxisCount );
	assignGlobalFunction( "GetGamepadAxisMovement", lcoreGetGamepadAxisMovement );
	assignGlobalFunction( "SetGamepadMappings", lcoreSetGamepadMappings );
	assignGlobalFunction( "SetGamepadVibration", lcoreSetGamepadVibration );
		/* Input-related functions: mouse. */
	assignGlobalFunction( "IsMouseButtonPressed", lcoreIsMouseButtonPressed );
	assignGlobalFunction( "IsMouseButtonDown", lcoreIsMouseButtonDown );
	assignGlobalFunction( "IsMouseButtonReleased", lcoreIsMouseButtonReleased );
	assignGlobalFunction( "IsMouseButtonUp", lcoreIsMouseButtonUp );
	assignGlobalFunction( "GetMousePosition", lcoreGetMousePosition );
	assignGlobalFunction( "GetMouseDelta", lcoreGetMouseDelta );
	assignGlobalFunction( "SetMousePosition", lcoreSetMousePosition );
	assignGlobalFunction( "SetMouseOffset", lcoreSetMouseOffset );
	assignGlobalFunction( "SetMouseScale", lcoreSetMouseScale );
	assignGlobalFunction( "GetMouseOffset", lcoreGetMouseOffset );
	assignGlobalFunction( "GetMouseScale", lcoreGetMouseScale );
	assignGlobalFunction( "GetMouseWheelMove", lcoreGetMouseWheelMove );
	assignGlobalFunction( "GetMouseWheelMoveV", lcoreGetMouseWheelMoveV );
	assignGlobalFunction( "SetMouseCursor", lcoreSetMouseCursor );
		/* Input-related functions: touch */
	assignGlobalFunction( "GetTouchPosition", lcoreGetTouchPosition );
	assignGlobalFunction( "GetTouchPointId", lcoreGetTouchPointId );
	assignGlobalFunction( "GetTouchPointCount", lcoreGetTouchPointCount );
		/* Input-related functions: gestures. */
	assignGlobalFunction( "SetGesturesEnabled", lcoreSetGesturesEnabled );
	assignGlobalFunction( "IsGestureDetected", lcoreIsGestureDetected );
	assignGlobalFunction( "GetGestureDetected", lcoreGetGestureDetected );
	assignGlobalFunction( "GetGestureHoldDuration", lcoreGetGestureHoldDuration );
	assignGlobalFunction( "GetGestureDragVector", lcoreGetGestureDragVector );
	assignGlobalFunction( "GetGestureDragAngle", lcoreGetGestureDragAngle );
	assignGlobalFunction( "GetGesturePinchVector", lcoreGetGesturePinchVector );
	assignGlobalFunction( "GetGesturePinchAngle", lcoreGetGesturePinchAngle );
		/* Camera2D System functions. */
	assignGlobalFunction( "CreateCamera2D", lcoreCreateCamera2D );
	assignGlobalFunction( "SetCamera2DTarget", lcoreSetCamera2DTarget );
	assignGlobalFunction( "SetCamera2DOffset", lcoreSetCamera2DOffset );
	assignGlobalFunction( "SetCamera2DRotation", lcoreSetCamera2DRotation );
	assignGlobalFunction( "SetCamera2DZoom", lcoreSetCamera2DZoom );
	assignGlobalFunction( "GetCamera2DTarget", lcoreGetCamera2DTarget );
	assignGlobalFunction( "GetCamera2DOffset", lcoreGetCamera2DOffset );
	assignGlobalFunction( "GetCamera2DRotation", lcoreGetCamera2DRotation );
	assignGlobalFunction( "GetCamera2DZoom", lcoreGetCamera2DZoom );
		/* Camera3D System functions. */
	assignGlobalFunction( "CreateCamera3D", lcoreCreateCamera3D );
	assignGlobalFunction( "SetCamera3DPosition", lcoreSetCamera3DPosition );
	assignGlobalFunction( "SetCamera3DTarget", lcoreSetCamera3DTarget );
	assignGlobalFunction( "SetCamera3DUp", lcoreSetCamera3DUp );
	assignGlobalFunction( "SetCamera3DFovy", lcoreSetCamera3DFovy );
	assignGlobalFunction( "SetCamera3DProjection", lcoreSetCamera3DProjection );
	assignGlobalFunction( "GetCamera3DPosition", lcoreGetCamera3DPosition );
	assignGlobalFunction( "GetCamera3DTarget", lcoreGetCamera3DTarget );
	assignGlobalFunction( "GetCamera3DUp", lcoreGetCamera3DUp );
	assignGlobalFunction( "GetCamera3DFovy", lcoreGetCamera3DFovy );
	assignGlobalFunction( "GetCamera3DProjection", lcoreGetCamera3DProjection );
	assignGlobalFunction( "GetCamera3DForward", lcoreGetCamera3DForward );
	assignGlobalFunction( "GetCamera3DUpNormalized", lcoreGetCamera3DUpNormalized );
	assignGlobalFunction( "GetCamera3DRight", lcoreGetCamera3DRight );
	assignGlobalFunction( "Camera3DMoveForward", lcoreCamera3DMoveForward );
	assignGlobalFunction( "Camera3DMoveUp", lcoreCamera3DMoveUp );
	assignGlobalFunction( "Camera3DMoveRight", lcoreCamera3DMoveRight );
	assignGlobalFunction( "Camera3DMoveToTarget", lcoreCamera3DMoveToTarget );
	assignGlobalFunction( "Camera3DYaw", lcoreCamera3DYaw );
	assignGlobalFunction( "Camera3DPitch", lcoreCamera3DPitch );
	assignGlobalFunction( "Camera3DRoll", lcoreCamera3DRoll );
	assignGlobalFunction( "GetCamera3DViewMatrix", lcoreGetCamera3DViewMatrix );
	assignGlobalFunction( "GetCamera3DProjectionMatrix", lcoreGetCamera3DProjectionMatrix );
	assignGlobalFunction( "UpdateCamera3D", lcoreUpdateCamera3D );
	assignGlobalFunction( "UpdateCamera3DPro", lcoreUpdateCamera3DPro );
		/* Buffer management functions. */
	assignGlobalFunction( "LoadBuffer", lcoreLoadBuffer );
	assignGlobalFunction( "LoadBufferFormatted", lcoreLoadBufferFormatted );
	assignGlobalFunction( "LoadBufferFromFile", lcoreLoadBufferFromFile );
	assignGlobalFunction( "LoadBufferFromString", lcoreLoadBufferFromString );
	assignGlobalFunction( "UnloadBuffer", lcoreUnloadBuffer );
	assignGlobalFunction( "CopyBufferData", lcoreCopyBufferData );
	assignGlobalFunction( "SetBufferData", lcoreSetBufferData );
	assignGlobalFunction( "SwapBufferEndianness", lcoreSwapBufferEndianness );
	assignGlobalFunction( "GetBufferData", lcoreGetBufferData );
	assignGlobalFunction( "GetBufferAsString", lcoreGetBufferAsString );
	assignGlobalFunction( "GetBufferType", lcoreGetBufferType );
	assignGlobalFunction( "GetBufferSize", lcoreGetBufferSize );
	assignGlobalFunction( "GetBufferElementSize", lcoreGetBufferElementSize );
	assignGlobalFunction( "GetBufferLength", lcoreGetBufferLength );
	assignGlobalFunction( "ExportBuffer", lcoreExportBuffer );

	/* Shapes. */
		/* Basic shapes drawing functions. */
	assignGlobalFunction( "SetShapesTexture", lshapesSetShapesTexture );
	assignGlobalFunction( "GetShapesTexture", lshapesGetShapesTexture );
	assignGlobalFunction( "GetShapesTextureRectangle", lshapesGetShapesTextureRectangle );
	assignGlobalFunction( "DrawPixel", lshapesDrawPixel );
	assignGlobalFunction( "DrawLine", lshapesDrawLine );
	assignGlobalFunction( "DrawLineStrip", lshapesDrawLineStrip );
	assignGlobalFunction( "DrawLineBezier", lshapesDrawLineBezier );
	assignGlobalFunction( "DrawLineDashed", lshapesDrawLineDashed );
	assignGlobalFunction( "DrawCircle", lshapesDrawCircle );
	assignGlobalFunction( "DrawCircleSector", lshapesDrawCircleSector );
	assignGlobalFunction( "DrawCircleSectorLines", lshapesDrawCircleSectorLines );
	assignGlobalFunction( "DrawCircleGradient", lshapesDrawCircleGradient );
	assignGlobalFunction( "DrawCircleLines", lshapesDrawCircleLines );
	assignGlobalFunction( "DrawEllipse", lshapesDrawEllipse );
	assignGlobalFunction( "DrawEllipseLines", lshapesDrawEllipseLines );
	assignGlobalFunction( "DrawRing", lshapesDrawRing );
	assignGlobalFunction( "DrawRingLines", lshapesDrawRingLines );
	assignGlobalFunction( "DrawRectangle", lshapesDrawRectangle );
	assignGlobalFunction( "DrawRectanglePro", lshapesDrawRectanglePro );
	assignGlobalFunction( "DrawRectangleGradientV", lshapesDrawRectangleGradientV );
	assignGlobalFunction( "DrawRectangleGradientH", lshapesDrawRectangleGradientH );
	assignGlobalFunction( "DrawRectangleGradientEx", lshapesDrawRectangleGradientEx );
	assignGlobalFunction( "DrawRectangleLines", lshapesDrawRectangleLines );
	assignGlobalFunction( "DrawRectangleLinesEx", lshapesDrawRectangleLinesEx );
	assignGlobalFunction( "DrawRectangleRounded", lshapesDrawRectangleRounded );
	assignGlobalFunction( "DrawRectangleRoundedLines", lshapesDrawRectangleRoundedLines );
	assignGlobalFunction( "DrawRectangleRoundedLinesEx", lshapesDrawRectangleRoundedLinesEx );
	assignGlobalFunction( "DrawTriangle", lshapesDrawTriangle );
	assignGlobalFunction( "DrawTriangleLines", lshapesDrawTriangleLines );
	assignGlobalFunction( "DrawTriangleFan", lshapesDrawTriangleFan );
	assignGlobalFunction( "DrawTriangleStrip", lshapesDrawTriangleStrip );
	assignGlobalFunction( "DrawPoly", lshapesDrawPoly );
	assignGlobalFunction( "DrawPolyLines", lshapesDrawPolyLines );
	assignGlobalFunction( "DrawPolyLinesEx", lshapesDrawPolyLinesEx );
		/* Splines drawing functions. */
	assignGlobalFunction( "DrawSplineLinear", lshapesDrawSplineLinear );
	assignGlobalFunction( "DrawSplineBasis", lshapesDrawSplineBasis );
	assignGlobalFunction( "DrawSplineCatmullRom", lshapesDrawSplineCatmullRom );
	assignGlobalFunction( "DrawSplineBezierQuadratic", lshapesDrawSplineBezierQuadratic );
	assignGlobalFunction( "DrawSplineBezierCubic", lshapesDrawSplineBezierCubic );
	assignGlobalFunction( "DrawSplineSegmentLinear", lshapesDrawSplineSegmentLinear );
	assignGlobalFunction( "DrawSplineSegmentBasis", lshapesDrawSplineSegmentBasis );
	assignGlobalFunction( "DrawSplineSegmentCatmullRom", lshapesDrawSplineSegmentCatmullRom );
	assignGlobalFunction( "DrawSplineSegmentBezierQuadratic", lshapesDrawSplineSegmentBezierQuadratic );
	assignGlobalFunction( "DrawSplineSegmentBezierCubic", lshapesDrawSplineSegmentBezierCubic );
		/* Basic Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]. */
	assignGlobalFunction( "GetSplinePointLinear", lshapesGetSplinePointLinear );
	assignGlobalFunction( "GetSplinePointBasis", lshapesGetSplinePointBasis );
	assignGlobalFunction( "GetSplinePointCatmullRom", lshapesGetSplinePointCatmullRom );
	assignGlobalFunction( "GetSplinePointBezierQuad", lshapesGetSplinePointBezierQuad );
	assignGlobalFunction( "GetSplinePointBezierCubic", lshapesGetSplinePointBezierCubic );
		/* Basic shapes collision detection functions. */
	assignGlobalFunction( "CheckCollisionRecs", lshapesCheckCollisionRecs );
	assignGlobalFunction( "CheckCollisionCircles", lshapesCheckCollisionCircles );
	assignGlobalFunction( "CheckCollisionCircleRec", lshapesCheckCollisionCircleRec );
	assignGlobalFunction( "CheckCollisionCircleLine", lshapesCheckCollisionCircleLine );
	assignGlobalFunction( "CheckCollisionPointRec", lshapesCheckCollisionPointRec );
	assignGlobalFunction( "CheckCollisionPointCircle", lshapesCheckCollisionPointCircle );
	assignGlobalFunction( "CheckCollisionPointTriangle", lshapesCheckCollisionPointTriangle );
	assignGlobalFunction( "CheckCollisionPointPoly", lshapesCheckCollisionPointPoly );
	assignGlobalFunction( "CheckCollisionLines", lshapesCheckCollisionLines );
	assignGlobalFunction( "CheckCollisionPointLine", lshapesCheckCollisionPointLine );
	assignGlobalFunction( "GetCollisionRec", lshapesGetCollisionRec );
	assignGlobalFunction( "RectPack", lshapesRectPack );

	/* Textures. */
		/* Image loading functions. */
	assignGlobalFunction( "LoadImage", ltexturesLoadImage );
	assignGlobalFunction( "LoadImageRaw", ltexturesLoadImageRaw );
	assignGlobalFunction( "LoadImageAnim", ltexturesLoadImageAnim );
	assignGlobalFunction( "LoadImageAnimFromMemory", ltexturesLoadImageAnimFromMemory );
	assignGlobalFunction( "LoadImageFromMemory", ltexturesLoadImageFromMemory );
	assignGlobalFunction( "LoadImageFromData", ltexturesLoadImageFromData );
	assignGlobalFunction( "LoadImageFromTexture", ltexturesLoadImageFromTexture );
	assignGlobalFunction( "LoadImageFromScreen", ltexturesLoadImageFromScreen );
	assignGlobalFunction( "IsImageValid", ltextureIsImageValid );
	assignGlobalFunction( "UnloadImage", ltextureUnloadImage );
	assignGlobalFunction( "ExportImage", ltexturesExportImage );
	assignGlobalFunction( "ExportImageToMemory", ltexturesExportImageToMemory );
	assignGlobalFunction( "ExportImageAsCode", ltexturesExportImageAsCode );
		/* Image generation functions. */
	assignGlobalFunction( "GenImageColor", ltexturesGenImageColor );
	assignGlobalFunction( "GenImageGradientLinear", ltexturesGenImageGradientLinear );
	assignGlobalFunction( "GenImageGradientRadial", ltexturesGenImageGradientRadial );
	assignGlobalFunction( "GenImageGradientSquare", ltexturesGenImageGradientSquare );
	assignGlobalFunction( "GenImageChecked", ltexturesGenImageChecked );
	assignGlobalFunction( "GenImageWhiteNoise", ltexturesGenImageWhiteNoise );
	assignGlobalFunction( "GenImagePerlinNoise", ltexturesGenImagePerlinNoise );
	assignGlobalFunction( "GenImageCellular", ltexturesGenImageCellular );
	assignGlobalFunction( "GenImageText", ltexturesGenImageText );
		/* Image manipulation functions. */
	assignGlobalFunction( "ImageCopy", ltexturesImageCopy );
	assignGlobalFunction( "ImageFromImage", ltexturesImageFromImage );
	assignGlobalFunction( "ImageFromChannel", ltexturesImageFromChannel );
	assignGlobalFunction( "ImageText", ltexturesImageText );
	assignGlobalFunction( "ImageTextEx", ltexturesImageTextEx );
	assignGlobalFunction( "ImageFormat", ltexturesImageFormat );
	assignGlobalFunction( "ImageToPOT", ltexturesImageToPOT );
	assignGlobalFunction( "ImageCrop", ltexturesImageCrop );
	assignGlobalFunction( "ImageAlphaCrop", ltexturesImageAlphaCrop );
	assignGlobalFunction( "ImageAlphaClear", ltexturesImageAlphaClear );
	assignGlobalFunction( "ImageAlphaMask", ltexturesImageAlphaMask );
	assignGlobalFunction( "ImageAlphaPremultiply", ltexturesImageAlphaPremultiply );
	assignGlobalFunction( "ImageBlurGaussian", ltexturesImageBlurGaussian );
	assignGlobalFunction( "ImageKernelConvolution", ltexturesImageKernelConvolution );
	assignGlobalFunction( "ImageResize", ltexturesImageResize );
	assignGlobalFunction( "ImageResizeNN", ltexturesImageResizeNN );
	assignGlobalFunction( "ImageResizeCanvas", ltexturesImageResizeCanvas );
	assignGlobalFunction( "ImageMipmaps", ltexturesImageMipmaps );
	assignGlobalFunction( "ImageDither", ltexturesImageDither );
	assignGlobalFunction( "ImageFlipVertical", ltexturesImageFlipVertical );
	assignGlobalFunction( "ImageFlipHorizontal", ltexturesImageFlipHorizontal );
	assignGlobalFunction( "ImageRotate", ltexturesImageRotate );
	assignGlobalFunction( "ImageRotateCW", ltexturesImageRotateCW );
	assignGlobalFunction( "ImageRotateCCW", ltexturesImageRotateCCW );
	assignGlobalFunction( "ImageColorTint", ltexturesImageColorTint );
	assignGlobalFunction( "ImageColorInvert", ltexturesImageColorInvert );
	assignGlobalFunction( "ImageColorGrayscale", ltexturesImageColorGrayscale );
	assignGlobalFunction( "ImageColorContrast", ltexturesImageColorContrast );
	assignGlobalFunction( "ImageColorBrightness", ltexturesImageColorBrightness );
	assignGlobalFunction( "ImageColorReplace", ltexturesImageColorReplace );
	assignGlobalFunction( "LoadImageColors", ltexturesLoadImageColors );
	assignGlobalFunction( "LoadImagePalette", ltexturesLoadImagePalette );
	assignGlobalFunction( "GetImageAlphaBorder", ltexturesGetImageAlphaBorder );
	assignGlobalFunction( "GetImageColor", ltexturesGetImageColor );
		/* Image configuration functions. */
	assignGlobalFunction( "SetImageData", ltexturesSetImageData );
	assignGlobalFunction( "GetImageData", ltexturesGetImageData );
	assignGlobalFunction( "GetImageSize", ltexturesGetImageSize );
	assignGlobalFunction( "GetImageMipmaps", ltexturesGetImageMipmaps );
	assignGlobalFunction( "GetImageFormat", ltexturesGetImageFormat );
		/* Image drawing functions. */
	assignGlobalFunction( "ImageClearBackground", ltexturesImageClearBackground );
	assignGlobalFunction( "ImageDrawPixel", ltexturesImageDrawPixel );
	assignGlobalFunction( "ImageDrawLine", ltexturesImageDrawLine );
	assignGlobalFunction( "ImageDrawLineEx", ltexturesImageDrawLineEx );
	assignGlobalFunction( "ImageDrawCircle", ltexturesImageDrawCircle );
	assignGlobalFunction( "ImageDrawCircleLines", ltexturesImageDrawCircleLines );
	assignGlobalFunction( "ImageDrawRectangle", ltexturesImageDrawRectangle );
	assignGlobalFunction( "ImageDrawRectangleLines", ltexturesImageDrawRectangleLines );
	assignGlobalFunction( "ImageDrawTriangle", ltexturesImageDrawTriangle );
	assignGlobalFunction( "ImageDrawTriangleEx", ltexturesImageDrawTriangleEx );
	assignGlobalFunction( "ImageDrawTriangleLines", ltexturesImageDrawTriangleLines );
	assignGlobalFunction( "ImageDrawTriangleFan", ltexturesImageDrawTriangleFan );
	assignGlobalFunction( "ImageDrawTriangleStrip", ltexturesImageDrawTriangleStrip );
	assignGlobalFunction( "ImageDraw", ltexturesImageDraw );
	assignGlobalFunction( "ImageDrawText", ltexturesImageDrawText );
	assignGlobalFunction( "ImageDrawTextEx", ltexturesImageDrawTextEx );
		/* Texture loading functions. */
	assignGlobalFunction( "GetTextureDefault", ltexturesGetTextureDefault );
	assignGlobalFunction( "LoadTexture", ltexturesLoadTexture );
	assignGlobalFunction( "LoadTextureFromImage", ltexturesLoadTextureFromImage );
	assignGlobalFunction( "LoadTextureCubemap", ltexturesLoadTextureCubemap );
	assignGlobalFunction( "LoadTextureFromData", ltexturesLoadTextureFromData );
	assignGlobalFunction( "LoadRenderTexture", ltexturesLoadRenderTexture );
	assignGlobalFunction( "LoadRenderTextureFromData", ltexturesLoadRenderTextureFromData );
	assignGlobalFunction( "IsTextureValid", ltexturesIsTextureValid );
	assignGlobalFunction( "UnloadTexture", ltextureUnloadTexture );
	assignGlobalFunction( "IsRenderTextureValid", ltexturesIsRenderTextureValid );
	assignGlobalFunction( "UnloadRenderTexture", ltextureUnloadRenderTexture );
	assignGlobalFunction( "UpdateTexture", ltexturesUpdateTexture );
	assignGlobalFunction( "UpdateTextureRec", ltexturesUpdateTextureRec );
		/* Texture configuration functions. */
	assignGlobalFunction( "GenTextureMipmaps", ltexturesGenTextureMipmaps );
	assignGlobalFunction( "SetTextureFilter", ltexturesSetTextureFilter );
	assignGlobalFunction( "SetTextureWrap", ltexturesSetTextureWrap );
	assignGlobalFunction( "GetTextureId", ltexturesGetTextureId );
	assignGlobalFunction( "GetTextureSize", ltexturesGetTextureSize );
	assignGlobalFunction( "GetTextureMipmaps", ltexturesGetTextureMipmaps );
	assignGlobalFunction( "GetTextureFormat", ltexturesGetTextureFormat );
		/* Texture drawing functions. */
	assignGlobalFunction( "DrawTexture", ltexturesDrawTexture );
	assignGlobalFunction( "DrawTextureEx", ltexturesDrawTextureEx );
	assignGlobalFunction( "DrawTextureRec", ltexturesDrawTextureRec );
	assignGlobalFunction( "DrawTexturePro", ltexturesDrawTexturePro );
	assignGlobalFunction( "DrawTextureNPatch", ltexturesDrawTextureNPatch );
	assignGlobalFunction( "DrawTextureNPatchRepeat", ltexturesDrawTextureNPatchRepeat );
		/* RenderTexture configuration functions. */
	assignGlobalFunction( "SetRenderTextureTexture", ltexturesSetRenderTextureTexture );
	assignGlobalFunction( "SetRenderTextureDepthTexture", ltexturesSetRenderTextureDepthTexture );
	assignGlobalFunction( "GetRenderTextureId", ltexturesGetRenderTextureId );
	assignGlobalFunction( "GetRenderTextureTexture", ltexturesGetRenderTextureTexture );
	assignGlobalFunction( "GetRenderTextureDepthTexture", ltexturesGetRenderTextureDepthTexture );
		/* Color/pixel related functions */
	assignGlobalFunction( "ColorIsEqual", ltexturesColorIsEqual );
	assignGlobalFunction( "Fade", ltexturesFade );
	assignGlobalFunction( "ColorToInt", ltexturesColorToInt );
	assignGlobalFunction( "ColorNormalize", ltexturesColorNormalize );
	assignGlobalFunction( "ColorFromNormalized", ltexturesColorFromNormalized );
	assignGlobalFunction( "ColorToHSV", ltexturesColorToHSV );
	assignGlobalFunction( "ColorFromHSV", ltexturesColorFromHSV );
	assignGlobalFunction( "ColorTint", ltexturesColorTint );
	assignGlobalFunction( "ColorBrightness", ltexturesColorBrightness );
	assignGlobalFunction( "ColorContrast", ltexturesColorContrast );
	assignGlobalFunction( "ColorAlpha", ltexturesColorAlpha );
	assignGlobalFunction( "ColorAlphaBlend", ltexturesColorAlphaBlend );
	assignGlobalFunction( "ColorLerp", ltexturesColorLerp );
	assignGlobalFunction( "GetColor", ltexturesGetColor );
	assignGlobalFunction( "GetPixelDataSize", ltexturesGetPixelDataSize );

	/* Models. */
		/* Basic geometric 3D shapes drawing functions. */
	assignGlobalFunction( "DrawLine3D", lmodelsDrawLine3D );
	assignGlobalFunction( "DrawPoint3D", lmodelsDrawPoint3D );
	assignGlobalFunction( "DrawCircle3D", lmodelsDrawCircle3D );
	assignGlobalFunction( "DrawTriangle3D", lmodelsDrawTriangle3D );
	assignGlobalFunction( "DrawTriangleStrip3D", lmodelsDrawTriangleStrip3D );
	assignGlobalFunction( "DrawCube", lmodelsDrawCube );
	assignGlobalFunction( "DrawCubeWires", lmodelsDrawCubeWires );
	assignGlobalFunction( "DrawSphere", lmodelsDrawSphere );
	assignGlobalFunction( "DrawSphereEx", lmodelsDrawSphereEx );
	assignGlobalFunction( "DrawSphereWires", lmodelsDrawSphereWires );
	assignGlobalFunction( "DrawCylinder", lmodelsDrawCylinder );
	assignGlobalFunction( "DrawCylinderEx", lmodelsDrawCylinderEx );
	assignGlobalFunction( "DrawCylinderWires", lmodelsDrawCylinderWires );
	assignGlobalFunction( "DrawCylinderWiresEx", lmodelsDrawCylinderWiresEx );
	assignGlobalFunction( "DrawCapsule", lmodelsDrawCapsule );
	assignGlobalFunction( "DrawCapsuleWires", lmodelsDrawCapsuleWires );
	assignGlobalFunction( "DrawPlane", lmodelsDrawPlane );
	assignGlobalFunction( "DrawQuad3DTexture", lmodelDrawQuad3DTexture );
	assignGlobalFunction( "DrawRay", lmodelsDrawRay );
	assignGlobalFunction( "DrawGrid", lmodelsDrawGrid );
	assignGlobalFunction( "DrawGridEx", lmodelsDrawGridEx );
		/* Model management functions. */
	assignGlobalFunction( "LoadModel", lmodelsLoadModel );
	assignGlobalFunction( "LoadModelFromMesh", lmodelsLoadModelFromMesh );
	assignGlobalFunction( "LoadModelFromMeshes", lmodelsLoadModelFromMeshes );
	assignGlobalFunction( "IsModelValid", lmodelsIsModelValid );
	assignGlobalFunction( "UnloadModel", lmodelsUnloadModel );
	assignGlobalFunction( "GetModelBoundingBox", lmodelsGetModelBoundingBox );
	assignGlobalFunction( "SetModelTransform", lmodelsSetModelTransform );
	assignGlobalFunction( "SetModelMesh", lmodelsSetModelMesh );
	assignGlobalFunction( "SetModelMaterial", lmodelsSetModelMaterial );
	assignGlobalFunction( "SetModelMeshMaterial", lmodelsSetModelMeshMaterial );
	assignGlobalFunction( "SetModelSkeleton", lmodelsSetModelSkeleton );
	assignGlobalFunction( "SetModelCurrentPose", lmodelsSetModelCurrentPose );
	assignGlobalFunction( "SetModelBoneMatrix", lmodelsSetModelBoneMatrix );
	assignGlobalFunction( "GetModelTransform", lmodelsGetModelTransform );
	assignGlobalFunction( "GetModelMeshCount", lmodelsGetModelMeshCount );
	assignGlobalFunction( "GetModelMaterialCount", lmodelsGetModelMaterialCount );
	assignGlobalFunction( "GetModelMesh", lmodelsGetModelMesh );
	assignGlobalFunction( "GetModelMaterial", lmodelsGetModelMaterial );
	assignGlobalFunction( "GetModelSkeleton", lmodelsGetModelSkeleton );
	assignGlobalFunction( "GetModelCurrentPose", lmodelsGetModelCurrentPose );
	assignGlobalFunction( "GetModelBoneMatrix", lmodelsGetModelBoneMatrix );
		/* Model drawing functions. */
	assignGlobalFunction( "DrawModel", lmodelsDrawModel );
	assignGlobalFunction( "DrawModelEx", lmodelsDrawModelEx );
	assignGlobalFunction( "DrawModelWires", lmodelsDrawModelWires );
	assignGlobalFunction( "DrawModelWiresEx", lmodelsDrawModelWiresEx );
	assignGlobalFunction( "DrawBoundingBox", lmodelsDrawBoundingBox );
	assignGlobalFunction( "DrawBillboard", lmodelsDrawBillboard );
	assignGlobalFunction( "DrawBillboardRec", lmodelsDrawBillboardRec );
	assignGlobalFunction( "DrawBillboardPro", lmodelsDrawBillboardPro );
		/* Mesh management functions. */
	assignGlobalFunction( "UpdateMesh", lmodelsUpdateMesh );
	assignGlobalFunction( "UnloadMesh", lmodelsUnloadMesh );
	assignGlobalFunction( "DrawMesh", lmodelsDrawMesh );
	assignGlobalFunction( "DrawMeshInstanced", lmodelsDrawMeshInstanced );
	assignGlobalFunction( "SetMeshColor", lmodelsSetMeshColor );
	assignGlobalFunction( "ExportMesh", lmodelsExportMesh );
	assignGlobalFunction( "ExportMeshAsCode", lmodelsExportMeshAsCode );
	assignGlobalFunction( "GetMeshBoundingBox", lmodelsGetMeshBoundingBox );
	assignGlobalFunction( "GenMeshTangents", lmodelsGenMeshTangents );
	assignGlobalFunction( "GetMeshData", lmodelsGetMeshData );
		/* Mesh generation functions. */
	assignGlobalFunction( "GenMeshPoly", lmodelsGenMeshPoly );
	assignGlobalFunction( "GenMeshPlane", lmodelsGenMeshPlane );
	assignGlobalFunction( "GenMeshCube", lmodelsGenMeshCube );
	assignGlobalFunction( "GenMeshSphere", lmodelsGenMeshSphere );
	assignGlobalFunction( "GenMeshHemiSphere", lmodelsGenMeshHemiSphere );
	assignGlobalFunction( "GenMeshCylinder", lmodelsGenMeshCylinder );
	assignGlobalFunction( "GenMeshCone", lmodelsGenMeshCone );
	assignGlobalFunction( "GenMeshTorus", lmodelsGenMeshTorus );
	assignGlobalFunction( "GenMeshKnot", lmodelsGenMeshKnot );
	assignGlobalFunction( "GenMeshHeightmap", lmodelsGenMeshHeightmap );
	assignGlobalFunction( "GenMeshCubicmap", lmodelsGenMeshCubicmap );
	assignGlobalFunction( "GenMeshCustom", lmodelsGenMeshCustom );
		/* Material management functions. */
	assignGlobalFunction( "LoadMaterials", lmodelsLoadMaterials );
	assignGlobalFunction( "GetMaterialDefault", lmodelsGetMaterialDefault );
	assignGlobalFunction( "LoadMaterialDefault", lmodelsLoadMaterialDefault );
	assignGlobalFunction( "CreateMaterial", lmodelsCreateMaterial );
	assignGlobalFunction( "IsMaterialValid", lmodelsIsMaterialValid );
	assignGlobalFunction( "UnloadMaterial", lmodelsUnloadMaterial );
	assignGlobalFunction( "SetMaterialTexture", lmodelsSetMaterialTexture );
	assignGlobalFunction( "SetMaterialColor", lmodelsSetMaterialColor );
	assignGlobalFunction( "SetMaterialValue", lmodelsSetMaterialValue );
	assignGlobalFunction( "SetMaterialShader", lmodelsSetMaterialShader );
	assignGlobalFunction( "SetMaterialParams", lmodelsSetMaterialParams );
	assignGlobalFunction( "GetMaterialTexture", lmodelsGetMaterialTexture );
	assignGlobalFunction( "GetMaterialColor", lmodelsGetMaterialColor );
	assignGlobalFunction( "GetMaterialValue", lmodelsGetMaterialValue );
	assignGlobalFunction( "GetMaterialShader", lmodelsGetMaterialShader );
	assignGlobalFunction( "GetMaterialParams", lmodelsGetMaterialParams );
		/* Model animations management functions. */
	assignGlobalFunction( "LoadModelAnimations", lmodelsLoadModelAnimations );
	assignGlobalFunction( "UpdateModelAnimation", lmodelsUpdateModelAnimation );
	assignGlobalFunction( "UpdateModelAnimationEx", lmodelsUpdateModelAnimationEx );
	assignGlobalFunction( "UnloadModelAnimation", lmodelsUnloadModelAnimation );
	assignGlobalFunction( "UnloadModelAnimations", lmodelsUnloadModelAnimations );
	assignGlobalFunction( "IsModelAnimationValid", lmodelsIsModelAnimationValid );
	assignGlobalFunction( "SetModelAnimationName", lmodelsSetModelAnimationName );
	assignGlobalFunction( "SetModelAnimationKeyframePose", lmodelsSetModelAnimationKeyframePose );
	assignGlobalFunction( "GetModelAnimationName", lmodelsGetModelAnimationName );
	assignGlobalFunction( "GetModelAnimationBoneCount", lmodelsGetModelAnimationBoneCount );
	assignGlobalFunction( "GetModelAnimationKeyframeCount", lmodelsGetModelAnimationKeyframeCount );
	assignGlobalFunction( "GetModelAnimationKeyframePose", lmodelsGetModelAnimationKeyframePose );
	/* Model skeleton management functions. */
	assignGlobalFunction( "SetModelSkeletonBone", lmodelsSetModelSkeletonBone );
	assignGlobalFunction( "SetModelSkeletonBindPose", lmodelsSetModelSkeletonBindPose );
	assignGlobalFunction( "GetModelSkeletonBoneCount", lmodelsGetModelSkeletonBoneCount );
	assignGlobalFunction( "GetModelSkeletonBone", lmodelsGetModelSkeletonBone );
	assignGlobalFunction( "GetModelSkeletonBindPose", lmodelsGetModelSkeletonBindPose );
	/* Collision detection functions. */
	assignGlobalFunction( "CheckCollisionSpheres", lmodelsCheckCollisionSpheres );
	assignGlobalFunction( "CheckCollisionBoxes", lmodelsCheckCollisionBoxes );
	assignGlobalFunction( "CheckCollisionBoxSphere", lmodelsCheckCollisionBoxSphere );
	assignGlobalFunction( "GetRayCollisionSphere", lmodelsGetRayCollisionSphere );
	assignGlobalFunction( "GetRayCollisionBox", lmodelsGetRayCollisionBox );
	assignGlobalFunction( "GetRayCollisionMesh", lmodelsGetRayCollisionMesh );
	assignGlobalFunction( "GetRayCollisionTriangle", lmodelsGetRayCollisionTriangle );
	assignGlobalFunction( "GetRayCollisionQuad", lmodelsGetRayCollisionQuad );
	assignGlobalFunction( "GetRayBoxCells", lmodelsGetRayBoxCells );

	/* Text. */
		/* Font loading/unloading functions. */
	assignGlobalFunction( "GetFontDefault", ltextGetFontDefault );
	assignGlobalFunction( "LoadFont", ltextLoadFont );
	assignGlobalFunction( "LoadFontEx", ltextLoadFontEx );
	assignGlobalFunction( "LoadFontFromImage", ltextLoadFontFromImage );
	assignGlobalFunction( "LoadFontFromMemory", ltextLoadFontFromMemory );
	assignGlobalFunction( "LoadFontFromData", ltextLoadFontFromData );
	assignGlobalFunction( "FontCopy", ltextFontCopy );
	assignGlobalFunction( "IsFontValid", ltextIsFontValid );
	assignGlobalFunction( "LoadFontData", ltextLoadFontData );
	assignGlobalFunction( "GenImageFontAtlas", ltextGenImageFontAtlas );
	assignGlobalFunction( "UnloadFont", ltextUnloadFont );
	assignGlobalFunction( "ExportFontAsCode", ltextExportFontAsCode );
		/* Text drawing functions. */
	assignGlobalFunction( "DrawFPS", ltextDrawFPS );
	assignGlobalFunction( "DrawText", ltextDrawText );
	assignGlobalFunction( "DrawTextEx", ltextDrawTextEx );
	assignGlobalFunction( "DrawTextPro", ltextDrawTextPro );
	assignGlobalFunction( "DrawTextCodepoint", ltextDrawTextCodepoint );
	assignGlobalFunction( "DrawTextCodepoints", ltextDrawTextCodepoints );
	assignGlobalFunction( "DrawTextBoxed", ltextDrawTextBoxed );
		/* Text font info functions. */
	assignGlobalFunction( "SetTextLineSpacing", ltextSetTextLineSpacing );
	assignGlobalFunction( "GetTextLineSpacing", ltextGetTextLineSpacing );
	assignGlobalFunction( "MeasureText", ltextMeasureText );
	assignGlobalFunction( "MeasureTextEx", ltextMeasureTextEx );
	assignGlobalFunction( "MeasureTextBoxed", ltextMeasureTextBoxed );
	assignGlobalFunction( "GetGlyphIndex", ltextGetGlyphIndex );
	assignGlobalFunction( "GetGlyphInfo", ltextGetGlyphInfo );
	assignGlobalFunction( "GetGlyphInfoByIndex", ltextGetGlyphInfoByIndex );
	assignGlobalFunction( "GetGlyphAtlasRec", ltextGetGlyphAtlasRec );
	assignGlobalFunction( "GetGlyphAtlasRecByIndex", ltextGetGlyphAtlasRecByIndex );
	assignGlobalFunction( "GetFontBaseSize", ltextGetFontBaseSize );
	assignGlobalFunction( "GetFontGlyphCount", ltextGetFontGlyphCount );
	assignGlobalFunction( "GetFontGlyphPadding", ltextGetFontGlyphPadding );
	assignGlobalFunction( "GetFontTexture", ltextGetFontTexture );
	assignGlobalFunction( "SetFontTexture", ltextSetFontTexture );
	assignGlobalFunction( "SetGlyphAtlasRec", ltextSetGlyphAtlasRec );
	assignGlobalFunction( "SetFontGlyph", ltextSetFontGlyph );
		/* GlyphInfo management functions. */
	assignGlobalFunction( "LoadGlyphInfo", ltextLoadGlyphInfo );
	assignGlobalFunction( "UnloadGlyphInfo", ltextUnloadGlyphInfo );
	assignGlobalFunction( "SetGlyphInfoValue", ltextSetGlyphInfoValue );
	assignGlobalFunction( "SetGlyphInfoOffset", ltextSetGlyphInfoOffset );
	assignGlobalFunction( "SetGlyphInfoAdvanceX", ltextSetGlyphInfoAdvanceX );
	assignGlobalFunction( "SetGlyphInfoImage", ltextSetGlyphInfoImage );
	assignGlobalFunction( "GetGlyphInfoValue", ltextGetGlyphInfoValue );
	assignGlobalFunction( "GetGlyphInfoOffset", ltextGetGlyphInfoOffset );
	assignGlobalFunction( "GetGlyphInfoAdvanceX", ltextGetGlyphInfoAdvanceX );
	assignGlobalFunction( "GetGlyphInfoImage", ltextGetGlyphInfoImage );
		/* Text codepoints management functions (unicode characters). */
	assignGlobalFunction( "LoadUTF8", ltextLoadUTF8 );
	assignGlobalFunction( "LoadCodepoints", ltextLoadCodepoints );
	assignGlobalFunction( "GetCodepointCount", ltextGetCodepointCount );
	assignGlobalFunction( "GetCodepoint", ltextGetCodepoint );
	assignGlobalFunction( "GetCodepointNext", ltextGetCodepointNext );
	assignGlobalFunction( "GetCodepointPrevious", ltextGetCodepointPrevious );
	assignGlobalFunction( "CodepointToUTF8", ltextCodepointToUTF8 );
		/* Text strings management functions (no UTF-8 strings, only byte chars) */
	assignGlobalFunction( "TextSubtext", ltextTextSubtext );
	assignGlobalFunction( "TextReplace", ltextTextReplace );
	assignGlobalFunction( "TextInsert", ltextTextInsert );
	assignGlobalFunction( "TextSplit", ltextTextSplit );
	assignGlobalFunction( "TextFindIndex", ltextTextFindIndex );
	assignGlobalFunction( "TextToPascal", ltextTextToPascal );
	assignGlobalFunction( "TextToSnake", ltextTextToSnake );
	assignGlobalFunction( "TextToCamel", ltextTextToCamel );

	/* Audio. */
		/* Audio device management functions. */
	assignGlobalFunction( "InitAudioDevice", laudioInitAudioDevice );
	assignGlobalFunction( "CloseAudioDevice", laudioCloseAudioDevice );
	assignGlobalFunction( "IsAudioDeviceReady", laudioIsAudioDeviceReady );
	assignGlobalFunction( "SetMasterVolume", laudioSetMasterVolume );
	assignGlobalFunction( "GetMasterVolume", laudioGetMasterVolume );
		/* Wave/Sound loading/unloading functions. */
	assignGlobalFunction( "LoadSound", laudioLoadSound );
	assignGlobalFunction( "LoadWave", laudioLoadWave );
	assignGlobalFunction( "LoadWaveFromMemory", laudioLoadWaveFromMemory );
	assignGlobalFunction( "IsWaveValid", laudioIsWaveValid );
	assignGlobalFunction( "LoadSoundFromWave", laudioLoadSoundFromWave );
	assignGlobalFunction( "LoadSoundAlias", laudioLoadSoundAlias );
	assignGlobalFunction( "IsSoundValid", laudioIsSoundValid );
	assignGlobalFunction( "UpdateSound", laudioUpdateSound );
	assignGlobalFunction( "UnloadWave", laudioUnloadWave );
	assignGlobalFunction( "UnloadSound", laudioUnloadSound );
	assignGlobalFunction( "UnloadSoundAlias", laudioUnloadSoundAlias );
	assignGlobalFunction( "ExportWave", laudioExportWave );
	assignGlobalFunction( "ExportWaveAsCode", laudioExportWaveAsCode );
		/* Wave/Sound management functions. */
	assignGlobalFunction( "PlaySound", laudioPlaySound );
	assignGlobalFunction( "StopSound", laudioStopSound );
	assignGlobalFunction( "PauseSound", laudioPauseSound );
	assignGlobalFunction( "ResumeSound", laudioResumeSound );
	assignGlobalFunction( "IsSoundPlaying", laudioIsSoundPlaying );
	assignGlobalFunction( "SetSoundVolume", laudioSetSoundVolume );
	assignGlobalFunction( "SetSoundPitch", laudioSetSoundPitch );
	assignGlobalFunction( "SetSoundPan", laudioSetSoundPan );
	assignGlobalFunction( "WaveFormat", laudioWaveFormat );
	assignGlobalFunction( "LoadWaveSamples", laudioLoadWaveSamples );
	assignGlobalFunction( "WaveCopy", laudioWaveCopy );
	assignGlobalFunction( "WaveCrop", laudioWaveCrop );
		/* Music management functions. */
	assignGlobalFunction( "LoadMusicStream", laudioLoadMusicStream );
	assignGlobalFunction( "LoadMusicStreamFromMemory", laudioLoadMusicStreamFromMemory );
	assignGlobalFunction( "IsMusicValid", laudioIsMusicValid );
	assignGlobalFunction( "UnloadMusicStream", laudioUnloadMusicStream );
	assignGlobalFunction( "PlayMusicStream", laudioPlayMusicStream );
	assignGlobalFunction( "IsMusicStreamPlaying", laudioIsMusicStreamPlaying );
	assignGlobalFunction( "UpdateMusicStream", laudioUpdateMusicStream );
	assignGlobalFunction( "StopMusicStream", laudioStopMusicStream );
	assignGlobalFunction( "PauseMusicStream", laudioPauseMusicStream );
	assignGlobalFunction( "ResumeMusicStream", laudioResumeMusicStream );
	assignGlobalFunction( "SeekMusicStream", laudioSeekMusicStream );
	assignGlobalFunction( "SetMusicVolume", laudioSetMusicVolume );
	assignGlobalFunction( "SetMusicPitch", laudioSetMusicPitch );
	assignGlobalFunction( "SetMusicPan", laudioSetMusicPan );
	assignGlobalFunction( "SetMusicLooping", laudioSetMusicLooping );
	assignGlobalFunction( "GetMusicLooping", laudioGetMusicLooping );
	assignGlobalFunction( "GetMusicTimeLength", laudioGetMusicTimeLength );
	assignGlobalFunction( "GetMusicTimePlayed", laudioGetMusicTimePlayed );
	assignGlobalFunction( "GetMusicStream", laudioGetMusicStream );
	/* AudioStream management functions. */
	assignGlobalFunction( "LoadAudioStream", laudioLoadAudioStream );
	assignGlobalFunction( "IsAudioStreamValid", laudioIsAudioStreamValid );
	assignGlobalFunction( "UnloadAudioStream", laudioUnloadAudioStream );
	assignGlobalFunction( "UpdateAudioStream", laudioUpdateAudioStream );
	assignGlobalFunction( "IsAudioStreamProcessed", laudioIsAudioStreamProcessed );
	assignGlobalFunction( "PlayAudioStream", laudioPlayAudioStream );
	assignGlobalFunction( "PauseAudioStream", laudioPauseAudioStream );
	assignGlobalFunction( "ResumeAudioStream", laudioResumeAudioStream );
	assignGlobalFunction( "IsAudioStreamPlaying", laudioIsAudioStreamPlaying );
	assignGlobalFunction( "StopAudioStream", laudioStopAudioStream );
	assignGlobalFunction( "SetAudioStreamVolume", laudioSetAudioStreamVolume );
	assignGlobalFunction( "SetAudioStreamPitch", laudioSetAudioStreamPitch );
	assignGlobalFunction( "SetAudioStreamPan", laudioSetAudioStreamPan );
	assignGlobalFunction( "SetAudioStreamBufferSizeDefault", laudioSetAudioStreamBufferSizeDefault );
	assignGlobalFunction( "SetAudioStreamCallback", laudioSetAudioStreamCallback );
	assignGlobalFunction( "AttachAudioStreamProcessor", laudioAttachAudioStreamProcessor );
	assignGlobalFunction( "DetachAudioStreamProcessor", laudioDetachAudioStreamProcessor );
	assignGlobalFunction( "AttachAudioMixedProcessor", laudioAttachAudioMixedProcessor );
	assignGlobalFunction( "DetachAudioMixedProcessor", laudioDetachAudioMixedProcessor );

	/* Math. */
		/* Utils. */
	assignGlobalFunction( "Round", lmathRound );
	assignGlobalFunction( "Sign", lmathSign );
	assignGlobalFunction( "Clamp", lmathClamp );
	assignGlobalFunction( "Lerp", lmathLerp );
	assignGlobalFunction( "Normalize", lmathNormalize );
	assignGlobalFunction( "Remap", lmathRemap );
	assignGlobalFunction( "Wrap", lmathWrap );
	assignGlobalFunction( "FloatEquals", lmathFloatEquals );
		/* Vector2. */
	assignGlobalFunction( "Vector2Zero", lmathVector2Zero );
	assignGlobalFunction( "Vector2One", lmathVector2One );
	assignGlobalFunction( "Vector2Add", lmathVector2Add );
	assignGlobalFunction( "Vector2AddValue", lmathVector2AddValue );
	assignGlobalFunction( "Vector2Subtract", lmathVector2Subtract );
	assignGlobalFunction( "Vector2SubtractValue", lmathVector2SubtractValue );
	assignGlobalFunction( "Vector2Length", lmathVector2Length );
	assignGlobalFunction( "Vector2LengthSqr", lmathVector2LengthSqr );
	assignGlobalFunction( "Vector2DotProduct", lmathVector2DotProduct );
	assignGlobalFunction( "Vector2CrossProduct", lmathVector2CrossProduct );
	assignGlobalFunction( "Vector2Distance", lmathVector2Distance );
	assignGlobalFunction( "Vector2DistanceSqr", lmathVector2DistanceSqr );
	assignGlobalFunction( "Vector2Angle", lmathVector2Angle );
	assignGlobalFunction( "Vector2LineAngle", lmathVector2LineAngle );
	assignGlobalFunction( "Vector2Scale", lmathVector2Scale );
	assignGlobalFunction( "Vector2Multiply", lmathVector2Multiply );
	assignGlobalFunction( "Vector2Negate", lmathVector2Negate );
	assignGlobalFunction( "Vector2Divide", lmathVector2Divide );
	assignGlobalFunction( "Vector2Normalize", lmathVector2Normalize );
	assignGlobalFunction( "Vector2Transform", lmathVector2Transform );
	assignGlobalFunction( "Vector2Lerp", lmathVector2Lerp );
	assignGlobalFunction( "Vector2Reflect", lmathVector2Reflect );
	assignGlobalFunction( "Vector2Min", lmathVector2Min );
	assignGlobalFunction( "Vector2Max", lmathVector2Max );
	assignGlobalFunction( "Vector2Rotate", lmathVector2Rotate );
	assignGlobalFunction( "Vector2MoveTowards", lmathVector2MoveTowards );
	assignGlobalFunction( "Vector2Invert", lmathVector2Invert );
	assignGlobalFunction( "Vector2Clamp", lmathVector2Clamp );
	assignGlobalFunction( "Vector2ClampValue", lmathVector2ClampValue );
	assignGlobalFunction( "Vector2Equals", lmathVector2Equals );
	assignGlobalFunction( "Vector2Refract", lmathVector2Refract );
		/* Vector3. */
	assignGlobalFunction( "Vector3Zero", lmathVector3Zero );
	assignGlobalFunction( "Vector3One", lmathVector3One );
	assignGlobalFunction( "Vector3Add", lmathVector3Add );
	assignGlobalFunction( "Vector3AddValue", lmathVector3AddValue );
	assignGlobalFunction( "Vector3Subtract", lmathVector3Subtract );
	assignGlobalFunction( "Vector3SubtractValue", lmathVector3SubtractValue );
	assignGlobalFunction( "Vector3Scale", lmathVector3Scale );
	assignGlobalFunction( "Vector3Multiply", lmathVector3Multiply );
	assignGlobalFunction( "Vector3CrossProduct", lmathVector3CrossProduct );
	assignGlobalFunction( "Vector3Perpendicular", lmathVector3Perpendicular );
	assignGlobalFunction( "Vector3Length", lmathVector3Length );
	assignGlobalFunction( "Vector3LengthSqr", lmathVector3LengthSqr );
	assignGlobalFunction( "Vector3DotProduct", lmathVector3DotProduct );
	assignGlobalFunction( "Vector3Distance", lmathVector3Distance );
	assignGlobalFunction( "Vector3DistanceSqr", lmathVector3DistanceSqr );
	assignGlobalFunction( "Vector3Angle", lmathVector3Angle );
	assignGlobalFunction( "Vector3Negate", lmathVector3Negate );
	assignGlobalFunction( "Vector3Divide", lmathVector3Divide );
	assignGlobalFunction( "Vector3Normalize", lmathVector3Normalize );
	assignGlobalFunction( "Vector3Project", lmathVector3Project );
	assignGlobalFunction( "Vector3Reject", lmathVector3Reject );
	assignGlobalFunction( "Vector3OrthoNormalize", lmathVector3OrthoNormalize );
	assignGlobalFunction( "Vector3Transform", lmathVector3Transform );
	assignGlobalFunction( "Vector3RotateByQuaternion", lmathVector3RotateByQuaternion );
	assignGlobalFunction( "Vector3RotateByAxisAngle", lmathVector3RotateByAxisAngle );
	assignGlobalFunction( "Vector3MoveTowards", lmathVector3MoveTowards );
	assignGlobalFunction( "Vector3Lerp", lmathVector3Lerp );
	assignGlobalFunction( "Vector3CubicHermite", lmathVector3CubicHermite );
	assignGlobalFunction( "Vector3Reflect", lmathVector3Reflect );
	assignGlobalFunction( "Vector3Min", lmathVector3Min );
	assignGlobalFunction( "Vector3Max", lmathVector3Max );
	assignGlobalFunction( "Vector3Barycenter", lmathVector3Barycenter );
	assignGlobalFunction( "Vector3Unproject", lmathVector3Unproject );
	assignGlobalFunction( "Vector3Invert", lmathVector3Invert );
	assignGlobalFunction( "Vector3Clamp", lmathVector3Clamp );
	assignGlobalFunction( "Vector3ClampValue", lmathVector3ClampValue );
	assignGlobalFunction( "Vector3Equals", lmathVector3Equals );
	assignGlobalFunction( "Vector3Refract", lmathVector3Refract );
		/* Vector4. */
	assignGlobalFunction( "Vector4Zero", lmathVector4Zero );
	assignGlobalFunction( "Vector4One", lmathVector4One );
	assignGlobalFunction( "Vector4Add", lmathVector4Add );
	assignGlobalFunction( "Vector4AddValue", lmathVector4AddValue );
	assignGlobalFunction( "Vector4Subtract", lmathVector4Subtract );
	assignGlobalFunction( "Vector4SubtractValue", lmathVector4SubtractValue );
	assignGlobalFunction( "Vector4Length", lmathVector4Length );
	assignGlobalFunction( "Vector4LengthSqr", lmathVector4LengthSqr );
	assignGlobalFunction( "Vector4DotProduct", lmathVector4DotProduct );
	assignGlobalFunction( "Vector4Distance", lmathVector4Distance );
	assignGlobalFunction( "Vector4DistanceSqr", lmathVector4DistanceSqr );
	assignGlobalFunction( "Vector4Scale", lmathVector4Scale );
	assignGlobalFunction( "Vector4Multiply", lmathVector4Multiply );
	assignGlobalFunction( "Vector4Negate", lmathVector4Negate );
	assignGlobalFunction( "Vector4Divide", lmathVector4Divide );
	assignGlobalFunction( "Vector4Normalize", lmathVector4Normalize );
	assignGlobalFunction( "Vector4Min", lmathVector4Min );
	assignGlobalFunction( "Vector4Max", lmathVector4Max );
	assignGlobalFunction( "Vector4Lerp", lmathVector4Lerp );
	assignGlobalFunction( "Vector4MoveTowards", lmathVector4MoveTowards );
	assignGlobalFunction( "Vector4Invert", lmathVector4Invert );
	assignGlobalFunction( "Vector4Equals", lmathVector4Equals );
		/* Matrix. */
	assignGlobalFunction( "MatrixDeterminant", lmathMatrixDeterminant );
	assignGlobalFunction( "MatrixTrace", lmathMatrixTrace );
	assignGlobalFunction( "MatrixTranspose", lmathMatrixTranspose );
	assignGlobalFunction( "MatrixInvert", lmathMatrixInvert );
	assignGlobalFunction( "MatrixIdentity", lmathMatrixIdentity );
	assignGlobalFunction( "MatrixAdd", lmathMatrixAdd );
	assignGlobalFunction( "MatrixSubtract", lmathMatrixSubtract );
	assignGlobalFunction( "MatrixMultiply", lmathMatrixMultiply );
	assignGlobalFunction( "MatrixMultiplyValue", lmathMatrixMultiplyValue );
	assignGlobalFunction( "MatrixTranslate", lmathMatrixTranslate );
	assignGlobalFunction( "MatrixRotate", lmathMatrixRotate );
	assignGlobalFunction( "MatrixRotateX", lmathMatrixRotateX );
	assignGlobalFunction( "MatrixRotateY", lmathMatrixRotateY );
	assignGlobalFunction( "MatrixRotateZ", lmathMatrixRotateZ );
	assignGlobalFunction( "MatrixRotateXYZ", lmathMatrixRotateXYZ );
	assignGlobalFunction( "MatrixRotateZYX", lmathMatrixRotateZYX );
	assignGlobalFunction( "MatrixScale", lmathMatrixScale );
	assignGlobalFunction( "MatrixFrustum", lmathMatrixFrustum );
	assignGlobalFunction( "MatrixPerspective", lmathMatrixPerspective );
	assignGlobalFunction( "MatrixOrtho", lmathMatrixOrtho );
	assignGlobalFunction( "MatrixLookAt", lmathMatrixLookAt );
	assignGlobalFunction( "MatrixCompose", lmathMatrixCompose );
	assignGlobalFunction( "MatrixDecompose", lmathMatrixDecompose );
		/* Quaternion. */
	assignGlobalFunction( "QuaternionAdd", lmathQuaternionAdd );
	assignGlobalFunction( "QuaternionAddValue", lmathQuaternionAddValue );
	assignGlobalFunction( "QuaternionSubtract", lmathQuaternionSubtract );
	assignGlobalFunction( "QuaternionSubtractValue", lmathQuaternionSubtractValue );
	assignGlobalFunction( "QuaternionIdentity", lmathQuaternionIdentity );
	assignGlobalFunction( "QuaternionLength", lmathQuaternionLength );
	assignGlobalFunction( "QuaternionNormalize", lmathQuaternionNormalize );
	assignGlobalFunction( "QuaternionInvert", lmathQuaternionInvert );
	assignGlobalFunction( "QuaternionMultiply", lmathQuaternionMultiply );
	assignGlobalFunction( "QuaternionScale", lmathQuaternionScale );
	assignGlobalFunction( "QuaternionDivide", lmathQuaternionDivide );
	assignGlobalFunction( "QuaternionLerp", lmathQuaternionLerp );
	assignGlobalFunction( "QuaternionNlerp", lmathQuaternionNlerp );
	assignGlobalFunction( "QuaternionSlerp", lmathQuaternionSlerp );
	assignGlobalFunction( "QuaternionCubicHermiteSpline", lmathQuaternionCubicHermiteSpline );
	assignGlobalFunction( "QuaternionFromVector3ToVector3", lmathQuaternionFromVector3ToVector3 );
	assignGlobalFunction( "QuaternionFromMatrix", lmathQuaternionFromMatrix );
	assignGlobalFunction( "QuaternionToMatrix", lmathQuaternionToMatrix );
	assignGlobalFunction( "QuaternionFromAxisAngle", lmathQuaternionFromAxisAngle );
	assignGlobalFunction( "QuaternionToAxisAngle", lmathQuaternionToAxisAngle );
	assignGlobalFunction( "QuaternionFromEuler", lmathQuaternionFromEuler );
	assignGlobalFunction( "QuaternionToEuler", lmathQuaternionToEuler );
	assignGlobalFunction( "QuaternionTransform", lmathQuaternionTransform );
	assignGlobalFunction( "QuaternionEquals", lmathQuaternionEquals );
		/* Frustum. */
	assignGlobalFunction( "ExtractFrustum", lmathExtractFrustum );
	assignGlobalFunction( "PointInFrustum", lmathPointInFrustum );
	assignGlobalFunction( "SphereInFrustum", lmathSphereInFrustum );
	assignGlobalFunction( "AABBInFrustum", lmathAABBInFrustum );

	/* Gui. */
		/* Global gui state control functions. */
	assignGlobalFunction( "GuiEnable", lguiGuiEnable );
	assignGlobalFunction( "GuiDisable", lguiGuiDisable );
	assignGlobalFunction( "GuiLock", lguiGuiLock );
	assignGlobalFunction( "GuiUnlock", lguiGuiUnlock );
	assignGlobalFunction( "GuiIsLocked", lguiGuiIsLocked );
	assignGlobalFunction( "GuiSetAlpha", lguiGuiSetAlpha );
	assignGlobalFunction( "GuiSetState", lguiGuiSetState );
	assignGlobalFunction( "GuiGetState", lguiGuiGetState );
	assignGlobalFunction( "GuiSetSliderDragging", lguiGuiSetSliderDragging );
	assignGlobalFunction( "GuiGetSliderDragging", lguiGuiGetSliderDragging );
	assignGlobalFunction( "GuiSetSliderActive", lguiGuiSetSliderActive );
	assignGlobalFunction( "GuiGetSliderActive", lguiGuiGetSliderActive );
		/* Font set/get functions. */
	assignGlobalFunction( "GuiSetFont", lguiGuiSetFont );
	assignGlobalFunction( "GuiGetFont", lguiGuiGetFont );
		/* Style set/get functions. */
	assignGlobalFunction( "GuiSetStyle", lguiGuiSetStyle );
	assignGlobalFunction( "GuiGetStyle", lguiGuiGetStyle );
		/* Styles loading functions */
	assignGlobalFunction( "GuiLoadStyle", lguiGuiLoadStyle );
	assignGlobalFunction( "GuiLoadStyleDefault", lguiGuiLoadStyleDefault );
		/* Tooltips management functions. */
	assignGlobalFunction( "GuiEnableTooltip", lguiGuiEnableTooltip );
	assignGlobalFunction( "GuiDisableTooltip", lguiGuiDisableTooltip );
	assignGlobalFunction( "GuiSetTooltip", lguiGuiSetTooltip );
		/* Icons functionality. */
	assignGlobalFunction( "GuiIconText", lguiGuiIconText );
	assignGlobalFunction( "GuiSetIconScale", lguiGuiSetIconScale );
	assignGlobalFunction( "GuiGetIcons", lguiGuiGetIcons );
	assignGlobalFunction( "GuiSetIcons", lguiGuiSetIcons );
	assignGlobalFunction( "GuiLoadIcons", lguiGuiLoadIcons );
	assignGlobalFunction( "GuiDrawIcon", lguiGuiDrawIcon );
		/* Container/separator controls, useful for controls organization. */
	assignGlobalFunction( "GuiWindowBox", lguiGuiWindowBox );
	assignGlobalFunction( "GuiGroupBox", lguiGuiGroupBox );
	assignGlobalFunction( "GuiLine", lguiGuiLine );
	assignGlobalFunction( "GuiPanel", lguiGuiPanel );
	assignGlobalFunction( "GuiTabBar", lguiGuiTabBar );
	assignGlobalFunction( "GuiScrollPanel", lguiGuiScrollPanel );
		/* Basic controls set. */
	assignGlobalFunction( "GuiLabel", lguiGuiLabel );
	assignGlobalFunction( "GuiButton", lguiGuiButton );
	assignGlobalFunction( "GuiLabelButton", lguiGuiLabelButton );
	assignGlobalFunction( "GuiToggle", lguiGuiToggle );
	assignGlobalFunction( "GuiToggleGroup", lguiGuiToggleGroup );
	assignGlobalFunction( "GuiToggleSlider", lguiGuiToggleSlider );
	assignGlobalFunction( "GuiCheckBox", lguiGuiCheckBox );
	assignGlobalFunction( "GuiComboBox", lguiGuiComboBox );
	assignGlobalFunction( "GuiDropdownBox", lguiGuiDropdownBox );
	assignGlobalFunction( "GuiSpinner", lguiGuiSpinner );
	assignGlobalFunction( "GuiValueBox", lguiGuiValueBox );
	assignGlobalFunction( "GuiTextBox", lguiGuiTextBox );
	assignGlobalFunction( "GuiSlider", lguiGuiSlider );
	assignGlobalFunction( "GuiSliderBar", lguiGuiSliderBar );
	assignGlobalFunction( "GuiProgressBar", lguiGuiProgressBar );
	assignGlobalFunction( "GuiStatusBar", lguiGuiStatusBar );
	assignGlobalFunction( "GuiDummyRec", lguiGuiDummyRec );
	assignGlobalFunction( "GuiGrid", lguiGuiGrid );
	assignGlobalFunction( "GuiScrollBar", lguiGuiScrollBar );
		/* Advance controls set. */
	assignGlobalFunction( "GuiListView", lguiGuiListView );
	assignGlobalFunction( "GuiListViewEx", lguiGuiListViewEx );
	assignGlobalFunction( "GuiMessageBox", lguiGuiMessageBox );
	assignGlobalFunction( "GuiTextInputBox", lguiGuiTextInputBox );
	assignGlobalFunction( "GuiColorPicker", lguiGuiColorPicker );
	assignGlobalFunction( "GuiColorPanel", lguiGuiColorPanel );
	assignGlobalFunction( "GuiColorBarAlpha", lguiGuiColorBarAlpha );
	assignGlobalFunction( "GuiColorBarHue", lguiGuiColorBarHue );
	assignGlobalFunction( "GuiColorPickerHSV", lguiGuiColorPickerHSV );
	assignGlobalFunction( "GuiColorPanelHSV", lguiGuiColorPanelHSV );

	/* Lights */
		/* Light management functions. */
	assignGlobalFunction( "CreateLight", llightsCreateLight );
	assignGlobalFunction( "UpdateLightValues", llightsUpdateLightValues );
	assignGlobalFunction( "SetLightType", llightsSetLightType );
	assignGlobalFunction( "SetLightPosition", llightsSetLightPosition );
	assignGlobalFunction( "SetLightTarget", llightsSetLightTarget );
	assignGlobalFunction( "SetLightColor", llightsSetLightColor );
	assignGlobalFunction( "SetLightEnabled", llightsSetLightEnabled );
	assignGlobalFunction( "GetLightType", llightsGetLightType );
	assignGlobalFunction( "GetLightPosition", llightsGetLightPosition );
	assignGlobalFunction( "GetLightTarget", llightsGetLightTarget );
	assignGlobalFunction( "GetLightColor", llightsGetLightColor );
	assignGlobalFunction( "IsLightEnabled", llightsIsLightEnabled );

	/* RLGL */
		/* Matrix operations. */
	assignGlobalFunction( "rlMatrixMode", lrlglMatrixMode );
	assignGlobalFunction( "rlPushMatrix", lrlglPushMatrix );
	assignGlobalFunction( "rlPopMatrix", lrlglPopMatrix );
	assignGlobalFunction( "rlLoadIdentity", lrlglLoadIdentity );
	assignGlobalFunction( "rlTranslatef", lrlglTranslatef );
	assignGlobalFunction( "rlRotatef", lrlglRotatef );
	assignGlobalFunction( "rlScalef", lrlglScalef );
	assignGlobalFunction( "rlMultMatrixf", lrlglMultMatrixf );
	assignGlobalFunction( "rlFrustum", lrlglFrustum );
	assignGlobalFunction( "rlOrtho", lrlglOrtho );
	assignGlobalFunction( "rlViewport", lrlglViewport );
	assignGlobalFunction( "rlSetClipPlanes", lrlglSetClipPlanes );
	assignGlobalFunction( "rlGetCullDistanceNear", lrlglGetCullDistanceNear );
	assignGlobalFunction( "rlGetCullDistanceFar", lrlglGetCullDistanceFar );
		/* Vertex level operations. */
	assignGlobalFunction( "rlBegin", lrlglBegin );
	assignGlobalFunction( "rlEnd", lrlglEnd );
	assignGlobalFunction( "rlVertex2f", lrlglVertex2f );
	assignGlobalFunction( "rlVertex3f", lrlglVertex3f );
	assignGlobalFunction( "rlTexCoord2f", lrlglTexCoord2f );
	assignGlobalFunction( "rlNormal3f", lrlglNormal3f );
	assignGlobalFunction( "rlColor4ub", lrlglColor4ub );
	assignGlobalFunction( "rlColor3f", lrlglColor3f );
	assignGlobalFunction( "rlColor4f", lrlglColor4f );
		/* Vertex buffers state. */
	assignGlobalFunction( "rlEnableVertexArray", lrlglEnableVertexArray );
	assignGlobalFunction( "rlDisableVertexArray", lrlglDisableVertexArray );
	assignGlobalFunction( "rlEnableVertexBuffer", lrlglEnableVertexBuffer );
	assignGlobalFunction( "rlDisableVertexBuffer", lrlglDisableVertexBuffer );
	assignGlobalFunction( "rlEnableVertexBufferElement", lrlglEnableVertexBufferElement );
	assignGlobalFunction( "rlDisableVertexBufferElement", lrlglDisableVertexBufferElement );
	assignGlobalFunction( "rlEnableVertexAttribute", lrlglEnableVertexAttribute );
	assignGlobalFunction( "rlDisableVertexAttribute", lrlglDisableVertexAttribute );
#if defined( GRAPHICS_API_OPENGL_11 )
	assignGlobalFunction( "rlEnableStatePointer", lrlglEnableStatePointer );
	assignGlobalFunction( "rlDisableStatePointer", lrlglDisableStatePointer );
#endif
		/* Textures state. */
	assignGlobalFunction( "rlActiveTextureSlot", lrlglActiveTextureSlot );
	assignGlobalFunction( "rlEnableTexture", lrlglEnableTexture );
	assignGlobalFunction( "rlDisableTexture", lrlglDisableTexture );
	assignGlobalFunction( "rlEnableTextureCubemap", lrlglEnableTextureCubemap );
	assignGlobalFunction( "rlDisableTextureCubemap", lrlglDisableTextureCubemap );
	assignGlobalFunction( "rlTextureParameters", lrlglTextureParameters );
	assignGlobalFunction( "rlCubemapParameters", lrlglCubemapParameters );
		/* Shader state. */
	assignGlobalFunction( "rlEnableShader", lrlglEnableShader );
	assignGlobalFunction( "rlDisableShader", lrlglDisableShader );
		/* Framebuffer state. */
	assignGlobalFunction( "rlEnableFramebuffer", lrlglEnableFramebuffer );
	assignGlobalFunction( "rlDisableFramebuffer", lrlglDisableFramebuffer );
	assignGlobalFunction( "rlGetActiveFramebuffer", lrlglGetActiveFramebuffer );
	assignGlobalFunction( "rlActiveDrawBuffers", lrlglActiveDrawBuffers );
	assignGlobalFunction( "rlBlitFramebuffer", lrlglBlitFramebuffer );
	assignGlobalFunction( "rlBindFramebuffer", lrlglBindFramebuffer );
		/* General render state. */
	assignGlobalFunction( "rlEnableColorBlend", lrlglEnableColorBlend );
	assignGlobalFunction( "rlDisableColorBlend", lrlglDisableColorBlend );
	assignGlobalFunction( "rlEnableDepthTest", lrlglEnableDepthTest );
	assignGlobalFunction( "rlDisableDepthTest", lrlglDisableDepthTest );
	assignGlobalFunction( "rlEnableDepthMask", lrlglEnableDepthMask );
	assignGlobalFunction( "rlDisableDepthMask", lrlglDisableDepthMask );
	assignGlobalFunction( "rlEnableBackfaceCulling", lrlglEnableBackfaceCulling );
	assignGlobalFunction( "rlDisableBackfaceCulling", lrlglDisableBackfaceCulling );
	assignGlobalFunction( "rlColorMask", lrlglColorMask );
	assignGlobalFunction( "rlSetCullFace", lrlglSetCullFace );
	assignGlobalFunction( "rlEnableScissorTest", lrlglEnableScissorTest );
	assignGlobalFunction( "rlDisableScissorTest", lrlglDisableScissorTest );
	assignGlobalFunction( "rlScissor", lrlglScissor );
	assignGlobalFunction( "rlEnableWireMode", lrlglEnableWireMode );
	assignGlobalFunction( "rlDisableWireMode", lrlglDisableWireMode );
	assignGlobalFunction( "rlEnablePointMode", lrlglEnablePointMode );
	assignGlobalFunction( "rlDisablePointMode", lrlglDisablePointMode );
	assignGlobalFunction( "rlSetLineWidth", lrlglSetLineWidth );
	assignGlobalFunction( "rlGetLineWidth", lrlglGetLineWidth );
	assignGlobalFunction( "rlSetPointSize", lrlglSetPointSize );
	assignGlobalFunction( "rlGetPointSize", lrlglGetPointSize );
	assignGlobalFunction( "rlEnableSmoothLines", lrlglEnableSmoothLines );
	assignGlobalFunction( "rlDisableSmoothLines", lrlglDisableSmoothLines );
	assignGlobalFunction( "rlEnableStereoRender", lrlglEnableStereoRender );
	assignGlobalFunction( "rlDisableStereoRender", lrlglDisableStereoRender );
	assignGlobalFunction( "rlIsStereoRenderEnabled", lrlglIsStereoRenderEnabled );
	assignGlobalFunction( "rlClearColor", lrlglClearColor );
	assignGlobalFunction( "rlClearScreenBuffers", lrlglClearScreenBuffers );
	assignGlobalFunction( "rlCheckErrors", lrlglCheckErrors );
	assignGlobalFunction( "rlSetBlendMode", lrlglSetBlendMode );
	assignGlobalFunction( "rlSetBlendFactors", lrlglSetBlendFactors );
	assignGlobalFunction( "rlSetBlendFactorsSeparate", lrlglSetBlendFactorsSeparate );
		/* Initialization functions. */
	assignGlobalFunction( "rlGetVersion", lrlglGetVersion );
	assignGlobalFunction( "rlSetFramebufferWidth", lrlglSetFramebufferWidth );
	assignGlobalFunction( "rlGetFramebufferWidth", lrlglGetFramebufferWidth );
	assignGlobalFunction( "rlSetFramebufferHeight", lrlglSetFramebufferHeight );
	assignGlobalFunction( "rlGetFramebufferHeight", lrlglGetFramebufferHeight );
	assignGlobalFunction( "rlGetTextureIdDefault", lrlglGetTextureIdDefault );
	assignGlobalFunction( "rlGetShaderIdDefault", lrlglGetShaderIdDefault );
	assignGlobalFunction( "rlGetShaderLocsDefault", lrlglGetShaderLocsDefault );
		/* Render batch management. */
	assignGlobalFunction( "rlLoadRenderBatch", lrlglLoadRenderBatch );
	assignGlobalFunction( "rlUnloadRenderBatch", lrlglUnloadRenderBatch );
	assignGlobalFunction( "rlDrawRenderBatch", lrlglDrawRenderBatch );
	assignGlobalFunction( "rlSetRenderBatchActive", lrlglSetRenderBatchActive );
	assignGlobalFunction( "rlDrawRenderBatchActive", lrlglDrawRenderBatchActive );
	assignGlobalFunction( "rlCheckRenderBatchLimit", lrlglCheckRenderBatchLimit );
	assignGlobalFunction( "rlSetTexture", lrlglSetTexture );
		/* Vertex buffers management. */
	assignGlobalFunction( "rlLoadVertexArray", lrlglLoadVertexArray );
	assignGlobalFunction( "rlLoadVertexBuffer", lrlglLoadVertexBuffer );
	assignGlobalFunction( "rlLoadVertexBufferElement", lrlglLoadVertexBufferElement );
	assignGlobalFunction( "rlUpdateVertexBuffer", lrlglUpdateVertexBuffer );
	assignGlobalFunction( "rlUpdateVertexBufferElements", lrlglUpdateVertexBufferElements );
	assignGlobalFunction( "rlUnloadVertexArray", lrlglUnloadVertexArray );
	assignGlobalFunction( "rlUnloadVertexBuffer", lrlglUnloadVertexBuffer );
	assignGlobalFunction( "rlSetVertexAttribute", lrlglSetVertexAttribute );
	assignGlobalFunction( "rlSetVertexAttributeDivisor", lrlglSetVertexAttributeDivisor );
	assignGlobalFunction( "rlSetVertexAttributeDefault", lrlglSetVertexAttributeDefault );
	assignGlobalFunction( "rlDrawVertexArray", lrlglDrawVertexArray );
	assignGlobalFunction( "rlDrawVertexArrayElements", lrlglDrawVertexArrayElements );
	assignGlobalFunction( "rlDrawVertexArrayInstanced", lrlglDrawVertexArrayInstanced );
	assignGlobalFunction( "rlDrawVertexArrayElementsInstanced", lrlglDrawVertexArrayElementsInstanced );
		/* Textures management. */
	assignGlobalFunction( "rlLoadTexture", lrlglLoadTexture );
	assignGlobalFunction( "rlLoadTextureDepth", lrlglLoadTextureDepth );
	assignGlobalFunction( "rlLoadTextureCubemap", lrlglLoadTextureCubemap );
	assignGlobalFunction( "rlUpdateTexture", lrlglUpdateTexture );
	assignGlobalFunction( "rlGetGlTextureFormats", lrlglGetGlTextureFormats );
	assignGlobalFunction( "rlGetPixelFormatName", lrlglGetPixelFormatName );
	assignGlobalFunction( "rlUnloadTexture", lrlglUnloadTexture );
	assignGlobalFunction( "rlGenTextureMipmaps", lrlglGenTextureMipmaps );
	assignGlobalFunction( "rlReadTexturePixels", lrlglReadTexturePixels );
	assignGlobalFunction( "rlReadScreenPixels", lrlglReadScreenPixels );
		/* Framebuffer management (fbo). */
	assignGlobalFunction( "rlLoadFramebuffer", lrlglLoadFramebuffer );
	assignGlobalFunction( "rlFramebufferAttach", lrlglFramebufferAttach );
	assignGlobalFunction( "rlFramebufferComplete", lrlglFramebufferComplete );
	assignGlobalFunction( "rlUnloadFramebuffer", lrlglUnloadFramebuffer );
	assignGlobalFunction( "rlCopyFramebuffer", lrlglCopyFramebuffer );
	assignGlobalFunction( "rlResizeFramebuffer", lrlglResizeFramebuffer );
		/* Shaders management */
	assignGlobalFunction( "rlLoadShader", lrlglLoadShader );
	assignGlobalFunction( "rlLoadShaderProgram", lrlglLoadShaderProgram );
	assignGlobalFunction( "rlLoadShaderProgramEx", lrlglLoadShaderProgramEx );
	assignGlobalFunction( "rlLoadShaderProgramCompute", lrlglLoadShaderProgramCompute );
	assignGlobalFunction( "rlUnloadShader", lrlgUnloadShader );
	assignGlobalFunction( "rlUnloadShaderProgram", lrlglUnloadShaderProgram );
	assignGlobalFunction( "rlGetLocationUniform", lrlglGetLocationUniform );
	assignGlobalFunction( "rlGetLocationAttrib", lrlglGetLocationAttrib );
	assignGlobalFunction( "rlSetUniform", lrlglSetUniform );
	assignGlobalFunction( "rlSetUniformMatrix", lrlglSetUniformMatrix );
	assignGlobalFunction( "rlSetUniformMatrices", lrlglSetUniformMatrices );
	assignGlobalFunction( "rlSetUniformSampler", lrlglSetUniformSampler );
	assignGlobalFunction( "rlSetShader", lrlglSetShader );
		/* Compute shader management */
	assignGlobalFunction( "rlComputeShaderDispatch", lrlglComputeShaderDispatch );
		/* Shader buffer storage object management (ssbo) */
	assignGlobalFunction( "rlLoadShaderBuffer", lrlglLoadShaderBuffer );
	assignGlobalFunction( "rlUnloadShaderBuffer", lrlglUnloadShaderBuffer );
	assignGlobalFunction( "rlUpdateShaderBuffer", lrlglUpdateShaderBuffer );
	assignGlobalFunction( "rlBindShaderBuffer", lrlglBindShaderBuffer );
	assignGlobalFunction( "rlReadShaderBuffer", lrlglReadShaderBuffer );
	assignGlobalFunction( "rlCopyShaderBuffer", lrlglCopyShaderBuffer );
	assignGlobalFunction( "rlGetShaderBufferSize", lrlglGetShaderBufferSize );
		/* Buffer management */
	assignGlobalFunction( "rlBindImageTexture", lrlglBindImageTexture );
		/* Matrix state management. */
	assignGlobalFunction( "rlGetMatrixModelview", lrlglGetMatrixModelview );
	assignGlobalFunction( "rlGetMatrixProjection", lrlglGetMatrixProjection );
	assignGlobalFunction( "rlGetMatrixTransform", lrlglGetMatrixTransform );
	assignGlobalFunction( "rlGetMatrixProjectionStereo", lrlglGetMatrixProjectionStereo );
	assignGlobalFunction( "rlGetMatrixViewOffsetStereo", lrlglGetMatrixViewOffsetStereo );
	assignGlobalFunction( "rlSetMatrixProjection", lrlglSetMatrixProjection );
	assignGlobalFunction( "rlSetMatrixModelview", lrlglSetMatrixModelview );
	assignGlobalFunction( "rlSetMatrixProjectionStereo", lrlglSetMatrixProjectionStereo );
	assignGlobalFunction( "rlSetMatrixViewOffsetStereo", lrlglSetMatrixViewOffsetStereo );

	/* OpenGL */
		/* Rendering. */
	assignGlobalFunction( "glClear", lglClear );
		/* Frame Buffers. */
	assignGlobalFunction( "glBlitFramebuffer", lglBlitFramebuffer );
		/* State Management. */
	assignGlobalFunction( "glDepthRange", lglDepthRange );
	assignGlobalFunction( "glEnable", lglEnable );
	assignGlobalFunction( "glDisable", lglDisable );
	assignGlobalFunction( "glPolygonOffset", lglPolygonOffset );
	assignGlobalFunction( "glStencilFunc", lglStencilFunc );
	assignGlobalFunction( "glStencilFuncSeparate", lglStencilFuncSeparate );
	assignGlobalFunction( "glStencilMask", lglStencilMask );
	assignGlobalFunction( "glStencilMaskSeparate", lglStencilMaskSeparate );
	assignGlobalFunction( "glStencilOp", lglStencilOp );
	assignGlobalFunction( "glStencilOpSeparate", lglStencilOpSeparate );
		/* Utility. */
	assignGlobalFunction( "glGetString", lglGetString );

	/* Easings */
		/* Linear Easing functions. */
	assignGlobalFunction( "EaseLinear", leasingsEaseLinear );
		/* Sine Easing functions. */
	assignGlobalFunction( "EaseSineIn", leasingsEaseSineIn );
	assignGlobalFunction( "EaseSineOut", leasingsEaseSineOut );
	assignGlobalFunction( "EaseSineInOut", leasingsEaseSineInOut );
		/* Circular Easing functions. */
	assignGlobalFunction( "EaseCircIn", leasingsEaseCircIn );
	assignGlobalFunction( "EaseCircOut", leasingsEaseCircOut );
	assignGlobalFunction( "EaseCircInOut", leasingsEaseCircInOut );
		/* Cubic Easing functions. */
	assignGlobalFunction( "EaseCubicIn", leasingsEaseCubicIn );
	assignGlobalFunction( "EaseCubicOut", leasingsEaseCubicOut );
	assignGlobalFunction( "EaseCubicInOut", leasingsEaseCubicInOut );
		/* Quadratic Easing functions. */
	assignGlobalFunction( "EaseQuadIn", leasingsEaseQuadIn );
	assignGlobalFunction( "EaseQuadOut", leasingsEaseQuadOut );
	assignGlobalFunction( "EaseQuadInOut", leasingsEaseQuadInOut );
		/* Exponential Easing functions. */
	assignGlobalFunction( "EaseExpoIn", leasingsEaseExpoIn );
	assignGlobalFunction( "EaseExpoOut", leasingsEaseExpoOut );
	assignGlobalFunction( "EaseExpoInOut", leasingsEaseExpoInOut );
		/* Back Easing functions. */
	assignGlobalFunction( "EaseBackIn", leasingsEaseBackIn );
	assignGlobalFunction( "EaseBackOut", leasingsEaseBackOut );
	assignGlobalFunction( "EaseBackInOut", leasingsEaseBackInOut );
		/* Bounce Easing functions. */
	assignGlobalFunction( "EaseBounceIn", leasingsEaseBounceIn );
	assignGlobalFunction( "EaseBounceOut", leasingsEaseBounceOut );
	assignGlobalFunction( "EaseBounceInOut", leasingsEaseBounceInOut );
		/* Elastic Easing functions. */
	assignGlobalFunction( "EaseElasticIn", leasingsEaseElasticIn );
	assignGlobalFunction( "EaseElasticOut", leasingsEaseElasticOut );
	assignGlobalFunction( "EaseElasticInOut", leasingsEaseElasticInOut );

	/* Bitwise Operations */
		/* Arithmetic. */
	assignGlobalFunction( "BitAnd", lbitAnd );
	assignGlobalFunction( "BitOr", lbitOr );
	assignGlobalFunction( "BitXor", lbitXor );
	assignGlobalFunction( "BitNot", lbitNot );
	assignGlobalFunction( "BitShiftLeft", lbitShiftLeft );
	assignGlobalFunction( "BitShiftRight", lbitShiftRight );
	assignGlobalFunction( "BitSet", lbitSet );
	assignGlobalFunction( "BitGet", lbitGet );
	assignGlobalFunction( "BitToggle", lbitToggle );

	lua_pop( L, -1 );
}

/* Lua util functions. */

bool uluaGetBoolean( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TBOOLEAN );

	return lua_toboolean( L, index );
}

Color uluaGetColor( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Color color = { 0, 0, 0, 255 };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "r" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "r" );
		color.r = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "g" );
		color.g = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "b" );
		color.b = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "a" );
		color.a = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		color.r = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		color.g = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 3 );
		color.b = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 4 );
		color.a = (uint8_t)lua_tointeger( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return color;
}

Vector2 uluaGetVector2( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Vector2 vector = { 0.0f, 0.0f };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "x" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "x" );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "y" );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return vector;
}

Vector3 uluaGetVector3( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Vector3 vector = { 0.0f, 0.0f, 0.0f };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "x" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "x" );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "y" );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "z" );
		vector.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 3 );
		vector.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return vector;
}

Vector4 uluaGetVector4( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Vector4 vector = { 0.0f, 0.0f, 0.0f, 0.0f };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "x" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "x" );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "y" );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "z" );
		vector.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "w" );
		vector.w = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		vector.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		vector.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 3 );
		vector.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 4 );
		vector.w = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return vector;
}

Rectangle uluaGetRectangle( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Rectangle rect = { 0.0f, 0.0f, 0.0f, 0.0f };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "x" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "x" );
		rect.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "y" );
		rect.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "width" );
		rect.width = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "height" );
		rect.height = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		rect.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		rect.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 3 );
		rect.width = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 4 );
		rect.height = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return rect;
}

Quaternion uluaGetQuaternion( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Quaternion quaternion = { 0.0f, 0.0f, 0.0f, 0.0f };

	/* Assume object is given in named form if gets number. */
	lua_getfield( L, index, "x" );

	if ( lua_isnumber( L, -1 ) ) {
		lua_getfield( L, index, "x" );
		quaternion.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "y" );
		quaternion.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "z" );
		quaternion.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getfield( L, index, "w" );
		quaternion.w = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	else {
		lua_getiCustom( L, index, 1 );
		quaternion.x = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 2 );
		quaternion.y = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 3 );
		quaternion.z = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		lua_getiCustom( L, index, 4 );
		quaternion.w = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
	}
	lua_pop( L, 1 );

	return quaternion;
}

Matrix uluaGetMatrix( lua_State* L, int index ) {
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
				/* Look for one depth further if Matrix given as class. */
				else if ( lua_istable( L, -1 ) ) {
					int t3 = lua_gettop( L ), k = 0;
					lua_pushnil( L );

					while ( lua_next( L, t3 ) != 0 ) {
						if ( lua_isnumber( L, -1 ) ) {
							m[j][k] = lua_tonumber( L, -1 );
						}
					k++;
					lua_pop( L, 1 );
					}
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

BoundingBox uluaGetBoundingBox( lua_State* L, int index ) {
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
				if ( TextIsEqual( "min", lua_tostring( L, -2 ) ) ) {
					box.min = uluaGetVector3( L, lua_gettop( L ) );
				}
				else if ( TextIsEqual( "max", lua_tostring( L, -2 ) ) ) {
					box.max = uluaGetVector3( L, lua_gettop( L ) );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
	}
	return box;
}

Ray uluaGetRay( lua_State* L, int index ) {
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
				if ( TextIsEqual( "position", lua_tostring( L, -2 ) ) ) {
					ray.position = uluaGetVector3( L, lua_gettop( L ) );
				}
				else if ( TextIsEqual( "direction", lua_tostring( L, -2 ) ) ) {
					ray.direction = uluaGetVector3( L, lua_gettop( L ) );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
	}
	return ray;
}

NPatchInfo uluaGetNPatchInfo( lua_State* L, int index ) {
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
			if ( TextIsEqual( "source", lua_tostring( L, -2 ) ) ) {
				npatch.source = uluaGetRectangle( L, lua_gettop( L ) );
			}
			else if ( TextIsEqual( "left", lua_tostring( L, -2 ) ) ) {
				npatch.left = lua_tointeger( L, -1 );
			}
			else if ( TextIsEqual( "top", lua_tostring( L, -2 ) ) ) {
				npatch.top = lua_tointeger( L, -1 );
			}
			else if ( TextIsEqual( "right", lua_tostring( L, -2 ) ) ) {
				npatch.right = lua_tointeger( L, -1 );
			}
			else if ( TextIsEqual( "bottom", lua_tostring( L, -2 ) ) ) {
				npatch.bottom = lua_tointeger( L, -1 );
			}
			else if ( TextIsEqual( "layout", lua_tostring( L, -2 ) ) ) {
				npatch.layout = lua_tointeger( L, -1 );
			}
		}
		i++;
		lua_pop( L, 1 );
	}
	return npatch;
}

BoneInfo uluaGetBoneInfo( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	BoneInfo bone = { 0 };

	int t = index, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		/* Do not check type since there should be table and ints. */
		if ( lua_isnumber( L, -2 ) ) {
			switch ( i ) {
				case 0:
					strncpy( bone.name, lua_tostring( L, lua_gettop( L ) ), 32 );
					break;
				case 1:
					bone.parent = lua_tointeger( L, -1 );
					break;
				default:
					break;
			}
		}
		else if ( lua_istable( L, -1 ) ) {
			if ( lua_isstring( L, -2 ) ) {
				if ( TextIsEqual( "name", lua_tostring( L, -2 ) ) ) {
					strncpy( bone.name, lua_tostring( L, lua_gettop( L ) ), 32 );
				}
				else if ( TextIsEqual( "parent", lua_tostring( L, -2 ) ) ) {
					bone.parent = lua_tointeger( L, -1 );
				}
			}
		}
		i++;
		lua_pop( L, 1 );
	}
	return bone;
}

Transform uluaGetTransform( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	Transform transform = { 0 };

	int t = index, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		/* Do not check type since there should be table and ints. */
		if ( lua_isnumber( L, -2 ) ) {
			switch ( i ) {
				case 0:
					transform.translation = uluaGetVector3( L, lua_gettop( L ) );
					break;
				case 1:
					transform.rotation = uluaGetQuaternion( L, lua_gettop( L ) );
					break;
				case 2:
					transform.scale = uluaGetVector3( L, lua_gettop( L ) );
					break;
				default:
					break;
			}
		}
		else if ( lua_istable( L, -1 ) ) {
			if ( lua_isstring( L, -2 ) ) {
				if ( TextIsEqual( "translation", lua_tostring( L, -2 ) ) ) {
					transform.translation = uluaGetVector3( L, lua_gettop( L ) );
				}
				else if ( TextIsEqual( "rotation", lua_tostring( L, -2 ) ) ) {
					transform.rotation = uluaGetQuaternion( L, lua_gettop( L ) );
				}
				else if ( TextIsEqual( "scale", lua_tostring( L, -2 ) ) ) {
					transform.scale = uluaGetVector3( L, lua_gettop( L ) );
				}
			}
		}
		i++;
		lua_pop( L, 1 );
	}
	return transform;
}

Buffer* uluaGetBuffer( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Buffer*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "buffer", lua_tostring( L, -2 ) ) ) {
				Buffer* buffer = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					buffer = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					buffer = luaL_checkudata( L, lua_gettop( L ), "Buffer" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return buffer;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Buffer" );
	}
}

Image* uluaGetImage( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Image*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "image", lua_tostring( L, -2 ) ) ) {
				Image* image = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					image = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					image = luaL_checkudata( L, lua_gettop( L ), "Image" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return image;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Image" );
	}
}

Texture* uluaGetTexture( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Texture*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "texture", lua_tostring( L, -2 ) ) ) {
				Texture* texture = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					texture = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					texture = luaL_checkudata( L, lua_gettop( L ), "Texture" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return texture;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Texture" );
	}
}

RenderTexture* uluaGetRenderTexture( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (RenderTexture*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "renderTexture", lua_tostring( L, -2 ) ) ) {
				RenderTexture* renderTexture = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					renderTexture = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					renderTexture = luaL_checkudata( L, lua_gettop( L ), "RenderTexture" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return renderTexture;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "RenderTexture" );
	}
}

Shader* uluaGetShader( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Shader*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "shader", lua_tostring( L, -2 ) ) ) {
				Shader* shader = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					shader = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					shader = luaL_checkudata( L, lua_gettop( L ), "Shader" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return shader;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Shader" );
	}
}

Mesh* uluaGetMesh( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Mesh*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "mesh", lua_tostring( L, -2 ) ) ) {
				Mesh* mesh = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					mesh = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					mesh = luaL_checkudata( L, lua_gettop( L ), "Mesh" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return mesh;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Mesh" );
	}
}

Camera2D* uluaGetCamera2D( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Camera2D*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "camera2D", lua_tostring( L, -2 ) ) ) {
				Camera2D* camera = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					camera = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					camera = luaL_checkudata( L, lua_gettop( L ), "Camera2D" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return camera;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Camera2D" );
	}
}

Camera3D* uluaGetCamera3D( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Camera3D*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "camera3D", lua_tostring( L, -2 ) ) ) {
				Camera3D* camera = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					camera = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					camera = luaL_checkudata( L, lua_gettop( L ), "Camera3D" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return camera;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Camera3D" );
	}
}

Font* uluaGetFont( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Font*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "font", lua_tostring( L, -2 ) ) ) {
				Font* font = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					font = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					font = luaL_checkudata( L, lua_gettop( L ), "Font" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return font;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Font" );
	}
}

GlyphInfo* uluaGetGlyphInfo( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (GlyphInfo*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "glyphInfo", lua_tostring( L, -2 ) ) ) {
				GlyphInfo* glyph = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					glyph = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					glyph = luaL_checkudata( L, lua_gettop( L ), "GlyphInfo" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return glyph;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "GlyphInfo" );
	}
}

Wave* uluaGetWave( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Wave*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "wave", lua_tostring( L, -2 ) ) ) {
				Wave* wave = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					wave = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					wave = luaL_checkudata( L, lua_gettop( L ), "Wave" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return wave;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Wave" );
	}
}

Sound* uluaGetSound( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Sound*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "sound", lua_tostring( L, -2 ) ) ) {
				Sound* sound = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					sound = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					sound = luaL_checkudata( L, lua_gettop( L ), "Sound" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return sound;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		/* Also allow SoundAlias. */
		if ( luaL_testudata( L, index, "SoundAlias" ) ) {
			return (Sound*)lua_touserdata( L, index );
		}
		else {
			return luaL_checkudata( L, index, "Sound" );
		}
	}
}

Music* uluaGetMusic( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Music*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "music", lua_tostring( L, -2 ) ) ) {
				Music* music = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					music = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					music = luaL_checkudata( L, lua_gettop( L ), "Music" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return music;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Music" );
	}
}

AudioStream* uluaGetAudioStream( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (AudioStream*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "audioStream", lua_tostring( L, -2 ) ) ) {
				AudioStream* stream = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					stream = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					stream = luaL_checkudata( L, lua_gettop( L ), "AudioStream" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return stream;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "AudioStream" );
	}
}

Light* uluaGetLight( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Light*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "light", lua_tostring( L, -2 ) ) ) {
				Light* light = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					light = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					light = luaL_checkudata( L, lua_gettop( L ), "Light" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return light;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Light" );
	}
}

Material* uluaGetMaterial( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Material*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "material", lua_tostring( L, -2 ) ) ) {
				Material* material = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					material = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					material = luaL_checkudata( L, lua_gettop( L ), "Material" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return material;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Material" );
	}
}

Model* uluaGetModel( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (Model*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "model", lua_tostring( L, -2 ) ) ) {
				Model* model = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					model = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					model = luaL_checkudata( L, lua_gettop( L ), "Model" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return model;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "Model" );
	}
}

ModelAnimation* uluaGetModelAnimation( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (ModelAnimation*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "modelAnimation", lua_tostring( L, -2 ) ) ) {
				ModelAnimation* animation = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					animation = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					animation = luaL_checkudata( L, lua_gettop( L ), "ModelAnimation" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return animation;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "ModelAnimation" );
	}
}

ModelSkeleton* uluaGetModelSkeleton( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (ModelSkeleton*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "modelSkeleton", lua_tostring( L, -2 ) ) ) {
				ModelSkeleton* skeleton = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					skeleton = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					skeleton = luaL_checkudata( L, lua_gettop( L ), "ModelSkeleton" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return skeleton;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "ModelSkeleton" );
	}
}

rlRenderBatch* uluaGetRLRenderBatch( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (rlRenderBatch*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "rlRenderBatch", lua_tostring( L, -2 ) ) ) {
				rlRenderBatch* batch = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					batch = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					batch = luaL_checkudata( L, lua_gettop( L ), "rlRenderBatch" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return batch;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "rlRenderBatch" );
	}
}

AutomationEvent* uluaGetAutomationEvent( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (AutomationEvent*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "automationEvent", lua_tostring( L, -2 ) ) ) {
				AutomationEvent* event = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					event = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					event = luaL_checkudata( L, lua_gettop( L ), "AutomationEvent" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return event;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "AutomationEvent" );
	}
}

AutomationEventList* uluaGetAutomationEventList( lua_State* L, int index ) {
	int t = index, i = 0;

	switch ( lua_type( L, index ) )	{
	case LUA_TLIGHTUSERDATA:
		return (AutomationEventList*)lua_touserdata( L, index );
	case LUA_TTABLE:
		lua_pushnil( L );
		while ( lua_next( L, t ) != 0 ) {
			if ( TextIsEqual( "automationEventList", lua_tostring( L, -2 ) ) ) {
				AutomationEventList* list = NULL;
				if ( lua_islightuserdata( L, lua_gettop( L ) ) ) {
					list = lua_touserdata( L, lua_gettop( L ) );
				}
				else {
					list = luaL_checkudata( L, lua_gettop( L ), "AutomationEventList" );
				}
				lua_pop( L, 2 ); /* Pops also the string. */
				return list;
			}
			else {
				lua_pop( L, 1 );
			}
			i++;
		}
		/* Don't brake here, we want to get error from default if not found. */
	default:
		return luaL_checkudata( L, index, "AutomationEventList" );
	}
}

void getVector2Array( lua_State* L, int index, Vector2 points[] ) {
	int t = index, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
}

/* Push types. */

void uluaPushColor( lua_State* L, Color color ) {
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

void uluaPushVector2( lua_State* L, Vector2 vector ) {
	lua_createtable( L, 2, 0 );
	lua_pushnumber( L, vector.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, vector.y );
	lua_rawseti( L, -2, 2 );
}

void uluaPushVector3( lua_State* L, Vector3 vector ) {
	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, vector.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, vector.y );
	lua_rawseti( L, -2, 2 );	
	lua_pushnumber( L, vector.z );
	lua_rawseti( L, -2, 3 );
}

void uluaPushVector4( lua_State* L, Vector4 vector ) {
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

void uluaPushRectangle( lua_State* L, Rectangle rect ) {
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

void uluaPushQuaternion( lua_State* L, Quaternion quaternion ) {
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

void uluaPushMatrix( lua_State* L, Matrix matrix ) {
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

void uluaPushRay( lua_State* L, Ray ray ) {
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

void uluaPushRayCollision( lua_State* L, RayCollision rayCol ) {
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

void uluaPushBoundingBox( lua_State* L, BoundingBox box ) {
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

void uluaPushBoneInfo( lua_State* L, BoneInfo boneInfo ) {
	lua_createtable( L, 2, 0 );
	lua_pushstring( L, boneInfo.name );
	lua_setfield( L, -2, "name" );
	lua_pushinteger( L, boneInfo.parent );
	lua_setfield( L, -2, "parent" );
}

void uluaPushTransform( lua_State* L, Transform transform ) {
	lua_createtable( L, 3, 0 );
	uluaPushVector3( L, transform.translation );
	lua_setfield( L, -2, "translation" );
	uluaPushQuaternion( L, transform.rotation );
	lua_setfield( L, -2, "rotation" );
	uluaPushVector3( L, transform.scale );
	lua_setfield( L, -2, "scale" );
}

void uluaPushBuffer( lua_State* L, Buffer buffer ) {
	if ( buffer.size == 0 ) {
		buffer.data = NULL;
	}
	Buffer* bufferP = lua_newuserdata( L, sizeof( Buffer ) );
	*bufferP = buffer;
	luaCallLoad( "Buffer", bufferP );
	luaL_setmetatable( L, "Buffer" );
}

void uluaPushImage( lua_State* L, Image image ) {
	Image* imageP = lua_newuserdata( L, sizeof( Image ) );
	*imageP = image;
	luaCallLoad( "Image", imageP );
	luaL_setmetatable( L, "Image" );
}

void uluaPushTexture( lua_State* L, Texture texture ) {
	Texture* textureP = lua_newuserdata( L, sizeof( Texture ) );
	*textureP = texture;
	luaCallLoad( "Texture", textureP );
	luaL_setmetatable( L, "Texture" );
}

void uluaPushRenderTexture( lua_State* L, RenderTexture renderTexture ) {
	RenderTexture* renderTextureP = lua_newuserdata( L, sizeof( RenderTexture ) );
	*renderTextureP = renderTexture;
	luaCallLoad( "RenderTexture", renderTextureP );
	luaL_setmetatable( L, "RenderTexture" );
}

void uluaPushCamera2D( lua_State* L, Camera2D camera ) {
	Camera2D* cameraP = lua_newuserdata( L, sizeof( Camera2D ) );
	*cameraP = camera;
	luaL_setmetatable( L, "Camera2D" );
}

void uluaPushCamera3D( lua_State* L, Camera3D camera ) {
	Camera3D* cameraP = lua_newuserdata( L, sizeof( Camera3D ) );
	*cameraP = camera;
	luaL_setmetatable( L, "Camera3D" );
}

void uluaPushShader( lua_State* L, Shader shader ) {
	Shader* shaderP = lua_newuserdata( L, sizeof( Shader ) );
	*shaderP = shader;
	luaCallLoad( "Shader", shaderP );
	luaL_setmetatable( L, "Shader" );
}

void uluaPushFont( lua_State* L, Font font ) {
	Font* fontP = lua_newuserdata( L, sizeof( Font ) );
	*fontP = font;
	luaCallLoad( "Font", fontP );
	luaL_setmetatable( L, "Font" );
}

void uluaPushGlyphInfo( lua_State* L, GlyphInfo glyph ) {
	GlyphInfo* glyphP = lua_newuserdata( L, sizeof( GlyphInfo ) );
	*glyphP = glyph;
	luaCallLoad( "GlyphInfo", glyphP );
	luaL_setmetatable( L, "GlyphInfo" );
}

void uluaPushWave( lua_State* L, Wave wave ) {
	Wave* waveP = lua_newuserdata( L, sizeof( Wave ) );
	*waveP = wave;
	luaCallLoad( "Wave", waveP );
	luaL_setmetatable( L, "Wave" );
}

void uluaPushSound( lua_State* L, Sound sound ) {
	Sound* soundP = lua_newuserdata( L, sizeof( Sound ) );
	*soundP = sound;
	luaCallLoad( "Sound", soundP );
	luaL_setmetatable( L, "Sound" );
}

void uluaPushSoundAlias( lua_State* L, Sound alias ) {
	Sound* aliasP = lua_newuserdata( L, sizeof( Sound ) );
	*aliasP = alias;
	luaCallLoad( "SoundAlias", aliasP );
	luaL_setmetatable( L, "SoundAlias" );
}

void uluaPushMusic( lua_State* L, Music music ) {
	Music* musicP = lua_newuserdata( L, sizeof( Music ) );
	*musicP = music;
	luaCallLoad( "Music", musicP );
	luaL_setmetatable( L, "Music" );
}

void uluaPushAudioStream( lua_State* L, AudioStream stream ) {
	AudioStream* streamP = lua_newuserdata( L, sizeof( AudioStream ) );
	*streamP = stream;
	luaCallLoad( "AudioStream", streamP );
	luaL_setmetatable( L, "AudioStream" );
}

void uluaPushLight( lua_State* L, Light light ) {
	Light* lightP = lua_newuserdata( L, sizeof( Light ) );
	*lightP = light;
	luaCallLoad( "Light", lightP );
	luaL_setmetatable( L, "Light" );
}

void uluaPushMaterial( lua_State* L, Material material ) {
	Material* materialP = lua_newuserdata( L, sizeof( Material ) );
	*materialP = material;
	luaCallLoad( "Material", materialP );
	luaL_setmetatable( L, "Material" );
}

void uluaPushMesh( lua_State* L, Mesh mesh ) {
	Mesh* meshP = lua_newuserdata( L, sizeof( Mesh ) );
	*meshP = mesh;
	luaCallLoad( "Mesh", meshP );
	luaL_setmetatable( L, "Mesh" );
}

void uluaPushModel( lua_State* L, Model model ) {
	Model* modelP = lua_newuserdata( L, sizeof( Model ) );
	*modelP = model;
	luaCallLoad( "Model", modelP );
	luaL_setmetatable( L, "Model" );
}

void uluaPushModelAnimation( lua_State* L, ModelAnimation modelAnimation ) {
	ModelAnimation* modelAnimationP = lua_newuserdata( L, sizeof( ModelAnimation ) );
	*modelAnimationP = modelAnimation;
	luaCallLoad( "ModelAnimation", modelAnimationP );
	luaL_setmetatable( L, "ModelAnimation" );
}

void uluaPushModelSkeleton( lua_State* L, ModelSkeleton modelSkeleton ) {
	ModelSkeleton* modelSkeletonP = lua_newuserdata( L, sizeof( ModelSkeleton ) );
	*modelSkeletonP = modelSkeleton;
	luaCallLoad( "ModelSkeleton", modelSkeletonP );
	luaL_setmetatable( L, "ModelSkeleton" );
}

void uluaPushRLRenderBatch( lua_State* L, rlRenderBatch renderBatch ) {
	rlRenderBatch* renderBatchP = lua_newuserdata( L, sizeof( rlRenderBatch ) );
	*renderBatchP = renderBatch;
	luaCallLoad( "rlRenderBatch", renderBatchP );
	luaL_setmetatable( L, "rlRenderBatch" );
}

void uluaPushAutomationEvent( lua_State* L, AutomationEvent event ) {
	AutomationEvent* eventP = lua_newuserdata( L, sizeof( AutomationEvent ) );
	*eventP = event;
	luaCallLoad( "AutomationEvent", eventP );
	luaL_setmetatable( L, "AutomationEvent" );
}

void uluaPushAutomationEventList( lua_State* L, AutomationEventList eventList ) {
	AutomationEventList* eventListP = lua_newuserdata( L, sizeof( AutomationEventList ) );
	*eventListP = eventList;
	luaCallLoad( "AutomationEventList", eventListP );
	luaL_setmetatable( L, "AutomationEventList" );
}

/* Unload objects. */

void uluaUnloadBuffer( Buffer* buffer ) {
	luaCallUnload( "Buffer", buffer );
	unloadBuffer( buffer );
	memset( buffer, 0, sizeof( Buffer ) );
}

void uluaUnloadImage( Image* image ) {
	luaCallUnload( "Image", image );
	UnloadImage( *image );
	memset( image, 0, sizeof( Image ) );
}

void uluaUnloadTexture( Texture* texture ) {
	luaCallUnload( "Texture", texture );
	UnloadTexture( *texture );
	memset( texture, 0, sizeof( Texture ) );
}

void uluaUnloadRenderTexture( RenderTexture* renderTexture ) {
	luaCallUnload( "RenderTexture", renderTexture );
	UnloadRenderTexture( *renderTexture );
	memset( renderTexture, 0, sizeof( RenderTexture ) );
}

void uluaUnloadShader( Shader* shader ) {
	luaCallUnload( "Shader", shader );
	UnloadShader( *shader );
	memset( shader, 0, sizeof( Shader ) );
}

void uluaUnloadFont( Font* font ) {
	luaCallUnload( "Font", font );
	UnloadFont( *font );
	memset( font, 0, sizeof( Font ) );
}

void uluaUnloadGlyphInfo( GlyphInfo* glyph ) {
	luaCallUnload( "GlyphInfo", glyph );
	unloadGlyphInfo( glyph );
}

void uluaUnloadWave( Wave* wave ) {
	luaCallUnload( "Wave", wave );
	UnloadWave( *wave );
	memset( wave, 0, sizeof( Wave ) );
}

void uluaUnloadSound( Sound* sound ) {
	luaCallUnload( "Sound", sound );
	UnloadSound( *sound );
	memset( sound, 0, sizeof( Sound ) );
}

void uluaUnloadSoundAlias( Sound* alias ) {
	luaCallUnload( "SoundAlias", alias );
	UnloadSoundAlias( *alias );
	memset( alias, 0, sizeof( Sound ) );
}

void uluaUnloadMusic( Music* music ) {
	luaCallUnload( "Music", music );
	UnloadMusicStream( *music );
	memset( music, 0, sizeof( Music ) );
}

void uluaUnloadAudioStream( AudioStream* stream ) {
	luaCallUnload( "AudioStream", stream );
	UnloadAudioStream( *stream );
	memset( stream, 0, sizeof( AudioStream ) );
}

void uluaUnloadMaterial( Material* material, bool freeAll ) {
	luaCallUnload( "Material", material );
	if ( freeAll ) {
		UnloadMaterial( *material );
	}
	/* Custom UnloadMaterial if we don't want to free Shaders or Textures. */
	else {
		unloadMaterial( material );
	}
	memset( material, 0, sizeof( Material ) );
}

void uluaUnloadMesh( Mesh* mesh ) {
	luaCallUnload( "Mesh", mesh );
	UnloadMesh( *mesh );
	memset( mesh, 0, sizeof( Mesh ) );
}

void uluaUnloadModel( Model* model, bool freeAll ) {
	luaCallUnload( "Model", model );
	if ( freeAll ) {
		UnloadModel( *model );
	}
	/* Custom UnloadModel if we don't want to free Meshes or Materials. */
	else {
		unloadModel( model );
	}
	memset( model, 0, sizeof( Model ) );
}

void uluaUnloadModelAnimation( ModelAnimation* modelAnimation ) {
	luaCallUnload( "ModelAnimation", modelAnimation );
	unloadModelAnimation( *modelAnimation );
	memset( modelAnimation, 0, sizeof( ModelAnimation ) );
}

void uluaUnloadModelSkeleton( ModelSkeleton* modelSkeleton ) {
	luaCallUnload( "ModelSkeleton", modelSkeleton );
	unloadModelSkeleton( modelSkeleton );
	memset( modelSkeleton, 0, sizeof( ModelSkeleton ) );
}

void uluaUnloadRLRenderBatch( rlRenderBatch* renderBatch ) {
	luaCallUnload( "rlRenderBatch", renderBatch );
	rlUnloadRenderBatch( *renderBatch );
	memset( renderBatch, 0, sizeof( rlRenderBatch ) );
}

void uluaUnloadAutomationEventList( AutomationEventList* eventList ) {
	luaCallUnload( "AutomationEventList", eventList );
	UnloadAutomationEventList( *eventList );
	memset( eventList, 0, sizeof( AutomationEventList ) );
}

/* Utils. */

int uluaGetTableLen( lua_State* L, int index ) {
	luaL_checktype( L, index, LUA_TTABLE );
	int t = index, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		i++;
		lua_pop( L, 1 );
	}
	return i;
}

/* Accepts no arg and nil. */
bool uluaIsNil( lua_State* L, int index ) {
	return lua_type( L, index ) <= 0; /* -1 is no arg(nil) and 0 is nil. */
}
