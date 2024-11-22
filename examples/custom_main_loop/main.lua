package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vector2 = require( "vector2" )

local function dysfunctionalPrint( message )
	printt( message )
end

local function main()
	RL.SetConfigFlags( RL.FLAG_VSYNC_HINT )
	RL.InitWindow( { 800, 600 }, "Custom Main Loop" )

	local catTex = RL.LoadTexture( RL.GetBasePath().."../resources/images/cat.png" )
	local catPos = Vector2:new( 20, 20 )
	local catSpeed = 200

	while not RL.WindowShouldClose() do
		local delta = RL.GetFrameTime()
		local vel = Vector2:new()

		if RL.IsKeyDown( RL.KEY_RIGHT ) then
			vel.x = catSpeed * delta
		elseif RL.IsKeyDown( RL.KEY_LEFT ) then
			vel.x = -catSpeed * delta
		end
		if RL.IsKeyDown( RL.KEY_DOWN ) then
			vel.y = catSpeed * delta
		elseif RL.IsKeyDown( RL.KEY_UP ) then
			vel.y = -catSpeed * delta
		end

		if RL.IsKeyPressed( RL.KEY_ENTER ) then
			dysfunctionalPrint( "This will fail and give usefull traceback info" )
		end

		catPos:addEq( vel )

		RL.BeginDrawing()
			RL.ClearBackground( RL.LIGHTGRAY )
			RL.DrawTexture( catTex, catPos, RL.WHITE )
			RL.DrawFPS( { 10, 10 } )
		RL.EndDrawing()
	end
end

-- Call main to get traceback info.
local success, result = xpcall( main, debug.traceback )

if not success then
	RL.TraceLog( RL.LOG_WARNING, "Error: "..result )
	RL.CloseWindow()
end
