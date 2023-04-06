--[[
  Contributed by Codecat (@codecat)
  Reviewed by Ramon Santamaria (@raysan5)

  Modified by Teddy Astie (@TSnake41) for Lua binding.
  Modified by Jussi Viitala (@nullstare) for ReiLua style.
]]

local camera = -1
local num_blocks = 15

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowTitle( "Waving cubes" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	camera = RL.CreateCamera3D()
	RL.SetCamera3DPosition( camera, { 30, 20, 30 } )
	RL.SetCamera3DTarget( camera, { 0, 0, 0 } )
	RL.SetCamera3DUp( camera, { 0, 1, 0 } )
end

function RL.draw()
  	local t = RL.GetTime()
	local cos = math.cos
	local sin = math.sin

	local scale = (2.0 + sin(t)) * 0.7
	local camera_time = t * 0.3
	local camera_pos = RL.GetCamera3DPosition( camera )

	camera_pos[1] = cos(camera_time) * 40.0
	camera_pos[3] = sin(camera_time) * 40.0

	RL.SetCamera3DPosition( camera, camera_pos )
	RL.ClearBackground( RL.RAYWHITE )

	RL.BeginMode3D( camera )
		RL.DrawGrid( 10, 5.0 )

		for x = 0,num_blocks - 1 do
			for y = 0,num_blocks - 1 do
				for z = 0,num_blocks - 1 do
					local block_scale = (x + y + z) / 30
					local scatter = sin(block_scale * 20.0 + t * 4.0)

					local cube_pos = {
						(x - num_blocks / 2) * (scale * 3.0) + scatter,
						(y - num_blocks / 2) * (scale * 2.0) + scatter,
						(z - num_blocks / 2) * (scale * 3.0) + scatter
					}
					local cube_color = RL.ColorFromHSV( (((x + y + z) * 18) % 360), 0.75, 0.9 )
					local cube_size = (2.4 - scale) * block_scale

					RL.DrawCube( cube_pos, { cube_size, cube_size, cube_size }, cube_color )
				end
			end
		end
  	RL.EndMode3D()

  	RL.DrawFPS( { 10, 10 } )
end
