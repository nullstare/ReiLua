local text = ""
local textPos = { 100, 100 }
local cursorIn = 0

function RL.init()
	RL.SetWindowTitle( "Events" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
end

local function getEventType( event )
	if event.type == RL.EVENT_WINDOW_SIZE then
		return "Window Size"
	elseif event.type == RL.EVENT_WINDOW_MAXIMIZE then
		return "Window Maximized"
	elseif event.type == RL.EVENT_WINDOW_ICONYFY then
		return "Window Iconyfy"
	elseif event.type == RL.EVENT_WINDOW_FOCUS then
		return "Window Focus"
	elseif event.type == RL.EVENT_WINDOW_DROP then
		return "Window Drop"
	elseif event.type == RL.EVENT_KEY then
		return "Key"
	elseif event.type == RL.EVENT_CHAR then
		return "Char"
	elseif event.type == RL.EVENT_MOUSE_BUTTON then
		return "Mouse Button"
	elseif event.type == RL.EVENT_MOUSE_CURSOR_POS then
		return "Mouse Cursor Position"
	elseif event.type == RL.EVENT_MOUSE_SCROLL then
		return "Mouse Scroll"
	elseif event.type == RL.EVENT_CURSOR_ENTER then
		return "Cursor Enter"
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

	if event.type == RL.EVENT_WINDOW_SIZE then
		text = text.."width: "..event.width.." height: "..event.height
	elseif event.type == RL.EVENT_WINDOW_MAXIMIZE then
		text = text.."maximized: "..event.maximized
	elseif event.type == RL.EVENT_WINDOW_ICONYFY then
		text = text.."iconified: "..event.iconified
	elseif event.type == RL.EVENT_WINDOW_FOCUS then
		text = text.."focused: "..event.focused
	elseif event.type == RL.EVENT_WINDOW_DROP then
		text = text.."count: "..event.count.."\n"
		for _, path in ipairs( event.paths ) do
			text = text..path.."\n"
		end
	elseif event.type == RL.EVENT_KEY then
		text = text.."key: "..event.key.." scancode: "..event.scancode.." action: "..getAction( event.action ).." mods: "..event.mods
		text = text .."\nkeyName: "..keyName( event.key )
	elseif event.type == RL.EVENT_CHAR then
		text = text.."key: "..event.key
		-- text = text .."\nchar: "..string.char( event.key )
		text = text .."\nchar: "..utf8.char( event.key )
	elseif event.type == RL.EVENT_MOUSE_BUTTON then
		text = text.."button: "..event.button.." action: "..getAction( event.action ).." mods: "..event.mods
	elseif event.type == RL.EVENT_MOUSE_CURSOR_POS then
		text = text.."x: "..event.x.." y: "..event.y
	elseif event.type == RL.EVENT_MOUSE_SCROLL then
		text = text.."xoffset: "..event.xoffset.." yoffset: "..event.yoffset
	elseif event.type == RL.EVENT_CURSOR_ENTER then
		text = text.."enter: "..event.enter
		cursorIn = event.enter
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
