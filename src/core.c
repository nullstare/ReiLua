#include "main.h"
#include "state.h"
#include "core.h"
#include "textures.h"
#include "lua_core.h"

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

bool validCamera3D( size_t id ) {
	if ( id < 0 || state->camera3DCount < id || state->camera3Ds[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid camera", id );
		return false;
	}
	else {
		return true;
	}
}

static inline bool validShader( size_t id ) {
	if ( id < 0 || state->shaderCount < id || state->shaders[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid shader", id );
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
> state = RL_IsWindowReady()

Check if window has been initialized successfully

- Success return bool
*/
int lcoreIsWindowReady( lua_State *L ) {
	lua_pushboolean( L, IsWindowReady() );

	return 1;
}

/*
> state = RL_IsWindowFullscreen()

Check if window is currently fullscreen

- Success return bool
*/
int lcoreIsWindowFullscreen( lua_State *L ) {
	lua_pushboolean( L, IsWindowFullscreen() );

	return 1;
}

/*
> state = RL_IsWindowHidden()

Check if window is currently hidden ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowHidden( lua_State *L ) {
	lua_pushboolean( L, IsWindowHidden() );

	return 1;
}

/*
> state = RL_IsWindowMinimized()

Check if window is currently minimized ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowMinimized( lua_State *L ) {
	lua_pushboolean( L, IsWindowMinimized() );

	return 1;
}

/*
> state = RL_IsWindowMaximized()

Check if window is currently maximized ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowMaximized( lua_State *L ) {
	lua_pushboolean( L, IsWindowMaximized() );

	return 1;
}

/*
> state = RL_IsWindowFocused()

Check if window is currently focused ( only PLATFORM_DESKTOP )

- Success return bool
*/
int lcoreIsWindowFocused( lua_State *L ) {
	lua_pushboolean( L, IsWindowFocused() );

	return 1;
}

/*
> success = RL_SetWindowMonitor( int monitor )

Set monitor for the current window (fullscreen mode)

- Failure return false
- Success return true
*/
int lcoreSetWindowMonitor( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowMonitor( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetWindowMonitor( lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );
	return 1;
}

/*
> success = RL_SetWindowPosition( Vector2 pos )

Set window position on screen

- Failure return false
- Success return true
*/
int lcoreSetWindowPosition( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowPosition( Vector2 pos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2( L );

	SetWindowPosition( pos.x, pos.y );
	lua_pushboolean( L, true );
	return 1;
}

/*
> success = RL_SetWindowSize( Vector2 size )

Set window dimensions

- Failure return false
- Success return true
*/
int lcoreSetWindowSize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowSize( Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 size = uluaGetVector2( L );

	SetWindowSize( (int)size.x, (int)size.y );
	lua_pushboolean( L, true );
	return 1;
}

/*
> success = RL_SetWindowMinSize( Vector2 size )

Set window minimum dimensions ( for FLAG_WINDOW_RESIZABLE )

- Failure return false
- Success return true
*/
int lcoreSetWindowMinSize( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowMinSize( Vector2 size )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 size = uluaGetVector2( L );

	SetWindowMinSize( (int)size.x, (int)size.y );
	lua_pushboolean( L, true );
	return 1;
}

/*
> position = RL_GetMonitorPosition( int monitor )

Get specified monitor position

- Failure return nil
- Success return Vector2
*/
int lcoreGetMonitorPosition( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMonitorPosition( int monitor )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 pos = GetMonitorPosition( lua_tointeger( L, -1 ) );
	uluaPushVector2( L, pos );

	return 1;
}

/*
> size = RL_GetMonitorSize( int monitor )

Get specified monitor size

- Failure return nil
- Success return Vector2
*/
int lcoreGetMonitorSize( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMonitorSize( int monitor )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 size = (Vector2){ GetMonitorWidth( lua_tointeger( L, -1 ) ), GetMonitorHeight( lua_tointeger( L, -1 ) ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> position = RL_GetWindowPosition()

Get window position on monitor

- Success return Vector2
*/
int lcoreGetWindowPosition( lua_State *L ) {
	Vector2 pos = GetWindowPosition();
	uluaPushVector2( L, pos );

	return 1;
}

/*
> size = RL_GetWindowPosition()

Get window size

- Success return Vector2
*/
int lcoreGetWindowSize( lua_State *L ) {
	Vector2 size = (Vector2){ GetScreenWidth(), GetScreenHeight() };
	uluaPushVector2( L, size );

	return 1;
}

/*
> success = RL_SetWindowState( int flag )

Set window configuration state using flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return false
- Success return true
*/
int lcoreSetWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowState( int flags )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetWindowState( (unsigned int)lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );
	return 1;
}

/*
> state = RL_IsWindowState( int flag ) )

Check if one specific window flag is enabled ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return nil
- Success return bool
*/
int lcoreIsWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsWindowState( int flags )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsWindowState( (unsigned int)lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> resized = RL_ClearWindowState( int flag )

Clear window configuration state flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Success return bool
*/
int lcoreClearWindowState( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ClearWindowState( int flag )" );
		lua_pushnil( L );
		return 1;
	}
	ClearWindowState( (unsigned int)lua_tointeger( L, -1 ) );

	return 1;
}

/*
> resized = RL_IsWindowResized()

Check if window has been resized from last frame

- Success return bool
*/
int lcoreIsWindowResized( lua_State *L ) {
	lua_pushboolean( L, IsWindowResized() );

	return 1;
}

/*
> success = RL_SetWindowIcon( Image image )

Set icon for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true
*/
int lcoreSetWindowIcon( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowIcon( Image image )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t imageId = lua_tointeger( L, -1 );

	if ( !validImage( imageId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetWindowIcon( *state->images[ imageId ] );
	lua_pushboolean( L, true );
	return 1;
}

/*
> success = RL_SetWindowTitle( string title )

Set title for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true
*/
int lcoreSetWindowTitle( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetWindowTitle( string title )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetWindowTitle( lua_tostring( L, -1 ) );
	lua_pushboolean( L, true );
	return 1;
}

/*
> count = RL_GetMonitorCount()

Get number of connected monitors

- Success return int
*/
int lcoreGetMonitorCount( lua_State *L ) {
	lua_pushinteger( L, GetMonitorCount() );
	return 1;
}

/*
> monitor = RL_GetCurrentMonitor()

Get current connected monitor

- Success return int
*/
int lcoreGetCurrentMonitor( lua_State *L ) {
	lua_pushinteger( L, GetCurrentMonitor() );
	return 1;
}

/*
> size = RL_GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Failure return false
- Success return Vector2
*/
int lcoreGetMonitorPhysicalSize( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMonitorPhysicalSize( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int monitor = lua_tointeger( L, -1 );
	Vector2 size = { GetMonitorPhysicalWidth( monitor ), GetMonitorPhysicalHeight( monitor ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> size = RL_GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Failure return false
- Success return int
*/
int lcoreGetMonitorRefreshRate( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMonitorRefreshRate( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetMonitorRefreshRate( lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> scale = RL_GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2
*/
int lcoreGetWindowScaleDPI( lua_State *L ) {
	uluaPushVector2( L, GetWindowScaleDPI() );

	return 1;
}

/*
> name = RL_GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the monitor

- Failure return false
- Success return string
*/
int lcoreGetMonitorName( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMonitorName( int monitor )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetMonitorName( lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> RL_CloseWindow()

Close window and unload OpenGL context and free all resources
*/
int lcoreCloseWindow( lua_State *L ) {
	state->run = false;

	return 0;
}

/*
> success = RL_SetClipboardText( string text )

Set clipboard text content

- Failure return false
- Success return true
*/
int lcoreSetClipboardText( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetClipboardText( string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetClipboardText( lua_tostring( L, -1 ) );
	lua_pushboolean( L, true );
	return 1;
}

/*
> text = RL_GetClipboardText()

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
> success = RL_SetTargetFPS( int fps )

Set target FPS ( maximum )

- Failure return false
- Success return true
*/
int lcoreSetTargetFPS( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetTargetFPS( int fps )" );
		lua_pushboolean( L, false );
		return 1;
	}

	SetTargetFPS( lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );
	return 1;
}

/*
> delta = RL_GetFrameTime()

Get time in seconds for last frame drawn ( Delta time )

- Success return float
*/
int lcoreGetFrameTime( lua_State *L ) {
	lua_pushnumber( L, GetFrameTime() );

	return 1;
}

/*
> time = RL_GetTime()

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
> success = RL_TraceLog( int logLevel, string text )

Show trace log messages ( LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR... )

- Failure return false
- Success return true
*/
int lcoreTraceLog( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_TraceLog( int logLevel, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	TraceLog( lua_tointeger( L, -2 ), "%s", lua_tostring( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_OpenURL( string url )

Open URL with default system browser ( If available )

- Failure return false
- Success return true
*/
int lcoreOpenURL( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_OpenURL( string url )" );
		lua_pushboolean( L, false );
		return 1;
	}
	OpenURL( lua_tostring( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Cursor
*/

/*
> RL_ShowCursor()

Shows cursor
*/
int lcoreShowCursor( lua_State *L ) {
	ShowCursor();

	return 0;
}

/*
> RL_HideCursor()

Hides cursor
*/
int lcoreHideCursor( lua_State *L ) {
	HideCursor();

	return 0;
}

/*
> hidden = RL_IsCursorHidden()

Check if cursor is not visible

- Success return bool
*/
int lcoreIsCursorHidden( lua_State *L ) {
	lua_pushboolean( L, IsCursorHidden() );

	return 1;
}

/*
> RL_EnableCursor()

Enables cursor (unlock cursor)
*/
int lcoreEnableCursor( lua_State *L ) {
	EnableCursor();

	return 0;
}

/*
> RL_DisableCursor()

Disables cursor (lock cursor)
*/
int lcoreDisableCursor( lua_State *L ) {
	DisableCursor();

	return 0;
}

/*
> onSreen = RL_IsCursorOnScreen()

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
> success = RL_ClearBackground( Color color )

Set background color ( framebuffer clear color )

- Failure return false
- Success return true
*/
int lcoreClearBackground( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ClearBackground( Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	ClearBackground( color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_BeginDrawing()

Setup canvas ( framebuffer ) to start drawing
*/
int lcoreBeginDrawing( lua_State *L ) {
	BeginDrawing();

	return 1;
}

/*
> RL_EndDrawing()

End canvas drawing and swap buffers ( double buffering )
*/
int lcoreEndDrawing( lua_State *L ) {
	EndDrawing();

	return 1;
}

/*
> success = RL_BeginBlendMode( int mode )

Begin blending mode ( BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED... )

- Failure return false
- Success return true
*/
int lcoreBeginBlendMode( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_BeginBlendMode( int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	BeginBlendMode( lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_EndBlendMode()

End blending mode ( reset to default: BLEND_ALPHA )
*/
int lcoreEndBlendMode( lua_State *L ) {
	EndBlendMode();
	
	return 1;
}

/*
> success = RL_BeginScissorMode( Rectangle rectange )

Begin scissor mode ( define screen area for following drawing )

- Failure return false
- Success return true
*/
int lcoreBeginScissorMode( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_BeginScissorMode( Rectangle rectange )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangle( L );

	BeginScissorMode( rect.x, rect.y, rect.width, rect.height );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_EndScissorMode()

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
> shader = RL_LoadShader( string vsFileName, string fsFileName )

Load shader from files and bind default locations

- Failure return -1
- Success return int
*/
int lcoreLoadShader( lua_State *L ) {
	// if ( !lua_isstring( L, -2 ) || !lua_isstring( L, -1 ) ) {
	// 	TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadShader( string vsFileName, string fsFileName )" );
	// 	lua_pushinteger( L, -1 );
	// 	return 1;
	// }

	char fsFileName[ STRING_LEN ] = { '\0' };
	char vsFileName[ STRING_LEN ] = { '\0' };

	if ( lua_isstring( L, -1 ) ) {
		if ( FileExists( lua_tostring( L, -1 ) ) ) {
			strcpy( fsFileName, lua_tostring( L, -1 ) );
		}
	}
	if ( lua_isstring( L, -2 ) ) {
		if ( FileExists( lua_tostring( L, -2 ) ) ) {
			strcpy( vsFileName, lua_tostring( L, -2 ) );
		}
	}

	int i = 0;

	for ( i = 0; i < state->shaderCount; i++ ) {
		if ( state->shaders[i] == NULL ) {
			break;
		}
	}
	state->shaders[i] = malloc( sizeof( Shader ) );
	// *state->shaders[i] = LoadShader( lua_tostring( L, -2 ), lua_tostring( L, -1 ) );
	// *state->shaders[i] = LoadShader( vsFileName, fsFileName );
	*state->shaders[i] = LoadShader( 0, fsFileName );
	lua_pushinteger( L, i );
	checkShaderRealloc( i );

	return 1;
}

/*
> shader = RL_LoadShaderFromMemory( string vsCode, string fsCode )

Load shader from code strings and bind default locations

- Failure return -1
- Success return int
*/

//TODO Should also allow only one shader.
int lcoreLoadShaderFromMemory( lua_State *L ) {
	if ( !lua_isstring( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadShaderFromMemory( string vsCode, string fsCode )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->shaderCount; i++ ) {
		if ( state->shaders[i] == NULL ) {
			break;
		}
	}
	state->shaders[i] = malloc( sizeof( Shader ) );
	*state->shaders[i] = LoadShaderFromMemory( lua_tostring( L, -2 ), lua_tostring( L, -1 ) );
	lua_pushinteger( L, i );
	checkShaderRealloc( i );

	return 1;
}

/*
> success = RL_BeginShaderMode( Shader shader )

Begin custom shader drawing

- Failure return false
- Success return true
*/
int lcoreBeginShaderMode( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_BeginShaderMode( Shader shader )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, -1 );
	
	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	BeginShaderMode( *state->shaders[ shaderId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> EndShaderMode()

End custom shader drawing ( use default shader )
*/
int lcoreEndShaderMode( lua_State *L ) {
	EndShaderMode();

	return 1;
}

/*
> location = RL_GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Failure return -1
- Success return int
*/
int lcoreGetShaderLocation( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetShaderLocation( Shader shader, string uniformName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, -2 );

	if ( !validShader( shaderId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	lua_pushinteger( L, GetShaderLocation( *state->shaders[ shaderId ], lua_tostring( L, -1 ) ) );

	return 1;
}

/*
> location = RL_GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Failure return -1
- Success return int
*/
int lcoreGetShaderLocationAttrib( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetShaderLocationAttrib( Shader shader, string attribName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t shaderId = lua_tointeger( L, -2 );

	if ( !validShader( shaderId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	lua_pushinteger( L, GetShaderLocationAttrib( *state->shaders[ shaderId ], lua_tostring( L, -1 ) ) );

	return 1;
}

/*
> success = RL_SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value ( matrix 4x4 )

- Failure return false
- Success return true
*/
int lcoreSetShaderValueMatrix( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Matrix mat = uluaGetMatrix( L );
	lua_pop( L, 1 );
	int locIndex = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t shaderId = lua_tointeger( L, -1 );

	if ( !validShader( shaderId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetShaderValueMatrix( *state->shaders[ shaderId ], locIndex, mat );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )

Set shader uniform value for texture ( sampler2d )

- Failure return false
- Success return true
*/
int lcoreSetShaderValueTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t textureId = lua_tointeger( L, -1 );
	int locIndex = lua_tointeger( L, -2 );
	size_t shaderId = lua_tointeger( L, -3 );

	if ( !validShader( shaderId ) || !validTexture( textureId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetShaderValueTexture( *state->shaders[ shaderId ], locIndex, *state->textures[ textureId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table

- Failure return false
- Success return true
*/
int lcoreSetShaderValue( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int uniformType = lua_tointeger( L, -1 );
	lua_pop( L, 1 );

	/* Read values. */
	size_t valueCount = uluaGetTableLen( L );
	float floats[ valueCount ];
	int ints[ valueCount ];

	int t = lua_gettop( L ), i = 0;
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

	int locIndex = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t shaderId = lua_tointeger( L, -1 );

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
> success = RL_SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table

- Failure return false
- Success return true
*/
int lcoreSetShaderValueV( lua_State *L ) {
	if ( !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int count = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int uniformType = lua_tointeger( L, -1 );
	lua_pop( L, 1 );

	/* Read values. */
	size_t valueCount = uluaGetTableLen( L );
	float floats[ valueCount * count ];
	int ints[ valueCount * count ];

	int t = lua_gettop( L ), i = 0;
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

	int locIndex = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	size_t shaderId = lua_tointeger( L, -1 );

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
> success = RL_UnloadShader( Shader shader )

Unload shader from GPU memory ( VRAM )

- Failure return false
- Success return true
*/
int lcoreUnloadShader( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadShader( Shader shader )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

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
## Core - Input
*/

/*
> pressed = RL_IsKeyPressed( int key )

Detect if a key has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsKeyPressed( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsKeyPressed( int key )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsKeyPressed( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> pressed = RL_IsKeyDown( int key )

Detect if a key is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsKeyDown( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsKeyDown( int key )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsKeyDown( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> released = RL_IsKeyReleased( int key )

Detect if a key has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsKeyReleased( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsKeyReleased( int key )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsKeyReleased( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> keycode = RL_GetKeyPressed()

Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetKeyPressed( lua_State *L ) {
	lua_pushinteger( L, GetKeyPressed() );

	return 1;
}

/*
> unicode = RL_GetCharPressed()

Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetCharPressed( lua_State *L ) {
	lua_pushinteger( L, GetCharPressed() );

	return 1;
}

/*
> RL_SetExitKey( int key )

Set a custom key to exit program ( default is ESC )
*/
int lcoreSetExitKey( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetExitKey( int key )" );
		lua_pushnil( L );
		return 1;
	}
	SetExitKey( lua_tointeger( L, -1 ) );

	return 1;
}

/*
> available = RL_IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadAvailable( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsGamepadAvailable( int gamepad )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsGamepadAvailable( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> pressed = RL_IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonPressed( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsGamepadButtonPressed( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsGamepadButtonPressed( lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> pressed = RL_IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonDown( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsGamepadButtonDown( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsGamepadButtonDown( lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> released = RL_IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsGamepadButtonReleased( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsGamepadButtonReleased( int gamepad, int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsGamepadButtonReleased( lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> count = RL_GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Failure return false
- Success return int
*/
int lcoreGetGamepadAxisCount( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetGamepadAxisCount( int gamepad )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetGamepadAxisCount( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> value = RL_GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Failure return false
- Success return float
*/
int lcoreGetGamepadAxisMovement( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetGamepadAxisMovement( int gamepad, int axis )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushnumber( L, GetGamepadAxisMovement( lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> name = RL_GetGamepadName( int gamepad )

Return gamepad internal name id

- Failure return false
- Success return string
*/
int lcoreGetGamepadName( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetGamepadName( int gamepad )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetGamepadName( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> pressed = RL_IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonPressed( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsMouseButtonPressed( int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsMouseButtonPressed( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> pressed = RL_IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonDown( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsMouseButtonDown( int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsMouseButtonDown( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> released = RL_IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Failure return nil
- Success return bool
*/
int lcoreIsMouseButtonReleased( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsMouseButtonReleased( int button )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsMouseButtonReleased( lua_tointeger( L, -1 ) ) );
	return 1;
}

/*
> position = RL_GetMousePosition()

Returns mouse position

- Success return Vector2
*/
int lcoreGetMousePosition( lua_State *L ) {
	uluaPushVector2( L, GetMousePosition() );
	return 1;
}

/*
> position = RL_GetMouseDelta()

Get mouse delta between frames

- Success return Vector2
*/
int lcoreGetMouseDelta( lua_State *L ) {
	uluaPushVector2( L, GetMouseDelta() );
	return 1;
}

/*
> movement = RL_GetMouseWheelMove()

Returns mouse wheel movement Y

- Success return float
*/
int lcoreGetMouseWheelMove( lua_State *L ) {
	lua_pushnumber( L, GetMouseWheelMove() );
	return 1;
}

/*
> success = RL_SetMousePosition( Vector2 position )

Set mouse position XY

- Failure return false
- Success return true
*/
int lcoreSetMousePosition( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMousePosition( Vector2 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2( L );

	SetMousePosition( pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> position = RL_GetTouchPosition( int index )

Get touch position XY for a touch point index ( relative to screen size )

- Failure return false
- Success return Vector2
*/
int lcoreGetTouchPosition( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetTouchPosition( int index )" );
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushVector2( L, GetTouchPosition( lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> id = RL_GetTouchPointId( int index )

Get touch point identifier for given index

- Failure return false
- Success return int
*/
int lcoreGetTouchPointId( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetTouchPointId( int index )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetTouchPointId( lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> count = RL_GetTouchPointCount()

Get touch point identifier for given index

- Success return int
*/
int lcoreGetTouchPointCount( lua_State *L ) {
	lua_pushinteger( L, GetTouchPointCount() );

	return 1;
}

/*
> success = RL_SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags

- Failure return false
- Success return true
*/
int lcoreSetGesturesEnabled( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetGesturesEnabled( unsigned int flags )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetGesturesEnabled( (unsigned int)lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> detected = RL_IsGestureDetected( int gesture )

Check if a gesture have been detected

- Failure return nil
- Success return bool
*/
int lcoreIsGestureDetected( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsGestureDetected( int gesture )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsGestureDetected( lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
> gesture = RL_GetGestureDetected()

Get latest detected gesture

- Success return int
*/
int lcoreGetGestureDetected( lua_State *L ) {
	lua_pushinteger( L, GetGestureDetected() );

	return 1;
}

/*
> time = RL_GetGestureHoldDuration()

Get gesture hold time in milliseconds

- Success return float
*/
int lcoreGetGestureHoldDuration( lua_State *L ) {
	lua_pushnumber( L, GetGestureHoldDuration() );

	return 1;
}

/*
> vector = RL_GetGestureDragVector()

Get gesture drag vector

- Success return Vector2
*/
int lcoreGetGestureDragVector( lua_State *L ) {
	uluaPushVector2( L, GetGestureDragVector() );

	return 1;
}

/*
> angle = RL_GetGestureDragAngle()

Get gesture drag angle

- Success return float
*/
int lcoreGetGestureDragAngle( lua_State *L ) {
	lua_pushnumber( L, GetGestureDragAngle() );

	return 1;
}

/*
> vector = RL_GetGesturePinchVector()

Get gesture pinch delta

- Success return Vector2
*/
int lcoreGetGesturePinchVector( lua_State *L ) {
	uluaPushVector2( L, GetGesturePinchVector() );

	return 1;
}

/*
> angle = RL_GetGesturePinchAngle()

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
> path = RL_GetBasePath()

Return game directory ( where main.lua is located )

- Success return string
*/
int lcoreGetBasePath( lua_State *L ) {
	lua_pushstring( L, state->exePath );

	return 1;
}

/*
> fileExists = RL_FileExists( string fileName )

Check if file exists

- Failure return nil
- Success return bool
*/
int lcoreFileExists( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_FileExists( string fileName )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, FileExists( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> dirExists = RL_DirectoryExists( string dirPath )

Check if a directory path exists

- Failure return nil
- Success return bool
*/
int lcoreDirectoryExists( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DirectoryExists( string dirPath )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, DirectoryExists( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> hasFileExtension = RL_IsFileExtension( string fileName, string ext )

Check file extension ( Including point: .png, .wav )

- Failure return nil
- Success return bool
*/
int lcoreIsFileExtension( lua_State *L ) {
	if ( !lua_isstring( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsFileExtension( string fileName, string ext )" );
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsFileExtension( lua_tostring( L, -2 ), lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> extension = RL_GetFileExtension( string fileName )

Get pointer to extension for a filename string ( Includes dot: '.png' )

- Failure return false
- Success return string
*/
int lcoreGetFileExtension( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetFileExtension( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileExtension( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> filePath = RL_GetFileName( string filePath )

Get pointer to filename for a path string

- Failure return false
- Success return string
*/
int lcoreGetFileName( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetFileName( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileName( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> filePath = RL_GetFileNameWithoutExt( string filePath )

Get filename string without extension ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetFileNameWithoutExt( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetFileNameWithoutExt( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetFileNameWithoutExt( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> filePath = RL_GetDirectoryPath( string filePath )

Get full path for a given fileName with path ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetDirectoryPath( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetDirectoryPath( string filePath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetDirectoryPath( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> filePath = RL_GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetPrevDirectoryPath( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetPrevDirectoryPath( string dirPath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetPrevDirectoryPath( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
> filePath = RL_GetWorkingDirectory()

Get current working directory ( Uses static string )

- Failure return false
- Success return string
*/
int lcoreGetWorkingDirectory( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetWorkingDirectory()" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushstring( L, GetWorkingDirectory() );
	return 1;
}

/*
> fileNames = RL_GetDirectoryFiles( string dirPath )

Get filenames in a directory path

- Failure return false
- Success return string{}
*/
int lcoreGetDirectoryFiles( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetDirectoryFiles( string dirPath )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int count = 0;
	char **strings = GetDirectoryFiles( lua_tostring( L, -1 ), &count );

	lua_createtable( L, count, 0 );

	for ( int i = 0; i < count; ++i ) {
		lua_pushstring( L, strings[i] );
    	lua_rawseti( L, -2, i+1 );
	}
	ClearDirectoryFiles();

	return 1;
}

/*
> time = RL_GetFileModTime( string fileName )

Get file modification time ( Last write time )

- Failure return false
- Success return int
*/
int lcoreGetFileModTime( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetFileModTime( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GetFileModTime( lua_tostring( L, -1 ) ) );
	return 1;
}

/*
## Core - Camera
*/

/*
> camera = RL_CreateCamera3D()

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
	state->camera3Ds[i]->fovy = 45.0f;
	state->camera3Ds[i]->projection = CAMERA_PERSPECTIVE;
	SetCameraMode( *state->camera3Ds[i], CAMERA_CUSTOM );

	lua_pushinteger( L, i );
	checkCamera3DRealloc(i);

	return 1;
}

/*
> success = RL_UnloadCamera3D( int Camera3D )

Unload Camera3D

- Failure return false
- Success return true
*/
int lcoreUnloadCamera3D( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadCamera3D( int Camera3D )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validCamera3D( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	free( state->camera3Ds[ id ] );
	state->camera3Ds[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_BeginMode3D( camera3D camera )

Initializes 3D mode with custom camera ( 3D )

- Failure return false
- Success return true
*/
int lcoreBeginMode3D( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_BeginMode3D( camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validCamera3D( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	BeginMode3D( *state->camera3Ds[ id ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode
*/
int lcoreEndMode3D( lua_State *L ) {
	EndMode3D();

	return 1;
}

/*
> success = RL_SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position ( Remember to call "RL_UpdateCamera3D()" to apply changes )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DPosition( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DPosition( camera3D camera, Vector3 position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 pos = uluaGetVector3( L );
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->camera3Ds[ cameraId ]->position = pos;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at

- Failure return false
- Success return true
*/
int lcoreSetCamera3DTarget( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DTarget( camera3D camera, Vector3 target )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 target = uluaGetVector3( L );
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->camera3Ds[ cameraId ]->target = target;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector ( Rotation over it's axis )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DUp( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DUp( camera3D camera, Vector3 up )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector3 up = uluaGetVector3( L );
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->camera3Ds[ cameraId ]->up = up;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetCamera3DFovy( camera3D camera, Vector3 fovy )

Set camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return false
- Success return true
*/
int lcoreSetCamera3DFovy( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DFovy( camera3D camera, Vector3 fovy )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->camera3Ds[ cameraId ]->fovy = lua_tonumber( L, -1 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode ( CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DProjection( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DProjection( camera3D camera, int projection )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	state->camera3Ds[ cameraId ]->projection = lua_tointeger( L, -1 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetCamera3DMode( camera3D camera, int mode )

Set camera mode ( CAMERA_CUSTOM, CAMERA_FREE, CAMERA_ORBITAL... )

- Failure return false
- Success return true
*/
int lcoreSetCamera3DMode( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetCamera3DMode( camera3D camera, int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -2 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	SetCameraMode( *state->camera3Ds[ cameraId ], lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> position = RL_GetCamera3DPosition( camera3D camera )

Get camera position

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DPosition( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCamera3DPosition( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushnil( L );
		return 1;
	}

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->position );

	return 1;
}

/*
> target = RL_GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DTarget( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCamera3DTarget( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushnil( L );
		return 1;
	}

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->target );

	return 1;
}

/*
> up = RL_GetCamera3DUp( camera3D camera )

Get camera up vector ( Rotation over it's axis )

- Failure return nil
- Success return Vector3
*/
int lcoreGetCamera3DUp( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCamera3DUp( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushnil( L );
		return 1;
	}

	uluaPushVector3( L, state->camera3Ds[ cameraId ]->up );

	return 1;
}

/*
> fovy = RL_GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return nil
- Success return float
*/
int lcoreGetCamera3DFovy( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCamera3DFovy( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushnil( L );
		return 1;
	}

	lua_pushnumber( L, state->camera3Ds[ cameraId ]->fovy );

	return 1;
}

/*
> projection = RL_GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Failure return nil
- Success return int
*/
int lcoreGetCamera3DProjection( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCamera3DProjection( camera3D camera )" );
		lua_pushnil( L );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushnil( L );
		return 1;
	}

	lua_pushinteger( L, state->camera3Ds[ cameraId ]->projection );

	return 1;
}

/*
> success = RL_UpdateCamera3D( camera3D camera )

Update camera position for selected mode

- Failure return false
- Success return true
*/
int lcoreUpdateCamera3D( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UpdateCamera3D( camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	UpdateCamera( state->camera3Ds[ cameraId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Core - Screen-space
*/

/*
> ray = RL_GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Failure return false
- Success return Ray
*/
int lcoreGetMouseRay( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetMouseRay( Vector2 mousePosition, Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 mousePosition = uluaGetVector2( L );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushRay( L, GetMouseRay( mousePosition, *state->camera3Ds[ cameraId ] ) );

	return 1;
}

/*
> matrix = RL_GetCameraMatrix( Camera3D camera )

Get camera transform matrix ( view matrix )

- Failure return false
- Success return Matrix
*/
int lcoreGetCameraMatrix( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCameraMatrix( Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushMatrix( L, GetCameraMatrix( *state->camera3Ds[ cameraId ] ) );

	return 1;
}

/*
> position = RL_GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Failure return false
- Success return Vector2
*/
int lcoreGetWorldToScreen( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetWorldToScreen( Vector3 position, Camera3D camera )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t cameraId = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector3 position = uluaGetVector3( L );

	if ( !validCamera3D( cameraId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	uluaPushVector2( L, GetWorldToScreen( position, *state->camera3Ds[ cameraId ] ) );

	return 1;
}
