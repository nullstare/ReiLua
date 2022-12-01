package.path = package.path..";"..RL_GetBasePath().."../resources/lib/?.lua"

util = require( "utillib" )
Vec2 = require( "vector2" )
Rect = require( "rectangle" )
Gui = require( "gui" )

local textColor = BLACK
local textPos = { 192, 200 }
local imageFont = -1

local container = {}

function initGui()
	-- local label = Gui.label:new( { text = "Dog", bounds = { 32, 32, 96, 96 }, drawBounds = true, Haling = Gui.ALING.CENTER, Valing = Gui.ALING.TOP } )
	local panel = Gui.panel:new( { bounds = Rect:new( 60, 32, 128, 128 ) } )
	container = Gui.container:new( {
		bounds = Rect:new( 256, 120, 128, 128 ),
		drawBounds = true,
		-- Haling = Gui.ALING.LEFT,
		-- Haling = Gui.ALING.CENTER,
		-- Valing = Gui.ALING.CENTER,
		-- type = Gui.CONTAINER.HORIZONTAL,
		-- scrollPos = Vec2:new( 0, 0 ),
		scrollable = true,
	} )

	-- local container = Gui.container:new( { bounds = Rect:new( 256, 120, 128, 128 ), drawBounds = true, type = Gui.CONTAINER.HORIZONTAL } )

	-- local itemBounds = { 0, 0, container.bounds.width - container.spacing * 2, 36 }
	local itemBounds = Rect:new( 0, 0, 64, 36 )

	container:add( Gui.label:new( {
		text = "Dog",
		bounds = itemBounds:clone(),
		onClicked = function() panel:setPosition( Vec2:new( 500, 80 ) ) end,
		onMouseOver = function( self ) self.color = RED end,
		notMouseOver = function( self ) self.color = BLACK end,
		drawBounds = true,
	} ) )

	container:add( Gui.label:new( {
		text = "Cat",
		-- bounds = itemBounds:clone(),
		bounds = Rect:new( 0, 0, 78, 24 ),
		onClicked = function() panel:setPosition( Vec2:new( 290, 120 ) ) end,
		onMouseOver = function( self ) self.color = RED end,
		notMouseOver = function( self ) self.color = BLACK end,
		drawBounds = true,
	} ) )

	for i = 1, 5 do
		container:add( Gui.label:new( {
			text = "Giraffe",
			bounds = Rect:new( 0, 0, 100, 30 ),
			onClicked = function() panel:setPosition( Vec2:new( 340, 380 ) ) end,
			onMouseOver = function( self ) self.color = RED end,
			notMouseOver = function( self ) self.color = BLACK end,
			drawBounds = true,
		} ) )
	end

	local container2 = Gui.container:new( {
		bounds = Rect:new( 400, 120, 154, 30 ),
		drawBounds = true,
		-- Haling = Gui.ALING.LEFT,
		-- Haling = Gui.ALING.CENTER,
		-- Valing = Gui.ALING.CENTER,
		type = Gui.CONTAINER.HORIZONTAL,
	} )

	container2:add( Gui.label:new( {
		text = "Dog",
		bounds = itemBounds:clone(),
		-- onClicked = function() panel:setPosition( Vec2:new( 500, 80 ) ) end,
		onMouseOver = function( self ) self.color = RED end,
		notMouseOver = function( self ) self.color = BLACK end,
		drawBounds = true,
	} ) )

	container2:add( Gui.label:new( {
		text = "Cat",
		-- bounds = itemBounds:clone(),
		bounds = Rect:new( 0, 0, 78, 24 ),
		-- onClicked = function() panel:setPosition( Vec2:new( 290, 120 ) ) end,
		onMouseOver = function( self ) self.color = RED end,
		notMouseOver = function( self ) self.color = BLACK end,
		drawBounds = true,
	} ) )

	container:add( container2 )

	panel:set2Top()
end

function init()
	local monitor = 0
	local mPos = RL_GetMonitorPosition( monitor )
	local mSize = RL_GetMonitorSize( monitor )
	winSize = RL_GetWindowSize()
	-- local winSize = { 1920, 1080 }

	RL_SetWindowTitle( "ReiLua Gui" )
	RL_SetWindowState( FLAG_WINDOW_RESIZABLE )
	RL_SetWindowState( FLAG_VSYNC_HINT )
	RL_SetWindowSize( winSize )
	RL_SetWindowPosition( { mPos[1] + mSize[1] / 2 - winSize[1] / 2, mPos[2] + mSize[2] / 2 - winSize[2] / 2 } )

	initGui()
end

function process( delta )
	if RL_IsKeyDown( KEY_RIGHT ) then
		container:scroll( Vec2:new( container._scrollRect.x + 50 * delta, 0 ) )
	elseif RL_IsKeyDown( KEY_LEFT ) then
		container:scroll( Vec2:new( container._scrollRect.x - 50 * delta, 0 ) )
	elseif RL_IsKeyDown( KEY_UP ) then
		container:scroll( Vec2:new( 0, container._scrollRect.y - 50 * delta ) )
	elseif RL_IsKeyDown( KEY_DOWN ) then
		container:scroll( Vec2:new( 0, container._scrollRect.y + 50 * delta ) )
	end

	Gui.process( RL_GetMousePosition() )
end

function draw()
	RL_ClearBackground( RAYWHITE )

	Gui.draw()
end
