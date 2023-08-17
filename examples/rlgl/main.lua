-- Work In Progress!

local monitor = 0
local texture = -1
local vaoId = -1
local vboId = -1
local triSize = 32.0
local vertices = {
	0.0, 0.0, 0.0,
	0.0, 0.0, triSize,
	triSize, 0.0, triSize
}
local colors = {
	RL.RED, RL.RED, RL.RED,
	RL.GREEN, RL.GREEN, RL.GREEN,
	RL.BLUE, RL.BLUE, RL.BLUE
}

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	vaoId = RL.rlLoadVertexArray()

	RL.rlEnableVertexArray( vaoId )
	-- vboId = RL.rlLoadVertexBuffer( vertexBuffer, RL.RL_UNSIGNED_BYTE, false )
	vboId = RL.rlLoadVertexBuffer( vertices, RL.RL_FLOAT, false )
	RL.rlSetVertexAttribute( 0, 3, RL.RL_FLOAT, false, 0, 0 )
	RL.rlEnableVertexAttribute( 0 )

	RL.rlDisableVertexArray()

	-- RL.DrawMesh(  )

	-- print( "vaoId", vaoId )
	-- print( "vboId", vboId )
end

function RL.draw()
	RL.ClearBackground( { 100, 150, 100 } )
end

function RL.exit()
	if 0 <= vaoId then
		RL.rlUnloadVertexArray( vaoId )
	end

	if 0 <= vboId then
		RL.rlUnloadVertexBuffer( vboId )
	end
end