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

-- Globals - TextureTypes

RL.TEXTURE_TYPE_TEXTURE=0
RL.TEXTURE_TYPE_RENDER_TEXTURE=1

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

---Check if window is currently hidden ( only PLATFORM_DESKTOP )
---- Success return bool
---@return any state 
function RL.IsWindowHidden() end

---Check if window is currently minimized ( only PLATFORM_DESKTOP )
---- Success return bool
---@return any state 
function RL.IsWindowMinimized() end

---Check if window is currently maximized ( only PLATFORM_DESKTOP )
---- Success return bool
---@return any state 
function RL.IsWindowMaximized() end

---Check if window is currently focused ( only PLATFORM_DESKTOP )
---- Success return bool
---@return any state 
function RL.IsWindowFocused() end

---Set monitor for the current window (fullscreen mode)
---- Failure return false
---- Success return true
---@param monitor integer
---@return any success 
function RL.SetWindowMonitor( monitor ) end

---Set window position on screen
---- Failure return false
---- Success return true
---@param pos table
---@return any success 
function RL.SetWindowPosition( pos ) end

---Set window dimensions
---- Failure return false
---- Success return true
---@param size table
---@return any success 
function RL.SetWindowSize( size ) end

---Set window minimum dimensions ( for FLAG_WINDOW_RESIZABLE )
---- Failure return false
---- Success return true
---@param size table
---@return any success 
function RL.SetWindowMinSize( size ) end

---Get specified monitor position
---- Failure return nil
---- Success return Vector2
---@param monitor integer
---@return any position 
function RL.GetMonitorPosition( monitor ) end

---Get specified monitor size
---- Failure return nil
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

---Set window configuration state using flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )
---- Failure return false
---- Success return true
---@param flag integer
---@return any success 
function RL.SetWindowState( flag ) end

---Check if one specific window flag is enabled ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )
---- Failure return nil
---- Success return bool
---@param flag integer
---@return any state 
function RL.IsWindowState( flag ) end

---Clear window configuration state flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )
---- Success return bool
---@param flag integer
---@return any resized 
function RL.ClearWindowState( flag ) end

---Check if window has been resized from last frame
---- Success return bool
---@return any resized 
function RL.IsWindowResized() end

---Set icon for window ( Only PLATFORM_DESKTOP )
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.SetWindowIcon( image ) end

---Set title for window ( Only PLATFORM_DESKTOP )
---- Failure return false
---- Success return true
---@param title string
---@return any success 
function RL.SetWindowTitle( title ) end

---Get number of connected monitors
---- Success return int
---@return any count 
function RL.GetMonitorCount() end

---Get current connected monitor
---- Success return int
---@return any monitor 
function RL.GetCurrentMonitor() end

---Get specified monitor physical size in millimetres
---- Failure return false
---- Success return Vector2
---@param monitor integer
---@return any size 
function RL.GetMonitorPhysicalSize( monitor ) end

---Get specified monitor refresh rate
---- Failure return false
---- Success return int
---@param monitor integer
---@return any size 
function RL.GetMonitorRefreshRate( monitor ) end

---Get window scale DPI factor
---- Success return Vector2
---@return any scale 
function RL.GetWindowScaleDPI() end

---Get the human-readable, UTF-8 encoded name of the monitor
---- Failure return false
---- Success return string
---@param monitor integer
---@return any name 
function RL.GetMonitorName( monitor ) end

---Close window and unload OpenGL context and free all resources
---@return any RL.CloseWindow
function  RL.CloseWindow() end

---Set clipboard text content
---- Failure return false
---- Success return true
---@param text string
---@return any success 
function RL.SetClipboardText( text ) end

---Get clipboard text content
---- Success return string
---@return any text 
function RL.GetClipboardText() end

-- Core - Timing

---Set target FPS ( maximum )
---- Failure return false
---- Success return true
---@param fps integer
---@return any success 
function RL.SetTargetFPS( fps ) end

---Get current FPS
---- Success return int
---@return any FPS 
function RL.GetFPS() end

---Get time in seconds for last frame drawn ( Delta time )
---- Success return float
---@return any delta 
function RL.GetFrameTime() end

---Get elapsed time in seconds since InitWindow()
---- Success return float
---@return any time 
function RL.GetTime() end

-- Core - Misc

---Takes a screenshot of current screen ( filename extension defines format )
---- Failure return false
---- Success return true
---@param fileName string
---@return any success 
function RL.TakeScreenshot( fileName ) end

---Setup init configuration flags ( view FLAGS )
---- Failure return false
---- Success return true
---@param flags integer
---@return any success 
function RL.SetConfigFlags( flags ) end

---Show trace log messages ( LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR... )
---- Failure return false
---- Success return true
---@param logLevel integer
---@param text string
---@return any success 
function RL.TraceLog( logLevel, text ) end

---Set the current threshold ( minimum ) log level
---- Failure return false
---- Success return true
---@param logLevel integer
---@return any success 
function RL.SetTraceLogLevel( logLevel ) end

---Set the log level for bad function calls and invalid data formats.
---- Failure return false
---- Success return true
---@param logLevel integer
---@return any success 
function RL.SetLogLevelInvalid( logLevel ) end

---Get the log level for bad function calls and invalid data formats.
---- Success return int
---@return any logLevel 
function RL.GetLogLevelInvalid() end

---Open URL with default system browser ( If available )
---- Failure return false
---- Success return true
---@param url string
---@return any success 
function RL.OpenURL( url ) end

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

---Set background color ( framebuffer clear color )
---- Failure return false
---- Success return true
---@param color table
---@return any success 
function RL.ClearBackground( color ) end

---Setup canvas ( framebuffer ) to start drawing
---@return any RL.BeginDrawing
function  RL.BeginDrawing() end

---End canvas drawing and swap buffers ( double buffering )
---@return any RL.EndDrawing
function  RL.EndDrawing() end

---Begin blending mode ( BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED... )
---- Failure return false
---- Success return true
---@param mode integer
---@return any success 
function RL.BeginBlendMode( mode ) end

---End blending mode ( reset to default: BLEND_ALPHA )
---@return any RL.EndBlendMode
function  RL.EndBlendMode() end

---Begin scissor mode ( define screen area for following drawing )
---- Failure return false
---- Success return true
---@param rectange table
---@return any success 
function RL.BeginScissorMode( rectange ) end

---End scissor mode
---@return any RL.EndScissorMode
function  RL.EndScissorMode() end

-- Core - Shader

---Load shader from files and bind default locations.
---NOTE: Set nil if no shader
---- Failure return -1
---- Success return int
---@param vsFileName string
---@param fsFileName string
---@return any shader 
function RL.LoadShader( vsFileName, fsFileName ) end

---Load shader from code strings and bind default locations
---NOTE: Set nil if no shader
---- Failure return -1
---- Success return int
---@param vsCode string
---@param fsCode string
---@return any shader 
function RL.LoadShaderFromMemory( vsCode, fsCode ) end

---Begin custom shader drawing
---- Failure return false
---- Success return true
---@param shader any
---@return any success 
function RL.BeginShaderMode( shader ) end

---End custom shader drawing ( use default shader )
---@return any RL.EndShaderMode
function  RL.EndShaderMode() end

---Get shader uniform location
---- Failure return -1
---- Success return int
---@param shader any
---@param uniformName string
---@return any location 
function RL.GetShaderLocation( shader, uniformName ) end

---Get shader attribute location
---- Failure return -1
---- Success return int
---@param shader any
---@param attribName string
---@return any location 
function RL.GetShaderLocationAttrib( shader, attribName ) end

---Set shader location index
---- Failure return false
---- Success return true
---@param shader any
---@param shaderLocationIndex integer
---@param location integer
---@return any success 
function RL.SetShaderLocationIndex( shader, shaderLocationIndex, location ) end

---Get shader location index
---- Failure return false
---- Success return int
---@param shader any
---@param shaderLocationIndex integer
---@return any location 
function RL.GetShaderLocationIndex( shader, shaderLocationIndex ) end

---Set shader uniform value ( matrix 4x4 )
---- Failure return false
---- Success return true
---@param shader any
---@param locIndex integer
---@param mat table
---@return any success 
function RL.SetShaderValueMatrix( shader, locIndex, mat ) end

---Set shader uniform value for texture ( sampler2d )
---- Failure return false
---- Success return true
---@param shader any
---@param locIndex integer
---@param texture any
---@return any success 
function RL.SetShaderValueTexture( shader, locIndex, texture ) end

---Set shader uniform value
---NOTE: Even one value should be in table
---- Failure return false
---- Success return true
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@return any success 
function RL.SetShaderValue( shader, locIndex, values, uniformType ) end

---Set shader uniform value vector
---NOTE: Even one value should be in table
---- Failure return false
---- Success return true
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@param count integer
---@return any success 
function RL.SetShaderValueV( shader, locIndex, values, uniformType, count ) end

---Unload shader from GPU memory ( VRAM )
---- Failure return false
---- Success return true
---@param shader any
---@return any success 
function RL.UnloadShader( shader ) end

-- Core - Input-related Keyboard

---Detect if a key has been pressed once
---- Failure return nil
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyPressed( key ) end

---Detect if a key is being pressed
---- Failure return nil
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyDown( key ) end

---Detect if a key has been released once
---- Failure return nil
---- Success return bool
---@param key integer
---@return any released 
function RL.IsKeyReleased( key ) end

---Check if a key is NOT being pressed
---- Failure return nil
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

---Set a custom key to exit program ( default is ESC )
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
---- Failure return -1
---- Success return string or nil
---@param key integer
---@param scancode integer
---@return any keyName 
function RL.GetKeyName( key, scancode ) end

---This function returns the platform-specific scancode of the specified key.
---If the key is KEY_UNKNOWN or does not exist on the keyboard this method will return -1.
---- Failure return nil
---- Success return int
---@param key integer
---@return any scancode 
function RL.GetKeyScancode( key ) end

-- Core - Input-related Gamepad

---Detect if a gamepad is available
---- Failure return nil
---- Success return bool
---@param gamepad integer
---@return any available 
function RL.IsGamepadAvailable( gamepad ) end

---Detect if a gamepad button has been pressed once
---- Failure return nil
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any pressed 
function RL.IsGamepadButtonPressed( gamepad, button ) end

---Detect if a gamepad button is being pressed
---- Failure return nil
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any pressed 
function RL.IsGamepadButtonDown( gamepad, button ) end

---Detect if a gamepad button has been released once
---- Failure return nil
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any released 
function RL.IsGamepadButtonReleased( gamepad, button ) end

---Return gamepad axis count for a gamepad
---- Failure return false
---- Success return int
---@param gamepad integer
---@return any count 
function RL.GetGamepadAxisCount( gamepad ) end

---Return axis movement value for a gamepad axis
---- Failure return false
---- Success return float
---@param gamepad integer
---@param axis integer
---@return any value 
function RL.GetGamepadAxisMovement( gamepad, axis ) end

---Return gamepad internal name id
---- Failure return false
---- Success return string
---@param gamepad integer
---@return any name 
function RL.GetGamepadName( gamepad ) end

-- Core - Input-related Mouse

---Detect if a mouse button has been pressed once
---- Failure return nil
---- Success return bool
---@param button integer
---@return any pressed 
function RL.IsMouseButtonPressed( button ) end

---Detect if a mouse button is being pressed
---- Failure return nil
---- Success return bool
---@param button integer
---@return any pressed 
function RL.IsMouseButtonDown( button ) end

---Detect if a mouse button has been released once
---- Failure return nil
---- Success return bool
---@param button integer
---@return any released 
function RL.IsMouseButtonReleased( button ) end

---Check if a mouse button is NOT being pressed
---- Failure return nil
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
---- Failure return false
---- Success return true
---@param position table
---@return any success 
function RL.SetMousePosition( position ) end

---Set mouse offset
---- Failure return false
---- Success return true
---@param offset table
---@return any success 
function RL.SetMouseOffset( offset ) end

---Set mouse scaling
---- Failure return false
---- Success return true
---@param scale table
---@return any success 
function RL.SetMouseScale( scale ) end

---Returns mouse wheel movement Y
---- Success return float
---@return any movement 
function RL.GetMouseWheelMove() end

---Set mouse cursor
---- Failure return false
---- Success return true
---@param cursor integer
---@return any success 
function RL.SetMouseCursor( cursor ) end

-- Core - Input-related Touch

---Get touch position XY for a touch point index ( relative to screen size )
---- Failure return false
---- Success return Vector2
---@param index integer
---@return any position 
function RL.GetTouchPosition( index ) end

---Get touch point identifier for given index
---- Failure return false
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
---- Failure return false
---- Success return true
---@param int any
---@return any success 
function RL.SetGesturesEnabled( int ) end

---Check if a gesture have been detected
---- Failure return nil
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

---Return game directory ( where main.lua is located )
---- Success return string
---@return any path 
function RL.GetBasePath() end

---Check if file exists
---- Failure return nil
---- Success return bool
---@param fileName string
---@return any fileExists 
function RL.FileExists( fileName ) end

---Check if a directory path exists
---- Failure return nil
---- Success return bool
---@param dirPath string
---@return any dirExists 
function RL.DirectoryExists( dirPath ) end

---Check file extension ( Including point: .png, .wav )
---- Failure return nil
---- Success return bool
---@param fileName string
---@param ext string
---@return any hasFileExtension 
function RL.IsFileExtension( fileName, ext ) end

---Get file length in bytes ( NOTE: GetFileSize() conflicts with windows.h )
---- Failure return false
---- Success return int
---@param fileName string
---@return any length 
function RL.GetFileLength( fileName ) end

---Get pointer to extension for a filename string ( Includes dot: '.png' )
---- Failure return false
---- Success return string
---@param fileName string
---@return any extension 
function RL.GetFileExtension( fileName ) end

---Get pointer to filename for a path string
---- Failure return false
---- Success return string
---@param filePath string
---@return any filePath 
function RL.GetFileName( filePath ) end

---Get filename string without extension ( Uses static string )
---- Failure return false
---- Success return string
---@param filePath string
---@return any filePath 
function RL.GetFileNameWithoutExt( filePath ) end

---Get full path for a given fileName with path ( Uses static string )
---- Failure return false
---- Success return string
---@param filePath string
---@return any filePath 
function RL.GetDirectoryPath( filePath ) end

---Get previous directory path for a given path ( Uses static string )
---- Failure return false
---- Success return string
---@param dirPath string
---@return any directory 
function RL.GetPrevDirectoryPath( dirPath ) end

---Get current working directory ( Uses static string )
---- Success return string
---@return any directory 
function RL.GetWorkingDirectory() end

---Load directory filepaths
---- Failure return false
---- Success return string{}
---@param dirPath string
---@return any fileNames 
function RL.LoadDirectoryFiles( dirPath ) end

---Load directory filepaths with extension filtering and recursive directory scan
---- Failure return false
---- Success return string{}
---@param basePath string
---@param filter string
---@param scanSubdirs boolean
---@return any fileNames 
function RL.LoadDirectoryFilesEx( basePath, filter, scanSubdirs ) end

---Change working directory, return true on success
---- Failure return false
---- Success return true
---@param directory string
---@return any success 
function RL.ChangeDirectory( directory ) end

---Check if a given path is a file or a directory
---- Failure return nil
---- Success return bool
---@param path string
---@return any isFile 
function RL.IsPathFile( path ) end

---Check if a file has been dropped into window
---- Success return bool
---@return any fileDropped 
function RL.IsFileDropped() end

---Load dropped filepaths
---- Success return string{}
---@return any files 
function RL.LoadDroppedFiles() end

---Get file modification time ( Last write time )
---- Failure return false
---- Success return int
---@param fileName string
---@return any time 
function RL.GetFileModTime( fileName ) end

-- Core - Camera2D

---Return camera2D id set to default configuration
---- Success return int
---@return any camera2D 
function RL.CreateCamera2D() end

---Unload Camera2D
---- Failure return false
---- Success return true
---@param camera any
---@return any success 
function RL.UnloadCamera2D( camera ) end

---Begin 2D mode with custom camera ( 2D )
---- Failure return false
---- Success return true
---@param camera any
---@return any success 
function RL.BeginMode2D( camera ) end

---Ends 2D mode with custom camera
---@return any RL.EndMode2D
function  RL.EndMode2D() end

---Set camera target ( rotation and zoom origin )
---- Failure return false
---- Success return true
---@param camera any
---@param target table
---@return any success 
function RL.SetCamera2DTarget( camera, target ) end

---Set camera offset ( displacement from target )
---- Failure return false
---- Success return true
---@param camera any
---@param offset table
---@return any success 
function RL.SetCamera2DOffset( camera, offset ) end

---Set camera rotation in degrees
---- Failure return false
---- Success return true
---@param camera any
---@param rotation number
---@return any success 
function RL.SetCamera2DRotation( camera, rotation ) end

---Set camera zoom ( scaling ), should be 1.0f by default
---- Failure return false
---- Success return true
---@param camera any
---@param zoom number
---@return any success 
function RL.SetCamera2DZoom( camera, zoom ) end

---Get camera2D target
---- Failure return nil
---- Success return Vector2
---@param camera any
---@return any target 
function RL.GetCamera2DTarget( camera ) end

---Get camera2D offset
---- Failure return nil
---- Success return Vector2
---@param camera any
---@return any offset 
function RL.GetCamera2DOffset( camera ) end

---Get camera2D rotation
---- Failure return nil
---- Success return float
---@param camera any
---@return any rotation 
function RL.GetCamera2DRotation( camera ) end

---Get camera2D zoom
---- Failure return nil
---- Success return float
---@param camera any
---@return any zoom 
function RL.GetCamera2DZoom( camera ) end

-- Core - Camera3D

---Return camera3D id set to default configuration
---- Success return int
---@return any camera 
function RL.CreateCamera3D() end

---Unload Camera3D
---- Failure return false
---- Success return true
---@param Camera3D integer
---@return any success 
function RL.UnloadCamera3D( Camera3D ) end

---Begin 3D mode with custom camera ( 3D )
---- Failure return false
---- Success return true
---@param camera any
---@return any success 
function RL.BeginMode3D( camera ) end

---Ends 3D mode and returns to default 2D orthographic mode
---@return any RL.EndMode3D
function  RL.EndMode3D() end

---Set camera position ( Remember to call "RL.UpdateCamera3D()" to apply changes )
---- Failure return false
---- Success return true
---@param camera any
---@param position table
---@return any success 
function RL.SetCamera3DPosition( camera, position ) end

---Set camera target it looks-at
---- Failure return false
---- Success return true
---@param camera any
---@param target table
---@return any success 
function RL.SetCamera3DTarget( camera, target ) end

---Set camera up vector ( Rotation over it's axis )
---- Failure return false
---- Success return true
---@param camera any
---@param up table
---@return any success 
function RL.SetCamera3DUp( camera, up ) end

---Set camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic
---- Failure return false
---- Success return true
---@param camera any
---@param fovy number
---@return any success 
function RL.SetCamera3DFovy( camera, fovy ) end

---Set camera projection mode ( CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC )
---- Failure return false
---- Success return true
---@param camera any
---@param projection integer
---@return any success 
function RL.SetCamera3DProjection( camera, projection ) end

---Get camera position
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any position 
function RL.GetCamera3DPosition( camera ) end

---Get camera target it looks-at
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any target 
function RL.GetCamera3DTarget( camera ) end

---Get camera up vector ( Rotation over it's axis )
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any up 
function RL.GetCamera3DUp( camera ) end

---Get camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic
---- Failure return nil
---- Success return float
---@param camera any
---@return any fovy 
function RL.GetCamera3DFovy( camera ) end

---Get camera projection mode
---- Failure return nil
---- Success return int
---@param camera any
---@return any projection 
function RL.GetCamera3DProjection( camera ) end

---Returns the cameras forward vector ( normalized )
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any forward 
function RL.GetCamera3DForward( camera ) end

---Returns the cameras up vector ( normalized )
---Note: The up vector might not be perpendicular to the forward vector
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any up 
function RL.GetCamera3DUpNormalized( camera ) end

---Returns the cameras right vector ( normalized )
---- Failure return nil
---- Success return Vector3
---@param camera any
---@return any right 
function RL.GetCamera3DRight( camera ) end

---Moves the camera in it's forward direction
---- Failure return false
---- Success return true
---@param camera any
---@param distance number
---@param moveInWorldPlane boolean
---@return any success 
function RL.Camera3DMoveForward( camera, distance, moveInWorldPlane ) end

---Moves the camera in it's up direction
---- Failure return false
---- Success return true
---@param camera any
---@param distance number
---@return any success 
function RL.Camera3DMoveUp( camera, distance ) end

---Moves the camera target in it's current right direction
---- Failure return false
---- Success return true
---@param camera any
---@param distance number
---@param moveInWorldPlane boolean
---@return any success 
function RL.Camera3DMoveRight( camera, distance, moveInWorldPlane ) end

---Moves the camera position closer/farther to/from the camera target
---- Failure return false
---- Success return true
---@param camera any
---@param delta number
---@return any success 
function RL.Camera3DMoveToTarget( camera, delta ) end

---Rotates the camera around it's up vector
---Yaw is "looking left and right"
---If rotateAroundTarget is false, the camera rotates around it's position
---Note: angle must be provided in radians
---- Failure return false
---- Success return true
---@param camera any
---@param angle number
---@param rotateAroundTarget boolean
---@return any success 
function RL.Camera3DYaw( camera, angle, rotateAroundTarget ) end

---Rotates the camera around it's right vector, pitch is "looking up and down"
--- - lockView prevents camera overrotation (aka "somersaults")
--- - rotateAroundTarget defines if rotation is around target or around it's position
--- - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
---NOTE: angle must be provided in radians
---- Failure return false
---- Success return true
---@param camera any
---@param angle number
---@param lockView boolean
---@param rotateAroundTarget boolean
---@param rotateUp boolean
---@return any success 
function RL.Camera3DPitch( camera, angle, lockView, rotateAroundTarget, rotateUp ) end

---Rotates the camera around it's forward vector
---Roll is "turning your head sideways to the left or right"
---Note: angle must be provided in radians
---- Failure return false
---- Success return true
---@param camera any
---@param angle number
---@return any success 
function RL.Camera3DRoll( camera, angle ) end

---Returns the camera view matrix
---- Failure return false
---- Success return Matrix
---@param camera any
---@return any view 
function RL.GetCamera3DViewMatrix( camera ) end

---Returns the camera projection matrix
---- Failure return false
---- Success return Matrix
---@param camera any
---@param aspect number
---@return any projection 
function RL.GetCamera3DProjectionMatrix( camera, aspect ) end

---Update camera position for selected mode
---- Failure return false
---- Success return true
---@param camera any
---@param mode integer
---@return any success 
function RL.UpdateCamera3D( camera, mode ) end

---Update camera movement, movement/rotation values should be provided by user
---- Failure return false
---- Success return true
---@param camera any
---@param movement table
---@param rotation table
---@param zoom number
---@return any success 
function RL.UpdateCamera3DPro( camera, movement, rotation, zoom ) end

-- Core - Screen-space

---Get a ray trace from mouse position
---- Failure return false
---- Success return Ray
---@param mousePosition table
---@param camera any
---@return any ray 
function RL.GetMouseRay( mousePosition, camera ) end

---Get camera transform matrix ( view matrix )
---- Failure return false
---- Success return Matrix
---@param camera any
---@return any matrix 
function RL.GetCameraMatrix( camera ) end

---Get camera 2d transform matrix
---- Failure return false
---- Success return Matrix
---@param camera any
---@return any matrix 
function RL.GetCameraMatrix2D( camera ) end

---Get the screen space position for a 3d world space position
---- Failure return false
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetWorldToScreen( position, camera ) end

---Get size position for a 3d world space position
---- Failure return false
---- Success return Vector2
---@param position table
---@param camera any
---@param size table
---@return any position 
function RL.GetWorldToScreenEx( position, camera, size ) end

---Get the screen space position for a 2d camera world space position
---- Failure return false
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetWorldToScreen2D( position, camera ) end

---Get the world space position for a 2d camera screen space position
---- Failure return false
---- Success return Vector2
---@param position table
---@param camera any
---@return any position 
function RL.GetScreenToWorld2D( position, camera ) end

---Creates buffer as userdata. Type should be one of the Buffer types
---- Failure return false
---- Success return Buffer
---@param buffer any
---@param type integer
---@return any buffer 
function RL.LoadBuffer( buffer, type ) end

-- Shapes - Drawing

---Set texture and rectangle to be used on shapes drawing
---NOTE: It can be useful when using basic shapes and one single font,
---defining a font char white rectangle would allow drawing everything in a single draw call
---- Failure return false
---- Success return true
---@param texture any
---@param source table
---@return any success 
function RL.SetShapesTexture( texture, source ) end

---Draw a pixel
---- Failure return false
---- Success return true
---@param pos table
---@param color table
---@return any success 
function RL.DrawPixel( pos, color ) end

---Draw a line defining thickness
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param thickness number
---@param color table
---@return any success 
function RL.DrawLine( startPos, endPos, thickness, color ) end

---Draw a line using cubic-bezier curves in-out
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param thickness number
---@param color table
---@return any success 
function RL.DrawLineBezier( startPos, endPos, thickness, color ) end

---Draw line using quadratic bezier curves with a control point
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param controlPos table
---@param thickness number
---@param color table
---@return any success 
function RL.DrawLineBezierQuad( startPos, endPos, controlPos, thickness, color ) end

---Draw line using quadratic bezier curves with a control point
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param startControlPos table
---@param endControlPos table
---@param thickness number
---@param color table
---@return any success 
function RL.DrawLineBezierCubic( startPos, endPos, startControlPos, endControlPos, thickness, color ) end

---Draw lines sequence
---- Failure return false
---- Success return true
---@param points any
---@param color table
---@return any success 
function RL.DrawLineStrip( points, color ) end

---Draw a color-filled circle
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param color table
---@return any success 
function RL.DrawCircle( center, radius, color ) end

---Draw a piece of a circle
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any success 
function RL.DrawCircleSector( center, radius, startAngle, endAngle, segments, color ) end

---Draw circle sector outline
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any success 
function RL.DrawCircleSectorLines( center, radius, startAngle, endAngle, segments, color ) end

---Draw a gradient-filled circle
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param color1 table
---@param color2 table
---@return any success 
function RL.DrawCircleGradient( center, radius, color1, color2 ) end

---Draw circle outline
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param color table
---@return any success 
function RL.DrawCircleLines( center, radius, color ) end

---Draw ellipse
---- Failure return false
---- Success return true
---@param center table
---@param radiusH number
---@param radiusV number
---@param color table
---@return any success 
function RL.DrawEllipse( center, radiusH, radiusV, color ) end

---Draw ellipse outline
---- Failure return false
---- Success return true
---@param center table
---@param radiusH number
---@param radiusV number
---@param color table
---@return any success 
function RL.DrawEllipseLines( center, radiusH, radiusV, color ) end

---Draw ring
---- Failure return false
---- Success return true
---@param center table
---@param innerRadius number
---@param outerRadius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any success 
function RL.DrawRing( center, innerRadius, outerRadius, startAngle, endAngle, segments, color ) end

---Draw ring outline
---- Failure return false
---- Success return true
---@param center table
---@param innerRadius number
---@param outerRadius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color table
---@return any success 
function RL.DrawRingLines( center, innerRadius, outerRadius, startAngle, endAngle, segments, color ) end

---Draw a color-filled rectangle
---- Failure return false
---- Success return true
---@param rec table
---@param color table
---@return any success 
function RL.DrawRectangle( rec, color ) end

---Draw a color-filled rectangle with pro parameters
---- Failure return false
---- Success return true
---@param rec table
---@param origin table
---@param rotation number
---@param color table
---@return any success 
function RL.DrawRectanglePro( rec, origin, rotation, color ) end

---Draw a vertical-gradient-filled rectangle
---- Failure return false
---- Success return true
---@param rectangle table
---@param color1 table
---@param color2 table
---@return any success 
function RL.DrawRectangleGradientV( rectangle, color1, color2 ) end

---Draw a horizontal-gradient-filled rectangle
---- Failure return false
---- Success return true
---@param rectangle table
---@param color1 table
---@param color2 table
---@return any success 
function RL.DrawRectangleGradientH( rectangle, color1, color2 ) end

---Draw a gradient-filled rectangle with custom vertex colors
---- Failure return false
---- Success return true
---@param rectangle table
---@param col1 table
---@param col2 table
---@param col3 table
---@param col4 table
---@return any success 
function RL.DrawRectangleGradientEx( rectangle, col1, col2, col3, col4 ) end

---Draw rectangle outline
---- Failure return false
---- Success return true
---@param rec table
---@param color table
---@return any success 
function RL.DrawRectangleLines( rec, color ) end

---Draw rectangle outline with extended parameters
---- Failure return false
---- Success return true
---@param rec table
---@param lineThick integer
---@param color table
---@return any success 
function RL.DrawRectangleLinesEx( rec, lineThick, color ) end

---Draw rectangle with rounded edges
---- Failure return false
---- Success return true
---@param rec table
---@param roundness number
---@param segments integer
---@param color table
---@return any success 
function RL.DrawRectangleRounded( rec, roundness, segments, color ) end

---Draw rectangle with rounded edges outline
---- Failure return false
---- Success return true
---@param rec table
---@param roundness number
---@param segments integer
---@param lineThick integer
---@param color table
---@return any success 
function RL.DrawRectangleRoundedLines( rec, roundness, segments, lineThick, color ) end

---Draw a color-filled triangle ( Vertex in counter-clockwise order! )
---- Failure return false
---- Success return true
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any success 
function RL.DrawTriangle( v1, v2, v3, color ) end

---Draw triangle outline ( Vertex in counter-clockwise order! )
---- Failure return false
---- Success return true
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any success 
function RL.DrawTriangleLines( v1, v2, v3, color ) end

---Draw a triangle fan defined by points ( first vertex is the center )
---- Failure return false
---- Success return true
---@param points any
---@param color table
---@return any success 
function RL.DrawTriangleFan( points, color ) end

---Draw a triangle strip defined by points
---- Failure return false
---- Success return true
---@param points any
---@param color table
---@return any success 
function RL.DrawTriangleStrip( points, color ) end

---Draw a regular polygon ( Vector version )
---- Failure return false
---- Success return true
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param color table
---@return any success 
function RL.DrawPoly( center, sides, radius, rotation, color ) end

---Draw a polygon outline of n sides
---- Failure return false
---- Success return true
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param color table
---@return any success 
function RL.DrawPolyLines( center, sides, radius, rotation, color ) end

---Draw a polygon outline of n sides with extended parameters
---- Failure return false
---- Success return true
---@param center table
---@param sides integer
---@param radius number
---@param rotation number
---@param lineThick number
---@param color table
---@return any success 
function RL.DrawPolyLinesEx( center, sides, radius, rotation, lineThick, color ) end

-- Shapes - Collision

---Check collision between two rectangles
---- Failure return nil
---- Success return bool
---@param rec1 table
---@param rec2 table
---@return any collision 
function RL.CheckCollisionRecs( rec1, rec2 ) end

---Check collision between two circles
---- Failure return nil
---- Success return bool
---@param center1 table
---@param radius1 number
---@param center2 table
---@param radius2 number
---@return any collision 
function RL.CheckCollisionCircles( center1, radius1, center2, radius2 ) end

---Check collision between circle and rectangle
---- Failure return nil
---- Success return bool
---@param center table
---@param radius number
---@param rec table
---@return any collision 
function RL.CheckCollisionCircleRec( center, radius, rec ) end

---Check if point is inside rectangle
---- Failure return nil
---- Success return bool
---@param point table
---@param rec table
---@return any collision 
function RL.CheckCollisionPointRec( point, rec ) end

---Check if point is inside circle
---- Failure return nil
---- Success return bool
---@param point table
---@param center table
---@param radius number
---@return any collision 
function RL.CheckCollisionPointCircle( point, center, radius ) end

---Check if point is inside a triangle
---- Failure return nil
---- Success return bool
---@param point table
---@param p1 table
---@param p2 table
---@param p3 table
---@return any collision 
function RL.CheckCollisionPointTriangle( point, p1, p2, p3 ) end

---Check if point is within a polygon described by array of vertices
---- Failure return nil
---- Success return bool
---@param point table
---@param points any
---@return any collision 
function RL.CheckCollisionPointPoly( point, points ) end

---Check the collision between two lines defined by two points each, returns collision point by reference
---- Failure return nil
---- Success return bool, Vector2
---@param startPos1 table
---@param endPos1 table
---@param startPos2 table
---@param endPos2 table
---@return any collision
---@return any position 
function RL.CheckCollisionLines( startPos1, endPos1, startPos2, endPos2 ) end

---Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
---- Failure return nil
---- Success return bool
---@param point table
---@param p1 table
---@param p2 table
---@param threshold integer
---@return any collision 
function RL.CheckCollisionPointLine( point, p1, p2, threshold ) end

---Get collision rectangle for two rectangles collision
---- Failure return nil
---- Success return Rectangle
---@param rec1 table
---@param rec2 table
---@return any rectangle 
function RL.GetCollisionRec( rec1, rec2 ) end

-- Textures - Image Loading

---Load image from file into CPU memory ( RAM )
---- Failure return -1
---- Success return int
---@param fileName string
---@return any image 
function RL.LoadImage( fileName ) end

---Load image from GPU texture data
---- Failure return -1
---- Success return int
---@param texture any
---@return any image 
function RL.LoadImageFromTexture( texture ) end

---Load image from screen buffer and ( screenshot )
---- Success return int
---@return any image 
function RL.LoadImageFromScreen() end

---Unload image from CPU memory ( RAM )
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.UnloadImage( image ) end

---Export image data to file, returns true on success
---- Failure return nil
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImage( image, fileName ) end

---Export image as code file defining an array of bytes, returns true on success
---- Failure return nil
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImageAsCode( image, fileName ) end

-- Textures - Image Generation

---Generate image: plain color
---- Failure return -1
---- Success return int
---@param width integer
---@param height integer
---@param color table
---@return any image 
function RL.GenImageColor( width, height, color ) end

---Generate image: vertical gradient
---- Failure return -1
---- Success return int
---@param size table
---@param top table
---@param bottom table
---@return any image 
function RL.GenImageGradientV( size, top, bottom ) end

---Generate image: horizontal gradient
---- Failure return -1
---- Success return int
---@param size table
---@param left table
---@param right table
---@return any image 
function RL.GenImageGradientH( size, left, right ) end

---Generate image: radial gradient
---- Failure return -1
---- Success return int
---@param size table
---@param density number
---@param inner table
---@param outer table
---@return any image 
function RL.GenImageGradientRadial( size, density, inner, outer ) end

---Generate image: checked
---- Failure return -1
---- Success return int
---@param size table
---@param checks table
---@param col1 table
---@param col2 table
---@return any image 
function RL.GenImageChecked( size, checks, col1, col2 ) end

---Generate image: white noise
---- Failure return -1
---- Success return int
---@param size table
---@param factor number
---@return any image 
function RL.GenImageWhiteNoise( size, factor ) end

---Generate image: perlin noise
---- Failure return -1
---- Success return int
---@param size table
---@param offset table
---@param factor number
---@return any image 
function RL.GenImagePerlinNoise( size, offset, factor ) end

---Generate image: cellular algorithm. Bigger tileSize means bigger cells
---- Failure return -1
---- Success return int
---@param size table
---@param tileSize integer
---@return any image 
function RL.GenImageCellular( size, tileSize ) end

---Generate image: grayscale image from text data
---- Failure return -1
---- Success return int
---@param size table
---@param text string
---@return any image 
function RL.GenImageText( size, text ) end

-- Textures - Image Manipulation Functions

---Create an image duplicate ( useful for transformations )
---- Failure return -1
---- Success return int
---@param image any
---@return any image 
function RL.ImageCopy( image ) end

---Create an image from another image piece
---- Failure return -1
---- Success return int
---@param image any
---@param rec table
---@return any image 
function RL.ImageFromImage( image, rec ) end

---Create an image from text ( custom sprite font )
---- Failure return -1
---- Success return int
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@param tint table
---@return any image 
function RL.ImageText( font, text, fontSize, spacing, tint ) end

---Convert image data to desired format
---- Failure return false
---- Success return true
---@param image any
---@param newFormat integer
---@return any success 
function RL.ImageFormat( image, newFormat ) end

---Convert image to POT ( power-of-two )
---- Failure return false
---- Success return true
---@param image any
---@param fill table
---@return any success 
function RL.ImageToPOT( image, fill ) end

---Crop an image to a defined rectangle
---- Failure return false
---- Success return true
---@param image any
---@param crop table
---@return any success 
function RL.ImageCrop( image, crop ) end

---Crop image depending on alpha value
---- Failure return false
---- Success return true
---@param image any
---@param threshold number
---@return any success 
function RL.ImageAlphaCrop( image, threshold ) end

---Clear alpha channel to desired color
---- Failure return false
---- Success return true
---@param image any
---@param color table
---@param threshold number
---@return any success 
function RL.ImageAlphaClear( image, color, threshold ) end

---Apply alpha mask to image
---- Failure return false
---- Success return true
---@param image any
---@param alphaMask any
---@return any success 
function RL.ImageAlphaMask( image, alphaMask ) end

---Premultiply alpha channel
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageAlphaPremultiply( image ) end

---Apply Gaussian blur using a box blur approximation
---- Failure return false
---- Success return true
---@param image any
---@param blurSize integer
---@return any success 
function RL.ImageBlurGaussian( image, blurSize ) end

---Resize image ( Bicubic scaling algorithm )
---- Failure return false
---- Success return true
---@param image any
---@param size table
---@return any success 
function RL.ImageResize( image, size ) end

---Resize image ( Nearest-Neighbor scaling algorithm )
---- Failure return false
---- Success return true
---@param image any
---@param size table
---@return any success 
function RL.ImageResizeNN( image, size ) end

---Resize canvas and fill with color
---- Failure return false
---- Success return true
---@param image any
---@param size table
---@param offset table
---@param fill table
---@return any success 
function RL.ImageResizeCanvas( image, size, offset, fill ) end

---Generate all mipmap levels for a provided image
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageMipmaps( image ) end

---Dither image data to 16bpp or lower ( Floyd-Steinberg dithering )
---- Failure return false
---- Success return true
---@param image any
---@param bpp table
---@return any success 
function RL.ImageDither( image, bpp ) end

---Flip image vertically
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageFlipVertical( image ) end

---Flip image horizontally
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageFlipHorizontal( image ) end

---Rotate image clockwise 90deg
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageRotateCW( image ) end

---Rotate image counter-clockwise 90deg
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageRotateCCW( image ) end

---Modify image color: tint
---- Failure return false
---- Success return true
---@param image any
---@param color table
---@return any success 
function RL.ImageColorTint( image, color ) end

---Modify image color: invert
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageColorInvert( image ) end

---Modify image color: grayscale
---- Failure return false
---- Success return true
---@param image any
---@return any success 
function RL.ImageColorGrayscale( image ) end

---Modify image color: contrast ( -100 to 100 )
---- Failure return false
---- Success return true
---@param image any
---@param contrast number
---@return any success 
function RL.ImageColorContrast( image, contrast ) end

---Modify image color: brightness ( -255 to 255 )
---- Failure return false
---- Success return true
---@param image any
---@param brightness integer
---@return any success 
function RL.ImageColorBrightness( image, brightness ) end

---Modify image color: replace color
---- Failure return false
---- Success return true
---@param image any
---@param color table
---@param replace table
---@return any success 
function RL.ImageColorReplace( image, color, replace ) end

---Load color data from image as a Color array ( RGBA - 32bit )
---- Failure return false
---- Success return Color{}
---@param image any
---@return any colors 
function RL.LoadImageColors( image ) end

---Load colors palette from image as a Color array ( RGBA - 32bit )
---- Failure return false
---- Success return Color{}
---@param image any
---@param maxPaletteSize integer
---@return any colors 
function RL.LoadImagePalette( image, maxPaletteSize ) end

---Get image alpha border rectangle
---- Failure return false
---- Success return Rectangle
---@param image any
---@param threshold number
---@return any rectangle 
function RL.GetImageAlphaBorder( image, threshold ) end

---Get image pixel color at ( x, y ) position
---- Failure return false
---- Success return Color
---@param image any
---@param pixelPos table
---@return any color 
function RL.GetImageColor( image, pixelPos ) end

-- Textures - Image Drawing

---Clear image background with given color
---- Failure return false
---- Success return true
---@param dst any
---@param color table
---@return any success 
function RL.ImageClearBackground( dst, color ) end

---Draw pixel within an image
---- Failure return false
---- Success return true
---@param dst any
---@param position table
---@param color table
---@return any success 
function RL.ImageDrawPixel( dst, position, color ) end

---Draw line within an image
---- Failure return false
---- Success return true
---@param dst any
---@param a table
---@param b table
---@param color table
---@return any success 
function RL.ImageDrawLine( dst, a, b, color ) end

---Draw circle within an image
---- Failure return false
---- Success return true
---@param dst any
---@param center table
---@param radius integer
---@param color table
---@return any success 
function RL.ImageDrawCircle( dst, center, radius, color ) end

---Draw circle outline within an image
---- Failure return false
---- Success return true
---@param dst any
---@param center table
---@param radius integer
---@param color table
---@return any success 
function RL.ImageDrawCircleLines( dst, center, radius, color ) end

---Draw rectangle within an image
---- Failure return false
---- Success return true
---@param dst any
---@param rec table
---@param color table
---@return any success 
function RL.ImageDrawRectangle( dst, rec, color ) end

---Draw rectangle lines within an image
---- Failure return false
---- Success return true
---@param dst any
---@param rec table
---@param thick integer
---@param color table
---@return any success 
function RL.ImageDrawRectangleLines( dst, rec, thick, color ) end

---Draw a source image within a destination image ( Tint applied to source )
---- Failure return false
---- Success return true
---@param dst any
---@param src any
---@param srcRec table
---@param dstRec table
---@param tint table
---@return any success 
function RL.ImageDraw( dst, src, srcRec, dstRec, tint ) end

---Draw text ( Custom sprite font ) within an image ( Destination )
---- Failure return false
---- Success return true
---@param dst any
---@param font any
---@param text string
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any success 
function RL.ImageDrawTextEx( dst, font, text, position, fontSize, spacing, tint ) end

-- Textures - Image Configuration

---Get image size
---- Failure return nil
---- Success return Vector2
---@param image any
---@return any size 
function RL.GetImageSize( image ) end

---Get image mipmaps. Mipmap levels, 1 by default
---- Failure return false
---- Success return int
---@param image any
---@return any mipmaps 
function RL.GetImageMipmaps( image ) end

---Get image data format ( PixelFormat type )
---- Failure return false
---- Success return int
---@param image any
---@return any format 
function RL.GetImageFormat( image ) end

-- Textures - Texture Loading

---Load texture from file into GPU memory ( VRAM )
---- Failure return -1
---- Success return int
---@param fileName string
---@return any texture 
function RL.LoadTexture( fileName ) end

---Load texture from image data
---- Failure return -1
---- Success return int
---@param image any
---@return any texture 
function RL.LoadTextureFromImage( image ) end

---Load cubemap from image, multiple image cubemap layouts supported
---- Failure return -1
---- Success return int
---@param image any
---@param layout integer
---@return any texture 
function RL.LoadTextureCubemap( image, layout ) end

---Load texture for rendering ( framebuffer )
---- Failure return -1
---- Success return int
---@param size table
---@return any renderTexture 
function RL.LoadRenderTexture( size ) end

---Unload texture from GPU memory ( VRAM ). NOTE! Must be texture id.
---- Failure return false
---- Success return true
---@param texture any
---@return any success 
function RL.UnloadTexture( texture ) end

---Check if a texture is ready
---- Failure return nil
---- Success return true
---@param texture any
---@return any isReady 
function RL.IsTextureReady( texture ) end

---Update GPU texture with new data
---NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
---- Failure return false
---- Success return true
---@param texture any
---@param pixels any
---@return any success 
function RL.UpdateTexture( texture, pixels ) end

---Update GPU texture rectangle with new data
---NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format
---- Failure return false
---- Success return true
---@param texture any
---@param rec table
---@param pixels any
---@return any success 
function RL.UpdateTextureRec( texture, rec, pixels ) end

-- Textures - Texture Drawing

---Draw a Texture2D
---- Failure return false
---- Success return true
---@param texture any
---@param position table
---@param tint table
---@return any success 
function RL.DrawTexture( texture, position, tint ) end

---Draw a part of a texture defined by a rectangle
---- Failure return false
---- Success return true
---@param texture any
---@param source table
---@param position table
---@param tint table
---@return any success 
function RL.DrawTextureRec( texture, source, position, tint ) end

---Draw a part of a texture defined by a rectangle with "pro" parameters
---- Failure return false
---- Success return true
---@param texture any
---@param source table
---@param dest table
---@param origin table
---@param rotation number
---@param tint table
---@return any success 
function RL.DrawTexturePro( texture, source, dest, origin, rotation, tint ) end

---Draws a texture ( or part of it ) that stretches or shrinks nicely
---- Failure return false
---- Success return true
---@param texture any
---@param nPatchInfo any
---@param dest table
---@param origin table
---@param rotation number
---@param tint table
---@return any success 
function RL.DrawTextureNPatch( texture, nPatchInfo, dest, origin, rotation, tint ) end

---Begin drawing to render texture
---- Failure return false
---- Success return true
---@param target any
---@return any success 
function RL.BeginTextureMode( target ) end

---Ends drawing to render texture
---@return any RL.EndTextureMode
function  RL.EndTextureMode() end

---Get texture type ( TEXTURE_TYPE_TEXTURE or TEXTURE_TYPE_RENDER_TEXTURE )
---- Failure return false
---- Success return int
---@param texture any
---@return any type 
function RL.GetTextureType( texture ) end

-- Textures - Texture Configuration

---Generate GPU mipmaps for a texture
---- Failure return false
---- Success return true
---@param texture any
---@return any success 
function RL.GenTextureMipmaps( texture ) end

---Set texture scaling filter mode ( TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR... )
---- Failure return false
---- Success return true
---@param texture any
---@param filter integer
---@return any success 
function RL.SetTextureFilter( texture, filter ) end

---Set texture wrapping mode ( TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP... )
---- Failure return false
---- Success return true
---@param texture any
---@param wrap integer
---@return any success 
function RL.SetTextureWrap( texture, wrap ) end

---Get texture OpenGL id
---- Failure return false
---- Success return int
---@param texture any
---@return any id 
function RL.GetTextureId( texture ) end

---Get texture size
---- Failure return false
---- Success return Vector2
---@param texture any
---@return any size 
function RL.GetTextureSize( texture ) end

---Get texture mipmaps. Mipmap levels, 1 by default
---- Failure return false
---- Success return int
---@param texture any
---@return any mipmaps 
function RL.GetTextureMipmaps( texture ) end

---Get texture data format ( PixelFormat type )
---- Failure return false
---- Success return int
---@param texture any
---@return any format 
function RL.GetTextureFormat( texture ) end

-- Textures - Color/pixel

---Returns color with alpha applied, alpha goes from 0.0f to 1.0f
---- Failure return false
---- Success return Color
---@param color table
---@param alpha number
---@return any color 
function RL.Fade( color, alpha ) end

---Returns hexadecimal value for a Color
---- Failure return false
---- Success return int
---@param color table
---@return any value 
function RL.ColorToInt( color ) end

---Returns Color normalized as float [0..1]
---- Failure return false
---- Success return Vector4
---@param color table
---@return any color 
function RL.ColorNormalize( color ) end

---Color from normalized values [0..1]
---- Failure return false
---- Success return Color
---@param normalized table
---@return any color 
function RL.ColorFromNormalized( normalized ) end

---Returns HSV values for a Color, hue [0..360], saturation/value [0..1]
---- Failure return false
---- Success return Vector3
---@param color table
---@return any HSV 
function RL.ColorToHSV( color ) end

---Returns a Color from HSV values, hue [0..360], saturation/value [0..1]
---- Failure return false
---- Success return Color
---@param hue number
---@param saturation number
---@param value number
---@return any color 
function RL.ColorFromHSV( hue, saturation, value ) end

---Get color multiplied with another color
---- Failure return false
---- Success return Color
---@param color table
---@param tint table
---@return any color 
function RL.ColorTint( color, tint ) end

---Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
---- Failure return false
---- Success return Color
---@param color table
---@param factor number
---@return any color 
function RL.ColorBrightness( color, factor ) end

---Get color with contrast correction, contrast values between -1.0f and 1.0f
---- Failure return false
---- Success return Color
---@param color table
---@param contrast number
---@return any color 
function RL.ColorContrast( color, contrast ) end

---Returns color with alpha applied, alpha goes from 0.0f to 1.0f
---- Failure return false
---- Success return Color
---@param color table
---@param alpha number
---@return any color 
function RL.ColorAlpha( color, alpha ) end

---Returns src alpha-blended into dst color with tint
---- Failure return false
---- Success return Color
---@param dst table
---@param src table
---@param tint table
---@return any color 
function RL.ColorAlphaBlend( dst, src, tint ) end

---Get Color structure from hexadecimal value
---- Failure return false
---- Success return Color
---@param int any
---@return any color 
function RL.GetColor( int ) end

---Get pixel color from source texture
---- Failure return false
---- Success return Color
---@param texture any
---@param position table
---@return any color 
function RL.GetPixelColor( texture, position ) end

---Get pixel data size in bytes for certain format
---- Failure return false
---- Success return int
---@param width integer
---@param height integer
---@param format integer
---@return any size 
function RL.GetPixelDataSize( width, height, format ) end

-- Text - Loading

---Load font from file into GPU memory ( VRAM )
---- Failure return -1
---- Success return int
---@param fileName string
---@return any font 
function RL.LoadFont( fileName ) end

---Load font from file with extended parameters. Loading the default character set
---- Failure return -1
---- Success return int
---@param fileName string
---@param fontSize integer
---@return any font 
function RL.LoadFontEx( fileName, fontSize ) end

---Load font from Image ( XNA style )
---- Failure return -1
---- Success return int
---@param image any
---@param key table
---@param firstChar integer
---@return any font 
function RL.LoadFontFromImage( image, key, firstChar ) end

---Unload Font from GPU memory ( VRAM )
---- Failure return false
---- Success return true
---@param font any
---@return any success 
function RL.UnloadFont( font ) end

-- Text - Draw

---Draw current FPS
---- Failure return false
---- Success return true
---@param pos table
---@return any success 
function RL.DrawFPS( pos ) end

---Draw text using font and additional parameters
---- Failure return false
---- Success return true
---@param font any
---@param text string
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any success 
function RL.DrawText( font, text, position, fontSize, spacing, tint ) end

---Draw text using Font and pro parameters ( rotation )
---- Failure return false
---- Success return true
---@param font any
---@param text string
---@param position table
---@param origin table
---@param rotation number
---@param fontSize number
---@param spacing number
---@param tint table
---@return any success 
function RL.DrawTextPro( font, text, position, origin, rotation, fontSize, spacing, tint ) end

-- Text - Misc

---Measure string size for Font
---- Failure return false
---- Success return Vector2
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@return any size 
function RL.MeasureText( font, text, fontSize, spacing ) end

---Get font base size ( default chars height )
---- Failure return false
---- Success return int
---@param font any
---@return any baseSize 
function RL.GetFontBaseSize( font ) end

---Get font number of glyph characters
---- Failure return false
---- Success return int
---@param font any
---@return any glyphCount 
function RL.GetFontGlyphCount( font ) end

---Get font padding around the glyph characters
---- Failure return false
---- Success return int
---@param font any
---@return any glyphPadding 
function RL.GetFontGlyphPadding( font ) end

---Get font texture atlas containing the glyphs. NOTE! Texture in table form.
---- Failure return false
---- Success return table
---@param font any
---@return any textureTable 
function RL.GetFontTexture( font ) end

-- Models - Basic

---Draw a line in 3D world space
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param color table
---@return any success 
function RL.DrawLine3D( startPos, endPos, color ) end

---Draw a point in 3D space, actually a small line
---- Failure return false
---- Success return true
---@param position table
---@param color table
---@return any success 
function RL.DrawPoint3D( position, color ) end

---Draw a circle in 3D world space
---- Failure return false
---- Success return true
---@param center table
---@param radius number
---@param rotationAxis table
---@param rotationAngle number
---@param color table
---@return any success 
function RL.DrawCircle3D( center, radius, rotationAxis, rotationAngle, color ) end

---Draw a color-filled triangle ( Vertex in counter-clockwise order! )
---- Failure return false
---- Success return true
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any success 
function RL.DrawTriangle3D( v1, v2, v3, color ) end

---Draw cube
---- Failure return false
---- Success return true
---@param position table
---@param size table
---@param color table
---@return any success 
function RL.DrawCube( position, size, color ) end

---Draw cube wires
---- Failure return false
---- Success return true
---@param position table
---@param size table
---@param color table
---@return any success 
function RL.DrawCubeWires( position, size, color ) end

---Draw sphere
---- Failure return false
---- Success return true
---@param centerPos table
---@param radius number
---@param color table
---@return any success 
function RL.DrawSphere( centerPos, radius, color ) end

---Draw sphere with extended parameters
---- Failure return false
---- Success return true
---@param centerPos table
---@param radius number
---@param rings integer
---@param slices integer
---@param color table
---@return any success 
function RL.DrawSphereEx( centerPos, radius, rings, slices, color ) end

---Draw sphere wires
---- Failure return false
---- Success return true
---@param centerPos table
---@param radius number
---@param rings integer
---@param slices integer
---@param color table
---@return any success 
function RL.DrawSphereWires( centerPos, radius, rings, slices, color ) end

---Draw a cylinder/cone
---- Failure return false
---- Success return true
---@param position table
---@param radiusTop number
---@param radiusBottom number
---@param height number
---@param slices integer
---@param color table
---@return any success 
function RL.DrawCylinder( position, radiusTop, radiusBottom, height, slices, color ) end

---Draw a cylinder with base at startPos and top at endPos
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param startRadius number
---@param endRadius number
---@param sides integer
---@param color table
---@return any success 
function RL.DrawCylinderEx( startPos, endPos, startRadius, endRadius, sides, color ) end

---Draw a cylinder/cone wires
---- Failure return false
---- Success return true
---@param position table
---@param radiusTop number
---@param radiusBottom number
---@param height number
---@param slices integer
---@param color table
---@return any success 
function RL.DrawCylinderWires( position, radiusTop, radiusBottom, height, slices, color ) end

---Draw a cylinder wires with base at startPos and top at endPos
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param startRadius number
---@param endRadius number
---@param sides integer
---@param color table
---@return any success 
function RL.DrawCylinderWiresEx( startPos, endPos, startRadius, endRadius, sides, color ) end

---Draw a capsule with the center of its sphere caps at startPos and endPos
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param radius number
---@param slices integer
---@param rings integer
---@param color table
---@return any success 
function RL.DrawCapsule( startPos, endPos, radius, slices, rings, color ) end

---Draw capsule wireframe with the center of its sphere caps at startPos and endPos
---- Failure return false
---- Success return true
---@param startPos table
---@param endPos table
---@param radius number
---@param slices integer
---@param rings integer
---@param color table
---@return any success 
function RL.DrawCapsuleWires( startPos, endPos, radius, slices, rings, color ) end

---Draw a plane XZ
---- Failure return false
---- Success return true
---@param centerPos table
---@param size table
---@param color table
---@return any success 
function RL.DrawPlane( centerPos, size, color ) end

---Draw 3D textured quad. ( Texture coordinates opengl style 0.0 - 1.0 ).
---- Failure return false
---- Success return true
---@param texture any
---@param vertices any
---@param texCoords any
---@param colors any
---@return any success 
function RL.DrawQuad3DTexture( texture, vertices, texCoords, colors ) end

---Draw a ray line
---- Failure return false
---- Success return true
---@param ray any
---@param color table
---@return any success 
function RL.DrawRay( ray, color ) end

---Draw a grid ( Centered at ( 0, 0, 0 ) )
---- Failure return false
---- Success return true
---@param slices integer
---@param spacing number
---@return any success 
function RL.DrawGrid( slices, spacing ) end

-- Models - Mesh

---Generate polygonal mesh
---- Failure return -1
---- Success return int
---@param sides integer
---@param radius number
---@return any mesh 
function RL.GenMeshPoly( sides, radius ) end

---Generate plane mesh ( With subdivisions )
---- Failure return -1
---- Success return int
---@param width number
---@param length number
---@param resX integer
---@param resZ integer
---@return any mesh 
function RL.GenMeshPlane( width, length, resX, resZ ) end

---Generate cuboid mesh
---- Failure return -1
---- Success return int
---@param size table
---@return any mesh 
function RL.GenMeshCube( size ) end

---Generate sphere mesh ( Standard sphere )
---- Failure return -1
---- Success return int
---@param radius number
---@param rings integer
---@param slices integer
---@return any mesh 
function RL.GenMeshSphere( radius, rings, slices ) end

---Generate cylinder mesh
---- Failure return -1
---- Success return int
---@param radius number
---@param height number
---@param slices integer
---@return any mesh 
function RL.GenMeshCylinder( radius, height, slices ) end

---Generate cone/pyramid mesh
---- Failure return -1
---- Success return int
---@param radius number
---@param height number
---@param slices integer
---@return any mesh 
function RL.GenMeshCone( radius, height, slices ) end

---Generate torus mesh
---- Failure return -1
---- Success return int
---@param radius number
---@param size number
---@param radSeg integer
---@param sides integer
---@return any mesh 
function RL.GenMeshTorus( radius, size, radSeg, sides ) end

---Generate torus mesh
---- Failure return -1
---- Success return int
---@param radius number
---@param size number
---@param radSeg integer
---@param sides integer
---@return any mesh 
function RL.GenMeshKnot( radius, size, radSeg, sides ) end

---Generate heightmap mesh from image data
---- Failure return -1
---- Success return int
---@param heightmap any
---@param size table
---@return any mesh 
function RL.GenMeshHeightmap( heightmap, size ) end

---Generate custom mesh from vertex attribute data and uploads it into a VAO ( if supported ) and VBO
---- Failure return -1
---- Success return int
---@param mesh any
---@param dynamic boolean
---@return any mesh 
function RL.GenMeshCustom( mesh, dynamic ) end

---Update mesh vertex data in GPU.
---Note! Mainly intented to be used with custom meshes.
---- Failure return false
---- Success return true
---@param mesh any
---@param updatedMesh any
---@return any success 
function RL.UpdateMesh( mesh, updatedMesh ) end

---Unload mesh data from CPU and GPU
---- Failure return false
---- Success return true
---@param mesh any
---@return any success 
function RL.UnloadMesh( mesh ) end

---Draw a 3d mesh with material and transform
---- Failure return false
---- Success return true
---@param mesh any
---@param material any
---@param transform table
---@return any success 
function RL.DrawMesh( mesh, material, transform ) end

---Draw multiple mesh instances with material and different transforms
---- Failure return false
---- Success return true
---@param mesh any
---@param material any
---@param transforms any
---@param instances integer
---@return any success 
function RL.DrawMeshInstanced( mesh, material, transforms, instances ) end

---Updades mesh color vertex attribute buffer
---NOTE: Currently only works on custom mesh
---- Failure return false
---- Success return true
---@param mesh any
---@param color table
---@return any success 
function RL.SetMeshColor( mesh, color ) end

---Export mesh data to file, returns true on success
---- Failure return false
---- Success return true
---@param mesh any
---@param fileName string
---@return any success 
function RL.ExportMesh( mesh, fileName ) end

---Compute mesh bounding box limits
---- Failure return false
---- Success return BoundingBox
---@param mesh any
---@return any boundingBox 
function RL.GetMeshBoundingBox( mesh ) end

---Compute mesh tangents
---- Failure return false
---- Success return true
---@param mesh any
---@return any success 
function RL.GenMeshTangents( mesh ) end

-- Models - Material

---Load default material
---- Success return int
---@return any material 
function RL.LoadMaterialDefault() end

---Load material from table. See material table definition
---- Failure return false
---- Success return int
---@param material any
---@return any material 
function RL.CreateMaterial( material ) end

---Unload material from GPU memory ( VRAM )
---- Failure return false
---- Success return true
---@param material any
---@return any success 
function RL.UnloadMaterial( material ) end

---Set texture for a material map type ( MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS... )
---- Failure return false
---- Success return true
---@param material any
---@param mapType integer
---@param texture any
---@return any success 
function RL.SetMaterialTexture( material, mapType, texture ) end

---Set color for a material map type
---- Failure return false
---- Success return true
---@param material any
---@param mapType integer
---@param color table
---@return any success 
function RL.SetMaterialColor( material, mapType, color ) end

---Set value for a material map type
---- Failure return false
---- Success return true
---@param material any
---@param mapType integer
---@param value number
---@return any success 
function RL.SetMaterialValue( material, mapType, value ) end

---Set shader for material
---- Failure return false
---- Success return true
---@param material any
---@param shader any
---@return any success 
function RL.SetMaterialShader( material, shader ) end

---Set material generic parameters ( if required )
---- Failure return false
---- Success return true
---@param material any
---@param params any
---@return any success 
function RL.SetMaterialParams( material, params ) end

---Get texture from material map type. Returns -1 if no texture.
---- Failure return false
---- Success return int
---@param material any
---@param mapType integer
---@return any texture 
function RL.GetMaterialTexture( material, mapType ) end

---Get color from material map type.
---- Failure return false
---- Success return Color
---@param material any
---@param mapType integer
---@return any color 
function RL.GetMaterialColor( material, mapType ) end

---Get color from material map type.
---- Failure return false
---- Success return float
---@param material any
---@param mapType integer
---@return any value 
function RL.GetMaterialValue( material, mapType ) end

---Get material shader. Returns -1 if no shader.
---- Failure return false
---- Success return int
---@param material any
---@return any shader 
function RL.GetMaterialShader( material ) end

---Get material parameters.
---- Failure return false
---- Success return float{}
---@param material any
---@return any params 
function RL.GetMaterialParams( material ) end

-- Models - Model

---Load model from files ( Meshes and materials )
---- Failure return -1
---- Success return int
---@param fileName string
---@return any model 
function RL.LoadModel( fileName ) end

---Load model from generated mesh ( Default material )
---- Failure return -1
---- Success return int
---@param mesh any
---@return any model 
function RL.LoadModelFromMesh( mesh ) end

---Unload model ( Including meshes ) from memory ( RAM and/or VRAM )
---- Failure return false
---- Success return true
---@param model any
---@return any success 
function RL.UnloadModel( model ) end

---Draw a model ( With texture if set )
---- Failure return false
---- Success return true
---@param model any
---@param position table
---@param scale number
---@param tint table
---@return any success 
function RL.DrawModel( model, position, scale, tint ) end

---Draw a model with extended parameters
---- Failure return false
---- Success return true
---@param model any
---@param position table
---@param rotationAxis table
---@param rotationAngle number
---@param scale table
---@param tint table
---@return any success 
function RL.DrawModelEx( model, position, rotationAxis, rotationAngle, scale, tint ) end

---Copies material to model material. ( Model material is the material id in models. Material can be deleted if not used elsewhere )
---- Failure return false
---- Success return true
---@param model any
---@param modelMaterial any
---@param material any
---@return any success 
function RL.SetModelMaterial( model, modelMaterial, material ) end

---Set material for a mesh ( Mesh and material on this model )
---- Failure return false
---- Success return true
---@param model any
---@param meshId integer
---@param materialId integer
---@return any success 
function RL.SetModelMeshMaterial( model, meshId, materialId ) end

---Draw a billboard texture
---- Failure return false
---- Success return true
---@param camera any
---@param texture any
---@param position table
---@param size number
---@param tint table
---@return any success 
function RL.DrawBillboard( camera, texture, position, size, tint ) end

---Draw a billboard texture defined by source
---- Failure return false
---- Success return true
---@param camera any
---@param texture any
---@param source table
---@param position table
---@param size table
---@param tint table
---@return any success 
function RL.DrawBillboardRec( camera, texture, source, position, size, tint ) end

---Draw a billboard texture defined by source and rotation
---- Failure return false
---- Success return true
---@param camera any
---@param texture any
---@param source table
---@param position table
---@param up table
---@param size table
---@param origin table
---@param rotation number
---@param tint table
---@return any success 
function RL.DrawBillboardPro( camera, texture, source, position, up, size, origin, rotation, tint ) end

---Set model transform matrix
---- Failure return false
---- Success return true
---@param model any
---@param transform table
---@return any success 
function RL.SetModelTransform( model, transform ) end

---Get model transform matrix
---- Failure return false
---- Success return Matrix
---@param model any
---@return any transform 
function RL.GetModelTransform( model ) end

-- Model - Animations

---Load model animations from file
---- Failure return -1
---- Success return int, int
---@param fileName string
---@return any animations
---@return any animationCount 
function RL.LoadModelAnimations( fileName ) end

---Update model animation pose
---- Failure return false
---- Success return true
---@param model any
---@param animations any
---@param animation integer
---@param frame integer
---@return any success 
function RL.UpdateModelAnimation( model, animations, animation, frame ) end

---Unload animation data
---- Failure return false
---- Success return true
---@param animations any
---@return any success 
function RL.UnloadModelAnimations( animations ) end

---Check model animation skeleton match
---- Failure return nil
---- Success return bool
---@param model any
---@param animations any
---@return any valid 
function RL.IsModelAnimationValid( model, animations ) end

---Return modelAnimation bone count
---- Failure return false
---- Success return int
---@param animations any
---@param animation integer
---@return any boneCount 
function RL.GetModelAnimationBoneCount( animations, animation ) end

---Return modelAnimation frame count
---- Failure return false
---- Success return int
---@param animations any
---@param animation integer
---@return any frameCount 
function RL.GetModelAnimationFrameCount( animations, animation ) end

-- Model - Collision

---Check collision between two spheres
---- Failure return nil
---- Success return bool
---@param center1 table
---@param radius1 number
---@param center2 table
---@param radius2 number
---@return any collision 
function RL.CheckCollisionSpheres( center1, radius1, center2, radius2 ) end

---Check collision between two bounding boxes
---- Failure return nil
---- Success return bool
---@param box1 any
---@param box2 any
---@return any collision 
function RL.CheckCollisionBoxes( box1, box2 ) end

---Check collision between box and sphere
---- Failure return nil
---- Success return bool
---@param box any
---@param center table
---@param radius number
---@return any collision 
function RL.CheckCollisionBoxSphere( box, center, radius ) end

---Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )
---- Failure return nil
---- Success return RayCollision
---@param ray any
---@param center table
---@param radius number
---@return any rayCollision 
function RL.GetRayCollisionSphere( ray, center, radius ) end

---Get collision info between ray and box
---- Failure return nil
---- Success return RayCollision
---@param ray any
---@param box any
---@return any rayCollision 
function RL.GetRayCollisionBox( ray, box ) end

---Get collision info between ray and mesh
---- Failure return nil
---- Success return RayCollision
---@param ray any
---@param mesh any
---@param transform table
---@return any rayCollision 
function RL.GetRayCollisionMesh( ray, mesh, transform ) end

---Get collision info between ray and triangle
---- Failure return nil
---- Success return RayCollision
---@param ray any
---@param p1 table
---@param p2 table
---@param p3 table
---@return any rayCollision 
function RL.GetRayCollisionTriangle( ray, p1, p2, p3 ) end

---Get collision info between ray and quad
---- Failure return nil
---- Success return RayCollision
---@param ray any
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@return any rayCollision 
function RL.GetRayCollisionQuad( ray, p1, p2, p3, p4 ) end

-- Audio - Audio device management

---Set master volume ( listener )
---- Failure return false
---- Success return true
---@param volume number
---@return any success 
function RL.SetMasterVolume( volume ) end

-- Audio - Wave/Sound Loading

---Load sound from file
---- Failure return -1
---- Success return int
---@param fileName string
---@return any sound 
function RL.LoadSound( fileName ) end

---Load wave data from file
---- Failure return -1
---- Success return int
---@param fileName string
---@return any wave 
function RL.LoadWave( fileName ) end

---Load sound from wave data
---- Failure return -1
---- Success return int
---@param wave any
---@return any sound 
function RL.LoadSoundFromWave( wave ) end

---Unload sound
---- Failure return false
---- Success return true
---@param sound any
---@return any success 
function RL.UnloadSound( sound ) end

---Unload wave data
---- Failure return false
---- Success return true
---@param wave any
---@return any success 
function RL.UnloadWave( wave ) end

---Export wave data to file, returns true on success
---- Failure return false
---- Success return true
---@param wave any
---@param fileName string
---@return any success 
function RL.ExportWave( wave, fileName ) end

---Export wave sample data to code (.h), returns true on success
---- Failure return false
---- Success return true
---@param wave any
---@param fileName string
---@return any success 
function RL.ExportWaveAsCode( wave, fileName ) end

-- Audio - Wave/Sound management

---Play a sound
---- Failure return false
---- Success return true
---@param sound any
---@return any success 
function RL.PlaySound( sound ) end

---Stop playing a sound
---- Failure return false
---- Success return true
---@param sound any
---@return any success 
function RL.StopSound( sound ) end

---Pause a sound
---- Failure return false
---- Success return true
---@param sound any
---@return any success 
function RL.PauseSound( sound ) end

---Resume a paused sound
---- Failure return false
---- Success return true
---@param sound any
---@return any success 
function RL.ResumeSound( sound ) end

---Check if a sound is currently playing
---- Failure return nil
---- Success return bool
---@param sound any
---@return any playing 
function RL.IsSoundPlaying( sound ) end

---Set volume for a sound ( 1.0 is max level )
---- Failure return false
---- Success return true
---@param sound any
---@param volume number
---@return any success 
function RL.SetSoundVolume( sound, volume ) end

---Set pitch for a sound ( 1.0 is base level )
---- Failure return false
---- Success return true
---@param sound any
---@param pitch number
---@return any success 
function RL.SetSoundPitch( sound, pitch ) end

---Set pan for a sound ( 0.5 is center )
---- Failure return false
---- Success return true
---@param sound any
---@param pan number
---@return any success 
function RL.SetSoundPan( sound, pan ) end

---Convert wave data to desired format
---- Failure return false
---- Success return true
---@param wave any
---@param sampleRate integer
---@param sampleSize integer
---@param channels integer
---@return any success 
function RL.WaveFormat( wave, sampleRate, sampleSize, channels ) end

---Copy a wave to a new wave
---- Failure return -1
---- Success return int
---@param wave any
---@return any wave 
function RL.WaveCopy( wave ) end

---Crop a wave to defined samples range
---- Failure return false
---- Success return true
---@param wave any
---@param initSample integer
---@param finalSample integer
---@return any success 
function RL.WaveCrop( wave, initSample, finalSample ) end

-- Audio - Music management

---Load music stream from file
---- Failure return -1
---- Success return int
---@param fileName string
---@return any music 
function RL.LoadMusicStream( fileName ) end

---Start music playing
---- Failure return false
---- Success return true
---@param music any
---@return any success 
function RL.PlayMusicStream( music ) end

---Check if music is playing
---- Failure return nil
---- Success return bool
---@param music any
---@return any playing 
function RL.IsMusicStreamPlaying( music ) end

---Updates buffers for music streaming
---- Failure return false
---- Success return true
---@param music any
---@return any success 
function RL.UpdateMusicStream( music ) end

---Stop music playing
---- Failure return false
---- Success return true
---@param music any
---@return any success 
function RL.StopMusicStream( music ) end

---Pause music playing
---- Failure return false
---- Success return true
---@param music any
---@return any success 
function RL.PauseMusicStream( music ) end

---Resume playing paused music
---- Failure return false
---- Success return true
---@param music any
---@return any success 
function RL.ResumeMusicStream( music ) end

---Seek music to a position ( in seconds )
---- Failure return false
---- Success return true
---@param music any
---@param position number
---@return any success 
function RL.SeekMusicStream( music, position ) end

---Set volume for music ( 1.0 is max level )
---- Failure return false
---- Success return true
---@param music any
---@param volume number
---@return any success 
function RL.SetMusicVolume( music, volume ) end

---Set pitch for a music ( 1.0 is base level )
---- Failure return false
---- Success return true
---@param music any
---@param pitch number
---@return any success 
function RL.SetMusicPitch( music, pitch ) end

---Set pan for a music ( 0.5 is center )
---- Failure return false
---- Success return true
---@param music any
---@param pan number
---@return any success 
function RL.SetMusicPan( music, pan ) end

---Set looping for a music
---- Failure return false
---- Success return true
---@param music any
---@param looping boolean
---@return any success 
function RL.SetMusicLooping( music, looping ) end

---Get looping of a music
---- Failure return nil
---- Success return bool
---@param music any
---@return any looping 
function RL.GetMusicLooping( music ) end

---Get music time length ( in seconds )
---- Failure return false
---- Success return float
---@param music any
---@return any length 
function RL.GetMusicTimeLength( music ) end

---Get current music time played ( in seconds )
---- Failure return false
---- Success return float
---@param music any
---@return any played 
function RL.GetMusicTimePlayed( music ) end

-- Math - Utils

---Clamp float value
---- Failure return false
---- Success return float
---@param value number
---@param min number
---@param max number
---@return any result 
function RL.Clamp( value, min, max ) end

---Calculate linear interpolation between two floats
---- Failure return false
---- Success return float
---@param a number
---@param b number
---@param amount number
---@return any result 
function RL.Lerp( a, b, amount ) end

---Normalize input value within input range
---- Failure return false
---- Success return float
---@param value number
---@param a number
---@param b number
---@return any result 
function RL.Normalize( value, a, b ) end

---Remap input value within input range to output range
---- Failure return false
---- Success return float
---@param value number
---@param inputStart number
---@param inputEnd number
---@param outputStart number
---@param outputEnd number
---@return any result 
function RL.Remap( value, inputStart, inputEnd, outputStart, outputEnd ) end

---Wrap input value from min to max
---- Failure return false
---- Success return float
---@param value number
---@param min number
---@param max number
---@return any result 
function RL.Wrap( value, min, max ) end

---Check whether two given floats are almost equal
---- Failure return false
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
---- Failure return false
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Add( v1, v2 ) end

---Add vector and float value
---- Failure return false
---- Success return Vector2
---@param v table
---@param add number
---@return any result 
function RL.Vector2AddValue( v, add ) end

---Subtract two vectors (v1 - v2)
---- Failure return false
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Subtract( v1, v2 ) end

---Subtract vector by float value
---- Failure return false
---- Success return Vector2
---@param v table
---@param sub number
---@return any result 
function RL.Vector2SubtractValue( v, sub ) end

---Calculate vector length
---- Failure return false
---- Success return float
---@param v any
---@return any result 
function RL.Vector2Length( v ) end

---Calculate vector square length
---- Failure return false
---- Success return float
---@param v any
---@return any result 
function RL.Vector2LengthSqr( v ) end

---Calculate two vectors dot product
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2DotProduct( v1, v2 ) end

---Calculate distance between two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Distance( v1, v2 ) end

---Calculate square distance between two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2DistanceSqr( v1, v2 ) end

---Calculate angle from two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Angle( v1, v2 ) end

---Calculate angle defined by a two vectors line.
---NOTE: Parameters need to be normalized.
---Current implementation should be aligned with glm::angle.
---- Failure return false
---- Success return float
---@param a table
---@param b table
---@return any result 
function RL.Vector2LineAngle( a, b ) end

---Scale vector ( multiply by value )
---- Failure return false
---- Success return Vector2
---@param v table
---@param scale number
---@return any result 
function RL.Vector2Scale( v, scale ) end

---Multiply vector by vector
---- Failure return false
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Multiply( v1, v2 ) end

---Negate vector
---- Failure return false
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Negate( v ) end

---Divide vector by vector
---- Failure return false
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Divide( v1, v2 ) end

---Normalize provided vector
---- Failure return false
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Normalize( v ) end

---Transforms a Vector2 by a given Matrix
---- Failure return false
---- Success return Vector2
---@param v table
---@param mat table
---@return any result 
function RL.Vector2Transform( v, mat ) end

---Calculate linear interpolation between two vectors
---- Failure return false
---- Success return Vector2
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector2Lerp( v1, v2, amount ) end

---Calculate reflected vector to normal
---- Failure return false
---- Success return Vector2
---@param v table
---@param normal table
---@return any result 
function RL.Vector2Reflect( v, normal ) end

---Rotate vector by angle
---- Failure return false
---- Success return Vector2
---@param v table
---@param angle number
---@return any result 
function RL.Vector2Rotate( v, angle ) end

---Move Vector towards target
---- Failure return false
---- Success return Vector2
---@param v table
---@param target table
---@param maxDistance number
---@return any result 
function RL.Vector2MoveTowards( v, target, maxDistance ) end

---Invert the given vector
---- Failure return false
---- Success return Vector2
---@param v table
---@return any result 
function RL.Vector2Invert( v ) end

---Clamp the components of the vector between
---min and max values specified by the given vectors
---- Failure return false
---- Success return Vector2
---@param v table
---@param min table
---@param max table
---@return any result 
function RL.Vector2Clamp( v, min, max ) end

---Clamp the magnitude of the vector between two min and max values
---- Failure return false
---- Success return Vector2
---@param v table
---@param min number
---@param max number
---@return any result 
function RL.Vector2ClampValue( v, min, max ) end

---Check whether two given vectors are almost equal
---- Failure return false
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
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Add( v1, v2 ) end

---Add vector and float value
---- Failure return false
---- Success return Vector3
---@param v table
---@param add number
---@return any result 
function RL.Vector3AddValue( v, add ) end

---Subtract two vectors
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Subtract( v1, v2 ) end

---Subtract vector by float value
---- Failure return false
---- Success return Vector3
---@param v table
---@param sub number
---@return any result 
function RL.Vector3SubtractValue( v, sub ) end

---Multiply vector by scalar
---- Failure return false
---- Success return Vector3
---@param v table
---@param scalar number
---@return any result 
function RL.Vector3Scale( v, scalar ) end

---Multiply vector by vector
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Multiply( v1, v2 ) end

---Calculate two vectors cross product
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3CrossProduct( v1, v2 ) end

---Calculate one vector perpendicular vector
---- Failure return false
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Perpendicular( v ) end

---Calculate vector length
---- Failure return false
---- Success return float
---@param v table
---@return any result 
function RL.Vector3Length( v ) end

---Calculate vector square length
---- Failure return false
---- Success return float
---@param v table
---@return any result 
function RL.Vector3LengthSqr( v ) end

---Calculate two vectors dot product
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3DotProduct( v1, v2 ) end

---Calculate distance between two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Distance( v1, v2 ) end

---Calculate square distance between two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3DistanceSqr( v1, v2 ) end

---Calculate angle between two vectors
---- Failure return false
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Angle( v1, v2 ) end

---Negate provided vector ( invert direction )
---- Failure return false
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Negate( v ) end

---Divide vector by vector
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Divide( v1, v2 ) end

---Normalize provided vector
---- Failure return false
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Normalize( v ) end

---Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
---Gram-Schmidt function implementation
---- Failure return false
---- Success return Vector3, Vector3
---@param v1 table
---@param v2 table
---@return any v1
---@return any v2 
function RL.Vector3OrthoNormalize( v1, v2 ) end

---Transforms a Vector3 by a given Matrix
---- Failure return false
---- Success return Vector3
---@param v table
---@param mat table
---@return any result 
function RL.Vector3Transform( v, mat ) end

---Transform a vector by quaternion rotation
---- Failure return false
---- Success return Vector3
---@param v table
---@param q table
---@return any result 
function RL.Vector3RotateByQuaternion( v, q ) end

---Rotates a vector around an axis
---- Failure return false
---- Success return Vector3
---@param v table
---@param axis table
---@param angle number
---@return any result 
function RL.Vector3RotateByAxisAngle( v, axis, angle ) end

---Calculate linear interpolation between two vectors
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector3Lerp( v1, v2, amount ) end

---Calculate reflected vector to normal
---- Failure return false
---- Success return Vector3
---@param v table
---@param normal table
---@return any result 
function RL.Vector3Reflect( v, normal ) end

---Get min value for each pair of components
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Min( v1, v2 ) end

---Get max value for each pair of components
---- Failure return false
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Max( v1, v2 ) end

---Compute barycenter coordinates ( u, v, w ) for point p with respect to triangle ( a, b, c )
---NOTE: Assumes P is on the plane of the triangle
---- Failure return false
---- Success return Vector3
---@param p table
---@param a table
---@param b table
---@param c table
---@return any result 
function RL.Vector3Barycenter( p, a, b, c ) end

---Projects a Vector3 from screen space into object space
---NOTE: We are avoiding calling other raymath functions despite available
---- Failure return false
---- Success return Vector3
---@param source table
---@param projection table
---@param view table
---@return any result 
function RL.Vector3Unproject( source, projection, view ) end

---Invert the given vector
---- Failure return false
---- Success return Vector3
---@param v table
---@return any result 
function RL.Vector3Invert( v ) end

---Clamp the components of the vector between
---min and max values specified by the given vectors
---- Failure return false
---- Success return Vector3
---@param v table
---@param min table
---@param max table
---@return any result 
function RL.Vector3Clamp( v, min, max ) end

---Clamp the magnitude of the vector between two values
---- Failure return false
---- Success return Vector3
---@param v table
---@param min number
---@param max number
---@return any result 
function RL.Vector3ClampValue( v, min, max ) end

---Check whether two given vectors are almost equal
---- Failure return false
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
---- Failure return false
---- Success return Vector3
---@param v table
---@param n table
---@param r number
---@return any result 
function RL.Vector3Refract( v, n, r ) end

-- Math - Matrix

---Compute matrix determinant
---- Failure return false
---- Success return float
---@param mat table
---@return any result 
function RL.MatrixDeterminant( mat ) end

---Get the trace of the matrix ( sum of the values along the diagonal )
---- Failure return false
---- Success return float
---@param mat table
---@return any result 
function RL.MatrixTrace( mat ) end

---Transposes provided matrix
---- Failure return false
---- Success return Matrix
---@param mat table
---@return any result 
function RL.MatrixTranspose( mat ) end

---Invert provided matrix
---- Failure return false
---- Success return Matrix
---@param mat table
---@return any result 
function RL.MatrixInvert( mat ) end

---Get identity matrix
---- Success return Matrix
---@return any result 
function RL.MatrixIdentity() end

---Add two matrices
---- Failure return false
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixAdd( left, right ) end

---Subtract two matrices (left - right)
---- Failure return false
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixSubtract( left, right ) end

---Get two matrix multiplication
---- Failure return false
---- Success return Matrix
---@param left table
---@param right table
---@return any result 
function RL.MatrixMultiply( left, right ) end

---Get translation matrix
---- Failure return false
---- Success return Matrix
---@param translate table
---@return any result 
function RL.MatrixTranslate( translate ) end

---Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians
---- Failure return false
---- Success return Matrix
---@param axis table
---@param angle number
---@return any result 
function RL.MatrixRotate( axis, angle ) end

---Get x-rotation matrix ( angle in radians )
---- Failure return false
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateX( angle ) end

---Get y-rotation matrix ( angle in radians )
---- Failure return false
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateY( angle ) end

---Get z-rotation matrix ( angle in radians )
---- Failure return false
---- Success return Matrix
---@param angle number
---@return any result 
function RL.MatrixRotateZ( angle ) end

---Get xyz-rotation matrix ( angles in radians )
---- Failure return false
---- Success return Matrix
---@param angle table
---@return any result 
function RL.MatrixRotateXYZ( angle ) end

---Get zyx-rotation matrix ( angles in radians )
---- Failure return false
---- Success return Matrix
---@param angle table
---@return any result 
function RL.MatrixRotateZYX( angle ) end

---Get scaling matrix
---- Failure return false
---- Success return Matrix
---@param scale table
---@return any result 
function RL.MatrixScale( scale ) end

---Get perspective projection matrix
---- Failure return false
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
---- Failure return false
---- Success return Matrix
---@param fovy any
---@param aspect any
---@param near any
---@param far any
---@return any result 
function RL.MatrixPerspective( fovy, aspect, near, far ) end

---Get orthographic projection matrix
---- Failure return false
---- Success return Matrix
---@param left any
---@param right any
---@param bottom any
---@param top any
---@param near any
---@param far any
---@return any result 
function RL.MatrixOrtho( left, right, bottom, top, near, far ) end

---Get camera look-at matrix ( View matrix )
---- Failure return false
---- Success return Matrix
---@param eye table
---@param target table
---@param up table
---@return any result 
function RL.MatrixLookAt( eye, target, up ) end

-- Math - Quaternion

---Add two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionAdd( q1, q2 ) end

---Add quaternion and float value
---- Failure return false
---- Success return Quaternion
---@param q table
---@param add number
---@return any result 
function RL.QuaternionAddValue( q, add ) end

---Subtract two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionSubtract( q1, q2 ) end

---Subtract quaternion and float value
---- Failure return false
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
---- Failure return false
---- Success return float
---@param q table
---@return any result 
function RL.QuaternionLength( q ) end

---Normalize provided quaternion
---- Failure return false
---- Success return Quaternion
---@param q table
---@return any result 
function RL.QuaternionNormalize( q ) end

---Invert provided quaternion
---- Failure return false
---- Success return Quaternion
---@param q table
---@return any result 
function RL.QuaternionInvert( q ) end

---Calculate two quaternion multiplication
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionMultiply( q1, q2 ) end

---Scale quaternion by float value
---- Failure return false
---- Success return Quaternion
---@param q table
---@param mul number
---@return any result 
function RL.QuaternionScale( q, mul ) end

---Divide two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionDivide( q1, q2 ) end

---Calculate linear interpolation between two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionLerp( q1, q2, amount ) end

---Calculate slerp-optimized interpolation between two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionNlerp( q1, q2, amount ) end

---Calculates spherical linear interpolation between two quaternions
---- Failure return false
---- Success return Quaternion
---@param q1 table
---@param q2 table
---@param amount number
---@return any result 
function RL.QuaternionSlerp( q1, q2, amount ) end

---Calculate quaternion based on the rotation from one vector to another
---- Failure return false
---- Success return Quaternion
---@param from table
---@param to table
---@return any result 
function RL.QuaternionFromVector3ToVector3( from, to ) end

---Get a quaternion for a given rotation matrix
---- Failure return false
---- Success return Quaternion
---@param mat table
---@return any result 
function RL.QuaternionFromMatrix( mat ) end

---Get a quaternion for a given rotation matrix
---- Failure return false
---- Success return Matrix
---@param q table
---@return any result 
function RL.QuaternionToMatrix( q ) end

---Get rotation quaternion for an angle and axis
---NOTE: angle must be provided in radians
---- Failure return false
---- Success return Quaternion
---@param axis table
---@param angle number
---@return any result 
function RL.QuaternionFromAxisAngle( axis, angle ) end

---Get the rotation angle and axis for a given quaternion
---- Failure return false
---- Success return Vector3, float
---@param q table
---@return any axis
---@return any angle 
function RL.QuaternionToAxisAngle( q ) end

---Get the quaternion equivalent to Euler angles
---NOTE: Rotation order is ZYX
---- Failure return false
---- Success return Quaternion
---@param pitch number
---@param yaw number
---@param roll number
---@return any result 
function RL.QuaternionFromEuler( pitch, yaw, roll ) end

---Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
---NOTE: Angles are returned in a Vector3 struct in radians
---- Failure return false
---- Success return Vector3
---@param q table
---@return any result 
function RL.QuaternionToEuler( q ) end

---Transform a quaternion given a transformation matrix
---- Failure return false
---- Success return Quaternion
---@param q table
---@param mat table
---@return any result 
function RL.QuaternionTransform( q, mat ) end

---Check whether two given quaternions are almost equal
---- Failure return false
---- Success return int
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionEquals( q1, q2 ) end

-- Gui - Global

---Enable gui controls ( global state )
---@return any RL.GuiEnable
function  RL.GuiEnable() end

---Disable gui controls ( global state )
---@return any RL.GuiDisable
function  RL.GuiDisable() end

---Lock gui controls ( global state )
---@return any RL.GuiLock
function  RL.GuiLock() end

---Unlock gui controls ( global state )
---@return any RL.GuiUnlock
function  RL.GuiUnlock() end

---Check if gui is locked ( global state )
---- Success return bool
---@return any locked 
function RL.GuiIsLocked() end

---Set gui controls alpha ( global state ), alpha goes from 0.0f to 1.0f
---- Failure return false
---- Success return true
---@param alpha number
---@return any success 
function RL.GuiFade( alpha ) end

---Set gui state ( global state )
---- Failure return false
---- Success return true
---@param state integer
---@return any success 
function RL.GuiSetState( state ) end

---Get gui state ( global state )
---- Success return int
---@return any state 
function RL.GuiGetState() end

-- Gui - Font

---Set gui custom font ( global state )
---- Failure return false
---- Success return true
---@param font any
---@return any success 
function RL.GuiSetFont( font ) end

---Get gui custom font ( global state )
---- Success return int
---@return any font 
function RL.GuiGetFont() end

-- Gui - Style

---Set one style property
---- Failure return false
---- Success return true
---@param control integer
---@param property integer
---@param value integer
---@return any success 
function RL.GuiSetStyle( control, property, value ) end

---Get one style property
---- Failure return false
---- Success return int
---@param control integer
---@param property integer
---@return any value 
function RL.GuiGetStyle( control, property ) end

---Load style file over global style variable ( .rgs )
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
---- Failure return nil
---- Success return bool
---@param bounds table
---@param title string
---@return any state 
function RL.GuiWindowBox( bounds, title ) end

---Group Box control with text name
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiGroupBox( bounds, text ) end

---Line separator control, could contain text
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiLine( bounds, text ) end

---Panel control, useful to group controls
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiPanel( bounds, text ) end

---Scroll Panel control
---- Failure return false
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
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiLabel( bounds, text ) end

---Button control, returns true when clicked
---- Failure return nil
---- Success return boolean
---@param bounds table
---@param text string
---@return any clicked 
function RL.GuiButton( bounds, text ) end

---Label button control, show true when clicked
---- Failure return nil
---- Success return boolean
---@param bounds table
---@param text string
---@return any clicked 
function RL.GuiLabelButton( bounds, text ) end

---Toggle Button control, returns true when active
---- Failure return nil
---- Success return boolean
---@param bounds table
---@param text string
---@param active boolean
---@return any active 
function RL.GuiToggle( bounds, text, active ) end

---Toggle Group control, returns active toggle index
---- Failure return false
---- Success return int
---@param bounds table
---@param text string
---@param active integer
---@return any index 
function RL.GuiToggleGroup( bounds, text, active ) end

---Check Box control, returns true when active
---- Failure return nil
---- Success return boolean
---@param bounds table
---@param text string
---@param checked boolean
---@return any active 
function RL.GuiCheckBox( bounds, text, checked ) end

---Combo Box control, returns selected item index
---- Failure return nil
---- Success return int
---@param bounds table
---@param text string
---@param active integer
---@return any active 
function RL.GuiComboBox( bounds, text, active ) end

---Text Box control, updates input text
---- Failure return nil
---- Success return boolean, string
---@param bounds table
---@param text string
---@param textSize integer
---@param editMode boolean
---@return any pressed
---@return any text 
function RL.GuiTextBox( bounds, text, textSize, editMode ) end

---Text Box control with multiple lines
---- Failure return nil
---- Success return boolean, string
---@param bounds table
---@param text string
---@param textSize integer
---@param editMode boolean
---@return any pressed
---@return any text 
function RL.GuiTextBoxMulti( bounds, text, textSize, editMode ) end

---Spinner control, returns selected value
---- Failure return nil
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
---- Failure return nil
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
---- Failure return nil
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
---- Failure return nil
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
---- Failure return nil
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
---- Failure return nil
---- Success return int
---@param bounds table
---@param value integer
---@param minValue integer
---@param maxValue integer
---@return any value 
function RL.GuiScrollBar( bounds, value, minValue, maxValue ) end

---Dropdown Box control, returns selected item
---- Failure return nil
---- Success return bool, int
---@param bounds table
---@param text string
---@param active integer
---@param editMode boolean
---@return any pressed
---@return any item 
function RL.GuiDropdownBox( bounds, text, active, editMode ) end

---Status Bar control, shows info text
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiStatusBar( bounds, text ) end

---Dummy control for placeholders
---- Failure return false
---- Success return true
---@param bounds table
---@param text string
---@return any success 
function RL.GuiDummyRec( bounds, text ) end

---Grid control, returns mouse cell position
---- Failure return false
---- Success return Vector2
---@param bounds table
---@param text string
---@param spacing number
---@param subdivs integer
---@return any cell 
function RL.GuiGrid( bounds, text, spacing, subdivs ) end

-- Gui - Advanced

---List View control, returns selected list item index and scroll index
---- Failure return nil
---- Success return int, int
---@param bounds table
---@param text string
---@param scrollIndex integer
---@param active integer
---@return any itemIndex
---@return any scrollIndex 
function RL.GuiListView( bounds, text, scrollIndex, active ) end

---List View with extended parameters, returns selected list item index, scroll index and focus
---- Failure return nil
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

---Message Box control, displays a message, returns button index ( 0 is x button )
---- Failure return false
---- Success return int
---@param bounds table
---@param title string
---@param message string
---@param buttons string
---@return any buttonIndex 
function RL.GuiMessageBox( bounds, title, message, buttons ) end

---Text Input Box control, ask for text, supports secret
---- Failure return false
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

---Color Picker control ( multiple color controls )
---- Failure return false
---- Success return Color
---@param bounds table
---@param text string
---@param color table
---@return any color 
function RL.GuiColorPicker( bounds, text, color ) end

---Color Panel control
---- Failure return false
---- Success return Color
---@param bounds table
---@param text string
---@param color table
---@return any color 
function RL.GuiColorPanel( bounds, text, color ) end

---Color Bar Alpha control
---- Failure return false
---- Success return float
---@param bounds table
---@param text string
---@param alpha number
---@return any alpha 
function RL.GuiColorBarAlpha( bounds, text, alpha ) end

---Color Bar Hue control
---- Failure return false
---- Success return float
---@param bounds table
---@param text string
---@param value number
---@return any hue 
function RL.GuiColorBarHue( bounds, text, value ) end

-- Gui - Icons

---Get text with icon id prepended ( if supported )
---- Failure return false
---- Success return string
---@param iconId integer
---@param text string
---@return any text 
function RL.GuiIconText( iconId, text ) end

---Draw icon
---- Failure return false
---- Success return true
---@param iconId integer
---@param pos table
---@param pixelSize integer
---@param color table
---@return any success 
function RL.GuiDrawIcon( iconId, pos, pixelSize, color ) end

---Set icon scale ( 1 by default )
---- Failure return false
---- Success return true
---@param scale integer
---@return any success 
function RL.GuiSetIconScale( scale ) end

---Set icon pixel value
---- Failure return false
---- Success return true
---@param iconId integer
---@param pos table
---@return any success 
function RL.GuiSetIconPixel( iconId, pos ) end

---Clear icon pixel value
---- Failure return false
---- Success return true
---@param iconId integer
---@param pos table
---@return any success 
function RL.GuiClearIconPixel( iconId, pos ) end

---Check icon pixel value
---- Failure return nil
---- Success return bool
---@param iconId integer
---@param pos table
---@return any value 
function RL.GuiCheckIconPixel( iconId, pos ) end

-- Lights - Basics

---Create a light and get shader locations
---- Failure return -1
---- Success return int
---@param type integer
---@param position table
---@param target table
---@param color table
---@param shader any
---@return any light 
function RL.CreateLight( type, position, target, color, shader ) end

---Send light properties to shader
---- Failure return false
---- Success return true
---@param shader any
---@param light any
---@return any success 
function RL.UpdateLightValues( shader, light ) end

---Set light type
---- Failure return false
---- Success return true
---@param light any
---@param type integer
---@return any success 
function RL.SetLightType( light, type ) end

---Set light position
---- Failure return false
---- Success return true
---@param light any
---@param position table
---@return any success 
function RL.SetLightPosition( light, position ) end

---Set light target
---- Failure return false
---- Success return true
---@param light any
---@param target table
---@return any success 
function RL.SetLightTarget( light, target ) end

---Set light color
---- Failure return false
---- Success return true
---@param light any
---@param color table
---@return any success 
function RL.SetLightColor( light, color ) end

---Set light enabled
---- Failure return false
---- Success return true
---@param light any
---@param enabled boolean
---@return any success 
function RL.SetLightEnabled( light, enabled ) end

---Get light type
---- Failure return false
---- Success return int
---@param light any
---@return any type 
function RL.GetLightType( light ) end

---Get light position
---- Failure return false
---- Success return Vector3
---@param light any
---@return any position 
function RL.GetLightPosition( light ) end

---Get light target
---- Failure return false
---- Success return Vector3
---@param light any
---@return any target 
function RL.GetLightTarget( light ) end

---Get light color
---- Failure return false
---- Success return Color
---@param light any
---@return any color 
function RL.GetLightColor( light ) end

---Get light enabled
---- Failure return nil
---- Success return boolean
---@param light any
---@return any enabled 
function RL.IsLightEnabled( light ) end

-- RLGL - Matrix operations

---Choose the current matrix to be transformed
---- Failure return false
---- Success return true
---@param mode integer
---@return any success 
function RL.rlMatrixMode( mode ) end

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
---- Failure return false
---- Success return true
---@param translation table
---@return any success 
function RL.rlTranslatef( translation ) end

---Multiply the current matrix by a rotation matrix
---- Failure return false
---- Success return true
---@param angle number
---@param rotation table
---@return any success 
function RL.rlRotatef( angle, rotation ) end

---Multiply the current matrix by a scaling matrix
---- Failure return false
---- Success return true
---@param scale table
---@return any success 
function RL.rlScalef( scale ) end

---Multiply the current matrix by another matrix
---- Failure return false
---- Success return true
---@param matrix table
---@return any success 
function RL.rlMultMatrixf( matrix ) end

---Multiply the current matrix by a perspective matrix generated by parameters
---- Failure return false
---- Success return true
---@param left number
---@param right number
---@param bottom number
---@param top number
---@param znear number
---@param zfar number
---@return any success 
function RL.rlFrustum( left, right, bottom, top, znear, zfar ) end

---Multiply the current matrix by an orthographic matrix generated by parameters
---- Failure return false
---- Success return true
---@param left number
---@param right number
---@param bottom number
---@param top number
---@param znear number
---@param zfar number
---@return any success 
function RL.rlOrtho( left, right, bottom, top, znear, zfar ) end

---Set the viewport area ( transformation from normalized device coordinates to window coordinates )
---NOTE: We store current viewport dimensions
---- Failure return false
---- Success return true
---@param viewport table
---@return any success 
function RL.rlViewport( viewport ) end

-- RLGL - Vertex level operations

---Initialize drawing mode ( how to organize vertex )
---- Failure return false
---- Success return true
---@param mode integer
---@return any success 
function RL.rlBegin( mode ) end

---Finish vertex providing
---@return any RL.rlEnd
function  RL.rlEnd() end

---Define one vertex ( position )
---- Failure return false
---- Success return true
---@param position table
---@return any success 
function RL.rlVertex2f( position ) end

---Define one vertex ( position )
---- Failure return false
---- Success return true
---@param position table
---@return any success 
function RL.rlVertex3f( position ) end

---Define one vertex ( texture coordinate ) - 2 float
---- Failure return false
---- Success return true
---@param texCoord table
---@return any success 
function RL.rlTexCoord2f( texCoord ) end

---Define one vertex ( normal ) - 3 float
---- Failure return false
---- Success return true
---@param normal table
---@return any success 
function RL.rlNormal3f( normal ) end

---Define one vertex ( color ) - 4 byte
---- Failure return false
---- Success return true
---@param color table
---@return any success 
function RL.rlColor4ub( color ) end

---Define one vertex ( color ) - 3 float
---- Failure return false
---- Success return true
---@param color table
---@return any success 
function RL.rlColor3f( color ) end

---Define one vertex ( color ) - 4 float
---- Failure return false
---- Success return true
---@param color table
---@return any success 
function RL.rlColor4f( color ) end

-- RLGL - Vertex buffers state

---Enable vertex array ( VAO, if supported )
---- Failure return nil
---- Success return bool
---@param vaoId integer
---@return any supported 
function RL.rlEnableVertexArray( vaoId ) end

---Disable vertex array ( VAO, if supported )
---@return any RL.rlDisableVertexArray
function  RL.rlDisableVertexArray() end

---Enable vertex buffer ( VBO )
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableVertexBuffer( id ) end

---Disable vertex buffer ( VBO )
---@return any RL.rlDisableVertexBuffer
function  RL.rlDisableVertexBuffer() end

---Enable vertex buffer element ( VBO element )
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableVertexBufferElement( id ) end

---Disable vertex buffer element ( VBO element )
---@return any RL.rlDisableVertexBufferElement
function  RL.rlDisableVertexBufferElement() end

---Enable vertex attribute index
---- Failure return false
---- Success return true
---@param index integer
---@return any success 
function RL.rlEnableVertexAttribute( index ) end

---Disable vertex attribute index
---- Failure return false
---- Success return true
---@param index integer
---@return any success 
function RL.rlDisableVertexAttribute( index ) end

-- RLGL - Textures state

---Select and active a texture slot
---- Failure return false
---- Success return true
---@param slot integer
---@return any success 
function RL.rlActiveTextureSlot( slot ) end

---Enable texture
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableTexture( id ) end

---Disable texture
---@return any RL.rlDisableTexture
function  RL.rlDisableTexture() end

---Enable texture cubemap
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableTextureCubemap( id ) end

---Disable texture cubemap
---@return any RL.rlDisableTextureCubemap
function  RL.rlDisableTextureCubemap() end

---Set texture parameters ( filter, wrap )
---- Failure return false
---- Success return true
---@param id integer
---@param param integer
---@param value integer
---@return any success 
function RL.rlTextureParameters( id, param, value ) end

---Set cubemap parameters ( filter, wrap )
---- Failure return false
---- Success return true
---@param id integer
---@param param integer
---@param value integer
---@return any success 
function RL.rlCubemapParameters( id, param, value ) end

-- RLGL - Shader state

---Enable shader program
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableShader( id ) end

---Disable shader program
---@return any RL.rlDisableShader
function  RL.rlDisableShader() end

-- RLGL - Framebuffer state

---Enable render texture (fbo)
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlEnableFramebuffer( id ) end

---Disable render texture (fbo), return to default framebuffer
---@return any RL.rlDisableFramebuffer
function  RL.rlDisableFramebuffer() end

---Activate multiple draw color buffers
---- Failure return false
---- Success return true
---@param count integer
---@return any success 
function RL.rlActiveDrawBuffers( count ) end

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
---- Failure return false
---- Success return true
---@param mode integer
---@return any success 
function RL.rlSetCullFace( mode ) end

---Enable scissor test
---@return any RL.rlEnableScissorTest
function  RL.rlEnableScissorTest() end

---Disable scissor test
---@return any RL.rlDisableScissorTest
function  RL.rlDisableScissorTest() end

---Scissor test
---- Failure return false
---- Success return true
---@param area table
---@return any success 
function RL.rlScissor( area ) end

---Enable wire mode
---@return any RL.rlEnableWireMode
function  RL.rlEnableWireMode() end

---Disable wire mode
---@return any RL.rlDisableWireMode
function  RL.rlDisableWireMode() end

---Set the line drawing width
---- Failure return false
---- Success return true
---@param width number
---@return any success 
function RL.rlSetLineWidth( width ) end

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
---- Failure return false
---- Success return true
---@param color table
---@return any success 
function RL.rlClearColor( color ) end

---Clear used screen buffers ( color and depth )
---@return any RL.rlClearScreenBuffers
function  RL.rlClearScreenBuffers() end

---Check and log OpenGL error codes
---@return any RL.rlCheckErrors
function  RL.rlCheckErrors() end

---Set blending mode
---- Failure return false
---- Success return true
---@param mode integer
---@return any success 
function RL.rlSetBlendMode( mode ) end

---Set blending mode factor and equation ( using OpenGL factors )
---- Failure return false
---- Success return true
---@param glSrcFactor integer
---@param glDstFactor integer
---@param glEquation integer
---@return any success 
function RL.rlSetBlendFactors( glSrcFactor, glDstFactor, glEquation ) end

---Set blending mode factors and equations separately ( using OpenGL factors )
---- Failure return false
---- Success return true
---@param glSrcRGB integer
---@param glDstRGB integer
---@param glSrcAlpha integer
---@param glDstAlpha integer
---@param glEqRGB integer
---@param glEqAlpha integer
---@return any success 
function RL.rlSetBlendFactorsSeparate( glSrcRGB, glDstRGB, glSrcAlpha, glDstAlpha, glEqRGB, glEqAlpha ) end

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
---- Failure return nil
---- Success return bool
---@param vCount integer
---@return any overflow 
function RL.rlCheckRenderBatchLimit( vCount ) end

---Set current texture for render batch and check buffers limits
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlSetTexture( id ) end

-- RLGL - Vertex buffers management

---Load vertex array (vao) if supported
---- Success return int
---@return any vaoId 
function RL.rlLoadVertexArray() end

---Load a vertex buffer attribute
---- Failure return -1
---- Success return int
---@param buffer any
---@param dynamic boolean
---@return any vboId 
function RL.rlLoadVertexBuffer( buffer, dynamic ) end

---Load a new attributes element buffer
---- Failure return -1
---- Success return int
---@param buffer any
---@param dynamic boolean
---@return any vboId 
function RL.rlLoadVertexBufferElement( buffer, dynamic ) end

---Update GPU buffer with new data
---- Failure return false
---- Success return true
---@param bufferId integer
---@param buffer any
---@param offset integer
---@return any success 
function RL.rlUpdateVertexBuffer( bufferId, buffer, offset ) end

---Update vertex buffer elements with new data
---- Failure return false
---- Success return true
---@param id integer
---@param buffer any
---@param offset integer
---@return any success 
function RL.rlUpdateVertexBufferElements( id, buffer, offset ) end

---Unload vertex array object (VAO)
---- Failure return false
---- Success return true
---@param vaoId integer
---@return any success 
function RL.rlUnloadVertexArray( vaoId ) end

---Unload vertex buffer (VBO)
---- Failure return false
---- Success return true
---@param vboId integer
---@return any success 
function RL.rlUnloadVertexBuffer( vboId ) end

---Set vertex attribute
---- Failure return false
---- Success return true
---@param index integer
---@param compSize integer
---@param type integer
---@param normalized boolean
---@param stride integer
---@param pointer integer
---@return any success 
function RL.rlSetVertexAttribute( index, compSize, type, normalized, stride, pointer ) end

---Set vertex attribute divisor
---- Failure return false
---- Success return true
---@param index integer
---@param divisor integer
---@return any success 
function RL.rlSetVertexAttributeDivisor( index, divisor ) end

---Set vertex attribute default value
---- Failure return false
---- Success return true
---@param locIndex integer
---@param value any
---@param attribType integer
---@return any success 
function RL.rlSetVertexAttributeDefault( locIndex, value, attribType ) end

---Draw vertex array
---- Failure return false
---- Success return true
---@param offset integer
---@param count integer
---@return any success 
function RL.rlDrawVertexArray( offset, count ) end

---Draw vertex array elements
---- Failure return false
---- Success return true
---@param offset integer
---@param count integer
---@param buffer any
---@return any success 
function RL.rlDrawVertexArrayElements( offset, count, buffer ) end

---Draw vertex array instanced
---- Failure return false
---- Success return true
---@param offset integer
---@param count integer
---@param instances integer
---@return any success 
function RL.rlDrawVertexArrayInstanced( offset, count, instances ) end

---Draw vertex array elements instanced
---- Failure return false
---- Success return true
---@param offset integer
---@param count integer
---@param buffer any
---@param instances integer
---@return any success 
function RL.rlDrawVertexArrayElementsInstanced( offset, count, buffer, instances ) end

-- RLGL - Textures management

---Load texture in GPU
---- Failure return -1
---- Success return int
---@param size table
---@param format integer
---@param mipmapCount integer
---@return any id 
function RL.rlLoadTexture( size, format, mipmapCount ) end

---Load depth texture/renderbuffer ( to be attached to fbo )
---- Failure return -1
---- Success return int
---@param size table
---@param useRenderBuffer boolean
---@return any id 
function RL.rlLoadTextureDepth( size, useRenderBuffer ) end

---Unload texture from GPU memory
---- Failure return false
---- Success return true
---@param id integer
---@return any success 
function RL.rlUnloadTexture( id ) end

-- RLGL - Framebuffer management (fbo)

---Load an empty framebuffer
---- Failure return -1
---- Success return int
---@param size table
---@return any fboId 
function RL.rlLoadFramebuffer( size ) end

---Attach texture/renderbuffer to a framebuffer
---- Failure return false
---- Success return true
---@param fboId integer
---@param texId integer
---@param attachType integer
---@param texType integer
---@param mipLevel integer
---@return any success 
function RL.rlFramebufferAttach( fboId, texId, attachType, texType, mipLevel ) end

---Verify framebuffer is complete
---- Failure return nil
---- Success return bool
---@param id integer
---@return any isComplete 
function RL.rlFramebufferComplete( id ) end

---Delete framebuffer from GPU
---- Failure return nil
---- Success return bool
---@param id integer
---@return any success 
function RL.rlUnloadFramebuffer( id ) end

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
---- Failure return false
---- Success return Matrix
---@param eye integer
---@return any projection 
function RL.rlGetMatrixProjectionStereo( eye ) end

---Get internal view offset matrix for stereo render (selected eye)
---- Failure return false
---- Success return Matrix
---@param eye integer
---@return any viewOffset 
function RL.rlGetMatrixViewOffsetStereo( eye ) end

---Set a custom projection matrix (replaces internal projection matrix)
---- Failure return false
---- Success return true
---@param proj table
---@return any success 
function RL.rlSetMatrixProjection( proj ) end

---Set a custom modelview matrix (replaces internal modelview matrix)
---- Failure return false
---- Success return true
---@param view table
---@return any success 
function RL.rlSetMatrixModelview( view ) end

---Set eyes projection matrices for stereo rendering
---- Failure return false
---- Success return true
---@param right table
---@param left table
---@return any success 
function RL.rlSetMatrixProjectionStereo( right, left ) end

---Set eyes view offsets matrices for stereo rendering
---- Failure return false
---- Success return true
---@param right table
---@param left table
---@return any success 
function RL.rlSetMatrixViewOffsetStereo( right, left ) end

-- OpenGL - Framebuffer management

---Copy a block of pixels from one framebuffer object to another.
---Use -1 RenderTexture for window framebuffer.
---- Failure return false
---- Success return true
---@param srcTex any
---@param dstTex any
---@param srcRect table
---@param dstRect table
---@param mask integer
---@param filter integer
---@return any success 
function RL.glBlitFramebuffer( srcTex, dstTex, srcRect, dstRect, mask, filter ) end

-- Easings - Linear Easing functions

---Ease linear
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseLinear( t, b, c, d ) end

-- Easings - Sine Easing functions

---Ease sine in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineIn( t, b, c, d ) end

---Ease sine out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineOut( t, b, c, d ) end

---Ease sine in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseSineInOut( t, b, c, d ) end

-- Easings - Circular Easing functions

---Ease circle in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircIn( t, b, c, d ) end

---Ease circle out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircOut( t, b, c, d ) end

---Ease circle in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCircInOut( t, b, c, d ) end

-- Easings - Cubic Easing functions

---Ease cubic in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicIn( t, b, c, d ) end

---Ease cubic out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicOut( t, b, c, d ) end

---Ease cubic in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseCubicInOut( t, b, c, d ) end

-- Easings - Quadratic Easing functions

---Ease quadratic in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadIn( t, b, c, d ) end

---Ease quadratic out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadOut( t, b, c, d ) end

---Ease quadratic in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseQuadInOut( t, b, c, d ) end

-- Easings - Exponential Easing functions

---Ease exponential in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoIn( t, b, c, d ) end

---Ease exponential out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoOut( t, b, c, d ) end

---Ease exponential in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseExpoInOut( t, b, c, d ) end

-- Easings - Back Easing functions

---Ease back in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackIn( t, b, c, d ) end

---Ease back out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackOut( t, b, c, d ) end

---Ease back in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBackInOut( t, b, c, d ) end

-- Easings - Bounce Easing functions

---Ease bounce in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceIn( t, b, c, d ) end

---Ease bounce out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceOut( t, b, c, d ) end

---Ease bounce in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseBounceInOut( t, b, c, d ) end

-- Easings - Elastic Easing functions

---Ease elastic in
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticIn( t, b, c, d ) end

---Ease elastic out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticOut( t, b, c, d ) end

---Ease elastic in out
---- Failure return false
---- Success return float
---@param t number
---@param b number
---@param c number
---@param d number
---@return any value 
function RL.EaseElasticInOut( t, b, c, d ) end

