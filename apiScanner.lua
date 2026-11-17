local raylib = {
	prefix = "RLAPI",
	file = "raylib.h",
	funcBlacklist = {
		GetScreenWidth = "Replaced by GetScreenSize",
		GetScreenHeight = "Replaced by GetScreenSize",
		GetRenderWidth = "Replaced by GetRenderSize",
		GetRenderHeight = "Replaced by GetRenderSize",
		GetMonitorWidth = "Replaced by GetMonitorSize",
		GetMonitorHeight = "Replaced by GetMonitorSize",
		GetMonitorPhysicalWidth = "Replaced by GetMonitorPhysicalSize",
		GetMonitorPhysicalHeight = "Replaced by GetMonitorPhysicalSize",
		UnloadRandomSequence = "Handled internally",
		MemAlloc = "Buffer should be used instead",
		MemRealloc = "Buffer should be used instead",
		MemFree = "Buffer should be used instead",
		SetTraceLogCallback = "Handled internally",
		SetLoadFileDataCallback = "Not seen necessary",
		SetSaveFileDataCallback = "Not seen necessary",
		SetLoadFileTextCallback = "Not seen necessary",
		SetSaveFileTextCallback = "Not seen necessary",
		UnloadFileData = "Handled internally",
		UnloadFileText = "Handled internally",
		UnloadDirectoryFiles = "Handled internally",
		UnloadDroppedFiles = "Handled internally",
		GetMouseX = "Replaced by GetMousePosition",
		GetMouseY = "Replaced by GetMousePosition",
		GetTouchX = "Replaced by GetTouchPosition",
		GetTouchY = "Replaced by GetTouchPosition",
		UpdateCamera = "Replaced by UpdateCamera3D",
		UpdateCameraPro = "Replaced by UpdateCameraPro3D",
		DrawPixelV = "Replaced by DrawPixel",
		DrawLineV = "Replaced by DrawLine",
		DrawLineEx = "Replaced by DrawLine",
		DrawCircleV = "Replaced by DrawCircle",
		DrawCircleLinesV = "Replaced by DrawCircleLines",
		DrawRectangleV = "Replaced by DrawRectangle",
		DrawRectangleRec = "Replaced by DrawRectangle",
		UnloadImageColors = "Handled internally",
		UnloadImagePalette = "Handled internally",
		ImageDrawPixelV = "Replaced by ImageDrawPixel",
		ImageDrawLineV = "Replaced by ImageDrawLine",
		ImageDrawCircleV = "Replaced by ImageDrawCircle",
		ImageDrawCircleLinesV = "Replaced by ImageDrawCircleLines",
		ImageDrawRectangleV = "Replaced by ImageDrawRectangle",
		ImageDrawRectangleRec = "Replaced by ImageDrawRectangle",
		ImageDrawRectangleGradientEx = "Replaced by ImageDrawRectangleGradient (no thick as other Ex functions)",
		ImageDrawImagePro = "Origin and rotation not implemented",
		DrawTextureV = "Replaced by DrawTexture",
		UnloadFontData = "Handled internally",
		UnloadUTF8 = "Handled internally",
		UnloadCodepoints = "Handled internally",
		TextCopy = "Can be replaced by Lua equivalent",
		TextIsEqual = "Can be replaced by Lua equivalent",
		TextLength = "Can be replaced by Lua equivalent",
		TextFormat = "Can be replaced by Lua equivalent",
		TextJoin = "Can be replaced by Lua equivalent",
		TextAppend = "Can be replaced by Lua equivalent",
		TextToUpper = "Can be replaced by Lua equivalent",
		TextToLower = "Can be replaced by Lua equivalent",
		TextToInteger = "Can be replaced by Lua equivalent",
		TextToFloat = "Can be replaced by Lua equivalent",
		LoadTextLines = "Can be replaced by Lua equivalent",
		UnloadTextLines = "Can be replaced by Lua equivalent",
		TextRemoveSpaces = "Can be replaced by Lua equivalent",
		GetTextBetween = "Can be replaced by Lua equivalent",
		TextReplaceAlloc = "Not seen necessary",
		TextReplaceBetween = "Can be replaced by Lua equivalent",
		TextReplaceBetweenAlloc = "Not seen necessary",
		TextInsertAlloc = "Not seen necessary",
		MeasureTextCodepoints = "Not seen necessary",
		DrawCubeV = "Replaced by DrawCube",
		DrawCubeWiresV = "Replaced by DrawCubeWires",
		UploadMesh = "Handled internally",
		UpdateMeshBuffer = "Handled internally",
		UnloadWaveSamples = "Handled internally",
		GetPixelColor = "Not seen necessary",
		SetPixelColor = "Not seen necessary",
		DrawEllipseV = "Replaced by DrawEllipse",
		DrawEllipseLinesV = "Replaced by DrawEllipseLines",
	},
	-- enumBlacklist = {},
	info = {
	}
}
local rlgl = {
	prefix = "RLAPI",
	file = "rlgl.h",
	funcBlacklist = {
		rlVertex2i = "Most likely not needed",
		rlglInit = "Handled internally",
		rlglClose = "Handled internally",
		rlLoadExtensions = "Handled internally",
		rlLoadDrawCube = "Most likely not needed",
		rlLoadDrawQuad = "Most likely not needed",
		rlGetProcAddress = "Most likely not needed",
	},
	enumBlacklist = {
		RL_LOG_ALL = "Same as LOG_ALL",
		RL_LOG_TRACE = "Same as LOG_TRACE",
		RL_LOG_DEBUG = "Same as LOG_DEBUG",
		RL_LOG_INFO = "Same as LOG_INFO",
		RL_LOG_WARNING = "Same as LOG_WARNING",
		RL_LOG_ERROR = "Same as LOG_ERROR",
		RL_LOG_FATAL = "Same as LOG_FATAL",
		RL_LOG_NONE = "Same as LOG_NONE",
		RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = "Same as PIXELFORMAT_UNCOMPRESSED_GRAYSCALE",
		RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA = "Same as PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA",
		RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5 = "Same as PIXELFORMAT_UNCOMPRESSED_R5G6B5",
		RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8 = "Same as PIXELFORMAT_UNCOMPRESSED_R8G8B8",
		RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 = "Same as PIXELFORMAT_UNCOMPRESSED_R5G5B5A1",
		RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 = "Same as PIXELFORMAT_UNCOMPRESSED_R4G4B4A4",
		RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = "Same as PIXELFORMAT_UNCOMPRESSED_R8G8B8A8",
		RL_PIXELFORMAT_UNCOMPRESSED_R32 = "Same as PIXELFORMAT_UNCOMPRESSED_R32",
		RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32 = "Same as PIXELFORMAT_UNCOMPRESSED_R32G32B32",
		RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 = "Same as PIXELFORMAT_UNCOMPRESSED_R32G32B32A32",
		RL_PIXELFORMAT_UNCOMPRESSED_R16 = "Same as PIXELFORMAT_UNCOMPRESSED_R16",
		RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16 = "Same as PIXELFORMAT_UNCOMPRESSED_R16G16B16",
		RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16 = "Same as PIXELFORMAT_UNCOMPRESSED_R16G16B16A16",
		RL_PIXELFORMAT_COMPRESSED_DXT1_RGB = "Same as PIXELFORMAT_COMPRESSED_DXT1_RGB",
		RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA = "Same as PIXELFORMAT_COMPRESSED_DXT1_RGBA",
		RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA = "Same as PIXELFORMAT_COMPRESSED_DXT3_RGBA",
		RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA = "Same as PIXELFORMAT_COMPRESSED_DXT5_RGBA",
		RL_PIXELFORMAT_COMPRESSED_ETC1_RGB = "Same as PIXELFORMAT_COMPRESSED_ETC1_RGB",
		RL_PIXELFORMAT_COMPRESSED_ETC2_RGB = "Same as PIXELFORMAT_COMPRESSED_ETC2_RGB",
		RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA = "Same as PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA",
		RL_PIXELFORMAT_COMPRESSED_PVRT_RGB = "Same as PIXELFORMAT_COMPRESSED_PVRT_RGB",
		RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA = "Same as PIXELFORMAT_COMPRESSED_PVRT_RGBA",
		RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA = "Same as PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA",
		RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA = "Same as PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA",
		RL_TEXTURE_FILTER_POINT = "Same as TEXTURE_FILTER_POINT",
		RL_TEXTURE_FILTER_BILINEAR = "Same as TEXTURE_FILTER_BILINEAR",
		RL_TEXTURE_FILTER_TRILINEAR = "Same as TEXTURE_FILTER_TRILINEAR",
		RL_TEXTURE_FILTER_ANISOTROPIC_4X = "Same as TEXTURE_FILTER_ANISOTROPIC_4X",
		RL_TEXTURE_FILTER_ANISOTROPIC_8X = "Same as TEXTURE_FILTER_ANISOTROPIC_8X",
		RL_TEXTURE_FILTER_ANISOTROPIC_16X = "Same as TEXTURE_FILTER_ANISOTROPIC_16X",
		RL_BLEND_ALPHA = "Same as BLEND_ALPHA",
		RL_BLEND_ADDITIVE = "Same as BLEND_ADDITIVE",
		RL_BLEND_MULTIPLIED = "Same as BLEND_MULTIPLIED",
		RL_BLEND_ADD_COLORS = "Same as BLEND_ADD_COLORS",
		RL_BLEND_SUBTRACT_COLORS = "Same as BLEND_SUBTRACT_COLORS",
		RL_BLEND_ALPHA_PREMULTIPLY = "Same as BLEND_ALPHA_PREMULTIPLY",
		RL_BLEND_CUSTOM = "Same as BLEND_CUSTOM",
		RL_BLEND_CUSTOM_SEPARATE = "Same as BLEND_CUSTOM_SEPARATE",
		RL_SHADER_LOC_VERTEX_POSITION = "Same as SHADER_LOC_VERTEX_POSITION",
		RL_SHADER_LOC_VERTEX_TEXCOORD01 = "Same as SHADER_LOC_VERTEX_TEXCOORD01",
		RL_SHADER_LOC_VERTEX_TEXCOORD02 = "Same as SHADER_LOC_VERTEX_TEXCOORD02",
		RL_SHADER_LOC_VERTEX_NORMAL = "Same as SHADER_LOC_VERTEX_NORMAL",
		RL_SHADER_LOC_VERTEX_TANGENT = "Same as SHADER_LOC_VERTEX_TANGENT",
		RL_SHADER_LOC_VERTEX_COLOR = "Same as SHADER_LOC_VERTEX_COLOR",
		RL_SHADER_LOC_MATRIX_MVP = "Same as SHADER_LOC_MATRIX_MVP",
		RL_SHADER_LOC_MATRIX_VIEW = "Same as SHADER_LOC_MATRIX_VIEW",
		RL_SHADER_LOC_MATRIX_PROJECTION = "Same as SHADER_LOC_MATRIX_PROJECTION",
		RL_SHADER_LOC_MATRIX_MODEL = "Same as SHADER_LOC_MATRIX_MODEL",
		RL_SHADER_LOC_MATRIX_NORMAL = "Same as SHADER_LOC_MATRIX_NORMAL",
		RL_SHADER_LOC_VECTOR_VIEW = "Same as SHADER_LOC_VECTOR_VIEW",
		RL_SHADER_LOC_COLOR_DIFFUSE = "Same as SHADER_LOC_COLOR_DIFFUSE",
		RL_SHADER_LOC_COLOR_SPECULAR = "Same as SHADER_LOC_COLOR_SPECULAR",
		RL_SHADER_LOC_COLOR_AMBIENT = "Same as SHADER_LOC_COLOR_AMBIENT",
		RL_SHADER_LOC_MAP_ALBEDO = "Same as SHADER_LOC_MAP_ALBEDO",
		RL_SHADER_LOC_MAP_METALNESS = "Same as SHADER_LOC_MAP_METALNESS",
		RL_SHADER_LOC_MAP_NORMAL = "Same as SHADER_LOC_MAP_NORMAL",
		RL_SHADER_LOC_MAP_ROUGHNESS = "Same as SHADER_LOC_MAP_ROUGHNESS",
		RL_SHADER_LOC_MAP_OCCLUSION = "Same as SHADER_LOC_MAP_OCCLUSION",
		RL_SHADER_LOC_MAP_EMISSION = "Same as SHADER_LOC_MAP_EMISSION",
		RL_SHADER_LOC_MAP_HEIGHT = "Same as SHADER_LOC_MAP_HEIGHT",
		RL_SHADER_LOC_MAP_CUBEMAP = "Same as SHADER_LOC_MAP_CUBEMAP",
		RL_SHADER_LOC_MAP_IRRADIANCE = "Same as SHADER_LOC_MAP_IRRADIANCE",
		RL_SHADER_LOC_MAP_PREFILTER = "Same as SHADER_LOC_MAP_PREFILTER",
		RL_SHADER_LOC_MAP_BRDF = "Same as SHADER_LOC_MAP_BRDF",
		RL_SHADER_UNIFORM_FLOAT = "Same as SHADER_UNIFORM_FLOAT",
		RL_SHADER_UNIFORM_VEC2 = "Same as SHADER_UNIFORM_VEC2",
		RL_SHADER_UNIFORM_VEC3 = "Same as SHADER_UNIFORM_VEC3",
		RL_SHADER_UNIFORM_VEC4 = "Same as SHADER_UNIFORM_VEC4",
		RL_SHADER_UNIFORM_INT = "Same as SHADER_UNIFORM_INT",
		RL_SHADER_UNIFORM_IVEC2 = "Same as SHADER_UNIFORM_IVEC2",
		RL_SHADER_UNIFORM_IVEC3 = "Same as SHADER_UNIFORM_IVEC3",
		RL_SHADER_UNIFORM_IVEC4 = "Same as SHADER_UNIFORM_IVEC4",
		RL_SHADER_UNIFORM_UINT = "Same as SHADER_UNIFORM_UINT",
		RL_SHADER_UNIFORM_UIVEC2 = "Same as SHADER_UNIFORM_UIVEC2",
		RL_SHADER_UNIFORM_UIVEC3 = "Same as SHADER_UNIFORM_UIVEC3",
		RL_SHADER_UNIFORM_UIVEC4 = "Same as SHADER_UNIFORM_UIVEC4",
		RL_SHADER_UNIFORM_SAMPLER2D = "Same as SHADER_UNIFORM_SAMPLER2D",
		RL_SHADER_ATTRIB_FLOAT = "Same as SHADER_ATTRIB_FLOAT",
		RL_SHADER_ATTRIB_VEC2 = "Same as SHADER_ATTRIB_VEC2",
		RL_SHADER_ATTRIB_VEC3 = "Same as SHADER_ATTRIB_VEC3",
		RL_SHADER_ATTRIB_VEC4 = "Same as SHADER_ATTRIB_VEC4",
	},
	info = {
		rlEnableStatePointer = "Available for GRAPHICS_API_OPENGL_11",
		rlDisableStatePointer = "Available for GRAPHICS_API_OPENGL_11",
	},
}
local raygui = {
	prefix = "RAYGUIAPI",
	file = "raygui.h",
	-- funcBlacklist = {
	-- },
	-- enumBlacklist = {},
	info = {
	},
}
local raymath = {
	prefix = "RMAPI",
	file = "raymath.h",
	funcBlacklist = {
		Vector3ToFloatV = "Can be replaced by Lua equivalent",
		MatrixToFloatV = "Can be replaced by Lua equivalent",
	},
	-- enumBlacklist = {},
	info = {
	},
}
local easings = {
	prefix = "EASEDEF",
	file = "easings.h",
	funcBlacklist = {
		EaseLinearNone = "Replaced by EaseLinear",
		EaseLinearIn = "Replaced by EaseLinear",
		EaseLinearOut = "Replaced by EaseLinear",
		EaseLinearInOut = "Replaced by EaseLinear",
	},
	-- enumBlacklist = {},
	info = {
	},
}

local filePrefix = "../include/"
local headers = {
	raylib,
	rlgl,
	raygui,
	raymath,
	easings,
}

if RL.arg[4] == "--help" then
	print( "You can get blacklisted functions with argument '--blacklist'. Give additional argument to find specific function." )
	return
end

for _, header in ipairs( headers ) do
	if RL.arg[4] == "--blacklist" then
		if RL.arg[5] == nil then
			if header.funcBlacklist then
				print( "\nFunctions blacklisted from '"..header.file.."':\n" )
				
				for func, info in pairs( header.funcBlacklist ) do
					print( func.."\t\""..info.."\"" )
				end
			end
			
			if header.enumBlacklist then
				print( "\nEnums blacklisted from '"..header.file.."':\n" )
	
				for enum, info in pairs( header.enumBlacklist ) do
					print( enum.."\t\""..info.."\"" )
				end
			end
		else
			if header.funcBlacklist then
				for func, info in pairs( header.funcBlacklist ) do
					if func:lower() == RL.arg[5]:lower() then
						print( "\nFunction '"..func.."' blacklisted from '"..header.file.."'\t\""..info.."\"\n" )
					end
				end
			end
			if header.enumBlacklist then
				for enum, info in pairs( header.enumBlacklist ) do
					if enum:lower() == RL.arg[5]:lower() then
						print( "\nEnum '"..enum.."' blacklisted from '"..header.file.."'\t\""..info.."\"\n" )
					end
				end
			end
		end
	else
		local file = io.open( filePrefix..header.file, "r" )
	
		if file ~= nil then
			local line = ""
			local functions = {}
			local enums = {}
			local pickEnums = false

			repeat
				line = file:read( "*l" )
	
				if line ~= nil then
					if line:sub( 1, #header.prefix ) == header.prefix then
						local splits = RL.TextSplit( line:sub( 1, RL.TextFindIndex( line, "(" ) ), " " )
						local func = splits[ #splits ]

						func = func:gsub( "*", "" ) -- Removes pointer signs.

						local checkBlacklist = not header.funcBlacklist or ( header.funcBlacklist and not header.funcBlacklist[ func ] )
		
						if RL[ func ] == nil and checkBlacklist then
							local output = func
		
							if header.info[ func ] ~= nil then
								output = output.."\t\""..header.info[ func ].."\""
							end
		
							table.insert( functions, output )
						end
					elseif line == "typedef enum {" then
						pickEnums = true
					elseif pickEnums then
						if line:sub( 1, 1 ) == "}" then
							pickEnums = false
						else
							local enum = line:match( "%S+" )

							if enum then
								enum = enum:gsub( "/", "" )
								enum = enum:gsub( ",", "" )

								local checkBlacklist = not header.enumBlacklist or ( header.enumBlacklist and not header.enumBlacklist[ enum ] )
		
								if 0 < #enum and RL[ enum ] == nil and checkBlacklist then
									local prefix = enum:sub( 1, 3 )

									-- Check if some of the enums are already defined without RL_ prefix.
									if prefix == "RL_" then
										if RL[ enum:sub( 4 ) ] then
											enum = string.format( "%s\t\"Most likely same as %s = %d\"", enum, enum:sub( 4 ), RL[ enum:sub( 4 ) ] )
											-- Could use this to help copy it to enumBlacklist.
											-- enum = string.format( "%s = \"Same as %s\",", enum, enum:sub( 4 ) )
										end
									end

									table.insert( enums, enum )
								end
							end
						end
					end
				end
			until line == nil

			if 0 < #functions then
				print( "\nFunctions not implemented from '"..header.file.."':" )
				
				for _, f in ipairs( functions ) do
					print( "\t"..f )
				end
			end

			if 0 < #enums then
				print( "\nEnums not implemented from '"..header.file.."':" )
				
				for _, e in ipairs( enums ) do
					print( "\t"..e )
				end
			end
		end
	end
end
