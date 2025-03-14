local text = ""
local textPos = { 100, 100 }
local cursorIn = 0

function RL.init()
	RL.SetWindowTitle( "Events" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	RL.SetTextLineSpacing( 24 )

	-- RL.EnableEventWaiting()
	-- RL.DisableEventWaiting()
end

local function getEventType( event )
	if event.type == RL.GLFW_WINDOW_SIZE_EVENT then
		return "Window Size"
	elseif event.type == RL.GLFW_WINDOW_MAXIMIZE_EVENT then
		return "Window Maximized"
	elseif event.type == RL.GLFW_WINDOW_ICONYFY_EVENT then
		return "Window Iconyfy"
	elseif event.type == RL.GLFW_WINDOW_FOCUS_EVENT then
		return "Window Focus"
	elseif event.type == RL.GLFW_WINDOW_DROP_EVENT then
		return "Window Drop"
	elseif event.type == RL.GLFW_KEY_EVENT then
		return "Key"
	elseif event.type == RL.GLFW_CHAR_EVENT then
		return "Char"
	elseif event.type == RL.GLFW_MOUSE_BUTTON_EVENT then
		return "Mouse Button"
	elseif event.type == RL.GLFW_MOUSE_CURSOR_POS_EVENT then
		return "Mouse Cursor Position"
	elseif event.type == RL.GLFW_MOUSE_SCROLL_EVENT then
		return "Mouse Scroll"
	elseif event.type == RL.GLFW_CURSOR_ENTER_EVENT then
		return "Cursor Enter"
	elseif event.type == RL.EVENT_JOYSTICK then
		return "Joystick"
	elseif event.type == RL.SDL_KEYBOARD_EVENT then
		return "SDL_KEYBOARD_EVENT"
	end

	return "Unknown"
end

local function getAction( action )
	if action == RL.GLFW_RELEASE then
		return "Release"
	elseif action == RL.GLFW_PRESS then
		return "Press"
	elseif action == RL.GLFW_REPEAT then
		return "Repeat"
	end

	return "Unknown"
end

local function keyName( key )
	for item, value in pairs( RL ) do
		if value == key and string.match( item, "KEY_", 0 ) ~= nil and item ~= "KEY_MENU" then
			return string.sub( item, 5 )
		end
	end
	
	return "Unknown"
end

local mousePos = { 0, 0 }
local cursorMode = 1

local pen = {
	state = RL.SDL_EVENT_PEN_UP,
	pos = { 0, 0 },
	pressure = 0,
	down = false,
	eraser = false,
}

function RL.event( event )
	-- text = "Event: "..getEventType( event ).."\n"

	-- if event.type == RL.GLFW_WINDOW_SIZE_EVENT then
	-- 	text = text.."width: "..event.width.." height: "..event.height
	-- elseif event.type == RL.GLFW_WINDOW_MAXIMIZE_EVENT then
	-- 	text = text.."maximized: "..event.maximized
	-- elseif event.type == RL.GLFW_WINDOW_ICONYFY_EVENT then
	-- 	text = text.."iconified: "..event.iconified
	-- elseif event.type == RL.GLFW_WINDOW_FOCUS_EVENT then
	-- 	text = text.."focused: "..event.focused
	-- elseif event.type == RL.GLFW_WINDOW_DROP_EVENT then
	-- 	text = text.."count: "..event.count.."\n"
	-- 	for _, path in ipairs( event.paths ) do
	-- 		text = text..path.."\n"
	-- 	end
	-- elseif event.type == RL.GLFW_KEY_EVENT then
	-- 	text = text.."key: "..event.key.." scancode: "..event.scancode.." action: "..getAction( event.action ).." mods: "..event.mods
	-- 	text = text .."\nkeyName: "..keyName( event.key )
	-- elseif event.type == RL.GLFW_CHAR_EVENT then
	-- 	text = text.."key: "..event.key
	-- 	-- text = text .."\nchar: "..string.char( event.key )
	-- 	text = text .."\nchar: "..utf8.char( event.key )
	-- elseif event.type == RL.GLFW_MOUSE_BUTTON_EVENT then
	-- 	text = text.."button: "..event.button.." action: "..getAction( event.action ).." mods: "..event.mods
	-- elseif event.type == RL.GLFW_MOUSE_CURSOR_POS_EVENT then
	-- 	text = text.."x: "..event.x.." y: "..event.y
	-- elseif event.type == RL.GLFW_MOUSE_SCROLL_EVENT then
	-- 	text = text.."xoffset: "..event.xoffset.." yoffset: "..event.yoffset
	-- elseif event.type == RL.GLFW_CURSOR_ENTER_EVENT then
	-- 	text = text.."enter: "..event.enter
	-- 	cursorIn = event.enter
	-- elseif event.type == RL.EVENT_JOYSTICK then
	-- 	text = text.."jid: "..event.jid.." event: "..event.event
	-- 	if event.event == RL.GLFW_CONNECTED then
	-- 		text = text.."\nConnected"
	-- 	elseif event.event == RL.GLFW_DISCONNECTED then
	-- 		text = text.."\nDisconnected"
	-- 	end
	-- end

	-- Some SDL events.

	-- text = event.type.."\n\n"

	-- if event.type == RL.SDL_KEYDOWN or event.type == RL.SDL_KEYUP then
	-- 	text = text.."state: "..event.state.." repeat: "..event.repeating
	-- elseif event.type == RL.SDL_WINDOWEVENT then
	-- 	text = text.."event: "..event.event.." "..event.data1.." "..event.data2
	-- elseif event.type == RL.SDL_MOUSEMOTION then
	-- 	text = text.."Pos: "..event.x..", "..event.y
	-- elseif event.type == RL.SDL_MOUSEBUTTONDOWN or event.type == RL.SDL_MOUSEBUTTONUP then
	-- 	text = text.."button "..event.button.." Pos: "..event.x..", "..event.y
	-- elseif event.type == RL.SDL_MOUSEWHEEL then
	-- 	text = text.."which "..event.which.." Scroll: "..event.x..", "..event.y
	-- -- elseif event.type == RL.SDL_CONTROLLERAXISMOTION then
	-- elseif event.type == RL.SDL_JOYAXISMOTION then
	-- 	text = text.."which "..event.which.." Axis: "..event.axis.." Value: "..event.value
	-- -- elseif event.type == RL.SDL_CONTROLLERBUTTONDOWN or event.type == RL.SDL_CONTROLLERBUTTONUP then
	-- elseif event.type == RL.SDL_JOYBUTTONDOWN or event.type == RL.SDL_JOYBUTTONUP then
	-- 	text = text.."which "..event.which.." Button: "..event.button.." State: "..event.state
	-- end

	-- Experimental GLFW pen tablet events.

	-- if event.type == RL.GLFW_MOUSE_CURSOR_POS_EVENT then
	-- 	mousePos = { event.x, event.y }
	-- elseif event.type == RL.GLFW_PEN_TABLET_DATA_EVENT then
	-- 	text = "x: "..event.x.." y: "..event.y.." pressure: "..event.pressure
	-- 	text = text.."\nMouse Pos: "..mousePos[1]..", "..mousePos[2]
		
	-- 	if cursorMode == 1 then
	-- 		text = text.."\nMode: Pen"
	-- 	elseif cursorMode == 2 then
	-- 		text = text.."\nMode: Eraser"
	-- 	end
	-- elseif event.type == RL.GLFW_PEN_TABLET_CURSOR_EVENT then
	-- 	cursorMode = event.identifier
	-- elseif event.type == RL.GLFW_PEN_TABLET_PROXIMITY_EVENT then
	-- 	print( event.state )
	-- end

	-- Some SDL3 events.

	text = event.type.."\n\n"

	if event.type == RL.SDL_EVENT_KEY_DOWN or event.type == RL.SDL_EVENT_KEY_UP then
		text = text.."key: "..event.key.." repeat: "..tostring( event.repeating )
	elseif event.type == RL.SDL_EVENT_PEN_AXIS then
		text = text.."pen_state: "..event.pen_state.." axis: "..event.axis.." value: "..event.value
		pen.pressure = event.value
		pen.state = event.pen_state
		pen.pos[1] = event.x
		pen.pos[2] = event.y
	elseif event.type == RL.SDL_EVENT_PEN_MOTION then
		text = text.."pen_state: "..event.pen_state.." pos: "..event.x..", "..event.y
		pen.pos[1] = event.x
		pen.pos[2] = event.y
	elseif event.type == RL.SDL_EVENT_PEN_DOWN or event.type == RL.SDL_EVENT_PEN_UP then
		pen.down = event.down
		pen.eraser = event.eraser
	elseif event.type == RL.SDL_EVENT_CLIPBOARD_UPDATE then
		print( "SDL_EVENT_CLIPBOARD_UPDATE:" )
		for i, t in ipairs( event.mime_types ) do
			print( i, t )
		end
	elseif event.type == RL.SDL_EVENT_GAMEPAD_AXIS_MOTION then
		text = text.."axis: "..event.axis.."value: "..event.value
		print( "axis: "..event.axis.." value: "..event.value )
	elseif event.type == RL.SDL_EVENT_GAMEPAD_ADDED then
		print( "SDL_EVENT_GAMEPAD_ADDED" )
	end
end

local function drawSDL3PenCircle()
	RL.DrawCircleLines( pen.pos, 32, RL.GREEN )

	if pen.down then
		RL.DrawCircle( pen.pos, pen.pressure * 32, pen.eraser and RL.YELLOW or RL.BLUE )
	end
end

function RL.draw()
	if 0 < cursorIn then
		RL.ClearBackground( RL.RAYWHITE )
	else
		RL.ClearBackground( RL.RED )
	end

	drawSDL3PenCircle()

    RL.DrawText( text, textPos, 20, RL.BLACK )
end
