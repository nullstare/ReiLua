local atlas = nil
local shader = nil

local GLSL_VERSION = "330" -- PLATFORM_DESKTOP

function RL.init()
	RL.SetWindowTitle( "Texture atlas repeat shader" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	local path = RL.GetBasePath().."../resources/"
	local shaderPath = path.."/shaders/glsl"..GLSL_VERSION.."/"

	shader = RL.LoadShader( shaderPath.."base.vs", shaderPath.."atlas_repeat.fs" )
	atlas = RL.LoadTexture( path.."images/tiles.png" )

	local loc = RL.GetShaderLocation( shader, "atlasSize" )
	RL.SetShaderValue( shader, loc, RL.GetTextureSize( atlas ), RL.SHADER_UNIFORM_VEC2 )
	loc = RL.GetShaderLocation( shader, "tileTexSize" )
	RL.SetShaderValue( shader, loc, { 32, 32 }, RL.SHADER_UNIFORM_VEC2 )
	-- Set texture for DrawTriangle.
	RL.SetShapesTexture( atlas, { 32 * 4, 0, 32, 32 } )
end

function RL.update( delta )
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	RL.BeginShaderMode( shader )
		RL.DrawTexturePro( atlas, { 0, 0, 32, 32 }, { 0, 0, 64, 64 }, { 0.0, 0.0 }, 0.0, RL.WHITE )
		RL.DrawTexturePro( atlas, { 32, 0, 32, 32 }, { 0, 64, 128, 64 }, { 0.0, 0.0 }, 0.0, RL.WHITE )
		RL.DrawTriangle( { 32, 200 }, { 128, 400 }, { 320, 240 }, RL.WHITE )
	RL.EndShaderMode()
end
