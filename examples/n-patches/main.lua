package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vec2 = require( "vector2" )
Rect = require( "rectangle" )

local dstRec = Rect:new( 100.0, 100.0, 8.0, 8.0 )
local origin = Vec2:new( 0.0, 0.0 )
local stretched = true
local ninePatchInfo = { source = { 0, 0, 96, 96 }, left = 32, top = 32, right = 32, bottom = 32, layout = RL.NPATCH_NINE_PATCH }
-- local ninePatchInfo = { source = { 0, 0, 96, 96 }, left = 32, top = 32, right = 32, bottom = 32, layout = RL.NPATCH_THREE_PATCH_VERTICAL }
-- local ninePatchInfo = { source = { 0, 0, 96, 96 }, left = 32, top = 32, right = 32, bottom = 32, layout = RL.NPATCH_THREE_PATCH_HORIZONTAL }
local nPatchTexture = nil

function RL.init()
	RL.SetWindowTitle( "N-Patches" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	nPatchTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/nPatch.png" )
end

function RL.update( delta )
	local mousePosition = Vec2:newT( RL.GetMousePosition() )

    -- Resize the n-patch based on mouse position
	dstRec.width = mousePosition.x - dstRec.x;
	dstRec.height = mousePosition.y - dstRec.y;

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		stretched = not stretched
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	local modeText = "Stretched"

	if stretched then
		RL.DrawTextureNPatch( nPatchTexture, ninePatchInfo, dstRec, origin, 0.0, RL.WHITE )
	else
		RL.DrawTextureNPatchRepeat( nPatchTexture, ninePatchInfo, dstRec, origin, 0.0, RL.WHITE )
		modeText = "Repeat"
	end

	RL.DrawText( "Press space to toggle mode: "..modeText, { 20, 20 }, 20, RL.BLACK )
end
