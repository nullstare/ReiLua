-- Forked from raylib-lua example by TSnake41
-- https://github.com/TSnake41/raylib-lua/blob/master/examples/textures_bunnymark.lua

local MAX_BUNNIES = 100000

-- This is the maximum amount of elements (quads) per batch
-- NOTE: This value is defined in [rlgl] module and can be changed there
local MAX_BATCH_ELEMENTS = 8192

-- Create the Bunny class.
local Bunny = {}
Bunny.__index = Bunny

function Bunny:new( pos, spd, col )
	local bunny = {}
	setmetatable( bunny, Bunny )
	bunny.position = pos
	bunny.speed = spd
	bunny.color = col
	return bunny
end

-- Initialization
local screenWidth = 800
local screenHeight = 450
local texSize = { 0, 0 }
local texBunny = -1
local bunnies = {}

function Bunny:update()
	self.position[1] = self.position[1] + self.speed[1]
	self.position[2] = self.position[2] + self.speed[2]

	if ( ( self.position[1] + texSize[1] / 2 ) > screenWidth )
	or ( ( self.position[2] + texSize[1] / 2 ) < 0 ) then
		self.speed[1] = self.speed[1] * -1
	end

	if ( ( self.position[2] + texSize[2] / 2 ) > screenHeight )
	or ( ( self.position[2] + texSize[2] / 2 - 40 ) < 0 ) then
		self.speed[2] = self.speed[2] * -1
	end
end

function RL.init()
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( { screenWidth, screenHeight } )
	RL.SetWindowTitle( "raylib [textures] example - bunnymark" )
	-- Load bunny texture
	texBunny = RL.LoadTexture( RL.GetBasePath().."../resources/images/wabbit_alpha.png" )
	texSize = RL.GetTextureSize( texBunny )
end

function RL.process( delta )
	if RL.IsMouseButtonDown( 0 ) then
	 	-- Create more bunnies
		for i = 1, 100 do
			if #bunnies < MAX_BUNNIES then
				local speed = { math.random( -250, 250 ) / 60, math.random( -250, 250 ) / 60 }
				local color = { math.random( 50, 240 ), math.random( 80, 240 ), math.random( 100, 240 ), 255 }
				table.insert( bunnies, Bunny:new( RL.GetMousePosition(), speed, color ) )
			end
		end
	end
	-- Update bunnies
	for i = 1, #bunnies do
	  	bunnies[i]:update()
	end
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	for i = 1, #bunnies do
		local bunny = bunnies[i]
		-- NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
		-- a draw call is launched and buffer starts being filled again;
		-- before issuing a draw call, updated vertex data from internal CPU buffer is send to GPU...
		-- Process of sending data is costly and it could happen that GPU data has not been completely
		-- processed for drawing while new data is tried to be sent (updating current in-use buffers)
		-- it could generates a stall and consequently a frame drop, limiting the number of drawn bunnies
		RL.DrawTexture( texBunny, { bunny.position[1], bunny.position[2] }, bunny.color )
	end

	RL.DrawRectangle( { 0, 0, screenWidth, 40 }, RL.BLACK)
	RL.DrawText( RL.GetFontDefault(), "bunnies: " .. #bunnies, { 120, 10 }, 20, 2, RL.GREEN )
	RL.DrawText( RL.GetFontDefault(), "batched draw calls: " .. math.ceil( 1 + #bunnies / MAX_BATCH_ELEMENTS ), { 320, 10 }, 20, 2, RL.RED )
	RL.DrawFPS( { 10, 10 } )
end
