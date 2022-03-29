#include "main.h"
#include "state.h"
#include "rgui.h"
#include "lua_core.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

/*
## Gui - Global
*/

/*
> RL_GuiEnable()

Enable gui controls ( Global state )
*/
int lguiGuiEnable( lua_State *L ) {
	GuiEnable();

	return 1;
}

/*
> RL_GuiDisable()

Disable gui controls ( Global state )
*/
int lguiGuiDisable( lua_State *L ) {
	GuiDisable();

	return 1;
}

/*
> RL_GuiLock()

Lock gui controls ( Global state )
*/
int lguiGuiLock( lua_State *L ) {
	GuiLock();

	return 1;
}

/*
> RL_GuiUnlock()

Unlock gui controls ( Global state )
*/
int lguiGuiUnlock( lua_State *L ) {
	GuiUnlock();

	return 1;
}

/*
## Gui - Font
*/

/*
> success = RL_GuiSetFont( Font font )

Set gui custom font ( Global state )

- Failure return false
- Success return true
*/
int lguiGuiSetFont( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiSetFont( Font font )" );
		lua_pushboolean( L, false );
		return 1;
	}
	GuiSetFont( *state->fonts[ lua_tointeger( L, -1 ) ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Gui - Style
*/

/*
> success = RL_GuiSetStyle( int control, int property, int value )

Set one style property

- Failure return false
- Success return true
*/
int lguiGuiSetStyle( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiSetStyle( int control, int property, int value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	GuiSetStyle( lua_tointeger( L, -3 ), lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> value = RL_GuiGetStyle( int control, int property )

Get one style property

- Failure return false
- Success return int
*/
int lguiGuiGetStyle( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiGetStyle( int control, int property )" );
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushinteger( L, GuiGetStyle( lua_tointeger( L, -2 ), lua_tointeger( L, -1 ) ) );

	return 1;
}

/*
## Gui - Container
*/

/*
> state = RL_GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Failure return nil
- Success return bool
*/
int lguiGuiWindowBox( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiWindowBox( Rectangle bounds, string title )" );
		lua_pushnil( L );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiWindowBox( bounds, text ) );

	return 1;
}

/*
> success = RL_GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name

- Failure return false
- Success return true
*/
int lguiGuiGroupBox( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiGroupBox( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	GuiGroupBox( bounds, text );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_GuiLine( Rectangle bounds, string text )

Line separator control, could contain text

- Failure return false
- Success return true
*/
int lguiGuiLine( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiLine( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	GuiLine( bounds, text );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls

- Failure return false
- Success return true
*/
int lguiGuiPanel( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiPanel( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	GuiPanel( bounds, text );
	lua_pushboolean( L, true );

	return 1;
}

/*
> view, scroll = RL_GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )

Scroll Panel control

- Failure return false
- Success return Rectangle, Vector2
*/
int lguiGuiScrollPanel( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isstring( L, -3 ) || lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 scroll = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle content = uluaGetRectangle( L );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	uluaPushRectangle( L, GuiScrollPanel( bounds, text, content, &scroll ) );
	uluaPushVector2( L, scroll );

	return 2;
}

/*
## Gui - Basic
*/

/*
> success = RL_GuiLabel( Rectangle bounds, string text )

Label control, shows text

- Failure return false
- Success return true
*/
int lguiGuiLabel( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiLabel( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	GuiLabel( bounds, text );
	lua_pushboolean( L, true );

	return 1;
}

/*
> clicked = RL_GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Failure return nil
- Success return boolean
*/
int lguiGuiButton( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiButton( Rectangle bounds, string text )" );
		lua_pushnil( L );
		return 1;
	}
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiButton( bounds, text ) );

	return 1;
}

/*
> active = RL_GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Failure return nil
- Success return boolean
*/
int lguiGuiToggle( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isstring( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiToggle( Rectangle bounds, string text, bool active )" );
		lua_pushnil( L );
		return 1;
	}
	bool checked = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiToggle( bounds, text, checked ) );

	return 1;
}

/*
> index = RL_GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Failure return false
- Success return int
*/
int lguiGuiToggleGroup( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isstring( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiToggleGroup( Rectangle bounds, string text, bool active )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int active = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushinteger( L, GuiToggleGroup( bounds, text, active ) );

	return 1;
}

/*
> active = RL_GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Failure return nil
- Success return boolean
*/
int lguiGuiCheckBox( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isstring( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiCheckBox( Rectangle bounds, string text, bool checked )" );
		lua_pushnil( L );
		return 1;
	}
	bool checked = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiCheckBox( bounds, text, checked ) );

	return 1;
}

/*
> pressed, text = RL_GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Failure return nil
- Success return boolean, string
*/
int lguiGuiTextBox( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isstring( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	bool editMode = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	int textSize = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiTextBox( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, text = RL_GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control with multiple lines

- Failure return nil
- Success return boolean, string
*/
int lguiGuiTextBoxMulti( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isstring( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	bool editMode = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	int textSize = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiTextBoxMulti( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, value = RL_GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Failure return nil
- Success return boolean, int
*/
int lguiGuiSpinner( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isnumber( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	bool editMode = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	int maxValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int minValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int value = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiSpinner( bounds, text, &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> pressed, value = RL_GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Failure return nil
- Success return boolean, int
*/
int lguiGuiValueBox( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isnumber( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	bool editMode = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	int maxValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int minValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int value = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiValueBox( bounds, text, &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> value = RL_GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Failure return nil
- Success return float
*/
int lguiGuiSlider( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isstring( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	float maxValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float minValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float value = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	char textRight[ STRING_LEN ] = { '\0' };
	strcpy( textRight, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char textLeft[ STRING_LEN ] = { '\0' };
	strcpy( textLeft, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushnumber( L, GuiSlider( bounds, textLeft, textRight, value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL_GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Failure return nil
- Success return float
*/
int lguiGuiSliderBar( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isstring( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	float maxValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float minValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float value = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	char textRight[ STRING_LEN ] = { '\0' };
	strcpy( textRight, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char textLeft[ STRING_LEN ] = { '\0' };
	strcpy( textLeft, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushnumber( L, GuiSliderBar( bounds, textLeft, textRight, value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL_GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Failure return nil
- Success return float
*/
int lguiGuiProgressBar( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isstring( L, -4 )
	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	float maxValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float minValue = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float value = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	char textRight[ STRING_LEN ] = { '\0' };
	strcpy( textRight, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char textLeft[ STRING_LEN ] = { '\0' };
	strcpy( textLeft, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushnumber( L, GuiProgressBar( bounds, textLeft, textRight, value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL_GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll Bar control

- Failure return nil
- Success return int
*/
int lguiGuiScrollBar( lua_State *L ) {
	if ( !lua_istable( L, -4 )	|| !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	int maxValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int minValue = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int value = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushinteger( L, GuiScrollBar( bounds, value, minValue, maxValue ) );

	return 1;
}

/*
> pressed, item = RL_GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Failure return nil
- Success return bool, int
*/
int lguiGuiDropdownBox( lua_State *L ) {
	if ( !lua_istable( L, -4 )	|| !lua_isstring( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isboolean( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	bool editMode = lua_toboolean( L, -1 );
	lua_pop( L, 1 );
	int active = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushboolean( L, GuiDropdownBox( bounds, text, &active, editMode ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
## Gui - Advanced
*/

/*
> itemIndex, scrollIndex = RL_GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index and scroll index

- Failure return nil
- Success return int, int
*/
int lguiGuiListView( lua_State *L ) {
	if ( !lua_istable( L, -4 )	|| !lua_isstring( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiListView( Rectangle bounds, string text, int scrollIndex, int active )" );
		lua_pushnil( L );
		return 1;
	}
	int active = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int scrollIndex = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushinteger( L, GuiListView( bounds, text, &scrollIndex, active ) );
	lua_pushinteger( L, scrollIndex );

	return 2;
}

/*
> buttonIndex = RL_GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message, returns button index ( 0 is x button )

- Failure return false
- Success return int
*/
int lguiGuiMessageBox( lua_State *L ) {
	if ( !lua_istable( L, -4 )	|| !lua_isstring( L, -3 ) || !lua_isstring( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiMessageBox( Rectangle bounds, string title, string message, string buttons )" );
		lua_pushboolean( L, false );
		return 1;
	}
	char buttons[ STRING_LEN ] = { '\0' };
	strcpy( buttons, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char message[ STRING_LEN ] = { '\0' };
	strcpy( message, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char title[ STRING_LEN ] = { '\0' };
	strcpy( title, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushinteger( L, GuiMessageBox( bounds, title, message, buttons ) );

	return 1;
}

/*
> buttonIndex, text, secretViewActive = RL_GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )

Text Input Box control, ask for text, supports secret

- Failure return false
- Success return int, string, int
*/
int lguiGuiTextInputBox( lua_State *L ) {
	if ( !lua_istable( L, -7 )	|| !lua_isstring( L, -6 ) || !lua_isstring( L, -5 ) || !lua_isstring( L, -4 ) || !lua_isstring( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int secretViewActive = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int textMaxSize = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char buttons[ STRING_LEN ] = { '\0' };
	strcpy( buttons, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char message[ STRING_LEN ] = { '\0' };
	strcpy( message, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	char title[ STRING_LEN ] = { '\0' };
	strcpy( title, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushinteger( L, GuiTextInputBox( bounds, title, message, buttons, text, textMaxSize, &secretViewActive ) );
	lua_pushstring( L, text );
	lua_pushinteger( L, secretViewActive );

	return 3;
}

/*
> color = RL_GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control ( multiple color controls )

- Failure return false
- Success return Color
*/
int lguiGuiColorPicker( lua_State *L ) {
	if ( !lua_istable( L, -3 )	|| !lua_isstring( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiColorPicker( Rectangle bounds, string text, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	uluaPushColor( L, GuiColorPicker( bounds, text, color ) );

	return 1;
}

/*
> color = RL_GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Failure return false
- Success return Color
*/
int lguiGuiColorPanel( lua_State *L ) {
	if ( !lua_istable( L, -3 )	|| !lua_isstring( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiColorPanel( Rectangle bounds, string text, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	uluaPushColor( L, GuiColorPanel( bounds, text, color ) );

	return 1;
}

/*
> alpha = RL_GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Failure return false
- Success return float
*/
int lguiGuiColorBarAlpha( lua_State *L ) {
	if ( !lua_istable( L, -3 )	|| !lua_isstring( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiColorBarAlpha( Rectangle bounds, string text, float alpha )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float alpha = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushnumber( L, GuiColorBarAlpha( bounds, text, alpha ) );

	return 1;
}

/*
> hue = RL_GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Failure return false
- Success return float
*/
int lguiGuiColorBarHue( lua_State *L ) {
	if ( !lua_istable( L, -3 )	|| !lua_isstring( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiColorBarHue( Rectangle bounds, string text, float value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float value = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	char text[ STRING_LEN ] = { '\0' };
	strcpy( text, lua_tostring( L, -1 ) );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	lua_pushnumber( L, GuiColorBarHue( bounds, text, value ) );

	return 1;
}
