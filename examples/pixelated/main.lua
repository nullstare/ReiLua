local tex = -1
local pos = { 32, 32 }
local speed = 60.0
local monitor = 0
local mPos = RL.GetMonitorPosition( monitor )
local mSize = RL.GetMonitorSize( monitor )
local framebuffer = -1
local res = { 320, 180 }
local scale = 5
local winSize = { res[1] * scale, res[2] * scale }

function RL.init()
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL.SetWindowSize( winSize )
	tex = RL.LoadTexture( RL.GetBasePath().."../resources/images/cat.png" )
	-- Create framebuffer.
	framebuffer = RL.LoadRenderTexture( res )
end

function RL.process( delta )
	if RL.IsKeyDown( RL.KEY_RIGHT ) then
		pos[1] = pos[1] + delta * speed
	elseif RL.IsKeyDown( RL.KEY_LEFT ) then
		pos[1] = pos[1] - delta * speed
	end

	if RL.IsKeyDown( RL.KEY_UP ) then
		pos[2] = pos[2] - delta * speed
	elseif RL.IsKeyDown( RL.KEY_DOWN ) then
		pos[2] = pos[2] + delta * speed
	end

	if RL.IsWindowResized() then
		winSize = RL.GetScreenSize()
	end
end

function RL.draw()
	RL.ClearBackground( { 0, 0, 0 } )

	RL.BeginTextureMode( framebuffer )
		RL.ClearBackground( { 100, 150, 100 } )
		RL.DrawPixel( { 100, 100 }, { 255, 50, 100 } )
		RL.DrawLine( { 120, 100 }, { 140, 150 }, 2.4, { 255, 150, 255 } )
		RL.DrawRectangle( { 200, 120, 40, 50 }, { 100, 170, 255 } )
		RL.DrawTexturePro( tex, { 166, 138, 128, 128 }, { pos[1], pos[2], 128, 128 }, { 16, 16 }, 0.0, RL.WHITE )
		RL.DrawText( 0, "Cat MIAU!!", { 16, 32 }, 10, 1, { 255, 180, 155 } )
		RL.DrawTriangle( { 0, 32 }, { 32, 16 }, { 0, 0 }, RL.RED )
	RL.EndTextureMode()

	RL.SetTextureSource( RL.TEXTURE_SOURCE_RENDER_TEXTURE )
	RL.DrawTexturePro( framebuffer, { 0, 0, res[1], -res[2] }, { 0, 0, winSize[1], winSize[2] }, { 0, 0 }, 0.0, { 255, 255, 255 } )
	RL.SetTextureSource( RL.TEXTURE_SOURCE_TEXTURE )
end
