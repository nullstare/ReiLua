local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

FileBrowser = {}
local metatable = {
	__index = setmetatable( FileBrowser, { __index = GuiControl } ),
}

FileBrowser.DEFAULT_STYLES = {
	fileBrowser = {
		defaultRect = Rectangle:new( 0, 0, 600, 490 ),
		padding = 8,
		spacing = 4,
		iconButtonSize = Vector2:new( 28 ),
		textButtonSize = Vector2:new( 72, 28 ),
		fileButtonHeight = 24,
	},
	window = Util.deepCopy( Gui.Window.DEFAULT_STYLES ),
	pathInput = Util.deepCopy( Gui.TextInputBox.DEFAULT_STYLES ),
	searchButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	backButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	fileList = Util.deepCopy( Gui.Container.DEFAULT_STYLES ),
	fileInput = Util.deepCopy( Gui.TextInputBox.DEFAULT_STYLES ),
	filterDropdown = Util.deepCopy( Gui.Dropdown.DEFAULT_STYLES ),
	applyButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
	listFileButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
}

-- File list.

FileBrowser.DEFAULT_STYLES.fileList.container.scrollSteps = 32

-- Search button.

FileBrowser.DEFAULT_STYLES.searchButton.normal.icons = {
	{
		iconId = RL.ICON_LENS,
		offset = Vector2:new( 0, 0 ),
		pixelSize = 1,
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
		alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
	}
}
Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.searchButton, "icons", FileBrowser.DEFAULT_STYLES.searchButton.normal.icons )

-- Back button.

FileBrowser.DEFAULT_STYLES.backButton.normal.icons = {
	{
		iconId = RL.ICON_ARROW_LEFT,
		offset = Vector2:new( 0, 0 ),
		pixelSize = 1,
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
		alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
	}
}
Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.backButton, "icons", FileBrowser.DEFAULT_STYLES.backButton.normal.icons )

FileBrowser.FILE_TYPES = { "*.*", "DIRS*", "FILES*", ".png", ".lua", ".wav", ".ogg", ".txt" }
FileBrowser.FILE_ICONS = {
	DIR = RL.ICON_FOLDER,
	FILE = RL.ICON_FILE,
	[".txt"] = RL.ICON_FILETYPE_TEXT,
	[".lua"] = RL.ICON_FILETYPE_TEXT,
	[".c"] = RL.ICON_FILETYPE_TEXT,
	[".wav"] = RL.ICON_FILETYPE_AUDIO,
	[".mp3"] = RL.ICON_FILETYPE_AUDIO,
	[".ogg"] = RL.ICON_FILETYPE_AUDIO,
	[".mid"] = RL.ICON_FILETYPE_AUDIO,
	[".png"] = RL.ICON_FILETYPE_IMAGE,
	[".jpg"] = RL.ICON_FILETYPE_IMAGE,
	[".jpeg"] = RL.ICON_FILETYPE_IMAGE,
	[".avi"] = RL.ICON_FILETYPE_VIDEO,
	[".mov"] = RL.ICON_FILETYPE_VIDEO,
	[".mp4"] = RL.ICON_FILETYPE_VIDEO,
	[".exe"] = RL.ICON_GEAR_BIG,
}

-- List file button.

FileBrowser.DEFAULT_STYLES.listFileButton.normal.icons = {
	{
		iconId = FileBrowser.FILE_ICONS.FILE,
		offset = Vector2:new( 0, 0 ),
		pixelSize = 1,
		color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		-- alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
		alignH = RL.TEXT_ALIGN_LEFT,
		alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
	}
}
Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.listFileButton, "icons", FileBrowser.DEFAULT_STYLES.listFileButton.normal.icons )
Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.listFileButton, "text.alignH", RL.TEXT_ALIGN_LEFT )
Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.listFileButton, "text.offset", Vector2:new( 20, 0 ) )

function FileBrowser:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	object.bounds = t.bounds and t.bounds:clone() or object.DEFAULT_STYLES.fileBrowser.defaultRect:clone()
	object.text = t.text or "File Browser"
	object.callbacks = { -- grab, drag, close, setPosition, apply.
		close = t.callbacks and t.callbacks.close or function() object:setVisible( false ) end,
		grab = t.callbacks and t.callbacks.grab or function() object:setToTop() end,
		drag = t.callbacks and t.callbacks.drag or function( this ) object:setPosition( this.bounds:getPosition() ) end,
		apply = t.callbacks.apply
	}
	object.styles = t.styles or object.DEFAULT_STYLES
	object.filters = self.FILE_TYPES

	-- Implementation controls.
	object._controls = {
		-- window = nil,
		-- pathInput = nil,
		-- searchButton = nil,
		-- backButton = nil,
		-- fileList = nil,
		-- fileInput = nil,
		-- filterDropdown = nil,
		-- applyButton = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.

	object.path = t.path or RL.GetBasePath()
	object.files = {}
	object.filter = object.filters[1]
	object.file = nil -- Path.
	object.searchText = ""
	object.lastIndex = 0

	object:createControls()
	object:setPosition( object.bounds:getPosition() )

	return object
end

function FileBrowser:createControls()
	local styles = self.styles
	local padding = styles.fileBrowser.padding
	local spacing = styles.fileBrowser.spacing
	local iconButtonSize = styles.fileBrowser.iconButtonSize
	local textButtonSize = styles.fileBrowser.textButtonSize

	-- Window.

	self._controls.window = self._gui:newWindow( {
		bounds = Rectangle:new( 0, 0, self.bounds.width, self.bounds.height ),
		text = self.text,
		draggable = self.draggable,
		callbacks = {
			close = self.callbacks.close,
			grab = self.callbacks.grab,
			drag = self.callbacks.drag,
		},
		styles = styles.window,
	} )
	self._controls.window.position = Vector2:new()

	table.insert( self._controlsArray, self._controls.window )

	local windowHandleHeight = self._controls.window._controls.handle.bounds.height

	-- Path input.

	local pos = Vector2:new( padding, windowHandleHeight + padding )

	self._controls.pathInput = self._gui:newTextInputBox( {
		bounds = Rectangle:new( 0, 0,
			self.bounds.width - padding * 2 - spacing * 2 - iconButtonSize.x * 2, iconButtonSize.y
		),
		text = self.path,
		callbacks = {
			set = function( this )
				self:checkPath( this.text )
			end,
			edit = function( this )
				if self._controls.searchButton.toggle then
					self.searchText = this.text
					self:updateList()
				end
			end,
		},
		styles = styles.pathInput,
	} )
	self._controls.pathInput.position = pos:clone()

	table.insert( self._controlsArray, self._controls.pathInput )

	-- Search button.

	pos.x = pos.x + self._controls.pathInput.bounds.width + spacing

	self._controls.searchButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, iconButtonSize.x, iconButtonSize.y ),
		toggle = false,
		callbacks = {
			released = function( this )
				self:updateSearch( this.toggle )
			end,
		},
		styles = Util.deepCopy( styles.searchButton ),
	} )
	self._controls.searchButton.position = pos:clone()

	table.insert( self._controlsArray, self._controls.searchButton )

	-- Back button.

	pos.x = pos.x + self._controls.searchButton.bounds.width + spacing

	self._controls.backButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, iconButtonSize.x, iconButtonSize.y ),
		callbacks = {
			released = function()
				self:back()
			end,
		},
		styles = Util.deepCopy( styles.backButton ),
	} )
	self._controls.backButton.position = pos:clone()

	table.insert( self._controlsArray, self._controls.backButton )

	-- File list.

	pos.x = padding
	pos.y = pos.y + iconButtonSize.y + spacing

	self._controls.fileList = self._gui:newContainer( {
		bounds = Rectangle:new(	0, 0,
			self.bounds.width - padding * 2,
			self.bounds.height - padding * 2 - spacing * 2 - iconButtonSize.y * 2 - windowHandleHeight
		),
		styles = styles.fileList,
	} )
	self._controls.fileList.position = pos:clone()

	table.insert( self._controlsArray, self._controls.fileList )

	-- File input.

	pos.y = pos.y + self._controls.fileList.bounds.height + spacing

	self._controls.fileInput = self._gui:newTextInputBox( {
		bounds = Rectangle:new( 0, 0,
			self.bounds.width - padding * 2 - spacing * 2 - textButtonSize.x * 2,
			iconButtonSize.y
		),
		callbacks = {},
		styles = styles.fileInput,
	} )
	self._controls.fileInput.position = pos:clone()

	table.insert( self._controlsArray, self._controls.fileInput )

	-- Filter dropdown.

	pos.x = pos.x + self._controls.fileInput.bounds.width + spacing

	self._controls.filterDropdown = self._gui:newDropdown( {
		bounds = Rectangle:new( 0, 0, textButtonSize.x, textButtonSize.y ),
		text = self.filters[1],
		callbacks = {},
		styles = styles.filterDropdown,
		tooltip = "Filter",
	} )
	self._controls.filterDropdown.position = pos:clone()

	table.insert( self._controlsArray, self._controls.filterDropdown )

	self:updateFilterDropdown()

	-- Apply button.

	pos.x = pos.x + self._controls.filterDropdown.bounds.width + spacing

	self._controls.applyButton = self._gui:newButton( {
		bounds = Rectangle:new( 0, 0, textButtonSize.x, textButtonSize.y ),
		text = "Open",
		callbacks = {
			released = function()
				self:apply( self.path.."/"..self._controls.fileInput.text )
			end,
		},
		styles = Util.deepCopy( styles.applyButton ),
	} )
	self._controls.applyButton.position = pos:clone()

	table.insert( self._controlsArray, self._controls.applyButton )

	self:checkPath( self.path )
end

function FileBrowser:popup( path, callback, filters )
	self:checkPath( path or self.path )

	self.callbacks.apply = callback

	if filters ~= nil then
		self.filters = filters

		self._controls.filterDropdown:clear()
		self:updateFilterDropdown()
	end

	local winSize = Vector2:tempT( RL.GetScreenSize() )

	self:setPosition( winSize:scale( 0.5 ) - self.bounds:getSize():scale( 0.5 ) )
	self:setVisible( true )
	self:setToTop()
end

function FileBrowser:updateFilterDropdown()
	local textButtonSize = self.styles.fileBrowser.textButtonSize

	for _, ft in ipairs( self.filters ) do
		self._controls.filterDropdown:addControl( self._gui:newButton( {
			bounds = Rectangle:new( 0, 0, textButtonSize.x, textButtonSize.y ),
			text = ft,
			visible = false,
			callbacks = {
				released = function( this )
					self.filter = ft
					self._controls.filterDropdown._controls.button.text = ft
					self._controls.filterDropdown:showContent( false )
					self:checkPath( self.path )
				end
			}
		} )	)
	end
end

function FileBrowser:checkPath( path )
	if path:sub( 1, 2 ) == "//" then
		path = path:sub( 2 )
	end

	if RL.DirectoryExists( path ) then
		self.path = path
		self.searchText = ""
		self._controls.searchButton.toggle = false
		self._controls.pathInput.text = self.path
		self:updateList()
	end
end

function FileBrowser:updateList()
	local list = self._controls.fileList
	list:clear()
	self._controls.fileInput.text = ""
	self.files = {}
	self.lastIndex = 0
	local files = RL.LoadDirectoryFilesEx( self.path, self.filter, false )

	table.sort( files, function( a, b ) return a < b end )
	
	for i = #files, 1, -1 do
		local filePath = files[i]

		-- Don't add unix hidden files.
		if RL.GetFileName( filePath ):sub( 1, 1 ) ~= "." then
			local record = {
				path = filePath,
				name = RL.GetFileName( filePath ),
				isFile = RL.IsPathFile( filePath ),
				sortValue = i
			}
			if record.isFile then
				record.sortValue = record.sortValue + #files
			end

			-- Search.
			if self.searchText == "" or ( 0 < #self.searchText
			and -1 < RL.TextFindIndex( record.name:lower(), self.searchText:lower() ) ) then
				table.insert( self.files, record )
			end
		end
	end

	table.sort( self.files, function( a, b ) return a.sortValue < b.sortValue end )

	for i, file in ipairs( self.files ) do
		local styles = Util.deepCopy( FileBrowser.DEFAULT_STYLES.listFileButton )
		local icon = self.FILE_ICONS.DIR

		if file.isFile then
			local ext = RL.GetFileExtension( file.name )

			if self.FILE_ICONS[ ext ] ~= nil then
				icon = self.FILE_ICONS[ ext ]
			else
				icon = self.FILE_ICONS.FILE
			end
		end

		styles.normal.icons[1].iconId = icon
		Gui:setForAllStyles( styles, "icons", styles.normal.icons )

		list:addControl(
			list.gui:newButton( {
				bounds = Rectangle:new( 0, 0, list.view.width, self.styles.fileBrowser.fileButtonHeight ),
				text = file.name,
				toggle = false,
				callbacks = {
					pressed = function( this )
						self:select( i )
					end
				},
				styles = styles,
			} )
		)
	end

	list:updateControls()
end

function FileBrowser:select( index )
	local list = self._controls.fileList

	if index == self.lastIndex then
		if RL.IsPathFile( self.file ) then
			self:apply( self.file )
		else
			self:checkPath( self.file )
			return
		end
	else
		self.file = self.files[ index ].path
		self._controls.fileInput.text = RL.GetFileName( self.file )
	end

	for i, control in ipairs( list.controls ) do
		control.toggle = index == i
	end

	self.lastIndex = index
end

function FileBrowser:back()
	if self._controls.searchButton.toggle then
		return
	end

	local pathInput = self._controls.pathInput

	for i = #pathInput.text, 1, -1 do
		if pathInput.text:sub( i, i ) == "/" and i < #pathInput.text then
			pathInput.text = pathInput.text:sub( 1, math.max( 1, i - 1 ) )
			self:checkPath( pathInput.text )

			return
		end
	end
end

function FileBrowser:updateSearch( toggle )
	toggle = not toggle
	self._controls.searchButton.toggle = toggle
	self.searchText = ""
	self._controls.pathInput.text = toggle and self.searchText or self.path

	self:updateList()
end

function FileBrowser:apply( path )
	if self.callbacks.apply then
		-- self.callbacks.apply( self )
		self.callbacks.apply( path )
	end
end

function FileBrowser:setSize( size )
	self.bounds:setSize( size )

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

return { FileBrowser = FileBrowser }
