-- Followed this tutorial. https://www.youtube.com/watch?v=_EurjoraotA

local monitor = 0
local camera = -1
local texture = nil
local material = -1
local model = -1
local animations = {}
local frame = 0
local curAnim = 0
local frameCount = 0
local animSpeed = 60

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { 0, 2, 4 } )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )

	texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/monkey_tex.png" )

	material = RL.CreateMaterial( {
		maps = {
			{
				RL.MATERIAL_MAP_ALBEDO,
				{
					texture = texture,
					color = RL.WHITE,
				},
			},
		},
	} )

	model = RL.LoadModel( RL.GetBasePath().."../resources/iqm/monkey.iqm" )
	RL.SetModelMaterial( model, 0, material )
	animations = RL.LoadModelAnimations( RL.GetBasePath().."../resources/iqm/monkey.iqm" )
end

function RL.process( delta )
	if RL.IsKeyPressed( RL.KEY_ENTER ) then
		curAnim = curAnim + 1

		if #animations <= curAnim then
			curAnim = 0
		end

		frame = 0.0
		frameCount = RL.GetModelAnimationFrameCount( animations[ curAnim + 1 ] )
	elseif RL.IsKeyPressed( RL.KEY_UP ) then
		animSpeed = animSpeed + 5
	elseif RL.IsKeyPressed( RL.KEY_DOWN ) then
		animSpeed = animSpeed - 5
	end

	if RL.IsKeyDown( RL.KEY_SPACE ) then
		RL.UpdateModelAnimation( model, animations[ curAnim + 1 ], math.floor( frame ) )
		frame = frame + animSpeed * delta

		if frameCount < frame then
			frame = 0.0
		elseif frame < 0 then
			frame = frameCount
		end
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )
	RL.UpdateCamera3D( camera, RL.CAMERA_FIRST_PERSON )

	RL.BeginMode3D( camera )
		RL.DrawGrid( 8, 1 )
		RL.DrawModelEx( model, { 0, 0, 0 }, { 1.0, 0.0, 0.0 }, -90.0, { 1.0, 1.0, 1.0 }, RL.WHITE )
	RL.EndMode3D()

	RL.DrawText(
"Enter: Change animation\
Space: Play animation\
Up arrow: Inreace animation speed\
Down arrow: Decreace animation speed",
		{ 10, 10 }, 30, RL.WHITE )
end
