# ReiLua API

## Usage

Application needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where "main.lua" is located can be given as argument. There are five Lua functions that the framework will call, 'RL.init', 'RL.process', 'RL.draw', 'RL.log' and 'RL.exit'.

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

> function RL.log( logLevel, message )

This function can be used for custom log message handling.

---

> function RL.exit()

This function will be called on program close. Cleanup could be done here.

---

## Globals - ConfigFlags

FLAG_VSYNC_HINT

FLAG_FULLSCREEN_MODE

FLAG_WINDOW_RESIZABLE

FLAG_WINDOW_UNDECORATED

FLAG_WINDOW_HIDDEN

FLAG_WINDOW_MINIMIZED

FLAG_WINDOW_MAXIMIZED

FLAG_WINDOW_UNFOCUSED

FLAG_WINDOW_TOPMOST

FLAG_WINDOW_ALWAYS_RUN

FLAG_WINDOW_TRANSPARENT

FLAG_WINDOW_HIGHDPI

FLAG_MSAA_4X_HINT

FLAG_INTERLACED_HINT

## Globals - TraceLogLevel

LOG_ALL

LOG_TRACE

LOG_DEBUG

LOG_INFO

LOG_WARNING

LOG_ERROR

LOG_FATAL

LOG_NONE

## Globals - KeyboardKey

GLFW_KEY_UNKNOWN

KEY_NULL

KEY_APOSTROPHE

KEY_COMMA

KEY_MINUS

KEY_PERIOD

KEY_SLASH

KEY_ZERO

KEY_ONE

KEY_TWO

KEY_THREE

KEY_FOUR

KEY_FIVE

KEY_SIX

KEY_SEVEN

KEY_EIGHT

KEY_NINE

KEY_SEMICOLON

KEY_EQUAL

KEY_A

KEY_B

KEY_C

KEY_D

KEY_E

KEY_F

KEY_G

KEY_H

KEY_I

KEY_J

KEY_K

KEY_L

KEY_M

KEY_N

KEY_O

KEY_P

KEY_Q

KEY_R

KEY_S

KEY_T

KEY_U

KEY_V

KEY_W

KEY_X

KEY_Y

KEY_Z

KEY_LEFT_BRACKET

KEY_BACKSLASH

KEY_RIGHT_BRACKET

KEY_GRAVE

KEY_SPACE

KEY_ESCAPE

KEY_ENTER

KEY_TAB

KEY_BACKSPACE

KEY_INSERT

KEY_DELETE

KEY_RIGHT

KEY_LEFT

KEY_DOWN

KEY_UP

KEY_PAGE_UP

KEY_PAGE_DOWN

KEY_HOME

KEY_END

KEY_CAPS_LOCK

KEY_SCROLL_LOCK

KEY_NUM_LOCK

KEY_PRINT_SCREEN

KEY_PAUSE

KEY_F1

KEY_F2

KEY_F3

KEY_F4

KEY_F5

KEY_F6

KEY_F7

KEY_F8

KEY_F9

KEY_F10

KEY_F11

KEY_F12

KEY_LEFT_SHIFT

KEY_LEFT_CONTROL

KEY_LEFT_ALT

KEY_LEFT_SUPER

KEY_RIGHT_SHIFT

KEY_RIGHT_CONTROL

KEY_RIGHT_ALT

KEY_RIGHT_SUPER

KEY_KB_MENU

KEY_KP_0

KEY_KP_1

KEY_KP_2

KEY_KP_3

KEY_KP_4

KEY_KP_5

KEY_KP_6

KEY_KP_7

KEY_KP_8

KEY_KP_9

KEY_KP_DECIMAL

KEY_KP_DIVIDE

KEY_KP_MULTIPLY

KEY_KP_SUBTRACT

KEY_KP_ADD

KEY_KP_ENTER

KEY_KP_EQUAL

KEY_BACK

KEY_MENU

KEY_VOLUME_UP

KEY_VOLUME_DOWN

## Globals - MouseButtons

MOUSE_BUTTON_LEFT

MOUSE_BUTTON_RIGHT

MOUSE_BUTTON_MIDDLE

MOUSE_BUTTON_SIDE

MOUSE_BUTTON_EXTRA

MOUSE_BUTTON_FORWARD

MOUSE_BUTTON_BACK

## Globals - MouseCursor

MOUSE_CURSOR_DEFAULT

MOUSE_CURSOR_ARROW

MOUSE_CURSOR_IBEAM

MOUSE_CURSOR_CROSSHAIR

MOUSE_CURSOR_POINTING_HAND

MOUSE_CURSOR_RESIZE_EW

MOUSE_CURSOR_RESIZE_NS

MOUSE_CURSOR_RESIZE_NWSE

MOUSE_CURSOR_RESIZE_NESW

MOUSE_CURSOR_RESIZE_ALL

MOUSE_CURSOR_NOT_ALLOWED

## Globals - GamepadButtons

GAMEPAD_BUTTON_UNKNOWN

GAMEPAD_BUTTON_LEFT_FACE_UP

GAMEPAD_BUTTON_LEFT_FACE_RIGHT

GAMEPAD_BUTTON_LEFT_FACE_DOWN

GAMEPAD_BUTTON_LEFT_FACE_LEFT

GAMEPAD_BUTTON_RIGHT_FACE_UP

GAMEPAD_BUTTON_RIGHT_FACE_RIGHT

GAMEPAD_BUTTON_RIGHT_FACE_DOWN

GAMEPAD_BUTTON_RIGHT_FACE_LEFT

GAMEPAD_BUTTON_LEFT_TRIGGER_1

GAMEPAD_BUTTON_LEFT_TRIGGER_2

GAMEPAD_BUTTON_RIGHT_TRIGGER_1

GAMEPAD_BUTTON_RIGHT_TRIGGER_2

GAMEPAD_BUTTON_MIDDLE_LEFT

GAMEPAD_BUTTON_MIDDLE

GAMEPAD_BUTTON_MIDDLE_RIGHT

GAMEPAD_BUTTON_LEFT_THUMB

GAMEPAD_BUTTON_RIGHT_THUMB

## Globals - GamepadAxis

GAMEPAD_AXIS_LEFT_X

GAMEPAD_AXIS_LEFT_Y

GAMEPAD_AXIS_RIGHT_X

GAMEPAD_AXIS_RIGHT_Y

GAMEPAD_AXIS_LEFT_TRIGGER

GAMEPAD_AXIS_RIGHT_TRIGGER

## Globals - MapTypes

MATERIAL_MAP_ALBEDO

MATERIAL_MAP_METALNESS

MATERIAL_MAP_NORMAL

MATERIAL_MAP_ROUGHNESS

MATERIAL_MAP_OCCLUSION

MATERIAL_MAP_EMISSION

MATERIAL_MAP_HEIGHT

MATERIAL_MAP_CUBEMAP

MATERIAL_MAP_IRRADIANCE

MATERIAL_MAP_PREFILTER

MATERIAL_MAP_BRDF

MATERIAL_MAP_DIFFUSE

MATERIAL_MAP_SPECULAR

## Globals - ShaderLocationIndex

SHADER_LOC_VERTEX_POSITION

SHADER_LOC_VERTEX_TEXCOORD01

SHADER_LOC_VERTEX_TEXCOORD02

SHADER_LOC_VERTEX_NORMAL

SHADER_LOC_VERTEX_TANGENT

SHADER_LOC_VERTEX_COLOR

SHADER_LOC_MATRIX_MVP

SHADER_LOC_MATRIX_VIEW

SHADER_LOC_MATRIX_PROJECTION

SHADER_LOC_MATRIX_MODEL

SHADER_LOC_MATRIX_NORMAL

SHADER_LOC_VECTOR_VIEW

SHADER_LOC_COLOR_DIFFUSE

SHADER_LOC_COLOR_SPECULAR

SHADER_LOC_COLOR_AMBIENT

SHADER_LOC_MAP_ALBEDO

SHADER_LOC_MAP_METALNESS

SHADER_LOC_MAP_NORMAL

SHADER_LOC_MAP_ROUGHNESS

SHADER_LOC_MAP_OCCLUSION

SHADER_LOC_MAP_EMISSION

SHADER_LOC_MAP_HEIGHT

SHADER_LOC_MAP_CUBEMAP

SHADER_LOC_MAP_IRRADIANCE

SHADER_LOC_MAP_PREFILTER

SHADER_LOC_MAP_BRDF

SHADER_LOC_MAP_DIFFUSE

SHADER_LOC_MAP_SPECULAR

## Globals - ShaderUniformDataType

SHADER_UNIFORM_FLOAT

SHADER_UNIFORM_VEC2

SHADER_UNIFORM_VEC3

SHADER_UNIFORM_VEC4

SHADER_UNIFORM_INT

SHADER_UNIFORM_IVEC2

SHADER_UNIFORM_IVEC3

SHADER_UNIFORM_IVEC4

SHADER_UNIFORM_SAMPLER2D

## Globals - ShaderAttributeDataTypes

SHADER_ATTRIB_FLOAT

SHADER_ATTRIB_VEC2

SHADER_ATTRIB_VEC3

SHADER_ATTRIB_VEC4

## Globals - PixelFormats

PIXELFORMAT_UNCOMPRESSED_GRAYSCALE

PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA

PIXELFORMAT_UNCOMPRESSED_R5G6B5

PIXELFORMAT_UNCOMPRESSED_R8G8B8

PIXELFORMAT_UNCOMPRESSED_R5G5B5A1

PIXELFORMAT_UNCOMPRESSED_R4G4B4A4

PIXELFORMAT_UNCOMPRESSED_R8G8B8A8

PIXELFORMAT_UNCOMPRESSED_R32

PIXELFORMAT_UNCOMPRESSED_R32G32B32

PIXELFORMAT_UNCOMPRESSED_R32G32B32A32

PIXELFORMAT_COMPRESSED_DXT1_RGB

PIXELFORMAT_COMPRESSED_DXT1_RGBA

PIXELFORMAT_COMPRESSED_DXT3_RGBA

PIXELFORMAT_COMPRESSED_DXT5_RGBA

PIXELFORMAT_COMPRESSED_ETC1_RGB

PIXELFORMAT_COMPRESSED_ETC2_RGB

PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA

PIXELFORMAT_COMPRESSED_PVRT_RGB

PIXELFORMAT_COMPRESSED_PVRT_RGBA

PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA

PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA

## Globals - TextureFilters

TEXTURE_FILTER_POINT

TEXTURE_FILTER_BILINEAR

TEXTURE_FILTER_TRILINEAR

TEXTURE_FILTER_ANISOTROPIC_4X

TEXTURE_FILTER_ANISOTROPIC_8X

TEXTURE_FILTER_ANISOTROPIC_16X

## Globals - TextureWrap

TEXTURE_WRAP_REPEAT

TEXTURE_WRAP_CLAMP

TEXTURE_WRAP_MIRROR_REPEAT

TEXTURE_WRAP_MIRROR_CLAMP

## Globals - CubemapLayout

CUBEMAP_LAYOUT_AUTO_DETECT

CUBEMAP_LAYOUT_LINE_VERTICAL

CUBEMAP_LAYOUT_LINE_HORIZONTAL

CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR

CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE

CUBEMAP_LAYOUT_PANORAMA

## Globals - FontType

FONT_DEFAULT

FONT_BITMAP

FONT_SDF

## Globals - BlendModes

BLEND_ALPHA

BLEND_ADDITIVE

BLEND_MULTIPLIED

BLEND_ADD_COLORS

BLEND_SUBTRACT_COLORS

BLEND_ALPHA_PREMULTIPLY

BLEND_CUSTOM

BLEND_CUSTOM_SEPARATE

## Globals - Gesture

GESTURE_NONE

GESTURE_TAP

GESTURE_DOUBLETAP

GESTURE_HOLD

GESTURE_DRAG

GESTURE_SWIPE_RIGHT

GESTURE_SWIPE_LEFT

GESTURE_SWIPE_UP

GESTURE_SWIPE_DOWN

GESTURE_PINCH_IN

GESTURE_PINCH_OUT

## Globals - CameraMode

CAMERA_CUSTOM

CAMERA_FREE

CAMERA_ORBITAL

CAMERA_FIRST_PERSON

CAMERA_THIRD_PERSON

## Globals - CameraProjections

CAMERA_PERSPECTIVE

CAMERA_ORTHOGRAPHIC

## Globals - N-patchLayout

NPATCH_NINE_PATCH

NPATCH_THREE_PATCH_VERTICAL

NPATCH_THREE_PATCH_HORIZONTAL

## Globals - TextureTypes

TEXTURE_TYPE_TEXTURE

TEXTURE_TYPE_RENDER_TEXTURE

## Globals - Colors

LIGHTGRAY

GRAY

DARKGRAY

YELLOW

GOLD

ORANGE

PINK

RED

MAROON

GREEN

LIME

DARKGREEN

SKYBLUE

BLUE

DARKBLUE

PURPLE

VIOLET

DARKPURPLE

BEIGE

BROWN

DARKBROWN

WHITE

BLACK

BLANK

MAGENTA

RAYWHITE

## Globals - Math

PI

DEG2RAD

RAD2DEG

## Globals - GuiControlState

STATE_NORMAL

STATE_FOCUSED

STATE_PRESSED

STATE_DISABLED

## Globals - GuiTextAlignment

TEXT_ALIGN_LEFT

TEXT_ALIGN_CENTER

TEXT_ALIGN_RIGHT

## Globals - GuiControl

DEFAULT

LABEL

BUTTON

TOGGLE

SLIDER

PROGRESSBAR

CHECKBOX

COMBOBOX

DROPDOWNBOX

TEXTBOX

VALUEBOX

SPINNER

LISTVIEW

COLORPICKER

SCROLLBAR

STATUSBAR

## Globals - GuiControlProperty

BORDER_COLOR_NORMAL

BASE_COLOR_NORMAL

TEXT_COLOR_NORMAL

BORDER_COLOR_FOCUSED

BASE_COLOR_FOCUSED

TEXT_COLOR_FOCUSED

BORDER_COLOR_PRESSED

BASE_COLOR_PRESSED

TEXT_COLOR_PRESSED

BORDER_COLOR_DISABLED

BASE_COLOR_DISABLED

TEXT_COLOR_DISABLED

BORDER_WIDTH

TEXT_PADDING

TEXT_ALIGNMENT

RESERVED

## Globals - GuiDefaultProperty

TEXT_SIZE

TEXT_SPACING

LINE_COLOR

BACKGROUND_COLOR

## Globals - GuiToggleProperty

GROUP_PADDING

## Globals - GuiSliderProperty

SLIDER_WIDTH

SLIDER_PADDING

## Globals - GuiProgressBarProperty

PROGRESS_PADDING

## Globals - GuiScrollBarProperty

ARROWS_SIZE

ARROWS_VISIBLE

SCROLL_SLIDER_PADDING

SCROLL_SLIDER_SIZE

SCROLL_PADDING

SCROLL_SPEED

## Globals - GuiCheckBoxProperty

CHECK_PADDING

## Globals - GuiComboBoxProperty

COMBO_BUTTON_WIDTH

COMBO_BUTTON_SPACING

## Globals - GuiDropdownBoxProperty

ARROW_PADDING

DROPDOWN_ITEMS_SPACING

## Globals - GuiTextBoxProperty

TEXT_INNER_PADDING

TEXT_LINES_SPACING

## Globals - GuiSpinnerProperty

SPIN_BUTTON_WIDTH

SPIN_BUTTON_SPACING

## Globals - GuiListViewProperty

LIST_ITEMS_HEIGHT

LIST_ITEMS_SPACING

SCROLLBAR_WIDTH

SCROLLBAR_SIDE

## Globals - GuiColorPickerProperty

COLOR_SELECTOR_SIZE

HUEBAR_WIDTH

HUEBAR_PADDING

HUEBAR_SELECTOR_HEIGHT

HUEBAR_SELECTOR_OVERFLOW

## Globals - LightType

LIGHT_DIRECTIONAL

LIGHT_POINT

## Globals - RLGL

RL_DEFAULT_BATCH_BUFFER_ELEMENTS

RL_DEFAULT_BATCH_BUFFERS

RL_DEFAULT_BATCH_DRAWCALLS

RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS

## Globals - RLGL

RL_MAX_MATRIX_STACK_SIZE

## Globals - RLGL

RL_MAX_SHADER_LOCATIONS

## Globals - RLGL

RL_CULL_DISTANCE_NEAR

RL_CULL_DISTANCE_FAR

## Globals - RLGL

RL_TEXTURE_WRAP_S

RL_TEXTURE_WRAP_T

RL_TEXTURE_MAG_FILTER

RL_TEXTURE_MIN_FILTER

RL_TEXTURE_FILTER_NEAREST

RL_TEXTURE_FILTER_LINEAR

RL_TEXTURE_FILTER_MIP_NEAREST

RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR

RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST

RL_TEXTURE_FILTER_MIP_LINEAR

RL_TEXTURE_FILTER_ANISOTROPIC

RL_TEXTURE_MIPMAP_BIAS_RATIO

RL_TEXTURE_WRAP_REPEAT

RL_TEXTURE_WRAP_CLAMP

RL_TEXTURE_WRAP_MIRROR_REPEAT

RL_TEXTURE_WRAP_MIRROR_CLAMP

## Globals - RLGL

RL_MODELVIEW

RL_PROJECTION

RL_TEXTURE

## Globals - RLGL

RL_LINES

RL_TRIANGLES

RL_QUADS

## Globals - RLGL

RL_UNSIGNED_BYTE

RL_FLOAT

## Globals - RLGL

RL_STREAM_DRAW

RL_STREAM_READ

RL_STREAM_COPY

RL_STATIC_DRAW

RL_STATIC_READ

RL_STATIC_COPY

RL_DYNAMIC_DRAW

RL_DYNAMIC_READ

RL_DYNAMIC_COPY

## Globals - RLGL

RL_FRAGMENT_SHADER

RL_VERTEX_SHADER

RL_COMPUTE_SHADER

## Globals - RLGL

RL_ZERO

RL_ONE

RL_SRC_COLOR

RL_ONE_MINUS_SRC_COLOR

RL_SRC_ALPHA

RL_ONE_MINUS_SRC_ALPHA

RL_DST_ALPHA

RL_ONE_MINUS_DST_ALPHA

RL_DST_COLOR

RL_ONE_MINUS_DST_COLOR

RL_SRC_ALPHA_SATURATE

RL_CONSTANT_COLOR

RL_ONE_MINUS_CONSTANT_COLOR

RL_CONSTANT_ALPHA

RL_ONE_MINUS_CONSTANT_ALPHA

## Globals - RLGL

RL_FUNC_ADD

RL_MIN

RL_MAX

RL_FUNC_SUBTRACT

RL_FUNC_REVERSE_SUBTRACT

RL_BLEND_EQUATION

RL_BLEND_EQUATION_RGB

RL_BLEND_EQUATION_ALPHA

RL_BLEND_DST_RGB

RL_BLEND_SRC_RGB

RL_BLEND_DST_ALPHA

RL_BLEND_SRC_ALPHA

RL_BLEND_COLOR

## Globals - RLGL

RL_OPENGL_11

RL_OPENGL_21

RL_OPENGL_33

RL_OPENGL_43

RL_OPENGL_ES_20

## Globals - RLGL

RL_ATTACHMENT_COLOR_CHANNEL0

RL_ATTACHMENT_COLOR_CHANNEL1

RL_ATTACHMENT_COLOR_CHANNEL2

RL_ATTACHMENT_COLOR_CHANNEL3

RL_ATTACHMENT_COLOR_CHANNEL4

RL_ATTACHMENT_COLOR_CHANNEL5

RL_ATTACHMENT_COLOR_CHANNEL6

RL_ATTACHMENT_COLOR_CHANNEL7

RL_ATTACHMENT_DEPTH

RL_ATTACHMENT_STENCIL

## Globals - RLGL

RL_ATTACHMENT_CUBEMAP_POSITIVE_X

RL_ATTACHMENT_CUBEMAP_NEGATIVE_X

RL_ATTACHMENT_CUBEMAP_POSITIVE_Y

RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y

RL_ATTACHMENT_CUBEMAP_POSITIVE_Z

RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z

RL_ATTACHMENT_TEXTURE2D

RL_ATTACHMENT_RENDERBUFFER

## Globals - RLGL

RL_CULL_FACE_FRONT

RL_CULL_FACE_BACK

## Globals - OpenGL

GL_COLOR_BUFFER_BIT

GL_DEPTH_BUFFER_BIT

GL_STENCIL_BUFFER_BIT

GL_NEAREST

GL_LINEAR

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

Check if window is currently hidden ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL.IsWindowMinimized()

Check if window is currently minimized ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL.IsWindowMaximized()

Check if window is currently maximized ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL.IsWindowFocused()

Check if window is currently focused ( only PLATFORM_DESKTOP )

- Success return bool

---

> success = RL.SetWindowMonitor( int monitor )

Set monitor for the current window (fullscreen mode)

- Failure return false
- Success return true

---

> success = RL.SetWindowPosition( Vector2 pos )

Set window position on screen

- Failure return false
- Success return true

---

> success = RL.SetWindowSize( Vector2 size )

Set window dimensions

- Failure return false
- Success return true

---

> success = RL.SetWindowMinSize( Vector2 size )

Set window minimum dimensions ( for FLAG_WINDOW_RESIZABLE )

- Failure return false
- Success return true

---

> position = RL.GetMonitorPosition( int monitor )

Get specified monitor position

- Failure return nil
- Success return Vector2

---

> size = RL.GetMonitorSize( int monitor )

Get specified monitor size

- Failure return nil
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

> success = RL.SetWindowState( int flag )

Set window configuration state using flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return false
- Success return true

---

> state = RL.IsWindowState( int flag )

Check if one specific window flag is enabled ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return nil
- Success return bool

---

> resized = RL.ClearWindowState( int flag )

Clear window configuration state flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Success return bool

---

> resized = RL.IsWindowResized()

Check if window has been resized from last frame

- Success return bool

---

> success = RL.SetWindowIcon( Image image )

Set icon for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true

---

> success = RL.SetWindowTitle( string title )

Set title for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true

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

- Failure return false
- Success return Vector2

---

> size = RL.GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Failure return false
- Success return int

---

> scale = RL.GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2

---

> name = RL.GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the monitor

- Failure return false
- Success return string

---

> RL.CloseWindow()

Close window and unload OpenGL context and free all resources

---

> success = RL.SetClipboardText( string text )

Set clipboard text content

- Failure return false
- Success return true

---

> text = RL.GetClipboardText()

Get clipboard text content

- Success return string

---

## Core - Timing

---

> success = RL.SetTargetFPS( int fps )

Set target FPS ( maximum )

- Failure return false
- Success return true

---

> FPS = RL.GetFPS()

Get current FPS

- Success return int

---

> delta = RL.GetFrameTime()

Get time in seconds for last frame drawn ( Delta time )

- Success return float

---

> time = RL.GetTime()

Get elapsed time in seconds since InitWindow()

- Success return float

---

## Core - Misc

---

> success = RL.TakeScreenshot( string fileName )

Takes a screenshot of current screen ( filename extension defines format )

- Failure return false
- Success return true

---

> success = RL.SetConfigFlags( int flags )

Setup init configuration flags ( view FLAGS )

- Failure return false
- Success return true

---

> success = RL.TraceLog( int logLevel, string text )

Show trace log messages ( LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR... )

- Failure return false
- Success return true

---

> success = RL.SetTraceLogLevel( int logLevel )

Set the current threshold ( minimum ) log level

- Failure return false
- Success return true

---

> success = RL.OpenURL( string url )

Open URL with default system browser ( If available )

- Failure return false
- Success return true

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

> success = RL.ClearBackground( Color color )

Set background color ( framebuffer clear color )

- Failure return false
- Success return true

---

> RL.BeginDrawing()

Setup canvas ( framebuffer ) to start drawing

---

> RL.EndDrawing()

End canvas drawing and swap buffers ( double buffering )

---

> success = RL.BeginBlendMode( int mode )

Begin blending mode ( BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED... )

- Failure return false
- Success return true

---

> RL.EndBlendMode()

End blending mode ( reset to default: BLEND_ALPHA )

---

> success = RL.BeginScissorMode( Rectangle rectange )

Begin scissor mode ( define screen area for following drawing )

- Failure return false
- Success return true

---

> RL.EndScissorMode()

End scissor mode

---

## Core - Shader

---

> shader = RL.LoadShader( string vsFileName, string fsFileName )

Load shader from files and bind default locations.
NOTE: Set nil if no shader

- Failure return -1
- Success return int

---

> shader = RL.LoadShaderFromMemory( string vsCode, string fsCode )

Load shader from code strings and bind default locations
NOTE: Set nil if no shader

- Failure return -1
- Success return int

---

> success = RL.BeginShaderMode( Shader shader )

Begin custom shader drawing

- Failure return false
- Success return true

---

> RL.EndShaderMode()

End custom shader drawing ( use default shader )

---

> location = RL.GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Failure return -1
- Success return int

---

> location = RL.GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Failure return -1
- Success return int

---

> success = RL.SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )

Set shader location index

- Failure return false
- Success return true

---

> location = RL.GetShaderLocationIndex( Shader shader, int shaderLocationIndex )

Get shader location index

- Failure return false
- Success return int

---

> success = RL.SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value ( matrix 4x4 )

- Failure return false
- Success return true

---

> success = RL.SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )

Set shader uniform value for texture ( sampler2d )

- Failure return false
- Success return true

---

> success = RL.SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table

- Failure return false
- Success return true

---

> success = RL.SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table

- Failure return false
- Success return true

---

> success = RL.UnloadShader( Shader shader )

Unload shader from GPU memory ( VRAM )

- Failure return false
- Success return true

---

## Core - Input-related Keyboard

---

> pressed = RL.IsKeyPressed( int key )

Detect if a key has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL.IsKeyDown( int key )

Detect if a key is being pressed

- Failure return nil
- Success return bool

---

> released = RL.IsKeyReleased( int key )

Detect if a key has been released once

- Failure return nil
- Success return bool

---

> released = RL.IsKeyUp( int key )

Check if a key is NOT being pressed

- Failure return nil
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

Set a custom key to exit program ( default is ESC )

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

- Failure return -1
- Success return string or nil

---

> scancode = RL.GetKeyScancode( int key )

This function returns the platform-specific scancode of the specified key.
If the key is KEY_UNKNOWN or does not exist on the keyboard this method will return -1.

- Failure return nil
- Success return int

---

## Core - Input-related Gamepad

---

> available = RL.IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Failure return nil
- Success return bool

---

> pressed = RL.IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL.IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Failure return nil
- Success return bool

---

> released = RL.IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Failure return nil
- Success return bool

---

> count = RL.GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Failure return false
- Success return int

---

> value = RL.GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Failure return false
- Success return float

---

> name = RL.GetGamepadName( int gamepad )

Return gamepad internal name id

- Failure return false
- Success return string

---

## Core - Input-related Mouse

---

> pressed = RL.IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL.IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Failure return nil
- Success return bool

---

> released = RL.IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Failure return nil
- Success return bool

---

> released = RL.IsMouseButtonUp( int button )

Check if a mouse button is NOT being pressed

- Failure return nil
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

> success = RL.SetMousePosition( Vector2 position )

Set mouse position XY

- Failure return false
- Success return true

---

> success = RL.SetMouseOffset( Vector2 offset )

Set mouse offset

- Failure return false
- Success return true

---

> success = RL.SetMouseScale( Vector2 scale )

Set mouse scaling

- Failure return false
- Success return true

---

> movement = RL.GetMouseWheelMove()

Returns mouse wheel movement Y

- Success return float

---

> success = RL.SetMouseCursor( int cursor )

Set mouse cursor

- Failure return false
- Success return true

---

## Core - Input-related Touch

---

> position = RL.GetTouchPosition( int index )

Get touch position XY for a touch point index ( relative to screen size )

- Failure return false
- Success return Vector2

---

> id = RL.GetTouchPointId( int index )

Get touch point identifier for given index

- Failure return false
- Success return int

---

> count = RL.GetTouchPointCount()

Get touch point identifier for given index

- Success return int

---

## Core - Input-related Gestures

---

> success = RL.SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags

- Failure return false
- Success return true

---

> detected = RL.IsGestureDetected( int gesture )

Check if a gesture have been detected

- Failure return nil
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

Return game directory ( where main.lua is located )

- Success return string

---

> fileExists = RL.FileExists( string fileName )

Check if file exists

- Failure return nil
- Success return bool

---

> dirExists = RL.DirectoryExists( string dirPath )

Check if a directory path exists

- Failure return nil
- Success return bool

---

> hasFileExtension = RL.IsFileExtension( string fileName, string ext )

Check file extension ( Including point: .png, .wav )

- Failure return nil
- Success return bool

---

> length = RL.GetFileLength( string fileName )

Get file length in bytes ( NOTE: GetFileSize() conflicts with windows.h )

- Failure return false
- Success return int

---

> extension = RL.GetFileExtension( string fileName )

Get pointer to extension for a filename string ( Includes dot: '.png' )

- Failure return false
- Success return string

---

> filePath = RL.GetFileName( string filePath )

Get pointer to filename for a path string

- Failure return false
- Success return string

---

> filePath = RL.GetFileNameWithoutExt( string filePath )

Get filename string without extension ( Uses static string )

- Failure return false
- Success return string

---

> filePath = RL.GetDirectoryPath( string filePath )

Get full path for a given fileName with path ( Uses static string )

- Failure return false
- Success return string

---

> directory = RL.GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path ( Uses static string )

- Failure return false
- Success return string

---

> directory = RL.GetWorkingDirectory()

Get current working directory ( Uses static string )

- Success return string

---

> fileNames = RL.LoadDirectoryFiles( string dirPath )

Load directory filepaths

- Failure return false
- Success return string{}

---

> fileNames = RL.LoadDirectoryFilesEx( string basePath, string filter, bool scanSubdirs )

Load directory filepaths with extension filtering and recursive directory scan

- Failure return false
- Success return string{}

---

> success = RL.ChangeDirectory( string directory )

Change working directory, return true on success

- Failure return false
- Success return true

---

> isFile = RL.IsPathFile( string path )

Check if a given path is a file or a directory

- Failure return nil
- Success return bool

---

> fileDropped = RL.IsFileDropped()

Check if a file has been dropped into window

- Success return bool

---

> files = RL.LoadDroppedFiles()

Load dropped filepaths

- Success return string{}

---

> time = RL.GetFileModTime( string fileName )

Get file modification time ( Last write time )

- Failure return false
- Success return int

---

## Core - Camera2D

---

> camera2D = RL.CreateCamera2D()

Return camera2D id set to default configuration

- Success return int

---

> success = RL.UnloadCamera2D( camera2D camera )

Unload Camera2D

- Failure return false
- Success return true

---

> success = RL.BeginMode2D( camera2D camera )

Begin 2D mode with custom camera ( 2D )

- Failure return false
- Success return true

---

> RL.EndMode2D()

Ends 2D mode with custom camera

---

> success = RL.SetCamera2DTarget( camera2D camera, Vector2 target )

Set camera target ( rotation and zoom origin )

- Failure return false
- Success return true

---

> success = RL.SetCamera2DOffset( camera2D camera, Vector2 offset )

Set camera offset ( displacement from target )

- Failure return false
- Success return true

---

> success = RL.SetCamera2DRotation( camera2D camera, float rotation )

Set camera rotation in degrees

- Failure return false
- Success return true

---

> success = RL.SetCamera2DZoom( camera2D camera, float zoom )

Set camera zoom ( scaling ), should be 1.0f by default

- Failure return false
- Success return true

---

> target = RL.GetCamera2DTarget( camera2D camera )

Get camera2D target

- Failure return nil
- Success return Vector2

---

> offset = RL.GetCamera2DOffset( camera2D camera )

Get camera2D offset

- Failure return nil
- Success return Vector2

---

> rotation = RL.GetCamera2DRotation( camera2D camera )

Get camera2D rotation

- Failure return nil
- Success return float

---

> zoom = RL.GetCamera2DZoom( camera2D camera )

Get camera2D zoom

- Failure return nil
- Success return float

---

## Core - Camera3D

---

> camera = RL.CreateCamera3D()

Return camera3D id set to default configuration

- Success return int

---

> success = RL.UnloadCamera3D( int Camera3D )

Unload Camera3D

- Failure return false
- Success return true

---

> success = RL.BeginMode3D( camera3D camera )

Begin 3D mode with custom camera ( 3D )

- Failure return false
- Success return true

---

> RL.EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode

---

> success = RL.SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position ( Remember to call "RL.UpdateCamera3D()" to apply changes )

- Failure return false
- Success return true

---

> success = RL.SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at

- Failure return false
- Success return true

---

> success = RL.SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector ( Rotation over it's axis )

- Failure return false
- Success return true

---

> success = RL.SetCamera3DFovy( camera3D camera, float fovy )

Set camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return false
- Success return true

---

> success = RL.SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode ( CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC )

- Failure return false
- Success return true

---

> position = RL.GetCamera3DPosition( camera3D camera )

Get camera position

- Failure return nil
- Success return Vector3

---

> target = RL.GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Failure return nil
- Success return Vector3

---

> up = RL.GetCamera3DUp( camera3D camera )

Get camera up vector ( Rotation over it's axis )

- Failure return nil
- Success return Vector3

---

> fovy = RL.GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return nil
- Success return float

---

> projection = RL.GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Failure return nil
- Success return int

---

> forward = RL.GetCamera3DForward( camera3D camera )

Returns the cameras forward vector ( normalized )

- Failure return nil
- Success return Vector3

---

> up = RL.GetCamera3DUpNormalized( camera3D camera )

Returns the cameras up vector ( normalized )
Note: The up vector might not be perpendicular to the forward vector

- Failure return nil
- Success return Vector3

---

> right = RL.GetCamera3DRight( camera3D camera )

Returns the cameras right vector ( normalized )

- Failure return nil
- Success return Vector3

---

> success = RL.Camera3DMoveForward( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera in it's forward direction

- Failure return false
- Success return true

---

> success = RL.Camera3DMoveUp( camera3D camera, float distance )

Moves the camera in it's up direction

- Failure return false
- Success return true

---

> success = RL.Camera3DMoveRight( camera3D camera, float distance, bool moveInWorldPlane )

Moves the camera target in it's current right direction

- Failure return false
- Success return true

---

> success = RL.Camera3DMoveToTarget( camera3D camera, float delta )

Moves the camera position closer/farther to/from the camera target

- Failure return false
- Success return true

---

> success = RL.Camera3DYaw( camera3D camera, float angle, bool rotateAroundTarget )

Rotates the camera around it's up vector
Yaw is "looking left and right"
If rotateAroundTarget is false, the camera rotates around it's position
Note: angle must be provided in radians

- Failure return false
- Success return true

---

> success = RL.Camera3DPitch( camera3D camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp )

Rotates the camera around it's right vector, pitch is "looking up and down"
 - lockView prevents camera overrotation (aka "somersaults")
 - rotateAroundTarget defines if rotation is around target or around it's position
 - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
NOTE: angle must be provided in radians

- Failure return false
- Success return true

---

> success = RL.Camera3DRoll( camera3D camera, float angle )

Rotates the camera around it's forward vector
Roll is "turning your head sideways to the left or right"
Note: angle must be provided in radians

- Failure return false
- Success return true

---

> view = RL.GetCamera3DViewMatrix( camera3D camera )

Returns the camera view matrix

- Failure return false
- Success return Matrix

---

> projection = RL.GetCamera3DProjectionMatrix( camera3D camera, float aspect )

Returns the camera projection matrix

- Failure return false
- Success return Matrix

---

> success = RL.UpdateCamera3D( camera3D camera, int mode )

Update camera position for selected mode

- Failure return false
- Success return true

---

> success = RL.UpdateCamera3DPro( camera3D camera, Vector3 movement, Vector3 rotation, float zoom )

Update camera movement, movement/rotation values should be provided by user

- Failure return false
- Success return true

---

## Core - Screen-space

---

> ray = RL.GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Failure return false
- Success return Ray

---

> matrix = RL.GetCameraMatrix( Camera3D camera )

Get camera transform matrix ( view matrix )

- Failure return false
- Success return Matrix

---

> matrix = RL.GetCameraMatrix2D( Camera2D camera )

Get camera 2d transform matrix

- Failure return false
- Success return Matrix

---

> position = RL.GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Failure return false
- Success return Vector2

---

> position = RL.GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )

Get size position for a 3d world space position

- Failure return false
- Success return Vector2

---

> position = RL.GetWorldToScreen2D( Vector2 position, Camera2D camera )

Get the screen space position for a 2d camera world space position

- Failure return false
- Success return Vector2

---

> position = RL.GetScreenToWorld2D( Vector2 position, Camera2D camera )

Get the world space position for a 2d camera screen space position

- Failure return false
- Success return Vector2

---

## Shapes - Drawing

---

> success = RL.SetShapesTexture( Texture2D texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

- Failure return false
- Success return true

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

Load image from file into CPU memory ( RAM )

- Failure return -1
- Success return int

---

> image = RL.LoadImageFromTexture( Texture2D texture )

Load image from GPU texture data

- Failure return -1
- Success return int

---

> image = RL.LoadImageFromScreen()

Load image from screen buffer and ( screenshot )

- Success return int

---

> success = RL.UnloadImage( Image image )

Unload image from CPU memory ( RAM )

- Failure return false
- Success return true

---

> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Failure return nil
- Success return bool

---

> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Failure return nil
- Success return bool

---

## Textures - Image Generation

---

> image = RL.GenImageColor( int width, int height, Color color )

Generate image: plain color

- Failure return -1
- Success return int

---

> image = RL.GenImageGradientV( Vector2 size, Color top, Color bottom )

Generate image: vertical gradient

- Failure return -1
- Success return int

---

> image = RL.GenImageGradientH( Vector2 size, Color left, Color right )

Generate image: horizontal gradient

- Failure return -1
- Success return int

---

> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Failure return -1
- Success return int

---

> image = RL.GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Failure return -1
- Success return int

---

> image = RL.GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Failure return -1
- Success return int

---

> image = RL.GenImagePerlinNoise( Vector2 size, Vector2 offset, float factor )

Generate image: perlin noise

- Failure return -1
- Success return int

---

> image = RL.GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Failure return -1
- Success return int

---

> image = RL.GenImageText( Vector2 size, string text )

Generate image: grayscale image from text data

- Failure return -1
- Success return int

---

## Textures - Image Manipulation Functions

---

> image = RL.ImageCopy( Image image )

Create an image duplicate ( useful for transformations )

- Failure return -1
- Success return int

---

> image = RL.ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Failure return -1
- Success return int

---

> image = RL.ImageText( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text ( custom sprite font )

- Failure return -1
- Success return int

---

> success = RL.ImageFormat( Image image, int newFormat )

Convert image data to desired format

- Failure return false
- Success return true

---

> success = RL.ImageToPOT( Image image, Color fill )

Convert image to POT ( power-of-two )

- Failure return false
- Success return true

---

> success = RL.ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle

- Failure return false
- Success return true

---

> success = RL.ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value

- Failure return false
- Success return true

---

> success = RL.ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color

- Failure return false
- Success return true

---

> success = RL.ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image

- Failure return false
- Success return true

---

> success = RL.ImageAlphaPremultiply( Image image )

Premultiply alpha channel

- Failure return false
- Success return true

---

> success = RL.ImageResize( Image image, Vector2 size )

Resize image ( Bicubic scaling algorithm )

- Failure return false
- Success return true

---

> success = RL.ImageResizeNN( Image image, Vector2 size )

Resize image ( Nearest-Neighbor scaling algorithm )

- Failure return false
- Success return true

---

> success = RL.ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color

- Failure return false
- Success return true

---

> success = RL.ImageMipmaps( Image image )

Generate all mipmap levels for a provided image

- Failure return false
- Success return true

---

> success = RL.ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower ( Floyd-Steinberg dithering )

- Failure return false
- Success return true

---

> success = RL.ImageFlipVertical( Image image )

Flip image vertically

- Failure return false
- Success return true

---

> success = RL.ImageFlipHorizontal( Image image )

Flip image horizontally

- Failure return false
- Success return true

---

> success = RL.ImageRotateCW( Image image )

Rotate image clockwise 90deg

- Failure return false
- Success return true

---

> success = RL.ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg

- Failure return false
- Success return true

---

> success = RL.ImageColorTint( Image image, Color color )

Modify image color: tint

- Failure return false
- Success return true

---

> success = RL.ImageColorInvert( Image image )

Modify image color: invert

- Failure return false
- Success return true

---

> success = RL.ImageColorGrayscale( Image image )

Modify image color: grayscale

- Failure return false
- Success return true

---

> success = RL.ImageColorContrast( Image image, float contrast )

Modify image color: contrast ( -100 to 100 )

- Failure return false
- Success return true

---

> success = RL.ImageColorBrightness( Image image, int brightness )

Modify image color: brightness ( -255 to 255 )

- Failure return false
- Success return true

---

> success = RL.ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color

- Failure return false
- Success return true

---

> colors = RL.LoadImageColors( Image image )

Load color data from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}

---

> colors = RL.LoadImagePalette( Image image, int maxPaletteSize )

Load colors palette from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}

---

> rectangle = RL.GetImageAlphaBorder( Image image, float threshold )

Get image alpha border rectangle

- Failure return false
- Success return Rectangle

---

> color = RL.GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at ( x, y ) position

- Failure return false
- Success return Color

---

## Textures - Image Drawing

---

> success = RL.ImageClearBackground( Image dst, Color color )

Clear image background with given color

- Failure return false
- Success return true

---

> success = RL.ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image

- Failure return false
- Success return true

---

> success = RL.ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )

Draw line within an image

- Failure return false
- Success return true

---

> success = RL.ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image

- Failure return false
- Success return true

---

> success = RL.ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image

- Failure return false
- Success return true

---

> success = RL.ImageDrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image

- Failure return false
- Success return true

---

> success = RL.ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image ( Tint applied to source )

- Failure return false
- Success return true

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

- Failure return nil
- Success return Vector2

---

> mipmaps = RL.GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

> format = RL.GetImageFormat( Image image )

Get image data format ( PixelFormat type )

- Failure return false
- Success return int

---

## Textures - Texture Loading

---

> texture = RL.LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return -1
- Success return int

---

> texture = RL.LoadTextureFromImage( Image image )

Load texture from image data

- Failure return -1
- Success return int

---

> texture = RL.LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Failure return -1
- Success return int

---

> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering ( framebuffer )

- Failure return -1
- Success return int

---

> success = RL.UnloadTexture( Texture2D texture )

Unload texture from GPU memory ( VRAM ). NOTE! Must be texture id.

- Failure return false
- Success return true

---

> isReady = RL.IsTextureReady( Texture2D texture )

Check if a texture is ready

- Failure return nil
- Success return true

---

> success = RL.UpdateTexture( Texture2D texture, int{} pixels )

Update GPU texture with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true

---

> success = RL.UpdateTextureRec( Texture2D texture, Rectangle rec, int{} pixels )

Update GPU texture rectangle with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true

---

## Textures - Texture Drawing

---

> success = RL.DrawTexture( Texture2D texture, Vector2 position, Color tint )

Draw a Texture2D

- Failure return false
- Success return true

---

> success = RL.DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle

- Failure return false
- Success return true

---

> success = RL.DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters

- Failure return false
- Success return true

---

> success = RL.DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture ( or part of it ) that stretches or shrinks nicely

- Failure return false
- Success return true

---

> success = RL.BeginTextureMode( RenderTexture2D target )

Begin drawing to render texture

- Failure return false
- Success return true

---

> RL.EndTextureMode()

Ends drawing to render texture

---

> type = RL.GetTextureType( Texture2D texture )

Get texture type ( TEXTURE_TYPE_TEXTURE or TEXTURE_TYPE_RENDER_TEXTURE )

- Failure return false
- Success return int

---

## Textures - Texture Configuration

---

> success = RL.GenTextureMipmaps( Texture2D texture )

Generate GPU mipmaps for a texture

- Failure return false
- Success return true

---

> success = RL.SetTextureFilter( Texture2D texture, int filter )

Set texture scaling filter mode ( TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR... )

- Failure return false
- Success return true

---

> success = RL.SetTextureWrap( Texture2D texture, int wrap )

Set texture wrapping mode ( TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP... )

- Failure return false
- Success return true

---

> id = RL.GetTextureId( Texture2D texture )

Get texture OpenGL id

- Failure return false
- Success return int

---

> size = RL.GetTextureSize( Texture2D texture )

Get texture size

- Failure return false
- Success return Vector2

---

> mipmaps = RL.GetTextureMipmaps( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

> format = RL.GetTextureFormat( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

## Textures - Color/pixel

---

> color = RL.Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color

---

> value = RL.ColorToInt( Color color )

Returns hexadecimal value for a Color

- Failure return false
- Success return int

---

> color = RL.ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Failure return false
- Success return Vector4

---

> color = RL.ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Failure return false
- Success return Color

---

> HSV = RL.ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Vector3

---

> color = RL.ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Color

---

> color = RL.ColorTint( Color color, Color tint )

Get color multiplied with another color

- Failure return false
- Success return Color

---

> color = RL.ColorBrightness( Color color, float factor )

Get color with brightness correction, brightness factor goes from -1.0f to 1.0f

- Failure return false
- Success return Color

---

> color = RL.ColorContrast( Color color, float contrast )

Get color with contrast correction, contrast values between -1.0f and 1.0f

- Failure return false
- Success return Color

---

> color = RL.ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color

---

> color = RL.ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Failure return false
- Success return Color

---

> color = RL.GetColor( unsigned int hexValue )

Get Color structure from hexadecimal value

- Failure return false
- Success return Color

---

> color = RL.GetPixelColor( Texture2D texture, Vector2 position )

Get pixel color from source texture

- Failure return false
- Success return Color

---

> size = RL.GetPixelDataSize( int width, int height, int format )

Get pixel data size in bytes for certain format

- Failure return false
- Success return int

---

## Text - Loading

---

> font = RL.LoadFont( string fileName )

Load font from file into GPU memory ( VRAM )

- Failure return -1
- Success return int

---

> font = RL.LoadFontEx( string fileName, int fontSize )

Load font from file with extended parameters. Loading the default character set

- Failure return -1
- Success return int

---

> font = RL.LoadFontFromImage( Image image, Color key, int firstChar )

Load font from Image ( XNA style )

- Failure return -1
- Success return int

---

> success = RL.UnloadFont( Font font )

Unload Font from GPU memory ( VRAM )

- Failure return false
- Success return true

---

## Text - Draw

---

> success = RL.DrawFPS( Vector2 pos )

Draw current FPS

- Failure return false
- Success return true

---

> success = RL.DrawText( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters

- Failure return false
- Success return true

---

> success = RL.DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters ( rotation )

- Failure return false
- Success return true

---

## Text - Misc

---

> size = RL.MeasureText( Font font, string text, float fontSize, float spacing )

Measure string size for Font

- Failure return false
- Success return Vector2

---

> baseSize = RL.GetFontBaseSize( Font font )

Get font baseSize

- Failure return false
- Success return int

---

> glyphCount = RL.GetFontGlyphCount( Font font )

Get font glyphCount

- Failure return false
- Success return int

---

> glyphPadding = RL.GetFontGlyphPadding( Font font )

Get font glyphPadding

- Failure return false
- Success return int

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

> success = RL.DrawQuad3DTexture( Texture2D texture, Vector3{} vertices, Vector2{} texCoords, Color{} colors )

Draw 3D textured quad. ( Texture coordinates opengl style 0.0 - 1.0 ).

- Failure return false
- Success return true

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

> success = RL.SetMaterialTexture( Material material, int mapType, Texture2D texture )

Set texture for a material map type ( MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS... )

- Failure return false
- Success return true

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

> success = RL.SetMaterialShader( Material material, Shader shader )

Set shader for material

- Failure return false
- Success return true

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
- Success return int

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

> success = RL.DrawBillboard( Camera3D camera, Texture2D texture, Vector3 position, float size, Color tint )

Draw a billboard texture

- Failure return false
- Success return true

---

> success = RL.DrawBillboardRec( Camera3D camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint )

Draw a billboard texture defined by source

- Failure return false
- Success return true

---

> success = RL.DrawBillboardPro( Camera3D camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint )

Draw a billboard texture defined by source and rotation

- Failure return false
- Success return true

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

> result = RL.Lerp( float start, float end, float amount )

Calculate linear interpolation between two floats

- Failure return false
- Success return float

---

> result = RL.Normalize( float value, float start, float end )

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

> result = RL.Vector2LineAngle( Vector2 start, Vector2 end )

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

> success = RL.GuiSetFont( Font font )

Set gui custom font ( global state )

- Failure return false
- Success return true

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

> success = RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader

- Failure return false
- Success return true

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

## RLGL - Initialization functions

---

> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int

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

## OpenGL - Framebuffer management

---

> success = RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use -1 RenderTexture for window framebuffer.

- Failure return false
- Success return true

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
