local FileBrowser = {}
FileBrowser.__index = FileBrowser

FileBrowser.MODES = {
	OPEN = 1,
	SAVE = 2,
}
FileBrowser.FILE_ICONS = {
	DIR = 1,
	FILE = 10,
	[".wav"] = 11,
	[".mp3"] = 11,
	[".ogg"] = 11,
	[".mid"] = 11,
	[".png"] = 12,
	[".jpg"] = 12,
	[".jpeg"] = 12,
	[".avi"] = 13,
	[".mov"] = 13,
	[".mp4"] = 13,
	[".exe"] = 142,
}

function FileBrowser:new( pos )
	local object = setmetatable( {}, FileBrowser )
	
	object.padding = 4
	object.spacing = 4
	object.controls = {}
	object.callbacks = {} -- open.

	local winSize = Vec2:new( 600, 490 )
	local iconButtonSize = Vec2:new( 28, 28 )
	local textButtonSize = Vec2:new( 72, 28 )

	-- Window.
	object.window = Gui:WindowBox(
		Rect:new( pos.x, pos.y, winSize.x, winSize.y ),
		"File Browser",
		{ -- callbacks.
			close = function() object:setVisible( false ) end,
			grab = function() object:setToTop() end,
			drag = function( this ) object:setPosition( Vec2:new( this.bounds.x, this.bounds.y ) ) end
		}
	)

	-- Ok button.
	object.okButton = Gui:Button(
		Rect:new( 0, 0, textButtonSize.x, textButtonSize.y ),
		"Open",
		{ -- callbacks.
			pressed = function() object:ok() end
		}
	)
	object.okButton.position = Vec2:new(
		winSize.x - textButtonSize.x - object.padding,
		winSize.y - textButtonSize.y - object.padding
	)

	-- Filter dropdown.
	object.filterDropdown = Gui:DropdownBox(
		Rect:new( 0, 0, textButtonSize.x, textButtonSize.y ),
		"All\n.png\n.lua\n.wav\n.ogg\n.txt",
		0, -- active.
		false, -- editMode.
		{ -- callbacks.
			select = function() object:setFilter() end
		},
		{ -- styles.
			properties = {
				{ RL.DROPDOWNBOX, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT },
				{ RL.DROPDOWNBOX, RL.TEXT_PADDING, 8 },
			}
		}
	)
	object.filterDropdown.position = Vec2:new(
		winSize.x - textButtonSize.x * 2 - object.padding * 2,
		winSize.y - textButtonSize.y - object.padding
	)

	-- Back button.
	object.backButton = Gui:Button(
		Rect:new( 0, 0, iconButtonSize.x, iconButtonSize.y ),
		RL.GuiIconText( 118, "" ),
		{ -- callbacks.
			pressed = function() object:back() end
		}
	)
	object.backButton.position = Vec2:new(
		winSize.x - iconButtonSize.x - object.padding,
		Gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + object.padding
	)

	-- Search button.
	object.searchToggle = Gui:Toggle(
		Rect:new( 0, 0, iconButtonSize.x, iconButtonSize.y ),
		RL.GuiIconText( 42, "" ),
		false, -- active.
		{ -- callbacks.
			pressed = function( this ) object:searchPressed( this.active ) end
		}
	)
	object.searchToggle.position = Vec2:new(
		winSize.x - iconButtonSize.x * 2 - object.padding * 2,
		Gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + object.padding
	)

	-- Path text box.
	object.pathBox = Gui:TextBox(
		Rect:new( 0, 0, winSize.x - iconButtonSize.x * 2 - object.padding * 4, iconButtonSize.y ),
		"",
		256,
		false,
		{ -- callbacks.
			-- edit = function() object:editPathCallback() end,
			textEdit = function() object:editPathCallback() end
		}
	)
	object.pathBox.position = Vec2:new(
		object.padding,
		Gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + object.padding
	)

	-- File text box.
	object.fileBox = Gui:TextBox(
		Rect:new( 0, 0, winSize.x - textButtonSize.x * 2 - object.padding * 4, iconButtonSize.y ),
		"",
		256,
		false,
		{ -- callbacks.
			-- edit = function() object:checkPath() end
		}
	)
	object.fileBox.position = Vec2:new(
		object.padding,
		winSize.y - object.okButton.bounds.height - object.padding
	)

	-- File List.
	object.list = Gui:ListView(
		Rect:new( 0, 0,
			winSize.x - object.padding * 2,
			winSize.y - Gui.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - textButtonSize.y
			- object.pathBox.bounds.height - object.padding * 3 - object.spacing
		),
		"",
		0, -- scrollIndex.
		0, -- active.
		{ -- callbacks.
			select = function() object:select() end
		},
		{ -- styles
			properties = {
				{ RL.LISTVIEW, RL.TEXT_ALIGNMENT, RL.TEXT_ALIGN_LEFT }
			}
		}
	)
	object.list.position = Vec2:new(
		object.padding,
		object.pathBox.position.y + object.pathBox.bounds.height + object.padding
	)

	table.insert( object.controls, object.okButton )
	table.insert( object.controls, object.filterDropdown )
	table.insert( object.controls, object.backButton )
	table.insert( object.controls, object.searchToggle )
	table.insert( object.controls, object.list )
	table.insert( object.controls, object.pathBox )
	table.insert( object.controls, object.fileBox )

	object.filter = nil
	object.path = ""
	object.file = ""
	object.searchText = ""
	object.files = {}
	object.lastActive = 0
	object.mode = self.MODES.OPEN

	object:setPosition( pos )
	object:setVisible( false )

	return object
end

function FileBrowser:popup( mode, path, callback, filters )
	self:setPath( path )
	self.mode = mode

	if self.mode == self.MODES.OPEN then
		self.okButton.text = "Open"
		self.callbacks.ok = callback
	end

	if filters ~= nil then
		self.filterDropdown.text = "All\n"..filters
	end

	self:setVisible( true )
end

function FileBrowser:editPathCallback()
	if self.searchToggle.active then
		self.searchText = self.pathBox.text
		self:updateList()
	else
		self:checkPath()
	end
end

function FileBrowser:checkPath()
	local path = self.pathBox.text

	self.searchToggle.active = false
	self.searchText = ""

	if RL.FileExists( path ) and not RL.IsPathFile( path ) then
		self:setPath( path )
	end
end

function FileBrowser:back()
	if self.searchToggle.active then
		return
	end

	for i = #self.pathBox.text, 1, -1 do
		if self.pathBox.text:sub( i, i ) == "/" and i < #self.pathBox.text then
			self.pathBox.text = self.pathBox.text:sub( 1, math.max( 1, i - 1 ) )
			self:checkPath()

			return
		end
	end
end

function FileBrowser:setPath( path )
	if path:sub( 1, 2 ) == "//" then
		path = path:sub( 2 )
	end

	self.lastActive = 0
	self.list.active = -1
	self.pathBox.text = path
	self.path = path

	self:updateList()
end

function FileBrowser:updateList()
	self.list.text = ""
	self.files = {}
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
		local icon = self.FILE_ICONS.DIR

		if file.isFile then
			local ext = RL.GetFileExtension( file.name )

			if self.FILE_ICONS[ ext ] ~= nil then
				icon = self.FILE_ICONS[ ext ]
			else
				icon = self.FILE_ICONS.FILE
			end
		end

		self.list.text = self.list.text..RL.GuiIconText( icon, file.name )

		if i < #self.files then
			self.list.text = self.list.text.."\n"
		end
	end
end

function FileBrowser:select()
	local index = self.list.active + 1
	local lastFile = self.files[ self.lastActive ]

	if 0 < index then
		self.file = self.files[ index ].path
		self.fileBox.text = self.files[ index ].name
	elseif lastFile ~= nil then
		-- Trigger if active pressed again, so index would be 0.
		if index == 0 then
			if RL.IsPathFile( lastFile.path ) then
				self:ok()
			else
				self.pathBox.text = lastFile.path
				self:checkPath()
			end
		end
	end

	self.lastActive = index
end

function FileBrowser:ok()
	if self.mode == self.MODES.OPEN then
		if RL.IsPathFile( self.file ) then
			if self.callbacks.ok ~= nil then
				self.callbacks.ok( self.file )
			end
		else
			self.pathBox.text = self.file
			self:checkPath()
		end
	end
end

function FileBrowser:searchPressed( active )
	if active then
		self.pathBox.text = self.searchText
		self.pathBox.active = true
		Gui:editMode( self.pathBox ) -- Would not call edit callback if had one.
		self.pathBox.editMode = true
	else
		self.searchText = ""
		self.pathBox.text = self.path
		self:checkPath()
	end
end

function FileBrowser:setFilter()
	if self.filterDropdown.active == 0 then
		self.filter = nil
	else
		self.filter = self.filterDropdown:getItem( self.filterDropdown.active )
	end

	self:updateList()
end

function FileBrowser:setPosition( pos )
	for _, control in ipairs( self.controls ) do
		control:setPosition( pos + control.position )
	end
end

function FileBrowser:setToTop()
	Gui:setToTop( self.window )

	for _, control in ipairs( self.controls ) do
		Gui:setToTop( control )
	end
end

function FileBrowser:setVisible( visible )
	self.visible = visible
	self.window.visible = visible

	for _, control in ipairs( self.controls ) do
		control.visible = visible
	end
end

return FileBrowser
