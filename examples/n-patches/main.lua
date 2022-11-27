local dstRec = { 160.0, 160.0, 8.0, 8.0 };
local origin = { 0.0, 0.0 }

-- local ninePatchInfo = { { 0.0, 0.0, 24.0, 24.0 }, 8, 8, 8, 8, NPATCH_NINE_PATCH }
local ninePatchInfo = { source = { 0, 0, 24.0, 24.0 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }

local nPatchTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/n-patch.png" )

function init()
	RL_SetWindowTitle( "N-Patches" )
	RL_SetWindowState( FLAG_VSYNC_HINT )
end

function process( delta )
	local mousePosition = RL_GetMousePosition();

    -- Resize the n-patch based on mouse position
	dstRec[3] = mousePosition[1] - dstRec[1];
	dstRec[4] = mousePosition[2] - dstRec[2];
end

function draw()
	RL_ClearBackground( RAYWHITE )
	RL_DrawTextureNPatch( nPatchTexture, ninePatchInfo, dstRec, origin, 0.0, WHITE )
end
