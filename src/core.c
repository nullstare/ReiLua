#include "main.h"
#include "state.h"
#include "core.h"
#include "textures.h"
#include "lua_core.h"

static int getBufferElementSize( Buffer* buffer ) {
	switch ( buffer->type ) {
		case BUFFER_UNSIGNED_CHAR: return sizeof( unsigned char );
		case BUFFER_UNSIGNED_SHORT: return sizeof( unsigned short );
		case BUFFER_UNSIGNED_INT: return sizeof( unsigned int );
		case BUFFER_CHAR: return sizeof( char );
		case BUFFER_SHORT: return sizeof( short );
		case BUFFER_INT: return sizeof( int );
		case BUFFER_FLOAT: return sizeof( float );
		case BUFFER_DOUBLE: return sizeof( double );
	}
	return 1;
}

void unloadBuffer( Buffer* buffer ) {
	free( buffer->data );

	TraceLog( LOG_INFO, "BUFFER: Unloaded buffer with %u bytes of data", buffer->size );
}

/*
## Core - Window-related functions
*/

/*
> RL.CloseWindow()

Close window and unload OpenGL context and free all resources
*/
int lcoreCloseWindow( lua_State* L ) {
	state->run = false;

	return 0;
}

/*
> state = RL.IsWindowReady()

Check if window has been initialized successfully

- Success return bool
*/
int lcoreIsWindowReady( lua_State* L ) {
	lua_pushboolean( L, IsWindowReady() );

	return 1;
}

/*
> state = RL.IsWindowFullscreen()

Check if window is currently fullscreen

- Success return bool
*/
int lcoreIsWindowFullscreen( lua_State* L ) {
	lua_pushboolean( L, IsWindowFullscreen() );

	return 1;
}

/*
> state = RL.IsWindowHidden()

Check if window is currently hidden (only PLATFORM_DESKTOP)

- Success return bool
*/
int lcoreIsWindowHidden( lua_State* L ) {
	lua_pushboolean( L, IsWindowHidden() );

	return 1;
}

/*
> state = RL.IsWindowMinimized()

Check if window is currently minimized (only PLATFORM_DESKTOP)

- Success return bool
*/
int lcoreIsWindowMinimized( lua_State* L ) {
	lua_pushboolean( L, IsWindowMinimized() );

	return 1;
}

/*
> state = RL.IsWindowMaximized()

Check if window is currently maximized (only PLATFORM_DESKTOP)

- Success return bool
*/
int lcoreIsWindowMaximized( lua_State* L ) {
	lua_pushboolean( L, IsWindowMaximized() );

	return 1;
}

/*
> state = RL.IsWindowFocused()

Check if window is currently focused (only PLATFORM_DESKTOP)

- Success return bool
*/
int lcoreIsWindowFocused( lua_State* L ) {
	lua_pushboolean( L, IsWindowFocused() );

	return 1;
}

/*
> resized = RL.IsWindowResized()

Check if window has been resized from last frame

- Success return bool
*/
int lcoreIsWindowResized( lua_State* L ) {
	lua_pushboolean( L, IsWindowResized() );

	return 1;
}

/*
> state = RL.IsWindowState( int flag )

Check if one specific window flag is enabled (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool
*/
int lcoreIsWindowState( lua_State* L ) {
	unsigned int flag = (unsigned int)luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsWindowState( flag ) );

	return 1;
}

/*
> RL.SetWindowState( int flag )

Set window configuration state using flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
*/
int lcoreSetWindowState( lua_State* L ) {
	unsigned int flag = (unsigned int)luaL_checkinteger( L, 1 );

	SetWindowState( flag );

	return 0;
}

/*
> resized = RL.ClearWindowState( int flag )

Clear window configuration state flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool
*/
int lcoreClearWindowState( lua_State* L ) {
	unsigned int flag = (unsigned int)luaL_checkinteger( L, 1 );

	ClearWindowState( flag );

	return 1;
}

/*
> RL.ToggleFullscreen()

Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
*/
int lcoreToggleFullscreen( lua_State* L ) {
	ToggleFullscreen();

	return 0;
}

/*
> RL.ToggleBorderlessWindowed()

Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
*/
int lcoreToggleBorderlessWindowed( lua_State* L ) {
	ToggleBorderlessWindowed();

	return 0;
}

/*
> RL.MaximizeWindow()

Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
*/
int lcoreMaximizeWindow( lua_State* L ) {
	MaximizeWindow();

	return 0;
}

/*
> RL.MinimizeWindow()

Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
*/
int lcoreMinimizeWindow( lua_State* L ) {
	MinimizeWindow();

	return 0;
}

/*
> RL.RestoreWindow()

Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
*/
int lcoreRestoreWindow( lua_State* L ) {
	RestoreWindow();

	return 0;
}

/*
> RL.SetWindowIcon( Image image )

Set icon for window (Only PLATFORM_DESKTOP)
*/
int lcoreSetWindowIcon( lua_State* L ) {
	Image* image = uluaGetImage( L, 1 );

	SetWindowIcon( *image );

	return 0;
}

/*
> RL.SetWindowIcons( Image{} images )

Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
*/
int lcoreSetWindowIcons( lua_State* L ) {
	int count = uluaGetTableLen( L, 1 );
	Image images[ count ];

	int t = 1;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		images[i] = *uluaGetImage( L, lua_gettop( L ) );

		i++;
		lua_pop( L, 1 );
	}
	SetWindowIcons( images, count );

	return 0;
}

/*
> RL.SetWindowTitle( string title )

Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
*/
int lcoreSetWindowTitle( lua_State* L ) {
	SetWindowTitle( luaL_checkstring( L, 1 ) );

	return 0;
}

/*
> RL.SetWindowPosition( Vector2 pos )

Set window position on screen
*/
int lcoreSetWindowPosition( lua_State* L ) {
	Vector2 pos = uluaGetVector2( L, 1 );

	SetWindowPosition( pos.x, pos.y );

	return 0;
}

/*
> RL.SetWindowMonitor( int monitor )

Set monitor for the current window
*/
int lcoreSetWindowMonitor( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );

	SetWindowMonitor( monitor );

	return 0;
}

/*
> RL.SetWindowMinSize( Vector2 size )

Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
*/
int lcoreSetWindowMinSize( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );

	SetWindowMinSize( (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.SetWindowMaxSize( Vector2 size )

Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
*/
int lcoreSetWindowMaxSize( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );

	SetWindowMaxSize( (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.SetWindowSize( Vector2 size )

Set window dimensions
*/
int lcoreSetWindowSize( lua_State* L ) {
	Vector2 size = uluaGetVector2( L, 1 );

	SetWindowSize( (int)size.x, (int)size.y );

	return 0;
}

/*
> RL.SetWindowOpacity( float opacity )

Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
*/
int lcoreSetWindowOpacity( lua_State* L ) {
	float opacity = luaL_checknumber( L, 1 );

	SetWindowOpacity( opacity );

	return 0;
}

/*
> RL.SetWindowFocused()

Set window focused (only PLATFORM_DESKTOP)
*/
int lcoreSetWindowFocused( lua_State* L ) {
	SetWindowFocused();

	return 0;
}

/*
> windowHandle = RL.GetWindowHandle()

Get native window handle. Return as lightuserdata

- Success return lightuserdata
*/
int lcoreGetWindowHandle( lua_State* L ) {
	lua_pushlightuserdata( L, GetWindowHandle() );

	return 1;
}

/*
> size = RL.GetScreenSize()

Get screen size

- Success return Vector2
*/
int lcoreGetScreenSize( lua_State* L ) {
	Vector2 size = (Vector2){ GetScreenWidth(), GetScreenHeight() };
	uluaPushVector2( L, size );

	return 1;
}

/*
> size = RL.GetRenderSize()

Get render size

- Success return Vector2
*/
int lcoreGetRenderSize( lua_State* L ) {
	Vector2 size = (Vector2){ GetRenderWidth(), GetRenderHeight() };
	uluaPushVector2( L, size );

	return 1;
}

/*
> count = RL.GetMonitorCount()

Get number of connected monitors

- Success return int
*/
int lcoreGetMonitorCount( lua_State* L ) {
	lua_pushinteger( L, GetMonitorCount() );

	return 1;
}

/*
> monitor = RL.GetCurrentMonitor()

Get current connected monitor

- Success return int
*/
int lcoreGetCurrentMonitor( lua_State* L ) {
	lua_pushinteger( L, GetCurrentMonitor() );

	return 1;
}

/*
> position = RL.GetMonitorPosition( int monitor )

Get specified monitor position

- Success return Vector2
*/
int lcoreGetMonitorPosition( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );

	uluaPushVector2( L, GetMonitorPosition( monitor ) );

	return 1;
}

/*
> size = RL.GetMonitorSize( int monitor )

Get specified monitor size

- Success return Vector2
*/
int lcoreGetMonitorSize( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );

	Vector2 size = (Vector2){ GetMonitorWidth( monitor ), GetMonitorHeight( monitor ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> size = RL.GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Success return Vector2
*/
int lcoreGetMonitorPhysicalSize( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );

	Vector2 size = { GetMonitorPhysicalWidth( monitor ), GetMonitorPhysicalHeight( monitor ) };
	uluaPushVector2( L, size );

	return 1;
}

/*
> refreshRate = RL.GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Success return int
*/
int lcoreGetMonitorRefreshRate( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );
	
	lua_pushinteger( L, GetMonitorRefreshRate( monitor ) );

	return 1;
}

/*
> position = RL.GetWindowPosition()

Get window position on monitor

- Success return Vector2
*/
int lcoreGetWindowPosition( lua_State* L ) {
	uluaPushVector2( L, GetWindowPosition() );

	return 1;
}

/*
> dpi = RL.GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2
*/
int lcoreGetWindowScaleDPI( lua_State* L ) {
	uluaPushVector2( L, GetWindowScaleDPI() );

	return 1;
}

/*
> name = RL.GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the specified monitor

- Success return string
*/
int lcoreGetMonitorName( lua_State* L ) {
	int monitor = luaL_checkinteger( L, 1 );

	lua_pushstring( L, GetMonitorName( monitor ) );

	return 1;
}

/*
> RL.SetClipboardText( string text )

Set clipboard text content
*/
int lcoreSetClipboardText( lua_State* L ) {
	SetClipboardText( luaL_checkstring( L, 1 ) );

	return 0;
}

/*
> text = RL.GetClipboardText()

Get clipboard text content

- Success return string
*/
int lcoreGetClipboardText( lua_State* L ) {
	lua_pushstring( L, GetClipboardText() );

	return 1;
}

/*
> RL.EnableEventWaiting()

Enable waiting for events on EndDrawing(), no automatic event polling
*/
int lcoreEnableEventWaiting( lua_State* L ) {
	EnableEventWaiting();

	return 0;
}

/*
> RL.DisableEventWaiting()

Disable waiting for events on EndDrawing(), automatic events polling
*/
int lcoreDisableEventWaiting( lua_State* L ) {
	DisableEventWaiting();

	return 0;
}

/*
## Core - Cursor-related functions
*/

/*
> RL.ShowCursor()

Shows cursor
*/
int lcoreShowCursor( lua_State* L ) {
	ShowCursor();

	return 0;
}

/*
> RL.HideCursor()

Hides cursor
*/
int lcoreHideCursor( lua_State* L ) {
	HideCursor();

	return 0;
}

/*
> hidden = RL.IsCursorHidden()

Check if cursor is not visible

- Success return bool
*/
int lcoreIsCursorHidden( lua_State* L ) {
	lua_pushboolean( L, IsCursorHidden() );

	return 1;
}

/*
> RL.EnableCursor()

Enables cursor (unlock cursor)
*/
int lcoreEnableCursor( lua_State* L ) {
	EnableCursor();

	return 0;
}

/*
> RL.DisableCursor()

Disables cursor (lock cursor)
*/
int lcoreDisableCursor( lua_State* L ) {
	DisableCursor();

	return 0;
}

/*
> onSreen = RL.IsCursorOnScreen()

Check if cursor is on the screen

- Success return bool
*/
int lcoreIsCursorOnScreen( lua_State* L ) {
	lua_pushboolean( L, IsCursorOnScreen() );

	return 1;
}

/*
## Core - Drawing-related functions
*/

/*
> RL.ClearBackground( Color color )

Set background color (framebuffer clear color)
*/
int lcoreClearBackground( lua_State* L ) {
	Color color = uluaGetColor( L, 1 );

	ClearBackground( color );

	return 0;
}

/*
> RL.BeginDrawing()

Setup canvas (framebuffer) to start drawing
*/
int lcoreBeginDrawing( lua_State* L ) {
	BeginDrawing();

	return 0;
}

/*
> RL.EndDrawing()

End canvas drawing and swap buffers (double buffering)
*/
int lcoreEndDrawing( lua_State* L ) {
	EndDrawing();

	return 0;
}

/*
> RL.BeginMode2D( camera2D camera )

Begin 2D mode with custom camera (2D)
*/
int lcoreBeginMode2D( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );

	BeginMode2D( *camera );

	return 0;
}

/*
> RL.EndMode2D()

Ends 2D mode with custom camera
*/
int lcoreEndMode2D( lua_State* L ) {
	EndMode2D();

	return 0;
}

/*
> RL.BeginMode3D( camera3D camera )

Begin 3D mode with custom camera (3D)
*/
int lcoreBeginMode3D( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	BeginMode3D( *camera );

	return 0;
}

/*
> RL.EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode
*/
int lcoreEndMode3D( lua_State* L ) {
	EndMode3D();

	return 0;
}

/*
> RL.BeginTextureMode( RenderTexture target )

Begin drawing to render texture
*/
int lcoreBeginTextureMode( lua_State* L ) {
	RenderTexture* renderTexture = uluaGetRenderTexture( L, 1 );

	BeginTextureMode( *renderTexture );

	return 0;
}

/*
> RL.EndTextureMode()

Ends drawing to render texture
*/
int lcoreEndTextureMode( lua_State* L ) {
	EndTextureMode();

	return 0;
}

/*
> RL.BeginShaderMode( Shader shader )

Begin custom shader drawing
*/
int lcoreBeginShaderMode( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	BeginShaderMode( *shader );

	return 0;
}

/*
> RL.EndShaderMode()

End custom shader drawing (use default shader)
*/
int lcoreEndShaderMode( lua_State* L ) {
	EndShaderMode();

	return 0;
}

/*
> RL.BeginBlendMode( int mode )

Begin blending mode (BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED...)
*/
int lcoreBeginBlendMode( lua_State* L ) {
	int mode = luaL_checkinteger( L, 1 );

	BeginBlendMode( mode );

	return 0;
}

/*
> RL.EndBlendMode()

End blending mode (reset to default: BLEND_ALPHA)
*/
int lcoreEndBlendMode( lua_State* L ) {
	EndBlendMode();
	
	return 0;
}

/*
> RL.BeginScissorMode( Rectangle rectange )

Begin scissor mode (define screen area for following drawing)
*/
int lcoreBeginScissorMode( lua_State* L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );

	BeginScissorMode( rect.x, rect.y, rect.width, rect.height );

	return 0;
}

/*
> RL.EndScissorMode()

End scissor mode
*/
int lcoreEndScissorMode( lua_State* L ) {
	EndScissorMode();

	return 0;
}

/*
## Core - Shader management functions
*/

/*
> shader = RL.LoadShader( string|nil vsFileName, string|nil fsFileName )

Load shader from files and bind default locations.
NOTE: Set nil if no shader

- Failure return nil
- Success return Shader
*/
int lcoreLoadShader( lua_State* L ) {
	if ( !( lua_isstring( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isstring( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Argument needs to be string or nil" );
		lua_pushnil( L );
		return 1;
	}
	/* Will result to NULL if given nil. */
	const char* vsFileName = lua_tostring( L, 1 );
	const char* fsFileName = lua_tostring( L, 2 );

	uluaPushShader( L, LoadShader( vsFileName, fsFileName ) );

	return 1;
}

/*
> shader = RL.LoadShaderFromMemory( string|nil vsCode, string|nil fsCode )

Load shader from code strings and bind default locations
NOTE: Set nil if no shader

- Failure return nil
- Success return Shader
*/

int lcoreLoadShaderFromMemory( lua_State* L ) {
	if ( !( lua_isstring( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isstring( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.LoadShaderFromMemory( string vsCode, string fsCode )" );
		lua_pushnil( L );
		return 1;
	}
	/* Will result to NULL if given nil. */
	const char* vs = lua_tostring( L, 1 );
	const char* fs = lua_tostring( L, 2 );

	uluaPushShader( L, LoadShaderFromMemory( vs, fs ) );

	return 1;
}

/*
> isReady = RL.IsShaderReady( Shader shader )

Check if a shader is ready

- Success return bool
*/
int lcoreIsShaderReady( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	lua_pushboolean( L, IsShaderReady( *shader ) );

	return 1;
}

/*
> shaderId = RL.GetShaderId( Shader shader )

Get shader program id

- Success return int
*/
int lcoreGetShaderId( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	lua_pushinteger( L, shader->id );

	return 1;
}

/*
> location = RL.GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Success return int
*/
int lcoreGetShaderLocation( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	lua_pushinteger( L, GetShaderLocation( *shader, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> location = RL.GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Success return int
*/
int lcoreGetShaderLocationAttrib( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	lua_pushinteger( L, GetShaderLocationAttrib( *shader, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> RL.SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )

Set shader location index
*/
int lcoreSetShaderLocationIndex( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int shaderLocationIndex = luaL_checkinteger( L, 2 );
	int location = luaL_checkinteger( L, 3 );

	shader->locs[ shaderLocationIndex ] = location;

	return 0;
}

/*
> location = RL.GetShaderLocationIndex( Shader shader, int shaderLocationIndex )

Get shader location index

- Success return int
*/
int lcoreGetShaderLocationIndex( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int shaderLocationIndex = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, shader->locs[ shaderLocationIndex ] );

	return 1;
}

/*
> RL.SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value (matrix 4x4)
*/
int lcoreSetShaderValueMatrix( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int locIndex = luaL_checkinteger( L, 2 );
	Matrix mat = uluaGetMatrix( L, 3 );

	SetShaderValueMatrix( *shader, locIndex, mat );

	return 0;
}

/*
> RL.SetShaderValueTexture( Shader shader, int locIndex, Texture texture )

Set shader uniform value for texture (sampler2d)
*/
int lcoreSetShaderValueTexture( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int locIndex = luaL_checkinteger( L, 2 );
	Texture* texture = uluaGetTexture( L, 3 );

	SetShaderValueTexture( *shader, locIndex, *texture );

	return 0;
}

/*
> RL.SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table
*/
int lcoreSetShaderValue( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int locIndex = luaL_checkinteger( L, 2 );
	size_t valueCount = uluaGetTableLen( L, 3 );
	int uniformType = luaL_checkinteger( L, 4 );

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

	if ( uniformType == SHADER_UNIFORM_FLOAT || uniformType == SHADER_UNIFORM_VEC2
	|| uniformType == SHADER_UNIFORM_VEC3 || uniformType == SHADER_UNIFORM_VEC4 ) {
		SetShaderValue( *shader, locIndex, floats, uniformType );
	}
	else {
		SetShaderValue( *shader, locIndex, ints, uniformType );
	}

	return 0;
}

/*
> RL.SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table
*/
int lcoreSetShaderValueV( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );
	int locIndex = luaL_checkinteger( L, 2 );
	size_t valueCount = uluaGetTableLen( L, 3 );
	int uniformType = luaL_checkinteger( L, 4 );
	int count = luaL_checkinteger( L, 5 );

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

	if ( uniformType == SHADER_UNIFORM_FLOAT || uniformType == SHADER_UNIFORM_VEC2
	|| uniformType == SHADER_UNIFORM_VEC3 || uniformType == SHADER_UNIFORM_VEC4 ) {
		SetShaderValueV( *shader, locIndex, floats, uniformType, count );
	}
	else {
		SetShaderValueV( *shader, locIndex, ints, uniformType, count );
	}

	return 0;
}

/*
> RL.UnloadShader( Shader shader )

Unload shader from GPU memory (VRAM)
*/
int lcoreUnloadShader( lua_State* L ) {
	Shader* shader = uluaGetShader( L, 1 );

	UnloadShader( *shader );
	memset( shader, 0, sizeof( Shader ) );

	return 0;
}

/*
## Core - Screen-space-related functions
*/

/*
> ray = RL.GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Success return Ray
*/
int lcoreGetMouseRay( lua_State* L ) {
	Vector2 mousePosition = uluaGetVector2( L, 1 );
	Camera3D* camera = uluaGetCamera3D( L, 2 );

	uluaPushRay( L, GetMouseRay( mousePosition, *camera ) );

	return 1;
}

/*
> matrix = RL.GetCameraMatrix( Camera3D camera )

Get camera transform matrix (view matrix)

- Success return Matrix
*/
int lcoreGetCameraMatrix( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushMatrix( L, GetCameraMatrix( *camera ) );

	return 1;
}

/*
> matrix = RL.GetCameraMatrix2D( Camera2D camera )

Get camera 2d transform matrix

- Success return Matrix
*/
int lcoreGetCameraMatrix2D( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );

	uluaPushMatrix( L, GetCameraMatrix2D( *camera ) );

	return 1;
}

/*
> position = RL.GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Success return Vector2
*/
int lcoreGetWorldToScreen( lua_State* L ) {
	Vector3 position = uluaGetVector3( L, 1 );
	Camera3D* camera = uluaGetCamera3D( L, 2 );

	uluaPushVector2( L, GetWorldToScreen( position, *camera ) );

	return 1;
}

/*
> position = RL.GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )

Get size position for a 3d world space position

- Success return Vector2
*/
int lcoreGetWorldToScreenEx( lua_State* L ) {
	Vector3 position = uluaGetVector3( L, 1 );
	Camera3D* camera = uluaGetCamera3D( L, 2 );
	Vector2 size = uluaGetVector2( L, 3 );

	uluaPushVector2( L, GetWorldToScreenEx( position, *camera, size.x, size.y ) );

	return 1;
}

/*
> position = RL.GetWorldToScreen2D( Vector2 position, Camera2D camera )

Get the screen space position for a 2d camera world space position

- Success return Vector2
*/
int lcoreGetWorldToScreen2D( lua_State* L ) {
	Vector2 position = uluaGetVector2( L, 1 );
	Camera2D* camera = uluaGetCamera2D( L, 2 );

	uluaPushVector2( L, GetWorldToScreen2D( position, *camera ) );

	return 1;
}

/*
> position = RL.GetScreenToWorld2D( Vector2 position, Camera2D camera )

Get the world space position for a 2d camera screen space position

- Success return Vector2
*/
int lcoreGetScreenToWorld2D( lua_State* L ) {
	Vector2 position = uluaGetVector2( L, 1 );
	Camera2D* camera = uluaGetCamera2D( L, 2 );

	uluaPushVector2( L, GetScreenToWorld2D( position, *camera ) );

	return 1;
}

/*
## Core - Timing-related functions
*/

/*
> RL.SetTargetFPS( int fps )

Set target FPS (maximum)
*/
int lcoreSetTargetFPS( lua_State* L ) {
	int fps = luaL_checkinteger( L, 1 );

	SetTargetFPS( fps );

	return 0;
}

/*
> delta = RL.GetFrameTime()

Get time in seconds for last frame drawn (Delta time)

- Success return float
*/
int lcoreGetFrameTime( lua_State* L ) {
	lua_pushnumber( L, GetFrameTime() );

	return 1;
}

/*
> time = RL.GetTime()

Get elapsed time in seconds since InitWindow()

- Success return float
*/
int lcoreGetTime( lua_State* L ) {
	lua_pushnumber( L, GetTime() );

	return 1;
}

/*
> FPS = RL.GetFPS()

Get current FPS

- Success return int
*/
int lcoreGetFPS( lua_State* L ) {
	lua_pushinteger( L, GetFPS() );

	return 1;
}

/*
## Core - Custom frame control functions
*/

/*
> RL.SwapScreenBuffer()

Swap back buffer with front buffer (screen drawing)
*/
int lcoreSwapScreenBuffer( lua_State* L ) {
	SwapScreenBuffer();

	return 0;
}

/*
> RL.PollInputEvents()

Register all input events
*/
int lcorePollInputEvents( lua_State* L ) {
	PollInputEvents();

	return 0;
}

/*
> RL.WaitTime( number seconds )

Wait for some time (halt program execution)
*/
int lcoreWaitTime( lua_State* L ) {
	double seconds = luaL_checknumber( L, 1 );

	WaitTime( seconds );

	return 0;
}

/*
## Core - Random values generation functions
*/

/*
> RL.SetRandomSeed( int seed )

Set the seed for the random number generator
*/
int lcoreSetRandomSeed( lua_State* L ) {
	unsigned int seed = (unsigned int)luaL_checkinteger( L, 1 );

	SetRandomSeed( seed );

	return 0;
}

/*
> time = RL.GetRandomValue( int min, int max )

Get a random value between min and max (both included)

- Success return int
*/
int lcoreGetRandomValue( lua_State* L ) {
	int min = luaL_checkinteger( L, 1 );
	int max = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, GetRandomValue( min, max ) );

	return 1;
}

/*
> sequence = RL.LoadRandomSequence( int count, int min, int max )

Load random values sequence, no values repeated

- Success return int{}
*/
int lcoreLoadRandomSequence( lua_State* L ) {
	unsigned int count = luaL_checkinteger( L, 1 );
	int min = luaL_checkinteger( L, 1 );
	int max = luaL_checkinteger( L, 2 );

	int* sequence = LoadRandomSequence( count, min, max );
	lua_createtable( L, count, 0 );

	for ( int i = 0; i < count; i++ ) {
		lua_pushinteger( L, sequence[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	UnloadRandomSequence( sequence );

	return 1;
}

/*
## Core - Misc
*/

/*
> RL.TakeScreenshot( string fileName )

Takes a screenshot of current screen (filename extension defines format)
*/
int lcoreTakeScreenshot( lua_State* L ) {
	TakeScreenshot( luaL_checkstring( L, 1 ) );

	return 0;
}

/*
> RL.SetConfigFlags( int flags )

Setup init configuration flags (view FLAGS)
*/
int lcoreSetConfigFlags( lua_State* L ) {
	unsigned int flag = (unsigned int)luaL_checkinteger( L, 1 );

	SetConfigFlags( flag );

	return 0;
}

/*
> RL.TraceLog( int logLevel, string text )

Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
*/
int lcoreTraceLog( lua_State* L ) {
	int logLevel = luaL_checkinteger( L, 1 );

	TraceLog( logLevel, "%s", luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> RL.SetTraceLogLevel( int logLevel )

Set the current threshold (minimum) log level
*/
int lcoreSetTraceLogLevel( lua_State* L ) {
	int logLevel = luaL_checkinteger( L, 1 );

	SetTraceLogLevel( logLevel );

	return 0;
}

/*
> RL.SetLogLevelInvalid( int logLevel )

Set the log level for bad function calls and invalid data formats.
*/
int lcoreSetLogLevelInvalid( lua_State* L ) {
	state->logLevelInvalid = luaL_checkinteger( L, 1 );

	return 0;
}

/*
> logLevel = RL.GetLogLevelInvalid()

Get the log level for bad function calls and invalid data formats.

- Success return int
*/
int lcoreGetLogLevelInvalid( lua_State* L ) {
	lua_pushinteger( L, state->logLevelInvalid );

	return 1;
}

/*
> RL.OpenURL( string url )

Open URL with default system browser (if available)
*/
int lcoreOpenURL( lua_State* L ) {
	OpenURL( luaL_checkstring( L, 1 ) );

	return 0;
}

/*
> enabled = RL.IsGCUnloadEnabled()

Check if Lua garbage collection is set to unload object data

- Success return bool
*/
int lcoreIsGCUnloadEnabled( lua_State* L ) {
	lua_pushboolean( L, state->gcUnload );

	return 1;
}

/*
> RL.SetGCUnload( bool enabled )

Set Lua garbage collection to unload object data
*/
int lcoreSetGCUnload( lua_State* L ) {
	state->gcUnload = uluaGetBoolean( L, 1 );

	return 0;
}

/*
> platform = RL.GetPlatform()

Get platform. Returns "Windows", "Linux", "FreeBSD", "OpenBSD", "Apple" or "Emscripten"

- Success return string
*/
int lcoreGetPlatform( lua_State* L ) {
#if defined( _WIN32 )
	lua_pushstring( L, "Windows" );
#elif defined( __linux__ )
	lua_pushstring( L, "Linux" );
#elif defined( __FreeBSD__ )
	lua_pushstring( L, "FreeBSD" );
#elif defined( __OpenBSD__ )
	lua_pushstring( L, "OpenBSD" );
#elif defined( __APPLE__ )
	lua_pushstring( L, "Apple" );
#elif defined( __EMSCRIPTEN__ )
	lua_pushstring( L, "Emscripten" );
#endif

	return 1;
}

/*
## Core - Files management functions
*/

/*
> buffer = RL.LoadFileData( string fileName )

Load file data as byte array (read). Buffer type is BUFFER_UNSIGNED_CHAR

- Success return Buffer
*/
int lcoreLoadFileData( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );

	Buffer buffer = {
		.type = BUFFER_UNSIGNED_CHAR
	};
	buffer.data = LoadFileData( fileName, (int*)&buffer.size );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> success = RL.SaveFileData( string fileName, buffer Buffer )

Save data to file from byte array (write), returns true on success

- Success return bool
*/
int lcoreSaveFileData( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );
	Buffer* buffer = uluaGetBuffer( L, 2 );

	lua_pushboolean( L, SaveFileData( fileName, buffer->data, buffer->size ) );

	return 1;
}

/*
> success = RL.ExportDataAsCode( Buffer buffer, string fileName )

Export data to code (.h), returns true on success

- Success return bool
*/
int lcoreExportDataAsCode( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );
	const char* fileName = luaL_checkstring( L, 2 );

	lua_pushboolean( L, ExportDataAsCode( buffer->data, buffer->size, fileName ) );

	return 1;
}

/*
> text = RL.LoadFileText( string fileName )

Load text data from file (read)

- Success return string
*/
int lcoreLoadFileText( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );

	char* text = LoadFileText( fileName );
	lua_pushstring( L, text );
	UnloadFileText( text );

	return 1;
}

/*
> success = RL.SaveFileText( string fileName, string text )

Save text data to file (write), returns true on success

- Success return bool
*/
int lcoreSaveFileText( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );
	char* text = (char*)luaL_checkstring( L, 2 );

	lua_pushboolean( L, SaveFileText( fileName, text ) );

	return 1;
}

/*
## Core - Files system functions
*/

/*
> path = RL.GetBasePath()

Return game directory (where main.lua is located)

- Success return string
*/
int lcoreGetBasePath( lua_State* L ) {
	lua_pushstring( L, state->basePath );

	return 1;
}

/*
> fileExists = RL.FileExists( string fileName )

Check if file exists

- Success return bool
*/
int lcoreFileExists( lua_State* L ) {
	lua_pushboolean( L, FileExists( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> dirExists = RL.DirectoryExists( string dirPath )

Check if a directory path exists

- Success return bool
*/
int lcoreDirectoryExists( lua_State* L ) {
	lua_pushboolean( L, DirectoryExists( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> hasFileExtension = RL.IsFileExtension( string fileName, string ext )

Check file extension (Including point: .png, .wav)

- Success return bool
*/
int lcoreIsFileExtension( lua_State* L ) {
	lua_pushboolean( L, IsFileExtension( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> length = RL.GetFileLength( string fileName )

Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)

- Success return int
*/
int lcoreGetFileLength( lua_State* L ) {
	lua_pushinteger( L, GetFileLength( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> extension = RL.GetFileExtension( string fileName )

Get pointer to extension for a filename string (Includes dot: '.png')

- Success return string
*/
int lcoreGetFileExtension( lua_State* L ) {
	lua_pushstring( L, GetFileExtension( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> fileName = RL.GetFileName( string filePath )

Get pointer to filename for a path string

- Success return string
*/
int lcoreGetFileName( lua_State* L ) {
	lua_pushstring( L, GetFileName( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> fileName = RL.GetFileNameWithoutExt( string filePath )

Get filename string without extension (Uses static string)

- Success return string
*/
int lcoreGetFileNameWithoutExt( lua_State* L ) {
	lua_pushstring( L, GetFileNameWithoutExt( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> filePath = RL.GetDirectoryPath( string filePath )

Get full path for a given fileName with path (Uses static string)

- Success return string
*/
int lcoreGetDirectoryPath( lua_State* L ) {
	lua_pushstring( L, GetDirectoryPath( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> directory = RL.GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path (Uses static string)

- Success return string
*/
int lcoreGetPrevDirectoryPath( lua_State* L ) {
	lua_pushstring( L, GetPrevDirectoryPath( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> directory = RL.GetWorkingDirectory()

Get current working directory (Uses static string)

- Success return string
*/
int lcoreGetWorkingDirectory( lua_State* L ) {
	lua_pushstring( L, GetWorkingDirectory() );

	return 1;
}

/*
> directory = RL.GetApplicationDirectory()

Get the directory of the running application (uses static string)

- Success return string
*/
int lcoreGetApplicationDirectory( lua_State* L ) {
	lua_pushstring( L, GetApplicationDirectory() );

	return 1;
}

/*
> fileNames = RL.LoadDirectoryFiles( string dirPath )

Load directory filepaths

- Success return string{}
*/
int lcoreLoadDirectoryFiles( lua_State* L ) {
	FilePathList files = LoadDirectoryFiles( luaL_checkstring( L, 1 ) );

	lua_createtable( L, files.count, 0 );

	for ( int i = 0; i < files.count; ++i ) {
		lua_pushstring( L, files.paths[i] );
		lua_rawseti( L, -2, i+1 );
	}
	UnloadDirectoryFiles( files );

	return 1;
}

/*
> fileNames = RL.LoadDirectoryFilesEx( string basePath, string|nil filter, bool scanSubdirs )

Load directory filepaths with extension filtering and recursive directory scan

- Success return string{}
*/
int lcoreLoadDirectoryFilesEx( lua_State* L ) {
	bool scanSubdirs = uluaGetBoolean( L, 3 );
	const char* basePath = luaL_checkstring( L, 1 );
	char* filter = NULL;

	if ( lua_isstring( L, 2 ) ) {
		filter = (char*)lua_tostring( L, 2 );
	}
	FilePathList files = LoadDirectoryFilesEx( basePath, filter, scanSubdirs );

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

- Success return bool
*/
int lcoreChangeDirectory( lua_State* L ) {
	lua_pushboolean( L, ChangeDirectory( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> isFile = RL.IsPathFile( string path )

Check if a given path is a file or a directory

- Success return bool
*/
int lcoreIsPathFile( lua_State* L ) {
	lua_pushboolean( L, IsPathFile( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
> iSFileDropped = RL.IsFileDropped()

Check if a file has been dropped into window

- Success return bool
*/
int lcoreIsFileDropped( lua_State* L ) {
	lua_pushboolean( L, IsFileDropped() );

	return 1;
}

/*
> files = RL.LoadDroppedFiles()

Load dropped filepaths

- Success return string{}
*/
int lcoreLoadDroppedFiles( lua_State* L ) {
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

Get file modification time (Last write time)

- Success return int
*/
int lcoreGetFileModTime( lua_State* L ) {
	lua_pushinteger( L, GetFileModTime( luaL_checkstring( L, 1 ) ) );

	return 1;
}

/*
## Core - Compression/Encoding functionality
*/

/*
> compData = RL.CompressData( Buffer buffer )

Compress data (DEFLATE algorithm)

- Success return Buffer
*/
int lcoreCompressData( lua_State* L ) {
	Buffer* inBuffer = uluaGetBuffer( L, 1 );
	Buffer outBuffer = {
		.size = 0,
		.type = inBuffer->type
	};
	unsigned char* compData = CompressData( inBuffer->data, inBuffer->size, (int*)&outBuffer.size );

	outBuffer.data = malloc( outBuffer.size );
	memcpy( outBuffer.data, compData, outBuffer.size );
	uluaPushBuffer( L, outBuffer );

	free( compData );

	return 1;
}

/*
> decompData = RL.DecompressData( Buffer compData )

Decompress data (DEFLATE algorithm).

- Success Buffer 
*/
int lcoreDecompressData( lua_State* L ) {
	Buffer* inBuffer = uluaGetBuffer( L, 1 );
	Buffer outBuffer = {
		.size = 0,
		.type = inBuffer->type
	};
	unsigned char* data = DecompressData( inBuffer->data, inBuffer->size, (int*)&outBuffer.size );

	outBuffer.data = malloc( outBuffer.size );
	memcpy( outBuffer.data, data, outBuffer.size );
	uluaPushBuffer( L, outBuffer );

	free( data );

	return 1;
}

/*
> encodedData, outputSize = RL.EncodeDataBase64( string data )

Encode data to Base64 string

- Success return string, int
*/
int lcoreEncodeDataBase64( lua_State* L ) {
	int dataSize = 0;
	const char* string = luaL_checklstring( L, 1, (size_t*)&dataSize );

	int outputSize = 0;
	char* compData = EncodeDataBase64( string, dataSize, &outputSize );

	lua_pushstring( L, compData );
	lua_pushinteger( L, outputSize );

	free( compData );

	return 2;
}

/*
> decodedData, outputSize = RL.DecodeDataBase64( string data )

Decode Base64 string data

- Success return string, int
*/
int lcoreDecodeDataBase64( lua_State* L ) {
	int outputSize = 0;
	unsigned char* decodedData = DecodeDataBase64( luaL_checkstring( L, 1 ), &outputSize );

	lua_pushstring( L, decodedData );
	lua_pushinteger( L, outputSize );

	free( decodedData );

	return 2;
}

/*
## Core - Automation events functionality
*/

/*
> eventList = RL.LoadAutomationEventList( string|nil fileName )

Load automation events list from file, nil for empty list, capacity = MAX_AUTOMATION_EVENTS

- Success return AutomationEventList
*/
int lcoreLoadAutomationEventList( lua_State* L ) {
	if ( lua_isstring( L, 1 ) ) {
		uluaPushAutomationEventList( L, LoadAutomationEventList( lua_tostring( L, 1 ) ) );
	}
	else if ( lua_isnil( L, 1 ) ) {
		uluaPushAutomationEventList( L, LoadAutomationEventList( NULL ) );
	}

	return 1;
}

/*
> RL.UnloadAutomationEventList( AutomationEventList list )

Unload automation events list from file
*/
int lcoreUnloadAutomationEventList( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );

	UnloadAutomationEventList( list );
	memset( list, 0, sizeof( AutomationEventList ) );

	return 0;
}

/*
> success = RL.ExportAutomationEventList( string fileName )

Export automation events list as text file

- Failure return false
- Success return true
*/
int lcoreExportAutomationEventList( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );
	const char* fileName = luaL_checkstring( L, 2 );

	lua_pushboolean( L, ExportAutomationEventList( *list, fileName ) );

	return 1;
}

/*
> RL.SetAutomationEventList( AutomationEventList list )

Set automation event list to record to
*/
int lcoreSetAutomationEventList( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );

	SetAutomationEventList( list );

	return 0;
}

/*
> RL.SetAutomationEventBaseFrame( int frame )

Set automation event internal base frame to start recording
*/
int lcoreSetAutomationEventBaseFrame( lua_State* L ) {
	int frame = luaL_checkinteger( L, 1 );

	SetAutomationEventBaseFrame( frame );

	return 0;
}

/*
> RL.StartAutomationEventRecording()

Start recording automation events (AutomationEventList must be set)
*/
int lcoreStartAutomationEventRecording( lua_State* L ) {
	StartAutomationEventRecording();

	return 0;
}

/*
> RL.StopAutomationEventRecording()

Stop recording automation events
*/
int lcoreStopAutomationEventRecording( lua_State* L ) {
	
	StopAutomationEventRecording();

	return 0;
}

/*
> RL.PlayAutomationEvent( AutomationEvent event )

Play a recorded automation event
*/
int lcorePlayAutomationEvent( lua_State* L ) {
	AutomationEvent* event = uluaGetAutomationEvent( L, 1 );

	PlayAutomationEvent( *event );

	return 0;
}

/*
> capacity = RL.GetAutomationEventListCapacity( AutomationEventList list )

Get automation event list capacity

- Success return int
*/
int lcoreGetAutomationEventListCapacity( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );

	lua_pushinteger( L, list->capacity );

	return 1;
}

/*
> count = RL.GetAutomationEventListCount( AutomationEventList list )

Get automation event list count

- Success return int
*/
int lcoreGetAutomationEventListCount( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );

	lua_pushinteger( L, list->count );

	return 1;
}

/*
> event = RL.GetAutomationEvent( AutomationEventList list, int index )

Get automation event from automation event list. Return as lightuserdata

- Failure return nil
- Success return AutomationEvent
*/
int lcoreGetAutomationEvent( lua_State* L ) {
	AutomationEventList* list = uluaGetAutomationEventList( L, 1 );
	int index = luaL_checkinteger( L, 2 );

	if ( 0 <= index && index < list->count ) {
		lua_pushlightuserdata( L, &list->events[ index ] );
	}
	else {
		TraceLog( LOG_WARNING, "GetAutomationEvent index %d out of bounds", index );
		lua_pushnil( L );
	}

	return 1;
}

/*
> frame = RL.GetAutomationEventFrame( AutomationEvent event )

Get automation event frame

- Success return int
*/
int lcoreGetAutomationEventFrame( lua_State* L ) {
	AutomationEvent* event = uluaGetAutomationEvent( L, 1 );

	lua_pushinteger( L, event->frame );

	return 1;
}

/*
> type = RL.GetAutomationEventType( AutomationEvent event )

Get automation event type

- Success return int
*/
int lcoreGetAutomationEventType( lua_State* L ) {
	AutomationEvent* event = uluaGetAutomationEvent( L, 1 );

	lua_pushinteger( L, event->type );

	return 1;
}

/*
> params = RL.GetAutomationEventParams( AutomationEvent event )

Get automation event params

- Success return int{}
*/
int lcoreGetAutomationEventParams( lua_State* L ) {
	AutomationEvent* event = uluaGetAutomationEvent( L, 1 );

	lua_createtable( L, 4, 0 );

	for ( int i = 0; i < 4; i++ ) {
		lua_pushnumber( L, event->params[i] );
		lua_rawseti( L, -2, i + 1 );
	}

	return 1;
}

/*
## Core - Input-related functions: keyboard
*/

/*
> pressed = RL.IsKeyPressed( int key )

Detect if a key has been pressed once

- Success return bool
*/
int lcoreIsKeyPressed( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsKeyPressed( key ) );

	return 1;
}

/*
> pressed = RL.IsKeyPressedRepeat( int key )

Check if a key has been pressed again (Only PLATFORM_DESKTOP)

- Success return bool
*/
int lcoreIsKeyPressedRepeat( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsKeyPressedRepeat( key ) );

	return 1;
}

/*
> pressed = RL.IsKeyDown( int key )

Detect if a key is being pressed

- Success return bool
*/
int lcoreIsKeyDown( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsKeyDown( key ) );

	return 1;
}

/*
> released = RL.IsKeyReleased( int key )

Detect if a key has been released once

- Success return bool
*/
int lcoreIsKeyReleased( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsKeyReleased( key ) );

	return 1;
}

/*
> released = RL.IsKeyUp( int key )

Check if a key is NOT being pressed

- Success return bool
*/
int lcoreIsKeyUp( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsKeyUp( key ) );

	return 1;
}

/*
> keycode = RL.GetKeyPressed()

Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetKeyPressed( lua_State* L ) {
	lua_pushinteger( L, GetKeyPressed() );

	return 1;
}

/*
> unicode = RL.GetCharPressed()

Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

- Success return int
*/
int lcoreGetCharPressed( lua_State* L ) {
	lua_pushinteger( L, GetCharPressed() );

	return 1;
}

/*
> RL.SetExitKey( int key )

Set a custom key to exit program (default is ESC)
*/
int lcoreSetExitKey( lua_State* L ) {
	int key = luaL_checkinteger( L, 1 );

	SetExitKey( key );

	return 0;
}

/*
## Core - Input-related functions: gamepads
*/

/*
> available = RL.IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Success return bool
*/
int lcoreIsGamepadAvailable( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsGamepadAvailable( gamepad ) );

	return 1;
}

/*
> name = RL.GetGamepadName( int gamepad )

Return gamepad internal name id

- Success return string
*/
int lcoreGetGamepadName( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );

	lua_pushstring( L, GetGamepadName( gamepad ) );

	return 1;
}

/*
> pressed = RL.IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Success return bool
*/
int lcoreIsGamepadButtonPressed( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );
	int button = luaL_checkinteger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonPressed( gamepad, button ) );

	return 1;
}

/*
> pressed = RL.IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Success return bool
*/
int lcoreIsGamepadButtonDown( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );
	int button = luaL_checkinteger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonDown( gamepad, button ) );

	return 1;
}

/*
> released = RL.IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Success return bool
*/
int lcoreIsGamepadButtonReleased( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );
	int button = luaL_checkinteger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonReleased( gamepad, button ) );

	return 1;
}

/*
> notPressed = RL.IsGamepadButtonUp( int gamepad, int button )

Check if a gamepad button is NOT being pressed

- Success return bool
*/
int lcoreIsGamepadButtonUp( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );
	int button = luaL_checkinteger( L, 2 );

	lua_pushboolean( L, IsGamepadButtonUp( gamepad, button ) );

	return 1;
}

/*
> button = RL.GetGamepadButtonPressed()

Get the last gamepad button pressed

- Success return int
*/
int lcoreGetGamepadButtonPressed( lua_State* L ) {
	lua_pushinteger( L, GetGamepadButtonPressed() );

	return 1;
}

/*
> count = RL.GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Success return int
*/
int lcoreGetGamepadAxisCount( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, GetGamepadAxisCount( gamepad ) );

	return 1;
}

/*
> value = RL.GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Success return float
*/
int lcoreGetGamepadAxisMovement( lua_State* L ) {
	int gamepad = luaL_checkinteger( L, 1 );
	int axis = luaL_checkinteger( L, 2 );

	lua_pushnumber( L, GetGamepadAxisMovement( gamepad, axis ) );

	return 1;
}

/*
> result = RL.SetGamepadMappings( string mappings )

Set internal gamepad mappings (SDL_GameControllerDB)

- Success return int
*/
int lcoreSetGamepadMappings( lua_State* L ) {
	const char* mappings = luaL_checkstring( L, 1 );

	lua_pushnumber( L, SetGamepadMappings( mappings ) );

	return 1;
}

/*
## Core - Input-related functions: mouse
*/

/*
> pressed = RL.IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Success return bool
*/
int lcoreIsMouseButtonPressed( lua_State* L ) {
	int button = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsMouseButtonPressed( button ) );

	return 1;
}

/*
> pressed = RL.IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Success return bool
*/
int lcoreIsMouseButtonDown( lua_State* L ) {
	int button = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsMouseButtonDown( button ) );

	return 1;
}

/*
> released = RL.IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Success return bool
*/
int lcoreIsMouseButtonReleased( lua_State* L ) {
	int button = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsMouseButtonReleased( button ) );

	return 1;
}

/*
> released = RL.IsMouseButtonUp( int button )

Check if a mouse button is NOT being pressed

- Success return bool
*/
int lcoreIsMouseButtonUp( lua_State* L ) {
	int button = luaL_checkinteger( L, 1 );

	/* IsMouseButtonUp is broken. Review when fixed in raylib. */
	lua_pushboolean( L, !IsMouseButtonDown( button ) );
	// lua_pushboolean( L, IsMouseButtonUp( button ) );

	return 1;
}

/*
> position = RL.GetMousePosition()

Returns mouse position

- Success return Vector2
*/
int lcoreGetMousePosition( lua_State* L ) {
	uluaPushVector2( L, GetMousePosition() );

	return 1;
}

/*
> position = RL.GetMouseDelta()

Get mouse delta between frames

- Success return Vector2
*/
int lcoreGetMouseDelta( lua_State* L ) {
	uluaPushVector2( L, GetMouseDelta() );

	return 1;
}

/*
> RL.SetMousePosition( Vector2 position )

Set mouse position XY
*/
int lcoreSetMousePosition( lua_State* L ) {
	Vector2 pos = uluaGetVector2( L, 1 );

	SetMousePosition( pos.x, pos.y );

	return 0;
}

/*
> RL.SetMouseOffset( Vector2 offset )

Set mouse offset
*/
int lcoreSetMouseOffset( lua_State* L ) {
	Vector2 offset = uluaGetVector2( L, 1 );

	SetMouseOffset( offset.x, offset.y );
	state->mouseOffset = offset;

	return 0;
}

/*
> RL.SetMouseScale( Vector2 scale )

Set mouse scaling
*/
int lcoreSetMouseScale( lua_State* L ) {
	Vector2 scale = uluaGetVector2( L, 1 );

	SetMouseScale( scale.x, scale.y );
	state->mouseScale = scale;

	return 0;
}

/*
> offset = RL.GetMouseOffset()

Get mouse offset

- Success return Vector2
*/
int lcoreGetMouseOffset( lua_State* L ) {
	uluaPushVector2( L, state->mouseOffset );

	return 1;
}

/*
> scale = RL.GetMouseScale()

Get mouse scale

- Success return Vector2
*/
int lcoreGetMouseScale( lua_State* L ) {
	uluaPushVector2( L, state->mouseScale );

	return 1;
}

/*
> movement = RL.GetMouseWheelMove()

Get mouse wheel movement for X or Y, whichever is larger

- Success return float
*/
int lcoreGetMouseWheelMove( lua_State* L ) {
	lua_pushnumber( L, GetMouseWheelMove() );

	return 1;
}

/*
> movement = RL.GetMouseWheelMoveV()

Get mouse wheel movement for both X and Y

- Success return Vector2
*/
int lcoreGetMouseWheelMoveV( lua_State* L ) {
	uluaPushVector2( L, GetMouseWheelMoveV() );

	return 1;
}

/*
> RL.SetMouseCursor( int cursor )

Set mouse cursor
*/
int lcoreSetMouseCursor( lua_State* L ) {
	int cursor = luaL_checkinteger( L, 1 );

	SetMouseCursor( cursor );

	return 0;
}

/*
## Core - Input-related functions: touch
*/

/*
> position = RL.GetTouchPosition( int index )

Get touch position XY for a touch point index (relative to screen size)

- Success return Vector2
*/
int lcoreGetTouchPosition( lua_State* L ) {
	int index = luaL_checkinteger( L, 1 );

	uluaPushVector2( L, GetTouchPosition( index ) );

	return 1;
}

/*
> id = RL.GetTouchPointId( int index )

Get touch point identifier for given index

- Success return int
*/
int lcoreGetTouchPointId( lua_State* L ) {
	int index = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, GetTouchPointId( index ) );

	return 1;
}

/*
> count = RL.GetTouchPointCount()

Get touch point identifier for given index

- Success return int
*/
int lcoreGetTouchPointCount( lua_State* L ) {
	lua_pushinteger( L, GetTouchPointCount() );

	return 1;
}

/*
## Core - Input-related functions: gestures
*/

/*
> RL.SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags
*/
int lcoreSetGesturesEnabled( lua_State* L ) {
	unsigned int flags = (unsigned int)luaL_checkinteger( L, 1 );

	SetGesturesEnabled( flags );

	return 0;
}

/*
> detected = RL.IsGestureDetected( int gesture )

Check if a gesture have been detected

- Success return bool
*/
int lcoreIsGestureDetected( lua_State* L ) {
	int gesture = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, IsGestureDetected( gesture ) );

	return 1;
}

/*
> gesture = RL.GetGestureDetected()

Get latest detected gesture

- Success return int
*/
int lcoreGetGestureDetected( lua_State* L ) {
	lua_pushinteger( L, GetGestureDetected() );

	return 1;
}

/*
> time = RL.GetGestureHoldDuration()

Get gesture hold time in milliseconds

- Success return float
*/
int lcoreGetGestureHoldDuration( lua_State* L ) {
	lua_pushnumber( L, GetGestureHoldDuration() );

	return 1;
}

/*
> vector = RL.GetGestureDragVector()

Get gesture drag vector

- Success return Vector2
*/
int lcoreGetGestureDragVector( lua_State* L ) {
	uluaPushVector2( L, GetGestureDragVector() );

	return 1;
}

/*
> angle = RL.GetGestureDragAngle()

Get gesture drag angle

- Success return float
*/
int lcoreGetGestureDragAngle( lua_State* L ) {
	lua_pushnumber( L, GetGestureDragAngle() );

	return 1;
}

/*
> vector = RL.GetGesturePinchVector()

Get gesture pinch delta

- Success return Vector2
*/
int lcoreGetGesturePinchVector( lua_State* L ) {
	uluaPushVector2( L, GetGesturePinchVector() );

	return 1;
}

/*
> angle = RL.GetGesturePinchAngle()

Get gesture pinch angle

- Success return float
*/
int lcoreGetGesturePinchAngle( lua_State* L ) {
	lua_pushnumber( L, GetGesturePinchAngle() );

	return 1;
}

/*
## Core - Camera2D System functions
*/

/*
> camera2D = RL.CreateCamera2D()

Return camera2D set to default configuration

- Success return Camera2D
*/
int lcoreCreateCamera2D( lua_State* L ) {
	Camera2D camera = { 0 };
	
	camera.offset = (Vector2){ 0.0, 0.0 };
	camera.target = (Vector2){ 0.0, 0.0 };
	camera.rotation = 0.0;
	camera.zoom = 1.0;

	uluaPushCamera2D( L, camera );

	return 1;
}

/*
> RL.SetCamera2DTarget( camera2D camera, Vector2 target )

Set camera target (rotation and zoom origin)
*/
int lcoreSetCamera2DTarget( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	Vector2 target = uluaGetVector2( L, 2 );

	camera->target = target;

	return 0;
}

/*
> RL.SetCamera2DOffset( camera2D camera, Vector2 offset )

Set camera offset (displacement from target)
*/
int lcoreSetCamera2DOffset( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	Vector2 offset = uluaGetVector2( L, 2 );

	camera->offset = offset;

	return 0;
}

/*
> RL.SetCamera2DRotation( camera2D camera, float rotation )

Set camera rotation in degrees
*/
int lcoreSetCamera2DRotation( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	float rotation = luaL_checknumber( L, 2 );

	camera->rotation = rotation;

	return 0;
}

/*
> RL.SetCamera2DZoom( camera2D camera, float zoom )

Set camera zoom (scaling), should be 1.0f by default
*/
int lcoreSetCamera2DZoom( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	float zoom = luaL_checknumber( L, 2 );

	camera->zoom = zoom;

	return 0;
}

/*
> target = RL.GetCamera2DTarget( camera2D camera )

Get camera2D target

- Success return Vector2
*/
int lcoreGetCamera2DTarget( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );

	uluaPushVector2( L, camera->target );

	return 1;
}

/*
> offset = RL.GetCamera2DOffset( camera2D camera )

Get camera2D offset

- Success return Vector2
*/
int lcoreGetCamera2DOffset( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	uluaPushVector2( L, camera->offset );

	return 1;
}

/*
> rotation = RL.GetCamera2DRotation( camera2D camera )

Get camera2D rotation

- Success return float
*/
int lcoreGetCamera2DRotation( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	lua_pushnumber( L, camera->rotation );

	return 1;
}

/*
> zoom = RL.GetCamera2DZoom( camera2D camera )

Get camera2D zoom

- Success return float
*/
int lcoreGetCamera2DZoom( lua_State* L ) {
	Camera2D* camera = uluaGetCamera2D( L, 1 );
	lua_pushnumber( L, camera->zoom );

	return 1;
}

/*
## Core - Camera3D System functions
*/

/*
> camera = RL.CreateCamera3D()

Return camera3D id set to default configuration

- Success return int
*/
int lcoreCreateCamera3D( lua_State* L ) {
	Camera3D camera = { 0 };

	camera.position = (Vector3){ 0.0, 0.0, 0.0 };
	camera.target = (Vector3){ 0.0, 0.0, 0.0 };
	camera.up = (Vector3){ 0.0, 0.0, 0.0 };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	uluaPushCamera3D( L, camera );

	return 1;
}

/*
> RL.SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position (Remember to call "RL.UpdateCamera3D()" to apply changes)
*/
int lcoreSetCamera3DPosition( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Vector3 pos = uluaGetVector3( L, 2 );

	camera->position = pos;

	return 0;
}

/*
> RL.SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at
*/
int lcoreSetCamera3DTarget( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Vector3 target = uluaGetVector3( L, 2 );

	camera->target = target;

	return 0;
}

/*
> RL.SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector (Rotation over it's axis)
*/
int lcoreSetCamera3DUp( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Vector3 up = uluaGetVector3( L, 2 );

	camera->up = up;

	return 0;
}

/*
> RL.SetCamera3DFovy( camera3D camera, float fovy )

Set camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
*/
int lcoreSetCamera3DFovy( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float fovy = luaL_checknumber( L, 2 );

	camera->fovy = fovy;

	return 0;
}

/*
> RL.SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC)
*/
int lcoreSetCamera3DProjection( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	int projection = luaL_checkinteger( L, 2 );

	camera->projection = projection;

	return 0;
}

/*
> position = RL.GetCamera3DPosition( camera3D camera )

Get camera position

- Success return Vector3
*/
int lcoreGetCamera3DPosition( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, camera->position );

	return 1;
}

/*
> target = RL.GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Success return Vector3
*/
int lcoreGetCamera3DTarget( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, camera->target );

	return 1;
}

/*
> up = RL.GetCamera3DUp( camera3D camera )

Get camera up vector (Rotation over it's axis)

- Success return Vector3
*/
int lcoreGetCamera3DUp( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, camera->up );

	return 1;
}

/*
> fovy = RL.GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic

- Success return float
*/
int lcoreGetCamera3DFovy( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	lua_pushnumber( L, camera->fovy );

	return 1;
}

/*
> projection = RL.GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Success return int
*/
int lcoreGetCamera3DProjection( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	lua_pushinteger( L, camera->projection );

	return 1;
}

/*
> forward = RL.GetCamera3DForward( camera3D camera )

Returns the cameras forward vector (normalized)

- Success return Vector3
*/
int lcoreGetCamera3DForward( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, GetCameraForward( camera ) );

	return 1;
}

/*
> up = RL.GetCamera3DUpNormalized( camera3D camera )

Returns the cameras up vector (normalized)
Note: The up vector might not be perpendicular to the forward vector

- Success return Vector3
*/
int lcoreGetCamera3DUpNormalized( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, GetCameraUp( camera ) );

	return 1;
}

/*
> right = RL.GetCamera3DRight( camera3D camera )

Returns the cameras right vector (normalized)

- Success return Vector3
*/
int lcoreGetCamera3DRight( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushVector3( L, GetCameraRight( camera ) );

	return 1;
}

/*
> RL.Camera3DMoveForward( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera in it's forward direction
*/
int lcoreCamera3DMoveForward( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float distance = luaL_checknumber( L, 2 );
	bool moveInWorldPlane = uluaGetBoolean( L, 3 );

	CameraMoveForward( camera, distance, moveInWorldPlane );

	return 0;
}

/*
> RL.Camera3DMoveUp( camera3D camera, float distance )

Moves the camera in it's up direction
*/
int lcoreCamera3DMoveUp( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float distance = luaL_checknumber( L, 2 );

	CameraMoveUp( camera, distance );

	return 0;
}

/*
> RL.Camera3DMoveRight( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera target in it's current right direction
*/
int lcoreCamera3DMoveRight( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float distance = luaL_checknumber( L, 2 );
	bool moveInWorldPlane = uluaGetBoolean( L, 3 );

	CameraMoveRight( camera, distance, moveInWorldPlane );

	return 0;
}

/*
> RL.Camera3DMoveToTarget( camera3D camera, float delta )

Moves the camera position closer/farther to/from the camera target
*/
int lcoreCamera3DMoveToTarget( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float delta = luaL_checknumber( L, 2 );

	CameraMoveToTarget( camera, delta );

	return 0;
}

/*
> RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )

Rotates the camera around it's up vector
Yaw is "looking left and right"
If rotateAroundTarget is false, the camera rotates around it's position
Note: angle must be provided in radians
*/
int lcoreCamera3DYaw( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float delta = luaL_checknumber( L, 2 );
	bool rotateAroundTarget = uluaGetBoolean( L, 3 );

	CameraYaw( camera, delta, rotateAroundTarget );

	return 0;
}

/*
> RL.Camera3DPitch( camera3D camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp )

Rotates the camera around it's right vector, pitch is "looking up and down"
- lockView prevents camera overrotation (aka "somersaults")
- rotateAroundTarget defines if rotation is around target or around it's position
- rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
NOTE: angle must be provided in radians
*/
int lcoreCamera3DPitch( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float delta = luaL_checknumber( L, 2 );
	bool lockView = uluaGetBoolean( L, 3 );
	bool rotateAroundTarget = uluaGetBoolean( L, 4 );
	bool rotateUp = uluaGetBoolean( L, 5 );

	CameraPitch( camera, delta, lockView, rotateAroundTarget, rotateUp );

	return 0;
}

/*
> RL.Camera3DRoll( camera3D camera, float angle )

Rotates the camera around it's forward vector
Roll is "turning your head sideways to the left or right"
Note: angle must be provided in radians
*/
int lcoreCamera3DRoll( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float angle = luaL_checknumber( L, 2 );

	CameraRoll( camera, angle );

	return 0;
}

/*
> view = RL.GetCamera3DViewMatrix( camera3D camera )

Returns the camera view matrix

- Success return Matrix
*/
int lcoreGetCamera3DViewMatrix( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );

	uluaPushMatrix( L, GetCameraViewMatrix( camera ) );

	return 1;
}

/*
> projection = RL.GetCamera3DProjectionMatrix( camera3D camera, float aspect )

Returns the camera projection matrix

- Success return Matrix
*/
int lcoreGetCamera3DProjectionMatrix( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	float aspect = luaL_checknumber( L, 2 );

	uluaPushMatrix( L, GetCameraProjectionMatrix( camera, aspect ) );

	return 1;
}

/*
> RL.UpdateCamera3D( camera3D camera, int mode )

Update camera position for selected mode
*/
int lcoreUpdateCamera3D( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	int mode = luaL_checkinteger( L, 2 );

	UpdateCamera( camera, mode );

	return 0;
}

/*
> RL.UpdateCamera3DPro( camera3D camera, Vector3 movement, Vector3 rotation, float zoom )

Update camera movement, movement/rotation values should be provided by user
*/
int lcoreUpdateCamera3DPro( lua_State* L ) {
	Camera3D* camera = uluaGetCamera3D( L, 1 );
	Vector3 movement = uluaGetVector3( L, 2 );
	Vector3 rotation = uluaGetVector3( L, 3 );
	float zoom = luaL_checknumber( L, 4 );

	UpdateCameraPro( camera, movement, rotation, zoom );

	return 0;
}

/*
## Core - Buffer management functions
*/

/*
> buffer = RL.LoadBuffer( data{} buffer, int type )

Load Buffer. Type should be one of the Buffer types. Empty buffer will set data to NULL.

- Success return Buffer
*/
int lcoreLoadBuffer( lua_State* L ) {
	luaL_checktype( L, 1, LUA_TTABLE );
	int type = luaL_checkinteger( L, 2 );

	Buffer buffer = {
		.type = type
	};
	int len = uluaGetTableLen( L, 1 );

	if ( len == 0 ) {
		buffer.size = 0;
		buffer.data = NULL;

		uluaPushBuffer( L, buffer );
		return 1;
	}
	buffer.size = len * getBufferElementSize( &buffer );
	buffer.data = malloc( buffer.size );

	int t = 1;
	int i = 0;
	unsigned char* ucp = buffer.data;
	unsigned short *usp = buffer.data;
	unsigned int* uip = buffer.data;
	char* cp = buffer.data;
	short *sp = buffer.data;
	int* ip = buffer.data;
	float* fp = buffer.data;
	double* dp = buffer.data;
	
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		switch ( type ) {
			case BUFFER_UNSIGNED_CHAR:
				*ucp = (unsigned char)lua_tointeger( L, -1 );
				ucp++;
				break;
			case BUFFER_UNSIGNED_SHORT:
				*usp = (unsigned short)lua_tointeger( L, -1 );
				usp++;
				break;
			case BUFFER_UNSIGNED_INT:
				*uip = (unsigned int)lua_tointeger( L, -1 );
				uip++;
				break;
			case BUFFER_CHAR:
				*cp = (char)lua_tointeger( L, -1 );
				cp++;
				break;
			case BUFFER_SHORT:
				*sp = (short)lua_tointeger( L, -1 );
				sp++;
				break;
			case BUFFER_INT:
				*ip = (int)lua_tointeger( L, -1 );
				ip++;
				break;
			case BUFFER_FLOAT:
				*fp = (float)lua_tonumber( L, -1 );
				fp++;
				break;
			case BUFFER_DOUBLE:
				*dp = (double)lua_tonumber( L, -1 );
				dp++;
				break;
			default:
				break;
		}
		lua_pop( L, 1 );
		i++;
	}
	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> buffer = RL.LoadBufferFromFile( string path, type int )

Read buffer data from binary file

- Failure return nil
- Success return Buffer
*/
int lcoreLoadBufferFromFile( lua_State* L ) {
	const char* path = luaL_checkstring( L, 1 );
	int type = luaL_checkinteger( L, 2 );

	int fileLen = GetFileLength( path );
	Buffer buffer = {
		.type = type,
		.size = fileLen,
		.data = malloc( fileLen )
	};
	size_t elementSize = getBufferElementSize( &buffer );
	FILE* file;
	file = fopen( path, "rb" );

	if ( file == NULL ) {
		TraceLog( LOG_WARNING, "Invalid file %s\n", path );
		lua_pushnil( L );
		return 1;
	}
	fread( buffer.data, elementSize, buffer.size / elementSize, file );
	fclose( file );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> buffer = RL.LoadBufferFromString( string buffer )

Read buffer data from string

- Failure return nil
- Success return Buffer
*/
int lcoreLoadBufferFromString( lua_State* L ) {
	size_t len = 0;
	const char* string = luaL_checklstring( L, 1, &len );

	Buffer buffer = {
		.type = BUFFER_UNSIGNED_CHAR,
		.size = len,
		.data = malloc( len * sizeof( unsigned char ) )
	};
	memcpy( buffer.data, string, len );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> RL.UnloadBuffer( Buffer buffer )

Unload buffer data
*/
int lcoreUnloadBuffer( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	unloadBuffer( buffer );
	memset( buffer, 0, sizeof( Buffer ) );

	return 0;
}

/*
> data = RL.GetBufferData( Buffer buffer, int position, int length )

Get buffer data as table in the format it was stored

- Success return data{}
*/
int lcoreGetBufferData( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );
	size_t position = luaL_checkinteger( L, 2 );
	size_t length = luaL_checkinteger( L, 3 );

	if ( buffer->type == BUFFER_UNSIGNED_CHAR ) {
		unsigned char* p = buffer->data + position * sizeof( unsigned char );
		size_t bufLen = buffer->size / sizeof( unsigned char );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (unsigned char)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_UNSIGNED_SHORT ) {
		unsigned short *p = buffer->data + position * sizeof( unsigned short );
		size_t bufLen = buffer->size / sizeof( unsigned short );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (unsigned short)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_UNSIGNED_INT ) {
		unsigned int* p = buffer->data + position * sizeof( unsigned int );
		size_t bufLen = buffer->size / sizeof( unsigned int );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (unsigned int)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_CHAR ) {
		char* p = buffer->data + position * sizeof( char );
		size_t bufLen = buffer->size / sizeof( char );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (char)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_SHORT ) {
		short *p = buffer->data + position * sizeof( short );
		size_t bufLen = buffer->size / sizeof( short );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (short)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_INT ) {
		int* p = buffer->data + position * sizeof( int );
		size_t bufLen = buffer->size / sizeof( int );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushinteger( L, (int)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_FLOAT ) {
		float* p = buffer->data + position * sizeof( float );
		size_t bufLen = buffer->size / sizeof( float );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushnumber( L, (float)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	else if ( buffer->type == BUFFER_DOUBLE ) {
		double* p = buffer->data + position * sizeof( double );
		size_t bufLen = buffer->size / sizeof( double );
		size_t count = bufLen < ( position + length ) ? ( position + length ) - bufLen : length;
		lua_createtable( L, count, 0 );

		for ( int i = 0; i < count; i++ ) {
			lua_pushnumber( L, (double)*p );
			lua_rawseti( L, -2, i+1 );
			p++;
		}
	}
	return 1;
}

/*
> type = RL.GetBufferType( Buffer buffer )

Get buffer type

- Success return int
*/
int lcoreGetBufferType( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	lua_pushinteger( L, buffer->type );

	return 1;
}

/*
> size = RL.GetBufferSize( Buffer buffer )

Get buffer size in bytes

- Success return int
*/
int lcoreGetBufferSize( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	lua_pushinteger( L, buffer->size );

	return 1;
}

/*
> size = RL.GetBufferElementSize( Buffer buffer )

Get buffer element size in bytes

- Success return int
*/
int lcoreGetBufferElementSize( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	lua_pushinteger( L, getBufferElementSize( buffer ) );

	return 1;
}

/*
> length = RL.GetBufferLength( Buffer buffer )

Get buffer element count

- Success return int
*/
int lcoreGetBufferLength( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	lua_pushinteger( L, buffer->size / getBufferElementSize( buffer ) );

	return 1;
}

/*
> RL.ExportBuffer( Buffer buffer, string path )

Write buffer data to binary file
*/
int lcoreExportBuffer( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );
	const char* path = luaL_checkstring( L, 2 );

	size_t elementSize = getBufferElementSize( buffer );
	FILE* file;
	file = fopen( path, "wb" );

	fwrite( buffer->data, elementSize, buffer->size / elementSize, file );
	fclose( file );

	return 0;
}
