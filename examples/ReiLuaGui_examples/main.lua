package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )
Color = require( "color" )
Gui = require( "gui" )

Calculator = require( "calculator" )
FileExplorer = require( "file_explorer" )

-- Textures.

-- Note that textures are global.
cancelTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/cancel.png" )
backTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/previous-button.png" )
folderTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/open-folder.png" )
filesTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/files.png" )
borderTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/ui_border.png" )
bgrTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/ui_bgr.png" )

RL.GenTextureMipmaps( cancelTexture )
RL.GenTextureMipmaps( backTexture )
RL.GenTextureMipmaps( folderTexture )
RL.GenTextureMipmaps( filesTexture )
RL.GenTextureMipmaps( borderTexture )
RL.GenTextureMipmaps( bgrTexture )

RL.SetTextureFilter( cancelTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( backTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( folderTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( filesTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( borderTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( bgrTexture, RL.TEXTURE_FILTER_TRILINEAR )

RL.SetTextureWrap( borderTexture, RL.TEXTURE_WRAP_REPEAT )
RL.SetTextureWrap( bgrTexture, RL.TEXTURE_WRAP_REPEAT )

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
		onMouseOver = function( self ) self.color = Color:new( RL.LIGHTGRAY ) end,
		notMouseOver = function( self ) self.color = Color:new( RL.GRAY ) end,
	} )

	showButton:add( Gui.text:new( { text = "Show", VAling = Gui.ALING.CENTER, HAling = Gui.ALING.CENTER } ) )

	calculator = Calculator:new( Vec2:new( 32, 96 ) )
	fileExplorer = FileExplorer:new( Vec2:new( 280, 96 ) )
end

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	winSize = RL.GetScreenSize()

	RL.SetWindowTitle( "ReiLuaGui examples" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	initGui()
end

function RL.process( delta )
	Gui.process( Vec2:new( RL.GetMousePosition() ) )
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	Gui.draw()
end
