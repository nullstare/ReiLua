local tileTexture = -1
local camera = -1
local cameraPos = { 0, 0 }
local cameraRot = 0.0
local cameraZoom = 1.0
local cameraSpeed = 100.0
local cameraRotSpeed = 100.0
local cameraZoomSpeed = 2.0

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()
	
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL.SetWindowTitle( "Camera 2D" )

	tileTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/tiles.png" )
	camera = RL.CreateCamera2D()
	RL.SetCamera2DOffset( camera, { winSize[1] / 2, winSize[2] / 2 } )
end

function RL.update( delta )
	-- Move.
	if RL.IsKeyDown( RL.KEY_RIGHT ) then
		cameraPos[1] = cameraPos[1] + cameraSpeed * delta
	elseif RL.IsKeyDown( RL.KEY_LEFT ) then
		cameraPos[1] = cameraPos[1] - cameraSpeed * delta
	end
	if RL.IsKeyDown( RL.KEY_DOWN ) then
		cameraPos[2] = cameraPos[2] + cameraSpeed * delta
	elseif RL.IsKeyDown( RL.KEY_UP ) then
		cameraPos[2] = cameraPos[2] - cameraSpeed * delta
	end
	-- Rotate.
	if RL.IsKeyDown( RL.KEY_E ) then
		cameraRot = cameraRot + cameraRotSpeed * delta
	elseif RL.IsKeyDown( RL.KEY_Q ) then
		cameraRot = cameraRot - cameraRotSpeed * delta
	end
	-- Zoom.
	if RL.IsKeyDown( RL.KEY_R ) then
		cameraZoom = cameraZoom + cameraZoom * cameraZoomSpeed * delta
	elseif RL.IsKeyDown( RL.KEY_F ) then
		cameraZoom = cameraZoom - cameraZoom * cameraZoomSpeed * delta
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.SetCamera2DTarget( camera, cameraPos )
	RL.SetCamera2DRotation( camera, cameraRot )
	RL.SetCamera2DZoom( camera, cameraZoom )
	
	RL.BeginMode2D( camera )
		-- Draw wall.
		for y = 0, 4 do
			for x = 0, 6 do
				RL.DrawTextureRec( tileTexture, { 0, 0, 32, 32 }, { x * 32, y * 32 }, RL.WHITE )
			end
		end

		-- Draw hero.
		RL.DrawTextureRec( tileTexture, { 3 * 32, 0, 32, 32 }, { cameraPos[1] - 16, cameraPos[2] - 16 }, RL.WHITE )
	RL.EndMode2D()
end
