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
> RL.GuiEnable()

Enable gui controls ( global state )
*/
int lguiGuiEnable( lua_State *L ) {
	GuiEnable();

	return 0;
}

/*
> RL.GuiDisable()

Disable gui controls ( global state )
*/
int lguiGuiDisable( lua_State *L ) {
	GuiDisable();

	return 0;
}

/*
> RL.GuiLock()

Lock gui controls ( global state )
*/
int lguiGuiLock( lua_State *L ) {
	GuiLock();

	return 0;
}

/*
> RL.GuiUnlock()

Unlock gui controls ( global state )
*/
int lguiGuiUnlock( lua_State *L ) {
	GuiUnlock();

	return 0;
}

/*
> locked = RL.GuiIsLocked()

Check if gui is locked ( global state )

- Success return bool
*/
int lguiGuiIsLocked( lua_State *L ) {
	lua_pushboolean( L, GuiIsLocked() );

	return 0;
}

/*
> success = RL.GuiFade( float alpha )

Set gui controls alpha ( global state ), alpha goes from 0.0f to 1.0f

- Failure return false
- Success return true
*/
int lguiGuiFade( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiFade( float alpha )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float alpha = lua_tonumber( L, 1 );

	GuiFade( alpha );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiSetState( int state )

Set gui state ( global state )

- Failure return false
- Success return true
*/
int lguiGuiSetState( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSetState( int state )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int state = lua_tointeger( L, 1 );

	GuiSetState( state );
	lua_pushboolean( L, true );

	return 1;
}

/*
> state = RL.GuiGetState()

Get gui state ( global state )

- Success return int
*/
int lguiGuiGetState( lua_State *L ) {
	lua_pushinteger( L, GuiGetState() );

	return 1;
}

/*
## Gui - Font
*/

/*
> success = RL.GuiSetFont( Font font )

Set gui custom font ( global state )

- Failure return false
- Success return true
*/
int lguiGuiSetFont( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSetFont( Font font )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t fontId = lua_tointeger( L, 1 );
	state->guiFont = fontId;

	GuiSetFont( *state->fonts[ fontId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> font = RL.GuiGetFont()

Get gui custom font ( global state )

- Success return int
*/
int lguiGuiGetFont( lua_State *L ) {
	lua_pushinteger( L, state->guiFont );

	return 1;
}

/*
## Gui - Style
*/

/*
> success = RL.GuiSetStyle( int control, int property, int value )

Set one style property

- Failure return false
- Success return true
*/
int lguiGuiSetStyle( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSetStyle( int control, int property, int value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int control = lua_tointeger( L, 1 );
	int property = lua_tointeger( L, 2 );
	int value = lua_tointeger( L, 3 );

	GuiSetStyle( control, property, value );
	lua_pushboolean( L, true );

	return 1;
}

/*
> value = RL.GuiGetStyle( int control, int property )

Get one style property

- Failure return false
- Success return int
*/
int lguiGuiGetStyle( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiGetStyle( int control, int property )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int control = lua_tointeger( L, 1 );
	int property = lua_tointeger( L, 2 );

	lua_pushinteger( L, GuiGetStyle( control, property ) );

	return 1;
}

/*
> success = RL.GuiLoadStyle( string fileName )

Load style file over global style variable ( .rgs )

- Failure return false
- Success return true
*/
int lguiGuiLoadStyle( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiLoadStyle( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}

	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		GuiLoadStyle( lua_tostring( L, 1 ) );
		lua_pushboolean( L, true );
		return 1;
	}
	else {
		lua_pushboolean( L, false );
		return 1;
	}

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
## Gui - Container
*/

/*
> state = RL.GuiWindowBox( Rectangle bounds, string title )

Window Box control, shows a window that can be closed

- Failure return nil
- Success return bool
*/
int lguiGuiWindowBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiWindowBox( Rectangle bounds, string title )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	lua_pushboolean( L, GuiWindowBox( bounds, lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.GuiGroupBox( Rectangle bounds, string text )

Group Box control with text name

- Failure return false
- Success return true
*/
int lguiGuiGroupBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiGroupBox( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiGroupBox( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiLine( Rectangle bounds, string text )

Line separator control, could contain text

- Failure return false
- Success return true
*/
int lguiGuiLine( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiLine( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiLine( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiPanel( Rectangle bounds, string text )

Panel control, useful to group controls

- Failure return false
- Success return true
*/
int lguiGuiPanel( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiPanel( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiPanel( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> view, scroll = RL.GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )

Scroll Panel control

- Failure return false
- Success return Rectangle, Vector2
*/
int lguiGuiScrollPanel( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiScrollPanel( Rectangle bounds, string text, Rectangle content, Vector2 scroll )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	Rectangle content = uluaGetRectangleIndex( L, 3 );
	Vector2 scroll = uluaGetVector2Index( L, 4 );

	uluaPushRectangle( L, GuiScrollPanel( bounds, lua_tostring( L, 2 ), content, &scroll ) );
	uluaPushVector2( L, scroll );

	return 2;
}

/*
## Gui - Basic
*/

/*
> success = RL.GuiLabel( Rectangle bounds, string text )

Label control, shows text

- Failure return false
- Success return true
*/
int lguiGuiLabel( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiLabel( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiLabel( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> clicked = RL.GuiButton( Rectangle bounds, string text )

Button control, returns true when clicked

- Failure return nil
- Success return boolean
*/
int lguiGuiButton( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiButton( Rectangle bounds, string text )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	lua_pushboolean( L, GuiButton( bounds, lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> clicked = RL.GuiLabelButton( Rectangle bounds, string text )

Label button control, show true when clicked

- Failure return nil
- Success return boolean
*/
int lguiGuiLabelButton( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiLabelButton( Rectangle bounds, string text )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	lua_pushboolean( L, GuiLabelButton( bounds, lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> active = RL.GuiToggle( Rectangle bounds, string text, bool active )

Toggle Button control, returns true when active

- Failure return nil
- Success return boolean
*/
int lguiGuiToggle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiToggle( Rectangle bounds, string text, bool active )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	bool checked = lua_toboolean( L, 3 );

	lua_pushboolean( L, GuiToggle( bounds, lua_tostring( L, 2 ), checked ) );

	return 1;
}

/*
> index = RL.GuiToggleGroup( Rectangle bounds, string text, int active )

Toggle Group control, returns active toggle index

- Failure return false
- Success return int
*/
int lguiGuiToggleGroup( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiToggleGroup( Rectangle bounds, string text, bool active )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int active = lua_tointeger( L, 3 );

	lua_pushinteger( L, GuiToggleGroup( bounds, lua_tostring( L, 2 ), active ) );

	return 1;
}

/*
> active = RL.GuiCheckBox( Rectangle bounds, string text, bool checked )

Check Box control, returns true when active

- Failure return nil
- Success return boolean
*/
int lguiGuiCheckBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isboolean( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiCheckBox( Rectangle bounds, string text, bool checked )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	bool checked = lua_toboolean( L, 3 );

	lua_pushboolean( L, GuiCheckBox( bounds, lua_tostring( L, 2 ), checked ) );

	return 1;
}

/*
> active = RL.GuiComboBox( Rectangle bounds, string text, int active )

Combo Box control, returns selected item index

- Failure return nil
- Success return int
*/
int lguiGuiComboBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiComboBox( Rectangle bounds, string text, int active )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int active = lua_tointeger( L, 3 );

	lua_pushinteger( L, GuiComboBox( bounds, lua_tostring( L, 2 ), active ) );

	return 1;
}

/*
> pressed, text = RL.GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control, updates input text

- Failure return nil
- Success return boolean, string
*/
int lguiGuiTextBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isboolean( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiTextBox( Rectangle bounds, string text, int textSize, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int textSize = lua_tointeger( L, 3 );
	// char text[ STRING_LEN ] = { '\0' };
	char text[ textSize + 1 ];
	strcpy( text, lua_tostring( L, 2 ) );
	bool editMode = lua_toboolean( L, 4 );

	lua_pushboolean( L, GuiTextBox( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, text = RL.GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )

Text Box control with multiple lines

- Failure return nil
- Success return boolean, string
*/
int lguiGuiTextBoxMulti( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isboolean( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiTextBoxMulti( Rectangle bounds, string text, int textSize, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int textSize = lua_tointeger( L, 3 );
	// char text[ STRING_LEN ] = { '\0' };
	char text[ textSize + 1 ];
	strcpy( text, lua_tostring( L, 2 ) );
	bool editMode = lua_toboolean( L, 4 );

	lua_pushboolean( L, GuiTextBoxMulti( bounds, text, textSize, editMode ) );
	lua_pushstring( L, text );

	return 2;
}

/*
> pressed, value = RL.GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Spinner control, returns selected value

- Failure return nil
- Success return boolean, int
*/
int lguiGuiSpinner( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isboolean( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSpinner( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int value = lua_tointeger( L, 3 );
	int minValue = lua_tointeger( L, 4 );
	int maxValue = lua_tointeger( L, 5 );
	bool editMode = lua_toboolean( L, 6 );

	lua_pushboolean( L, GuiSpinner( bounds, lua_tostring( L, 2 ), &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> pressed, value = RL.GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )

Value Box control, updates input text with numbers

- Failure return nil
- Success return boolean, int
*/
int lguiGuiValueBox( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isboolean( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiValueBox( Rectangle bounds, string text, int value, int minValue, int maxValue, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int value = lua_tointeger( L, 3 );
	int minValue = lua_tointeger( L, 4 );
	int maxValue = lua_tointeger( L, 5 );
	bool editMode = lua_toboolean( L, 6 );

	lua_pushboolean( L, GuiValueBox( bounds, lua_tostring( L, 2 ), &value, minValue, maxValue, editMode ) );
	lua_pushinteger( L, value );

	return 2;
}

/*
> value = RL.GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider control, returns selected value

- Failure return nil
- Success return float
*/
int lguiGuiSlider( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isstring( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSlider( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float value = lua_tonumber( L, 4 );
	float minValue = lua_tonumber( L, 5 );
	float maxValue = lua_tonumber( L, 6 );

	lua_pushnumber( L, GuiSlider( bounds, lua_tostring( L, 2 ), lua_tostring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Slider Bar control, returns selected value

- Failure return nil
- Success return float
*/
int lguiGuiSliderBar( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isstring( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSliderBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float value = lua_tonumber( L, 4 );
	float minValue = lua_tonumber( L, 5 );
	float maxValue = lua_tonumber( L, 6 );

	lua_pushnumber( L, GuiSliderBar( bounds, lua_tostring( L, 2 ), lua_tostring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )

Progress Bar control, shows current progress value

- Failure return nil
- Success return float
*/
int lguiGuiProgressBar( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isstring( L, 2 ) || !lua_isstring( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiProgressBar( Rectangle bounds, string textLeft, string textRight, float value, float minValue, float maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float value = lua_tonumber( L, 4 );
	float minValue = lua_tonumber( L, 5 );
	float maxValue = lua_tonumber( L, 6 );

	lua_pushnumber( L, GuiProgressBar( bounds, lua_tostring( L, 2 ), lua_tostring( L, 3 ), value, minValue, maxValue ) );

	return 1;
}

/*
> value = RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )

Scroll Bar control

- Failure return nil
- Success return int
*/
int lguiGuiScrollBar( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiScrollBar( Rectangle bounds, int value, int minValue, int maxValue )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int value = lua_tointeger( L, 2 );
	int minValue = lua_tointeger( L, 3 );
	int maxValue = lua_tointeger( L, 4 );

	lua_pushinteger( L, GuiScrollBar( bounds, value, minValue, maxValue ) );

	return 1;
}

/*
> pressed, item = RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )

Dropdown Box control, returns selected item

- Failure return nil
- Success return bool, int
*/
int lguiGuiDropdownBox( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isboolean( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiDropdownBox( Rectangle bounds, string text, int active, bool editMode )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int active = lua_tointeger( L, 3 );
	bool editMode = lua_toboolean( L, 4 );

	lua_pushboolean( L, GuiDropdownBox( bounds, lua_tostring( L, 2 ), &active, editMode ) );
	lua_pushinteger( L, active );

	return 2;
}

/*
> success = RL.GuiStatusBar( Rectangle bounds, string text )

Status Bar control, shows info text

- Failure return false
- Success return true
*/
int lguiGuiStatusBar( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiStatusBar( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiStatusBar( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiDummyRec( Rectangle bounds, string text )

Dummy control for placeholders

- Failure return false
- Success return true
*/
int lguiGuiDummyRec( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiDummyRec( Rectangle bounds, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	GuiDummyRec( bounds, lua_tostring( L, 2 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> cell = RL.GuiGrid( Rectangle bounds, string text, float spacing, int subdivs )

Grid control, returns mouse cell position

- Failure return false
- Success return Vector2
*/
int lguiGuiGrid( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiGrid( Rectangle bounds, string text, float spacing, int subdivs )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float spacing = lua_tonumber( L, 3 );
	int subdivs = lua_tointeger( L, 4 );

	uluaPushVector2( L, GuiGrid( bounds, lua_tostring( L, 2 ), spacing, subdivs ) );

	return 1;
}

/*
## Gui - Advanced
*/

/*
> itemIndex, scrollIndex = RL.GuiListView( Rectangle bounds, string text, int scrollIndex, int active )

List View control, returns selected list item index and scroll index

- Failure return nil
- Success return int, int
*/
int lguiGuiListView( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiListView( Rectangle bounds, string text, int scrollIndex, int active )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int scrollIndex = lua_tointeger( L, 3 );
	int active = lua_tointeger( L, 4 );

	lua_pushinteger( L, GuiListView( bounds, lua_tostring( L, 2 ), &scrollIndex, active ) );
	lua_pushinteger( L, scrollIndex );

	return 2;
}

/*
> itemIndex, scrollIndex, focus = RL.GuiListViewEx( Rectangle bounds, string text, int focus, int scrollIndex, int active )

List View with extended parameters, returns selected list item index, scroll index and focus

- Failure return nil
- Success return int, int, int
*/
int lguiGuiListViewEx( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiListViewEx( Rectangle bounds, string text, int focus, int scrollIndex, int active )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int focus = lua_tointeger( L, 3 );
	int scrollIndex = lua_tointeger( L, 4 );
	int active = lua_tointeger( L, 5 );
	int count = 0;
	const char **text = GuiTextSplit( lua_tostring( L, 2 ), &count, NULL );

	lua_pushinteger( L, GuiListViewEx( bounds, text, count, &focus, &scrollIndex, active ) );
	lua_pushinteger( L, scrollIndex );
	lua_pushinteger( L, focus );

	return 3;
}

/*
> buttonIndex = RL.GuiMessageBox( Rectangle bounds, string title, string message, string buttons )

Message Box control, displays a message, returns button index ( 0 is x button )

- Failure return false
- Success return int
*/
int lguiGuiMessageBox( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isstring( L, 3 ) || !lua_isstring( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiMessageBox( Rectangle bounds, string title, string message, string buttons )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );

	lua_pushinteger( L, GuiMessageBox( bounds, lua_tostring( L, 2 ), lua_tostring( L, 3 ), lua_tostring( L, 4 ) ) );

	return 1;
}

/*
> buttonIndex, text, secretViewActive = RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )

Text Input Box control, ask for text, supports secret

- Failure return false
- Success return int, string, int
*/
int lguiGuiTextInputBox( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isstring( L, 3 ) || !lua_isstring( L, 4 )
	|| !lua_isstring( L, 5 ) || !lua_isnumber( L, 6 ) || !lua_isnumber( L, 7 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiTextInputBox( Rectangle bounds, string title, string message, string buttons, string text, int textMaxSize, int secretViewActive )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	int textMaxSize = lua_tointeger( L, 6 );
	int secretViewActive = lua_tointeger( L, 7 );
	char text[ textMaxSize + 1 ];
	strcpy( text, lua_tostring( L, 5 ) );

	lua_pushinteger( L, GuiTextInputBox( bounds, lua_tostring( L, 2 ), lua_tostring( L, 3 ), lua_tostring( L, 4 ), text, textMaxSize, &secretViewActive ) );
	lua_pushstring( L, text );
	lua_pushinteger( L, secretViewActive );

	return 3;
}

/*
> color = RL.GuiColorPicker( Rectangle bounds, string text, Color color )

Color Picker control ( multiple color controls )

- Failure return false
- Success return Color
*/
int lguiGuiColorPicker( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiColorPicker( Rectangle bounds, string text, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 3 );

	uluaPushColor( L, GuiColorPicker( bounds, lua_tostring( L, 2 ), color ) );

	return 1;
}

/*
> color = RL.GuiColorPanel( Rectangle bounds, string text, Color color )

Color Panel control

- Failure return false
- Success return Color
*/
int lguiGuiColorPanel( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiColorPanel( Rectangle bounds, string text, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 3 );

	uluaPushColor( L, GuiColorPanel( bounds, lua_tostring( L, 2 ), color ) );

	return 1;
}

/*
> alpha = RL.GuiColorBarAlpha( Rectangle bounds, string text, float alpha )

Color Bar Alpha control

- Failure return false
- Success return float
*/
int lguiGuiColorBarAlpha( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiColorBarAlpha( Rectangle bounds, string text, float alpha )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float alpha = lua_tonumber( L, 3 );

	lua_pushnumber( L, GuiColorBarAlpha( bounds, lua_tostring( L, 2 ), alpha ) );

	return 1;
}

/*
> hue = RL.GuiColorBarHue( Rectangle bounds, string text, float value )

Color Bar Hue control

- Failure return false
- Success return float
*/
int lguiGuiColorBarHue( lua_State *L ) {
	if ( !lua_istable( L, 1 )	|| !lua_isstring( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiColorBarHue( Rectangle bounds, string text, float value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle bounds = uluaGetRectangleIndex( L, 1 );
	float value = lua_tonumber( L, 3 );

	lua_pushnumber( L, GuiColorBarHue( bounds, lua_tostring( L, 2 ), value ) );

	return 1;
}

/*
## Gui - Icons
*/

/*
> text = RL.GuiIconText( int iconId, string text )

Get text with icon id prepended ( if supported )

- Failure return false
- Success return string
*/
int lguiGuiIconText( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiIconText( int iconId, string text )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int iconId = lua_tointeger( L, 1 );

	if ( TextIsEqual( lua_tostring( L, 2 ), "" ) ) {
		lua_pushstring( L, GuiIconText( iconId, NULL ) );
	}
	else {
		lua_pushstring( L, GuiIconText( iconId, lua_tostring( L, 2 ) ) );
	}

	return 1;
}

/*
> success = RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )

Draw icon

- Failure return false
- Success return true
*/
int lguiGuiDrawIcon( lua_State *L ) {
	if ( !lua_isnumber( L, 1 )	|| !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiDrawIcon( int iconId, Vector2 pos, int pixelSize, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int iconId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );
	int pixelSize = lua_tointeger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	GuiDrawIcon( iconId, pos.x, pos.y, pixelSize, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiSetIconScale( int scale )

Set icon scale ( 1 by default )

- Failure return false
- Success return true
*/
int lguiGuiSetIconScale( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSetIconScale( int scale )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int scale = lua_tointeger( L, 1 );

	GuiSetIconScale( scale );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiSetIconPixel( int iconId, Vector2 pos )

Set icon pixel value

- Failure return false
- Success return true
*/
int lguiGuiSetIconPixel( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiSetIconPixel( int iconId, Vector2 pos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int iconId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );

	GuiSetIconPixel( iconId, pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.GuiClearIconPixel( int iconId, Vector2 pos )

Clear icon pixel value

- Failure return false
- Success return true
*/
int lguiGuiClearIconPixel( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiClearIconPixel( int iconId, Vector2 pos )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int iconId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );

	GuiClearIconPixel( iconId, pos.x, pos.y );
	lua_pushboolean( L, true );

	return 1;
}

/*
> value = RL.GuiCheckIconPixel( int iconId, Vector2 pos )

Check icon pixel value

- Failure return nil
- Success return bool
*/
int lguiGuiCheckIconPixel( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GuiCheckIconPixel( int iconId, Vector2 pos )" );
		lua_pushnil( L );
		return 1;
	}
	int iconId = lua_tointeger( L, 1 );
	Vector2 pos = uluaGetVector2Index( L, 2 );

	lua_pushboolean( L, GuiCheckIconPixel( iconId, pos.x, pos.y ) );

	return 1;
}
