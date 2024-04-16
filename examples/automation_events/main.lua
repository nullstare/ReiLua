package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vec2 = require( "vector2" )

local eventList = nil
local evenRecording = false
local eventPlaying = false
local frameCounter = 0
local playFrameCounter = 0
local currentPlayFrame = 0
local player = {
	pos = Vec2:new( 160, 200 ),
	speed = 100.0,
}

function RL.init()
	RL.SetWindowTitle( "Automation Events" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetTextLineSpacing( 25 )

	eventList = RL.LoadAutomationEventList( nil )
	RL.SetAutomationEventList( eventList )
end

function RL.update( delta )
	local moveDir = Vec2:new( 0, 0 )

	if RL.IsKeyDown( RL.KEY_RIGHT ) then
		moveDir.x = 1
	elseif RL.IsKeyDown( RL.KEY_LEFT ) then
		moveDir.x = -1
	end

	if RL.IsKeyDown( RL.KEY_DOWN ) then
		moveDir.y = 1
	elseif RL.IsKeyDown( RL.KEY_UP ) then
		moveDir.y = -1
	end

	player.pos:addEq( moveDir:scale( player.speed * delta ) )

	-- Events.

	if RL.IsKeyPressed( RL.KEY_S ) then
		evenRecording = not evenRecording

		if evenRecording then
			RL.StartAutomationEventRecording()
		else
			RL.StopAutomationEventRecording()
		end
	end
	if RL.IsKeyPressed( RL.KEY_A ) then
		eventPlaying = not eventPlaying
		evenRecording = false
		playFrameCounter = 0
		currentPlayFrame = 0
	end

	if eventPlaying then
		while playFrameCounter == RL.GetAutomationEventFrame( RL.GetAutomationEvent( eventList, currentPlayFrame ) ) do
			RL.TraceLog( RL.LOG_INFO, "playFrameCounter: "..playFrameCounter.."\tcurrentPlayFrame: "..currentPlayFrame )

			RL.PlayAutomationEvent( RL.GetAutomationEvent( eventList, currentPlayFrame ) )
			currentPlayFrame = currentPlayFrame + 1

			if currentPlayFrame == RL.GetAutomationEventListCount( eventList ) then
				eventPlaying = false
				currentPlayFrame = 0
				playFrameCounter = 0

				RL.TraceLog( RL.LOG_INFO, "FINISH PLAYING!" )
				break
			end
		end

		playFrameCounter = playFrameCounter + 1
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )
	RL.DrawCircle( player.pos, 8.0, RL.BLUE )

	local text = "Toggle recording: S\nToggle play: A\n"
	local textColor = RL.GREEN

	if evenRecording then
		text = text.."Recording"
		textColor = RL.RED
	elseif eventPlaying then
		text = text.."Playing"
		textColor = RL.BLUE
	end

    RL.DrawText( text, { 20, 20 }, 20, textColor )
end
