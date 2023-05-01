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
#include "lrlgl.h"
#include "lgl.h"
#include "reasings.h"

static void assignGlobalInt( int value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushinteger( L, value );
	// lua_setglobal( L, name );
	lua_setfield( L, -2, name );
}

static void assignGlobalFloat( float value, const char *name ) {
	lua_State *L = state->luaState;
	lua_pushnumber( L, value );
	// lua_setglobal( L, name );
	lua_setfield( L, -2, name );
}

static void assignGlobalColor( Color color, const char *name ) {
	lua_State *L = state->luaState;
	uluaPushColor( L, color );
	// lua_setglobal( L, name );
	lua_setfield( L, -2, name );
}

static void assingGlobalFunction( const char *name, int ( *functionPtr )( lua_State* ) ) {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, functionPtr );
	lua_setfield( L, -2, name );
}

void defineGlobals() {
	lua_State *L = state->luaState;

	lua_newtable( state->luaState );
	lua_setglobal( L, "RL" );
	lua_getglobal( L, "RL" );

/*DOC_START*/
	/* ConfigFlags */
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
	/* TraceLogLevel */
	assignGlobalInt( LOG_ALL, "LOG_ALL" );
	assignGlobalInt( LOG_TRACE, "LOG_TRACE" );
	assignGlobalInt( LOG_DEBUG, "LOG_DEBUG" );
	assignGlobalInt( LOG_INFO, "LOG_INFO" );
	assignGlobalInt( LOG_WARNING, "LOG_WARNING" );
	assignGlobalInt( LOG_ERROR, "LOG_ERROR" );
	assignGlobalInt( LOG_FATAL, "LOG_FATAL" );
	assignGlobalInt( LOG_NONE, "LOG_NONE" );
	/* KeyboardKey */
	assignGlobalInt( GLFW_KEY_UNKNOWN, "KEY_UNKNOWN" );
	assignGlobalInt( KEY_NULL, "KEY_NULL" );
	assignGlobalInt( KEY_APOSTROPHE, "KEY_APOSTROPHE" );
	assignGlobalInt( KEY_COMMA, "KEY_COMMA" );
	assignGlobalInt( KEY_MINUS, "KEY_MINUS" );
	assignGlobalInt( KEY_PERIOD, "KEY_PERIOD" );
	assignGlobalInt( KEY_SLASH, "KEY_SLASH" );
	assignGlobalInt( KEY_ZERO, "KEY_ZERO" );
	assignGlobalInt( KEY_ONE, "KEY_ONE" );
	assignGlobalInt( KEY_TWO, "KEY_TWO" );
	assignGlobalInt( KEY_THREE, "KEY_THREE" );
	assignGlobalInt( KEY_FOUR, "KEY_FOUR" );
	assignGlobalInt( KEY_FIVE, "KEY_FIVE" );
	assignGlobalInt( KEY_SIX, "KEY_SIX" );
	assignGlobalInt( KEY_SEVEN, "KEY_SEVEN" );
	assignGlobalInt( KEY_EIGHT, "KEY_EIGHT" );
	assignGlobalInt( KEY_NINE, "KEY_NINE" );
	assignGlobalInt( KEY_SEMICOLON, "KEY_SEMICOLON" );
	assignGlobalInt( KEY_EQUAL, "KEY_EQUAL" );
	assignGlobalInt( KEY_A, "KEY_A" );
	assignGlobalInt( KEY_B, "KEY_B" );
	assignGlobalInt( KEY_C, "KEY_C" );
	assignGlobalInt( KEY_D, "KEY_D" );
	assignGlobalInt( KEY_E, "KEY_E" );
	assignGlobalInt( KEY_F, "KEY_F" );
	assignGlobalInt( KEY_G, "KEY_G" );
	assignGlobalInt( KEY_H, "KEY_H" );
	assignGlobalInt( KEY_I, "KEY_I" );
	assignGlobalInt( KEY_J, "KEY_J" );
	assignGlobalInt( KEY_K, "KEY_K" );
	assignGlobalInt( KEY_L, "KEY_L" );
	assignGlobalInt( KEY_M, "KEY_M" );
	assignGlobalInt( KEY_N, "KEY_N" );
	assignGlobalInt( KEY_O, "KEY_O" );
	assignGlobalInt( KEY_P, "KEY_P" );
	assignGlobalInt( KEY_Q, "KEY_Q" );
	assignGlobalInt( KEY_R, "KEY_R" );
	assignGlobalInt( KEY_S, "KEY_S" );
	assignGlobalInt( KEY_T, "KEY_T" );
	assignGlobalInt( KEY_U, "KEY_U" );
	assignGlobalInt( KEY_V, "KEY_V" );
	assignGlobalInt( KEY_W, "KEY_W" );
	assignGlobalInt( KEY_X, "KEY_X" );
	assignGlobalInt( KEY_Y, "KEY_Y" );
	assignGlobalInt( KEY_Z, "KEY_Z" );
	assignGlobalInt( KEY_LEFT_BRACKET, "KEY_LEFT_BRACKET" );
	assignGlobalInt( KEY_BACKSLASH, "KEY_BACKSLASH" );
	assignGlobalInt( KEY_RIGHT_BRACKET, "KEY_RIGHT_BRACKET" );
	assignGlobalInt( KEY_GRAVE, "KEY_GRAVE" );
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
	assignGlobalInt( KEY_PAGE_UP, "KEY_PAGE_UP" );
	assignGlobalInt( KEY_PAGE_DOWN, "KEY_PAGE_DOWN" );
	assignGlobalInt( KEY_HOME, "KEY_HOME" );
	assignGlobalInt( KEY_END, "KEY_END" );
	assignGlobalInt( KEY_CAPS_LOCK, "KEY_CAPS_LOCK" );
	assignGlobalInt( KEY_SCROLL_LOCK, "KEY_SCROLL_LOCK" );
	assignGlobalInt( KEY_NUM_LOCK, "KEY_NUM_LOCK" );
	assignGlobalInt( KEY_PRINT_SCREEN, "KEY_PRINT_SCREEN" );
	assignGlobalInt( KEY_PAUSE, "KEY_PAUSE" );
	assignGlobalInt( KEY_F1, "KEY_F1" );
	assignGlobalInt( KEY_F2, "KEY_F2" );
	assignGlobalInt( KEY_F3, "KEY_F3" );
	assignGlobalInt( KEY_F4, "KEY_F4" );
	assignGlobalInt( KEY_F5, "KEY_F5" );
	assignGlobalInt( KEY_F6, "KEY_F6" );
	assignGlobalInt( KEY_F7, "KEY_F7" );
	assignGlobalInt( KEY_F8, "KEY_F8" );
	assignGlobalInt( KEY_F9, "KEY_F9" );
	assignGlobalInt( KEY_F10, "KEY_F10" );
	assignGlobalInt( KEY_F11, "KEY_F11" );
	assignGlobalInt( KEY_F12, "KEY_F12" );
	assignGlobalInt( KEY_LEFT_SHIFT, "KEY_LEFT_SHIFT" );
	assignGlobalInt( KEY_LEFT_CONTROL, "KEY_LEFT_CONTROL" );
	assignGlobalInt( KEY_LEFT_ALT, "KEY_LEFT_ALT" );
	assignGlobalInt( KEY_LEFT_SUPER, "KEY_LEFT_SUPER" );
	assignGlobalInt( KEY_RIGHT_SHIFT, "KEY_RIGHT_SHIFT" );
	assignGlobalInt( KEY_RIGHT_CONTROL, "KEY_RIGHT_CONTROL" );
	assignGlobalInt( KEY_RIGHT_ALT, "KEY_RIGHT_ALT" );
	assignGlobalInt( KEY_RIGHT_SUPER, "KEY_RIGHT_SUPER" );
	assignGlobalInt( KEY_KB_MENU, "KEY_KB_MENU" );
	assignGlobalInt( KEY_KP_0, "KEY_KP_0" );
	assignGlobalInt( KEY_KP_1, "KEY_KP_1" );
	assignGlobalInt( KEY_KP_2, "KEY_KP_2" );
	assignGlobalInt( KEY_KP_3, "KEY_KP_3" );
	assignGlobalInt( KEY_KP_4, "KEY_KP_4" );
	assignGlobalInt( KEY_KP_5, "KEY_KP_5" );
	assignGlobalInt( KEY_KP_6, "KEY_KP_6" );
	assignGlobalInt( KEY_KP_7, "KEY_KP_7" );
	assignGlobalInt( KEY_KP_8, "KEY_KP_8" );
	assignGlobalInt( KEY_KP_9, "KEY_KP_9" );
	assignGlobalInt( KEY_KP_DECIMAL, "KEY_KP_DECIMAL" );
	assignGlobalInt( KEY_KP_DIVIDE, "KEY_KP_DIVIDE" );
	assignGlobalInt( KEY_KP_MULTIPLY, "KEY_KP_MULTIPLY" );
	assignGlobalInt( KEY_KP_SUBTRACT, "KEY_KP_SUBTRACT" );
	assignGlobalInt( KEY_KP_ADD, "KEY_KP_ADD" );
	assignGlobalInt( KEY_KP_ENTER, "KEY_KP_ENTER" );
	assignGlobalInt( KEY_KP_EQUAL, "KEY_KP_EQUAL" );
	assignGlobalInt( KEY_BACK, "KEY_BACK" );
	assignGlobalInt( KEY_MENU, "KEY_MENU" );
	assignGlobalInt( KEY_VOLUME_UP, "KEY_VOLUME_UP" );
	assignGlobalInt( KEY_VOLUME_DOWN, "KEY_VOLUME_DOWN" );
	/* MouseButtons */
	assignGlobalInt( MOUSE_BUTTON_LEFT, "MOUSE_BUTTON_LEFT" );
	assignGlobalInt( MOUSE_BUTTON_RIGHT, "MOUSE_BUTTON_RIGHT" );
	assignGlobalInt( MOUSE_BUTTON_MIDDLE, "MOUSE_BUTTON_MIDDLE" );
	assignGlobalInt( MOUSE_BUTTON_SIDE, "MOUSE_BUTTON_SIDE" );
	assignGlobalInt( MOUSE_BUTTON_EXTRA, "MOUSE_BUTTON_EXTRA" );
	assignGlobalInt( MOUSE_BUTTON_FORWARD, "MOUSE_BUTTON_FORWARD" );
	assignGlobalInt( MOUSE_BUTTON_BACK, "MOUSE_BUTTON_BACK" );
	/* MouseCursor */
	assignGlobalInt( MOUSE_CURSOR_DEFAULT, "MOUSE_CURSOR_DEFAULT" );
	assignGlobalInt( MOUSE_CURSOR_ARROW, "MOUSE_CURSOR_ARROW" );
	assignGlobalInt( MOUSE_CURSOR_IBEAM, "MOUSE_CURSOR_IBEAM" );
	assignGlobalInt( MOUSE_CURSOR_CROSSHAIR, "MOUSE_CURSOR_CROSSHAIR" );
	assignGlobalInt( MOUSE_CURSOR_POINTING_HAND, "MOUSE_CURSOR_POINTING_HAND" );
	assignGlobalInt( MOUSE_CURSOR_RESIZE_EW, "MOUSE_CURSOR_RESIZE_EW" );
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NS, "MOUSE_CURSOR_RESIZE_NS" );
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NWSE, "MOUSE_CURSOR_RESIZE_NWSE" );
	assignGlobalInt( MOUSE_CURSOR_RESIZE_NESW, "MOUSE_CURSOR_RESIZE_NESW" );
	assignGlobalInt( MOUSE_CURSOR_RESIZE_ALL, "MOUSE_CURSOR_RESIZE_ALL" );
	assignGlobalInt( MOUSE_CURSOR_NOT_ALLOWED, "MOUSE_CURSOR_NOT_ALLOWED" );
	/* GamepadButtons */
	assignGlobalInt( GAMEPAD_BUTTON_UNKNOWN, "GAMEPAD_BUTTON_UNKNOWN" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_UP, "GAMEPAD_BUTTON_LEFT_FACE_UP" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_RIGHT, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_DOWN, "GAMEPAD_BUTTON_LEFT_FACE_DOWN" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_FACE_LEFT, "GAMEPAD_BUTTON_LEFT_FACE_LEFT" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_UP, "GAMEPAD_BUTTON_RIGHT_FACE_UP" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_DOWN, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_FACE_LEFT, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_TRIGGER_1, "GAMEPAD_BUTTON_LEFT_TRIGGER_1" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_TRIGGER_2, "GAMEPAD_BUTTON_LEFT_TRIGGER_2" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_TRIGGER_1, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_TRIGGER_2, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2" );
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE_LEFT, "GAMEPAD_BUTTON_MIDDLE_LEFT" );
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE, "GAMEPAD_BUTTON_MIDDLE" );
	assignGlobalInt( GAMEPAD_BUTTON_MIDDLE_RIGHT, "GAMEPAD_BUTTON_MIDDLE_RIGHT" );
	assignGlobalInt( GAMEPAD_BUTTON_LEFT_THUMB, "GAMEPAD_BUTTON_LEFT_THUMB" );
	assignGlobalInt( GAMEPAD_BUTTON_RIGHT_THUMB, "GAMEPAD_BUTTON_RIGHT_THUMB" );
	/* GamepadAxis */
	assignGlobalInt( GAMEPAD_AXIS_LEFT_X, "GAMEPAD_AXIS_LEFT_X" );
	assignGlobalInt( GAMEPAD_AXIS_LEFT_Y, "GAMEPAD_AXIS_LEFT_Y" );
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_X, "GAMEPAD_AXIS_RIGHT_X" );
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_Y, "GAMEPAD_AXIS_RIGHT_Y" );
	assignGlobalInt( GAMEPAD_AXIS_LEFT_TRIGGER, "GAMEPAD_AXIS_LEFT_TRIGGER" );
	assignGlobalInt( GAMEPAD_AXIS_RIGHT_TRIGGER, "GAMEPAD_AXIS_RIGHT_TRIGGER" );
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
	assignGlobalInt( MATERIAL_MAP_DIFFUSE, "MATERIAL_MAP_DIFFUSE" );
	assignGlobalInt( MATERIAL_MAP_SPECULAR, "MATERIAL_MAP_SPECULAR" );
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
	assignGlobalInt( SHADER_LOC_MAP_DIFFUSE, "SHADER_LOC_MAP_DIFFUSE" );
	assignGlobalInt( SHADER_LOC_MAP_SPECULAR, "SHADER_LOC_MAP_SPECULAR" );
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
	/* TextureFilters */
	assignGlobalInt( TEXTURE_FILTER_POINT, "TEXTURE_FILTER_POINT" );
	assignGlobalInt( TEXTURE_FILTER_BILINEAR, "TEXTURE_FILTER_BILINEAR" );
	assignGlobalInt( TEXTURE_FILTER_TRILINEAR, "TEXTURE_FILTER_TRILINEAR" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_4X, "TEXTURE_FILTER_ANISOTROPIC_4X" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_8X, "TEXTURE_FILTER_ANISOTROPIC_8X" );
	assignGlobalInt( TEXTURE_FILTER_ANISOTROPIC_16X, "TEXTURE_FILTER_ANISOTROPIC_16X" );
	/* TextureWrap */
	assignGlobalInt( TEXTURE_WRAP_REPEAT, "TEXTURE_WRAP_REPEAT" );
	assignGlobalInt( TEXTURE_WRAP_CLAMP, "TEXTURE_WRAP_CLAMP" );
	assignGlobalInt( TEXTURE_WRAP_MIRROR_REPEAT, "TEXTURE_WRAP_MIRROR_REPEAT" );
	assignGlobalInt( TEXTURE_WRAP_MIRROR_CLAMP, "TEXTURE_WRAP_MIRROR_CLAMP" );
	/* CubemapLayout */
	assignGlobalInt( CUBEMAP_LAYOUT_AUTO_DETECT, "CUBEMAP_LAYOUT_AUTO_DETECT" );
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_VERTICAL, "CUBEMAP_LAYOUT_LINE_VERTICAL" );
	assignGlobalInt( CUBEMAP_LAYOUT_LINE_HORIZONTAL, "CUBEMAP_LAYOUT_LINE_HORIZONTAL" );
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR" );
	assignGlobalInt( CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE" );
	assignGlobalInt( CUBEMAP_LAYOUT_PANORAMA, "CUBEMAP_LAYOUT_PANORAMA" );
	/* FontType */
	assignGlobalInt( FONT_DEFAULT, "FONT_DEFAULT" );
	assignGlobalInt( FONT_BITMAP, "FONT_BITMAP" );
	assignGlobalInt( FONT_SDF, "FONT_SDF" );
	/* BlendModes */
	assignGlobalInt( BLEND_ALPHA, "BLEND_ALPHA" );
	assignGlobalInt( BLEND_ADDITIVE, "BLEND_ADDITIVE" );
	assignGlobalInt( BLEND_MULTIPLIED, "BLEND_MULTIPLIED" );
	assignGlobalInt( BLEND_ADD_COLORS, "BLEND_ADD_COLORS" );
	assignGlobalInt( BLEND_SUBTRACT_COLORS, "BLEND_SUBTRACT_COLORS" );
	assignGlobalInt( BLEND_ALPHA_PREMULTIPLY, "BLEND_ALPHA_PREMULTIPLY" );
	assignGlobalInt( BLEND_CUSTOM, "BLEND_CUSTOM" );
	assignGlobalInt( BLEND_CUSTOM_SEPARATE, "BLEND_CUSTOM_SEPARATE" );
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
	/* CameraMode */
	assignGlobalInt( CAMERA_CUSTOM, "CAMERA_CUSTOM" );
	assignGlobalInt( CAMERA_FREE, "CAMERA_FREE" );
	assignGlobalInt( CAMERA_ORBITAL, "CAMERA_ORBITAL" );
	assignGlobalInt( CAMERA_FIRST_PERSON, "CAMERA_FIRST_PERSON" );
	assignGlobalInt( CAMERA_THIRD_PERSON, "CAMERA_THIRD_PERSON" );
	/* CameraProjections */
	assignGlobalInt( CAMERA_PERSPECTIVE, "CAMERA_PERSPECTIVE" );
	assignGlobalInt( CAMERA_ORTHOGRAPHIC, "CAMERA_ORTHOGRAPHIC" );
	/* N-patchLayout */
	assignGlobalInt( NPATCH_NINE_PATCH, "NPATCH_NINE_PATCH" );
	assignGlobalInt( NPATCH_THREE_PATCH_VERTICAL, "NPATCH_THREE_PATCH_VERTICAL" );
	assignGlobalInt( NPATCH_THREE_PATCH_HORIZONTAL, "NPATCH_THREE_PATCH_HORIZONTAL" );
	/* TextureModes */
	assignGlobalInt( TEXTURE_TYPE_TEXTURE, "TEXTURE_TYPE_TEXTURE" );
	assignGlobalInt( TEXTURE_TYPE_RENDER_TEXTURE, "TEXTURE_TYPE_RENDER_TEXTURE" );
	/* Colors */
	assignGlobalColor( LIGHTGRAY, "LIGHTGRAY" );
	assignGlobalColor( GRAY, "GRAY" );
	assignGlobalColor( DARKGRAY, "DARKGRAY" );
	assignGlobalColor( YELLOW, "YELLOW" );
	assignGlobalColor( GOLD, "GOLD" );
	assignGlobalColor( ORANGE, "ORANGE" );
	assignGlobalColor( PINK, "PINK" );
	assignGlobalColor( RED, "RED" );
	assignGlobalColor( MAROON, "MAROON" );
	assignGlobalColor( GREEN, "GREEN" );
	assignGlobalColor( LIME, "LIME" );
	assignGlobalColor( DARKGREEN, "DARKGREEN" );
	assignGlobalColor( SKYBLUE, "SKYBLUE" );
	assignGlobalColor( BLUE, "BLUE" );
	assignGlobalColor( DARKBLUE, "DARKBLUE" );
	assignGlobalColor( PURPLE, "PURPLE" );
	assignGlobalColor( VIOLET, "VIOLET" );
	assignGlobalColor( DARKPURPLE, "DARKPURPLE" );
	assignGlobalColor( BEIGE, "BEIGE" );
	assignGlobalColor( BROWN, "BROWN" );
	assignGlobalColor( DARKBROWN, "DARKBROWN" );
	assignGlobalColor( WHITE, "WHITE" );
	assignGlobalColor( BLACK, "BLACK" );
	assignGlobalColor( BLANK, "BLANK" );
	assignGlobalColor( MAGENTA, "MAGENTA" );
	assignGlobalColor( RAYWHITE, "RAYWHITE" );
	/* Math */
	assignGlobalFloat( PI, "PI" );
	assignGlobalFloat( DEG2RAD, "DEG2RAD" );
	assignGlobalFloat( RAD2DEG, "RAD2DEG" );
	/* GuiControlState */
	assignGlobalInt( STATE_NORMAL, "STATE_NORMAL" );
	assignGlobalInt( STATE_FOCUSED, "STATE_FOCUSED" );
	assignGlobalInt( STATE_PRESSED, "STATE_PRESSED" );
	assignGlobalInt( STATE_DISABLED, "STATE_DISABLED" );
	/* GuiTextAlignment */
	assignGlobalInt( TEXT_ALIGN_LEFT, "TEXT_ALIGN_LEFT" );
	assignGlobalInt( TEXT_ALIGN_CENTER, "TEXT_ALIGN_CENTER" );
	assignGlobalInt( TEXT_ALIGN_RIGHT, "TEXT_ALIGN_RIGHT" );
	/* GuiControl */
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
	/* GuiScrollBarProperty */
	assignGlobalInt( ARROWS_SIZE, "ARROWS_SIZE" );
	assignGlobalInt( ARROWS_VISIBLE, "ARROWS_VISIBLE" );
	assignGlobalInt( SCROLL_SLIDER_PADDING, "SCROLL_SLIDER_PADDING" );
	assignGlobalInt( SCROLL_SLIDER_SIZE, "SCROLL_SLIDER_SIZE" );
	assignGlobalInt( SCROLL_PADDING, "SCROLL_PADDING" );
	assignGlobalInt( SCROLL_SPEED, "SCROLL_SPEED" );
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
	/* OpenGL */
	assignGlobalInt( GL_COLOR_BUFFER_BIT, "GL_COLOR_BUFFER_BIT" );
	assignGlobalInt( GL_DEPTH_BUFFER_BIT, "GL_DEPTH_BUFFER_BIT" );
	assignGlobalInt( GL_STENCIL_BUFFER_BIT, "GL_STENCIL_BUFFER_BIT" );
	assignGlobalInt( GL_NEAREST, "GL_NEAREST" );
	assignGlobalInt( GL_LINEAR, "GL_LINEAR" );
/*DOC_END*/

	lua_pop( L, -1 );
}

// Custom logging funtion
void LogCustom( int logLevel, const char *text, va_list args ) {
	char string[ STRING_LEN ] = {'\0'};
	char msg[ STRING_LEN ] = {'\0'};

	vsprintf( string, text, args );

    switch ( logLevel ) {
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
        lua_pushinteger( L, logLevel );
        lua_pushstring( L, msg );

        if ( lua_pcall( L, 2, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
			lua_pop( L, -1 );
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
	defineGlobals();

	return true;
}

int luaTraceback( lua_State *L ) {
	lua_getglobal( L, "debug" );

	if ( !lua_istable( L, -1 ) ) {
		lua_pop( L, 1 );
		return 1;
	}

	lua_getfield( L, -1, "traceback" );

	if ( !lua_isfunction( L, -1 ) ) {
		lua_pop( L, 2 );
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
		TraceLog( LOG_ERROR, "Lua error: %s\n", lua_tostring( state->luaState, -1 ) );
	}

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop( L );

	// lua_getglobal( L, "init" );
	lua_getglobal( L, "RL" );
	lua_getfield ( L, -1, "init" );

	if ( lua_isfunction( L, -1 ) ) {
		if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			return false;
		}
	}
	//TODO Should this be removed?
	else {
		TraceLog( LOG_ERROR, "%s", "No Lua init found!" );
        return false;
    }
	lua_pop( L, -1 );
	/* Apply custom callback here. */
	SetTraceLogCallback( LogCustom );

	return true;
}

void luaCallProcess() {
    lua_State *L = state->luaState;

	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
    // lua_getglobal( L, "process" );
	lua_getglobal( L, "RL" );
	lua_getfield ( L, -1, "process" );

    if ( lua_isfunction( L, -1 ) ) {
        lua_pushnumber( L, GetFrameTime() );

        if ( lua_pcall( L, 1, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
			lua_pop( L, -1 );
 	    	return;
        }
    }
	lua_pop( L, -1 );
}

void luaCallDraw() {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
    // lua_getglobal( L, "draw" );
	lua_getglobal( L, "RL" );
	lua_getfield ( L, -1, "draw" );

    if ( lua_isfunction( L, -1 ) ) {
		BeginDrawing();

        if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }

		EndDrawing();
    }
	lua_pop( L, -1 );
}

void luaCallExit() {
	lua_State *L = state->luaState;
	lua_pushcfunction( L, luaTraceback );
	int tracebackidx = lua_gettop(L);
	
    // lua_getglobal( L, "exit" );
	lua_getglobal( L, "RL" );
	lua_getfield ( L, -1, "exit" );

    if ( lua_isfunction( L, -1 ) ) {
        if ( lua_pcall( L, 0, 0, tracebackidx ) != 0 ) {
			TraceLog( LOG_ERROR, "Lua error: %s", lua_tostring( L, -1 ) );
			state->run = false;
 	    	return;
        }
    }
	lua_pop( L, -1 );
}

void luaRegister() {
	lua_State *L = state->luaState;
	lua_getglobal( L, "RL" );

	/* Core. */
		/* Window. */

	assingGlobalFunction( "IsWindowReady", lcoreIsWindowReady );
	assingGlobalFunction( "IsWindowFullscreen", lcoreIsWindowFullscreen );
	assingGlobalFunction( "IsWindowHidden", lcoreIsWindowHidden );
	assingGlobalFunction( "IsWindowMinimized", lcoreIsWindowMinimized );
	assingGlobalFunction( "IsWindowMaximized", lcoreIsWindowMaximized );
	assingGlobalFunction( "IsWindowFocused", lcoreIsWindowFocused );
	assingGlobalFunction( "SetWindowMonitor", lcoreSetWindowMonitor );
	assingGlobalFunction( "SetWindowPosition", lcoreSetWindowPosition );
	assingGlobalFunction( "SetWindowSize", lcoreSetWindowSize );
	assingGlobalFunction( "SetWindowMinSize", lcoreSetWindowMinSize );
	assingGlobalFunction( "GetMonitorPosition", lcoreGetMonitorPosition );
	assingGlobalFunction( "GetMonitorSize", lcoreGetMonitorSize );
	assingGlobalFunction( "GetWindowPosition", lcoreGetWindowPosition );
	assingGlobalFunction( "GetScreenSize", lcoreGetScreenSize );
	assingGlobalFunction( "SetWindowState", lcoreSetWindowState );
	assingGlobalFunction( "IsWindowState", lcoreIsWindowState );
	assingGlobalFunction( "ClearWindowState", lcoreClearWindowState );
	assingGlobalFunction( "IsWindowResized", lcoreIsWindowResized );
	assingGlobalFunction( "SetWindowIcon", lcoreSetWindowIcon );
	assingGlobalFunction( "SetWindowTitle", lcoreSetWindowTitle );
	assingGlobalFunction( "GetMonitorCount", lcoreGetMonitorCount );
	assingGlobalFunction( "GetCurrentMonitor", lcoreGetCurrentMonitor );
	assingGlobalFunction( "GetMonitorPhysicalSize", lcoreGetMonitorPhysicalSize );
	assingGlobalFunction( "GetMonitorRefreshRate", lcoreGetMonitorRefreshRate );
	assingGlobalFunction( "GetWindowScaleDPI", lcoreGetWindowScaleDPI );
	assingGlobalFunction( "GetMonitorName", lcoreGetMonitorName );
	assingGlobalFunction( "CloseWindow", lcoreCloseWindow );
	assingGlobalFunction( "SetClipboardText", lcoreSetClipboardText );
	assingGlobalFunction( "GetClipboardText", lcoreGetClipboardText );
		/* Timing. */
	assingGlobalFunction( "SetTargetFPS", lcoreSetTargetFPS );
	assingGlobalFunction( "GetFPS", lcoreGetFPS );
	assingGlobalFunction( "GetFrameTime", lcoreGetFrameTime );
	assingGlobalFunction( "GetTime", lcoreGetTime );
		/* Misc. */
	assingGlobalFunction( "TakeScreenshot", lcoreTakeScreenshot );
	assingGlobalFunction( "SetConfigFlags", lcoreSetConfigFlags );
	assingGlobalFunction( "TraceLog", lcoreTraceLog );
	assingGlobalFunction( "SetTraceLogLevel", lcoreSetTraceLogLevel );
	assingGlobalFunction( "OpenURL", lcoreOpenURL );
		/* Cursor. */
	assingGlobalFunction( "ShowCursor", lcoreShowCursor );
	assingGlobalFunction( "HideCursor", lcoreHideCursor );
	assingGlobalFunction( "IsCursorHidden", lcoreIsCursorHidden );
	assingGlobalFunction( "EnableCursor", lcoreEnableCursor );
	assingGlobalFunction( "DisableCursor", lcoreDisableCursor );
	assingGlobalFunction( "IsCursorOnScreen", lcoreIsCursorOnScreen );
		/* Drawing. */
	assingGlobalFunction( "ClearBackground", lcoreClearBackground );
	assingGlobalFunction( "BeginDrawing", lcoreBeginDrawing );
	assingGlobalFunction( "EndDrawing", lcoreEndDrawing );
	assingGlobalFunction( "BeginBlendMode", lcoreBeginBlendMode );
	assingGlobalFunction( "EndBlendMode", lcoreEndBlendMode );
	assingGlobalFunction( "BeginScissorMode", lcoreBeginScissorMode );
	assingGlobalFunction( "EndScissorMode", lcoreEndScissorMode );
		/* Shader. */
	assingGlobalFunction( "LoadShader", lcoreLoadShader );
	assingGlobalFunction( "LoadShaderFromMemory", lcoreLoadShaderFromMemory );
	assingGlobalFunction( "BeginShaderMode", lcoreBeginShaderMode );
	assingGlobalFunction( "EndShaderMode", lcoreEndShaderMode );
	assingGlobalFunction( "GetShaderLocation", lcoreGetShaderLocation );
	assingGlobalFunction( "GetShaderLocationAttrib", lcoreGetShaderLocationAttrib );
	assingGlobalFunction( "SetShaderLocationIndex", lcoreSetShaderLocationIndex );
	assingGlobalFunction( "GetShaderLocationIndex", lcoreGetShaderLocationIndex );
	assingGlobalFunction( "SetShaderValueMatrix", lcoreSetShaderValueMatrix );
	assingGlobalFunction( "SetShaderValueTexture", lcoreSetShaderValueTexture );
	assingGlobalFunction( "SetShaderValue", lcoreSetShaderValue );
	assingGlobalFunction( "SetShaderValueV", lcoreSetShaderValueV );
	assingGlobalFunction( "UnloadShader", lcoreUnloadShader );
		/* File. */
	assingGlobalFunction( "GetBasePath", lcoreGetBasePath );
	assingGlobalFunction( "FileExists", lcoreFileExists );
	assingGlobalFunction( "DirectoryExists", lcoreDirectoryExists );
	assingGlobalFunction( "IsFileExtension", lcoreIsFileExtension );
	assingGlobalFunction( "GetFileLength", lcoreGetFileLength );
	assingGlobalFunction( "GetFileExtension", lcoreGetFileExtension );
	assingGlobalFunction( "GetFileName", lcoreGetFileName );
	assingGlobalFunction( "GetFileNameWithoutExt", lcoreGetFileNameWithoutExt );
	assingGlobalFunction( "GetDirectoryPath", lcoreGetDirectoryPath );
	assingGlobalFunction( "GetPrevDirectoryPath", lcoreGetPrevDirectoryPath );
	assingGlobalFunction( "GetWorkingDirectory", lcoreGetWorkingDirectory );
	assingGlobalFunction( "LoadDirectoryFiles", lcoreLoadDirectoryFiles );
	assingGlobalFunction( "LoadDirectoryFilesEx", lcoreLoadDirectoryFilesEx );
	assingGlobalFunction( "ChangeDirectory", lcoreChangeDirectory );
	assingGlobalFunction( "IsPathFile", lcoreIsPathFile );
	assingGlobalFunction( "IsFileDropped", lcoreIsFileDropped );
	assingGlobalFunction( "LoadDroppedFiles", lcoreLoadDroppedFiles );
	assingGlobalFunction( "GetFileModTime", lcoreGetFileModTime );
		/* Camera2D. */
	assingGlobalFunction( "CreateCamera2D", lcoreCreateCamera2D );
	assingGlobalFunction( "UnloadCamera2D", lcoreUnloadCamera2D );
	assingGlobalFunction( "BeginMode2D", lcoreBeginMode2D );
	assingGlobalFunction( "EndMode2D", lcoreEndMode2D );
	assingGlobalFunction( "SetCamera2DTarget", lcoreSetCamera2DTarget );
	assingGlobalFunction( "SetCamera2DOffset", lcoreSetCamera2DOffset );
	assingGlobalFunction( "SetCamera2DRotation", lcoreSetCamera2DRotation );
	assingGlobalFunction( "SetCamera2DZoom", lcoreSetCamera2DZoom );
	assingGlobalFunction( "GetCamera2DTarget", lcoreGetCamera2DTarget );
	assingGlobalFunction( "GetCamera2DOffset", lcoreGetCamera2DOffset );
	assingGlobalFunction( "GetCamera2DRotation", lcoreGetCamera2DRotation );
	assingGlobalFunction( "GetCamera2DZoom", lcoreGetCamera2DZoom );
		/* Camera3D. */
	assingGlobalFunction( "CreateCamera3D", lcoreCreateCamera3D );
	assingGlobalFunction( "UnloadCamera3D", lcoreUnloadCamera3D );
	assingGlobalFunction( "BeginMode3D", lcoreBeginMode3D );
	assingGlobalFunction( "EndMode3D", lcoreEndMode3D );
	assingGlobalFunction( "SetCamera3DPosition", lcoreSetCamera3DPosition );
	assingGlobalFunction( "SetCamera3DTarget", lcoreSetCamera3DTarget );
	assingGlobalFunction( "SetCamera3DUp", lcoreSetCamera3DUp );
	assingGlobalFunction( "SetCamera3DFovy", lcoreSetCamera3DFovy );
	assingGlobalFunction( "SetCamera3DProjection", lcoreSetCamera3DProjection );
	assingGlobalFunction( "GetCamera3DPosition", lcoreGetCamera3DPosition );
	assingGlobalFunction( "GetCamera3DTarget", lcoreGetCamera3DTarget );
	assingGlobalFunction( "GetCamera3DUp", lcoreGetCamera3DUp );
	assingGlobalFunction( "GetCamera3DFovy", lcoreGetCamera3DFovy );
	assingGlobalFunction( "GetCamera3DProjection", lcoreGetCamera3DProjection );
	assingGlobalFunction( "GetCamera3DForward", lcoreGetCamera3DForward );
	assingGlobalFunction( "GetCamera3DUpNormalized", lcoreGetCamera3DUpNormalized );
	assingGlobalFunction( "GetCamera3DRight", lcoreGetCamera3DRight );
	assingGlobalFunction( "Camera3DMoveForward", lcoreCamera3DMoveForward );
	assingGlobalFunction( "Camera3DMoveUp", lcoreCamera3DMoveUp );
	assingGlobalFunction( "Camera3DMoveRight", lcoreCamera3DMoveRight );
	assingGlobalFunction( "Camera3DMoveToTarget", lcoreCamera3DMoveToTarget );
	assingGlobalFunction( "Camera3DYaw", lcoreCamera3DYaw );
	assingGlobalFunction( "Camera3DPitch", lcoreCamera3DPitch );
	assingGlobalFunction( "Camera3DRoll", lcoreCamera3DRoll );
	assingGlobalFunction( "GetCamera3DViewMatrix", lcoreGetCamera3DViewMatrix );
	assingGlobalFunction( "GetCamera3DProjectionMatrix", lcoreGetCamera3DProjectionMatrix );
	assingGlobalFunction( "UpdateCamera3D", lcoreUpdateCamera3D );
	assingGlobalFunction( "UpdateCamera3DPro", lcoreUpdateCamera3DPro );
		/* Input-related Keyboard. */
	assingGlobalFunction( "IsKeyPressed", lcoreIsKeyPressed );
	assingGlobalFunction( "IsKeyDown", lcoreIsKeyDown );
	assingGlobalFunction( "IsKeyReleased", lcoreIsKeyReleased );
	assingGlobalFunction( "IsKeyUp", lcoreIsKeyUp );
	assingGlobalFunction( "GetKeyPressed", lcoreGetKeyPressed );
	assingGlobalFunction( "GetCharPressed", lcoreGetCharPressed );
	assingGlobalFunction( "SetExitKey", lcoreSetExitKey );
	assingGlobalFunction( "GetKeyName", lcoreGetKeyName );
	assingGlobalFunction( "GetKeyScancode", lcoreGetKeyScancode );
		/* Input-related Gamepad. */
	assingGlobalFunction( "IsGamepadAvailable", lcoreIsGamepadAvailable );
	assingGlobalFunction( "IsGamepadButtonPressed", lcoreIsGamepadButtonPressed );
	assingGlobalFunction( "IsGamepadButtonDown", lcoreIsGamepadButtonDown );
	assingGlobalFunction( "IsGamepadButtonReleased", lcoreIsGamepadButtonReleased );
	assingGlobalFunction( "GetGamepadAxisCount", lcoreGetGamepadAxisCount );
	assingGlobalFunction( "GetGamepadAxisMovement", lcoreGetGamepadAxisMovement );
	assingGlobalFunction( "GetGamepadName", lcoreGetGamepadName );
		/* Input-related Mouse. */
	assingGlobalFunction( "IsMouseButtonPressed", lcoreIsMouseButtonPressed );
	assingGlobalFunction( "IsMouseButtonDown", lcoreIsMouseButtonDown );
	assingGlobalFunction( "IsMouseButtonReleased", lcoreIsMouseButtonReleased );
	assingGlobalFunction( "IsMouseButtonUp", lcoreIsMouseButtonUp );
	assingGlobalFunction( "GetMousePosition", lcoreGetMousePosition );
	assingGlobalFunction( "GetMouseDelta", lcoreGetMouseDelta );
	assingGlobalFunction( "SetMousePosition", lcoreSetMousePosition );
	assingGlobalFunction( "SetMouseOffset", lcoreSetMouseOffset );
	assingGlobalFunction( "SetMouseScale", lcoreSetMouseScale );
	assingGlobalFunction( "GetMouseWheelMove", lcoreGetMouseWheelMove );
	assingGlobalFunction( "SetMouseCursor", lcoreSetMouseCursor );
		/* Input-related Touch */
	assingGlobalFunction( "GetTouchPosition", lcoreGetTouchPosition );
	assingGlobalFunction( "GetTouchPointId", lcoreGetTouchPointId );
	assingGlobalFunction( "GetTouchPointCount", lcoreGetTouchPointCount );
		/* Input-related Gestures. */
	assingGlobalFunction( "SetGesturesEnabled", lcoreSetGesturesEnabled );
	assingGlobalFunction( "IsGestureDetected", lcoreIsGestureDetected );
	assingGlobalFunction( "GetGestureDetected", lcoreGetGestureDetected );
	assingGlobalFunction( "GetGestureHoldDuration", lcoreGetGestureHoldDuration );
	assingGlobalFunction( "GetGestureDragVector", lcoreGetGestureDragVector );
	assingGlobalFunction( "GetGestureDragAngle", lcoreGetGestureDragAngle );
	assingGlobalFunction( "GetGesturePinchVector", lcoreGetGesturePinchVector );
	assingGlobalFunction( "GetGesturePinchAngle", lcoreGetGesturePinchAngle );
		/* Screen-space. */
	assingGlobalFunction( "GetMouseRay", lcoreGetMouseRay );
	assingGlobalFunction( "GetCameraMatrix", lcoreGetCameraMatrix );
	assingGlobalFunction( "GetCameraMatrix2D", lcoreGetCameraMatrix2D );
	assingGlobalFunction( "GetWorldToScreen", lcoreGetWorldToScreen );
	assingGlobalFunction( "GetWorldToScreenEx", lcoreGetWorldToScreenEx );
	assingGlobalFunction( "GetWorldToScreen2D", lcoreGetWorldToScreen2D );
	assingGlobalFunction( "GetScreenToWorld2D", lcoreGetScreenToWorld2D );

	/* Shapes. */
		/* Drawing. */
	assingGlobalFunction( "SetShapesTexture", lshapesSetShapesTexture );
	assingGlobalFunction( "DrawPixel", lshapesDrawPixel );
	assingGlobalFunction( "DrawLine", lshapesDrawLine );
	assingGlobalFunction( "DrawLineBezier", lshapesDrawLineBezier );
	assingGlobalFunction( "DrawLineBezierQuad", lshapesDrawLineBezierQuad );
	assingGlobalFunction( "DrawLineBezierCubic", lshapesDrawLineBezierCubic );
	assingGlobalFunction( "DrawLineStrip", lshapesDrawLineStrip );
	assingGlobalFunction( "DrawCircle", lshapesDrawCircle );
	assingGlobalFunction( "DrawCircleSector", lshapesDrawCircleSector );
	assingGlobalFunction( "DrawCircleSectorLines", lshapesDrawCircleSectorLines );
	assingGlobalFunction( "DrawCircleGradient", lshapesDrawCircleGradient );
	assingGlobalFunction( "DrawCircleLines", lshapesDrawCircleLines );
	assingGlobalFunction( "DrawEllipse", lshapesDrawEllipse );
	assingGlobalFunction( "DrawEllipseLines", lshapesDrawEllipseLines );
	assingGlobalFunction( "DrawRing", lshapesDrawRing );
	assingGlobalFunction( "DrawRingLines", lshapesDrawRingLines );
	assingGlobalFunction( "DrawRectangle", lshapesDrawRectangle );
	assingGlobalFunction( "DrawRectanglePro", lshapesDrawRectanglePro );
	assingGlobalFunction( "DrawRectangleGradientV", lshapesDrawRectangleGradientV );
	assingGlobalFunction( "DrawRectangleGradientH", lshapesDrawRectangleGradientH );
	assingGlobalFunction( "DrawRectangleGradientEx", lshapesDrawRectangleGradientEx );
	assingGlobalFunction( "DrawRectangleLines", lshapesDrawRectangleLines );
	assingGlobalFunction( "DrawRectangleLinesEx", lshapesDrawRectangleLinesEx );
	assingGlobalFunction( "DrawRectangleRounded", lshapesDrawRectangleRounded );
	assingGlobalFunction( "DrawRectangleRoundedLines", lshapesDrawRectangleRoundedLines );
	assingGlobalFunction( "DrawTriangle", lshapesDrawTriangle );
	assingGlobalFunction( "DrawTriangleLines", lshapesDrawTriangleLines );
	assingGlobalFunction( "DrawTriangleFan", lshapesDrawTriangleFan );
	assingGlobalFunction( "DrawTriangleStrip", lshapesDrawTriangleStrip );
	assingGlobalFunction( "DrawPoly", lshapesDrawPoly );
	assingGlobalFunction( "DrawPolyLines", lshapesDrawPolyLines );
	assingGlobalFunction( "DrawPolyLinesEx", lshapesDrawPolyLinesEx );
		/* Collision. */
	assingGlobalFunction( "CheckCollisionRecs", lshapesCheckCollisionRecs );
	assingGlobalFunction( "CheckCollisionCircles", lshapesCheckCollisionCircles );
	assingGlobalFunction( "CheckCollisionCircleRec", lshapesCheckCollisionCircleRec );
	assingGlobalFunction( "CheckCollisionPointRec", lshapesCheckCollisionPointRec );
	assingGlobalFunction( "CheckCollisionPointCircle", lshapesCheckCollisionPointCircle );
	assingGlobalFunction( "CheckCollisionPointTriangle", lshapesCheckCollisionPointTriangle );
	assingGlobalFunction( "CheckCollisionPointPoly", lshapesCheckCollisionPointPoly );
	assingGlobalFunction( "CheckCollisionLines", lshapesCheckCollisionLines );
	assingGlobalFunction( "CheckCollisionPointLine", lshapesCheckCollisionPointLine );
	assingGlobalFunction( "GetCollisionRec", lshapesGetCollisionRec );

	/* Textures. */
		/* Image Loading. */
	assingGlobalFunction( "LoadImage", ltexturesLoadImage );
	assingGlobalFunction( "LoadImageFromTexture", ltexturesLoadImageFromTexture );
	assingGlobalFunction( "LoadImageFromScreen", ltexturesLoadImageFromScreen );
	assingGlobalFunction( "UnloadImage", ltexturesUnloadImage );
	assingGlobalFunction( "ExportImage", ltexturesExportImage );
	assingGlobalFunction( "ExportImageAsCode", ltexturesExportImageAsCode );
		/* Image Generation. */
	assingGlobalFunction( "GenImageColor", ltexturesGenImageColor );
	assingGlobalFunction( "GenImageGradientV", ltexturesGenImageGradientV );
	assingGlobalFunction( "GenImageGradientH", ltexturesGenImageGradientH );
	assingGlobalFunction( "GenImageGradientRadial", ltexturesGenImageGradientRadial );
	assingGlobalFunction( "GenImageChecked", ltexturesGenImageChecked );
	assingGlobalFunction( "GenImageWhiteNoise", ltexturesGenImageWhiteNoise );
	assingGlobalFunction( "GenImagePerlinNoise", ltexturesGenImagePerlinNoise );
	assingGlobalFunction( "GenImageCellular", ltexturesGenImageCellular );
	assingGlobalFunction( "GenImageText", ltexturesGenImageText );
		/* Image Manipulation Functions. */
	assingGlobalFunction( "ImageCopy", ltexturesImageCopy );
	assingGlobalFunction( "ImageFromImage", ltexturesImageFromImage );
	assingGlobalFunction( "ImageText", ltexturesImageText );
	assingGlobalFunction( "ImageFormat", ltexturesImageFormat );
	assingGlobalFunction( "ImageToPOT", ltexturesImageToPOT );
	assingGlobalFunction( "ImageCrop", ltexturesImageCrop );
	assingGlobalFunction( "ImageAlphaCrop", ltexturesImageAlphaCrop );
	assingGlobalFunction( "ImageAlphaClear", ltexturesImageAlphaClear );
	assingGlobalFunction( "ImageAlphaMask", ltexturesImageAlphaMask );
	assingGlobalFunction( "ImageAlphaPremultiply", ltexturesImageAlphaPremultiply );
	assingGlobalFunction( "ImageResize", ltexturesImageResize );
	assingGlobalFunction( "ImageResizeNN", ltexturesImageResizeNN );
	assingGlobalFunction( "ImageResizeCanvas", ltexturesImageResizeCanvas );
	assingGlobalFunction( "ImageMipmaps", ltexturesImageMipmaps );
	assingGlobalFunction( "ImageDither", ltexturesImageDither );
	assingGlobalFunction( "ImageFlipVertical", ltexturesImageFlipVertical );
	assingGlobalFunction( "ImageFlipHorizontal", ltexturesImageFlipHorizontal );
	assingGlobalFunction( "ImageRotateCW", ltexturesImageRotateCW );
	assingGlobalFunction( "ImageRotateCCW", ltexturesImageRotateCCW );
	assingGlobalFunction( "ImageColorTint", ltexturesImageColorTint );
	assingGlobalFunction( "ImageColorInvert", ltexturesImageColorInvert );
	assingGlobalFunction( "ImageColorGrayscale", ltexturesImageColorGrayscale );
	assingGlobalFunction( "ImageColorContrast", ltexturesImageColorContrast );
	assingGlobalFunction( "ImageColorBrightness", ltexturesImageColorBrightness );
	assingGlobalFunction( "ImageColorReplace", ltexturesImageColorReplace );
	assingGlobalFunction( "LoadImageColors", ltexturesLoadImageColors );
	assingGlobalFunction( "LoadImagePalette", ltexturesLoadImagePalette );
	assingGlobalFunction( "GetImageAlphaBorder", ltexturesGetImageAlphaBorder );
	assingGlobalFunction( "GetImageColor", ltexturesGetImageColor );
		/* Image Drawing. */
	assingGlobalFunction( "ImageClearBackground", ltexturesImageClearBackground );
	assingGlobalFunction( "ImageDrawPixel", ltexturesImageDrawPixel );
	assingGlobalFunction( "ImageDrawLine", ltexturesImageDrawLine );
	assingGlobalFunction( "ImageDrawCircle", ltexturesImageDrawCircle );
	assingGlobalFunction( "ImageDrawRectangle", ltexturesImageDrawRectangle );
	assingGlobalFunction( "ImageDrawRectangleLines", ltexturesImageDrawRectangleLines );
	assingGlobalFunction( "ImageDraw", ltexturesImageDraw );
	assingGlobalFunction( "ImageDrawTextEx", ltexturesImageDrawTextEx );
		/* Image Configuration. */
	assingGlobalFunction( "GetImageSize", ltexturesGetImageSize );
	assingGlobalFunction( "GetImageMipmaps", ltexturesGetImageMipmaps );
	assingGlobalFunction( "GetImageFormat", ltexturesGetImageFormat );
		/* Texture Loading. */
	assingGlobalFunction( "LoadTexture", ltexturesLoadTexture );
	assingGlobalFunction( "LoadTextureFromImage", ltexturesLoadTextureFromImage );
	assingGlobalFunction( "LoadTextureCubemap", ltexturesLoadTextureCubemap );
	assingGlobalFunction( "LoadRenderTexture", ltexturesLoadRenderTexture );
	assingGlobalFunction( "UnloadTexture", ltexturesUnloadTexture );
	assingGlobalFunction( "UpdateTexture", ltexturesUpdateTexture );
	assingGlobalFunction( "UpdateTextureRec", ltexturesUpdateTextureRec );
		/* Texture Drawing. */
	assingGlobalFunction( "DrawTexture", ltexturesDrawTexture );
	assingGlobalFunction( "DrawTextureRec", ltexturesDrawTextureRec );
	assingGlobalFunction( "DrawTexturePro", ltexturesDrawTexturePro );
	assingGlobalFunction( "DrawTextureNPatch", ltexturesDrawTextureNPatch );
	assingGlobalFunction( "BeginTextureMode", ltexturesBeginTextureMode );
	assingGlobalFunction( "EndTextureMode", ltexturesEndTextureMode );
	assingGlobalFunction( "GetTextureType", ltexturesGetTextureType );
		/* Texture Configuration. */
	assingGlobalFunction( "GenTextureMipmaps", ltexturesGenTextureMipmaps );
	assingGlobalFunction( "SetTextureFilter", ltexturesSetTextureFilter );
	assingGlobalFunction( "SetTextureWrap", ltexturesSetTextureWrap );
	assingGlobalFunction( "GetTextureSize", ltexturesGetTextureSize );
	assingGlobalFunction( "GetTextureMipmaps", ltexturesGetTextureMipmaps );
	assingGlobalFunction( "GetTextureFormat", ltexturesGetTextureFormat );
		/* Color/pixel */
	assingGlobalFunction( "Fade", ltexturesFade );
	assingGlobalFunction( "ColorToInt", ltexturesColorToInt );
	assingGlobalFunction( "ColorNormalize", ltexturesColorNormalize );
	assingGlobalFunction( "ColorFromNormalized", ltexturesColorFromNormalized );
	assingGlobalFunction( "ColorToHSV", ltexturesColorToHSV );
	assingGlobalFunction( "ColorFromHSV", ltexturesColorFromHSV );
	assingGlobalFunction( "ColorTint", ltexturesColorTint );
	assingGlobalFunction( "ColorBrightness", ltexturesColorBrightness );
	assingGlobalFunction( "ColorContrast", ltexturesColorContrast );
	assingGlobalFunction( "ColorAlpha", ltexturesColorAlpha );
	assingGlobalFunction( "ColorAlphaBlend", ltexturesColorAlphaBlend );
	assingGlobalFunction( "GetColor", ltexturesGetColor );
	assingGlobalFunction( "GetPixelColor", ltexturesGetPixelColor );
	assingGlobalFunction( "GetPixelDataSize", ltexturesGetPixelDataSize );

	/* Models. */
		/* Basic. */
	assingGlobalFunction( "DrawLine3D", lmodelsDrawLine3D );
	assingGlobalFunction( "DrawPoint3D", lmodelsDrawPoint3D );
	assingGlobalFunction( "DrawCircle3D", lmodelsDrawCircle3D );
	assingGlobalFunction( "DrawTriangle3D", lmodelsDrawTriangle3D );
	assingGlobalFunction( "DrawCube", lmodelsDrawCube );
	assingGlobalFunction( "DrawCubeWires", lmodelsDrawCubeWires );
	assingGlobalFunction( "DrawSphere", lmodelsDrawSphere );
	assingGlobalFunction( "DrawSphereEx", lmodelsDrawSphereEx );
	assingGlobalFunction( "DrawSphereWires", lmodelsDrawSphereWires );
	assingGlobalFunction( "DrawCylinder", lmodelsDrawCylinder );
	assingGlobalFunction( "DrawCylinderEx", lmodelsDrawCylinderEx );
	assingGlobalFunction( "DrawCylinderWires", lmodelsDrawCylinderWires );
	assingGlobalFunction( "DrawCylinderWiresEx", lmodelsDrawCylinderWiresEx );
	assingGlobalFunction( "DrawCapsule", lmodelsDrawCapsule );
	assingGlobalFunction( "DrawCapsuleWires", lmodelsDrawCapsuleWires );
	assingGlobalFunction( "DrawPlane", lmodelsDrawPlane );
	assingGlobalFunction( "DrawQuad3DTexture", lmodelDrawQuad3DTexture );
	assingGlobalFunction( "DrawRay", lmodelsDrawRay );
	assingGlobalFunction( "DrawGrid", lmodelsDrawGrid );
		/* Mesh. */
	assingGlobalFunction( "GenMeshPoly", lmodelsGenMeshPoly );
	assingGlobalFunction( "GenMeshPlane", lmodelsGenMeshPlane );
	assingGlobalFunction( "GenMeshCube", lmodelsGenMeshCube );
	assingGlobalFunction( "GenMeshSphere", lmodelsGenMeshSphere );
	assingGlobalFunction( "GenMeshCylinder", lmodelsGenMeshCylinder );
	assingGlobalFunction( "GenMeshCone", lmodelsGenMeshCone );
	assingGlobalFunction( "GenMeshTorus", lmodelsGenMeshTorus );
	assingGlobalFunction( "GenMeshKnot", lmodelsGenMeshKnot );
	assingGlobalFunction( "GenMeshHeightmap", lmodelsGenMeshHeightmap );
	assingGlobalFunction( "GenMeshCustom", lmodelsGenMeshCustom );
	assingGlobalFunction( "UpdateMesh", lmodelsUpdateMesh );
	assingGlobalFunction( "UnloadMesh", lmodelsUnloadMesh );
	assingGlobalFunction( "DrawMesh", lmodelsDrawMesh );
	assingGlobalFunction( "DrawMeshInstanced", lmodelsDrawMeshInstanced );
	assingGlobalFunction( "SetMeshColor", lmodelsSetMeshColor );
	assingGlobalFunction( "ExportMesh", lmodelsExportMesh );
	assingGlobalFunction( "GetMeshBoundingBox", lmodelsGetMeshBoundingBox );
	assingGlobalFunction( "GenMeshTangents", lmodelsGenMeshTangents );
		/* Material. */
	assingGlobalFunction( "LoadMaterialDefault", lmodelsLoadMaterialDefault );
	assingGlobalFunction( "CreateMaterial", lmodelsCreateMaterial );
	assingGlobalFunction( "UnloadMaterial", lmodelsUnloadMaterial );
	assingGlobalFunction( "SetMaterialTexture", lmodelsSetMaterialTexture );
	assingGlobalFunction( "SetMaterialColor", lmodelsSetMaterialColor );
	assingGlobalFunction( "SetMaterialValue", lmodelsSetMaterialValue );
	assingGlobalFunction( "SetMaterialShader", lmodelsSetMaterialShader );
		/* Model. */
	assingGlobalFunction( "LoadModel", lmodelsLoadModel );
	assingGlobalFunction( "LoadModelFromMesh", lmodelsLoadModelFromMesh );
	assingGlobalFunction( "UnloadModel", lmodelsUnloadModel );
	assingGlobalFunction( "DrawModel", lmodelsDrawModel );
	assingGlobalFunction( "DrawModelEx", lmodelsDrawModelEx );
	assingGlobalFunction( "SetModelMaterial", lmodelsSetModelMaterial );
	assingGlobalFunction( "SetModelMeshMaterial", lmodelsSetModelMeshMaterial );
	assingGlobalFunction( "DrawBillboard", lmodelsDrawBillboard );
	assingGlobalFunction( "DrawBillboardRec", lmodelsDrawBillboardRec );
	assingGlobalFunction( "SetModelTransform", lmodelsSetModelTransform );
	assingGlobalFunction( "GetModelTransform", lmodelsGetModelTransform );
		/* Animations. */
	assingGlobalFunction( "LoadModelAnimations", lmodelsLoadModelAnimations );
	assingGlobalFunction( "UpdateModelAnimation", lmodelsUpdateModelAnimation );
	assingGlobalFunction( "UnloadModelAnimations", lmodelsUnloadModelAnimations );
	assingGlobalFunction( "IsModelAnimationValid", lmodelsIsModelAnimationValid );
	assingGlobalFunction( "GetModelAnimationBoneCount", lmodelsGetModelAnimationBoneCount );
	assingGlobalFunction( "GetModelAnimationFrameCount", lmodelsGetModelAnimationFrameCount );
		/* Collision. */
	assingGlobalFunction( "CheckCollisionSpheres", lmodelsCheckCollisionSpheres );
	assingGlobalFunction( "CheckCollisionBoxes", lmodelsCheckCollisionBoxes );
	assingGlobalFunction( "CheckCollisionBoxSphere", lmodelsCheckCollisionBoxSphere );
	assingGlobalFunction( "GetRayCollisionSphere", lmodelsGetRayCollisionSphere );
	assingGlobalFunction( "GetRayCollisionBox", lmodelsGetRayCollisionBox );
	assingGlobalFunction( "GetRayCollisionMesh", lmodelsGetRayCollisionMesh );
	assingGlobalFunction( "GetRayCollisionTriangle", lmodelsGetRayCollisionTriangle );
	assingGlobalFunction( "GetRayCollisionQuad", lmodelsGetRayCollisionQuad );

	/* Text. */
		/* Loading. */
	assingGlobalFunction( "LoadFont", ltextLoadFont );
	assingGlobalFunction( "LoadFontEx", ltextLoadFontEx );
	assingGlobalFunction( "LoadFontFromImage", ltextLoadFontFromImage );
	assingGlobalFunction( "UnloadFont", ltextUnloadFont );
		/* Drawing. */
	assingGlobalFunction( "DrawFPS", ltextDrawFPS );
	assingGlobalFunction( "DrawText", ltextDrawText );
	assingGlobalFunction( "DrawTextPro", ltextDrawTextPro );
		/* Misc. */
	assingGlobalFunction( "MeasureText", ltextMeasureText );
	assingGlobalFunction( "GetFontBaseSize", ltextGetFontBaseSize );
	assingGlobalFunction( "GetFontGlyphCount", ltextGetFontGlyphCount );
	assingGlobalFunction( "GetFontGlyphPadding", ltextGetFontGlyphPadding );

	/* Audio. */
		/* Audio device management. */
	assingGlobalFunction( "SetMasterVolume", laudioSetMasterVolume );
		/* Wave/Sound Loading. */
	assingGlobalFunction( "LoadSound", laudioLoadSound );
	assingGlobalFunction( "LoadWave", laudioLoadWave );
	assingGlobalFunction( "LoadSoundFromWave", laudioLoadSoundFromWave );
	assingGlobalFunction( "UnloadSound", laudioUnloadSound );
	assingGlobalFunction( "UnloadWave", laudioUnloadWave );
	assingGlobalFunction( "ExportWave", laudioExportWave );
	assingGlobalFunction( "ExportWaveAsCode", laudioExportWaveAsCode );
		/* Wave/Sound management */
	assingGlobalFunction( "PlaySound", laudioPlaySound );
	assingGlobalFunction( "StopSound", laudioStopSound );
	assingGlobalFunction( "PauseSound", laudioPauseSound );
	assingGlobalFunction( "ResumeSound", laudioResumeSound );
	assingGlobalFunction( "IsSoundPlaying", laudioIsSoundPlaying );
	assingGlobalFunction( "SetSoundVolume", laudioSetSoundVolume );
	assingGlobalFunction( "SetSoundPitch", laudioSetSoundPitch );
	assingGlobalFunction( "SetSoundPan", laudioSetSoundPan );
	assingGlobalFunction( "WaveFormat", laudioWaveFormat );
	assingGlobalFunction( "WaveCopy", laudioWaveCopy );
	assingGlobalFunction( "WaveCrop", laudioWaveCrop );
		/* Music management. */
	assingGlobalFunction( "LoadMusicStream", laudioLoadMusicStream );
	assingGlobalFunction( "PlayMusicStream", laudioPlayMusicStream );
	assingGlobalFunction( "IsMusicStreamPlaying", laudioIsMusicStreamPlaying );
	assingGlobalFunction( "UpdateMusicStream", laudioUpdateMusicStream );
	assingGlobalFunction( "StopMusicStream", laudioStopMusicStream );
	assingGlobalFunction( "PauseMusicStream", laudioPauseMusicStream );
	assingGlobalFunction( "ResumeMusicStream", laudioResumeMusicStream );
	assingGlobalFunction( "SetMusicVolume", laudioSetMusicVolume );
	assingGlobalFunction( "SetMusicPitch", laudioSetMusicPitch );
	assingGlobalFunction( "SetMusicPan", laudioSetMusicPan );
	assingGlobalFunction( "SetMusicLooping", laudioSetMusicLooping );
	assingGlobalFunction( "GetMusicLooping", laudioGetMusicLooping );
	assingGlobalFunction( "GetMusicTimeLength", laudioGetMusicTimeLength );
	assingGlobalFunction( "GetMusicTimePlayed", laudioGetMusicTimePlayed );

	/* Math. */
		/* Utils. */
	assingGlobalFunction( "Clamp", lmathClamp );
	assingGlobalFunction( "Lerp", lmathLerp );
	assingGlobalFunction( "Normalize", lmathNormalize );
	assingGlobalFunction( "Remap", lmathRemap );
	assingGlobalFunction( "Wrap", lmathWrap );
	assingGlobalFunction( "FloatEquals", lmathFloatEquals );
		/* Vector2. */
	assingGlobalFunction( "Vector2Zero", lmathVector2Zero );
	assingGlobalFunction( "Vector2One", lmathVector2One );
	assingGlobalFunction( "Vector2Add", lmathVector2Add );
	assingGlobalFunction( "Vector2AddValue", lmathVector2AddValue );
	assingGlobalFunction( "Vector2Subtract", lmathVector2Subtract );
	assingGlobalFunction( "Vector2SubtractValue", lmathVector2SubtractValue );
	assingGlobalFunction( "Vector2Length", lmathVector2Length );
	assingGlobalFunction( "Vector2LengthSqr", lmathVector2LengthSqr );
	assingGlobalFunction( "Vector2DotProduct", lmathVector2DotProduct );
	assingGlobalFunction( "Vector2Distance", lmathVector2Distance );
	assingGlobalFunction( "Vector2DistanceSqr", lmathVector2DistanceSqr );
	assingGlobalFunction( "Vector2Angle", lmathVector2Angle );
	assingGlobalFunction( "Vector2LineAngle", lmathVector2LineAngle );
	assingGlobalFunction( "Vector2Scale", lmathVector2Scale );
	assingGlobalFunction( "Vector2Multiply", lmathVector2Multiply );
	assingGlobalFunction( "Vector2Negate", lmathVector2Negate );
	assingGlobalFunction( "Vector2Divide", lmathVector2Divide );
	assingGlobalFunction( "Vector2Normalize", lmathVector2Normalize );
	assingGlobalFunction( "Vector2Transform", lmathVector2Transform );
	assingGlobalFunction( "Vector2Lerp", lmathVector2Lerp );
	assingGlobalFunction( "Vector2Reflect", lmathVector2Reflect );
	assingGlobalFunction( "Vector2Rotate", lmathVector2Rotate );
	assingGlobalFunction( "Vector2MoveTowards", lmathVector2MoveTowards );
	assingGlobalFunction( "Vector2Invert", lmathVector2Invert );
	assingGlobalFunction( "Vector2Clamp", lmathVector2Clamp );
	assingGlobalFunction( "Vector2ClampValue", lmathVector2ClampValue );
	assingGlobalFunction( "Vector2Equals", lmathVector2Equals );
		/* Vector3. */
	assingGlobalFunction( "Vector3Zero", lmathVector3Zero );
	assingGlobalFunction( "Vector3One", lmathVector3One );
	assingGlobalFunction( "Vector3Add", lmathVector3Add );
	assingGlobalFunction( "Vector3AddValue", lmathVector3AddValue );
	assingGlobalFunction( "Vector3Subtract", lmathVector3Subtract );
	assingGlobalFunction( "Vector3SubtractValue", lmathVector3SubtractValue );
	assingGlobalFunction( "Vector3Scale", lmathVector3Scale );
	assingGlobalFunction( "Vector3Multiply", lmathVector3Multiply );
	assingGlobalFunction( "Vector3CrossProduct", lmathVector3CrossProduct );
	assingGlobalFunction( "Vector3Perpendicular", lmathVector3Perpendicular );
	assingGlobalFunction( "Vector3Length", lmathVector3Length );
	assingGlobalFunction( "Vector3LengthSqr", lmathVector3LengthSqr );
	assingGlobalFunction( "Vector3DotProduct", lmathVector3DotProduct );
	assingGlobalFunction( "Vector3Distance", lmathVector3Distance );
	assingGlobalFunction( "Vector3DistanceSqr", lmathVector3DistanceSqr );
	assingGlobalFunction( "Vector3Angle", lmathVector3Angle );
	assingGlobalFunction( "Vector3Negate", lmathVector3Negate );
	assingGlobalFunction( "Vector3Divide", lmathVector3Divide );
	assingGlobalFunction( "Vector3Normalize", lmathVector3Normalize );
	assingGlobalFunction( "Vector3OrthoNormalize", lmathVector3OrthoNormalize );
	assingGlobalFunction( "Vector3Transform", lmathVector3Transform );
	assingGlobalFunction( "Vector3RotateByQuaternion", lmathVector3RotateByQuaternion );
	assingGlobalFunction( "Vector3Lerp", lmathVector3Lerp );
	assingGlobalFunction( "Vector3Reflect", lmathVector3Reflect );
	assingGlobalFunction( "Vector3Min", lmathVector3Min );
	assingGlobalFunction( "Vector3Max", lmathVector3Max );
	assingGlobalFunction( "Vector3Barycenter", lmathVector3Barycenter );
	assingGlobalFunction( "Vector3Unproject", lmathVector3Unproject );
	assingGlobalFunction( "Vector3Invert", lmathVector3Invert );
	assingGlobalFunction( "Vector3Clamp", lmathVector3Clamp );
	assingGlobalFunction( "Vector3ClampValue", lmathVector3ClampValue );
	assingGlobalFunction( "Vector3Equals", lmathVector3Equals );
	assingGlobalFunction( "Vector3Refract", lmathVector3Refract );
		/* Matrix. */
	assingGlobalFunction( "MatrixDeterminant", lmathMatrixDeterminant );
	assingGlobalFunction( "MatrixTrace", lmathMatrixTrace );
	assingGlobalFunction( "MatrixTranspose", lmathMatrixTranspose );
	assingGlobalFunction( "MatrixInvert", lmathMatrixInvert );
	assingGlobalFunction( "MatrixIdentity", lmathMatrixIdentity );
	assingGlobalFunction( "MatrixAdd", lmathMatrixAdd );
	assingGlobalFunction( "MatrixSubtract", lmathMatrixSubtract );
	assingGlobalFunction( "MatrixMultiply", lmathMatrixMultiply );
	assingGlobalFunction( "MatrixTranslate", lmathMatrixTranslate );
	assingGlobalFunction( "MatrixRotate", lmathMatrixRotate );
	assingGlobalFunction( "MatrixRotateX", lmathMatrixRotateX );
	assingGlobalFunction( "MatrixRotateY", lmathMatrixRotateY );
	assingGlobalFunction( "MatrixRotateZ", lmathMatrixRotateZ );
	assingGlobalFunction( "MatrixRotateXYZ", lmathMatrixRotateXYZ );
	assingGlobalFunction( "MatrixRotateZYX", lmathMatrixRotateZYX );
	assingGlobalFunction( "MatrixScale", lmathMatrixScale );
	assingGlobalFunction( "MatrixFrustum", lmathMatrixFrustum );
	assingGlobalFunction( "MatrixPerspective", lmathMatrixPerspective );
	assingGlobalFunction( "MatrixOrtho", lmathMatrixOrtho );
	assingGlobalFunction( "MatrixLookAt", lmathMatrixLookAt );
		/* Quaternion. */
	assingGlobalFunction( "QuaternionAdd", lmathQuaternionAdd );
	assingGlobalFunction( "QuaternionAddValue", lmathQuaternionAddValue );
	assingGlobalFunction( "QuaternionSubtract", lmathQuaternionSubtract );
	assingGlobalFunction( "QuaternionSubtractValue", lmathQuaternionSubtractValue );
	assingGlobalFunction( "QuaternionIdentity", lmathQuaternionIdentity );
	assingGlobalFunction( "QuaternionLength", lmathQuaternionLength );
	assingGlobalFunction( "QuaternionNormalize", lmathQuaternionNormalize );
	assingGlobalFunction( "QuaternionInvert", lmathQuaternionInvert );
	assingGlobalFunction( "QuaternionMultiply", lmathQuaternionMultiply );
	assingGlobalFunction( "QuaternionScale", lmathQuaternionScale );
	assingGlobalFunction( "QuaternionDivide", lmathQuaternionDivide );
	assingGlobalFunction( "QuaternionLerp", lmathQuaternionLerp );
	assingGlobalFunction( "QuaternionNlerp", lmathQuaternionNlerp );
	assingGlobalFunction( "QuaternionSlerp", lmathQuaternionSlerp );
	assingGlobalFunction( "QuaternionFromVector3ToVector3", lmathQuaternionFromVector3ToVector3 );
	assingGlobalFunction( "QuaternionFromMatrix", lmathQuaternionFromMatrix );
	assingGlobalFunction( "QuaternionToMatrix", lmathQuaternionToMatrix );
	assingGlobalFunction( "QuaternionFromAxisAngle", lmathQuaternionFromAxisAngle );
	assingGlobalFunction( "QuaternionToAxisAngle", lmathQuaternionToAxisAngle );
	assingGlobalFunction( "QuaternionFromEuler", lmathQuaternionFromEuler );
	assingGlobalFunction( "QuaternionToEuler", lmathQuaternionToEuler );
	assingGlobalFunction( "QuaternionTransform", lmathQuaternionTransform );
	assingGlobalFunction( "QuaternionEquals", lmathQuaternionEquals );

	/* Gui. */
		/* Global. */
	assingGlobalFunction( "GuiEnable", lguiGuiEnable );
	assingGlobalFunction( "GuiDisable", lguiGuiDisable );
	assingGlobalFunction( "GuiLock", lguiGuiLock );
	assingGlobalFunction( "GuiUnlock", lguiGuiUnlock );
	assingGlobalFunction( "GuiIsLocked", lguiGuiIsLocked );
	assingGlobalFunction( "GuiFade", lguiGuiFade );
	assingGlobalFunction( "GuiSetState", lguiGuiSetState );
	assingGlobalFunction( "GuiGetState", lguiGuiGetState );
		/* Font. */
	assingGlobalFunction( "GuiSetFont", lguiGuiSetFont );
	assingGlobalFunction( "GuiGetFont", lguiGuiGetFont );
		/* Style. */
	assingGlobalFunction( "GuiSetStyle", lguiGuiSetStyle );
	assingGlobalFunction( "GuiGetStyle", lguiGuiGetStyle );
	assingGlobalFunction( "GuiLoadStyle", lguiGuiLoadStyle );
	assingGlobalFunction( "GuiLoadStyleDefault", lguiGuiLoadStyleDefault );
		/* Container. */
	assingGlobalFunction( "GuiWindowBox", lguiGuiWindowBox );
	assingGlobalFunction( "GuiGroupBox", lguiGuiGroupBox );
	assingGlobalFunction( "GuiLine", lguiGuiLine );
	assingGlobalFunction( "GuiPanel", lguiGuiPanel );
	assingGlobalFunction( "GuiScrollPanel", lguiGuiScrollPanel );
		/* Basic. */
	assingGlobalFunction( "GuiLabel", lguiGuiLabel );
	assingGlobalFunction( "GuiButton", lguiGuiButton );
	assingGlobalFunction( "GuiLabelButton", lguiGuiLabelButton );
	assingGlobalFunction( "GuiToggle", lguiGuiToggle );
	assingGlobalFunction( "GuiToggleGroup", lguiGuiToggleGroup );
	assingGlobalFunction( "GuiCheckBox", lguiGuiCheckBox );
	assingGlobalFunction( "GuiComboBox", lguiGuiComboBox );
	assingGlobalFunction( "GuiTextBox", lguiGuiTextBox );
	assingGlobalFunction( "GuiTextBoxMulti", lguiGuiTextBoxMulti );
	assingGlobalFunction( "GuiSpinner", lguiGuiSpinner );
	assingGlobalFunction( "GuiValueBox", lguiGuiValueBox );
	assingGlobalFunction( "GuiSlider", lguiGuiSlider );
	assingGlobalFunction( "GuiSliderBar", lguiGuiSliderBar );
	assingGlobalFunction( "GuiProgressBar", lguiGuiProgressBar );
	assingGlobalFunction( "GuiScrollBar", lguiGuiScrollBar );
	assingGlobalFunction( "GuiDropdownBox", lguiGuiDropdownBox );
	assingGlobalFunction( "GuiStatusBar", lguiGuiStatusBar );
	assingGlobalFunction( "GuiDummyRec", lguiGuiDummyRec );
	assingGlobalFunction( "GuiGrid", lguiGuiGrid );
		/* Advanced. */
	assingGlobalFunction( "GuiListView", lguiGuiListView );
	assingGlobalFunction( "GuiListViewEx", lguiGuiListViewEx );
	assingGlobalFunction( "GuiMessageBox", lguiGuiMessageBox );
	assingGlobalFunction( "GuiTextInputBox", lguiGuiTextInputBox );
	assingGlobalFunction( "GuiColorPicker", lguiGuiColorPicker );
	assingGlobalFunction( "GuiColorPanel", lguiGuiColorPanel );
	assingGlobalFunction( "GuiColorBarAlpha", lguiGuiColorBarAlpha );
	assingGlobalFunction( "GuiColorBarHue", lguiGuiColorBarHue );
		/* Icons. */
	assingGlobalFunction( "GuiIconText", lguiGuiIconText );
	assingGlobalFunction( "GuiDrawIcon", lguiGuiDrawIcon );
	assingGlobalFunction( "GuiSetIconScale", lguiGuiSetIconScale );
	assingGlobalFunction( "GuiSetIconPixel", lguiGuiSetIconPixel );
	assingGlobalFunction( "GuiClearIconPixel", lguiGuiClearIconPixel );
	assingGlobalFunction( "GuiCheckIconPixel", lguiGuiCheckIconPixel );

	/* Lights */
		/* Basics. */
	assingGlobalFunction( "CreateLight", llightsCreateLight );
	assingGlobalFunction( "UpdateLightValues", llightsUpdateLightValues );

	/* RLGL */
		/* General render state. */
	assingGlobalFunction( "rlglSetLineWidth", lrlglSetLineWidth );
	assingGlobalFunction( "rlglGetLineWidth", lrlglGetLineWidth );

	/* OpenGL */
		/* Framebuffer management. */
	assingGlobalFunction( "glBlitFramebuffer", lglBlitFramebuffer );

	/* Easings */
		/* Linear Easing functions. */
	assingGlobalFunction( "EaseLinear", leasingsEaseLinear );
		/* Sine Easing functions. */
	assingGlobalFunction( "EaseSineIn", leasingsEaseSineIn );
	assingGlobalFunction( "EaseSineOut", leasingsEaseSineOut );
	assingGlobalFunction( "EaseSineInOut", leasingsEaseSineInOut );
		/* Circular Easing functions. */
	assingGlobalFunction( "EaseCircIn", leasingsEaseCircIn );
	assingGlobalFunction( "EaseCircOut", leasingsEaseCircOut );
	assingGlobalFunction( "EaseCircInOut", leasingsEaseCircInOut );
		/* Cubic Easing functions. */
	assingGlobalFunction( "EaseCubicIn", leasingsEaseCubicIn );
	assingGlobalFunction( "EaseCubicOut", leasingsEaseCubicOut );
	assingGlobalFunction( "EaseCubicInOut", leasingsEaseCubicInOut );
		/* Quadratic Easing functions. */
	assingGlobalFunction( "EaseQuadIn", leasingsEaseQuadIn );
	assingGlobalFunction( "EaseQuadOut", leasingsEaseQuadOut );
	assingGlobalFunction( "EaseQuadInOut", leasingsEaseQuadInOut );
		/* Exponential Easing functions. */
	assingGlobalFunction( "EaseExpoIn", leasingsEaseExpoIn );
	assingGlobalFunction( "EaseExpoOut", leasingsEaseExpoOut );
	assingGlobalFunction( "EaseExpoInOut", leasingsEaseExpoInOut );
		/* Back Easing functions. */
	assingGlobalFunction( "EaseBackIn", leasingsEaseBackIn );
	assingGlobalFunction( "EaseBackOut", leasingsEaseBackOut );
	assingGlobalFunction( "EaseBackInOut", leasingsEaseBackInOut );
		/* Bounce Easing functions. */
	assingGlobalFunction( "EaseBounceIn", leasingsEaseBounceIn );
	assingGlobalFunction( "EaseBounceOut", leasingsEaseBounceOut );
	assingGlobalFunction( "EaseBounceInOut", leasingsEaseBounceInOut );
		/* Elastic Easing functions. */
	assingGlobalFunction( "EaseElasticIn", leasingsEaseElasticIn );
	assingGlobalFunction( "EaseElasticOut", leasingsEaseElasticOut );
	assingGlobalFunction( "EaseElasticInOut", leasingsEaseElasticInOut );

	lua_pop( L, -1 );
}

/* Lua util functions. */

Color uluaGetColor( lua_State *L ) {
    return uluaGetColorIndex( L, lua_gettop( L ) );
}

Color uluaGetColorIndex( lua_State *L, int index ) {
    Color color = { 0, 0, 0, 255 };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong color value. Returning { 0, 0, 0, 255 }" );
        return color;
    }
	// int t = lua_gettop( L ), i = 0;
	int t = index, i = 0;
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
    return uluaGetVector2Index( L, lua_gettop( L ) );
}

Vector2 uluaGetVector2Index( lua_State *L, int index ) {
    Vector2 vector = { 0.0f, 0.0f };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector2 value. Returning { 0, 0 }" );
        return vector;
    }
	int t = index, i = 0;
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
    return uluaGetVector3Index( L, lua_gettop( L ) );
}

Vector3 uluaGetVector3Index( lua_State *L, int index ) {
    Vector3 vector = { 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector3 value. Returning { 0, 0, 0 }" );
        return vector;
    }
	int t = index, i = 0;
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
   return uluaGetVector4Index( L, lua_gettop( L ) );
}

Vector4 uluaGetVector4Index( lua_State *L, int index ) {
    Vector4 vector = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong vector4 value. Returning { 0, 0, 0, 0 }" );
        return vector;
    }
	int t = index, i = 0;
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
	return uluaGetRectangleIndex( L, lua_gettop( L ) );
}

Rectangle uluaGetRectangleIndex( lua_State *L, int index ) {
    Rectangle rect = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong rectangle value. Returning { 0, 0, 0, 0 }" );
        return rect;
    }

	int t = index, i = 0;
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
    return uluaGetQuaternionIndex( L, lua_gettop( L ) );
}

Quaternion uluaGetQuaternionIndex( lua_State *L, int index ) {
    Quaternion quaternion = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong quaternion value. Returning { 0, 0, 0, 0 }" );
        return quaternion;
    }
	int t = index, i = 0;
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
	return uluaGetMatrixIndex( L, lua_gettop( L ) );
}

Matrix uluaGetMatrixIndex( lua_State *L, int index ) {
	Matrix matrix = { 0.0f };
	float m[4][4];

    if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong matrix value. Returning MatrixIdentity." );
        return MatrixIdentity();
    }
	int t = index, i = 0;
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
	return uluaGetBoundingBoxIndex( L, lua_gettop( L ) );
}

BoundingBox uluaGetBoundingBoxIndex( lua_State *L, int index ) {
	BoundingBox box = { .min = { 0.0, 0.0, 0.0 }, .max = { 0.0, 0.0, 0.0 } };

	if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong boundingbox value. Returning { min{ 0, 0, 0 }, max{ 0, 0, 0 } }." );
        return box;
    }
	int t = index, i = 0;
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
	return uluaGetRayIndex( L, lua_gettop( L ) );
}

Ray uluaGetRayIndex( lua_State *L, int index ) {
	Ray ray = { .position = { 0.0, 0.0, 0.0 }, .direction = { 0.0, 0.0, 0.0 } };

	if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong ray value. Returning { position{ 0, 0, 0 }, direction{ 0, 0, 0 } }." );
        return ray;
    }
	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( lua_istable( L, -1 ) ) {
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
	return uluaGetNPatchInfoIndex( L, lua_gettop( L ) );
}

NPatchInfo uluaGetNPatchInfoIndex( lua_State *L, int index ) {
	NPatchInfo npatch = { .source = { 0.0, 0.0, 0.0, 0.0 }, .left = 0, .top = 0, .right = 0, .bottom = 0, .layout = NPATCH_NINE_PATCH };

	if ( !lua_istable( L, index ) ) {
		TraceLog( LOG_WARNING, "%s", "Error. Wrong ray value. Returning { source = { 0.0, 0.0, 0.0, 0.0 }, left = 0, top = 0, right = 0, bottom = 0, layout = NPATCH_NINE_PATCH }." );
        return npatch;
    }
	int t = index, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		/* Do not check type since there should be table and ints. */
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

void uluaPushBoundingBox( lua_State *L, BoundingBox box ) {
	lua_createtable( L, 2, 0 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, box.min.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, box.min.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, box.min.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 1 );

	lua_createtable( L, 3, 0 );
	lua_pushnumber( L, box.max.x );
	lua_rawseti( L, -2, 1 );
	lua_pushnumber( L, box.max.y );
	lua_rawseti( L, -2, 2 );
	lua_pushnumber( L, box.max.z );
	lua_rawseti( L, -2, 3 );
	lua_rawseti( L, -2, 2 );
}

int uluaGetTableLen( lua_State *L ) {
	return uluaGetTableLenIndex( L, lua_gettop( L ) );
}

int uluaGetTableLenIndex( lua_State *L, int index ) {
	int t = index, i = 0;
    lua_pushnil( L );

    while ( lua_next( L, t ) != 0 ) {
        i++;
        lua_pop( L, 1 );
    }
    return i;
}
