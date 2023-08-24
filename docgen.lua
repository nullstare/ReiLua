--Create api.md and ReiLua_API.lua files from c sources.

-- Export each module as separate .md file.
local separate = false

if arg ~= nil and arg[1] ~= nil and arg[1] == "-s" then
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

local function getParamType( param )
	if param == "Color" or param == "Vector2" or param == "Vector3" or param == "Vector4"
	or param == "Quaternion" or param == "Matrix" or param == "Rectangle" then
		return "table"
	elseif param == "float" then
		return "number"
	elseif param == "int" then
		return "integer"
	elseif param == "string" then
		return "string"
	elseif param == "bool" then
		return "boolean"
	else
		return "any"
	end
end

local function parseFunction( line )
	local splitted = split( line, "(" )
	local parString = splitted[2]:sub(2)
	parString = parString:sub( 1, #parString - 2 )
	local parameters = split( parString, "," )
	local str = ""
	local parStr = ""

	for i, par in ipairs( parameters ) do
		local sepPar = split( par, " " )
		parStr = parStr..sepPar[2]
		str = str.."---@param "..sepPar[2].." "
		str = str..getParamType( sepPar[1] ).."\n"

		if i < #parameters then
			parStr = parStr..", "
		end
	end

	local returnsAndFuncName = split( splitted[1], "=" )

	for i, ret in ipairs( split( returnsAndFuncName[1]:sub(3), "," ) ) do
		if ret:sub( 1, 1 ) == " " then
			ret = ret:sub(2)
		end

		str = str.."---@return any "..ret.."\n"
	end

	str = str.."function "..returnsAndFuncName[ #returnsAndFuncName ]:sub(2)

	if parStr ~= "" then
		str = str.."( "..parStr.." )"
	else
		str = str.."()"
	end

	return str.." end\n"
end

local apiFile = io.open( "../API.md", "w" )
local luaApiFile = io.open( "../ReiLua_API.lua", "w" )

-- Header
apiFile:write( "# ReiLua API\n" )

-- Usage.

apiFile:write( "\n## Usage\n" )
apiFile:write( "\nApplication needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where \"main.lua\" is located can be given as argument. There are five Lua functions that the framework will call, 'RL.init', 'RL.process', 'RL.draw', 'RL.event', 'RL.log', and 'RL.exit'.\n" )

local FUNC_DESC = {
	init = "This function will be called first when 'main.lua' is found",
	process = "This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'",
	draw = "This function will be called every frame after process and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.",
	event = "This function will be called on events input. Content of event table is determined by event type.",
	log = "This function can be used for custom log message handling.",
	exit = "This function will be called on program close. Cleanup could be done here.",
}

apiFile:write( "\n---\n> function RL.init()\n\n"..FUNC_DESC.init.."\n\n---\n" )
apiFile:write( "\n> function RL.process( delta )\n\n"..FUNC_DESC.process.."\n\n---\n" )
apiFile:write( "\n> function RL.draw()\n\n"..FUNC_DESC.draw.."\n\n---\n" )
apiFile:write( "\n> function RL.event( event )\n\n"..FUNC_DESC.event.."\n\n---\n" )
apiFile:write( "\n> function RL.log( logLevel, message )\n\n"..FUNC_DESC.log.."\n\n---\n" )
apiFile:write( "\n> function RL.exit()\n\n"..FUNC_DESC.exit.."\n\n---\n" )

luaApiFile:write( "-- Put this file into your project folder to provide annotations when using Lua language server.\n\n" )
luaApiFile:write( "RL={}\n\n" )
luaApiFile:write( "-- Functions.\n\n" )

luaApiFile:write(
"---"..FUNC_DESC.init.."\nfunction RL.init() end\n" )
luaApiFile:write(
"---"..FUNC_DESC.process.."\n---@param delta number\nfunction RL.process( delta ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.draw.."\nfunction RL.draw() end\n" )
luaApiFile:write(
"---"..FUNC_DESC.event.."\n---@param event table\nfunction RL.event( event ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.log.."\n---@param logLevel integer\n---@param message string\nfunction RL.log( logLevel, message ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.exit.."\nfunction RL.exit() end\n" )

-- Globals.

local srcFile = io.open( "../src/lua_core.c", "r" )
local writing = false
local globalVariableCount = 0

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
			luaApiFile:write( "\n-- Globals - "..lineSplit[2].."\n\n" )
		else
			-- Remove comma from the end.
			local globalName = lineSplit[2]:sub( 1, -2 )

			local value = RL[ globalName ]
			
			globalVariableCount = globalVariableCount + 1

			if value == nil then
				apiFile:write( "\n"..globalName.." = nil\n" )
				luaApiFile:write( "RL."..globalName.."=nil\n" )
			elseif type( value ) == "table" then
				-- All tables are colors.
				apiFile:write( globalName.." = { "
					..math.tointeger( value[1] )..", "..math.tointeger( value[2] )..", "
					..math.tointeger( value[3] )..", "..math.tointeger( value[4] ).." }\n" )
				luaApiFile:write( "RL."..globalName.."={"
					..math.tointeger( value[1] )..","..math.tointeger( value[2] )..","
					..math.tointeger( value[3] )..","..math.tointeger( value[4] ).."}\n" )
			else
				apiFile:write( globalName.." = "..value.."\n" )
				luaApiFile:write( "RL."..globalName.."="..value.."\n" )
			end
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
apiFile:write( "\n> Texture = TextureId or { id, width, height, mipmaps, format }\n\
int id. Texture type (multiple internal formats supported). NOTE: Data stored in GPU memory (VRAM)\n\n---\n" )
apiFile:write( "\n> RenderTexture = RenderTextureId or { id, texture, depth }\n\
int id. RenderTexture type, for texture rendering\n\n---\n" )
apiFile:write( "\n> Font = FontId\n\
int id. Font type, includes texture and chars data\n\n---\n" )
apiFile:write( "\n> Camera2D = CameraId or { offset, target, rotation, zoom }\n\
int id. Defines 2D camera position/orientation\n\n---\n" )
apiFile:write( "\n> Camera = CameraId or { position, target, up, fovy, projection }\n\
int id. Defines 3D camera3D position/orientation\n\n---\n" )
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
apiFile:write( "\n> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } } or { min = { 0.0, 0.0, 0.0 }, max = { 1.0, 1.0, 1.0 } }\n\
{ min, max }. Accepts Vector3. Bounding box type for 3d mesh\n\n---\n" )
apiFile:write( "\n> Sound = SoundId\n\
int id. Basic Sound source and buffer\n\n---\n" )
apiFile:write( "\n> NPatchInfo = { { 0, 0, 24, 24 }, 8, 8, 8, 8, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }\n\
{ Rectangle source, int left, int top, int right, int bottom, int layout }.\
{ Texture source rectangle, Left border offset, Top border offset, Right border offset, Bottom border offset, Layout of the n-patch: 3x3, 1x3 or 3x1 }\n\n---\n" )
apiFile:write( "\n> ModelAnimations = ModelAnimationsId\n\
int id. ModelAnimations\n\n---\n" )

-- Events.

apiFile:write( "\n## Events\n" )
apiFile:write( "\nContent of event table received by RL.event.\n" )
apiFile:write( "\n### Window events\n" )
apiFile:write( "\n---\n> { type: RL.EVENT_WINDOW_SIZE, int width, int height }\n\n WindowSize Callback, runs when window is resized.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_WINDOW_MAXIMIZE, int maximized }\n\n Window Maximize Callback, runs when window is maximized.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_WINDOW_ICONYFY, int iconified }\n\n WindowIconify Callback, runs when window is minimized/restored.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_WINDOW_FOCUS, int focused }\n\n WindowFocus Callback, runs when window get/lose focus.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_WINDOW_DROP, int count, string{} paths }\n\n Window Drop Callback, runs when drop files into window.\n\n---\n" )
apiFile:write( "\n### Input events\n" )
apiFile:write( "\n---\n> { type: RL.EVENT_KEY, int key, int scancode, int action, int mods }\n\n Keyboard Callback, runs on key pressed.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_CHAR, int key }\n\n Char Key Callback, runs on key pressed (get char value).\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_MOUSE_BUTTON, int button, int action, int mods }\n\n Mouse Button Callback, runs on mouse button pressed.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_MOUSE_CURSOR_POS, number x, number y }\n\n Cursor Position Callback, runs on mouse move.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_MOUSE_SCROLL, number xoffset, number yoffset }\n\n Srolling Callback, runs on mouse wheel.\n\n---\n" )
apiFile:write( "\n> { type RL.EVENT_CURSOR_ENTER, int enter }\n\n Cursor Enter Callback, cursor enters client area.\n\n---\n" )

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
	"gl",
	"easings",
}

local functionCount = 0

for _, src in ipairs( sourceFiles ) do
	srcFile = io.open( "../src/"..src..".c", "r" )
	local line = ""
	local funcStr = ""
	local p = false

	if separate then
		apiFile = io.open( src..".md", "w" )
	end

	repeat
		line = srcFile:read( "*l" )

		if line == "*/" then
			p = false
			apiFile:write( "\n---\n" )
			luaApiFile:write( funcStr.."\n" )
			funcStr = ""
		end

		if p then
			apiFile:write( line.."\n" )

			if line:sub( 1, 2 ) == "##" then
				luaApiFile:write( "-- "..line:sub( 4 ).."\n" )
			elseif line:sub( 1, 1 ) == ">" then
				funcStr =  parseFunction( line )
				functionCount = functionCount + 1
			elseif line:sub( 1, 1 ) ~= "" then
				luaApiFile:write( "---"..line.."\n" )
			end
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

print( "Parsed:\n"..globalVariableCount.." Global variables\n"..functionCount.." Functions" )