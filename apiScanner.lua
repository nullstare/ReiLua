local raylib = {
	prefix = "RLAPI",
	file = "raylib.h",
	blacklist = {
		InitWindow = true, -- Handled internally.
		WindowShouldClose = true, -- Handled internally.
		GetScreenWidth = true, -- Replaced by GetScreenSize.
		GetScreenHeight = true, -- Replaced by GetScreenSize.
		GetRenderWidth = true, -- Replaced by GetRenderSize.
		GetRenderHeight = true, -- Replaced by GetRenderSize.
		GetMonitorWidth = true, -- Replaced by GetMonitorSize.
		GetMonitorHeight = true, -- Replaced by GetMonitorSize.
		GetMonitorPhysicalWidth = true, -- Replaced by GetMonitorPhysicalSize.
		GetMonitorPhysicalHeight = true, -- Replaced by GetMonitorPhysicalSize.
		UnloadRandomSequence = true, -- Handled internally.
		MemAlloc = true, -- Buffer should be used instead.
		MemRealloc = true, -- Buffer should be used instead.
		MemFree = true, -- Buffer should be used instead.
		SetTraceLogCallback = true, -- Handled internally.
		SetLoadFileDataCallback = true, -- Not seen necessary.
		SetSaveFileDataCallback = true, -- Not seen necessary.
		SetLoadFileTextCallback = true, -- Not seen necessary.
		SetSaveFileTextCallback = true, -- Not seen necessary.
		UnloadFileData = true, -- Handled internally.
		UnloadFileText = true, -- Handled internally.
		UnloadDirectoryFiles = true, -- Handled internally.
		UnloadDroppedFiles = true, -- Handled internally.
		GetMouseX = true, -- Replaced by GetMousePosition.
		GetMouseY = true, -- Replaced by GetMousePosition.
		GetTouchX = true, -- Replaced by GetTouchPosition.
		GetTouchY = true, -- Replaced by GetTouchPosition.
		UpdateCamera = true, -- Replaced by UpdateCamera3D.
		UpdateCameraPro = true, -- Replaced by UpdateCameraPro3D.
		DrawPixelV = true, -- Replaced by DrawPixel.
		DrawLineV = true, -- Replaced by DrawLine.
		DrawCircleV = true, -- Replaced by DrawCircle.
		DrawCircleLinesV = true, -- Replaced by DrawCircleLines.
		DrawRectangleV = true, -- Replaced by DrawRectangle.
		DrawRectangleRec = true, -- Replaced by DrawRectangle.
		ImageTextEx = true, -- Replaced by ImageText.
		UnloadImageColors = true, -- Handled internally.
		UnloadImagePalette = true, -- Handled internally.
		ImageDrawPixelV = true, -- Replaced by ImageDrawPixel.
		ImageDrawLineV = true, -- Replaced by ImageDrawLine.
		ImageDrawCircleV = true, -- Replaced by ImageDrawCircle.
		ImageDrawCircleLinesV = true, -- Replaced by ImageDrawCircleLines.
		ImageDrawRectangleV = true, -- Replaced by ImageDrawRectangle.
		ImageDrawRectangleRec = true, -- Replaced by ImageDrawRectangle.
		DrawTextureV = true, -- Replaced by DrawTexture.
		UnloadFontData = true, -- Handled internally.
		MeasureTextEx = true, -- Replaced by MeasureText.
		UnloadUTF8 = true, -- Handled internally.
		UnloadCodepoints = true, -- Handled internally.
		TextCopy = true, -- Can be replaced by Lua equivalent.
		TextIsEqual = true, -- Can be replaced by Lua equivalent.
		TextLength = true, -- Can be replaced by Lua equivalent.
		TextSubtext = true, -- Can be replaced by Lua equivalent.
		TextJoin = true, -- Can be replaced by Lua equivalent.
		TextAppend = true, -- Can be replaced by Lua equivalent.
		TextToUpper = true, -- Can be replaced by Lua equivalent.
		TextToLower = true, -- Can be replaced by Lua equivalent.
		TextToInteger = true, -- Can be replaced by Lua equivalent.
		DrawCubeV = true, -- Replaced by DrawCube.
		DrawCubeWiresV = true, -- Replaced by DrawCubeWires.
		UploadMesh = true, -- Handled internally.
		UpdateMeshBuffer = true, -- Handled internally.
		UnloadWaveSamples = true, -- Handled internally.
	},
	info = {
		IsKeyPressedRepeat = "Will be added",
		IsGamepadButtonUp = "Will be added",
		GetGamepadButtonPressed = "Will be added",
		GetMouseWheelMoveV = "Will be added",
		DrawLineEx = "Will be added",
		ImageDrawText = "Could be added",
		DrawTextureEx = "Will be added",
		DrawTriangleStrip3D = "Will be added",
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
		rlVertex2i = true, -- Most likely not needed.
		rlglInit = true, -- Handled internally.
		rlglClose = true, -- Handled internally.
		rlLoadExtensions = true, -- Handled internally.
		rlLoadDrawCube = true, -- Most likely not needed.
		rlLoadDrawQuad = true, -- Most likely not needed.
	},
	info = {
		rlBlitFramebuffer = "Will be added",
		rlEnablePointMode = "Will be added",
		rlEnableStatePointer = "Should probably be added for GRAPHICS_API_OPENGL_11",
		rlDisableStatePointer = "Should probably be added for GRAPHICS_API_OPENGL_11",
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
		Vector3ToFloatV = true, -- Can be replaced by Lua equivalent.
		MatrixToFloatV = true, -- Can be replaced by Lua equivalent.
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
	},
	info = {
		EaseLinearNone = "Will be added",
		EaseLinearIn = "Will be added",
		EaseLinearOut = "Will be added",
		EaseLinearInOut = "Will be added",
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

for _, header in ipairs( headers ) do
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
