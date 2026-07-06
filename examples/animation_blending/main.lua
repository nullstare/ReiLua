-- Based on raylib example contributed by Kirandeep (@Kirandeep-Singh-Khehra) and reviewed by Ramon Santamaria (@raysan5) https://github.com/raysan5/raylib/blob/master/examples/models/models_animation_blending.c

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vector2 = require( "vector2" )
Vector3 = require( "vector3" )
Camera3D = require( "camera3d" )

local monitor = 0
local winSize = Vector2:new( 1024, 720 )
local camera = Camera3D:new()
local model = nil
local anim = {
	data = {},				-- Animation user data.
	info = {},				-- Animation info { name, keyFrameCount }
	currentPlaying = 0,		-- Current animation playing (0 or 1)
	nextToPlay = 1,			-- Next animation to play (to transition)
	transition = false,		-- Flag to register anim transition state

	index0 = 10,			-- Current animation playing (walking)
	currentFrame0 = 0,		-- Current animation frame (supporting interpolated frames)
	frameSpeed0 = 0.5,		-- Current animation play speed
	index1 = 6,				-- Next animation to play (running)
	currentFrame1 = 0,		-- Next animation frame (supporting interpolated frames)
	frameSpeed1 = 0.5,		-- Next animation play speed

	blendFactor = 0,		-- Blend factor from anim0[frame0] --> anim1[frame1], [0.0f..1.0f]
							-- NOTE: 0.0f results in full anim0[] and 1.0f in full anim1[]
	blendTime = 2,			-- Time to blend from one playing animation to another (in seconds)
	blendTimeCounter = 0,	-- Time counter (delta time)
	pause = false,			-- Pause animation
	transforms = {},
	transforms0 = {},
	transforms1 = {},
}
local ui = {
	dropdownEditMode0 = false,
	dropdownEditMode1 = false,
	frameProgress0 = 0,
	frameProgress1 = 0,
	blendProgress = 0,
}

function RL.init()
	local mPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local mSize = Vector2:newT( RL.GetMonitorSize( monitor ) )

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( mPos + mSize:scale( 0.5 ) - winSize:scale( 0.5 ) )

	camera:setPosition( { 0, 6, 10 } )
	camera:setTarget( { 0, 2, 0 } )
	camera:setUp( { 0, 1, 0 } )
	camera.mode = camera.MODES.ORBITAL

	local path = RL.GetBasePath().."../resources/gltf/robot.glb"
	model = RL.LoadModel( path )
	anim.data = RL.LoadModelAnimations( path )
	local names = {}

	if anim.data then
		for _, a in ipairs( anim.data ) do
			local name = RL.GetModelAnimationName( a )

			table.insert( names, name )
			table.insert( anim.info,
				{
					name = name,
					keyFrameCount = RL.GetModelAnimationKeyframeCount( a ),
				}
			)
		end
	end

	anim.info.names = table.concat( names, ";" )
end

function RL.update( delta )
	camera:update( delta )

	if RL.IsKeyPressed( RL.KEY_P ) then
		anim.pause = not anim.pause
	end

	if not anim.pause then
		-- Start transition from anim0[] to anim1[]
		if RL.IsKeyPressed( RL.KEY_SPACE ) and not anim.transition then
			if anim.currentPlaying == 0 then
				-- Transition anim0 --> anim1
				anim.nextToPlay = 1
				anim.currentFrame1 = 0
			else
				-- Transition anim1 --> anim0
				anim.nextToPlay = 0
				anim.currentFrame0 = 0
			end

			-- Set animation transition
			anim.transition = true
			anim.blendTimeCounter = 0
			anim.blendFactor = 0
		end

		if anim.transition then
			-- Playing anim0 and anim1 at the same time
			anim.currentFrame0 = anim.currentFrame0 + anim.frameSpeed0
			if anim.info[ anim.index0 + 1 ].keyFrameCount <= anim.currentFrame0 then
				anim.currentFrame0 = 0
			end

			anim.currentFrame1 = anim.currentFrame1 + anim.frameSpeed1
			if anim.info[ anim.index1 + 1 ].keyFrameCount <= anim.currentFrame1 then
				anim.currentFrame1 = 0
			end

			-- Increment blend factor over time to transition from anim0 --> anim1 over time
			-- NOTE: Time blending could be other than linear, using some easing
			anim.blendFactor = anim.blendTimeCounter / anim.blendTime
			anim.blendTimeCounter = anim.blendTimeCounter + delta
			ui.blendProgress = anim.blendFactor

			-- Update model with animations blending
			if anim.nextToPlay == 1 then
				-- Blend anim0 --> anim1
				RL.UpdateModelAnimationEx( model,
					anim.data[ anim.index0 + 1 ], anim.currentFrame0,
					anim.data[ anim.index1 + 1 ], anim.currentFrame1,
					anim.blendFactor
				)
			else
				-- Blend anim1 --> anim0
				RL.UpdateModelAnimationEx( model,
					anim.data[ anim.index1 + 1 ], anim.currentFrame1,
					anim.data[ anim.index0 + 1 ], anim.currentFrame0,
					anim.blendFactor
				)
			end

			-- Check if transition completed
			if 1 < anim.blendFactor then
				-- Reset frame states
				if anim.currentPlaying == 0 then
					anim.currentFrame0 = 0
				elseif anim.currentPlaying == 1 then
					anim.currentFrame1 = 0
				end
				-- Update current animation playing
				anim.currentPlaying = anim.nextToPlay

				anim.blendFactor = 0 -- Reset blend factor
				anim.transition = false -- Exit transition mode
				anim.blendTimeCounter = 0
			end
		else
			-- Play only one anim, the current one
			if anim.currentPlaying == 0 then
				-- Playing anim0 at defined speed
				anim.currentFrame0 = anim.currentFrame0 + anim.frameSpeed0

				if anim.info[ anim.index0 + 1 ].keyFrameCount <= anim.currentFrame0 then
					anim.currentFrame0 = 0
				end
				RL.UpdateModelAnimation( model, anim.data[ anim.index0 + 1 ], anim.currentFrame0 )
			elseif anim.currentPlaying == 1 then
				-- Playing anim1 at defined speed
				anim.currentFrame1 = anim.currentFrame1 + anim.frameSpeed1

				if anim.info[ anim.index1 + 1 ].keyFrameCount <= anim.currentFrame1 then
					anim.currentFrame1 = 0
				end
				RL.UpdateModelAnimation( model, anim.data[ anim.index1 + 1 ], anim.currentFrame1 )
			end
		end
	end

	-- Update progress bars values with current frame for each animation
	ui.frameProgress0 = anim.currentFrame0
	ui.frameProgress1 = anim.currentFrame1

	-- for i = 1, RL.GetModelSkeletonBoneCount( RL.GetModelSkeleton( model ) ) do
	-- 	anim.transforms[i] = RL.GetModelCurrentPose( model, i - 1 )
	-- 	anim.transforms0[i] = RL.GetModelAnimationKeyframePose( anim.data[ anim.index0 + 1 ], anim.currentFrame0, i - 1 )
	-- 	anim.transforms1[i] = RL.GetModelAnimationKeyframePose( anim.data[ anim.index1 + 1 ], anim.currentFrame1, i - 1 )
	-- end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	camera:beginMode3D()
		RL.DrawGrid( 10, 1 )

		if model then
			RL.DrawModel( model, { 0, 0, 0 }, 1, RL.WHITE )
		end

		-- Draw bones.
		-- for _, tran in ipairs( anim.transforms ) do
		-- 	RL.DrawSphereWires( tran.translation, 0.2, 4, 6, RL.RED )
		-- end
		-- if anim.transition then
		-- 	for _, tran in ipairs( anim.transforms0 ) do
		-- 		RL.DrawCubeWires( tran.translation, { 0.1, 0.1, 0.1 }, RL.GREEN )
		-- 	end
		-- 	for _, tran in ipairs( anim.transforms1 ) do
		-- 		RL.DrawCubeWires( tran.translation, { 0.1, 0.1, 0.1 }, RL.BLUE )
		-- 	end
		-- end
	camera:endMode3D()

	-- Draw UI elements

	-- Draw blending text
	if anim.transition then
		local blendDir = anim.nextToPlay == 1 and "->" or "<-"

		RL.DrawText( "ANIM TRANSITION BLENDING! Direction "..blendDir, { 10, 60 }, 30, RL.BLUE )
	else
		RL.DrawText( "PRESS SPACE to START BLENDING", { 10, 60 }, 30, RL.BLUE )
	end

	if ui.dropdownEditMode0 then
		RL.GuiDisable()
	end
	_, anim.frameSpeed0 = RL.GuiSlider(
		{ 10, 38, 160, 12 },
		nil, string.format( "x%.1f", anim.frameSpeed0 ),
		anim.frameSpeed0, 0.1, 2
	)
	RL.GuiEnable()

	if ui.dropdownEditMode1 then
		RL.GuiDisable()
	end
	_, anim.frameSpeed1 = RL.GuiSlider(
		{ winSize.x - 170, 38, 160, 12 },
		string.format( "x%.1f", anim.frameSpeed1 ), nil,
		anim.frameSpeed1, 0.1, 2
	)
	RL.GuiEnable()

	-- Blend time.
	_, anim.blendTime = RL.GuiSlider(
		{ winSize.x / 2 - 80, 38, 160, 12 },
		string.format( "x%.1f", anim.blendTime ), nil,
		anim.blendTime, 0.1, 5
	)
	RL.GuiEnable()

	-- Draw animation selectors for blending transition
	-- NOTE: Transition does not start until requested
	RL.GuiSetStyle( RL.DROPDOWNBOX, RL.DROPDOWN_ITEMS_SPACING, 1 )

	local result
	result, anim.index0 = RL.GuiDropdownBox( { 10, 10, 160, 24 }, anim.info.names, anim.index0, ui.dropdownEditMode0 )

	if result == 1 then
		ui.dropdownEditMode0 = not ui.dropdownEditMode0
	end

	-- Blending process progress bar
	RL.GuiProgressBar( { 180, 14, winSize.x - 170 - 180 - 10, 16 }, nil, nil, ui.blendProgress, 0, 1 )

	result, anim.index1 = RL.GuiDropdownBox( { winSize.x - 170, 10, 160, 24 }, anim.info.names, anim.index1, ui.dropdownEditMode1 )

	if result == 1 then
		ui.dropdownEditMode1 = not ui.dropdownEditMode1
	end

	-- Draw playing timeline with keyframes for anim0[]
	local keyframeCount = anim.info[ anim.index0 + 1 ].keyFrameCount

	RL.GuiProgressBar( { 60, winSize.y - 60, winSize.x - 180, 20 }, "ANIM 0",
		string.format( "FRAME: %.2f / %i", ui.frameProgress0, keyframeCount ),
		ui.frameProgress0, 0, keyframeCount
	)

	for i = 1, keyframeCount - 1 do
		RL.DrawRectangle( { 60 + ( winSize.x - 180 ) / keyframeCount * i, winSize.y - 60, 1, 20 },
			RL.BLUE
		)
	end

	-- Draw playing timeline with keyframes for anim1[]
	keyframeCount = anim.info[ anim.index1 + 1 ].keyFrameCount

	RL.GuiProgressBar( { 60, winSize.y - 30, winSize.x - 180, 20 }, "ANIM 1",
		string.format( "FRAME: %.2f / %i", ui.frameProgress1, keyframeCount ),
		ui.frameProgress1, 0, keyframeCount
	)

	for i = 1, keyframeCount - 1 do
		RL.DrawRectangle( { 60 + ( winSize.x - 180 ) / keyframeCount * i, winSize.y - 30, 1, 20 },
			RL.BLUE
		)
	end
end
