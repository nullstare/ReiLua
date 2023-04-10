#pragma once

/* Validators. */
bool validCamera3D( size_t id );
bool validShader( size_t id );
/* Window. */
int lcoreIsWindowReady( lua_State *L );
int lcoreIsWindowFullscreen( lua_State *L );
int lcoreIsWindowHidden( lua_State *L );
int lcoreIsWindowMinimized( lua_State *L );
int lcoreIsWindowMaximized( lua_State *L );
int lcoreIsWindowFocused( lua_State *L );
int lcoreSetWindowMonitor( lua_State *L );
int lcoreSetWindowPosition( lua_State *L );
int lcoreSetWindowSize( lua_State *L );
int lcoreSetWindowMinSize( lua_State *L );
int lcoreGetMonitorPosition( lua_State *L );
int lcoreGetMonitorSize( lua_State *L );
int lcoreGetWindowPosition( lua_State *L );
int lcoreGetScreenSize( lua_State *L );
int lcoreSetWindowState( lua_State *L );
int lcoreIsWindowState( lua_State *L );
int lcoreClearWindowState( lua_State *L );
int lcoreIsWindowResized( lua_State *L );
int lcoreSetWindowIcon( lua_State *L );
int lcoreSetWindowTitle( lua_State *L );
int lcoreGetMonitorCount( lua_State *L );
int lcoreGetCurrentMonitor( lua_State *L );
int lcoreGetMonitorPhysicalSize( lua_State *L );
int lcoreGetMonitorRefreshRate( lua_State *L );
int lcoreGetWindowScaleDPI( lua_State *L );
int lcoreGetMonitorName( lua_State *L );
int lcoreCloseWindow( lua_State *L );
int lcoreSetClipboardText( lua_State *L );
int lcoreGetClipboardText( lua_State *L );
/* Timing. */
int lcoreSetTargetFPS( lua_State *L );
int lcoreGetFPS( lua_State *L );
int lcoreGetFrameTime( lua_State *L );
int lcoreGetTime( lua_State *L );
/* Misc. */
int lcoreTakeScreenshot( lua_State *L );
int lcoreSetConfigFlags( lua_State *L );
int lcoreTraceLog( lua_State *L );
int lcoreSetTraceLogLevel( lua_State *L );
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
int lcoreBeginDrawing( lua_State *L );
int lcoreEndDrawing( lua_State *L );
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
int lcoreSetShaderLocationIndex( lua_State *L );
int lcoreGetShaderLocationIndex( lua_State *L );
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
int lcoreGetFileLength( lua_State *L );
int lcoreGetFileExtension( lua_State *L );
int lcoreGetFileName( lua_State *L );
int lcoreGetFileNameWithoutExt( lua_State *L );
int lcoreGetDirectoryPath( lua_State *L );
int lcoreGetPrevDirectoryPath( lua_State *L );
int lcoreGetWorkingDirectory( lua_State *L );
int lcoreLoadDirectoryFiles( lua_State *L );
int lcoreLoadDirectoryFilesEx( lua_State *L );
int lcoreChangeDirectory( lua_State *L );
int lcoreIsPathFile( lua_State *L );
int lcoreIsFileDropped( lua_State *L );
int lcoreLoadDroppedFiles( lua_State *L );
int lcoreGetFileModTime( lua_State *L );
/* Camera2D. */
int lcoreCreateCamera2D( lua_State *L );
int lcoreUnloadCamera2D( lua_State *L );
int lcoreBeginMode2D( lua_State *L );
int lcoreEndMode2D( lua_State *L );
int lcoreSetCamera2DTarget( lua_State *L );
int lcoreSetCamera2DOffset( lua_State *L );
int lcoreSetCamera2DRotation( lua_State *L );
int lcoreSetCamera2DZoom( lua_State *L );
int lcoreGetCamera2DTarget( lua_State *L );
int lcoreGetCamera2DOffset( lua_State *L );
int lcoreGetCamera2DRotation( lua_State *L );
int lcoreGetCamera2DZoom( lua_State *L );
/* Camera3D. */
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
int lcoreGetCamera3DForward( lua_State *L );
int lcoreGetCamera3DUpNormalized( lua_State *L );
int lcoreGetCamera3DRight( lua_State *L );
int lcoreCamera3DMoveForward( lua_State *L );
int lcoreCamera3DMoveUp( lua_State *L );
int lcoreCamera3DMoveRight( lua_State *L );
int lcoreCamera3DMoveToTarget( lua_State *L );
int lcoreCamera3DYaw( lua_State *L );
int lcoreCamera3DPitch( lua_State *L );
int lcoreCamera3DRoll( lua_State *L );
int lcoreGetCamera3DViewMatrix( lua_State *L );
int lcoreGetCamera3DProjectionMatrix( lua_State *L );
int lcoreUpdateCamera3D( lua_State *L );
int lcoreUpdateCamera3DPro( lua_State *L );
/* Input-related Keyboard. */
int lcoreIsKeyPressed( lua_State *L );
int lcoreIsKeyDown( lua_State *L );
int lcoreIsKeyReleased( lua_State *L );
int lcoreIsKeyUp( lua_State *L );
int lcoreGetKeyPressed( lua_State *L );
int lcoreGetCharPressed( lua_State *L );
int lcoreSetExitKey( lua_State *L );
int lcoreGetKeyName( lua_State *L );
int lcoreGetKeyScancode( lua_State *L );
/* Input-related Gamepad. */
int lcoreIsGamepadAvailable( lua_State *L );
int lcoreIsGamepadButtonPressed( lua_State *L );
int lcoreIsGamepadButtonDown( lua_State *L );
int lcoreIsGamepadButtonReleased( lua_State *L );
int lcoreGetGamepadAxisCount( lua_State *L );
int lcoreGetGamepadAxisMovement( lua_State *L );
int lcoreGetGamepadName( lua_State *L );
/* Input-related Mouse. */
int lcoreIsMouseButtonPressed( lua_State *L );
int lcoreIsMouseButtonDown( lua_State *L );
int lcoreIsMouseButtonReleased( lua_State *L );
int lcoreIsMouseButtonUp( lua_State *L );
int lcoreGetMousePosition( lua_State *L );
int lcoreGetMouseDelta( lua_State *L );
int lcoreSetMousePosition( lua_State *L );
int lcoreSetMouseOffset( lua_State *L );
int lcoreSetMouseScale( lua_State *L );
int lcoreGetMouseWheelMove( lua_State *L );
int lcoreSetMouseCursor( lua_State *L );
/* Input-related Touch */
int lcoreGetTouchPosition( lua_State *L );
int lcoreGetTouchPointId( lua_State *L );
int lcoreGetTouchPointCount( lua_State *L );
/* Input-related Gestures. */
int lcoreSetGesturesEnabled( lua_State *L );
int lcoreIsGestureDetected( lua_State *L );
int lcoreGetGestureDetected( lua_State *L );
int lcoreGetGestureHoldDuration( lua_State *L );
int lcoreGetGestureDragVector( lua_State *L );
int lcoreGetGestureDragAngle( lua_State *L );
int lcoreGetGesturePinchVector( lua_State *L );
int lcoreGetGesturePinchAngle( lua_State *L );
/* Screen-space. */
int lcoreGetMouseRay( lua_State *L );
int lcoreGetCameraMatrix( lua_State *L );
int lcoreGetCameraMatrix2D( lua_State *L );
int lcoreGetWorldToScreen( lua_State *L );
int lcoreGetWorldToScreenEx( lua_State *L );
int lcoreGetWorldToScreen2D( lua_State *L );
int lcoreGetScreenToWorld2D( lua_State *L );
