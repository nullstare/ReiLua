-- Based on raylib example - Draw Textured Polygon by Chris Camacho (@codifies)

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vec2 = require( "vector2" )

local monitor = 0
local mPos = Vec2:new( RL.GetMonitorPosition( monitor ) )
local mSize = Vec2:new( RL.GetMonitorSize( monitor ) )
local winSize = Vec2:new( RL.GetScreenSize() )

local polygon = {
	texture = -1,
	texcoords = {
		Vec2:new( 0.75, 0.0 ),
		Vec2:new( 0.25, 0.0 ),
		Vec2:new( 0.0, 0.5 ),
		Vec2:new( 0.0, 0.75 ),
		Vec2:new( 0.25, 1.0 ),
		Vec2:new( 0.375, 0.875 ),
		Vec2:new( 0.625, 0.875 ),
		Vec2:new( 0.75, 1.0 ),
		Vec2:new( 1.0, 0.75 ),
		Vec2:new( 1.0, 0.5 ),
		Vec2:new( 0.75, 0.0 ),
    },
	points = {},
	positions = {},
	angle = 0.0,
}

function RL.init()
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos.x + mSize.x / 2 - winSize.x / 2, mPos.y + mSize.y / 2 - winSize.y / 2 } )
	RL.SetWindowTitle( "Textured Polygon" )

	polygon.texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/cat.png" )

	-- Define the base poly vertices from the UV's
    -- NOTE: They can be specified in any other way
	for _, texcoord in ipairs( polygon.texcoords ) do
		table.insert( polygon.points, Vec2:new( ( texcoord.x - 0.5 ) * 256, ( texcoord.y - 0.5 ) * 256 ) )
	end

    -- Define the vertices drawing position
    -- NOTE: Initially same as points but updated every frame
	for _, point in ipairs( polygon.points ) do
		table.insert( polygon.positions, point:clone() )
	end
end

function RL.process( delta )
	polygon.angle = polygon.angle + delta

	-- Update points rotation with an angle transform
	-- NOTE: Base points position are not modified
	for i = 1, #polygon.points do
		polygon.positions[i] = Vec2:new( RL.Vector2Rotate( polygon.points[i], polygon.angle ) )
	end
end

-- Draw textured polygon, defined by vertex and texture coordinates
-- NOTE: Polygon center must have straight line path to all points
-- without crossing perimeter, points must be in anticlockwise order
local function drawTexturePoly( texture, center, points, texcoords, tint )
	RL.rlSetTexture( RL.GetTextureId( texture ) )

	-- Texturing is only supported on RL_QUADS
	RL.rlBegin( RL.RL_QUADS )
		RL.rlColor4ub( tint )

		for i = 1, #points - 1 do
			RL.rlTexCoord2f( { 0.5, 0.5 } )
			RL.rlVertex2f( center )

			RL.rlTexCoord2f( texcoords[i] )
			RL.rlVertex2f( center + points[i] )

			RL.rlTexCoord2f( texcoords[i + 1] )
			RL.rlVertex2f( center + points[i + 1] )
			-- Dublicate of last vertex to complete quad.
			RL.rlTexCoord2f( texcoords[i + 1] )
			RL.rlVertex2f( center + points[i + 1] )
		end
	RL.rlEnd()
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	drawTexturePoly( polygon.texture, winSize:scale( 0.5 ), polygon.positions, polygon.texcoords, RL.WHITE )
end
