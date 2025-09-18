--[[
	We can use mesh to draw tilemap in one draw call.
	On large maps you could devide the tilemap in sections to cull tiles that are not
	in view.
--]]

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vector2 = require( "vector2" )
Vector3 = require( "vector3" )

QUAD = {
	VERTICES = {
		Vector3:new( 0, 0, 0 ), Vector3:new( 0, 1, 0 ), Vector3:new( 1, 1, 0 ),
		Vector3:new( 0, 0, 0 ), Vector3:new( 1, 1, 0 ), Vector3:new( 1, 0, 0 )
	},
	TEXCOORDS = {
		Vector2:new( 0, 0 ), Vector2:new( 0, 1 ), Vector2:new( 1, 1 ),
		Vector2:new( 0, 0 ), Vector2:new( 1, 1 ), Vector2:new( 1, 0 )
	},
}

local res = Vector2:new( 1024, 720 )
local winScale = 1
local winSize = res:scale( winScale )
local monitor = 0

local tilemap = {
	texture = nil,
	texSize = Vector2:new(),
	mesh = nil,
	material = nil,
	tileSize = 32,
	tilecount = 0,
}

local function setTile( meshData, pos, texcoord )
	local texelSize = Vector2:new( 1 / tilemap.texSize.x, 1 / tilemap.texSize.y )

	for i, v in ipairs( QUAD.VERTICES ) do
		table.insert( meshData.vertices, ( Vector3:temp( pos.x + v.x, pos.y + v.y, 0 ) ):scale( tilemap.tileSize ) )
		table.insert( meshData.texcoords, ( QUAD.TEXCOORDS[i] + texcoord ) * texelSize:scale( tilemap.tileSize ) )
		table.insert( meshData.colors, RL.WHITE )
	end

	tilemap.tilecount = tilemap.tilecount + 1
end

local function genTilemap()
	local meshData = { vertices = {}, texcoords = {}, colors = {} }
	-- Ground.
	for x = 0, winSize.x / tilemap.tileSize do
		for y = 0, winSize.y / tilemap.tileSize do
			setTile( meshData, Vector2:new( x, y ), Vector2:new( 4, 0 ) )
		end	
	end
	-- House. Will be overdrawn to ground but we don't care we are so efficient! (You should though.)
	for x = 0, 6 do
		for y = 0, 10 do
			local tilePos = Vector2:new( x, y ) + Vector2:new( 8, 6 )
			
			if ( x == 0 or x == 6 or y == 0 or y == 10 ) and y ~= 4 then
				setTile( meshData, tilePos, Vector2:new( 0, 0 ) )
			else
				setTile( meshData, tilePos, Vector2:new( 1, 0 ) )
			end
		end	
	end
	-- Characters. You probably would not do this, but we do it here to get some variation.
	setTile( meshData, Vector2:new( 4, 3 ), Vector2:new( 3, 0 ) )
	setTile( meshData, Vector2:new( 8, 4 ), Vector2:new( 3, 1 ) )
	setTile( meshData, Vector2:new( 10, 8 ), Vector2:new( 1, 1 ) )

	tilemap.mesh = RL.GenMeshCustom( meshData, false )
end

function RL.init()
	local monitorPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local monitorSize = Vector2:newT( RL.GetMonitorSize( monitor ) )

	RL.SetWindowTitle( "Fast tilemap" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )

	local path = RL.GetBasePath().."../resources/images/tiles.png"

	tilemap.texture = RL.LoadTexture( path )
	tilemap.texSize:setT( RL.GetTextureSize( tilemap.texture ) )

	tilemap.material = RL.LoadMaterialDefault()
	RL.SetMaterialTexture( tilemap.material, RL.MATERIAL_MAP_ALBEDO, tilemap.texture )

	genTilemap()
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )
	RL.DrawMesh( tilemap.mesh, tilemap.material, RL.MatrixIdentity() )
	RL.DrawText( "Tile count: "..tostring( tilemap.tilecount ), { 3, 3 }, 20, RL.GREEN )
end
