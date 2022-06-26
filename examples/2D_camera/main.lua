local tileTexture = -1
local camera = -1
local cameraPos = { 0, 0 }
local cameraRot = 0.0
local cameraZoom = 1.0
local cameraSpeed = 100.0
local cameraRotSpeed = 100.0
local cameraZoomSpeed = 10.0

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()
	
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowTitle( "Camera 2D" )

	tileTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/tiles.png" )
	camera = RL_CreateCamera2D()
	RL_SetCamera2DOffset( camera, { winSize[1] / 2, winSize[2] / 2 } )
end

function process( delta )
	-- Move.
	if RL_IsKeyDown( KEY_RIGHT ) then
		cameraPos[1] = cameraPos[1] + cameraSpeed * delta
	elseif RL_IsKeyDown( KEY_LEFT ) then
		cameraPos[1] = cameraPos[1] - cameraSpeed * delta
	end
	if RL_IsKeyDown( KEY_DOWN ) then
		cameraPos[2] = cameraPos[2] + cameraSpeed * delta
	elseif RL_IsKeyDown( KEY_UP ) then
		cameraPos[2] = cameraPos[2] - cameraSpeed * delta
	end
	-- Rotate.
	if RL_IsKeyDown( string.byte( "E" ) ) then
		cameraRot = cameraRot + cameraRotSpeed * delta
	elseif RL_IsKeyDown( string.byte( "Q" ) ) then
		cameraRot = cameraRot - cameraRotSpeed * delta
	end
	-- Zoom.
	if RL_IsKeyDown( string.byte( "R" ) ) then
		cameraZoom = cameraZoom + cameraZoomSpeed * delta
	elseif RL_IsKeyDown( string.byte( "F" ) ) then
		cameraZoom = cameraZoom - cameraZoomSpeed * delta
	end
end

function draw()
	RL_ClearBackground( RAYWHITE )
	RL_SetCamera2DTarget( camera, cameraPos )
	RL_SetCamera2DRotation( camera, cameraRot )
	RL_SetCamera2DZoom( camera, cameraZoom )
	
	RL_BeginMode2D( camera )
		-- Draw wall.
		for y = 0, 4 do
			for x = 0, 6 do
				RL_DrawTextureRec( tileTexture, { 0, 0, 32, 32 }, { x * 32, y * 32 }, WHITE )
			end
		end
		-- Draw hero.
		RL_DrawTextureRec( tileTexture, { 3 * 32, 0, 32, 32 }, { cameraPos[1] - 16, cameraPos[2] - 16 }, WHITE )
	RL_EndMode2D()
end
