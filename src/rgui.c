#include "main.h"
#include "state.h"
#include "rgui.h"
#include "lua_core.h"
#include "rmath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

static inline char* getTextOrNil( lua_State* L, int index ) {
	char* text = NULL;

	if ( lua_isstring( L, index ) ) {
		text = (char*)lua_tostring( L, index );
	}
	return text;
}

/*
## Gui - Global gui state control functions
*/

/*
> RL.GuiEnable()

Enable gui controls (global state)
*/
int lguiGuiEnable( lua_State* L ) {
	GuiEnable();

	return 0;
}

/*
> RL.GuiDisable()

Disable gui controls (global state)
*/
int lguiGuiDisable( lua_State* L ) {
	GuiDisable();

	return 0;
}

/*
> RL.GuiLock()

Lock gui controls (global state)
*/
int lguiGuiLock( lua_State* L ) {
	GuiLock();

	return 0;
}

/*
> RL.GuiUnlock()

Unlock gui controls (global state)
*/
int lguiGuiUnlock( lua_State* L ) {
	GuiUnlock();

	return 0;
}

/*
> locked = RL.GuiIsLocked()

Check if gui is locked (global state)

- Success return bool
*/
int lguiGuiIsLocked( lua_State* L ) {
	lua_pushboolean( L, GuiIsLocked() );

	return 1;
}

/*
> RL.GuiSetAlpha( float alpha )

Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f
*/
int lguiGuiSetAlpha( lua_State* L ) {
	float alpha = luaL_checknumber( L, 1 );

	GuiSetAlpha( alpha );

	return 0;
}

/*
> RL.GuiSetState( int state )

Set gui state (global state)
*/
int lguiGuiSetState( lua_State* L ) {
	int state = luaL_checkinteger( L, 1 );

	GuiSetState( state );

	return 0;
}

/*
> state = RL.GuiGetState()

Get gui state (global state)

- Success return int
*/
int lguiGuiGetState( lua_State* L ) {
	lua_pushinteger( L, GuiGetState() );

	return 1;
}

/*
> RL.GuiSetSliderDragging()

Set guiSliderDragging
*/
int lguiGuiSetSliderDragging( lua_State* L ) {
	bool dragging = lua_toboolean( L, 1 );

	GuiSetSliderDragging( dragging );

	return 0;
}

/*
> isSliderDragging = RL.GuiGetSliderDragging()

Get guiSliderDragging

- Success return bool
*/
int lguiGuiGetSliderDragging( lua_State* L ) {
	lua_pushboolean( L, GuiGetSliderDragging() );

	return 1;
}

/*
> RL.GuiSetSliderActive()

Set guiSliderActive
*/
int lguiGuiSetSliderActive( lua_State* L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );

	GuiSetSliderActive( rect );

	return 0;
}

/*
> isSliderDragging = RL.GuiGetSliderActive()

Get guiSliderActive

- Success return Rectangle
*/
int lguiGuiGetSliderActive( lua_State* L ) {
	uluaPushRectangle( L, GuiGetSliderActive() );

	return 1;
}

/*
## Gui - Font set/get functions
*/

/*
> RL.GuiSetFont( Font font )

Set gui custom font (global state)
*/
int lguiGuiSetFont( lua_State* L ) {
	Font* font = uluaGetFont( L, 1 );

	GuiSetFont( *font );
	// state->guiFont = GuiGetFont();
	state->guiFont = *font;

	return 0;
}

/*
> font = RL.GuiGetFont()

Get gui font (global state). Return as lightuserdata

- Success return Font
*/
int lguiGuiGetFont( lua_State* L ) {
	lua_pushlightuserdata( L, &state->guiFont );

	return 1;
}

/*
## Gui - Style set/get functions
*/

/*
> RL.GuiSetStyle( int control, int property, int value )

Set one style property
*/
int lguiGuiSetStyle( lua_State* L ) {
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
int lguiGuiGetStyle( lua_State* L ) {
	int control = luaL_checkinteger( L, 1 );
	int property = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, GuiGetStyle( control, property ) );

	return 1;
}

/*
## Gui - Styles loading functions
*/

/*
> success = RL.GuiLoadStyle( string fileName )

Load style file over global style variable (.rgs)

- Failure return nil
- Success return true
*/
int lguiGuiLoadStyle( lua_State* L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		GuiLoadStyle( lua_tostring( L, 1 ) );
		state->guiFont = GuiGetFont();
		lua_pushboolean( L, true );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> RL.GuiLoadStyleDefault()

Load style default over global style
*/
int lguiGuiLoadStyleDefault( lua_State* L ) {
	GuiLoadStyleDefault();
	state->guiFont = GuiGetFont();

	return 0;
}

/*
## Gui - Tooltips management functions
*/

/*
> RL.GuiEnableTooltip()

Enable gui tooltips (global state)
*/
int lguiGuiEnableTooltip( lua_State* L ) {
	GuiEnableTooltip();

	return 0;
}

/*
> RL.GuiDisableTooltip()

Disable gui tooltips (global state)
*/
int lguiGuiDisableTooltip( lua_State* L ) {
	GuiDisableTooltip();

	return 0;
}

/*
> RL.GuiSetTooltip( string tooltip )

Set tooltip string
*/
int lguiGuiSetTooltip( lua_State* L ) {
	GuiSetTooltip( luaL_checkstring( L, 1 ) );

	return 0;
}

/*
## Gui - Icons functionality
*/

/*
> text = RL.GuiIconText( int iconId, string|nil text )

Get text with icon id prepended (if supported)

- Success return string
*/
int lguiGuiIconText( lua_State* L ) {
	int iconId = luaL_checkinteger( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushstring( L, GuiIconText( iconId, text ) );

	return 1;
}

/*
> RL.GuiSetIconScale( int scale )

Set icon scale (1 by default)
*/
int lguiGuiSetIconScale( lua_State* L ) {
	unsigned int scale = luaL_checkinteger( L, 1 );

	GuiSetIconScale( scale );

	return 0;
}

/*
> iconsBuffer = RL.GuiGetIcons()

Get raygui icons data in buffer. guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB

- Success return Buffer
*/
int lguiGuiGetIcons( lua_State* L ) {
	const unsigned int dataSize = RAYGUI_ICON_MAX_ICONS * RAYGUI_ICON_DATA_ELEMENTS * sizeof( unsigned int );

	Buffer buffer = {
		.type = BUFFER_UNSIGNED_INT,
		.size = dataSize * sizeof( unsigned int ),
		.data = malloc( dataSize * sizeof( unsigned int ) )
	};
	memcpy( buffer.data, GuiGetIcons(), dataSize );

	uluaPushBuffer( L, buffer );

	return 1;
}

/*
> success = RL.GuiSetIcons( Buffer iconBuffer )

Set raygui icons data in buffer. guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB

- Failure return false
- Success return true
*/
int lguiGuiSetIcons( lua_State* L ) {
	Buffer* buffer = uluaGetBuffer( L, 1 );

	if ( buffer->type != BUFFER_UNSIGNED_INT ) {
		TraceLog( state->logLevelInvalid, "Buffer type must be BUFFER_UNSIGNED_INT" );
		lua_pushboolean( L, false );

		return 1;
	}
	const unsigned int dataSize = RAYGUI_ICON_MAX_ICONS * RAYGUI_ICON_DATA_ELEMENTS * sizeof( unsigned int );
	memcpy( GuiGetIcons(), buffer->data, imin( dataSize, buffer->size ) );

	lua_pushboolean( L, true );

	return 1;
}

/*
> iconNames = RL.GuiLoadIcons( string fileName, bool loadIconsName )

Load raygui icons file (.rgi) into internal icons data

- Failure return nil
- Success return strings{}
*/
int lguiGuiLoadIcons( lua_State* L ) {
	const char* fileName = luaL_checkstring( L, 1 );
	bool loadIconsName = uluaGetBoolean( L, 2 );

	if ( FileExists( fileName ) ) {
		char** iconNames = GuiLoadIcons( fileName, loadIconsName );

		lua_createtable( L, 255, 0 );

		for ( int i = 0; i < 255; i++ ) {
			lua_pushstring( L, iconNames[i] );
			lua_rawseti( L, -2, i + 1 );
			free( iconNames[i] );
		}
		free( iconNames );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon
*/
int lguiGuiDrawIcon( lua_State* L ) {
	int iconId = luaL_checkinteger( L, 1 );
	Vector2 pos = uluaGetVector2( L, 2 );
	int pixelSize = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	GuiDrawIcon( iconId, pos.x, pos.y, pixelSize, color );

	return 0;
}

/*
## Gui - Container/separator controls, useful for controls organization
*/

/*
> result = RL.GuiWindowBox( Rectangle bounds, string|nil title )

Window Box control, shows a window that can be closed

- Success return int
*/
int lguiGuiWindowBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* title = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiWindowBox( bounds, title ) );

	return 1;
}

/*
> result = RL.GuiGroupBox( Rectangle bounds, string|nil text )

Group Box control with text name

- Success return int
*/
int lguiGuiGroupBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiGroupBox( bounds, text ) );

	return 1;
}

/*
> result = RL.GuiLine( Rectangle bounds, string|nil text )

Line separator control, could contain text

- Success return int
*/
int lguiGuiLine( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiLine( bounds, text ) );

	return 1;
}

/*
> result = RL.GuiPanel( Rectangle bounds, string|nil text )

Panel control, useful to group controls

- Success return int
*/
int lguiGuiPanel( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiPanel( bounds, text ) );

	return 1;
}

/*
> result, active = RL.GuiTabBar( Rectangle bounds, string text, int active )

Tab Bar control, returns TAB to be closed or -1

- Success return int, int
*/
int lguiGuiTabBar( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int active = luaL_checkinteger( L, 3 );

	int count = 0;
	const char** text = TextSplit( luaL_checkstring( L, 2 ), ';', &count );

	lua_pushinteger( L, GuiTabBar( bounds, text, count, &active ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> result, scroll, view = RL.GuiScrollPanel( Rectangle bounds, string|nil text, Rectangle content, Vector2 scroll, Rectangle view )

Scroll Panel control

- Success return int, Vector2, Rectangle
*/
int lguiGuiScrollPanel( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	Rectangle content = uluaGetRectangle( L, 3 );
	Vector2 scroll = uluaGetVector2( L, 4 );
	Rectangle view = uluaGetRectangle( L, 5 );

	lua_pushinteger( L, GuiScrollPanel( bounds, text, content, &scroll, &view ) );
	uluaPushVector2( L, scroll );
	uluaPushRectangle( L, view );

	return 3;
}

/*
## Gui - Basic controls set
*/

/*
> result = RL.GuiLabel( Rectangle bounds, string|nil text )

Label control, shows text

- Success return int
*/
int lguiGuiLabel( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiLabel( bounds, text ) );

	return 1;
}

/*
> result = RL.GuiButton( Rectangle bounds, string|nil text )

Button control, returns true when clicked

- Success return int
*/
int lguiGuiButton( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiButton( bounds, text ) );

	return 1;
}

/*
> result = RL.GuiLabelButton( Rectangle bounds, string|nil text )

Label button control, show true when clicked

- Success return int
*/
int lguiGuiLabelButton( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiLabelButton( bounds, text ) );

	return 1;
}

/*
> result, active = RL.GuiToggle( Rectangle bounds, string|nil text, bool active )

Toggle Button control, returns true when active

- Success return int, bool
*/
int lguiGuiToggle( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	bool active = uluaGetBoolean( L, 3 );

	lua_pushinteger( L, GuiToggle( bounds, text, &active ) );
	lua_pushboolean( L, active );

	return 2;
}

/*
> result, active = RL.GuiToggleGroup( Rectangle bounds, string|nil text, int active )

Toggle Group control, returns active toggle index

- Success return int, int
*/
int lguiGuiToggleGroup( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int active = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GuiToggleGroup( bounds, text, &active ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> result, active = RL.GuiToggleSlider( Rectangle bounds, string|nil text, int active )

Toggle Slider control, returns true when clicked

- Success return int, int
*/
int lguiGuiToggleSlider( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int active = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GuiToggleSlider( bounds, text, &active ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> result, checked, textBounds = RL.GuiCheckBox( Rectangle bounds, string|nil text, bool checked )

Check Box control, returns true when active

- Success return bool, Rectangle
*/
int lguiGuiCheckBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	bool checked = uluaGetBoolean( L, 3 );

	Rectangle textBounds = {};
	lua_pushinteger( L, GuiCheckBox( bounds, text, &checked, &textBounds ) );
	lua_pushboolean( L, checked );
	uluaPushRectangle( L, textBounds );

	return 3;
}

/*
> result, active = RL.GuiComboBox( Rectangle bounds, string|nil text, int active )

Combo Box control, returns selected item index

- Success return int, int
*/
int lguiGuiComboBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int active = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, GuiComboBox( bounds, text, &active ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> result, active = RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Success return int, int
*/
int lguiGuiDropdownBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	const char* text = luaL_checkstring( L, 2 );
	int active = luaL_checkinteger( L, 3 );
	bool editMode = uluaGetBoolean( L, 4 );

	lua_pushinteger( L, GuiDropdownBox( bounds, text, &active, editMode ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> result, value, textBounds = RL.GuiSpinner( Rectangle bounds, string|nil text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Success return int, int, Rectangle
*/
int lguiGuiSpinner( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int value = luaL_checkinteger( L, 3 );
	int minValue = luaL_checkinteger( L, 4 );
	int maxValue = luaL_checkinteger( L, 5 );
	bool editMode = uluaGetBoolean( L, 6 );

	Rectangle textBounds = { 0 };
	lua_pushinteger( L, GuiSpinner( bounds, text, &value, minValue, maxValue, editMode, &textBounds ) );
	lua_pushinteger( L, value );
	uluaPushRectangle( L, textBounds );

	return 3;
}

/*
> result, value, textBounds = RL.GuiValueBox( Rectangle bounds, string|nil text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Success return int, int, Rectangle
*/
int lguiGuiValueBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int value = luaL_checkinteger( L, 3 );
	int minValue = luaL_checkinteger( L, 4 );
	int maxValue = luaL_checkinteger( L, 5 );
	bool editMode = uluaGetBoolean( L, 6 );

	Rectangle textBounds = { 0 };
	lua_pushinteger( L, GuiValueBox( bounds, text, &value, minValue, maxValue, editMode, &textBounds ) );
	lua_pushinteger( L, value );
	uluaPushRectangle( L, textBounds );

	return 3;
}

/*
> result, text = RL.GuiTextBox( Rectangle bounds, string text, int bufferSize, bool editMode )

Text Box control, updates input text

- Success return int, string
*/
int lguiGuiTextBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int bufferSize = luaL_checkinteger( L, 3 );
	char text[ bufferSize + 1 ];
	strcpy( text, luaL_checkstring( L, 2 ) );
	bool editMode = uluaGetBoolean( L, 4 );

	lua_pushinteger( L, GuiTextBox( bounds, text, bufferSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> result, value, textLeftBounds, textRightBounds = RL.GuiSlider( Rectangle bounds, string|nil textLeft, string|nil textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Success return int, float, Rectangle, Rectangle
*/
int lguiGuiSlider( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* textLeft = getTextOrNil( L, 2 );
	char* textRight = getTextOrNil( L, 3 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	Rectangle textLeftBounds = { 0 };
	Rectangle textRightBounds = { 0 };
	lua_pushinteger( L, GuiSlider( bounds, textLeft, textRight, &value, minValue, maxValue, &textLeftBounds, &textRightBounds ) );
	lua_pushnumber( L, value );
	uluaPushRectangle( L, textLeftBounds );
	uluaPushRectangle( L, textRightBounds );

	return 4;
}

/*
> result, value, textLeftBounds, textRightBounds = RL.GuiSliderBar( Rectangle bounds, string|nil textLeft, string|nil textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Success return int, float, Rectangle, Rectangle
*/
int lguiGuiSliderBar( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* textLeft = getTextOrNil( L, 2 );
	char* textRight = getTextOrNil( L, 3 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	Rectangle textLeftBounds = { 0 };
	Rectangle textRightBounds = { 0 };
	lua_pushinteger( L, GuiSliderBar( bounds, textLeft, textRight, &value, minValue, maxValue, &textLeftBounds, &textRightBounds ) );
	lua_pushnumber( L, value );
	uluaPushRectangle( L, textLeftBounds );
	uluaPushRectangle( L, textRightBounds );

	return 4;
}

/*
> result, value, textLeftBounds, textRightBounds = RL.GuiProgressBar( Rectangle bounds, string|nil textLeft, string|nil textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Success return int, float, Rectangle, Rectangle
*/
int lguiGuiProgressBar( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* textLeft = getTextOrNil( L, 2 );
	char* textRight = getTextOrNil( L, 3 );
	float value = luaL_checknumber( L, 4 );
	float minValue = luaL_checknumber( L, 5 );
	float maxValue = luaL_checknumber( L, 6 );

	Rectangle textLeftBounds = { 0 };
	Rectangle textRightBounds = { 0 };
	lua_pushinteger( L, GuiProgressBar( bounds, textLeft, textRight, &value, minValue, maxValue, &textLeftBounds, &textRightBounds ) );
	lua_pushnumber( L, value );
	uluaPushRectangle( L, textLeftBounds );
	uluaPushRectangle( L, textRightBounds );

	return 4;
}

/*
> result = RL.GuiStatusBar( Rectangle bounds, string|nil text )

Status Bar control, shows info text

- Success return int
*/
int lguiGuiStatusBar( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiStatusBar( bounds, text ) );

	return 1;
}

/*
> result = RL.GuiDummyRec( Rectangle bounds, string|nil text )

Dummy control for placeholders

- Success return int
*/
int lguiGuiDummyRec( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );

	lua_pushinteger( L, GuiDummyRec( bounds, text ) );

	return 1;
}

/*
> result, mouseCell = RL.GuiGrid( Rectangle bounds, string|nil text, float spacing, int subdivs, Vector2 mouseCell )

Grid control, returns mouse cell position

- Success return int, Vector2
*/
int lguiGuiGrid( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	float spacing = luaL_checknumber( L, 3 );
	int subdivs = luaL_checkinteger( L, 4 );
	Vector2 mouseCell = uluaGetVector2( L, 5 );

	lua_pushinteger( L, GuiGrid( bounds, text, spacing, subdivs, &mouseCell ) );
	uluaPushVector2( L, mouseCell );

	return 2;
}

/*
> value = RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll bar control

- Success return int
*/
int lguiGuiScrollBar( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	int value = luaL_checkinteger( L, 2 );
	int minValue = luaL_checkinteger( L, 3 );
	int maxValue = luaL_checkinteger( L, 4 );

	lua_pushinteger( L, GuiScrollBar( bounds, value, minValue, maxValue ) );

	return 1;
}

/*
## Gui - Advance controls set
*/

/*
> result, scrollIndex, active = RL.GuiListView( Rectangle bounds, string|nil text, int scrollIndex, int active )

List View control, returns selected list item index

- Success return int, int, int
*/
int lguiGuiListView( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	int scrollIndex = luaL_checkinteger( L, 3 );
	int active = luaL_checkinteger( L, 4 );

	lua_pushinteger( L, GuiListView( bounds, text, &scrollIndex, &active ) );
	lua_pushinteger( L, scrollIndex );
	lua_pushinteger( L, active );

	return 3;
}

/*
> result, scrollIndex, active, focus = RL.GuiListViewEx( Rectangle bounds, string text, int scrollIndex, int active, int focus )

List View with extended parameters

- Success return int, int, int, int
*/
int lguiGuiListViewEx( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	const char* text = luaL_checkstring( L, 2 );
	int scrollIndex = luaL_checkinteger( L, 3 );
	int active = luaL_checkinteger( L, 4 );
	int focus = luaL_checkinteger( L, 5 );

	int count = 0;
	const char** textSplits = TextSplit( text, ';', &count );

	lua_pushinteger( L, GuiListViewEx( bounds, textSplits, count, &scrollIndex, &active, &focus ) );
	lua_pushinteger( L, scrollIndex );
	lua_pushinteger( L, active );
	lua_pushinteger( L, focus );

	return 4;
}

/*
> result = RL.GuiMessageBox( Rectangle bounds, string|nil title, string message, string buttons )

Message Box control, displays a message

- Success return int
*/
int lguiGuiMessageBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* title = getTextOrNil( L, 2 );
	const char* message = luaL_checkstring( L, 3 );
	const char* buttons = luaL_checkstring( L, 4 );

	lua_pushinteger( L, GuiMessageBox( bounds, title, message, buttons ) );

	return 1;
}

/*
> result, text, secretViewActive = RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, bool secretViewActive )

Text Input Box control, ask for text, supports secret

- Success return int, string, bool
*/
int lguiGuiTextInputBox( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	const char* title = luaL_checkstring( L, 2 );
	const char* message = luaL_checkstring( L, 3 );
	const char* buttons = luaL_checkstring( L, 4 );
	int textMaxSize = luaL_checkinteger( L, 6 );
	bool secretViewActive = uluaGetBoolean( L, 7 );
	char text[ textMaxSize + 1 ];
	strcpy( text, luaL_checkstring( L, 5 ) );

	lua_pushinteger( L, GuiTextInputBox( bounds, title, message, buttons, text, textMaxSize, &secretViewActive ) );
	lua_pushstring( L, text );
	lua_pushboolean( L, secretViewActive );

	return 3;
}

/*
> result, color = RL.GuiColorPicker( Rectangle bounds, string|nil text, Color color )

Color Picker control (multiple color controls)

- Success return int, Color
*/
int lguiGuiColorPicker( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	Color color = uluaGetColor( L, 3 );

	lua_pushinteger( L, GuiColorPicker( bounds, text, &color ) );
	uluaPushColor( L, color );

	return 2;
}

/*
> result, color = RL.GuiColorPanel( Rectangle bounds, string|nil text, Color color )

Color Panel control

- Success return int, Color
*/
int lguiGuiColorPanel( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	Color color = uluaGetColor( L, 3 );

	lua_pushinteger( L, GuiColorPanel( bounds, text, &color ) );
	uluaPushColor( L, color );

	return 2;
}

/*
> result, alpha = RL.GuiColorBarAlpha( Rectangle bounds, string|nil text, float alpha )

Color Bar Alpha control

- Success return int, float
*/
int lguiGuiColorBarAlpha( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	float alpha = luaL_checknumber( L, 3 );

	lua_pushinteger( L, GuiColorBarAlpha( bounds, text, &alpha ) );
	lua_pushnumber( L, alpha );

	return 2;
}

/*
> result, value = RL.GuiColorBarHue( Rectangle bounds, string|nil text, float value )

Color Bar Hue control

- Success return int, float
*/
int lguiGuiColorBarHue( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	float value = luaL_checknumber( L, 3 );

	lua_pushinteger( L, GuiColorBarHue( bounds, text, &value ) );
	lua_pushnumber( L, value );

	return 2;
}

/*
> result, colorHsv = RL.GuiColorPickerHSV( Rectangle bounds, string|nil text, Vector3 colorHsv )

Color Picker control that avoids conversion to RGB on each call (multiple color controls)

- Success return int, Vector3
*/
int lguiGuiColorPickerHSV( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	Vector3 colorHsv = uluaGetVector3( L, 3 );

	lua_pushinteger( L, GuiColorPickerHSV( bounds, text, &colorHsv ) );
	uluaPushVector3( L, colorHsv );

	return 2;
}

/*
> result, colorHsv = RL.GuiColorPanelHSV( Rectangle bounds, string|nil text, Vector3 colorHsv )

Color Panel control that returns HSV color value, used by GuiColorPickerHSV()

- Success return int, Vector3
*/
int lguiGuiColorPanelHSV( lua_State* L ) {
	Rectangle bounds = uluaGetRectangle( L, 1 );
	char* text = getTextOrNil( L, 2 );
	Vector3 colorHsv = uluaGetVector3( L, 3 );

	lua_pushinteger( L, GuiColorPanelHSV( bounds, text, &colorHsv ) );
	uluaPushVector3( L, colorHsv );

	return 2;
}
