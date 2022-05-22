#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "core.h"
#include "shapes.h"
#include "textures.h"
#include "models.h"
#include "text.h"
#include "audio.h"
#include "rmath.h"
#include "rgui.h"
#include "lights.h"

static void assignGlobalInt( int value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushinteger( L, value );
	lua_setglobal( L, name );
}

static void assignGlobalFloat( float value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushnumber( L, value );
	lua_setglobal( L, name );
}

static void assignGlobalColor( Color color, const char *name ) {
	lua_State *L = state->luaState;
	uluaPushColor( L, color );
	lua_setglobal( L, name );
}

void defineGlobals() {
/*DOC_START*/
	/* Keys */
	assignGlobalInt( KEY_ENTER, "KEY_ENTER" );
	assignGlobalInt( KEY_SPACE, "KEY_SPACE" );
	assignGlobalInt( KEY_ESCAPE, "KEY_ESCAPE" );
	assignGlobalInt( KEY_ENTER, "KEY_ENTER" );
	assignGlobalInt( KEY_TAB, "KEY_TAB" );
	assignGlobalInt( KEY_BACKSPACE, "KEY_BACKSPACE" );
	assignGlobalInt( KEY_INSERT, "KEY_INSERT" );
	assignGlobalInt( KEY_DELETE, "KEY_DELETE" );
	assignGlobalInt( KEY_RIGHT, "KEY_RIGHT" );
	assignGlobalInt( KEY_LEFT, "KEY_LEFT" );
	assignGlobalInt( KEY_DOWN, "KEY_DOWN" );
	assignGlobalInt( KEY_UP, "KEY_UP" );
	/* WindowFlags */
	assignGlobalInt( FLAG_VSYNC_HINT, "FLAG_VSYNC_HINT" );
	assignGlobalInt( FLAG_FULLSCREEN_MODE, "FLAG_FULLSCREEN_MODE" );
	assignGlobalInt( FLAG_WINDOW_RESIZABLE, "FLAG_WINDOW_RESIZABLE" );
	assignGlobalInt( FLAG_WINDOW_UNDECORATED, "FLAG_WINDOW_UNDECORATED" );
	assignGlobalInt( FLAG_WINDOW_HIDDEN, "FLAG_WINDOW_HIDDEN" );
	assignGlobalInt( FLAG_WINDOW_MINIMIZED, "FLAG_WINDOW_MINIMIZED" );
	assignGlobalInt( FLAG_WINDOW_MAXIMIZED, "FLAG_WINDOW_MAXIMIZED" );
	assignGlobalInt( FLAG_WINDOW_UNFOCUSED, "FLAG_WINDOW_UNFOCUSED" );
	assignGlobalInt( FLAG_WINDOW_TOPMOST, "FLAG_WINDOW_TOPMOST" );
	assignGlobalInt( FLAG_WINDOW_ALWAYS_RUN, "FLAG_WINDOW_ALWAYS_RUN" );
	assignGlobalInt( FLAG_WINDOW_TRANSPARENT, "FLAG_WINDOW_TRANSPARENT" );
	assignGlobalInt( FLAG_WINDOW_HIGHDPI, "FLAG_WINDOW_HIGHDPI" );
	assignGlobalInt( FLAG_MSAA_4X_HINT, "FLAG_MSAA_4X_HINT" );
	assignGlobalInt( FLAG_INTERLACED_HINT, "FLAG_INTERLACED_HINT" );
	/* BlendModes */
	assignGlobalInt( BLEND_ALPHA, "BLEND_ALPHA" );
	assignGlobalInt( BLEND_ADDITIVE, "BLEND_ADDITIVE" );
	assignGlobalInt( BLEND_MULTIPLIED, "BLEND_MULTIPLIED" );
	assignGlobalInt( BLEND_ADD_COLORS, "BLEND_ADD_COLORS" );
	assignGlobalInt( BLEND_SUBTRACT_COLORS, "BLEND_SUBTRACT_COLORS" );
	assignGlobalInt( BLEND_CUSTOM, "BLEND_CUSTOM" );
	/* TextureModes */
	assignGlobalInt( TEXTURE_SOURCE_TEXTURE, "TEXTURE_SOURCE_TEXTURE" );
	assignGlobalInt( TEXTURE_SOURCE_RENDER_TEXTURE, "TEXTURE_SOURCE_RENDER_TEXTURE" );
	/* CameraProjections */
	assignGlobalInt( CAMERA_PERSPECTIVE, "CAMERA_PERSPECTIVE" );
	assignGlobalInt( CAMERA_ORTHOGRAPHIC, "CAMERA_ORTHOGRAPHIC" );
	/* CameraMode */
	assignGlobalInt( CAMERA_CUSTOM, "CAMERA_CUSTOM" );
	assignGlobalInt( CAMERA_FREE, "CAMERA_FREE" );
	assignGlobalInt( CAMERA_ORBITAL, "CAMERA_ORBITAL" );
	assignGlobalInt( CAMERA_FIRST_PERSON, "CAMERA_FIRST_PERSON" );
	assignGlobalInt( CAMERA_THIRD_PERSON, "CAMERA_THIRD_PERSON" );
	/* MapTypes */
	assignGlobalInt( MATERIAL_MAP_ALBEDO, "MATERIAL_MAP_ALBEDO" );
	assignGlobalInt( MATERIAL_MAP_METALNESS, "MATERIAL_MAP_METALNESS" );
	assignGlobalInt( MATERIAL_MAP_NORMAL, "MATERIAL_MAP_NORMAL" );
	assignGlobalInt( MATERIAL_MAP_ROUGHNESS, "MATERIAL_MAP_ROUGHNESS" );
	assignGlobalInt( MATERIAL_MAP_OCCLUSION, "MATERIAL_MAP_OCCLUSION" );
	assignGlobalInt( MATERIAL_MAP_EMISSION, "MATERIAL_MAP_EMISSION" );
	assignGlobalInt( MATERIAL_MAP_HEIGHT, "MATERIAL_MAP_HEIGHT" );
	assignGlobalInt( MATERIAL_MAP_CUBEMAP, "MATERIAL_MAP_CUBEMAP" );
	assignGlobalInt( MATERIAL_MAP_IRRADIANCE, "MATERIAL_MAP_IRRADIANCE" );
	assignGlobalInt( MATERIAL_MAP_PREFILTER, "MATERIAL_MAP_PREFILTER" );
	assignGlobalInt( MATERIAL_MAP_BRDF, "MATERIAL_MAP_BRDF" );
	/* TextureFilters */
	assignGlobalInt( TEXTURE_FILTER_POINT, "TEXTURE_FILTER_POINT" );
	assignGlobalInt( TEXTURE_FILTER_BILINEAR, "TEXTURE_FILTER_BILINEAR" );
	assignGlobalInt( TEXTURE_FILTER_TRILINEAR, "TEXTURE_FILTER_TRILINEAR" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_4X, "TEXTURE_FILTER_ANISOTROPIC_4X" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_8X, "TEXTURE_FILTER_ANISOTROPIC_8X" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_16X, "TEXTURE_FILTER_ANISOTROPIC_16X" );
	/* TextureWrapModes */
	assignGlobalInt( TEXTURE_WRAP_REPEAT, "TEXTURE_WRAP_REPEAT" );
	assignGlobalInt( TEXTURE_WRAP_CLAMP, "TEXTURE_WRAP_CLAMP" );
	assignGlobalInt( TEXTURE_WRAP_MIRROR_REPEAT, "TEXTURE_WRAP_MIRROR_REPEAT" );
	assignGlobalInt( TEXTURE_WRAP_MIRROR_CLAMP, "TEXTURE_WRAP_MIRROR_CLAMP" );
	/* TraceLogLevel */
	assignGlobalInt( LOG_ALL, "LOG_ALL" );
	assignGlobalInt( LOG_TRACE, "LOG_TRACE" );
	assignGlobalInt( LOG_DEBUG, "LOG_DEBUG" );
	assignGlobalInt( LOG_INFO, "LOG_INFO" );
	assignGlobalInt( LOG_WARNING, "LOG_WARNING" );
	assignGlobalInt( LOG_ERROR, "LOG_ERROR" );
	assignGlobalInt( LOG_FATAL, "LOG_FATAL" );
	assignGlobalInt( LOG_NONE, "LOG_NONE" );
	/* N-patchLayout */
	assignGlobalInt( NPATCH_NINE_PATCH, "NPATCH_NINE_PATCH" );
	assignGlobalInt( NPATCH_THREE_PATCH_VERTICAL, "NPATCH_THREE_PATCH_VERTICAL" );
	assignGlobalInt( NPATCH_THREE_PATCH_HORIZONTAL, "NPATCH_THREE_PATCH_HORIZONTAL" );
	/* ShaderLocationIndex */
	assignGlobalInt( SHADER_LOC_VERTEX_POSITION, "SHADER_LOC_VERTEX_POSITION" );
	assignGlobalInt( SHADER_LOC_VERTEX_TEXCOORD01, "SHADER_LOC_VERTEX_TEXCOORD01" );
	assignGlobalInt( SHADER_LOC_VERTEX_TEXCOORD02, "SHADER_LOC_VERTEX_TEXCOORD02" );
	assignGlobalInt( SHADER_LOC_VERTEX_NORMAL, "SHADER_LOC_VERTEX_NORMAL" );
	assignGlobalInt( SHADER_LOC_VERTEX_TANGENT, "SHADER_LOC_VERTEX_TANGENT" );
	assignGlobalInt( SHADER_LOC_VERTEX_COLOR, "SHADER_LOC_VERTEX_COLOR" );
	assignGlobalInt( SHADER_LOC_MATRIX_MVP, "SHADER_LOC_MATRIX_MVP" );
	assignGlobalInt( SHADER_LOC_MATRIX_VIEW, "SHADER_LOC_MATRIX_VIEW" );
	assignGlobalInt( SHADER_LOC_MATRIX_PROJECTION, "SHADER_LOC_MATRIX_PROJECTION" );
	assignGlobalInt( SHADER_LOC_MATRIX_MODEL, "SHADER_LOC_MATRIX_MODEL" );
	assignGlobalInt( SHADER_LOC_MATRIX_NORMAL, "SHADER_LOC_MATRIX_NORMAL" );
	assignGlobalInt( SHADER_LOC_VECTOR_VIEW, "SHADER_LOC_VECTOR_VIEW" );
	assignGlobalInt( SHADER_LOC_COLOR_DIFFUSE, "SHADER_LOC_COLOR_DIFFUSE" );
	assignGlobalInt( SHADER_LOC_COLOR_SPECULAR, "SHADER_LOC_COLOR_SPECULAR" );
	assignGlobalInt( SHADER_LOC_COLOR_AMBIENT, "SHADER_LOC_COLOR_AMBIENT" );
	assignGlobalInt( SHADER_LOC_MAP_ALBEDO, "SHADER_LOC_MAP_ALBEDO" );
	assignGlobalInt( SHADER_LOC_MAP_METALNESS, "SHADER_LOC_MAP_METALNESS" );
	assignGlobalInt( SHADER_LOC_MAP_NORMAL, "SHADER_LOC_MAP_NORMAL" );
	assignGlobalInt( SHADER_LOC_MAP_ROUGHNESS, "SHADER_LOC_MAP_ROUGHNESS" );
	assignGlobalInt( SHADER_LOC_MAP_OCCLUSION, "SHADER_LOC_MAP_OCCLUSION" );
	assignGlobalInt( SHADER_LOC_MAP_EMISSION, "SHADER_LOC_MAP_EMISSION" );
	assignGlobalInt( SHADER_LOC_MAP_HEIGHT, "SHADER_LOC_MAP_HEIGHT" );
	assignGlobalInt( SHADER_LOC_MAP_CUBEMAP, "SHADER_LOC_MAP_CUBEMAP" );
	assignGlobalInt( SHADER_LOC_MAP_IRRADIANCE, "SHADER_LOC_MAP_IRRADIANCE" );
	assignGlobalInt( SHADER_LOC_MAP_PREFILTER, "SHADER_LOC_MAP_PREFILTER" );
	assignGlobalInt( SHADER_LOC_MAP_BRDF, "SHADER_LOC_MAP_BRDF" );
	/* ShaderUniformDataType */
	assignGlobalInt( SHADER_UNIFORM_FLOAT, "SHADER_UNIFORM_FLOAT" );
	assignGlobalInt( SHADER_UNIFORM_VEC2, "SHADER_UNIFORM_VEC2" );
	assignGlobalInt( SHADER_UNIFORM_VEC3, "SHADER_UNIFORM_VEC3" );
	assignGlobalInt( SHADER_UNIFORM_VEC4, "SHADER_UNIFORM_VEC4" );
	assignGlobalInt( SHADER_UNIFORM_INT, "SHADER_UNIFORM_INT" );
	assignGlobalInt( SHADER_UNIFORM_IVEC2, "SHADER_UNIFORM_IVEC2" );
	assignGlobalInt( SHADER_UNIFORM_IVEC3, "SHADER_UNIFORM_IVEC3" );
	assignGlobalInt( SHADER_UNIFORM_IVEC4, "SHADER_UNIFORM_IVEC4" );
	assignGlobalInt( SHADER_UNIFORM_SAMPLER2D, "SHADER_UNIFORM_SAMPLER2D" );
	/* ShaderAttributeDataTypes */
	assignGlobalInt( SHADER_ATTRIB_FLOAT, "SHADER_ATTRIB_FLOAT" );
	assignGlobalInt( SHADER_ATTRIB_VEC2, "SHADER_ATTRIB_VEC2" );
	assignGlobalInt( SHADER_ATTRIB_VEC3, "SHADER_ATTRIB_VEC3" );
	assignGlobalInt( SHADER_ATTRIB_VEC4, "SHADER_ATTRIB_VEC4" );
	/* Gesture */
	assignGlobalInt( GESTURE_NONE, "GESTURE_NONE" );
	assignGlobalInt( GESTURE_TAP, "GESTURE_TAP" );
	assignGlobalInt( GESTURE_DOUBLETAP, "GESTURE_DOUBLETAP" );
	assignGlobalInt( GESTURE_HOLD, "GESTURE_HOLD" );
	assignGlobalInt( GESTURE_DRAG, "GESTURE_DRAG" );
	assignGlobalInt( GESTURE_SWIPE_RIGHT, "GESTURE_SWIPE_RIGHT" );
	assignGlobalInt( GESTURE_SWIPE_LEFT, "GESTURE_SWIPE_LEFT" );
	assignGlobalInt( GESTURE_SWIPE_UP, "GESTURE_SWIPE_UP" );
	assignGlobalInt( GESTURE_SWIPE_DOWN, "GESTURE_SWIPE_DOWN" );
	assignGlobalInt( GESTURE_PINCH_IN, "GESTURE_PINCH_IN" );
	assignGlobalInt( GESTURE_PINCH_OUT, "GESTURE_PINCH_OUT" );
	/* PixelFormats */
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R5G6B5, "PIXELFORMAT_UNCOMPRESSED_R5G6B5" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R8G8B8, "PIXELFORMAT_UNCOMPRESSED_R8G8B8" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R5G5B5A1, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R4G4B4A4, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32, "PIXELFORMAT_UNCOMPRESSED_R32" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32G32B32, "PIXELFORMAT_UNCOMPRESSED_R32G32B32" );
	assignGlobalInt( PIXELFORMAT_UNCOMPRESSED_R32G32B32A32, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT1_RGB, "PIXELFORMAT_COMPRESSED_DXT1_RGB" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT1_RGBA, "PIXELFORMAT_COMPRESSED_DXT1_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT3_RGBA, "PIXELFORMAT_COMPRESSED_DXT3_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_DXT5_RGBA, "PIXELFORMAT_COMPRESSED_DXT5_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC1_RGB, "PIXELFORMAT_COMPRESSED_ETC1_RGB" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC2_RGB, "PIXELFORMAT_COMPRESSED_ETC2_RGB" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_PVRT_RGB, "PIXELFORMAT_COMPRESSED_PVRT_RGB" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_PVRT_RGBA, "PIXELFORMAT_COMPRESSED_PVRT_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA" );
	assignGlobalInt( PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA" );
	/* Colors */
	assignGlobalColor( WHITE, "WHITE" );
	assignGlobalColor( BLACK, "BLACK" );
	assignGlobalColor( BLANK, "BLANK" );
	assignGlobalColor( MAGENTA, "MAGENTA" );
	assignGlobalColor( RAYWHITE, "RAYWHITE" );
	assignGlobalColor( RED, "RED" );
	assignGlobalColor( GREEN, "GREEN" );
	assignGlobalColor( BLUE, "BLUE" );
	/* Math */
	assignGlobalFloat( PI, "PI" );
	assignGlobalFloat( DEG2RAD, "DEG2RAD" );
	assignGlobalFloat( RAD2DEG, "RAD2DEG" );
	/* GuiControlState */
	assignGlobalInt( GUI_STATE_NORMAL, "GUI_STATE_NORMAL" );
	assignGlobalInt( GUI_STATE_FOCUSED, "GUI_STATE_FOCUSED" );
	assignGlobalInt( GUI_STATE_PRESSED, "GUI_STATE_PRESSED" );
	assignGlobalInt( GUI_STATE_DISABLED, "GUI_STATE_DISABLED" );
	/* GuiTextAlignment */
	assignGlobalInt( GUI_TEXT_ALIGN_LEFT, "GUI_TEXT_ALIGN_LEFT" );
	assignGlobalInt( GUI_TEXT_ALIGN_CENTER, "GUI_TEXT_ALIGN_CENTER" );
	assignGlobalInt( GUI_TEXT_ALIGN_RIGHT, "GUI_TEXT_ALIGN_RIGHT" );
	/* GuiControls */
	assignGlobalInt( DEFAULT, "DEFAULT" );
	assignGlobalInt( LABEL, "LABEL" );
	assignGlobalInt( BUTTON, "BUTTON" );
	assignGlobalInt( TOGGLE, "TOGGLE" );
	assignGlobalInt( SLIDER, "SLIDER" );
	assignGlobalInt( PROGRESSBAR, "PROGRESSBAR" );
	assignGlobalInt( CHECKBOX, "CHECKBOX" );
	assignGlobalInt( COMBOBOX, "COMBOBOX" );
	assignGlobalInt( DROPDOWNBOX, "DROPDOWNBOX" );
	assignGlobalInt( TEXTBOX, "TEXTBOX" );
	assignGlobalInt( VALUEBOX, "VALUEBOX" );
	assignGlobalInt( SPINNER, "SPINNER" );
	assignGlobalInt( LISTVIEW, "LISTVIEW" );
	assignGlobalInt( COLORPICKER, "COLORPICKER" );
	assignGlobalInt( SCROLLBAR, "SCROLLBAR" );
	assignGlobalInt( STATUSBAR, "STATUSBAR" );
	/* GuiControlProperty */
	assignGlobalInt( BORDER_COLOR_NORMAL, "BORDER_COLOR_NORMAL" );
	assignGlobalInt( BASE_COLOR_NORMAL, "BASE_COLOR_NORMAL" );
	assignGlobalInt( TEXT_COLOR_NORMAL, "TEXT_COLOR_NORMAL" );
	assignGlobalInt( BORDER_COLOR_FOCUSED, "BORDER_COLOR_FOCUSED" );
	assignGlobalInt( BASE_COLOR_FOCUSED, "BASE_COLOR_FOCUSED" );
	assignGlobalInt( TEXT_COLOR_FOCUSED, "TEXT_COLOR_FOCUSED" );
	assignGlobalInt( BORDER_COLOR_PRESSED, "BORDER_COLOR_PRESSED" );
	assignGlobalInt( BASE_COLOR_PRESSED, "BASE_COLOR_PRESSED" );
	assignGlobalInt( TEXT_COLOR_PRESSED, "TEXT_COLOR_PRESSED" );
	assignGlobalInt( BORDER_COLOR_DISABLED, "BORDER_COLOR_DISABLED" );
	assignGlobalInt( BASE_COLOR_DISABLED, "BASE_COLOR_DISABLED" );
	assignGlobalInt( TEXT_COLOR_DISABLED, "TEXT_COLOR_DISABLED" );
	assignGlobalInt( BORDER_WIDTH, "BORDER_WIDTH" );
	assignGlobalInt( TEXT_PADDING, "TEXT_PADDING" );
	assignGlobalInt( TEXT_ALIGNMENT, "TEXT_ALIGNMENT" );
	assignGlobalInt( RESERVED, "RESERVED" );
	/* GuiDefaultProperty */
	assignGlobalInt( TEXT_SIZE, "TEXT_SIZE" );
	assignGlobalInt( TEXT_SPACING, "TEXT_SPACING" );
	assignGlobalInt( LINE_COLOR, "LINE_COLOR" );
	assignGlobalInt( BACKGROUND_COLOR, "BACKGROUND_COLOR" );
	/* GuiToggleProperty */
	assignGlobalInt( GROUP_PADDING, "GROUP_PADDING" );
	/* GuiSliderProperty */
	assignGlobalInt( SLIDER_WIDTH, "SLIDER_WIDTH" );
	assignGlobalInt( SLIDER_PADDING, "SLIDER_PADDING" );
	/* GuiProgressBarProperty */
	assignGlobalInt( PROGRESS_PADDING, "PROGRESS_PADDING" );
	/* GuiCheckBoxProperty */
	assignGlobalInt( CHECK_PADDING, "CHECK_PADDING" );
	/* GuiComboBoxProperty */
	assignGlobalInt( COMBO_BUTTON_WIDTH, "COMBO_BUTTON_WIDTH" );
	assignGlobalInt( COMBO_BUTTON_SPACING, "COMBO_BUTTON_SPACING" );
	/* GuiDropdownBoxProperty */
	assignGlobalInt( ARROW_PADDING, "ARROW_PADDING" );
	assignGlobalInt( DROPDOWN_ITEMS_SPACING, "DROPDOWN_ITEMS_SPACING" );
	/* GuiTextBoxProperty */
	assignGlobalInt( TEXT_INNER_PADDING, "TEXT_INNER_PADDING" );
	assignGlobalInt( TEXT_LINES_SPACING, "TEXT_LINES_SPACING" );
	/* GuiSpinnerProperty */
	assignGlobalInt( SPIN_BUTTON_WIDTH, "SPIN_BUTTON_WIDTH" );
	assignGlobalInt( SPIN_BUTTON_SPACING, "SPIN_BUTTON_SPACING" );
	/* GuiScrollBarProperty */
	assignGlobalInt( ARROWS_SIZE, "ARROWS_SIZE" );
	assignGlobalInt( ARROWS_VISIBLE, "ARROWS_VISIBLE" );
	assignGlobalInt( SCROLL_SLIDER_PADDING, "SCROLL_SLIDER_PADDING" );
	assignGlobalInt( SCROLL_SLIDER_SIZE, "SCROLL_SLIDER_SIZE" );
	assignGlobalInt( SCROLL_PADDING, "SCROLL_PADDING" );
	assignGlobalInt( SCROLL_SPEED, "SCROLL_SPEED" );
	/* GuiListViewProperty */
	assignGlobalInt( LIST_ITEMS_HEIGHT, "LIST_ITEMS_HEIGHT" );
	assignGlobalInt( LIST_ITEMS_SPACING, "LIST_ITEMS_SPACING" );
	assignGlobalInt( SCROLLBAR_WIDTH, "SCROLLBAR_WIDTH" );
	assignGlobalInt( SCROLLBAR_SIDE, "SCROLLBAR_SIDE" );
	/* GuiColorPickerProperty */
	assignGlobalInt( COLOR_SELECTOR_SIZE, "COLOR_SELECTOR_SIZE" );
	assignGlobalInt( HUEBAR_WIDTH, "HUEBAR_WIDTH" );
	assignGlobalInt( HUEBAR_PADDING, "HUEBAR_PADDING" );
	assignGlobalInt( HUEBAR_SELECTOR_HEIGHT, "HUEBAR_SELECTOR_HEIGHT" );
	assignGlobalInt( HUEBAR_SELECTOR_OVERFLOW, "HUEBAR_SELECTOR_OVERFLOW" );
	/* LightType */
	assignGlobalInt( LIGHT_DIRECTIONAL, "LIGHT_DIRECTIONAL" );
	assignGlobalInt( LIGHT_POINT, "LIGHT_POINT" );
/*DOC_END*/
}

// Custom logging funtion
void LogCustom( int msgType, const char *text, va_list args ) {
	char string[ STRING_LEN ] = {'\0'};
	char msg[ STRING_LEN ] = {'\0'};

	vsprintf( string, text, args );

    switch ( msgType ) {
        case LOG_ALL: sprintf( msg, "ALL: %s", string ); break;
        case LOG_TRACE: sprintf( msg, "TRACE: %s", string ); break;
        case LOG_DEBUG: sprintf( msg, "DEBUG: %s", string ); break;
        case LOG_INFO: sprintf( msg, "INFO: %s", string ); break;
        case LOG_WARNING: sprintf( msg, "WARNING: %s", string ); break;
        case LOG_ERROR: sprintf( msg, "ERROR: %s", string ); break;
        case LOG_FATAL: sprintf( msg, "FATAL: %s", string ); break;
        default: break;
    }
	printf( "%s\n", msg );

	/* Call Lua log function if exists. */
	lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );
	lua_getglobal( L, "log" );

    if ( lua_isfunction( L, -1 ) ) {
        lua_pushstring( L, msg );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_WARNING, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }
    }
	lua_pop( L, -1 );
}

bool luaInit() {
	state->luaState = luaL_newstate();

    luaL_openlibs( state->luaState );

	if ( state->luaState == NULL ) {
		TraceLog( LOG_WARNING, "%s", "Failed to init Lua" );

		return false;
	}
	luaRegister();
	defineGlobals();

	return luaCallMain();
}

int luaTraceback( lua_State *L ) {
	lua_getglobal( L, "debug" );

	if ( !lua_istable( L, -1 ) ) {
		lua_pop( L, 1 );
		return 1;
	}

	lua_getfield( L, -1, "traceback" );

	if ( !lua_isfunction( L, -1 ) ) {
		lua_pop(L, 2);
		return 1;
	}

	lua_pushvalue( L, 1 ); // pass error message
	lua_pushinteger( L, 2 ); // skip this function and traceback
	lua_call( L, 2, 1 ); // call debug.traceback

	return 1;
}

bool luaCallMain() {
	lua_State *L = state->luaState;

	char path[ STRING_LEN ] = { '\0' };

/* If web, set path to resources folder. */
#ifdef EMSCRIPTEN
	sprintf( path, "resources/main.lua" );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		sprintf( path, "resources/main" );
	}
#else
	sprintf( path, "%smain.lua", state->exePath );
	/* Alternatively look for main. Could be precompiled binary file. */
	if ( !FileExists( path ) ) {
		sprintf( path, "%smain", state->exePath );
	}
#endif

    luaL_dofile( L, path );

	/* Check errors in main.lua */
	if ( lua_tostring( state->luaState, -1 ) ) {
		TraceLog( LOG_WARNING, "Lua error: %s\n", lua_tostring( state->luaState, -1 ) );
	}

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	lua_getglobal( L, "init" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_WARNING, "Lua error: %s", lua_tostring( L, -1 ) );
			return false;
		}
	}
	else {
		TraceLog( LOG_WARNING, "%s", "No Lua main found!" );
        return false;
    }
	/* Apply custom callback here. */
	SetTraceLogCallback( LogCustom );

	return true;
}

void luaCallProcess() {
    lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
    lua_getglobal( L, "process" );

    if ( lua_isfunction( L, -1 ) ) {
        lua_pushnumber( L, GetFrameTime() );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_WARNING, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }
    }
    // else {
	// 	TraceLog( LOG_WARNING, "%s", "No Lua process found!" );
	// 	state->run = false;
    //     return;
    // }
	lua_pop( L, -1 );
}

void luaCallDraw() {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
    lua_getglobal( L, "draw" );

    if ( lua_isfunction( L, -1 ) ) {
		BeginDrawing();

        if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_WARNING, "Lua error: %s", lua_tostring( L, -1 ) );
			// state->run = false;
 	    	return;
        }

		EndDrawing();
    }
    // else {
	// 	TraceLog( LOG_WARNING, "%s", "No Lua render found!" );
	// 	state->run = false;
    //     return;
    // }
	lua_pop( L, -1 );
}

void luaRegister() {
	lua_State *L = state->luaState;

	/* Core. */
		/* Window. */
	lua_register( L, "RL_IsWindowReady", lcoreIsWindowReady );
	lua_register( L, "RL_IsWindowFullscreen", lcoreIsWindowFullscreen );
	lua_register( L, "RL_IsWindowHidden", lcoreIsWindowHidden );
	lua_register( L, "RL_IsWindowMinimized", lcoreIsWindowMinimized );
	lua_register( L, "RL_IsWindowMaximized", lcoreIsWindowMaximized );
	lua_register( L, "RL_IsWindowFocused", lcoreIsWindowFocused );
	lua_register( L, "RL_SetWindowMonitor", lcoreSetWindowMonitor );
	lua_register( L, "RL_SetWindowPosition", lcoreSetWindowPosition );
	lua_register( L, "RL_SetWindowSize", lcoreSetWindowSize );
	lua_register( L, "RL_SetWindowMinSize", lcoreSetWindowMinSize );
	lua_register( L, "RL_GetMonitorPosition", lcoreGetMonitorPosition );
	lua_register( L, "RL_GetMonitorSize", lcoreGetMonitorSize );
	lua_register( L, "RL_GetWindowPosition", lcoreGetWindowPosition );
	lua_register( L, "RL_GetWindowSize", lcoreGetWindowSize );
	lua_register( L, "RL_SetWindowState", lcoreSetWindowState );
	lua_register( L, "RL_IsWindowState", lcoreIsWindowState );
	lua_register( L, "RL_ClearWindowState", lcoreClearWindowState );
	lua_register( L, "RL_IsWindowResized", lcoreIsWindowResized );
	lua_register( L, "RL_SetWindowIcon", lcoreSetWindowIcon );
	lua_register( L, "RL_SetWindowTitle", lcoreSetWindowTitle );
	lua_register( L, "RL_GetMonitorCount", lcoreGetMonitorCount );
	lua_register( L, "RL_GetCurrentMonitor", lcoreGetCurrentMonitor );
	lua_register( L, "RL_GetMonitorPhysicalSize", lcoreGetMonitorPhysicalSize );
	lua_register( L, "RL_GetMonitorRefreshRate", lcoreGetMonitorRefreshRate );
	lua_register( L, "RL_GetWindowScaleDPI", lcoreGetWindowScaleDPI );
	lua_register( L, "RL_GetMonitorName", lcoreGetMonitorName );
	lua_register( L, "RL_CloseWindow", lcoreCloseWindow );
	lua_register( L, "RL_SetClipboardText", lcoreSetClipboardText );
	lua_register( L, "RL_GetClipboardText", lcoreGetClipboardText );
		/* Timing. */
	lua_register( L, "RL_SetTargetFPS", lcoreSetTargetFPS );
	lua_register( L, "RL_GetFrameTime", lcoreGetFrameTime );
	lua_register( L, "RL_GetTime", lcoreGetTime );
		/* Misc. */
	lua_register( L, "RL_TraceLog", lcoreTraceLog );
	lua_register( L, "RL_OpenURL", lcoreOpenURL );
		/* Cursor. */
	lua_register( L, "RL_ShowCursor", lcoreShowCursor );
	lua_register( L, "RL_HideCursor", lcoreHideCursor );
	lua_register( L, "RL_IsCursorHidden", lcoreIsCursorHidden );
	lua_register( L, "RL_EnableCursor", lcoreEnableCursor );
	lua_register( L, "RL_DisableCursor", lcoreDisableCursor );
	lua_register( L, "RL_IsCursorOnScreen", lcoreIsCursorOnScreen );
		/* Drawing. */
	lua_register( L, "RL_ClearBackground", lcoreClearBackground );
	lua_register( L, "RL_BeginDrawing", lcoreBeginDrawing );
	lua_register( L, "RL_EndDrawing", lcoreEndDrawing );
	lua_register( L, "RL_BeginBlendMode", lcoreBeginBlendMode );
	lua_register( L, "RL_EndBlendMode", lcoreEndBlendMode );
	lua_register( L, "RL_BeginScissorMode", lcoreBeginScissorMode );
	lua_register( L, "RL_EndScissorMode", lcoreEndScissorMode );
		/* Shader. */
	lua_register( L, "RL_LoadShader", lcoreLoadShader );
	lua_register( L, "RL_LoadShaderFromMemory", lcoreLoadShaderFromMemory );
	lua_register( L, "RL_BeginShaderMode", lcoreBeginShaderMode );
	lua_register( L, "RL_EndShaderMode", lcoreEndShaderMode );
	lua_register( L, "RL_GetShaderLocation", lcoreGetShaderLocation );
	lua_register( L, "RL_GetShaderLocationAttrib", lcoreGetShaderLocationAttrib );
	lua_register( L, "RL_SetShaderLocationIndex", lcoreSetShaderLocationIndex );
	lua_register( L, "RL_GetShaderLocationIndex", lcoreGetShaderLocationIndex );
	lua_register( L, "RL_SetShaderValueMatrix", lcoreSetShaderValueMatrix );
	lua_register( L, "RL_SetShaderValueTexture", lcoreSetShaderValueTexture );
	lua_register( L, "RL_SetShaderValue", lcoreSetShaderValue );
	lua_register( L, "RL_SetShaderValueV", lcoreSetShaderValueV );
	lua_register( L, "RL_UnloadShader", lcoreUnloadShader );
		/* File. */
	lua_register( L, "RL_GetBasePath", lcoreGetBasePath );
	lua_register( L, "RL_FileExists", lcoreFileExists );
	lua_register( L, "RL_DirectoryExists", lcoreDirectoryExists );
	lua_register( L, "RL_IsFileExtension", lcoreIsFileExtension );
	lua_register( L, "RL_GetFileExtension", lcoreGetFileExtension );
	lua_register( L, "RL_GetFileName", lcoreGetFileName );
	lua_register( L, "RL_GetFileNameWithoutExt", lcoreGetFileNameWithoutExt );
	lua_register( L, "RL_GetDirectoryPath", lcoreGetDirectoryPath );
	lua_register( L, "RL_GetPrevDirectoryPath", lcoreGetPrevDirectoryPath );
	lua_register( L, "RL_GetWorkingDirectory", lcoreGetWorkingDirectory );
	lua_register( L, "RL_GetDirectoryFiles", lcoreGetDirectoryFiles );
	lua_register( L, "RL_ChangeDirectory", lcoreChangeDirectory );
	lua_register( L, "RL_IsFileDropped", lcoreIsFileDropped );
	lua_register( L, "RL_GetDroppedFiles", lcoreGetDroppedFiles );
	lua_register( L, "RL_GetFileModTime", lcoreGetFileModTime );
		/* Camera3D. */
	lua_register( L, "RL_CreateCamera2D", lcoreCreateCamera2D );
	lua_register( L, "RL_UnloadCamera2D", lcoreUnloadCamera2D );
	lua_register( L, "RL_BeginMode2D", lcoreBeginMode2D );
	lua_register( L, "RL_EndMode2D", lcoreEndMode2D );
	lua_register( L, "RL_SetCamera2DTarget", lcoreSetCamera2DTarget );
	lua_register( L, "RL_SetCamera2DOffset", lcoreSetCamera2DOffset );
	lua_register( L, "RL_SetCamera2DRotation", lcoreSetCamera2DRotation );
	lua_register( L, "RL_SetCamera2DZoom", lcoreSetCamera2DZoom );
	lua_register( L, "RL_GetCamera2DTarget", lcoreGetCamera2DTarget );
	lua_register( L, "RL_GetCamera2DOffset", lcoreGetCamera2DOffset );
	lua_register( L, "RL_GetCamera2DRotation", lcoreGetCamera2DRotation );
	lua_register( L, "RL_GetCamera2DZoom", lcoreGetCamera2DZoom );
		/* Camera3D. */
	lua_register( L, "RL_CreateCamera3D", lcoreCreateCamera3D );
	lua_register( L, "RL_UnloadCamera3D", lcoreUnloadCamera3D );
	lua_register( L, "RL_BeginMode3D", lcoreBeginMode3D );
	lua_register( L, "RL_EndMode3D", lcoreEndMode3D );
	lua_register( L, "RL_SetCamera3DPosition", lcoreSetCamera3DPosition );
	lua_register( L, "RL_SetCamera3DTarget", lcoreSetCamera3DTarget );
	lua_register( L, "RL_SetCamera3DUp", lcoreSetCamera3DUp );
	lua_register( L, "RL_SetCamera3DFovy", lcoreSetCamera3DFovy );
	lua_register( L, "RL_SetCamera3DProjection", lcoreSetCamera3DProjection );
	lua_register( L, "RL_GetCamera3DPosition", lcoreGetCamera3DPosition );
	lua_register( L, "RL_GetCamera3DTarget", lcoreGetCamera3DTarget );
	lua_register( L, "RL_GetCamera3DUp", lcoreGetCamera3DUp );
	lua_register( L, "RL_GetCamera3DFovy", lcoreGetCamera3DFovy );
	lua_register( L, "RL_GetCamera3DProjection", lcoreGetCamera3DProjection );
	lua_register( L, "RL_UpdateCamera3D", lcoreUpdateCamera3D );
	lua_register( L, "RL_SetCamera3DMode", lcoreSetCamera3DMode );
		/* Input. */
	lua_register( L, "RL_IsKeyPressed", lcoreIsKeyPressed );
	lua_register( L, "RL_IsKeyDown", lcoreIsKeyDown );
	lua_register( L, "RL_IsKeyReleased", lcoreIsKeyReleased );
	lua_register( L, "RL_GetKeyPressed", lcoreGetKeyPressed );
	lua_register( L, "RL_GetCharPressed", lcoreGetCharPressed );
	lua_register( L, "RL_SetExitKey", lcoreSetExitKey );
	lua_register( L, "RL_IsGamepadAvailable", lcoreIsGamepadAvailable );
	lua_register( L, "RL_IsGamepadButtonPressed", lcoreIsGamepadButtonPressed );
	lua_register( L, "RL_IsGamepadButtonDown", lcoreIsGamepadButtonDown );
	lua_register( L, "RL_IsGamepadButtonReleased", lcoreIsGamepadButtonReleased );
	lua_register( L, "RL_GetGamepadAxisCount", lcoreGetGamepadAxisCount );
	lua_register( L, "RL_GetGamepadAxisMovement", lcoreGetGamepadAxisMovement );
	lua_register( L, "RL_GetGamepadName", lcoreGetGamepadName );
	lua_register( L, "RL_IsMouseButtonPressed", lcoreIsMouseButtonPressed );
	lua_register( L, "RL_IsMouseButtonDown", lcoreIsMouseButtonDown );
	lua_register( L, "RL_IsMouseButtonReleased", lcoreIsMouseButtonReleased );
	lua_register( L, "RL_GetMousePosition", lcoreGetMousePosition );
	lua_register( L, "RL_GetMouseDelta", lcoreGetMouseDelta );
	lua_register( L, "RL_GetMouseWheelMove", lcoreGetMouseWheelMove );
	lua_register( L, "RL_SetMousePosition", lcoreSetMousePosition );
	lua_register( L, "RL_GetTouchPosition", lcoreGetTouchPosition );
	lua_register( L, "RL_GetTouchPointId", lcoreGetTouchPointId );
	lua_register( L, "RL_GetTouchPointCount", lcoreGetTouchPointCount );
	lua_register( L, "RL_SetGesturesEnabled", lcoreSetGesturesEnabled );
	lua_register( L, "RL_IsGestureDetected", lcoreIsGestureDetected );
	lua_register( L, "RL_GetGestureDetected", lcoreGetGestureDetected );
	lua_register( L, "RL_GetGestureHoldDuration", lcoreGetGestureHoldDuration );
	lua_register( L, "RL_GetGestureDragVector", lcoreGetGestureDragVector );
	lua_register( L, "RL_GetGestureDragAngle", lcoreGetGestureDragAngle );
	lua_register( L, "RL_GetGesturePinchVector", lcoreGetGesturePinchVector );
	lua_register( L, "RL_GetGesturePinchAngle", lcoreGetGesturePinchAngle );
		/* Screen-space. */
	lua_register( L, "RL_GetMouseRay", lcoreGetMouseRay );
	lua_register( L, "RL_GetCameraMatrix", lcoreGetCameraMatrix );
	lua_register( L, "RL_GetCameraMatrix2D", lcoreGetCameraMatrix2D );
	lua_register( L, "RL_GetWorldToScreen", lcoreGetWorldToScreen );
	lua_register( L, "RL_GetWorldToScreenEx", lcoreGetWorldToScreenEx );
	lua_register( L, "RL_GetWorldToScreen2D", lcoreGetWorldToScreen2D );
	lua_register( L, "RL_GetScreenToWorld2D", lcoreGetScreenToWorld2D );

	/* Shapes. */
		/* Drawing. */
	lua_register( L, "RL_DrawPixel", lshapesDrawPixel );
	lua_register( L, "RL_DrawLine", lshapesDrawLine );
	lua_register( L, "RL_DrawCircle", lshapesDrawCircle );
	lua_register( L, "RL_DrawCircleLines", lshapesDrawCircleLines );
	lua_register( L, "RL_DrawRectangle", lshapesDrawRectangle );
	lua_register( L, "RL_DrawRectanglePro", lshapesDrawRectanglePro );
	lua_register( L, "RL_DrawTriangle", lshapesDrawTriangle );
	lua_register( L, "RL_DrawTriangleLines", lshapesDrawTriangleLines );
		/* Collision. */
	lua_register( L, "RL_CheckCollisionRecs", lshapesCheckCollisionRecs );
	lua_register( L, "RL_CheckCollisionCircles", lshapesCheckCollisionCircles );
	lua_register( L, "RL_CheckCollisionCircleRec", lshapesCheckCollisionCircleRec );
	lua_register( L, "RL_CheckCollisionPointRec", lshapesCheckCollisionPointRec );
	lua_register( L, "RL_CheckCollisionPointCircle", lshapesCheckCollisionPointCircle );
	lua_register( L, "RL_CheckCollisionPointTriangle", lshapesCheckCollisionPointTriangle );
	lua_register( L, "RL_CheckCollisionLines", lshapesCheckCollisionLines );
	lua_register( L, "RL_CheckCollisionPointLine", lshapesCheckCollisionPointLine );
	lua_register( L, "RL_GetCollisionRec", lshapesGetCollisionRec );

	/* Textures. */
		/* File. */
	lua_register( L, "RL_LoadImage", ltexturesLoadImage );
	lua_register( L, "RL_LoadImageFromTexture", ltexturesLoadImageFromTexture );
	lua_register( L, "RL_LoadImageFromScreen", ltexturesLoadImageFromScreen );
	lua_register( L, "RL_UnloadImage", ltexturesUnloadImage );
	lua_register( L, "RL_ExportImage", ltexturesExportImage );
	lua_register( L, "RL_ExportImageAsCode", ltexturesExportImageAsCode );
	lua_register( L, "RL_LoadTexture", ltexturesLoadTexture );
	lua_register( L, "RL_LoadTextureFromImage", ltexturesLoadTextureFromImage );
	lua_register( L, "RL_UnloadTexture", ltexturesUnloadTexture );
	lua_register( L, "RL_LoadRenderTexture", ltexturesLoadRenderTexture );
	lua_register( L, "RL_UnloadRenderTexture", ltexturesUnloadRenderTexture );
		/* Image Generation. */
	lua_register( L, "RL_GenImageColor", ltexturesGenImageColor );
	lua_register( L, "RL_GenImageGradientV", ltexturesGenImageGradientV );
	lua_register( L, "RL_GenImageGradientH", ltexturesGenImageGradientH );
	lua_register( L, "RL_GenImageGradientRadial", ltexturesGenImageGradientRadial );
	lua_register( L, "RL_GenImageChecked", ltexturesGenImageChecked );
	lua_register( L, "RL_GenImageWhiteNoise", ltexturesGenImageWhiteNoise );
	lua_register( L, "RL_GenImageCellular", ltexturesGenImageCellular );
		/* Image Manipulation Functions. */
	lua_register( L, "RL_ImageCopy", ltexturesImageCopy );
	lua_register( L, "RL_ImageFromImage", ltexturesImageFromImage );
	lua_register( L, "RL_ImageText", ltexturesImageText );
	lua_register( L, "RL_ImageFormat", ltexturesImageFormat );
	lua_register( L, "RL_ImageToPOT", ltexturesImageToPOT );
	lua_register( L, "RL_ImageCrop", ltexturesImageCrop );
	lua_register( L, "RL_ImageAlphaCrop", ltexturesImageAlphaCrop );
	lua_register( L, "RL_ImageAlphaClear", ltexturesImageAlphaClear );
	lua_register( L, "RL_ImageAlphaMask", ltexturesImageAlphaMask );
	lua_register( L, "RL_ImageAlphaPremultiply", ltexturesImageAlphaPremultiply );
	lua_register( L, "RL_ImageResize", ltexturesImageResize );
	lua_register( L, "RL_ImageResizeNN", ltexturesImageResizeNN );
	lua_register( L, "RL_ImageResizeCanvas", ltexturesImageResizeCanvas );
	lua_register( L, "RL_ImageMipmaps", ltexturesImageMipmaps );
	lua_register( L, "RL_ImageDither", ltexturesImageDither );
	lua_register( L, "RL_ImageFlipVertical", ltexturesImageFlipVertical );
	lua_register( L, "RL_ImageFlipHorizontal", ltexturesImageFlipHorizontal );
	lua_register( L, "RL_ImageRotateCW", ltexturesImageRotateCW );
	lua_register( L, "RL_ImageRotateCCW", ltexturesImageRotateCCW );
	lua_register( L, "RL_ImageColorTint", ltexturesImageColorTint );
	lua_register( L, "RL_ImageColorInvert", ltexturesImageColorInvert );
	lua_register( L, "RL_ImageColorGrayscale", ltexturesImageColorGrayscale );
	lua_register( L, "RL_ImageColorContrast", ltexturesImageColorContrast );
	lua_register( L, "RL_ImageColorBrightness", ltexturesImageColorBrightness );
	lua_register( L, "RL_ImageColorReplace", ltexturesImageColorReplace );
	lua_register( L, "RL_LoadImageColors", ltexturesLoadImageColors );
	lua_register( L, "RL_LoadImagePalette", ltexturesLoadImagePalette );
	lua_register( L, "RL_GetImageAlphaBorder", ltexturesGetImageAlphaBorder );
	lua_register( L, "RL_GetImageColor", ltexturesGetImageColor );
		/* Image Drawing. */
	lua_register( L, "RL_ImageClearBackground", ltexturesImageClearBackground );
	lua_register( L, "RL_ImageDrawPixel", ltexturesImageDrawPixel );
	lua_register( L, "RL_ImageDrawLine", ltexturesImageDrawLine );
	lua_register( L, "RL_ImageDrawCircle", ltexturesImageDrawCircle );
	lua_register( L, "RL_ImageDrawRectangle", ltexturesImageDrawRectangle );
	lua_register( L, "RL_ImageDrawRectangleLines", ltexturesImageDrawRectangleLines );
	lua_register( L, "RL_ImageDraw", ltexturesImageDraw );
	lua_register( L, "RL_ImageDrawTextEx", ltexturesImageDrawTextEx );
		/* Image Configuration. */
	lua_register( L, "RL_GetImageSize", ltexturesGetImageSize );
	lua_register( L, "RL_GetImageMipmaps", ltexturesGetImageMipmaps );
	lua_register( L, "RL_GetImageFormat", ltexturesGetImageFormat );
		/* Texture Drawing. */
	lua_register( L, "RL_DrawTexture", ltexturesDrawTexture );
	lua_register( L, "RL_DrawTextureRec", ltexturesDrawTextureRec );
	lua_register( L, "RL_DrawTextureTiled", ltexturesDrawTextureTiled );
	lua_register( L, "RL_DrawTexturePro", ltexturesDrawTexturePro );
	lua_register( L, "RL_DrawTextureNPatch", ltexturesDrawTextureNPatch );
	lua_register( L, "RL_DrawTexturePoly", ltexturesDrawTexturePoly );
	lua_register( L, "RL_BeginTextureMode", ltexturesBeginTextureMode );
	lua_register( L, "RL_EndTextureMode", ltexturesEndTextureMode );
	lua_register( L, "RL_SetTextureSource", ltexturesSetTextureSource );
	lua_register( L, "RL_GetTextureSource", ltexturesGetTextureSource );
		/* Texture Configuration. */
	lua_register( L, "RL_GenTextureMipmaps", ltexturesGenTextureMipmaps );
	lua_register( L, "RL_SetTextureFilter", ltexturesSetTextureFilter );
	lua_register( L, "RL_SetTextureWrap", ltexturesSetTextureWrap );
	lua_register( L, "RL_GetTextureSize", ltexturesGetTextureSize );
	lua_register( L, "RL_GetTextureMipmaps", ltexturesGetTextureMipmaps );
	lua_register( L, "RL_GetTextureFormat", ltexturesGetTextureFormat );
		/* Color/pixel */
	lua_register( L, "RL_Fade", ltexturesFade );
	lua_register( L, "RL_ColorToInt", ltexturesColorToInt );
	lua_register( L, "RL_ColorNormalize", ltexturesColorNormalize );
	lua_register( L, "RL_ColorFromNormalized", ltexturesColorFromNormalized );
	lua_register( L, "RL_ColorToHSV", ltexturesColorToHSV );
	lua_register( L, "RL_ColorFromHSV", ltexturesColorFromHSV );
	lua_register( L, "RL_ColorAlpha", ltexturesColorAlpha );
	lua_register( L, "RL_ColorAlphaBlend", ltexturesColorAlphaBlend );
	lua_register( L, "RL_GetColor", ltexturesGetColor );
	lua_register( L, "RL_GetPixelColor", ltexturesGetPixelColor );
	lua_register( L, "RL_GetPixelDataSize", ltexturesGetPixelDataSize );

	/* Models. */
		/* Basic. */
	lua_register( L, "RL_DrawLine3D", lmodelsDrawLine3D );
	lua_register( L, "RL_DrawPoint3D", lmodelsDrawPoint3D );
	lua_register( L, "RL_DrawCircle3D", lmodelsDrawCircle3D );
	lua_register( L, "RL_DrawTriangle3D", lmodelsDrawTriangle3D );
	lua_register( L, "RL_DrawCube", lmodelsDrawCube );
	lua_register( L, "RL_DrawCubeWires", lmodelsDrawCubeWires );
	lua_register( L, "RL_DrawCubeTexture", lmodelsDrawCubeTexture );
	lua_register( L, "RL_DrawSphere", lmodelsDrawSphere );
	lua_register( L, "RL_DrawSphereEx", lmodelsDrawSphereEx );
	lua_register( L, "RL_DrawSphereWires", lmodelsDrawSphereWires );
	lua_register( L, "RL_DrawCylinder", lmodelsDrawCylinder );
	lua_register( L, "RL_DrawCylinderEx", lmodelsDrawCylinderEx );
	lua_register( L, "RL_DrawCylinderWires", lmodelsDrawCylinderWires );
	lua_register( L, "RL_DrawCylinderWiresEx", lmodelsDrawCylinderWiresEx );
	lua_register( L, "RL_DrawPlane", lmodelsDrawPlane );
	lua_register( L, "RL_DrawQuad3DTexture", lmodelDrawQuad3DTexture );
	lua_register( L, "RL_DrawRay", lmodelsDrawRay );
	lua_register( L, "RL_DrawGrid", lmodelsDrawGrid );
		/* Mesh. */
	lua_register( L, "RL_GenMeshPoly", lmodelsGenMeshPoly );
	lua_register( L, "RL_GenMeshPlane", lmodelsGenMeshPlane );
	lua_register( L, "RL_GenMeshCube", lmodelsGenMeshCube );
	lua_register( L, "RL_GenMeshSphere", lmodelsGenMeshSphere );
	lua_register( L, "RL_GenMeshCylinder", lmodelsGenMeshCylinder );
	lua_register( L, "RL_GenMeshCone", lmodelsGenMeshCone );
	lua_register( L, "RL_GenMeshTorus", lmodelsGenMeshTorus );
	lua_register( L, "RL_GenMeshKnot", lmodelsGenMeshKnot );
	lua_register( L, "RL_GenMeshHeightmap", lmodelsGenMeshHeightmap );
	lua_register( L, "RL_GenMeshCustom", lmodelsGenMeshCustom );
	lua_register( L, "RL_UpdateMesh", lmodelsUpdateMesh );
	lua_register( L, "RL_UnloadMesh", lmodelsUnloadMesh );
	lua_register( L, "RL_DrawMesh", lmodelsDrawMesh );
	lua_register( L, "RL_DrawMeshInstanced", lmodelsDrawMeshInstanced );
	lua_register( L, "RL_SetMeshColor", lmodelsSetMeshColor );
		/* Material. */
	lua_register( L, "RL_LoadMaterialDefault", lmodelsLoadMaterialDefault );
	lua_register( L, "RL_CreateMaterial", lmodelsCreateMaterial );
	lua_register( L, "RL_UnloadMaterial", lmodelsUnloadMaterial );
	lua_register( L, "RL_SetMaterialTexture", lmodelsSetMaterialTexture );
	lua_register( L, "RL_SetMaterialColor", lmodelsSetMaterialColor );
	lua_register( L, "RL_SetMaterialValue", lmodelsSetMaterialValue );
		/* Model. */
	lua_register( L, "RL_LoadModel", lmodelsLoadModel );
	lua_register( L, "RL_LoadModelFromMesh", lmodelsLoadModelFromMesh );
	lua_register( L, "RL_UnloadModel", lmodelsUnloadModel );
	lua_register( L, "RL_DrawModel", lmodelsDrawModel );
	lua_register( L, "RL_DrawModelEx", lmodelsDrawModelEx );
	lua_register( L, "RL_SetModelMaterial", lmodelsSetModelMaterial );
	lua_register( L, "RL_SetModelMeshMaterial", lmodelsSetModelMeshMaterial );
	lua_register( L, "RL_DrawBillboard", lmodelsDrawBillboard );
	lua_register( L, "RL_DrawBillboardRec", lmodelsDrawBillboardRec );
	lua_register( L, "RL_SetModelTransform", lmodelsSetModelTransform );
	lua_register( L, "RL_GetModelTransform", lmodelsGetModelTransform );
		/* Animations. */
	lua_register( L, "RL_LoadModelAnimations", lmodelsLoadModelAnimations );
	lua_register( L, "RL_UpdateModelAnimation", lmodelsUpdateModelAnimation );
	lua_register( L, "RL_GetModelAnimationBoneCount", lmodelsGetModelAnimationBoneCount );
	lua_register( L, "RL_GetModelAnimationFrameCount", lmodelsGetModelAnimationFrameCount );
		/* Collision. */
	lua_register( L, "RL_CheckCollisionSpheres", lmodelsCheckCollisionSpheres );
	lua_register( L, "RL_CheckCollisionBoxes", lmodelsCheckCollisionBoxes );
	lua_register( L, "RL_CheckCollisionBoxSphere", lmodelsCheckCollisionBoxSphere );
	lua_register( L, "RL_GetRayCollisionSphere", lmodelsGetRayCollisionSphere );
	lua_register( L, "RL_GetRayCollisionBox", lmodelsGetRayCollisionBox );
	lua_register( L, "RL_GetRayCollisionModel", lmodelsGetRayCollisionModel );
	lua_register( L, "RL_GetRayCollisionMesh", lmodelsGetRayCollisionMesh );
	lua_register( L, "RL_GetRayCollisionTriangle", lmodelsGetRayCollisionTriangle );
	lua_register( L, "RL_GetRayCollisionQuad", lmodelsGetRayCollisionQuad );

	/* Text. */
		/* Loading. */
	lua_register( L, "RL_LoadFont", ltextLoadFont );
	lua_register( L, "RL_LoadFontFromImage", ltextLoadFontFromImage );
	lua_register( L, "RL_UnloadFont", ltextUnloadFont );
		/* Drawing. */
	lua_register( L, "RL_DrawFPS", ltextDrawFPS );
	lua_register( L, "RL_DrawText", ltextDrawText );
	lua_register( L, "RL_DrawTextPro", ltextDrawTextPro );
		/* Misc. */
	lua_register( L, "RL_MeasureText", ltextMeasureText );

	/* Audio. */
		/* Sound. */
	lua_register( L, "RL_LoadSound", laudioLoadSound );
	lua_register( L, "RL_PlaySoundMulti", laudioPlaySoundMulti );
	lua_register( L, "RL_SetSoundVolume", laudioSetSoundVolume );
	lua_register( L, "RL_SetSoundPitch", laudioSetSoundPitch );
	lua_register( L, "RL_UnloadSound", laudioUnloadSound );
		/* Music. */
	lua_register( L, "RL_LoadMusicStream", laudioLoadMusicStream );
	lua_register( L, "RL_PlayMusicStream", laudioPlayMusicStream );
	lua_register( L, "RL_StopMusicStream", laudioStopMusicStream );
	lua_register( L, "RL_PauseMusicStream", laudioPauseMusicStream );
	lua_register( L, "RL_ResumeMusicStream", laudioResumeMusicStream );
	lua_register( L, "RL_IsMusicStreamPlaying", laudioIsMusicStreamPlaying );
	lua_register( L, "RL_SetMusicVolume", laudioSetMusicVolume );

	/* Math. */
		/* Utils. */
	lua_register( L, "RL_Clamp", lmathClamp );
	lua_register( L, "RL_Lerp", lmathLerp );
	lua_register( L, "RL_Normalize", lmathNormalize );
	lua_register( L, "RL_Remap", lmathRemap );
		/* Vector2. */
	lua_register( L, "RL_Vector2Zero", lmathVector2Zero );
	lua_register( L, "RL_Vector2One", lmathVector2One );
	lua_register( L, "RL_Vector2Add", lmathVector2Add );
	lua_register( L, "RL_Vector2AddValue", lmathVector2AddValue );
	lua_register( L, "RL_Vector2Subtract", lmathVector2Subtract );
	lua_register( L, "RL_Vector2SubtractValue", lmathVector2SubtractValue );
	lua_register( L, "RL_Vector2Length", lmathVector2Length );
	lua_register( L, "RL_Vector2LengthSqr", lmathVector2LengthSqr );
	lua_register( L, "RL_Vector2DotProduct", lmathVector2DotProduct );
	lua_register( L, "RL_Vector2Distance", lmathVector2Distance );
	lua_register( L, "RL_Vector2Angle", lmathVector2Angle );
	lua_register( L, "RL_Vector2Scale", lmathVector2Scale );
	lua_register( L, "RL_Vector2Multiply", lmathVector2Multiply );
	lua_register( L, "RL_Vector2Negate", lmathVector2Negate );
	lua_register( L, "RL_Vector2Divide", lmathVector2Divide );
	lua_register( L, "RL_Vector2Normalize", lmathVector2Normalize );
	lua_register( L, "RL_Vector2Lerp", lmathVector2Lerp );
	lua_register( L, "RL_Vector2Reflect", lmathVector2Reflect );
	lua_register( L, "RL_Vector2Rotate", lmathVector2Rotate );
	lua_register( L, "RL_Vector2MoveTowards", lmathVector2MoveTowards );
		/* Vector3. */
	lua_register( L, "RL_Vector3Zero", lmathVector3Zero );
	lua_register( L, "RL_Vector3One", lmathVector3One );
	lua_register( L, "RL_Vector3Add", lmathVector3Add );
	lua_register( L, "RL_Vector3AddValue", lmathVector3AddValue );
	lua_register( L, "RL_Vector3Subtract", lmathVector3Subtract );
	lua_register( L, "RL_Vector3SubtractValue", lmathVector3SubtractValue );
	lua_register( L, "RL_Vector3Scale", lmathVector3Scale );
	lua_register( L, "RL_Vector3Multiply", lmathVector3Multiply );
	lua_register( L, "RL_Vector3CrossProduct", lmathVector3CrossProduct );
	lua_register( L, "RL_Vector3Perpendicular", lmathVector3Perpendicular );
	lua_register( L, "RL_Vector3Length", lmathVector3Length );
	lua_register( L, "RL_Vector3LengthSqr", lmathVector3LengthSqr );
	lua_register( L, "RL_Vector3DotProduct", lmathVector3DotProduct );
	lua_register( L, "RL_Vector3Distance", lmathVector3Distance );
	lua_register( L, "RL_Vector3Angle", lmathVector3Angle );
	lua_register( L, "RL_Vector3Negate", lmathVector3Negate );
	lua_register( L, "RL_Vector3Divide", lmathVector3Divide );
	lua_register( L, "RL_Vector3Normalize", lmathVector3Normalize );
	lua_register( L, "RL_Vector3OrthoNormalize", lmathVector3OrthoNormalize );
	lua_register( L, "RL_Vector3Transform", lmathVector3Transform );
	lua_register( L, "RL_Vector3RotateByQuaternion", lmathVector3RotateByQuaternion );
	lua_register( L, "RL_Vector3Lerp", lmathVector3Lerp );
	lua_register( L, "RL_Vector3Reflect", lmathVector3Reflect );
	lua_register( L, "RL_Vector3Min", lmathVector3Min );
	lua_register( L, "RL_Vector3Max", lmathVector3Max );
	lua_register( L, "RL_Vector3Barycenter", lmathVector3Barycenter );
	lua_register( L, "RL_Vector3Unproject", lmathVector3Unproject );
		/* Matrix. */
	lua_register( L, "RL_MatrixDeterminant", lmathMatrixDeterminant );
	lua_register( L, "RL_MatrixTrace", lmathMatrixTrace );
	lua_register( L, "RL_MatrixTranspose", lmathMatrixTranspose );
	lua_register( L, "RL_MatrixInvert", lmathMatrixInvert );
	lua_register( L, "RL_MatrixNormalize", lmathMatrixNormalize );
	lua_register( L, "RL_MatrixIdentity", lmathMatrixIdentity );
	lua_register( L, "RL_MatrixAdd", lmathMatrixAdd );
	lua_register( L, "RL_MatrixSubtract", lmathMatrixSubtract );
	lua_register( L, "RL_MatrixMultiply", lmathMatrixMultiply );
	lua_register( L, "RL_MatrixTranslate", lmathMatrixTranslate );
	lua_register( L, "RL_MatrixRotate", lmathMatrixRotate );
	lua_register( L, "RL_MatrixRotateX", lmathMatrixRotateX );
	lua_register( L, "RL_MatrixRotateY", lmathMatrixRotateY );
	lua_register( L, "RL_MatrixRotateZ", lmathMatrixRotateZ );
	lua_register( L, "RL_MatrixRotateXYZ", lmathMatrixRotateXYZ );
	lua_register( L, "RL_MatrixRotateZYX", lmathMatrixRotateZYX );
	lua_register( L, "RL_MatrixScale", lmathMatrixScale );
	lua_register( L, "RL_MatrixFrustum", lmathMatrixFrustum );
	lua_register( L, "RL_MatrixPerspective", lmathMatrixPerspective );
	lua_register( L, "RL_MatrixOrtho", lmathMatrixOrtho );
	lua_register( L, "RL_MatrixLookAt", lmathMatrixLookAt );
		/* Quaternion. */
	lua_register( L, "RL_QuaternionAdd", lmathQuaternionAdd );
	lua_register( L, "RL_QuaternionAddValue", lmathQuaternionAddValue );
	lua_register( L, "RL_QuaternionSubtract", lmathQuaternionSubtract );
	lua_register( L, "RL_QuaternionSubtractValue", lmathQuaternionSubtractValue );
	lua_register( L, "RL_QuaternionIdentity", lmathQuaternionIdentity );
	lua_register( L, "RL_QuaternionLength", lmathQuaternionLength );
	lua_register( L, "RL_QuaternionNormalize", lmathQuaternionNormalize );
	lua_register( L, "RL_QuaternionInvert", lmathQuaternionInvert );
	lua_register( L, "RL_QuaternionMultiply", lmathQuaternionMultiply );
	lua_register( L, "RL_QuaternionScale", lmathQuaternionScale );
	lua_register( L, "RL_QuaternionDivide", lmathQuaternionDivide );
	lua_register( L, "RL_QuaternionLerp", lmathQuaternionLerp );
	lua_register( L, "RL_QuaternionNlerp", lmathQuaternionNlerp );
	lua_register( L, "RL_QuaternionSlerp", lmathQuaternionSlerp );
	lua_register( L, "RL_QuaternionFromVector3ToVector3", lmathQuaternionFromVector3ToVector3 );
	lua_register( L, "RL_QuaternionFromMatrix", lmathQuaternionFromMatrix );
	lua_register( L, "RL_QuaternionToMatrix", lmathQuaternionToMatrix );
	lua_register( L, "RL_QuaternionFromAxisAngle", lmathQuaternionFromAxisAngle );
	lua_register( L, "RL_QuaternionToAxisAngle", lmathQuaternionToAxisAngle );
	lua_register( L, "RL_QuaternionFromEuler", lmathQuaternionFromEuler );
	lua_register( L, "RL_QuaternionToEuler", lmathQuaternionToEuler );
	lua_register( L, "RL_QuaternionTransform", lmathQuaternionTransform );

	/* Gui. */
		/* Global. */
	lua_register( L, "RL_GuiEnable", lguiGuiEnable );
	lua_register( L, "RL_GuiDisable", lguiGuiDisable );
	lua_register( L, "RL_GuiLock", lguiGuiLock );
	lua_register( L, "RL_GuiUnlock", lguiGuiUnlock );
	lua_register( L, "RL_GuiIsLocked", lguiGuiIsLocked );
	lua_register( L, "RL_GuiFade", lguiGuiFade );
	lua_register( L, "RL_GuiSetState", lguiGuiSetState );
	lua_register( L, "RL_GuiGetState", lguiGuiGetState );
		/* Font. */
	lua_register( L, "RL_GuiSetFont", lguiGuiSetFont );
		/* Style. */
	lua_register( L, "RL_GuiSetStyle", lguiGuiSetStyle );
	lua_register( L, "RL_GuiGetStyle", lguiGuiGetStyle );
	lua_register( L, "RL_GuiLoadStyle", lguiGuiLoadStyle );
	lua_register( L, "RL_GuiLoadStyleDefault", lguiGuiLoadStyleDefault );
		/* Container. */
	lua_register( L, "RL_GuiWindowBox", lguiGuiWindowBox );
	lua_register( L, "RL_GuiGroupBox", lguiGuiGroupBox );
	lua_register( L, "RL_GuiLine", lguiGuiLine );
	lua_register( L, "RL_GuiPanel", lguiGuiPanel );
	lua_register( L, "RL_GuiScrollPanel", lguiGuiScrollPanel );
		/* Basic. */
	lua_register( L, "RL_GuiLabel", lguiGuiLabel );
	lua_register( L, "RL_GuiButton", lguiGuiButton );
	lua_register( L, "RL_GuiLabelButton", lguiGuiLabelButton );
	lua_register( L, "RL_GuiToggle", lguiGuiToggle );
	lua_register( L, "RL_GuiToggleGroup", lguiGuiToggleGroup );
	lua_register( L, "RL_GuiCheckBox", lguiGuiCheckBox );
	lua_register( L, "RL_GuiComboBox", lguiGuiComboBox );
	lua_register( L, "RL_GuiTextBox", lguiGuiTextBox );
	lua_register( L, "RL_GuiTextBoxMulti", lguiGuiTextBoxMulti );
	lua_register( L, "RL_GuiSpinner", lguiGuiSpinner );
	lua_register( L, "RL_GuiValueBox", lguiGuiValueBox );
	lua_register( L, "RL_GuiSlider", lguiGuiSlider );
	lua_register( L, "RL_GuiSliderBar", lguiGuiSliderBar );
	lua_register( L, "RL_GuiProgressBar", lguiGuiProgressBar );
	lua_register( L, "RL_GuiScrollBar", lguiGuiScrollBar );
	lua_register( L, "RL_GuiDropdownBox", lguiGuiDropdownBox );
	lua_register( L, "RL_GuiStatusBar", lguiGuiStatusBar );
	lua_register( L, "RL_GuiDummyRec", lguiGuiDummyRec );
	lua_register( L, "RL_GuiGrid", lguiGuiGrid );
		/* Advanced. */
	lua_register( L, "RL_GuiListView", lguiGuiListView );
	lua_register( L, "RL_GuiListViewEx", lguiGuiListViewEx );
	lua_register( L, "RL_GuiMessageBox", lguiGuiMessageBox );
	lua_register( L, "RL_GuiTextInputBox", lguiGuiTextInputBox );
	lua_register( L, "RL_GuiColorPicker", lguiGuiColorPicker );
	lua_register( L, "RL_GuiColorPanel", lguiGuiColorPanel );
	lua_register( L, "RL_GuiColorBarAlpha", lguiGuiColorBarAlpha );
	lua_register( L, "RL_GuiColorBarHue", lguiGuiColorBarHue );
		/* Icons. */
	lua_register( L, "RL_GuiIconText", lguiGuiIconText );
	lua_register( L, "RL_GuiDrawIcon", lguiGuiDrawIcon );
	lua_register( L, "RL_GuiSetIconScale", lguiGuiSetIconScale );
	lua_register( L, "RL_GuiSetIconPixel", lguiGuiSetIconPixel );
	lua_register( L, "RL_GuiClearIconPixel", lguiGuiClearIconPixel );
	lua_register( L, "RL_GuiCheckIconPixel", lguiGuiCheckIconPixel );
	/* Lights */
		/* Basics. */
	lua_register( L, "RL_CreateLight", llightsCreateLight );
	lua_register( L, "RL_UpdateLightValues", llightsUpdateLightValues );
}

/* Lua util functions. */

Color uluaGetColor( lua_State *L ) {
    Color color = { 0, 0, 0, 255 };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong color value. Returning { 0, 0, 0, 255 }" );
        return color;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						color.r = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 1:
						color.g = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 2:
						color.b = (uint8_t)lua_tointeger( L, -1 );
						break;
					case 3:
						color.a = (uint8_t)lua_tointeger( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "r", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.r = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "g", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.g = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "b", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.b = (uint8_t)lua_tointeger( L, -1 );
				}
				else if ( strcmp( "a", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					color.a = (uint8_t)lua_tointeger( L, -1 );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }
    return color;
}

Vector2 uluaGetVector2( lua_State *L ) {
    Vector2 vector = { 0.0f, 0.0f };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector2 value. Returning { 0, 0 }" );
        return vector;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }
    return vector;
}

Vector3 uluaGetVector3( lua_State *L ) {
    Vector3 vector = { 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector3 value. Returning { 0, 0, 0 }" );
        return vector;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					case 2:
						vector.z = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.z = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return vector;
}

Vector4 uluaGetVector4( lua_State *L ) {
    Vector4 vector = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector4 value. Returning { 0, 0, 0, 0 }" );
        return vector;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						vector.x = lua_tonumber( L, -1 );
						break;
					case 1:
						vector.y = lua_tonumber( L, -1 );
						break;
					case 2:
						vector.z = lua_tonumber( L, -1 );
						break;
					case 3:
						vector.w = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.z = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "w", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					vector.w = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return vector;
}

Rectangle uluaGetRectangle( lua_State *L ) {
    Rectangle rect = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong rectangle value. Returning { 0, 0, 0, 0 }" );
        return rect;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						rect.x = lua_tonumber( L, -1 );
						break;
					case 1:
						rect.y = lua_tonumber( L, -1 );
						break;
					case 2:
						rect.width = lua_tonumber( L, -1 );
						break;
					case 3:
						rect.height = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "width", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.width = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "height", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					rect.height = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return rect;
}

Quaternion uluaGetQuaternion( lua_State *L ) {
    Quaternion quaternion = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong quaternion value. Returning { 0, 0, 0, 0 }" );
        return quaternion;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						quaternion.x = lua_tonumber( L, -1 );
						break;
					case 1:
						quaternion.y = lua_tonumber( L, -1 );
						break;
					case 2:
						quaternion.z = lua_tonumber( L, -1 );
						break;
					case 3:
						quaternion.w = lua_tonumber( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "x", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.x = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "y", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.y = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "z", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.z = lua_tonumber( L, -1 );
				}
				else if ( strcmp( "w", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					quaternion.w = lua_tonumber( L, -1 );
				}
			}
        }
        i++;
        lua_pop( L, 1 );
    }
    return quaternion;
}

Matrix uluaGetMatrix( lua_State *L ) {
	Matrix matrix = { 0.0f };
	float m[4][4];

    if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong matrix value. Returning MatrixIdentity." );
        return MatrixIdentity();
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        if ( lua_istable( L, -1 ) ) {
			int t2 = lua_gettop( L ), j = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				if ( lua_isnumber( L, -1 ) ) {
					m[i][j] = lua_tonumber( L, -1 );
				}
				j++;
				lua_pop( L, 1 );
			}
        }
        i++;
        lua_pop( L, 1 );
    }
	matrix.m0 = m[0][0]; 	matrix.m1 = m[0][1]; 	matrix.m2 = m[0][2]; 	matrix.m3 = m[0][3];
	matrix.m4 = m[1][0]; 	matrix.m5 = m[1][1]; 	matrix.m6 = m[1][2]; 	matrix.m7 = m[1][3];
	matrix.m8 = m[2][0]; 	matrix.m9 = m[2][1]; 	matrix.m10 = m[2][2]; 	matrix.m11 = m[2][3];
	matrix.m12 = m[3][0]; 	matrix.m13 = m[3][1]; 	matrix.m14 = m[3][2]; 	matrix.m15 = m[3][3];

	return matrix;
}

BoundingBox uluaGetBoundingBox( lua_State *L ) {
	BoundingBox box = { .min = { 0.0, 0.0, 0.0 }, .max = { 0.0, 0.0, 0.0 } };

	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong boundingbox value. Returning { min{ 0, 0, 0 }, max{ 0, 0, 0 } }." );
        return box;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						box.min = uluaGetVector3( L );
						break;
					case 1:
						box.max = uluaGetVector3( L );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "min", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					box.min = uluaGetVector3( L );
				}
				else if ( strcmp( "max", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					box.max = uluaGetVector3( L );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }

	return box;
}

Ray uluaGetRay( lua_State *L ) {
	Ray ray = { .position = { 0.0, 0.0, 0.0 }, .direction = { 0.0, 0.0, 0.0 } };

	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong ray value. Returning { position{ 0, 0, 0 }, direction{ 0, 0, 0 } }." );
        return ray;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						ray.position = uluaGetVector3( L );
						break;
					case 1:
						ray.direction = uluaGetVector3( L );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "position", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					ray.position = uluaGetVector3( L );
				}
				else if ( strcmp( "direction", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					ray.direction = uluaGetVector3( L );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }

	return ray;
}

NPatchInfo uluaGetNPatchInfo( lua_State *L ) {
	NPatchInfo npatch = { .source = { 0.0, 0.0, 0.0, 0.0 }, .left = 0, .top = 0, .right = 0, .bottom = 0, .layout = NPATCH_NINE_PATCH };

	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong ray value. Returning { source = { 0.0, 0.0, 0.0, 0.0 }, left = 0, top = 0, right = 0, bottom = 0, layout = NPATCH_NINE_PATCH }." );
        return npatch;
    }
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_isnumber( L, -1 ) ) {
			if ( lua_isnumber( L, -2 ) ) {
				switch ( i ) {
					case 0:
						npatch.source = uluaGetRectangle( L );
						break;
					case 1:
						npatch.left = lua_tointeger( L, -1 );
						break;
					case 2:
						npatch.top = lua_tointeger( L, -1 );
						break;
					case 3:
						npatch.right = lua_tointeger( L, -1 );
						break;
					case 4:
						npatch.bottom = lua_tointeger( L, -1 );
						break;
					case 5:
						npatch.layout = lua_tointeger( L, -1 );
						break;
					default:
						break;
				}
			}
			else if ( lua_isstring( L, -2 ) ) {
				if ( strcmp( "source", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.source = uluaGetRectangle( L );
				}
				else if ( strcmp( "left", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.left = lua_tointeger( L, -1 );
				}
				else if ( strcmp( "top", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.top = lua_tointeger( L, -1 );
				}
				else if ( strcmp( "right", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.right = lua_tointeger( L, -1 );
				}
				else if ( strcmp( "bottom", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.bottom = lua_tointeger( L, -1 );
				}
				else if ( strcmp( "layout", (char*)lua_tostring( L, -2 ) ) == 0 ) {
					npatch.layout = lua_tointeger( L, -1 );
				}
			}
			i++;
			lua_pop( L, 1 );
		}
    }
	return npatch;
}

void uluaPushColor( lua_State *L, Color color ) {
	lua_createtable( L, 3, 0 );
    lua_pushnumber( L, color.r );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, color.g );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, color.b );
    lua_rawseti( L, -2, 3 );
    lua_pushnumber( L, color.a );
    lua_rawseti( L, -2, 4 );
}

void uluaPushVector2( lua_State *L, Vector2 vector ) {
	lua_createtable( L, 2, 0 );
    lua_pushnumber( L, vector.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, vector.y );
    lua_rawseti( L, -2, 2 );
}

void uluaPushVector3( lua_State *L, Vector3 vector ) {
	lua_createtable( L, 3, 0 );
    lua_pushnumber( L, vector.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, vector.y );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, vector.z );
    lua_rawseti( L, -2, 3 );
}

void uluaPushVector4( lua_State *L, Vector4 vector ) {
	lua_createtable( L, 4, 0 );
    lua_pushnumber( L, vector.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, vector.y );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, vector.z );
    lua_rawseti( L, -2, 3 );
    lua_pushnumber( L, vector.w );
    lua_rawseti( L, -2, 4 );
}

void uluaPushRectangle( lua_State *L, Rectangle rect ) {
	lua_createtable( L, 4, 0 );
    lua_pushnumber( L, rect.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, rect.y );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, rect.width );
    lua_rawseti( L, -2, 3 );
    lua_pushnumber( L, rect.height );
    lua_rawseti( L, -2, 4 );
}

void uluaPushQuaternion( lua_State *L, Quaternion quaternion ) {
	lua_createtable( L, 4, 0 );
    lua_pushnumber( L, quaternion.x );
    lua_rawseti( L, -2, 1 );
    lua_pushnumber( L, quaternion.y );
    lua_rawseti( L, -2, 2 );
    lua_pushnumber( L, quaternion.z );
    lua_rawseti( L, -2, 3 );
    lua_pushnumber( L, quaternion.w );
    lua_rawseti( L, -2, 4 );
}

void uluaPushMatrix( lua_State *L, Matrix matrix ) {
	lua_createtable( L, 4, 0 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m0 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m1 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m2 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m3 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m4 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m5 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m6 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m7 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 2 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m8 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m9 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m10 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m11 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 3 );

	lua_createtable( L, 4, 0 );
	lua_pushnumber( L, matrix.m12 );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, matrix.m13 );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, matrix.m14 );
	lua_rawseti( L, -2, 3 );
	lua_pushnumber( L, matrix.m15 );
	lua_rawseti( L, -2, 4 );
	lua_rawseti( L, -2, 4 );
}

void uluaPushRay( lua_State *L, Ray ray ) {
	lua_createtable( L, 2, 0 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, ray.position.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, ray.position.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, ray.position.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, ray.direction.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, ray.direction.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, ray.direction.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 2 );
}

void uluaPushRayCollision( lua_State *L, RayCollision rayCol ) {
	lua_createtable( L, 4, 0 );
	lua_pushboolean( L, rayCol.hit );
	lua_setfield( L, -2, "hit" );
	lua_pushnumber( L, rayCol.distance );
	lua_setfield( L, -2, "distance" );
	uluaPushVector3( L, rayCol.point );
	lua_setfield( L, -2, "point" );
	uluaPushVector3( L, rayCol.normal );
	lua_setfield( L, -2, "normal" );
}

int uluaGetTableLen( lua_State *L ) {
	int t = lua_gettop( L ), i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        i++;
        lua_pop( L, 1 );
    }
    return i;
}
