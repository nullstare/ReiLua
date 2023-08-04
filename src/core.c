#include "main.h"
#include "state.h"
#include "core.h"
#include "textures.h"
#include "lua_core.h"

static void checkCamera2DRealloc( int i ) {
	if ( i == state->camera2DCount ) {
		state->camera2DCount++;
	}

	if ( state->camera2DCount == state->camera2DAlloc ) {
		state->camera2DAlloc += ALLOC_PAGE_SIZE;
		state->camera2Ds = realloc( state->camera2Ds, state->camera2DAlloc * sizeof( Camera2D* ) );

		for ( i = state->camera2DCount; i < state->camera2DAlloc; i++ ) {
			state->camera2Ds[i] = NULL;
		}
	}
}

static void checkCamera3DRealloc( int i ) {
	if ( i == state->camera3DCount ) {
		state->camera3DCount++;
	}

	if ( state->camera3DCount == state->camera3DAlloc ) {
		state->camera3DAlloc += ALLOC_PAGE_SIZE;
		state->camera3Ds = realloc( state->camera3Ds, state->camera3DAlloc * sizeof( Camera3D* ) );

		for ( i = state->camera3DCount; i < state->camera3DAlloc; i++ ) {
			state->camera3Ds[i] = NULL;
		}
	}
}

static void checkShaderRealloc( int i ) {
	if ( i == state->shaderCount ) {
		state->shaderCount++;
	}

	if ( state->shaderCount == state->shaderAlloc ) {
		state->shaderAlloc += ALLOC_PAGE_SIZE;
		state->shaders = realloc( state->shaders, state->shaderAlloc * sizeof( Shader* ) );

		for ( i = state->shaderCount; i < state->shaderAlloc; i++ ) {
			state->shaders[i] = NULL;
		}
	}
}

bool validShader( size_t id ) {
	if ( id < 0 || state->shaderCount < id || state->shaders[ id ] == NULL ) {
		TraceLog( state->logLevelInvalid, "%s %d", "Invalid shader", id );
		return false;
	}
	else {
		return true;
	}
}

/*
## Core - Window
*/

/*
> state = RL.IsWindowReady()

Check if window has been initialized successfully

- Success return bool
*/
int lcoreIsWindowReady( lua_State *L ) {
	lua_pushboolean( L, IsWindowReady() );

	return 1;
}

/*
> state = RL.IsWindowFullscreen()

Check if window is currently fullscreen

- Success return bool
*/
int lcoreIsWindowFullscreen( lua_State *L ) {
	lua_pushboolean( L, IsWindowFullscreen() );

	return 1;
}

/*
> state = RL.IsWindowHidden()

Check if window is currently hidden ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowHidden( lua_State *L ) {
	lua_pushboolean( L, IsWindowHidden() );

	return 1;
}

/*
> state = RL.IsWindowMinimized()

Check if window is currently minimized ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowMinimized( lua_State *L ) {
	lua_pushboolean( L, IsWindowMinimized() );

	return 1;
}

/*
> state = RL.IsWindowMaximized()

Check if window is currently maximized ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowMaximized( lua_State *L ) {
	lua_pushboolean( L, IsWindowMaximized() );

	return 1;
}

/*
> state = RL.IsWindowFocused()

Check if window is currently focused ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowFocused( lua_State *L ) {
	lua_pushboolean( L, IsWindowFocused() );

	return 1;
}

/*
> success = RL.SetWindowMonitor( int monitor )

Set monitor for the current window (fullscreen mode)

- Failure return false
- Success return true
*/
int lcoreSetWindowMonitor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowMonitor( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetWindowMonitor( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetWindowPosition( Vector2 pos )

Set window position on screen

- Failure return false
- Success return true
*/
int lcoreSetWindowPosition( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowPosition( Vector2 pos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2Index( L, 1 );

	SetWindowPosition( pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetWindowSize( Vector2 size )

Set window dimensions

- Failure return false
- Success return true
*/
int lcoreSetWindowSize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowSize( Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );

	SetWindowSize( (int)size.x, (int)size.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetWindowMinSize( Vector2 size )

Set window minimum dimensions ( for FLAG_WINDOW_RESIZABLE )

- Failure return false
- Success return true
*/
int lcoreSetWindowMinSize( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowMinSize( Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );

	SetWindowMinSize( (int)size.x, (int)size.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> position = RL.GetMonitorPosition( int monitor )

Get specified monitor position

- Failure return nil
- Success return Vector2
*/
int lcoreGetMonitorPosition( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMonitorPosition( int monitor )" );
		lua_pushnil( L );
		return 1;
	}
	int monitor = lua_tointeger( L, 1 );

	uluaPushVector2( L, GetMonitorPosition( monitor ) );

	return 1;
}

/*
> size = RL.GetMonitorSize( int monitor )

Get specified monitor size

- Failure return nil
- Success return Vector2
*/
int lcoreGetMonitorSize( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMonitorSize( int monitor )" );
		lua_pushnil( L );
		return 1;
	}
	int monitor = lua_tointeger( L, 1 );

	Vector2 size = (Vector2){ GetMonitorWidth( monitor ), GetMonitorHeight( monitor ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> position = RL.GetWindowPosition()

Get window position on monitor

- Success return Vector2
*/
int lcoreGetWindowPosition( lua_State *L ) {
	Vector2 pos = GetWindowPosition();
	uluaPushVector2( L, pos );

	return 1;
}

/*
> size = RL.GetScreenSize()

Get screen size

- Success return Vector2
*/
int lcoreGetScreenSize( lua_State *L ) {
	Vector2 size = (Vector2){ GetScreenWidth(), GetScreenHeight() };
	uluaPushVector2( L, size );

	return 1;
}

/*
> success = RL.SetWindowState( int flag )

Set window configuration state using flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return false
- Success return true
*/
int lcoreSetWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowState( int flags )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int flag = (unsigned int)lua_tointeger( L, 1 );

	SetWindowState( flag );
	lua_pushboolean( L, true );

	return 1;
}

/*
> state = RL.IsWindowState( int flag )

Check if one specific window flag is enabled ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return nil
- Success return bool
*/
int lcoreIsWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsWindowState( int flags )" );
		lua_pushnil( L );
		return 1;
	}
	unsigned int flag = (unsigned int)lua_tointeger( L, 1 );

	lua_pushboolean( L, IsWindowState( flag ) );

	return 1;
}

/*
> resized = RL.ClearWindowState( int flag )

Clear window configuration state flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Success return bool
*/
int lcoreClearWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.ClearWindowState( int flag )" );
		lua_pushnil( L );
		return 1;
	}
	unsigned int flag = (unsigned int)lua_tointeger( L, 1 );

	ClearWindowState( flag );

	return 1;
}

/*
> resized = RL.IsWindowResized()

Check if window has been resized from last frame

- Success return bool
*/
int lcoreIsWindowResized( lua_State *L ) {
	lua_pushboolean( L, IsWindowResized() );

	return 1;
}

/*
> success = RL.SetWindowIcon( Image image )

Set icon for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true
*/
int lcoreSetWindowIcon( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowIcon( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, 1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetWindowIcon( *state->images[ imageId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetWindowTitle( string title )

Set title for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true
*/
int lcoreSetWindowTitle( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetWindowTitle( string title )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetWindowTitle( lua_tostring( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> count = RL.GetMonitorCount()

Get number of connected monitors

- Success return int
*/
int lcoreGetMonitorCount( lua_State *L ) {
	lua_pushinteger( L, GetMonitorCount() );
	return 1;
}

/*
> monitor = RL.GetCurrentMonitor()

Get current connected monitor

- Success return int
*/
int lcoreGetCurrentMonitor( lua_State *L ) {
	lua_pushinteger( L, GetCurrentMonitor() );
	return 1;
}

/*
> size = RL.GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Failure return false
- Success return Vector2
*/
int lcoreGetMonitorPhysicalSize( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMonitorPhysicalSize( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int monitor = lua_tointeger( L, 1 );

	Vector2 size = { GetMonitorPhysicalWidth( monitor ), GetMonitorPhysicalHeight( monitor ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> size = RL.GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Failure return false
- Success return int
*/
int lcoreGetMonitorRefreshRate( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMonitorRefreshRate( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int monitor = lua_tointeger( L, 1 );
	
	lua_pushinteger( L, GetMonitorRefreshRate( monitor ) );

	return 1;
}

/*
> scale = RL.GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2
*/
int lcoreGetWindowScaleDPI( lua_State *L ) {
	uluaPushVector2( L, GetWindowScaleDPI() );

	return 1;
}

/*
> name = RL.GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the monitor

- Failure return false
- Success return string
*/
int lcoreGetMonitorName( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMonitorName( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int monitor = lua_tointeger( L, 1 );

	lua_pushstring( L, GetMonitorName( monitor ) );

	return 1;
}

/*
> RL.CloseWindow()

Close window and unload OpenGL context and free all resources
*/
int lcoreCloseWindow( lua_State *L ) {
	state->run = false;

	return 0;
}

/*
> success = RL.SetClipboardText( string text )

Set clipboard text content

- Failure return false
- Success return true
*/
int lcoreSetClipboardText( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetClipboardText( string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetClipboardText( lua_tostring( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> text = RL.GetClipboardText()

Get clipboard text content

- Success return string
*/
int lcoreGetClipboardText( lua_State *L ) {
	lua_pushstring( L, GetClipboardText() );
	return 1;
}

/*
## Core - Timing
*/

/*
> success = RL.SetTargetFPS( int fps )

Set target FPS ( maximum )

- Failure return false
- Success return true
*/
int lcoreSetTargetFPS( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetTargetFPS( int fps )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int fps = lua_tointeger( L, 1 );

	SetTargetFPS( fps );
	lua_pushboolean( L, true );

	return 1;
}

/*
> FPS = RL.GetFPS()

Get current FPS

- Success return int
*/
int lcoreGetFPS( lua_State *L ) {
	lua_pushinteger( L, GetFPS() );

	return 1;
}

/*
> delta = RL.GetFrameTime()

Get time in seconds for last frame drawn ( Delta time )

- Success return float
*/
int lcoreGetFrameTime( lua_State *L ) {
	lua_pushnumber( L, GetFrameTime() );

	return 1;
}

/*
> time = RL.GetTime()

Get elapsed time in seconds since InitWindow()

- Success return float
*/
int lcoreGetTime( lua_State *L ) {
	lua_pushnumber( L, GetTime() );

	return 1;
}

/*
## Core - Misc
*/

/*
> success = RL.TakeScreenshot( string fileName )

Takes a screenshot of current screen ( filename extension defines format )

- Failure return false
- Success return true
*/
int lcoreTakeScreenshot( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.TakeScreenshot( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	TakeScreenshot( lua_tostring( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetConfigFlags( int flags )

Setup init configuration flags ( view FLAGS )

- Failure return false
- Success return true
*/
int lcoreSetConfigFlags( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetConfigFlags( int flags )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int flag = (unsigned int)lua_tointeger( L, 1 );

	SetConfigFlags( flag );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.TraceLog( int logLevel, string text )

Show trace log messages ( LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR... )

- Failure return false
- Success return true
*/
int lcoreTraceLog( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.TraceLog( int logLevel, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int logLevel = lua_tointeger( L, 1 );

	TraceLog( logLevel, "%s", lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetTraceLogLevel( int logLevel )

Set the current threshold ( minimum ) log level

- Failure return false
- Success return true
*/
int lcoreSetTraceLogLevel( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetTraceLogLevel( int logLevel )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int logLevel = lua_tointeger( L, 1 );

	SetTraceLogLevel( logLevel );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetLogLevelInvalid( int logLevel )

Set the log level for bad function calls and invalid data formats.

- Failure return false
- Success return true
*/
int lcoreSetLogLevelInvalid( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetLogLevelInvalid( int logLevel )" );
		lua_pushboolean( L, false );
		return 1;
	}
	state->logLevelInvalid = lua_tointeger( L, 1 );

	lua_pushboolean( L, true );

	return 1;
}

/*
> logLevel = RL.GetLogLevelInvalid()

Get the log level for bad function calls and invalid data formats.

- Success return int
*/
int lcoreGetLogLevelInvalid( lua_State *L ) {
	lua_pushinteger( L, state->logLevelInvalid );

	return 1;
}

/*
> success = RL.OpenURL( string url )

Open URL with default system browser ( If available )

- Failure return false
- Success return true
*/
int lcoreOpenURL( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.OpenURL( string url )" );
		lua_pushboolean( L, false );
		return 1;
	}
	OpenURL( lua_tostring( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Cursor
*/

/*
> RL.ShowCursor()

Shows cursor
*/
int lcoreShowCursor( lua_State *L ) {
	ShowCursor();

	return 0;
}

/*
> RL.HideCursor()

Hides cursor
*/
int lcoreHideCursor( lua_State *L ) {
	HideCursor();

	return 0;
}

/*
> hidden = RL.IsCursorHidden()

Check if cursor is not visible

- Success return bool
*/
int lcoreIsCursorHidden( lua_State *L ) {
	lua_pushboolean( L, IsCursorHidden() );

	return 1;
}

/*
> RL.EnableCursor()

Enables cursor (unlock cursor)
*/
int lcoreEnableCursor( lua_State *L ) {
	EnableCursor();

	return 0;
}

/*
> RL.DisableCursor()

Disables cursor (lock cursor)
*/
int lcoreDisableCursor( lua_State *L ) {
	DisableCursor();

	return 0;
}

/*
> onSreen = RL.IsCursorOnScreen()

Check if cursor is on the screen

- Success return bool
*/
int lcoreIsCursorOnScreen( lua_State *L ) {
	lua_pushboolean( L, IsCursorOnScreen() );

	return 1;
}

/*
## Core - Drawing
*/

/*
> success = RL.ClearBackground( Color color )

Set background color ( framebuffer clear color )

- Failure return false
- Success return true
*/
int lcoreClearBackground( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.ClearBackground( Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColorIndex( L, 1 );

	ClearBackground( color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.BeginDrawing()

Setup canvas ( framebuffer ) to start drawing
*/
int lcoreBeginDrawing( lua_State *L ) {
	BeginDrawing();

	return 1;
}

/*
> RL.EndDrawing()

End canvas drawing and swap buffers ( double buffering )
*/
int lcoreEndDrawing( lua_State *L ) {
	EndDrawing();

	return 1;
}

/*
> success = RL.BeginBlendMode( int mode )

Begin blending mode ( BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED... )

- Failure return false
- Success return true
*/
int lcoreBeginBlendMode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.BeginBlendMode( int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int mode = lua_tointeger( L, 1 );

	BeginBlendMode( mode );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndBlendMode()

End blending mode ( reset to default: BLEND_ALPHA )
*/
int lcoreEndBlendMode( lua_State *L ) {
	EndBlendMode();
	
	return 1;
}

/*
> success = RL.BeginScissorMode( Rectangle rectange )

Begin scissor mode ( define screen area for following drawing )

- Failure return false
- Success return true
*/
int lcoreBeginScissorMode( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.BeginScissorMode( Rectangle rectange )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );

	BeginScissorMode( rect.x, rect.y, rect.width, rect.height );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndScissorMode()

End scissor mode
*/
int lcoreEndScissorMode( lua_State *L ) {
	EndScissorMode();

	return 1;
}

/*
## Core - Shader
*/

/*
> shader = RL.LoadShader( string vsFileName, string fsFileName )

Load shader from files and bind default locations.
NOTE: Set nil if no shader

- Failure return -1
- Success return int
*/
int lcoreLoadShader( lua_State *L ) {
	if ( !( lua_isstring( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isstring( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.LoadShader( string vsFileName, string fsFileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	char *vsFileName = NULL;
	char *fsFileName = NULL;

	if ( lua_isstring( L, 1 ) ) {
		if ( FileExists( lua_tostring( L, 1 ) ) ) {
			vsFileName = malloc( STRING_LEN * sizeof( char ) );
			strcpy( vsFileName, lua_tostring( L, 1 ) );
		}
	}
	if ( lua_isstring( L, 2 ) ) {
		if ( FileExists( lua_tostring( L, 2 ) ) ) {
			fsFileName = malloc( STRING_LEN * sizeof( char ) );
			strcpy( fsFileName, lua_tostring( L, 2 ) );
		}
	}

	int i = 0;

	for ( i = 0; i < state->shaderCount; i++ ) {
		if ( state->shaders[i] == NULL ) {
			break;
		}
	}
	state->shaders[i] = malloc( sizeof( Shader ) );
	*state->shaders[i] = LoadShader( vsFileName, fsFileName );
	lua_pushinteger( L, i );
	checkShaderRealloc( i );

	if ( vsFileName != NULL ) {
		free( vsFileName );
	}
	if ( fsFileName != NULL ) {
		free( fsFileName );
	}

	return 1;
}

/*
> shader = RL.LoadShaderFromMemory( string vsCode, string fsCode )

Load shader from code strings and bind default locations
NOTE: Set nil if no shader

- Failure return -1
- Success return int
*/

int lcoreLoadShaderFromMemory( lua_State *L ) {
	if ( !( lua_isstring( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isstring( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.LoadShaderFromMemory( string vsCode, string fsCode )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	char *vs = NULL;
	char *fs = NULL;

	if ( lua_isstring( L, 1 ) ) {
		size_t vsLen = uluaGetTableLenIndex( L, 1 ) + 1;

		vs = malloc( vsLen * sizeof( char ) );
		strcpy( vs, lua_tostring( L, 1 ) );
	}
	if ( lua_isstring( L, 2 ) ) {
		size_t fsLen = uluaGetTableLenIndex( L, 2 ) + 1;

		fs = malloc( fsLen * sizeof( char ) );
		strcpy( fs, lua_tostring( L, 2 ) );
	}

	int i = 0;

	for ( i = 0; i < state->shaderCount; i++ ) {
		if ( state->shaders[i] == NULL ) {
			break;
		}
	}
	state->shaders[i] = malloc( sizeof( Shader ) );
	*state->shaders[i] = LoadShaderFromMemory( vs, fs );
	lua_pushinteger( L, i );
	checkShaderRealloc( i );

	if ( vs != NULL ) {
		free( vs );
	}
	if ( fs != NULL ) {
		free( fs );
	}

	return 1;
}

/*
> success = RL.BeginShaderMode( Shader shader )

Begin custom shader drawing

- Failure return false
- Success return true
*/
int lcoreBeginShaderMode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.BeginShaderMode( Shader shader )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	
	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	BeginShaderMode( *state->shaders[ shaderId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndShaderMode()

End custom shader drawing ( use default shader )
*/
int lcoreEndShaderMode( lua_State *L ) {
	EndShaderMode();

	return 1;
}

/*
> location = RL.GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Failure return -1
- Success return int
*/
int lcoreGetShaderLocation( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetShaderLocation( Shader shader, string uniformName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );

	if ( !validShader( shaderId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	lua_pushinteger( L, GetShaderLocation( *state->shaders[ shaderId ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> location = RL.GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Failure return -1
- Success return int
*/
int lcoreGetShaderLocationAttrib( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetShaderLocationAttrib( Shader shader, string attribName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );

	if ( !validShader( shaderId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	lua_pushinteger( L, GetShaderLocationAttrib( *state->shaders[ shaderId ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )

Set shader location index

- Failure return false
- Success return true
*/
int lcoreSetShaderLocationIndex( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int shaderLocationIndex = lua_tointeger( L, 2 );
	int location = lua_tointeger( L, 3 );

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	state->shaders[ shaderId ]->locs[ shaderLocationIndex ] = location;
	lua_pushboolean( L, true );

	return 1;
}

/*
> location = RL.GetShaderLocationIndex( Shader shader, int shaderLocationIndex )

Get shader location index

- Failure return false
- Success return int
*/
int lcoreGetShaderLocationIndex( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetShaderLocationIndex( Shader shader, int shaderLocationIndex )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int shaderLocationIndex = lua_tointeger( L, 2 );

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, state->shaders[ shaderId ]->locs[ shaderLocationIndex ] );

	return 1;
}

/*
> success = RL.SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value ( matrix 4x4 )

- Failure return false
- Success return true
*/
int lcoreSetShaderValueMatrix( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int locIndex = lua_tointeger( L, 2 );
	Matrix mat = uluaGetMatrixIndex( L, 3 );

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetShaderValueMatrix( *state->shaders[ shaderId ], locIndex, mat );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )

Set shader uniform value for texture ( sampler2d )

- Failure return false
- Success return true
*/
int lcoreSetShaderValueTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !isValidTexture( L, 3, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int locIndex = lua_tointeger( L, 2 );
	Texture texture = uluaGetTexture( L, 3 );

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetShaderValueTexture( *state->shaders[ shaderId ], locIndex, texture );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table

- Failure return false
- Success return true
*/
int lcoreSetShaderValue( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int locIndex = lua_tointeger( L, 2 );
	size_t valueCount = uluaGetTableLenIndex( L, 3 );
	int uniformType = lua_tointeger( L, 4 );

	/* Read values. */
	float floats[ valueCount ];
	int ints[ valueCount ];

	/* t = values index. */
	int t = 3, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			floats[i] = lua_tonumber( L, -1 );
			ints[i] = lua_tointeger( L, -1 );
        }
        i++;
        lua_pop( L, 1 );
    }
	lua_pop( L, 1 );
	/* Read values end. */

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	if ( uniformType == SHADER_UNIFORM_FLOAT || uniformType == SHADER_UNIFORM_VEC2
	|| uniformType == SHADER_UNIFORM_VEC3 || uniformType == SHADER_UNIFORM_VEC4 ) {
		SetShaderValue( *state->shaders[ shaderId ], locIndex, floats, uniformType );
	}
	else {
		SetShaderValue( *state->shaders[ shaderId ], locIndex, ints, uniformType );
	}

	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table

- Failure return false
- Success return true
*/
int lcoreSetShaderValueV( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, 1 );
	int locIndex = lua_tointeger( L, 2 );
	size_t valueCount = uluaGetTableLenIndex( L, 3 );
	int uniformType = lua_tointeger( L, 4 );
	int count = lua_tointeger( L, 5 );

	/* Read values. */
	float floats[ valueCount * count ];
	int ints[ valueCount * count ];

	/* t = values index. */
	int t = 3, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			floats[i] = lua_tonumber( L, -1 );
			ints[i] = lua_tointeger( L, -1 );
        }
        i++;
        lua_pop( L, 1 );
    }
	lua_pop( L, 1 );
	/* Read values end. */

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	if ( uniformType == SHADER_UNIFORM_FLOAT || uniformType == SHADER_UNIFORM_VEC2
	|| uniformType == SHADER_UNIFORM_VEC3 || uniformType == SHADER_UNIFORM_VEC4 ) {
		SetShaderValueV( *state->shaders[ shaderId ], locIndex, floats, uniformType, count );
	}
	else {
		SetShaderValueV( *state->shaders[ shaderId ], locIndex, ints, uniformType, count );
	}
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.UnloadShader( Shader shader )

Unload shader from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int lcoreUnloadShader( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.UnloadShader( Shader shader )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, 1 );

	if ( !validShader( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadShader( *state->shaders[ id ] );
	state->shaders[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Input-related Keyboard
*/

/*
> pressed = RL.IsKeyPressed( int key )

Detect if a key has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsKeyPressed( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsKeyPressed( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsKeyPressed( key ) );

	return 1;
}

/*
> pressed = RL.IsKeyDown( int key )

Detect if a key is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsKeyDown( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsKeyDown( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsKeyDown( key ) );

	return 1;
}

/*
> released = RL.IsKeyReleased( int key )

Detect if a key has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsKeyReleased( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsKeyReleased( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsKeyReleased( key ) );

	return 1;
}

/*
> released = RL.IsKeyUp( int key )

Check if a key is NOT being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsKeyUp( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsKeyUp( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsKeyUp( key ) );

	return 1;
}

/*
> keycode = RL.GetKeyPressed()

Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetKeyPressed( lua_State *L ) {
	lua_pushinteger( L, GetKeyPressed() );

	return 1;
}

/*
> unicode = RL.GetCharPressed()

Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetCharPressed( lua_State *L ) {
	lua_pushinteger( L, GetCharPressed() );

	return 1;
}

/*
> RL.SetExitKey( int key )

Set a custom key to exit program ( default is ESC )
*/
int lcoreSetExitKey( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetExitKey( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	SetExitKey( key );

	return 1;
}

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

- Failure return -1
- Success return string or nil
*/
int lcoreGetKeyName( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetKeyName( int key, int scancode )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int key = lua_tointeger( L, 1 );
	int scancode = lua_tointeger( L, 2 );

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

- Failure return nil
- Success return int
*/
int lcoreGetKeyScancode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetKeyScancode( int key )" );
		lua_pushnil( L );
		return 1;
	}
	int key = lua_tointeger( L, 1 );

	lua_pushinteger( L, glfwGetKeyScancode( key ) );

	return 1;
}

/*
## Core - Input-related Gamepad
*/

/*
> available = RL.IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadAvailable( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsGamepadAvailable( int gamepad )" );
		lua_pushnil( L );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsGamepadAvailable( gamepad ) );

	return 1;
}

/*
> pressed = RL.IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonPressed( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsGamepadButtonPressed( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );
	int button = lua_tointeger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonPressed( gamepad, button ) );

	return 1;
}

/*
> pressed = RL.IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonDown( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsGamepadButtonDown( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );
	int button = lua_tointeger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonDown( gamepad, button ) );

	return 1;
}

/*
> released = RL.IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonReleased( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsGamepadButtonReleased( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );
	int button = lua_tointeger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonReleased( gamepad, button ) );

	return 1;
}

/*
> count = RL.GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Failure return false
- Success return int
*/
int lcoreGetGamepadAxisCount( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetGamepadAxisCount( int gamepad )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );

	lua_pushinteger( L, GetGamepadAxisCount( gamepad ) );

	return 1;
}

/*
> value = RL.GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Failure return false
- Success return float
*/
int lcoreGetGamepadAxisMovement( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetGamepadAxisMovement( int gamepad, int axis )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );
	int axis = lua_tointeger( L, 2 );

	lua_pushnumber( L, GetGamepadAxisMovement( gamepad, axis ) );

	return 1;
}

/*
> name = RL.GetGamepadName( int gamepad )

Return gamepad internal name id

- Failure return false
- Success return string
*/
int lcoreGetGamepadName( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetGamepadName( int gamepad )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int gamepad = lua_tointeger( L, 1 );

	lua_pushstring( L, GetGamepadName( gamepad ) );

	return 1;
}

/*
## Core - Input-related Mouse
*/

/*
> pressed = RL.IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonPressed( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsMouseButtonPressed( int button )" );
		lua_pushnil( L );
		return 1;
	}
	int button = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsMouseButtonPressed( button ) );

	return 1;
}

/*
> pressed = RL.IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonDown( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsMouseButtonDown( int button )" );
		lua_pushnil( L );
		return 1;
	}
	int button = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsMouseButtonDown( button ) );

	return 1;
}

/*
> released = RL.IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonReleased( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsMouseButtonReleased( int button )" );
		lua_pushnil( L );
		return 1;
	}
	int button = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsMouseButtonReleased( button ) );

	return 1;
}

/*
> released = RL.IsMouseButtonUp( int button )

Check if a mouse button is NOT being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonUp( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsMouseButtonUp( int button )" );
		lua_pushnil( L );
		return 1;
	}
	int button = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsMouseButtonUp( button ) );

	return 1;
}

/*
> position = RL.GetMousePosition()

Returns mouse position

- Success return Vector2
*/
int lcoreGetMousePosition( lua_State *L ) {
	uluaPushVector2( L, GetMousePosition() );
	return 1;
}

/*
> position = RL.GetMouseDelta()

Get mouse delta between frames

- Success return Vector2
*/
int lcoreGetMouseDelta( lua_State *L ) {
	uluaPushVector2( L, GetMouseDelta() );
	return 1;
}

/*
> success = RL.SetMousePosition( Vector2 position )

Set mouse position XY

- Failure return false
- Success return true
*/
int lcoreSetMousePosition( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetMousePosition( Vector2 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2Index( L, 1 );

	SetMousePosition( pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetMouseOffset( Vector2 offset )

Set mouse offset

- Failure return false
- Success return true
*/
int lcoreSetMouseOffset( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetMouseOffset( Vector2 offset )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 offset = uluaGetVector2Index( L, 1 );

	SetMouseOffset( offset.x, offset.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetMouseScale( Vector2 scale )

Set mouse scaling

- Failure return false
- Success return true
*/
int lcoreSetMouseScale( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetMouseScale( Vector2 scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 scale = uluaGetVector2Index( L, 1 );

	SetMouseScale( scale.x, scale.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> movement = RL.GetMouseWheelMove()

Returns mouse wheel movement Y

- Success return float
*/
int lcoreGetMouseWheelMove( lua_State *L ) {
	lua_pushnumber( L, GetMouseWheelMove() );
	return 1;
}

/*
> success = RL.SetMouseCursor( int cursor )

Set mouse cursor

- Failure return false
- Success return true
*/
int lcoreSetMouseCursor( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetMouseCursor( int cursor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int cursor = lua_tointeger( L, 1 );

	SetMouseCursor( cursor );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Input-related Touch
*/

/*
> position = RL.GetTouchPosition( int index )

Get touch position XY for a touch point index ( relative to screen size )

- Failure return false
- Success return Vector2
*/
int lcoreGetTouchPosition( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetTouchPosition( int index )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int index = lua_tointeger( L, 1 );

	uluaPushVector2( L, GetTouchPosition( index ) );

	return 1;
}

/*
> id = RL.GetTouchPointId( int index )

Get touch point identifier for given index

- Failure return false
- Success return int
*/
int lcoreGetTouchPointId( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetTouchPointId( int index )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int index = lua_tointeger( L, 1 );

	lua_pushinteger( L, GetTouchPointId( index ) );

	return 1;
}

/*
> count = RL.GetTouchPointCount()

Get touch point identifier for given index

- Success return int
*/
int lcoreGetTouchPointCount( lua_State *L ) {
	lua_pushinteger( L, GetTouchPointCount() );

	return 1;
}

/*
## Core - Input-related Gestures
*/

/*
> success = RL.SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags

- Failure return false
- Success return true
*/
int lcoreSetGesturesEnabled( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetGesturesEnabled( unsigned int flags )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int flags = (unsigned int)lua_tointeger( L, 1 );

	SetGesturesEnabled( flags );
	lua_pushboolean( L, true );

	return 1;
}

/*
> detected = RL.IsGestureDetected( int gesture )

Check if a gesture have been detected

- Failure return nil
- Success return bool
*/
int lcoreIsGestureDetected( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsGestureDetected( int gesture )" );
		lua_pushnil( L );
		return 1;
	}
	int gesture = lua_tointeger( L, 1 );

	lua_pushboolean( L, IsGestureDetected( gesture ) );

	return 1;
}

/*
> gesture = RL.GetGestureDetected()

Get latest detected gesture

- Success return int
*/
int lcoreGetGestureDetected( lua_State *L ) {
	lua_pushinteger( L, GetGestureDetected() );

	return 1;
}

/*
> time = RL.GetGestureHoldDuration()

Get gesture hold time in milliseconds

- Success return float
*/
int lcoreGetGestureHoldDuration( lua_State *L ) {
	lua_pushnumber( L, GetGestureHoldDuration() );

	return 1;
}

/*
> vector = RL.GetGestureDragVector()

Get gesture drag vector

- Success return Vector2
*/
int lcoreGetGestureDragVector( lua_State *L ) {
	uluaPushVector2( L, GetGestureDragVector() );

	return 1;
}

/*
> angle = RL.GetGestureDragAngle()

Get gesture drag angle

- Success return float
*/
int lcoreGetGestureDragAngle( lua_State *L ) {
	lua_pushnumber( L, GetGestureDragAngle() );

	return 1;
}

/*
> vector = RL.GetGesturePinchVector()

Get gesture pinch delta

- Success return Vector2
*/
int lcoreGetGesturePinchVector( lua_State *L ) {
	uluaPushVector2( L, GetGesturePinchVector() );

	return 1;
}

/*
> angle = RL.GetGesturePinchAngle()

Get gesture pinch angle

- Success return float
*/
int lcoreGetGesturePinchAngle( lua_State *L ) {
	lua_pushnumber( L, GetGesturePinchAngle() );

	return 1;
}

/*
## Core - File
*/

/*
> path = RL.GetBasePath()

Return game directory ( where main.lua is located )

- Success return string
*/
int lcoreGetBasePath( lua_State *L ) {
	lua_pushstring( L, state->exePath );

	return 1;
}

/*
> fileExists = RL.FileExists( string fileName )

Check if file exists

- Failure return nil
- Success return bool
*/
int lcoreFileExists( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.FileExists( string fileName )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, FileExists( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> dirExists = RL.DirectoryExists( string dirPath )

Check if a directory path exists

- Failure return nil
- Success return bool
*/
int lcoreDirectoryExists( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.DirectoryExists( string dirPath )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, DirectoryExists( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> hasFileExtension = RL.IsFileExtension( string fileName, string ext )

Check file extension ( Including point: .png, .wav )

- Failure return nil
- Success return bool
*/
int lcoreIsFileExtension( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsFileExtension( string fileName, string ext )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsFileExtension( lua_tostring( L, 1 ), lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> length = RL.GetFileLength( string fileName )

Get file length in bytes ( NOTE: GetFileSize() conflicts with windows.h )

- Failure return false
- Success return int
*/
int lcoreGetFileLength( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetFileLength( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetFileLength( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> extension = RL.GetFileExtension( string fileName )

Get pointer to extension for a filename string ( Includes dot: '.png' )

- Failure return false
- Success return string
*/
int lcoreGetFileExtension( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetFileExtension( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileExtension( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> filePath = RL.GetFileName( string filePath )

Get pointer to filename for a path string

- Failure return false
- Success return string
*/
int lcoreGetFileName( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetFileName( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileName( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> filePath = RL.GetFileNameWithoutExt( string filePath )

Get filename string without extension ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetFileNameWithoutExt( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetFileNameWithoutExt( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileNameWithoutExt( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> filePath = RL.GetDirectoryPath( string filePath )

Get full path for a given fileName with path ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetDirectoryPath( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetDirectoryPath( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetDirectoryPath( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> directory = RL.GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetPrevDirectoryPath( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetPrevDirectoryPath( string dirPath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetPrevDirectoryPath( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> directory = RL.GetWorkingDirectory()

Get current working directory ( Uses static string )

- Success return string
*/
int lcoreGetWorkingDirectory( lua_State *L ) {
	lua_pushstring( L, GetWorkingDirectory() );
	return 1;
}

/*
> fileNames = RL.LoadDirectoryFiles( string dirPath )

Load directory filepaths

- Failure return false
- Success return string{}
*/
int lcoreLoadDirectoryFiles( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.LoadDirectoryFiles( string dirPath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	FilePathList files = LoadDirectoryFiles( lua_tostring( L, 1 ) );

	lua_createtable( L, files.count, 0 );

	for ( int i = 0; i < files.count; ++i ) {
		lua_pushstring( L, files.paths[i] );
    	lua_rawseti( L, -2, i+1 );
	}
	UnloadDirectoryFiles( files );

	return 1;
}

/*
> fileNames = RL.LoadDirectoryFilesEx( string basePath, string filter, bool scanSubdirs )

Load directory filepaths with extension filtering and recursive directory scan

- Failure return false
- Success return string{}
*/
int lcoreLoadDirectoryFilesEx( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.LoadDirectoryFilesEx( string dirPath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	bool scanSubdirs = lua_toboolean( L, 3 );

	FilePathList files = LoadDirectoryFilesEx( lua_tostring( L, 1 ), lua_tostring( L, 2 ), scanSubdirs );

	lua_createtable( L, files.count, 0 );

	for ( int i = 0; i < files.count; ++i ) {
		lua_pushstring( L, files.paths[i] );
    	lua_rawseti( L, -2, i+1 );
	}
	UnloadDirectoryFiles( files );

	return 1;
}

/*
> success = RL.ChangeDirectory( string directory )

Change working directory, return true on success

- Failure return false
- Success return true
*/
int lcoreChangeDirectory( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.ChangeDirectory( string directory )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ChangeDirectory( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> isFile = RL.IsPathFile( string path )

Check if a given path is a file or a directory

- Failure return nil
- Success return bool
*/
int lcoreIsPathFile( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.IsPathFile( string path )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsPathFile( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
> fileDropped = RL.IsFileDropped()

Check if a file has been dropped into window

- Success return bool
*/
int lcoreIsFileDropped( lua_State *L ) {
	lua_pushboolean( L, IsFileDropped() );
	return 1;
}

/*
> files = RL.LoadDroppedFiles()

Load dropped filepaths

- Success return string{}
*/
int lcoreLoadDroppedFiles( lua_State *L ) {
	FilePathList files = LoadDroppedFiles();

	lua_createtable( L, files.count, 0 );

	for ( int i = 0; i < files.count; ++i ) {
		lua_pushstring( L, files.paths[i] );
		lua_rawseti( L, -2, i+1 );
	}
	UnloadDroppedFiles( files );

	return 1;
}

/*
> time = RL.GetFileModTime( string fileName )

Get file modification time ( Last write time )

- Failure return false
- Success return int
*/
int lcoreGetFileModTime( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetFileModTime( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetFileModTime( lua_tostring( L, 1 ) ) );

	return 1;
}

/*
## Core - Camera2D
*/

/*
> camera2D = RL.CreateCamera2D()

Return camera2D id set to default configuration

- Success return int
*/
int lcoreCreateCamera2D( lua_State *L ) {
	int i = 0;

	for ( i = 0; i < state->camera2DCount; i++ ) {
		if ( state->camera2Ds[i] == NULL ) {
			break;
		}
	}
	state->camera2Ds[i] = malloc( sizeof( Camera2D ) );
	state->camera2Ds[i]->offset = (Vector2){ 0.0, 0.0 };
	state->camera2Ds[i]->target = (Vector2){ 0.0, 0.0 };
	state->camera2Ds[i]->rotation = 0.0;
	state->camera2Ds[i]->zoom = 1.0;

	lua_pushinteger( L, i );
	checkCamera2DRealloc(i);

	return 1;
}

/*
> success = RL.UnloadCamera2D( camera2D camera )

Unload Camera2D

- Failure return false
- Success return true
*/
int lcoreUnloadCamera2D( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.UnloadCamera2D( int Camera2D )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	free( state->camera2Ds[ cameraId ] );
	state->camera2Ds[ cameraId ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.BeginMode2D( camera2D camera )

Begin 2D mode with custom camera ( 2D )

- Failure return false
- Success return true
*/
int lcoreBeginMode2D( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.BeginMode2D( camera2D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera2D camera = uluaGetCamera2D( L, 1 );

	BeginMode2D( camera );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndMode2D()

Ends 2D mode with custom camera
*/
int lcoreEndMode2D( lua_State *L ) {
	EndMode2D();

	return 1;
}

/*
> success = RL.SetCamera2DTarget( camera2D camera, Vector2 target )

Set camera target ( rotation and zoom origin )

- Failure return false
- Success return true
*/
int lcoreSetCamera2DTarget( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera2DTarget( camera2D camera, Vector2 target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector2 target = uluaGetVector2Index( L, 2 );

	state->camera2Ds[ cameraId ]->target = target;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera2DOffset( camera2D camera, Vector2 offset )

Set camera offset ( displacement from target )

- Failure return false
- Success return true
*/
int lcoreSetCamera2DOffset( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera2DOffset( camera2D camera, Vector2 offset )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector2 offset = uluaGetVector2Index( L, 2 );

	state->camera2Ds[ cameraId ]->offset = offset;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera2DRotation( camera2D camera, float rotation )

Set camera rotation in degrees

- Failure return false
- Success return true
*/
int lcoreSetCamera2DRotation( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera2DRotation( camera2D camera, float rotation )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float rotation = lua_tonumber( L, 2 );

	state->camera2Ds[ cameraId ]->rotation = rotation;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera2DZoom( camera2D camera, float zoom )

Set camera zoom ( scaling ), should be 1.0f by default

- Failure return false
- Success return true
*/
int lcoreSetCamera2DZoom( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera2DZoom( camera2D camera, float zoom )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float zoom = lua_tonumber( L, 2 );

	state->camera2Ds[ cameraId ]->zoom = zoom;
	lua_pushboolean( L, true );

	return 1;
}

/*
> target = RL.GetCamera2DTarget( camera2D camera )

Get camera2D target

- Failure return nil
- Success return Vector2
*/
int lcoreGetCamera2DTarget( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera2DTarget( camera2D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	uluaPushVector2( L, state->camera2Ds[ cameraId ]->target );

	return 1;
}

/*
> offset = RL.GetCamera2DOffset( camera2D camera )

Get camera2D offset

- Failure return nil
- Success return Vector2
*/
int lcoreGetCamera2DOffset( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera2DOffset( camera2D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	uluaPushVector2( L, state->camera2Ds[ cameraId ]->offset );

	return 1;
}

/*
> rotation = RL.GetCamera2DRotation( camera2D camera )

Get camera2D rotation

- Failure return nil
- Success return float
*/
int lcoreGetCamera2DRotation( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera2DRotation( camera2D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	lua_pushnumber( L, state->camera2Ds[ cameraId ]->rotation );

	return 1;
}

/*
> zoom = RL.GetCamera2DZoom( camera2D camera )

Get camera2D zoom

- Failure return nil
- Success return float
*/
int lcoreGetCamera2DZoom( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera2DZoom( camera2D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	lua_pushnumber( L, state->camera2Ds[ cameraId ]->zoom );

	return 1;
}

/*
## Core - Camera3D
*/

/*
> camera = RL.CreateCamera3D()

Return camera3D id set to default configuration

- Success return int
*/
int lcoreCreateCamera3D( lua_State *L ) {
	int i = 0;

	for ( i = 0; i < state->camera3DCount; i++ ) {
		if ( state->camera3Ds[i] == NULL ) {
			break;
		}
	}
	state->camera3Ds[i] = malloc( sizeof( Camera3D ) );
	state->camera3Ds[i]->position = (Vector3){ 0.0, 0.0, 0.0 };
	state->camera3Ds[i]->target = (Vector3){ 0.0, 0.0, 0.0 };
	state->camera3Ds[i]->up = (Vector3){ 0.0, 0.0, 0.0 };
	state->camera3Ds[i]->fovy = 45.0f;
	state->camera3Ds[i]->projection = CAMERA_PERSPECTIVE;

	lua_pushinteger( L, i );
	checkCamera3DRealloc(i);

	return 1;
}

/*
> success = RL.UnloadCamera3D( int Camera3D )

Unload Camera3D

- Failure return false
- Success return true
*/
int lcoreUnloadCamera3D( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.UnloadCamera3D( int Camera3D )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	free( state->camera3Ds[ cameraId ] );
	state->camera3Ds[ cameraId ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.BeginMode3D( camera3D camera )

Begin 3D mode with custom camera ( 3D )

- Failure return false
- Success return true
*/
int lcoreBeginMode3D( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.BeginMode3D( camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera3D camera = uluaGetCamera3D( L, 1 );

	BeginMode3D( camera );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode
*/
int lcoreEndMode3D( lua_State *L ) {
	EndMode3D();

	return 1;
}

/*
> success = RL.SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position ( Remember to call "RL.UpdateCamera3D()" to apply changes )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DPosition( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera3DPosition( camera3D camera, Vector3 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector3 pos = uluaGetVector3Index( L, 2 );

	state->camera3Ds[ cameraId ]->position = pos;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at

- Failure return false
- Success return true
*/
int lcoreSetCamera3DTarget( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera3DTarget( camera3D camera, Vector3 target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector3 target = uluaGetVector3Index( L, 2 );

	state->camera3Ds[ cameraId ]->target = target;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector ( Rotation over it's axis )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DUp( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_istable( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera3DUp( camera3D camera, Vector3 up )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector3 up = uluaGetVector3Index( L, 2 );

	state->camera3Ds[ cameraId ]->up = up;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera3DFovy( camera3D camera, float fovy )

Set camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return false
- Success return true
*/
int lcoreSetCamera3DFovy( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera3DFovy( camera3D camera, float fovy )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float fovy = lua_tonumber( L, 2 );

	state->camera3Ds[ cameraId ]->fovy = fovy;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode ( CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DProjection( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.SetCamera3DProjection( camera3D camera, int projection )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	int projection = lua_tointeger( L, 2 );

	state->camera3Ds[ cameraId ]->projection = projection;
	lua_pushboolean( L, true );

	return 1;
}

/*
> position = RL.GetCamera3DPosition( camera3D camera )

Get camera position

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DPosition( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DPosition( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->position );

	return 1;
}

/*
> target = RL.GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DTarget( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DTarget( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->target );

	return 1;
}

/*
> up = RL.GetCamera3DUp( camera3D camera )

Get camera up vector ( Rotation over it's axis )

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DUp( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DUp( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->up );

	return 1;
}

/*
> fovy = RL.GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return nil
- Success return float
*/
int lcoreGetCamera3DFovy( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DFovy( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	lua_pushnumber( L, state->camera3Ds[ cameraId ]->fovy );

	return 1;
}

/*
> projection = RL.GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Failure return nil
- Success return int
*/
int lcoreGetCamera3DProjection( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DProjection( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	lua_pushinteger( L, state->camera3Ds[ cameraId ]->projection );

	return 1;
}

/*
> forward = RL.GetCamera3DForward( camera3D camera )

Returns the cameras forward vector ( normalized )

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DForward( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DForward( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	Camera3D camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, GetCameraForward( &camera ) );

	return 1;
}

/*
> up = RL.GetCamera3DUpNormalized( camera3D camera )

Returns the cameras up vector ( normalized )
Note: The up vector might not be perpendicular to the forward vector

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DUpNormalized( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DUpNormalized( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	uluaPushVector3( L, GetCameraUp( state->camera3Ds[ cameraId ] ) );

	return 1;
}

/*
> right = RL.GetCamera3DRight( camera3D camera )

Returns the cameras right vector ( normalized )

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DRight( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DRight( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );

	uluaPushVector3( L, GetCameraRight( state->camera3Ds[ cameraId ] ) );

	return 1;
}

/*
> success = RL.Camera3DMoveForward( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera in it's forward direction

- Failure return false
- Success return true
*/
int lcoreCamera3DMoveForward( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DRight( camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float distance = lua_tonumber( L, 2 );
	bool moveInWorldPlane = lua_toboolean( L, 3 );

	CameraMoveForward( state->camera3Ds[ cameraId ], distance, moveInWorldPlane );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DMoveUp( camera3D camera, float distance )

Moves the camera in it's up direction

- Failure return false
- Success return true
*/
int lcoreCamera3DMoveUp( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DMoveUp( camera3D camera, float distance )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float distance = lua_tonumber( L, 2 );

	CameraMoveUp( state->camera3Ds[ cameraId ], distance );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DMoveRight( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera target in it's current right direction

- Failure return false
- Success return true
*/
int lcoreCamera3DMoveRight( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DMoveRight( camera3D camera, float distance, bool moveInWorldPlane )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float distance = lua_tonumber( L, 2 );
	bool moveInWorldPlane = lua_toboolean( L, 3 );

	CameraMoveRight( state->camera3Ds[ cameraId ], distance, moveInWorldPlane );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DMoveToTarget( camera3D camera, float delta )

Moves the camera position closer/farther to/from the camera target

- Failure return false
- Success return true
*/
int lcoreCamera3DMoveToTarget( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DMoveToTarget( camera3D camera, float delta )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float delta = lua_tonumber( L, 2 );

	CameraMoveToTarget( state->camera3Ds[ cameraId ], delta );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )

Rotates the camera around it's up vector
Yaw is "looking left and right"
If rotateAroundTarget is false, the camera rotates around it's position
Note: angle must be provided in radians

- Failure return false
- Success return true
*/
int lcoreCamera3DYaw( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float delta = lua_tonumber( L, 2 );
	bool rotateAroundTarget = lua_toboolean( L, 3 );

	CameraYaw( state->camera3Ds[ cameraId ], delta, rotateAroundTarget );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DPitch( camera3D camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp )

Rotates the camera around it's right vector, pitch is "looking up and down"
 - lockView prevents camera overrotation (aka "somersaults")
 - rotateAroundTarget defines if rotation is around target or around it's position
 - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
NOTE: angle must be provided in radians

- Failure return false
- Success return true
*/
int lcoreCamera3DPitch( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) || !lua_isboolean( L, 3 )
	|| !lua_isboolean( L, 4 ) || !lua_isboolean( L, 5 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float delta = lua_tonumber( L, 2 );
	bool lockView = lua_toboolean( L, 3 );
	bool rotateAroundTarget = lua_toboolean( L, 4 );
	bool rotateUp = lua_toboolean( L, 5 );

	CameraPitch( state->camera3Ds[ cameraId ], delta, lockView, rotateAroundTarget, rotateUp );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.Camera3DRoll( camera3D camera, float angle )

Rotates the camera around it's forward vector
Roll is "turning your head sideways to the left or right"
Note: angle must be provided in radians

- Failure return false
- Success return true
*/
int lcoreCamera3DRoll( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.Camera3DRoll( camera3D camera, float angle )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	float angle = lua_tonumber( L, 2 );

	CameraRoll( state->camera3Ds[ cameraId ], angle );
	lua_pushboolean( L, true );

	return 1;
}

/*
> view = RL.GetCamera3DViewMatrix( camera3D camera )

Returns the camera view matrix

- Failure return false
- Success return Matrix
*/
int lcoreGetCamera3DViewMatrix( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DViewMatrix( camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera3D camera = uluaGetCamera3D( L, 1 );

	uluaPushMatrix( L, GetCameraViewMatrix( &camera ) );

	return 1;
}

/*
> projection = RL.GetCamera3DProjectionMatrix( camera3D camera, float aspect )

Returns the camera projection matrix

- Failure return false
- Success return Matrix
*/
int lcoreGetCamera3DProjectionMatrix( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCamera3DProjectionMatrix( camera3D camera, float aspect )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera3D camera = uluaGetCamera3D( L, 1 );
	float aspect = lua_tonumber( L, 2 );

	uluaPushMatrix( L, GetCameraProjectionMatrix( &camera, aspect ) );

	return 1;
}

/*
> success = RL.UpdateCamera3D( camera3D camera, int mode )

Update camera position for selected mode

- Failure return false
- Success return true
*/
int lcoreUpdateCamera3D( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.UpdateCamera3D( camera3D camera, int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	int mode = lua_tointeger( L, 2 );

	UpdateCamera( state->camera3Ds[ cameraId ], mode );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.UpdateCamera3DPro( camera3D camera, Vector3 movement, Vector3 rotation, float zoom )

Update camera movement, movement/rotation values should be provided by user

- Failure return false
- Success return true
*/
int lcoreUpdateCamera3DPro( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, false ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.UpdateCamera3DPro( camera3D camera, Vector3 movement, Vector3 rotation, float zoom )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, 1 );
	Vector3 movement = uluaGetVector3Index( L, 2 );
	Vector3 rotation = uluaGetVector3Index( L, 3 );
	float zoom = lua_tointeger( L, 4 );

	UpdateCameraPro( state->camera3Ds[ cameraId ], movement, rotation, zoom );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Screen-space
*/

/*
> ray = RL.GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Failure return false
- Success return Ray
*/
int lcoreGetMouseRay( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !isValidCamera3D( L, 2, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetMouseRay( Vector2 mousePosition, Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 mousePosition = uluaGetVector2Index( L, 1 );
	Camera3D camera = uluaGetCamera3D( L, 2 );

	uluaPushRay( L, GetMouseRay( mousePosition, camera ) );

	return 1;
}

/*
> matrix = RL.GetCameraMatrix( Camera3D camera )

Get camera transform matrix ( view matrix )

- Failure return false
- Success return Matrix
*/
int lcoreGetCameraMatrix( lua_State *L ) {
	if ( !isValidCamera3D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCameraMatrix( Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera3D camera = uluaGetCamera3D( L, 1 );

	uluaPushMatrix( L, GetCameraMatrix( camera ) );

	return 1;
}

/*
> matrix = RL.GetCameraMatrix2D( Camera2D camera )

Get camera 2d transform matrix

- Failure return false
- Success return Matrix
*/
int lcoreGetCameraMatrix2D( lua_State *L ) {
	if ( !isValidCamera2D( L, 1, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetCameraMatrix2D( Camera2D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Camera2D camera = uluaGetCamera2D( L, 1 );
	uluaPushMatrix( L, GetCameraMatrix2D( camera ) );

	return 1;
}

/*
> position = RL.GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Failure return false
- Success return Vector2
*/
int lcoreGetWorldToScreen( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !isValidCamera3D( L, 2, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetWorldToScreen( Vector3 position, Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 position = uluaGetVector3Index( L, 1 );
	Camera3D camera = uluaGetCamera3D( L, 2 );

	uluaPushVector2( L, GetWorldToScreen( position, camera ) );

	return 1;
}

/*
> position = RL.GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )

Get size position for a 3d world space position

- Failure return false
- Success return Vector2
*/
int lcoreGetWorldToScreenEx( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !isValidCamera3D( L, 2, true ) || !lua_istable( L, 3 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 position = uluaGetVector3Index( L, 1 );
	Camera3D camera = uluaGetCamera3D( L, 2 );
	Vector2 size = uluaGetVector2Index( L, 3 );

	uluaPushVector2( L, GetWorldToScreenEx( position, camera, size.x, size.y ) );

	return 1;
}

/*
> position = RL.GetWorldToScreen2D( Vector2 position, Camera2D camera )

Get the screen space position for a 2d camera world space position

- Failure return false
- Success return Vector2
*/
int lcoreGetWorldToScreen2D( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !isValidCamera2D( L, 2, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetWorldToScreen2D( Vector2 position, Camera2D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 position = uluaGetVector2Index( L, 1 );
	Camera2D camera = uluaGetCamera2D( L, 1 );

	uluaPushVector2( L, GetWorldToScreen2D( position, camera ) );

	return 1;
}

/*
> position = RL.GetScreenToWorld2D( Vector2 position, Camera2D camera )

Get the world space position for a 2d camera screen space position

- Failure return false
- Success return Vector2
*/
int lcoreGetScreenToWorld2D( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !isValidCamera2D( L, 2, true ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.GetScreenToWorld2D( Vector2 position, Camera2D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 position = uluaGetVector2Index( L, 1 );
	Camera2D camera = uluaGetCamera2D( L, 1 );

	uluaPushVector2( L, GetScreenToWorld2D( position, camera ) );

	return 1;
}
