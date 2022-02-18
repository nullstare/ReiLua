#pragma once

/* Validators. */
bool validCamera3D( size_t id );
/* Window. */
int lcoreSetWindowMonitor( lua_State *L );
int lcoreSetWindowPosition( lua_State *L );
int lcoreSetWindowSize( lua_State *L );
int lcoreGetMonitorPosition( lua_State *L );
int lcoreGetMonitorSize( lua_State *L );
int lcoreGetWindowPosition( lua_State *L );
int lcoreGetWindowSize( lua_State *L );
int lcoreSetWindowState( lua_State *L );
int lcoreIsWindowState( lua_State *L );
int lcoreClearWindowState( lua_State *L );
int lcoreIsWindowResized( lua_State *L );
int lcoreSetWindowIcon( lua_State *L );
int lcoreSetWindowTitle( lua_State *L );
/* Timing. */
int lcoreSetTargetFPS( lua_State *L );
int lcoreGetFrameTime( lua_State *L );
int lcoreGetTime( lua_State *L );
/* Misc. */
int lcoreTraceLog( lua_State *L );
int lcoreOpenURL( lua_State *L );
/* Cursor. */
int lcoreShowCursor( lua_State *L );
int lcoreHideCursor( lua_State *L );
int lcoreIsCursorHidden( lua_State *L );
int lcoreEnableCursor( lua_State *L );
int lcoreDisableCursor( lua_State *L );
int lcoreIsCursorOnScreen( lua_State *L );
/* Drawing. */
int lcoreClearBackground( lua_State *L );
int lcoreBeginBlendMode( lua_State *L );
int lcoreEndBlendMode( lua_State *L );
int lcoreBeginScissorMode( lua_State *L );
int lcoreEndScissorMode( lua_State *L );
/* Shader. */
int lcoreLoadShader( lua_State *L );
int lcoreLoadShaderFromMemory( lua_State *L );
int lcoreBeginShaderMode( lua_State *L );
int lcoreEndShaderMode( lua_State *L );
int lcoreGetShaderLocation( lua_State *L );
int lcoreGetShaderLocationAttrib( lua_State *L );
int lcoreSetShaderValueMatrix( lua_State *L );
int lcoreSetShaderValueTexture( lua_State *L );
int lcoreSetShaderValue( lua_State *L );
int lcoreSetShaderValueV( lua_State *L );
int lcoreUnloadShader( lua_State *L );
/* File. */
int lcoreGetBasePath( lua_State *L );
int lcoreFileExists( lua_State *L );
int lcoreDirectoryExists( lua_State *L );
int lcoreIsFileExtension( lua_State *L );
int lcoreGetFileExtension( lua_State *L );
int lcoreGetFileName( lua_State *L );
int lcoreGetFileNameWithoutExt( lua_State *L );
int lcoreGetDirectoryPath( lua_State *L );
int lcoreGetPrevDirectoryPath( lua_State *L );
int lcoreGetWorkingDirectory( lua_State *L );
int lcoreGetDirectoryFiles( lua_State *L );
int lcoreGetFileModTime( lua_State *L );
/* Camera. */
int lcoreCreateCamera3D( lua_State *L );
int lcoreUnloadCamera3D( lua_State *L );
int lcoreBeginMode3D( lua_State *L );
int lcoreEndMode3D( lua_State *L );
int lcoreSetCamera3DPosition( lua_State *L );
int lcoreSetCamera3DTarget( lua_State *L );
int lcoreSetCamera3DUp( lua_State *L );
int lcoreSetCamera3DFovy( lua_State *L );
int lcoreSetCamera3DProjection( lua_State *L );
int lcoreGetCamera3DPosition( lua_State *L );
int lcoreGetCamera3DTarget( lua_State *L );
int lcoreGetCamera3DUp( lua_State *L );
int lcoreGetCamera3DFovy( lua_State *L );
int lcoreGetCamera3DProjection( lua_State *L );
int lcoreUpdateCamera3D( lua_State *L );
int lcoreSetCamera3DMode( lua_State *L );
/* Input. */
int lcoreIsKeyPressed( lua_State *L );
int lcoreIsKeyDown( lua_State *L );
int lcoreIsKeyReleased( lua_State *L );
int lcoreGetKeyPressed( lua_State *L );
int lcoreGetCharPressed( lua_State *L );
int lcoreSetExitKey( lua_State *L );
int lcoreIsGamepadAvailable( lua_State *L );
int lcoreIsGamepadButtonPressed( lua_State *L );
int lcoreIsGamepadButtonDown( lua_State *L );
int lcoreIsGamepadButtonReleased( lua_State *L );
int lcoreGetGamepadAxisCount( lua_State *L );
int lcoreGetGamepadAxisMovement( lua_State *L );
int lcoreGetGamepadName( lua_State *L );
int lcoreIsMouseButtonPressed( lua_State *L );
int lcoreIsMouseButtonDown( lua_State *L );
int lcoreIsMouseButtonReleased( lua_State *L );
int lcoreGetMousePosition( lua_State *L );
int lcoreGetMouseDelta( lua_State *L );
int lcoreGetMouseWheelMove( lua_State *L );
int lcoreSetMousePosition( lua_State *L );
