package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )

local res = Vec2:new( 1024, 720 )
local winScale = 1
local winSize = res:scale( winScale )
local monitor = 0

local triangle = {
	texture = {
		id = -1,
		data = nil,
		size = Vec2:new( 0, 0 ),
		mipmaps = 0,
		format = 0,
	},
	vao = -1,
	vbos = {
		positions = -1,
		texcoords = -1,
		colors = -1,
	},
}

local vertexShader = [[
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec4 aColor;
	layout (location = 2) in vec2 aTexCoord;
	
	out vec4 flagColor;
	out vec2 fragTexCoord;
	
	void main() {
		flagColor = aColor;
		fragTexCoord = aTexCoord;
		gl_Position = vec4( aPos, 1.0 );
	}
]]
local fragmentShader = [[
	#version 330 core
	out vec4 FragColor;
	
	in vec4 flagColor;
	in vec2 fragTexCoord;

	uniform sampler2D ourTexture;

	void main() {
		FragColor = texture( ourTexture, fragTexCoord ) * flagColor;
	}
]]

local shaderProgram = -1

-- Let's make our own custom texture.
local function loadTexture( path )
	local image = RL.LoadImage( path )

	triangle.texture.data = RL.GetImageData( image )
	triangle.texture.size = Vec2:newT( RL.GetImageSize( image ) )
	triangle.texture.format = RL.GetImageFormat( image )
	triangle.texture.mipmaps = RL.GetImageMipmaps( image )

	triangle.texture.id = RL.rlLoadTexture(
		triangle.texture.data,
		triangle.texture.size,
		triangle.texture.format,
		triangle.texture.mipmaps
	)
end

local function createTriangle()
	loadTexture( RL.GetBasePath().."../resources/images/monkey_tex.png" )
	-- Set texture to shader uniform.
	local shaderLoc = RL.rlGetLocationUniform( shaderProgram, "ourTexture" )

	RL.rlEnableShader( shaderProgram )
	-- NOTE: Default texture is always activated as GL_TEXTURE0 so our slot will be 1.
	RL.rlSetUniformSampler( shaderLoc, triangle.texture.id )
	RL.rlDisableShader()

	-- Setup triangle buffers.
	triangle.vao = RL.rlLoadVertexArray()
	RL.rlEnableVertexArray( triangle.vao )

	-- Positions.
	local vertexBuffer = RL.LoadBuffer(
		{
			-0.5, -0.5, 0.0,
			0.5, -0.5, 0.0,
			0.0,  0.5, 0.0
		},
		RL.BUFFER_FLOAT
	)
	triangle.vbos.positions = RL.rlLoadVertexBuffer( vertexBuffer, false )
	RL.rlSetVertexAttribute( 0, 3, RL.RL_FLOAT, false, 0, 0 )
	RL.rlEnableVertexAttribute( 0 )

	-- Colors.
	local colors = RL.LoadBuffer(
		{
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1
		},
		RL.BUFFER_FLOAT
	)
	triangle.vbos.colors = RL.rlLoadVertexBuffer( colors, false )
	RL.rlSetVertexAttribute( 1, 4, RL.RL_FLOAT, false, 0, 0 )
	RL.rlEnableVertexAttribute( 1 )

	-- Texcoords.
	local texcoors = RL.LoadBuffer(
		{
			0, 0,
			1, 0,
			0.5, 1,
		},
		RL.BUFFER_FLOAT
	)
	triangle.vbos.texcoors = RL.rlLoadVertexBuffer( texcoors, false )
	RL.rlSetVertexAttribute( 2, 2, RL.RL_FLOAT, false, 0, 0 )
	RL.rlEnableVertexAttribute( 2 )

	-- Disable.
	RL.rlDisableVertexBuffer()
	RL.rlDisableVertexArray()
end

function RL.init()
	local monitorPos = Vec2:newT( RL.GetMonitorPosition( monitor ) )
	local monitorSize = Vec2:newT( RL.GetMonitorSize( monitor ) )

	RL.SetWindowTitle( "RLGL Hello Triangle" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )

	RL.rlViewport( { 0, 0, res.x ,res.y } )
	shaderProgram = RL.rlLoadShaderCode( vertexShader, fragmentShader )

	createTriangle()
end

local function drawTriangle()
	-- Texture slot 0 is the default texture.
	RL.rlActiveTextureSlot( 1 )
	RL.rlEnableTexture( triangle.texture.id )

	RL.rlEnableShader( shaderProgram )

	RL.rlEnableVertexArray( triangle.vao )
	RL.rlDrawVertexArray( 0, 3 )

	-- Disable.
	RL.rlDisableVertexArray()
	RL.rlDisableVertexBuffer()
	RL.rlDisableTexture()
	RL.rlDisableShader()
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )
	drawTriangle()
end

function RL.exit()
	RL.rlUnloadVertexArray( triangle.vao )
	RL.rlUnloadVertexBuffer( triangle.vbos.positions )
	RL.rlUnloadVertexBuffer( triangle.vbos.colors )
	RL.rlUnloadVertexBuffer( triangle.vbos.texcoords )
	RL.rlUnloadTexture( triangle.texture.id )
end
