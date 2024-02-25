local raylib = {
	prefix = "RLAPI",
	file = "raylib.h",
	blacklist = {
		InitWindow = "Handled internally",
		WindowShouldClose = "Handled internally",
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
		DrawCubeV = "Replaced by DrawCube",
		DrawCubeWiresV = "Replaced by DrawCubeWires",
		UploadMesh = "Handled internally",
		UpdateMeshBuffer = "Handled internally",
		UnloadWaveSamples = "Handled internally",
		GetPixelColor = "Not seen necessary",
		SetPixelColor = "Not seen necessary",
	},
	info = {
		GenMeshHemiSphere = "Will be added",
		GenMeshCubicmap = "Will be added",
		UpdateSound = "Will be added",
		LoadWaveSamples = "Will be added",
	}
}
local rlgl = {
	prefix = "RLAPI",
	file = "rlgl.h",
	blacklist = {
		rlVertex2i = "Most likely not needed",
		rlglInit = "Handled internally",
		rlglClose = "Handled internally",
		rlLoadExtensions = "Handled internally",
		rlLoadDrawCube = "Most likely not needed",
		rlLoadDrawQuad = "Most likely not needed",
	},
	info = {
		rlEnableStatePointer = "Available for GRAPHICS_API_OPENGL_11",
		rlDisableStatePointer = "Available for GRAPHICS_API_OPENGL_11",
	},
}
local raygui = {
	prefix = "RAYGUIAPI",
	file = "raygui.h",
	blacklist = {
	},
	info = {
	},
}
local raymath = {
	prefix = "RMAPI",
	file = "raymath.h",
	blacklist = {
		Vector3ToFloatV = "Can be replaced by Lua equivalent",
		MatrixToFloatV = "Can be replaced by Lua equivalent",
	},
	info = {
		Vector3Project = "Will be added",
		Vector3Reject = "Will be added",
	},
}
local easings = {
	prefix = "EASEDEF",
	file = "easings.h",
	blacklist = {
		EaseLinearNone = "Replaced by EaseLinear",
		EaseLinearIn = "Replaced by EaseLinear",
		EaseLinearOut = "Replaced by EaseLinear",
		EaseLinearInOut = "Replaced by EaseLinear",
	},
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
			print( "\nFunctions blacklisted from '"..header.file.."':\n" )
	
			for func, info in pairs( header.blacklist ) do
				print( func.."\t\""..info.."\"" )
			end
		else
			for func, info in pairs( header.blacklist ) do
				if func:lower() == RL.arg[5]:lower() then
					print( "\nFunction '"..func.."' blacklisted from '"..header.file.."'\t\""..info.."\"\n" )
				end
			end
		end
	else
		local file = io.open( filePrefix..header.file, "r" )
	
		if file ~= nil then
			local line = ""
	
			print( "\nFunctions not implemented from '"..header.file.."':\n" )
	
			repeat
				line = file:read( "*l" )
	
				if line ~= nil and line:sub( 1, #header.prefix ) == header.prefix then
					local splits = RL.TextSplit( line:sub( 1, RL.TextFindIndex( line, "(" ) ), " " )
					local func = splits[ #splits ]
					func = func:gsub( "*", "" )
	
					if RL[ func ] == nil and not header.blacklist[ func ] then
						local output = func
	
						if header.info[ func ] ~= nil then
							output = output.."\t\""..header.info[ func ].."\""
						end
	
						print( output )
					end
				end
			until line == nil
		end
	end
end
