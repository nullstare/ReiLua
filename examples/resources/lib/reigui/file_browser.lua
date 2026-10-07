local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

local FileBrowser = {}
local metatable = {
	__index = setmetatable( FileBrowser, { __index = GuiControl } ),
}

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

FileBrowser.DEFAULT_STYLES = {}

function FileBrowser.DEFAULT_STYLES_UPDATE()
	FileBrowser.DEFAULT_STYLES = {
		fileBrowser = {
			defaultRect = Rectangle:new( 0, 0, 632, 504 ),
			padding = 8,
			spacing = 4,
			iconButtonSize = Vector2:new( 28 ),
			textButtonSize = Vector2:new( 72, 28 ),
			fileButtonHeight = 24,
			iconColor = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
		},
		window = Util.deepCopy( Gui.Window.DEFAULT_STYLES ),
		pathInput = Util.deepCopy( Gui.TextInputBox.DEFAULT_STYLES ),
		searchButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
		backButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
		fileContainer = Util.deepCopy( Gui.Container.DEFAULT_STYLES ),
		fileInput = Util.deepCopy( Gui.TextInputBox.DEFAULT_STYLES ),
		filterDropdown = Util.deepCopy( Gui.Dropdown.DEFAULT_STYLES ),
		applyButton = Util.deepCopy( Gui.Button.DEFAULT_STYLES ),
		fileList = Util.deepCopy( Gui.List.DEFAULT_STYLES ),
	}

	-- File list.

	FileBrowser.DEFAULT_STYLES.fileContainer.container.scrollSteps = FileBrowser.DEFAULT_STYLES.fileBrowser.fileButtonHeight
	+ FileBrowser.DEFAULT_STYLES.fileBrowser.spacing

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

	-- File list.

	Gui:setForAllStyles( FileBrowser.DEFAULT_STYLES.fileList, "text.padding", 18 )
end

FileBrowser.DEFAULT_STYLES_UPDATE()

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
	object.stylesOverlay = t.stylesOverlay or {}
	object.filters = self.FILE_TYPES

	-- Implementation controls.
	object._controls = {
		-- window = nil,
		-- pathInput = nil,
		-- searchButton = nil,
		-- backButton = nil,
		-- fileContainer = nil,
		-- fileInput = nil,
		-- filterDropdown = nil,
		-- applyButton = nil,
		-- fileList = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.
	object.draggable = Util.setWithDefault( t.draggable, true )

	object.path = t.path or RL.GetBasePath()
	object.files = {}
	object.filter = object.filters[1]
	object.file = nil -- Path.
	object.searchText = ""
	object.lastIndex = 0

	object:createControls()
	object:setPosition( object.bounds:getPosition() )
	object:setVisible( object.visible )

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

	self._controls.fileContainer = self._gui:newContainer( {
		bounds = Rectangle:new(	0, 0,
			self.bounds.width - padding * 2,
			self.bounds.height - padding * 2 - spacing * 2 - iconButtonSize.y * 2 - windowHandleHeight
		),
		styles = styles.fileContainer,
	} )
	self._controls.fileContainer.position = pos:clone()

	table.insert( self._controlsArray, self._controls.fileContainer )

	-- File input.

	pos.y = pos.y + self._controls.fileContainer.bounds.height + spacing

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

	-- File list.

	local view = self._controls.fileContainer.view

	self._controls.fileList = self._controls.fileContainer:addControl(
		self._controls.fileContainer.gui:newList( {
			bounds = Rectangle:new( 0, 0, view.width, view.height ),
			callbacks = {
				pressed = function( this )
					self:select( this.selectedId )
				end
			},
			styles = Util.deepCopy( styles.fileList ),
		} )
	)
end

function FileBrowser:popup( path, callback, filters )
	self.callbacks.apply = callback

	if filters ~= nil then
		self.filters = filters
		self.filter = self.filters[1]
		self._controls.filterDropdown:clear()
		self:updateFilterDropdown()
	end

	local winSize = Vector2:tempT( RL.GetScreenSize() )

	self:setPosition( winSize:scale( 0.5 ) - self.bounds:getSize():scale( 0.5 ) )
	self:setVisible( true )
	self:setToTop()
	self:checkPath( path or self.path )
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

		if ft == self.filter then
			self._controls.filterDropdown._controls.button.text = ft
		end
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

	local listT = {}

	for _, file in ipairs( self.files ) do
		local icon = self.FILE_ICONS.DIR

		if file.isFile then
			local ext = RL.GetFileExtension( file.name )

			if self.FILE_ICONS[ ext ] ~= nil then
				icon = self.FILE_ICONS[ ext ]
			else
				icon = self.FILE_ICONS.FILE
			end
		end

		table.insert( listT, {
			text = file.name,
			icon = {
				iconId = icon,
				offset = Vector2:new( 0, 0 ),
				pixelSize = 1,
				color = self.styles.fileBrowser.iconColor,
				alignH = RL.TEXT_ALIGN_LEFT,
				alignV = RL.TEXT_ALIGN_TOP,
			}
		} )
	end

	self._controls.fileList.selectedId = nil
	self._controls.fileList:updateList( listT )
	self._controls.fileContainer:updateControls()
end

function FileBrowser:select( index )
	local list = self._controls.fileContainer

	if index == self.lastIndex then
		if RL.IsPathFile( self.file ) then
			self:apply( self.file )
		else
			self:checkPath( self.file )
			return
		end
	elseif 0 < index and index <= #self.files then
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
		self.callbacks.apply( path )
	end
end

function FileBrowser:setSize( size )
	self.bounds:setSizeV( size )

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

return { FileBrowser = FileBrowser }
