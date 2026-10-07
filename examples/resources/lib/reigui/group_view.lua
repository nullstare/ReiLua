local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

-- GroupView control.

local GroupView = {}
local metatable = {
	__index = setmetatable( GroupView, { __index = GuiControl } ),
}

GroupView.DEFAULT_STYLES = {}

function GroupView.DEFAULT_STYLES_UPDATE()
	GroupView.DEFAULT_STYLES = {
		groupView = {
			buttonHeight = 22,
			indent = 8,
			padding = 4,
			spacing = 4,
		},
		container = Util.deepCopy( Gui.Container.DEFAULT_STYLES ),
		dropdown = Util.deepCopy( Gui.Dropdown.DEFAULT_STYLES ),
	}

	GroupView.DEFAULT_STYLES.dropdown.dropdown.alignH = RL.TEXT_ALIGN_RIGHT
	GroupView.DEFAULT_STYLES.dropdown.dropdown.accumPosY = false

	Gui:setForAllStyles( GroupView.DEFAULT_STYLES.dropdown.button, "icons", {
		{
			iconId = RL.ICON_ARROW_RIGHT_FILL,
			offset = Vector2:new( 0, 0 ),
			pixelSize = 1,
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
			alignH = RL.TEXT_ALIGN_LEFT,
			alignV = RL.TEXT_ALIGN_CENTER,
		},
	} )
	GroupView.DEFAULT_STYLES.dropdown.button.pressed.icons = {
		{
			iconId = RL.ICON_ARROW_DOWN_FILL,
			offset = Vector2:new( 0, 0 ),
			pixelSize = 1,
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.BUTTON, RL.TEXT_COLOR_NORMAL ) ) ),
			alignH = RL.TEXT_ALIGN_LEFT,
			alignV = RL.TEXT_ALIGN_CENTER,
		},
	}
end

GroupView.DEFAULT_STYLES_UPDATE()

function GroupView:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	object.gui = nil -- Set to container gui.

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new()
	object.toggle = Util.setWithDefault( t.toggle, false )
	object.text = t.text or ""

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.
	object.callbacks = t.callbacks or {} -- set, setPosition.
	object.styles = t.styles or object.DEFAULT_STYLES
	object.stylesOverlay = t.stylesOverlay or {}

	object._controls = {
		-- container = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	object.groups = {}

	object:createControls( t )
	object:setPosition( object.bounds:getPosition() )

	return object
end

function GroupView:createControls( t )
	local styles = self.styles

	-- Container.

	self._controls.container = self._gui:newContainer( {
		bounds = Rectangle:new( 0, 0, self.bounds.width, self.bounds.height ),
		styles = styles.container,
	} )
	self._controls.container.position = Vector2:new()

	self.gui = self._controls.container.gui

	table.insert( self._controlsArray, self._controls.container )
end

function GroupView:addGroup( name, text )
	local container = self._controls.container

	self.groups[ name ] = container:addControl(
		container.gui:newDropdown( {
			bounds = Rectangle:new( 0, 0, container.view.width, self.styles.groupView.buttonHeight ),
			text = text,
			mouseClose = false,
			callbacks = {
				released = function( _ )
					container:updateControls()
				end
			},
			styles = self.styles.dropdown,
		} )
	)

	container:updateControls()

	return self.groups[ name ]
end

function GroupView:addToGroup( name, control )
	local container = self._controls.container
	local dropdown = self.groups[ name ]
	local indent = self.styles.groupView.indent

	control:setVisible( dropdown.toggle and dropdown.visible )
	-- control:setSize( Vector2:new( container.view.width - indent, control.bounds.height ) )
	-- control:setPosition( Vector2:new( indent, 0 ) )

	container:addControl( dropdown:addControl( control ) )

	container:updateControls()
end

function GroupView:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	if self._controlsArray then
		for _, control in ipairs( self._controlsArray ) do
			control:setPosition( pos + control.position or Vector2:temp() )
		end
	end
	if self.callbacks.setPosition then
		self.callbacks.setPosition( self, pos )
	end

	self._controls.container:updateControls()
end

function GroupView:setSize( size )
	self.bounds.width = size.x
	self.bounds.height = size.y

	if self._controlsArray then
		for _, control in ipairs( self._controlsArray ) do
			control:setSize( size )
		end
	end

	if self.callbacks.setSize then
		self.callbacks.setSize( self, size )
	end

	self._controls.container:updateControls()
end

return { GroupView = GroupView }
