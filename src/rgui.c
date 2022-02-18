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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiWindowBox( rect, text ) );

	return 1;
}

/*
> success = RL_GuiPanel( Rectangle bounds )

Panel control, useful to group controls

- Failure return false
- Success return true
*/
int lguiGuiPanel( lua_State *L ) {
	if ( !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiPanel( Rectangle bounds )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangle( L );

	GuiPanel( rect );
	lua_pushboolean( L, true );

	return 1;
}

/*
> view, scroll = RL_GuiScrollPanel( Rectangle bounds, Rectangle content, Vector2 scroll )

Scroll Panel control

- Failure return false
- Success return Rectangle, Vector2
*/
int lguiGuiScrollPanel( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GuiScrollPanel( Rectangle bounds, Rectangle content, Vector2 scroll )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 scroll = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle content = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle bounds = uluaGetRectangle( L );

	uluaPushRectangle( L, GuiScrollPanel( bounds, content, &scroll ) );
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
	Rectangle rect = uluaGetRectangle( L );

	GuiLabel( rect, text );
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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiButton( rect, text ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiToggle( rect, text, checked ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiCheckBox( rect, text, checked ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiTextBox( rect, text, textSize, editMode ) );
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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiTextBoxMulti( rect, text, textSize, editMode ) );
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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiSpinner( rect, text, &value, minValue, maxValue, editMode ) );
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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiValueBox( rect, text, &value, minValue, maxValue, editMode ) );
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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushnumber( L, GuiSlider( rect, textLeft, textRight, value, minValue, maxValue ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushnumber( L, GuiSliderBar( rect, textLeft, textRight, value, minValue, maxValue ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushnumber( L, GuiProgressBar( rect, textLeft, textRight, value, minValue, maxValue ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushinteger( L, GuiScrollBar( rect, value, minValue, maxValue ) );

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
	Rectangle rect = uluaGetRectangle( L );

	lua_pushboolean( L, GuiDropdownBox( rect, text, &active, editMode ) );
	lua_pushinteger( L, active );

	return 2;
}
