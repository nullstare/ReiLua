# ReiLua API

## Usage

Application needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where "main.lua" is located can be given as argument. There are three global Lua functions that the engine will call, 'init', 'process' and 'draw'.

---
> function init()

This function will be called first when 'main.lua' is found

---

> function process( delta )

This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'

---

> function draw()

This function will be called every frame after process and it should have all rendering related functions.
Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it.
You can still use RL_BeginDrawing() and RL_EndDrawing() manually from anywhere.

---

> function log( message )

This function can be used for custom log message handling.

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

BLEND_CUSTOM

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

## Globals - TextureModes

TEXTURE_SOURCE_TEXTURE

TEXTURE_SOURCE_RENDER_TEXTURE

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

GUI_STATE_NORMAL

GUI_STATE_FOCUSED

GUI_STATE_PRESSED

GUI_STATE_DISABLED

## Globals - GuiTextAlignment

GUI_TEXT_ALIGN_LEFT

GUI_TEXT_ALIGN_CENTER

GUI_TEXT_ALIGN_RIGHT

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

> Texture = TextureId

int id. Texture type (multiple internal formats supported). NOTE: Data stored in GPU memory (VRAM)

---

> RenderTexture = RenderTextureId

int id. RenderTexture type, for texture rendering

---

> Font = FontId

int id. Font type, includes texture and chars data

---

> Camera = CameraId

int id. Defines 3d camera position/orientation

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

> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } }

{ min, max }. Bounding box type for 3d mesh

---

> Sound = SoundId

int id. Basic Sound source and buffer

---

> NPatchInfo = { { 0, 0, 24, 24 }, 0, 0, 0, 0, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 0, top = 0, right = 0, bottom = 0, layout = NPATCH_NINE_PATCH }

{ Rectangle source, int left, int top, int right, int bottom, int layout }.
{ Texture source rectangle, Left border offset, Top border offset, Right border offset, Bottom border offset, Layout of the n-patch: 3x3, 1x3 or 3x1 }

---

> ModelAnimations = ModelAnimationsId

int id. ModelAnimations

---

## Core - Window

---

> state = RL_IsWindowReady()

Check if window has been initialized successfully

- Success return bool

---

> state = RL_IsWindowFullscreen()

Check if window is currently fullscreen

- Success return bool

---

> state = RL_IsWindowHidden()

Check if window is currently hidden ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL_IsWindowMinimized()

Check if window is currently minimized ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL_IsWindowMaximized()

Check if window is currently maximized ( only PLATFORM_DESKTOP )

- Success return bool

---

> state = RL_IsWindowFocused()

Check if window is currently focused ( only PLATFORM_DESKTOP )

- Success return bool

---

> success = RL_SetWindowMonitor( int monitor )

Set monitor for the current window (fullscreen mode)

- Failure return false
- Success return true

---

> success = RL_SetWindowPosition( Vector2 pos )

Set window position on screen

- Failure return false
- Success return true

---

> success = RL_SetWindowSize( Vector2 size )

Set window dimensions

- Failure return false
- Success return true

---

> success = RL_SetWindowMinSize( Vector2 size )

Set window minimum dimensions ( for FLAG_WINDOW_RESIZABLE )

- Failure return false
- Success return true

---

> position = RL_GetMonitorPosition( int monitor )

Get specified monitor position

- Failure return nil
- Success return Vector2

---

> size = RL_GetMonitorSize( int monitor )

Get specified monitor size

- Failure return nil
- Success return Vector2

---

> position = RL_GetWindowPosition()

Get window position on monitor

- Success return Vector2

---

> size = RL_GetWindowPosition()

Get window size

- Success return Vector2

---

> success = RL_SetWindowState( int flag )

Set window configuration state using flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return false
- Success return true

---

> state = RL_IsWindowState( int flag ) )

Check if one specific window flag is enabled ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Failure return nil
- Success return bool

---

> resized = RL_ClearWindowState( int flag )

Clear window configuration state flags ( FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE... )

- Success return bool

---

> resized = RL_IsWindowResized()

Check if window has been resized from last frame

- Success return bool

---

> success = RL_SetWindowIcon( Image image )

Set icon for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true

---

> success = RL_SetWindowTitle( string title )

Set title for window ( Only PLATFORM_DESKTOP )

- Failure return false
- Success return true

---

> count = RL_GetMonitorCount()

Get number of connected monitors

- Success return int

---

> monitor = RL_GetCurrentMonitor()

Get current connected monitor

- Success return int

---

> size = RL_GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Failure return false
- Success return Vector2

---

> size = RL_GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Failure return false
- Success return int

---

> scale = RL_GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2

---

> name = RL_GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the monitor

- Failure return false
- Success return string

---

> RL_CloseWindow()

Close window and unload OpenGL context and free all resources

---

> success = RL_SetClipboardText( string text )

Set clipboard text content

- Failure return false
- Success return true

---

> text = RL_GetClipboardText()

Get clipboard text content

- Success return string

---

## Core - Timing

---

> success = RL_SetTargetFPS( int fps )

Set target FPS ( maximum )

- Failure return false
- Success return true

---

> FPS = RL_GetFPS()

Get current FPS

- Success return int

---

> delta = RL_GetFrameTime()

Get time in seconds for last frame drawn ( Delta time )

- Success return float

---

> time = RL_GetTime()

Get elapsed time in seconds since InitWindow()

- Success return float

---

## Core - Misc

---

> success = RL_TakeScreenshot( string fileName )

Takes a screenshot of current screen ( filename extension defines format )

- Failure return false
- Success return true

---

> success = RL_SetConfigFlags( int flags )

Setup init configuration flags ( view FLAGS )

- Failure return false
- Success return true

---

> success = RL_TraceLog( int logLevel, string text )

Show trace log messages ( LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR... )

- Failure return false
- Success return true

---

> success = RL_SetTraceLogLevel( int logLevel )

Set the current threshold ( minimum ) log level

- Failure return false
- Success return true

---

> success = RL_OpenURL( string url )

Open URL with default system browser ( If available )

- Failure return false
- Success return true

---

## Core - Cursor

---

> RL_ShowCursor()

Shows cursor

---

> RL_HideCursor()

Hides cursor

---

> hidden = RL_IsCursorHidden()

Check if cursor is not visible

- Success return bool

---

> RL_EnableCursor()

Enables cursor (unlock cursor)

---

> RL_DisableCursor()

Disables cursor (lock cursor)

---

> onSreen = RL_IsCursorOnScreen()

Check if cursor is on the screen

- Success return bool

---

## Core - Drawing

---

> success = RL_ClearBackground( Color color )

Set background color ( framebuffer clear color )

- Failure return false
- Success return true

---

> RL_BeginDrawing()

Setup canvas ( framebuffer ) to start drawing

---

> RL_EndDrawing()

End canvas drawing and swap buffers ( double buffering )

---

> success = RL_BeginBlendMode( int mode )

Begin blending mode ( BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED... )

- Failure return false
- Success return true

---

> RL_EndBlendMode()

End blending mode ( reset to default: BLEND_ALPHA )

---

> success = RL_BeginScissorMode( Rectangle rectange )

Begin scissor mode ( define screen area for following drawing )

- Failure return false
- Success return true

---

> RL_EndScissorMode()

End scissor mode

---

## Core - Shader

---

> shader = RL_LoadShader( string vsFileName, string fsFileName )

Load shader from files and bind default locations.
NOTE: Set nil if no shader

- Failure return -1
- Success return int

---

> shader = RL_LoadShaderFromMemory( string vsCode, string fsCode )

Load shader from code strings and bind default locations
NOTE: Set nil if no shader

- Failure return -1
- Success return int

---

> success = RL_BeginShaderMode( Shader shader )

Begin custom shader drawing

- Failure return false
- Success return true

---

> EndShaderMode()

End custom shader drawing ( use default shader )

---

> location = RL_GetShaderLocation( Shader shader, string uniformName )

Get shader uniform location

- Failure return -1
- Success return int

---

> location = RL_GetShaderLocationAttrib( Shader shader, string attribName )

Get shader attribute location

- Failure return -1
- Success return int

---

> success = RL_SetShaderLocationIndex( Shader shader, int shaderLocationIndex, int location )

Set shader location index

- Failure return false
- Success return true

---

> location = RL_GetShaderLocationIndex( Shader shader, int shaderLocationIndex )

Get shader location index

- Failure return false
- Success return int

---

> success = RL_SetShaderValueMatrix( Shader shader, int locIndex, Matrix mat )

Set shader uniform value ( matrix 4x4 )

- Failure return false
- Success return true

---

> success = RL_SetShaderValueTexture( Shader shader, int locIndex, Texture2D texture )

Set shader uniform value for texture ( sampler2d )

- Failure return false
- Success return true

---

> success = RL_SetShaderValue( Shader shader, int locIndex, number{} values, int uniformType )

Set shader uniform value
NOTE: Even one value should be in table

- Failure return false
- Success return true

---

> success = RL_SetShaderValueV( Shader shader, int locIndex, number{} values, int uniformType, int count )

Set shader uniform value vector
NOTE: Even one value should be in table

- Failure return false
- Success return true

---

> success = RL_UnloadShader( Shader shader )

Unload shader from GPU memory ( VRAM )

- Failure return false
- Success return true

---

## Core - Input-related Keyboard

---

> pressed = RL_IsKeyPressed( int key )

Detect if a key has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL_IsKeyDown( int key )

Detect if a key is being pressed

- Failure return nil
- Success return bool

---

> released = RL_IsKeyReleased( int key )

Detect if a key has been released once

- Failure return nil
- Success return bool

---

> released = RL_IsKeyUp( int key )

Check if a key is NOT being pressed

- Failure return nil
- Success return bool

---

> keycode = RL_GetKeyPressed()

Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty

- Success return int

---

> unicode = RL_GetCharPressed()

Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

- Success return int

---

> RL_SetExitKey( int key )

Set a custom key to exit program ( default is ESC )

---

## Core - Input-related Gamepad

---

> available = RL_IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Failure return nil
- Success return bool

---

> pressed = RL_IsGamepadButtonPressed( int gamepad, int button )

Detect if a gamepad button has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL_IsGamepadButtonDown( int gamepad, int button )

Detect if a gamepad button is being pressed

- Failure return nil
- Success return bool

---

> released = RL_IsGamepadButtonReleased( int gamepad, int button )

Detect if a gamepad button has been released once

- Failure return nil
- Success return bool

---

> count = RL_GetGamepadAxisCount( int gamepad )

Return gamepad axis count for a gamepad

- Failure return false
- Success return int

---

> value = RL_GetGamepadAxisMovement( int gamepad, int axis )

Return axis movement value for a gamepad axis

- Failure return false
- Success return float

---

> name = RL_GetGamepadName( int gamepad )

Return gamepad internal name id

- Failure return false
- Success return string

---

## Core - Input-related Mouse

---

> pressed = RL_IsMouseButtonPressed( int button )

Detect if a mouse button has been pressed once

- Failure return nil
- Success return bool

---

> pressed = RL_IsMouseButtonDown( int button )

Detect if a mouse button is being pressed

- Failure return nil
- Success return bool

---

> released = RL_IsMouseButtonReleased( int button )

Detect if a mouse button has been released once

- Failure return nil
- Success return bool

---

> released = RL_IsMouseButtonUp( int button )

Check if a mouse button is NOT being pressed

- Failure return nil
- Success return bool

---

> position = RL_GetMousePosition()

Returns mouse position

- Success return Vector2

---

> position = RL_GetMouseDelta()

Get mouse delta between frames

- Success return Vector2

---

> success = RL_SetMousePosition( Vector2 position )

Set mouse position XY

- Failure return false
- Success return true

---

> success = RL_SetMouseOffset( Vector2 offset )

Set mouse offset

- Failure return false
- Success return true

---

> success = RL_SetMouseScale( Vector2 scale )

Set mouse scaling

- Failure return false
- Success return true

---

> movement = RL_GetMouseWheelMove()

Returns mouse wheel movement Y

- Success return float

---

> success = RL_SetMouseCursor( int cursor )

Set mouse cursor

- Failure return false
- Success return true

---

## Core - Input-related Touch

---

> position = RL_GetTouchPosition( int index )

Get touch position XY for a touch point index ( relative to screen size )

- Failure return false
- Success return Vector2

---

> id = RL_GetTouchPointId( int index )

Get touch point identifier for given index

- Failure return false
- Success return int

---

> count = RL_GetTouchPointCount()

Get touch point identifier for given index

- Success return int

---

## Core - Input-related Gestures

---

> success = RL_SetGesturesEnabled( unsigned int flags )

Enable a set of gestures using flags

- Failure return false
- Success return true

---

> detected = RL_IsGestureDetected( int gesture )

Check if a gesture have been detected

- Failure return nil
- Success return bool

---

> gesture = RL_GetGestureDetected()

Get latest detected gesture

- Success return int

---

> time = RL_GetGestureHoldDuration()

Get gesture hold time in milliseconds

- Success return float

---

> vector = RL_GetGestureDragVector()

Get gesture drag vector

- Success return Vector2

---

> angle = RL_GetGestureDragAngle()

Get gesture drag angle

- Success return float

---

> vector = RL_GetGesturePinchVector()

Get gesture pinch delta

- Success return Vector2

---

> angle = RL_GetGesturePinchAngle()

Get gesture pinch angle

- Success return float

---

## Core - File

---

> path = RL_GetBasePath()

Return game directory ( where main.lua is located )

- Success return string

---

> fileExists = RL_FileExists( string fileName )

Check if file exists

- Failure return nil
- Success return bool

---

> dirExists = RL_DirectoryExists( string dirPath )

Check if a directory path exists

- Failure return nil
- Success return bool

---

> hasFileExtension = RL_IsFileExtension( string fileName, string ext )

Check file extension ( Including point: .png, .wav )

- Failure return nil
- Success return bool

---

> extension = RL_GetFileExtension( string fileName )

Get pointer to extension for a filename string ( Includes dot: '.png' )

- Failure return false
- Success return string

---

> filePath = RL_GetFileName( string filePath )

Get pointer to filename for a path string

- Failure return false
- Success return string

---

> filePath = RL_GetFileNameWithoutExt( string filePath )

Get filename string without extension ( Uses static string )

- Failure return false
- Success return string

---

> filePath = RL_GetDirectoryPath( string filePath )

Get full path for a given fileName with path ( Uses static string )

- Failure return false
- Success return string

---

> directory = RL_GetPrevDirectoryPath( string dirPath )

Get previous directory path for a given path ( Uses static string )

- Failure return false
- Success return string

---

> directory = RL_GetWorkingDirectory()

Get current working directory ( Uses static string )

- Success return string

---

> fileNames = RL_GetDirectoryFiles( string dirPath )

Get filenames in a directory path

- Failure return false
- Success return string{}

---

> success = RL_ChangeDirectory( string directory )

Change working directory, return true on success

- Failure return false
- Success return true

---

> fileDropped = RL_IsFileDropped()

Check if a file has been dropped into window

- Success return bool

---

> files = RL_GetDroppedFiles()

Get dropped files names

- Success return string{}

---

> time = RL_GetFileModTime( string fileName )

Get file modification time ( Last write time )

- Failure return false
- Success return int

---

## Core - Camera2D

---

> camera2D = RL_CreateCamera2D()

Return camera2D id set to default configuration

- Success return int

---

> success = RL_UnloadCamera2D( int Camera2D )

Unload Camera2D

- Failure return false
- Success return true

---

> success = RL_BeginMode2D( camera2D camera )

Begin 2D mode with custom camera ( 2D )

- Failure return false
- Success return true

---

> RL_EndMode2D()

Ends 2D mode with custom camera

---

> success = RL_SetCamera2DTarget( camera2D camera, Vector2 target )

Set camera target ( rotation and zoom origin )

- Failure return false
- Success return true

---

> success = RL_SetCamera2DOffset( camera2D camera, Vector2 offset )

Set camera offset ( displacement from target )

- Failure return false
- Success return true

---

> success = RL_SetCamera2DRotation( camera3D camera, float rotation )

Set camera rotation in degrees

- Failure return false
- Success return true

---

> success = RL_SetCamera2DZoom( camera3D camera, float zoom )

Set camera zoom ( scaling ), should be 1.0f by default

- Failure return false
- Success return true

---

> target = RL_GetCamera2DTarget( camera2D camera )

Get camera2D target

- Failure return nil
- Success return Vector2

---

> offset = RL_GetCamera2DOffset( camera2D camera )

Get camera2D offset

- Failure return nil
- Success return Vector2

---

> rotation = RL_GetCamera2DRotation( camera2D camera )

Get camera2D rotation

- Failure return nil
- Success return float

---

> zoom = RL_GetCamera2DZoom( camera2D camera )

Get camera2D zoom

- Failure return nil
- Success return float

---

## Core - Camera3D

---

> camera = RL_CreateCamera3D()

Return camera3D id set to default configuration

- Success return int

---

> success = RL_UnloadCamera3D( int Camera3D )

Unload Camera3D

- Failure return false
- Success return true

---

> success = RL_BeginMode3D( camera3D camera )

Begin 3D mode with custom camera ( 3D )

- Failure return false
- Success return true

---

> RL_EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode

---

> success = RL_SetCamera3DPosition( camera3D camera, Vector3 position )

Set camera position ( Remember to call "RL_UpdateCamera3D()" to apply changes )

- Failure return false
- Success return true

---

> success = RL_SetCamera3DTarget( camera3D camera, Vector3 target )

Set camera target it looks-at

- Failure return false
- Success return true

---

> success = RL_SetCamera3DUp( camera3D camera, Vector3 up )

Set camera up vector ( Rotation over it's axis )

- Failure return false
- Success return true

---

> success = RL_SetCamera3DFovy( camera3D camera, float fovy )

Set camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return false
- Success return true

---

> success = RL_SetCamera3DProjection( camera3D camera, int projection )

Set camera projection mode ( CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC )

- Failure return false
- Success return true

---

> success = RL_SetCameraMode( camera3D camera, int mode )

Set camera mode ( CAMERA_CUSTOM, CAMERA_FREE, CAMERA_ORBITAL... )

- Failure return false
- Success return true

---

> position = RL_GetCamera3DPosition( camera3D camera )

Get camera position

- Failure return nil
- Success return Vector3

---

> target = RL_GetCamera3DTarget( camera3D camera )

Get camera target it looks-at

- Failure return nil
- Success return Vector3

---

> up = RL_GetCamera3DUp( camera3D camera )

Get camera up vector ( Rotation over it's axis )

- Failure return nil
- Success return Vector3

---

> fovy = RL_GetCamera3DFovy( camera3D camera )

Get camera field-of-view apperture in Y ( degrees ) in perspective, used as near plane width in orthographic

- Failure return nil
- Success return float

---

> projection = RL_GetCamera3DProjection( camera3D camera )

Get camera projection mode

- Failure return nil
- Success return int

---

> success = RL_UpdateCamera3D( camera3D camera )

Update camera position for selected mode

- Failure return false
- Success return true

---

> success = RL_SetCameraPanControl( int keyPan )

Set camera pan key to combine with mouse movement ( free camera )

- Failure return false
- Success return true

---

> success = RL_SetCameraAltControl( int keyAlt )

Set camera alt key to combine with mouse movement ( free camera )

- Failure return false
- Success return true

---

> success = RL_SetCameraSmoothZoomControl( int keySmoothZoom )

Set camera smooth zoom key to combine with mouse ( free camera )

- Failure return false
- Success return true

---

> success = RL_SetCameraMoveControls( int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown )

Set camera move controls ( 1st person and 3rd person cameras )

- Failure return false
- Success return true

---

## Core - Screen-space

---

> ray = RL_GetMouseRay( Vector2 mousePosition, Camera3D camera )

Get a ray trace from mouse position

- Failure return false
- Success return Ray

---

> matrix = RL_GetCameraMatrix( Camera3D camera )

Get camera transform matrix ( view matrix )

- Failure return false
- Success return Matrix

---

> matrix = RL_GetCameraMatrix2D( Camera2D camera )

Get camera 2d transform matrix

- Failure return false
- Success return Matrix

---

> position = RL_GetWorldToScreen( Vector3 position, Camera3D camera )

Get the screen space position for a 3d world space position

- Failure return false
- Success return Vector2

---

> position = RL_GetWorldToScreenEx( Vector3 position, Camera3D camera, Vector2 size )

Get size position for a 3d world space position

- Failure return false
- Success return Vector2

---

> position = RL_GetWorldToScreen2D( Vector2 position, Camera2D camera )

Get the screen space position for a 2d camera world space position

- Failure return false
- Success return Vector2

---

> position = RL_GetScreenToWorld2D( Vector2 position, Camera2D camera )

Get the world space position for a 2d camera screen space position

- Failure return false
- Success return Vector2

---

## Shapes - Drawing

---

> success = RL_SetShapesTexture( Texture2D texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

- Failure return false
- Success return true

---

> success = RL_DrawPixel( Vector2 pos, Color color )

Draw a pixel

- Failure return false
- Success return true

---

> success = RL_DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness

- Failure return false
- Success return true

---

> success = RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out

- Failure return false
- Success return true

---

> success = RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true

---

> success = RL_DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true

---

> success = RL_DrawLineStrip( Vector2 points{}, int pointsCount, Color color )

Draw lines sequence

- Failure return false
- Success return true

---

> success = RL_DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle

- Failure return false
- Success return true

---

> success = RL_DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle

- Failure return false
- Success return true

---

> success = RL_DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline

- Failure return false
- Success return true

---

> success = RL_DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle

- Failure return false
- Success return true

---

> success = RL_DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline

- Failure return false
- Success return true

---

> success = RL_DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse

- Failure return false
- Success return true

---

> success = RL_DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline

- Failure return false
- Success return true

---

> success = RL_DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring

- Failure return false
- Success return true

---

> success = RL_DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline

- Failure return false
- Success return true

---

> success = RL_DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle

- Failure return false
- Success return true

---

> success = RL_DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters

- Failure return false
- Success return true

---

> success = RL_DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle

- Failure return false
- Success return true

---

> success = RL_DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle

- Failure return false
- Success return true

---

> success = RL_DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors

- Failure return false
- Success return true

---

> success = RL_DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline

- Failure return false
- Success return true

---

> success = RL_DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters

- Failure return false
- Success return true

---

> success = RL_DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges

- Failure return false
- Success return true

---

> success = RL_DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline

- Failure return false
- Success return true

---

> success = RL_DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL_DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL_DrawTriangleFan( Vector2 points{}, int pointsCount, Color color )

Draw a triangle fan defined by points ( first vertex is the center )

- Failure return false
- Success return true

---

> success = RL_DrawTriangleStrip( Vector2 points{}, int pointsCount, Color color )

Draw a triangle strip defined by points

- Failure return false
- Success return true

---

> success = RL_DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon ( Vector version )

- Failure return false
- Success return true

---

> success = RL_DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides

- Failure return false
- Success return true

---

> success = RL_DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters

- Failure return false
- Success return true

---

## Shapes - Collision

---

> collision = RL_CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Failure return nil
- Success return bool

---

> collision, position = RL_CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Failure return nil
- Success return bool, Vector2

---

> collision = RL_CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Failure return nil
- Success return bool

---

> rectangle = RL_GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Failure return nil
- Success return Rectangle

---

## Textures - Image Loading

---

> image = RL_LoadImage( string fileName )

Load image from file into CPU memory ( RAM )

- Failure return -1
- Success return int

---

> image = RL_LoadImageFromTexture( Texture2D texture )

Load image from GPU texture data

- Failure return -1
- Success return int

---

> image = RL_LoadImageFromScreen()

Load image from screen buffer and ( screenshot )

- Success return int

---

> success = RL_UnloadImage( Image image )

Unload image from CPU memory ( RAM )

- Failure return false
- Success return true

---

> success = RL_ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Failure return nil
- Success return bool

---

> success = RL_ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Failure return nil
- Success return bool

---

## Textures - Image Generation

---

> image = RL_GenImageColor( int width, int height, Color color )

Generate image: plain color

- Failure return -1
- Success return int

---

> image = RL_GenImageGradientV( Vector2 size, Color top, Color bottom )

Generate image: vertical gradient

- Failure return -1
- Success return int

---

> image = RL_GenImageGradientH( Vector2 size, Color left, Color right )

Generate image: horizontal gradient

- Failure return -1
- Success return int

---

> image = RL_GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Failure return -1
- Success return int

---

> image = RL_GenImageChecked( Vector2 size, Vector2 checks, Color col1, Color col2 )

Generate image: checked

- Failure return -1
- Success return int

---

> image = RL_GenImageWhiteNoise( Vector2 size, float factor )

Generate image: white noise

- Failure return -1
- Success return int

---

> image = RL_GenImageCellular( Vector2 size, int tileSize )

Generate image: cellular algorithm. Bigger tileSize means bigger cells

- Failure return -1
- Success return int

---

## Textures - Image Manipulation Functions

---

> image = RL_ImageCopy( Image image )

Create an image duplicate ( useful for transformations )

- Failure return -1
- Success return int

---

> image = RL_ImageFromImage( Image image, Rectangle rec )

Create an image from another image piece

- Failure return -1
- Success return int

---

> image = RL_ImageText( Font font, string text, float fontSize, float spacing, Color tint )

Create an image from text ( custom sprite font )

- Failure return -1
- Success return int

---

> success = RL_ImageFormat( Image image, int newFormat )

Convert image data to desired format

- Failure return false
- Success return true

---

> success = RL_ImageToPOT( Image image, Color fill )

Convert image to POT ( power-of-two )

- Failure return false
- Success return true

---

> success = RL_ImageCrop( Image image, Rectangle crop )

Crop an image to a defined rectangle

- Failure return false
- Success return true

---

> success = RL_ImageAlphaCrop( Image image, float threshold )

Crop image depending on alpha value

- Failure return false
- Success return true

---

> success = RL_ImageAlphaClear( Image image, Color color, float threshold )

Clear alpha channel to desired color

- Failure return false
- Success return true

---

> success = RL_ImageAlphaMask( Image image, Image alphaMask )

Apply alpha mask to image

- Failure return false
- Success return true

---

> success = RL_ImageAlphaPremultiply( Image image )

Premultiply alpha channel

- Failure return false
- Success return true

---

> success = RL_ImageResize( Image image, Vector2 size )

Resize image ( Bicubic scaling algorithm )

- Failure return false
- Success return true

---

> success = RL_ImageResizeNN( Image image, Vector2 size )

Resize image ( Nearest-Neighbor scaling algorithm )

- Failure return false
- Success return true

---

> success = RL_ImageResizeCanvas( Image image, Vector2 size, Vector2 offset, Color fill )

Resize canvas and fill with color

- Failure return false
- Success return true

---

> success = RL_ImageMipmaps( Image image )

Generate all mipmap levels for a provided image

- Failure return false
- Success return true

---

> success = RL_ImageDither( Image image, Color bpp )

Dither image data to 16bpp or lower ( Floyd-Steinberg dithering )

- Failure return false
- Success return true

---

> success = RL_ImageFlipVertical( Image image )

Flip image vertically

- Failure return false
- Success return true

---

> success = RL_ImageFlipHorizontal( Image image )

Flip image horizontally

- Failure return false
- Success return true

---

> success = RL_ImageRotateCW( Image image )

Rotate image clockwise 90deg

- Failure return false
- Success return true

---

> success = RL_ImageRotateCCW( Image image )

Rotate image counter-clockwise 90deg

- Failure return false
- Success return true

---

> success = RL_ImageColorTint( Image image, Color color )

Modify image color: tint

- Failure return false
- Success return true

---

> success = RL_ImageColorInvert( Image image )

Modify image color: invert

- Failure return false
- Success return true

---

> success = RL_ImageColorGrayscale( Image image )

Modify image color: grayscale

- Failure return false
- Success return true

---

> success = RL_ImageColorContrast( Image image, float contrast )

Modify image color: contrast ( -100 to 100 )

- Failure return false
- Success return true

---

> success = RL_ImageColorBrightness( Image image, int brightness )

Modify image color: brightness ( -255 to 255 )

- Failure return false
- Success return true

---

> success = RL_ImageColorReplace( Image image, Color color, Color replace )

Modify image color: replace color

- Failure return false
- Success return true

---

> colors = RL_LoadImageColors( Image image )

Load color data from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}

---

> colors = RL_LoadImagePalette( Image image, int maxPaletteSize )

Load colors palette from image as a Color array ( RGBA - 32bit )

- Failure return false
- Success return Color{}

---

> rectangle = RL_GetImageAlphaBorder( Image image, float threshold )

Get image alpha border rectangle

- Failure return false
- Success return Rectangle

---

> color = RL_GetImageColor( Image image, Vector2 pixelPos )

Get image pixel color at ( x, y ) position

- Failure return false
- Success return Color

---

## Textures - Image Drawing

---

> success = RL_ImageClearBackground( Image dst, Color color )

Clear image background with given color

- Failure return false
- Success return true

---

> success = RL_ImageDrawPixel( Image dst, Vector2 position, Color color )

Draw pixel within an image

- Failure return false
- Success return true

---

> success = RL_ImageDrawLine( Image dst, Vector2 start, Vector2 end, Color color )

Draw line within an image

- Failure return false
- Success return true

---

> success = RL_ImageDrawCircle( Image dst, Vector2 center, int radius, Color color )

Draw circle within an image

- Failure return false
- Success return true

---

> success = RL_ImageDrawRectangle( Image dst, Rectangle rec, Color color )

Draw rectangle within an image

- Failure return false
- Success return true

---

> success = RL_DrawRectangleLines( Image dst, Rectangle rec, int thick, Color color )

Draw rectangle lines within an image

- Failure return false
- Success return true

---

> success = RL_ImageDraw( Image dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint )

Draw a source image within a destination image ( Tint applied to source )

- Failure return false
- Success return true

---

> success = RL_ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text ( Custom sprite font ) within an image ( Destination )

- Failure return false
- Success return true

---

## Textures - Image Configuration

---

> size = RL_GetImageSize( Image image )

Get image size

- Failure return nil
- Success return Vector2

---

> mipmaps = RL_GetImageMipmaps( Image image )

Get image mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

> format = RL_GetImageFormat( Image image )

Get image data format ( PixelFormat type )

- Failure return false
- Success return int

---

## Textures - Texture Loading

---

> texture = RL_LoadTexture( string fileName )

Load texture from file into GPU memory ( VRAM )

- Failure return -1
- Success return int

---

> texture = RL_LoadTextureFromImage( Image image )

Load texture from image data

- Failure return -1
- Success return int

---

> texture = RL_LoadTextureCubemap( Image image, int layout )

Load cubemap from image, multiple image cubemap layouts supported

- Failure return -1
- Success return int

---

> renderTexture = RL_LoadRenderTexture( Vector2 size )

Load texture for rendering ( framebuffer )

- Failure return -1
- Success return int

---

> success = RL_UnloadTexture( Texture2D texture )

Unload texture from GPU memory ( VRAM )

- Failure return false
- Success return true

---

> success = RL_UnloadRenderTexture( RenderTexture2D target )

Unload render texture from GPU memory ( VRAM )

- Failure return false
- Success return true

---

> success = RL_UpdateTexture( Texture2D texture, int pixels{ {} } )

Update GPU texture with new data
NOTE! Should be TEXTURE_SOURCE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true

---

> success = RL_UpdateTextureRec( Texture2D texture, Rectangle rec, int pixels{ {} } )

Update GPU texture rectangle with new data
NOTE! Should be TEXTURE_SOURCE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

- Failure return false
- Success return true

---

## Textures - Texture Drawing

---

> success = RL_DrawTexture( Texture2D texture, Vector2 position, Color tint )

Draw a Texture2D

- Failure return false
- Success return true

---

> success = RL_DrawTextureRec( Texture2D texture, Rectangle source, Vector2 position, Color tint )

Draw a part of a texture defined by a rectangle

- Failure return false
- Success return true

---

> success = RL_DrawTextureTiled( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint )

Draw part of a texture ( defined by a rectangle ) with rotation and scale tiled into dest

- Failure return false
- Success return true

---

> success = RL_DrawTexturePro( Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draw a part of a texture defined by a rectangle with "pro" parameters

- Failure return false
- Success return true

---

> success = RL_DrawTextureNPatch( Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture ( or part of it ) that stretches or shrinks nicely

- Failure return false
- Success return true

---

> success = RL_DrawTexturePoly( Texture2D texture, Vector2 center, Vector2{} points, Vector2{} texcoords, int pointsCount, Color tint )

Draw a textured polygon ( Convex )

- Failure return false
- Success return true

---

> success = RL_BeginTextureMode( RenderTexture2D target )

Begin drawing to render texture

- Failure return false
- Success return true

---

> RL_EndTextureMode()

Ends drawing to render texture

---

> success = RL_SetTextureSource( int textureSource )

Set what texture source to use ( TEXTURE_SOURCE_TEXTURE or TEXTURE_SOURCE_RENDER_TEXTURE )

- Failure return false
- Success return true

---

> textureSource = RL_GetTextureSource()

Get current texture source type ( TEXTURE_SOURCE_TEXTURE or TEXTURE_SOURCE_RENDER_TEXTURE )

- Success return int

---

## Textures - Texture Configuration

---

> success = RL_GenTextureMipmaps( Texture2D texture )

Generate GPU mipmaps for a texture

- Failure return false
- Success return true

---

> success = RL_SetTextureFilter( Texture2D texture, int filter )

Set texture scaling filter mode ( TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR... )

- Failure return false
- Success return true

---

> success = RL_SetTextureWrap( Texture2D texture, int wrap )

Set texture wrapping mode ( TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP... )

- Failure return false
- Success return true

---

> size = RL_GetTextureSize( Texture2D texture )

Get texture size

- Failure return nil
- Success return Vector2

---

> mipmaps = RL_GetTextureMipmaps( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

> format = RL_GetTextureFormat( Texture2D texture )

Get texture mipmaps. Mipmap levels, 1 by default

- Failure return false
- Success return int

---

## Textures - Color/pixel

---

> color = RL_Fade( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color

---

> value = RL_ColorToInt( Color color )

Returns hexadecimal value for a Color

- Failure return false
- Success return int

---

> color = RL_ColorNormalize( Color color )

Returns Color normalized as float [0..1]

- Failure return false
- Success return Vector4

---

> color = RL_ColorFromNormalized( Vector4 normalized )

Color from normalized values [0..1]

- Failure return false
- Success return Color

---

> HSV = RL_ColorToHSV( Color color )

Returns HSV values for a Color, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Vector3

---

> color = RL_ColorFromHSV( float hue, float saturation, float value )

Returns a Color from HSV values, hue [0..360], saturation/value [0..1]

- Failure return false
- Success return Color

---

> color = RL_ColorAlpha( Color color, float alpha )

Returns color with alpha applied, alpha goes from 0.0f to 1.0f

- Failure return false
- Success return Color

---

> color = RL_ColorAlphaBlend( Color dst, Color src, Color tint )

Returns src alpha-blended into dst color with tint

- Failure return false
- Success return Color

---

> Color = RL_GetColor( unsigned int hexValue )

Get Color structure from hexadecimal value

- Failure return false
- Success return Color

---

> Color = RL_GetPixelColor( Texture2D texture, Vector2 position )

Get pixel color from source texture

- Failure return false
- Success return Color

---

> size = RL_GetPixelDataSize( int width, int height, int format )

Get pixel data size in bytes for certain format

- Failure return false
- Success return int

---

## Text - Loading

---

> font = RL_LoadFont( string fileName )

Load font from file into GPU memory ( VRAM )

- Failure return -1
- Success return int

---

> font = RL_LoadFontFromImage( Image image, Color key, int firstChar )

Load font from Image ( XNA style )

- Failure return -1
- Success return int

---

> success = RL_UnloadFont( Font font )

Unload Font from GPU memory ( VRAM )

- Failure return false
- Success return true

---

## Text - Draw

---

> success = RL_DrawFPS( Vector2 pos )

Draw current FPS

- Failure return false
- Success return true

---

> success = RL_DrawText( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters

- Failure return false
- Success return true

---

> success = RL_DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters ( rotation )

- Failure return false
- Success return true

---

## Text - Misc

---

> size = RL_MeasureText( Font font, string text, float fontSize, float spacing )

Measure string size for Font

- Failure return false
- Success return Vector2

---

## Models - Basic

---

> success = RL_DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )

Draw a line in 3D world space

- Failure return false
- Success return true

---

> success = RL_DrawPoint3D( Vector3 position, Color color )

Draw a point in 3D space, actually a small line

- Failure return false
- Success return true

---

> success = RL_DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )

Draw a circle in 3D world space

- Failure return false
- Success return true

---

> success = RL_DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true

---

> success = RL_DrawCube( Vector3 position, Vector3 size, Color color )

Draw cube

- Failure return false
- Success return true

---

> success = RL_DrawCubeWires( Vector3 position, Vector3 size, Color color )

Draw cube wires

- Failure return false
- Success return true

---

> success = RL_DrawCubeTexture( Texture2D texture, Vector3 position, Vector3 size, Color color )

Draw cube textured

- Failure return false
- Success return true

---

> success = RL_DrawSphere( Vector3 centerPos, float radius, Color color )

Draw sphere

- Failure return false
- Success return true

---

> success = RL_DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere with extended parameters

- Failure return false
- Success return true

---

> success = RL_DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere wires

- Failure return false
- Success return true

---

> success = RL_DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone

- Failure return false
- Success return true

---

> success = RL_DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder with base at startPos and top at endPos

- Failure return false
- Success return true

---

> success = RL_DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone wires

- Failure return false
- Success return true

---

> success = RL_DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder wires with base at startPos and top at endPos

- Failure return false
- Success return true

---

> success = RL_DrawPlane( Vector3 centerPos, Vector2 size, Color color )

Draw a plane XZ

- Failure return false
- Success return true

---

> success = RL_DrawQuad3DTexture( texture, Vector3{} vertices, Vector2{} texCoords, Color color )

Draw 3D quad texture using vertices and texture coordinates. Texture coordinates opengl style 0.0 - 1.0.
Note! Could be replaced something like "DrawPlaneTextureRec"

- Failure return false
- Success return true

---

> success = RL_DrawRay( Ray ray, Color color )

Draw a ray line

- Failure return false
- Success return true

---

> success = RL_DrawGrid( int slices, float spacing )

Draw a grid ( Centered at ( 0, 0, 0 ) )

- Failure return false
- Success return true

---

## Models - Mesh

---

> mesh = RL_GenMeshPoly( int sides, float radius )

Generate polygonal mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshPlane( float width, float length, int resX, int resZ )

Generate plane mesh ( With subdivisions )

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshCube( Vector3 size )

Generate cuboid mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshSphere( float radius, int rings, int slices )

Generate sphere mesh ( Standard sphere )

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshCylinder( float radius, float height, int slices )

Generate cylinder mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshCone( float radius, float height, int slices )

Generate cone/pyramid mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshTorus( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshKnot( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshHeightmap( Image heightmap, Vector3 size )

Generate heightmap mesh from image data

- Failure return -1
- Success return int

---

> mesh = RL_GenMeshCustom( Mesh{}, bool dynamic )

Generate custom mesh from vertex attribute data and uploads it into a VAO ( if supported ) and VBO

- Failure return -1
- Success return int

---

> success = RL_UpdateMesh( Mesh{} )

Update mesh vertex data in GPU. ( Mainly intented to be used with custom meshes )

- Failure return false
- Success return true

---

> success = RL_UnloadMesh( Mesh mesh )

Unload mesh data from CPU and GPU

- Failure return false
- Success return true

---

> success = RL_DrawMesh( Mesh mesh, Material material, Matrix transform )

Draw a 3d mesh with material and transform

- Failure return false
- Success return true

---

> success = RL_DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )

Draw multiple mesh instances with material and different transforms
Note! Untested.

- Failure return false
- Success return true

---

> success = RL_SetMeshColor( Mesh mesh, Color color )

Updades mesh color vertex attribute buffer
NOTE: Currently only works on custom mesh

- Failure return false
- Success return true

---

> success = RL_ExportMesh( Mesh mesh, string fileName )

Export mesh data to file, returns true on success

- Failure return false
- Success return true

---

> boundingBox = RL_GetMeshBoundingBox( Mesh mesh )

Compute mesh bounding box limits

- Failure return false
- Success return BoundingBox

---

> success = RL_GenMeshTangents( Mesh mesh )

Compute mesh tangents

- Failure return false
- Success return true

---

> success = RL_GenMeshBinormals( Mesh mesh )

Compute mesh binormals

- Failure return false
- Success return true

---

## Models - Material

---

> material = RL_LoadMaterialDefault()

Load default material

- Success return int

---

> material = RL_CreateMaterial( material{} )

Load material from table. See material table definition

- Failure return false
- Success return int

---

> success = RL_UnloadMaterial( Material material )

Unload material from GPU memory ( VRAM )

- Failure return false
- Success return true

---

> success = RL_SetMaterialTexture( Material material, int mapType, Texture2D texture )

Set texture for a material map type ( MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS... )

- Failure return false
- Success return true

---

> success = RL_SetMaterialColor( Material material, int mapType, Color color )

Set color for a material map type

- Failure return false
- Success return true

---

> success = RL_SetMaterialValue( Material material, int mapType, float value )

Set value for a material map type

- Failure return false
- Success return true

---

## Models - Model

---

> model = RL_LoadModel( string fileName )

Load model from files ( Meshes and materials )

- Failure return -1
- Success return int

---

> model = RL_LoadModelFromMesh( Mesh mesh )

Load model from generated mesh ( Default material )

- Failure return -1
- Success return int

---

> success = RL_UnloadModel( Model model )

Unload model ( Including meshes ) from memory ( RAM and/or VRAM )

- Failure return false
- Success return true

---

> success = RL_DrawModel( Model model, Vector3 position, float scale, Color tint )

Draw a model ( With texture if set )

- Failure return false
- Success return true

---

> success = RL_DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model with extended parameters

- Failure return false
- Success return true

---

> success = RL_SetModelMaterial( Model model, Material modelMaterial, Material material )

Copies material to model material. ( Model material is the material id in models. Material can be deleted if not used elsewhere )

- Failure return false
- Success return true

---

> success = RL_SetModelMeshMaterial( Model model, int meshId, int materialId )

Set material for a mesh ( Mesh and material on this model )

- Failure return false
- Success return true

---

> success = RL_DrawBillboard( Camera camera, Texture2D texture, Vector3 position, float size, Color tint )

Draw a billboard texture

- Failure return false
- Success return true

---

> success = RL_DrawBillboardRec( Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint )

Draw a billboard texture defined by source

- Failure return false
- Success return true

---

> success = RL_SetModelTransform( Model model, Matrix transform )

Set model transform matrix

- Failure return false
- Success return true

---

> transform = RL_GetModelTransform( Model model )

Get model transform matrix

- Failure return false
- Success return Matrix

---

## Model - Animations

---

> animations, animationCount = RL_LoadModelAnimations( string fileName )

Load model animations from file

- Failure return -1
- Success return int, int

---

> success = RL_UpdateModelAnimation( Model model, ModelAnimations animations, int animation, int frame )

Update model animation pose

- Failure return false
- Success return true

---

> success = RL_UnloadModelAnimations( ModelAnimations animations )

Unload animation data

- Failure return false
- Success return true

---

> valid = RL_IsModelAnimationValid( Model model, ModelAnimations animations )

Check model animation skeleton match

- Failure return nil
- Success return bool

---

> boneCount = RL_GetModelAnimationBoneCount( ModelAnimations animations, int animation )

Return modelAnimation bone count

- Failure return false
- Success return int

---

> frameCount = RL_GetModelAnimationFrameCount( ModelAnimations animations, int animation )

Return modelAnimation frame count

- Failure return false
- Success return int

---

## Model - Collision

---

> collision = RL_CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )

Check collision between two spheres

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )

Check collision between two bounding boxes

- Failure return nil
- Success return bool

---

> collision = RL_CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )

Check collision between box and sphere

- Failure return nil
- Success return bool

---

> rayCollision = RL_GetRayCollisionSphere( Ray ray, Vector3 center, float radius )

Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL_GetRayCollisionBox( Ray ray, BoundingBox box )

Get collision info between ray and box

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL_GetRayCollisionModel( Ray ray, Model model )

Get collision info between ray and model

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL_GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )

Get collision info between ray and mesh

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL_GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )

Get collision info between ray and triangle

- Failure return nil
- Success return RayCollision

---

> rayCollision = RL_GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )

Get collision info between ray and quad

- Failure return nil
- Success return RayCollision

---

## Audio - Audio device management

---

> success = RL_SetMasterVolume( float volume )

Set master volume ( listener )

- Failure return false
- Success return true

---

## Audio - Wave/Sound Loading

---

> sound = RL_LoadSound( string fileName )

Load sound from file

- Failure return -1
- Success return int

---

> wave = RL_LoadWave( string fileName )

Load wave data from file

- Failure return -1
- Success return int

---

> sound = RL_LoadSoundFromWave( Wave wave )

Load sound from wave data

- Failure return -1
- Success return int

---

> success = RL_UnloadSound( Sound sound )

Unload sound

- Failure return false
- Success return true

---

> success = RL_UnloadWave( Wave wave )

Unload wave data

- Failure return false
- Success return true

---

> success = RL_ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Failure return false
- Success return true

---

> success = RL_ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Failure return false
- Success return true

---

## Audio - Wave/Sound management

---

> success = RL_PlaySound( Sound sound )

Play a sound

- Failure return false
- Success return true

---

> success = RL_StopSound( Sound sound )

Stop playing a sound

- Failure return false
- Success return true

---

> success = RL_PauseSound( Sound sound )

Pause a sound

- Failure return false
- Success return true

---

> success = RL_ResumeSound( Sound sound )

Resume a paused sound

- Failure return false
- Success return true

---

> success = RL_PlaySoundMulti( Sound sound )

Play a sound ( Using multichannel buffer pool )

- Failure return false
- Success return true

---

> RL_StopSoundMulti()

Stop any sound playing ( using multichannel buffer pool )

---

> count = RL_GetSoundsPlaying()

Get number of sounds playing in the multichannel

- Success return int

---

> playing = RL_IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Failure return nil
- Success return bool

---

> success = RL_SetSoundVolume( Sound sound, float volume )

Set volume for a sound ( 1.0 is max level )

- Failure return false
- Success return true

---

> success = RL_SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound ( 1.0 is base level )

- Failure return false
- Success return true

---

> success = RL_WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format

- Failure return false
- Success return true

---

> wave = RL_WaveCopy( Wave wave )

Copy a wave to a new wave

- Failure return -1
- Success return int

---

> success = RL_WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range

- Failure return false
- Success return true

---

## Audio - Music management

---

> success = RL_LoadMusicStream( string fileName )

Load music stream from file

- Failure return false
- Success return true

---

> RL_PlayMusicStream()

Start music playing

---

> playing = RL_PlayMusicStream()

Check if music is playing

- Success return bool

---

> RL_StopMusicStream()

Stop music playing

---

> RL_PauseMusicStream()

Pause music playing

---

> RL_ResumeMusicStream()

Resume playing paused music

---

> success = RL_SeekMusicStream( float position )

Seek music to a position ( in seconds )

- Failure return false
- Success return true

---

> success = RL_SetMusicVolume( float volume )

Set volume for music ( 1.0 is max level )

- Failure return false
- Success return true

---

> success = RL_SetMusicPitch( float pitch )

Set pitch for a music ( 1.0 is base level )

- Failure return false
- Success return true

---

> length = RL_GetMusicTimeLength()

Get music time length ( in seconds )

- Success return float

---

> played = RL_GetMusicTimePlayed()

Get current music time played ( in seconds )

- Success return float

---

## Math - Utils

---

> result = RL_Clamp( float value, float min, float max )

Clamp float value

- Failure return false
- Success return float

---

> result = RL_Lerp( float start, float end, float amount )

Calculate linear interpolation between two floats

- Failure return false
- Success return float

---

> result = RL_Normalize( float value, float start, float end )

Normalize input value within input range

- Failure return false
- Success return float

---

> result = RL_Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )

Remap input value within input range to output range

- Failure return false
- Success return float

---

## Math - Vector2

---

> result = RL_Vector2Zero()

Vector with components value 0.0f

- Success return Vector2

---

> result = RL_Vector2One()

Vector with components value 1.0f

- Success return Vector2

---

> result = RL_Vector2Add( Vector2 v1, Vector2 v2 )

Add two vectors (v1 + v2)

- Failure return false
- Success return Vector2

---

> result = RL_Vector2AddValue( Vector2 v, float add )

Add vector and float value

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Subtract( Vector2 v1, Vector2 v2 )

Subtract two vectors (v1 - v2)

- Failure return false
- Success return Vector2

---

> result = RL_Vector2SubtractValue( Vector2 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Length( vector2 v )

Calculate vector length

- Failure return false
- Success return float

---

> result = RL_Vector2LengthSqr( vector2 v )

Calculate vector square length

- Failure return false
- Success return float

---

> result = RL_Vector2DotProduct( Vector2 v1, Vector2 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float

---

> result = RL_Vector2Distance( Vector2 v1, Vector2 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float

---

> result = RL_Vector2Angle( Vector2 v1, Vector2 v2 )

Calculate angle from two vectors

- Failure return false
- Success return float

---

> result = RL_Vector2Scale( Vector2 v, float scale )

Scale vector ( multiply by value )

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Multiply( Vector2 v1, Vector2 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Negate( Vector2 v )

Negate vector

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Divide( Vector2 v1, Vector2 v2 )

Divide vector by vector

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Normalize( Vector2 v )

Normalize provided vector

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Lerp( Vector2 v1, Vector2 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Reflect( Vector2 v, Vector2 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector2

---

> result = RL_Vector2Rotate( Vector2 v, float angle )

Rotate vector by angle

- Failure return false
- Success return Vector2

---

> result = RL_Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )

Move Vector towards target

- Failure return false
- Success return Vector2

---

## Math - Vector 3

---

> result = RL_Vector3Zero()

Vector with components value 0.0f

- Success return Vector3

---

> result = RL_Vector3One()

Vector with components value 1.0f

- Success return Vector3

---

> result = RL_Vector3Add( Vector3 v1, Vector3 v2 )

Add two vectors

- Failure return false
- Success return Vector3

---

> result = RL_Vector3AddValue( Vector3 v, float add )

Add vector and float value

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Subtract( Vector3 v1, Vector3 v2 )

Subtract two vectors

- Failure return false
- Success return Vector3

---

> result = RL_Vector3SubtractValue( Vector3 v, float sub )

Subtract vector by float value

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Scale( Vector3 v, float scalar )

Multiply vector by scalar

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Multiply( Vector3 v1, Vector3 v2 )

Multiply vector by vector

- Failure return false
- Success return Vector3

---

> result = RL_Vector3CrossProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors cross product

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Perpendicular( Vector3 v )

Calculate one vector perpendicular vector

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Length( Vector3 v )

Calculate vector length

- Failure return false
- Success return float

---

> result = RL_Vector3LengthSqr( Vector3 v )

Calculate vector square length

- Failure return false
- Success return float

---

> result = RL_Vector3DotProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors dot product

- Failure return false
- Success return float

---

> result = RL_Vector3Distance( Vector3 v1, Vector3 v2 )

Calculate distance between two vectors

- Failure return false
- Success return float

---

> result = RL_Vector3Angle( Vector3 v1, Vector3 v2 )

Calculate angle between two vectors

- Failure return false
- Success return float

---

> result = RL_Vector3Negate( Vector3 v )

Negate provided vector ( invert direction )

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Divide( Vector3 v1, Vector3 v2 )

Divide vector by vector

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Normalize( Vector3 v )

Normalize provided vector

- Failure return false
- Success return Vector3

---

> v1, v2 = RL_Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )

Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
Gram-Schmidt function implementation

- Failure return false
- Success return Vector3, Vector3

---

> result = RL_Vector3Transform( Vector3 v, Matrix mat )

Transforms a Vector3 by a given Matrix

- Failure return false
- Success return Vector3

---

> result = RL_Vector3RotateByQuaternion( Vector3 v, Quaternion q )

Transform a vector by quaternion rotation

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Lerp( Vector3 v1, Vector3 v2, float amount )

Calculate linear interpolation between two vectors

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Reflect( Vector3 v, Vector3 normal )

Calculate reflected vector to normal

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Min( Vector3 v1, Vector3 v2 )

Get min value for each pair of components

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Max( Vector3 v1, Vector3 v2 )

Get max value for each pair of components

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )

Compute barycenter coordinates ( u, v, w ) for point p with respect to triangle ( a, b, c )
NOTE: Assumes P is on the plane of the triangle

- Failure return false
- Success return Vector3

---

> result = RL_Vector3Unproject( Vector3 source, Matrix projection, Matrix view )

Projects a Vector3 from screen space into object space
NOTE: We are avoiding calling other raymath functions despite available

- Failure return false
- Success return Vector3

---

## Math - Matrix

---

> result = RL_MatrixDeterminant( Matrix mat )

Compute matrix determinant

- Failure return false
- Success return float

---

> result = RL_MatrixTrace( Matrix mat )

Get the trace of the matrix ( sum of the values along the diagonal )

- Failure return false
- Success return float

---

> result = RL_MatrixTranspose( Matrix mat )

Transposes provided matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixInvert( Matrix mat )

Invert provided matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixNormalize( Matrix mat )

Normalize provided matrix

- Failure return false
- Success return Matrix

---

> result = MatrixIdentity()

Get identity matrix

- Success return Matrix

---

> result = RL_MatrixAdd( Matrix left, Matrix right )

Add two matrices

- Failure return false
- Success return Matrix

---

> result = RL_MatrixSubtract( Matrix left, Matrix right )

Subtract two matrices (left - right)

- Failure return false
- Success return Matrix

---

> result = RL_MatrixMultiply( Matrix left, Matrix right )

Get two matrix multiplication

- Failure return false
- Success return Matrix

---

> result = RL_MatrixTranslate( Vector3 translate )

Get translation matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotate( Vector3 axis, float angle )

Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotateX( float angle )

Get x-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotateY( float angle )

Get y-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotateZ( float angle )

Get z-rotation matrix ( angle in radians )

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotateXYZ( Vector3 angle )

Get xyz-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix

---

> result = RL_MatrixRotateZYX( Vector3 angle )

Get zyx-rotation matrix ( angles in radians )

- Failure return false
- Success return Matrix

---

> result = RL_MatrixScale( Vector3 scale )

Get scaling matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixFrustum( double left, double right, double bottom, double top, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixPerspective( double fovy, double aspect, double near, double far )

Get perspective projection matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixOrtho( double left, double right, double bottom, double top, double near, double far )

Get orthographic projection matrix

- Failure return false
- Success return Matrix

---

> result = RL_MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )

Get camera look-at matrix ( View matrix )

- Failure return false
- Success return Matrix

---

## Math - Quaternion

---

> result = RL_QuaternionAdd( Quaternion q1, Quaternion q2 )

Add two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionAddValue( Quaternion q, float add )

Add quaternion and float value

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionSubtract( Quaternion q1, Quaternion q2 )

Subtract two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionSubtractValue( Quaternion q, float sub )

Subtract quaternion and float value

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionIdentity()

Get identity quaternion

- Success return Quaternion

---

> result = RL_QuaternionLength( Quaternion q )

Computes the length of a quaternion

- Failure return false
- Success return float

---

> result = RL_QuaternionNormalize( Quaternion q )

Normalize provided quaternion

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionInvert( Quaternion q )

Invert provided quaternion

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionMultiply( Quaternion q1, Quaternion q2 )

Calculate two quaternion multiplication

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionScale( Quaternion q, float mul )

Scale quaternion by float value

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionDivide( Quaternion q1, Quaternion q2 )

Divide two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionLerp( Quaternion q1, Quaternion q2, float amount )

Calculate linear interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )

Calculate slerp-optimized interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )

Calculates spherical linear interpolation between two quaternions

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )

Calculate quaternion based on the rotation from one vector to another

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionFromMatrix( Matrix mat )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionToMatrix( Quaternion q )

Get a quaternion for a given rotation matrix

- Failure return false
- Success return Matrix

---

> result = RL_QuaternionFromAxisAngle( Vector3 axis, float angle )

Get rotation quaternion for an angle and axis
NOTE: angle must be provided in radians

- Failure return false
- Success return Quaternion

---

> axis, angle = RL_QuaternionToAxisAngle( Quaternion q )

Get the rotation angle and axis for a given quaternion

- Failure return false
- Success return Vector3, float

---

> result = RL_QuaternionFromEuler( float pitch, float yaw, float roll )

Get the quaternion equivalent to Euler angles
NOTE: Rotation order is ZYX

- Failure return false
- Success return Quaternion

---

> result = RL_QuaternionToEuler( Quaternion q )

Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
NOTE: Angles are returned in a Vector3 struct in radians

- Failure return false
- Success return Vector3

---

> result = RL_QuaternionTransform( Quaternion q, Matrix mat )

Transform a quaternion given a transformation matrix

- Failure return false
- Success return Quaternion

---

## Gui - Global

---

> RL_GuiEnable()

Enable gui controls ( global state )

---

> RL_GuiDisable()

Disable gui controls ( global state )

---

> RL_GuiLock()

Lock gui controls ( global state )

---

> RL_GuiUnlock()

Unlock gui controls ( global state )

---

> locked = RL_GuiIsLocked()

Check if gui is locked ( global state )

- Success return bool

---

> success = RL_GuiFade( float alpha )

Set gui controls alpha ( global state ), alpha goes from 0.0f to 1.0f

- Failure return false
- Success return true

---

> success = RL_GuiSetState( int state )

Set gui state ( global state )

- Failure return false
- Success return true

---

> state = RL_GuiGetState()

Get gui state ( global state )

- Success return int

---

## Gui - Font

---

> success = RL_GuiSetFont( Font font )

Set gui custom font ( Global state )

- Failure return false
- Success return true

---

## Gui - Style

---

> success = RL_GuiSetStyle( int control, int property, int value )

Set one style property

- Failure return false
- Success return true

---

> value = RL_GuiGetStyle( int control, int property )

Get one style property

- Failure return false
- Success return int

---

> success = RL_GuiLoadStyle( int control, int property )

Load style file over global style variable ( .rgs )

- Failure return false
- Success return true

---

> RL_GuiLoadStyleDefault()

Load style default over global style

---

## Gui - Container

---

> state = RL_GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Failure return nil
- Success return bool

---

> success = RL_GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name

- Failure return false
- Success return true

---

> success = RL_GuiLine( Rectangle bounds, string text )

Line separator control, could contain text

- Failure return false
- Success return true

---

> success = RL_GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls

- Failure return false
- Success return true

---

> view, scroll = RL_GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )

Scroll Panel control

- Failure return false
- Success return Rectangle, Vector2

---

## Gui - Basic

---

> success = RL_GuiLabel( Rectangle bounds, string text )

Label control, shows text

- Failure return false
- Success return true

---

> clicked = RL_GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Failure return nil
- Success return boolean

---

> clicked = RL_GuiLabelButton( Rectangle bounds, string text )

Label button control, show true when clicked

- Failure return nil
- Success return boolean

---

> active = RL_GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Failure return nil
- Success return boolean

---

> index = RL_GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Failure return false
- Success return int

---

> active = RL_GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Failure return nil
- Success return boolean

---

> active = RL_GuiComboBox( Rectangle bounds, string text, int active )

Combo Box control, returns selected item index

- Failure return nil
- Success return int

---

> pressed, text = RL_GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Failure return nil
- Success return boolean, string

---

> pressed, text = RL_GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control with multiple lines

- Failure return nil
- Success return boolean, string

---

> pressed, value = RL_GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Failure return nil
- Success return boolean, int

---

> pressed, value = RL_GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Failure return nil
- Success return boolean, int

---

> value = RL_GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Failure return nil
- Success return float

---

> value = RL_GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Failure return nil
- Success return float

---

> value = RL_GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Failure return nil
- Success return float

---

> value = RL_GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll Bar control

- Failure return nil
- Success return int

---

> pressed, item = RL_GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Failure return nil
- Success return bool, int

---

> success = RL_GuiStatusBar( Rectangle bounds, string text )

Status Bar control, shows info text

- Failure return false
- Success return true

---

> success = RL_GuiDummyRec( Rectangle bounds, string text )

Dummy control for placeholders

- Failure return false
- Success return true

---

> cell = RL_GuiGrid( Rectangle bounds, string text, float spacing, int subdivs )

Grid control, returns mouse cell position

- Failure return false
- Success return Vector2

---

## Gui - Advanced

---

> itemIndex, scrollIndex = RL_GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index and scroll index

- Failure return nil
- Success return int, int

---

> itemIndex, scrollIndex, focus = RL_GuiListViewEx( Rectangle bounds, string text, int focus, int scrollIndex, int active )

List View with extended parameters, returns selected list item index, scroll index and focus

- Failure return nil
- Success return int, int, int

---

> buttonIndex = RL_GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message, returns button index ( 0 is x button )

- Failure return false
- Success return int

---

> buttonIndex, text, secretViewActive = RL_GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )

Text Input Box control, ask for text, supports secret

- Failure return false
- Success return int, string, int

---

> color = RL_GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control ( multiple color controls )

- Failure return false
- Success return Color

---

> color = RL_GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Failure return false
- Success return Color

---

> alpha = RL_GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Failure return false
- Success return float

---

> hue = RL_GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Failure return false
- Success return float

---

## Gui - Icons

---

> text = RL_GuiIconText( int iconId, string text )

Get text with icon id prepended ( if supported )

- Failure return false
- Success return string

---

> success = RL_GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon

- Failure return false
- Success return true

---

> success = RL_GuiSetIconScale( int scale )

Set icon scale ( 1 by default )

- Failure return false
- Success return true

---

> success = RL_GuiSetIconPixel( int iconId, Vector2 pos )

Set icon pixel value

- Failure return false
- Success return true

---

> success = RL_GuiClearIconPixel( int iconId, Vector2 pos )

Clear icon pixel value

- Failure return false
- Success return true

---

> value = RL_GuiCheckIconPixel( int iconId, Vector2 pos )

Check icon pixel value

- Failure return nil
- Success return bool

---

## Lights - Basics

---

> light = RL_CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )

Create a light and get shader locations

- Failure return -1
- Success return int

---

> success = RL_UpdateLightValues( Shader shader, Light light )

Send light properties to shader

- Failure return false
- Success return true

---

## RLGL - General render state

---

> success = RL_rlSetLineWidth( float width )

Set the line drawing width

- Failure return false
- Success return true

---

> width = RL_rlGetLineWidth()

Get the line drawing width

- Success return float

---
