local text = ""
local textPos = { 100, 100 }
local cursorIn = 0

function RL.init()
	RL.SetWindowTitle( "Events" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
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

function RL.event( event )
	text = "Event: "..getEventType( event ).."\n"

	if event.type == RL.GLFW_WINDOW_SIZE_EVENT then
		text = text.."width: "..event.width.." height: "..event.height
	elseif event.type == RL.GLFW_WINDOW_MAXIMIZE_EVENT then
		text = text.."maximized: "..event.maximized
	elseif event.type == RL.GLFW_WINDOW_ICONYFY_EVENT then
		text = text.."iconified: "..event.iconified
	elseif event.type == RL.GLFW_WINDOW_FOCUS_EVENT then
		text = text.."focused: "..event.focused
	elseif event.type == RL.GLFW_WINDOW_DROP_EVENT then
		text = text.."count: "..event.count.."\n"
		for _, path in ipairs( event.paths ) do
			text = text..path.."\n"
		end
	elseif event.type == RL.GLFW_KEY_EVENT then
		text = text.."key: "..event.key.." scancode: "..event.scancode.." action: "..getAction( event.action ).." mods: "..event.mods
		text = text .."\nkeyName: "..keyName( event.key )
	elseif event.type == RL.GLFW_CHAR_EVENT then
		text = text.."key: "..event.key
		-- text = text .."\nchar: "..string.char( event.key )
		text = text .."\nchar: "..utf8.char( event.key )
	elseif event.type == RL.GLFW_MOUSE_BUTTON_EVENT then
		text = text.."button: "..event.button.." action: "..getAction( event.action ).." mods: "..event.mods
	elseif event.type == RL.GLFW_MOUSE_CURSOR_POS_EVENT then
		text = text.."x: "..event.x.." y: "..event.y
	elseif event.type == RL.GLFW_MOUSE_SCROLL_EVENT then
		text = text.."xoffset: "..event.xoffset.." yoffset: "..event.yoffset
	elseif event.type == RL.GLFW_CURSOR_ENTER_EVENT then
		text = text.."enter: "..event.enter
		cursorIn = event.enter
	elseif event.type == RL.EVENT_JOYSTICK then
		text = text.."jid: "..event.jid.." event: "..event.event
		if event.event == RL.GLFW_CONNECTED then
			text = text.."\nConnected"
		elseif event.event == RL.GLFW_DISCONNECTED then
			text = text.."\nDisconnected"
		end
	elseif event.type == RL.SDL_KEYBOARD_EVENT then
		text = text.."state: "..event.state
	end
end

function RL.draw()
	if 0 < cursorIn then
		RL.ClearBackground( RL.RAYWHITE )
	else
		RL.ClearBackground( RL.RED )
	end

    RL.DrawText( text, textPos, 20, RL.BLACK )
end
