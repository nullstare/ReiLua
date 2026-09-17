local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Gui = Gui or require( "reigui/gui" )

Container = {}
local metatable = {
	__index = setmetatable( Container, { __index = GuiControl } ),
}

Container.FILL_TYPE = {
	LIST_DOWN = 0,
	LIST_RIGHT = 1,
	GRID_DOWN = 2,
	GRID_RIGHT = 3,
	FREE = 4,
}
Container.DEFAULT_STYLES = {
	container = {
		fillType = Container.FILL_TYPE.LIST_DOWN,
		size = Vector2:new( 256, 256 ),
		padding = 8,
		spacing = 4,
		scrollBarSpacing = 8,
		borderClipWidth = 4,
		scrollSteps = 8, -- How many slider valueSteps.
	},
	panel = Util.deepCopy( Gui.Panel.DEFAULT_STYLES ),
	scrollBarH = Util.deepCopy( Gui.Slider.DEFAULT_STYLES ),
	scrollBarV = Util.deepCopy( Gui.Slider.DEFAULT_STYLES ),
}
Gui:setForAllStyles( Container.DEFAULT_STYLES.scrollBarH, "slider.minWidth", 8 )
Gui:setForAllStyles( Container.DEFAULT_STYLES.scrollBarV, "slider.minWidth", 8 )

function Container:new( gui, t )
	local object = setmetatable( {}, metatable )
	object._gui = gui

	local styles = object.DEFAULT_STYLES.container

	object.bounds = t.bounds and t.bounds:clone() or Rectangle:new( 0, 0, styles.size.x, styles.size.y )
	object.callbacks = t.callbacks or {}
	object.styles = t.styles or object.DEFAULT_STYLES

	-- Implementation controls.
	object._controls = {
		-- panel = nil,
		-- scrollBarH = nil,
		-- scrollBarV = nil,
	}
	object._controlsArray = {} -- Controls in predefined order.

	-- Container controls.
	object.controls = {}

	object.gui = Gui:new() -- Contains full independent gui system.
	object.content = Rectangle:new()
	object.scroll = Vector2:new( 0, 0 )
	object.view = Rectangle:new( 0, 0, 0, 0 )
	-- Will reserve room for scrollbar within bounds.

	local fillType = styles.fillType

	object._scrollDir = {
		x = fillType == object.FILL_TYPE.LIST_RIGHT or fillType == object.FILL_TYPE.GRID_RIGHT or fillType == object.FILL_TYPE.FREE,
		y = fillType == object.FILL_TYPE.LIST_DOWN or fillType == object.FILL_TYPE.GRID_DOWN or fillType == object.FILL_TYPE.FREE
	}

	object.visible = Util.setWithDefault( t.visible, true )
	object.locked = Util.setWithDefault( t.locked, false )
	object.disabled = Util.setWithDefault( t.disabled, false ) -- Same as locked but also uses style.

	object._ctrPos = Vector2:new()

	object:createControls()
	object:setPosition( object.bounds:getPosition() )

	return object
end

function Container:createControls()
	local styles = self.styles
	local spacing = styles.container.scrollBarSpacing
	local scrollBarWidthH = styles.scrollBarH.normal.slider.width
	local scrollBarWidthV = styles.scrollBarV.normal.slider.width

	-- Panel.

	self._controls.panel = self._gui:newPanel( {
		bounds = Rectangle:new( 0, 0,
			self._scrollDir.y and ( self.bounds.width - scrollBarWidthV - spacing ) or self.bounds.width,
			self._scrollDir.x and ( self.bounds.height - scrollBarWidthH - spacing ) or self.bounds.height
		),
		styles = styles.panel,
	} )
	self._controls.panel.position = Vector2:new()

	table.insert( self._controlsArray, self._controls.panel )

	-- Scroll Bar Horizontal.

	if self._scrollDir.x then
		self._controls.scrollBarH = self._gui:newSlider( {
			bounds = Rectangle:new( 0, 0,
				self._controls.panel.bounds.width,
				scrollBarWidthH
			),
			callbacks = {
				edit = function( this )
					self.scroll.x = -RL.Round( this.value.x )
					self:refresh()
				end
			},
			valueStep = Vector2:new( 1, 0 ),
			styles = Util.deepCopy( styles.scrollBarH ),
		} )
		self._controls.scrollBarH.position = Vector2:new( 0, self.bounds.height - scrollBarWidthH )
	
		table.insert( self._controlsArray, self._controls.scrollBarH )
	end

	-- Scroll Bar Vertical.

	if self._scrollDir.y then
		self._controls.scrollBarV = self._gui:newSlider( {
			bounds = Rectangle:new( 0, 0,
				scrollBarWidthV,
				self._controls.panel.bounds.height
			),
			callbacks = {
				edit = function( this )
					self.scroll.y = -RL.Round( this.value.y )
					self:refresh()
				end
			},
			valueStep = Vector2:new( 0, 1 ),
			styles = Util.deepCopy( styles.scrollBarV ),
		} )
		self._controls.scrollBarV.position = Vector2:new( self.bounds.width - scrollBarWidthV, 0 )
	
		table.insert( self._controlsArray, self._controls.scrollBarV )
	end

	self:refresh()
	self:setToTop()
end

function Container:refresh()
	self:updateScrollBars()
	self:updateMouseOffset()
	self.gui.view:set( -self.scroll.x, -self.scroll.y, self.view.width, self.view.height )

	local styles = self.styles.container
	local panelBounds = self._controls.panel.bounds

	self.view:set(
		panelBounds.x + styles.padding,
		panelBounds.y + styles.padding,
		panelBounds.width - styles.padding * 2,
		panelBounds.height - styles.padding * 2
	)
end

function Container:updateScrollBars()
	local sbH = self._controls.scrollBarH
	local sbV = self._controls.scrollBarV

	if sbH then
		sbH.maxValue:set( math.max( self.content.width - self.view.width, 0 ), 0 )
		sbH.value:set( math.min( sbH.value.x, sbH.maxValue.x, 0 ) )

		local styles = sbH.styles
		local ratio = self.view.width / self.content.width
		local len = math.max( ratio * self.bounds.width, styles.normal.slider.minWidth )

		Gui:setForAllStyles( styles, "slider.width", len )
	end

	if sbV then
		sbV.maxValue:set( 0, math.max( self.content.height - self.view.height, 0 ) )
		sbV.value:set( 0, math.min( sbV.value.y, sbV.maxValue.y ) )
		self.scroll.y = math.max( self.scroll.y, -sbV.value.y )

		local styles = sbV.styles
		local ratio = self.view.height / self.content.height
		local len = math.max( ratio * self.bounds.height, styles.normal.slider.minWidth )

		Gui:setForAllStyles( styles, "slider.width", len )
	end
end

function Container:update( delta )
	local mousePos = Vector2:tempT( RL.GetMousePosition() )
	local styles = self.styles.container

	if self.view:checkCollisionPoint( mousePos ) then
		local mouseScroll = Vector2:tempT( RL.GetMouseWheelMoveV() )

		if mouseScroll.y ~= 0 then
			local sbV = self._controls.scrollBarV

			if sbV then
				self:refresh()
				local step = sbV.valueStep and sbV.valueStep.y or 1
				sbV:setValue( sbV.value - Vector2:temp( 0, mouseScroll.y * step * styles.scrollSteps ) )
			end
		end
	end

	self.gui.locked = not self._controls.panel._isMouseOver
	self.gui:update( delta )
end

function Container:updateControls()
	if self.fillType == self.FILL_TYPE.FREE then
		return
	end

	self._ctrPos:set()
	self.content:set()

	for _, control in ipairs( self.controls ) do
		if control.visible then
			self:setControlPos( control )
		end
	end

	self:refresh()
end

-- Note! GridFills expect that controls are the same size.
function Container:setControlPos( control )
	if self.fillType == self.FILL_TYPE.FREE or not control.visible then
		return
	end

	-- Note! Padding is handled by view.
	local styles = self.styles.container
	local spacing = styles.spacing

	control:setPosition( self._ctrPos )

	local fillType = styles.fillType

	if fillType == self.FILL_TYPE.LIST_DOWN or fillType == self.FILL_TYPE.GRID_RIGHT then
		self._ctrPos.y = control.bounds.y + control.bounds.height + spacing

		if fillType == self.FILL_TYPE.GRID_RIGHT
		and self.view.height < ( self._ctrPos.y + control.bounds.height ) then
			self._ctrPos.x = control.bounds.x + control.bounds.width + spacing
			self._ctrPos.y = 0
		end
	elseif fillType == self.FILL_TYPE.LIST_RIGHT or fillType == self.FILL_TYPE.GRID_DOWN then
		self._ctrPos.x = control.bounds.x + control.bounds.width + spacing

		if fillType == self.FILL_TYPE.GRID_DOWN
		and self.view.width < ( self._ctrPos.x + control.bounds.width ) then
			self._ctrPos.x = 0
			self._ctrPos.y = control.bounds.y + control.bounds.height + spacing
		end
	end

	self.content = self.content:fit( control.bounds )
end

function Container:addControl( control, index )
	index = RL.Clamp( index or #self.controls + 1, 1, #self.controls + 1 )
	table.insert( self.controls, index, control )

	self:setControlPos( control )

	return control
end

function Container:clear()
	self.controls = {}
	self.gui:clear()
	self.scroll:set( 0 )
end

function Container:updateMouseOffset()
	if self._gui then
		self.gui.mouseScale = self._gui.mouseScale
		local mouseScale = Vector2:temp( 1, 1 ) / self.gui.mouseScale

		self.gui.mouseOffset = self._gui.mouseOffset + ( -Vector2:temp( self.view.x, self.view.y ) - self.scroll ) * mouseScale
	end
end

function Container:draw()
	local styles = self.styles.container
	local panelBounds = self._controls.panel.bounds

	local clipRect = Rectangle:new(
		panelBounds.x + styles.padding,
		panelBounds.y + styles.padding,
		panelBounds.width - styles.padding * 2,
		panelBounds.height - styles.padding * 2
	)

	RL.BeginScissorMode( clipRect )
		RL.rlPushMatrix()
		RL.rlTranslatef( { RL.Round( self.view.x + self.scroll.x ), RL.Round( self.view.y + self.scroll.y ), 0 } )
		self.gui:draw()
		RL.rlPopMatrix()
	RL.EndScissorMode()

	-- RL.DrawRectangleLines( self.gui.view, RL.RED )
	-- RL.DrawRectangleLines( self.view, RL.RED )
	-- RL.DrawRectangleLines( self.content, RL.BLUE )
	-- RL.DrawRectangleLines( clipRect, RL.GREEN )
end

function Container:setPosition( pos )
	self.bounds.x = pos.x
	self.bounds.y = pos.y

	for _, control in ipairs( self._controlsArray ) do
		if control.setPosition then
			control:setPosition( pos + control.position or Vector2:temp() )
		else
			control.bounds:setPositionV( self.bounds:getPosition() + control.position or Vector2:temp() )
		end
	end

	if self.callbacks.setPosition then
		self.callbacks.setPosition( self )
	end

	self:refresh()
end

function Container:setSize( size )
	self.bounds:setSize( size )

	if self.callbacks.setSize then
		self.callbacks.setSize( self )
	end

	self:setPosition( self.bounds:getPosition() )
end

function Container:setToTop()
	if self._controlsArray then
		for _, control in ipairs( self._controlsArray ) do
			control:setToTop()
		end
	end
	if self.callbacks.setToTop then
		self.callbacks.setToTop( self )
	end
	-- Sets gui in front of others.
	self._gui:setToTop( self )
end

return { Container = Container }
