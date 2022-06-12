-- Followed this tutorial. https://www.youtube.com/watch?v=_EurjoraotA

local monitor = 0
local camera = -1
local texture = -1
local material = -1
local model = -1
local animations = -1
local animationCount = 0
local frame = 0
local curAnim = 0
local frameCount = 0
local animSpeed = 60

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )
	camera = RL_CreateCamera3D()
	RL_SetCamera3DPosition( camera, { 0, 2, 4 } )
	RL_SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL_SetCamera3DUp( camera, { 0, 1, 0 } )
	RL_SetCameraMode( camera, CAMERA_FREE )

	material = RL_CreateMaterial( {
		maps = {
			{
				MATERIAL_MAP_ALBEDO,
				{
					texture = RL_LoadTexture( RL_GetBasePath().."../resources/images/monkey_tex.png" ),
					color = WHITE,
				},
			},
		},
	} )
	
	model = RL_LoadModel( RL_GetBasePath().."../resources/iqm/monkey.iqm" )
	RL_SetModelMaterial( model, 0, material )
	animations, animationCount = RL_LoadModelAnimations( RL_GetBasePath().."../resources/iqm/monkey.iqm" )

	print( "animationCount", animationCount )
end

function process( delta )
	if RL_IsKeyPressed( KEY_ENTER ) then
		curAnim = curAnim + 1

		if animationCount <= curAnim then
			curAnim = 0
		end

		frame = 0.0
		frameCount = RL_GetModelAnimationFrameCount( animations, curAnim )
	elseif RL_IsKeyPressed( KEY_UP ) then
		animSpeed = animSpeed + 5
	elseif RL_IsKeyPressed( KEY_DOWN ) then
		animSpeed = animSpeed - 5
	end

	if RL_IsKeyDown( KEY_SPACE ) then
		RL_UpdateModelAnimation( model, animations, curAnim, math.floor( frame ) )
		frame = frame + animSpeed * delta

		if frameCount < frame then
			frame = 0.0
		elseif frame < 0 then
			frame = frameCount
		end
	end
end

function draw()
	RL_ClearBackground( { 100, 150, 100 } )
	RL_UpdateCamera3D( camera )
	
	RL_BeginMode3D( camera )
		RL_DrawGrid( 8, 1 )
		RL_DrawModelEx( model, { 0, 0, 0 }, { 1.0, 0.0, 0.0 }, -90.0, { 1.0, 1.0, 1.0 }, WHITE )
	RL_EndMode3D()

	RL_DrawText( 0,
"Enter: Change animation\
Space: Play animation\
Up arrow: Inreace animation speed\
Down arrow: Decreace animation speed",
				 { 10, 10 }, 30, 5, WHITE )
end
