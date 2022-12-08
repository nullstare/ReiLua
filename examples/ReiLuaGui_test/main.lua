package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )
Color = require( "color" )
Gui = require( "gui" )

local container = {}
-- local circleTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/circle.png" )
local circleTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/plain-circle.png" )
local checkTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/check-mark.png" )
local borderTexture = RL_LoadTexture( RL_GetBasePath().."../resources/images/ui_border.png" )
local textInput

RL_GenTextureMipmaps( circleTexture )
RL_GenTextureMipmaps( checkTexture )
RL_SetTextureFilter( circleTexture, TEXTURE_FILTER_TRILINEAR )
RL_SetTextureFilter( checkTexture, TEXTURE_FILTER_TRILINEAR )

function initGui()
	-- local label = Gui.label:new( { text = "Dog", bounds = { 32, 32, 96, 96 }, drawBounds = true, Haling = Gui.ALING.CENTER, Valing = Gui.ALING.TOP } )
	local panel = Gui.element:new( { bounds = Rect:new( 60, 32, 128, 128 ), drawBounds = true } )

	container = Gui.container:new( {
		bounds = Rect:new( 256, 120, 128, 128 ),
		-- spacing = 14,
		-- drawScrollRect = true,
		-- HAling = Gui.ALING.RIGHT,
		-- HAling = Gui.ALING.CENTER,
		-- type = Gui.CONTAINER.HORIZONTAL,
		-- VAling = Gui.ALING.CENTER,
		-- type = Gui.CONTAINER.GRID,
		-- columns = 2,
		-- rows = 2,
		scrollable = true,
		showScrollbar = true,
	} )

	-- local container = Gui.container:new( { bounds = Rect:new( 256, 120, 128, 128 ), drawBounds = true, type = Gui.CONTAINER.HORIZONTAL } )

	-- local itemBounds = { 0, 0, container.bounds.width - container.spacing * 2, 36 }
	local itemBounds = Rect:new( 0, 0, 64, 36 )

	local dog = Gui.element:new( {
		bounds = Rect:new( 0, 0, 128, 36 ),
		onClicked = function() panel:setPosition( Vec2:new( 290, 120 ) ) end,
		onMouseOver = function( self ) self.items[1].color = RED end,
		notMouseOver = function( self ) self.items[1].color = BLACK end,
		drawBounds = true,
	} )

	dog:add( Gui.text:new( { text = "Dog", HAling = Gui.ALING.LEFT } ) )

	dog:add( Gui.texture:new( {
		bounds = dog.bounds:clone(),
		texture = borderTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		visible = true,
		nPatchInfo = { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = NPATCH_NINE_PATCH },
	} ) )

	dog:add( Gui.texture:new( { bounds = Rect:new( 0, 0, 24, 24 ), texture = circleTexture, HAling = Gui.ALING.RIGHT, color = Color:new( 150, 150, 255 ) } ) )
	dog:add( Gui.texture:new( { bounds = Rect:new( 0, 0, 24, 24 ), texture = checkTexture, HAling = Gui.ALING.RIGHT, visible = true } ) )
	-- dog:add( Gui.text:new( { text = "Cat", HAling = Gui.ALING.RIGHT } ) )
	-- dog:add( Gui.shape:new( { bounds = Rect:new( 0, 0, 128, 36 ), shape = Gui.SHAPE.RECTANGLE_ROUNDED, color = Color:new( GREEN ) } ) )

	container:add( dog )

	-- container:add( Gui.element:new( {
	-- 	text = "Cat",
	-- 	bounds = Rect:new( 0, 0, 78, 24 ),
	-- 	onClicked = function() panel:setPosition( Vec2:new( 290, 120 ) ) end,
	-- 	onMouseOver = function( self ) self.color = RED end,
	-- 	notMouseOver = function( self ) self.color = BLACK end,
	-- 	drawBounds = true,
	-- } ) )

	for i = 1, 5 do
		local element = Gui.element:new( {
			bounds = Rect:new( 0, 0, 120, 30 ),
			onClicked = function() panel:setPosition( Vec2:new( 340, 380 ) ) end,
			onMouseOver = function( self ) self.color = Color:new( DARKBLUE ) end,
			notMouseOver = function( self ) self.color = Color:new( LIGHTGRAY ) end,
			drawBounds = true,
		} )

		element:add( Gui.text:new( { text = "Giraffe" } ) )
		container:add( element )
	end

	local container2 = Gui.container:new( {
		bounds = Rect:new( 0, 0, 154, 64 ),
		type = Gui.CONTAINER.HORIZONTAL,
	} )

	local element = Gui.element:new( {
		bounds = itemBounds:clone(),
		onMouseOver = function( self ) self.color = Color:new( DARKBLUE ) end,
		notMouseOver = function( self ) self.color = Color:new( LIGHTGRAY ) end,
		drawBounds = true,
	} )
	element:add( Gui.text:new( { text = "Dog" } ) )
	container2:add( element )
	
	element = Gui.element:new( {
		bounds = Rect:new( 0, 0, 78, 24 ),
		-- bounds = Rect:new( 0, 0, 78, 64 ),
		onMouseOver = function( self ) self.color = Color:new( DARKBLUE ) end,
		notMouseOver = function( self ) self.color = Color:new( LIGHTGRAY ) end,
		drawBounds = true,
	} )
	element:add( Gui.text:new( { text = "Cat" } ) )
	container2:add( element )

	container:add( container2 )

	panel:set2Top()

	-- Text input.

	textInput = Gui.element:new( {
		bounds = Rect:new( 64, 360, 300, 32 ),
		drawBounds = true,
		color = Color:new( LIGHTGRAY ),
		onClicked = function() Gui.setInputFocus( textInput ) end,
		inputFocus = function() textInput.color = Color:new( BLUE ) end,
		-- inputFocus = function() container:delete() end,
		-- inputFocus = function() panel:set2Back() end,
		inputUnfocus = function() textInput.color = Color:new( LIGHTGRAY ) end,
	} )

	textInput:add( Gui.text:new( { text = "", maxTextLen = 16, allowLineBreak = false } ) )
end

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	winSize = RL_GetWindowSize()

	RL_SetWindowTitle( "ReiLuaGui Test" )
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
	RL_DrawText( 0, "Work in progress GuiLib test.", { 10, 10 }, 30, 4, BLACK )
end
