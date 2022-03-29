#pragma once

/* Global. */
int lguiGuiEnable( lua_State *L );
int lguiGuiDisable( lua_State *L );
int lguiGuiLock( lua_State *L );
int lguiGuiUnlock( lua_State *L );
/* Font. */
int lguiGuiSetFont( lua_State *L );
/* Style */
int lguiGuiSetStyle( lua_State *L );
int lguiGuiGetStyle( lua_State *L );
/* Container. */
int lguiGuiWindowBox( lua_State *L );
int lguiGuiGroupBox( lua_State *L );
int lguiGuiLine( lua_State *L );
int lguiGuiPanel( lua_State *L );
int lguiGuiScrollPanel( lua_State *L );
/* Basic. */
int lguiGuiLabel( lua_State *L );
int lguiGuiButton( lua_State *L );
int lguiGuiToggle( lua_State *L );
int lguiGuiToggleGroup( lua_State *L );
int lguiGuiCheckBox( lua_State *L );
int lguiGuiTextBox( lua_State *L );
int lguiGuiTextBoxMulti( lua_State *L );
int lguiGuiSpinner( lua_State *L );
int lguiGuiValueBox( lua_State *L );
int lguiGuiSlider( lua_State *L );
int lguiGuiSliderBar( lua_State *L );
int lguiGuiProgressBar( lua_State *L );
int lguiGuiScrollBar( lua_State *L );
int lguiGuiDropdownBox( lua_State *L );
/* Advanced. */
int lguiGuiListView( lua_State *L );
int lguiGuiMessageBox( lua_State *L );
int lguiGuiTextInputBox( lua_State *L );
int lguiGuiColorPicker( lua_State *L );
int lguiGuiColorPanel( lua_State *L );
int lguiGuiColorBarAlpha( lua_State *L );
int lguiGuiColorBarHue( lua_State *L );
