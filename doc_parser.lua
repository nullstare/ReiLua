--Create api.md file from c sources.

-- Export each module as separate .md file.
local separate = false

if arg[1] ~= nil and arg[1] == "-s" then
	separate = true
end

local function split( str, sep )
	if sep == nil then
		sep = "%s"
	end

	local t = {}

	for str in string.gmatch( str, "([^"..sep.."]+)" ) do
		table.insert( t, str )
	end

	return t
end

local apiFile = io.open( "API.md", "w" )

-- Header
apiFile:write( "# ReiLua API\n" )

-- Usage.

apiFile:write( "\n## Usage\n" )
apiFile:write( "\nApplication needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where \"main.lua\" is located can be given as argument. There are three global Lua functions that the engine will call, 'init', 'process' and 'draw'.\n" )

apiFile:write( "\n---\n> function init()\n\
This function will be called first when 'main.lua' is found\n\n---\n" )
apiFile:write( "\n> function process( delta )\n\
This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'\n\n---\n" )
apiFile:write( "\n> function draw()\n\
This function will be called every frame after process and it should have all rendering related functions.\
Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it.\
You can still use RL_BeginDrawing() and RL_EndDrawing() manually from anywhere.\n\n---\n" )
apiFile:write( "\n> function log( logLevel, message )\n\
This function can be used for custom log message handling.\n\n---\n" )
apiFile:write( "\n> function exit()\n\
This function will be called on program close. Cleanup could be done here.\n\n---\n" )

-- Globals.

local srcFile = io.open( "src/lua_core.c", "r" )
local writing = false

repeat
	line = srcFile:read( "*l" )
	local lineSplit = split( line, " " )

	if line == "/*DOC_END*/" then
		writing = false
		break
	end

	if writing then
		if lineSplit[1] == "\t/*" then
			apiFile:write( "\n## Globals - "..lineSplit[2].."\n" )
		else
			-- Remove comma from the end.
			apiFile:write( "\n"..lineSplit[2]:sub( 1, -2 ).."\n" )
		end
	end

	if line == "/*DOC_START*/" then
		writing = true
	end
until line == nil

srcFile:close()

-- Types.

apiFile:write( "\n## Types\n\
Raylib structs in Lua\n\n---\n" )

apiFile:write( "\n> Vector2 = { 1.0, 1.0 } or { x = 1.0, y = 1.0 }\n\
Vector2 type\n\n---\n" )
apiFile:write( "\n> Vector3 = { 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0 }\n\
Vector3 type\n\n---\n" )
apiFile:write( "\n> Vector4 = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }\n\
Vector4 type\n\n---\n" )
apiFile:write( "\n> Quaternion = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }\n\
Quaternion type\n\n---\n" )
apiFile:write( "\n> Matrix = { { 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } }\n\
OpenGL style 4x4. Identity matrix example\n\n---\n" )
apiFile:write( "\n> Color = { 255, 255, 255, 255 } or { r = 255, g = 255, b = 255, a = 255 }\n\
{ r, g, b ,a }. Color type, RGBA (32bit)\n\n---\n" )
apiFile:write( "\n> Rectangle = { 0.0, 0.0, 1.0, 1.0 } or { x = 0.0, y = 0.0, width = 1.0, height = 1.0 }\n\
{ x, y, width ,height }. Rectangle type\n\n---\n" )
apiFile:write( "\n> Image = ImageId\n\
int id. Image type (multiple pixel formats supported). NOTE: Data stored in CPU memory (RAM)\n\n---\n" )
apiFile:write( "\n> Texture = TextureId\n\
int id. Texture type (multiple internal formats supported). NOTE: Data stored in GPU memory (VRAM)\n\n---\n" )
apiFile:write( "\n> RenderTexture = RenderTextureId\n\
int id. RenderTexture type, for texture rendering\n\n---\n" )
apiFile:write( "\n> Font = FontId\n\
int id. Font type, includes texture and chars data\n\n---\n" )
apiFile:write( "\n> Camera = CameraId\n\
int id. Defines 3d camera position/orientation\n\n---\n" )
apiFile:write( "\n> Mesh = MeshId\n\
int id. Vertex data defining a mesh\n\
```\
mesh{} = {\
  vertices = { Vector3, ... },\
  texcoords = { Vector2, ... },\
  texcoords2 = { Vector2, ... },\
  normals = { Vector3, ... },\
  tangents = { Vector4, ... },\
  colors = { Color, ... },\
  indices = { int, ... },\
}\
```\n\n---\n" )
apiFile:write( "\n> Material = MaterialId\n\
int id. Material type\n\
```\
material{} = {\
  shader = Shader,\
  maps = {\
    {\
      MATERIAL_MAP_ALBEDO,\
      {\
        texture = Texture,\
        color = WHITE,\
        value = 1.0,\
      },\
    },\
    ...\
  },\
  params = { 1.0, 2.0, 3.0, 4.0 },\
}\
```\n\n---\n" )
apiFile:write( "\n> Model = ModelId\n\
int id. Basic 3d Model type\n\n---\n" )
apiFile:write( "\n> Ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } or { position = { 0.0, 0.0, 0.0 }, direction = { 1.0, 0.0, 0.0 } }\n\
{ position, direction }. Ray type (useful for raycast)\n\n---\n" )
apiFile:write( "\n> RayCollision = { hit = true, distance = 1.0, point = { 0.0, 0.0, 0.0 }, normal = { 0.0, 0.0, 1.0 } }\n\
Raycast hit information. NOTE: Data in named keys\n\n---\n" )
apiFile:write( "\n> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } }\n\
{ min, max }. Bounding box type for 3d mesh\n\n---\n" )
apiFile:write( "\n> Sound = SoundId\n\
int id. Basic Sound source and buffer\n\n---\n" )
apiFile:write( "\n> NPatchInfo = { { 0, 0, 24, 24 }, 8, 8, 8, 8, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }\n\
{ Rectangle source, int left, int top, int right, int bottom, int layout }.\
{ Texture source rectangle, Left border offset, Top border offset, Right border offset, Bottom border offset, Layout of the n-patch: 3x3, 1x3 or 3x1 }\n\n---\n" )
apiFile:write( "\n> ModelAnimations = ModelAnimationsId\n\
int id. ModelAnimations\n\n---\n" )

if separate then
	apiFile:close()
end

-- Functions.

local sourceFiles = {
	"core",
	"shapes",
	"textures",
	"text",
	"models",
	"audio",
	"rmath",
	"rgui",
	"lights",
	"rlgl",
	"easings",
}

for _, src in ipairs( sourceFiles ) do
	srcFile = io.open( "src/"..src..".c", "r" )
	local line = ""
	local p = false

	if separate then
		apiFile = io.open( src..".md", "w" )
	end

	repeat
		line = srcFile:read( "*l" )

		if line == "*/" then
			p = false
			apiFile:write( "\n---\n" )
		end
		
		if p then
			apiFile:write( line.."\n" )
		end
		
		if line == "/*" then
			p = true
			apiFile:write( "\n" )
		end
	until line == nil

	srcFile:close()

	if separate then
		apiFile:close()
	end
end

if not separate then
	apiFile:close()
end
