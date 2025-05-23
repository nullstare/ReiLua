--[[
	Create api.md and ReiLua_API.lua files from c sources.

	To generate API for other platforms you need to change sourceFiles.
]]--

-- Export each module as separate .md file. Does not affect on ReiLua_API.lua file.
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
	elseif param == "float" then return "number"
	elseif param == "int" then return "integer"
	elseif param == "string" then return "string"
	elseif param == "bool" then return "boolean"
	elseif param == "nil" then return "nil"
	elseif param:sub( #param - 1, #param ) == "{}" then return "table"
	else 
		return "any"
	end
end

local function getParam( param )
	local text = ""
	local params = split( param, "|" )

	for i, p in ipairs( params ) do
		text = text..getParamType( p )

		if i < #params then
			text = text.."|"
		end
	end

	return text
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
		-- str = str..getParamType( sepPar[1] ).."\n"
		str = str..getParam( sepPar[1] ).."\n"

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

apiFile:write( "\n## Functions\n" )
apiFile:write( "\nApplication needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where \"main.lua\" is located can be given as argument. There are seven Lua functions that the framework will call, 'RL.init', 'RL.update', 'RL.draw', 'RL.event', 'RL.log', 'RL.exit' and 'RL.config'.\n" )

local FUNC_DESC = {
	init = "This function will be called after window has been initialized. Should be used as the main init point.",
	update = "This function will be called every frame during execution. It will get time duration from last frame on argument 'delta'",
	draw = "This function will be called every frame after update and it should have all rendering related functions. Note: Engine will call Raylib functions 'BeginDrawing()' before this function call and 'EndDrawing()' after it. You can still use RL.BeginDrawing() and RL.EndDrawing() manually from anywhere.",
	event = "This function will be called on events input. Content of event table is determined by event type.",
	log = "This function can be used for custom log message handling.",
	exit = "This function will be called on program close. Cleanup could be done here.",
	config = "This function will be called before InitWindow. Note! Only place where you should call InitWindow manually. Doesn't have OpenGL context at this point.",
	load = "This function will be called when loading resource that allocates memory. Usefull for memory leak debugging. Note! Cannot detect all resources, for example material textures.",
	unload = "This function will be called when unloading resource that has allocated memory. Usefull for memory leak debugging. Note! Cannot detect all resources, for example material textures.",
}

apiFile:write( "\n---\n> function RL.init()\n\n"..FUNC_DESC.init.."\n\n---\n" )
apiFile:write( "\n> function RL.update( delta )\n\n"..FUNC_DESC.update.."\n\n---\n" )
apiFile:write( "\n> function RL.draw()\n\n"..FUNC_DESC.draw.."\n\n---\n" )
apiFile:write( "\n> function RL.event( event )\n\n"..FUNC_DESC.event.."\n\n---\n" )
apiFile:write( "\n> function RL.log( logLevel, message )\n\n"..FUNC_DESC.log.."\n\n---\n" )
apiFile:write( "\n> function RL.exit()\n\n"..FUNC_DESC.exit.."\n\n---\n" )
apiFile:write( "\n> function RL.config()\n\n"..FUNC_DESC.config.."\n\n---\n" )
apiFile:write( "\n> function RL.load()\n\n"..FUNC_DESC.load.."\n\n---\n" )
apiFile:write( "\n> function RL.unload()\n\n"..FUNC_DESC.unload.."\n\n---\n" )

luaApiFile:write( "-- Put this file into your project folder to provide annotations when using Lua language server.\n\n" )
luaApiFile:write( "RL={}\n\n" )
luaApiFile:write( "-- Functions.\n\n" )

luaApiFile:write(
"---"..FUNC_DESC.init.."\nfunction RL.init() end\n" )
luaApiFile:write(
"---"..FUNC_DESC.update.."\n---@param delta number\nfunction RL.update( delta ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.draw.."\nfunction RL.draw() end\n" )
luaApiFile:write(
"---"..FUNC_DESC.event.."\n---@param event table\nfunction RL.event( event ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.log.."\n---@param logLevel integer\n---@param message string\nfunction RL.log( logLevel, message ) end\n" )
luaApiFile:write(
"---"..FUNC_DESC.exit.."\nfunction RL.exit() end\n" )
luaApiFile:write(
"---"..FUNC_DESC.config.."\nfunction RL.config() end\n" )

-- Object unloading.

apiFile:write( "\n## Object unloading\n" )
apiFile:write( "\nSome objects allocate memory that needs to be freed when object is no longer needed. By default objects like Textures are unloaded by the Lua garbage collector. It is generatty however recommended to handle this manually in more complex projects. You can change the behavior with SetGCUnload.\n" )

-- Arguments.

apiFile:write( "\n## Arguments\n" )
apiFile:write( "\nArguments are stored in 'RL.arg' array.\n" )

-- Structures.

apiFile:write( "\n## Structures\n\
Raylib structs in Lua\n\n---\n" )

apiFile:write( "\n> Vector2 = { 1.0, 1.0 } or { x = 1.0, y = 1.0 }\n\
Vector2, 2 components\n\n---\n" )
apiFile:write( "\n> Vector3 = { 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0 }\n\
Vector3, 3 components\n\n---\n" )
apiFile:write( "\n> Vector4 = { 1.0, 1.0, 1.0, 1.0 } or { x = 1.0, y = 1.0, z = 1.0, w = 1.0 }\n\
Vector4, 4 components\n\n---\n" )
apiFile:write( "\n> Quaternion = { 0.0, 0.0, 0.0, 1.0 } or { x = 0.0, y = 0.0, z = 0.0, w = 1.0 }\n\
Quaternion, 4 components (Vector4 alias)\n\n---\n" )
apiFile:write( "\n> Matrix = { { 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } }\n\
Matrix, 4x4 components, column major, OpenGL style, right-handed. Identity matrix example\n\n---\n" )
apiFile:write( "\n> Color = { 255, 255, 255, 255 } or { r = 255, g = 255, b = 255, a = 255 }\n\
Color, 4 components, R8G8B8A8 (32bit)\n\n---\n" )
apiFile:write( "\n> Rectangle = { 0.0, 0.0, 1.0, 1.0 } or { x = 0.0, y = 0.0, width = 1.0, height = 1.0 }\n\
Rectangle, 4 components\n\n---\n" )
apiFile:write( "\n> Image = Userdata\n\
Image, pixel data stored in CPU memory (RAM)\n\n---\n" )
apiFile:write( "\n> Texture = Userdata\n\
Texture, tex data stored in GPU memory (VRAM)\
```\
textureData = {\
	id = unsigned int,		--OpenGL texture id\
	width = int,			--Texture base width\
	height = int,			--Texture base height\
	mipmaps = int,			--Mipmap levels, 1 by default\
	format = int			--Data format (PixelFormat type)\
}\
```\n\n---\n" )
apiFile:write( "\n> RenderTexture = Userdata\n\
RenderTexture, fbo for texture rendering\
```\
renderTextureData = {\
	id = unsigned int,		--OpenGL framebuffer object id\
	texture = Texture,		--Color buffer attachment texture\
	depth = Texture,		--Depth buffer attachment texture\
}\
```\n\n---\n" )
apiFile:write( "\n> Font = Userdata\n\
Font, font texture and GlyphInfo array data\n\n---\n" )
apiFile:write( "\n> Camera2D = Userdata\n\
Camera2D, defines position/orientation in 2d space\n\n---\n" )
apiFile:write( "\n> Camera3D = Userdata\n\
Camera, defines position/orientation in 3d space\n\n---\n" )
apiFile:write( "\n> Mesh = Userdata\n\
Mesh, vertex data and vao/vbo\n\
```\
meshData = {\
	vertices = Vector3{},		--Vertex position (XYZ - 3 components per vertex) (shader-location = 0)\
	texcoords = Vector2{},		--Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)\
	texcoords2 = Vector2{},		--Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)\
	normals = Vector3{},		--Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)\
	tangents = Vector4{},		--Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)\
	colors = Color{},			--Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)\
	indices = int{}				--Vertex indices (in case vertex data comes indexed)\
}\
```\n\n---\n" )
apiFile:write( "\n> Material = Userdata\n\
Material, includes shader and maps\n\
```\
materialData = {\
	shader = Shader,\
	maps = {									--Material maps array (MAX_MATERIAL_MAPS)\
		{\
    		MATERIAL_MAP_*,						--Example MATERIAL_MAP_ALBEDO\
			{\
    			texture = Texture,				--Material map texture\
        		color = Color,					--Material map color\
        		value = float,					--Material map value\
      		},\
    	},\
    	...\
  	},\
  	params = { float, float, float, float }		--Material generic parameters (if required)\
}\
```\n\n---\n" )
apiFile:write( "\n> Model = Userdata\n\
Model, meshes, materials and animation data\n\n---\n" )
apiFile:write( "\n> Ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } or { position = { 0.0, 0.0, 0.0 }, direction = { 1.0, 0.0, 0.0 } }\n\
Ray, ray for raycasting\n\n---\n" )
apiFile:write( "\n> RayCollision = { hit = true, distance = 1.0, point = { 0.0, 0.0, 0.0 }, normal = { 0.0, 0.0, 1.0 } }\n\
RayCollision, ray hit information\n\n---\n" )
apiFile:write( "\n> BoundingBox = { { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 } } or { min = { 0.0, 0.0, 0.0 }, max = { 1.0, 1.0, 1.0 } }\n\
BoundingBox\n\n---\n" )
apiFile:write( "\n> GlyphInfo = Userdata\n\
GlyphInfo, font characters glyphs info\n\
```\
glyphInfoData = {\
	value = int,		--Character value (Unicode)\
	offsetX = int,		--Character offset X when drawing\
	offsetY = int,		--Character offset Y when drawing\
	advanceX = int,		--Character advance position X\
	image = Image,		--Character image data\
}\
```\n\n---\n" )
apiFile:write( "\n> BoneInfo = { name = string[32], parent = int }\n\
Bone, skeletal animation bone\n\n---\n" )
apiFile:write( "\n> Transform = { translation = Vector3, rotation = Quaternion, scale = Vector3 }\n\
Transform, vertex transformation data\n\n---\n" )
apiFile:write( "\n> Wave = Userdata\n\
Wave, audio wave data\n\n---\n" )
apiFile:write( "\n> Sound = Userdata\n\
Sound\n\n---\n" )
apiFile:write( "\n> SoundAlias = Userdata\n\
SoundAlias\n\n---\n" )
apiFile:write( "\n> Music = Userdata\n\
Music, audio stream, anything longer than ~10 seconds should be streamed\n\n---\n" )
apiFile:write( "\n> NPatchInfo = { { 0, 0, 24, 24 }, 8, 8, 8, 8, NPATCH_NINE_PATCH } or { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH }\n\
NPatchInfo, n-patch layout info\n\n---\n" )
apiFile:write( "\n> ModelAnimations = Userdata\n\
ModelAnimation\n\n---\n" )
apiFile:write( "\n> AutomationEvent = Userdata\n\
Automation event\n\n---\n" )
apiFile:write( "\n> AutomationEventList = Userdata\n\
Automation event list\n\n---\n" )
apiFile:write( "\n> Buffer = Buffer userdata\n\
Data buffer for C primitive types. Type should be one of the Buffer types.\n\n---\n" )

if separate then
	apiFile:close()
end

-- Defines.

local definesCount = 0
local sourceFiles = {
	"lua_core",
	"platforms/core_desktop_glfw",
	-- "platforms/core_desktop_sdl",
}

for _, src in ipairs( sourceFiles ) do
	local srcFile = io.open( "../src/"..src..".c", "r" )
	local writing = false

	if separate then
		local splits = split( src, "/" )

		apiFile = io.open( "../"..splits[ #splits ]..".md", "w" )
	end
	
	repeat
		local line = srcFile:read( "*l" )
		local lineSplit = split( line, " " )
	
		if line == "/*DOC_DEFINES_END*/" then
			writing = false
			break
		end
	
		if writing then
			if lineSplit[1] == "\t/*" then
				local gategorySplit = split( line, "*" )
				apiFile:write( "\n## Defines - "..gategorySplit[2]:sub( 2, #gategorySplit[2] - 1 ).."\n" )
				luaApiFile:write( "\n-- Defines - "..gategorySplit[2]:sub( 2, #gategorySplit[2] - 1 ).."\n\n" )
			else
				-- Remove comma from the end.
				local defineName = lineSplit[2]:sub( 1, -2 )
				local value = RL[ defineName ]
				local comment = lineSplit[6] -- First split after //
	
				if comment ~= nil then
					local i = 7
	
					while lineSplit[i] ~= nil do
						comment = comment.." "..lineSplit[i]
						i = i + 1
					end
					luaApiFile:write( "---"..comment.."\n" )
				end
				
				definesCount = definesCount + 1
	
				if value == nil then
					apiFile:write( "\n"..defineName.." = nil\n\n" )
					luaApiFile:write( "RL."..defineName.."=nil\n" )
				elseif type( value ) == "table" then
					-- All tables are colors.
					apiFile:write( defineName.." = { "
						..math.floor( value[1] )..", "..math.floor( value[2] )..", "
						..math.floor( value[3] )..", "..math.floor( value[4] ).." }\n\n" )
					luaApiFile:write( "RL."..defineName.."={"
						..math.floor( value[1] )..","..math.floor( value[2] )..","
						..math.floor( value[3] )..","..math.floor( value[4] ).."}\n" )
				else
					apiFile:write( "> "..defineName.." = "..value.."\n\n" )
					luaApiFile:write( "RL."..defineName.."="..value.."\n" )
				end
	
				if comment ~= nil then
					apiFile:write( comment.."\n\n" )
				end
	
				apiFile:write( "---\n\n" )
			end
		end
	
		if line == "/*DOC_DEFINES_START*/" then
			writing = true
		end
	until line == nil

	srcFile:close()
end

-- Functions and events.

sourceFiles = {
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
	"bitwiseOp",
	"platforms/core_desktop_glfw",
	-- "platforms/core_desktop_sdl",
}

local functionCount = 0

for _, src in ipairs( sourceFiles ) do
	local srcFile = io.open( "../src/"..src..".c", "r" )
	local line = ""
	local funcStr = ""
	local p = false
	local event = false

	if separate then
		local splits = split( src, "/" )

		apiFile = io.open( "../"..splits[ #splits ]..".md", "a" )
	end

	repeat
		line = srcFile:read( "*l" )

		if line == "*/" then
			p = false
			apiFile:write( "\n---\n" )

			if not event then
				luaApiFile:write( funcStr.."\n" )
				funcStr = ""
			end
		-- There should be not function definition after events.
		elseif line == "/* Events. */" then
			event = true
		end

		if p then
			apiFile:write( line.."\n" )

			if line:sub( 1, 2 ) == "##" then
				if not event then
					luaApiFile:write( "-- "..line:sub( 4 ).."\n" )
				end
			elseif line:sub( 1, 1 ) == ">" then
				-- Do not parse events. Only visible in API.md
				if not event then
					funcStr = parseFunction( line )
					functionCount = functionCount + 1
				end
			elseif line:sub( 1, 1 ) ~= "" then
				if not event then
					luaApiFile:write( "---"..line.."\n" )
				end
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

print( "Parsed:\n"..definesCount.." Defines\n"..functionCount.." Functions" )
