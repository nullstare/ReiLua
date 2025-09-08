-- Based on raylib audio_stream_effects example

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"
package.cpath = package.cpath..";"..RL.GetBasePath().."../resources/clib/?.so"

Vector2 = require( "vector2" )
Rect = require( "rectangle" )

-- NOTE! You have to compile the C lib containing the effects in resources/clib/audioProcess.c
-- Implementing audio processors in Lua would probably be too slow.
AudioProcess = require( "audioProcess" )

local music = nil
local rect = Rect:new()
local rect2 = Rect:new()
local effectLPF = nil
local effectDelay = nil
local enableEffectLPF = false
local enableEffectDelay = false

function RL.init()
	RL.SetWindowTitle( "Audio stream effects" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.InitAudioDevice()

	music = RL.LoadMusicStream( RL.GetBasePath().."../resources/music/Juhani Junkala [Retro Game Music Pack] Title Screen.ogg" )

	RL.PlayMusicStream( music )

	AudioProcess.init()
	effectLPF = AudioProcess.AudioProcessEffectLPF()
	effectDelay = AudioProcess.AudioProcessEffectDelay()

	local winSize = Vector2:newT( RL.GetScreenSize() )
	local barWidth = 256

	rect:set(
		winSize.x / 2 - barWidth / 2,
		winSize.y / 2 - 5,
		barWidth,
		10
	)
	rect2:setR( rect )
end

function RL.update( delta )
	RL.UpdateMusicStream( music )

	-- Add/Remove effect: lowpass filter
	if RL.IsKeyPressed( RL.KEY_F ) then
		local stream = RL.GetMusicStream( music )
		enableEffectLPF = not enableEffectLPF

		if enableEffectLPF then
			RL.AttachAudioStreamProcessor( stream, effectLPF )
			-- RL.AttachAudioMixedProcessor( effectLPF )
		else
			RL.DetachAudioStreamProcessor( stream, effectLPF )
			-- RL.DetachAudioMixedProcessor( effectLPF )
		end
	end

	-- Add/Remove effect: delay
	if RL.IsKeyPressed( RL.KEY_D ) then
		local stream = RL.GetMusicStream( music )
		enableEffectDelay = not enableEffectDelay

		if enableEffectDelay then
			RL.AttachAudioStreamProcessor( stream, effectDelay )
			-- RL.AttachAudioMixedProcessor( effectDelay )
		else
			RL.DetachAudioStreamProcessor( stream, effectDelay )
			-- RL.DetachAudioMixedProcessor( effectDelay )
		end
	end
end

function RL.draw()
	local musicLen = RL.GetMusicTimeLength( music )
	local musicPos = RL.GetMusicTimePlayed( music )

	RL.ClearBackground( RL.RAYWHITE )

	RL.DrawText(
		"PRESS F TO TOGGLE LPF EFFECT "..( enableEffectLPF and "ON" or "OFF" ),
		Vector2:temp( rect.x - 80, rect.y - 80 ), 20, RL.GRAY
	)
	RL.DrawText(
		"PRESS D TO TOGGLE DELAY EFFECT "..( enableEffectDelay and "ON" or "OFF" ),
		Vector2:temp( rect.x - 90, rect.y - 40 ), 20, RL.GRAY
	)

	RL.DrawRectangleLines( rect + Rect:temp( 0, -1, 1, 1 ), RL.BLACK )
	rect2.width = musicPos / musicLen * rect.width
	RL.DrawRectangle( rect2, RL.RED )
end

function RL.exit()
	AudioProcess.free()
end
