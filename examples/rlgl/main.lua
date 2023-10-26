-- Work In Progress!

local monitor = 0
local texture = -1
local triSize = 32.0
local vertices = {
	0.0, 0.0, 0.0,
	0.0, 0.0, triSize,
	triSize, 0.0, triSize
}
local colors = {
	255, 0, 0,
	0, 255, 0,
	0, 0, 255
}

local VBO_VERTEX_POS = 0
local VBO_COLOR_POS = 1

local mesh = {
	vaoId = -1,
	vboIds = {
		vertices = -1,
		colors = -1,
	}
}

local function uploadMesh()
	mesh.vaoId = RL.rlLoadVertexArray()

	RL.rlEnableVertexArray( mesh.vaoId )
	
	-- Vertices.
	local vertexBuffer = RL.LoadBuffer( vertices, RL.BUFFER_FLOAT )
	mesh.vboIds.vertices = RL.rlLoadVertexBuffer( vertexBuffer, false )
	RL.rlSetVertexAttribute( VBO_VERTEX_POS, 3, RL.RL_FLOAT, false, 0, 0 )
	RL.rlEnableVertexAttribute( VBO_VERTEX_POS )

	-- Colors.
	local colorBuffer = RL.LoadBuffer( colors, RL.BUFFER_UNSIGNED_CHAR )
	mesh.vboIds.colors = RL.rlLoadVertexBuffer( colorBuffer, false )
	RL.rlSetVertexAttribute( VBO_COLOR_POS, 4, RL.RL_UNSIGNED_BYTE, false, 0, 0 )
	RL.rlEnableVertexAttribute( VBO_COLOR_POS )

	RL.rlDisableVertexArray()

	print( "\nMesh:" )
	print( "\tvaoId: "..mesh.vaoId )
	print( "\tvboIds.vertices: "..mesh.vboIds.vertices )
	print( "\tvboIds.colors: "..mesh.vboIds.colors )
end

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	uploadMesh()
end

local function drawMesh()
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )
end

-- You need to manually free resources.
function RL.exit()
	if 0 <= mesh.vaoId then
		RL.rlUnloadVertexArray( mesh.vaoId )
	end

	for _, vboId in pairs( mesh.vboIds ) do
		if 0 <= vboId then
			RL.rlUnloadVertexBuffer( vboId )
		end
	end
end