local dstRec = { 160.0, 160.0, 8.0, 8.0 };
local origin = { 0.0, 0.0 }

-- local ninePatchInfo = { { 0.0, 0.0, 24.0, 24.0 }, 8, 8, 8, 8, NPATCH_NINE_PATCH }
local ninePatchInfo = { source = { 0, 0, 24.0, 24.0 }, left = 8, top = 8, right = 8, bottom = 8, layout = RL.NPATCH_NINE_PATCH }

local nPatchTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/ui_border.png" )

function RL.init()
	RL.SetWindowTitle( "N-Patches" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

function RL.process( delta )
	local mousePosition = RL.GetMousePosition();

    -- Resize the n-patch based on mouse position
	dstRec[3] = mousePosition[1] - dstRec[1];
	dstRec[4] = mousePosition[2] - dstRec[2];
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.DrawTextureNPatch( nPatchTexture, ninePatchInfo, dstRec, origin, 0.0, RL.WHITE )
end
