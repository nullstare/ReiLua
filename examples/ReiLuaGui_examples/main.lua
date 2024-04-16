package.path = package.path..";"..RL.GetBasePath().."?.lua"
package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )
Color = require( "color" )
Gui = require( "gui" )

Calculator = require( "calculator" )
FileExplorer = require( "file_explorer" )

-- Textures.

-- Note that textures are global.
CancelTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/cancel.png" )
BackTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/previous-button.png" )
FolderTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/open-folder.png" )
FilesTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/files.png" )
BorderTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/ui_border.png" )
BgrTexture = RL.LoadTexture( RL.GetBasePath().."../resources/images/ui_bgr.png" )

RL.GenTextureMipmaps( CancelTexture )
RL.GenTextureMipmaps( BackTexture )
RL.GenTextureMipmaps( FolderTexture )
RL.GenTextureMipmaps( FilesTexture )
RL.GenTextureMipmaps( BorderTexture )
RL.GenTextureMipmaps( BgrTexture )

RL.SetTextureFilter( CancelTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( BackTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( FolderTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( FilesTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( BorderTexture, RL.TEXTURE_FILTER_TRILINEAR )
RL.SetTextureFilter( BgrTexture, RL.TEXTURE_FILTER_TRILINEAR )

RL.SetTextureWrap( BorderTexture, RL.TEXTURE_WRAP_REPEAT )
RL.SetTextureWrap( BgrTexture, RL.TEXTURE_WRAP_REPEAT )

-- End of calculator definition.

local calculator = nil
local fileExplorer = nil
local showButton = nil

local function initGui()
	showButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, 96, 32 ),
		drawBounds = true,
		onClicked = function()
			calculator:setVisible( true )
			fileExplorer:setVisible( true )
		end,
		onMouseOver = function( self ) self.color = Color:newT( RL.LIGHTGRAY ) end,
		notMouseOver = function( self ) self.color = Color:newT( RL.GRAY ) end,
	} )

	showButton:add( Gui.text:new( { text = "Show", VAling = Gui.ALING.CENTER, HAling = Gui.ALING.CENTER } ) )

	calculator = Calculator:new( Vec2:new( 32, 96 ) )
	fileExplorer = FileExplorer:new( Vec2:new( 280, 96 ) )
end

function RL.init()
	local monitor = 0
	local mPos = RL.GetMonitorPosition( monitor )
	local mSize = RL.GetMonitorSize( monitor )
	local winSize = RL.GetScreenSize()

	RL.SetWindowTitle( "ReiLuaGui examples" )
	RL.SetWindowState( RL.FLAG_WINDOW_RESIZABLE )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )
	RL.SetWindowSize( winSize )
	RL.SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	initGui()
end

function RL.update( delta )
	Gui.update( Vec2:newT( RL.GetMousePosition() ) )
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	Gui.draw()
end
