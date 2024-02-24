# ReiLua API

## Functions

Application needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where "main.lua" is located can be given as argument. There are five Lua functions that the framework will call, 'RL.init', 'RL.update', 'RL.draw', 'RL.event', 'RL.log', and 'RL.exit'.

---
> function RL.init()

This function will be called first when 'main.lua' is found

---

> function RL.update( delta )

This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'

---

> function RL.draw()

This function will be called every frame after update and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.

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

## Object unloading

Some objects allocate memory that needs to be freed when object is no longer needed. By default objects like Textures are unloaded by the Lua garbage collector. It is generatty however recommended to handle this manually in more complex projects. You can change the behavior with SetGCUnload.

## Arguments

Arguments are stored in 'RL.arg' array.

## Structures

Raylib structs in Lua

---

> Vector2 = { 1.0, 1.0 } or { x = 1.0, y = 1.0 }

Vector2, 2 components

---

> Vector3 = { 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0 }

Vector3, 3 components

---

> Vector4 = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }

Vector4, 4 components

---

> Quaternion = { 0.0, 0.0, 0.0, 1.0 } or { x = 0.0, y = 0.0, z = 0.0, w = 1.0 }

Quaternion, 4 components (Vector4 alias)

---

> Matrix = { { 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } }

Matrix, 4x4 components, column major, OpenGL style, right-handed. Identity matrix example

---

> Color = { 255, 255, 255, 255 } or { r = 255, g = 255, b = 255, a = 255 }

Color, 4 components, R8G8B8A8 (32bit)

---

> Rectangle = { 0.0, 0.0, 1.0, 1.0 } or { x = 0.0, y = 0.0, width = 1.0, height = 1.0 }

Rectangle, 4 components

---

> Image = Userdata

Image, pixel data stored in CPU memory (RAM)

---

> Texture = Userdata

Texture, tex data stored in GPU memory (VRAM)
```
textureData = {
	id = unsigned int,		--OpenGL texture id
	width = int,			--Texture base width
	height = int,			--Texture base height
	mipmaps = int,			--Mipmap levels, 1 by default
	format = int			--Data format (PixelFormat type)
}
```

---

> RenderTexture = Userdata

RenderTexture, fbo for texture rendering
```
renderTextureData = {
	id = unsigned int,		--OpenGL texture id
	texture = Texture,		--Texture base width
	depth = Texture,		--Texture base height
}
```

---

> Font = Userdata

Font, font texture and GlyphInfo array data

---

> Camera2D = Userdata

Camera2D, defines position/orientation in 2d space

---

> Camera3D = Userdata

Camera, defines position/orientation in 3d space

---

> Mesh = Userdata

Mesh, vertex data and vao/vbo

```
meshData = {
	vertices = Vector3{},		--Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
	texcoords = Vector2{},		--Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
	texcoords2 = Vector2{},		--Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
	normals = Vector3{},		--Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
	tangents = Vector4{},		--Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
	colors = Color{},			--Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
	indices = int{}				--Vertex indices (in case vertex data comes indexed)
}
```

---

> Material = Userdata

Material, includes shader and maps

```
materialData = {
	shader = Shader,
	maps = {									--Material maps array (MAX_MATERIAL_MAPS)
		{
    		MATERIAL_MAP_*,						--Example MATERIAL_MAP_ALBEDO
			{
    			texture = Texture,				--Material map texture
        		color = Color,					--Material map color
        		value = float,					--Material map value
      		},
    	},
    	...
  	},
  	params = { float, float, float, float }		--Material generic parameters (if required)
}
```

---

> Model = Userdata

Model, meshes, materials and animation data

---

> Ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } or { position = { 0.0, 0.0, 0.0 }, direction = { 1.0, 0.0, 0.0 } }

Ray, ray for raycasting

---

> RayCollision = { hit = true, distance = 1.0, point = { 0.0, 0.0, 0.0 }, normal = { 0.0, 0.0, 1.0 } }

RayCollision, ray hit information

---

> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } } or { min = { 0.0, 0.0, 0.0 }, max = { 1.0, 1.0, 1.0 } }

BoundingBox

---

> GlyphInfo = Userdata

GlyphInfo, font characters glyphs info

```
glyphInfoData = {
	value = int,		--Character value (Unicode)
	offsetX = int,		--Character offset X when drawing
	offsetY = int,		--Character offset Y when drawing
	advanceX = int,		--Character advance position X
	image = Image,		--Character image data
}
```

---

> BoneInfo = { name = string[32], parent = int }

Bone, skeletal animation bone

---

> Transform = { translation = Vector3, rotation = Quaternion, scale = Vector3 }

Transform, vertex transformation data

---

> Wave = Userdata

Wave, audio wave data

---

> Sound = Userdata

Sound

---

> Music = Userdata

Music, audio stream, anything longer than ~10 seconds should be streamed

---

> NPatchInfo = { { 0, 0, 24, 24 }, 8, 8, 8, 8, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }

NPatchInfo, n-patch layout info

---

> ModelAnimations = Userdata

ModelAnimation

---

> Buffer = Buffer userdata

Data buffer for C primitive types. Type should be one of the Buffer types.

---

## Defines - System/Window config flags
> FLAG_VSYNC_HINT = 64

Set to try enabling V-Sync on GPU

---

> FLAG_FULLSCREEN_MODE = 2

Set to run program in fullscreen

---

> FLAG_WINDOW_RESIZABLE = 4

Set to allow resizable window

---

> FLAG_WINDOW_UNDECORATED = 8

Set to disable window decoration (frame and buttons)

---

> FLAG_WINDOW_HIDDEN = 128

Set to hide window

---

> FLAG_WINDOW_MINIMIZED = 512

Set to minimize window (iconify)

---

> FLAG_WINDOW_MAXIMIZED = 1024

Set to maximize window (expanded to monitor)

---

> FLAG_WINDOW_UNFOCUSED = 2048

Set to window non focused

---

> FLAG_WINDOW_TOPMOST = 4096

Set to window always on top

---

> FLAG_WINDOW_ALWAYS_RUN = 256

Set to allow windows running while minimized

---

> FLAG_WINDOW_TRANSPARENT = 16

Set to allow transparent framebuffer

---

> FLAG_WINDOW_HIGHDPI = 8192

Set to support HighDPI

---

> FLAG_WINDOW_MOUSE_PASSTHROUGH = 16384

Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED

---

> FLAG_MSAA_4X_HINT = 32

Set to try enabling MSAA 4X

---

> FLAG_INTERLACED_HINT = 65536

Set to try enabling interlaced video format (for V3D)

---


## Defines - Trace log level
> LOG_ALL = 0

Display all logs

---

> LOG_TRACE = 1

Trace logging, intended for internal use only

---

> LOG_DEBUG = 2

Debug logging, used for internal debugging, it should be disabled on release builds

---

> LOG_INFO = 3

Info logging, used for program execution info

---

> LOG_WARNING = 4

Warning logging, used on recoverable failures

---

> LOG_ERROR = 5

Error logging, used on unrecoverable failures

---

> LOG_FATAL = 6

Fatal logging, used to abort program: exit(EXIT_FAILURE)

---

> LOG_NONE = 7

Disable logging

---


## Defines - Keyboard keys (US keyboard layout)
> KEY_NULL = 0

Key: NULL, used for no key pressed

---

> KEY_APOSTROPHE = 39

Key: '

---

> KEY_COMMA = 44

Key: ,

---

> KEY_MINUS = 45

Key: -

---

> KEY_PERIOD = 46

Key: .

---

> KEY_SLASH = 47

Key: /

---

> KEY_ZERO = 48

Key: 0

---

> KEY_ONE = 49

Key: 1

---

> KEY_TWO = 50

Key: 2

---

> KEY_THREE = 51

Key: 3

---

> KEY_FOUR = 52

Key: 4

---

> KEY_FIVE = 53

Key: 5

---

> KEY_SIX = 54

Key: 6

---

> KEY_SEVEN = 55

Key: 7

---

> KEY_EIGHT = 56

Key: 8

---

> KEY_NINE = 57

Key: 9

---

> KEY_SEMICOLON = 59

Key: ;

---

> KEY_EQUAL = 61

Key: =

---

> KEY_A = 65

Key: A | a

---

> KEY_B = 66

Key: B | b

---

> KEY_C = 67

Key: C | c

---

> KEY_D = 68

Key: D | d

---

> KEY_E = 69

Key: E | e

---

> KEY_F = 70

Key: F | f

---

> KEY_G = 71

Key: G | g

---

> KEY_H = 72

Key: H | h

---

> KEY_I = 73

Key: I | i

---

> KEY_J = 74

Key: J | j

---

> KEY_K = 75

Key: K | k

---

> KEY_L = 76

Key: L | l

---

> KEY_M = 77

Key: M | m

---

> KEY_N = 78

Key: N | n

---

> KEY_O = 79

Key: O | o

---

> KEY_P = 80

Key: P | p

---

> KEY_Q = 81

Key: Q | q

---

> KEY_R = 82

Key: R | r

---

> KEY_S = 83

Key: S | s

---

> KEY_T = 84

Key: T | t

---

> KEY_U = 85

Key: U | u

---

> KEY_V = 86

Key: V | v

---

> KEY_W = 87

Key: W | w

---

> KEY_X = 88

Key: X | x

---

> KEY_Y = 89

Key: Y | y

---

> KEY_Z = 90

Key: Z | z

---

> KEY_LEFT_BRACKET = 91

Key: [

---

> KEY_BACKSLASH = 92

Key: '\'

---

> KEY_RIGHT_BRACKET = 93

Key: ]

---

> KEY_GRAVE = 96

Key: `

---

> KEY_SPACE = 32

Key: Space

---

> KEY_ESCAPE = 256

Key: Esc

---

> KEY_ENTER = 257

Key: Enter

---

> KEY_TAB = 258

Key: Tab

---

> KEY_BACKSPACE = 259

Key: Backspace

---

> KEY_INSERT = 260

Key: Ins

---

> KEY_DELETE = 261

Key: Del

---

> KEY_RIGHT = 262

Key: Cursor right

---

> KEY_LEFT = 263

Key: Cursor left

---

> KEY_DOWN = 264

Key: Cursor down

---

> KEY_UP = 265

Key: Cursor up

---

> KEY_PAGE_UP = 266

Key: Page up

---

> KEY_PAGE_DOWN = 267

Key: Page down

---

> KEY_HOME = 268

Key: Home

---

> KEY_END = 269

Key: End

---

> KEY_CAPS_LOCK = 280

Key: Caps lock

---

> KEY_SCROLL_LOCK = 281

Key: Scroll down

---

> KEY_NUM_LOCK = 282

Key: Num lock

---

> KEY_PRINT_SCREEN = 283

Key: Print screen

---

> KEY_PAUSE = 284

Key: Pause

---

> KEY_F1 = 290

Key: F1

---

> KEY_F2 = 291

Key: F2

---

> KEY_F3 = 292

Key: F3

---

> KEY_F4 = 293

Key: F4

---

> KEY_F5 = 294

Key: F5

---

> KEY_F6 = 295

Key: F6

---

> KEY_F7 = 296

Key: F7

---

> KEY_F8 = 297

Key: F8

---

> KEY_F9 = 298

Key: F9

---

> KEY_F10 = 299

Key: F10

---

> KEY_F11 = 300

Key: F11

---

> KEY_F12 = 301

Key: F12

---

> KEY_LEFT_SHIFT = 340

Key: Shift left

---

> KEY_LEFT_CONTROL = 341

Key: Control left

---

> KEY_LEFT_ALT = 342

Key: Alt left

---

> KEY_LEFT_SUPER = 343

Key: Super left

---

> KEY_RIGHT_SHIFT = 344

Key: Shift right

---

> KEY_RIGHT_CONTROL = 345

Key: Control right

---

> KEY_RIGHT_ALT = 346

Key: Alt right

---

> KEY_RIGHT_SUPER = 347

Key: Super right

---

> KEY_KB_MENU = 348

Key: KB menu

---

> KEY_KP_0 = 320

Key: Keypad 0

---

> KEY_KP_1 = 321

Key: Keypad 1

---

> KEY_KP_2 = 322

Key: Keypad 2

---

> KEY_KP_3 = 323

Key: Keypad 3

---

> KEY_KP_4 = 324

Key: Keypad 4

---

> KEY_KP_5 = 325

Key: Keypad 5

---

> KEY_KP_6 = 326

Key: Keypad 6

---

> KEY_KP_7 = 327

Key: Keypad 7

---

> KEY_KP_8 = 328

Key: Keypad 8

---

> KEY_KP_9 = 329

Key: Keypad 9

---

> KEY_KP_DECIMAL = 330

Key: Keypad .

---

> KEY_KP_DIVIDE = 331

Key: Keypad /

---

> KEY_KP_MULTIPLY = 332

Key: Keypad *

---

> KEY_KP_SUBTRACT = 333

Key: Keypad -

---

> KEY_KP_ADD = 334

Key: Keypad +

---

> KEY_KP_ENTER = 335

Key: Keypad Enter

---

> KEY_KP_EQUAL = 336

Key: Keypad =

---

> KEY_BACK = 4

Key: Android back button

---

> KEY_MENU = 82

Key: Android menu button

---

> KEY_VOLUME_UP = 24

Key: Android volume up button

---

> KEY_VOLUME_DOWN = 25

Key: Android volume down button

---


## Defines - Mouse buttons
> MOUSE_BUTTON_LEFT = 0

Mouse button left

---

> MOUSE_BUTTON_RIGHT = 1

Mouse button right

---

> MOUSE_BUTTON_MIDDLE = 2

Mouse button middle (pressed wheel)

---

> MOUSE_BUTTON_SIDE = 3

Mouse button side (advanced mouse device)

---

> MOUSE_BUTTON_EXTRA = 4

Mouse button extra (advanced mouse device)

---

> MOUSE_BUTTON_FORWARD = 5

Mouse button forward (advanced mouse device)

---

> MOUSE_BUTTON_BACK = 6

Mouse button back (advanced mouse device)

---


## Defines - Mouse cursor
> MOUSE_CURSOR_DEFAULT = 0

Default pointer shape

---

> MOUSE_CURSOR_ARROW = 1

Arrow shape

---

> MOUSE_CURSOR_IBEAM = 2

Text writing cursor shape

---

> MOUSE_CURSOR_CROSSHAIR = 3

Cross shape

---

> MOUSE_CURSOR_POINTING_HAND = 4

Pointing hand cursor

---

> MOUSE_CURSOR_RESIZE_EW = 5

Horizontal resize/move arrow shape

---

> MOUSE_CURSOR_RESIZE_NS = 6

Vertical resize/move arrow shape

---

> MOUSE_CURSOR_RESIZE_NWSE = 7

Top-left to bottom-right diagonal resize/move arrow shape

---

> MOUSE_CURSOR_RESIZE_NESW = 8

The top-right to bottom-left diagonal resize/move arrow shape

---

> MOUSE_CURSOR_RESIZE_ALL = 9

The omnidirectional resize/move cursor shape

---

> MOUSE_CURSOR_NOT_ALLOWED = 10

The operation-not-allowed shape

---


## Defines - Gamepad buttons
> GAMEPAD_BUTTON_UNKNOWN = 0

Unknown button, just for error checking

---

> GAMEPAD_BUTTON_LEFT_FACE_UP = 1

Gamepad left DPAD up button

---

> GAMEPAD_BUTTON_LEFT_FACE_RIGHT = 2

Gamepad left DPAD right button

---

> GAMEPAD_BUTTON_LEFT_FACE_DOWN = 3

Gamepad left DPAD down button

---

> GAMEPAD_BUTTON_LEFT_FACE_LEFT = 4

Gamepad left DPAD left button

---

> GAMEPAD_BUTTON_RIGHT_FACE_UP = 5

Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)

---

> GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = 6

Gamepad right button right (i.e. PS3: Square, Xbox: X)

---

> GAMEPAD_BUTTON_RIGHT_FACE_DOWN = 7

Gamepad right button down (i.e. PS3: Cross, Xbox: A)

---

> GAMEPAD_BUTTON_RIGHT_FACE_LEFT = 8

Gamepad right button left (i.e. PS3: Circle, Xbox: B)

---

> GAMEPAD_BUTTON_LEFT_TRIGGER_1 = 9

Gamepad top/back trigger left (first), it could be a trailing button

---

> GAMEPAD_BUTTON_LEFT_TRIGGER_2 = 10

Gamepad top/back trigger left (second), it could be a trailing button

---

> GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = 11

Gamepad top/back trigger right (one), it could be a trailing button

---

> GAMEPAD_BUTTON_RIGHT_TRIGGER_2 = 12

Gamepad top/back trigger right (second), it could be a trailing button

---

> GAMEPAD_BUTTON_MIDDLE_LEFT = 13

Gamepad center buttons, left one (i.e. PS3: Select)

---

> GAMEPAD_BUTTON_MIDDLE = 14

Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)

---

> GAMEPAD_BUTTON_MIDDLE_RIGHT = 15

Gamepad center buttons, right one (i.e. PS3: Start)

---

> GAMEPAD_BUTTON_LEFT_THUMB = 16

Gamepad joystick pressed button left

---

> GAMEPAD_BUTTON_RIGHT_THUMB = 17

Gamepad joystick pressed button right

---


## Defines - Gamepad axis
> GAMEPAD_AXIS_LEFT_X = 0

Gamepad left stick X axis

---

> GAMEPAD_AXIS_LEFT_Y = 1

Gamepad left stick Y axis

---

> GAMEPAD_AXIS_RIGHT_X = 2

Gamepad right stick X axis

---

> GAMEPAD_AXIS_RIGHT_Y = 3

Gamepad right stick Y axis

---

> GAMEPAD_AXIS_LEFT_TRIGGER = 4

Gamepad back trigger left, pressure level: [1..-1]

---

> GAMEPAD_AXIS_RIGHT_TRIGGER = 5

Gamepad back trigger right, pressure level: [1..-1]

---


## Defines - Material map index
> MATERIAL_MAP_ALBEDO = 0

Albedo material (same as: MATERIAL_MAP_DIFFUSE)

---

> MATERIAL_MAP_METALNESS = 1

Metalness material (same as: MATERIAL_MAP_SPECULAR)

---

> MATERIAL_MAP_NORMAL = 2

Normal material

---

> MATERIAL_MAP_ROUGHNESS = 3

Roughness material

---

> MATERIAL_MAP_OCCLUSION = 4

Ambient occlusion material

---

> MATERIAL_MAP_EMISSION = 5

Emission material

---

> MATERIAL_MAP_HEIGHT = 6

Heightmap material

---

> MATERIAL_MAP_CUBEMAP = 7

Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)

---

> MATERIAL_MAP_IRRADIANCE = 8

Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)

---

> MATERIAL_MAP_PREFILTER = 9

Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)

---

> MATERIAL_MAP_BRDF = 10

Brdf material

---

> MATERIAL_MAP_DIFFUSE = 0

Diffuce material (same as: MATERIAL_MAP_ALBEDO)

---

> MATERIAL_MAP_SPECULAR = 1

Specular material (same as: MATERIAL_MAP_METALNESS)

---


## Defines - Shader location index
> SHADER_LOC_VERTEX_POSITION = 0

Shader location: vertex attribute: position

---

> SHADER_LOC_VERTEX_TEXCOORD01 = 1

Shader location: vertex attribute: texcoord01

---

> SHADER_LOC_VERTEX_TEXCOORD02 = 2

Shader location: vertex attribute: texcoord02

---

> SHADER_LOC_VERTEX_NORMAL = 3

Shader location: vertex attribute: normal

---

> SHADER_LOC_VERTEX_TANGENT = 4

Shader location: vertex attribute: tangent

---

> SHADER_LOC_VERTEX_COLOR = 5

Shader location: vertex attribute: color

---

> SHADER_LOC_MATRIX_MVP = 6

Shader location: matrix uniform: model-view-projection

---

> SHADER_LOC_MATRIX_VIEW = 7

Shader location: matrix uniform: view (camera transform)

---

> SHADER_LOC_MATRIX_PROJECTION = 8

Shader location: matrix uniform: projection

---

> SHADER_LOC_MATRIX_MODEL = 9

Shader location: matrix uniform: model (transform)

---

> SHADER_LOC_MATRIX_NORMAL = 10

Shader location: matrix uniform: normal

---

> SHADER_LOC_VECTOR_VIEW = 11

Shader location: vector uniform: view

---

> SHADER_LOC_COLOR_DIFFUSE = 12

Shader location: vector uniform: diffuse color

---

> SHADER_LOC_COLOR_SPECULAR = 13

Shader location: vector uniform: specular color

---

> SHADER_LOC_COLOR_AMBIENT = 14

Shader location: vector uniform: ambient color

---

> SHADER_LOC_MAP_ALBEDO = 15

Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)

---

> SHADER_LOC_MAP_METALNESS = 16

Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)

---

> SHADER_LOC_MAP_NORMAL = 17

Shader location: sampler2d texture: normal

---

> SHADER_LOC_MAP_ROUGHNESS = 18

Shader location: sampler2d texture: roughness

---

> SHADER_LOC_MAP_OCCLUSION = 19

Shader location: sampler2d texture: occlusion

---

> SHADER_LOC_MAP_EMISSION = 20

Shader location: sampler2d texture: emission

---

> SHADER_LOC_MAP_HEIGHT = 21

Shader location: sampler2d texture: height

---

> SHADER_LOC_MAP_CUBEMAP = 22

Shader location: samplerCube texture: cubemap

---

> SHADER_LOC_MAP_IRRADIANCE = 23

Shader location: samplerCube texture: irradiance

---

> SHADER_LOC_MAP_PREFILTER = 24

Shader location: samplerCube texture: prefilter

---

> SHADER_LOC_MAP_BRDF = 25

Shader location: sampler2d texture: brdf

---

> SHADER_LOC_MAP_DIFFUSE = 15

Shader location: sampler2d texture: diffuce (same as: SHADER_LOC_MAP_ALBEDO)

---

> SHADER_LOC_MAP_SPECULAR = 16

Shader location: sampler2d texture: specular (same as: SHADER_LOC_MAP_METALNESS)

---


## Defines - Shader uniform data type
> SHADER_UNIFORM_FLOAT = 0

Shader uniform type: float

---

> SHADER_UNIFORM_VEC2 = 1

Shader uniform type: vec2 (2 float)

---

> SHADER_UNIFORM_VEC3 = 2

Shader uniform type: vec3 (3 float)

---

> SHADER_UNIFORM_VEC4 = 3

Shader uniform type: vec4 (4 float)

---

> SHADER_UNIFORM_INT = 4

Shader uniform type: int

---

> SHADER_UNIFORM_IVEC2 = 5

Shader uniform type: ivec2 (2 int)

---

> SHADER_UNIFORM_IVEC3 = 6

Shader uniform type: ivec3 (3 int)

---

> SHADER_UNIFORM_IVEC4 = 7

Shader uniform type: ivec4 (4 int)

---

> SHADER_UNIFORM_SAMPLER2D = 8

Shader uniform type: sampler2d

---


## Defines - Shader attribute data types
> SHADER_ATTRIB_FLOAT = 0

Shader attribute type: float

---

> SHADER_ATTRIB_VEC2 = 1

Shader attribute type: vec2 (2 float)

---

> SHADER_ATTRIB_VEC3 = 2

Shader attribute type: vec3 (3 float)

---

> SHADER_ATTRIB_VEC4 = 3

Shader attribute type: vec4 (4 float)

---


## Defines - Pixel formats
> PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1

8 bit per pixel (no alpha)

---

> PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA = 2

8*2 bpp (2 channels)

---

> PIXELFORMAT_UNCOMPRESSED_R5G6B5 = 3

16 bpp

---

> PIXELFORMAT_UNCOMPRESSED_R8G8B8 = 4

24 bpp

---

> PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 = 5

16 bpp (1 bit alpha)

---

> PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 = 6

16 bpp (4 bit alpha)

---

> PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = 7

32 bpp

---

> PIXELFORMAT_UNCOMPRESSED_R32 = 8

32 bpp (1 channel - float)

---

> PIXELFORMAT_UNCOMPRESSED_R32G32B32 = 9

32*3 bpp (3 channels - float)

---

> PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 = 10

32*4 bpp (4 channels - float)

---

> PIXELFORMAT_COMPRESSED_DXT1_RGB = 14

4 bpp (no alpha)

---

> PIXELFORMAT_COMPRESSED_DXT1_RGBA = 15

4 bpp (1 bit alpha)

---

> PIXELFORMAT_COMPRESSED_DXT3_RGBA = 16

8 bpp

---

> PIXELFORMAT_COMPRESSED_DXT5_RGBA = 17

8 bpp

---

> PIXELFORMAT_COMPRESSED_ETC1_RGB = 18

4 bpp

---

> PIXELFORMAT_COMPRESSED_ETC2_RGB = 19

4 bpp

---

> PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA = 20

8 bpp

---

> PIXELFORMAT_COMPRESSED_PVRT_RGB = 21

4 bpp

---

> PIXELFORMAT_COMPRESSED_PVRT_RGBA = 22

4 bpp

---

> PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA = 23

8 bpp

---

> PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA = 24

2 bpp

---


## Defines - Texture parameters: filter mode
> TEXTURE_FILTER_POINT = 0

No filter, just pixel approximation

---

> TEXTURE_FILTER_BILINEAR = 1

Linear filtering

---

> TEXTURE_FILTER_TRILINEAR = 2

Trilinear filtering (linear with mipmaps)

---

> TEXTURE_FILTER_ANISOTROPIC_4X = 3

Anisotropic filtering 4x

---

> TEXTURE_FILTER_ANISOTROPIC_8X = 4

Anisotropic filtering 8x

---

> TEXTURE_FILTER_ANISOTROPIC_16X = 5

Anisotropic filtering 16x

---


## Defines - Texture parameters: wrap mode
> TEXTURE_WRAP_REPEAT = 0

Repeats texture in tiled mode

---

> TEXTURE_WRAP_CLAMP = 1

Clamps texture to edge pixel in tiled mode

---

> TEXTURE_WRAP_MIRROR_REPEAT = 2

Mirrors and repeats the texture in tiled mode

---

> TEXTURE_WRAP_MIRROR_CLAMP = 3

Mirrors and clamps to border the texture in tiled mode

---


## Defines - Cubemap layouts
> CUBEMAP_LAYOUT_AUTO_DETECT = 0

Automatically detect layout type

---

> CUBEMAP_LAYOUT_LINE_VERTICAL = 1

Layout is defined by a vertical line with faces

---

> CUBEMAP_LAYOUT_LINE_HORIZONTAL = 2

Layout is defined by a horizontal line with faces

---

> CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR = 3

Layout is defined by a 3x4 cross with cubemap faces

---

> CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE = 4

Layout is defined by a 4x3 cross with cubemap faces

---

> CUBEMAP_LAYOUT_PANORAMA = 5

Layout is defined by a panorama image (equirrectangular map)

---


## Defines - Font type, defines generation method
> FONT_DEFAULT = 0

Default font generation, anti-aliased

---

> FONT_BITMAP = 1

Bitmap font generation, no anti-aliasing

---

> FONT_SDF = 2

SDF font generation, requires external shader

---


## Defines - Color blending modes (pre-defined)
> BLEND_ALPHA = 0

Blend textures considering alpha (default)

---

> BLEND_ADDITIVE = 1

Blend textures adding colors

---

> BLEND_MULTIPLIED = 2

Blend textures multiplying colors

---

> BLEND_ADD_COLORS = 3

Blend textures adding colors (alternative)

---

> BLEND_SUBTRACT_COLORS = 4

Blend textures subtracting colors (alternative)

---

> BLEND_ALPHA_PREMULTIPLY = 5

Blend premultiplied textures considering alpha

---

> BLEND_CUSTOM = 6

Blend textures using custom src/dst factors (use rlSetBlendFactors())

---

> BLEND_CUSTOM_SEPARATE = 7

Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

---


## Defines - Gesture
> GESTURE_NONE = 0

No gesture

---

> GESTURE_TAP = 1

Tap gesture

---

> GESTURE_DOUBLETAP = 2

Double tap gesture

---

> GESTURE_HOLD = 4

Hold gesture

---

> GESTURE_DRAG = 8

Drag gesture

---

> GESTURE_SWIPE_RIGHT = 16

Swipe right gesture

---

> GESTURE_SWIPE_LEFT = 32

Swipe left gesture

---

> GESTURE_SWIPE_UP = 64

Swipe up gesture

---

> GESTURE_SWIPE_DOWN = 128

Swipe down gesture

---

> GESTURE_PINCH_IN = 256

Pinch in gesture

---

> GESTURE_PINCH_OUT = 512

Pinch out gesture

---


## Defines - Camera system modes
> CAMERA_CUSTOM = 0

Custom camera

---

> CAMERA_FREE = 1

Free camera

---

> CAMERA_ORBITAL = 2

Orbital camera

---

> CAMERA_FIRST_PERSON = 3

First person camera

---

> CAMERA_THIRD_PERSON = 4

Third person camera

---


## Defines - Camera projection
> CAMERA_PERSPECTIVE = 0

Perspective projection

---

> CAMERA_ORTHOGRAPHIC = 1

Orthographic projection

---


## Defines - N-patch layout
> NPATCH_NINE_PATCH = 0

Npatch layout: 3x3 tiles

---

> NPATCH_THREE_PATCH_VERTICAL = 1

Npatch layout: 1x3 tiles

---

> NPATCH_THREE_PATCH_HORIZONTAL = 2

Npatch layout: 3x1 tiles

---


## Defines - Colors
LIGHTGRAY = { 200, 200, 200, 255 }

Light Gray

---

GRAY = { 130, 130, 130, 255 }

Gray

---

DARKGRAY = { 80, 80, 80, 255 }

Dark Gray

---

YELLOW = { 253, 249, 0, 255 }

Yellow

---

GOLD = { 255, 203, 0, 255 }

Gold

---

ORANGE = { 255, 161, 0, 255 }

Orange

---

PINK = { 255, 109, 194, 255 }

Pink

---

RED = { 230, 41, 55, 255 }

Red

---

MAROON = { 190, 33, 55, 255 }

Maroon

---

GREEN = { 0, 228, 48, 255 }

Green

---

LIME = { 0, 158, 47, 255 }

Lime

---

DARKGREEN = { 0, 117, 44, 255 }

Dark Green

---

SKYBLUE = { 102, 191, 255, 255 }

Sky Blue

---

BLUE = { 0, 121, 241, 255 }

Blue

---

DARKBLUE = { 0, 82, 172, 255 }

Dark Blue

---

PURPLE = { 200, 122, 255, 255 }

Purple

---

VIOLET = { 135, 60, 190, 255 }

Violet

---

DARKPURPLE = { 112, 31, 126, 255 }

Dark Purple

---

BEIGE = { 211, 176, 131, 255 }

Beige

---

BROWN = { 127, 106, 79, 255 }

Brown

---

DARKBROWN = { 76, 63, 47, 255 }

Dark Brown

---

WHITE = { 255, 255, 255, 255 }

White

---

BLACK = { 0, 0, 0, 255 }

Black

---

BLANK = { 0, 0, 0, 0 }

Blank (Transparent)

---

MAGENTA = { 255, 0, 255, 255 }

Magenta

---

RAYWHITE = { 245, 245, 245, 255 }

My own White (raylib logo)

---


## Defines - Math
> PI = 3.1415927410126

Pi

---

> DEG2RAD = 0.017453292384744

Degrees to radians

---

> RAD2DEG = 57.295776367188

Radians to degrees

---


## Defines - Gui control state
> STATE_NORMAL = 0

---

> STATE_FOCUSED = 1

---

> STATE_PRESSED = 2

---

> STATE_DISABLED = 3

---


## Defines - Gui control text alignment
> TEXT_ALIGN_LEFT = 0

---

> TEXT_ALIGN_CENTER = 1

---

> TEXT_ALIGN_RIGHT = 2

---


## Defines - Gui control text alignment vertical
> TEXT_ALIGN_TOP = 0

---

> TEXT_ALIGN_MIDDLE = 1

---

> TEXT_ALIGN_BOTTOM = 2

---


## Defines - Gui control text wrap mode
> TEXT_WRAP_NONE = 0

---

> TEXT_WRAP_CHAR = 1

---

> TEXT_WRAP_WORD = 2

---


## Defines - Gui controls
> DEFAULT = 0

---

> LABEL = 1

Used also for: LABELBUTTON

---

> BUTTON = 2

---

> TOGGLE = 3

Used also for: TOGGLEGROUP

---

> SLIDER = 4

Used also for: SLIDERBAR

---

> PROGRESSBAR = 5

---

> CHECKBOX = 6

---

> COMBOBOX = 7

---

> DROPDOWNBOX = 8

---

> TEXTBOX = 9

Used also for: TEXTBOXMULTI

---

> VALUEBOX = 10

---

> SPINNER = 11

Uses: BUTTON, VALUEBOX

---

> LISTVIEW = 12

---

> COLORPICKER = 13

---

> SCROLLBAR = 14

---

> STATUSBAR = 15

---


## Defines - Gui base properties for every control
> BORDER_COLOR_NORMAL = 0

---

> BASE_COLOR_NORMAL = 1

---

> TEXT_COLOR_NORMAL = 2

---

> BORDER_COLOR_FOCUSED = 3

---

> BASE_COLOR_FOCUSED = 4

---

> TEXT_COLOR_FOCUSED = 5

---

> BORDER_COLOR_PRESSED = 6

---

> BASE_COLOR_PRESSED = 7

---

> TEXT_COLOR_PRESSED = 8

---

> BORDER_COLOR_DISABLED = 9

---

> BASE_COLOR_DISABLED = 10

---

> TEXT_COLOR_DISABLED = 11

---

> BORDER_WIDTH = 12

---

> TEXT_PADDING = 13

---

> TEXT_ALIGNMENT = 14

---


## Defines - Gui extended properties depend on control
> TEXT_SIZE = 16

Text size (glyphs max height)

---

> TEXT_SPACING = 17

Text spacing between glyphs

---

> LINE_COLOR = 18

Line control color

---

> BACKGROUND_COLOR = 19

Background color

---

> TEXT_LINE_SPACING = 20

Text spacing between lines

---

> TEXT_ALIGNMENT_VERTICAL = 21

Text vertical alignment inside text bounds (after border and padding)

---

> TEXT_WRAP_MODE = 22

Text wrap-mode inside text bounds

---


## Defines - Gui Toggle/ToggleGroup
> GROUP_PADDING = 16

ToggleGroup separation between toggles

---


## Defines - Gui Slider/SliderBar
> SLIDER_WIDTH = 16

Slider size of internal bar

---

> SLIDER_PADDING = 17

Slider/SliderBar internal bar padding

---


## Defines - Gui ProgressBar
> PROGRESS_PADDING = 16

ProgressBar internal padding

---


## Defines - Gui ScrollBar
> ARROWS_SIZE = 16

---

> ARROWS_VISIBLE = 17

---

> SCROLL_SLIDER_PADDING = 18

(SLIDERBAR, SLIDER_PADDING)

---

> SCROLL_SLIDER_SIZE = 19

---

> SCROLL_PADDING = 20

---

> SCROLL_SPEED = 21

---


## Defines - Gui CheckBox
> CHECK_PADDING = 16

CheckBox internal check padding

---


## Defines - Gui ComboBox
> COMBO_BUTTON_WIDTH = 16

ComboBox right button width

---

> COMBO_BUTTON_SPACING = 17

ComboBox button separation

---


## Defines - Gui DropdownBox
> ARROW_PADDING = 16

DropdownBox arrow separation from border and items

---

> DROPDOWN_ITEMS_SPACING = 17

DropdownBox items separation

---


## Defines - Gui TextBox/TextBoxMulti/ValueBox/Spinner
> TEXT_READONLY = 16

TextBox in read-only mode: 0-text editable, 1-text no-editable

---


## Defines - Gui Spinner
> SPIN_BUTTON_WIDTH = 16

Spinner left/right buttons width

---

> SPIN_BUTTON_SPACING = 17

Spinner buttons separation

---


## Defines - Gui ListView
> LIST_ITEMS_HEIGHT = 16

ListView items height

---

> LIST_ITEMS_SPACING = 17

ListView items separation

---

> SCROLLBAR_WIDTH = 18

ListView scrollbar size (usually width)

---

> SCROLLBAR_SIDE = 19

ListView scrollbar side (0-left, 1-right)

---


## Defines - Gui ColorPicker
> COLOR_SELECTOR_SIZE = 16

---

> HUEBAR_WIDTH = 17

ColorPicker right hue bar width

---

> HUEBAR_PADDING = 18

ColorPicker right hue bar separation from panel

---

> HUEBAR_SELECTOR_HEIGHT = 19

ColorPicker right hue bar selector height

---

> HUEBAR_SELECTOR_OVERFLOW = 20

ColorPicker right hue bar selector overflow

---


## Defines - Light type
> LIGHT_DIRECTIONAL = 0

Directional light

---

> LIGHT_POINT = 1

Point light

---


## Defines - RLGL Default internal render batch elements limits
> RL_DEFAULT_BATCH_BUFFER_ELEMENTS = 8192

Default internal render batch elements limits

---

> RL_DEFAULT_BATCH_BUFFERS = 1

Default number of batch buffers (multi-buffering)

---

> RL_DEFAULT_BATCH_DRAWCALLS = 256

Default number of batch draw calls (by state changes: mode, texture)

---

> RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS = 4

Maximum number of textures units that can be activated on batch drawing (SetShaderValueTexture())

---


## Defines - RLGL Internal Matrix stack
> RL_MAX_MATRIX_STACK_SIZE = 32

Maximum size of internal Matrix stack

---


## Defines - RLGL Shader limits
> RL_MAX_SHADER_LOCATIONS = 32

Maximum number of shader locations supported

---


## Defines - RLGL Projection matrix culling
> RL_CULL_DISTANCE_NEAR = 0.01

Default projection matrix near cull distance

---

> RL_CULL_DISTANCE_FAR = 1000.0

Default projection matrix far cull distance

---


## Defines - RLGL Texture parameters
> RL_TEXTURE_WRAP_S = 10242

GL_TEXTURE_WRAP_S

---

> RL_TEXTURE_WRAP_T = 10243

GL_TEXTURE_WRAP_T

---

> RL_TEXTURE_MAG_FILTER = 10240

GL_TEXTURE_MAG_FILTER

---

> RL_TEXTURE_MIN_FILTER = 10241

GL_TEXTURE_MIN_FILTER

---

> RL_TEXTURE_FILTER_NEAREST = 9728

GL_NEAREST

---

> RL_TEXTURE_FILTER_LINEAR = 9729

GL_LINEAR

---

> RL_TEXTURE_FILTER_MIP_NEAREST = 9984

GL_NEAREST_MIPMAP_NEAREST

---

> RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR = 9986

GL_NEAREST_MIPMAP_LINEAR

---

> RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST = 9985

GL_LINEAR_MIPMAP_NEAREST

---

> RL_TEXTURE_FILTER_MIP_LINEAR = 9987

GL_LINEAR_MIPMAP_LINEAR

---

> RL_TEXTURE_FILTER_ANISOTROPIC = 12288

Anisotropic filter (custom identifier)

---

> RL_TEXTURE_MIPMAP_BIAS_RATIO = 16384

Texture mipmap bias, percentage ratio (custom identifier)

---

> RL_TEXTURE_WRAP_REPEAT = 10497

GL_REPEAT

---

> RL_TEXTURE_WRAP_CLAMP = 33071

GL_CLAMP_TO_EDGE

---

> RL_TEXTURE_WRAP_MIRROR_REPEAT = 33648

GL_MIRRORED_REPEAT

---

> RL_TEXTURE_WRAP_MIRROR_CLAMP = 34626

GL_MIRROR_CLAMP_EXT

---


## Defines - RLGL Matrix modes (equivalent to OpenGL)
> RL_MODELVIEW = 5888

GL_MODELVIEW

---

> RL_PROJECTION = 5889

GL_PROJECTION

---

> RL_TEXTURE = 5890

GL_TEXTURE

---


## Defines - RLGL Primitive assembly draw modes
> RL_LINES = 1

GL_LINES

---

> RL_TRIANGLES = 4

GL_TRIANGLES

---

> RL_QUADS = 7

GL_QUADS

---


## Defines - RLGL GL equivalent data types
> RL_UNSIGNED_BYTE = 5121

GL_UNSIGNED_BYTE

---

> RL_FLOAT = 5126

GL_FLOAT

---


## Defines - RLGL GL buffer usage hint
> RL_STREAM_DRAW = 35040

GL_STREAM_DRAW

---

> RL_STREAM_READ = 35041

GL_STREAM_READ

---

> RL_STREAM_COPY = 35042

GL_STREAM_COPY

---

> RL_STATIC_DRAW = 35044

GL_STATIC_DRAW

---

> RL_STATIC_READ = 35045

GL_STATIC_READ

---

> RL_STATIC_COPY = 35046

GL_STATIC_COPY

---

> RL_DYNAMIC_DRAW = 35048

GL_DYNAMIC_DRAW

---

> RL_DYNAMIC_READ = 35049

GL_DYNAMIC_READ

---

> RL_DYNAMIC_COPY = 35050

GL_DYNAMIC_COPY

---


## Defines - RLGL Shader type
> RL_FRAGMENT_SHADER = 35632

GL_FRAGMENT_SHADER

---

> RL_VERTEX_SHADER = 35633

GL_VERTEX_SHADER

---

> RL_COMPUTE_SHADER = 37305

GL_COMPUTE_SHADER

---


## Defines - RLGL GL blending factors
> RL_ZERO = 0

GL_ZERO

---

> RL_ONE = 1

GL_ONE

---

> RL_SRC_COLOR = 768

GL_SRC_COLOR

---

> RL_ONE_MINUS_SRC_COLOR = 769

GL_ONE_MINUS_SRC_COLOR

---

> RL_SRC_ALPHA = 770

GL_SRC_ALPHA

---

> RL_ONE_MINUS_SRC_ALPHA = 771

GL_ONE_MINUS_SRC_ALPHA

---

> RL_DST_ALPHA = 772

GL_DST_ALPHA

---

> RL_ONE_MINUS_DST_ALPHA = 773

GL_ONE_MINUS_DST_ALPHA

---

> RL_DST_COLOR = 774

GL_DST_COLOR

---

> RL_ONE_MINUS_DST_COLOR = 775

GL_ONE_MINUS_DST_COLOR

---

> RL_SRC_ALPHA_SATURATE = 776

GL_SRC_ALPHA_SATURATE

---

> RL_CONSTANT_COLOR = 32769

GL_CONSTANT_COLOR

---

> RL_ONE_MINUS_CONSTANT_COLOR = 32770

GL_ONE_MINUS_CONSTANT_COLOR

---

> RL_CONSTANT_ALPHA = 32771

GL_CONSTANT_ALPHA

---

> RL_ONE_MINUS_CONSTANT_ALPHA = 32772

GL_ONE_MINUS_CONSTANT_ALPHA

---


## Defines - RLGL GL blending functions/equations
> RL_FUNC_ADD = 32774

GL_FUNC_ADD

---

> RL_MIN = 32775

GL_MIN

---

> RL_MAX = 32776

GL_MAX

---

> RL_FUNC_SUBTRACT = 32778

GL_FUNC_SUBTRACT

---

> RL_FUNC_REVERSE_SUBTRACT = 32779

GL_FUNC_REVERSE_SUBTRACT

---

> RL_BLEND_EQUATION = 32777

GL_BLEND_EQUATION

---

> RL_BLEND_EQUATION_RGB = 32777

GL_BLEND_EQUATION_RGB // (Same as BLEND_EQUATION)

---

> RL_BLEND_EQUATION_ALPHA = 34877

GL_BLEND_EQUATION_ALPHA

---

> RL_BLEND_DST_RGB = 32968

GL_BLEND_DST_RGB

---

> RL_BLEND_SRC_RGB = 32969

GL_BLEND_SRC_RGB

---

> RL_BLEND_DST_ALPHA = 32970

GL_BLEND_DST_ALPHA

---

> RL_BLEND_SRC_ALPHA = 32971

GL_BLEND_SRC_ALPHA

---

> RL_BLEND_COLOR = 32773

GL_BLEND_COLOR

---


## Defines - RLGL GlVersion
> RL_OPENGL_11 = 1

OpenGL 1.1

---

> RL_OPENGL_21 = 2

OpenGL 2.1 (GLSL 120)

---

> RL_OPENGL_33 = 3

OpenGL 3.3 (GLSL 330)

---

> RL_OPENGL_43 = 4

OpenGL 4.3 (using GLSL 330)

---

> RL_OPENGL_ES_20 = 5

OpenGL ES 2.0 (GLSL 100)

---


## Defines - RLGL Framebuffer attachment type
> RL_ATTACHMENT_COLOR_CHANNEL0 = 0

Framebuffer attachment type: color 0

---

> RL_ATTACHMENT_COLOR_CHANNEL1 = 1

Framebuffer attachment type: color 1

---

> RL_ATTACHMENT_COLOR_CHANNEL2 = 2

Framebuffer attachment type: color 2

---

> RL_ATTACHMENT_COLOR_CHANNEL3 = 3

Framebuffer attachment type: color 3

---

> RL_ATTACHMENT_COLOR_CHANNEL4 = 4

Framebuffer attachment type: color 4

---

> RL_ATTACHMENT_COLOR_CHANNEL5 = 5

Framebuffer attachment type: color 5

---

> RL_ATTACHMENT_COLOR_CHANNEL6 = 6

Framebuffer attachment type: color 6

---

> RL_ATTACHMENT_COLOR_CHANNEL7 = 7

Framebuffer attachment type: color 7

---

> RL_ATTACHMENT_DEPTH = 100

Framebuffer attachment type: depth

---

> RL_ATTACHMENT_STENCIL = 200

Framebuffer attachment type: stencil

---


## Defines - RLGL Framebuffer texture attachment type
> RL_ATTACHMENT_CUBEMAP_POSITIVE_X = 0

Framebuffer texture attachment type: cubemap, +X side

---

> RL_ATTACHMENT_CUBEMAP_NEGATIVE_X = 1

Framebuffer texture attachment type: cubemap, -X side

---

> RL_ATTACHMENT_CUBEMAP_POSITIVE_Y = 2

Framebuffer texture attachment type: cubemap, +Y side

---

> RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y = 3

Framebuffer texture attachment type: cubemap, -Y side

---

> RL_ATTACHMENT_CUBEMAP_POSITIVE_Z = 4

Framebuffer texture attachment type: cubemap, +Z side

---

> RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z = 5

Framebuffer texture attachment type: cubemap, -Z side

---

> RL_ATTACHMENT_TEXTURE2D = 100

Framebuffer texture attachment type: texture2d

---

> RL_ATTACHMENT_RENDERBUFFER = 200

Framebuffer texture attachment type: renderbuffer

---


## Defines - RLGL CullMode
> RL_CULL_FACE_FRONT = 0

---

> RL_CULL_FACE_BACK = 1

---


## Defines - OpenGL
> GL_COLOR_BUFFER_BIT = 16384

---

> GL_DEPTH_BUFFER_BIT = 256

---

> GL_STENCIL_BUFFER_BIT = 1024

---

> GL_NEAREST = 9728

---

> GL_LINEAR = 9729

---


## Defines - CBuffer Data types
> BUFFER_UNSIGNED_CHAR = 0

C type unsigned char

---

> BUFFER_UNSIGNED_SHORT = 1

C type unsigned short

---

> BUFFER_UNSIGNED_INT = 2

C type unsigned int

---

> BUFFER_CHAR = 3

C type char

---

> BUFFER_SHORT = 4

C type short

---

> BUFFER_INT = 5

C type int

---

> BUFFER_FLOAT = 6

C type float

---

> BUFFER_DOUBLE = 7

C type double

---


## Defines - Keyboard keys (US keyboard layout)
> GLFW_KEY_UNKNOWN = -1

Key: Unknown

---


## Defines - GLFW API tokens.
> GLFW_RELEASE = 0

The key or mouse button was released

---

> GLFW_PRESS = 1

The key or mouse button was pressed

---

> GLFW_REPEAT = 2

The key was held down until it repeated

---

> GLFW_CONNECTED = 262145

Joystick connected

---

> GLFW_DISCONNECTED = 262146

Joystick disconnected

---


## Defines - GLFW Window Events.
> GLFW_WINDOW_SIZE_EVENT = 0

GLFW event window size changed

---

> GLFW_WINDOW_MAXIMIZE_EVENT = 1

GLFW event window maximize

---

> GLFW_WINDOW_ICONYFY_EVENT = 2

GLFW event window iconify

---

> GLFW_WINDOW_FOCUS_EVENT = 3

GLFW event window focus

---

> GLFW_WINDOW_DROP_EVENT = 4

GLFW event window drop

---


## Defines - GLFW Input Events.
> GLFW_KEY_EVENT = 5

GLFW event keyboard key

---

> GLFW_CHAR_EVENT = 6

GLFW event Unicode character

---

> GLFW_MOUSE_BUTTON_EVENT = 7

GLFW event mouse button

---

> GLFW_MOUSE_CURSOR_POS_EVENT = 8

GLFW event cursor position

---

> GLFW_MOUSE_SCROLL_EVENT = 9

GLFW event mouse scroll

---

> GLFW_CURSOR_ENTER_EVENT = 10

GLFW event cursor enter/leave

---

> GLFW_JOYSTICK_EVENT = 11

GLFW event joystick

---


## Defines - GLFW Pen Tablet Events. NOTE! Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445.

assignGlobalInt = nil

// GLFW event pen tablet data

---


assignGlobalInt = nil

// GLFW event pen tablet cursor

---


assignGlobalInt = nil

// GLFW event pen tablet proximity

---


## Core - Window-related functions

---

> RL.CloseWindow()

Close window and unload OpenGL context and free all resources

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

> resized = RL.IsWindowResized()

Check if window has been resized from last frame

- Success return bool

---

> state = RL.IsWindowState( int flag )

Check if one specific window flag is enabled (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool

---

> RL.SetWindowState( int flag )

Set window configuration state using flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

---

> resized = RL.ClearWindowState( int flag )

Clear window configuration state flags (FLAG_FULLSCREEN_MODE, FLAG_WINDOW_RESIZABLE...)

- Success return bool

---

> RL.ToggleFullscreen()

Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)

---

> RL.ToggleBorderlessWindowed()

Toggle window state: borderless windowed (only PLATFORM_DESKTOP)

---

> RL.MaximizeWindow()

Set window state: maximized, if resizable (only PLATFORM_DESKTOP)

---

> RL.MinimizeWindow()

Set window state: minimized, if resizable (only PLATFORM_DESKTOP)

---

> RL.RestoreWindow()

Set window state: not minimized/maximized (only PLATFORM_DESKTOP)

---

> RL.SetWindowIcon( Image image )

Set icon for window (Only PLATFORM_DESKTOP)

---

> RL.SetWindowIcons( Image{} images )

Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)

---

> RL.SetWindowTitle( string title )

Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)

---

> RL.SetWindowPosition( Vector2 pos )

Set window position on screen

---

> RL.SetWindowMonitor( int monitor )

Set monitor for the current window

---

> RL.SetWindowMinSize( Vector2 size )

Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)

---

> RL.SetWindowMaxSize( Vector2 size )

Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)

---

> RL.SetWindowSize( Vector2 size )

Set window dimensions

---

> RL.SetWindowOpacity( float opacity )

Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)

---

> RL.SetWindowFocused()

Set window focused (only PLATFORM_DESKTOP)

---

> windowHandle = RL.GetWindowHandle()

Get native window handle. Return as lightuserdata

- Success return lightuserdata

---

> size = RL.GetScreenSize()

Get screen size

- Success return Vector2

---

> size = RL.GetRenderSize()

Get render size

- Success return Vector2

---

> count = RL.GetMonitorCount()

Get number of connected monitors

- Success return int

---

> monitor = RL.GetCurrentMonitor()

Get current connected monitor

- Success return int

---

> position = RL.GetMonitorPosition( int monitor )

Get specified monitor position

- Success return Vector2

---

> size = RL.GetMonitorSize( int monitor )

Get specified monitor size

- Success return Vector2

---

> size = RL.GetMonitorPhysicalSize( int monitor )

Get specified monitor physical size in millimetres

- Success return Vector2

---

> refreshRate = RL.GetMonitorRefreshRate( int monitor )

Get specified monitor refresh rate

- Success return int

---

> position = RL.GetWindowPosition()

Get window position on monitor

- Success return Vector2

---

> dpi = RL.GetWindowScaleDPI()

Get window scale DPI factor

- Success return Vector2

---

> name = RL.GetMonitorName( int monitor )

Get the human-readable, UTF-8 encoded name of the specified monitor

- Success return string

---

> RL.SetClipboardText( string text )

Set clipboard text content

---

> text = RL.GetClipboardText()

Get clipboard text content

- Success return string

---

## Core - Cursor-related functions

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

## Core - Drawing-related functions

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

> RL.BeginMode2D( camera2D camera )

Begin 2D mode with custom camera (2D)

---

> RL.EndMode2D()

Ends 2D mode with custom camera

---

> RL.BeginMode3D( camera3D camera )

Begin 3D mode with custom camera (3D)

---

> RL.EndMode3D()

Ends 3D mode and returns to default 2D orthographic mode

---

> RL.BeginTextureMode( RenderTexture target )

Begin drawing to render texture

---

> RL.EndTextureMode()

Ends drawing to render texture

---

> RL.BeginShaderMode( Shader shader )

Begin custom shader drawing

---

> RL.EndShaderMode()

End custom shader drawing (use default shader)

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

## Core - Shader management functions

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

> isReady = RL.IsShaderReady( Shader shader )

Check if a shader is ready

- Success return bool

---

> shaderId = RL.GetShaderId( Shader shader )

Get shader program id

- Success return int

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

> RL.UnloadShader( Shader shader )

Unload shader from GPU memory (VRAM)

---

## Core - Screen-space-related functions

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

## Core - Timing-related functions

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

## Core - Random values generation functions

---

> RL.SetRandomSeed( int seed )

Set the seed for the random number generator

---

> time = RL.GetRandomValue( int min, int max )

Get a random value between min and max (both included)

- Success return int

---

> sequence = RL.LoadRandomSequence( int count, int min, int max )

Load random values sequence, no values repeated

- Success return int{}

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

Open URL with default system browser (if available)

---

> enabled = RL.IsGCUnloadEnabled()

Check if Lua garbage collection is set to unload object data

- Success return bool

---

> RL.SetGCUnload( bool enabled )

Set Lua garbage collection to unload object data

---

## Core - Files management functions

---

> buffer = RL.LoadFileData( string fileName )

Load file data as byte array (read). Buffer type is BUFFER_UNSIGNED_CHAR

- Success return Buffer

---

> success = RL.SaveFileData( string fileName, buffer Buffer )

Save data to file from byte array (write), returns true on success

- Success return bool

---

> success = RL.ExportDataAsCode( Buffer buffer, string fileName )

Export data to code (.h), returns true on success

- Success return bool

---

> text = RL.LoadFileText( string fileName )

Load text data from file (read)

- Success return string

---

> success = RL.SaveFileText( string fileName, string text )

Save text data to file (write), returns true on success

- Success return bool

---

## Core - Files system functions

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

> directory = RL.GetApplicationDirectory()

Get the directory of the running application (uses static string)

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

## Core - Compression/Encoding functionality

---

> compData = RL.CompressData( Buffer buffer )

Compress data (DEFLATE algorithm)

- Success return Buffer

---

> decompData = RL.DecompressData( Buffer compData )

Decompress data (DEFLATE algorithm).

- Success Buffer 

---

> encodedData, outputSize = RL.EncodeDataBase64( string data )

Encode data to Base64 string

- Success return string, int

---

> decodedData, outputSize = RL.DecodeDataBase64( string data )

Decode Base64 string data

- Success return string, int

---

## Core - Input-related functions: keyboard

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

## Core - Input-related functions: gamepads

---

> available = RL.IsGamepadAvailable( int gamepad )

Detect if a gamepad is available

- Success return bool

---

> name = RL.GetGamepadName( int gamepad )

Return gamepad internal name id

- Success return string

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

> result = RL.SetGamepadMappings( string mappings )

Set internal gamepad mappings (SDL_GameControllerDB)

- Success return int

---

## Core - Input-related functions: mouse

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

## Core - Input-related functions: touch

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

## Core - Input-related functions: gestures

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

## Core - Camera2D System functions

---

> camera2D = RL.CreateCamera2D()

Return camera2D set to default configuration

- Success return Camera2D

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

## Core - Camera3D System functions

---

> camera = RL.CreateCamera3D()

Return camera3D id set to default configuration

- Success return int

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

## Core - Buffer management functions

---

> buffer = RL.LoadBuffer( data{} buffer, int type )

Load Buffer. Type should be one of the Buffer types. Empty buffer will set data to NULL.

- Success return Buffer

---

> buffer = RL.LoadBufferFromFile( string path, type int )

Read buffer data from binary file

- Failure return nil
- Success return Buffer

---

> buffer = RL.LoadBufferFromString( string buffer )

Read buffer data from string

- Failure return nil
- Success return Buffer

---

> RL.UnloadBuffer( Buffer buffer )

Unload buffer data

---

> data = RL.GetBufferData( Buffer buffer, int position, int length )

Get buffer data as table in the format it was stored

- Success return data{}

---

> type = RL.GetBufferType( Buffer buffer )

Get buffer type

- Success return int

---

> size = RL.GetBufferSize( Buffer buffer )

Get buffer size in bytes

- Success return int

---

> size = RL.GetBufferElementSize( Buffer buffer )

Get buffer element size in bytes

- Success return int

---

> length = RL.GetBufferLength( Buffer buffer )

Get buffer element count

- Success return int

---

> RL.ExportBuffer( Buffer buffer, string path )

Write buffer data to binary file

---

## Shapes - Basic shapes drawing functions

---

> RL.SetShapesTexture( Texture texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

---

> RL.DrawPixel( Vector2 pos, Color color )

Draw a pixel

---

> RL.DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness

---

> RL.DrawLineStrip( Vector2{} points, Color color )

Draw lines sequence

---

> RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out

---

> RL.DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle

---

> RL.DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle

---

> RL.DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline

---

> RL.DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle

---

> RL.DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline

---

> RL.DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse

---

> RL.DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline

---

> RL.DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring

---

> RL.DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline

---

> RL.DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle

---

> RL.DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters

---

> RL.DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle

---

> RL.DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle

---

> RL.DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors

---

> RL.DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline

---

> RL.DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters

---

> RL.DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges

---

> RL.DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline

---

> RL.DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle (Vertex in counter-clockwise order!)

---

> RL.DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline (Vertex in counter-clockwise order!)

---

> RL.DrawTriangleFan( Vector2{} points, Color color )

Draw a triangle fan defined by points (first vertex is the center)

---

> RL.DrawTriangleStrip( Vector2{} points, Color color )

Draw a triangle strip defined by points

---

> RL.DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon (Vector version)

---

> RL.DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides

---

> RL.DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters

---

## Shapes - Splines drawing functions

---

> RL.DrawSplineLinear( Vector2{} points, float thick, Color color )

Draw spline: Linear, minimum 2 points

---

> RL.DrawSplineBasis( Vector2{} points, float thick, Color color )

Draw spline: B-Spline, minimum 4 points

---

> RL.DrawSplineCatmullRom( Vector2{} points, float thick, Color color )

Draw spline: Catmull-Rom, minimum 4 points

---

> RL.DrawSplineBezierQuadratic( Vector2{} points, float thick, Color color )

Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]

---

> RL.DrawSplineBezierCubic( Vector2{} points, float thick, Color color )

Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]

---

> RL.DrawSplineSegmentLinear( Vector2 p1, Vector2 p2, float thick, Color color )

Draw spline segment: Linear, 2 points

---

> RL.DrawSplineSegmentBasis( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color )

Draw spline segment: B-Spline, 4 points

---

> RL.DrawSplineSegmentCatmullRom( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color )

Draw spline segment: Catmull-Rom, 4 points

---

> RL.DrawSplineSegmentBezierQuadratic( Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color )

Draw spline segment: Quadratic Bezier, 2 points, 1 control point

---

> RL.DrawSplineSegmentBezierCubic( Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color )

Draw spline segment: Cubic Bezier, 2 points, 2 control points

---

## Shapes - Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]

---

> point = RL.GetSplinePointLinear( Vector2 startPos, Vector2 endPos, float t )

Get (evaluate) spline point: Linear

- Success return Vector2

---

> point = RL.GetSplinePointBasis( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t )

Get (evaluate) spline point: B-Spline

- Success return Vector2

---

> point = RL.GetSplinePointCatmullRom( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t )

Get (evaluate) spline point: Catmull-Rom

- Success return Vector2

---

> point = RL.GetSplinePointBezierQuad( Vector2 p1, Vector2 c2, Vector2 p3, float t )

Get (evaluate) spline point: Quadratic Bezier

- Success return Vector2

---

> point = RL.GetSplinePointBezierCubic( Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t )

Get (evaluate) spline point: Cubic Bezier

- Success return Vector2

---

## Shapes - Basic shapes collision detection functions

---

> collision = RL.CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Success return bool

---

> collision = RL.CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Success return bool

---

> collision = RL.CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Success return bool

---

> collision = RL.CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Success return bool

---

> collision = RL.CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Success return bool

---

> collision = RL.CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Success return bool

---

> collision = RL.CheckCollisionPointPoly( Vector2 point, Vector2{} points )

Check if point is within a polygon described by array of vertices

- Success return bool

---

> collision, position = RL.CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Success return bool, Vector2

---

> collision = RL.CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Success return bool

---

> rectangle = RL.GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Success return Rectangle

---

## Textures - Image loading functions

---

> image = RL.LoadImage( string fileName )

Load image from file into CPU memory (RAM)

- Failure return nil
- Success return Image

---

> image = RL.LoadImageRaw( string fileName, Vector2 size, int format, int headerSize )

Load image from RAW file data

- Failure return nil
- Success return Image

---

> image = RL.LoadImageSvg( string fileNameOrString, Vector2 size )

Load image from SVG file data or string with specified size

- Success return Image

---

> image, frameCount = RL.LoadImageAnim( string fileName )

Load image sequence from file (frames appended to image.data). All frames are returned in RGBA format

- Failure return nil
- Success return Image, int

---

> image, frameCount = RL.LoadImageFromMemory( string fileType, Buffer data )

Load image from memory buffer, fileType refers to extension: i.e. '.png'

- Success return Image

---

> image, frameCount = RL.LoadImageFromData( Buffer data, Vector2 size, int mipmaps, int format )

Load image from data

- Success return Image

---

> image = RL.LoadImageFromTexture( Texture texture )

Load image from GPU texture data

- Success return Image

---

> image = RL.LoadImageFromScreen()

Load image from screen buffer and (screenshot)

- Success return Image

---

> isReady = RL.IsImageReady( Image image )

Check if an image is ready

- Success return bool

---

> RL.UnloadImage( Image image )

Unload image from CPU memory (RAM)

---

> success = RL.ExportImage( Image image, string fileName )

Export image data to file, returns true on success

- Success return bool

---

> buffer = RL.ExportImageToMemory( Image image, string fileType )

Export image to memory buffer

- Success return Buffer

---

> success = RL.ExportImageAsCode( Image image, string fileName )

Export image as code file defining an array of bytes, returns true on success

- Success return bool

---

## Textures - Image generation functions

---

> image = RL.GenImageColor( Vector2 size, Color color )

Generate image: plain color

- Success return Image

---

> image = RL.GenImageGradientLinear( Vector2 size, int direction, Color a, Color b )

Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient

- Success return Image

---

> image = RL.GenImageGradientRadial( Vector2 size, float density, Color inner, Color outer )

Generate image: radial gradient

- Success return Image

---

> image = RL.GenImageGradientSquare( Vector2 size, float density, Color inner, Color outer )

Generate image: square gradient

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

## Textures - Image manipulation functions

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

- Success return Image

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

> RL.ImageRotate( Image image, int degrees )

Rotate image by input angle in degrees (-359 to 359)

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

## Textures - Image configuration functions

---

> imageData = RL.GetImageData( Image image )

Get image data as Buffer

- Success return Buffer

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

## Textures - Image drawing functions

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

> RL.ImageDrawTextEx( Image dst, Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text (Custom sprite font) within an image (Destination)

---

## Textures - Texture loading functions

---

> texture = RL.GetTextureDefault()

Get default texture. Return as lightuserdata

- Success return Texture

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

> texture = RL.LoadTextureFromData( Texture{} textureData )

Load Texture from data

- Success return Texture

---

> renderTexture = RL.LoadRenderTexture( Vector2 size )

Load texture for rendering (framebuffer)

- Success return RenderTexture

---

> renderTexture = RL.LoadRenderTextureFromData( Texture{} renderTextureData )

Load RenderTexture from data (framebuffer)

- Success return RenderTexture

---

> isReady = RL.IsTextureReady( Texture texture )

Check if a texture is ready

- Success return bool

---

> RL.UnloadTexture( Texture texture )

Unload texture from GPU memory (VRAM)

---

> isReady = RL.IsRenderTextureReady( RenderTexture target )

Check if a render texture is ready

- Success return bool

---

> RL.UnloadRenderTexture( RenderTexture target )

Unload render texture from GPU memory (VRAM)

---

> RL.UpdateTexture( Texture texture, int{} pixels )

Update GPU texture with new data
NOTE! Should be TEXTURE_TYPE_TEXTURE. Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

---

> RL.UpdateTextureRec( Texture texture, Rectangle rec, int{} pixels )

Update GPU texture rectangle with new data.
Pixel should be in format { { 255, 255, 255, 255 }... } depending on the pixel format

---

## Textures - Texture configuration functions

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

## Textures - Texture drawing functions

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

> RL.DrawTextureNPatchRepeat( Texture texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint )

Draws a texture (or part of it) that repeats nicely

---

## Textures - RenderTexture configuration functions

---

> id = RL.GetRenderTextureId( RenderTexture renderTexture )

Get OpenGL framebuffer object id

- Success return int

---

> texture = RL.GetRenderTextureTexture( RenderTexture renderTexture )

Get color buffer attachment texture. Returns as lightuserdata

- Success return Texture

---

> texture = RL.GetRenderTextureDepthTexture( RenderTexture renderTexture )

Get depth buffer attachment texture. Returns as lightuserdata

- Success return Texture

---

## Textures - Color/pixel related functions

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

## Text - Font loading/unloading functions

---

> font = RL.GetFontDefault()

Get the default Font. Return as lightuserdata

- Success return Font

---

> font = RL.LoadFont( string fileName )

Load font from file into GPU memory (VRAM)

- Failure return nil
- Success return Font

---

> font = RL.LoadFontEx( string fileName, int fontSize, int{} codepoints )

Load font from file with extended parameters, use NULL for codepoints to load the default character set

- Failure return nil
- Success return Font

---

> font = RL.LoadFontFromImage( Image image, Color key, int firstChar )

Load font from Image (XNA style)

- Success return Font

---

> font = RL.LoadFontFromMemory( string fileType, Buffer fileData, int fontSize, int{} codepoints )

Load font from memory buffer, fileType refers to extension: i.e. '.ttf'. NOTE: fileData type should be unsigned char

- Success return Font

---

> font = RL.LoadFontFromData( Font{} fontData )

Load Font from data

- Success return Font

---

> isReady = RL.IsFontReady( Font font )

Check if a font is ready

- Success return bool

---

> glyphs = RL.LoadFontData( Buffer fileData, int fontSize, int{} codepoints, int type )

Load font data for further use. NOTE: fileData type should be unsigned char

- Success return GlyphInfo{}

---

> image, rectangles = RL.GenImageFontAtlas( GlyphInfo{} glyphs, int fontSize, int padding, int packMethod )

Generate image font atlas using chars info. NOTE: Packing method: 0-Default, 1-Skyline

- Success Image, Rectangle{}

---

> RL.UnloadFont( Font font )

Unload font from GPU memory (VRAM)

---

> RL.ExportFontAsCode( Font font, string fileName )

Export font as code file, returns true on success

- Success return bool

---

## Text - Text drawing functions

---

> RL.DrawFPS( Vector2 pos )

Draw current FPS

---

> RL.DrawText( string text, Vector2 position, float fontSize, Color tint )

Draw text (using default font)

---

> RL.DrawTextEx( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters

---

> RL.DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters (rotation)

---

> RL.DrawTextCodepoint( Font font, int codepoint, Vector2 position, float fontSize, Color tint )

Draw one character (codepoint)

---

> RL.DrawTextCodepoints( Font font, int{} codepoints, Vector2 position, float fontSize, float spacing, Color tint )

Draw multiple character (codepoint)

---

> mouseCharId = RL.DrawTextBoxed(Font font, string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint )

Draw text using font inside rectangle limits. Return character id from mouse position (default -1). Function from raylib [text] example - Rectangle bounds.

- Success return int

---

> mouseCharId = RL.DrawTextBoxedTinted( Font font, string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tints, Color backTints )

Draw text using font inside rectangle limits with support for tint and background tint for each character. Return character id from mouse position (default -1)

- Success return int

---

## Text - Text font info functions

---

> size = RL.SetTextLineSpacing( int spacing )

Set vertical line spacing when drawing with line-breaks

---

> size = RL.MeasureText( Font font, string text, float fontSize, float spacing )

Measure string size for Font

- Success return Vector2

---

> index = RL.GetGlyphIndex( Font font, int codepoint )

Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found

- Success return int

---

> glyphInfo = RL.GetGlyphInfo( Font font, int codepoint )

Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found. Return as lightuserdata

- Success return GlyphInfo

---

> glyphInfo = RL.GetGlyphInfoByIndex( Font font, int index )

Get glyph font info data by index. Return as lightuserdata

- Failure return nil
- Success return GlyphInfo

---

> rect = RL.GetGlyphAtlasRec( Font font, int codepoint )

Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

- Success return Rectangle

---

> rect = RL.GetGlyphAtlasRecByIndex( Font font, int index )

Get glyph rectangle in font atlas by index

- Failure return nil
- Success return Rectangle

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

Get font texture atlas containing the glyphs. Return as lightuserdata

- Success return Texture

---

## Text - GlyphInfo management functions

---

> glyphInfo = RL.LoadGlyphInfo( GlyphInfo{} glyphInfoData )

Load GlyphInfo from data

- Success return GlyphInfo

---

> RL.UnloadGlyphInfo( GlyphInfo glyphInfo )

Unload glyphInfo image from CPU memory (RAM)

---

> RL.SetGlyphInfoValue( GlyphInfo glyphInfo, int value )

Set glyphInfo character value (Unicode)

---

> RL.SetGlyphInfoOffset( GlyphInfo glyphInfo, Vector2 offset )

Set glyphInfo character offset when drawing

---

> RL.SetGlyphInfoAdvanceX( GlyphInfo glyphInfo, int advanceX )

Set glyphInfo character advance position X

---

> RL.SetGlyphInfoImage( GlyphInfo glyphInfo, Image image )

Set glyphInfo character image data

---

> value = RL.GetGlyphInfoValue( GlyphInfo glyphInfo )

Get glyphInfo character value (Unicode)

- Success return int

---

> offset = RL.GetGlyphInfoOffset( GlyphInfo glyphInfo )

Get glyphInfo character offset when drawing

- Success return Vector2

---

> advanceX = RL.GetGlyphInfoAdvanceX( GlyphInfo glyphInfo )

Get glyphInfo character advance position X

- Success return int

---

> image = RL.GetGlyphInfoImage( GlyphInfo glyphInfo )

Get glyphInfo character image data. Return as lightuserdata

- Success return Image

---

## Text - Text codepoints management functions (unicode characters)

---

> string = RL.LoadUTF8( int{} codepoints )

Load UTF-8 text encoded from codepoints array

- Success return string

---

> codepoints = RL.LoadCodepoints( string text )

Load all codepoints from a UTF-8 text string

- Success return int{}

---

> count = RL.GetCodepointCount( string text )

Get total number of codepoints in a UTF-8 encoded string

- Success return int

---

> codepoint, codepointSize = RL.GetCodepoint( string text )

Get codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int

---

> codepoint, codepointSize = RL.GetCodepointNext( string text )

Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int

---

> codepoint, codepointSize = RL.GetCodepointPrevious( string text )

Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int

---

> string = RL.CodepointToUTF8( int codepoint )

Encode one codepoint into UTF-8 byte array

- Success return string

---

## Text - Text strings management functions (no UTF-8 strings, only byte chars)

---

> text = RL.TextInsert( string text, string insert, int position )

Insert text in a specific position, moves all text forward

- Success return string

---

> splits = RL.TextSplit( string text, char delimiter )

Split text into multiple strings

- Success return string{}

---

> index = RL.TextFindIndex( string text, string find )

Find first text occurrence within a string

- Success return int

---

## Models - Basic geometric 3D shapes drawing functions

---

> RL.DrawLine3D( Vector3 startPos, Vector3 endPos, Color color )

Draw a line in 3D world space

---

> RL.DrawPoint3D( Vector3 position, Color color )

Draw a point in 3D space, actually a small line

---

> RL.DrawCircle3D( Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color )

Draw a circle in 3D world space

---

> RL.DrawTriangle3D( Vector3 v1, Vector3 v2, Vector3 v3, Color color )

Draw a color-filled triangle (Vertex in counter-clockwise order!)

---

> RL.DrawCube( Vector3 position, Vector3 size, Color color )

Draw cube

---

> RL.DrawCubeWires( Vector3 position, Vector3 size, Color color )

Draw cube wires

---

> RL.DrawSphere( Vector3 centerPos, float radius, Color color )

Draw sphere

---

> RL.DrawSphereEx( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere with extended parameters

---

> RL.DrawSphereWires( Vector3 centerPos, float radius, int rings, int slices, Color color )

Draw sphere wires

---

> RL.DrawCylinder( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone

---

> RL.DrawCylinderEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder with base at startPos and top at endPos

---

> RL.DrawCylinderWires( Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color )

Draw a cylinder/cone wires

---

> RL.DrawCylinderWiresEx( Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color )

Draw a cylinder wires with base at startPos and top at endPos

---

> RL.DrawCapsule( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw a capsule with the center of its sphere caps at startPos and endPos

---

> RL.DrawCapsuleWires( Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color )

Draw capsule wireframe with the center of its sphere caps at startPos and endPos

---

> RL.DrawPlane( Vector3 centerPos, Vector2 size, Color color )

Draw a plane XZ

---

> RL.DrawQuad3DTexture( Texture texture, Vector3{} vertices, Vector2{} texCoords, Color{} colors )

Draw 3D textured quad. (Texture coordinates opengl style 0.0 - 1.0)

---

> RL.DrawRay( Ray ray, Color color )

Draw a ray line

---

> RL.DrawGrid( int slices, float spacing )

Draw a grid (Centered at ( 0, 0, 0 ))

---

## Models - Model management functions

---

> model = RL.LoadModel( string fileName )

Load model from files (Meshes and materials)

- Failure return nil
- Success return Model

---

> model = RL.LoadModelFromMesh( Mesh mesh )

Load model from generated mesh (Default material)

- Success return Model

---

> isReady = RL.IsModelReady( Model model )

Check if a model is ready

- Success return bool

---

> RL.UnloadModel( Model model )

Unload model (including meshes) from memory (RAM and/or VRAM)

---

> boundingBox = RL.GetModelBoundingBox( Model model )

Compute model bounding box limits (considers all meshes)

- Success return BoundingBox

---

> RL.SetModelTransform( Model model, Matrix transform )

Set model transform matrix

---

> success = RL.SetModelMesh( Model model, int meshId, Mesh mesh )

Set model mesh.

- Failure return false
- Success return true

---

> success = RL.SetModelMaterial( Model model, int materialId, Material material )

Set material to model material

- Failure return false
- Success return true

---

> RL.SetModelMeshMaterial( Model model, int meshId, int materialId )

Set material for a mesh (Mesh and material on this model)

---

> success = RL.SetModelBone( Model model, int boneId, BoneInfo bone )

Set model bone information (skeleton)

- Failure return false
- Success return true

---

> success = RL.SetModelBindPose( Model model, int boneId, Transform pose )

Set model bones base transformation (pose)

- Failure return false
- Success return true

---

> transform = RL.GetModelTransform( Model model )

Get model transform matrix

- Success return Matrix

---

> meshCount = RL.GetModelMeshCount( Model model )

Get model number of meshes

- Success return int

---

> meshCount = RL.GetModelMaterialCount( Model model )

Get model number of materials

- Success return int

---

> mesh = RL.GetModelMesh( Model model, int meshId )

Get model mesh. Return as lightuserdata

- Failure return nil
- Success return Mesh

---

> material = RL.GetModelMaterial( Model model, int materialId )

Get model material. Return as lightuserdata

- Failure return nil
- Success return Material

---

> boneCount = RL.GetModelBoneCount( Model model )

Get model number of bones

- Success return int

---

> bone = RL.GetModelBone( Model model, int boneId )

Get model bones information (skeleton)

- Failure return nil
- Success return BoneInfo

---

> pose = RL.GetModelBindPose( Model model, int boneId )

Get models bones base transformation (pose)

- Failure return nil
- Success return Transform

---

## Models - Model drawing functions

---

> RL.DrawModel( Model model, Vector3 position, float scale, Color tint )

Draw a model (With texture if set)

---

> RL.DrawModelEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model with extended parameters

---

> RL.DrawModelWires( Model model, Vector3 position, float scale, Color tint )

Draw a model wires (with texture if set)

---

> RL.DrawModelWiresEx( Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint )

Draw a model wires (with texture if set) with extended parameters

---

> RL.DrawBoundingBox( BoundingBox box, Color color )

Draw bounding box (wires)

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

## Models - Mesh management functions

---

> RL.UpdateMesh( Mesh mesh, Mesh{} meshData )

Update mesh vertex data in GPU.
NOTE: Mainly intented to be used with custom meshes.

---

> RL.UnloadMesh( Mesh mesh )

Unload mesh data from CPU and GPU

---

> RL.DrawMesh( Mesh mesh, Material material, Matrix transform )

Draw a 3d mesh with material and transform

---

> RL.DrawMeshInstanced( Mesh mesh, Material material, Matrix{} transforms, int instances )

Draw multiple mesh instances with material and different transforms

---

> success = RL.SetMeshColor( Mesh mesh, Color color )

Updades mesh color vertex attribute buffer
NOTE: Currently only works on custom mesh

- Failure return false
- Success return true

---

> success = RL.ExportMesh( Mesh mesh, string fileName )

Export mesh data to file, returns true on success

- Success return bool

---

> boundingBox = RL.GetMeshBoundingBox( Mesh mesh )

Compute mesh bounding box limits

- Success return BoundingBox

---

> RL.GenMeshTangents( Mesh mesh )

Compute mesh tangents

---

## Models - Mesh generation functions

---

> mesh = RL.GenMeshPoly( int sides, float radius )

Generate polygonal mesh

- Success return Mesh

---

> mesh = RL.GenMeshPlane( float width, float length, int resX, int resZ )

Generate plane mesh (With subdivisions)

- Success return Mesh

---

> mesh = RL.GenMeshCube( Vector3 size )

Generate cuboid mesh

- Success return Mesh

---

> mesh = RL.GenMeshSphere( float radius, int rings, int slices )

Generate sphere mesh (Standard sphere)

- Success return Mesh

---

> mesh = RL.GenMeshCylinder( float radius, float height, int slices )

Generate cylinder mesh

- Success return Mesh

---

> mesh = RL.GenMeshCone( float radius, float height, int slices )

Generate cone/pyramid mesh

- Success return Mesh

---

> mesh = RL.GenMeshTorus( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Success return Mesh

---

> mesh = RL.GenMeshKnot( float radius, float size, int radSeg, int sides )

Generate torus mesh

- Success return Mesh

---

> mesh = RL.GenMeshHeightmap( Image heightmap, Vector3 size )

Generate heightmap mesh from image data

- Success return Mesh

---

> mesh = RL.GenMeshCubicmap( Image cubicmap, Vector3 cubeSize )

Generate cubes-based map mesh from image data

- Success return Mesh

---

> mesh = RL.GenMeshCustom( Mesh{} meshData, bool dynamic )

Generate custom mesh from vertex attribute data and uploads it into a VAO (if supported) and VBO

- Success return Mesh

---

## Models - Material management functions

---

> materials = RL.LoadMaterials( string fileName )

Load materials from model file

- Success return Material{}

---

> material = RL.GetMaterialDefault()

Default material for reference. Return as lightuserdata

- Success return Material

---

> material = RL.LoadMaterialDefault()

Load default material as new object

- Success return Material

---

> material = RL.CreateMaterial( Material{} materialData )

Load material from table. See material table definition

- Success return Material

---

> isReady = RL.IsMaterialReady( Material material )

Check if a material is ready

- Success return bool

---

> RL.UnloadMaterial( Material material )

Unload material from GPU memory (VRAM)

---

> RL.SetMaterialTexture( Material material, int mapType, Texture texture )

Set texture for a material map type (MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS...)

---

> RL.SetMaterialColor( Material material, int mapType, Color color )

Set color for a material map type

---

> RL.SetMaterialValue( Material material, int mapType, float value )

Set value for a material map type

---

> RL.SetMaterialShader( Material material, Shader shader )

Set shader for material

---

> RL.SetMaterialParams( Material material, float{} params )

Set material generic parameters (if required)

---

> texture = RL.GetMaterialTexture( Material material, int mapType )

Get texture from material map type. Return as lightuserdata

- Success return Texture

---

> color = RL.GetMaterialColor( Material material, int mapType )

Get color from material map type

- Success return Color

---

> value = RL.GetMaterialValue( Material material, int mapType )

Get color from material map type

- Success return float

---

> shader = RL.GetMaterialShader( Material material )

Get material shader. Return as lightuserdata

- Success return Shader

---

> params = RL.GetMaterialParams( Material material )

Get material parameters

- Success return float{}

---

## Model - Model animations management functions

---

> animations = RL.LoadModelAnimations( string fileName )

Load model animations from file

- Failure return nil
- Success return ModelAnimations{}

---

> RL.UpdateModelAnimation( Model model, ModelAnimation animation, int frame )

Update model animation pose

---

> RL.UnloadModelAnimation( ModelAnimation animation )

Unload animation data

---

> RL.UnloadModelAnimations( ModelAnimation{} animations )

Unload animation table data

---

> valid = RL.IsModelAnimationValid( Model model, ModelAnimation animation )

Check model animation skeleton match

- Success return bool

---

> success = RL.SetModelAnimationBone( ModelAnimation animation, int boneId, BoneInfo bone )

Set modelAnimation bones information (skeleton)

- Failure return false
- Success return true

---

> success = RL.SetModelAnimationFramePose( ModelAnimation animation, int frame, int boneId, Transform pose )

Set modelAnimation bones base transformation (pose)

- Failure return false
- Success return true

---

> RL.SetModelAnimationName( ModelAnimation animation, string name )

Set modelAnimation name

---

> boneCount = RL.GetModelAnimationBoneCount( ModelAnimation animation )

Return modelAnimation bone count

- Success return int

---

> frameCount = RL.GetModelAnimationFrameCount( ModelAnimation animation )

Return modelAnimation frame count

- Success return int

---

> bone = RL.GetModelAnimationBone( ModelAnimation animation, int boneId )

Get modelAnimation bones information (skeleton)

- Failure return nil
- Success return BoneInfo

---

> pose = RL.GetModelAnimationFramePose( ModelAnimation animation, int frame, int boneId )

Get modelAnimation bones base transformation (pose)

- Failure return nil
- Success return Transform

---

> name = RL.GetModelAnimationName( ModelAnimation animation )

Get modelAnimation name

- Success return string

---

## Model - Collision detection functions

---

> collision = RL.CheckCollisionSpheres( Vector3 center1, float radius1, Vector3 center2, float radius2 )

Check collision between two spheres

- Success return bool

---

> collision = RL.CheckCollisionBoxes( BoundingBox box1, BoundingBox box2 )

Check collision between two bounding boxes

- Success return bool

---

> collision = RL.CheckCollisionBoxSphere( BoundingBox box, Vector3 center, float radius )

Check collision between box and sphere

- Success return bool

---

> rayCollision = RL.GetRayCollisionSphere( Ray ray, Vector3 center, float radius )

Get collision info between ray and sphere. ( RayCollision is Lua table of { hit, distance, point, normal } )

- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionBox( Ray ray, BoundingBox box )

Get collision info between ray and box

- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionMesh( Ray ray, Mesh mesh, Matrix transform )

Get collision info between ray and mesh

- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionTriangle( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3 )

Get collision info between ray and triangle

- Success return RayCollision

---

> rayCollision = RL.GetRayCollisionQuad( Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4 )

Get collision info between ray and quad

- Success return RayCollision

---

## Audio - Audio device management functions

---

> RL.InitAudioDevice()

Initialize audio device and context

---

> RL.CloseAudioDevice()

Close the audio device and context

---

> isReady = RL.IsAudioDeviceReady()

Check if audio device has been initialized successfully

- Success return bool

---

> RL.SetMasterVolume( float volume )

Set master volume (listener)

---

> isReady = RL.GetMasterVolume()

Get master volume (listener)

- Success return float

---

## Audio - Wave/Sound loading/unloading functions

---

> sound = RL.LoadSound( string fileName )

Load sound from file

- Failure return nil
- Success return Sound

---

> wave = RL.LoadWave( string fileName )

Load wave data from file

- Failure return nil
- Success return Wave

---

> wave = RL.LoadWaveFromMemory( string fileType, Buffer data )

Load wave from memory buffer, fileType refers to extension: i.e. '.wav'

- Success return Wave

---

> isReady = RL.IsWaveReady( Wave wave )

Checks if wave data is ready

- Success return bool

---

> sound = RL.LoadSoundFromWave( Wave wave )

Load sound from wave data

- Success return Sound

---

> sound = RL.LoadSoundAlias( Sound source )

Create a new sound that shares the same sample data as the source sound, does not own the sound data

- Success return Sound

---

> isReady = RL.IsSoundReady( Sound sound )

Checks if a sound is ready

- Success return bool

---

> RL.UnloadWave( Wave wave )

Unload wave data

---

> RL.UnloadSound( Sound sound )

Unload sound

---

> RL.UnloadSoundAlias( Sound alias )

Unload a sound alias (does not deallocate sample data)

---

> success = RL.ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Success return bool

---

> success = RL.ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Success return true

---

## Audio - Wave/Sound management functions

---

> RL.PlaySound( Sound sound )

Play a sound

---

> RL.StopSound( Sound sound )

Stop playing a sound

---

> RL.PauseSound( Sound sound )

Pause a sound

---

> RL.ResumeSound( Sound sound )

Resume a paused sound

---

> playing = RL.IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Success return bool

---

> RL.SetSoundVolume( Sound sound, float volume )

Set volume for a sound (1.0 is max level)

---

> RL.SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound (1.0 is base level)

---

> RL.SetSoundPan( Sound sound, float pan )

Set pan for a sound (0.5 is center)

---

> RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format

---

> wave = RL.WaveCopy( Wave wave )

Copy a wave to a new wave

- Success return Wave

---

> RL.WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range

---

## Audio - Music management functions

---

> music = RL.LoadMusicStream( string fileName )

Load music stream from file

- Success return Music

---

> music = RL.LoadMusicStreamFromMemory( string fileType, Buffer data )

Load music stream from data

- Success return Music

---

> isReady = RL.IsMusicReady( Music music )

Checks if a music stream is ready

- Success return bool

---

> RL.UnloadMusicStream( Music music )

Unload music stream

---

> RL.PlayMusicStream( Music music )

Start music playing

---

> playing = RL.IsMusicStreamPlaying( Music music )

Check if music is playing

- Success return bool

---

> RL.UpdateMusicStream( Music music )

Updates buffers for music streaming

---

> RL.StopMusicStream( Music music )

Stop music playing

---

> RL.PauseMusicStream( Music music )

Pause music playing

---

> RL.ResumeMusicStream( Music music )

Resume playing paused music

---

> RL.SeekMusicStream( Music music, float position )

Seek music to a position (in seconds)

---

> RL.SetMusicVolume( Music music, float volume )

Set volume for music (1.0 is max level)

---

> RL.SetMusicPitch( Music music, float pitch )

Set pitch for a music (1.0 is base level)

---

> RL.SetMusicPan( Music music, float pan )

Set pan for a music (0.5 is center)

---

> RL.SetMusicLooping( Music music, bool looping )

Set looping for a music

---

> looping = RL.GetMusicLooping( Music music )

Get looping of a music

- Success return bool

---

> length = RL.GetMusicTimeLength( Music music )

Get music time length (in seconds)

- Success return float

---

> timePlayed = RL.GetMusicTimePlayed( Music music )

Get current music time played (in seconds)

- Success return float

---

## Math - Utils

---

> result = RL.Clamp( float value, float min, float max )

Clamp float value

- Success return float

---

> result = RL.Lerp( float a, float b, float amount )

Calculate linear interpolation between two floats

- Success return float

---

> result = RL.Normalize( float value, float a, float b )

Normalize input value within input range

- Success return float

---

> result = RL.Remap( float value, float inputStart, float inputEnd, float outputStart, float outputEnd )

Remap input value within input range to output range

- Success return float

---

> result = RL.Wrap( float value, float min, float max )

Wrap input value from min to max

- Success return float

---

> result = RL.FloatEquals( float x, float y )

Check whether two given floats are almost equal

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

- Success return Vector2

---

> result = RL.Vector2AddValue( Vector2 v, float add )

Add vector and float value

- Success return Vector2

---

> result = RL.Vector2Subtract( Vector2 v1, Vector2 v2 )

Subtract two vectors (v1 - v2)

- Success return Vector2

---

> result = RL.Vector2SubtractValue( Vector2 v, float sub )

Subtract vector by float value

- Success return Vector2

---

> result = RL.Vector2Length( vector2 v )

Calculate vector length

- Success return float

---

> result = RL.Vector2LengthSqr( vector2 v )

Calculate vector square length

- Success return float

---

> result = RL.Vector2DotProduct( Vector2 v1, Vector2 v2 )

Calculate two vectors dot product

- Success return float

---

> result = RL.Vector2Distance( Vector2 v1, Vector2 v2 )

Calculate distance between two vectors

- Success return float

---

> result = RL.Vector2DistanceSqr( Vector2 v1, Vector2 v2 )

Calculate square distance between two vectors

- Success return float

---

> result = RL.Vector2Angle( Vector2 v1, Vector2 v2 )

Calculate angle between two vectors
NOTE: Angle is calculated from origin point (0, 0)

- Success return float

---

> result = RL.Vector2LineAngle( Vector2 a, Vector2 b )

Calculate angle defined by a two vectors line
NOTE: Parameters need to be normalized
Current implementation should be aligned with glm::angle

- Success return float

---

> result = RL.Vector2Scale( Vector2 v, float scale )

Scale vector (multiply by value)

- Success return Vector2

---

> result = RL.Vector2Multiply( Vector2 v1, Vector2 v2 )

Multiply vector by vector

- Success return Vector2

---

> result = RL.Vector2Negate( Vector2 v )

Negate vector

- Success return Vector2

---

> result = RL.Vector2Divide( Vector2 v1, Vector2 v2 )

Divide vector by vector

- Success return Vector2

---

> result = RL.Vector2Normalize( Vector2 v )

Normalize provided vector

- Success return Vector2

---

> result = RL.Vector2Transform( Vector2 v, Matrix mat )

Transforms a Vector2 by a given Matrix

- Success return Vector2

---

> result = RL.Vector2Lerp( Vector2 v1, Vector2 v2, float amount )

Calculate linear interpolation between two vectors

- Success return Vector2

---

> result = RL.Vector2Reflect( Vector2 v, Vector2 normal )

Calculate reflected vector to normal

- Success return Vector2

---

> result = RL.Vector2Rotate( Vector2 v, float angle )

Rotate vector by angle

- Success return Vector2

---

> result = RL.Vector2MoveTowards( Vector2 v, Vector2 target, float maxDistance )

Move Vector towards target

- Success return Vector2

---

> result = RL.Vector2Invert( Vector2 v )

Invert the given vector

- Success return Vector2

---

> result = RL.Vector2Clamp( Vector2 v, Vector2 min, Vector2 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Success return Vector2

---

> result = RL.Vector2ClampValue( Vector2 v, float min, float max )

Clamp the magnitude of the vector between two min and max values

- Success return Vector2

---

> result = RL.Vector2Equals( Vector2 v1, Vector2 v2 )

Check whether two given vectors are almost equal

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

- Success return Vector3

---

> result = RL.Vector3AddValue( Vector3 v, float add )

Add vector and float value

- Success return Vector3

---

> result = RL.Vector3Subtract( Vector3 v1, Vector3 v2 )

Subtract two vectors

- Success return Vector3

---

> result = RL.Vector3SubtractValue( Vector3 v, float sub )

Subtract vector by float value

- Success return Vector3

---

> result = RL.Vector3Scale( Vector3 v, float scalar )

Multiply vector by scalar

- Success return Vector3

---

> result = RL.Vector3Multiply( Vector3 v1, Vector3 v2 )

Multiply vector by vector

- Success return Vector3

---

> result = RL.Vector3CrossProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors cross product

- Success return Vector3

---

> result = RL.Vector3Perpendicular( Vector3 v )

Calculate one vector perpendicular vector

- Success return Vector3

---

> result = RL.Vector3Length( Vector3 v )

Calculate vector length

- Success return float

---

> result = RL.Vector3LengthSqr( Vector3 v )

Calculate vector square length

- Success return float

---

> result = RL.Vector3DotProduct( Vector3 v1, Vector3 v2 )

Calculate two vectors dot product

- Success return float

---

> result = RL.Vector3Distance( Vector3 v1, Vector3 v2 )

Calculate distance between two vectors

- Success return float

---

> result = RL.Vector3DistanceSqr( Vector3 v1, Vector3 v2 )

Calculate square distance between two vectors

- Success return float

---

> result = RL.Vector3Angle( Vector3 v1, Vector3 v2 )

Calculate angle between two vectors

- Success return float

---

> result = RL.Vector3Negate( Vector3 v )

Negate provided vector (invert direction)

- Success return Vector3

---

> result = RL.Vector3Divide( Vector3 v1, Vector3 v2 )

Divide vector by vector

- Success return Vector3

---

> result = RL.Vector3Normalize( Vector3 v )

Normalize provided vector

- Success return Vector3

---

> result = RL.Vector3Project( Vector3 v1, Vector3 v2 )

Calculate the projection of the vector v1 on to v2

- Success return Vector3

---

> result = RL.Vector3Reject( Vector3 v1, Vector3 v2 )

Calculate the rejection of the vector v1 on to v2

- Success return Vector3

---

> v1, v2 = RL.Vector3OrthoNormalize( Vector3 v1, Vector3 v2 )

Orthonormalize provided vectors. Makes vectors normalized and orthogonal to each other.
Gram-Schmidt function implementation

- Success return Vector3, Vector3

---

> result = RL.Vector3Transform( Vector3 v, Matrix mat )

Transforms a Vector3 by a given Matrix

- Success return Vector3

---

> result = RL.Vector3RotateByQuaternion( Vector3 v, Quaternion q )

Transform a vector by quaternion rotation

- Success return Vector3

---

> result = RL.Vector3RotateByAxisAngle( Vector3 v, Vector3 axis, float angle )

Rotates a vector around an axis

- Success return Vector3

---

> result = RL.Vector3Lerp( Vector3 v1, Vector3 v2, float amount )

Calculate linear interpolation between two vectors

- Success return Vector3

---

> result = RL.Vector3Reflect( Vector3 v, Vector3 normal )

Calculate reflected vector to normal

- Success return Vector3

---

> result = RL.Vector3Min( Vector3 v1, Vector3 v2 )

Get min value for each pair of components

- Success return Vector3

---

> result = RL.Vector3Max( Vector3 v1, Vector3 v2 )

Get max value for each pair of components

- Success return Vector3

---

> result = RL.Vector3Barycenter( Vector3 p, Vector3 a, Vector3 b, Vector3 c )

Compute barycenter coordinates (u, v, w) for point p with respect to triangle (a, b, c)
NOTE: Assumes P is on the plane of the triangle

- Success return Vector3

---

> result = RL.Vector3Unproject( Vector3 source, Matrix projection, Matrix view )

Projects a Vector3 from screen space into object space
NOTE: We are avoiding calling other raymath functions despite available

- Success return Vector3

---

> result = RL.Vector3Invert( Vector3 v )

Invert the given vector

- Success return Vector3

---

> result = RL.Vector3Clamp( Vector3 v, Vector3 min, Vector3 max )

Clamp the components of the vector between
min and max values specified by the given vectors

- Success return Vector3

---

> result = RL.Vector3ClampValue( Vector3 v, float min, float max )

Clamp the magnitude of the vector between two values

- Success return Vector3

---

> result = RL.Vector3Equals( Vector3 v1, Vector3 v2 )

Check whether two given vectors are almost equal

- Success return int

---

> result = RL.Vector3Refract( Vector3 v, Vector3 n, float r )

Compute the direction of a refracted ray where v specifies the
normalized direction of the incoming ray, n specifies the
normalized normal vector of the interface of two optical media,
and r specifies the ratio of the refractive index of the medium
from where the ray comes to the refractive index of the medium
on the other side of the surface

- Success return Vector3

---

## Math - Matrix

---

> result = RL.MatrixDeterminant( Matrix mat )

Compute matrix determinant

- Success return float

---

> result = RL.MatrixTrace( Matrix mat )

Get the trace of the matrix (sum of the values along the diagonal)

- Success return float

---

> result = RL.MatrixTranspose( Matrix mat )

Transposes provided matrix

- Success return Matrix

---

> result = RL.MatrixInvert( Matrix mat )

Invert provided matrix

- Success return Matrix

---

> result = RL.MatrixIdentity()

Get identity matrix

- Success return Matrix

---

> result = RL.MatrixAdd( Matrix left, Matrix right )

Add two matrices

- Success return Matrix

---

> result = RL.MatrixSubtract( Matrix left, Matrix right )

Subtract two matrices (left - right)

- Success return Matrix

---

> result = RL.MatrixMultiply( Matrix left, Matrix right )

Get two matrix multiplication

- Success return Matrix

---

> result = RL.MatrixTranslate( Vector3 translate )

Get translation matrix

- Success return Matrix

---

> result = RL.MatrixRotate( Vector3 axis, float angle )

Create rotation matrix from axis and angle. NOTE: Angle should be provided in radians

- Success return Matrix

---

> result = RL.MatrixRotateX( float angle )

Get x-rotation matrix (angle in radians)

- Success return Matrix

---

> result = RL.MatrixRotateY( float angle )

Get y-rotation matrix (angle in radians)

- Success return Matrix

---

> result = RL.MatrixRotateZ( float angle )

Get z-rotation matrix (angle in radians)

- Success return Matrix

---

> result = RL.MatrixRotateXYZ( Vector3 angles )

Get xyz-rotation matrix (angles in radians)

- Success return Matrix

---

> result = RL.MatrixRotateZYX( Vector3 angles )

Get zyx-rotation matrix (angles in radians)

- Success return Matrix

---

> result = RL.MatrixScale( Vector3 scale )

Get scaling matrix

- Success return Matrix

---

> result = RL.MatrixFrustum( double left, double right, double bottom, double top, double near, double far )

Get perspective projection matrix

- Success return Matrix

---

> result = RL.MatrixPerspective( double fovy, double aspect, double near, double far )

Get perspective projection matrix

- Success return Matrix

---

> result = RL.MatrixOrtho( double left, double right, double bottom, double top, double near, double far )

Get orthographic projection matrix

- Success return Matrix

---

> result = RL.MatrixLookAt( Vector3 eye, Vector3 target, Vector3 up )

Get camera look-at matrix (View matrix)

- Success return Matrix

---

## Math - Quaternion

---

> result = RL.QuaternionAdd( Quaternion q1, Quaternion q2 )

Add two quaternions

- Success return Quaternion

---

> result = RL.QuaternionAddValue( Quaternion q, float add )

Add quaternion and float value

- Success return Quaternion

---

> result = RL.QuaternionSubtract( Quaternion q1, Quaternion q2 )

Subtract two quaternions

- Success return Quaternion

---

> result = RL.QuaternionSubtractValue( Quaternion q, float sub )

Subtract quaternion and float value

- Success return Quaternion

---

> result = RL.QuaternionIdentity()

Get identity quaternion

- Success return Quaternion

---

> result = RL.QuaternionLength( Quaternion q )

Computes the length of a quaternion

- Success return float

---

> result = RL.QuaternionNormalize( Quaternion q )

Normalize provided quaternion

- Success return Quaternion

---

> result = RL.QuaternionInvert( Quaternion q )

Invert provided quaternion

- Success return Quaternion

---

> result = RL.QuaternionMultiply( Quaternion q1, Quaternion q2 )

Calculate two quaternion multiplication

- Success return Quaternion

---

> result = RL.QuaternionScale( Quaternion q, float mul )

Scale quaternion by float value

- Success return Quaternion

---

> result = RL.QuaternionDivide( Quaternion q1, Quaternion q2 )

Divide two quaternions

- Success return Quaternion

---

> result = RL.QuaternionLerp( Quaternion q1, Quaternion q2, float amount )

Calculate linear interpolation between two quaternions

- Success return Quaternion

---

> result = RL.QuaternionNlerp( Quaternion q1, Quaternion q2, float amount )

Calculate slerp-optimized interpolation between two quaternions

- Success return Quaternion

---

> result = RL.QuaternionSlerp( Quaternion q1, Quaternion q2, float amount )

Calculates spherical linear interpolation between two quaternions

- Success return Quaternion

---

> result = RL.QuaternionFromVector3ToVector3( Vector3 from, Vector3 to )

Calculate quaternion based on the rotation from one vector to another

- Success return Quaternion

---

> result = RL.QuaternionFromMatrix( Matrix mat )

Get a quaternion for a given rotation matrix

- Success return Quaternion

---

> result = RL.QuaternionToMatrix( Quaternion q )

Get a quaternion for a given rotation matrix

- Success return Matrix

---

> result = RL.QuaternionFromAxisAngle( Vector3 axis, float angle )

Get rotation quaternion for an angle and axis
NOTE: angle must be provided in radians

- Success return Quaternion

---

> axis, angle = RL.QuaternionToAxisAngle( Quaternion q )

Get the rotation angle and axis for a given quaternion

- Success return Vector3, float

---

> result = RL.QuaternionFromEuler( float pitch, float yaw, float roll )

Get the quaternion equivalent to Euler angles
NOTE: Rotation order is ZYX

- Success return Quaternion

---

> result = RL.QuaternionToEuler( Quaternion q )

Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
NOTE: Angles are returned in a Vector3 struct in radians

- Success return Vector3

---

> result = RL.QuaternionTransform( Quaternion q, Matrix mat )

Transform a quaternion given a transformation matrix

- Success return Quaternion

---

> result = RL.QuaternionEquals( Quaternion q1, Quaternion q2 )

Check whether two given quaternions are almost equal

- Success return int

---

## Gui - Global gui state control functions

---

> RL.GuiEnable()

Enable gui controls (global state)

---

> RL.GuiDisable()

Disable gui controls (global state)

---

> RL.GuiLock()

Lock gui controls (global state)

---

> RL.GuiUnlock()

Unlock gui controls (global state)

---

> locked = RL.GuiIsLocked()

Check if gui is locked (global state)

- Success return bool

---

> RL.GuiSetAlpha( float alpha )

Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f

---

> RL.GuiSetState( int state )

Set gui state (global state)

---

> state = RL.GuiGetState()

Get gui state (global state)

- Success return int

---

## Gui - Font set/get functions

---

> RL.GuiSetFont( Font font )

Set gui custom font (global state)

---

> font = RL.GuiGetFont()

Get gui custom font (global state). Return as lightuserdata

- Success return Font

---

## Gui - Style set/get functions

---

> RL.GuiSetStyle( int control, int property, int value )

Set one style property

---

> value = RL.GuiGetStyle( int control, int property )

Get one style property

- Success return int

---

## Gui - Styles loading functions

---

> success = RL.GuiLoadStyle( string fileName )

Load style file over global style variable (.rgs)

- Failure return nil
- Success return true

---

> RL.GuiLoadStyleDefault()

Load style default over global style

---

## Gui - Tooltips management functions

---

> RL.GuiEnableTooltip()

Enable gui tooltips (global state)

---

> RL.GuiDisableTooltip()

Disable gui tooltips (global state)

---

> RL.GuiSetTooltip( string tooltip )

Set tooltip string

---

## Gui - Icons functionality

---

> text = RL.GuiIconText( int iconId, string text )

Get text with icon id prepended (if supported)

- Success return string

---

> RL.GuiSetIconScale( int scale )

Set icon scale (1 by default)

---

> icons = RL.GuiGetIcons()

Get raygui icons data pointer

- Success return int

---

> iconNames = RL.GuiLoadIcons( string fileName, bool loadIconsName )

Load raygui icons file (.rgi) into internal icons data

- Failure return nil
- Success return strings{}

---

> RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon

---

## Gui - Container/separator controls, useful for controls organization

---

> result = RL.GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Success return int

---

> result = RL.GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name

- Success return int

---

> result = RL.GuiLine( Rectangle bounds, string text )

Line separator control, could contain text

- Success return int

---

> result = RL.GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls

- Success return int

---

> result, active = RL.GuiTabBar( Rectangle bounds, string text, int active )

Tab Bar control, returns TAB to be closed or -1

- Success return int, int

---

> result, scroll, view = RL.GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll, Rectangle view )

Scroll Panel control

- Success return int, Vector2, Rectangle

---

## Gui - Basic controls set

---

> result = RL.GuiLabel( Rectangle bounds, string text )

Label control, shows text

- Success return int

---

> result = RL.GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Success return int

---

> result = RL.GuiLabelButton( Rectangle bounds, string text )

Label button control, show true when clicked

- Success return int

---

> result, active = RL.GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Success return int, bool

---

> result, active = RL.GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Success return int, int

---

> result, active = RL.GuiToggleSlider( Rectangle bounds, string text, int active )

Toggle Slider control, returns true when clicked

- Success return int, int

---

> result, checked, textBounds = RL.GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Success return bool, Rectangle

---

> result, active = RL.GuiComboBox( Rectangle bounds, string text, int active )

Combo Box control, returns selected item index

- Success return int, int

---

> result, active = RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Success return int, int

---

> result, value, textBounds = RL.GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Success return int, int, Rectangle

---

> result, value, textBounds = RL.GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Success return int, int, Rectangle

---

> result, text = RL.GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Success return int, string

---

> result, value, textLeftBounds, textRightBounds = RL.GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Success return int, float, Rectangle, Rectangle

---

> result, value, textLeftBounds, textRightBounds = RL.GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Success return int, float, Rectangle, Rectangle

---

> result, value, textLeftBounds, textRightBounds = RL.GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Success return int, float, Rectangle, Rectangle

---

> result = RL.GuiStatusBar( Rectangle bounds, string text )

Status Bar control, shows info text

- Success return int

---

> result = RL.GuiDummyRec( Rectangle bounds, string text )

Dummy control for placeholders

- Success return int

---

> result, mouseCell = RL.GuiGrid( Rectangle bounds, string text, float spacing, int subdivs, Vector2 mouseCell )

Grid control, returns mouse cell position

- Success return int, Vector2

---

> value = RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll bar control

- Success return int

---

## Gui - Advance controls set

---

> result, scrollIndex, active = RL.GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index

- Success return int, int, int

---

> result, scrollIndex, active, focus = RL.GuiListViewEx( Rectangle bounds, string text, int scrollIndex, int active, int focus )

List View with extended parameters

- Success return int, int, int, int

---

> result = RL.GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message

- Success return int

---

> result, text, secretViewActive = RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, bool secretViewActive )

Text Input Box control, ask for text, supports secret

- Success return int, string, bool

---

> result, color = RL.GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control (multiple color controls)

- Success return int, Color

---

> result, color = RL.GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Success return int, Color

---

> result, alpha = RL.GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Success return int, float

---

> result, value = RL.GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Success return int, float

---

> result, colorHsv = RL.GuiColorPickerHSV( Rectangle bounds, string text, Vector3 colorHsv )

Color Picker control that avoids conversion to RGB on each call (multiple color controls)

- Success return int, Vector3

---

> result, colorHsv = RL.GuiColorPanelHSV( Rectangle bounds, string text, Vector3 colorHsv )

Color Panel control that returns HSV color value, used by GuiColorPickerHSV()

- Success return int, Vector3

---

## Lights - Light management functions

---

> light = RL.CreateLight( int type, Vector3 position, Vector3 target, Color color, Shader shader )

Create a light and get shader locations

- Success return Light

---

> RL.UpdateLightValues( Shader shader, Light light )

Send light properties to shader

---

> RL.SetLightType( Light light, int type )

Set light type

---

> RL.SetLightPosition( Light light, Vector3 position )

Set light position

---

> RL.SetLightTarget( Light light, Vector3 target )

Set light target

---

> RL.SetLightColor( Light light, Color color )

Set light color

---

> RL.SetLightEnabled( Light light, bool enabled )

Set light enabled

---

> type = RL.GetLightType( Light light )

Get light type

- Success return int

---

> position = RL.GetLightPosition( Light light )

Get light position

- Success return Vector3

---

> target = RL.GetLightTarget( Light light )

Get light target

- Success return Vector3

---

> color = RL.GetLightColor( Light light )

Get light color

- Success return Color

---

> enabled = RL.IsLightEnabled( Light light )

Get light enabled

- Success return bool

---

## RLGL - Matrix operations

---

> RL.rlMatrixMode( int mode )

Choose the current matrix to be transformed

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

> RL.rlTranslatef( Vector3 translation )

Multiply the current matrix by a translation matrix

---

> RL.rlRotatef( float angle, Vector3 rotation )

Multiply the current matrix by a rotation matrix

---

> RL.rlScalef( Vector3 scale )

Multiply the current matrix by a scaling matrix

---

> RL.rlMultMatrixf( Matrix matrix )

Multiply the current matrix by another matrix

---

> RL.rlFrustum( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by a perspective matrix generated by parameters

---

> RL.rlOrtho( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by an orthographic matrix generated by parameters

---

> RL.rlViewport( Rectangle viewport )

Set the viewport area (transformation from normalized device coordinates to window coordinates)
NOTE: We store current viewport dimensions

---

## RLGL - Vertex level operations

---

> RL.rlBegin( int mode )

Initialize drawing mode (how to organize vertex)

---

> RL.rlEnd()

Finish vertex providing

---

> RL.rlVertex2f( Vector2 position )

Define one vertex (position)

---

> RL.rlVertex3f( Vector3 position )

Define one vertex (position)

---

> RL.rlTexCoord2f( Vector2 texCoord )

Define one vertex (texture coordinate) - 2 float

---

> RL.rlNormal3f( Vector3 normal )

Define one vertex (normal) - 3 float

---

> RL.rlColor4ub( Color color )

Define one vertex (color) - 4 byte

---

> RL.rlColor3f( Vector3 color )

Define one vertex (color) - 3 float

---

> RL.rlColor4f( Vector4 color )

Define one vertex (color) - 4 float

---

## RLGL - Vertex buffers state

---

> supported = RL.rlEnableVertexArray( int vaoId )

Enable vertex array (VAO, if supported)

- Success return bool

---

> RL.rlDisableVertexArray()

Disable vertex array (VAO, if supported)

---

> RL.rlEnableVertexBuffer( int id )

Enable vertex buffer (VBO)

- Failure return false
- Success return true

---

> RL.rlDisableVertexBuffer()

Disable vertex buffer (VBO)

---

> RL.rlEnableVertexBufferElement( int id )

Enable vertex buffer element (VBO element)

---

> RL.rlDisableVertexBufferElement()

Disable vertex buffer element (VBO element)

---

> RL.rlEnableVertexAttribute( int index )

Enable vertex attribute index

---

> RL.rlDisableVertexAttribute( int index )

Disable vertex attribute index

---

> RL.rlEnableStatePointer( int vertexAttribType, Buffer buffer )

Enable attribute state pointer

---

> RL.rlDisableStatePointer( int vertexAttribType )

Disable attribute state pointer

---

## RLGL - Textures state

---

> RL.rlActiveTextureSlot( int slot )

Select and active a texture slot

---

> RL.rlEnableTexture( int id )

Enable texture

---

> RL.rlDisableTexture()

Disable texture

---

> RL.rlEnableTextureCubemap( int id )

Enable texture cubemap

---

> RL.rlDisableTextureCubemap()

Disable texture cubemap

---

> RL.rlTextureParameters( int id, int param, int value )

Set texture parameters (filter, wrap)

---

> RL.rlCubemapParameters( int id, int param, int value )

Set cubemap parameters (filter, wrap)

---

## RLGL - Shader state

---

> RL.rlEnableShader( int id )

Enable shader program

---

> RL.rlDisableShader()

Disable shader program

---

## RLGL - Framebuffer state

---

> RL.rlEnableFramebuffer( int id )

Enable render texture (fbo)

---

> RL.rlDisableFramebuffer()

Disable render texture (fbo), return to default framebuffer

---

> RL.rlActiveDrawBuffers( int count )

Activate multiple draw color buffers

---

> RL.rlBlitFramebuffer( Rectangle srcRect, Rectangle dstRect, int bufferMask )

Blit active framebuffer to main framebuffer

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

> RL.rlSetCullFace( int mode )

Set face culling mode

---

> RL.rlEnableScissorTest()

Enable scissor test

---

> RL.rlDisableScissorTest()

Disable scissor test

---

> RL.rlScissor( Rectangle area )

Scissor test

---

> RL.rlEnableWireMode()

Enable wire mode

---

> RL.rlEnablePointMode()

Enable point mode

---

> RL.rlDisableWireMode()

Disable wire mode

---

> RL.rlSetLineWidth( float width )

Set the line drawing width

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

> RL.rlClearColor( Color color )

Clear color buffer with color

---

> RL.rlClearScreenBuffers()

Clear used screen buffers (color and depth)

---

> RL.rlCheckErrors()

Check and log OpenGL error codes

---

> RL.rlSetBlendMode( int mode )

Set blending mode

---

> RL.rlSetBlendFactors( int glSrcFactor, int glDstFactor, int glEquation )

Set blending mode factor and equation (using OpenGL factors)

---

> RL.rlSetBlendFactorsSeparate( int glSrcRGB, int glDstRGB, int glSrcAlpha, int glDstAlpha, int glEqRGB, int glEqAlpha )

Set blending mode factors and equations separately (using OpenGL factors)

---

## RLGL - Initialization functions

---

> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int

---

> version = RL.rlSetFramebufferWidth( int width )

Set current framebuffer width

---

> width = RL.rlGetFramebufferWidth()

Get default framebuffer width

- Success return int

---

> version = RL.rlSetFramebufferHeight( int height )

Set current framebuffer height

---

> height = RL.rlGetFramebufferHeight()

Get default framebuffer height

- Success return int

---

> id = RL.rlGetTextureIdDefault()

Get default texture id

- Success return int

---

> id = RL.rlGetShaderIdDefault()

Get default shader id

- Success return int

---

> locations = RL.rlGetShaderLocsDefault()

Get default shader locations

- Success return int{}

---

## RLGL - Render batch management

---

> renderBatch = RL.rlLoadRenderBatch( int numBuffers, int bufferElements )

Load a render batch system

- Success return rlRenderBatch

---

> RL.rlUnloadRenderBatch( rlRenderBatch renderBatch )

Unload render batch system

---

> RL.rlDrawRenderBatch( rlRenderBatch renderBatch )

Draw render batch data (Update->Draw->Reset)

---

> RL.rlSetRenderBatchActive( rlRenderBatch renderBatch )

Set the active render batch for rlgl (nil for default internal)

---

> RL.rlDrawRenderBatchActive()

Update and draw internal render batch

---

> overflow = RL.rlCheckRenderBatchLimit( int vCount )

Check internal buffer overflow for a given number of vertex and force a rlRenderBatch draw call if required

- Success return bool

---

> RL.rlSetTexture( int id )

Set current texture for render batch and check buffers limits

---

## RLGL - Vertex buffers management

---

> vaoId = RL.rlLoadVertexArray()

Load vertex array (vao) if supported

- Success return int

---

> vboId = RL.rlLoadVertexBuffer( Buffer buffer, bool dynamic )

Load a vertex buffer attribute

- Success return int

---

> vboId = RL.rlLoadVertexBufferElement( Buffer buffer, bool dynamic )

Load a new attributes element buffer

- Success return int

---

> RL.rlUpdateVertexBuffer( int bufferId, Buffer buffer, int offset )

Update GPU buffer with new data

---

> RL.rlUpdateVertexBufferElements( int id, Buffer buffer, int offset )

Update vertex buffer elements with new data

---

> RL.rlUnloadVertexArray( int vaoId )

Unload vertex array object (VAO)

---

> RL.rlUnloadVertexBuffer( int vboId )

Unload vertex buffer (VBO)

---

> RL.rlSetVertexAttribute( int index, int compSize, int type, bool normalized, int stride, int pointer )

Set vertex attribute. NOTE: Pointer should be given in size of bytes

---

> RL.rlSetVertexAttributeDivisor( int index, int divisor )

Set vertex attribute divisor

---

> RL.rlSetVertexAttributeDefault( int locIndex, float{} value, int attribType )

Set vertex attribute default value

---

> RL.rlDrawVertexArray( int offset, int count )

Draw vertex array

---

> RL.rlDrawVertexArrayElements( int offset, int count, Buffer buffer )

Draw vertex array elements

---

> RL.rlDrawVertexArrayInstanced( int offset, int count, int instances )

Draw vertex array instanced

---

> RL.rlDrawVertexArrayElementsInstanced( int offset, int count, Buffer buffer, int instances )

Draw vertex array elements instanced

---

## RLGL - Textures management

---

> id = RL.rlLoadTexture( Buffer data, Vector2 size, int format, int mipmapCount )

Load texture in GPU

- Success return int

---

> id = RL.rlLoadTextureDepth( Vector2 size, bool useRenderBuffer )

Load depth texture/renderbuffer (to be attached to fbo)

- Success return int

---

> id = RL.rlLoadTextureCubemap( Buffer data, int size, int format )

Load texture cubemap

- Success return int

---

> RL.rlUpdateTexture( int id, Vector2 offset, Vector2 size, int format, Buffer data )

Update GPU texture with new data

---

> glInternalFormat, glFormat, glType = RL.rlGetGlTextureFormats( int format )

Get OpenGL internal formats

- Success return int, int, int

---

> name = RL.rlGetPixelFormatName( int format )

Get name string for pixel format

- Success return string

---

> RL.rlUnloadTexture( int id )

Unload texture from GPU memory

---

> mipmapCount = RL.rlGenTextureMipmaps( int id, Vector2 size, int format )

Generate mipmap data for selected texture

- Success return int

---

> data = RL.rlReadTexturePixels( int id, Vector2 size, int format )

Read texture pixel data

- Success return Buffer

---

> data = RL.rlReadScreenPixels( Vector2 size )

Read screen pixel data (color buffer)

- Success return Buffer

---

## RLGL - Framebuffer management (fbo)

---

> fboId = RL.rlLoadFramebuffer( Vector2 size )

Load an empty framebuffer

- Success return int

---

> RL.rlFramebufferAttach( int fboId, int texId, int attachType, int texType, int mipLevel )

Attach texture/renderbuffer to a framebuffer

---

> isComplete = RL.rlFramebufferComplete( int id )

Verify framebuffer is complete

- Success return bool

---

> RL.rlUnloadFramebuffer( int id )

Delete framebuffer from GPU

---

## RLGL - Shaders management

---

> shaderId = RL.rlLoadShaderCode( string vsCode, string fsCode )

Load shader from code strings

- Success return int

---

> shaderId = RL.rlCompileShader( string shaderCode, int type )

Compile custom shader and return shader id (type: RL_VERTEX_SHADER, RL_FRAGMENT_SHADER, RL_COMPUTE_SHADER)

- Success return int

---

> shaderProgramId = RL.rlLoadShaderProgram( int vShaderId, int fShaderId )

Load custom shader program

- Success return int

---

> RL.rlUnloadShaderProgram( int id )

Unload shader program

---

> location = RL.rlGetLocationUniform( int shaderId, string uniformName )

Get shader location uniform

- Success return int

---

> location = RL.rlGetLocationAttrib( int shaderId, string attribName )

Get shader location attribute

- Success return int

---

> RL.rlSetUniform( int locIndex, Buffer value, int uniformType, int count )

Set shader value uniform

---

> RL.rlSetUniformMatrix( int locIndex, Matrix mat )

Set shader value matrix

---

> RL.rlSetUniformSampler( int locIndex, int textureId )

Set shader value sampler

---

> RL.rlSetShader( int id, int{} locs )

Set shader currently active (id and locations)

---

## RLGL - Compute shader management

---

> programId = RL.rlLoadComputeShaderProgram( int shaderId )

Load compute shader program

- Success return int

---

> RL.rlComputeShaderDispatch( int groupX, int groupY, int groupZ )

Dispatch compute shader (equivalent to *draw* for graphics pipeline)

---

## RLGL - Shader buffer storage object management (ssbo)

---

> buffer = RL.rlLoadShaderBuffer( int size, Buffer data, int usageHint )

Load shader storage buffer object (SSBO)

- Success return int

---

> RL.rlUnloadShaderBuffer( int ssboId )

Unload shader storage buffer object (SSBO)

---

> RL.rlUpdateShaderBuffer( int id, Buffer data, int offset )

Update SSBO buffer data

---

> RL.rlBindShaderBuffer( int id, int index )

Bind SSBO buffer

---

> data = RL.rlReadShaderBuffer( int id, int count, int offset )

Read SSBO buffer data (GPU->CPU)

- Success return Buffer

---

> RL.rlCopyShaderBuffer( int destId, int srcId, int destOffset, int srcOffset, int count )

Copy SSBO data between buffers

---

> size = RL.rlGetShaderBufferSize( int id )

Get SSBO buffer size

- Success return int

---

## RLGL - Buffer management

---

> RL.rlBindImageTexture( int id, int index, int format, bool readonly )

Bind image texture

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

- Success return Matrix

---

> viewOffset = RL.rlGetMatrixViewOffsetStereo( int eye )

Get internal view offset matrix for stereo render (selected eye)

- Success return Matrix

---

> RL.rlSetMatrixProjection( Matrix proj )

Set a custom projection matrix (replaces internal projection matrix)

---

> RL.rlSetMatrixModelview( Matrix view )

Set a custom modelview matrix (replaces internal modelview matrix)

---

> RL.rlSetMatrixProjectionStereo( Matrix right, Matrix left )

Set eyes projection matrices for stereo rendering

---

> RL.rlSetMatrixViewOffsetStereo( Matrix right, Matrix left )

Set eyes view offsets matrices for stereo rendering

---

## OpenGL - Framebuffer management

---

> RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use -1 RenderTexture for window framebuffer

---

## Easings - Linear Easing functions

---

> value = RL.EaseLinear( float t, float b, float c, float d )

Ease linear

- Success return float

---

## Easings - Sine Easing functions

---

> value = RL.EaseSineIn( float t, float b, float c, float d )

Ease sine in

- Success return float

---

> value = RL.EaseSineOut( float t, float b, float c, float d )

Ease sine out

- Success return float

---

> value = RL.EaseSineInOut( float t, float b, float c, float d )

Ease sine in out

- Success return float

---

## Easings - Circular Easing functions

---

> value = RL.EaseCircIn( float t, float b, float c, float d )

Ease circle in

- Success return float

---

> value = RL.EaseCircOut( float t, float b, float c, float d )

Ease circle out

- Success return float

---

> value = RL.EaseCircInOut( float t, float b, float c, float d )

Ease circle in out

- Success return float

---

## Easings - Cubic Easing functions

---

> value = RL.EaseCubicIn( float t, float b, float c, float d )

Ease cubic in

- Success return float

---

> value = RL.EaseCubicOut( float t, float b, float c, float d )

Ease cubic out

- Success return float

---

> value = RL.EaseCubicInOut( float t, float b, float c, float d )

Ease cubic in out

- Success return float

---

## Easings - Quadratic Easing functions

---

> value = RL.EaseQuadIn( float t, float b, float c, float d )

Ease quadratic in

- Success return float

---

> value = RL.EaseQuadOut( float t, float b, float c, float d )

Ease quadratic out

- Success return float

---

> value = RL.EaseQuadInOut( float t, float b, float c, float d )

Ease quadratic in out

- Success return float

---

## Easings - Exponential Easing functions

---

> value = RL.EaseExpoIn( float t, float b, float c, float d )

Ease exponential in

- Success return float

---

> value = RL.EaseExpoOut( float t, float b, float c, float d )

Ease exponential out

- Success return float

---

> value = RL.EaseExpoInOut( float t, float b, float c, float d )

Ease exponential in out

- Success return float

---

## Easings - Back Easing functions

---

> value = RL.EaseBackIn( float t, float b, float c, float d )

Ease back in

- Success return float

---

> value = RL.EaseBackOut( float t, float b, float c, float d )

Ease back out

- Success return float

---

> value = RL.EaseBackInOut( float t, float b, float c, float d )

Ease back in out

- Success return float

---

## Easings - Bounce Easing functions

---

> value = RL.EaseBounceIn( float t, float b, float c, float d )

Ease bounce in

- Success return float

---

> value = RL.EaseBounceOut( float t, float b, float c, float d )

Ease bounce out

- Success return float

---

> value = RL.EaseBounceInOut( float t, float b, float c, float d )

Ease bounce in out

- Success return float

---

## Easings - Elastic Easing functions

---

> value = RL.EaseElasticIn( float t, float b, float c, float d )

Ease elastic in

- Success return float

---

> value = RL.EaseElasticOut( float t, float b, float c, float d )

Ease elastic out

- Success return float

---

> value = RL.EaseElasticInOut( float t, float b, float c, float d )

Ease elastic in out

- Success return float

---

## GLFW Core - Input-related functions: keyboard

---

> keyName = RL.GetKeyName( int key, int scancode )

This function returns the name of the specified printable key, encoded as UTF-8.
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

## Window events

---

> GLFWwindowsizeEvent = { int type, int width, int height }

Called when the window is resized. Type GLFW_WINDOW_SIZE_EVENT

---

> GLFWwindowmaximizeEvent = { int type, int maximized }

Called when the window is maximized or restored. Type GLFW_WINDOW_MAXIMIZE_EVENT

---

> GLFWwindowiconifyEvent = { int type, int iconified }

Called when the window is iconified or restored. Type GLFW_WINDOW_ICONYFY_EVENT

---

> GLFWwindowfocusEvent = { int type, int focused }

Called when the window gains or loses input focus. Type GLFW_WINDOW_FOCUS_EVENT

---

> GLFWdropEvent = { int type, int count, string{} paths }

Called when files are dropped to the window. Type GLFW_WINDOW_DROP_EVENT

---

## Input events

---

> GLFWkeyEvent = { int type, int key, int scancode, int action, int mods }

Called when a physical key is pressed or released or when it repeats. Type GLFW_KEY_EVENT

---

> GLFWcharEvent = { int type, int key }

Unicode code points for key events that would have led to regular text input and generally behaves as a standard text field on that platform. Type GLFW_CHAR_EVENT

---

> GLFWmousebuttonEvent = { int type, int button, int action, int mods }

Called when a mouse button is pressed or released. Type GLFW_MOUSE_BUTTON_EVENT

---

> GLFWcursorposEvent = { int type, float x, float y }

Called when the cursor moves over the window. Type GLFW_MOUSE_CURSOR_POS_EVENT

---

> GLFWscrollEvent = { int type, float xoffset, float yoffset }

Called when the user scrolls, whether with a mouse wheel or touchpad gesture. Type GLFW_MOUSE_SCROLL_EVENT

---

> GLFWcursorenterEvent = { int type, int enter }

Called when the cursor enters or leaves the content area of a window. Type GLFW_CURSOR_ENTER_EVENT

---

> GLFWjoystickEvent = { int type, int jid, int event }

Called when a joystick is connected or disconnected. Type GLFW_JOYSTICK_EVENT

---

> GLFWpentabletdataEvent = { int type, float x, float y, float z, float pressure, float pitch, float yaw, float roll }

Called when the pen tablet data is updated. Type GLFW_PEN_TABLET_DATA_EVENT
NOTE: Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445

---

> GLFWpentabletcursorEvent = { int type, int identifier }

Called when the pen tablet cursor has changed. Type GLFW_PEN_TABLET_CURSOR_EVENT
NOTE: Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445

---

> GLFWpentabletproximityEvent = { int type, int proxState }

Called when the pen tablet proximity has changed. Type GLFW_PEN_TABLET_PROXIMITY_EVENT
NOTE: Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445

---
