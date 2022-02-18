local tex = -1
local pos = { 32, 32 }
local speed = 60.0
local sound = -1
local monitor = 0
local mPos = RL_GetMonitorPosition( monitor )
local mSize = RL_GetMonitorSize( monitor )
local framebuffer = -1
local res = { 320, 180 }
local scale = 5
local winSize = { res[1] * scale, res[2] * scale }

function init()
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	RL_SetWindowSize( winSize )
	tex = RL_LoadTexture( RL_GetBasePath().."../resources/images/cat.png" )
	-- Create framebuffer.
	framebuffer = RL_LoadRenderTexture( res )
end

function process( delta )
	if RL_IsKeyDown( KEY_RIGHT ) then
		pos[1] = pos[1] + delta * speed
	elseif RL_IsKeyDown( KEY_LEFT ) then
		pos[1] = pos[1] - delta * speed
	end

	if RL_IsKeyDown( KEY_UP ) then
		pos[2] = pos[2] - delta * speed
	elseif RL_IsKeyDown( KEY_DOWN ) then
		pos[2] = pos[2] + delta * speed
	end

	if RL_IsWindowResized() then
		winSize = RL_GetWindowSize()
	end
end

function draw()
	RL_ClearBackground( { 0, 0, 0 } )

	RL_BeginTextureMode( framebuffer )
		RL_ClearBackground( { 100, 150, 100 } )
		RL_DrawPixel( { 100, 100 }, { 255, 50, 100 } )
		RL_DrawLine( { 120, 100 }, { 140, 150 }, 2.4, { 255, 150, 255 } )
		RL_DrawRectangle( { 200, 120, 40, 50 }, { 100, 170, 255 } )
		RL_DrawTexturePro( tex, { 166, 138, 128, 128 }, { pos[1], pos[2], 128, 128 }, { 16, 16 }, 0.0, WHITE )
		RL_DrawText( 0, "Cat MIAU!!", { 16, 32 }, 10, 1, { 255, 180, 155 } )
	RL_EndTextureMode()

	RL_SetTextureSource( TEXTURE_SOURCE_RENDER_TEXTURE )
	RL_DrawTexturePro( framebuffer, { 0, 0, res[1], -res[2] }, { 0, 0, winSize[1], winSize[2] }, { 0, 0 }, 0.0, { 255, 255, 255 } )
	RL_SetTextureSource( TEXTURE_SOURCE_TEXTURE )
end
