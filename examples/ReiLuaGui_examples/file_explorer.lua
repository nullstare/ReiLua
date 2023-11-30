FileExplorer = {}
FileExplorer.__index = FileExplorer

function FileExplorer:new( pos )
	pos = pos or Vec2:new( 0, 0 )

	local object = setmetatable( {}, self )

	object.HANDLE_HIGHT = 32
	object.DISPLAY_HIGHT = 40
	object.OPERATIONS = { ADD = 0, SUB = 1, MUL = 2, DIV = 3 }

	object.windowRect = Rect:new( pos.x, pos.y, 500, 330 )
	object.dragPos = Vec2:new( 0, 0 )

	-- Handle.

	object.handle = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width, object.HANDLE_HIGHT ),
		padding = 10,
		onClicked = function()
			object:set2Top()
			object.dragPos = Vec2:new( RL.GetMousePosition() ) - Vec2:new( object.handle.bounds.x, object.handle.bounds.y )
			Gui.heldCallback = function() object:drag() end
		end,
	} )

	object.handle:add( Gui.texture:new( {
		bounds = object.handle.bounds:clone(),
		texture = BgrTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( RL.LIGHTGRAY ),
	} ) )

	object.handle:add( Gui.texture:new( {
		bounds = object.handle.bounds:clone(),
		texture = BorderTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( RL.LIGHTGRAY ),
		nPatchInfo = { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = RL.NPATCH_NINE_PATCH },
	} ) )

	object.handle:add( Gui.text:new( { text = "File Explorer", fontSize = 20, VAling = Gui.ALING.CENTER } ) )

	-- Close button.

	object.closeButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.HANDLE_HIGHT, object.HANDLE_HIGHT ),
		onClicked = function()
			object:setVisible( false )
		end,
		onMouseOver = function( self ) self.items[1].color = Color:new( RL.WHITE ) end,
		notMouseOver = function( self ) self.items[1].color = Color:new( RL.BLACK ) end,
	} )

	object.closeButton:add( Gui.texture:new( {
		bounds = object.closeButton.bounds:clone(),
		texture = CancelTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
	} ) )

	-- Panel.

	object.panel = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width, object.windowRect.height - object.HANDLE_HIGHT ),
	} )

	object.panel:add( Gui.texture:new( {
		bounds = object.panel.bounds:clone(),
		texture = BgrTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( RL.GRAY ),
	} ) )

	object.panel:add( Gui.texture:new( {
		bounds = object.panel.bounds:clone(),
		texture = BorderTexture,
		HAling = Gui.ALING.CENTER,
		VAling = Gui.ALING.CENTER,
		color = Color:new( RL.LIGHTGRAY ),
		nPatchInfo = { source = { 0, 0, 24, 24 }, left = 8, top = 8, right = 8, bottom = 8, layout = RL.NPATCH_NINE_PATCH },
	} ) )

	-- Path.

	object.pathBox = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width - 16 - 64, object.HANDLE_HIGHT ),
		drawBounds = true,
		color = Color:new( RL.WHITE ),
		-- onClicked = function() Gui.setInputFocus( object.pathBox ) end,
		-- inputFocus = function() object.pathBox.color = Color:new( BLUE ) end,
		-- inputUnfocus = function() object.pathBox.color = Color:new( WHITE ) end,
	} )

	object.pathBox:add( Gui.text:new( { text = "", maxTextLen = 30, allowLineBreak = false, VAling = Gui.ALING.CENTER } ) )

	-- Back button.

	object.backButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, 56, object.HANDLE_HIGHT ),
		drawBounds = true,
		onMouseOver = function( self ) self.color = Color:new( RL.WHITE ) end,
		notMouseOver = function( self ) self.color = Color:new( RL.LIGHTGRAY ) end,
		onClicked = function() object:backDir() end,
	} )

	object.backButton:add( Gui.texture:new( {
		bounds = Rect:new( 0, 0, object.HANDLE_HIGHT, object.HANDLE_HIGHT ),
		texture = BackTexture,
		HAling = Gui.ALING.CENTER,
		color = Color:new( RL.BLACK )
	} ) )

	-- Files.

	object.files = Gui.container:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width - 24, 200 ),
		drawBounds = true,
		scrollable = true,
		showScrollbar = true,
		-- drawScrollRect = true,
	} )

	-- File name.

	object.fileName = Gui.element:new( {
		bounds = Rect:new( 0, 0, object.windowRect.width - 16 - 70, object.HANDLE_HIGHT ),
		drawBounds = true,
		color = Color:new( RL.WHITE ),
	} )

	object.fileName:add( Gui.text:new( { text = "", maxTextLen = 32, allowLineBreak = false, VAling = Gui.ALING.CENTER } ) )

	-- Open button.

	object.openButton = Gui.element:new( {
		bounds = Rect:new( 0, 0, 64, object.HANDLE_HIGHT ),
		drawBounds = true,
		color = Color:new( RL.WHITE ),
		onClicked = function() object:openFile() end,
		onMouseOver = function( self ) self.color = Color:new( RL.WHITE ) end,
		notMouseOver = function( self ) self.color = Color:new( RL.LIGHTGRAY ) end,
	} )

	object.openButton:add( Gui.text:new( { text = "Open", VAling = Gui.ALING.CENTER, HAling = Gui.ALING.CENTER } ) )

	-- Variables.

	object.path = RL.GetBasePath()

	-- Take last '/' away.
	if Util.utf8Sub( object.path, utf8.len( object.path ), utf8.len( object.path ) ) == "/" then
		object.path = Util.utf8Sub( object.path, 1, utf8.len( object.path ) - 1 )
	end
	object.file = ""

	-- Update.

	object:setPosition( Vec2:new( object.windowRect.x, object.windowRect.y ) )
	object:updatePath()

    return object
end

function FileExplorer:updatePath()
	local maxLen = self.pathBox.items[1].maxTextLen
	local pathLen = utf8.len( self.path )
	local text = ""

	if maxLen < pathLen then
		text = self.path:sub( pathLen - maxLen + 1, pathLen )
	else
		text = self.path
	end

	self.pathBox.items[1]:set( text )

	self:updateFiles()
end

function FileExplorer:changeDir( path )
	self.path = path

	self:updatePath()
end

function FileExplorer:backDir()
	self.path = RL.GetPrevDirectoryPath( self.path )

	self:updatePath()
end

function FileExplorer:fileSelect( file )
	self.file = file

	self.fileName.items[1]:set( RL.GetFileName( file ) )
end

function FileExplorer:openFile()
	print( self.file, RL.GetFileLength( self.file ) )
end

function FileExplorer:updateFiles()
	self.files:scroll( Vec2:new( 0, 0 ) )

	for _, cell in ipairs( self.files.cells ) do
		cell:delete()
	end

	self.files.cells = {}

	local files = {}
	local folders = {}

	for _, file in ipairs( RL.LoadDirectoryFiles( self.path ) ) do
		if RL.IsPathFile( file ) then
			table.insert( files, file )
		else
			table.insert( folders, file )
		end
	end

	table.sort( files, function( a, b ) return a < b end )
	table.sort( folders, function( a, b ) return a < b end )

	for _, folder in ipairs( folders ) do
		self:addFileToList( folder, FolderTexture, { 150, 120, 80 }, function() self:changeDir( folder ) end )
	end

	for _, file in ipairs( files ) do
		self:addFileToList( file, FilesTexture, RL.WHITE, function() self:fileSelect( file ) end )
	end
end

function FileExplorer:addFileToList( file, texture, color, func )
	self.files:add( Gui.element:new( {
		bounds = Rect:new( 0, 0, self.windowRect.width - 16 - 20, 20 ),
		padding = 4,
		onClicked = func,
	} ) )

	local element = self.files.cells[ #self.files.cells ]

	element:add( Gui.text:new( {
		bounds = Rect:new( 28, 0, 20, 20 ),
		text = RL.GetFileName( file ),
		fontSize = 20,
		HAling = Gui.ALING.NONE,
		VAling = Gui.ALING.CENTER,
	} ) )

	element:add( Gui.texture:new( {
		bounds = Rect:new( 0, 0, 20, 20 ),
		texture = texture,
		VAling = Gui.ALING.CENTER,
		color = Color:new( color ),
	} ) )

	element.bounds.width = element.items[1].bounds.width + element.padding + element.items[2].bounds.width
end

function FileExplorer:drag()
	local mousePos = Vec2:new( RL.GetMousePosition() )
	local winPos = Vec2:new( self.handle.bounds.x, self.handle.bounds.y )

	self:setPosition( mousePos - self.dragPos )
end

function FileExplorer:setPosition( pos )
	self.windowRect.x = pos.x
	self.windowRect.y = pos.y

	self.handle:setPosition( pos )
	self.closeButton:setPosition( Vec2:new( pos.x + self.windowRect.width - self.HANDLE_HIGHT, pos.y ) )
	self.panel:setPosition( Vec2:new( pos.x, pos.y + self.HANDLE_HIGHT ) )
	self.pathBox:setPosition( Vec2:new( pos.x + 8, pos.y + self.HANDLE_HIGHT + 8 ) )
	self.backButton:setPosition( Vec2:new( pos.x + self.pathBox.bounds.width + 16, pos.y + self.HANDLE_HIGHT + 8 ) )
	self.files:setPosition( Vec2:new( pos.x + 8, pos.y + self.HANDLE_HIGHT * 2 + 16 ) )
	self.fileName:setPosition( Vec2:new( pos.x + 8, pos.y + self.HANDLE_HIGHT * 2 + 16 + 208 ) )
	self.openButton:setPosition( Vec2:new( pos.x + 8 + 420, pos.y + self.HANDLE_HIGHT * 2 + 16 + 208 ) )
end

function FileExplorer:setVisible( visible )
	self.handle.visible = visible
	self.handle.disabled = not visible
	self.panel.visible = visible
	self.panel.disabled = not visible
	self.closeButton.visible = visible
	self.closeButton.disabled = not visible
	self.pathBox.visible = visible
	self.pathBox.disabled = not visible
	self.backButton.visible = visible
	self.backButton.disabled = not visible
	self.files.visible = visible
	self.files.disabled = not visible
	self.fileName.visible = visible
	self.fileName.disabled = not visible
	self.openButton.visible = visible
	self.openButton.disabled = not visible

	self.files:update()
end

function FileExplorer:set2Top()
	self.panel:set2Top()
	self.handle:set2Top()
	self.closeButton:set2Top()
	self.pathBox:set2Top()
	self.backButton:set2Top()
	self.files:set2Top()
	self.fileName:set2Top()
	self.openButton:set2Top()
end

return FileExplorer
