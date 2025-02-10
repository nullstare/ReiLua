package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vector2 = require( "vector2" )
Rect = require( "rectangle" )

local monitor = 0
local winSize = Vector2:new( 1920, 1080 )

local catTex = nil
local tileTex = nil
local lightTex = nil
local lightTexSize = Vector2:new()

local buttonSize = Vector2:new( 20, 20 )
local fontSize = 20
local textTint = RL.BLACK

local guiRect = Rect:new( 0, 0, 550, 210 )
local lightPos = Vector2:new()
local lightPos2 = Vector2:new()

local framebuffer = nil

local blendMode = {
	mode = 1,
	options = {
		{ name = "BLEND_ALPHA", value = RL.BLEND_ALPHA },
		{ name = "BLEND_ADDITIVE", value = RL.BLEND_ADDITIVE },
		{ name = "BLEND_MULTIPLIED", value = RL.BLEND_MULTIPLIED },
		{ name = "BLEND_ADD_COLORS", value = RL.BLEND_ADD_COLORS },
		{ name = "BLEND_SUBTRACT_COLORS", value = RL.BLEND_SUBTRACT_COLORS },
		{ name = "BLEND_ALPHA_PREMULTIPLY", value = RL.BLEND_ALPHA_PREMULTIPLY },
		{ name = "BLEND_CUSTOM", value = RL.BLEND_CUSTOM },
		{ name = "BLEND_CUSTOM_SEPARATE", value = RL.BLEND_CUSTOM_SEPARATE },
	}
}
local blendFactor = {
	srcRGB = 1,
	dstRGB = 1,
	srcAlpha = 1,
	dstAlpha = 1,
	options = {
		{ name = "RL_ZERO", value = RL.RL_ZERO },
		{ name = "RL_ONE", value = RL.RL_ONE },
		{ name = "RL_SRC_COLOR", value = RL.RL_SRC_COLOR },
		{ name = "RL_ONE_MINUS_SRC_COLOR", value = RL.RL_ONE_MINUS_SRC_COLOR },
		{ name = "RL_SRC_ALPHA", value = RL.RL_SRC_ALPHA },
		{ name = "RL_ONE_MINUS_SRC_ALPHA", value = RL.RL_ONE_MINUS_SRC_ALPHA },
		{ name = "RL_DST_ALPHA", value = RL.RL_DST_ALPHA },
		{ name = "RL_ONE_MINUS_DST_ALPHA", value = RL.RL_ONE_MINUS_DST_ALPHA },
		{ name = "RL_DST_COLOR", value = RL.RL_DST_COLOR },
		{ name = "RL_ONE_MINUS_DST_COLOR", value = RL.RL_ONE_MINUS_DST_COLOR },
		{ name = "RL_SRC_ALPHA_SATURATE", value = RL.RL_SRC_ALPHA_SATURATE },
		{ name = "RL_CONSTANT_COLOR", value = RL.RL_CONSTANT_COLOR },
		{ name = "RL_ONE_MINUS_CONSTANT_COLOR", value = RL.RL_ONE_MINUS_CONSTANT_COLOR },
		{ name = "RL_CONSTANT_ALPHA", value = RL.RL_CONSTANT_ALPHA },
		{ name = "RL_ONE_MINUS_CONSTANT_ALPHA", value = RL.RL_ONE_MINUS_CONSTANT_ALPHA },
	}
}
local blendFunction = {
	eqRGB = 1,
	eqAlpha = 1,
	options = {
		{ name = "RL_FUNC_ADD", value = RL.RL_FUNC_ADD },
		{ name = "RL_MIN", value = RL.RL_MIN },
		{ name = "RL_MAX", value = RL.RL_MAX },
		{ name = "RL_FUNC_SUBTRACT", value = RL.RL_FUNC_SUBTRACT },
		{ name = "RL_FUNC_REVERSE_SUBTRACT", value = RL.RL_FUNC_REVERSE_SUBTRACT },
		{ name = "RL_BLEND_EQUATION", value = RL.RL_BLEND_EQUATION },
		{ name = "RL_BLEND_EQUATION_RGB", value = RL.RL_BLEND_EQUATION_RGB },
		{ name = "RL_BLEND_EQUATION_ALPHA", value = RL.RL_BLEND_EQUATION_ALPHA },
		{ name = "RL_BLEND_DST_RGB", value = RL.RL_BLEND_DST_RGB },
		{ name = "RL_BLEND_SRC_RGB", value = RL.RL_BLEND_SRC_RGB },
		{ name = "RL_BLEND_DST_ALPHA", value = RL.RL_BLEND_DST_ALPHA },
		{ name = "RL_BLEND_SRC_ALPHA", value = RL.RL_BLEND_SRC_ALPHA },
		{ name = "RL_BLEND_COLOR", value = RL.RL_BLEND_COLOR },
	}
}

function RL.init()
	RL.SetWindowTitle( "Blend modes" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )

	local monitorPos = Vector2:newT( RL.GetMonitorPosition( monitor ) )
	local monitorSize = Vector2:newT( RL.GetMonitorSize( monitor ) )
	RL.SetWindowPosition( { monitorPos.x + monitorSize.x / 2 - winSize.x / 2, monitorPos.y + monitorSize.y / 2 - winSize.y / 2 } )

	local path = RL.GetBasePath().."../resources/images/"

	catTex = RL.LoadTexture( path.."cat.png" )
	RL.SetTextureWrap( catTex, RL.TEXTURE_WRAP_REPEAT )

	tileTex = RL.LoadTexture( path.."tile.png" )
	RL.SetTextureWrap( tileTex, RL.TEXTURE_WRAP_REPEAT )

	lightTex = RL.LoadTexture( path.."light.png" )
	lightTexSize:setT( RL.GetTextureSize( lightTex ) )

	framebuffer = RL.LoadRenderTexture( winSize )

	lightPos:setV( winSize:scale( 0.5 ) - lightTexSize:scale( 0.5 ) )
	lightPos2:setV( winSize:scale( 0.5 ) - lightTexSize:scale( 0.5 ) )
end

function RL.update( delta )
	local mousePos = Vector2:newT( RL.GetMousePosition() )

	if not RL.CheckCollisionPointRec( mousePos, guiRect ) then
		if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_LEFT ) then
			lightPos:setV( mousePos - lightTexSize:scale( 0.5 ) )
		end
		if RL.IsMouseButtonDown( RL.MOUSE_BUTTON_RIGHT ) then
			lightPos2:setV( mousePos - lightTexSize:scale( 0.5 ) )
		end
	end
end

local function drawControl( pos, t, name )
	if RL.GuiButton( { pos.x, pos.y, buttonSize.x, buttonSize.y }, RL.GuiIconText( RL.ICON_ARROW_LEFT, "" ) ) == 1 then
		t[ name ] = 1 < t[ name ] and t[ name ] - 1 or #t.options
	end
	pos.x = pos.x + buttonSize.x + 2

	if RL.GuiButton( { pos.x, pos.y, buttonSize.x, buttonSize.y }, RL.GuiIconText( RL.ICON_ARROW_RIGHT, "" ) ) == 1 then
		t[ name ] = t[ name ] < #t.options and t[ name ] + 1 or 1
	end
	pos.x = pos.x + buttonSize.x + 2

	RL.DrawText( name..": "..t.options[ t[ name ] ].name, pos, fontSize, textTint )

	pos.x = 2
	pos.y = pos.y + 2 + buttonSize.y
end

local function drawControls()
	local pos = Vector2:new( 2 )

	-- Blend mode.
	drawControl( pos, blendMode, "mode" )
	-- Blend RPG.
	pos.y = pos.y + 8
	drawControl( pos, blendFactor, "srcRGB" )
	drawControl( pos, blendFactor, "dstRGB" )
	drawControl( pos, blendFunction, "eqRGB" )
	-- Blend Alpha.
	pos.y = pos.y + 8
	drawControl( pos, blendFactor, "srcAlpha" )
	drawControl( pos, blendFactor, "dstAlpha" )
	drawControl( pos, blendFunction, "eqAlpha" )
	
	pos.y = pos.y + 8
	RL.DrawText( "Set texture positions with mouse right and left.", pos, 20, RL.BLACK )
end

function RL.draw()
	RL.ClearBackground( RL.BLACK )

	if framebuffer then
		RL.BeginTextureMode( framebuffer )
			RL.ClearBackground( RL.BLACK )
			RL.DrawTexturePro( catTex,
				{ 0, 0, winSize.x, winSize.y },
				{ 0, 0, winSize.x, winSize.y },
				{ 0, 0 },
				0.0,
				RL.WHITE
			)
			RL.rlSetBlendFactors(
				blendFactor.options[ blendFactor.srcRGB ].value,
				blendFactor.options[ blendFactor.dstRGB ].value,
				blendFunction.options[ blendFunction.eqRGB ].value
			)
			RL.rlSetBlendFactorsSeparate(
				blendFactor.options[ blendFactor.srcRGB ].value,
				blendFactor.options[ blendFactor.dstRGB ].value,
				blendFactor.options[ blendFactor.srcAlpha ].value,
				blendFactor.options[ blendFactor.dstAlpha ].value,
				blendFunction.options[ blendFunction.eqRGB ].value,
				blendFunction.options[ blendFunction.eqAlpha ].value
			)
			RL.BeginBlendMode( blendMode.options[ blendMode.mode ].value )
				RL.DrawTexture( lightTex, lightPos, RL.RED )
				RL.DrawTexture( lightTex, lightPos2, RL.BLUE )
			RL.EndBlendMode()
		RL.EndTextureMode()
	end

	RL.DrawTexturePro( tileTex,
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0 },
		0.0,
		RL.WHITE
	)
	RL.DrawTexturePro(
		RL.GetRenderTextureTexture( framebuffer ),
		{ 0, 0, winSize.x, -winSize.y },
		{ 0, 0, winSize.x, winSize.y },
		{ 0, 0 },
		0.0,
		RL.WHITE
	)
	RL.DrawRectangle( guiRect, { 255, 255, 255, 200 } )
	drawControls()
end
