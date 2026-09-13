local Util = Util or require( "utillib" )
local Rectangle = Rectangle or require( "rectangle" )
local Vector2 = Vector2 or require( "vector2" )
local Color = Color or require( "color" )

GUI_DEFAULT_STYLES = {
	normal = {
		base = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BASE_COLOR_NORMAL ) ) ),
		},
		border = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_COLOR_NORMAL ) ) ),
			width = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH ),
		},
		text = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_COLOR_NORMAL ) ) ),
			font = RL.GuiGetFont(),
			fontSize = RL.GetFontBaseSize( RL.GuiGetFont() ),
			spacing = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING ),
			alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	},
	focused = {
		base = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BASE_COLOR_FOCUSED ) ) ),
		},
		border = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_COLOR_FOCUSED ) ) ),
			width = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH ),
		},
		text = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_COLOR_FOCUSED ) ) ),
			font = RL.GuiGetFont(),
			fontSize = RL.GetFontBaseSize( RL.GuiGetFont() ),
			spacing = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING ),
			alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	},
	disabled = {
		base = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BASE_COLOR_DISABLED ) ) ),
		},
		border = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_COLOR_DISABLED ) ) ),
			width = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH ),
		},
		text = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_COLOR_DISABLED ) ) ),
			font = RL.GuiGetFont(),
			fontSize = RL.GetFontBaseSize( RL.GuiGetFont() ),
			spacing = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING ),
			alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	},
	pressed = {
		base = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BASE_COLOR_PRESSED ) ) ),
		},
		border = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_COLOR_PRESSED ) ) ),
			width = RL.GuiGetStyle( RL.DEFAULT, RL.BORDER_WIDTH ),
		},
		text = {
			color = Color:newT( RL.GetColor( RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_COLOR_PRESSED ) ) ),
			font = RL.GuiGetFont(),
			fontSize = RL.GetFontBaseSize( RL.GuiGetFont() ),
			spacing = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_SPACING ),
			alignH = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT ),
			alignV = RL.GuiGetStyle( RL.DEFAULT, RL.TEXT_ALIGNMENT_VERTICAL ),
		}
	},
}

local Gui = {}
Gui.__index = Gui

function Gui:new()
	local object = setmetatable( {}, self )

	object.MOUSE_BUTTON = RL.MOUSE_BUTTON_LEFT
	object.MOUSE_BUTTON_SECONDARY = RL.MOUSE_BUTTON_RIGHT

	object.disabled = false
	object.locked = false -- Shows locked style.

	object.controls = {}
	-- object.focused = 0
	object.dragging = nil
	object.grabPos = Vector2:new( 0, 0 )
	object.mouseOffset = Vector2:new( 0, 0 )
	object.mouseScale = Vector2:new( 1, 1 )
	object.view = Rectangle:new( 0, 0, 0, 0 ) -- Active if larger than 0. Then only controls in view will be updated and drawn.
	object.tooltipStyles = Util.deepCopy( GUI_DEFAULT_STYLES.normal )
	object.tooltip = {
		mouseOver = nil,
		text = nil,
		offset = Vector2:new( 12, 24 ),
		delay = 0.5,
		timer = 0.0
	}
	object.mouseOver = nil
	object.controlPressed = nil
	object.controlTextEdit = nil
	object.controlDragged = nil
	
	object._mousePos = Vector2:new()
	object._mousePressPos = Vector2:new( -1, -1 ) -- Use to check if release and check are inside bounds.
	object._isMousePressed = false

	return object
end

function Gui:inView( control )
	-- CheckBox for example uses focusBounds and sliders viewBounds.
	return self.view.width == 0 or self.view.height == 0 or self.view:checkCollisionRec( control.viewBounds or control.focusBounds or control.bounds )
end

function Gui:update( delta )
	if self.disabled or self.locked then
		self.mouseOver = nil
		self.controlPressed = nil
		self.tooltip.text = nil
		return
	end
	self._mousePos = Vector2:newT( RL.GetMousePosition() )

	self._isMousePressed = RL.IsMouseButtonPressed( self.MOUSE_BUTTON )
	self._isMouseDown = RL.IsMouseButtonDown( self.MOUSE_BUTTON )
	self._isMouseReleased = RL.IsMouseButtonReleased( self.MOUSE_BUTTON )

	if self._isMousePressed then
		self._mousePressPos:setV( self._mousePos )
	end

	self.mouseOver = nil
	self.tooltip.mouseOver = nil

	if self.controlDragged then
		if self.controlTextEdit then
			self.controlTextEdit:endEditMode()
		end

		self.controlDragged:update( delta )

		return
	end

	for i = #self.controls, 1, -1 do
		local control = self.controls[i]

		-- print( control.__index == self.Slider, control.disabled, control.locked )

		if control.visible then
			if control._isMouseOver ~= nil then
				control._isMouseOver = self.mouseOver == nil and RL.CheckCollisionPointRec( self._mousePos, control.bounds )
			end

			if control._isMouseOver then
				self.mouseOver = control

				if self._isMousePressed then
					self.controlPressed = control
				end

				if self.mouseOver and control.tooltip then
					self.tooltip.mouseOver = control
					self.tooltip.position = self._mousePos + self.tooltip.offset

					if self.tooltip.timer < self.tooltip.delay then
						self.tooltip.timer = self.tooltip.timer + delta
					else
						self.tooltip.text = control.tooltip
					end
				else
					self.tooltip.mouseOver = nil
					self.tooltip.timer = 0.0
				end
			end

			if control.update then
				control:update( delta )
			end
		end
	end

	if not self.mouseOver then
		self.tooltip.timer = 0.0
	end

	-- RL.SetMouseOffset( mouseOffset )
	-- RL.SetMouseScale( mouseScale )
end

function Gui:drag( control )
	local mousePos = Vector2:tempT( RL.GetMousePosition() )
	local mouseOver = RL.CheckCollisionPointRec( mousePos, control.bounds )

	if not control.disabled and control.draggable and control ~= self.dragging and RL.IsMouseButtonPressed( self.MOUSE_BUTTON )
	and mouseOver and mousePos.y - control.bounds.y <= self.RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT then
		self.grabPos = mousePos - Vector2:temp( control.bounds.x, control.bounds.y )

		if control.callbacks.grab then
			control.callbacks.grab( control )
		end
		self.dragging = control
	end

	if control == self.dragging then
		if not RL.IsMouseButtonDown( self.MOUSE_BUTTON ) then
			self.dragging = nil
		end
		control:setPosition( mousePos - self.grabPos )

		if control.callbacks.drag then
			control.callbacks.drag( control )
		end
	end

	return mouseOver
end

function Gui:drawTooltip()
	local styles = self.tooltipStyles
	local textSize = Vector2:tempT( RL.MeasureTextEx(
		styles.text.font,
		self.tooltip.text,
		styles.text.fontSize,
		styles.text.spacing
	) )
	local borderW = styles.border.width + styles.text.spacing
	local rect = Rectangle:temp(
		self.tooltip.position.x,
		self.tooltip.position.y,
		textSize.x + borderW * 2,
		textSize.y + borderW * 2
	)
	local view = self.view:clone()
	-- If no view size, clamp to window size.
	if view.width == 0 or view.height == 0 then
		local screenSize = Vector2:tempT( RL.GetScreenSize() )
		view.width = screenSize.x
		view.height = screenSize.y
	end

	self:drawRectangle( rect, styles )
	self:drawText( self.tooltip.text, rect, styles )
end

function Gui:draw()
	-- local oldTextEditText = "" -- For checking if text has changed so we can call input callback.

	-- if self.textEdit then
	-- 	oldTextEditText = self.textEditControl.text
	-- end

	-- Set mouse offset if gui is for example embedded to some control.
	-- local mouseOffset = RL.GetMouseOffset()
	-- local mouseScale = RL.GetMouseScale()
	-- RL.SetMouseOffset( self.mouseOffset )
	-- RL.SetMouseScale( self.mouseScale )

	for _, control in ipairs( self.controls ) do
		if control.visible and control.draw ~= nil and self:inView( control ) then
			control:draw()
		end
	end

	if self.locked and self.disabled then
		return
	end

	if self.tooltip.mouseOver ~= nil and self.tooltip.text ~= nil and self.tooltip.delay <= self.tooltip.timer then
		self:drawTooltip()
	end

	-- if not self.locked and not self.disabled and self.tooltip.text ~= nil
	-- and self.controls[ self.tooltip.focused ]:update()
	-- and self.tooltip.delay <= self.tooltip.timer then
	-- 	self:drawTooltip()
	-- end

	-- if self.textEdit and oldTextEditText ~= self.textEditControl.text and self.textEditControl.callbacks.textEdit ~= nil then
	-- 	self.textEditControl.callbacks.textEdit( self.textEditControl )
	-- end

	-- RL.SetMouseOffset( mouseOffset )
	-- RL.SetMouseScale( mouseScale )
end

function Gui:clickedInBounds( bounds )
	return RL.CheckCollisionPointRec( self._mousePressPos, bounds )
end

function Gui:setToTop( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			Util.tableMove( self.controls, i, 1, #self.controls )

			return
		end
	end
end

function Gui:setToBack( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			Util.tableMove( self.controls, i, 1, 1 )

			return
		end
	end
end

function Gui:remove( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			table.remove( self.controls, i )

			return
		end
	end
end

function Gui:getId( control )
	for i, curControl in ipairs( self.controls ) do
		if control == curControl then
			return i
		end
	end
end

function Gui:clear()
	for _, control in ipairs( self.controls ) do
		table.remove( control )
	end
end

function Gui:addControl( control )
	table.insert( self.controls, control )

	return control
end

function Gui:include( controls )
	for name, control in pairs( controls ) do
		self.__index[ name ] = control
		self.__index[ "new"..name ] = function( this, t )
			local c = this:addControl( control:new( this, t ) )

			return c
		end
	end
end

function Gui:setForAllStyles( styles, keyChain, value, makeDeepCopy )
	if keyChain then
		for _, style in pairs( styles ) do
			Util.setNested( style, keyChain, makeDeepCopy and Util.deepCopy( value ) or value )
		end
	else
		for name, _ in pairs( styles ) do
			styles[ name ] = makeDeepCopy and Util.deepCopy( value ) or value
		end
	end
end

-- Draw functions.

function Gui:drawRectangle( rect, styles, crop )
	if styles.drawRectangleCallback then
		styles.drawRectangleCallback( rect, styles, crop )
		return
	end
	if styles.textures then
		self:drawTexturedRectangle( rect, styles, crop )
		return
	end

	crop = crop or styles.base.crop

	if crop then
		RL.BeginScissorMode( crop )
	end

	local drawCallbacks = {
		horizontal = function( r, c ) RL.DrawRectangleGradientH( r, c[1], c[2] ) end,
		vertical = function( r, c ) RL.DrawRectangleGradientV( r, c[1], c[2] ) end,
		vertex = function( r, c ) RL.DrawRectangleGradientEx( r, c[1], c[2], c[3], c[4] ) end,
		normal = function( r, c ) RL.DrawRectangle( r, c ) end,
	}

	if styles.border and 0 < styles.border.width then
		local borderW = styles.border.width
		local innerRect = Rectangle:temp(
			rect.x + borderW,
			rect.y + borderW,
			rect.width - borderW * 2,
			rect.height - borderW * 2
		)
		drawCallbacks[ styles.border.gradient or "normal" ]( rect, styles.border.color )
		drawCallbacks[ styles.base.gradient or "normal" ]( innerRect, styles.base.color )
	else
		drawCallbacks[ styles.base.gradient or "normal" ]( rect, styles.base.color )
	end

	if crop then
		RL.EndScissorMode()
	end
end

function Gui:drawTexturedRectangle( rect, styles, crop )
	crop = crop or styles.base.crop

	if crop then
		RL.BeginScissorMode( crop )
	end

	for _, tex in ipairs( styles.textures ) do
		local dest = tex.dest and tex.dest:addPosition( rect:getPosition() ) or rect

		if tex.nPatchInfo then
			if tex.nPatchRepeat then
				RL.DrawTextureNPatchRepeat(
					tex.texture,
					tex.nPatchInfo,
					dest, { 0, 0 }, 0,
					tex.color
				)
			else
				RL.DrawTextureNPatch(
					tex.texture,
					tex.nPatchInfo,
					dest, { 0, 0 }, 0,
					tex.color
				)
			end
		-- elseif styles.textureGradient then
		-- 	RL.SetShapesTexture( tex.texture, tex.source )
		-- 	-- self:drawRectangle( rect, styles )
		-- 	RL.DrawRectangleGradientEx( dest, tex.color[1], tex.color[2], tex.color[3], tex.color[4] )
		-- 	RL.SetShapesTexture( RL.GetTextureDefault(), { 0, 0, 1, 1 } )
		else
			RL.DrawTexturePro( tex.texture, tex.source, dest, { 0, 0 }, 0, tex.color )
		end
	end

	if crop then
		RL.EndScissorMode()
	end
end

function Gui:drawText( text, bounds, styles, crop )
	crop = crop or styles.text.crop

	local textSize = Vector2:newT( RL.MeasureTextEx( styles.text.font, text, styles.text.fontSize, styles.text.spacing ) )
	local pos = bounds:getPosition()

	if styles.text.alignH == RL.TEXT_ALIGN_MIDDLE then
		pos.x = bounds.x + bounds.width / 2 - textSize.x / 2
	elseif styles.text.alignH == RL.TEXT_ALIGN_RIGHT then
		pos.x = bounds.x + bounds.width - textSize.x
	end

	if styles.text.alignV == RL.TEXT_ALIGN_MIDDLE then
		pos.y = bounds.y + bounds.height / 2 - textSize.y / 2
	elseif styles.text.alignV == RL.TEXT_ALIGN_BOTTOM then
		pos.y = bounds.y + bounds.height - textSize.y
	end

	if styles.text.offset then
		pos:addEq( styles.text.offset )
	end

	pos.x = RL.Round( pos.x )
	pos.y = RL.Round( pos.y )

	if crop then
		RL.BeginScissorMode( crop )
	end

	RL.DrawTextEx( styles.text.font, text, pos, styles.text.fontSize, styles.text.spacing, styles.text.color )

	if crop then
		RL.EndScissorMode()
	end
end

function Gui:drawIcons( bounds, styles )
	local ICON_SIZE = 16

	for _, icon in ipairs( styles.icons ) do
		local iconSize = ICON_SIZE * icon.pixelSize
		local pos = bounds:getPosition()

		if icon.alignH == RL.TEXT_ALIGN_MIDDLE then
			pos.x = bounds.x + bounds.width / 2 - iconSize / 2
		elseif icon.alignH == RL.TEXT_ALIGN_RIGHT then
			pos.x = bounds.x + bounds.width - iconSize
		end

		if icon.alignV == RL.TEXT_ALIGN_MIDDLE then
			pos.y = bounds.y + bounds.height / 2 - iconSize / 2
		elseif icon.alignV == RL.TEXT_ALIGN_BOTTOM then
			pos.y = bounds.y + bounds.height - iconSize
		end

		RL.GuiDrawIcon( icon.iconId, pos + icon.offset, icon.pixelSize, icon.color )
	end
end

return Gui
