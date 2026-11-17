-- Followed this tutorial. https://www.youtube.com/watch?v=_EurjoraotA

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Camera3D = require( "camera3d" )

local camera = Camera3D:new()
local monitor = 0
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

	camera:setPosition( { 0, 2, 4 } )
	camera:setTarget( { 0, 0, 0 } )
	camera:setUp( { 0, 1, 0 } )
	camera.mode = camera.MODES.FIRST_PERSON

	RL.SetTextLineSpacing( 26 )
	-- If custom material or mesh is set to model, we need to use custom unloading to prevent double free errors.
	RL.SetGCUnload( false )

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
	-- Unload old material.
	RL.UnloadMaterial( RL.GetModelMaterial( model, 0 ), true )

	RL.SetModelMaterial( model, 0, material )
	animations = RL.LoadModelAnimations( RL.GetBasePath().."../resources/iqm/monkey.iqm" )
end

function RL.update( delta )
	if RL.IsKeyPressed( RL.KEY_ENTER ) then
		curAnim = curAnim + 1

		if #animations <= curAnim then
			curAnim = 0
		end

		frame = 0.0
		frameCount = RL.GetModelAnimationKeyframeCount( animations[ curAnim + 1 ] )
	elseif RL.IsKeyPressed( RL.KEY_UP ) then
		animSpeed = animSpeed + 5
	elseif RL.IsKeyPressed( RL.KEY_DOWN ) then
		animSpeed = animSpeed - 5
	end

	if RL.IsKeyDown( RL.KEY_P ) then
		RL.UpdateModelAnimation( model, animations[ curAnim + 1 ], math.floor( frame ) )
		frame = frame + animSpeed * delta

		if frameCount < frame then
			frame = 0.0
		elseif frame < 0 then
			frame = frameCount
		end
	end

	camera:update( delta )

	if RL.IsKeyPressed( RL.KEY_SPACE ) then
		if camera.mode == camera.MODES.FREE then
			camera.mode = camera.MODES.FIRST_PERSON
		else
			camera.mode = camera.MODES.FREE
		end
	end
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )

	camera:beginMode3D()
		RL.DrawGrid( 8, 1 )
		RL.DrawModelEx( model, { 0, 0, 0 }, { 1.0, 0.0, 0.0 }, -90.0, { 1.0, 1.0, 1.0 }, RL.WHITE )
	camera:endMode3D()

	RL.DrawText(
"Enter: Change animation\
P: Play animation\
Up arrow: Inreace animation speed\
Down arrow: Decreace animation speed",
		{ 10, 10 }, 30, RL.WHITE
	)
end

function RL.exit()
	RL.UnloadTexture( texture )
	RL.UnloadModel( model, true )
	RL.UnloadModelAnimations( animations )
end
