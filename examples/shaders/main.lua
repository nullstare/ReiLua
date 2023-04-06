local monitor = 0
local shader = -1
local texture = -1
local textureSize

local GLSL_VERSION = "330" -- PLATFORM_DESKTOP
-- local GLSL_VERSION = "100" -- PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB

local secondsLoc

function RL.init()
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	texture = RL.LoadTexture( RL.GetBasePath().."../resources/images/cat.png" )
	textureSize = RL.GetTextureSize( texture )
	shader = RL.LoadShader( nil, RL.GetBasePath().."../resources/shaders/glsl"..GLSL_VERSION.."/wave.fs" )

	secondsLoc = RL.GetShaderLocation( shader, "secondes" )
	local sizeLoc = RL.GetShaderLocation( shader, "size" )
    local freqXLoc = RL.GetShaderLocation( shader, "freqX" )
    local freqYLoc = RL.GetShaderLocation( shader, "freqY" )
    local ampXLoc = RL.GetShaderLocation( shader, "ampX" )
    local ampYLoc = RL.GetShaderLocation( shader, "ampY" )
    local speedXLoc = RL.GetShaderLocation( shader, "speedX" )
    local speedYLoc = RL.GetShaderLocation( shader, "speedY" )

	local freqX = 25.0
    local freqY = 25.0
    local ampX = 5.0
    local ampY = 5.0
    local speedX = 8.0
    local speedY = 8.0

    RL.SetShaderValue( shader, sizeLoc, textureSize, RL.SHADER_UNIFORM_VEC2 )
    RL.SetShaderValue( shader, freqXLoc, { freqX }, RL.SHADER_UNIFORM_FLOAT )
    RL.SetShaderValue( shader, freqYLoc, { freqY }, RL.SHADER_UNIFORM_FLOAT )
    RL.SetShaderValue( shader, ampXLoc, { ampX }, RL.SHADER_UNIFORM_FLOAT )
    RL.SetShaderValue( shader, ampYLoc, { ampY }, RL.SHADER_UNIFORM_FLOAT )
    RL.SetShaderValue( shader, speedXLoc, { speedX }, RL.SHADER_UNIFORM_FLOAT )
    RL.SetShaderValue( shader, speedYLoc, { speedY }, RL.SHADER_UNIFORM_FLOAT )
end

local seconds = 0.0

function RL.draw()
	seconds = seconds + RL.GetFrameTime();

    RL.SetShaderValue( shader, secondsLoc, { seconds }, RL.SHADER_UNIFORM_FLOAT );

	RL.ClearBackground( { 100, 150, 100 } )

	RL.BeginShaderMode( shader )
		RL.DrawTexture( texture, { 0, 0 }, RL.WHITE );
	RL.EndShaderMode()
end
