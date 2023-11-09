#include "main.h"
#include "state.h"
#include "rgui.h"
#include "lua_core.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

/*
## Gui - Global gui state control functions
*/

/*
> RL.GuiEnable()

Enable gui controls (global state)
*/
int lguiGuiEnable( lua_State *L ) {
	GuiEnable();

	return 0;
}

/*
> RL.GuiDisable()

Disable gui controls (global state)
*/
int lguiGuiDisable( lua_State *L ) {
	GuiDisable();

	return 0;
}

/*
> RL.GuiLock()

Lock gui controls (global state)
*/
int lguiGuiLock( lua_State *L ) {
	GuiLock();

	return 0;
}

/*
> RL.GuiUnlock()

Unlock gui controls (global state)
*/
int lguiGuiUnlock( lua_State *L ) {
	GuiUnlock();

	return 0;
}

/*
> locked = RL.GuiIsLocked()

Check if gui is locked (global state)

- Success return bool
*/
int lguiGuiIsLocked( lua_State *L ) {
	lua_pushboolean( L, GuiIsLocked() );

	return 0;
}

/*
> RL.GuiFade( float alpha )

Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f
*/
int lguiGuiFade( lua_State *L ) {
	float alpha = luaL_checknumber( L, 1 );

	GuiFade( alpha );

	return 0;
}

/*
> RL.GuiSetState( int state )

Set gui state (global state)
*/
int lguiGuiSetState( lua_State *L ) {
	int state = luaL_checkinteger( L, 1 );

	GuiSetState( state );

	return 0;
}

/*
> state = RL.GuiGetState()

Get gui state (global state)

- Success return int
*/
int lguiGuiGetState( lua_State *L ) {
	lua_pushinteger( L, GuiGetState() );

	return 1;
}

/*
## Gui - Font set/get functions
*/

/*
> RL.GuiSetFont( Font font )

Set gui custom font (global state)
*/
int lguiGuiSetFont( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	GuiSetFont( *font );

	return 0;
}

/*
> font = RL.GuiGetFont()

Get gui custom font (global state)

- Success return Font
*/
int lguiGuiGetFont( lua_State *L ) {
	uluaPushFont( L, GuiGetFont() );

	return 1;
}

/*
## Gui - Style set/get functions
*/

/*
> RL.GuiSetStyle( int control, int property, int value )

Set one style property
*/
int lguiGuiSetStyle( lua_State *L ) {
	int control = luaL_checkinteger( L, 1 );
	int property = luaL_checkinteger( L, 2 );
	int value = luaL_checkinteger( L, 3 );

	GuiSetStyle( control, property, value );

	return 0;
}

/*
> value = RL.GuiGetStyle( int control, int property )

Get one style property

- Success return int
*/
int lguiGuiGetStyle( lua_State *L ) {
	int control = luaL_checkinteger( L, 1 );
	int property = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, GuiGetStyle( control, property ) );

	return 1;
}

/*
## Gui - Container/separator controls, useful for controls organization
*/

/*
> state = RL.GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Success return bool
*/
int lguiGuiWindowBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	lua_pushboolean( L, GuiWindowBox( bounds, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> RL.GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name
*/
int lguiGuiGroupBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiGroupBox( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> RL.GuiLine( Rectangle bounds, string text )

Line separator control, could contain text
*/
int lguiGuiLine( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiLine( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> RL.GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls
*/
int lguiGuiPanel( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiPanel( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> view, scroll = RL.GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )

Scroll Panel control

- Success return Rectangle, Vector2
*/
int lguiGuiScrollPanel( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	Rectangle content = uluaGetRectangle( L, 3 );
	Vector2 scroll = uluaGetVector2( L, 4 );

	uluaPushRectangle( L, GuiScrollPanel( bounds, luaL_checkstring( L, 2 ), content, &scroll ) );
	uluaPushVector2( L, scroll );

	return 2;
}

/*
## Gui - Basic controls set
*/

/*
> RL.GuiLabel( Rectangle bounds, string text )

Label control, shows text
*/
int lguiGuiLabel( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiLabel( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> clicked = RL.GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Success return boolean
*/
int lguiGuiButton( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	lua_pushboolean( L, GuiButton( bounds, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> clicked = RL.GuiLabelButton( Rectangle bounds, string text )

Label button control, show true when clicked

- Success return boolean
*/
int lguiGuiLabelButton( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	lua_pushboolean( L, GuiLabelButton( bounds, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> active = RL.GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Success return boolean
*/
int lguiGuiToggle( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	bool checked = uluaGetBoolean( L, 3 );

	lua_pushboolean( L, GuiToggle( bounds, luaL_checkstring( L, 2 ), checked ) );

	return 1;
}

/*
> index = RL.GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Success return int
*/
int lguiGuiToggleGroup( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int active = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GuiToggleGroup( bounds, luaL_checkstring( L, 2 ), active ) );

	return 1;
}

/*
> active = RL.GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Success return boolean
*/
int lguiGuiCheckBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	bool checked = uluaGetBoolean( L, 3 );

	lua_pushboolean( L, GuiCheckBox( bounds, luaL_checkstring( L, 2 ), checked ) );

	return 1;
}

/*
> active = RL.GuiComboBox( Rectangle bounds, string text, int active )

Combo Box control, returns selected item index

- Success return int
*/
int lguiGuiComboBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int active = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GuiComboBox( bounds, luaL_checkstring( L, 2 ), active ) );

	return 1;
}

/*
> pressed, text = RL.GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Success return boolean, string
*/
int lguiGuiTextBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int textSize = luaL_checkinteger( L, 3 );
	// char text[ STRING_LEN ] = { '\0' };
	char text[ textSize + 1 ];
	strcpy( text, luaL_checkstring( L, 2 ) );
	bool editMode = uluaGetBoolean( L, 4 );

	lua_pushboolean( L, GuiTextBox( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, text = RL.GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control with multiple lines

- Success return boolean, string
*/
int lguiGuiTextBoxMulti( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int textSize = luaL_checkinteger( L, 3 );
	// char text[ STRING_LEN ] = { '\0' };
	char text[ textSize + 1 ];
	strcpy( text, luaL_checkstring( L, 2 ) );
	bool editMode = uluaGetBoolean( L, 4 );

	lua_pushboolean( L, GuiTextBoxMulti( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, value = RL.GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Success return boolean, int
*/
int lguiGuiSpinner( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int value = luaL_checkinteger( L, 3 );
	int minValue = luaL_checkinteger( L, 4 );
	int maxValue = luaL_checkinteger( L, 5 );
	bool editMode = uluaGetBoolean( L, 6 );

	lua_pushboolean( L, GuiSpinner( bounds, luaL_checkstring( L, 2 ), &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> pressed, value = RL.GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Success return boolean, int
*/
int lguiGuiValueBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int value = luaL_checkinteger( L, 3 );
	int minValue = luaL_checkinteger( L, 4 );
	int maxValue = luaL_checkinteger( L, 5 );
	bool editMode = uluaGetBoolean( L, 6 );

	lua_pushboolean( L, GuiValueBox( bounds, luaL_checkstring( L, 2 ), &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> value = RL.GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Success return float
*/
int lguiGuiSlider( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	lua_pushnumber( L, GuiSlider( bounds, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Success return float
*/
int lguiGuiSliderBar( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	lua_pushnumber( L, GuiSliderBar( bounds, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Success return float
*/
int lguiGuiProgressBar( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	lua_pushnumber( L, GuiProgressBar( bounds, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll Bar control

- Success return int
*/
int lguiGuiScrollBar( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int value = luaL_checkinteger( L, 2 );
	int minValue = luaL_checkinteger( L, 3 );
	int maxValue = luaL_checkinteger( L, 4 );

	lua_pushinteger( L, GuiScrollBar( bounds, value, minValue, maxValue ) );

	return 1;
}

/*
> pressed, item = RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Success return bool, int
*/
int lguiGuiDropdownBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int active = luaL_checkinteger( L, 3 );
	bool editMode = uluaGetBoolean( L, 4 );

	lua_pushboolean( L, GuiDropdownBox( bounds, luaL_checkstring( L, 2 ), &active, editMode ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> RL.GuiStatusBar( Rectangle bounds, string text )

Status Bar control, shows info text
*/
int lguiGuiStatusBar( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiStatusBar( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> RL.GuiDummyRec( Rectangle bounds, string text )

Dummy control for placeholders
*/
int lguiGuiDummyRec( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	GuiDummyRec( bounds, luaL_checkstring( L, 2 ) );

	return 0;
}

/*
> cell = RL.GuiGrid( Rectangle bounds, string text, float spacing, int subdivs )

Grid control, returns mouse cell position

- Success return Vector2
*/
int lguiGuiGrid( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float spacing = luaL_checknumber( L, 3 );
	int subdivs = luaL_checkinteger( L, 4 );

	uluaPushVector2( L, GuiGrid( bounds, luaL_checkstring( L, 2 ), spacing, subdivs ) );

	return 1;
}

/*
## Gui - Advance controls set
*/

/*
> itemIndex, scrollIndex = RL.GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index and scroll index

- Success return int, int
*/
int lguiGuiListView( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int scrollIndex = luaL_checkinteger( L, 3 );
	int active = luaL_checkinteger( L, 4 );

	lua_pushinteger( L, GuiListView( bounds, luaL_checkstring( L, 2 ), &scrollIndex, active ) );
	lua_pushinteger( L, scrollIndex );

	return 2;
}

/*
> itemIndex, scrollIndex, focus = RL.GuiListViewEx( Rectangle bounds, string text, int focus, int scrollIndex, int active )

List View with extended parameters, returns selected list item index, scroll index and focus

- Success return int, int, int
*/
int lguiGuiListViewEx( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int focus = luaL_checkinteger( L, 3 );
	int scrollIndex = luaL_checkinteger( L, 4 );
	int active = luaL_checkinteger( L, 5 );
	int count = 0;
	const char **text = GuiTextSplit( luaL_checkstring( L, 2 ), &count, NULL );

	lua_pushinteger( L, GuiListViewEx( bounds, text, count, &focus, &scrollIndex, active ) );
	lua_pushinteger( L, scrollIndex );
	lua_pushinteger( L, focus );

	return 3;
}

/*
> buttonIndex = RL.GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message, returns button index (0 is x button)

- Success return int
*/
int lguiGuiMessageBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );

	lua_pushinteger( L, GuiMessageBox( bounds, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), luaL_checkstring( L, 4 ) ) );

	return 1;
}

/*
> buttonIndex, text, secretViewActive = RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )

Text Input Box control, ask for text, supports secret

- Success return int, string, int
*/
int lguiGuiTextInputBox( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int textMaxSize = luaL_checkinteger( L, 6 );
	int secretViewActive = luaL_checkinteger( L, 7 );
	char text[ textMaxSize + 1 ];
	strcpy( text, luaL_checkstring( L, 5 ) );

	lua_pushinteger( L, GuiTextInputBox( bounds, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), luaL_checkstring( L, 4 ), text, textMaxSize, &secretViewActive ) );
	lua_pushstring( L, text );
	lua_pushinteger( L, secretViewActive );

	return 3;
}

/*
> color = RL.GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control (multiple color controls)

- Success return Color
*/
int lguiGuiColorPicker( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	Color color = uluaGetColor( L, 3 );

	uluaPushColor( L, GuiColorPicker( bounds, luaL_checkstring( L, 2 ), color ) );

	return 1;
}

/*
> color = RL.GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Success return Color
*/
int lguiGuiColorPanel( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	Color color = uluaGetColor( L, 3 );

	uluaPushColor( L, GuiColorPanel( bounds, luaL_checkstring( L, 2 ), color ) );

	return 1;
}

/*
> alpha = RL.GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Success return float
*/
int lguiGuiColorBarAlpha( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float alpha = luaL_checknumber( L, 3 );

	lua_pushnumber( L, GuiColorBarAlpha( bounds, luaL_checkstring( L, 2 ), alpha ) );

	return 1;
}

/*
> hue = RL.GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Success return float
*/
int lguiGuiColorBarHue( lua_State *L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	float value = luaL_checknumber( L, 3 );

	lua_pushnumber( L, GuiColorBarHue( bounds, luaL_checkstring( L, 2 ), value ) );

	return 1;
}

/*
## Gui - Styles loading functions
*/

/*
> success = RL.GuiLoadStyle( string fileName )

Load style file over global style variable (.rgs)

- Failure return false
- Success return true
*/
int lguiGuiLoadStyle( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		GuiLoadStyle( lua_tostring( L, 1 ) );
		lua_pushboolean( L, true );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushboolean( L, false );

	return 1;
}

/*
> RL.GuiLoadStyleDefault()

Load style default over global style
*/
int lguiGuiLoadStyleDefault( lua_State *L ) {
	GuiLoadStyleDefault();

	return 0;
}

/*
## Gui - Icons functionality
*/

/*
> text = RL.GuiIconText( int iconId, string text )

Get text with icon id prepended (if supported)

- Success return string
*/
int lguiGuiIconText( lua_State *L ) {
	int iconId = luaL_checkinteger( L, 1 );

	if ( TextIsEqual( luaL_checkstring( L, 2 ), "" ) ) {
		lua_pushstring( L, GuiIconText( iconId, NULL ) );
	}
	else {
		lua_pushstring( L, GuiIconText( iconId, luaL_checkstring( L, 2 ) ) );
	}

	return 1;
}

/*
> RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon
*/
int lguiGuiDrawIcon( lua_State *L ) {
	int iconId = luaL_checkinteger( L, 1 );
	Vector2 pos = uluaGetVector2( L, 2 );
	int pixelSize = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	GuiDrawIcon( iconId, pos.x, pos.y, pixelSize, color );

	return 0;
}

/*
> RL.GuiSetIconScale( int scale )

Set icon scale (1 by default)
*/
int lguiGuiSetIconScale( lua_State *L ) {
	unsigned int scale = luaL_checkinteger( L, 1 );

	GuiSetIconScale( scale );

	return 0;
}

/*
> RL.GuiSetIconPixel( int iconId, Vector2 pos )

Set icon pixel value
*/
int lguiGuiSetIconPixel( lua_State *L ) {
	int iconId = luaL_checkinteger( L, 1 );
	Vector2 pos = uluaGetVector2( L, 2 );

	GuiSetIconPixel( iconId, pos.x, pos.y );

	return 0;
}

/*
> RL.GuiClearIconPixel( int iconId, Vector2 pos )

Clear icon pixel value
*/
int lguiGuiClearIconPixel( lua_State *L ) {
	int iconId = luaL_checkinteger( L, 1 );
	Vector2 pos = uluaGetVector2( L, 2 );

	GuiClearIconPixel( iconId, pos.x, pos.y );

	return 0;
}

/*
> value = RL.GuiCheckIconPixel( int iconId, Vector2 pos )

Check icon pixel value

- Success return bool
*/
int lguiGuiCheckIconPixel( lua_State *L ) {
	int iconId = luaL_checkinteger( L, 1 );
	Vector2 pos = uluaGetVector2( L, 2 );

	lua_pushboolean( L, GuiCheckIconPixel( iconId, pos.x, pos.y ) );

	return 1;
}
