-- Put this file into your project folder to provide annotations when using Lua language server.

RL={}

-- Functions.

---This function will be called after window has been initialized. Should be used as the main init point.
function RL.init() end
---This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'
---@param delta number
function RL.update( delta ) end
---This function will be called every frame after update and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.
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
---This function will be called before InitWindow. Note! Only place where you should call InitWindow manually. Doesn't have OpenGL context at this point.
function RL.config() end

-- Defines - System/Window config flags

---Set to try enabling V-Sync on GPU
RL.FLAG_VSYNC_HINT=64
---Set to run program in fullscreen
RL.FLAG_FULLSCREEN_MODE=2
---Set to allow resizable window
RL.FLAG_WINDOW_RESIZABLE=4
---Set to disable window decoration (frame and buttons)
RL.FLAG_WINDOW_UNDECORATED=8
---Set to hide window
RL.FLAG_WINDOW_HIDDEN=128
---Set to minimize window (iconify)
RL.FLAG_WINDOW_MINIMIZED=512
---Set to maximize window (expanded to monitor)
RL.FLAG_WINDOW_MAXIMIZED=1024
---Set to window non focused
RL.FLAG_WINDOW_UNFOCUSED=2048
---Set to window always on top
RL.FLAG_WINDOW_TOPMOST=4096
---Set to allow windows running while minimized
RL.FLAG_WINDOW_ALWAYS_RUN=256
---Set to allow transparent framebuffer
RL.FLAG_WINDOW_TRANSPARENT=16
---Set to support HighDPI
RL.FLAG_WINDOW_HIGHDPI=8192
---Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
RL.FLAG_WINDOW_MOUSE_PASSTHROUGH=16384
---Set to try enabling MSAA 4X
RL.FLAG_MSAA_4X_HINT=32
---Set to try enabling interlaced video format (for V3D)
RL.FLAG_INTERLACED_HINT=65536

-- Defines - Trace log level

---Display all logs
RL.LOG_ALL=0
---Trace logging, intended for internal use only
RL.LOG_TRACE=1
---Debug logging, used for internal debugging, it should be disabled on release builds
RL.LOG_DEBUG=2
---Info logging, used for program execution info
RL.LOG_INFO=3
---Warning logging, used on recoverable failures
RL.LOG_WARNING=4
---Error logging, used on unrecoverable failures
RL.LOG_ERROR=5
---Fatal logging, used to abort program: exit(EXIT_FAILURE)
RL.LOG_FATAL=6
---Disable logging
RL.LOG_NONE=7

-- Defines - Keyboard keys (US keyboard layout)

---Key: NULL, used for no key pressed
RL.KEY_NULL=0
---Key: '
RL.KEY_APOSTROPHE=39
---Key: ,
RL.KEY_COMMA=44
---Key: -
RL.KEY_MINUS=45
---Key: .
RL.KEY_PERIOD=46
---Key: /
RL.KEY_SLASH=47
---Key: 0
RL.KEY_ZERO=48
---Key: 1
RL.KEY_ONE=49
---Key: 2
RL.KEY_TWO=50
---Key: 3
RL.KEY_THREE=51
---Key: 4
RL.KEY_FOUR=52
---Key: 5
RL.KEY_FIVE=53
---Key: 6
RL.KEY_SIX=54
---Key: 7
RL.KEY_SEVEN=55
---Key: 8
RL.KEY_EIGHT=56
---Key: 9
RL.KEY_NINE=57
---Key: ;
RL.KEY_SEMICOLON=59
---Key: =
RL.KEY_EQUAL=61
---Key: A | a
RL.KEY_A=65
---Key: B | b
RL.KEY_B=66
---Key: C | c
RL.KEY_C=67
---Key: D | d
RL.KEY_D=68
---Key: E | e
RL.KEY_E=69
---Key: F | f
RL.KEY_F=70
---Key: G | g
RL.KEY_G=71
---Key: H | h
RL.KEY_H=72
---Key: I | i
RL.KEY_I=73
---Key: J | j
RL.KEY_J=74
---Key: K | k
RL.KEY_K=75
---Key: L | l
RL.KEY_L=76
---Key: M | m
RL.KEY_M=77
---Key: N | n
RL.KEY_N=78
---Key: O | o
RL.KEY_O=79
---Key: P | p
RL.KEY_P=80
---Key: Q | q
RL.KEY_Q=81
---Key: R | r
RL.KEY_R=82
---Key: S | s
RL.KEY_S=83
---Key: T | t
RL.KEY_T=84
---Key: U | u
RL.KEY_U=85
---Key: V | v
RL.KEY_V=86
---Key: W | w
RL.KEY_W=87
---Key: X | x
RL.KEY_X=88
---Key: Y | y
RL.KEY_Y=89
---Key: Z | z
RL.KEY_Z=90
---Key: [
RL.KEY_LEFT_BRACKET=91
---Key: '\'
RL.KEY_BACKSLASH=92
---Key: ]
RL.KEY_RIGHT_BRACKET=93
---Key: `
RL.KEY_GRAVE=96
---Key: Space
RL.KEY_SPACE=32
---Key: Esc
RL.KEY_ESCAPE=256
---Key: Enter
RL.KEY_ENTER=257
---Key: Tab
RL.KEY_TAB=258
---Key: Backspace
RL.KEY_BACKSPACE=259
---Key: Ins
RL.KEY_INSERT=260
---Key: Del
RL.KEY_DELETE=261
---Key: Cursor right
RL.KEY_RIGHT=262
---Key: Cursor left
RL.KEY_LEFT=263
---Key: Cursor down
RL.KEY_DOWN=264
---Key: Cursor up
RL.KEY_UP=265
---Key: Page up
RL.KEY_PAGE_UP=266
---Key: Page down
RL.KEY_PAGE_DOWN=267
---Key: Home
RL.KEY_HOME=268
---Key: End
RL.KEY_END=269
---Key: Caps lock
RL.KEY_CAPS_LOCK=280
---Key: Scroll down
RL.KEY_SCROLL_LOCK=281
---Key: Num lock
RL.KEY_NUM_LOCK=282
---Key: Print screen
RL.KEY_PRINT_SCREEN=283
---Key: Pause
RL.KEY_PAUSE=284
---Key: F1
RL.KEY_F1=290
---Key: F2
RL.KEY_F2=291
---Key: F3
RL.KEY_F3=292
---Key: F4
RL.KEY_F4=293
---Key: F5
RL.KEY_F5=294
---Key: F6
RL.KEY_F6=295
---Key: F7
RL.KEY_F7=296
---Key: F8
RL.KEY_F8=297
---Key: F9
RL.KEY_F9=298
---Key: F10
RL.KEY_F10=299
---Key: F11
RL.KEY_F11=300
---Key: F12
RL.KEY_F12=301
---Key: Shift left
RL.KEY_LEFT_SHIFT=340
---Key: Control left
RL.KEY_LEFT_CONTROL=341
---Key: Alt left
RL.KEY_LEFT_ALT=342
---Key: Super left
RL.KEY_LEFT_SUPER=343
---Key: Shift right
RL.KEY_RIGHT_SHIFT=344
---Key: Control right
RL.KEY_RIGHT_CONTROL=345
---Key: Alt right
RL.KEY_RIGHT_ALT=346
---Key: Super right
RL.KEY_RIGHT_SUPER=347
---Key: KB menu
RL.KEY_KB_MENU=348
---Key: Keypad 0
RL.KEY_KP_0=320
---Key: Keypad 1
RL.KEY_KP_1=321
---Key: Keypad 2
RL.KEY_KP_2=322
---Key: Keypad 3
RL.KEY_KP_3=323
---Key: Keypad 4
RL.KEY_KP_4=324
---Key: Keypad 5
RL.KEY_KP_5=325
---Key: Keypad 6
RL.KEY_KP_6=326
---Key: Keypad 7
RL.KEY_KP_7=327
---Key: Keypad 8
RL.KEY_KP_8=328
---Key: Keypad 9
RL.KEY_KP_9=329
---Key: Keypad .
RL.KEY_KP_DECIMAL=330
---Key: Keypad /
RL.KEY_KP_DIVIDE=331
---Key: Keypad *
RL.KEY_KP_MULTIPLY=332
---Key: Keypad -
RL.KEY_KP_SUBTRACT=333
---Key: Keypad +
RL.KEY_KP_ADD=334
---Key: Keypad Enter
RL.KEY_KP_ENTER=335
---Key: Keypad =
RL.KEY_KP_EQUAL=336
---Key: Android back button
RL.KEY_BACK=4
---Key: Android menu button
RL.KEY_MENU=5
---Key: Android volume up button
RL.KEY_VOLUME_UP=24
---Key: Android volume down button
RL.KEY_VOLUME_DOWN=25

-- Defines - Mouse buttons

---Mouse button left
RL.MOUSE_BUTTON_LEFT=0
---Mouse button right
RL.MOUSE_BUTTON_RIGHT=1
---Mouse button middle (pressed wheel)
RL.MOUSE_BUTTON_MIDDLE=2
---Mouse button side (advanced mouse device)
RL.MOUSE_BUTTON_SIDE=3
---Mouse button extra (advanced mouse device)
RL.MOUSE_BUTTON_EXTRA=4
---Mouse button forward (advanced mouse device)
RL.MOUSE_BUTTON_FORWARD=5
---Mouse button back (advanced mouse device)
RL.MOUSE_BUTTON_BACK=6

-- Defines - Mouse cursor

---Default pointer shape
RL.MOUSE_CURSOR_DEFAULT=0
---Arrow shape
RL.MOUSE_CURSOR_ARROW=1
---Text writing cursor shape
RL.MOUSE_CURSOR_IBEAM=2
---Cross shape
RL.MOUSE_CURSOR_CROSSHAIR=3
---Pointing hand cursor
RL.MOUSE_CURSOR_POINTING_HAND=4
---Horizontal resize/move arrow shape
RL.MOUSE_CURSOR_RESIZE_EW=5
---Vertical resize/move arrow shape
RL.MOUSE_CURSOR_RESIZE_NS=6
---Top-left to bottom-right diagonal resize/move arrow shape
RL.MOUSE_CURSOR_RESIZE_NWSE=7
---The top-right to bottom-left diagonal resize/move arrow shape
RL.MOUSE_CURSOR_RESIZE_NESW=8
---The omnidirectional resize/move cursor shape
RL.MOUSE_CURSOR_RESIZE_ALL=9
---The operation-not-allowed shape
RL.MOUSE_CURSOR_NOT_ALLOWED=10

-- Defines - Gamepad buttons

---Unknown button, just for error checking
RL.GAMEPAD_BUTTON_UNKNOWN=0
---Gamepad left DPAD up button
RL.GAMEPAD_BUTTON_LEFT_FACE_UP=1
---Gamepad left DPAD right button
RL.GAMEPAD_BUTTON_LEFT_FACE_RIGHT=2
---Gamepad left DPAD down button
RL.GAMEPAD_BUTTON_LEFT_FACE_DOWN=3
---Gamepad left DPAD left button
RL.GAMEPAD_BUTTON_LEFT_FACE_LEFT=4
---Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
RL.GAMEPAD_BUTTON_RIGHT_FACE_UP=5
---Gamepad right button right (i.e. PS3: Square, Xbox: X)
RL.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT=6
---Gamepad right button down (i.e. PS3: Cross, Xbox: A)
RL.GAMEPAD_BUTTON_RIGHT_FACE_DOWN=7
---Gamepad right button left (i.e. PS3: Circle, Xbox: B)
RL.GAMEPAD_BUTTON_RIGHT_FACE_LEFT=8
---Gamepad top/back trigger left (first), it could be a trailing button
RL.GAMEPAD_BUTTON_LEFT_TRIGGER_1=9
---Gamepad top/back trigger left (second), it could be a trailing button
RL.GAMEPAD_BUTTON_LEFT_TRIGGER_2=10
---Gamepad top/back trigger right (one), it could be a trailing button
RL.GAMEPAD_BUTTON_RIGHT_TRIGGER_1=11
---Gamepad top/back trigger right (second), it could be a trailing button
RL.GAMEPAD_BUTTON_RIGHT_TRIGGER_2=12
---Gamepad center buttons, left one (i.e. PS3: Select)
RL.GAMEPAD_BUTTON_MIDDLE_LEFT=13
---Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
RL.GAMEPAD_BUTTON_MIDDLE=14
---Gamepad center buttons, right one (i.e. PS3: Start)
RL.GAMEPAD_BUTTON_MIDDLE_RIGHT=15
---Gamepad joystick pressed button left
RL.GAMEPAD_BUTTON_LEFT_THUMB=16
---Gamepad joystick pressed button right
RL.GAMEPAD_BUTTON_RIGHT_THUMB=17

-- Defines - Gamepad axis

---Gamepad left stick X axis
RL.GAMEPAD_AXIS_LEFT_X=0
---Gamepad left stick Y axis
RL.GAMEPAD_AXIS_LEFT_Y=1
---Gamepad right stick X axis
RL.GAMEPAD_AXIS_RIGHT_X=2
---Gamepad right stick Y axis
RL.GAMEPAD_AXIS_RIGHT_Y=3
---Gamepad back trigger left, pressure level: [1..-1]
RL.GAMEPAD_AXIS_LEFT_TRIGGER=4
---Gamepad back trigger right, pressure level: [1..-1]
RL.GAMEPAD_AXIS_RIGHT_TRIGGER=5

-- Defines - Material map index

---Albedo material (same as: MATERIAL_MAP_DIFFUSE)
RL.MATERIAL_MAP_ALBEDO=0
---Metalness material (same as: MATERIAL_MAP_SPECULAR)
RL.MATERIAL_MAP_METALNESS=1
---Normal material
RL.MATERIAL_MAP_NORMAL=2
---Roughness material
RL.MATERIAL_MAP_ROUGHNESS=3
---Ambient occlusion material
RL.MATERIAL_MAP_OCCLUSION=4
---Emission material
RL.MATERIAL_MAP_EMISSION=5
---Heightmap material
RL.MATERIAL_MAP_HEIGHT=6
---Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
RL.MATERIAL_MAP_CUBEMAP=7
---Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
RL.MATERIAL_MAP_IRRADIANCE=8
---Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
RL.MATERIAL_MAP_PREFILTER=9
---Brdf material
RL.MATERIAL_MAP_BRDF=10
---Diffuce material (same as: MATERIAL_MAP_ALBEDO)
RL.MATERIAL_MAP_DIFFUSE=0
---Specular material (same as: MATERIAL_MAP_METALNESS)
RL.MATERIAL_MAP_SPECULAR=1

-- Defines - Shader location index

---Shader location: vertex attribute: position
RL.SHADER_LOC_VERTEX_POSITION=0
---Shader location: vertex attribute: texcoord01
RL.SHADER_LOC_VERTEX_TEXCOORD01=1
---Shader location: vertex attribute: texcoord02
RL.SHADER_LOC_VERTEX_TEXCOORD02=2
---Shader location: vertex attribute: normal
RL.SHADER_LOC_VERTEX_NORMAL=3
---Shader location: vertex attribute: tangent
RL.SHADER_LOC_VERTEX_TANGENT=4
---Shader location: vertex attribute: color
RL.SHADER_LOC_VERTEX_COLOR=5
---Shader location: matrix uniform: model-view-projection
RL.SHADER_LOC_MATRIX_MVP=6
---Shader location: matrix uniform: view (camera transform)
RL.SHADER_LOC_MATRIX_VIEW=7
---Shader location: matrix uniform: projection
RL.SHADER_LOC_MATRIX_PROJECTION=8
---Shader location: matrix uniform: model (transform)
RL.SHADER_LOC_MATRIX_MODEL=9
---Shader location: matrix uniform: normal
RL.SHADER_LOC_MATRIX_NORMAL=10
---Shader location: vector uniform: view
RL.SHADER_LOC_VECTOR_VIEW=11
---Shader location: vector uniform: diffuse color
RL.SHADER_LOC_COLOR_DIFFUSE=12
---Shader location: vector uniform: specular color
RL.SHADER_LOC_COLOR_SPECULAR=13
---Shader location: vector uniform: ambient color
RL.SHADER_LOC_COLOR_AMBIENT=14
---Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
RL.SHADER_LOC_MAP_ALBEDO=15
---Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
RL.SHADER_LOC_MAP_METALNESS=16
---Shader location: sampler2d texture: normal
RL.SHADER_LOC_MAP_NORMAL=17
---Shader location: sampler2d texture: roughness
RL.SHADER_LOC_MAP_ROUGHNESS=18
---Shader location: sampler2d texture: occlusion
RL.SHADER_LOC_MAP_OCCLUSION=19
---Shader location: sampler2d texture: emission
RL.SHADER_LOC_MAP_EMISSION=20
---Shader location: sampler2d texture: height
RL.SHADER_LOC_MAP_HEIGHT=21
---Shader location: samplerCube texture: cubemap
RL.SHADER_LOC_MAP_CUBEMAP=22
---Shader location: samplerCube texture: irradiance
RL.SHADER_LOC_MAP_IRRADIANCE=23
---Shader location: samplerCube texture: prefilter
RL.SHADER_LOC_MAP_PREFILTER=24
---Shader location: sampler2d texture: brdf
RL.SHADER_LOC_MAP_BRDF=25
---Shader location: sampler2d texture: diffuce (same as: SHADER_LOC_MAP_ALBEDO)
RL.SHADER_LOC_MAP_DIFFUSE=15
---Shader location: sampler2d texture: specular (same as: SHADER_LOC_MAP_METALNESS)
RL.SHADER_LOC_MAP_SPECULAR=16

-- Defines - Shader uniform data type

---Shader uniform type: float
RL.SHADER_UNIFORM_FLOAT=0
---Shader uniform type: vec2 (2 float)
RL.SHADER_UNIFORM_VEC2=1
---Shader uniform type: vec3 (3 float)
RL.SHADER_UNIFORM_VEC3=2
---Shader uniform type: vec4 (4 float)
RL.SHADER_UNIFORM_VEC4=3
---Shader uniform type: int
RL.SHADER_UNIFORM_INT=4
---Shader uniform type: ivec2 (2 int)
RL.SHADER_UNIFORM_IVEC2=5
---Shader uniform type: ivec3 (3 int)
RL.SHADER_UNIFORM_IVEC3=6
---Shader uniform type: ivec4 (4 int)
RL.SHADER_UNIFORM_IVEC4=7
---Shader uniform type: sampler2d
RL.SHADER_UNIFORM_SAMPLER2D=8

-- Defines - Shader attribute data types

---Shader attribute type: float
RL.SHADER_ATTRIB_FLOAT=0
---Shader attribute type: vec2 (2 float)
RL.SHADER_ATTRIB_VEC2=1
---Shader attribute type: vec3 (3 float)
RL.SHADER_ATTRIB_VEC3=2
---Shader attribute type: vec4 (4 float)
RL.SHADER_ATTRIB_VEC4=3

-- Defines - Pixel formats

---8 bit per pixel (no alpha)
RL.PIXELFORMAT_UNCOMPRESSED_GRAYSCALE=1
---8*2 bpp (2 channels)
RL.PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA=2
---16 bpp
RL.PIXELFORMAT_UNCOMPRESSED_R5G6B5=3
---24 bpp
RL.PIXELFORMAT_UNCOMPRESSED_R8G8B8=4
---16 bpp (1 bit alpha)
RL.PIXELFORMAT_UNCOMPRESSED_R5G5B5A1=5
---16 bpp (4 bit alpha)
RL.PIXELFORMAT_UNCOMPRESSED_R4G4B4A4=6
---32 bpp
RL.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8=7
---32 bpp (1 channel - float)
RL.PIXELFORMAT_UNCOMPRESSED_R32=8
---32*3 bpp (3 channels - float)
RL.PIXELFORMAT_UNCOMPRESSED_R32G32B32=9
---32*4 bpp (4 channels - float)
RL.PIXELFORMAT_UNCOMPRESSED_R32G32B32A32=10
---4 bpp (no alpha)
RL.PIXELFORMAT_COMPRESSED_DXT1_RGB=14
---4 bpp (1 bit alpha)
RL.PIXELFORMAT_COMPRESSED_DXT1_RGBA=15
---8 bpp
RL.PIXELFORMAT_COMPRESSED_DXT3_RGBA=16
---8 bpp
RL.PIXELFORMAT_COMPRESSED_DXT5_RGBA=17
---4 bpp
RL.PIXELFORMAT_COMPRESSED_ETC1_RGB=18
---4 bpp
RL.PIXELFORMAT_COMPRESSED_ETC2_RGB=19
---8 bpp
RL.PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA=20
---4 bpp
RL.PIXELFORMAT_COMPRESSED_PVRT_RGB=21
---4 bpp
RL.PIXELFORMAT_COMPRESSED_PVRT_RGBA=22
---8 bpp
RL.PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA=23
---2 bpp
RL.PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA=24

-- Defines - Texture parameters: filter mode

---No filter, just pixel approximation
RL.TEXTURE_FILTER_POINT=0
---Linear filtering
RL.TEXTURE_FILTER_BILINEAR=1
---Trilinear filtering (linear with mipmaps)
RL.TEXTURE_FILTER_TRILINEAR=2
---Anisotropic filtering 4x
RL.TEXTURE_FILTER_ANISOTROPIC_4X=3
---Anisotropic filtering 8x
RL.TEXTURE_FILTER_ANISOTROPIC_8X=4
---Anisotropic filtering 16x
RL.TEXTURE_FILTER_ANISOTROPIC_16X=5

-- Defines - Texture parameters: wrap mode

---Repeats texture in tiled mode
RL.TEXTURE_WRAP_REPEAT=0
---Clamps texture to edge pixel in tiled mode
RL.TEXTURE_WRAP_CLAMP=1
---Mirrors and repeats the texture in tiled mode
RL.TEXTURE_WRAP_MIRROR_REPEAT=2
---Mirrors and clamps to border the texture in tiled mode
RL.TEXTURE_WRAP_MIRROR_CLAMP=3

-- Defines - Cubemap layouts

---Automatically detect layout type
RL.CUBEMAP_LAYOUT_AUTO_DETECT=0
---Layout is defined by a vertical line with faces
RL.CUBEMAP_LAYOUT_LINE_VERTICAL=1
---Layout is defined by a horizontal line with faces
RL.CUBEMAP_LAYOUT_LINE_HORIZONTAL=2
---Layout is defined by a 3x4 cross with cubemap faces
RL.CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR=3
---Layout is defined by a 4x3 cross with cubemap faces
RL.CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE=4

-- Defines - Font type, defines generation method

---Default font generation, anti-aliased
RL.FONT_DEFAULT=0
---Bitmap font generation, no anti-aliasing
RL.FONT_BITMAP=1
---SDF font generation, requires external shader
RL.FONT_SDF=2

-- Defines - Color blending modes (pre-defined)

---Blend textures considering alpha (default)
RL.BLEND_ALPHA=0
---Blend textures adding colors
RL.BLEND_ADDITIVE=1
---Blend textures multiplying colors
RL.BLEND_MULTIPLIED=2
---Blend textures adding colors (alternative)
RL.BLEND_ADD_COLORS=3
---Blend textures subtracting colors (alternative)
RL.BLEND_SUBTRACT_COLORS=4
---Blend premultiplied textures considering alpha
RL.BLEND_ALPHA_PREMULTIPLY=5
---Blend textures using custom src/dst factors (use rlSetBlendFactors())
RL.BLEND_CUSTOM=6
---Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
RL.BLEND_CUSTOM_SEPARATE=7

-- Defines - Gesture

---No gesture
RL.GESTURE_NONE=0
---Tap gesture
RL.GESTURE_TAP=1
---Double tap gesture
RL.GESTURE_DOUBLETAP=2
---Hold gesture
RL.GESTURE_HOLD=4
---Drag gesture
RL.GESTURE_DRAG=8
---Swipe right gesture
RL.GESTURE_SWIPE_RIGHT=16
---Swipe left gesture
RL.GESTURE_SWIPE_LEFT=32
---Swipe up gesture
RL.GESTURE_SWIPE_UP=64
---Swipe down gesture
RL.GESTURE_SWIPE_DOWN=128
---Pinch in gesture
RL.GESTURE_PINCH_IN=256
---Pinch out gesture
RL.GESTURE_PINCH_OUT=512

-- Defines - Camera system modes

---Custom camera
RL.CAMERA_CUSTOM=0
---Free camera
RL.CAMERA_FREE=1
---Orbital camera
RL.CAMERA_ORBITAL=2
---First person camera
RL.CAMERA_FIRST_PERSON=3
---Third person camera
RL.CAMERA_THIRD_PERSON=4

-- Defines - Camera projection

---Perspective projection
RL.CAMERA_PERSPECTIVE=0
---Orthographic projection
RL.CAMERA_ORTHOGRAPHIC=1

-- Defines - N-patch layout

---Npatch layout: 3x3 tiles
RL.NPATCH_NINE_PATCH=0
---Npatch layout: 1x3 tiles
RL.NPATCH_THREE_PATCH_VERTICAL=1
---Npatch layout: 3x1 tiles
RL.NPATCH_THREE_PATCH_HORIZONTAL=2

-- Defines - Colors

---Light Gray
RL.LIGHTGRAY={200,200,200,255}
---Gray
RL.GRAY={130,130,130,255}
---Dark Gray
RL.DARKGRAY={80,80,80,255}
---Yellow
RL.YELLOW={253,249,0,255}
---Gold
RL.GOLD={255,203,0,255}
---Orange
RL.ORANGE={255,161,0,255}
---Pink
RL.PINK={255,109,194,255}
---Red
RL.RED={230,41,55,255}
---Maroon
RL.MAROON={190,33,55,255}
---Green
RL.GREEN={0,228,48,255}
---Lime
RL.LIME={0,158,47,255}
---Dark Green
RL.DARKGREEN={0,117,44,255}
---Sky Blue
RL.SKYBLUE={102,191,255,255}
---Blue
RL.BLUE={0,121,241,255}
---Dark Blue
RL.DARKBLUE={0,82,172,255}
---Purple
RL.PURPLE={200,122,255,255}
---Violet
RL.VIOLET={135,60,190,255}
---Dark Purple
RL.DARKPURPLE={112,31,126,255}
---Beige
RL.BEIGE={211,176,131,255}
---Brown
RL.BROWN={127,106,79,255}
---Dark Brown
RL.DARKBROWN={76,63,47,255}
---White
RL.WHITE={255,255,255,255}
---Black
RL.BLACK={0,0,0,255}
---Blank (Transparent)
RL.BLANK={0,0,0,0}
---Magenta
RL.MAGENTA={255,0,255,255}
---My own White (raylib logo)
RL.RAYWHITE={245,245,245,255}

-- Defines - Math

---Pi
RL.PI=3.1415927410126
---Epsilon
RL.EPSILON=9.9999999747524e-07
---Degrees to radians
RL.DEG2RAD=0.017453292384744
---Radians to degrees
RL.RAD2DEG=57.295776367188

-- Defines - Gui control state

RL.STATE_NORMAL=0
RL.STATE_FOCUSED=1
RL.STATE_PRESSED=2
RL.STATE_DISABLED=3

-- Defines - Gui control text alignment

RL.TEXT_ALIGN_LEFT=0
RL.TEXT_ALIGN_CENTER=1
RL.TEXT_ALIGN_RIGHT=2

-- Defines - Gui control text alignment vertical

RL.TEXT_ALIGN_TOP=0
RL.TEXT_ALIGN_MIDDLE=1
RL.TEXT_ALIGN_BOTTOM=2

-- Defines - Gui control text wrap mode

RL.TEXT_WRAP_NONE=0
RL.TEXT_WRAP_CHAR=1
RL.TEXT_WRAP_WORD=2

-- Defines - Gui controls

RL.DEFAULT=0
---Used also for: LABELBUTTON
RL.LABEL=1
RL.BUTTON=2
---Used also for: TOGGLEGROUP
RL.TOGGLE=3
---Used also for: SLIDERBAR
RL.SLIDER=4
RL.PROGRESSBAR=5
RL.CHECKBOX=6
RL.COMBOBOX=7
RL.DROPDOWNBOX=8
---Used also for: TEXTBOXMULTI
RL.TEXTBOX=9
RL.VALUEBOX=10
---Uses: BUTTON, VALUEBOX
RL.SPINNER=11
RL.LISTVIEW=12
RL.COLORPICKER=13
RL.SCROLLBAR=14
RL.STATUSBAR=15

-- Defines - Gui base properties for every control

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

-- Defines - Gui extended properties depend on control

---Text size (glyphs max height)
RL.TEXT_SIZE=16
---Text spacing between glyphs
RL.TEXT_SPACING=17
---Line control color
RL.LINE_COLOR=18
---Background color
RL.BACKGROUND_COLOR=19
---Text spacing between lines
RL.TEXT_LINE_SPACING=20
---Text vertical alignment inside text bounds (after border and padding)
RL.TEXT_ALIGNMENT_VERTICAL=21
---Text wrap-mode inside text bounds
RL.TEXT_WRAP_MODE=22

-- Defines - Gui Toggle/ToggleGroup

---ToggleGroup separation between toggles
RL.GROUP_PADDING=16

-- Defines - Gui Slider/SliderBar

---Slider size of internal bar
RL.SLIDER_WIDTH=16
---Slider/SliderBar internal bar padding
RL.SLIDER_PADDING=17

-- Defines - Gui ProgressBar

---ProgressBar internal padding
RL.PROGRESS_PADDING=16

-- Defines - Gui ScrollBar

RL.ARROWS_SIZE=16
RL.ARROWS_VISIBLE=17
---(SLIDERBAR, SLIDER_PADDING)
RL.SCROLL_SLIDER_PADDING=18
RL.SCROLL_SLIDER_SIZE=19
RL.SCROLL_PADDING=20
RL.SCROLL_SPEED=21

-- Defines - Gui CheckBox

---CheckBox internal check padding
RL.CHECK_PADDING=16

-- Defines - Gui ComboBox

---ComboBox right button width
RL.COMBO_BUTTON_WIDTH=16
---ComboBox button separation
RL.COMBO_BUTTON_SPACING=17

-- Defines - Gui DropdownBox

---DropdownBox arrow separation from border and items
RL.ARROW_PADDING=16
---DropdownBox items separation
RL.DROPDOWN_ITEMS_SPACING=17

-- Defines - Gui TextBox/TextBoxMulti/ValueBox/Spinner

---TextBox in read-only mode: 0-text editable, 1-text no-editable
RL.TEXT_READONLY=16

-- Defines - Gui Spinner

---Spinner left/right buttons width
RL.SPIN_BUTTON_WIDTH=16
---Spinner buttons separation
RL.SPIN_BUTTON_SPACING=17

-- Defines - Gui ListView

---ListView items height
RL.LIST_ITEMS_HEIGHT=16
---ListView items separation
RL.LIST_ITEMS_SPACING=17
---ListView scrollbar size (usually width)
RL.SCROLLBAR_WIDTH=18
---ListView scrollbar side (0-left, 1-right)
RL.SCROLLBAR_SIDE=19

-- Defines - Gui ColorPicker

RL.COLOR_SELECTOR_SIZE=16
---ColorPicker right hue bar width
RL.HUEBAR_WIDTH=17
---ColorPicker right hue bar separation from panel
RL.HUEBAR_PADDING=18
---ColorPicker right hue bar selector height
RL.HUEBAR_SELECTOR_HEIGHT=19
---ColorPicker right hue bar selector overflow
RL.HUEBAR_SELECTOR_OVERFLOW=20

-- Defines - Gui Icons enumeration

RL.ICON_NONE=0
RL.ICON_FOLDER_FILE_OPEN=1
RL.ICON_FILE_SAVE_CLASSIC=2
RL.ICON_FOLDER_OPEN=3
RL.ICON_FOLDER_SAVE=4
RL.ICON_FILE_OPEN=5
RL.ICON_FILE_SAVE=6
RL.ICON_FILE_EXPORT=7
RL.ICON_FILE_ADD=8
RL.ICON_FILE_DELETE=9
RL.ICON_FILETYPE_TEXT=10
RL.ICON_FILETYPE_AUDIO=11
RL.ICON_FILETYPE_IMAGE=12
RL.ICON_FILETYPE_PLAY=13
RL.ICON_FILETYPE_VIDEO=14
RL.ICON_FILETYPE_INFO=15
RL.ICON_FILE_COPY=16
RL.ICON_FILE_CUT=17
RL.ICON_FILE_PASTE=18
RL.ICON_CURSOR_HAND=19
RL.ICON_CURSOR_POINTER=20
RL.ICON_CURSOR_CLASSIC=21
RL.ICON_PENCIL=22
RL.ICON_PENCIL_BIG=23
RL.ICON_BRUSH_CLASSIC=24
RL.ICON_BRUSH_PAINTER=25
RL.ICON_WATER_DROP=26
RL.ICON_COLOR_PICKER=27
RL.ICON_RUBBER=28
RL.ICON_COLOR_BUCKET=29
RL.ICON_TEXT_T=30
RL.ICON_TEXT_A=31
RL.ICON_SCALE=32
RL.ICON_RESIZE=33
RL.ICON_FILTER_POINT=34
RL.ICON_FILTER_BILINEAR=35
RL.ICON_CROP=36
RL.ICON_CROP_ALPHA=37
RL.ICON_SQUARE_TOGGLE=38
RL.ICON_SYMMETRY=39
RL.ICON_SYMMETRY_HORIZONTAL=40
RL.ICON_SYMMETRY_VERTICAL=41
RL.ICON_LENS=42
RL.ICON_LENS_BIG=43
RL.ICON_EYE_ON=44
RL.ICON_EYE_OFF=45
RL.ICON_FILTER_TOP=46
RL.ICON_FILTER=47
RL.ICON_TARGET_POINT=48
RL.ICON_TARGET_SMALL=49
RL.ICON_TARGET_BIG=50
RL.ICON_TARGET_MOVE=51
RL.ICON_CURSOR_MOVE=52
RL.ICON_CURSOR_SCALE=53
RL.ICON_CURSOR_SCALE_RIGHT=54
RL.ICON_CURSOR_SCALE_LEFT=55
RL.ICON_UNDO=56
RL.ICON_REDO=57
RL.ICON_REREDO=58
RL.ICON_MUTATE=59
RL.ICON_ROTATE=60
RL.ICON_REPEAT=61
RL.ICON_SHUFFLE=62
RL.ICON_EMPTYBOX=63
RL.ICON_TARGET=64
RL.ICON_TARGET_SMALL_FILL=65
RL.ICON_TARGET_BIG_FILL=66
RL.ICON_TARGET_MOVE_FILL=67
RL.ICON_CURSOR_MOVE_FILL=68
RL.ICON_CURSOR_SCALE_FILL=69
RL.ICON_CURSOR_SCALE_RIGHT_FILL=70
RL.ICON_CURSOR_SCALE_LEFT_FILL=71
RL.ICON_UNDO_FILL=72
RL.ICON_REDO_FILL=73
RL.ICON_REREDO_FILL=74
RL.ICON_MUTATE_FILL=75
RL.ICON_ROTATE_FILL=76
RL.ICON_REPEAT_FILL=77
RL.ICON_SHUFFLE_FILL=78
RL.ICON_EMPTYBOX_SMALL=79
RL.ICON_BOX=80
RL.ICON_BOX_TOP=81
RL.ICON_BOX_TOP_RIGHT=82
RL.ICON_BOX_RIGHT=83
RL.ICON_BOX_BOTTOM_RIGHT=84
RL.ICON_BOX_BOTTOM=85
RL.ICON_BOX_BOTTOM_LEFT=86
RL.ICON_BOX_LEFT=87
RL.ICON_BOX_TOP_LEFT=88
RL.ICON_BOX_CENTER=89
RL.ICON_BOX_CIRCLE_MASK=90
RL.ICON_POT=91
RL.ICON_ALPHA_MULTIPLY=92
RL.ICON_ALPHA_CLEAR=93
RL.ICON_DITHERING=94
RL.ICON_MIPMAPS=95
RL.ICON_BOX_GRID=96
RL.ICON_GRID=97
RL.ICON_BOX_CORNERS_SMALL=98
RL.ICON_BOX_CORNERS_BIG=99
RL.ICON_FOUR_BOXES=100
RL.ICON_GRID_FILL=101
RL.ICON_BOX_MULTISIZE=102
RL.ICON_ZOOM_SMALL=103
RL.ICON_ZOOM_MEDIUM=104
RL.ICON_ZOOM_BIG=105
RL.ICON_ZOOM_ALL=106
RL.ICON_ZOOM_CENTER=107
RL.ICON_BOX_DOTS_SMALL=108
RL.ICON_BOX_DOTS_BIG=109
RL.ICON_BOX_CONCENTRIC=110
RL.ICON_BOX_GRID_BIG=111
RL.ICON_OK_TICK=112
RL.ICON_CROSS=113
RL.ICON_ARROW_LEFT=114
RL.ICON_ARROW_RIGHT=115
RL.ICON_ARROW_DOWN=116
RL.ICON_ARROW_UP=117
RL.ICON_ARROW_LEFT_FILL=118
RL.ICON_ARROW_RIGHT_FILL=119
RL.ICON_ARROW_DOWN_FILL=120
RL.ICON_ARROW_UP_FILL=121
RL.ICON_AUDIO=122
RL.ICON_FX=123
RL.ICON_WAVE=124
RL.ICON_WAVE_SINUS=125
RL.ICON_WAVE_SQUARE=126
RL.ICON_WAVE_TRIANGULAR=127
RL.ICON_CROSS_SMALL=128
RL.ICON_PLAYER_PREVIOUS=129
RL.ICON_PLAYER_PLAY_BACK=130
RL.ICON_PLAYER_PLAY=131
RL.ICON_PLAYER_PAUSE=132
RL.ICON_PLAYER_STOP=133
RL.ICON_PLAYER_NEXT=134
RL.ICON_PLAYER_RECORD=135
RL.ICON_MAGNET=136
RL.ICON_LOCK_CLOSE=137
RL.ICON_LOCK_OPEN=138
RL.ICON_CLOCK=139
RL.ICON_TOOLS=140
RL.ICON_GEAR=141
RL.ICON_GEAR_BIG=142
RL.ICON_BIN=143
RL.ICON_HAND_POINTER=144
RL.ICON_LASER=145
RL.ICON_COIN=146
RL.ICON_EXPLOSION=147
RL.ICON_1UP=148
RL.ICON_PLAYER=149
RL.ICON_PLAYER_JUMP=150
RL.ICON_KEY=151
RL.ICON_DEMON=152
RL.ICON_TEXT_POPUP=153
RL.ICON_GEAR_EX=154
RL.ICON_CRACK=155
RL.ICON_CRACK_POINTS=156
RL.ICON_STAR=157
RL.ICON_DOOR=158
RL.ICON_EXIT=159
RL.ICON_MODE_2D=160
RL.ICON_MODE_3D=161
RL.ICON_CUBE=162
RL.ICON_CUBE_FACE_TOP=163
RL.ICON_CUBE_FACE_LEFT=164
RL.ICON_CUBE_FACE_FRONT=165
RL.ICON_CUBE_FACE_BOTTOM=166
RL.ICON_CUBE_FACE_RIGHT=167
RL.ICON_CUBE_FACE_BACK=168
RL.ICON_CAMERA=169
RL.ICON_SPECIAL=170
RL.ICON_LINK_NET=171
RL.ICON_LINK_BOXES=172
RL.ICON_LINK_MULTI=173
RL.ICON_LINK=174
RL.ICON_LINK_BROKE=175
RL.ICON_TEXT_NOTES=176
RL.ICON_NOTEBOOK=177
RL.ICON_SUITCASE=178
RL.ICON_SUITCASE_ZIP=179
RL.ICON_MAILBOX=180
RL.ICON_MONITOR=181
RL.ICON_PRINTER=182
RL.ICON_PHOTO_CAMERA=183
RL.ICON_PHOTO_CAMERA_FLASH=184
RL.ICON_HOUSE=185
RL.ICON_HEART=186
RL.ICON_CORNER=187
RL.ICON_VERTICAL_BARS=188
RL.ICON_VERTICAL_BARS_FILL=189
RL.ICON_LIFE_BARS=190
RL.ICON_INFO=191
RL.ICON_CROSSLINE=192
RL.ICON_HELP=193
RL.ICON_FILETYPE_ALPHA=194
RL.ICON_FILETYPE_HOME=195
RL.ICON_LAYERS_VISIBLE=196
RL.ICON_LAYERS=197
RL.ICON_WINDOW=198
RL.ICON_HIDPI=199
RL.ICON_FILETYPE_BINARY=200
RL.ICON_HEX=201
RL.ICON_SHIELD=202
RL.ICON_FILE_NEW=203
RL.ICON_FOLDER_ADD=204
RL.ICON_ALARM=205
RL.ICON_CPU=206
RL.ICON_ROM=207
RL.ICON_STEP_OVER=208
RL.ICON_STEP_INTO=209
RL.ICON_STEP_OUT=210
RL.ICON_RESTART=211
RL.ICON_BREAKPOINT_ON=212
RL.ICON_BREAKPOINT_OFF=213
RL.ICON_BURGER_MENU=214
RL.ICON_CASE_SENSITIVE=215
RL.ICON_REG_EXP=216
RL.ICON_FOLDER=217
RL.ICON_FILE=218
RL.ICON_SAND_TIMER=219

-- Defines - Light type

---Directional light
RL.LIGHT_DIRECTIONAL=0
---Point light
RL.LIGHT_POINT=1

-- Defines - RLGL Default internal render batch elements limits

---Default internal render batch elements limits
RL.RL_DEFAULT_BATCH_BUFFER_ELEMENTS=8192
---Default number of batch buffers (multi-buffering)
RL.RL_DEFAULT_BATCH_BUFFERS=1
---Default number of batch draw calls (by state changes: mode, texture)
RL.RL_DEFAULT_BATCH_DRAWCALLS=256
---Maximum number of textures units that can be activated on batch drawing (SetShaderValueTexture())
RL.RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS=4

-- Defines - RLGL Internal Matrix stack

---Maximum size of internal Matrix stack
RL.RL_MAX_MATRIX_STACK_SIZE=32

-- Defines - RLGL Shader limits

---Maximum number of shader locations supported
RL.RL_MAX_SHADER_LOCATIONS=32

-- Defines - RLGL Projection matrix culling

---Default projection matrix near cull distance
RL.RL_CULL_DISTANCE_NEAR=0.01
---Default projection matrix far cull distance
RL.RL_CULL_DISTANCE_FAR=1000

-- Defines - RLGL Texture parameters

---GL_TEXTURE_WRAP_S
RL.RL_TEXTURE_WRAP_S=10242
---GL_TEXTURE_WRAP_T
RL.RL_TEXTURE_WRAP_T=10243
---GL_TEXTURE_MAG_FILTER
RL.RL_TEXTURE_MAG_FILTER=10240
---GL_TEXTURE_MIN_FILTER
RL.RL_TEXTURE_MIN_FILTER=10241
---GL_NEAREST
RL.RL_TEXTURE_FILTER_NEAREST=9728
---GL_LINEAR
RL.RL_TEXTURE_FILTER_LINEAR=9729
---GL_NEAREST_MIPMAP_NEAREST
RL.RL_TEXTURE_FILTER_MIP_NEAREST=9984
---GL_NEAREST_MIPMAP_LINEAR
RL.RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR=9986
---GL_LINEAR_MIPMAP_NEAREST
RL.RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST=9985
---GL_LINEAR_MIPMAP_LINEAR
RL.RL_TEXTURE_FILTER_MIP_LINEAR=9987
---Anisotropic filter (custom identifier)
RL.RL_TEXTURE_FILTER_ANISOTROPIC=12288
---Texture mipmap bias, percentage ratio (custom identifier)
RL.RL_TEXTURE_MIPMAP_BIAS_RATIO=16384
---GL_REPEAT
RL.RL_TEXTURE_WRAP_REPEAT=10497
---GL_CLAMP_TO_EDGE
RL.RL_TEXTURE_WRAP_CLAMP=33071
---GL_MIRRORED_REPEAT
RL.RL_TEXTURE_WRAP_MIRROR_REPEAT=33648
---GL_MIRROR_CLAMP_EXT
RL.RL_TEXTURE_WRAP_MIRROR_CLAMP=34626

-- Defines - RLGL Matrix modes (equivalent to OpenGL)

---GL_MODELVIEW
RL.RL_MODELVIEW=5888
---GL_PROJECTION
RL.RL_PROJECTION=5889
---GL_TEXTURE
RL.RL_TEXTURE=5890

-- Defines - RLGL Primitive assembly draw modes

---GL_LINES
RL.RL_LINES=1
---GL_TRIANGLES
RL.RL_TRIANGLES=4
---GL_QUADS
RL.RL_QUADS=7

-- Defines - RLGL GL equivalent data types

---GL_UNSIGNED_BYTE
RL.RL_UNSIGNED_BYTE=5121
---GL_FLOAT
RL.RL_FLOAT=5126

-- Defines - RLGL GL buffer usage hint

---GL_STREAM_DRAW
RL.RL_STREAM_DRAW=35040
---GL_STREAM_READ
RL.RL_STREAM_READ=35041
---GL_STREAM_COPY
RL.RL_STREAM_COPY=35042
---GL_STATIC_DRAW
RL.RL_STATIC_DRAW=35044
---GL_STATIC_READ
RL.RL_STATIC_READ=35045
---GL_STATIC_COPY
RL.RL_STATIC_COPY=35046
---GL_DYNAMIC_DRAW
RL.RL_DYNAMIC_DRAW=35048
---GL_DYNAMIC_READ
RL.RL_DYNAMIC_READ=35049
---GL_DYNAMIC_COPY
RL.RL_DYNAMIC_COPY=35050

-- Defines - RLGL Shader type

---GL_FRAGMENT_SHADER
RL.RL_FRAGMENT_SHADER=35632
---GL_VERTEX_SHADER
RL.RL_VERTEX_SHADER=35633
---GL_COMPUTE_SHADER
RL.RL_COMPUTE_SHADER=37305

-- Defines - RLGL GL blending factors

---GL_ZERO
RL.RL_ZERO=0
---GL_ONE
RL.RL_ONE=1
---GL_SRC_COLOR
RL.RL_SRC_COLOR=768
---GL_ONE_MINUS_SRC_COLOR
RL.RL_ONE_MINUS_SRC_COLOR=769
---GL_SRC_ALPHA
RL.RL_SRC_ALPHA=770
---GL_ONE_MINUS_SRC_ALPHA
RL.RL_ONE_MINUS_SRC_ALPHA=771
---GL_DST_ALPHA
RL.RL_DST_ALPHA=772
---GL_ONE_MINUS_DST_ALPHA
RL.RL_ONE_MINUS_DST_ALPHA=773
---GL_DST_COLOR
RL.RL_DST_COLOR=774
---GL_ONE_MINUS_DST_COLOR
RL.RL_ONE_MINUS_DST_COLOR=775
---GL_SRC_ALPHA_SATURATE
RL.RL_SRC_ALPHA_SATURATE=776
---GL_CONSTANT_COLOR
RL.RL_CONSTANT_COLOR=32769
---GL_ONE_MINUS_CONSTANT_COLOR
RL.RL_ONE_MINUS_CONSTANT_COLOR=32770
---GL_CONSTANT_ALPHA
RL.RL_CONSTANT_ALPHA=32771
---GL_ONE_MINUS_CONSTANT_ALPHA
RL.RL_ONE_MINUS_CONSTANT_ALPHA=32772

-- Defines - RLGL GL blending functions/equations

---GL_FUNC_ADD
RL.RL_FUNC_ADD=32774
---GL_MIN
RL.RL_MIN=32775
---GL_MAX
RL.RL_MAX=32776
---GL_FUNC_SUBTRACT
RL.RL_FUNC_SUBTRACT=32778
---GL_FUNC_REVERSE_SUBTRACT
RL.RL_FUNC_REVERSE_SUBTRACT=32779
---GL_BLEND_EQUATION
RL.RL_BLEND_EQUATION=32777
---GL_BLEND_EQUATION_RGB // (Same as BLEND_EQUATION)
RL.RL_BLEND_EQUATION_RGB=32777
---GL_BLEND_EQUATION_ALPHA
RL.RL_BLEND_EQUATION_ALPHA=34877
---GL_BLEND_DST_RGB
RL.RL_BLEND_DST_RGB=32968
---GL_BLEND_SRC_RGB
RL.RL_BLEND_SRC_RGB=32969
---GL_BLEND_DST_ALPHA
RL.RL_BLEND_DST_ALPHA=32970
---GL_BLEND_SRC_ALPHA
RL.RL_BLEND_SRC_ALPHA=32971
---GL_BLEND_COLOR
RL.RL_BLEND_COLOR=32773

-- Defines - RLGL GlVersion

---OpenGL 1.1
RL.RL_OPENGL_11=1
---OpenGL 2.1 (GLSL 120)
RL.RL_OPENGL_21=2
---OpenGL 3.3 (GLSL 330)
RL.RL_OPENGL_33=3
---OpenGL 4.3 (using GLSL 330)
RL.RL_OPENGL_43=4
---OpenGL ES 2.0 (GLSL 100)
RL.RL_OPENGL_ES_20=5

-- Defines - RLGL Framebuffer attachment type

---Framebuffer attachment type: color 0
RL.RL_ATTACHMENT_COLOR_CHANNEL0=0
---Framebuffer attachment type: color 1
RL.RL_ATTACHMENT_COLOR_CHANNEL1=1
---Framebuffer attachment type: color 2
RL.RL_ATTACHMENT_COLOR_CHANNEL2=2
---Framebuffer attachment type: color 3
RL.RL_ATTACHMENT_COLOR_CHANNEL3=3
---Framebuffer attachment type: color 4
RL.RL_ATTACHMENT_COLOR_CHANNEL4=4
---Framebuffer attachment type: color 5
RL.RL_ATTACHMENT_COLOR_CHANNEL5=5
---Framebuffer attachment type: color 6
RL.RL_ATTACHMENT_COLOR_CHANNEL6=6
---Framebuffer attachment type: color 7
RL.RL_ATTACHMENT_COLOR_CHANNEL7=7
---Framebuffer attachment type: depth
RL.RL_ATTACHMENT_DEPTH=100
---Framebuffer attachment type: stencil
RL.RL_ATTACHMENT_STENCIL=200

-- Defines - RLGL Framebuffer texture attachment type

---Framebuffer texture attachment type: cubemap, +X side
RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_X=0
---Framebuffer texture attachment type: cubemap, -X side
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_X=1
---Framebuffer texture attachment type: cubemap, +Y side
RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_Y=2
---Framebuffer texture attachment type: cubemap, -Y side
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y=3
---Framebuffer texture attachment type: cubemap, +Z side
RL.RL_ATTACHMENT_CUBEMAP_POSITIVE_Z=4
---Framebuffer texture attachment type: cubemap, -Z side
RL.RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z=5
---Framebuffer texture attachment type: texture2d
RL.RL_ATTACHMENT_TEXTURE2D=100
---Framebuffer texture attachment type: renderbuffer
RL.RL_ATTACHMENT_RENDERBUFFER=200

-- Defines - RLGL CullMode

RL.RL_CULL_FACE_FRONT=0
RL.RL_CULL_FACE_BACK=1

-- Defines - OpenGL Bitfield mask

RL.GL_COLOR_BUFFER_BIT=16384
RL.GL_DEPTH_BUFFER_BIT=256
RL.GL_STENCIL_BUFFER_BIT=1024

-- Defines - OpenGL Texture parameter

RL.GL_NEAREST=9728
RL.GL_LINEAR=9729

-- Defines - OpenGL Capability

---If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc
RL.GL_BLEND=3042
---If enabled, cull polygons based on their winding in window coordinates. See glCullFace
RL.GL_CULL_FACE=2884
---If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled. See glDepthFunc and glDepthRangef
RL.GL_DEPTH_TEST=2929
---If enabled, dither color components or indices before they are written to the color buffer
RL.GL_DITHER=3024
---If enabled, an offset is added to depth values of a polygon's fragments produced by rasterization. See glPolygonOffset
RL.GL_POLYGON_OFFSET_FILL=32823
RL.GL_POLYGON_OFFSET_LINE=10754
RL.GL_POLYGON_OFFSET_POINT=10753
---If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value
RL.GL_SAMPLE_ALPHA_TO_COVERAGE=32926
---If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage
RL.GL_SAMPLE_COVERAGE=32928
---If enabled, discard fragments that are outside the scissor rectangle. See glScissor
RL.GL_SCISSOR_TEST=3089
---If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp
RL.GL_STENCIL_TEST=2960

-- Defines - OpenGL Test function

---Always fails
RL.GL_NEVER=512
---Passes if ( ref & mask ) < ( stencil & mask )
RL.GL_LESS=513
---Passes if ( ref & mask ) <= ( stencil & mask )
RL.GL_LEQUAL=515
---Passes if ( ref & mask ) > ( stencil & mask )
RL.GL_GREATER=516
---Passes if ( ref & mask ) >= ( stencil & mask )
RL.GL_GEQUAL=518
---Passes if ( ref & mask ) = ( stencil & mask )
RL.GL_EQUAL=514
---Passes if ( ref & mask ) != ( stencil & mask )
RL.GL_NOTEQUAL=517
---Always passes
RL.GL_ALWAYS=519

-- Defines - OpenGL Face

RL.GL_FRONT=1028
RL.GL_BACK=1029
RL.GL_FRONT_AND_BACK=1032

-- Defines - OpenGL Stencil test

---Keeps the current value
RL.GL_KEEP=7680
---Sets the stencil buffer value to 0
RL.GL_ZERO=0
---Sets the stencil buffer value to ref, as specified by glStencilFunc
RL.GL_REPLACE=7681
---Increments the current stencil buffer value. Clamps to the maximum representable unsigned value
RL.GL_INCR=7682
---Increments the current stencil buffer value. Wraps stencil buffer value to zero when incrementing the maximum representable unsigned value
RL.GL_INCR_WRAP=34055
---Decrements the current stencil buffer value. Clamps to 0
RL.GL_DECR=7683
---Decrements the current stencil buffer value. Wraps stencil buffer value to the maximum representable unsigned value when decrementing a stencil buffer value of zero
RL.GL_DECR_WRAP=34056
---Bitwise inverts the current stencil buffer value
RL.GL_INVERT=5386

-- Defines - OpenGL Connection

---Returns the company responsible for this GL implementation. This name does not change from release to release
RL.GL_VENDOR=7936
---Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release
RL.GL_RENDERER=7937
---Returns a version or release number of the form OpenGLES
RL.GL_VERSION=7938
---Returns a version or release number for the shading language of the form OpenGLESGLSLES
RL.GL_SHADING_LANGUAGE_VERSION=35724
---Returns a space-separated list of supported extensions to GL
RL.GL_EXTENSIONS=7939

-- Defines - CBuffer Data type

---C type unsigned char
RL.BUFFER_UNSIGNED_CHAR=0
---C type unsigned short
RL.BUFFER_UNSIGNED_SHORT=1
---C type unsigned int
RL.BUFFER_UNSIGNED_INT=2
---C type unsigned long
RL.BUFFER_UNSIGNED_LONG=3
---C type char
RL.BUFFER_CHAR=4
---C type short
RL.BUFFER_SHORT=5
---C type int
RL.BUFFER_INT=6
---C type long
RL.BUFFER_LONG=7
---C type float
RL.BUFFER_FLOAT=8
---C type double
RL.BUFFER_DOUBLE=9

-- Defines - Keyboard keys (US keyboard layout)

---Key: Unknown
RL.GLFW_KEY_UNKNOWN=-1

-- Defines - GLFW API tokens.

---The key or mouse button was released
RL.GLFW_RELEASE=0
---The key or mouse button was pressed
RL.GLFW_PRESS=1
---The key was held down until it repeated
RL.GLFW_REPEAT=2
---Joystick connected
RL.GLFW_CONNECTED=262145
---Joystick disconnected
RL.GLFW_DISCONNECTED=262146

-- Defines - GLFW Window Events.

---GLFW event window size changed
RL.GLFW_WINDOW_SIZE_EVENT=0
---GLFW event window maximize
RL.GLFW_WINDOW_MAXIMIZE_EVENT=1
---GLFW event window iconify
RL.GLFW_WINDOW_ICONYFY_EVENT=2
---GLFW event window focus
RL.GLFW_WINDOW_FOCUS_EVENT=3
---GLFW event window drop
RL.GLFW_WINDOW_DROP_EVENT=4

-- Defines - GLFW Input Events.

---GLFW event keyboard key
RL.GLFW_KEY_EVENT=5
---GLFW event Unicode character
RL.GLFW_CHAR_EVENT=6
---GLFW event mouse button
RL.GLFW_MOUSE_BUTTON_EVENT=7
---GLFW event cursor position
RL.GLFW_MOUSE_CURSOR_POS_EVENT=8
---GLFW event mouse scroll
RL.GLFW_MOUSE_SCROLL_EVENT=9
---GLFW event cursor enter/leave
RL.GLFW_CURSOR_ENTER_EVENT=10
---GLFW event joystick
RL.GLFW_JOYSTICK_EVENT=11

-- Defines - GLFW Pen Tablet Events. NOTE! Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445.

---// GLFW event pen tablet data
RL.assignGlobalInt=nil
---// GLFW event pen tablet cursor
RL.assignGlobalInt=nil
---// GLFW event pen tablet proximity
RL.assignGlobalInt=nil
-- Core - Window-related functions

---Initialize window and OpenGL context. Note! Should be called only in RL.config.
---InitWindow will still be called automatically before RL.init
---@param size table
---@param title string
---@return any RL.InitWindow
function  RL.InitWindow( size, title ) end

---Close window and unload OpenGL context and free all resources
---@return any RL.CloseWindow
function  RL.CloseWindow() end

---Check if application should close (KEY_ESCAPE pressed or windows close icon clicked).
---Note! Not needed unless you want to make custom main loop
---@return any RL.WindowShouldClose
function  RL.WindowShouldClose() end

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

---Check if window has been resized from last frame
---- Success return bool
---@return any resized 
function RL.IsWindowResized() end

---Check if one specific window flag is enabled (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---- Success return bool
---@param flag integer
---@return any state 
function RL.IsWindowState( flag ) end

---Set window configuration state using flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---@param flag integer
---@return any RL.SetWindowState
function  RL.SetWindowState( flag ) end

---Clear window configuration state flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)
---- Success return bool
---@param flag integer
---@return any resized 
function RL.ClearWindowState( flag ) end

---Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
---@return any RL.ToggleFullscreen
function  RL.ToggleFullscreen() end

---Toggle window state: borderless windowed, resizes window to match monitor resolution
---@return any RL.ToggleBorderlessWindowed
function  RL.ToggleBorderlessWindowed() end

---Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
---@return any RL.MaximizeWindow
function  RL.MaximizeWindow() end

---Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
---@return any RL.MinimizeWindow
function  RL.MinimizeWindow() end

---Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
---@return any RL.RestoreWindow
function  RL.RestoreWindow() end

---Set icon for window (Only PLATFORM_DESKTOP)
---@param image any
---@return any RL.SetWindowIcon
function  RL.SetWindowIcon( image ) end

---Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
---@param images table
---@return any RL.SetWindowIcons
function  RL.SetWindowIcons( images ) end

---Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
---@param title string
---@return any RL.SetWindowTitle
function  RL.SetWindowTitle( title ) end

---Set window position on screen
---@param pos table
---@return any RL.SetWindowPosition
function  RL.SetWindowPosition( pos ) end

---Set monitor for the current window
---@param monitor integer
---@return any RL.SetWindowMonitor
function  RL.SetWindowMonitor( monitor ) end

---Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
---@param size table
---@return any RL.SetWindowMinSize
function  RL.SetWindowMinSize( size ) end

---Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
---@param size table
---@return any RL.SetWindowMaxSize
function  RL.SetWindowMaxSize( size ) end

---Set window dimensions
---@param size table
---@return any RL.SetWindowSize
function  RL.SetWindowSize( size ) end

---Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
---@param opacity number
---@return any RL.SetWindowOpacity
function  RL.SetWindowOpacity( opacity ) end

---Set window focused (only PLATFORM_DESKTOP)
---@return any RL.SetWindowFocused
function  RL.SetWindowFocused() end

---Get native window handle. Return as lightuserdata
---- Success return lightuserdata
---@return any windowHandle 
function RL.GetWindowHandle() end

---Get screen size
---- Success return Vector2
---@return any size 
function RL.GetScreenSize() end

---Get render size
---- Success return Vector2
---@return any size 
function RL.GetRenderSize() end

---Get number of connected monitors
---- Success return int
---@return any count 
function RL.GetMonitorCount() end

---Get current connected monitor
---- Success return int
---@return any monitor 
function RL.GetCurrentMonitor() end

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

---Get window position on monitor
---- Success return Vector2
---@return any position 
function RL.GetWindowPosition() end

---Get window scale DPI factor
---- Success return Vector2
---@return any dpi 
function RL.GetWindowScaleDPI() end

---Get the human-readable, UTF-8 encoded name of the specified monitor
---- Success return string
---@param monitor integer
---@return any name 
function RL.GetMonitorName( monitor ) end

---Set clipboard text content
---@param text string
---@return any RL.SetClipboardText
function  RL.SetClipboardText( text ) end

---Get clipboard text content
---- Success return string
---@return any text 
function RL.GetClipboardText() end

---Get clipboard image content
---- Success return Image
---@return any image 
function RL.GetClipboardImage() end

---Enable waiting for events on EndDrawing(), no automatic event polling
---@return any RL.EnableEventWaiting
function  RL.EnableEventWaiting() end

---Disable waiting for events on EndDrawing(), automatic events polling
---@return any RL.DisableEventWaiting
function  RL.DisableEventWaiting() end

-- Core - Cursor-related functions

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

-- Core - Drawing-related functions

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

---Begin 2D mode with custom camera (2D)
---@param camera any
---@return any RL.BeginMode2D
function  RL.BeginMode2D( camera ) end

---Ends 2D mode with custom camera
---@return any RL.EndMode2D
function  RL.EndMode2D() end

---Begin 3D mode with custom camera (3D)
---@param camera any
---@return any RL.BeginMode3D
function  RL.BeginMode3D( camera ) end

---Ends 3D mode and returns to default 2D orthographic mode
---@return any RL.EndMode3D
function  RL.EndMode3D() end

---Begin drawing to render texture
---@param target any
---@return any RL.BeginTextureMode
function  RL.BeginTextureMode( target ) end

---Ends drawing to render texture
---@return any RL.EndTextureMode
function  RL.EndTextureMode() end

---Begin custom shader drawing
---@param shader any
---@return any RL.BeginShaderMode
function  RL.BeginShaderMode( shader ) end

---End custom shader drawing (use default shader)
---@return any RL.EndShaderMode
function  RL.EndShaderMode() end

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

-- Core - Shader management functions

---Load shader from files and bind default locations.
---NOTE: Set nil if no shader
---- Failure return nil
---- Success return Shader
---@param vsFileName string|nil
---@param fsFileName string|nil
---@return any shader 
function RL.LoadShader( vsFileName, fsFileName ) end

---Load shader from code strings and bind default locations
---NOTE: Set nil if no shader
---- Failure return nil
---- Success return Shader
---@param vsCode string|nil
---@param fsCode string|nil
---@return any shader 
function RL.LoadShaderFromMemory( vsCode, fsCode ) end

---Check if a shader is valid (loaded on GPU)
---- Success return bool
---@param shader any
---@return any isValid 
function RL.IsShaderValid( shader ) end

---Get shader program id
---- Success return int
---@param shader any
---@return any shaderId 
function RL.GetShaderId( shader ) end

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
---@param values table
---@param uniformType integer
---@return any RL.SetShaderValue
function  RL.SetShaderValue( shader, locIndex, values, uniformType ) end

---Set shader uniform value vector
---NOTE: Even one value should be in table
---@param shader any
---@param locIndex integer
---@param values table
---@param uniformType integer
---@param count integer
---@return any RL.SetShaderValueV
function  RL.SetShaderValueV( shader, locIndex, values, uniformType, count ) end

---Set shader uniform value using Buffer object
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@return any RL.SetShaderValueWithBuffer
function  RL.SetShaderValueWithBuffer( shader, locIndex, values, uniformType ) end

---Set shader uniform value vector using Buffer object
---@param shader any
---@param locIndex integer
---@param values any
---@param uniformType integer
---@param count integer
---@return any RL.SetShaderValueVWithBuffer
function  RL.SetShaderValueVWithBuffer( shader, locIndex, values, uniformType, count ) end

---Unload shader from GPU memory (VRAM)
---@param shader any
---@return any RL.UnloadShader
function  RL.UnloadShader( shader ) end

-- Core - Screen-space-related functions

---Get a ray trace from screen position (i.e mouse)
---- Success return Ray
---@param mousePosition table
---@param camera any
---@return any ray 
function RL.GetScreenToWorldRay( mousePosition, camera ) end

---Get a ray trace from screen position (i.e mouse) in a viewport
---- Success return Ray
---@param mousePosition table
---@param camera any
---@param size table
---@return any ray 
function RL.GetScreenToWorldRayEx( mousePosition, camera, size ) end

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

-- Core - Timing-related functions

---Set target FPS (maximum)
---@param fps integer
---@return any RL.SetTargetFPS
function  RL.SetTargetFPS( fps ) end

---Get time in seconds for last frame drawn (Delta time)
---- Success return float
---@return any delta 
function RL.GetFrameTime() end

---Get elapsed time in seconds since InitWindow()
---- Success return float
---@return any time 
function RL.GetTime() end

---Get current FPS
---- Success return int
---@return any FPS 
function RL.GetFPS() end

-- Core - Custom frame control functions

---Swap back buffer with front buffer (screen drawing)
---@return any RL.SwapScreenBuffer
function  RL.SwapScreenBuffer() end

---Register all input events
---@return any RL.PollInputEvents
function  RL.PollInputEvents() end

---Wait for some time (halt program execution)
---@param seconds any
---@return any RL.WaitTime
function  RL.WaitTime( seconds ) end

-- Core - Random values generation functions

---Set the seed for the random number generator
---@param seed integer
---@return any RL.SetRandomSeed
function  RL.SetRandomSeed( seed ) end

---Get a random value between min and max (both included)
---- Success return int
---@param min integer
---@param max integer
---@return any time 
function RL.GetRandomValue( min, max ) end

---Load random values sequence, no values repeated
---- Success return int{}
---@param count integer
---@param min integer
---@param max integer
---@return any sequence 
function RL.LoadRandomSequence( count, min, max ) end

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

---Open URL with default system browser (if available)
---@param url string
---@return any RL.OpenURL
function  RL.OpenURL( url ) end

---Check if Lua garbage collection is set to unload object data
---- Success return bool
---@return any enabled 
function RL.IsGCUnloadEnabled() end

---Set Lua garbage collection to unload object data
---@param enabled boolean
---@return any RL.SetGCUnload
function  RL.SetGCUnload( enabled ) end

---Get platform. Returns "Windows", "Linux", "FreeBSD", "OpenBSD", "Apple" or "Emscripten"
---- Success return string
---@return any platform 
function RL.GetPlatform() end

-- Core - Files management functions

---Load file data as byte array (read). Buffer type is BUFFER_UNSIGNED_CHAR
---- Success return Buffer
---@param fileName string
---@return any buffer 
function RL.LoadFileData( fileName ) end

---Save data to file from byte array (write), returns true on success
---- Success return bool
---@param fileName string
---@param Buffer any
---@return any success 
function RL.SaveFileData( fileName, Buffer ) end

---Export data to code (.h), returns true on success
---- Success return bool
---@param buffer any
---@param fileName string
---@return any success 
function RL.ExportDataAsCode( buffer, fileName ) end

---Load text data from file (read)
---- Success return string
---@param fileName string
---@return any text 
function RL.LoadFileText( fileName ) end

---Save text data to file (write), returns true on success
---- Success return bool
---@param fileName string
---@param text string
---@return any success 
function RL.SaveFileText( fileName, text ) end

-- Core - Files system functions

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

---Get the directory of the running application (uses static string)
---- Success return string
---@return any directory 
function RL.GetApplicationDirectory() end

---Create directories (including full path requested), returns 0 on success
---- Success return int
---@param dirPath string
---@return any success 
function RL.MakeDirectory( dirPath ) end

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

---Check if fileName is valid for the platform/OS
---- Success return bool
---@param fileName string
---@return any isValid 
function RL.IsFileNameValid( fileName ) end

---Load directory filepaths
---- Success return string{}
---@param dirPath string
---@return any fileNames 
function RL.LoadDirectoryFiles( dirPath ) end

---Load directory filepaths with extension filtering and recursive directory scan
---- Success return string{}
---@param basePath string
---@param filter string|nil
---@param scanSubdirs boolean
---@return any fileNames 
function RL.LoadDirectoryFilesEx( basePath, filter, scanSubdirs ) end

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

-- Core - Compression/Encoding functionality

---Compress data (DEFLATE algorithm)
---- Success return Buffer
---@param buffer any
---@return any compData 
function RL.CompressData( buffer ) end

---Decompress data (DEFLATE algorithm).
---- Success Buffer 
---@param compData any
---@return any decompData 
function RL.DecompressData( compData ) end

---Encode data to Base64 string
---- Success return string, int
---@param data string
---@return any encodedData
---@return any outputSize 
function RL.EncodeDataBase64( data ) end

---Decode Base64 string data
---- Success return string, int
---@param data string
---@return any decodedData
---@return any outputSize 
function RL.DecodeDataBase64( data ) end

---Compute CRC32 hash code. Note! Buffer should be type BUFFER_UNSIGNED_CHAR
---- Failure return false
---- Success return int
---@param data any
---@return any code 
function RL.ComputeCRC32( data ) end

---Compute MD5 hash code, returns static int[4] (16 bytes). Note! Buffer should be type BUFFER_UNSIGNED_CHAR
---- Failure return false
---- Success return int{4}
---@param data any
---@return any code 
function RL.ComputeMD5( data ) end

---Compute SHA1 hash code, returns static int[5] (20 bytes). Note! Buffer should be type BUFFER_UNSIGNED_CHAR
---- Failure return false
---- Success return int{5}
---@param data any
---@return any code 
function RL.ComputeSHA1( data ) end

-- Core - Automation events functionality

---Load automation events list from file, nil for empty list, capacity = MAX_AUTOMATION_EVENTS
---- Success return AutomationEventList
---@param fileName string|nil
---@return any eventList 
function RL.LoadAutomationEventList( fileName ) end

---Unload automation events list from file
---@param list any
---@return any RL.UnloadAutomationEventList
function  RL.UnloadAutomationEventList( list ) end

---Export automation events list as text file
---- Failure return false
---- Success return true
---@param fileName string
---@return any success 
function RL.ExportAutomationEventList( fileName ) end

---Set automation event list to record to
---@param list any
---@return any RL.SetAutomationEventList
function  RL.SetAutomationEventList( list ) end

---Set automation event internal base frame to start recording
---@param frame integer
---@return any RL.SetAutomationEventBaseFrame
function  RL.SetAutomationEventBaseFrame( frame ) end

---Start recording automation events (AutomationEventList must be set)
---@return any RL.StartAutomationEventRecording
function  RL.StartAutomationEventRecording() end

---Stop recording automation events
---@return any RL.StopAutomationEventRecording
function  RL.StopAutomationEventRecording() end

---Play a recorded automation event
---@param event any
---@return any RL.PlayAutomationEvent
function  RL.PlayAutomationEvent( event ) end

---Get automation event list capacity
---- Success return int
---@param list any
---@return any capacity 
function RL.GetAutomationEventListCapacity( list ) end

---Get automation event list count
---- Success return int
---@param list any
---@return any count 
function RL.GetAutomationEventListCount( list ) end

---Get automation event from automation event list. Return as lightuserdata
---- Failure return nil
---- Success return AutomationEvent
---@param list any
---@param index integer
---@return any event 
function RL.GetAutomationEvent( list, index ) end

---Get automation event frame
---- Success return int
---@param event any
---@return any frame 
function RL.GetAutomationEventFrame( event ) end

---Get automation event type
---- Success return int
---@param event any
---@return any type 
function RL.GetAutomationEventType( event ) end

---Get automation event params
---- Success return int{}
---@param event any
---@return any params 
function RL.GetAutomationEventParams( event ) end

-- Core - Input-related functions: keyboard

---Detect if a key has been pressed once
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyPressed( key ) end

---Check if a key has been pressed again (Only PLATFORM_DESKTOP)
---- Success return bool
---@param key integer
---@return any pressed 
function RL.IsKeyPressedRepeat( key ) end

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

-- Core - Input-related functions: gamepads

---Detect if a gamepad is available
---- Success return bool
---@param gamepad integer
---@return any available 
function RL.IsGamepadAvailable( gamepad ) end

---Return gamepad internal name id
---- Success return string
---@param gamepad integer
---@return any name 
function RL.GetGamepadName( gamepad ) end

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

---Check if a gamepad button is NOT being pressed
---- Success return bool
---@param gamepad integer
---@param button integer
---@return any notPressed 
function RL.IsGamepadButtonUp( gamepad, button ) end

---Get the last gamepad button pressed
---- Success return int
---@return any button 
function RL.GetGamepadButtonPressed() end

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

---Set internal gamepad mappings (SDL_GameControllerDB)
---- Success return int
---@param mappings string
---@return any result 
function RL.SetGamepadMappings( mappings ) end

---Set gamepad vibration for both motors (duration in seconds)
---@param gamepad integer
---@param leftMotor number
---@param rightMotor number
---@param duration number
---@return any RL.SetGamepadVibration
function  RL.SetGamepadVibration( gamepad, leftMotor, rightMotor, duration ) end

-- Core - Input-related functions: mouse

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

---Get mouse offset
---- Success return Vector2
---@return any offset 
function RL.GetMouseOffset() end

---Get mouse scale
---- Success return Vector2
---@return any scale 
function RL.GetMouseScale() end

---Get mouse wheel movement for X or Y, whichever is larger
---- Success return float
---@return any movement 
function RL.GetMouseWheelMove() end

---Get mouse wheel movement for both X and Y
---- Success return Vector2
---@return any movement 
function RL.GetMouseWheelMoveV() end

---Set mouse cursor
---@param cursor integer
---@return any RL.SetMouseCursor
function  RL.SetMouseCursor( cursor ) end

-- Core - Input-related functions: touch

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

-- Core - Input-related functions: gestures

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

-- Core - Camera2D System functions

---Return camera2D set to default configuration
---- Success return Camera2D
---@return any camera2D 
function RL.CreateCamera2D() end

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

-- Core - Camera3D System functions

---Return camera3D id set to default configuration
---- Success return int
---@return any camera 
function RL.CreateCamera3D() end

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
---- lockView prevents camera overrotation (aka "somersaults")
---- rotateAroundTarget defines if rotation is around target or around it's position
---- rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
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

-- Core - Buffer management functions

---Load Buffer. Type should be one of the Buffer types. Empty buffer will set data to NULL.
---- Success return Buffer
---@param buffer table
---@param type integer
---@return any buffer 
function RL.LoadBuffer( buffer, type ) end

---Load formatted buffer with all values set to 'value'
---- Success return Buffer
---@param length integer
---@param type integer
---@param value integer
---@return any buffer 
function RL.LoadBufferFormatted( length, type, value ) end

---Read buffer data from binary file
---- Failure return nil
---- Success return Buffer
---@param path string
---@param type integer
---@return any buffer 
function RL.LoadBufferFromFile( path, type ) end

---Read buffer data from string
---- Failure return nil
---- Success return Buffer
---@param buffer string
---@return any buffer 
function RL.LoadBufferFromString( buffer ) end

---Unload buffer data
---@param buffer any
---@return any RL.UnloadBuffer
function  RL.UnloadBuffer( buffer ) end

---Copy buffer data to another buffer. Size is in bytes
---@param dst any
---@param src any
---@param posDst integer
---@param posSrc integer
---@param size integer
---@return any RL.CopyBufferData
function  RL.CopyBufferData( dst, src, posDst, posSrc, size ) end

---Set buffer data value
---@param buffer any
---@param position integer
---@param values table
---@return any RL.SetBufferData
function  RL.SetBufferData( buffer, position, values ) end

---Swap buffer endianness from big endian to little endian and vice versa
---@param buffer any
---@return any RL.SwapBufferEndianness
function  RL.SwapBufferEndianness( buffer ) end

---Get buffer data as table in the format it was stored
---- Success return data{}
---@param buffer any
---@param position integer
---@param length integer
---@return any data 
function RL.GetBufferData( buffer, position, length ) end

---Get buffer as string
---- Success return string
---@param buffer any
---@return any string 
function RL.GetBufferAsString( buffer ) end

---Get buffer type
---- Success return int
---@param buffer any
---@return any type 
function RL.GetBufferType( buffer ) end

---Get buffer size in bytes
---- Success return int
---@param buffer any
---@return any size 
function RL.GetBufferSize( buffer ) end

---Get buffer element size in bytes
---- Success return int
---@param buffer any
---@return any size 
function RL.GetBufferElementSize( buffer ) end

---Get buffer element count
---- Success return int
---@param buffer any
---@return any length 
function RL.GetBufferLength( buffer ) end

---Write buffer data to binary file
---@param buffer any
---@param path string
---@return any RL.ExportBuffer
function  RL.ExportBuffer( buffer, path ) end

-- Shapes - Basic shapes drawing functions

---Set texture and rectangle to be used on shapes drawing
---NOTE: It can be useful when using basic shapes and one single font,
---defining a font char white rectangle would allow drawing everything in a single draw call
---@param texture any
---@param source table
---@return any RL.SetShapesTexture
function  RL.SetShapesTexture( texture, source ) end

---Get texture that is used for shapes drawing. Return as lightuserdata
---- Success return Texture
---@return any texture 
function RL.GetShapesTexture() end

---Get texture source rectangle that is used for shapes drawing
---- Success return Rectangle
---@return any source 
function RL.GetShapesTextureRectangle() end

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

---Draw lines sequence
---@param points table
---@param color table
---@return any RL.DrawLineStrip
function  RL.DrawLineStrip( points, color ) end

---Draw a line using cubic-bezier curves in-out
---@param startPos table
---@param endPos table
---@param thickness number
---@param color table
---@return any RL.DrawLineBezier
function  RL.DrawLineBezier( startPos, endPos, thickness, color ) end

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

---Draw rectangle lines with rounded edges
---@param rec table
---@param roundness number
---@param segments integer
---@param color table
---@return any RL.DrawRectangleRoundedLines
function  RL.DrawRectangleRoundedLines( rec, roundness, segments, color ) end

---Draw rectangle with rounded edges outline
---@param rec table
---@param roundness number
---@param segments integer
---@param lineThick number
---@param color table
---@return any RL.DrawRectangleRoundedLinesEx
function  RL.DrawRectangleRoundedLinesEx( rec, roundness, segments, lineThick, color ) end

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
---@param points table
---@param color table
---@return any RL.DrawTriangleFan
function  RL.DrawTriangleFan( points, color ) end

---Draw a triangle strip defined by points
---@param points table
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

-- Shapes - Splines drawing functions

---Draw spline: Linear, minimum 2 points
---@param points table
---@param thick number
---@param color table
---@return any RL.DrawSplineLinear
function  RL.DrawSplineLinear( points, thick, color ) end

---Draw spline: B-Spline, minimum 4 points
---@param points table
---@param thick number
---@param color table
---@return any RL.DrawSplineBasis
function  RL.DrawSplineBasis( points, thick, color ) end

---Draw spline: Catmull-Rom, minimum 4 points
---@param points table
---@param thick number
---@param color table
---@return any RL.DrawSplineCatmullRom
function  RL.DrawSplineCatmullRom( points, thick, color ) end

---Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
---@param points table
---@param thick number
---@param color table
---@return any RL.DrawSplineBezierQuadratic
function  RL.DrawSplineBezierQuadratic( points, thick, color ) end

---Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
---@param points table
---@param thick number
---@param color table
---@return any RL.DrawSplineBezierCubic
function  RL.DrawSplineBezierCubic( points, thick, color ) end

---Draw spline segment: Linear, 2 points
---@param p1 table
---@param p2 table
---@param thick number
---@param color table
---@return any RL.DrawSplineSegmentLinear
function  RL.DrawSplineSegmentLinear( p1, p2, thick, color ) end

---Draw spline segment: B-Spline, 4 points
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@param thick number
---@param color table
---@return any RL.DrawSplineSegmentBasis
function  RL.DrawSplineSegmentBasis( p1, p2, p3, p4, thick, color ) end

---Draw spline segment: Catmull-Rom, 4 points
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@param thick number
---@param color table
---@return any RL.DrawSplineSegmentCatmullRom
function  RL.DrawSplineSegmentCatmullRom( p1, p2, p3, p4, thick, color ) end

---Draw spline segment: Quadratic Bezier, 2 points, 1 control point
---@param p1 table
---@param c2 table
---@param p3 table
---@param thick number
---@param color table
---@return any RL.DrawSplineSegmentBezierQuadratic
function  RL.DrawSplineSegmentBezierQuadratic( p1, c2, p3, thick, color ) end

---Draw spline segment: Cubic Bezier, 2 points, 2 control points
---@param p1 table
---@param c2 table
---@param c3 table
---@param p4 table
---@param thick number
---@param color table
---@return any RL.DrawSplineSegmentBezierCubic
function  RL.DrawSplineSegmentBezierCubic( p1, c2, c3, p4, thick, color ) end

-- Shapes - Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]

---Get (evaluate) spline point: Linear
---- Success return Vector2
---@param startPos table
---@param endPos table
---@param t number
---@return any point 
function RL.GetSplinePointLinear( startPos, endPos, t ) end

---Get (evaluate) spline point: B-Spline
---- Success return Vector2
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@param t number
---@return any point 
function RL.GetSplinePointBasis( p1, p2, p3, p4, t ) end

---Get (evaluate) spline point: Catmull-Rom
---- Success return Vector2
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@param t number
---@return any point 
function RL.GetSplinePointCatmullRom( p1, p2, p3, p4, t ) end

---Get (evaluate) spline point: Quadratic Bezier
---- Success return Vector2
---@param p1 table
---@param c2 table
---@param p3 table
---@param t number
---@return any point 
function RL.GetSplinePointBezierQuad( p1, c2, p3, t ) end

---Get (evaluate) spline point: Cubic Bezier
---- Success return Vector2
---@param p1 table
---@param c2 table
---@param c3 table
---@param p4 table
---@param t number
---@return any point 
function RL.GetSplinePointBezierCubic( p1, c2, c3, p4, t ) end

-- Shapes - Basic shapes collision detection functions

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

---Check if circle collides with a line created betweeen two points [p1] and [p2]
---- Success return bool
---@param center table
---@param radius number
---@param p1 table
---@param p2 table
---@return any collision 
function RL.CheckCollisionCircleLine( center, radius, p1, p2 ) end

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
---@param points table
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

---Useful for e.g. packing rectangular textures into an atlas. stbrp_pack_rects
---- Success return Rectangle{}
---@param rects table
---@param size table
---@param padding integer
---@return any rects{} 
function RL.RectPack( rects, size, padding ) end

-- Textures - Image loading functions

---Load image from file into CPU memory (RAM)
---- Failure return nil
---- Success return Image
---@param fileName string
---@return any image 
function RL.LoadImage( fileName ) end

---Load image from RAW file data
---- Failure return nil
---- Success return Image
---@param fileName string
---@param size table
---@param format integer
---@param headerSize integer
---@return any image 
function RL.LoadImageRaw( fileName, size, format, headerSize ) end

---Load image sequence from file (frames appended to image.data). All frames are returned in RGBA format
---- Failure return nil
---- Success return Image, int
---@param fileName string
---@return any image
---@return any frameCount 
function RL.LoadImageAnim( fileName ) end

---Load image sequence from memory buffer. All frames are returned in RGBA format
---- Success return Image, int
---@param fileType string
---@param fileData any
---@return any image
---@return any frameCount 
function RL.LoadImageAnimFromMemory( fileType, fileData ) end

---Load image from memory buffer, fileType refers to extension: i.e. '.png'
---- Success return Image
---@param fileType string
---@param data any
---@return any image
---@return any frameCount 
function RL.LoadImageFromMemory( fileType, data ) end

---Load image from data
---- Success return Image
---@param data any
---@param size table
---@param mipmaps integer
---@param format integer
---@return any image
---@return any frameCount 
function RL.LoadImageFromData( data, size, mipmaps, format ) end

---Load image from GPU texture data
---- Success return Image
---@param texture any
---@return any image 
function RL.LoadImageFromTexture( texture ) end

---Load image from screen buffer and (screenshot)
---- Success return Image
---@return any image 
function RL.LoadImageFromScreen() end

---Check if an image is valid (data and parameters)
---- Success return bool
---@param image any
---@return any isValid 
function RL.IsImageValid( image ) end

---Unload image from CPU memory (RAM)
---@param image any
---@return any RL.UnloadImage
function  RL.UnloadImage( image ) end

---Export image data to file, returns true on success
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImage( image, fileName ) end

---Export image to memory buffer
---- Success return Buffer
---@param image any
---@param fileType string
---@return any buffer 
function RL.ExportImageToMemory( image, fileType ) end

---Export image as code file defining an array of bytes, returns true on success
---- Success return bool
---@param image any
---@param fileName string
---@return any success 
function RL.ExportImageAsCode( image, fileName ) end

-- Textures - Image generation functions

---Generate image: plain color
---- Success return Image
---@param size table
---@param color table
---@return any image 
function RL.GenImageColor( size, color ) end

---Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
---- Success return Image
---@param size table
---@param direction integer
---@param a table
---@param b table
---@return any image 
function RL.GenImageGradientLinear( size, direction, a, b ) end

---Generate image: radial gradient
---- Success return Image
---@param size table
---@param density number
---@param inner table
---@param outer table
---@return any image 
function RL.GenImageGradientRadial( size, density, inner, outer ) end

---Generate image: square gradient
---- Success return Image
---@param size table
---@param density number
---@param inner table
---@param outer table
---@return any image 
function RL.GenImageGradientSquare( size, density, inner, outer ) end

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

-- Textures - Image manipulation functions

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

---Create an image from a selected channel of another image (GRAYSCALE)
---- Success return Image
---@param image any
---@param selectedChannel integer
---@return any image 
function RL.ImageFromChannel( image, selectedChannel ) end

---Create an image from text (default font)
---- Success return Image
---@param text string
---@param fontSize integer
---@param tint table
---@return any image 
function RL.ImageText( text, fontSize, tint ) end

---Create an image from text (custom sprite font)
---- Success return Image
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@param tint table
---@return any image 
function RL.ImageTextEx( font, text, fontSize, spacing, tint ) end

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

---Apply custom square convolution kernel to image
---@param image any
---@param kernel table
---@return any RL.ImageKernelConvolution
function  RL.ImageKernelConvolution( image, kernel ) end

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

---Rotate image by input angle in degrees (-359 to 359)
---@param image any
---@param degrees integer
---@return any RL.ImageRotate
function  RL.ImageRotate( image, degrees ) end

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

-- Textures - Image configuration functions

---Set image data from Buffer
---@param image any
---@param data any
---@return any RL.SetImageData
function  RL.SetImageData( image, data ) end

---Get image data as Buffer
---- Success return Buffer
---@param image any
---@return any imageData 
function RL.GetImageData( image ) end

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

-- Textures - Image drawing functions

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
---@param start table
---@param end table
---@param color table
---@return any RL.ImageDrawLine
function  RL.ImageDrawLine( dst, start, end, color ) end

---Draw a line defining thickness within an image
---@param dst any
---@param start table
---@param end table
---@param thick integer
---@param color table
---@return any RL.ImageDrawLineEx
function  RL.ImageDrawLineEx( dst, start, end, thick, color ) end

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

---Draw triangle within an image
---@param dst any
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any RL.ImageDrawTriangle
function  RL.ImageDrawTriangle( dst, v1, v2, v3, color ) end

---Draw triangle with interpolated colors within an image
---@param dst any
---@param v1 table
---@param v2 table
---@param v3 table
---@param c1 table
---@param c2 table
---@param c3 table
---@return any RL.ImageDrawTriangleEx
function  RL.ImageDrawTriangleEx( dst, v1, v2, v3, c1, c2, c3 ) end

---Draw triangle outline within an image
---@param dst any
---@param v1 table
---@param v2 table
---@param v3 table
---@param color table
---@return any RL.ImageDrawTriangleLines
function  RL.ImageDrawTriangleLines( dst, v1, v2, v3, color ) end

---Draw a triangle fan defined by points within an image (first vertex is the center)
---@param dst any
---@param points table
---@param color table
---@return any RL.ImageDrawTriangleFan
function  RL.ImageDrawTriangleFan( dst, points, color ) end

---Draw a triangle strip defined by points within an image
---@param dst any
---@param points table
---@param color table
---@return any RL.ImageDrawTriangleStrip
function  RL.ImageDrawTriangleStrip( dst, points, color ) end

---Draw a source image within a destination image (Tint applied to source)
---@param dst any
---@param src any
---@param srcRec table
---@param dstRec table
---@param tint table
---@return any RL.ImageDraw
function  RL.ImageDraw( dst, src, srcRec, dstRec, tint ) end

---Draw text (using default font) within an image (destination)
---@param dst any
---@param text string
---@param position table
---@param fontSize number
---@param tint table
---@return any RL.ImageDrawText
function  RL.ImageDrawText( dst, text, position, fontSize, tint ) end

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

-- Textures - Texture loading functions

---Get default texture. Return as lightuserdata
---- Success return Texture
---@return any texture 
function RL.GetTextureDefault() end

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

---Load Texture from data
---- Success return Texture
---@param textureData table
---@return any texture 
function RL.LoadTextureFromData( textureData ) end

---Load texture for rendering (framebuffer)
---- Success return RenderTexture
---@param size table
---@return any renderTexture 
function RL.LoadRenderTexture( size ) end

---Load RenderTexture from data (framebuffer)
---- Success return RenderTexture
---@param renderTextureData table
---@return any renderTexture 
function RL.LoadRenderTextureFromData( renderTextureData ) end

---Check if a texture is valid (loaded in GPU)
---- Success return bool
---@param texture any
---@return any isValid 
function RL.IsTextureValid( texture ) end

---Unload texture from GPU memory (VRAM)
---@param texture any
---@return any RL.UnloadTexture
function  RL.UnloadTexture( texture ) end

---Check if a render texture is valid (loaded in GPU)
---- Success return bool
---@param target any
---@return any isValid 
function RL.IsRenderTextureValid( target ) end

---Unload render texture from GPU memory (VRAM)
---@param target any
---@return any RL.UnloadRenderTexture
function  RL.UnloadRenderTexture( target ) end

---Update GPU texture with new data
---@param texture any
---@param pixels any
---@return any RL.UpdateTexture
function  RL.UpdateTexture( texture, pixels ) end

---Update GPU texture rectangle with new data.
---@param texture any
---@param rec table
---@param pixels any
---@return any RL.UpdateTextureRec
function  RL.UpdateTextureRec( texture, rec, pixels ) end

-- Textures - Texture configuration functions

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

-- Textures - Texture drawing functions

---Draw a Texture2D
---@param texture any
---@param position table
---@param tint table
---@return any RL.DrawTexture
function  RL.DrawTexture( texture, position, tint ) end

---Draw a Texture2D with extended parameters
---@param texture any
---@param position table
---@param rotation number
---@param scale number
---@param tint table
---@return any RL.DrawTextureEx
function  RL.DrawTextureEx( texture, position, rotation, scale, tint ) end

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

---Draws a texture (or part of it) that repeats nicely
---@param texture any
---@param nPatchInfo any
---@param dest table
---@param origin table
---@param rotation number
---@param tint table
---@return any RL.DrawTextureNPatchRepeat
function  RL.DrawTextureNPatchRepeat( texture, nPatchInfo, dest, origin, rotation, tint ) end

-- Textures - RenderTexture configuration functions

---Get OpenGL framebuffer object id
---- Success return int
---@param renderTexture any
---@return any id 
function RL.GetRenderTextureId( renderTexture ) end

---Get color buffer attachment texture. Returns as lightuserdata
---- Success return Texture
---@param renderTexture any
---@return any texture 
function RL.GetRenderTextureTexture( renderTexture ) end

---Get depth buffer attachment texture. Returns as lightuserdata
---- Success return Texture
---@param renderTexture any
---@return any texture 
function RL.GetRenderTextureDepthTexture( renderTexture ) end

-- Textures - Color/pixel related functions

---Check if two colors are equal
---- Success return bool
---@param col1 table
---@param col2 table
---@return any isEqual 
function RL.ColorIsEqual( col1, col2 ) end

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

---Get color lerp interpolation between two colors, factor [0.0f..1.0f]
---- Success return Color
---@param color1 table
---@param color2 table
---@param factor number
---@return any color 
function RL.ColorLerp( color1, color2, factor ) end

---Get Color structure from hexadecimal value
---- Success return Color
---@param hexValue integer
---@return any color 
function RL.GetColor( hexValue ) end

---Get pixel data size in bytes for certain format
---- Success return int
---@param size table
---@param format integer
---@return any size 
function RL.GetPixelDataSize( size, format ) end

-- Text - Font loading/unloading functions

---Get the default Font. Return as lightuserdata
---- Success return Font
---@return any font 
function RL.GetFontDefault() end

---Load font from file into GPU memory (VRAM)
---- Failure return nil
---- Success return Font
---@param fileName string
---@return any font 
function RL.LoadFont( fileName ) end

---Load font from file with extended parameters, use NULL for codepoints to load the default character set
---- Failure return nil
---- Success return Font
---@param fileName string
---@param fontSize integer
---@param codepoints table|nil
---@return any font 
function RL.LoadFontEx( fileName, fontSize, codepoints ) end

---Load font from Image (XNA style)
---- Success return Font
---@param image any
---@param key table
---@param firstChar integer
---@return any font 
function RL.LoadFontFromImage( image, key, firstChar ) end

---Load font from memory buffer, fileType refers to extension: i.e. '.ttf'. NOTE: fileData type should be unsigned char
---- Success return Font
---@param fileType string
---@param fileData any
---@param fontSize integer
---@param codepoints table
---@return any font 
function RL.LoadFontFromMemory( fileType, fileData, fontSize, codepoints ) end

---Load Font from data
---- Success return Font
---@param fontData table
---@return any font 
function RL.LoadFontFromData( fontData ) end

---Load font copy as new userdata
---- Success return Font
---@param font any
---@return any font 
function RL.FontCopy( font ) end

---Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
---- Success return bool
---@param font any
---@return any isValid 
function RL.IsFontValid( font ) end

---Load font data for further use. NOTE: fileData type should be unsigned char
---- Success return GlyphInfo{}
---@param fileData any
---@param fontSize integer
---@param codepoints table
---@param type integer
---@return any glyphs 
function RL.LoadFontData( fileData, fontSize, codepoints, type ) end

---Generate image font atlas using chars info. NOTE: Packing method: 0-Default, 1-Skyline
---- Success Image, Rectangle{}
---@param glyphs table
---@param fontSize integer
---@param padding integer
---@param packMethod integer
---@return any image
---@return any rectangles 
function RL.GenImageFontAtlas( glyphs, fontSize, padding, packMethod ) end

---Unload font from GPU memory (VRAM)
---@param font any
---@return any RL.UnloadFont
function  RL.UnloadFont( font ) end

---Export font as code file, returns true on success
---- Success return bool
---@param font any
---@param fileName string
---@return any RL.ExportFontAsCode
function  RL.ExportFontAsCode( font, fileName ) end

-- Text - Text drawing functions

---Draw current FPS
---@param pos table
---@return any RL.DrawFPS
function  RL.DrawFPS( pos ) end

---Draw text (using default font)
---@param text string
---@param position table
---@param fontSize number
---@param tint table
---@return any RL.DrawText
function  RL.DrawText( text, position, fontSize, tint ) end

---Draw text using font and additional parameters
---@param font any
---@param text string
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any RL.DrawTextEx
function  RL.DrawTextEx( font, text, position, fontSize, spacing, tint ) end

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

---Draw one character (codepoint)
---@param font any
---@param codepoint integer
---@param position table
---@param fontSize number
---@param tint table
---@return any RL.DrawTextCodepoint
function  RL.DrawTextCodepoint( font, codepoint, position, fontSize, tint ) end

---Draw multiple character (codepoint)
---@param font any
---@param codepoints table
---@param position table
---@param fontSize number
---@param spacing number
---@param tint table
---@return any RL.DrawTextCodepoints
function  RL.DrawTextCodepoints( font, codepoints, position, fontSize, spacing, tint ) end

---Draw text using font inside rectangle limits.
---Support for tint change with "\a#FFFFFFFF"
---- Success return int, Vector2
---@param font any
---@param text string
---@param rec table
---@param fontSize number
---@param spacing number
---@param wordWrap boolean
---@param tint table
---@param limitHeight boolean
---@param tabSize integer|nil
---@return any mouseCharId
---@return any textOffset 
function RL.DrawTextBoxed( font, text, rec, fontSize, spacing, wordWrap, tint, limitHeight, tabSize ) end

---Draw text using font inside rectangle limits. Return character id from mouse position (default 0).
---textOffset can be used to set start position inside rectangle. Usefull to pass from previous
---DrawTextBoxedEx for continuous text.
---Support for tint change with "\a#FFFFFFFF"
---- Success return int, Vector2
---@param font any
---@param text string
---@param rec table
---@param fontSize number
---@param spacing number
---@param wordWrap boolean
---@param tint table
---@param limitHeight boolean
---@param textOffset table
---@param tabSize integer|nil
---@return any mouseCharId
---@return any textOffset 
function RL.DrawTextBoxedEx( font, text, rec, fontSize, spacing, wordWrap, tint, limitHeight, textOffset, tabSize ) end

-- Text - Text font info functions

---Set vertical line spacing when drawing with line-breaks
---@param spacing integer
---@return any RL.SetTextLineSpacing
function  RL.SetTextLineSpacing( spacing ) end

---Get vertical line spacing when drawing with line-breaks
---- Success return int
---@return any spacing 
function RL.GetTextLineSpacing() end

---Measure string width for default font
---- Success return int
---@param text string
---@param fontSize integer
---@return any width 
function RL.MeasureText( text, fontSize ) end

---Measure string size for Font
---- Success return Vector2
---@param font any
---@param text string
---@param fontSize number
---@param spacing number
---@return any size 
function RL.MeasureTextEx( font, text, fontSize, spacing ) end

---Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
---- Success return int
---@param font any
---@param codepoint integer
---@return any index 
function RL.GetGlyphIndex( font, codepoint ) end

---Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found. Return as lightuserdata
---- Success return GlyphInfo
---@param font any
---@param codepoint integer
---@return any glyphInfo 
function RL.GetGlyphInfo( font, codepoint ) end

---Get glyph font info data by index. Return as lightuserdata
---- Failure return nil
---- Success return GlyphInfo
---@param font any
---@param index integer
---@return any glyphInfo 
function RL.GetGlyphInfoByIndex( font, index ) end

---Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
---- Success return Rectangle
---@param font any
---@param codepoint integer
---@return any rect 
function RL.GetGlyphAtlasRec( font, codepoint ) end

---Get glyph rectangle in font atlas by index
---- Failure return nil
---- Success return Rectangle
---@param font any
---@param index integer
---@return any rect 
function RL.GetGlyphAtlasRecByIndex( font, index ) end

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

---Get font texture atlas containing the glyphs. Return as lightuserdata
---- Success return Texture
---@param font any
---@return any texture 
function RL.GetFontTexture( font ) end

-- Text - GlyphInfo management functions

---Load GlyphInfo from data
---- Success return GlyphInfo
---@param glyphInfoData table
---@return any glyphInfo 
function RL.LoadGlyphInfo( glyphInfoData ) end

---Unload glyphInfo image from CPU memory (RAM)
---@param glyphInfo any
---@return any RL.UnloadGlyphInfo
function  RL.UnloadGlyphInfo( glyphInfo ) end

---Set glyphInfo character value (Unicode)
---@param glyphInfo any
---@param value integer
---@return any RL.SetGlyphInfoValue
function  RL.SetGlyphInfoValue( glyphInfo, value ) end

---Set glyphInfo character offset when drawing
---@param glyphInfo any
---@param offset table
---@return any RL.SetGlyphInfoOffset
function  RL.SetGlyphInfoOffset( glyphInfo, offset ) end

---Set glyphInfo character advance position X
---@param glyphInfo any
---@param advanceX integer
---@return any RL.SetGlyphInfoAdvanceX
function  RL.SetGlyphInfoAdvanceX( glyphInfo, advanceX ) end

---Set glyphInfo character image data
---@param glyphInfo any
---@param image any
---@return any RL.SetGlyphInfoImage
function  RL.SetGlyphInfoImage( glyphInfo, image ) end

---Get glyphInfo character value (Unicode)
---- Success return int
---@param glyphInfo any
---@return any value 
function RL.GetGlyphInfoValue( glyphInfo ) end

---Get glyphInfo character offset when drawing
---- Success return Vector2
---@param glyphInfo any
---@return any offset 
function RL.GetGlyphInfoOffset( glyphInfo ) end

---Get glyphInfo character advance position X
---- Success return int
---@param glyphInfo any
---@return any advanceX 
function RL.GetGlyphInfoAdvanceX( glyphInfo ) end

---Get glyphInfo character image data. Return as lightuserdata
---- Success return Image
---@param glyphInfo any
---@return any image 
function RL.GetGlyphInfoImage( glyphInfo ) end

-- Text - Text codepoints management functions (unicode characters)

---Load UTF-8 text encoded from codepoints array
---- Success return string
---@param codepoints table
---@return any string 
function RL.LoadUTF8( codepoints ) end

---Load all codepoints from a UTF-8 text string
---- Success return int{}
---@param text string
---@return any codepoints 
function RL.LoadCodepoints( text ) end

---Get total number of codepoints in a UTF-8 encoded string
---- Success return int
---@param text string
---@return any count 
function RL.GetCodepointCount( text ) end

---Get codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
---- Success return int, int
---@param text string
---@param position integer
---@return any codepoint
---@return any codepointSize 
function RL.GetCodepoint( text, position ) end

---Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
---- Success return int, int
---@param text string
---@param position integer
---@return any codepoint
---@return any codepointSize 
function RL.GetCodepointNext( text, position ) end

---Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
---- Success return int, int
---@param text string
---@param position integer
---@return any codepoint
---@return any codepointSize 
function RL.GetCodepointPrevious( text, position ) end

---Encode one codepoint into UTF-8 byte array
---- Success return string
---@param codepoint integer
---@return any string 
function RL.CodepointToUTF8( codepoint ) end

-- Text - Text strings management functions (no UTF-8 strings, only byte chars)

---Get a piece of a text string
---- Success return string
---@param text string
---@param position integer
---@param length integer
---@return any text 
function RL.TextSubtext( text, position, length ) end

---Replace text string
---- Success return string
---@param text string
---@param replace string
---@param by string
---@return any text 
function RL.TextReplace( text, replace, by ) end

---Insert text in a specific position, moves all text forward
---- Success return string
---@param text string
---@param insert string
---@param position integer
---@return any text 
function RL.TextInsert( text, insert, position ) end

---Split text into multiple strings
---- Success return string{}
---@param text string
---@param delimiter any
---@return any splits 
function RL.TextSplit( text, delimiter ) end

---Find first text occurrence within a string
---- Success return int
---@param text string
---@param find string
---@return any index 
function RL.TextFindIndex( text, find ) end

---Get Pascal case notation version of provided string
---- Success return string
---@param text string
---@return any text 
function RL.TextToPascal( text ) end

---Get Snake case notation version of provided string
---- Success return string
---@param text string
---@return any text 
function RL.TextToSnake( text ) end

---Get Camel case notation version of provided string
---- Success return string
---@param text string
---@return any text 
function RL.TextToCamel( text ) end

-- Models - Basic geometric 3D shapes drawing functions

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

---Draw a triangle strip defined by points
---@param points table
---@param color table
---@return any RL.DrawTriangleStrip3D
function  RL.DrawTriangleStrip3D( points, color ) end

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

---Draw 3D textured quad. (Texture coordinates opengl style 0.0 - 1.0)
---@param texture any
---@param vertices table
---@param texCoords table
---@param colors table
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

---Draw a grid with extended parameters. Optionally you can define divider with different color for every n slices
---@param slices table
---@param spacing table
---@param transform table
---@param color table
---@param divider table|nil
---@param dividerColor table|nil
---@return any RL.DrawGridEx
function  RL.DrawGridEx( slices, spacing, transform, color, divider, dividerColor ) end

-- Models - Model management functions

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

---Check if a model is valid (loaded in GPU, VAO/VBOs)
---- Success return bool
---@param model any
---@return any isValid 
function RL.IsModelValid( model ) end

---Unload model (meshes/materials) from memory (RAM and/or VRAM)
---@param model any
---@return any RL.UnloadModel
function  RL.UnloadModel( model ) end

---Compute model bounding box limits (considers all meshes)
---- Success return BoundingBox
---@param model any
---@return any boundingBox 
function RL.GetModelBoundingBox( model ) end

---Set model transform matrix
---@param model any
---@param transform table
---@return any RL.SetModelTransform
function  RL.SetModelTransform( model, transform ) end

---Set model mesh.
---- Failure return false
---- Success return true
---@param model any
---@param meshId integer
---@param mesh any
---@return any success 
function RL.SetModelMesh( model, meshId, mesh ) end

---Set material to model material
---- Failure return false
---- Success return true
---@param model any
---@param materialId integer
---@param material any
---@return any success 
function RL.SetModelMaterial( model, materialId, material ) end

---Set material for a mesh (Mesh and material on this model)
---@param model any
---@param meshId integer
---@param materialId integer
---@return any RL.SetModelMeshMaterial
function  RL.SetModelMeshMaterial( model, meshId, materialId ) end

---Set model bone information (skeleton)
---- Failure return false
---- Success return true
---@param model any
---@param boneId integer
---@param bone any
---@return any success 
function RL.SetModelBone( model, boneId, bone ) end

---Set model bones base transformation (pose)
---- Failure return false
---- Success return true
---@param model any
---@param boneId integer
---@param pose any
---@return any success 
function RL.SetModelBindPose( model, boneId, pose ) end

---Get model transform matrix
---- Success return Matrix
---@param model any
---@return any transform 
function RL.GetModelTransform( model ) end

---Get model number of meshes
---- Success return int
---@param model any
---@return any meshCount 
function RL.GetModelMeshCount( model ) end

---Get model number of materials
---- Success return int
---@param model any
---@return any meshCount 
function RL.GetModelMaterialCount( model ) end

---Get model mesh. Return as lightuserdata
---- Failure return nil
---- Success return Mesh
---@param model any
---@param meshId integer
---@return any mesh 
function RL.GetModelMesh( model, meshId ) end

---Get model material. Return as lightuserdata
---- Failure return nil
---- Success return Material
---@param model any
---@param materialId integer
---@return any material 
function RL.GetModelMaterial( model, materialId ) end

---Get model number of bones
---- Success return int
---@param model any
---@return any boneCount 
function RL.GetModelBoneCount( model ) end

---Get model bones information (skeleton)
---- Failure return nil
---- Success return BoneInfo
---@param model any
---@param boneId integer
---@return any bone 
function RL.GetModelBone( model, boneId ) end

---Get models bones base transformation (pose)
---- Failure return nil
---- Success return Transform
---@param model any
---@param boneId integer
---@return any pose 
function RL.GetModelBindPose( model, boneId ) end

-- Models - Model drawing functions

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

---Draw a model wires (with texture if set)
---@param model any
---@param position table
---@param scale number
---@param tint table
---@return any RL.DrawModelWires
function  RL.DrawModelWires( model, position, scale, tint ) end

---Draw a model wires (with texture if set) with extended parameters
---@param model any
---@param position table
---@param rotationAxis table
---@param rotationAngle number
---@param scale table
---@param tint table
---@return any RL.DrawModelWiresEx
function  RL.DrawModelWiresEx( model, position, rotationAxis, rotationAngle, scale, tint ) end

---Draw a model as points
---@param model any
---@param position table
---@param scale number
---@param tint table
---@return any RL.DrawModelPoints
function  RL.DrawModelPoints( model, position, scale, tint ) end

---Draw a model as points with extended parameters
---@param model any
---@param position table
---@param rotationAxis table
---@param rotationAngle number
---@param scale table
---@param tint table
---@return any RL.DrawModelPointsEx
function  RL.DrawModelPointsEx( model, position, rotationAxis, rotationAngle, scale, tint ) end

---Draw bounding box (wires)
---@param box any
---@param color table
---@return any RL.DrawBoundingBox
function  RL.DrawBoundingBox( box, color ) end

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

-- Models - Mesh management functions

---Update mesh vertex data in GPU.
---NOTE: Mainly intented to be used with custom meshes.
---@param mesh any
---@param meshData table
---@return any RL.UpdateMesh
function  RL.UpdateMesh( mesh, meshData ) end

---Unload mesh data from CPU and GPU
---@param mesh any
---@return any RL.UnloadMesh
function  RL.UnloadMesh( mesh ) end

---Draw a 3d mesh with material and transform
---@param mesh any
---@param material any
---@param transform table
---@return any RL.DrawMesh
function  RL.DrawMesh( mesh, material, transform ) end

---Draw multiple mesh instances with material and different transforms
---@param mesh any
---@param material any
---@param transforms table
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

---Export mesh as code file (.h) defining multiple arrays of vertex attributes
---- Success return bool
---@param mesh any
---@param fileName string
---@return any success 
function RL.ExportMeshAsCode( mesh, fileName ) end

---Compute mesh bounding box limits
---- Success return BoundingBox
---@param mesh any
---@return any boundingBox 
function RL.GetMeshBoundingBox( mesh ) end

---Compute mesh tangents
---@param mesh any
---@return any RL.GenMeshTangents
function  RL.GenMeshTangents( mesh ) end

---Get mesh vertex attributes data as table.
---- Success return Mesh{}
---@param mesh any
---@return any meshData 
function RL.GetMeshData( mesh ) end

-- Models - Mesh generation functions

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

---Generate half-sphere mesh (no bottom cap)
---- Success return Mesh
---@param radius number
---@param rings integer
---@param slices integer
---@return any mesh 
function RL.GenMeshHemiSphere( radius, rings, slices ) end

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

---Generate cubes-based map mesh from image data
---- Success return Mesh
---@param cubicmap any
---@param cubeSize table
---@return any mesh 
function RL.GenMeshCubicmap( cubicmap, cubeSize ) end

---Generate custom mesh from vertex attribute data and uploads it into a VAO (if supported) and VBO
---- Success return Mesh
---@param meshData table
---@param dynamic boolean
---@return any mesh 
function RL.GenMeshCustom( meshData, dynamic ) end

-- Models - Material management functions

---Load materials from model file
---- Success return Material{}
---@param fileName string
---@return any materials 
function RL.LoadMaterials( fileName ) end

---Default material for reference. Return as lightuserdata
---- Success return Material
---@return any material 
function RL.GetMaterialDefault() end

---Load default material as new object
---- Success return Material
---@return any material 
function RL.LoadMaterialDefault() end

---Load material from table. See material table definition
---- Success return Material
---@param materialData table
---@return any material 
function RL.CreateMaterial( materialData ) end

---Check if a material is valid (shader assigned, map textures loaded in GPU)
---- Success return bool
---@param material any
---@return any isValid 
function RL.IsMaterialValid( material ) end

---Unload material from GPU memory (VRAM). Note! Use freeAll to unload shaders and textures
---@param material any
---@param freeAll boolean
---@return any RL.UnloadMaterial
function  RL.UnloadMaterial( material, freeAll ) end

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
---@param params table
---@return any RL.SetMaterialParams
function  RL.SetMaterialParams( material, params ) end

---Get texture from material map type. Return as lightuserdata
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

---Get material shader. Return as lightuserdata
---- Success return Shader
---@param material any
---@return any shader 
function RL.GetMaterialShader( material ) end

---Get material parameters
---- Success return float{}
---@param material any
---@return any params 
function RL.GetMaterialParams( material ) end

-- Model - Model animations management functions

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

---Update model animation mesh bone matrices (GPU skinning)
---@param model any
---@param animation any
---@param frame integer
---@return any RL.UpdateModelAnimationBones
function  RL.UpdateModelAnimationBones( model, animation, frame ) end

---Unload animation data
---@param animation any
---@return any RL.UnloadModelAnimation
function  RL.UnloadModelAnimation( animation ) end

---Unload animation table data
---@param animations table
---@return any RL.UnloadModelAnimations
function  RL.UnloadModelAnimations( animations ) end

---Check model animation skeleton match
---- Success return bool
---@param model any
---@param animation any
---@return any valid 
function RL.IsModelAnimationValid( model, animation ) end

---Set modelAnimation bones information (skeleton)
---- Failure return false
---- Success return true
---@param animation any
---@param boneId integer
---@param bone any
---@return any success 
function RL.SetModelAnimationBone( animation, boneId, bone ) end

---Set modelAnimation bones base transformation (pose)
---- Failure return false
---- Success return true
---@param animation any
---@param frame integer
---@param boneId integer
---@param pose any
---@return any success 
function RL.SetModelAnimationFramePose( animation, frame, boneId, pose ) end

---Set modelAnimation name
---@param animation any
---@param name string
---@return any RL.SetModelAnimationName
function  RL.SetModelAnimationName( animation, name ) end

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

---Get modelAnimation bones information (skeleton)
---- Failure return nil
---- Success return BoneInfo
---@param animation any
---@param boneId integer
---@return any bone 
function RL.GetModelAnimationBone( animation, boneId ) end

---Get modelAnimation bones base transformation (pose)
---- Failure return nil
---- Success return Transform
---@param animation any
---@param frame integer
---@param boneId integer
---@return any pose 
function RL.GetModelAnimationFramePose( animation, frame, boneId ) end

---Get modelAnimation name
---- Success return string
---@param animation any
---@return any name 
function RL.GetModelAnimationName( animation ) end

-- Model - Collision detection functions

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

---Get collision info between ray and quad. NOTE: The points are expected to be in counter-clockwise winding
---- Success return RayCollision
---@param ray any
---@param p1 table
---@param p2 table
---@param p3 table
---@param p4 table
---@return any rayCollision 
function RL.GetRayCollisionQuad( ray, p1, p2, p3, p4 ) end

---Get cell positions inside box that intersect with the ray. Also returns ray exit point. Returns empty table if ray misses the box
---- Success return Vector3{}, RayCollision|nil
---@param ray any
---@param box any
---@param cellSize table
---@return any cells
---@return any exitPoint 
function RL.GetRayBoxCells( ray, box, cellSize ) end

-- Audio - Audio device management functions

---Initialize audio device and context
---@return any RL.InitAudioDevice
function  RL.InitAudioDevice() end

---Close the audio device and context
---@return any RL.CloseAudioDevice
function  RL.CloseAudioDevice() end

---Check if audio device has been initialized successfully
---- Success return bool
---@return any isReady 
function RL.IsAudioDeviceReady() end

---Set master volume (listener)
---@param volume number
---@return any RL.SetMasterVolume
function  RL.SetMasterVolume( volume ) end

---Get master volume (listener)
---- Success return float
---@return any volume 
function RL.GetMasterVolume() end

-- Audio - Wave/Sound loading/unloading functions

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

---Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
---- Success return Wave
---@param fileType string
---@param data any
---@return any wave 
function RL.LoadWaveFromMemory( fileType, data ) end

---Checks if wave data is valid (data loaded and parameters)
---- Success return bool
---@param wave any
---@return any isValid 
function RL.IsWaveValid( wave ) end

---Load sound from wave data
---- Success return Sound
---@param wave any
---@return any sound 
function RL.LoadSoundFromWave( wave ) end

---Create a new sound that shares the same sample data as the source sound, does not own the sound data
---- Success return Sound
---@param source any
---@return any sound 
function RL.LoadSoundAlias( source ) end

---Checks if a sound is valid (data loaded and buffers initialized)
---- Success return bool
---@param sound any
---@return any isValid 
function RL.IsSoundValid( sound ) end

---Update sound buffer with new data
---@param sound any
---@param data any
---@param sampleCount integer
---@return any RL.UpdateSound
function  RL.UpdateSound( sound, data, sampleCount ) end

---Unload wave data
---@param wave any
---@return any RL.UnloadWave
function  RL.UnloadWave( wave ) end

---Unload sound
---@param sound any
---@return any RL.UnloadSound
function  RL.UnloadSound( sound ) end

---Unload a sound alias (does not deallocate sample data)
---@param alias any
---@return any RL.UnloadSoundAlias
function  RL.UnloadSoundAlias( alias ) end

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

-- Audio - Wave/Sound management functions

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

---Load samples data from wave as a 32bit float data array
---- Success return float{}
---@param wave any
---@return any samples 
function RL.LoadWaveSamples( wave ) end

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

-- Audio - Music management functions

---Load music stream from file
---- Success return Music
---@param fileName string
---@return any music 
function RL.LoadMusicStream( fileName ) end

---Load music stream from data
---- Success return Music
---@param fileType string
---@param data any
---@return any music 
function RL.LoadMusicStreamFromMemory( fileType, data ) end

---Checks if a music stream is valid (context and buffers initialized)
---- Success return bool
---@param music any
---@return any isValid 
function RL.IsMusicValid( music ) end

---Unload music stream
---@param music any
---@return any RL.UnloadMusicStream
function  RL.UnloadMusicStream( music ) end

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

---Round float value
---- Success return int
---@param value number
---@return any result 
function RL.Round( value ) end

---Sign of value
---- Success return int
---@param value number
---@return any result 
function RL.Sign( value ) end

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
---- Success return bool
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

---Calculate angle between two vectors
---NOTE: Angle is calculated from origin point (0, 0)
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Angle( v1, v2 ) end

---Calculate angle defined by a two vectors line
---NOTE: Parameters need to be normalized
---Current implementation should be aligned with glm::angle
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

---Get min value for each pair of components
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Min( v1, v2 ) end

---Get max value for each pair of components
---- Success return Vector2
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Max( v1, v2 ) end

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
---- Success return bool
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector2Equals( v1, v2 ) end

---Compute the direction of a refracted ray
---v: normalized direction of the incoming ray
---n: normalized normal vector of the interface of two optical media
---r: ratio of the refractive index of the medium from where the ray comes
---   to the refractive index of the medium on the other side of the surface
---- Success return Vector2
---@param v table
---@param n table
---@param r number
---@return any result 
function RL.Vector2Refract( v, n, r ) end

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

---Calculate the projection of the vector v1 on to v2
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Project( v1, v2 ) end

---Calculate the rejection of the vector v1 on to v2
---- Success return Vector3
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector3Reject( v1, v2 ) end

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

---Move Vector towards target
---- Success return Vector3
---@param v table
---@param target table
---@param maxDistance number
---@return any result 
function RL.Vector3MoveTowards( v, target, maxDistance ) end

---Calculate linear interpolation between two vectors
---- Success return Vector3
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector3Lerp( v1, v2, amount ) end

---Calculate cubic hermite interpolation between two vectors and their tangents
---as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
---- Success return Vector3
---@param v1 table
---@param tangent1 table
---@param v2 table
---@param tangent2 table
---@param amount number
---@return any result 
function RL.Vector3CubicHermite( v1, tangent1, v2, tangent2, amount ) end

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
---- Success return bool
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

-- Math - Vector4

---Vector with components value 0.0f
---- Success return Vector4
---@return any result 
function RL.Vector4Zero() end

---Vector with components value 1.0f
---- Success return Vector4
---@return any result 
function RL.Vector4One() end

---Add two vectors
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Add( v1, v2 ) end

---Add vector and float value
---- Success return Vector4
---@param v table
---@param add number
---@return any result 
function RL.Vector4AddValue( v, add ) end

---Subtract two vectors
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Subtract( v1, v2 ) end

---Subtract vector by float value
---- Success return Vector4
---@param v table
---@param sub number
---@return any result 
function RL.Vector4SubtractValue( v, sub ) end

---Calculate vector length
---- Success return float
---@param v table
---@return any result 
function RL.Vector4Length( v ) end

---Calculate vector square length
---- Success return float
---@param v table
---@return any result 
function RL.Vector4LengthSqr( v ) end

---Calculate two vectors dot product
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4DotProduct( v1, v2 ) end

---Calculate distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Distance( v1, v2 ) end

---Calculate square distance between two vectors
---- Success return float
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4DistanceSqr( v1, v2 ) end

---Multiply vector by scalar
---- Success return Vector4
---@param v table
---@param scalar number
---@return any result 
function RL.Vector4Scale( v, scalar ) end

---Multiply vector by vector
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Multiply( v1, v2 ) end

---Negate provided vector (invert direction)
---- Success return Vector4
---@param v table
---@return any result 
function RL.Vector4Negate( v ) end

---Divide vector by vector
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Divide( v1, v2 ) end

---Normalize provided vector
---- Success return Vector4
---@param v table
---@return any result 
function RL.Vector4Normalize( v ) end

---Get min value for each pair of components
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Min( v1, v2 ) end

---Get max value for each pair of components
---- Success return Vector4
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Max( v1, v2 ) end

---Calculate linear interpolation between two vectors
---- Success return Vector4
---@param v1 table
---@param v2 table
---@param amount number
---@return any result 
function RL.Vector4Lerp( v1, v2, amount ) end

---Move Vector towards target
---- Success return Vector4
---@param v table
---@param target table
---@param maxDistance number
---@return any result 
function RL.Vector4MoveTowards( v, target, maxDistance ) end

---Invert the given vector
---- Success return Vector4
---@param v table
---@return any result 
function RL.Vector4Invert( v ) end

---Check whether two given vectors are almost equal
---- Success return bool
---@param v1 table
---@param v2 table
---@return any result 
function RL.Vector4Equals( v1, v2 ) end

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
---@param angles table
---@return any result 
function RL.MatrixRotateXYZ( angles ) end

---Get zyx-rotation matrix (angles in radians)
---- Success return Matrix
---@param angles table
---@return any result 
function RL.MatrixRotateZYX( angles ) end

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

---Decompose a transformation matrix into its rotational, translational and scaling components
---- Success return Vector3, Quaternion, Vector3
---@param mat table
---@return any translation
---@return any rotation
---@return any scale 
function RL.MatrixDecompose( mat ) end

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

---Calculate quaternion cubic spline interpolation using Cubic Hermite Spline algorithm
---as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
---- Success return Quaternion
---@param q1 table
---@param outTangent1 table
---@param q2 table
---@param inTangent2 table
---@param t number
---@return any result 
function RL.QuaternionCubicHermiteSpline( q1, outTangent1, q2, inTangent2, t ) end

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

---Get a matrix for a given quaternion
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
---- Success return bool
---@param q1 table
---@param q2 table
---@return any result 
function RL.QuaternionEquals( q1, q2 ) end

-- Gui - Global gui state control functions

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
---@return any RL.GuiSetAlpha
function  RL.GuiSetAlpha( alpha ) end

---Set gui state (global state)
---@param state integer
---@return any RL.GuiSetState
function  RL.GuiSetState( state ) end

---Get gui state (global state)
---- Success return int
---@return any state 
function RL.GuiGetState() end

---Set guiSliderDragging
---@param dragging boolean
---@return any RL.GuiSetSliderDragging
function  RL.GuiSetSliderDragging( dragging ) end

---Get guiSliderDragging
---- Success return bool
---@return any isSliderDragging 
function RL.GuiGetSliderDragging() end

---Set guiSliderActive
---@param rect any
---@return any RL.GuiSetSliderActive
function  RL.GuiSetSliderActive( rect ) end

---Get guiSliderActive
---- Success return Rectangle
---@return any isSliderDragging 
function RL.GuiGetSliderActive() end

-- Gui - Font set/get functions

---Set gui custom font (global state)
---@param font any
---@return any RL.GuiSetFont
function  RL.GuiSetFont( font ) end

---Get gui font (global state). Return as lightuserdata
---- Success return Font
---@return any font 
function RL.GuiGetFont() end

-- Gui - Style set/get functions

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

-- Gui - Styles loading functions

---Load style file over global style variable (.rgs)
---- Failure return nil
---- Success return true
---@param fileName string
---@return any success 
function RL.GuiLoadStyle( fileName ) end

---Load style default over global style
---@return any RL.GuiLoadStyleDefault
function  RL.GuiLoadStyleDefault() end

-- Gui - Tooltips management functions

---Enable gui tooltips (global state)
---@return any RL.GuiEnableTooltip
function  RL.GuiEnableTooltip() end

---Disable gui tooltips (global state)
---@return any RL.GuiDisableTooltip
function  RL.GuiDisableTooltip() end

---Set tooltip string
---@param tooltip string
---@return any RL.GuiSetTooltip
function  RL.GuiSetTooltip( tooltip ) end

-- Gui - Icons functionality

---Get text with icon id prepended (if supported)
---- Success return string
---@param iconId integer
---@param text string|nil
---@return any text 
function RL.GuiIconText( iconId, text ) end

---Set icon scale (1 by default)
---@param scale integer
---@return any RL.GuiSetIconScale
function  RL.GuiSetIconScale( scale ) end

---Get raygui icons data in buffer. guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB
---- Success return Buffer
---@return any iconsBuffer 
function RL.GuiGetIcons() end

---Set raygui icons data in buffer. guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB
---- Failure return false
---- Success return true
---@param iconBuffer any
---@return any success 
function RL.GuiSetIcons( iconBuffer ) end

---Load raygui icons file (.rgi) into internal icons data
---- Failure return nil
---- Success return strings{}
---@param fileName string
---@param loadIconsName boolean
---@return any iconNames 
function RL.GuiLoadIcons( fileName, loadIconsName ) end

---Draw icon
---@param iconId integer
---@param pos table
---@param pixelSize integer
---@param color table
---@return any RL.GuiDrawIcon
function  RL.GuiDrawIcon( iconId, pos, pixelSize, color ) end

-- Gui - Container/separator controls, useful for controls organization

---Window Box control, shows a window that can be closed
---- Success return int
---@param bounds table
---@param title string|nil
---@return any result 
function RL.GuiWindowBox( bounds, title ) end

---Group Box control with text name
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiGroupBox( bounds, text ) end

---Line separator control, could contain text
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiLine( bounds, text ) end

---Panel control, useful to group controls
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiPanel( bounds, text ) end

---Tab Bar control, returns TAB to be closed or -1
---- Success return int, int
---@param bounds table
---@param text string
---@param active integer
---@return any result
---@return any active 
function RL.GuiTabBar( bounds, text, active ) end

---Scroll Panel control
---- Success return int, Vector2, Rectangle
---@param bounds table
---@param text string|nil
---@param content table
---@param scroll table
---@param view table
---@return any result
---@return any scroll
---@return any view 
function RL.GuiScrollPanel( bounds, text, content, scroll, view ) end

-- Gui - Basic controls set

---Label control, shows text
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiLabel( bounds, text ) end

---Button control, returns true when clicked
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiButton( bounds, text ) end

---Label button control, show true when clicked
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiLabelButton( bounds, text ) end

---Toggle Button control, returns true when active
---- Success return int, bool
---@param bounds table
---@param text string|nil
---@param active boolean
---@return any result
---@return any active 
function RL.GuiToggle( bounds, text, active ) end

---Toggle Group control, returns active toggle index
---- Success return int, int
---@param bounds table
---@param text string|nil
---@param active integer
---@return any result
---@return any active 
function RL.GuiToggleGroup( bounds, text, active ) end

---Toggle Slider control, returns true when clicked
---- Success return int, int
---@param bounds table
---@param text string|nil
---@param active integer
---@return any result
---@return any active 
function RL.GuiToggleSlider( bounds, text, active ) end

---Check Box control, returns true when active
---- Success return bool, Rectangle
---@param bounds table
---@param text string|nil
---@param checked boolean
---@return any result
---@return any checked
---@return any textBounds 
function RL.GuiCheckBox( bounds, text, checked ) end

---Combo Box control, returns selected item index
---- Success return int, int
---@param bounds table
---@param text string|nil
---@param active integer
---@return any result
---@return any active 
function RL.GuiComboBox( bounds, text, active ) end

---Dropdown Box control, returns selected item
---- Success return int, int
---@param bounds table
---@param text string
---@param active integer
---@param editMode boolean
---@return any result
---@return any active 
function RL.GuiDropdownBox( bounds, text, active, editMode ) end

---Spinner control, returns selected value
---- Success return int, int, Rectangle
---@param bounds table
---@param text string|nil
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@return any result
---@return any value
---@return any textBounds 
function RL.GuiSpinner( bounds, text, value, minValue, maxValue, editMode ) end

---Value Box control, updates input text with numbers
---- Success return int, int, Rectangle
---@param bounds table
---@param text string|nil
---@param value integer
---@param minValue integer
---@param maxValue integer
---@param editMode boolean
---@return any result
---@return any value
---@return any textBounds 
function RL.GuiValueBox( bounds, text, value, minValue, maxValue, editMode ) end

---Text Box control, updates input text
---- Success return int, string
---@param bounds table
---@param text string
---@param bufferSize integer
---@param editMode boolean
---@return any result
---@return any text 
function RL.GuiTextBox( bounds, text, bufferSize, editMode ) end

---Slider control, returns selected value
---- Success return int, float, Rectangle, Rectangle
---@param bounds table
---@param textLeft string|nil
---@param textRight string|nil
---@param value number
---@param minValue number
---@param maxValue number
---@return any result
---@return any value
---@return any textLeftBounds
---@return any textRightBounds 
function RL.GuiSlider( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Slider Bar control, returns selected value
---- Success return int, float, Rectangle, Rectangle
---@param bounds table
---@param textLeft string|nil
---@param textRight string|nil
---@param value number
---@param minValue number
---@param maxValue number
---@return any result
---@return any value
---@return any textLeftBounds
---@return any textRightBounds 
function RL.GuiSliderBar( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Progress Bar control, shows current progress value
---- Success return int, float, Rectangle, Rectangle
---@param bounds table
---@param textLeft string|nil
---@param textRight string|nil
---@param value number
---@param minValue number
---@param maxValue number
---@return any result
---@return any value
---@return any textLeftBounds
---@return any textRightBounds 
function RL.GuiProgressBar( bounds, textLeft, textRight, value, minValue, maxValue ) end

---Status Bar control, shows info text
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiStatusBar( bounds, text ) end

---Dummy control for placeholders
---- Success return int
---@param bounds table
---@param text string|nil
---@return any result 
function RL.GuiDummyRec( bounds, text ) end

---Grid control, returns mouse cell position
---- Success return int, Vector2
---@param bounds table
---@param text string|nil
---@param spacing number
---@param subdivs integer
---@param mouseCell table
---@return any result
---@return any mouseCell 
function RL.GuiGrid( bounds, text, spacing, subdivs, mouseCell ) end

---Scroll bar control
---- Success return int
---@param bounds table
---@param value integer
---@param minValue integer
---@param maxValue integer
---@return any value 
function RL.GuiScrollBar( bounds, value, minValue, maxValue ) end

-- Gui - Advance controls set

---List View control, returns selected list item index
---- Success return int, int, int
---@param bounds table
---@param text string|nil
---@param scrollIndex integer
---@param active integer
---@return any result
---@return any scrollIndex
---@return any active 
function RL.GuiListView( bounds, text, scrollIndex, active ) end

---List View with extended parameters
---- Success return int, int, int, int
---@param bounds table
---@param text string
---@param scrollIndex integer
---@param active integer
---@param focus integer
---@return any result
---@return any scrollIndex
---@return any active
---@return any focus 
function RL.GuiListViewEx( bounds, text, scrollIndex, active, focus ) end

---Message Box control, displays a message
---- Success return int
---@param bounds table
---@param title string|nil
---@param message string
---@param buttons string
---@return any result 
function RL.GuiMessageBox( bounds, title, message, buttons ) end

---Text Input Box control, ask for text, supports secret
---- Success return int, string, bool
---@param bounds table
---@param title string
---@param message string
---@param buttons string
---@param text string
---@param textMaxSize integer
---@param secretViewActive boolean
---@return any result
---@return any text
---@return any secretViewActive 
function RL.GuiTextInputBox( bounds, title, message, buttons, text, textMaxSize, secretViewActive ) end

---Color Picker control (multiple color controls)
---- Success return int, Color
---@param bounds table
---@param text string|nil
---@param color table
---@return any result
---@return any color 
function RL.GuiColorPicker( bounds, text, color ) end

---Color Panel control
---- Success return int, Color
---@param bounds table
---@param text string|nil
---@param color table
---@return any result
---@return any color 
function RL.GuiColorPanel( bounds, text, color ) end

---Color Bar Alpha control
---- Success return int, float
---@param bounds table
---@param text string|nil
---@param alpha number
---@return any result
---@return any alpha 
function RL.GuiColorBarAlpha( bounds, text, alpha ) end

---Color Bar Hue control
---- Success return int, float
---@param bounds table
---@param text string|nil
---@param value number
---@return any result
---@return any value 
function RL.GuiColorBarHue( bounds, text, value ) end

---Color Picker control that avoids conversion to RGB on each call (multiple color controls)
---- Success return int, Vector3
---@param bounds table
---@param text string|nil
---@param colorHsv table
---@return any result
---@return any colorHsv 
function RL.GuiColorPickerHSV( bounds, text, colorHsv ) end

---Color Panel control that returns HSV color value, used by GuiColorPickerHSV()
---- Success return int, Vector3
---@param bounds table
---@param text string|nil
---@param colorHsv table
---@return any result
---@return any colorHsv 
function RL.GuiColorPanelHSV( bounds, text, colorHsv ) end

-- Lights - Light management functions

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
---- Success return bool
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

---Set clip planes distances
---@param nearPlane number
---@param farPlane number
---@return any RL.rlSetClipPlanes
function  RL.rlSetClipPlanes( nearPlane, farPlane ) end

---Get cull plane distance near
---- Success return float
---@return any distance 
function RL.rlGetCullDistanceNear() end

---Get cull plane distance far
---- Success return float
---@return any distance 
function RL.rlGetCullDistanceFar() end

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

---Enable attribute state pointer
---@param vertexAttribType integer
---@param buffer any
---@return any RL.rlEnableStatePointer
function  RL.rlEnableStatePointer( vertexAttribType, buffer ) end

---Disable attribute state pointer
---@param vertexAttribType integer
---@return any RL.rlDisableStatePointer
function  RL.rlDisableStatePointer( vertexAttribType ) end

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

---Get the currently active render texture (fbo), 0 for default framebuffer
---- Success return int
---@return any framebuffer 
function RL.rlGetActiveFramebuffer() end

---Activate multiple draw color buffers
---@param count integer
---@return any RL.rlActiveDrawBuffers
function  RL.rlActiveDrawBuffers( count ) end

---Blit active framebuffer to main framebuffer
---@param srcRect table
---@param dstRect table
---@param bufferMask integer
---@return any RL.rlBlitFramebuffer
function  RL.rlBlitFramebuffer( srcRect, dstRect, bufferMask ) end

---Bind framebuffer (FBO)
---@param target integer
---@param framebuffer integer
---@return any RL.rlBindFramebuffer
function  RL.rlBindFramebuffer( target, framebuffer ) end

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

---Color mask control
---@param r boolean
---@param g boolean
---@param b boolean
---@param a boolean
---@return any RL.rlColorMask
function  RL.rlColorMask( r, g, b, a ) end

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

---Enable point mode
---@return any RL.rlEnablePointMode
function  RL.rlEnablePointMode() end

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

---Set current framebuffer width
---@param width integer
---@return any version 
function RL.rlSetFramebufferWidth( width ) end

---Get default framebuffer width
---- Success return int
---@return any width 
function RL.rlGetFramebufferWidth() end

---Set current framebuffer height
---@param height integer
---@return any version 
function RL.rlSetFramebufferHeight( height ) end

---Get default framebuffer height
---- Success return int
---@return any height 
function RL.rlGetFramebufferHeight() end

---Get default texture id
---- Success return int
---@return any id 
function RL.rlGetTextureIdDefault() end

---Get default shader id
---- Success return int
---@return any id 
function RL.rlGetShaderIdDefault() end

---Get default shader locations
---- Success return int{}
---@return any locations 
function RL.rlGetShaderLocsDefault() end

-- RLGL - Render batch management

---Load a render batch system
---- Success return rlRenderBatch
---@param numBuffers integer
---@param bufferElements integer
---@return any renderBatch 
function RL.rlLoadRenderBatch( numBuffers, bufferElements ) end

---Unload render batch system
---@param renderBatch any
---@return any RL.rlUnloadRenderBatch
function  RL.rlUnloadRenderBatch( renderBatch ) end

---Draw render batch data (Update->Draw->Reset)
---@param renderBatch any
---@return any RL.rlDrawRenderBatch
function  RL.rlDrawRenderBatch( renderBatch ) end

---Set the active render batch for rlgl (nil for default internal)
---@param renderBatch any
---@return any RL.rlSetRenderBatchActive
function  RL.rlSetRenderBatchActive( renderBatch ) end

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

---Set vertex attribute data configuration
---@param index integer
---@param compSize integer
---@param type integer
---@param normalized boolean
---@param stride integer
---@param offset integer
---@return any RL.rlSetVertexAttribute
function  RL.rlSetVertexAttribute( index, compSize, type, normalized, stride, offset ) end

---Set vertex attribute divisor
---@param index integer
---@param divisor integer
---@return any RL.rlSetVertexAttributeDivisor
function  RL.rlSetVertexAttributeDivisor( index, divisor ) end

---Set vertex attribute default value
---@param locIndex integer
---@param value table
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
---@param data any
---@param size table
---@param format integer
---@param mipmapCount integer
---@return any id 
function RL.rlLoadTexture( data, size, format, mipmapCount ) end

---Load depth texture/renderbuffer (to be attached to fbo)
---- Success return int
---@param size table
---@param useRenderBuffer boolean
---@return any id 
function RL.rlLoadTextureDepth( size, useRenderBuffer ) end

---Load texture cubemap data
---- Success return int
---@param data any
---@param size integer
---@param format integer
---@param mipmapCount integer
---@return any id 
function RL.rlLoadTextureCubemap( data, size, format, mipmapCount ) end

---Update GPU texture with new data
---@param id integer
---@param offset table
---@param size table
---@param format integer
---@param data any
---@return any RL.rlUpdateTexture
function  RL.rlUpdateTexture( id, offset, size, format, data ) end

---Get OpenGL internal formats
---- Success return int, int, int
---@param format integer
---@return any glInternalFormat
---@return any glFormat
---@return any glType 
function RL.rlGetGlTextureFormats( format ) end

---Get name string for pixel format
---- Success return string
---@param format integer
---@return any name 
function RL.rlGetPixelFormatName( format ) end

---Unload texture from GPU memory
---@param id integer
---@return any RL.rlUnloadTexture
function  RL.rlUnloadTexture( id ) end

---Generate mipmap data for selected texture
---- Success return int
---@param id integer
---@param size table
---@param format integer
---@return any mipmapCount 
function RL.rlGenTextureMipmaps( id, size, format ) end

---Read texture pixel data
---- Success return Buffer
---@param id integer
---@param size table
---@param format integer
---@return any data 
function RL.rlReadTexturePixels( id, size, format ) end

---Read screen pixel data (color buffer)
---- Success return Buffer
---@param size table
---@return any data 
function RL.rlReadScreenPixels( size ) end

-- RLGL - Framebuffer management (fbo)

---Load an empty framebuffer
---- Success return int
---@return any fboId 
function RL.rlLoadFramebuffer() end

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
---- Success return int
---@param vsCode string
---@param fsCode string
---@return any shaderId 
function RL.rlLoadShaderCode( vsCode, fsCode ) end

---Compile custom shader and return shader id (type: RL_VERTEX_SHADER, RL_FRAGMENT_SHADER, RL_COMPUTE_SHADER)
---- Success return int
---@param shaderCode string
---@param type integer
---@return any shaderId 
function RL.rlCompileShader( shaderCode, type ) end

---Load custom shader program
---- Success return int
---@param vShaderId integer
---@param fShaderId integer
---@return any shaderProgramId 
function RL.rlLoadShaderProgram( vShaderId, fShaderId ) end

---Unload shader program
---@param id integer
---@return any RL.rlUnloadShaderProgram
function  RL.rlUnloadShaderProgram( id ) end

---Get shader location uniform
---- Success return int
---@param shaderId integer
---@param uniformName string
---@return any location 
function RL.rlGetLocationUniform( shaderId, uniformName ) end

---Get shader location attribute
---- Success return int
---@param shaderId integer
---@param attribName string
---@return any location 
function RL.rlGetLocationAttrib( shaderId, attribName ) end

---Set shader value uniform
---@param locIndex integer
---@param value any
---@param uniformType integer
---@param count integer
---@return any RL.rlSetUniform
function  RL.rlSetUniform( locIndex, value, uniformType, count ) end

---Set shader value matrix
---@param locIndex integer
---@param mat table
---@return any RL.rlSetUniformMatrix
function  RL.rlSetUniformMatrix( locIndex, mat ) end

---Set shader value matrices
---@param locIndex integer
---@param mat table
---@return any RL.rlSetUniformMatrices
function  RL.rlSetUniformMatrices( locIndex, mat ) end

---Set shader value sampler
---@param locIndex integer
---@param textureId integer
---@return any RL.rlSetUniformSampler
function  RL.rlSetUniformSampler( locIndex, textureId ) end

---Set shader currently active (id and locations)
---@param id integer
---@param locs table
---@return any RL.rlSetShader
function  RL.rlSetShader( id, locs ) end

-- RLGL - Compute shader management

---Load compute shader program
---- Success return int
---@param shaderId integer
---@return any programId 
function RL.rlLoadComputeShaderProgram( shaderId ) end

---Dispatch compute shader (equivalent to *draw* for graphics pipeline)
---@param groupX integer
---@param groupY integer
---@param groupZ integer
---@return any RL.rlComputeShaderDispatch
function  RL.rlComputeShaderDispatch( groupX, groupY, groupZ ) end

-- RLGL - Shader buffer storage object management (ssbo)

---Load shader storage buffer object (SSBO)
---- Success return int
---@param size integer
---@param data any
---@param usageHint integer
---@return any buffer 
function RL.rlLoadShaderBuffer( size, data, usageHint ) end

---Unload shader storage buffer object (SSBO)
---@param ssboId integer
---@return any RL.rlUnloadShaderBuffer
function  RL.rlUnloadShaderBuffer( ssboId ) end

---Update SSBO buffer data
---@param id integer
---@param data any
---@param offset integer
---@return any RL.rlUpdateShaderBuffer
function  RL.rlUpdateShaderBuffer( id, data, offset ) end

---Bind SSBO buffer
---@param id integer
---@param index integer
---@return any RL.rlBindShaderBuffer
function  RL.rlBindShaderBuffer( id, index ) end

---Read SSBO buffer data (GPU->CPU)
---- Success return Buffer
---@param id integer
---@param count integer
---@param offset integer
---@return any data 
function RL.rlReadShaderBuffer( id, count, offset ) end

---Copy SSBO data between buffers
---@param destId integer
---@param srcId integer
---@param destOffset integer
---@param srcOffset integer
---@param count integer
---@return any RL.rlCopyShaderBuffer
function  RL.rlCopyShaderBuffer( destId, srcId, destOffset, srcOffset, count ) end

---Get SSBO buffer size
---- Success return int
---@param id integer
---@return any size 
function RL.rlGetShaderBufferSize( id ) end

-- RLGL - Buffer management

---Bind image texture
---@param id integer
---@param index integer
---@param format integer
---@param readonly boolean
---@return any RL.rlBindImageTexture
function  RL.rlBindImageTexture( id, index, format, readonly ) end

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

-- OpenGL - Rendering

---Clear buffers to preset values
---@param mask integer
---@return any RL.glClear
function  RL.glClear( mask ) end

-- OpenGL - Frame Buffers

---Copy a block of pixels from one framebuffer object to another.
---Use nil RenderTexture for window framebuffer
---@param srcTex any
---@param dstTex any
---@param srcRect table
---@param dstRect table
---@param mask integer
---@param filter integer
---@return any RL.glBlitFramebuffer
function  RL.glBlitFramebuffer( srcTex, dstTex, srcRect, dstRect, mask, filter ) end

-- OpenGL - State Management

---Specify mapping of depth values from normalized device coordinates to window coordinates
---@param nearVal number
---@param farVal number
---@return any RL.glDepthRange
function  RL.glDepthRange( nearVal, farVal ) end

---Enable server-side GL capabilities
---@param cap integer
---@return any RL.glEnable
function  RL.glEnable( cap ) end

---Disable server-side GL capabilities
---@param cap integer
---@return any RL.glDisable
function  RL.glDisable( cap ) end

---Set the scale and units used to calculate depth values
---@param factor number
---@param units number
---@return any RL.glPolygonOffset
function  RL.glPolygonOffset( factor, units ) end

---Set front and back function and reference value for stencil testing
---@param func integer
---@param ref integer
---@param mask integer
---@return any RL.glStencilFunc
function  RL.glStencilFunc( func, ref, mask ) end

---Set front and/or back function and reference value for stencil testing
---@param face integer
---@param func integer
---@param ref integer
---@param mask integer
---@return any RL.glStencilFuncSeparate
function  RL.glStencilFuncSeparate( face, func, ref, mask ) end

---Control the front and back writing of individual bits in the stencil planes
---@param mask integer
---@return any RL.glStencilMask
function  RL.glStencilMask( mask ) end

---Control the front and/or back writing of individual bits in the stencil planes
---@param face integer
---@param mask integer
---@return any RL.glStencilMaskSeparate
function  RL.glStencilMaskSeparate( face, mask ) end

---Set front and back stencil test actions
---@param sfail integer
---@param dpfail integer
---@param dppass integer
---@return any RL.glStencilOp
function  RL.glStencilOp( sfail, dpfail, dppass ) end

---Set front and back stencil test actions
---@param face integer
---@param sfail integer
---@param dpfail integer
---@param dppass integer
---@return any RL.glStencilOpSeparate
function  RL.glStencilOpSeparate( face, sfail, dpfail, dppass ) end

-- OpenGL - Utility

---Return a string describing the current GL connection. GL_EXTENSIONS returns the extension string supported by the implementation at index
---- Success return string
---@param name integer
---@param index integer|nil
---@return any connection 
function RL.glGetString( name, index ) end

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

-- Bitwise Operations - Arithmetic

---Equivalent to a & b in C
---- Success return int
---@param a integer
---@param b integer
---@return any result 
function RL.BitAnd( a, b ) end

---Equivalent to a | b in C
---- Success return int
---@param a integer
---@param b integer
---@return any result 
function RL.BitOr( a, b ) end

---Equivalent to a ^ b in C
---- Success return int
---@param a integer
---@param b integer
---@return any result 
function RL.BitXor( a, b ) end

---Equivalent to ~v in C
---- Success return int
---@param v integer
---@return any result 
function RL.BitNot( v ) end

---Equivalent to v << n in C
---- Success return int
---@param v integer
---@param n integer
---@return any result 
function RL.BitShiftLeft( v, n ) end

---Equivalent to v >> n in C
---- Success return int
---@param v integer
---@param n integer
---@return any result 
function RL.BitShiftRight( v, n ) end

---Set bit in index i to state b in value v
---- Success return int
---@param v integer
---@param i integer
---@param b boolean
---@return any result 
function RL.BitSet( v, i, b ) end

---Get bit in index i from value v
---- Success return bool
---@param v integer
---@param i integer
---@return any bit 
function RL.BitGet( v, i ) end

---Toggle bit in index i in value v
---- Success return int
---@param v integer
---@param i integer
---@return any result 
function RL.BitToggle( v, i ) end

-- GLFW Core - Input-related functions: keyboard

---This function returns the name of the specified printable key, encoded as UTF-8.
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

