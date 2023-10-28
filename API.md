# ReiLua API

## Functions

Application needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where "main.lua" is located can be given as argument. There are five Lua functions that the framework will call, 'RL.init', 'RL.process', 'RL.draw', 'RL.event', 'RL.log', and 'RL.exit'.

---
> function RL.init()

This function will be called first when 'main.lua' is found

---

> function RL.process( delta )

This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'

---

> function RL.draw()

This function will be called every frame after process and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.

---

> function RL.event( event )

This function will be called on events input. Content of event table is determined by event type.

---

> function RL.log( logLevel, message )

This function can be used for custom log message handling.

---

> function RL.exit()

This function will be called on program close. Cleanup could be done here.

---

## Arguments

Arguments are stored in 'RL.arg' array.

## Globals - ConfigFlags
FLAG_VSYNC_HINT = 64

FLAG_FULLSCREEN_MODE = 2

FLAG_WINDOW_RESIZABLE = 4

FLAG_WINDOW_UNDECORATED = 8

FLAG_WINDOW_HIDDEN = 128

FLAG_WINDOW_MINIMIZED = 512

FLAG_WINDOW_MAXIMIZED = 1024

FLAG_WINDOW_UNFOCUSED = 2048

FLAG_WINDOW_TOPMOST = 4096

FLAG_WINDOW_ALWAYS_RUN = 256

FLAG_WINDOW_TRANSPARENT = 16

FLAG_WINDOW_HIGHDPI = 8192

FLAG_MSAA_4X_HINT = 32

FLAG_INTERLACED_HINT = 65536


## Globals - TraceLogLevel
LOG_ALL = 0

LOG_TRACE = 1

LOG_DEBUG = 2

LOG_INFO = 3

LOG_WARNING = 4

LOG_ERROR = 5

LOG_FATAL = 6

LOG_NONE = 7


## Globals - KeyboardKey

GLFW_KEY_UNKNOWN = nil

KEY_NULL = 0

KEY_APOSTROPHE = 39

KEY_COMMA = 44

KEY_MINUS = 45

KEY_PERIOD = 46

KEY_SLASH = 47

KEY_ZERO = 48

KEY_ONE = 49

KEY_TWO = 50

KEY_THREE = 51

KEY_FOUR = 52

KEY_FIVE = 53

KEY_SIX = 54

KEY_SEVEN = 55

KEY_EIGHT = 56

KEY_NINE = 57

KEY_SEMICOLON = 59

KEY_EQUAL = 61

KEY_A = 65

KEY_B = 66

KEY_C = 67

KEY_D = 68

KEY_E = 69

KEY_F = 70

KEY_G = 71

KEY_H = 72

KEY_I = 73

KEY_J = 74

KEY_K = 75

KEY_L = 76

KEY_M = 77

KEY_N = 78

KEY_O = 79

KEY_P = 80

KEY_Q = 81

KEY_R = 82

KEY_S = 83

KEY_T = 84

KEY_U = 85

KEY_V = 86

KEY_W = 87

KEY_X = 88

KEY_Y = 89

KEY_Z = 90

KEY_LEFT_BRACKET = 91

KEY_BACKSLASH = 92

KEY_RIGHT_BRACKET = 93

KEY_GRAVE = 96

KEY_SPACE = 32

KEY_ESCAPE = 256

KEY_ENTER = 257

KEY_TAB = 258

KEY_BACKSPACE = 259

KEY_INSERT = 260

KEY_DELETE = 261

KEY_RIGHT = 262

KEY_LEFT = 263

KEY_DOWN = 264

KEY_UP = 265

KEY_PAGE_UP = 266

KEY_PAGE_DOWN = 267

KEY_HOME = 268

KEY_END = 269

KEY_CAPS_LOCK = 280

KEY_SCROLL_LOCK = 281

KEY_NUM_LOCK = 282

KEY_PRINT_SCREEN = 283

KEY_PAUSE = 284

KEY_F1 = 290

KEY_F2 = 291

KEY_F3 = 292

KEY_F4 = 293

KEY_F5 = 294

KEY_F6 = 295

KEY_F7 = 296

KEY_F8 = 297

KEY_F9 = 298

KEY_F10 = 299

KEY_F11 = 300

KEY_F12 = 301

KEY_LEFT_SHIFT = 340

KEY_LEFT_CONTROL = 341

KEY_LEFT_ALT = 342

KEY_LEFT_SUPER = 343

KEY_RIGHT_SHIFT = 344

KEY_RIGHT_CONTROL = 345

KEY_RIGHT_ALT = 346

KEY_RIGHT_SUPER = 347

KEY_KB_MENU = 348

KEY_KP_0 = 320

KEY_KP_1 = 321

KEY_KP_2 = 322

KEY_KP_3 = 323

KEY_KP_4 = 324

KEY_KP_5 = 325

KEY_KP_6 = 326

KEY_KP_7 = 327

KEY_KP_8 = 328

KEY_KP_9 = 329

KEY_KP_DECIMAL = 330

KEY_KP_DIVIDE = 331

KEY_KP_MULTIPLY = 332

KEY_KP_SUBTRACT = 333

KEY_KP_ADD = 334

KEY_KP_ENTER = 335

KEY_KP_EQUAL = 336

KEY_BACK = 4

KEY_MENU = 82

KEY_VOLUME_UP = 24

KEY_VOLUME_DOWN = 25


## Globals - MouseButtons
MOUSE_BUTTON_LEFT = 0

MOUSE_BUTTON_RIGHT = 1

MOUSE_BUTTON_MIDDLE = 2

MOUSE_BUTTON_SIDE = 3

MOUSE_BUTTON_EXTRA = 4

MOUSE_BUTTON_FORWARD = 5

MOUSE_BUTTON_BACK = 6


## Globals - MouseCursor
MOUSE_CURSOR_DEFAULT = 0

MOUSE_CURSOR_ARROW = 1

MOUSE_CURSOR_IBEAM = 2

MOUSE_CURSOR_CROSSHAIR = 3

MOUSE_CURSOR_POINTING_HAND = 4

MOUSE_CURSOR_RESIZE_EW = 5

MOUSE_CURSOR_RESIZE_NS = 6

MOUSE_CURSOR_RESIZE_NWSE = 7

MOUSE_CURSOR_RESIZE_NESW = 8

MOUSE_CURSOR_RESIZE_ALL = 9

MOUSE_CURSOR_NOT_ALLOWED = 10


## Globals - GamepadButtons
GAMEPAD_BUTTON_UNKNOWN = 0

GAMEPAD_BUTTON_LEFT_FACE_UP = 1

GAMEPAD_BUTTON_LEFT_FACE_RIGHT = 2

GAMEPAD_BUTTON_LEFT_FACE_DOWN = 3

GAMEPAD_BUTTON_LEFT_FACE_LEFT = 4

GAMEPAD_BUTTON_RIGHT_FACE_UP = 5

GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = 6

GAMEPAD_BUTTON_RIGHT_FACE_DOWN = 7

GAMEPAD_BUTTON_RIGHT_FACE_LEFT = 8

GAMEPAD_BUTTON_LEFT_TRIGGER_1 = 9

GAMEPAD_BUTTON_LEFT_TRIGGER_2 = 10

GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = 11

GAMEPAD_BUTTON_RIGHT_TRIGGER_2 = 12

GAMEPAD_BUTTON_MIDDLE_LEFT = 13

GAMEPAD_BUTTON_MIDDLE = 14

GAMEPAD_BUTTON_MIDDLE_RIGHT = 15

GAMEPAD_BUTTON_LEFT_THUMB = 16

GAMEPAD_BUTTON_RIGHT_THUMB = 17


## Globals - GamepadAxis
GAMEPAD_AXIS_LEFT_X = 0

GAMEPAD_AXIS_LEFT_Y = 1

GAMEPAD_AXIS_RIGHT_X = 2

GAMEPAD_AXIS_RIGHT_Y = 3

GAMEPAD_AXIS_LEFT_TRIGGER = 4

GAMEPAD_AXIS_RIGHT_TRIGGER = 5


## Globals - MapTypes
MATERIAL_MAP_ALBEDO = 0

MATERIAL_MAP_METALNESS = 1

MATERIAL_MAP_NORMAL = 2

MATERIAL_MAP_ROUGHNESS = 3

MATERIAL_MAP_OCCLUSION = 4

MATERIAL_MAP_EMISSION = 5

MATERIAL_MAP_HEIGHT = 6

MATERIAL_MAP_CUBEMAP = 7

MATERIAL_MAP_IRRADIANCE = 8

MATERIAL_MAP_PREFILTER = 9

MATERIAL_MAP_BRDF = 10

MATERIAL_MAP_DIFFUSE = 0

MATERIAL_MAP_SPECULAR = 1


## Globals - ShaderLocationIndex
SHADER_LOC_VERTEX_POSITION = 0

SHADER_LOC_VERTEX_TEXCOORD01 = 1

SHADER_LOC_VERTEX_TEXCOORD02 = 2

SHADER_LOC_VERTEX_NORMAL = 3

SHADER_LOC_VERTEX_TANGENT = 4

SHADER_LOC_VERTEX_COLOR = 5

SHADER_LOC_MATRIX_MVP = 6

SHADER_LOC_MATRIX_VIEW = 7

SHADER_LOC_MATRIX_PROJECTION = 8

SHADER_LOC_MATRIX_MODEL = 9

SHADER_LOC_MATRIX_NORMAL = 10

SHADER_LOC_VECTOR_VIEW = 11

SHADER_LOC_COLOR_DIFFUSE = 12

SHADER_LOC_COLOR_SPECULAR = 13

SHADER_LOC_COLOR_AMBIENT = 14

SHADER_LOC_MAP_ALBEDO = 15

SHADER_LOC_MAP_METALNESS = 16

SHADER_LOC_MAP_NORMAL = 17

SHADER_LOC_MAP_ROUGHNESS = 18

SHADER_LOC_MAP_OCCLUSION = 19

SHADER_LOC_MAP_EMISSION = 20

SHADER_LOC_MAP_HEIGHT = 21

SHADER_LOC_MAP_CUBEMAP = 22

SHADER_LOC_MAP_IRRADIANCE = 23

SHADER_LOC_MAP_PREFILTER = 24

SHADER_LOC_MAP_BRDF = 25

SHADER_LOC_MAP_DIFFUSE = 15

SHADER_LOC_MAP_SPECULAR = 16


## Globals - ShaderUniformDataType
SHADER_UNIFORM_FLOAT = 0

SHADER_UNIFORM_VEC2 = 1

SHADER_UNIFORM_VEC3 = 2

SHADER_UNIFORM_VEC4 = 3

SHADER_UNIFORM_INT = 4

SHADER_UNIFORM_IVEC2 = 5

SHADER_UNIFORM_IVEC3 = 6

SHADER_UNIFORM_IVEC4 = 7

SHADER_UNIFORM_SAMPLER2D = 8


## Globals - ShaderAttributeDataTypes
SHADER_ATTRIB_FLOAT = 0

SHADER_ATTRIB_VEC2 = 1

SHADER_ATTRIB_VEC3 = 2

SHADER_ATTRIB_VEC4 = 3


## Globals - PixelFormats
PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1

PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA = 2

PIXELFORMAT_UNCOMPRESSED_R5G6B5 = 3

PIXELFORMAT_UNCOMPRESSED_R8G8B8 = 4

PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 = 5

PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 = 6

PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = 7

PIXELFORMAT_UNCOMPRESSED_R32 = 8

PIXELFORMAT_UNCOMPRESSED_R32G32B32 = 9

PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 = 10

PIXELFORMAT_COMPRESSED_DXT1_RGB = 11

PIXELFORMAT_COMPRESSED_DXT1_RGBA = 12

PIXELFORMAT_COMPRESSED_DXT3_RGBA = 13

PIXELFORMAT_COMPRESSED_DXT5_RGBA = 14

PIXELFORMAT_COMPRESSED_ETC1_RGB = 15

PIXELFORMAT_COMPRESSED_ETC2_RGB = 16

PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA = 17

PIXELFORMAT_COMPRESSED_PVRT_RGB = 18

PIXELFORMAT_COMPRESSED_PVRT_RGBA = 19

PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA = 20

PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA = 21


## Globals - TextureFilters
TEXTURE_FILTER_POINT = 0

TEXTURE_FILTER_BILINEAR = 1

TEXTURE_FILTER_TRILINEAR = 2

TEXTURE_FILTER_ANISOTROPIC_4X = 3

TEXTURE_FILTER_ANISOTROPIC_8X = 4

TEXTURE_FILTER_ANISOTROPIC_16X = 5


## Globals - TextureWrap
TEXTURE_WRAP_REPEAT = 0

TEXTURE_WRAP_CLAMP = 1

TEXTURE_WRAP_MIRROR_REPEAT = 2

TEXTURE_WRAP_MIRROR_CLAMP = 3


## Globals - CubemapLayout
CUBEMAP_LAYOUT_AUTO_DETECT = 0

CUBEMAP_LAYOUT_LINE_VERTICAL = 1

CUBEMAP_LAYOUT_LINE_HORIZONTAL = 2

CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR = 3

CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE = 4

CUBEMAP_LAYOUT_PANORAMA = 5


## Globals - FontType
FONT_DEFAULT = 0

FONT_BITMAP = 1

FONT_SDF = 2


## Globals - BlendModes
BLEND_ALPHA = 0

BLEND_ADDITIVE = 1

BLEND_MULTIPLIED = 2

BLEND_ADD_COLORS = 3

BLEND_SUBTRACT_COLORS = 4

BLEND_ALPHA_PREMULTIPLY = 5

BLEND_CUSTOM = 6

BLEND_CUSTOM_SEPARATE = 7


## Globals - Gesture
GESTURE_NONE = 0

GESTURE_TAP = 1

GESTURE_DOUBLETAP = 2

GESTURE_HOLD = 4

GESTURE_DRAG = 8

GESTURE_SWIPE_RIGHT = 16

GESTURE_SWIPE_LEFT = 32

GESTURE_SWIPE_UP = 64

GESTURE_SWIPE_DOWN = 128

GESTURE_PINCH_IN = 256

GESTURE_PINCH_OUT = 512


## Globals - CameraMode
CAMERA_CUSTOM = 0

CAMERA_FREE = 1

CAMERA_ORBITAL = 2

CAMERA_FIRST_PERSON = 3

CAMERA_THIRD_PERSON = 4


## Globals - CameraProjections
CAMERA_PERSPECTIVE = 0

CAMERA_ORTHOGRAPHIC = 1


## Globals - N-patchLayout
NPATCH_NINE_PATCH = 0

NPATCH_THREE_PATCH_VERTICAL = 1

NPATCH_THREE_PATCH_HORIZONTAL = 2


## Globals - Colors
LIGHTGRAY = { 200, 200, 200, 255 }

GRAY = { 130, 130, 130, 255 }

DARKGRAY = { 80, 80, 80, 255 }

YELLOW = { 253, 249, 0, 255 }

GOLD = { 255, 203, 0, 255 }

ORANGE = { 255, 161, 0, 255 }

PINK = { 255, 109, 194, 255 }

RED = { 230, 41, 55, 255 }

MAROON = { 190, 33, 55, 255 }

GREEN = { 0, 228, 48, 255 }

LIME = { 0, 158, 47, 255 }

DARKGREEN = { 0, 117, 44, 255 }

SKYBLUE = { 102, 191, 255, 255 }

BLUE = { 0, 121, 241, 255 }

DARKBLUE = { 0, 82, 172, 255 }

PURPLE = { 200, 122, 255, 255 }

VIOLET = { 135, 60, 190, 255 }

DARKPURPLE = { 112, 31, 126, 255 }

BEIGE = { 211, 176, 131, 255 }

BROWN = { 127, 106, 79, 255 }

DARKBROWN = { 76, 63, 47, 255 }

WHITE = { 255, 255, 255, 255 }

BLACK = { 0, 0, 0, 255 }

BLANK = { 0, 0, 0, 0 }

MAGENTA = { 255, 0, 255, 255 }

RAYWHITE = { 245, 245, 245, 255 }


## Globals - Math
PI = 3.1415927410126

DEG2RAD = 0.017453292384744

RAD2DEG = 57.295776367188


## Globals - GuiControlState
STATE_NORMAL = 0

STATE_FOCUSED = 1

STATE_PRESSED = 2

STATE_DISABLED = 3


## Globals - GuiTextAlignment
TEXT_ALIGN_LEFT = 0

TEXT_ALIGN_CENTER = 1

TEXT_ALIGN_RIGHT = 2


## Globals - GuiControl
DEFAULT = 0

LABEL = 1

BUTTON = 2

TOGGLE = 3

SLIDER = 4

PROGRESSBAR = 5

CHECKBOX = 6

COMBOBOX = 7

DROPDOWNBOX = 8

TEXTBOX = 9

VALUEBOX = 10

SPINNER = 11

LISTVIEW = 12

COLORPICKER = 13

SCROLLBAR = 14

STATUSBAR = 15


## Globals - GuiControlProperty
BORDER_COLOR_NORMAL = 0

BASE_COLOR_NORMAL = 1

TEXT_COLOR_NORMAL = 2

BORDER_COLOR_FOCUSED = 3

BASE_COLOR_FOCUSED = 4

TEXT_COLOR_FOCUSED = 5

BORDER_COLOR_PRESSED = 6

BASE_COLOR_PRESSED = 7

TEXT_COLOR_PRESSED = 8

BORDER_COLOR_DISABLED = 9

BASE_COLOR_DISABLED = 10

TEXT_COLOR_DISABLED = 11

BORDER_WIDTH = 12

TEXT_PADDING = 13

TEXT_ALIGNMENT = 14

RESERVED = 15


## Globals - GuiDefaultProperty
TEXT_SIZE = 16

TEXT_SPACING = 17

LINE_COLOR = 18

BACKGROUND_COLOR = 19


## Globals - GuiToggleProperty
GROUP_PADDING = 16


## Globals - GuiSliderProperty
SLIDER_WIDTH = 16

SLIDER_PADDING = 17


## Globals - GuiProgressBarProperty
PROGRESS_PADDING = 16


## Globals - GuiScrollBarProperty
ARROWS_SIZE = 16

ARROWS_VISIBLE = 17

SCROLL_SLIDER_PADDING = 18

SCROLL_SLIDER_SIZE = 19

SCROLL_PADDING = 20

SCROLL_SPEED = 21


## Globals - GuiCheckBoxProperty
CHECK_PADDING = 16


## Globals - GuiComboBoxProperty
COMBO_BUTTON_WIDTH = 16

COMBO_BUTTON_SPACING = 17


## Globals - GuiDropdownBoxProperty
ARROW_PADDING = 16

DROPDOWN_ITEMS_SPACING = 17


## Globals - GuiTextBoxProperty
TEXT_INNER_PADDING = 16

TEXT_LINES_SPACING = 17


## Globals - GuiSpinnerProperty
SPIN_BUTTON_WIDTH = 16

SPIN_BUTTON_SPACING = 17


## Globals - GuiListViewProperty
LIST_ITEMS_HEIGHT = 16

LIST_ITEMS_SPACING = 17

SCROLLBAR_WIDTH = 18

SCROLLBAR_SIDE = 19


## Globals - GuiColorPickerProperty
COLOR_SELECTOR_SIZE = 16

HUEBAR_WIDTH = 17

HUEBAR_PADDING = 18

HUEBAR_SELECTOR_HEIGHT = 19

HUEBAR_SELECTOR_OVERFLOW = 20


## Globals - LightType
LIGHT_DIRECTIONAL = 0

LIGHT_POINT = 1


## Globals - RLGL
RL_DEFAULT_BATCH_BUFFER_ELEMENTS = 8192

RL_DEFAULT_BATCH_BUFFERS = 1

RL_DEFAULT_BATCH_DRAWCALLS = 256

RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS = 4


## Globals - RLGL
RL_MAX_MATRIX_STACK_SIZE = 32


## Globals - RLGL
RL_MAX_SHADER_LOCATIONS = 32


## Globals - RLGL
RL_CULL_DISTANCE_NEAR = 0.01

RL_CULL_DISTANCE_FAR = 1000.0


## Globals - RLGL
RL_TEXTURE_WRAP_S = 10242

RL_TEXTURE_WRAP_T = 10243

RL_TEXTURE_MAG_FILTER = 10240

RL_TEXTURE_MIN_FILTER = 10241

RL_TEXTURE_FILTER_NEAREST = 9728

RL_TEXTURE_FILTER_LINEAR = 9729

RL_TEXTURE_FILTER_MIP_NEAREST = 9984

RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR = 9986

RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST = 9985

RL_TEXTURE_FILTER_MIP_LINEAR = 9987

RL_TEXTURE_FILTER_ANISOTROPIC = 12288

RL_TEXTURE_MIPMAP_BIAS_RATIO = 16384

RL_TEXTURE_WRAP_REPEAT = 10497

RL_TEXTURE_WRAP_CLAMP = 33071

RL_TEXTURE_WRAP_MIRROR_REPEAT = 33648

RL_TEXTURE_WRAP_MIRROR_CLAMP = 34626


## Globals - RLGL
RL_MODELVIEW = 5888

RL_PROJECTION = 5889

RL_TEXTURE = 5890


## Globals - RLGL
RL_LINES = 1

RL_TRIANGLES = 4

RL_QUADS = 7


## Globals - RLGL
RL_UNSIGNED_BYTE = 5121

RL_FLOAT = 5126


## Globals - RLGL
RL_STREAM_DRAW = 35040

RL_STREAM_READ = 35041

RL_STREAM_COPY = 35042

RL_STATIC_DRAW = 35044

RL_STATIC_READ = 35045

RL_STATIC_COPY = 35046

RL_DYNAMIC_DRAW = 35048

RL_DYNAMIC_READ = 35049

RL_DYNAMIC_COPY = 35050


## Globals - RLGL
RL_FRAGMENT_SHADER = 35632

RL_VERTEX_SHADER = 35633

RL_COMPUTE_SHADER = 37305


## Globals - RLGL
RL_ZERO = 0

RL_ONE = 1

RL_SRC_COLOR = 768

RL_ONE_MINUS_SRC_COLOR = 769

RL_SRC_ALPHA = 770

RL_ONE_MINUS_SRC_ALPHA = 771

RL_DST_ALPHA = 772

RL_ONE_MINUS_DST_ALPHA = 773

RL_DST_COLOR = 774

RL_ONE_MINUS_DST_COLOR = 775

RL_SRC_ALPHA_SATURATE = 776

RL_CONSTANT_COLOR = 32769

RL_ONE_MINUS_CONSTANT_COLOR = 32770

RL_CONSTANT_ALPHA = 32771

RL_ONE_MINUS_CONSTANT_ALPHA = 32772


## Globals - RLGL
RL_FUNC_ADD = 32774

RL_MIN = 32775

RL_MAX = 32776

RL_FUNC_SUBTRACT = 32778

RL_FUNC_REVERSE_SUBTRACT = 32779

RL_BLEND_EQUATION = 32777

RL_BLEND_EQUATION_RGB = 32777

RL_BLEND_EQUATION_ALPHA = 34877

RL_BLEND_DST_RGB = 32968

RL_BLEND_SRC_RGB = 32969

RL_BLEND_DST_ALPHA = 32970

RL_BLEND_SRC_ALPHA = 32971

RL_BLEND_COLOR = 32773


## Globals - RLGL
RL_OPENGL_11 = 1

RL_OPENGL_21 = 2

RL_OPENGL_33 = 3

RL_OPENGL_43 = 4

RL_OPENGL_ES_20 = 5


## Globals - RLGL
RL_ATTACHMENT_COLOR_CHANNEL0 = 0

RL_ATTACHMENT_COLOR_CHANNEL1 = 1

RL_ATTACHMENT_COLOR_CHANNEL2 = 2

RL_ATTACHMENT_COLOR_CHANNEL3 = 3

RL_ATTACHMENT_COLOR_CHANNEL4 = 4

RL_ATTACHMENT_COLOR_CHANNEL5 = 5

RL_ATTACHMENT_COLOR_CHANNEL6 = 6

RL_ATTACHMENT_COLOR_CHANNEL7 = 7

RL_ATTACHMENT_DEPTH = 100

RL_ATTACHMENT_STENCIL = 200


## Globals - RLGL
RL_ATTACHMENT_CUBEMAP_POSITIVE_X = 0

RL_ATTACHMENT_CUBEMAP_NEGATIVE_X = 1

RL_ATTACHMENT_CUBEMAP_POSITIVE_Y = 2

RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y = 3

RL_ATTACHMENT_CUBEMAP_POSITIVE_Z = 4

RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z = 5

RL_ATTACHMENT_TEXTURE2D = 100

RL_ATTACHMENT_RENDERBUFFER = 200


## Globals - RLGL
RL_CULL_FACE_FRONT = 0

RL_CULL_FACE_BACK = 1


## Globals - OpenGL
GL_COLOR_BUFFER_BIT = 16384

GL_DEPTH_BUFFER_BIT = 256

GL_STENCIL_BUFFER_BIT = 1024

GL_NEAREST = 9728

GL_LINEAR = 9729


## Globals - GLFW
GLFW_RELEASE = 0

GLFW_PRESS = 1

GLFW_REPEAT = 2


## Globals - CBuffer
BUFFER_UNSIGNED_CHAR = 0

BUFFER_UNSIGNED_SHORT = 1

BUFFER_UNSIGNED_INT = 2

BUFFER_FLOAT = 3


## Globals - Window
EVENT_WINDOW_SIZE = 0

EVENT_WINDOW_MAXIMIZE = 1

EVENT_WINDOW_ICONYFY = 2

EVENT_WINDOW_FOCUS = 3

EVENT_WINDOW_DROP = 4


## Globals - Input
EVENT_KEY = 5

EVENT_CHAR = 6

EVENT_MOUSE_BUTTON = 7

EVENT_MOUSE_CURSOR_POS = 8

EVENT_MOUSE_SCROLL = 9

EVENT_CURSOR_ENTER = 10


## Types

Raylib structs in Lua

---

> Vector2 = { 1.0, 1.0 } or { x = 1.0, y = 1.0 }

Vector2 type

---

> Vector3 = { 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0 }

Vector3 type

---

> Vector4 = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }

Vector4 type

---

> Quaternion = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }

Quaternion type

---

> Matrix = { { 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } }

OpenGL style 4x4. Identity matrix example

---

> Color = { 255, 255, 255, 255 } or { r = 255, g = 255, b = 255, a = 255 }

{ r, g, b ,a }. Color type, RGBA (32bit)

---

> Rectangle = { 0.0, 0.0, 1.0, 1.0 } or { x = 0.0, y = 0.0, width = 1.0, height = 1.0 }

{ x, y, width ,height }. Rectangle type

---

> Image = ImageId

int id. Image type (multiple pixel formats supported). NOTE: Data stored in CPU memory (RAM)

---

> Texture = TextureId or { id, width, height, mipmaps, format }

int id. Texture type (multiple internal formats supported). NOTE: Data stored in GPU memory (VRAM)

---

> RenderTexture = RenderTextureId or { id, texture, depth }

int id. RenderTexture type, for texture rendering

---

> Font = FontId

int id. Font type, includes texture and chars data

---

> Camera2D = CameraId or { offset, target, rotation, zoom }

int id. Defines 2D camera position/orientation

---

> Camera = CameraId or { position, target, up, fovy, projection }

int id. Defines 3D camera3D position/orientation

---

> Mesh = MeshId

int id. Vertex data defining a mesh

```
mesh{} = {
  vertices = { Vector3, ... },
  texcoords = { Vector2, ... },
  texcoords2 = { Vector2, ... },
  normals = { Vector3, ... },
  tangents = { Vector4, ... },
  colors = { Color, ... },
  indices = { int, ... },
}
```

---

> Material = MaterialId

int id. Material type

```
material{} = {
  shader = Shader,
  maps = {
    {
      MATERIAL_MAP_ALBEDO,
      {
        texture = Texture,
        color = WHITE,
        value = 1.0,
      },
    },
    ...
  },
  params = { 1.0, 2.0, 3.0, 4.0 },
}
```

---

> Model = ModelId

int id. Basic 3d Model type

---

> Ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } or { position = { 0.0, 0.0, 0.0 }, direction = { 1.0, 0.0, 0.0 } }

{ position, direction }. Ray type (useful for raycast)

---

> RayCollision = { hit = true, distance = 1.0, point = { 0.0, 0.0, 0.0 }, normal = { 0.0, 0.0, 1.0 } }

Raycast hit information. NOTE: Data in named keys

---

> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } } or { min = { 0.0, 0.0, 0.0 }, max = { 1.0, 1.0, 1.0 } }

{ min, max }. Accepts Vector3. Bounding box type for 3d mesh

---

> Sound = SoundId

int id. Basic Sound source and buffer

---

> NPatchInfo = { { 0, 0, 24, 24 }, 8, 8, 8, 8, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }

{ Rectangle source, int left, int top, int right, int bottom, int layout }.
{ Texture source rectangle, Left border offset, Top border offset, Right border offset, Bottom border offset, Layout of the n-patch: 3x3, 1x3 or 3x1 }

---

> ModelAnimations = ModelAnimationsId

int id. ModelAnimations

---

> Buffer = Buffer userdata

Userdata.

---

## Events

Content of event table received by RL.event.

### Window events

---
> { type: RL.EVENT_WINDOW_SIZE, int width, int height }

 WindowSize Callback, runs when window is resized.

---

> { type RL.EVENT_WINDOW_MAXIMIZE, int maximized }

 Window Maximize Callback, runs when window is maximized.

---

> { type RL.EVENT_WINDOW_ICONYFY, int iconified }

 WindowIconify Callback, runs when window is minimized/restored.

---

> { type RL.EVENT_WINDOW_FOCUS, int focused }

 WindowFocus Callback, runs when window get/lose focus.

---

> { type RL.EVENT_WINDOW_DROP, int count, string{} paths }

 Window Drop Callback, runs when drop files into window.

---

### Input events

---
> { type: RL.EVENT_KEY, int key, int scancode, int action, int mods }

 Keyboard Callback, runs on key pressed.

---

> { type RL.EVENT_CHAR, int key }

 Char Key Callback, runs on key pressed (get char value).

---

> { type RL.EVENT_MOUSE_BUTTON, int button, int action, int mods }

 Mouse Button Callback, runs on mouse button pressed.

---

> { type RL.EVENT_MOUSE_CURSOR_POS, number x, number y }

 Cursor Position Callback, runs on mouse move.

---

> { type RL.EVENT_MOUSE_SCROLL, number xoffset, number yoffset }

 Srolling Callback, runs on mouse wheel.

---

> { type RL.EVENT_CURSOR_ENTER, int enter }

 Cursor Enter Callback, cursor enters client area.

---

## Core - Window

---

> state = RL.IsWindowReady()

Check if window has been initialized successfully

- Success return bool

---

> state = RL.IsWindowFullscreen()

Check if window is currently fullscreen

- Success return bool

---

> state = RL.IsWindowHidden()

Check if window is currently hidden (only PLATFORM_DESKTOP)

- Success return bool

---

> state = RL.IsWindowMinimized()

Check if window is currently minimized (only PLATFORM_DESKTOP)

- Success return bool

---

> state = RL.IsWindowMaximized()

Check if window is currently maximized (only PLATFORM_DESKTOP)

- Success return bool

---

> state = RL.IsWindowFocused()

Check if window is currently focused (only PLATFORM_DESKTOP)

- Success return bool

---

> RL.SetWindowMonitor( int monitor )

Set monitor for the current window (fullscreen mode)

---

> RL.SetWindowPosition( Vector2 pos )

Set window position on screen

---

> RL.SetWindowSize( Vector2 size )

Set window dimensions

---

> RL.SetWindowMinSize( Vector2 size )

Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)

---

> position = RL.GetMonitorPosition( int monitor )

Get specified monitor position

- Success return Vector2

---

> size = RL.GetMonitorSize( int monitor )

Get specified monitor size

- Success return Vector2

---

> position = RL.GetWindowPosition()

Get window position on monitor

- Success return Vector2

---

> size = RL.GetScreenSize()

Get screen size

- Success return Vector2

---

> RL.SetWindowState( int flag )

Set window configuration state using flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

---

> state = RL.IsWindowState( int flag )

Check if one specific window flag is enabled (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool

---

> resized = RL.ClearWindowState( int flag )

Clear window configuration state flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool

---

> resized = RL.IsWindowResized()

Check if window has been resized from last frame

- Success return bool

---

> RL.SetWindowIcon( Image image )

Set icon for window (Only PLATFORM_DESKTOP)

---

> RL.SetWindowTitle( string title )

Set title for window (Only PLATFORM_DESKTOP)

---

> count = RL.GetMonitorCount()

Get number of connected monitors

- Success return int

---

> monitor = RL.GetCurrentMonitor()

Get current connected monitor

- Success return int

---

> size = RL.GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Success return Vector2

---

> refreshRate = RL.GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Success return int

---

> dpi = RL.GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2

---

> name = RL.GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the monitor

- Success return string

---

> RL.CloseWindow()

Close window and unload OpenGL context and free all resources

---

> RL.SetClipboardText( string text )

Set clipboard text content

---

> text = RL.GetClipboardText()

Get clipboard text content

- Success return string

---

## Core - Timing

---

> RL.SetTargetFPS( int fps )

Set target FPS (maximum)

---

> FPS = RL.GetFPS()

Get current FPS

- Success return int

---

> delta = RL.GetFrameTime()

Get time in seconds for last frame drawn (Delta time)

- Success return float

---

> time = RL.GetTime()

Get elapsed time in seconds since InitWindow()

- Success return float

---

## Core - Misc

---

> RL.TakeScreenshot( string fileName )

Takes a screenshot of current screen (filename extension defines format)

---

> RL.SetConfigFlags( int flags )

Setup init configuration flags (view FLAGS)

---

> RL.TraceLog( int logLevel, string text )

Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)

---

> RL.SetTraceLogLevel( int logLevel )

Set the current threshold (minimum) log level

---

> RL.SetLogLevelInvalid( int logLevel )

Set the log level for bad function calls and invalid data formats.

---

> logLevel = RL.GetLogLevelInvalid()

Get the log level for bad function calls and invalid data formats.

- Success return int

---

> RL.OpenURL( string url )

Open URL with default system browser (If available)

---

> buffer = RL.LoadBuffer( data{} buffer, int type )

Creates buffer as userdata. Type should be one of the Buffer types

- Success return Buffer

---

## Core - Cursor

---

> RL.ShowCursor()

Shows cursor

---

> RL.HideCursor()

Hides cursor

---

> hidden = RL.IsCursorHidden()

Check if cursor is not visible

- Success return bool

---

> RL.EnableCursor()

Enables cursor (unlock cursor)

---

> RL.DisableCursor()

Disables cursor (lock cursor)

---

> onSreen = RL.IsCursorOnScreen()

Check if cursor is on the screen

- Success return bool

---

## Core - Drawing

---

> RL.ClearBackground( Color color )

Set background color (framebuffer clear color)

---

> RL.BeginDrawing()

Setup canvas (framebuffer) to start drawing

---

> RL.EndDrawing()

End canvas drawing and swap buffers (double buffering)

---

> RL.BeginBlendMode( int mode )

Begin blending mode (BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED...)

---

> RL.EndBlendMode()

End blending mode (reset to default: BLEND_ALPHA)

---

> RL.BeginScissorMode( Rectangle rectange )

Begin scissor mode (define screen area for following drawing)

---

> RL.EndScissorMode()

End scissor mode

---

## Core - Shader

---

> shader = RL.LoadShader( string vsFileName, string fsFileName )

Load shader from files and bind default locations.
NOTE: Set nil if no shader

- Failure return nil
- Success return Shader

---

> shader = RL.LoadShaderFromMemory( string vsCode, string fsCode )

Load shader from code strings and bind default locations
NOTE: Set nil if no shader

- Failure return nil
- Success return Shader

---

> RL.BeginShaderMode( Shader shader )

Begin custom shader drawing

---

> RL.EndShaderMode()

End custom shader drawing (use default shader)

---

> location = RL.GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Success return int

---

> location = RL.GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Success return int

---

> RL.SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )

Set shader location index

---

> location = RL.GetShaderLocationIndex( Shader shader, int shaderLocationIndex )

Get shader location index

- Success return int

---

> RL.SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value (matrix 4x4)

---

> RL.SetShaderValueTexture( Shader shader, int locIndex, Texture texture )

Set shader uniform value for texture (sampler2d)

---

> RL.SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table

---

> RL.SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table

---

## Core - Input-related Keyboard

---

> pressed = RL.IsKeyPressed( int key )

Detect if a key has been pressed once

- Success return bool

---

> pressed = RL.IsKeyDown( int key )

Detect if a key is being pressed

- Success return bool

---

> released = RL.IsKeyReleased( int key )

Detect if a key has been released once

- Success return bool

---

> released = RL.IsKeyUp( int key )

Check if a key is NOT being pressed

- Success return bool

---

> keycode = RL.GetKeyPressed()

Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty

- Success return int

---

> unicode = RL.GetCharPressed()

Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

- Success return int

---

> RL.SetExitKey( int key )

Set a custom key to exit program (default is ESC)

---

> keyName = RL.GetKeyName( int key, int scancode )

This function returns the name of the specified printable key, encoded as UTF-8.
This is typically the character that key would produce without any modifier keys,
intended for displaying key bindings to the user. For dead keys, it is typically
the diacritic it would add to a character.

Do not use this function for text input. You will break text input for many
languages even if it happens to work for yours.

If the key is KEY_UNKNOWN, the scancode is used to identify the key,
otherwise the scancode is ignored. If you specify a non-printable key,
or KEY_UNKNOWN and a scancode that maps to a non-printable key,
this function returns nil but does not emit an error.

- Success return string or nil

---

> scancode = RL.GetKeyScancode( int key )

This function returns the platform-specific scancode of the specified key.
If the key is KEY_UNKNOWN or does not exist on the keyboard this method will return -1.

- Success return int

---

## Core - Input-related Gamepad

---

> available = RL.IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Success return bool

---

> pressed = RL.IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Success return bool

---

> pressed = RL.IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Success return bool

---

> released = RL.IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Success return bool

---

> count = RL.GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Success return int

---

> value = RL.GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Success return float

---

> name = RL.GetGamepadName( int gamepad )

Return gamepad internal name id

- Success return string

---

## Core - Input-related Mouse

---

> pressed = RL.IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Success return bool

---

> pressed = RL.IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Success return bool

---

> released = RL.IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Success return bool

---

> released = RL.IsMouseButtonUp( int button )

Check if a mouse button is NOT being pressed

- Success return bool

---

> position = RL.GetMousePosition()

Returns mouse position

- Success return Vector2

---

> position = RL.GetMouseDelta()

Get mouse delta between frames

- Success return Vector2

---

> RL.SetMousePosition( Vector2 position )

Set mouse position XY

---

> RL.SetMouseOffset( Vector2 offset )

Set mouse offset

---

> RL.SetMouseScale( Vector2 scale )

Set mouse scaling

---

> movement = RL.GetMouseWheelMove()

Returns mouse wheel movement Y

- Success return float

---

> RL.SetMouseCursor( int cursor )

Set mouse cursor

---

## Core - Input-related Touch

---

> position = RL.GetTouchPosition( int index )

Get touch position XY for a touch point index (relative to screen size)

- Success return Vector2

---

> id = RL.GetTouchPointId( int index )

Get touch point identifier for given index

- Success return int

---

> count = RL.GetTouchPointCount()

Get touch point identifier for given index

- Success return int

---

## Core - Input-related Gestures

---

> RL.SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags

---

> detected = RL.IsGestureDetected( int gesture )

Check if a gesture have been detected

- Success return bool

---

> gesture = RL.GetGestureDetected()

Get latest detected gesture

- Success return int

---

> time = RL.GetGestureHoldDuration()

Get gesture hold time in milliseconds

- Success return float

---

> vector = RL.GetGestureDragVector()

Get gesture drag vector

- Success return Vector2

---

> angle = RL.GetGestureDragAngle()

Get gesture drag angle

- Success return float

---

> vector = RL.GetGesturePinchVector()

Get gesture pinch delta

- Success return Vector2

---

> angle = RL.GetGesturePinchAngle()

Get gesture pinch angle

- Success return float

---

## Core - File

---

> path = RL.GetBasePath()

Return game directory (where main.lua is located)

- Success return string

---

> fileExists = RL.FileExists( string fileName )

Check if file exists

- Success return bool

---

> dirExists = RL.DirectoryExists( string dirPath )

Check if a directory path exists

- Success return bool

---

> hasFileExtension = RL.IsFileExtension( string fileName, string ext )

Check file extension (Including point: .png, .wav)

- Success return bool

---

> length = RL.GetFileLength( string fileName )

Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)

- Success return int

---

> extension = RL.GetFileExtension( string fileName )

Get pointer to extension for a filename string (Includes dot: '.png')

- Success return string

---

> fileName = RL.GetFileName( string filePath )

Get pointer to filename for a path string

- Success return string

---

> fileName = RL.GetFileNameWithoutExt( string filePath )

Get filename string without extension (Uses static string)

- Success return string

---

> filePath = RL.GetDirectoryPath( string filePath )

Get full path for a given fileName with path (Uses static string)

- Success return string

---

> directory = RL.GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path (Uses static string)

- Success return string

---

> directory = RL.GetWorkingDirectory()

Get current working directory (Uses static string)

- Success return string

---

> fileNames = RL.LoadDirectoryFiles( string dirPath )

Load directory filepaths

- Success return string{}

---

> fileNames = RL.LoadDirectoryFilesEx( string basePath, string filter, bool scanSubdirs )

Load directory filepaths with extension filtering and recursive directory scan

- Success return string{}

---

> success = RL.ChangeDirectory( string directory )

Change working directory, return true on success

- Success return bool

---

> isFile = RL.IsPathFile( string path )

Check if a given path is a file or a directory

- Success return bool

---

> iSFileDropped = RL.IsFileDropped()

Check if a file has been dropped into window

- Success return bool

---

> files = RL.LoadDroppedFiles()

Load dropped filepaths

- Success return string{}

---

> time = RL.GetFileModTime( string fileName )

Get file modification time (Last write time)

- Success return int

---

## Core - Camera2D

---

> camera2D = RL.CreateCamera2D()

Return camera2D set to default configuration

- Success return Camera2D

---

> RL.BeginMode2D( camera2D camera )

Begin 2D mode with custom camera (2D)

---

> RL.EndMode2D()

Ends 2D mode with custom camera

---

> RL.SetCamera2DTarget( camera2D camera, Vector2 target )

Set camera target (rotation and zoom origin)

---

> RL.SetCamera2DOffset( camera2D camera, Vector2 offset )

Set camera offset (displacement from target)

---

> RL.SetCamera2DRotation( camera2D camera, float rotation )

Set camera rotation in degrees

---

> RL.SetCamera2DZoom( camera2D camera, float zoom )

Set camera zoom (scaling), should be 1.0f by default

---

> target = RL.GetCamera2DTarget( camera2D camera )

Get camera2D target

- Success return Vector2

---

> offset = RL.GetCamera2DOffset( camera2D camera )

Get camera2D offset

- Success return Vector2

---

> rotation = RL.GetCamera2DRotation( camera2D camera )

Get camera2D rotation

- Success return float

---

> zoom = RL.GetCamera2DZoom( camera2D camera )

Get camera2D zoom

- Success return float

---

## Core - Camera3D

---

> camera = RL.CreateCamera3D()

Return camera3D id set to default configuration

- Success return int

---

> RL.BeginMode3D( camera3D camera )

Begin 3D mode with custom camera (3D)

---

> RL.EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode

---

> RL.SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position (Remember to call "RL.UpdateCamera3D()" to apply changes)

---

> RL.SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at

---

> RL.SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector (Rotation over it's axis)

---

> RL.SetCamera3DFovy( camera3D camera, float fovy )

Set camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic

---

> RL.SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC)

---

> position = RL.GetCamera3DPosition( camera3D camera )

Get camera position

- Success return Vector3

---

> target = RL.GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Success return Vector3

---

> up = RL.GetCamera3DUp( camera3D camera )

Get camera up vector (Rotation over it's axis)

- Success return Vector3

---

> fovy = RL.GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic

- Success return float

---

> projection = RL.GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Success return int

---

> forward = RL.GetCamera3DForward( camera3D camera )

Returns the cameras forward vector (normalized)

- Success return Vector3

---

> up = RL.GetCamera3DUpNormalized( camera3D camera )

Returns the cameras up vector (normalized)
Note: The up vector might not be perpendicular to the forward vector

- Success return Vector3

---

> right = RL.GetCamera3DRight( camera3D camera )

Returns the cameras right vector (normalized)

- Success return Vector3

---

> RL.Camera3DMoveForward( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera in it's forward direction

---

> RL.Camera3DMoveUp( camera3D camera, float distance )

Moves the camera in it's up direction

---

> RL.Camera3DMoveRight( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera target in it's current right direction

---

> RL.Camera3DMoveToTarget( camera3D camera, float delta )

Moves the camera position closer/farther to/from the camera target

---

> RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )

Rotates the camera around it's up vector
Yaw is "looking left and right"
If rotateAroundTarget is false, the camera rotates around it's position
Note: angle must be provided in radians

---

> RL.Camera3DPitch( camera3D camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp )

Rotates the camera around it's right vector, pitch is "looking up and down"
 - lockView prevents camera overrotation (aka "somersaults")
 - rotateAroundTarget defines if rotation is around target or around it's position
 - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
NOTE: angle must be provided in radians

---

> RL.Camera3DRoll( camera3D camera, float angle )

Rotates the camera around it's forward vector
Roll is "turning your head sideways to the left or right"
Note: angle must be provided in radians

---

> view = RL.GetCamera3DViewMatrix( camera3D camera )

Returns the camera view matrix

- Success return Matrix

---

> projection = RL.GetCamera3DProjectionMatrix( camera3D camera, float aspect )

Returns the camera projection matrix

- Success return Matrix

---

> RL.UpdateCamera3D( camera3D camera, int mode )

Update camera position for selected mode

---

> RL.UpdateCamera3DPro( camera3D camera, Vector3 movement, Vector3 rotation, float zoom )

Update camera movement, movement/rotation values should be provided by user

---

## Core - Screen-space

---

> ray = RL.GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Success return Ray

---

> matrix = RL.GetCameraMatrix( Camera3D camera )

Get camera transform matrix (view matrix)

- Success return Matrix

---

> matrix = RL.GetCameraMatrix2D( Camera2D camera )

Get camera 2d transform matrix

- Success return Matrix

---

> position = RL.GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Success return Vector2

---

> position = RL.GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )

Get size position for a 3d world space position

- Success return Vector2

---

> position = RL.GetWorldToScreen2D( Vector2 position, Camera2D camera )

Get the screen space position for a 2d camera world space position

- Success return Vector2

---

> position = RL.GetScreenToWorld2D( Vector2 position, Camera2D camera )

Get the world space position for a 2d camera screen space position

- Success return Vector2

---

## Shapes - Drawing

---

> RL.SetShapesTexture( Texture texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

---

> success = RL.DrawPixel( Vector2 pos, Color color )

Draw a pixel

- Failure return false
- Success return true

---

> success = RL.DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness

- Failure return false
- Success return true

---

> success = RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out

- Failure return false
- Success return true

---

> success = RL.DrawLineBezierQuad( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true

---

> success = RL.DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true

---

> success = RL.DrawLineStrip( Vector2{} points, Color color )

Draw lines sequence

- Failure return false
- Success return true

---

> success = RL.DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle

- Failure return false
- Success return true

---

> success = RL.DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle

- Failure return false
- Success return true

---

> success = RL.DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline

- Failure return false
- Success return true

---

> success = RL.DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle

- Failure return false
- Success return true

---

> success = RL.DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline

- Failure return false
- Success return true

---

> success = RL.DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse

- Failure return false
- Success return true

---

> success = RL.DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline

- Failure return false
- Success return true

---

> success = RL.DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring

- Failure return false
- Success return true

---

> success = RL.DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline

- Failure return false
- Success return true

---

> success = RL.DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle

- Failure return false
- Success return true

---

> success = RL.DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters

- Failure return false
- Success return true

---

> success = RL.DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle

- Failure return false
- Success return true

---

> success = RL.DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle

- Failure return false
- Success return true

---

> success = RL.DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors

- Failure return false
- Success return true

---

> success = RL.DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline

- Failure return false
- Success return true

---

> success = RL.DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters

- Failure return false
- Success return true

---

> success = RL.DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges

- Failure return false
- Success return true

---

> success = RL.DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline

- Failure return false
- Success return true

---

> success = RL.DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL.DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL.DrawTriangleFan( Vector2{} points, Color color )

Draw a triangle fan defined by points ( first vertex is the center )

- Failure return false
- Success return true

---

> success = RL.DrawTriangleStrip( Vector2{} points, Color color )

Draw a triangle strip defined by points

- Failure return false
- Success return true

---

> success = RL.DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon ( Vector version )

- Failure return false
- Success return true

---

> success = RL.DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides

- Failure return false
- Success return true

---

> success = RL.DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters

- Failure return false
- Success return true

---

## Shapes - Collision

---

> collision = RL.CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionPointPoly( Vector2 point, Vector2{} points )

Check if point is within a polygon described by array of vertices

- Failure return nil
- Success return bool

---

> collision, position = RL.CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Failure return nil
- Success return bool, Vector2

---

> collision = RL.CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Failure return nil
- Success return bool

---

> rectangle = RL.GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Failure return nil
- Success return Rectangle

---

## Textures - Image Loading

---

> image = RL.LoadImage( string fileName )

Load image from file into CPU memory (RAM)

- Success return Image

---

> image = RL.LoadImageFromTexture( Texture2D texture )

Load image from GPU texture data

- Success return Image

---

> image = RL.LoadImageFromScreen()

Load image from screen buffer and (screenshot)

- Success return Image

---

> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Success return bool

---

> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Success return bool

---

## Textures - Image Generation

---

> image = RL.GenImageColor( Vector2 size, Color color )

Generate image: plain color

- Success return Image

---

> image = RL.GenImageGradientV( Vector2 size, Color top, Color bottom )

Generate image: vertical gradient

- Success return Image

---

> image = RL.GenImageGradientH( Vector2 size, Color left, Color right )

Generate image: horizontal gradient

- Success return Image

---

> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Success return Image

---

> image = RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Success return Image

---

> image = RL.GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Success return Image

---

> image = RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )

Generate image: perlin noise

- Success return Image

---

> image = RL.GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Success return Image

---

> image = RL.GenImageText( Vector2 size, string text )

Generate image: grayscale image from text data

- Success return Image

---

## Textures - Image Manipulation Functions

---

> image = RL.ImageCopy( Image image )

Create an image duplicate (useful for transformations)

- Success return Image

---

> image = RL.ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Success return Image

---

> image = RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text (custom sprite font)

- Failure return -1
- Success return int

---

> RL.ImageFormat( Image image, int newFormat )

Convert image data to desired format

---

> RL.ImageToPOT( Image image, Color fill )

Convert image to POT (power-of-two)

---

> RL.ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle

---

> RL.ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value

---

> RL.ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color

---

> RL.ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image

---

> RL.ImageAlphaPremultiply( Image image )

Premultiply alpha channel

---

> RL.ImageBlurGaussian( Image image, int blurSize )

Apply Gaussian blur using a box blur approximation

---

> RL.ImageResize( Image image, Vector2 size )

Resize image (Bicubic scaling algorithm)

---

> RL.ImageResizeNN( Image image, Vector2 size )

Resize image (Nearest-Neighbor scaling algorithm)

---

> RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color

---

> RL.ImageMipmaps( Image image )

Generate all mipmap levels for a provided image

---

> RL.ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower (Floyd-Steinberg dithering)

---

> RL.ImageFlipVertical( Image image )

Flip image vertically

---

> RL.ImageFlipHorizontal( Image image )

Flip image horizontally

---

> RL.ImageRotateCW( Image image )

Rotate image clockwise 90deg

---

> RL.ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg

---

> RL.ImageColorTint( Image image, Color color )

Modify image color: tint

---

> RL.ImageColorInvert( Image image )

Modify image color: invert

---

> RL.ImageColorGrayscale( Image image )

Modify image color: grayscale

---

> RL.ImageColorContrast( Image image, float contrast )

Modify image color: contrast (-100 to 100)

---

> RL.ImageColorBrightness( Image image, int brightness )

Modify image color: brightness (-255 to 255)

---

> RL.ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color

---

> colors = RL.LoadImageColors( Image image )

Load color data from image as a Color array (RGBA - 32bit)

- Success return Color{}

---

> colors = RL.LoadImagePalette( Image image, int maxPaletteSize )

Load colors palette from image as a Color array (RGBA - 32bit)

- Success return Color{}

---

> rectangle = RL.GetImageAlphaBorder( Image image, float threshold )

Get image alpha border rectangle

- Success return Rectangle

---

> color = RL.GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at (x, y) position

- Success return Color

---

## Textures - Image Drawing

---

> RL.ImageClearBackground( Image dst, Color color )

Clear image background with given color

---

> RL.ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image

---

> RL.ImageDrawLine( Image dst, Vector2 a, Vector2 b, Color color )

Draw line within an image

---

> RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image

---

> RL.ImageDrawCircleLines( Image dst, Vector2 center, int radius, Color color )

Draw circle outline within an image

---

> RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image

---

> RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image

---

> RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image (Tint applied to source)

---

> success = RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text ( Custom sprite font ) within an image ( Destination )

- Failure return false
- Success return true

---

## Textures - Image Configuration

---

> size = RL.GetImageSize( Image image )

Get image size

- Success return Vector2

---

> mipmaps = RL.GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Success return int

---

> format = RL.GetImageFormat( Image image )

Get image data format (PixelFormat type)

- Success return int

---

## Textures - Texture Loading

---

> texture = RL.LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return nil
- Success return Texture

---

> texture = RL.LoadTextureFromImage( Image image )

Load texture from image data

- Success return Texture

---

> texture = RL.LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Success return Texture

---

> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering (framebuffer)

- Success return RenderTexture

---

> isReady = RL.IsTextureReady( Texture texture )

Check if a texture is ready

- Success return bool

---

> RL.UpdateTexture( Texture texture, int{} pixels )

Update GPU texture with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

---

> RL.UpdateTextureRec( Texture texture, Rectangle rec, int{} pixels )

Update GPU texture rectangle with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

---

## Textures - Texture Drawing

---

> RL.DrawTexture( Texture texture, Vector2 position, Color tint )

Draw a Texture2D

---

> RL.DrawTextureRec( Texture texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle

---

> RL.DrawTexturePro( Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters

---

> RL.DrawTextureNPatch( Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture (or part of it) that stretches or shrinks nicely

---

> RL.BeginTextureMode( RenderTexture target )

Begin drawing to render texture

---

> RL.EndTextureMode()

Ends drawing to render texture

---

## Textures - Texture Configuration

---

> RL.GenTextureMipmaps( Texture texture )

Generate GPU mipmaps for a texture

---

> RL.SetTextureFilter( Texture texture, int filter )

Set texture scaling filter mode (TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR...)

---

> RL.SetTextureWrap( Texture texture, int wrap )

Set texture wrapping mode (TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP...)

---

> id = RL.GetTextureId( Texture texture )

Get OpenGL texture id

- Success return int

---

> size = RL.GetTextureSize( Texture texture )

Get texture size

- Success return Vector2

---

> mipmaps = RL.GetTextureMipmaps( Texture texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Success return int

---

> format = RL.GetTextureFormat( Texture texture )

Get texture data format (PixelFormat type)

- Success return int

---

## Textures - RenderTexture Configuration

---

> id = RL.GetRenderTextureId( RenderTexture renderTexture )

Get OpenGL framebuffer object id

- Success return int

---

> texture = RL.GetRenderTextureTexture( RenderTexture renderTexture )

Get color buffer attachment texture

- Success return Texture

---

> texture = RL.GetRenderTextureDepthTexture( RenderTexture renderTexture )

Get depth buffer attachment texture

- Success return Texture

---

## Textures - Color/pixel

---

> color = RL.Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color

---

> value = RL.ColorToInt( Color color )

Returns hexadecimal value for a Color

- Success return int

---

> color = RL.ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Success return Vector4

---

> color = RL.ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Success return Color

---

> HSV = RL.ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Success return Vector3

---

> color = RL.ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Success return Color

---

> color = RL.ColorTint( Color color, Color tint )

Get color multiplied with another color

- Success return Color

---

> color = RL.ColorBrightness( Color color, float factor )

Get color with brightness correction, brightness factor goes from -1.0f to 1.0f

- Success return Color

---

> color = RL.ColorContrast( Color color, float contrast )

Get color with contrast correction, contrast values between -1.0f and 1.0f

- Success return Color

---

> color = RL.ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Success return Color

---

> color = RL.ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Success return Color

---

> color = RL.GetColor( int hexValue )

Get Color structure from hexadecimal value

- Success return Color

---

> color = RL.GetPixelColor( Texture texture, Vector2 position )

Get pixel color from source texture

- Success return Color

---

> size = RL.GetPixelDataSize( int width, int height, int format )

Get pixel data size in bytes for certain format

- Success return int

---

## Text - Loading

---

> RL.GetFontDefault()

Get the default Font

---

> font = RL.LoadFont( string fileName )

Load font from file into GPU memory (VRAM)

- Failure return nil
- Success return Font

---

> font = RL.LoadFontEx( string fileName, int fontSize, int fontChars{} )

Load font from file with extended parameters. Loading the default character set

- Failure return nil
- Success return Font

---

> font = RL.LoadFontFromImage( Image image, Color key, int firstChar )

Load font from Image ( XNA style )

- Success return Font

---

## Text - Draw

---

> RL.DrawFPS( Vector2 pos )

Draw current FPS

---

> RL.DrawText( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters

---

> RL.DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters (rotation)

---

## Text - Misc

---

> size = RL.MeasureText( Font font, string text, float fontSize, float spacing )

Measure string size for Font

- Success return Vector2

---

> baseSize = RL.GetFontBaseSize( Font font )

Get font base size (default chars height)

- Success return int

---

> glyphCount = RL.GetFontGlyphCount( Font font )

Get font number of glyph characters

- Success return int

---

> glyphPadding = RL.GetFontGlyphPadding( Font font )

Get font padding around the glyph characters

- Success return int

---

> texture = RL.GetFontTexture( Font font )

Get font texture atlas containing the glyphs.

- Success return Texture

---

## Models - Basic

---

> success = RL.DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )

Draw a line in 3D world space

- Failure return false
- Success return true

---

> success = RL.DrawPoint3D( Vector3 position, Color color )

Draw a point in 3D space, actually a small line

- Failure return false
- Success return true

---

> success = RL.DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )

Draw a circle in 3D world space

- Failure return false
- Success return true

---

> success = RL.DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL.DrawCube( Vector3 position, Vector3 size, Color color )

Draw cube

- Failure return false
- Success return true

---

> success = RL.DrawCubeWires( Vector3 position, Vector3 size, Color color )

Draw cube wires

- Failure return false
- Success return true

---

> success = RL.DrawSphere( Vector3 centerPos, float radius, Color color )

Draw sphere

- Failure return false
- Success return true

---

> success = RL.DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere with extended parameters

- Failure return false
- Success return true

---

> success = RL.DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere wires

- Failure return false
- Success return true

---

> success = RL.DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone

- Failure return false
- Success return true

---

> success = RL.DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder with base at startPos and top at endPos

- Failure return false
- Success return true

---

> success = RL.DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone wires

- Failure return false
- Success return true

---

> success = RL.DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder wires with base at startPos and top at endPos

- Failure return false
- Success return true

---

> success = RL.DrawCapsule( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw a capsule with the center of its sphere caps at startPos and endPos

- Failure return false
- Success return true

---

> success = RL.DrawCapsuleWires( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw capsule wireframe with the center of its sphere caps at startPos and endPos

- Failure return false
- Success return true

---

> success = RL.DrawPlane( Vector3 centerPos, Vector2 size, Color color )

Draw a plane XZ

- Failure return false
- Success return true

---

> RL.DrawQuad3DTexture( Texture texture, Vector3{} vertices, Vector2{} texCoords, Color{} colors )

Draw 3D textured quad. ( Texture coordinates opengl style 0.0 - 1.0 ).

---

> success = RL.DrawRay( Ray ray, Color color )

Draw a ray line

- Failure return false
- Success return true

---

> success = RL.DrawGrid( int slices, float spacing )

Draw a grid ( Centered at ( 0, 0, 0 ) )

- Failure return false
- Success return true

---

## Models - Mesh

---

> mesh = RL.GenMeshPoly( int sides, float radius )

Generate polygonal mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshPlane( float width, float length, int resX, int resZ )

Generate plane mesh ( With subdivisions )

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshCube( Vector3 size )

Generate cuboid mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshSphere( float radius, int rings, int slices )

Generate sphere mesh ( Standard sphere )

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshCylinder( float radius, float height, int slices )

Generate cylinder mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshCone( float radius, float height, int slices )

Generate cone/pyramid mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshTorus( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshKnot( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshHeightmap( Image heightmap, Vector3 size )

Generate heightmap mesh from image data

- Failure return -1
- Success return int

---

> mesh = RL.GenMeshCustom( Mesh{} mesh, bool dynamic )

Generate custom mesh from vertex attribute data and uploads it into a VAO ( if supported ) and VBO

- Failure return -1
- Success return int

---

> success = RL.UpdateMesh( Mesh mesh, Mesh{} updatedMesh )

Update mesh vertex data in GPU.
Note! Mainly intented to be used with custom meshes.

- Failure return false
- Success return true

---

> success = RL.UnloadMesh( Mesh mesh )

Unload mesh data from CPU and GPU

- Failure return false
- Success return true

---

> success = RL.DrawMesh( Mesh mesh, Material material, Matrix transform )

Draw a 3d mesh with material and transform

- Failure return false
- Success return true

---

> success = RL.DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )

Draw multiple mesh instances with material and different transforms

- Failure return false
- Success return true

---

> success = RL.SetMeshColor( Mesh mesh, Color color )

Updades mesh color vertex attribute buffer
NOTE: Currently only works on custom mesh

- Failure return false
- Success return true

---

> success = RL.ExportMesh( Mesh mesh, string fileName )

Export mesh data to file, returns true on success

- Failure return false
- Success return true

---

> boundingBox = RL.GetMeshBoundingBox( Mesh mesh )

Compute mesh bounding box limits

- Failure return false
- Success return BoundingBox

---

> success = RL.GenMeshTangents( Mesh mesh )

Compute mesh tangents

- Failure return false
- Success return true

---

## Models - Material

---

> material = RL.LoadMaterialDefault()

Load default material

- Success return int

---

> material = RL.CreateMaterial( Material{} material )

Load material from table. See material table definition

- Failure return false
- Success return int

---

> success = RL.UnloadMaterial( Material material )

Unload material from GPU memory ( VRAM )

- Failure return false
- Success return true

---

> RL.SetMaterialTexture( Material material, int mapType, Texture2D texture )

Set texture for a material map type ( MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS... )

---

> success = RL.SetMaterialColor( Material material, int mapType, Color color )

Set color for a material map type

- Failure return false
- Success return true

---

> success = RL.SetMaterialValue( Material material, int mapType, float value )

Set value for a material map type

- Failure return false
- Success return true

---

> RL.SetMaterialShader( Material material, Shader shader )

Set shader for material

---

> success = RL.SetMaterialParams( Material material, float{} params )

Set material generic parameters ( if required )

- Failure return false
- Success return true

---

> texture = RL.GetMaterialTexture( Material material, int mapType )

Get texture from material map type. Returns -1 if no texture.

- Failure return false
- Success return int

---

> color = RL.GetMaterialColor( Material material, int mapType )

Get color from material map type.

- Failure return false
- Success return Color

---

> value = RL.GetMaterialValue( Material material, int mapType )

Get color from material map type.

- Failure return false
- Success return float

---

> shader = RL.GetMaterialShader( Material material )

Get material shader. Returns -1 if no shader.

- Failure return false
- Success return Shader

---

> params = RL.GetMaterialParams( Material material )

Get material parameters.

- Failure return false
- Success return float{}

---

## Models - Model

---

> model = RL.LoadModel( string fileName )

Load model from files ( Meshes and materials )

- Failure return -1
- Success return int

---

> model = RL.LoadModelFromMesh( Mesh mesh )

Load model from generated mesh ( Default material )

- Failure return -1
- Success return int

---

> success = RL.UnloadModel( Model model )

Unload model ( Including meshes ) from memory ( RAM and/or VRAM )

- Failure return false
- Success return true

---

> success = RL.DrawModel( Model model, Vector3 position, float scale, Color tint )

Draw a model ( With texture if set )

- Failure return false
- Success return true

---

> success = RL.DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model with extended parameters

- Failure return false
- Success return true

---

> success = RL.SetModelMaterial( Model model, Material modelMaterial, Material material )

Copies material to model material. ( Model material is the material id in models. Material can be deleted if not used elsewhere )

- Failure return false
- Success return true

---

> success = RL.SetModelMeshMaterial( Model model, int meshId, int materialId )

Set material for a mesh ( Mesh and material on this model )

- Failure return false
- Success return true

---

> RL.DrawBillboard( Camera3D camera, Texture texture, Vector3 position, float size, Color tint )

Draw a billboard texture

---

> RL.DrawBillboardRec( Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector2 size, Color tint )

Draw a billboard texture defined by source

---

> RL.DrawBillboardPro( Camera3D camera, Texture texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint )

Draw a billboard texture defined by source and rotation

---

> success = RL.SetModelTransform( Model model, Matrix transform )

Set model transform matrix

- Failure return false
- Success return true

---

> transform = RL.GetModelTransform( Model model )

Get model transform matrix

- Failure return false
- Success return Matrix

---

## Model - Animations

---

> animations, animationCount = RL.LoadModelAnimations( string fileName )

Load model animations from file

- Failure return -1
- Success return int, int

---

> success = RL.UpdateModelAnimation( Model model, ModelAnimations animations, int animation, int frame )

Update model animation pose

- Failure return false
- Success return true

---

> success = RL.UnloadModelAnimations( ModelAnimations animations )

Unload animation data

- Failure return false
- Success return true

---

> valid = RL.IsModelAnimationValid( Model model, ModelAnimations animations )

Check model animation skeleton match

- Failure return nil
- Success return bool

---

> boneCount = RL.GetModelAnimationBoneCount( ModelAnimations animations, int animation )

Return modelAnimation bone count

- Failure return false
- Success return int

---

> frameCount = RL.GetModelAnimationFrameCount( ModelAnimations animations, int animation )

Return modelAnimation frame count

- Failure return false
- Success return int

---

## Model - Collision

---

> collision = RL.CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )

Check collision between two spheres

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )

Check collision between two bounding boxes

- Failure return nil
- Success return bool

---

> collision = RL.CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )

Check collision between box and sphere

- Failure return nil
- Success return bool

---

> rayCollision = RL.GetRayCollisionSphere( Ray ray, Vector3 center, float radius )

Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionBox( Ray ray, BoundingBox box )

Get collision info between ray and box

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )

Get collision info between ray and mesh

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )

Get collision info between ray and triangle

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )

Get collision info between ray and quad

- Failure return nil
- Success return RayCollision

---

## Audio - Audio device management

---

> success = RL.SetMasterVolume( float volume )

Set master volume ( listener )

- Failure return false
- Success return true

---

## Audio - Wave/Sound Loading

---

> sound = RL.LoadSound( string fileName )

Load sound from file

- Failure return -1
- Success return int

---

> wave = RL.LoadWave( string fileName )

Load wave data from file

- Failure return -1
- Success return int

---

> sound = RL.LoadSoundFromWave( Wave wave )

Load sound from wave data

- Failure return -1
- Success return int

---

> success = RL.UnloadSound( Sound sound )

Unload sound

- Failure return false
- Success return true

---

> success = RL.UnloadWave( Wave wave )

Unload wave data

- Failure return false
- Success return true

---

> success = RL.ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Failure return false
- Success return true

---

> success = RL.ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Failure return false
- Success return true

---

## Audio - Wave/Sound management

---

> success = RL.PlaySound( Sound sound )

Play a sound

- Failure return false
- Success return true

---

> success = RL.StopSound( Sound sound )

Stop playing a sound

- Failure return false
- Success return true

---

> success = RL.PauseSound( Sound sound )

Pause a sound

- Failure return false
- Success return true

---

> success = RL.ResumeSound( Sound sound )

Resume a paused sound

- Failure return false
- Success return true

---

> playing = RL.IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Failure return nil
- Success return bool

---

> success = RL.SetSoundVolume( Sound sound, float volume )

Set volume for a sound ( 1.0 is max level )

- Failure return false
- Success return true

---

> success = RL.SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound ( 1.0 is base level )

- Failure return false
- Success return true

---

> success = RL.SetSoundPan( Sound sound, float pan )

Set pan for a sound ( 0.5 is center )

- Failure return false
- Success return true

---

> success = RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format

- Failure return false
- Success return true

---

> wave = RL.WaveCopy( Wave wave )

Copy a wave to a new wave

- Failure return -1
- Success return int

---

> success = RL.WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range

- Failure return false
- Success return true

---

## Audio - Music management

---

> music = RL.LoadMusicStream( string fileName )

Load music stream from file

- Failure return -1
- Success return int

---

> success = RL.PlayMusicStream( Music music )

Start music playing

- Failure return false
- Success return true

---

> playing = RL.IsMusicStreamPlaying( Music music )

Check if music is playing

- Failure return nil
- Success return bool

---

> success = RL.UpdateMusicStream( Music music )

Updates buffers for music streaming

- Failure return false
- Success return true

---

> success = RL.StopMusicStream( Music music )

Stop music playing

- Failure return false
- Success return true

---

> success = RL.PauseMusicStream( Music music )

Pause music playing

- Failure return false
- Success return true

---

> success = RL.ResumeMusicStream( Music music )

Resume playing paused music

- Failure return false
- Success return true

---

> success = RL.SeekMusicStream( Music music, float position )

Seek music to a position ( in seconds )

- Failure return false
- Success return true

---

> success = RL.SetMusicVolume( Music music, float volume )

Set volume for music ( 1.0 is max level )

- Failure return false
- Success return true

---

> success = RL.SetMusicPitch( Music music, float pitch )

Set pitch for a music ( 1.0 is base level )

- Failure return false
- Success return true

---

> success = RL.SetMusicPan( Music music, float pan )

Set pan for a music ( 0.5 is center )

- Failure return false
- Success return true

---

> success = RL.SetMusicLooping( Music music, bool looping )

Set looping for a music

- Failure return false
- Success return true

---

> looping = RL.GetMusicLooping( Music music )

Get looping of a music

- Failure return nil
- Success return bool

---

> length = RL.GetMusicTimeLength( Music music )

Get music time length ( in seconds )

- Failure return false
- Success return float

---

> played = RL.GetMusicTimePlayed( Music music )

Get current music time played ( in seconds )

- Failure return false
- Success return float

---

## Math - Utils

---

> result = RL.Clamp( float value, float min, float max )

Clamp float value

- Failure return false
- Success return float

---

> result = RL.Lerp( float a, float b, float amount )

Calculate linear interpolation between two floats

- Failure return false
- Success return float

---

> result = RL.Normalize( float value, float a, float b )

Normalize input value within input range

- Failure return false
- Success return float

---

> result = RL.Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )

Remap input value within input range to output range

- Failure return false
- Success return float

---

> result = RL.Wrap( float value, float min, float max )

Wrap input value from min to max

- Failure return false
- Success return float

---

> result = RL.FloatEquals( float x, float y )

Check whether two given floats are almost equal

- Failure return false
- Success return int

---

## Math - Vector2

---

> result = RL.Vector2Zero()

Vector with components value 0.0f

- Success return Vector2

---

> result = RL.Vector2One()

Vector with components value 1.0f

- Success return Vector2

---

> result = RL.Vector2Add( Vector2 v1, Vector2 v2 )

Add two vectors (v1 + v2)

- Failure return false
- Success return Vector2

---

> result = RL.Vector2AddValue( Vector2 v, float add )

Add vector and float value

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Subtract( Vector2 v1, Vector2 v2 )

Subtract two vectors (v1 - v2)

- Failure return false
- Success return Vector2

---

> result = RL.Vector2SubtractValue( Vector2 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Length( vector2 v )

Calculate vector length

- Failure return false
- Success return float

---

> result = RL.Vector2LengthSqr( vector2 v )

Calculate vector square length

- Failure return false
- Success return float

---

> result = RL.Vector2DotProduct( Vector2 v1, Vector2 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float

---

> result = RL.Vector2Distance( Vector2 v1, Vector2 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float

---

> result = RL.Vector2DistanceSqr( Vector2 v1, Vector2 v2 )

Calculate square distance between two vectors

- Failure return false
- Success return float

---

> result = RL.Vector2Angle( Vector2 v1, Vector2 v2 )

Calculate angle from two vectors

- Failure return false
- Success return float

---

> result = RL.Vector2LineAngle( Vector2 a, Vector2 b )

Calculate angle defined by a two vectors line.
NOTE: Parameters need to be normalized.
Current implementation should be aligned with glm::angle.

- Failure return false
- Success return float

---

> result = RL.Vector2Scale( Vector2 v, float scale )

Scale vector ( multiply by value )

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Multiply( Vector2 v1, Vector2 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Negate( Vector2 v )

Negate vector

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Divide( Vector2 v1, Vector2 v2 )

Divide vector by vector

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Normalize( Vector2 v )

Normalize provided vector

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Transform( Vector2 v, Matrix mat )

Transforms a Vector2 by a given Matrix

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Lerp( Vector2 v1, Vector2 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Reflect( Vector2 v, Vector2 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Rotate( Vector2 v, float angle )

Rotate vector by angle

- Failure return false
- Success return Vector2

---

> result = RL.Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )

Move Vector towards target

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Invert( Vector2 v )

Invert the given vector

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Clamp( Vector2 v, Vector2 min, Vector2 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Failure return false
- Success return Vector2

---

> result = RL.Vector2ClampValue( Vector2 v, float min, float max )

Clamp the magnitude of the vector between two min and max values

- Failure return false
- Success return Vector2

---

> result = RL.Vector2Equals( Vector2 v1, Vector2 v2 )

Check whether two given vectors are almost equal

- Failure return false
- Success return int

---

## Math - Vector 3

---

> result = RL.Vector3Zero()

Vector with components value 0.0f

- Success return Vector3

---

> result = RL.Vector3One()

Vector with components value 1.0f

- Success return Vector3

---

> result = RL.Vector3Add( Vector3 v1, Vector3 v2 )

Add two vectors

- Failure return false
- Success return Vector3

---

> result = RL.Vector3AddValue( Vector3 v, float add )

Add vector and float value

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Subtract( Vector3 v1, Vector3 v2 )

Subtract two vectors

- Failure return false
- Success return Vector3

---

> result = RL.Vector3SubtractValue( Vector3 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Scale( Vector3 v, float scalar )

Multiply vector by scalar

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Multiply( Vector3 v1, Vector3 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector3

---

> result = RL.Vector3CrossProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors cross product

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Perpendicular( Vector3 v )

Calculate one vector perpendicular vector

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Length( Vector3 v )

Calculate vector length

- Failure return false
- Success return float

---

> result = RL.Vector3LengthSqr( Vector3 v )

Calculate vector square length

- Failure return false
- Success return float

---

> result = RL.Vector3DotProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float

---

> result = RL.Vector3Distance( Vector3 v1, Vector3 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float

---

> result = RL.Vector3DistanceSqr( Vector3 v1, Vector3 v2 )

Calculate square distance between two vectors

- Failure return false
- Success return float

---

> result = RL.Vector3Angle( Vector3 v1, Vector3 v2 )

Calculate angle between two vectors

- Failure return false
- Success return float

---

> result = RL.Vector3Negate( Vector3 v )

Negate provided vector ( invert direction )

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Divide( Vector3 v1, Vector3 v2 )

Divide vector by vector

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Normalize( Vector3 v )

Normalize provided vector

- Failure return false
- Success return Vector3

---

> v1, v2 = RL.Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )

Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
Gram-Schmidt function implementation

- Failure return false
- Success return Vector3, Vector3

---

> result = RL.Vector3Transform( Vector3 v, Matrix mat )

Transforms a Vector3 by a given Matrix

- Failure return false
- Success return Vector3

---

> result = RL.Vector3RotateByQuaternion( Vector3 v, Quaternion q )

Transform a vector by quaternion rotation

- Failure return false
- Success return Vector3

---

> result = RL.Vector3RotateByAxisAngle( Vector3 v, Vector3 axis, float angle )

Rotates a vector around an axis

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Lerp( Vector3 v1, Vector3 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Reflect( Vector3 v, Vector3 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Min( Vector3 v1, Vector3 v2 )

Get min value for each pair of components

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Max( Vector3 v1, Vector3 v2 )

Get max value for each pair of components

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )

Compute barycenter coordinates ( u, v, w ) for point p with respect to triangle ( a, b, c )
NOTE: Assumes P is on the plane of the triangle

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Unproject( Vector3 source, Matrix projection, Matrix view )

Projects a Vector3 from screen space into object space
NOTE: We are avoiding calling other raymath functions despite available

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Invert( Vector3 v )

Invert the given vector

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Clamp( Vector3 v, Vector3 min, Vector3 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Failure return false
- Success return Vector3

---

> result = RL.Vector3ClampValue( Vector3 v, float min, float max )

Clamp the magnitude of the vector between two values

- Failure return false
- Success return Vector3

---

> result = RL.Vector3Equals( Vector3 v1, Vector3 v2 )

Check whether two given vectors are almost equal

- Failure return false
- Success return int

---

> result = RL.Vector3Refract( Vector3 v, Vector3 n, float r )

Compute the direction of a refracted ray where v specifies the
normalized direction of the incoming ray, n specifies the
normalized normal vector of the interface of two optical media,
and r specifies the ratio of the refractive index of the medium
from where the ray comes to the refractive index of the medium
on the other side of the surface

- Failure return false
- Success return Vector3

---

## Math - Matrix

---

> result = RL.MatrixDeterminant( Matrix mat )

Compute matrix determinant

- Failure return false
- Success return float

---

> result = RL.MatrixTrace( Matrix mat )

Get the trace of the matrix ( sum of the values along the diagonal )

- Failure return false
- Success return float

---

> result = RL.MatrixTranspose( Matrix mat )

Transposes provided matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixInvert( Matrix mat )

Invert provided matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixIdentity()

Get identity matrix

- Success return Matrix

---

> result = RL.MatrixAdd( Matrix left, Matrix right )

Add two matrices

- Failure return false
- Success return Matrix

---

> result = RL.MatrixSubtract( Matrix left, Matrix right )

Subtract two matrices (left - right)

- Failure return false
- Success return Matrix

---

> result = RL.MatrixMultiply( Matrix left, Matrix right )

Get two matrix multiplication

- Failure return false
- Success return Matrix

---

> result = RL.MatrixTranslate( Vector3 translate )

Get translation matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotate( Vector3 axis, float angle )

Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotateX( float angle )

Get x-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotateY( float angle )

Get y-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotateZ( float angle )

Get z-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotateXYZ( Vector3 angle )

Get xyz-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix

---

> result = RL.MatrixRotateZYX( Vector3 angle )

Get zyx-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix

---

> result = RL.MatrixScale( Vector3 scale )

Get scaling matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixFrustum( double left, double right, double bottom, double top, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixPerspective( double fovy, double aspect, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixOrtho( double left, double right, double bottom, double top, double near, double far )

Get orthographic projection matrix

- Failure return false
- Success return Matrix

---

> result = RL.MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )

Get camera look-at matrix ( View matrix )

- Failure return false
- Success return Matrix

---

## Math - Quaternion

---

> result = RL.QuaternionAdd( Quaternion q1, Quaternion q2 )

Add two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionAddValue( Quaternion q, float add )

Add quaternion and float value

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionSubtract( Quaternion q1, Quaternion q2 )

Subtract two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionSubtractValue( Quaternion q, float sub )

Subtract quaternion and float value

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionIdentity()

Get identity quaternion

- Success return Quaternion

---

> result = RL.QuaternionLength( Quaternion q )

Computes the length of a quaternion

- Failure return false
- Success return float

---

> result = RL.QuaternionNormalize( Quaternion q )

Normalize provided quaternion

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionInvert( Quaternion q )

Invert provided quaternion

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionMultiply( Quaternion q1, Quaternion q2 )

Calculate two quaternion multiplication

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionScale( Quaternion q, float mul )

Scale quaternion by float value

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionDivide( Quaternion q1, Quaternion q2 )

Divide two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionLerp( Quaternion q1, Quaternion q2, float amount )

Calculate linear interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )

Calculate slerp-optimized interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )

Calculates spherical linear interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )

Calculate quaternion based on the rotation from one vector to another

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionFromMatrix( Matrix mat )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionToMatrix( Quaternion q )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Matrix

---

> result = RL.QuaternionFromAxisAngle( Vector3 axis, float angle )

Get rotation quaternion for an angle and axis
NOTE: angle must be provided in radians

- Failure return false
- Success return Quaternion

---

> axis, angle = RL.QuaternionToAxisAngle( Quaternion q )

Get the rotation angle and axis for a given quaternion

- Failure return false
- Success return Vector3, float

---

> result = RL.QuaternionFromEuler( float pitch, float yaw, float roll )

Get the quaternion equivalent to Euler angles
NOTE: Rotation order is ZYX

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionToEuler( Quaternion q )

Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
NOTE: Angles are returned in a Vector3 struct in radians

- Failure return false
- Success return Vector3

---

> result = RL.QuaternionTransform( Quaternion q, Matrix mat )

Transform a quaternion given a transformation matrix

- Failure return false
- Success return Quaternion

---

> result = RL.QuaternionEquals( Quaternion q1, Quaternion q2 )

Check whether two given quaternions are almost equal

- Failure return false
- Success return int

---

## Gui - Global

---

> RL.GuiEnable()

Enable gui controls ( global state )

---

> RL.GuiDisable()

Disable gui controls ( global state )

---

> RL.GuiLock()

Lock gui controls ( global state )

---

> RL.GuiUnlock()

Unlock gui controls ( global state )

---

> locked = RL.GuiIsLocked()

Check if gui is locked ( global state )

- Success return bool

---

> success = RL.GuiFade( float alpha )

Set gui controls alpha ( global state ), alpha goes from 0.0f to 1.0f

- Failure return false
- Success return true

---

> success = RL.GuiSetState( int state )

Set gui state ( global state )

- Failure return false
- Success return true

---

> state = RL.GuiGetState()

Get gui state ( global state )

- Success return int

---

## Gui - Font

---

> RL.GuiSetFont( Font font )

Set gui custom font (global state)

---

> font = RL.GuiGetFont()

Get gui custom font ( global state )

- Success return int

---

## Gui - Style

---

> success = RL.GuiSetStyle( int control, int property, int value )

Set one style property

- Failure return false
- Success return true

---

> value = RL.GuiGetStyle( int control, int property )

Get one style property

- Failure return false
- Success return int

---

> success = RL.GuiLoadStyle( string fileName )

Load style file over global style variable ( .rgs )

- Failure return false
- Success return true

---

> RL.GuiLoadStyleDefault()

Load style default over global style

---

## Gui - Container

---

> state = RL.GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Failure return nil
- Success return bool

---

> success = RL.GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name

- Failure return false
- Success return true

---

> success = RL.GuiLine( Rectangle bounds, string text )

Line separator control, could contain text

- Failure return false
- Success return true

---

> success = RL.GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls

- Failure return false
- Success return true

---

> view, scroll = RL.GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )

Scroll Panel control

- Failure return false
- Success return Rectangle, Vector2

---

## Gui - Basic

---

> success = RL.GuiLabel( Rectangle bounds, string text )

Label control, shows text

- Failure return false
- Success return true

---

> clicked = RL.GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Failure return nil
- Success return boolean

---

> clicked = RL.GuiLabelButton( Rectangle bounds, string text )

Label button control, show true when clicked

- Failure return nil
- Success return boolean

---

> active = RL.GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Failure return nil
- Success return boolean

---

> index = RL.GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Failure return false
- Success return int

---

> active = RL.GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Failure return nil
- Success return boolean

---

> active = RL.GuiComboBox( Rectangle bounds, string text, int active )

Combo Box control, returns selected item index

- Failure return nil
- Success return int

---

> pressed, text = RL.GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Failure return nil
- Success return boolean, string

---

> pressed, text = RL.GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control with multiple lines

- Failure return nil
- Success return boolean, string

---

> pressed, value = RL.GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Failure return nil
- Success return boolean, int

---

> pressed, value = RL.GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Failure return nil
- Success return boolean, int

---

> value = RL.GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Failure return nil
- Success return float

---

> value = RL.GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Failure return nil
- Success return float

---

> value = RL.GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Failure return nil
- Success return float

---

> value = RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll Bar control

- Failure return nil
- Success return int

---

> pressed, item = RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Failure return nil
- Success return bool, int

---

> success = RL.GuiStatusBar( Rectangle bounds, string text )

Status Bar control, shows info text

- Failure return false
- Success return true

---

> success = RL.GuiDummyRec( Rectangle bounds, string text )

Dummy control for placeholders

- Failure return false
- Success return true

---

> cell = RL.GuiGrid( Rectangle bounds, string text, float spacing, int subdivs )

Grid control, returns mouse cell position

- Failure return false
- Success return Vector2

---

## Gui - Advanced

---

> itemIndex, scrollIndex = RL.GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index and scroll index

- Failure return nil
- Success return int, int

---

> itemIndex, scrollIndex, focus = RL.GuiListViewEx( Rectangle bounds, string text, int focus, int scrollIndex, int active )

List View with extended parameters, returns selected list item index, scroll index and focus

- Failure return nil
- Success return int, int, int

---

> buttonIndex = RL.GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message, returns button index ( 0 is x button )

- Failure return false
- Success return int

---

> buttonIndex, text, secretViewActive = RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )

Text Input Box control, ask for text, supports secret

- Failure return false
- Success return int, string, int

---

> color = RL.GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control ( multiple color controls )

- Failure return false
- Success return Color

---

> color = RL.GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Failure return false
- Success return Color

---

> alpha = RL.GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Failure return false
- Success return float

---

> hue = RL.GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Failure return false
- Success return float

---

## Gui - Icons

---

> text = RL.GuiIconText( int iconId, string text )

Get text with icon id prepended ( if supported )

- Failure return false
- Success return string

---

> success = RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon

- Failure return false
- Success return true

---

> success = RL.GuiSetIconScale( int scale )

Set icon scale ( 1 by default )

- Failure return false
- Success return true

---

> success = RL.GuiSetIconPixel( int iconId, Vector2 pos )

Set icon pixel value

- Failure return false
- Success return true

---

> success = RL.GuiClearIconPixel( int iconId, Vector2 pos )

Clear icon pixel value

- Failure return false
- Success return true

---

> value = RL.GuiCheckIconPixel( int iconId, Vector2 pos )

Check icon pixel value

- Failure return nil
- Success return bool

---

## Lights - Basics

---

> light = RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )

Create a light and get shader locations

- Failure return -1
- Success return int

---

> RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader

---

> success = RL.SetLightType( Light light, int type )

Set light type

- Failure return false
- Success return true

---

> success = RL.SetLightPosition( Light light, Vector3 position )

Set light position

- Failure return false
- Success return true

---

> success = RL.SetLightTarget( Light light, Vector3 target )

Set light target

- Failure return false
- Success return true

---

> success = RL.SetLightColor( Light light, Color color )

Set light color

- Failure return false
- Success return true

---

> success = RL.SetLightEnabled( Light light, bool enabled )

Set light enabled

- Failure return false
- Success return true

---

> type = RL.GetLightType( Light light )

Get light type

- Failure return false
- Success return int

---

> position = RL.GetLightPosition( Light light )

Get light position

- Failure return false
- Success return Vector3

---

> target = RL.GetLightTarget( Light light )

Get light target

- Failure return false
- Success return Vector3

---

> color = RL.GetLightColor( Light light )

Get light color

- Failure return false
- Success return Color

---

> enabled = RL.IsLightEnabled( Light light )

Get light enabled

- Failure return nil
- Success return boolean

---

## RLGL - Matrix operations

---

> success = RL.rlMatrixMode( int mode )

Choose the current matrix to be transformed

- Failure return false
- Success return true

---

> RL.rlPushMatrix()

Push the current matrix to stack

---

> RL.rlPopMatrix()

Pop latest inserted matrix from stack

---

> RL.rlLoadIdentity()

Reset current matrix to identity matrix

---

> success = RL.rlTranslatef( Vector3 translation )

Multiply the current matrix by a translation matrix

- Failure return false
- Success return true

---

> success = RL.rlRotatef( float angle, Vector3 rotation )

Multiply the current matrix by a rotation matrix

- Failure return false
- Success return true

---

> success = RL.rlScalef( Vector3 scale )

Multiply the current matrix by a scaling matrix

- Failure return false
- Success return true

---

> success = RL.rlMultMatrixf( Matrix matrix )

Multiply the current matrix by another matrix

- Failure return false
- Success return true

---

> success = RL.rlFrustum( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by a perspective matrix generated by parameters

- Failure return false
- Success return true

---

> success = RL.rlOrtho( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by an orthographic matrix generated by parameters

- Failure return false
- Success return true

---

> success = RL.rlViewport( Rectangle viewport )

Set the viewport area ( transformation from normalized device coordinates to window coordinates )
NOTE: We store current viewport dimensions

- Failure return false
- Success return true

---

## RLGL - Vertex level operations

---

> success = RL.rlBegin( int mode )

Initialize drawing mode ( how to organize vertex )

- Failure return false
- Success return true

---

> RL.rlEnd()

Finish vertex providing

---

> success = RL.rlVertex2f( Vector2 position )

Define one vertex ( position )

- Failure return false
- Success return true

---

> success = RL.rlVertex3f( Vector3 position )

Define one vertex ( position )

- Failure return false
- Success return true

---

> success = RL.rlTexCoord2f( Vector2 texCoord )

Define one vertex ( texture coordinate ) - 2 float

- Failure return false
- Success return true

---

> success = RL.rlNormal3f( Vector3 normal )

Define one vertex ( normal ) - 3 float

- Failure return false
- Success return true

---

> success = RL.rlColor4ub( Color color )

Define one vertex ( color ) - 4 byte

- Failure return false
- Success return true

---

> success = RL.rlColor3f( Vector3 color )

Define one vertex ( color ) - 3 float

- Failure return false
- Success return true

---

> success = RL.rlColor4f( Vector4 color )

Define one vertex ( color ) - 4 float

- Failure return false
- Success return true

---

## RLGL - Vertex buffers state

---

> supported = RL.rlEnableVertexArray( int vaoId )

Enable vertex array ( VAO, if supported )

- Failure return nil
- Success return bool

---

> RL.rlDisableVertexArray()

Disable vertex array ( VAO, if supported )

---

> success = RL.rlEnableVertexBuffer( int id )

Enable vertex buffer ( VBO )

- Failure return false
- Success return true

---

> RL.rlDisableVertexBuffer()

Disable vertex buffer ( VBO )

---

> success = RL.rlEnableVertexBufferElement( int id )

Enable vertex buffer element ( VBO element )

- Failure return false
- Success return true

---

> RL.rlDisableVertexBufferElement()

Disable vertex buffer element ( VBO element )

---

> success = RL.rlEnableVertexAttribute( int index )

Enable vertex attribute index

- Failure return false
- Success return true

---

> success = RL.rlDisableVertexAttribute( int index )

Disable vertex attribute index

- Failure return false
- Success return true

---

## RLGL - Textures state

---

> success = RL.rlActiveTextureSlot( int slot )

Select and active a texture slot

- Failure return false
- Success return true

---

> success = RL.rlEnableTexture( int id )

Enable texture

- Failure return false
- Success return true

---

> RL.rlDisableTexture()

Disable texture

---

> success = RL.rlEnableTextureCubemap( int id )

Enable texture cubemap

- Failure return false
- Success return true

---

> RL.rlDisableTextureCubemap()

Disable texture cubemap

---

> success = RL.rlTextureParameters( int id, int param, int value )

Set texture parameters ( filter, wrap )

- Failure return false
- Success return true

---

> success = RL.rlCubemapParameters( int id, int param, int value )

Set cubemap parameters ( filter, wrap )

- Failure return false
- Success return true

---

## RLGL - Shader state

---

> success = RL.rlEnableShader( int id )

Enable shader program

- Failure return false
- Success return true

---

> RL.rlDisableShader()

Disable shader program

---

## RLGL - Framebuffer state

---

> success = RL.rlEnableFramebuffer( int id )

Enable render texture (fbo)

- Failure return false
- Success return true

---

> RL.rlDisableFramebuffer()

Disable render texture (fbo), return to default framebuffer

---

> success = RL.rlActiveDrawBuffers( int count )

Activate multiple draw color buffers

- Failure return false
- Success return true

---

## RLGL - General render state

---

> RL.rlEnableColorBlend()

Enable color blending

---

> RL.rlDisableColorBlend()

Disable color blending

---

> RL.rlEnableDepthTest()

Enable depth test

---

> RL.rlDisableDepthTest()

Disable depth test

---

> RL.rlEnableDepthMask()

Enable depth write

---

> RL.rlDisableDepthMask()

Disable depth write

---

> RL.rlEnableBackfaceCulling()

Enable backface culling

---

> RL.rlDisableBackfaceCulling()

Disable backface culling

---

> success = RL.rlSetCullFace( int mode )

Set face culling mode

- Failure return false
- Success return true

---

> RL.rlEnableScissorTest()

Enable scissor test

---

> RL.rlDisableScissorTest()

Disable scissor test

---

> success = RL.rlScissor( Rectangle area )

Scissor test

- Failure return false
- Success return true

---

> RL.rlEnableWireMode()

Enable wire mode

---

> RL.rlDisableWireMode()

Disable wire mode

---

> success = RL.rlSetLineWidth( float width )

Set the line drawing width

- Failure return false
- Success return true

---

> width = RL.rlGetLineWidth()

Get the line drawing width

- Success return float

---

> RL.rlEnableSmoothLines()

Enable line aliasing

---

> RL.rlDisableSmoothLines()

Disable line aliasing

---

> RL.rlEnableStereoRender()

Enable stereo rendering

---

> RL.rlDisableStereoRender()

Enable stereo rendering

---

> enabled = RL.rlIsStereoRenderEnabled()

Check if stereo render is enabled

- Success return bool

---

> success = RL.rlClearColor( Color color )

Clear color buffer with color

- Failure return false
- Success return true

---

> RL.rlClearScreenBuffers()

Clear used screen buffers ( color and depth )

---

> RL.rlCheckErrors()

Check and log OpenGL error codes

---

> success = RL.rlSetBlendMode( int mode )

Set blending mode

- Failure return false
- Success return true

---

> success = RL.rlSetBlendFactors( int glSrcFactor, int glDstFactor, int glEquation )

Set blending mode factor and equation ( using OpenGL factors )

- Failure return false
- Success return true

---

> success = RL.rlSetBlendFactorsSeparate( int glSrcRGB, int glDstRGB, int glSrcAlpha, int glDstAlpha, int glEqRGB, int glEqAlpha )

Set blending mode factors and equations separately ( using OpenGL factors )

- Failure return false
- Success return true

---

## RLGL - Initialization functions

---

> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int

---

## RLGL - Render batch management

---

> RL.rlDrawRenderBatchActive()

Update and draw internal render batch

---

> overflow = RL.rlCheckRenderBatchLimit( int vCount )

Check internal buffer overflow for a given number of vertex and force a rlRenderBatch draw call if required

- Failure return nil
- Success return bool

---

> success = RL.rlSetTexture( int id )

Set current texture for render batch and check buffers limits

- Failure return false
- Success return true

---

## RLGL - Vertex buffers management

---

> vaoId = RL.rlLoadVertexArray()

Load vertex array (vao) if supported

- Success return int

---

> vboId = RL.rlLoadVertexBuffer( Buffer buffer, bool dynamic )

Load a vertex buffer attribute

- Failure return -1
- Success return int

---

> vboId = RL.rlLoadVertexBufferElement( Buffer buffer, bool dynamic )

Load a new attributes element buffer

- Failure return -1
- Success return int

---

> success = RL.rlUpdateVertexBuffer( int bufferId, Buffer buffer, int offset )

Update GPU buffer with new data

- Failure return false
- Success return true

---

> success = RL.rlUpdateVertexBufferElements( int id, Buffer buffer, int offset )

Update vertex buffer elements with new data

- Failure return false
- Success return true

---

> success = RL.rlUnloadVertexArray( int vaoId )

Unload vertex array object (VAO)

- Failure return false
- Success return true

---

> success = RL.rlUnloadVertexBuffer( int vboId )

Unload vertex buffer (VBO)

- Failure return false
- Success return true

---

> success = RL.rlSetVertexAttribute( int index, int compSize, int type, bool normalized, int stride, int pointer )

Set vertex attribute

- Failure return false
- Success return true

---

> success = RL.rlSetVertexAttributeDivisor( int index, int divisor )

Set vertex attribute divisor

- Failure return false
- Success return true

---

> success = RL.rlSetVertexAttributeDefault( int locIndex, float{} value, int attribType )

Set vertex attribute default value

- Failure return false
- Success return true

---

> success = RL.rlDrawVertexArray( int offset, int count )

Draw vertex array

- Failure return false
- Success return true

---

> success = RL.rlDrawVertexArrayElements( int offset, int count, Buffer buffer )

Draw vertex array elements

- Failure return false
- Success return true

---

> success = RL.rlDrawVertexArrayInstanced( int offset, int count, int instances )

Draw vertex array instanced

- Failure return false
- Success return true

---

> success = RL.rlDrawVertexArrayElementsInstanced( int offset, int count, Buffer buffer, int instances )

Draw vertex array elements instanced

- Failure return false
- Success return true

---

## RLGL - Textures management

---

> id = RL.rlLoadTexture( Vector2 size, int format, int mipmapCount )

Load texture in GPU

- Failure return -1
- Success return int

---

> id = RL.rlLoadTextureDepth( Vector2 size, bool useRenderBuffer )

Load depth texture/renderbuffer ( to be attached to fbo )

- Failure return -1
- Success return int

---

> success = RL.rlUnloadTexture( int id )

Unload texture from GPU memory

- Failure return false
- Success return true

---

## RLGL - Framebuffer management (fbo)

---

> fboId = RL.rlLoadFramebuffer( Vector2 size )

Load an empty framebuffer

- Failure return -1
- Success return int

---

> success = RL.rlFramebufferAttach( int fboId, int texId, int attachType, int texType, int mipLevel )

Attach texture/renderbuffer to a framebuffer

- Failure return false
- Success return true

---

> isComplete = RL.rlFramebufferComplete( int id )

Verify framebuffer is complete

- Failure return nil
- Success return bool

---

> success = RL.rlUnloadFramebuffer( int id )

Delete framebuffer from GPU

- Failure return nil
- Success return bool

---

## RLGL - Shaders management

---

> success = RL.rlLoadShaderCode( string vsCode, string fsCode )

Load shader from code strings

- Failure return nil
- Success return int

---

## RLGL - Matrix state management

---

> modelview = RL.rlGetMatrixModelview()

Get internal modelview matrix

- Success return Matrix

---

> projection = RL.rlGetMatrixProjection()

Get internal projection matrix

- Success return Matrix

---

> transform = RL.rlGetMatrixTransform()

Get internal accumulated transform matrix

- Success return Matrix

---

> projection = RL.rlGetMatrixProjectionStereo( int eye )

Get internal projection matrix for stereo render (selected eye)

- Failure return false
- Success return Matrix

---

> viewOffset = RL.rlGetMatrixViewOffsetStereo( int eye )

Get internal view offset matrix for stereo render (selected eye)

- Failure return false
- Success return Matrix

---

> success = RL.rlSetMatrixProjection( Matrix proj )

Set a custom projection matrix (replaces internal projection matrix)

- Failure return false
- Success return true

---

> success = RL.rlSetMatrixModelview( Matrix view )

Set a custom modelview matrix (replaces internal modelview matrix)

- Failure return false
- Success return true

---

> success = RL.rlSetMatrixProjectionStereo( Matrix right, Matrix left )

Set eyes projection matrices for stereo rendering

- Failure return false
- Success return true

---

> success = RL.rlSetMatrixViewOffsetStereo( Matrix right, Matrix left )

Set eyes view offsets matrices for stereo rendering

- Failure return false
- Success return true

---

## OpenGL - Framebuffer management

---

> RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use -1 RenderTexture for window framebuffer.

---

## Easings - Linear Easing functions

---

> value = RL.EaseLinear( float t, float b, float c, float d )

Ease linear

- Failure return false
- Success return float

---

## Easings - Sine Easing functions

---

> value = RL.EaseSineIn( float t, float b, float c, float d )

Ease sine in

- Failure return false
- Success return float

---

> value = RL.EaseSineOut( float t, float b, float c, float d )

Ease sine out

- Failure return false
- Success return float

---

> value = RL.EaseSineInOut( float t, float b, float c, float d )

Ease sine in out

- Failure return false
- Success return float

---

## Easings - Circular Easing functions

---

> value = RL.EaseCircIn( float t, float b, float c, float d )

Ease circle in

- Failure return false
- Success return float

---

> value = RL.EaseCircOut( float t, float b, float c, float d )

Ease circle out

- Failure return false
- Success return float

---

> value = RL.EaseCircInOut( float t, float b, float c, float d )

Ease circle in out

- Failure return false
- Success return float

---

## Easings - Cubic Easing functions

---

> value = RL.EaseCubicIn( float t, float b, float c, float d )

Ease cubic in

- Failure return false
- Success return float

---

> value = RL.EaseCubicOut( float t, float b, float c, float d )

Ease cubic out

- Failure return false
- Success return float

---

> value = RL.EaseCubicInOut( float t, float b, float c, float d )

Ease cubic in out

- Failure return false
- Success return float

---

## Easings - Quadratic Easing functions

---

> value = RL.EaseQuadIn( float t, float b, float c, float d )

Ease quadratic in

- Failure return false
- Success return float

---

> value = RL.EaseQuadOut( float t, float b, float c, float d )

Ease quadratic out

- Failure return false
- Success return float

---

> value = RL.EaseQuadInOut( float t, float b, float c, float d )

Ease quadratic in out

- Failure return false
- Success return float

---

## Easings - Exponential Easing functions

---

> value = RL.EaseExpoIn( float t, float b, float c, float d )

Ease exponential in

- Failure return false
- Success return float

---

> value = RL.EaseExpoOut( float t, float b, float c, float d )

Ease exponential out

- Failure return false
- Success return float

---

> value = RL.EaseExpoInOut( float t, float b, float c, float d )

Ease exponential in out

- Failure return false
- Success return float

---

## Easings - Back Easing functions

---

> value = RL.EaseBackIn( float t, float b, float c, float d )

Ease back in

- Failure return false
- Success return float

---

> value = RL.EaseBackOut( float t, float b, float c, float d )

Ease back out

- Failure return false
- Success return float

---

> value = RL.EaseBackInOut( float t, float b, float c, float d )

Ease back in out

- Failure return false
- Success return float

---

## Easings - Bounce Easing functions

---

> value = RL.EaseBounceIn( float t, float b, float c, float d )

Ease bounce in

- Failure return false
- Success return float

---

> value = RL.EaseBounceOut( float t, float b, float c, float d )

Ease bounce out

- Failure return false
- Success return float

---

> value = RL.EaseBounceInOut( float t, float b, float c, float d )

Ease bounce in out

- Failure return false
- Success return float

---

## Easings - Elastic Easing functions

---

> value = RL.EaseElasticIn( float t, float b, float c, float d )

Ease elastic in

- Failure return false
- Success return float

---

> value = RL.EaseElasticOut( float t, float b, float c, float d )

Ease elastic out

- Failure return false
- Success return float

---

> value = RL.EaseElasticInOut( float t, float b, float c, float d )

Ease elastic in out

- Failure return false
- Success return float

---
