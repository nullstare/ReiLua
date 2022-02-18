local monitor = 0
local shader = -1
local texture = -1
local textureSize

local GLSL_VERSION = "330" -- PLATFORM_DESKTOP
-- local GLSL_VERSION = "100" -- PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB

local secondsLoc

function init()
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	local winSize = RL_GetWindowSize()

	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	texture = RL_LoadTexture( RL_GetBasePath().."../resources/images/cat.png" )
	textureSize = RL_GetTextureSize( texture )
	shader = RL_LoadShader( nil, RL_GetBasePath().."../resources/shaders/glsl"..GLSL_VERSION.."/wave.fs" )

	secondsLoc = RL_GetShaderLocation( shader, "secondes" )
	local sizeLoc = RL_GetShaderLocation( shader, "size" )
    local freqXLoc = RL_GetShaderLocation( shader, "freqX" )
    local freqYLoc = RL_GetShaderLocation( shader, "freqY" )
    local ampXLoc = RL_GetShaderLocation( shader, "ampX" )
    local ampYLoc = RL_GetShaderLocation( shader, "ampY" )
    local speedXLoc = RL_GetShaderLocation( shader, "speedX" )
    local speedYLoc = RL_GetShaderLocation( shader, "speedY" )

	local freqX = 25.0
    local freqY = 25.0
    local ampX = 5.0
    local ampY = 5.0
    local speedX = 8.0
    local speedY = 8.0

    RL_SetShaderValue( shader, sizeLoc, textureSize, SHADER_UNIFORM_VEC2 )
    RL_SetShaderValue( shader, freqXLoc, { freqX }, SHADER_UNIFORM_FLOAT )
    RL_SetShaderValue( shader, freqYLoc, { freqY }, SHADER_UNIFORM_FLOAT )
    RL_SetShaderValue( shader, ampXLoc, { ampX }, SHADER_UNIFORM_FLOAT )
    RL_SetShaderValue( shader, ampYLoc, { ampY }, SHADER_UNIFORM_FLOAT )
    RL_SetShaderValue( shader, speedXLoc, { speedX }, SHADER_UNIFORM_FLOAT )
    RL_SetShaderValue( shader, speedYLoc, { speedY }, SHADER_UNIFORM_FLOAT )
end

local seconds = 0.0

function draw()
	seconds = seconds + RL_GetFrameTime();

    RL_SetShaderValue( shader, secondsLoc, { seconds }, SHADER_UNIFORM_FLOAT );

	RL_ClearBackground( { 100, 150, 100 } )

	RL_BeginShaderMode( shader )
		RL_DrawTexture( texture, { 0, 0 }, WHITE );
	RL_EndShaderMode()
end
