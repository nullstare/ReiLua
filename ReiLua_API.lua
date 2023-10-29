-- Put this file into your project folder to provide annotations when using Lua language server.

RL={}

-- Functions.

---This function will be called first when 'main.lua' is found
function RL.init() end
---This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'
---@param delta number
function RL.process( delta ) end
---This function will be called every frame after process and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.
function RL.draw() end
---This function will be called on events input. Content of event table is determined by event type.
---@param event table
function RL.event( event ) end
---This function can be used for custom log message handling.
---@param logLevel integer
---@param message string
function RL.log( logLevel, message ) end
---This function will be called on program close. Cleanup could be done here.
function RL.exit() end
---This function will be called on program close. Cleanup could be done here.
function RL.exit() end

-- Globals - ConfigFlags

RL.FLAG_VSYNC_HINT=64
RL.FLAG_FULLSCREEN_MODE=2
RL.FLAG_WINDOW_RESIZABLE=4
RL.FLAG_WINDOW_UNDECORATED=8
RL.FLAG_WINDOW_HIDDEN=128
RL.FLAG_WINDOW_MINIMIZED=512
RL.FLAG_WINDOW_MAXIMIZED=1024
RL.FLAG_WINDOW_UNFOCUSED=2048
RL.FLAG_WINDOW_TOPMOST=4096
RL.FLAG_WINDOW_ALWAYS_RUN=256
RL.FLAG_WINDOW_TRANSPARENT=16
RL.FLAG_WINDOW_HIGHDPI=8192
RL.FLAG_MSAA_4X_HINT=32
RL.FLAG_INTERLACED_HINT=65536

-- Globals - TraceLogLevel

RL.LOG_ALL=0
RL.LOG_TRACE=1
RL.LOG_DEBUG=2
RL.LOG_INFO=3
RL.LOG_WARNING=4
RL.LOG_ERROR=5
RL.LOG_FATAL=6
RL.LOG_NONE=7

-- Globals - KeyboardKey

RL.GLFW_KEY_UNKNOWN=nil
RL.KEY_NULL=0
RL.KEY_APOSTROPHE=39
RL.KEY_COMMA=44
RL.KEY_MINUS=45
RL.KEY_PERIOD=46
RL.KEY_SLASH=47
RL.KEY_ZERO=48
RL.KEY_ONE=49
RL.KEY_TWO=50
RL.KEY_THREE=51
RL.KEY_FOUR=52
RL.KEY_FIVE=53
RL.KEY_SIX=54
RL.KEY_SEVEN=55
RL.KEY_EIGHT=56
RL.KEY_NINE=57
RL.KEY_SEMICOLON=59
RL.KEY_EQUAL=61
RL.KEY_A=65
RL.KEY_B=66
RL.KEY_C=67
RL.KEY_D=68
RL.KEY_E=69
RL.KEY_F=70
RL.KEY_G=71
RL.KEY_H=72
RL.KEY_I=73
RL.KEY_J=74
RL.KEY_K=75
RL.KEY_L=76
RL.KEY_M=77
RL.KEY_N=78
RL.KEY_O=79
RL.KEY_P=80
RL.KEY_Q=81
RL.KEY_R=82
RL.KEY_S=83
RL.KEY_T=84
RL.KEY_U=85
RL.KEY_V=86
RL.KEY_W=87
RL.KEY_X=88
RL.KEY_Y=89
RL.KEY_Z=90
RL.KEY_LEFT_BRACKET=91
RL.KEY_BACKSLASH=92
RL.KEY_RIGHT_BRACKET=93
RL.KEY_GRAVE=96
RL.KEY_SPACE=32
RL.KEY_ESCAPE=256
RL.KEY_ENTER=257
RL.KEY_TAB=258
RL.KEY_BACKSPACE=259
RL.KEY_INSERT=260
RL.KEY_DELETE=261
RL.KEY_RIGHT=262
RL.KEY_LEFT=263
RL.KEY_DOWN=264
RL.KEY_UP=265
RL.KEY_PAGE_UP=266
RL.KEY_PAGE_DOWN=267
RL.KEY_HOME=268
RL.KEY_END=269
RL.KEY_CAPS_LOCK=280
RL.KEY_SCROLL_LOCK=281
RL.KEY_NUM_LOCK=282
RL.KEY_PRINT_SCREEN=283
RL.KEY_PAUSE=284
RL.KEY_F1=290
RL.KEY_F2=291
RL.KEY_F3=292
RL.KEY_F4=293
RL.KEY_F5=294
RL.KEY_F6=295
RL.KEY_F7=296
RL.KEY_F8=297
RL.KEY_F9=298
RL.KEY_F10=299
RL.KEY_F11=300
RL.KEY_F12=301
RL.KEY_LEFT_SHIFT=340
RL.KEY_LEFT_CONTROL=341
RL.KEY_LEFT_ALT=342
RL.KEY_LEFT_SUPER=343
RL.KEY_RIGHT_SHIFT=344
RL.KEY_RIGHT_CONTROL=345
RL.KEY_RIGHT_ALT=346
RL.KEY_RIGHT_SUPER=347
RL.KEY_KB_MENU=348
RL.KEY_KP_0=320
RL.KEY_KP_1=321
RL.KEY_KP_2=322
RL.KEY_KP_3=323
RL.KEY_KP_4=324
RL.KEY_KP_5=325
RL.KEY_KP_6=326
RL.KEY_KP_7=327
RL.KEY_KP_8=328
RL.KEY_KP_9=329
RL.KEY_KP_DECIMAL=330
RL.KEY_KP_DIVIDE=331
RL.KEY_KP_MULTIPLY=332
RL.KEY_KP_SUBTRACT=333
RL.KEY_KP_ADD=334
RL.KEY_KP_ENTER=335
RL.KEY_KP_EQUAL=336
RL.KEY_BACK=4
RL.KEY_MENU=82
RL.KEY_VOLUME_UP=24
RL.KEY_VOLUME_DOWN=25

-- Globals - MouseButtons

RL.MOUSE_BUTTON_LEFT=0
RL.MOUSE_BUTTON_RIGHT=1
RL.MOUSE_BUTTON_MIDDLE=2
RL.MOUSE_BUTTON_SIDE=3
RL.MOUSE_BUTTON_EXTRA=4
RL.MOUSE_BUTTON_FORWARD=5
RL.MOUSE_BUTTON_BACK=6

-- Globals - MouseCursor

RL.MOUSE_CURSOR_DEFAULT=0
RL.MOUSE_CURSOR_ARROW=1
RL.MOUSE_CURSOR_IBEAM=2
RL.MOUSE_CURSOR_CROSSHAIR=3
RL.MOUSE_CURSOR_POINTING_HAND=4
RL.MOUSE_CURSOR_RESIZE_EW=5
RL.MOUSE_CURSOR_RESIZE_NS=6
RL.MOUSE_CURSOR_RESIZE_NWSE=7
RL.MOUSE_CURSOR_RESIZE_NESW=8
RL.MOUSE_CURSOR_RESIZE_ALL=9
RL.MOUSE_CURSOR_NOT_ALLOWED=10

-- Globals - GamepadButtons

RL.GAMEPAD_BUTTON_UNKNOWN=0
RL.GAMEPAD_BUTTON_LEFT_FACE_UP=1
RL.GAMEPAD_BUTTON_LEFT_FACE_RIGHT=2
RL.GAMEPAD_BUTTON_LEFT_FACE_DOWN=3
RL.GAMEPAD_BUTTON_LEFT_FACE_LEFT=4
RL.GAMEPAD_BUTTON_RIGHT_FACE_UP=5
RL.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT=6
RL.GAMEPAD_BUTTON_RIGHT_FACE_DOWN=7
RL.GAMEPAD_BUTTON_RIGHT_FACE_LEFT=8
RL.GAMEPAD_BUTTON_LEFT_TRIGGER_1=9
RL.GAMEPAD_BUTTON_LEFT_TRIGGER_2=10
RL.GAMEPAD_BUTTON_RIGHT_TRIGGER_1=11
RL.GAMEPAD_BUTTON_RIGHT_TRIGGER_2=12
RL.GAMEPAD_BUTTON_MIDDLE_LEFT=13
RL.GAMEPAD_BUTTON_MIDDLE=14
RL.GAMEPAD_BUTTON_MIDDLE_RIGHT=15
RL.GAMEPAD_BUTTON_LEFT_THUMB=16
RL.GAMEPAD_BUTTON_RIGHT_THUMB=17

-- Globals - GamepadAxis

RL.GAMEPAD_AXIS_LEFT_X=0
RL.GAMEPAD_AXIS_LEFT_Y=1
RL.GAMEPAD_AXIS_RIGHT_X=2
RL.GAMEPAD_AXIS_RIGHT_Y=3
RL.GAMEPAD_AXIS_LEFT_TRIGGER=4
RL.GAMEPAD_AXIS_RIGHT_TRIGGER=5

-- Globals - MapTypes

RL.MATERIAL_MAP_ALBEDO=0
RL.MATERIAL_MAP_METALNESS=1
RL.MATERIAL_MAP_NORMAL=2
RL.MATERIAL_MAP_ROUGHNESS=3
RL.MATERIAL_MAP_OCCLUSION=4
RL.MATERIAL_MAP_EMISSION=5
RL.MATERIAL_MAP_HEIGHT=6
RL.MATERIAL_MAP_CUBEMAP=7
RL.MATERIAL_MAP_IRRADIANCE=8
RL.MATERIAL_MAP_PREFILTER=9
RL.MATERIAL_MAP_BRDF=10
RL.MATERIAL_MAP_DIFFUSE=0
RL.MATERIAL_MAP_SPECULAR=1

-- Globals - ShaderLocationIndex

RL.SHADER_LOC_VERTEX_POSITION=0
RL.SHADER_LOC_VERTEX_TEXCOORD01=1
RL.SHADER_LOC_VERTEX_TEXCOORD02=2
RL.SHADER_LOC_VERTEX_NORMAL=3
RL.SHADER_LOC_VERTEX_TANGENT=4
RL.SHADER_LOC_VERTEX_COLOR=5
RL.SHADER_LOC_MATRIX_MVP=6
RL.SHADER_LOC_MATRIX_VIEW=7
RL.SHADER_LOC_MATRIX_PROJECTION=8
RL.SHADER_LOC_MATRIX_MODEL=9
RL.SHADER_LOC_MATRIX_NORMAL=10
RL.SHADER_LOC_VECTOR_VIEW=11
RL.SHADER_LOC_COLOR_DIFFUSE=12
RL.SHADER_LOC_COLOR_SPECULAR=13
RL.SHADER_LOC_COLOR_AMBIENT=14
RL.SHADER_LOC_MAP_ALBEDO=15
RL.SHADER_LOC_MAP_METALNESS=16
RL.SHADER_LOC_MAP_NORMAL=17
RL.SHADER_LOC_MAP_ROUGHNESS=18
RL.SHADER_LOC_MAP_OCCLUSION=19
RL.SHADER_LOC_MAP_EMISSION=20
RL.SHADER_LOC_MAP_HEIGHT=21
RL.SHADER_LOC_MAP_CUBEMAP=22
RL.SHADER_LOC_MAP_IRRADIANCE=23
RL.SHADER_LOC_MAP_PREFILTER=24
RL.SHADER_LOC_MAP_BRDF=25
RL.SHADER_LOC_MAP_DIFFUSE=15
RL.SHADER_LOC_MAP_SPECULAR=16

-- Globals - ShaderUniformDataType

RL.SHADER_UNIFORM_FLOAT=0
RL.SHADER_UNIFORM_VEC2=1
RL.SHADER_UNIFORM_VEC3=2
RL.SHADER_UNIFORM_VEC4=3
RL.SHADER_UNIFORM_INT=4
RL.SHADER_UNIFORM_IVEC2=5
RL.SHADER_UNIFORM_IVEC3=6
RL.SHADER_UNIFORM_IVEC4=7
RL.SHADER_UNIFORM_SAMPLER2D=8

-- Globals - ShaderAttributeDataTypes

RL.SHADER_ATTRIB_FLOAT=0
RL.SHADER_ATTRIB_VEC2=1
RL.SHADER_ATTRIB_VEC3=2
RL.SHADER_ATTRIB_VEC4=3

-- Globals - PixelFormats

RL.PIXELFORMAT_UNCOMPRESSED_GRAYSCALE=1
RL.PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA=2
RL.PIXELFORMAT_UNCOMPRESSED_R5G6B5=3
RL.PIXELFORMAT_UNCOMPRESSED_R8G8B8=4
RL.PIXELFORMAT_UNCOMPRESSED_R5G5B5A1=5
RL.PIXELFORMAT_UNCOMPRESSED_R4G4B4A4=6
RL.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8=7
RL.PIXELFORMAT_UNCOMPRESSED_R32=8
RL.PIXELFORMAT_UNCOMPRESSED_R32G32B32=9
RL.PIXELFORMAT_UNCOMPRESSED_R32G32B32A32=10
RL.PIXELFORMAT_COMPRESSED_DXT1_RGB=11
RL.PIXELFORMAT_COMPRESSED_DXT1_RGBA=12
RL.PIXELFORMAT_COMPRESSED_DXT3_RGBA=13
RL.PIXELFORMAT_COMPRESSED_DXT5_RGBA=14
RL.PIXELFORMAT_COMPRESSED_ETC1_RGB=15
RL.PIXELFORMAT_COMPRESSED_ETC2_RGB=16
RL.PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA=17
RL.PIXELFORMAT_COMPRESSED_PVRT_RGB=18
RL.PIXELFORMAT_COMPRESSED_PVRT_RGBA=19
RL.PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA=20
RL.PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA=21

-- Globals - TextureFilters

RL.TEXTURE_FILTER_POINT=0
RL.TEXTURE_FILTER_BILINEAR=1
RL.TEXTURE_FILTER_TRILINEAR=2
RL.TEXTURE_FILTER_ANISOTROPIC_4X=3
RL.TEXTURE_FILTER_ANISOTROPIC_8X=4
RL.TEXTURE_FILTER_ANISOTROPIC_16X=5

-- Globals - TextureWrap

RL.TEXTURE_WRAP_REPEAT=0
RL.TEXTURE_WRAP_CLAMP=1
RL.TEXTURE_WRAP_MIRROR_REPEAT=2
RL.TEXTURE_WRAP_MIRROR_CLAMP=3

-- Globals - CubemapLayout

RL.CUBEMAP_LAYOUT_AUTO_DETECT=0
RL.CUBEMAP_LAYOUT_LINE_VERTICAL=1
RL.CUBEMAP_LAYOUT_LINE_HORIZONTAL=2
RL.CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR=3
RL.CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE=4
RL.CUBEMAP_LAYOUT_PANORAMA=5

-- Globals - FontType

RL.FONT_DEFAULT=0
RL.FONT_BITMAP=1
RL.FONT_SDF=2

-- Globals - BlendModes

RL.BLEND_ALPHA=0
RL.BLEND_ADDITIVE=1
RL.BLEND_MULTIPLIED=2
RL.BLEND_ADD_COLORS=3
RL.BLEND_SUBTRACT_COLORS=4
RL.BLEND_ALPHA_PREMULTIPLY=5
RL.BLEND_CUSTOM=6
RL.BLEND_CUSTOM_SEPARATE=7

-- Globals - Gesture

RL.GESTURE_NONE=0
RL.GESTURE_TAP=1
RL.GESTURE_DOUBLETAP=2
RL.GESTURE_HOLD=4
RL.GESTURE_DRAG=8
RL.GESTURE_SWIPE_RIGHT=16
RL.GESTURE_SWIPE_LEFT=32
RL.GESTURE_SWIPE_UP=64
RL.GESTURE_SWIPE_DOWN=128
RL.GESTURE_PINCH_IN=256
RL.GESTURE_PINCH_OUT=512

-- Globals - CameraMode

RL.CAMERA_CUSTOM=0
RL.CAMERA_FREE=1
RL.CAMERA_ORBITAL=2
RL.CAMERA_FIRST_PERSON=3
RL.CAMERA_THIRD_PERSON=4

-- Globals - CameraProjections

RL.CAMERA_PERSPECTIVE=0
RL.CAMERA_ORTHOGRAPHIC=1

-- Globals - N-patchLayout

RL.NPATCH_NINE_PATCH=0
RL.NPATCH_THREE_PATCH_VERTICAL=1
RL.NPATCH_THREE_PATCH_HORIZONTAL=2

-- Globals - Colors

RL.LIGHTGRAY={200,200,200,255}
RL.GRAY={130,130,130,255}
RL.DARKGRAY={80,80,80,255}
RL.YELLOW={253,249,0,255}
RL.GOLD={255,203,0,255}
RL.ORANGE={255,161,0,255}
RL.PINK={255,109,194,255}
RL.RED={230,41,55,255}
RL.MAROON={190,33,55,255}
RL.GREEN={0,228,48,255}
RL.LIME={0,158,47,255}
RL.DARKGREEN={0,117,44,255}
RL.SKYBLUE={102,191,255,255}
RL.BLUE={0,121,241,255}
RL.DARKBLUE={0,82,172,255}
RL.PURPLE={200,122,255,255}
RL.VIOLET={135,60,190,255}
RL.DARKPURPLE={112,31,126,255}
RL.BEIGE={211,176,131,255}
RL.BROWN={127,106,79,255}
RL.DARKBROWN={76,63,47,255}
RL.WHITE={255,255,255,255}
RL.BLACK={0,0,0,255}
RL.BLANK={0,0,0,0}
RL.MAGENTA={255,0,255,255}
RL.RAYWHITE={245,245,245,255}

-- Globals - Math

RL.PI=3.1415927410126
RL.DEG2RAD=0.017453292384744
RL.RAD2DEG=57.295776367188

-- Globals - GuiControlState

RL.STATE_NORMAL=0
RL.STATE_FOCUSED=1
RL.STATE_PRESSED=2
RL.STATE_DISABLED=3

-- Globals - GuiTextAlignment

RL.TEXT_ALIGN_LEFT=0
RL.TEXT_ALIGN_CENTER=1
RL.TEXT_ALIGN_RIGHT=2

-- Globals - GuiControl

RL.DEFAULT=0
RL.LABEL=1
RL.BUTTON=2
RL.TOGGLE=3
RL.SLIDER=4
RL.PROGRESSBAR=5
RL.CHECKBOX=6
RL.COMBOBOX=7
RL.DROPDOWNBOX=8
RL.TEXTBOX=9
RL.VALUEBOX=10
RL.SPINNER=11
RL.LISTVIEW=12
RL.COLORPICKER=13
RL.SCROLLBAR=14
RL.STATUSBAR=15

-- Globals - GuiControlProperty

RL.BORDER_COLOR_NORMAL=0
RL.BASE_COLOR_NORMAL=1
RL.TEXT_COLOR_NORMAL=2
RL.BORDER_COLOR_FOCUSED=3
RL.BASE_COLOR_FOCUSED=4
RL.TEXT_COLOR_FOCUSED=5
RL.BORDER_COLOR_PRESSED=6
RL.BASE_COLOR_PRESSED=7
RL.TEXT_COLOR_PRESSED=8
RL.BORDER_COLOR_DISABLED=9
RL.BASE_COLOR_DISABLED=10
RL.TEXT_COLOR_DISABLED=11
RL.BORDER_WIDTH=12
RL.TEXT_PADDING=13
RL.TEXT_ALIGNMENT=14
RL.RESERVED=15

-- Globals - GuiDefaultProperty

RL.TEXT_SIZE=16
RL.TEXT_SPACING=17
RL.LINE_COLOR=18
RL.BACKGROUND_COLOR=19

-- Globals - GuiToggleProperty

RL.GROUP_PADDING=16

-- Globals - GuiSliderProperty

RL.SLIDER_WIDTH=16
RL.SLIDER_PADDING=17

-- Globals - GuiProgressBarProperty

RL.PROGRESS_PADDING=16

-- Globals - GuiScrollBarProperty

RL.ARROWS_SIZE=16
RL.ARROWS_VISIBLE=17
RL.SCROLL_SLIDER_PADDING=18
RL.SCROLL_SLIDER_SIZE=19
RL.SCROLL_PADDING=20
RL.SCROLL_SPEED=21

-- Globals - GuiCheckBoxProperty

RL.CHECK_PADDING=16

-- Globals - GuiComboBoxProperty

RL.COMBO_BUTTON_WIDTH=16
RL.COMBO_BUTTON_SPACING=17

-- Globals - GuiDropdownBoxProperty

RL.ARROW_PADDING=16
RL.DROPDOWN_ITEMS_SPACING=17

-- Globals - GuiTextBoxProperty

RL.TEXT_INNER_PADDING=16
RL.TEXT_LINES_SPACING=17

-- Globals - GuiSpinnerProperty

RL.SPIN_BUTTON_WIDTH=16
RL.SPIN_BUTTON_SPACING=17

-- Globals - GuiListViewProperty

RL.LIST_ITEMS_HEIGHT=16
RL.LIST_ITEMS_SPACING=17
RL.SCROLLBAR_WIDTH=18
RL.SCROLLBAR_SIDE=19

-- Globals - GuiColorPickerProperty

RL.COLOR_SELECTOR_SIZE=16
RL.HUEBAR_WIDTH=17
RL.HUEBAR_PADDING=18
RL.HUEBAR_SELECTOR_HEIGHT=19
RL.HUEBAR_SELECTOR_OVERFLOW=20

-- Globals - LightType

RL.LIGHT_DIRECTIONAL=0
RL.LIGHT_POINT=1

-- Globals - RLGL

RL.RL_DEFAULT_BATCH_BUFFER_ELEMENTS=8192
RL.RL_DEFAULT_BATCH_BUFFERS=1
RL.RL_DEFAULT_BATCH_DRAWCALLS=256
RL.RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS=4

-- Globals - RLGL

RL.RL_MAX_MATRIX_STACK_SIZE=32

-- Globals - RLGL

RL.RL_MAX_SHADER_LOCATIONS=32

-- Globals - RLGL

RL.RL_CULL_DISTANCE_NEAR=0.01
RL.RL_CULL_DISTANCE_FAR=1000.0

-- Globals - RLGL

RL.RL_TEXTURE_WRAP_S=10242
RL.RL_TEXTURE_WRAP_T=10243
RL.RL_TEXTURE_MAG_FILTER=10240
RL.RL_TEXTURE_MIN_FILTER=10241
RL.RL_TEXTURE_FILTER_NEAREST=9728
RL.RL_TEXTURE_FILTER_LINEAR=9729
RL.RL_TEXTURE_FILTER_MIP_NEAREST=9984
RL.RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR=9986
RL.RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST=9985
RL.RL_TEXTURE_FILTER_MIP_LINEAR=9987
RL.RL_TEXTURE_FILTER_ANISOTROPIC=12288
RL.RL_TEXTURE_MIPMAP_BIAS_RATIO=16384
RL.RL_TEXTURE_WRAP_REPEAT=10497
RL.RL_TEXTURE_WRAP_CLAMP=33071
RL.RL_TEXTURE_WRAP_MIRROR_REPEAT=33648
RL.RL_TEXTURE_WRAP_MIRROR_CLAMP=34626

-- Globals - RLGL

RL.RL_MODELVIEW=5888
RL.RL_PROJECTION=5889
RL.RL_TEXTURE=5890

-- Globals - RLGL

RL.RL_LINES=1
RL.RL_TRIANGLES=4
RL.RL_QUADS=7

-- Globals - RLGL

RL.RL_UNSIGNED_BYTE=5121
RL.RL_FLOAT=5126

-- Globals - RLGL

RL.RL_STREAM_DRAW=35040
RL.RL_STREAM_READ=35041
RL.RL_STREAM_COPY=35042
RL.RL_STATIC_DRAW=35044
RL.RL_STATIC_READ=35045
RL.RL_STATIC_COPY=35046
RL.RL_DYNAMIC_DRAW=35048
RL.RL_DYNAMIC_READ=35049
RL.RL_DYNAMIC_COPY=35050

-- Globals - RLGL

RL.RL_FRAGMENT_SHADER=35632
RL.RL_VERTEX_SHADER=35633
RL.RL_COMPUTE_SHADER=37305

-- Globals - RLGL

RL.RL_ZERO=0
RL.RL_ONE=1
RL.RL_SRC_COLOR=768
RL.RL_ONE_MINUS_SRC_COLOR=769
RL.RL_SRC_ALPHA=770
RL.RL_ONE_MINUS_SRC_ALPHA=771
RL.RL_DST_ALPHA=772
RL.RL_ONE_MINUS_DST_ALPHA=773
RL.RL_DST_COLOR=774
RL.RL_ONE_MINUS_DST_COLOR=775
RL.RL_SRC_ALPHA_SATURATE=776
RL.RL_CONSTANT_COLOR=32769
RL.RL_ONE_MINUS_CONSTANT_COLOR=32770
RL.RL_CONSTANT_ALPHA=32771
RL.RL_ONE_MINUS_CONSTANT_ALPHA=32772

-- Globals - RLGL

RL.RL_FUNC_ADD=32774
RL.RL_MIN=32775
RL.RL_MAX=32776
RL.RL_FUNC_SUBTRACT=32778
RL.RL_FUNC_REVERSE_SUBTRACT=32779
RL.RL_BLEND_EQUATION=32777
RL.RL_BLEND_EQUATION_RGB=32777
RL.RL_BLEND_EQUATION_ALPHA=34877
RL.RL_BLEND_DST_RGB=32968
RL.RL_BLEND_SRC_RGB=32969
RL.RL_BLEND_DST_ALPHA=32970
RL.RL_BLEND_SRC_ALPHA=32971
RL.RL_BLEND_COLOR=32773

-- Globals - RLGL

RL.RL_OPENGL_11=1
RL.RL_OPENGL_21=2
RL.RL_OPENGL_33=3
RL.RL_OPENGL_43=4
RL.RL_OPENGL_ES_20=5

-- Globals - RLGL

RL.RL_ATTACHMENT_COLOR_CHANNEL0=0
RL.RL_ATTACHMENT_COLOR_CHANNEL1=1
RL.RL_ATTACHMENT_COLOR_CHANNEL2=2
RL.RL_ATTACHMENT_COLOR_CHANNEL3=3
RL.RL_ATTACHMENT_COLOR_CHANNEL4=4
RL.RL_ATTACHMENT_COLOR_CHANNEL5=5
RL.RL_ATTACHMENT_COLOR_CHANNEL6=6
RL.RL_ATTACHMENT_COLOR_CHANNEL7=7
RL.RL_ATTACHMENT_DEPTH=100
RL.RL_ATTACHMENT_STENCIL=200

-- Globals - RLGL

RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_X=0
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_X=1
RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_Y=2
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y=3
RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_Z=4
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z=5
RL.RL_ATTACHMENT_TEXTURE2D=100
RL.RL_ATTACHMENT_RENDERBUFFER=200

-- Globals - RLGL

RL.RL_CULL_FACE_FRONT=0
RL.RL_CULL_FACE_BACK=1

-- Globals - OpenGL

RL.GL_COLOR_BUFFER_BIT=16384
RL.GL_DEPTH_BUFFER_BIT=256
RL.GL_STENCIL_BUFFER_BIT=1024
RL.GL_NEAREST=9728
RL.GL_LINEAR=9729

-- Globals - GLFW

RL.GLFW_RELEASE=0
RL.GLFW_PRESS=1
RL.GLFW_REPEAT=2

-- Globals - CBuffer

RL.BUFFER_UNSIGNED_CHAR=0
RL.BUFFER_UNSIGNED_SHORT=1
RL.BUFFER_UNSIGNED_INT=2
RL.BUFFER_FLOAT=3

-- Globals - Window

RL.EVENT_WINDOW_SIZE=0
RL.EVENT_WINDOW_MAXIMIZE=1
RL.EVENT_WINDOW_ICONYFY=2
RL.EVENT_WINDOW_FOCUS=3
RL.EVENT_WINDOW_DROP=4

-- Globals - Input

RL.EVENT_KEY=5
RL.EVENT_CHAR=6
RL.EVENT_MOUSE_BUTTON=7
RL.EVENT_MOUSE_CURSOR_POS=8
RL.EVENT_MOUSE_SCROLL=9
RL.EVENT_CURSOR_ENTER=10
-- Core - Window

---Check if window has been initialized successfully
---- Success return bool
---@return any state 
function RL.IsWindowReady() end

---Check if window is currently fullscreen
---- Success return bool
---@return any state 
function RL.IsWindowFullscreen() end

---Check if window is currently hidden (only PLATFORM_DESKTOP)
---- Success return bool
---@return any state 
function RL.IsWindowHidden() end

---Check if window is currently minimized (only PLATFORM_DESKTOP)
---- Success return bool
---@return any state 
function RL.IsWindowMinimized() end

---Check if window is currently maximized (only PLATFORM_DESKTOP)
---- Success return bool
---@return any state 
function RL.IsWindowMaximized() end

---Check if window is currently focused (only PLATFORM_DESKTOP)
---- Success return bool
---@return any state 
function RL.IsWindowFocused() end

---Set monitor for the current window (fullscreen mode)
---@param monitor integer
---@return any RL.SetWindowMonitor
function  RL.SetWindowMonitor( monitor ) end

---Set window position on screen
---@param pos table
---@return any RL.SetWindowPosition
function  RL.SetWindowPosition( pos ) end

---Set window dimensions
---@param size table
---@return any RL.SetWindowSize
function  RL.SetWindowSize( size ) end

---Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
---@param size table
---@return any RL.SetWindowMinSize
function  RL.SetWindowMinSize( size ) end

---Get specified monitor position
---- Success return Vector2
---@param monitor integer
---@return any position 
function RL.GetMonitorPosition( monitor ) end

---Get specified monitor size
---- Success return Vector2
---@param monitor integer
---@return any size 
function RL.GetMonitorSize( monitor ) end

---Get window position on monitor
---- Success return Vector2
---@return any position 
function RL.GetWindowPosition() end

---Get screen size
---- Success return Vector2
---@return any size 
function RL.GetScreenSize() end

---Set window configuration state using flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---@param flag integer
---@return any RL.SetWindowState
function  RL.SetWindowState( flag ) end

---Check if one specific window flag is enabled (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---- Success return bool
---@param flag integer
---@return any state 
function RL.IsWindowState( flag ) end

---Clear window configuration state flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---- Success return bool
---@param flag integer
---@return any resized 
function RL.ClearWindowState( flag ) end

---Check if window has been resized from last frame
---- Success return bool
---@return any resized 
function RL.IsWindowResized() end

---Set icon for window (Only PLATFORM_DESKTOP)
---@param image any
---@return any RL.SetWindowIcon
function  RL.SetWindowIcon( image ) end

---Set title for window (Only PLATFORM_DESKTOP)
---@param title string
---@return any RL.SetWindowTitle
function  RL.SetWindowTitle( title ) end

---Get number of connected monitors
---- Success return int
---@return any count 
function RL.GetMonitorCount() end

---Get current connected monitor
---- Success return int
---@return any monitor 
function RL.GetCurrentMonitor() end

---Get specified monitor physical size in millimetres
---- Success return Vector2
---@param monitor integer
---@return any size 
function RL.GetMonitorPhysicalSize( monitor ) end

---Get specified monitor refresh rate
---- Success return int
---@param monitor integer
---@return any refreshRate 
function RL.GetMonitorRefreshRate( monitor ) end

---Get window scale DPI factor
---- Success return Vector2
---@return any dpi 
function RL.GetWindowScaleDPI() end

---Get the human-readable, UTF-8 encoded name of the monitor
---- Success return string
---@param monitor integer
---@return any name 
function RL.GetMonitorName( monitor ) end

---Close window and unload OpenGL context and free all resources
---@return any RL.CloseWindow
function  RL.CloseWindow() end

---Set clipboard text content
---@param text string
---@return any RL.SetClipboardText
function  RL.SetClipboardText( text ) end

---Get clipboard text content
---- Success return string
---@return any text 
function RL.GetClipboardText() end

-- Core - Timing

---Set target FPS (maximum)
---@param fps integer
---@return any RL.SetTargetFPS
function  RL.SetTargetFPS( fps ) end

---Get current FPS
---- Success return int
---@return any FPS 
function RL.GetFPS() end

---Get time in seconds for last frame drawn (Delta time)
---- Success return float
---@return any delta 
function RL.GetFrameTime() end

---Get elapsed time in seconds since InitWindow()
---- Success return float
---@return any time 
function RL.GetTime() end

-- Core - Misc

---Takes a screenshot of current screen (filename extension defines format)
---@param fileName string
---@return any RL.TakeScreenshot
function  RL.TakeScreenshot( fileName ) end

---Setup init configuration flags (view FLAGS)
---@param flags integer
---@return any RL.SetConfigFlags
function  RL.SetConfigFlags( flags ) end

---Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
---@param logLevel integer
---@param text string
---@return any RL.TraceLog
function  RL.TraceLog( logLevel, text ) end

---Set the current threshold (minimum) log level
---@param logLevel integer
---@return any RL.SetTraceLogLevel
function  RL.SetTraceLogLevel( logLevel ) end

---Set the log level for bad function calls and invalid data formats.
---@param logLevel integer
---@return any RL.SetLogLevelInvalid
function  RL.SetLogLevelInvalid( logLevel ) end

---Get the log level for bad function calls and invalid data formats.
---- Success return int
---@return any logLevel 
function RL.GetLogLevelInvalid() end

---Open URL with default system browser (If available)
---@param url string
---@return any RL.OpenURL
function  RL.OpenURL( url ) end

---Creates buffer as userdata. Type should be one of the Buffer types
---- Success return Buffer
---@param buffer any
---@param type integer
---@return any buffer 
function RL.LoadBuffer( buffer, type ) end

-- Core - Cursor

---Shows cursor
---@return any RL.ShowCursor
function  RL.ShowCursor() end

---Hides cursor
---@return any RL.HideCursor
function  RL.HideCursor() end

---Check if cursor is not visible
---- Success return bool
---@return any hidden 
function RL.IsCursorHidden() end

---Enables cursor (unlock cursor)
---@return any RL.EnableCursor
function  RL.EnableCursor() end

---Disables cursor (lock cursor)
---@return any RL.DisableCursor
function  RL.DisableCursor() end

---Check if cursor is on the screen
---- Success return bool
---@return any onSreen 
function RL.IsCursorOnScreen() end

-- Core - Drawing

---Set background color (framebuffer clear color)
---@param color table
---@return any RL.ClearBackground
function  RL.ClearBackground( color ) end

---Setup canvas (framebuffer) to start drawing
---@return any RL.BeginDrawing
function  RL.BeginDrawing() end

---End canvas drawing and swap buffers (double buffering)
---@return any RL.EndDrawing
function  RL.EndDrawing() end

---Begin blending mode (BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED...)
---@param mode integer
---@return any RL.BeginBlendMode
function  RL.BeginBlendMode( mode ) end

---End blending mode (reset to default: BLEND_ALPHA)
---@return any RL.EndBlendMode
function  RL.EndBlendMode() end

---Begin scissor mode (define screen area for following drawing)
---@param rectange table
---@return any RL.BeginScissorMode
function  RL.BeginScissorMode( rectange ) end

---End scissor mode
---@return any RL.EndScissorMode
function  RL.EndScissorMode() end

-- Core - Shader

---Load shader from files and bind default locations.
---NOTE: Set nil if no shader
---- Failure return nil
---- Success return Shader
---@param vsFileName string
---@param fsFileName string
---@return any shader 
function RL.LoadShader( vsFileName, fsFileName ) end

---Load shader from code strings and bind default locations
---NOTE: Set nil if no shader
---- Failure return nil
---- Success return Shader
---@param vsCode string
---@param fsCode string
---@return any shader 
function RL.LoadShaderFromMemory( vsCode, fsCode ) end

---Begin custom shader drawing
---@param shader any
---@return any RL.BeginShaderMode
function  RL.BeginShaderMode( shader ) end

---End custom shader drawing (use default shader)
---@return any RL.EndShaderMode
function  RL.EndShaderMode() end

---Get shader uniform location
---- Success return int
---@param shader any
---@param uniformName string
---@return any location 
function RL.GetShaderLocation( shader, uniformName ) end

---Get shader attribute location
---- Success return int
---@param shader any
---@param attribName string
---@return any location 
function RL.GetShaderLocationAttrib( shader, attribName ) end

---Set shader location index
---@param shader any
---@param shaderLocationIndex integer
---@param location integer
---@return any RL.SetShaderLocationIndex
function  RL.SetShaderLocationIndex( shader, shaderLocationIndex, location ) end

---Get shader location index
---- Success return int
---@param shader any
---@param shaderLocationIndex integer
---@return any location 
function RL.GetShaderLocationIndex( shader, shaderLocationIndex ) end

---Set shader uniform value (matrix 4x4)
---@param shader any
---@param locIndex integer
---@param mat table
---@return any RL.SetShaderValueMatrix
function  RL.SetShaderValueMatrix( shader, locIndex, mat ) end

---Set shader uniform value for texture (sampler2d)
---@param shader any
---@param locIndex integer
---@param texture any
---@return any RL.SetShaderValueTexture
function  RL.SetShaderValueTexture( shader, locIndex, texture ) end

---Set shader uniform value
---NOTE: Even one value should be in table
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@return any RL.SetShaderValue
function  RL.SetShaderValue( shader, locIndex, values, uniformType ) end

---Set shader uniform value vector
---NOTE: Even one value should be in table
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@param count integer
---@return any RL.SetShaderValueV
function  RL.SetShaderValueV( shader, locIndex, values, uniformType, count ) end

-- Core - Input-related Keyboard

---Detect if a key has been pressed once
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyPressed( key ) end

---Detect if a key is being pressed
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyDown( key ) end

---Detect if a key has been released once
---- Success return bool
---@param key integer
---@return any released 
function RL.IsKeyReleased( key ) end

---Check if a key is NOT being pressed
---- Success return bool
---@param key integer
---@return any released 
function RL.IsKeyUp( key ) end

---Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
---- Success return int
---@return any keycode 
function RL.GetKeyPressed() end

---Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
---- Success return int
---@return any unicode 
function RL.GetCharPressed() end

---Set a custom key to exit program (default is ESC)
---@param key integer
---@return any RL.SetExitKey
function  RL.SetExitKey( key ) end

---This function returns the name of the specified printable key, encoded as UTF-8.
---This is typically the character that key would produce without any modifier keys,
---intended for displaying key bindings to the user. For dead keys, it is typically
---the diacritic it would add to a character.
---Do not use this function for text input. You will break text input for many
---languages even if it happens to work for yours.
---If the key is KEY_UNKNOWN, the scancode is used to identify the key,
---otherwise the scancode is ignored. If you specify a non-printable key,
---or KEY_UNKNOWN and a scancode that maps to a non-printable key,
---this function returns nil but does not emit an error.
---- Success return string or nil
---@param key integer
---@param scancode integer
---@return any keyName 
function RL.GetKeyName( key, scancode ) end

---This function returns the platform-specific scancode of the specified key.
---If the key is KEY_UNKNOWN or does not exist on the keyboard this method will return -1.
---- Success return int
---@param key integer
---@return any scancode 
function RL.GetKeyScancode( key ) end

-- Core - Input-related Gamepad

---Detect if a gamepad is available
---- Success return bool
---@param gamepad integer
---@return any available 
function RL.IsGamepadAvailable( gamepad ) end

---Detect if a gamepad button has been pressed once
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any pressed 
function RL.IsGamepadButtonPressed( gamepad, button ) end

---Detect if a gamepad button is being pressed
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any pressed 
function RL.IsGamepadButtonDown( gamepad, button ) end

---Detect if a gamepad button has been released once
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any released 
function RL.IsGamepadButtonReleased( gamepad, button ) end

---Return gamepad axis count for a gamepad
---- Success return int
---@param gamepad integer
---@return any count 
function RL.GetGamepadAxisCount( gamepad ) end

---Return axis movement value for a gamepad axis
---- Success return float
---@param gamepad integer
---@param axis integer
---@return any value 
function RL.GetGamepadAxisMovement( gamepad, axis ) end

---Return gamepad internal name id
---- Success return string
---@param gamepad integer
---@return any name 
function RL.GetGamepadName( gamepad ) end

-- Core - Input-related Mouse

---Detect if a mouse button has been pressed once
---- Success return bool
---@param button integer
---@return any pressed 
function RL.IsMouseButtonPressed( button ) end

---Detect if a mouse button is being pressed
---- Success return bool
---@param button integer
---@return any pressed 
function RL.IsMouseButtonDown( button ) end

---Detect if a mouse button has been released once
---- Success return bool
---@param button integer
---@return any released 
function RL.IsMouseButtonReleased( button ) end

---Check if a mouse button is NOT being pressed
---- Success return bool
---@param button integer
---@return any released 
function RL.IsMouseButtonUp( button ) end

---Returns mouse position
---- Success return Vector2
---@return any position 
function RL.GetMousePosition() end

---Get mouse delta between frames
---- Success return Vector2
---@return any position 
function RL.GetMouseDelta() end

---Set mouse position XY
---@param position table
---@return any RL.SetMousePosition
function  RL.SetMousePosition( position ) end

---Set mouse offset
---@param offset table
---@return any RL.SetMouseOffset
function  RL.SetMouseOffset( offset ) end

---Set mouse scaling
---@param scale table
---@return any RL.SetMouseScale
function  RL.SetMouseScale( scale ) end

---Returns mouse wheel movement Y
---- Success return float
---@return any movement 
function RL.GetMouseWheelMove() end

---Set mouse cursor
---@param cursor integer
---@return any RL.SetMouseCursor
function  RL.SetMouseCursor( cursor ) end

-- Core - Input-related Touch

---Get touch position XY for a touch point index (relative to screen size)
---- Success return Vector2
---@param index integer
---@return any position 
function RL.GetTouchPosition( index ) end

---Get touch point identifier for given index
---- Success return int
---@param index integer
---@return any id 
function RL.GetTouchPointId( index ) end

---Get touch point identifier for given index
---- Success return int
---@return any count 
function RL.GetTouchPointCount() end

-- Core - Input-related Gestures

---Enable a set of gestures using flags
---@param int any
---@return any RL.SetGesturesEnabled
function  RL.SetGesturesEnabled( int ) end

---Check if a gesture have been detected
---- Success return bool
---@param gesture integer
---@return any detected 
function RL.IsGestureDetected( gesture ) end

---Get latest detected gesture
---- Success return int
---@return any gesture 
function RL.GetGestureDetected() end

---Get gesture hold time in milliseconds
---- Success return float
---@return any time 
function RL.GetGestureHoldDuration() end

---Get gesture drag vector
---- Success return Vector2
---@return any vector 
function RL.GetGestureDragVector() end

---Get gesture drag angle
---- Success return float
---@return any angle 
function RL.GetGestureDragAngle() end

---Get gesture pinch delta
---- Success return Vector2
---@return any vector 
function RL.GetGesturePinchVector() end

---Get gesture pinch angle
---- Success return float
---@return any angle 
function RL.GetGesturePinchAngle() end

-- Core - File

---Return game directory (where main.lua is located)
---- Success return string
---@return any path 
function RL.GetBasePath() end

---Check if file exists
---- Success return bool
---@param fileName string
---@return any fileExists 
function RL.FileExists( fileName ) end

---Check if a directory path exists
---- Success return bool
---@param dirPath string
---@return any dirExists 
function RL.DirectoryExists( dirPath ) end

---Check file extension (Including point: .png, .wav)
---- Success return bool
---@param fileName string
---@param ext string
---@return any hasFileExtension 
function RL.IsFileExtension( fileName, ext ) end

---Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
---- Success return int
---@param fileName string
---@return any length 
function RL.GetFileLength( fileName ) end

---Get pointer to extension for a filename string (Includes dot: '.png')
---- Success return string
---@param fileName string
---@return any extension 
function RL.GetFileExtension( fileName ) end

---Get pointer to filename for a path string
---- Success return string
---@param filePath string
---@return any fileName 
function RL.GetFileName( filePath ) end

---Get filename string without extension (Uses static string)
---- Success return string
---@param filePath string
---@return any fileName 
function RL.GetFileNameWithoutExt( filePath ) end

---Get full path for a given fileName with path (Uses static string)
---- Success return string
---@param filePath string
---@return any filePath 
function RL.GetDirectoryPath( filePath ) end

---Get previous directory path for a given path (Uses static string)
---- Success return string
---@param dirPath string
---@return any directory 
function RL.GetPrevDirectoryPath( dirPath ) end

---Get current working directory (Uses static string)
---- Success return string
---@return any directory 
function RL.GetWorkingDirectory() end

---Load directory filepaths
---- Success return string{}
---@param dirPath string
---@return any fileNames 
function RL.LoadDirectoryFiles( dirPath ) end

---Load directory filepaths with extension filtering and recursive directory scan
---- Success return string{}
---@param basePath string
---@param filter string
---@param scanSubdirs boolean
---@return any fileNames 
function RL.LoadDirectoryFilesEx( basePath, filter, scanSubdirs ) end

---Change working directory, return true on success
---- Success return bool
---@param directory string
---@return any success 
function RL.ChangeDirectory( directory ) end

---Check if a given path is a file or a directory
---- Success return bool
---@param path string
---@return any isFile 
function RL.IsPathFile( path ) end

---Check if a file has been dropped into window
---- Success return bool
---@return any iSFileDropped 
function RL.IsFileDropped() end

---Load dropped filepaths
---- Success return string{}
---@return any files 
function RL.LoadDroppedFiles() end

---Get file modification time (Last write time)
---- Success return int
---@param fileName string
---@return any time 
function RL.GetFileModTime( fileName ) end

-- Core - Camera2D

---Return camera2D set to default configuration
---- Success return Camera2D
---@return any camera2D 
function RL.CreateCamera2D() end

---Begin 2D mode with custom camera (2D)
---@param camera any
---@return any RL.BeginMode2D
function  RL.BeginMode2D( camera ) end

---Ends 2D mode with custom camera
---@return any RL.EndMode2D
function  RL.EndMode2D() end

---Set camera target (rotation and zoom origin)
---@param camera any
---@param target table
---@return any RL.SetCamera2DTarget
function  RL.SetCamera2DTarget( camera, target ) end

---Set camera offset (displacement from target)
---@param camera any
---@param offset table
---@return any RL.SetCamera2DOffset
function  RL.SetCamera2DOffset( camera, offset ) end

---Set camera rotation in degrees
---@param camera any
---@param rotation number
---@return any RL.SetCamera2DRotation
function  RL.SetCamera2DRotation( camera, rotation ) end

---Set camera zoom (scaling), should be 1.0f by default
---@param camera any
---@param zoom number
---@return any RL.SetCamera2DZoom
function  RL.SetCamera2DZoom( camera, zoom ) end

---Get camera2D target
---- Success return Vector2
---@param camera any
---@return any target 
function RL.GetCamera2DTarget( camera ) end

---Get camera2D offset
---- Success return Vector2
---@param camera any
---@return any offset 
function RL.GetCamera2DOffset( camera ) end

---Get camera2D rotation
---- Success return float
---@param camera any
---@return any rotation 
function RL.GetCamera2DRotation( camera ) end

---Get camera2D zoom
---- Success return float
---@param camera any
---@return any zoom 
function RL.GetCamera2DZoom( camera ) end

-- Core - Camera3D

---Return camera3D id set to default configuration
---- Success return int
---@return any camera 
function RL.CreateCamera3D() end

---Begin 3D mode with custom camera (3D)
---@param camera any
---@return any RL.BeginMode3D
function  RL.BeginMode3D( camera ) end

---Ends 3D mode and returns to default 2D orthographic mode
---@return any RL.EndMode3D
function  RL.EndMode3D() end

---Set camera position (Remember to call "RL.UpdateCamera3D()" to apply changes)
---@param camera any
---@param position table
---@return any RL.SetCamera3DPosition
function  RL.SetCamera3DPosition( camera, position ) end

---Set camera target it looks-at
---@param camera any
---@param target table
---@return any RL.SetCamera3DTarget
function  RL.SetCamera3DTarget( camera, target ) end

---Set camera up vector (Rotation over it's axis)
---@param camera any
---@param up table
---@return any RL.SetCamera3DUp
function  RL.SetCamera3DUp( camera, up ) end

---Set camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
---@param camera any
---@param fovy number
---@return any RL.SetCamera3DFovy
function  RL.SetCamera3DFovy( camera, fovy ) end

---Set camera projection mode (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC)
---@param camera any
---@param projection integer
---@return any RL.SetCamera3DProjection
function  RL.SetCamera3DProjection( camera, projection ) end

---Get camera position
---- Success return Vector3
---@param camera any
---@return any position 
function RL.GetCamera3DPosition( camera ) end

---Get camera target it looks-at
---- Success return Vector3
---@param camera any
---@return any target 
function RL.GetCamera3DTarget( camera ) end

---Get camera up vector (Rotation over it's axis)
---- Success return Vector3
---@param camera any
---@return any up 
function RL.GetCamera3DUp( camera ) end

---Get camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
---- Success return float
---@param camera any
---@return any fovy 
function RL.GetCamera3DFovy( camera ) end

---Get camera projection mode
---- Success return int
---@param camera any
---@return any projection 
function RL.GetCamera3DProjection( camera ) end

---Returns the cameras forward vector (normalized)
---- Success return Vector3
---@param camera any
---@return any forward 
function RL.GetCamera3DForward( camera ) end

---Returns the cameras up vector (normalized)
---Note: The up vector might not be perpendicular to the forward vector
---- Success return Vector3
---@param camera any
---@return any up 
function RL.GetCamera3DUpNormalized( camera ) end

---Returns the cameras right vector (normalized)
---- Success return Vector3
---@param camera any
---@return any right 
function RL.GetCamera3DRight( camera ) end

---Moves the camera in it's forward direction
---@param camera any
---@param distance number
---@param moveInWorldPlane boolean
---@return any RL.Camera3DMoveForward
function  RL.Camera3DMoveForward( camera, distance, moveInWorldPlane ) end

---Moves the camera in it's up direction
---@param camera any
---@param distance number
---@return any RL.Camera3DMoveUp
function  RL.Camera3DMoveUp( camera, distance ) end

---Moves the camera target in it's current right direction
---@param camera any
---@param distance number
---@param moveInWorldPlane boolean
---@return any RL.Camera3DMoveRight
function  RL.Camera3DMoveRight( camera, distance, moveInWorldPlane ) end

---Moves the camera position closer/farther to/from the camera target
---@param camera any
---@param delta number
---@return any RL.Camera3DMoveToTarget
function  RL.Camera3DMoveToTarget( camera, delta ) end

---Rotates the camera around it's up vector
---Yaw is "looking left and right"
---If rotateAroundTarget is false, the camera rotates around it's position
---Note: angle must be provided in radians
---@param camera any
---@param angle number
---@param rotateAroundTarget boolean
---@return any RL.Camera3DYaw
function  RL.Camera3DYaw( camera, angle, rotateAroundTarget ) end

---Rotates the camera around it's right vector, pitch is "looking up and down"
--- - lockView prevents camera overrotation (aka "somersaults")
--- - rotateAroundTarget defines if rotation is around target or around it's position
--- - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
---NOTE: angle must be provided in radians
---@param camera any
---@param angle number
---@param lockView boolean
---@param rotateAroundTarget boolean
---@param rotateUp boolean
---@return any RL.Camera3DPitch
function  RL.Camera3DPitch( camera, angle, lockView, rotateAroundTarget, rotateUp ) end

---Rotates the camera around it's forward vector
---Roll is "turning your head sideways to the left or right"
---Note: angle must be provided in radians
---@param camera any
---@param angle number
---@return any RL.Camera3DRoll
function  RL.Camera3DRoll( camera, angle ) end

---Returns the camera view matrix
---- Success return Matrix
---@param camera any
---@return any view 
function RL.GetCamera3DViewMatrix( camera ) end

---Returns the camera projection matrix
---- Success return Matrix
---@param camera any
---@param aspect number
---@return any projection 
function RL.GetCamera3DProjectionMatrix( camera, aspect ) end

---Update camera position for selected mode
---@param camera any
---@param mode integer
---@return any RL.UpdateCamera3D
function  RL.UpdateCamera3D( camera, mode ) end

---Update camera movement, movement/rotation values should be provided by user
---@param camera any
---@param movement table
---@param rotation table
---@param zoom number
---@return any RL.UpdateCamera3DPro
function  RL.UpdateCamera3DPro( camera, movement, rotation, zoom ) end

-- Core - Screen-space

---Get a ray trace from mouse position
---- Success return Ray
---@param mousePosition table
---@param camera any
---@return any ray 
function RL.GetMouseRay( mousePosition, camera ) end

---Get camera transform matrix (view matrix)
---- Success return Matrix
---@param camera any
---@return any matrix 
function RL.GetCameraMatrix( camera ) end

---Get camera 2d transform matrix
---- Success return Matrix
---@param camera any
---@return any matrix 
function RL.GetCameraMatrix2D( camera ) end

---Get the screen space position for a 3d world space position
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetWorldToScreen( position, camera ) end

---Get size position for a 3d world space position
---- Success return Vector2
---@param position table
---@param camera any
---@param size table
---@return any position 
function RL.GetWorldToScreenEx( position, camera, size ) end

---Get the screen space position for a 2d camera world space position
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetWorldToScreen2D( position, camera ) end

---Get the world space position for a 2d camera screen space position
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetScreenToWorld2D( position, camera ) end

-- Shapes - Drawing

---Set texture and rectangle to be used on shapes drawing
---NOTE: It can be useful when using basic shapes and one single font,
---defining a font char white rectangle would allow drawing everything in a single draw call
---@param texture any
---@param source table
---@return any RL.SetShapesTexture
function  RL.SetShapesTexture( texture, source ) end

---Draw a pixel
---@param pos table
---@param color table
---@return any RL.DrawPixel
function  RL.DrawPixel( pos, color ) end

---Draw a line defining thickness
---@param startPos table
---@param endPos table
---@param thickness number
---@param color table
---@return any RL.DrawLine
function  RL.DrawLine( startPos, endPos, thickness, color ) end

---Draw a line using cubic-bezier curves in-out
---@param startPos table
---@param endPos table
---@param thickness number
---@param color table
---@return any RL.DrawLineBezier
function  RL.DrawLineBezier( startPos, endPos, thickness, color ) end

---Draw line using quadratic bezier curves with a control point
---@param startPos table
---@param endPos table
---@param controlPos table
---@param thickness number
---@param color table
---@return any RL.DrawLineBezierQuad
function  RL.DrawLineBezierQuad( startPos, endPos, controlPos, thickness, color ) end

---Draw line using quadratic bezier curves with a control point
---@param startPos table
---@param endPos table
---@param startControlPos table
---@param endControlPos table
---@param thickness number
---@param color table
---@return any RL.DrawLineBezierCubic
function  RL.DrawLineBezierCubic( startPos, endPos, startControlPos, endControlPos, thickness, color ) end

---Draw lines sequence
---@param points any
---@param color table
---@return any RL.DrawLineStrip
function  RL.DrawLineStrip( points, color ) end

---Draw a color-filled circle
---@param center table
---@param radius number
---@param color table
---@return any RL.DrawCircle
function  RL.DrawCircle( center, radius, color ) end

---Draw a piece of a circle
---@param center table
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any RL.DrawCircleSector
function  RL.DrawCircleSector( center, radius, startAngle, endAngle, segments, color ) end

---Draw circle sector outline
---@param center table
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any RL.DrawCircleSectorLines
function  RL.DrawCircleSectorLines( center, radius, startAngle, endAngle, segments, color ) end

---Draw a gradient-filled circle
---@param center table
---@param radius number
---@param color1 table
---@param color2 table
---@return any RL.DrawCircleGradient
function  RL.DrawCircleGradient( center, radius, color1, color2 ) end

---Draw circle outline
---@param center table
---@param radius number
---@param color table
---@return any RL.DrawCircleLines
function  RL.DrawCircleLines( center, radius, color ) end

---Draw ellipse
---@param center table
---@param radiusH number
---@param radiusV number
---@param color table
---@return any RL.DrawEllipse
function  RL.DrawEllipse( center, radiusH, radiusV, color ) end

---Draw ellipse outline
---@param center table
---@param radiusH number
---@param radiusV number
---@param color table
---@return any RL.DrawEllipseLines
function  RL.DrawEllipseLines( center, radiusH, radiusV, color ) end

---Draw ring
---@param center table
---@param innerRadius number
---@param outerRadius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any RL.DrawRing
function  RL.DrawRing( center, innerRadius, outerRadius, startAngle, endAngle, segments, color ) end

---Draw ring outline
---@param center table
---@param innerRadius number
---@param outerRadius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any RL.DrawRingLines
function  RL.DrawRingLines( center, innerRadius, outerRadius, startAngle, endAngle, segments, color ) end

---Draw a color-filled rectangle
---@param rec table
---@param color table
---@return any RL.DrawRectangle
function  RL.DrawRectangle( rec, color ) end

---Draw a color-filled rectangle with pro parameters
---@param rec table
---@param origin table
---@param rotation number
---@param color table
---@return any RL.DrawRectanglePro
function  RL.DrawRectanglePro( rec, origin, rotation, color ) end

---Draw a vertical-gradient-filled rectangle
---@param rectangle table
---@param color1 table
---@param color2 table
---@return any RL.DrawRectangleGradientV
function  RL.DrawRectangleGradientV( rectangle, color1, color2 ) end

---Draw a horizontal-gradient-filled rectangle
---@param rectangle table
---@param color1 table
---@param color2 table
---@return any RL.DrawRectangleGradientH
function  RL.DrawRectangleGradientH( rectangle, color1, color2 ) end

---Draw a gradient-filled rectangle with custom vertex colors
---@param rectangle table
---@param col1 table
---@param col2 table
---@param col3 table
---@param col4 table
---@return any RL.DrawRectangleGradientEx
function  RL.DrawRectangleGradientEx( rectangle, col1, col2, col3, col4 ) end

---Draw rectangle outline
---@param rec table
---@param color table
---@return any RL.DrawRectangleLines
function  RL.DrawRectangleLines( rec, color ) end

---Draw rectangle outline with extended parameters
---@param rec table
---@param lineThick integer
---@param color table
---@return any RL.DrawRectangleLinesEx
function  RL.DrawRectangleLinesEx( rec, lineThick, color ) end

---Draw rectangle with rounded edges
---@param rec table
---@param roundness number
---@param segments integer
---@param color table
---@return any RL.DrawRectangleRounded
function  RL.DrawRectangleRounded( rec, roundness, segments, color ) end

---Draw rectangle with rounded edges outline
---@param rec table
---@param roundness number
---@param segments integer
---@param lineThick integer
---@param color table
---@return any RL.DrawRectangleRoundedLines
function  RL.DrawRectangleRoundedLines( rec, roundness, segments, lineThick, color ) end

---Draw a color-filled triangle (Vertex in counter-clockwise order!)
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any RL.DrawTriangle
function  RL.DrawTriangle( v1, v2, v3, color ) end

---Draw triangle outline (Vertex in counter-clockwise order!)
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any RL.DrawTriangleLines
function  RL.DrawTriangleLines( v1, v2, v3, color ) end

---Draw a triangle fan defined by points (first vertex is the center)
---@param points any
---@param color table
---@return any RL.DrawTriangleFan
function  RL.DrawTriangleFan( points, color ) end

---Draw a triangle strip defined by points
---@param points any
---@param color table
---@return any RL.DrawTriangleStrip
function  RL.DrawTriangleStrip( points, color ) end

---Draw a regular polygon (Vector version)
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param color table
---@return any RL.DrawPoly
function  RL.DrawPoly( center, sides, radius, rotation, color ) end

---Draw a polygon outline of n sides
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param color table
---@return any RL.DrawPolyLines
function  RL.DrawPolyLines( center, sides, radius, rotation, color ) end

---Draw a polygon outline of n sides with extended parameters
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param lineThick number
---@param color table
---@return any RL.DrawPolyLinesEx
function  RL.DrawPolyLinesEx( center, sides, radius, rotation, lineThick, color ) end

-- Shapes - Collision

---Check collision between two rectangles
---- Success return bool
---@param rec1 table
---@param rec2 table
---@return any collision 
function RL.CheckCollisionRecs( rec1, rec2 ) end

---Check collision between two circles
---- Success return bool
---@param center1 table
---@param radius1 number
---@param center2 table
---@param radius2 number
---@return any collision 
function RL.CheckCollisionCircles( center1, radius1, center2, radius2 ) end

---Check collision between circle and rectangle
---- Success return bool
---@param center table
---@param radius number
---@param rec table
---@return any collision 
function RL.CheckCollisionCircleRec( center, radius, rec ) end

---Check if point is inside rectangle
---- Success return bool
---@param point table
---@param rec table
---@return any collision 
function RL.CheckCollisionPointRec( point, rec ) end

---Check if point is inside circle
---- Success return bool
---@param point table
---@param center table
---@param radius number
---@return any collision 
function RL.CheckCollisionPointCircle( point, center, radius ) end

---Check if point is inside a triangle
---- Success return bool
---@param point table
---@param p1 table
---@param p2 table
---@param p3 table
---@return any collision 
function RL.CheckCollisionPointTriangle( point, p1, p2, p3 ) end

---Check if point is within a polygon described by array of vertices
---- Success return bool
---@param point table
---@param points any
---@return any collision 
function RL.CheckCollisionPointPoly( point, points ) end

---Check the collision between two lines defined by two points each, returns collision point by reference
---- Success return bool, Vector2
---@param startPos1 table
---@param endPos1 table
---@param startPos2 table
---@param endPos2 table
---@return any collision
---@return any position 
function RL.CheckCollisionLines( startPos1, endPos1, startPos2, endPos2 ) end

---Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
---- Success return bool
---@param point table
---@param p1 table
---@param p2 table
---@param threshold integer
---@return any collision 
function RL.CheckCollisionPointLine( point, p1, p2, threshold ) end

---Get collision rectangle for two rectangles collision
---- Success return Rectangle
---@param rec1 table
---@param rec2 table
---@return any rectangle 
function RL.GetCollisionRec( rec1, rec2 ) end

-- Textures - Image Loading

---Load image from file into CPU memory (RAM)
---- Success return Image
---@param fileName string
---@return any image 
function RL.LoadImage( fileName ) end

---Load image from GPU texture data
---- Success return Image
---@param texture any
---@return any image 
function RL.LoadImageFromTexture( texture ) end

---Load image from screen buffer and (screenshot)
---- Success return Image
---@return any image 
function RL.LoadImageFromScreen() end

---Export image data to file, returns true on success
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImage( image, fileName ) end

---Export image as code file defining an array of bytes, returns true on success
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImageAsCode( image, fileName ) end

-- Textures - Image Generation

---Generate image: plain color
---- Success return Image
---@param size table
---@param color table
---@return any image 
function RL.GenImageColor( size, color ) end

---Generate image: vertical gradient
---- Success return Image
---@param size table
---@param top table
---@param bottom table
---@return any image 
function RL.GenImageGradientV( size, top, bottom ) end

---Generate image: horizontal gradient
---- Success return Image
---@param size table
---@param left table
---@param right table
---@return any image 
function RL.GenImageGradientH( size, left, right ) end

---Generate image: radial gradient
---- Success return Image
---@param size table
---@param density number
---@param inner table
---@param outer table
---@return any image 
function RL.GenImageGradientRadial( size, density, inner, outer ) end

---Generate image: checked
---- Success return Image
---@param size table
---@param checks table
---@param col1 table
---@param col2 table
---@return any image 
function RL.GenImageChecked( size, checks, col1, col2 ) end

---Generate image: white noise
---- Success return Image
---@param size table
---@param factor number
---@return any image 
function RL.GenImageWhiteNoise( size, factor ) end

---Generate image: perlin noise
---- Success return Image
---@param size table
---@param offset table
---@param factor number
---@return any image 
function RL.GenImagePerlinNoise( size, offset, factor ) end

---Generate image: cellular algorithm. Bigger tileSize means bigger cells
---- Success return Image
---@param size table
---@param tileSize integer
---@return any image 
function RL.GenImageCellular( size, tileSize ) end

---Generate image: grayscale image from text data
---- Success return Image
---@param size table
---@param text string
---@return any image 
function RL.GenImageText( size, text ) end

-- Textures - Image Manipulation Functions

---Create an image duplicate (useful for transformations)
---- Success return Image
---@param image any
---@return any image 
function RL.ImageCopy( image ) end

---Create an image from another image piece
---- Success return Image
---@param image any
---@param rec table
---@return any image 
function RL.ImageFromImage( image, rec ) end

---Create an image from text (custom sprite font)
---- Success return Image
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@param tint table
---@return any image 
function RL.ImageText( font, text, fontSize, spacing, tint ) end

---Convert image data to desired format
---@param image any
---@param newFormat integer
---@return any RL.ImageFormat
function  RL.ImageFormat( image, newFormat ) end

---Convert image to POT (power-of-two)
---@param image any
---@param fill table
---@return any RL.ImageToPOT
function  RL.ImageToPOT( image, fill ) end

---Crop an image to a defined rectangle
---@param image any
---@param crop table
---@return any RL.ImageCrop
function  RL.ImageCrop( image, crop ) end

---Crop image depending on alpha value
---@param image any
---@param threshold number
---@return any RL.ImageAlphaCrop
function  RL.ImageAlphaCrop( image, threshold ) end

---Clear alpha channel to desired color
---@param image any
---@param color table
---@param threshold number
---@return any RL.ImageAlphaClear
function  RL.ImageAlphaClear( image, color, threshold ) end

---Apply alpha mask to image
---@param image any
---@param alphaMask any
---@return any RL.ImageAlphaMask
function  RL.ImageAlphaMask( image, alphaMask ) end

---Premultiply alpha channel
---@param image any
---@return any RL.ImageAlphaPremultiply
function  RL.ImageAlphaPremultiply( image ) end

---Apply Gaussian blur using a box blur approximation
---@param image any
---@param blurSize integer
---@return any RL.ImageBlurGaussian
function  RL.ImageBlurGaussian( image, blurSize ) end

---Resize image (Bicubic scaling algorithm)
---@param image any
---@param size table
---@return any RL.ImageResize
function  RL.ImageResize( image, size ) end

---Resize image (Nearest-Neighbor scaling algorithm)
---@param image any
---@param size table
---@return any RL.ImageResizeNN
function  RL.ImageResizeNN( image, size ) end

---Resize canvas and fill with color
---@param image any
---@param size table
---@param offset table
---@param fill table
---@return any RL.ImageResizeCanvas
function  RL.ImageResizeCanvas( image, size, offset, fill ) end

---Generate all mipmap levels for a provided image
---@param image any
---@return any RL.ImageMipmaps
function  RL.ImageMipmaps( image ) end

---Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
---@param image any
---@param bpp table
---@return any RL.ImageDither
function  RL.ImageDither( image, bpp ) end

---Flip image vertically
---@param image any
---@return any RL.ImageFlipVertical
function  RL.ImageFlipVertical( image ) end

---Flip image horizontally
---@param image any
---@return any RL.ImageFlipHorizontal
function  RL.ImageFlipHorizontal( image ) end

---Rotate image clockwise 90deg
---@param image any
---@return any RL.ImageRotateCW
function  RL.ImageRotateCW( image ) end

---Rotate image counter-clockwise 90deg
---@param image any
---@return any RL.ImageRotateCCW
function  RL.ImageRotateCCW( image ) end

---Modify image color: tint
---@param image any
---@param color table
---@return any RL.ImageColorTint
function  RL.ImageColorTint( image, color ) end

---Modify image color: invert
---@param image any
---@return any RL.ImageColorInvert
function  RL.ImageColorInvert( image ) end

---Modify image color: grayscale
---@param image any
---@return any RL.ImageColorGrayscale
function  RL.ImageColorGrayscale( image ) end

---Modify image color: contrast (-100 to 100)
---@param image any
---@param contrast number
---@return any RL.ImageColorContrast
function  RL.ImageColorContrast( image, contrast ) end

---Modify image color: brightness (-255 to 255)
---@param image any
---@param brightness integer
---@return any RL.ImageColorBrightness
function  RL.ImageColorBrightness( image, brightness ) end

---Modify image color: replace color
---@param image any
---@param color table
---@param replace table
---@return any RL.ImageColorReplace
function  RL.ImageColorReplace( image, color, replace ) end

---Load color data from image as a Color array (RGBA - 32bit)
---- Success return Color{}
---@param image any
---@return any colors 
function RL.LoadImageColors( image ) end

---Load colors palette from image as a Color array (RGBA - 32bit)
---- Success return Color{}
---@param image any
---@param maxPaletteSize integer
---@return any colors 
function RL.LoadImagePalette( image, maxPaletteSize ) end

---Get image alpha border rectangle
---- Success return Rectangle
---@param image any
---@param threshold number
---@return any rectangle 
function RL.GetImageAlphaBorder( image, threshold ) end

---Get image pixel color at (x, y) position
---- Success return Color
---@param image any
---@param pixelPos table
---@return any color 
function RL.GetImageColor( image, pixelPos ) end

-- Textures - Image Drawing

---Clear image background with given color
---@param dst any
---@param color table
---@return any RL.ImageClearBackground
function  RL.ImageClearBackground( dst, color ) end

---Draw pixel within an image
---@param dst any
---@param position table
---@param color table
---@return any RL.ImageDrawPixel
function  RL.ImageDrawPixel( dst, position, color ) end

---Draw line within an image
---@param dst any
---@param a table
---@param b table
---@param color table
---@return any RL.ImageDrawLine
function  RL.ImageDrawLine( dst, a, b, color ) end

---Draw circle within an image
---@param dst any
---@param center table
---@param radius integer
---@param color table
---@return any RL.ImageDrawCircle
function  RL.ImageDrawCircle( dst, center, radius, color ) end

---Draw circle outline within an image
---@param dst any
---@param center table
---@param radius integer
---@param color table
---@return any RL.ImageDrawCircleLines
function  RL.ImageDrawCircleLines( dst, center, radius, color ) end

---Draw rectangle within an image
---@param dst any
---@param rec table
---@param color table
---@return any RL.ImageDrawRectangle
function  RL.ImageDrawRectangle( dst, rec, color ) end

---Draw rectangle lines within an image
---@param dst any
---@param rec table
---@param thick integer
---@param color table
---@return any RL.ImageDrawRectangleLines
function  RL.ImageDrawRectangleLines( dst, rec, thick, color ) end

---Draw a source image within a destination image (Tint applied to source)
---@param dst any
---@param src any
---@param srcRec table
---@param dstRec table
---@param tint table
---@return any RL.ImageDraw
function  RL.ImageDraw( dst, src, srcRec, dstRec, tint ) end

---Draw text (Custom sprite font) within an image (Destination)
---@param dst any
---@param font any
---@param text string
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any RL.ImageDrawTextEx
function  RL.ImageDrawTextEx( dst, font, text, position, fontSize, spacing, tint ) end

-- Textures - Image Configuration

---Get image size
---- Success return Vector2
---@param image any
---@return any size 
function RL.GetImageSize( image ) end

---Get image mipmaps. Mipmap levels, 1 by default
---- Success return int
---@param image any
---@return any mipmaps 
function RL.GetImageMipmaps( image ) end

---Get image data format (PixelFormat type)
---- Success return int
---@param image any
---@return any format 
function RL.GetImageFormat( image ) end

-- Textures - Texture Loading

---Load texture from file into GPU memory ( VRAM )
---- Failure return nil
---- Success return Texture
---@param fileName string
---@return any texture 
function RL.LoadTexture( fileName ) end

---Load texture from image data
---- Success return Texture
---@param image any
---@return any texture 
function RL.LoadTextureFromImage( image ) end

---Load cubemap from image, multiple image cubemap layouts supported
---- Success return Texture
---@param image any
---@param layout integer
---@return any texture 
function RL.LoadTextureCubemap( image, layout ) end

---Load texture for rendering (framebuffer)
---- Success return RenderTexture
---@param size table
---@return any renderTexture 
function RL.LoadRenderTexture( size ) end

---Check if a texture is ready
---- Success return bool
---@param texture any
---@return any isReady 
function RL.IsTextureReady( texture ) end

---Update GPU texture with new data
---NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
---@param texture any
---@param pixels any
---@return any RL.UpdateTexture
function  RL.UpdateTexture( texture, pixels ) end

---Update GPU texture rectangle with new data
---NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
---@param texture any
---@param rec table
---@param pixels any
---@return any RL.UpdateTextureRec
function  RL.UpdateTextureRec( texture, rec, pixels ) end

-- Textures - Texture Drawing

---Draw a Texture2D
---@param texture any
---@param position table
---@param tint table
---@return any RL.DrawTexture
function  RL.DrawTexture( texture, position, tint ) end

---Draw a part of a texture defined by a rectangle
---@param texture any
---@param source table
---@param position table
---@param tint table
---@return any RL.DrawTextureRec
function  RL.DrawTextureRec( texture, source, position, tint ) end

---Draw a part of a texture defined by a rectangle with "pro" parameters
---@param texture any
---@param source table
---@param dest table
---@param origin table
---@param rotation number
---@param tint table
---@return any RL.DrawTexturePro
function  RL.DrawTexturePro( texture, source, dest, origin, rotation, tint ) end

---Draws a texture (or part of it) that stretches or shrinks nicely
---@param texture any
---@param nPatchInfo any
---@param dest table
---@param origin table
---@param rotation number
---@param tint table
---@return any RL.DrawTextureNPatch
function  RL.DrawTextureNPatch( texture, nPatchInfo, dest, origin, rotation, tint ) end

---Begin drawing to render texture
---@param target any
---@return any RL.BeginTextureMode
function  RL.BeginTextureMode( target ) end

---Ends drawing to render texture
---@return any RL.EndTextureMode
function  RL.EndTextureMode() end

-- Textures - Texture Configuration

---Generate GPU mipmaps for a texture
---@param texture any
---@return any RL.GenTextureMipmaps
function  RL.GenTextureMipmaps( texture ) end

---Set texture scaling filter mode (TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR...)
---@param texture any
---@param filter integer
---@return any RL.SetTextureFilter
function  RL.SetTextureFilter( texture, filter ) end

---Set texture wrapping mode (TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP...)
---@param texture any
---@param wrap integer
---@return any RL.SetTextureWrap
function  RL.SetTextureWrap( texture, wrap ) end

---Get OpenGL texture id
---- Success return int
---@param texture any
---@return any id 
function RL.GetTextureId( texture ) end

---Get texture size
---- Success return Vector2
---@param texture any
---@return any size 
function RL.GetTextureSize( texture ) end

---Get texture mipmaps. Mipmap levels, 1 by default
---- Success return int
---@param texture any
---@return any mipmaps 
function RL.GetTextureMipmaps( texture ) end

---Get texture data format (PixelFormat type)
---- Success return int
---@param texture any
---@return any format 
function RL.GetTextureFormat( texture ) end

-- Textures - RenderTexture Configuration

---Get OpenGL framebuffer object id
---- Success return int
---@param renderTexture any
---@return any id 
function RL.GetRenderTextureId( renderTexture ) end

---Get color buffer attachment texture
---- Success return Texture
---@param renderTexture any
---@return any texture 
function RL.GetRenderTextureTexture( renderTexture ) end

---Get depth buffer attachment texture
---- Success return Texture
---@param renderTexture any
---@return any texture 
function RL.GetRenderTextureDepthTexture( renderTexture ) end

-- Textures - Color/pixel

---Returns color with alpha applied, alpha goes from 0.0f to 1.0f
---- Success return Color
---@param color table
---@param alpha number
---@return any color 
function RL.Fade( color, alpha ) end

---Returns hexadecimal value for a Color
---- Success return int
---@param color table
---@return any value 
function RL.ColorToInt( color ) end

---Returns Color normalized as float [0..1]
---- Success return Vector4
---@param color table
---@return any color 
function RL.ColorNormalize( color ) end

---Color from normalized values [0..1]
---- Success return Color
---@param normalized table
---@return any color 
function RL.ColorFromNormalized( normalized ) end

---Returns HSV values for a Color, hue [0..360], saturation/value [0..1]
---- Success return Vector3
---@param color table
---@return any HSV 
function RL.ColorToHSV( color ) end

---Returns a Color from HSV values, hue [0..360], saturation/value [0..1]
---- Success return Color
---@param hue number
---@param saturation number
---@param value number
---@return any color 
function RL.ColorFromHSV( hue, saturation, value ) end

---Get color multiplied with another color
---- Success return Color
---@param color table
---@param tint table
---@return any color 
function RL.ColorTint( color, tint ) end

---Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
---- Success return Color
---@param color table
---@param factor number
---@return any color 
function RL.ColorBrightness( color, factor ) end

---Get color with contrast correction, contrast values between -1.0f and 1.0f
---- Success return Color
---@param color table
---@param contrast number
---@return any color 
function RL.ColorContrast( color, contrast ) end

---Returns color with alpha applied, alpha goes from 0.0f to 1.0f
---- Success return Color
---@param color table
---@param alpha number
---@return any color 
function RL.ColorAlpha( color, alpha ) end

---Returns src alpha-blended into dst color with tint
---- Success return Color
---@param dst table
---@param src table
---@param tint table
---@return any color 
function RL.ColorAlphaBlend( dst, src, tint ) end

---Get Color structure from hexadecimal value
---- Success return Color
---@param hexValue integer
---@return any color 
function RL.GetColor( hexValue ) end

---Get pixel color from source texture
---- Success return Color
---@param texture any
---@param position table
---@return any color 
function RL.GetPixelColor( texture, position ) end

---Get pixel data size in bytes for certain format
---- Success return int
---@param width integer
---@param height integer
---@param format integer
---@return any size 
function RL.GetPixelDataSize( width, height, format ) end

-- Text - Loading

---Get the default Font
---@return any RL.GetFontDefault
function  RL.GetFontDefault() end

---Load font from file into GPU memory (VRAM)
---- Failure return nil
---- Success return Font
---@param fileName string
---@return any font 
function RL.LoadFont( fileName ) end

---Load font from file with extended parameters. Loading the default character set
---- Failure return nil
---- Success return Font
---@param fileName string
---@param fontSize integer
---@param fontChars any
---@return any font 
function RL.LoadFontEx( fileName, fontSize, fontChars ) end

---Load font from Image ( XNA style)
---- Success return Font
---@param image any
---@param key table
---@param firstChar integer
---@return any font 
function RL.LoadFontFromImage( image, key, firstChar ) end

-- Text - Draw

---Draw current FPS
---@param pos table
---@return any RL.DrawFPS
function  RL.DrawFPS( pos ) end

---Draw text using font and additional parameters
---@param font any
---@param text string
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any RL.DrawText
function  RL.DrawText( font, text, position, fontSize, spacing, tint ) end

---Draw text using Font and pro parameters (rotation)
---@param font any
---@param text string
---@param position table
---@param origin table
---@param rotation number
---@param fontSize number
---@param spacing number
---@param tint table
---@return any RL.DrawTextPro
function  RL.DrawTextPro( font, text, position, origin, rotation, fontSize, spacing, tint ) end

-- Text - Misc

---Measure string size for Font
---- Success return Vector2
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@return any size 
function RL.MeasureText( font, text, fontSize, spacing ) end

---Get font base size (default chars height)
---- Success return int
---@param font any
---@return any baseSize 
function RL.GetFontBaseSize( font ) end

---Get font number of glyph characters
---- Success return int
---@param font any
---@return any glyphCount 
function RL.GetFontGlyphCount( font ) end

---Get font padding around the glyph characters
---- Success return int
---@param font any
---@return any glyphPadding 
function RL.GetFontGlyphPadding( font ) end

---Get font texture atlas containing the glyphs.
---- Success return Texture
---@param font any
---@return any texture 
function RL.GetFontTexture( font ) end

-- Models - Basic

---Draw a line in 3D world space
---@param startPos table
---@param endPos table
---@param color table
---@return any RL.DrawLine3D
function  RL.DrawLine3D( startPos, endPos, color ) end

---Draw a point in 3D space, actually a small line
---@param position table
---@param color table
---@return any RL.DrawPoint3D
function  RL.DrawPoint3D( position, color ) end

---Draw a circle in 3D world space
---@param center table
---@param radius number
---@param rotationAxis table
---@param rotationAngle number
---@param color table
---@return any RL.DrawCircle3D
function  RL.DrawCircle3D( center, radius, rotationAxis, rotationAngle, color ) end

---Draw a color-filled triangle (Vertex in counter-clockwise order!)
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any RL.DrawTriangle3D
function  RL.DrawTriangle3D( v1, v2, v3, color ) end

---Draw cube
---@param position table
---@param size table
---@param color table
---@return any RL.DrawCube
function  RL.DrawCube( position, size, color ) end

---Draw cube wires
---@param position table
---@param size table
---@param color table
---@return any RL.DrawCubeWires
function  RL.DrawCubeWires( position, size, color ) end

---Draw sphere
---@param centerPos table
---@param radius number
---@param color table
---@return any RL.DrawSphere
function  RL.DrawSphere( centerPos, radius, color ) end

---Draw sphere with extended parameters
---@param centerPos table
---@param radius number
---@param rings integer
---@param slices integer
---@param color table
---@return any RL.DrawSphereEx
function  RL.DrawSphereEx( centerPos, radius, rings, slices, color ) end

---Draw sphere wires
---@param centerPos table
---@param radius number
---@param rings integer
---@param slices integer
---@param color table
---@return any RL.DrawSphereWires
function  RL.DrawSphereWires( centerPos, radius, rings, slices, color ) end

---Draw a cylinder/cone
---@param position table
---@param radiusTop number
---@param radiusBottom number
---@param height number
---@param slices integer
---@param color table
---@return any RL.DrawCylinder
function  RL.DrawCylinder( position, radiusTop, radiusBottom, height, slices, color ) end

---Draw a cylinder with base at startPos and top at endPos
---@param startPos table
---@param endPos table
---@param startRadius number
---@param endRadius number
---@param sides integer
---@param color table
---@return any RL.DrawCylinderEx
function  RL.DrawCylinderEx( startPos, endPos, startRadius, endRadius, sides, color ) end

---Draw a cylinder/cone wires
---@param position table
---@param radiusTop number
---@param radiusBottom number
---@param height number
---@param slices integer
---@param color table
---@return any RL.DrawCylinderWires
function  RL.DrawCylinderWires( position, radiusTop, radiusBottom, height, slices, color ) end

---Draw a cylinder wires with base at startPos and top at endPos
---@param startPos table
---@param endPos table
---@param startRadius number
---@param endRadius number
---@param sides integer
---@param color table
---@return any RL.DrawCylinderWiresEx
function  RL.DrawCylinderWiresEx( startPos, endPos, startRadius, endRadius, sides, color ) end

---Draw a capsule with the center of its sphere caps at startPos and endPos
---@param startPos table
---@param endPos table
---@param radius number
---@param slices integer
---@param rings integer
---@param color table
---@return any RL.DrawCapsule
function  RL.DrawCapsule( startPos, endPos, radius, slices, rings, color ) end

---Draw capsule wireframe with the center of its sphere caps at startPos and endPos
---@param startPos table
---@param endPos table
---@param radius number
---@param slices integer
---@param rings integer
---@param color table
---@return any RL.DrawCapsuleWires
function  RL.DrawCapsuleWires( startPos, endPos, radius, slices, rings, color ) end

---Draw a plane XZ
---@param centerPos table
---@param size table
---@param color table
---@return any RL.DrawPlane
function  RL.DrawPlane( centerPos, size, color ) end

---Draw 3D textured quad. (Texture coordinates opengl style 0.0 - 1.0).
---@param texture any
---@param vertices any
---@param texCoords any
---@param colors any
---@return any RL.DrawQuad3DTexture
function  RL.DrawQuad3DTexture( texture, vertices, texCoords, colors ) end

---Draw a ray line
---@param ray any
---@param color table
---@return any RL.DrawRay
function  RL.DrawRay( ray, color ) end

---Draw a grid (Centered at ( 0, 0, 0 ))
---@param slices integer
---@param spacing number
---@return any RL.DrawGrid
function  RL.DrawGrid( slices, spacing ) end

-- Models - Mesh

---Generate polygonal mesh
---- Success return Mesh
---@param sides integer
---@param radius number
---@return any mesh 
function RL.GenMeshPoly( sides, radius ) end

---Generate plane mesh (With subdivisions)
---- Success return Mesh
---@param width number
---@param length number
---@param resX integer
---@param resZ integer
---@return any mesh 
function RL.GenMeshPlane( width, length, resX, resZ ) end

---Generate cuboid mesh
---- Success return Mesh
---@param size table
---@return any mesh 
function RL.GenMeshCube( size ) end

---Generate sphere mesh (Standard sphere)
---- Success return Mesh
---@param radius number
---@param rings integer
---@param slices integer
---@return any mesh 
function RL.GenMeshSphere( radius, rings, slices ) end

---Generate cylinder mesh
---- Success return Mesh
---@param radius number
---@param height number
---@param slices integer
---@return any mesh 
function RL.GenMeshCylinder( radius, height, slices ) end

---Generate cone/pyramid mesh
---- Success return Mesh
---@param radius number
---@param height number
---@param slices integer
---@return any mesh 
function RL.GenMeshCone( radius, height, slices ) end

---Generate torus mesh
---- Success return Mesh
---@param radius number
---@param size number
---@param radSeg integer
---@param sides integer
---@return any mesh 
function RL.GenMeshTorus( radius, size, radSeg, sides ) end

---Generate torus mesh
---- Success return Mesh
---@param radius number
---@param size number
---@param radSeg integer
---@param sides integer
---@return any mesh 
function RL.GenMeshKnot( radius, size, radSeg, sides ) end

---Generate heightmap mesh from image data
---- Success return Mesh
---@param heightmap any
---@param size table
---@return any mesh 
function RL.GenMeshHeightmap( heightmap, size ) end

---Generate custom mesh from vertex attribute data and uploads it into a VAO (if supported) and VBO
---- Success return Mesh
---@param meshData any
---@param dynamic boolean
---@return any mesh 
function RL.GenMeshCustom( meshData, dynamic ) end

---Update mesh vertex data in GPU.
---Note! Mainly intented to be used with custom meshes.
---@param mesh any
---@param meshData any
---@return any RL.UpdateMesh
function  RL.UpdateMesh( mesh, meshData ) end

---Draw a 3d mesh with material and transform
---@param mesh any
---@param material any
---@param transform table
---@return any RL.DrawMesh
function  RL.DrawMesh( mesh, material, transform ) end

---Draw multiple mesh instances with material and different transforms
---@param mesh any
---@param material any
---@param transforms any
---@param instances integer
---@return any RL.DrawMeshInstanced
function  RL.DrawMeshInstanced( mesh, material, transforms, instances ) end

---Updades mesh color vertex attribute buffer
---NOTE: Currently only works on custom mesh
---- Failure return false
---- Success return true
---@param mesh any
---@param color table
---@return any success 
function RL.SetMeshColor( mesh, color ) end

---Export mesh data to file, returns true on success
---- Success return bool
---@param mesh any
---@param fileName string
---@return any success 
function RL.ExportMesh( mesh, fileName ) end

---Compute mesh bounding box limits
---- Success return BoundingBox
---@param mesh any
---@return any boundingBox 
function RL.GetMeshBoundingBox( mesh ) end

---Compute mesh tangents
---@param mesh any
---@return any RL.GenMeshTangents
function  RL.GenMeshTangents( mesh ) end

-- Models - Material

---Load default material
---- Success return Material
---@return any material 
function RL.LoadMaterialDefault() end

---Load material from table. See material table definition
---- Success return Material
---@param materialData any
---@return any material 
function RL.CreateMaterial( materialData ) end

---Set texture for a material map type (MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS...)
---@param material any
---@param mapType integer
---@param texture any
---@return any RL.SetMaterialTexture
function  RL.SetMaterialTexture( material, mapType, texture ) end

---Set color for a material map type
---@param material any
---@param mapType integer
---@param color table
---@return any RL.SetMaterialColor
function  RL.SetMaterialColor( material, mapType, color ) end

---Set value for a material map type
---@param material any
---@param mapType integer
---@param value number
---@return any RL.SetMaterialValue
function  RL.SetMaterialValue( material, mapType, value ) end

---Set shader for material
---@param material any
---@param shader any
---@return any RL.SetMaterialShader
function  RL.SetMaterialShader( material, shader ) end

---Set material generic parameters (if required)
---@param material any
---@param params any
---@return any RL.SetMaterialParams
function  RL.SetMaterialParams( material, params ) end

---Get texture from material map type. Returns -1 if no texture
---- Success return Texture
---@param material any
---@param mapType integer
---@return any texture 
function RL.GetMaterialTexture( material, mapType ) end

---Get color from material map type
---- Success return Color
---@param material any
---@param mapType integer
---@return any color 
function RL.GetMaterialColor( material, mapType ) end

---Get color from material map type
---- Success return float
---@param material any
---@param mapType integer
---@return any value 
function RL.GetMaterialValue( material, mapType ) end

---Get material shader
---- Success return Shader
---@param material any
---@return any shader 
function RL.GetMaterialShader( material ) end

---Get material parameters
---- Success return float{}
---@param material any
---@return any params 
function RL.GetMaterialParams( material ) end

-- Models - Model

---Load model from files (Meshes and materials)
---- Failure return nil
---- Success return Model
---@param fileName string
---@return any model 
function RL.LoadModel( fileName ) end

---Load model from generated mesh (Default material)
---- Success return Model
---@param mesh any
---@return any model 
function RL.LoadModelFromMesh( mesh ) end

---Draw a model (With texture if set)
---@param model any
---@param position table
---@param scale number
---@param tint table
---@return any RL.DrawModel
function  RL.DrawModel( model, position, scale, tint ) end

---Draw a model with extended parameters
---@param model any
---@param position table
---@param rotationAxis table
---@param rotationAngle number
---@param scale table
---@param tint table
---@return any RL.DrawModelEx
function  RL.DrawModelEx( model, position, rotationAxis, rotationAngle, scale, tint ) end

---Copies material to model material. (Model material is the material id in models.)
---@param model any
---@param modelMaterial any
---@param material any
---@return any RL.SetModelMaterial
function  RL.SetModelMaterial( model, modelMaterial, material ) end

---Set material for a mesh (Mesh and material on this model)
---@param model any
---@param meshId integer
---@param materialId integer
---@return any RL.SetModelMeshMaterial
function  RL.SetModelMeshMaterial( model, meshId, materialId ) end

---Draw a billboard texture
---@param camera any
---@param texture any
---@param position table
---@param size number
---@param tint table
---@return any RL.DrawBillboard
function  RL.DrawBillboard( camera, texture, position, size, tint ) end

---Draw a billboard texture defined by source
---@param camera any
---@param texture any
---@param source table
---@param position table
---@param size table
---@param tint table
---@return any RL.DrawBillboardRec
function  RL.DrawBillboardRec( camera, texture, source, position, size, tint ) end

---Draw a billboard texture defined by source and rotation
---@param camera any
---@param texture any
---@param source table
---@param position table
---@param up table
---@param size table
---@param origin table
---@param rotation number
---@param tint table
---@return any RL.DrawBillboardPro
function  RL.DrawBillboardPro( camera, texture, source, position, up, size, origin, rotation, tint ) end

---Set model transform matrix
---@param model any
---@param transform table
---@return any RL.SetModelTransform
function  RL.SetModelTransform( model, transform ) end

---Get model transform matrix
---- Success return Matrix
---@param model any
---@return any transform 
function RL.GetModelTransform( model ) end

-- Model - Animations

---Load model animations from file
---- Failure return nil
---- Success return ModelAnimations{}
---@param fileName string
---@return any animations 
function RL.LoadModelAnimations( fileName ) end

---Update model animation pose
---@param model any
---@param animation any
---@param frame integer
---@return any RL.UpdateModelAnimation
function  RL.UpdateModelAnimation( model, animation, frame ) end

---Check model animation skeleton match
---- Success return bool
---@param model any
---@param animation any
---@return any valid 
function RL.IsModelAnimationValid( model, animation ) end

---Return modelAnimation bone count
---- Success return int
---@param animation any
---@return any boneCount 
function RL.GetModelAnimationBoneCount( animation ) end

---Return modelAnimation frame count
---- Success return int
---@param animation any
---@return any frameCount 
function RL.GetModelAnimationFrameCount( animation ) end

-- Model - Collision

---Check collision between two spheres
---- Success return bool
---@param center1 table
---@param radius1 number
---@param center2 table
---@param radius2 number
---@return any collision 
function RL.CheckCollisionSpheres( center1, radius1, center2, radius2 ) end

---Check collision between two bounding boxes
---- Success return bool
---@param box1 any
---@param box2 any
---@return any collision 
function RL.CheckCollisionBoxes( box1, box2 ) end

---Check collision between box and sphere
---- Success return bool
---@param box any
---@param center table
---@param radius number
---@return any collision 
function RL.CheckCollisionBoxSphere( box, center, radius ) end

---Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )
---- Success return RayCollision
---@param ray any
---@param center table
---@param radius number
---@return any rayCollision 
function RL.GetRayCollisionSphere( ray, center, radius ) end

---Get collision info between ray and box
---- Success return RayCollision
---@param ray any
---@param box any
---@return any rayCollision 
function RL.GetRayCollisionBox( ray, box ) end

---Get collision info between ray and mesh
---- Success return RayCollision
---@param ray any
---@param mesh any
---@param transform table
---@return any rayCollision 
function RL.GetRayCollisionMesh( ray, mesh, transform ) end

---Get collision info between ray and triangle
---- Success return RayCollision
---@param ray any
---@param p1 table
---@param p2 table
---@param p3 table
---@return any rayCollision 
function RL.GetRayCollisionTriangle( ray, p1, p2, p3 ) end

---Get collision info between ray and quad
---- Success return RayCollision
---@param ray any
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@return any rayCollision 
function RL.GetRayCollisionQuad( ray, p1, p2, p3, p4 ) end

-- Audio - Audio device management

---Set master volume (listener)
---@param volume number
---@return any RL.SetMasterVolume
function  RL.SetMasterVolume( volume ) end

-- Audio - Wave/Sound Loading

---Load sound from file
---- Failure return nil
---- Success return Sound
---@param fileName string
---@return any sound 
function RL.LoadSound( fileName ) end

---Load wave data from file
---- Failure return nil
---- Success return Wave
---@param fileName string
---@return any wave 
function RL.LoadWave( fileName ) end

---Load sound from wave data
---- Success return Sound
---@param wave any
---@return any sound 
function RL.LoadSoundFromWave( wave ) end

---Export wave data to file, returns true on success
---- Success return bool
---@param wave any
---@param fileName string
---@return any success 
function RL.ExportWave( wave, fileName ) end

---Export wave sample data to code (.h), returns true on success
---- Success return true
---@param wave any
---@param fileName string
---@return any success 
function RL.ExportWaveAsCode( wave, fileName ) end

-- Audio - Wave/Sound management

---Play a sound
---@param sound any
---@return any RL.PlaySound
function  RL.PlaySound( sound ) end

---Stop playing a sound
---@param sound any
---@return any RL.StopSound
function  RL.StopSound( sound ) end

---Pause a sound
---@param sound any
---@return any RL.PauseSound
function  RL.PauseSound( sound ) end

---Resume a paused sound
---@param sound any
---@return any RL.ResumeSound
function  RL.ResumeSound( sound ) end

---Check if a sound is currently playing
---- Success return bool
---@param sound any
---@return any playing 
function RL.IsSoundPlaying( sound ) end

---Set volume for a sound (1.0 is max level)
---@param sound any
---@param volume number
---@return any RL.SetSoundVolume
function  RL.SetSoundVolume( sound, volume ) end

---Set pitch for a sound (1.0 is base level)
---@param sound any
---@param pitch number
---@return any RL.SetSoundPitch
function  RL.SetSoundPitch( sound, pitch ) end

---Set pan for a sound (0.5 is center)
---@param sound any
---@param pan number
---@return any RL.SetSoundPan
function  RL.SetSoundPan( sound, pan ) end

---Convert wave data to desired format
---@param wave any
---@param sampleRate integer
---@param sampleSize integer
---@param channels integer
---@return any RL.WaveFormat
function  RL.WaveFormat( wave, sampleRate, sampleSize, channels ) end

---Copy a wave to a new wave
---- Success return Wave
---@param wave any
---@return any wave 
function RL.WaveCopy( wave ) end

---Crop a wave to defined samples range
---@param wave any
---@param initSample integer
---@param finalSample integer
---@return any RL.WaveCrop
function  RL.WaveCrop( wave, initSample, finalSample ) end

-- Audio - Music management

---Load music stream from file
---- Success return Music
---@param fileName string
---@return any music 
function RL.LoadMusicStream( fileName ) end

---Start music playing
---@param music any
---@return any RL.PlayMusicStream
function  RL.PlayMusicStream( music ) end

---Check if music is playing
---- Success return bool
---@param music any
---@return any playing 
function RL.IsMusicStreamPlaying( music ) end

---Updates buffers for music streaming
---@param music any
---@return any RL.UpdateMusicStream
function  RL.UpdateMusicStream( music ) end

---Stop music playing
---@param music any
---@return any RL.StopMusicStream
function  RL.StopMusicStream( music ) end

---Pause music playing
---@param music any
---@return any RL.PauseMusicStream
function  RL.PauseMusicStream( music ) end

---Resume playing paused music
---@param music any
---@return any RL.ResumeMusicStream
function  RL.ResumeMusicStream( music ) end

---Seek music to a position (in seconds)
---@param music any
---@param position number
---@return any RL.SeekMusicStream
function  RL.SeekMusicStream( music, position ) end

---Set volume for music (1.0 is max level)
---@param music any
---@param volume number
---@return any RL.SetMusicVolume
function  RL.SetMusicVolume( music, volume ) end

---Set pitch for a music (1.0 is base level)
---@param music any
---@param pitch number
---@return any RL.SetMusicPitch
function  RL.SetMusicPitch( music, pitch ) end

---Set pan for a music (0.5 is center)
---@param music any
---@param pan number
---@return any RL.SetMusicPan
function  RL.SetMusicPan( music, pan ) end

---Set looping for a music
---@param music any
---@param looping boolean
---@return any RL.SetMusicLooping
function  RL.SetMusicLooping( music, looping ) end

---Get looping of a music
---- Success return bool
---@param music any
---@return any looping 
function RL.GetMusicLooping( music ) end

---Get music time length (in seconds)
---- Success return float
---@param music any
---@return any length 
function RL.GetMusicTimeLength( music ) end

---Get current music time played (in seconds)
---- Success return float
---@param music any
---@return any timePlayed 
function RL.GetMusicTimePlayed( music ) end

-- Math - Utils

---Clamp float value
---- Success return float
---@param value number
---@param min number
---@param max number
---@return any result 
function RL.Clamp( value, min, max ) end

---Calculate linear interpolation between two floats
---- Success return float
---@param a number
---@param b number
---@param amount number
---@return any result 
function RL.Lerp( a, b, amount ) end

---Normalize input value within input range
---- Success return float
---@param value number
---@param a number
---@param b number
---@return any result 
function RL.Normalize( value, a, b ) end

---Remap input value within input range to output range
---- Success return float
---@param value number
---@param inputStart number
---@param inputEnd number
---@param outputStart number
---@param outputEnd number
---@return any result 
function RL.Remap( value, inputStart, inputEnd, outputStart, outputEnd ) end

---Wrap input value from min to max
---- Success return float
---@param value number
---@param min number
---@param max number
---@return any result 
function RL.Wrap( value, min, max ) end

---Check whether two given floats are almost equal
---- Success return int
---@param x number
---@param y number
---@return any result 
function RL.FloatEquals( x, y ) end

-- Math - Vector2

---Vector with components value 0.0f
---- Success return Vector2
---@return any result 
function RL.Vector2Zero() end

---Vector with components value 1.0f
---- Success return Vector2
---@return any result 
function RL.Vector2One() end

---Add two vectors (v1 + v2)
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Add( v1, v2 ) end

---Add vector and float value
---- Success return Vector2
---@param v table
---@param add number
---@return any result 
function RL.Vector2AddValue( v, add ) end

---Subtract two vectors (v1 - v2)
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Subtract( v1, v2 ) end

---Subtract vector by float value
---- Success return Vector2
---@param v table
---@param sub number
---@return any result 
function RL.Vector2SubtractValue( v, sub ) end

---Calculate vector length
---- Success return float
---@param v any
---@return any result 
function RL.Vector2Length( v ) end

---Calculate vector square length
---- Success return float
---@param v any
---@return any result 
function RL.Vector2LengthSqr( v ) end

---Calculate two vectors dot product
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2DotProduct( v1, v2 ) end

---Calculate distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Distance( v1, v2 ) end

---Calculate square distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2DistanceSqr( v1, v2 ) end

---Calculate angle from two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Angle( v1, v2 ) end

---Calculate angle defined by a two vectors line.
---NOTE: Parameters need to be normalized.
---Current implementation should be aligned with glm::angle.
---- Success return float
---@param a table
---@param b table
---@return any result 
function RL.Vector2LineAngle( a, b ) end

---Scale vector (multiply by value)
---- Success return Vector2
---@param v table
---@param scale number
---@return any result 
function RL.Vector2Scale( v, scale ) end

---Multiply vector by vector
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Multiply( v1, v2 ) end

---Negate vector
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Negate( v ) end

---Divide vector by vector
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Divide( v1, v2 ) end

---Normalize provided vector
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Normalize( v ) end

---Transforms a Vector2 by a given Matrix
---- Success return Vector2
---@param v table
---@param mat table
---@return any result 
function RL.Vector2Transform( v, mat ) end

---Calculate linear interpolation between two vectors
---- Success return Vector2
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector2Lerp( v1, v2, amount ) end

---Calculate reflected vector to normal
---- Success return Vector2
---@param v table
---@param normal table
---@return any result 
function RL.Vector2Reflect( v, normal ) end

---Rotate vector by angle
---- Success return Vector2
---@param v table
---@param angle number
---@return any result 
function RL.Vector2Rotate( v, angle ) end

---Move Vector towards target
---- Success return Vector2
---@param v table
---@param target table
---@param maxDistance number
---@return any result 
function RL.Vector2MoveTowards( v, target, maxDistance ) end

---Invert the given vector
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Invert( v ) end

---Clamp the components of the vector between
---min and max values specified by the given vectors
---- Success return Vector2
---@param v table
---@param min table
---@param max table
---@return any result 
function RL.Vector2Clamp( v, min, max ) end

---Clamp the magnitude of the vector between two min and max values
---- Success return Vector2
---@param v table
---@param min number
---@param max number
---@return any result 
function RL.Vector2ClampValue( v, min, max ) end

---Check whether two given vectors are almost equal
---- Success return int
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Equals( v1, v2 ) end

-- Math - Vector 3

---Vector with components value 0.0f
---- Success return Vector3
---@return any result 
function RL.Vector3Zero() end

---Vector with components value 1.0f
---- Success return Vector3
---@return any result 
function RL.Vector3One() end

---Add two vectors
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Add( v1, v2 ) end

---Add vector and float value
---- Success return Vector3
---@param v table
---@param add number
---@return any result 
function RL.Vector3AddValue( v, add ) end

---Subtract two vectors
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Subtract( v1, v2 ) end

---Subtract vector by float value
---- Success return Vector3
---@param v table
---@param sub number
---@return any result 
function RL.Vector3SubtractValue( v, sub ) end

---Multiply vector by scalar
---- Success return Vector3
---@param v table
---@param scalar number
---@return any result 
function RL.Vector3Scale( v, scalar ) end

---Multiply vector by vector
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Multiply( v1, v2 ) end

---Calculate two vectors cross product
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3CrossProduct( v1, v2 ) end

---Calculate one vector perpendicular vector
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Perpendicular( v ) end

---Calculate vector length
---- Success return float
---@param v table
---@return any result 
function RL.Vector3Length( v ) end

---Calculate vector square length
---- Success return float
---@param v table
---@return any result 
function RL.Vector3LengthSqr( v ) end

---Calculate two vectors dot product
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3DotProduct( v1, v2 ) end

---Calculate distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Distance( v1, v2 ) end

---Calculate square distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3DistanceSqr( v1, v2 ) end

---Calculate angle between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Angle( v1, v2 ) end

---Negate provided vector (invert direction)
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Negate( v ) end

---Divide vector by vector
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Divide( v1, v2 ) end

---Normalize provided vector
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Normalize( v ) end

---Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
---Gram-Schmidt function implementation
---- Success return Vector3, Vector3
---@param v1 table
---@param v2 table
---@return any v1
---@return any v2 
function RL.Vector3OrthoNormalize( v1, v2 ) end

---Transforms a Vector3 by a given Matrix
---- Success return Vector3
---@param v table
---@param mat table
---@return any result 
function RL.Vector3Transform( v, mat ) end

---Transform a vector by quaternion rotation
---- Success return Vector3
---@param v table
---@param q table
---@return any result 
function RL.Vector3RotateByQuaternion( v, q ) end

---Rotates a vector around an axis
---- Success return Vector3
---@param v table
---@param axis table
---@param angle number
---@return any result 
function RL.Vector3RotateByAxisAngle( v, axis, angle ) end

---Calculate linear interpolation between two vectors
---- Success return Vector3
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector3Lerp( v1, v2, amount ) end

---Calculate reflected vector to normal
---- Success return Vector3
---@param v table
---@param normal table
---@return any result 
function RL.Vector3Reflect( v, normal ) end

---Get min value for each pair of components
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Min( v1, v2 ) end

---Get max value for each pair of components
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Max( v1, v2 ) end

---Compute barycenter coordinates (u, v, w) for point p with respect to triangle (a, b, c)
---NOTE: Assumes P is on the plane of the triangle
---- Success return Vector3
---@param p table
---@param a table
---@param b table
---@param c table
---@return any result 
function RL.Vector3Barycenter( p, a, b, c ) end

---Projects a Vector3 from screen space into object space
---NOTE: We are avoiding calling other raymath functions despite available
---- Success return Vector3
---@param source table
---@param projection table
---@param view table
---@return any result 
function RL.Vector3Unproject( source, projection, view ) end

---Invert the given vector
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Invert( v ) end

---Clamp the components of the vector between
---min and max values specified by the given vectors
---- Success return Vector3
---@param v table
---@param min table
---@param max table
---@return any result 
function RL.Vector3Clamp( v, min, max ) end

---Clamp the magnitude of the vector between two values
---- Success return Vector3
---@param v table
---@param min number
---@param max number
---@return any result 
function RL.Vector3ClampValue( v, min, max ) end

---Check whether two given vectors are almost equal
---- Success return int
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Equals( v1, v2 ) end

---Compute the direction of a refracted ray where v specifies the
---normalized direction of the incoming ray, n specifies the
---normalized normal vector of the interface of two optical media,
---and r specifies the ratio of the refractive index of the medium
---from where the ray comes to the refractive index of the medium
---on the other side of the surface
---- Success return Vector3
---@param v table
---@param n table
---@param r number
---@return any result 
function RL.Vector3Refract( v, n, r ) end

-- Math - Matrix

---Compute matrix determinant
---- Success return float
---@param mat table
---@return any result 
function RL.MatrixDeterminant( mat ) end

---Get the trace of the matrix (sum of the values along the diagonal)
---- Success return float
---@param mat table
---@return any result 
function RL.MatrixTrace( mat ) end

---Transposes provided matrix
---- Success return Matrix
---@param mat table
---@return any result 
function RL.MatrixTranspose( mat ) end

---Invert provided matrix
---- Success return Matrix
---@param mat table
---@return any result 
function RL.MatrixInvert( mat ) end

---Get identity matrix
---- Success return Matrix
---@return any result 
function RL.MatrixIdentity() end

---Add two matrices
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixAdd( left, right ) end

---Subtract two matrices (left - right)
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixSubtract( left, right ) end

---Get two matrix multiplication
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixMultiply( left, right ) end

---Get translation matrix
---- Success return Matrix
---@param translate table
---@return any result 
function RL.MatrixTranslate( translate ) end

---Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians
---- Success return Matrix
---@param axis table
---@param angle number
---@return any result 
function RL.MatrixRotate( axis, angle ) end

---Get x-rotation matrix (angle in radians)
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateX( angle ) end

---Get y-rotation matrix (angle in radians)
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateY( angle ) end

---Get z-rotation matrix (angle in radians)
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateZ( angle ) end

---Get xyz-rotation matrix (angles in radians)
---- Success return Matrix
---@param angle table
---@return any result 
function RL.MatrixRotateXYZ( angle ) end

---Get zyx-rotation matrix (angles in radians)
---- Success return Matrix
---@param angle table
---@return any result 
function RL.MatrixRotateZYX( angle ) end

---Get scaling matrix
---- Success return Matrix
---@param scale table
---@return any result 
function RL.MatrixScale( scale ) end

---Get perspective projection matrix
---- Success return Matrix
---@param left any
---@param right any
---@param bottom any
---@param top any
---@param near any
---@param far any
---@return any result 
function RL.MatrixFrustum( left, right, bottom, top, near, far ) end

---Get perspective projection matrix
---- Success return Matrix
---@param fovy any
---@param aspect any
---@param near any
---@param far any
---@return any result 
function RL.MatrixPerspective( fovy, aspect, near, far ) end

---Get orthographic projection matrix
---- Success return Matrix
---@param left any
---@param right any
---@param bottom any
---@param top any
---@param near any
---@param far any
---@return any result 
function RL.MatrixOrtho( left, right, bottom, top, near, far ) end

---Get camera look-at matrix (View matrix)
---- Success return Matrix
---@param eye table
---@param target table
---@param up table
---@return any result 
function RL.MatrixLookAt( eye, target, up ) end

-- Math - Quaternion

---Add two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionAdd( q1, q2 ) end

---Add quaternion and float value
---- Success return Quaternion
---@param q table
---@param add number
---@return any result 
function RL.QuaternionAddValue( q, add ) end

---Subtract two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionSubtract( q1, q2 ) end

---Subtract quaternion and float value
---- Success return Quaternion
---@param q table
---@param sub number
---@return any result 
function RL.QuaternionSubtractValue( q, sub ) end

---Get identity quaternion
---- Success return Quaternion
---@return any result 
function RL.QuaternionIdentity() end

---Computes the length of a quaternion
---- Success return float
---@param q table
---@return any result 
function RL.QuaternionLength( q ) end

---Normalize provided quaternion
---- Success return Quaternion
---@param q table
---@return any result 
function RL.QuaternionNormalize( q ) end

---Invert provided quaternion
---- Success return Quaternion
---@param q table
---@return any result 
function RL.QuaternionInvert( q ) end

---Calculate two quaternion multiplication
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionMultiply( q1, q2 ) end

---Scale quaternion by float value
---- Success return Quaternion
---@param q table
---@param mul number
---@return any result 
function RL.QuaternionScale( q, mul ) end

---Divide two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionDivide( q1, q2 ) end

---Calculate linear interpolation between two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionLerp( q1, q2, amount ) end

---Calculate slerp-optimized interpolation between two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionNlerp( q1, q2, amount ) end

---Calculates spherical linear interpolation between two quaternions
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionSlerp( q1, q2, amount ) end

---Calculate quaternion based on the rotation from one vector to another
---- Success return Quaternion
---@param from table
---@param to table
---@return any result 
function RL.QuaternionFromVector3ToVector3( from, to ) end

---Get a quaternion for a given rotation matrix
---- Success return Quaternion
---@param mat table
---@return any result 
function RL.QuaternionFromMatrix( mat ) end

---Get a quaternion for a given rotation matrix
---- Success return Matrix
---@param q table
---@return any result 
function RL.QuaternionToMatrix( q ) end

---Get rotation quaternion for an angle and axis
---NOTE: angle must be provided in radians
---- Success return Quaternion
---@param axis table
---@param angle number
---@return any result 
function RL.QuaternionFromAxisAngle( axis, angle ) end

---Get the rotation angle and axis for a given quaternion
---- Success return Vector3, float
---@param q table
---@return any axis
---@return any angle 
function RL.QuaternionToAxisAngle( q ) end

---Get the quaternion equivalent to Euler angles
---NOTE: Rotation order is ZYX
---- Success return Quaternion
---@param pitch number
---@param yaw number
---@param roll number
---@return any result 
function RL.QuaternionFromEuler( pitch, yaw, roll ) end

---Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
---NOTE: Angles are returned in a Vector3 struct in radians
---- Success return Vector3
---@param q table
---@return any result 
function RL.QuaternionToEuler( q ) end

---Transform a quaternion given a transformation matrix
---- Success return Quaternion
---@param q table
---@param mat table
---@return any result 
function RL.QuaternionTransform( q, mat ) end

---Check whether two given quaternions are almost equal
---- Success return int
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionEquals( q1, q2 ) end

-- Gui - Global

---Enable gui controls (global state)
---@return any RL.GuiEnable
function  RL.GuiEnable() end

---Disable gui controls (global state)
---@return any RL.GuiDisable
function  RL.GuiDisable() end

---Lock gui controls (global state)
---@return any RL.GuiLock
function  RL.GuiLock() end

---Unlock gui controls (global state)
---@return any RL.GuiUnlock
function  RL.GuiUnlock() end

---Check if gui is locked (global state)
---- Success return bool
---@return any locked 
function RL.GuiIsLocked() end

---Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f
---@param alpha number
---@return any RL.GuiFade
function  RL.GuiFade( alpha ) end

---Set gui state (global state)
---@param state integer
---@return any RL.GuiSetState
function  RL.GuiSetState( state ) end

---Get gui state (global state)
---- Success return int
---@return any state 
function RL.GuiGetState() end

-- Gui - Font

---Set gui custom font (global state)
---@param font any
---@return any RL.GuiSetFont
function  RL.GuiSetFont( font ) end

---Get gui custom font (global state)
---- Success return Font
---@return any font 
function RL.GuiGetFont() end

-- Gui - Style

---Set one style property
---@param control integer
---@param property integer
---@param value integer
---@return any RL.GuiSetStyle
function  RL.GuiSetStyle( control, property, value ) end

---Get one style property
---- Success return int
---@param control integer
---@param property integer
---@return any value 
function RL.GuiGetStyle( control, property ) end

---Load style file over global style variable (.rgs)
---- Failure return false
---- Success return true
---@param fileName string
---@return any success 
function RL.GuiLoadStyle( fileName ) end

---Load style default over global style
---@return any RL.GuiLoadStyleDefault
function  RL.GuiLoadStyleDefault() end

-- Gui - Container

---Window Box control, shows a window that can be closed
---- Success return bool
---@param bounds table
---@param title string
---@return any state 
function RL.GuiWindowBox( bounds, title ) end

---Group Box control with text name
---@param bounds table
---@param text string
---@return any RL.GuiGroupBox
function  RL.GuiGroupBox( bounds, text ) end

---Line separator control, could contain text
---@param bounds table
---@param text string
---@return any RL.GuiLine
function  RL.GuiLine( bounds, text ) end

---Panel control, useful to group controls
---@param bounds table
---@param text string
---@return any RL.GuiPanel
function  RL.GuiPanel( bounds, text ) end

---Scroll Panel control
---- Success return Rectangle, Vector2
---@param bounds table
---@param text string
---@param content table
---@param scroll table
---@return any view
---@return any scroll 
function RL.GuiScrollPanel( bounds, text, content, scroll ) end

-- Gui - Basic

---Label control, shows text
---@param bounds table
---@param text string
---@return any RL.GuiLabel
function  RL.GuiLabel( bounds, text ) end

---Button control, returns true when clicked
---- Success return boolean
---@param bounds table
---@param text string
---@return any clicked 
function RL.GuiButton( bounds, text ) end

---Label button control, show true when clicked
---- Success return boolean
---@param bounds table
---@param text string
---@return any clicked 
function RL.GuiLabelButton( bounds, text ) end

---Toggle Button control, returns true when active
---- Success return boolean
---@param bounds table
---@param text string
---@param active boolean
---@return any active 
function RL.GuiToggle( bounds, text, active ) end

---Toggle Group control, returns active toggle index
---- Success return int
---@param bounds table
---@param text string
---@param active integer
---@return any index 
function RL.GuiToggleGroup( bounds, text, active ) end

---Check Box control, returns true when active
---- Success return boolean
---@param bounds table
---@param text string
---@param checked boolean
---@return any active 
function RL.GuiCheckBox( bounds, text, checked ) end

---Combo Box control, returns selected item index
---- Success return int
---@param bounds table
---@param text string
---@param active integer
---@return any active 
function RL.GuiComboBox( bounds, text, active ) end

---Text Box control, updates input text
---- Success return boolean, string
---@param bounds table
---@param text string
---@param textSize integer
---@param editMode boolean
---@return any pressed
---@return any text 
function RL.GuiTextBox( bounds, text, textSize, editMode ) end

---Text Box control with multiple lines
---- Success return boolean, string
---@param bounds table
---@param text string
---@param textSize integer
---@param editMode boolean
---@return any pressed
---@return any text 
function RL.GuiTextBoxMulti( bounds, text, textSize, editMode ) end

---Spinner control, returns selected value
---- Success return boolean, int
---@param bounds table
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@return any pressed
---@return any value 
function RL.GuiSpinner( bounds, text, value, minValue, maxValue, editMode ) end

---Value Box control, updates input text with numbers
---- Success return boolean, int
---@param bounds table
---@param text string
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@return any pressed
---@return any value 
function RL.GuiValueBox( bounds, text, value, minValue, maxValue, editMode ) end

---Slider control, returns selected value
---- Success return float
---@param bounds table
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@return any value 
function RL.GuiSlider( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Slider Bar control, returns selected value
---- Success return float
---@param bounds table
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@return any value 
function RL.GuiSliderBar( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Progress Bar control, shows current progress value
---- Success return float
---@param bounds table
---@param textLeft string
---@param textRight string
---@param value number
---@param minValue number
---@param maxValue number
---@return any value 
function RL.GuiProgressBar( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Scroll Bar control
---- Success return int
---@param bounds table
---@param value integer
---@param minValue integer
---@param maxValue integer
---@return any value 
function RL.GuiScrollBar( bounds, value, minValue, maxValue ) end

---Dropdown Box control, returns selected item
---- Success return bool, int
---@param bounds table
---@param text string
---@param active integer
---@param editMode boolean
---@return any pressed
---@return any item 
function RL.GuiDropdownBox( bounds, text, active, editMode ) end

---Status Bar control, shows info text
---@param bounds table
---@param text string
---@return any RL.GuiStatusBar
function  RL.GuiStatusBar( bounds, text ) end

---Dummy control for placeholders
---@param bounds table
---@param text string
---@return any RL.GuiDummyRec
function  RL.GuiDummyRec( bounds, text ) end

---Grid control, returns mouse cell position
---- Success return Vector2
---@param bounds table
---@param text string
---@param spacing number
---@param subdivs integer
---@return any cell 
function RL.GuiGrid( bounds, text, spacing, subdivs ) end

-- Gui - Advanced

---List View control, returns selected list item index and scroll index
---- Success return int, int
---@param bounds table
---@param text string
---@param scrollIndex integer
---@param active integer
---@return any itemIndex
---@return any scrollIndex 
function RL.GuiListView( bounds, text, scrollIndex, active ) end

---List View with extended parameters, returns selected list item index, scroll index and focus
---- Success return int, int, int
---@param bounds table
---@param text string
---@param focus integer
---@param scrollIndex integer
---@param active integer
---@return any itemIndex
---@return any scrollIndex
---@return any focus 
function RL.GuiListViewEx( bounds, text, focus, scrollIndex, active ) end

---Message Box control, displays a message, returns button index (0 is x button)
---- Success return int
---@param bounds table
---@param title string
---@param message string
---@param buttons string
---@return any buttonIndex 
function RL.GuiMessageBox( bounds, title, message, buttons ) end

---Text Input Box control, ask for text, supports secret
---- Success return int, string, int
---@param bounds table
---@param title string
---@param message string
---@param buttons string
---@param text string
---@param textMaxSize integer
---@param secretViewActive integer
---@return any buttonIndex
---@return any text
---@return any secretViewActive 
function RL.GuiTextInputBox( bounds, title, message, buttons, text, textMaxSize, secretViewActive ) end

---Color Picker control (multiple color controls)
---- Success return Color
---@param bounds table
---@param text string
---@param color table
---@return any color 
function RL.GuiColorPicker( bounds, text, color ) end

---Color Panel control
---- Success return Color
---@param bounds table
---@param text string
---@param color table
---@return any color 
function RL.GuiColorPanel( bounds, text, color ) end

---Color Bar Alpha control
---- Success return float
---@param bounds table
---@param text string
---@param alpha number
---@return any alpha 
function RL.GuiColorBarAlpha( bounds, text, alpha ) end

---Color Bar Hue control
---- Success return float
---@param bounds table
---@param text string
---@param value number
---@return any hue 
function RL.GuiColorBarHue( bounds, text, value ) end

-- Gui - Icons

---Get text with icon id prepended (if supported)
---- Success return string
---@param iconId integer
---@param text string
---@return any text 
function RL.GuiIconText( iconId, text ) end

---Draw icon
---@param iconId integer
---@param pos table
---@param pixelSize integer
---@param color table
---@return any RL.GuiDrawIcon
function  RL.GuiDrawIcon( iconId, pos, pixelSize, color ) end

---Set icon scale (1 by default)
---@param scale integer
---@return any RL.GuiSetIconScale
function  RL.GuiSetIconScale( scale ) end

---Set icon pixel value
---@param iconId integer
---@param pos table
---@return any RL.GuiSetIconPixel
function  RL.GuiSetIconPixel( iconId, pos ) end

---Clear icon pixel value
---@param iconId integer
---@param pos table
---@return any RL.GuiClearIconPixel
function  RL.GuiClearIconPixel( iconId, pos ) end

---Check icon pixel value
---- Success return bool
---@param iconId integer
---@param pos table
---@return any value 
function RL.GuiCheckIconPixel( iconId, pos ) end

-- Lights - Basics

---Create a light and get shader locations
---- Success return Light
---@param type integer
---@param position table
---@param target table
---@param color table
---@param shader any
---@return any light 
function RL.CreateLight( type, position, target, color, shader ) end

---Send light properties to shader
---@param shader any
---@param light any
---@return any RL.UpdateLightValues
function  RL.UpdateLightValues( shader, light ) end

---Set light type
---@param light any
---@param type integer
---@return any RL.SetLightType
function  RL.SetLightType( light, type ) end

---Set light position
---@param light any
---@param position table
---@return any RL.SetLightPosition
function  RL.SetLightPosition( light, position ) end

---Set light target
---@param light any
---@param target table
---@return any RL.SetLightTarget
function  RL.SetLightTarget( light, target ) end

---Set light color
---@param light any
---@param color table
---@return any RL.SetLightColor
function  RL.SetLightColor( light, color ) end

---Set light enabled
---@param light any
---@param enabled boolean
---@return any RL.SetLightEnabled
function  RL.SetLightEnabled( light, enabled ) end

---Get light type
---- Success return int
---@param light any
---@return any type 
function RL.GetLightType( light ) end

---Get light position
---- Success return Vector3
---@param light any
---@return any position 
function RL.GetLightPosition( light ) end

---Get light target
---- Success return Vector3
---@param light any
---@return any target 
function RL.GetLightTarget( light ) end

---Get light color
---- Success return Color
---@param light any
---@return any color 
function RL.GetLightColor( light ) end

---Get light enabled
---- Success return boolean
---@param light any
---@return any enabled 
function RL.IsLightEnabled( light ) end

-- RLGL - Matrix operations

---Choose the current matrix to be transformed
---@param mode integer
---@return any RL.rlMatrixMode
function  RL.rlMatrixMode( mode ) end

---Push the current matrix to stack
---@return any RL.rlPushMatrix
function  RL.rlPushMatrix() end

---Pop latest inserted matrix from stack
---@return any RL.rlPopMatrix
function  RL.rlPopMatrix() end

---Reset current matrix to identity matrix
---@return any RL.rlLoadIdentity
function  RL.rlLoadIdentity() end

---Multiply the current matrix by a translation matrix
---@param translation table
---@return any RL.rlTranslatef
function  RL.rlTranslatef( translation ) end

---Multiply the current matrix by a rotation matrix
---@param angle number
---@param rotation table
---@return any RL.rlRotatef
function  RL.rlRotatef( angle, rotation ) end

---Multiply the current matrix by a scaling matrix
---@param scale table
---@return any RL.rlScalef
function  RL.rlScalef( scale ) end

---Multiply the current matrix by another matrix
---@param matrix table
---@return any RL.rlMultMatrixf
function  RL.rlMultMatrixf( matrix ) end

---Multiply the current matrix by a perspective matrix generated by parameters
---@param left number
---@param right number
---@param bottom number
---@param top number
---@param znear number
---@param zfar number
---@return any RL.rlFrustum
function  RL.rlFrustum( left, right, bottom, top, znear, zfar ) end

---Multiply the current matrix by an orthographic matrix generated by parameters
---@param left number
---@param right number
---@param bottom number
---@param top number
---@param znear number
---@param zfar number
---@return any RL.rlOrtho
function  RL.rlOrtho( left, right, bottom, top, znear, zfar ) end

---Set the viewport area (transformation from normalized device coordinates to window coordinates)
---NOTE: We store current viewport dimensions
---@param viewport table
---@return any RL.rlViewport
function  RL.rlViewport( viewport ) end

-- RLGL - Vertex level operations

---Initialize drawing mode (how to organize vertex)
---@param mode integer
---@return any RL.rlBegin
function  RL.rlBegin( mode ) end

---Finish vertex providing
---@return any RL.rlEnd
function  RL.rlEnd() end

---Define one vertex (position)
---@param position table
---@return any RL.rlVertex2f
function  RL.rlVertex2f( position ) end

---Define one vertex (position)
---@param position table
---@return any RL.rlVertex3f
function  RL.rlVertex3f( position ) end

---Define one vertex (texture coordinate) - 2 float
---@param texCoord table
---@return any RL.rlTexCoord2f
function  RL.rlTexCoord2f( texCoord ) end

---Define one vertex (normal) - 3 float
---@param normal table
---@return any RL.rlNormal3f
function  RL.rlNormal3f( normal ) end

---Define one vertex (color) - 4 byte
---@param color table
---@return any RL.rlColor4ub
function  RL.rlColor4ub( color ) end

---Define one vertex (color) - 3 float
---@param color table
---@return any RL.rlColor3f
function  RL.rlColor3f( color ) end

---Define one vertex (color) - 4 float
---@param color table
---@return any RL.rlColor4f
function  RL.rlColor4f( color ) end

-- RLGL - Vertex buffers state

---Enable vertex array (VAO, if supported)
---- Success return bool
---@param vaoId integer
---@return any supported 
function RL.rlEnableVertexArray( vaoId ) end

---Disable vertex array (VAO, if supported)
---@return any RL.rlDisableVertexArray
function  RL.rlDisableVertexArray() end

---Enable vertex buffer (VBO)
---- Failure return false
---- Success return true
---@param id integer
---@return any RL.rlEnableVertexBuffer
function  RL.rlEnableVertexBuffer( id ) end

---Disable vertex buffer (VBO)
---@return any RL.rlDisableVertexBuffer
function  RL.rlDisableVertexBuffer() end

---Enable vertex buffer element (VBO element)
---@param id integer
---@return any RL.rlEnableVertexBufferElement
function  RL.rlEnableVertexBufferElement( id ) end

---Disable vertex buffer element (VBO element)
---@return any RL.rlDisableVertexBufferElement
function  RL.rlDisableVertexBufferElement() end

---Enable vertex attribute index
---@param index integer
---@return any RL.rlEnableVertexAttribute
function  RL.rlEnableVertexAttribute( index ) end

---Disable vertex attribute index
---@param index integer
---@return any RL.rlDisableVertexAttribute
function  RL.rlDisableVertexAttribute( index ) end

-- RLGL - Textures state

---Select and active a texture slot
---@param slot integer
---@return any RL.rlActiveTextureSlot
function  RL.rlActiveTextureSlot( slot ) end

---Enable texture
---@param id integer
---@return any RL.rlEnableTexture
function  RL.rlEnableTexture( id ) end

---Disable texture
---@return any RL.rlDisableTexture
function  RL.rlDisableTexture() end

---Enable texture cubemap
---@param id integer
---@return any RL.rlEnableTextureCubemap
function  RL.rlEnableTextureCubemap( id ) end

---Disable texture cubemap
---@return any RL.rlDisableTextureCubemap
function  RL.rlDisableTextureCubemap() end

---Set texture parameters (filter, wrap)
---@param id integer
---@param param integer
---@param value integer
---@return any RL.rlTextureParameters
function  RL.rlTextureParameters( id, param, value ) end

---Set cubemap parameters (filter, wrap)
---@param id integer
---@param param integer
---@param value integer
---@return any RL.rlCubemapParameters
function  RL.rlCubemapParameters( id, param, value ) end

-- RLGL - Shader state

---Enable shader program
---@param id integer
---@return any RL.rlEnableShader
function  RL.rlEnableShader( id ) end

---Disable shader program
---@return any RL.rlDisableShader
function  RL.rlDisableShader() end

-- RLGL - Framebuffer state

---Enable render texture (fbo)
---@param id integer
---@return any RL.rlEnableFramebuffer
function  RL.rlEnableFramebuffer( id ) end

---Disable render texture (fbo), return to default framebuffer
---@return any RL.rlDisableFramebuffer
function  RL.rlDisableFramebuffer() end

---Activate multiple draw color buffers
---@param count integer
---@return any RL.rlActiveDrawBuffers
function  RL.rlActiveDrawBuffers( count ) end

-- RLGL - General render state

---Enable color blending
---@return any RL.rlEnableColorBlend
function  RL.rlEnableColorBlend() end

---Disable color blending
---@return any RL.rlDisableColorBlend
function  RL.rlDisableColorBlend() end

---Enable depth test
---@return any RL.rlEnableDepthTest
function  RL.rlEnableDepthTest() end

---Disable depth test
---@return any RL.rlDisableDepthTest
function  RL.rlDisableDepthTest() end

---Enable depth write
---@return any RL.rlEnableDepthMask
function  RL.rlEnableDepthMask() end

---Disable depth write
---@return any RL.rlDisableDepthMask
function  RL.rlDisableDepthMask() end

---Enable backface culling
---@return any RL.rlEnableBackfaceCulling
function  RL.rlEnableBackfaceCulling() end

---Disable backface culling
---@return any RL.rlDisableBackfaceCulling
function  RL.rlDisableBackfaceCulling() end

---Set face culling mode
---@param mode integer
---@return any RL.rlSetCullFace
function  RL.rlSetCullFace( mode ) end

---Enable scissor test
---@return any RL.rlEnableScissorTest
function  RL.rlEnableScissorTest() end

---Disable scissor test
---@return any RL.rlDisableScissorTest
function  RL.rlDisableScissorTest() end

---Scissor test
---@param area table
---@return any RL.rlScissor
function  RL.rlScissor( area ) end

---Enable wire mode
---@return any RL.rlEnableWireMode
function  RL.rlEnableWireMode() end

---Disable wire mode
---@return any RL.rlDisableWireMode
function  RL.rlDisableWireMode() end

---Set the line drawing width
---@param width number
---@return any RL.rlSetLineWidth
function  RL.rlSetLineWidth( width ) end

---Get the line drawing width
---- Success return float
---@return any width 
function RL.rlGetLineWidth() end

---Enable line aliasing
---@return any RL.rlEnableSmoothLines
function  RL.rlEnableSmoothLines() end

---Disable line aliasing
---@return any RL.rlDisableSmoothLines
function  RL.rlDisableSmoothLines() end

---Enable stereo rendering
---@return any RL.rlEnableStereoRender
function  RL.rlEnableStereoRender() end

---Enable stereo rendering
---@return any RL.rlDisableStereoRender
function  RL.rlDisableStereoRender() end

---Check if stereo render is enabled
---- Success return bool
---@return any enabled 
function RL.rlIsStereoRenderEnabled() end

---Clear color buffer with color
---@param color table
---@return any RL.rlClearColor
function  RL.rlClearColor( color ) end

---Clear used screen buffers (color and depth)
---@return any RL.rlClearScreenBuffers
function  RL.rlClearScreenBuffers() end

---Check and log OpenGL error codes
---@return any RL.rlCheckErrors
function  RL.rlCheckErrors() end

---Set blending mode
---@param mode integer
---@return any RL.rlSetBlendMode
function  RL.rlSetBlendMode( mode ) end

---Set blending mode factor and equation (using OpenGL factors)
---@param glSrcFactor integer
---@param glDstFactor integer
---@param glEquation integer
---@return any RL.rlSetBlendFactors
function  RL.rlSetBlendFactors( glSrcFactor, glDstFactor, glEquation ) end

---Set blending mode factors and equations separately (using OpenGL factors)
---@param glSrcRGB integer
---@param glDstRGB integer
---@param glSrcAlpha integer
---@param glDstAlpha integer
---@param glEqRGB integer
---@param glEqAlpha integer
---@return any RL.rlSetBlendFactorsSeparate
function  RL.rlSetBlendFactorsSeparate( glSrcRGB, glDstRGB, glSrcAlpha, glDstAlpha, glEqRGB, glEqAlpha ) end

-- RLGL - Initialization functions

---Get current OpenGL version
---- Success return int
---@return any version 
function RL.rlGetVersion() end

-- RLGL - Render batch management

---Update and draw internal render batch
---@return any RL.rlDrawRenderBatchActive
function  RL.rlDrawRenderBatchActive() end

---Check internal buffer overflow for a given number of vertex and force a rlRenderBatch draw call if required
---- Success return bool
---@param vCount integer
---@return any overflow 
function RL.rlCheckRenderBatchLimit( vCount ) end

---Set current texture for render batch and check buffers limits
---@param id integer
---@return any RL.rlSetTexture
function  RL.rlSetTexture( id ) end

-- RLGL - Vertex buffers management

---Load vertex array (vao) if supported
---- Success return int
---@return any vaoId 
function RL.rlLoadVertexArray() end

---Load a vertex buffer attribute
---- Success return int
---@param buffer any
---@param dynamic boolean
---@return any vboId 
function RL.rlLoadVertexBuffer( buffer, dynamic ) end

---Load a new attributes element buffer
---- Success return int
---@param buffer any
---@param dynamic boolean
---@return any vboId 
function RL.rlLoadVertexBufferElement( buffer, dynamic ) end

---Update GPU buffer with new data
---@param bufferId integer
---@param buffer any
---@param offset integer
---@return any RL.rlUpdateVertexBuffer
function  RL.rlUpdateVertexBuffer( bufferId, buffer, offset ) end

---Update vertex buffer elements with new data
---@param id integer
---@param buffer any
---@param offset integer
---@return any RL.rlUpdateVertexBufferElements
function  RL.rlUpdateVertexBufferElements( id, buffer, offset ) end

---Unload vertex array object (VAO)
---@param vaoId integer
---@return any RL.rlUnloadVertexArray
function  RL.rlUnloadVertexArray( vaoId ) end

---Unload vertex buffer (VBO)
---@param vboId integer
---@return any RL.rlUnloadVertexBuffer
function  RL.rlUnloadVertexBuffer( vboId ) end

---Set vertex attribute
---@param index integer
---@param compSize integer
---@param type integer
---@param normalized boolean
---@param stride integer
---@param pointer integer
---@return any RL.rlSetVertexAttribute
function  RL.rlSetVertexAttribute( index, compSize, type, normalized, stride, pointer ) end

---Set vertex attribute divisor
---@param index integer
---@param divisor integer
---@return any RL.rlSetVertexAttributeDivisor
function  RL.rlSetVertexAttributeDivisor( index, divisor ) end

---Set vertex attribute default value
---@param locIndex integer
---@param value any
---@param attribType integer
---@return any RL.rlSetVertexAttributeDefault
function  RL.rlSetVertexAttributeDefault( locIndex, value, attribType ) end

---Draw vertex array
---@param offset integer
---@param count integer
---@return any RL.rlDrawVertexArray
function  RL.rlDrawVertexArray( offset, count ) end

---Draw vertex array elements
---@param offset integer
---@param count integer
---@param buffer any
---@return any RL.rlDrawVertexArrayElements
function  RL.rlDrawVertexArrayElements( offset, count, buffer ) end

---Draw vertex array instanced
---@param offset integer
---@param count integer
---@param instances integer
---@return any RL.rlDrawVertexArrayInstanced
function  RL.rlDrawVertexArrayInstanced( offset, count, instances ) end

---Draw vertex array elements instanced
---@param offset integer
---@param count integer
---@param buffer any
---@param instances integer
---@return any RL.rlDrawVertexArrayElementsInstanced
function  RL.rlDrawVertexArrayElementsInstanced( offset, count, buffer, instances ) end

-- RLGL - Textures management

---Load texture in GPU
---- Success return int
---@param size table
---@param format integer
---@param mipmapCount integer
---@return any id 
function RL.rlLoadTexture( size, format, mipmapCount ) end

---Load depth texture/renderbuffer (to be attached to fbo)
---- Success return int
---@param size table
---@param useRenderBuffer boolean
---@return any id 
function RL.rlLoadTextureDepth( size, useRenderBuffer ) end

---Unload texture from GPU memory
---@param id integer
---@return any RL.rlUnloadTexture
function  RL.rlUnloadTexture( id ) end

-- RLGL - Framebuffer management (fbo)

---Load an empty framebuffer
---- Success return int
---@param size table
---@return any fboId 
function RL.rlLoadFramebuffer( size ) end

---Attach texture/renderbuffer to a framebuffer
---@param fboId integer
---@param texId integer
---@param attachType integer
---@param texType integer
---@param mipLevel integer
---@return any RL.rlFramebufferAttach
function  RL.rlFramebufferAttach( fboId, texId, attachType, texType, mipLevel ) end

---Verify framebuffer is complete
---- Success return bool
---@param id integer
---@return any isComplete 
function RL.rlFramebufferComplete( id ) end

---Delete framebuffer from GPU
---@param id integer
---@return any RL.rlUnloadFramebuffer
function  RL.rlUnloadFramebuffer( id ) end

-- RLGL - Shaders management

---Load shader from code strings
---- Failure return nil
---- Success return int
---@param vsCode string
---@param fsCode string
---@return any success 
function RL.rlLoadShaderCode( vsCode, fsCode ) end

-- RLGL - Matrix state management

---Get internal modelview matrix
---- Success return Matrix
---@return any modelview 
function RL.rlGetMatrixModelview() end

---Get internal projection matrix
---- Success return Matrix
---@return any projection 
function RL.rlGetMatrixProjection() end

---Get internal accumulated transform matrix
---- Success return Matrix
---@return any transform 
function RL.rlGetMatrixTransform() end

---Get internal projection matrix for stereo render (selected eye)
---- Success return Matrix
---@param eye integer
---@return any projection 
function RL.rlGetMatrixProjectionStereo( eye ) end

---Get internal view offset matrix for stereo render (selected eye)
---- Success return Matrix
---@param eye integer
---@return any viewOffset 
function RL.rlGetMatrixViewOffsetStereo( eye ) end

---Set a custom projection matrix (replaces internal projection matrix)
---@param proj table
---@return any RL.rlSetMatrixProjection
function  RL.rlSetMatrixProjection( proj ) end

---Set a custom modelview matrix (replaces internal modelview matrix)
---@param view table
---@return any RL.rlSetMatrixModelview
function  RL.rlSetMatrixModelview( view ) end

---Set eyes projection matrices for stereo rendering
---@param right table
---@param left table
---@return any RL.rlSetMatrixProjectionStereo
function  RL.rlSetMatrixProjectionStereo( right, left ) end

---Set eyes view offsets matrices for stereo rendering
---@param right table
---@param left table
---@return any RL.rlSetMatrixViewOffsetStereo
function  RL.rlSetMatrixViewOffsetStereo( right, left ) end

-- OpenGL - Framebuffer management

---Copy a block of pixels from one framebuffer object to another.
---Use -1 RenderTexture for window framebuffer.
---@param srcTex any
---@param dstTex any
---@param srcRect table
---@param dstRect table
---@param mask integer
---@param filter integer
---@return any RL.glBlitFramebuffer
function  RL.glBlitFramebuffer( srcTex, dstTex, srcRect, dstRect, mask, filter ) end

-- Easings - Linear Easing functions

---Ease linear
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseLinear( t, b, c, d ) end

-- Easings - Sine Easing functions

---Ease sine in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineIn( t, b, c, d ) end

---Ease sine out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineOut( t, b, c, d ) end

---Ease sine in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineInOut( t, b, c, d ) end

-- Easings - Circular Easing functions

---Ease circle in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircIn( t, b, c, d ) end

---Ease circle out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircOut( t, b, c, d ) end

---Ease circle in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircInOut( t, b, c, d ) end

-- Easings - Cubic Easing functions

---Ease cubic in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicIn( t, b, c, d ) end

---Ease cubic out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicOut( t, b, c, d ) end

---Ease cubic in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicInOut( t, b, c, d ) end

-- Easings - Quadratic Easing functions

---Ease quadratic in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadIn( t, b, c, d ) end

---Ease quadratic out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadOut( t, b, c, d ) end

---Ease quadratic in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadInOut( t, b, c, d ) end

-- Easings - Exponential Easing functions

---Ease exponential in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoIn( t, b, c, d ) end

---Ease exponential out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoOut( t, b, c, d ) end

---Ease exponential in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoInOut( t, b, c, d ) end

-- Easings - Back Easing functions

---Ease back in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackIn( t, b, c, d ) end

---Ease back out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackOut( t, b, c, d ) end

---Ease back in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackInOut( t, b, c, d ) end

-- Easings - Bounce Easing functions

---Ease bounce in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceIn( t, b, c, d ) end

---Ease bounce out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceOut( t, b, c, d ) end

---Ease bounce in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceInOut( t, b, c, d ) end

-- Easings - Elastic Easing functions

---Ease elastic in
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticIn( t, b, c, d ) end

---Ease elastic out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticOut( t, b, c, d ) end

---Ease elastic in out
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticInOut( t, b, c, d ) end

