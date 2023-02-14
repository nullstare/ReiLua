package.path = package.path..";"..RL_GetBasePath().."?.lua"
package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )
Color = require( "color" )
Gui = require( "gui" )

Calculator = require( "calculator" )
FileExplorer = require( "file_explorer" )

-- Textures.

-- Note that textures are global.
cancelTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/cancel.png" )
backTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/previous-button.png" )
folderTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/open-folder.png" )
filesTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/files.png" )
borderTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/ui_border.png" )
bgrTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/ui_bgr.png" )

RL_GenTextureMipmaps( cancelTexture )
RL_GenTextureMipmaps( backTexture )
RL_GenTextureMipmaps( folderTexture )
RL_GenTextureMipmaps( filesTexture )
RL_GenTextureMipmaps( borderTexture )
RL_GenTextureMipmaps( bgrTexture )

RL_SetTextureFilter( cancelTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( backTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( folderTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( filesTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( borderTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( bgrTexture, TEXTURE_FILTER_TRILINEAR )

RL_SetTextureWrap( borderTexture, TEXTURE_WRAP_REPEAT )
RL_SetTextureWrap( bgrTexture, TEXTURE_WRAP_REPEAT )

-- End of calculator definition.

local calculator = nil
local fileExplorer = nil
local showButton = nil

function initGui()
	showButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, 96, 32 ),
		drawBounds = true,
		onClicked = function()
			calculator:setVisible( true )
			fileExplorer:setVisible( true )
		end,
		onMouseOver = function( self ) self.color = Color:new( LIGHTGRAY ) end,
		notMouseOver = function( self ) self.color = Color:new( GRAY ) end,
	} )

	showButton:add( Gui.text:new( { text = "Show", VAling = Gui.ALING.CENTER, HAling = Gui.ALING.CENTER } ) )

	calculator = Calculator:new( Vec2:new( 32, 96 ) )
	fileExplorer = FileExplorer:new( Vec2:new( 280, 96 ) )
end

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	winSize = RL_GetScreenSize()

	RL_SetWindowTitle( "ReiLuaGui examples" )
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	initGui()
end

function process( delta )
	Gui.process( Vec2:new( RL_GetMousePosition() ) )
end

function draw()
	RL_ClearBackground( RAYWHITE )

	Gui.draw()
end
