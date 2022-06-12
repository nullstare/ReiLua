#include "main.h"
#include "shapes.h"
#include "lua_core.h"
#include "textures.h"

/*
## Shapes - Drawing
*/

/*
> success = RL_SetShapesTexture( Texture2D texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

- Failure return false
- Success return true
*/
int lshapesSetShapesTexture( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetShapesTexture( Texture2D texture, Rectangle source )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle source = uluaGetRectangle( L );
	lua_pop( L, 1 );
	size_t texId = lua_tointeger( L, -1 );

	if ( !validSourceTexture( texId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetShapesTexture( *texturesGetSourceTexture( texId ), source );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPixel( Vector2 pos, Color color )

Draw a pixel

- Failure return false
- Success return true
*/
int lshapesDrawPixel( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPixel( Vector2 pos, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 pos = uluaGetVector2( L );

	DrawPixelV( pos, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness

- Failure return false
- Success return true
*/
int lshapesDrawLine( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float thickness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 endPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos = uluaGetVector2( L );

	DrawLineEx( startPos, endPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out

- Failure return false
- Success return true
*/
int lshapesDrawLineBezier( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float thickness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 endPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos = uluaGetVector2( L );

	DrawLineBezier( startPos, endPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true
*/
int lshapesDrawLineBezierQuad( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLineBezier( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float thickness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 controlPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 endPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos = uluaGetVector2( L );

	DrawLineBezierQuad( startPos, endPos, controlPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true
*/
int lshapesDrawLineBezierCubic( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_istable( L, -5 ) || !lua_istable( L, -4 ) ||
		 !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float thickness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 endControlPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startControlPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 endPos = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos = uluaGetVector2( L );

	DrawLineBezierCubic( startPos, endPos, startControlPos, endControlPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawLineStrip( Vector2 points{}, int pointsCount, Color color )

Draw lines sequence

- Failure return false
- Success return true
*/
int lshapesDrawLineStrip( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawLineStrip( Vector2 points{}, int pointsCount, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int pointsCount = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 points[ pointsCount ];

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}

	DrawLineStrip( points, pointsCount, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle

- Failure return false
- Success return true
*/
int lshapesDrawCircle( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircle( Vector2 center, float radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawCircleV( center, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle

- Failure return false
- Success return true
*/
int lshapesDrawCircleSector( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) ||
		 !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawCircleSector( center, radius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline

- Failure return false
- Success return true
*/
int lshapesDrawCircleSectorLines( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) ||
		 !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawCircleSectorLines( center, radius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle

- Failure return false
- Success return true
*/
int lshapesDrawCircleGradient( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color2 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color1 = uluaGetColor( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawCircleGradient( center.x, center.y, radius, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline

- Failure return false
- Success return true
*/
int lshapesDrawCircleLines( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawCircleLines( Vector2 center, float radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawCircleLines( center.x, center.y, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse

- Failure return false
- Success return true
*/
int lshapesDrawEllipse( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float radiusV = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusH = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawEllipse( center.x, center.y, radiusH, radiusV, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline

- Failure return false
- Success return true
*/
int lshapesDrawEllipseLines( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float radiusV = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radiusH = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawEllipseLines( center.x, center.y, radiusH, radiusV, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring

- Failure return false
- Success return true
*/
int lshapesDrawRing( lua_State *L ) {
	if ( !lua_istable( L, -7 ) || !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) ||
		 !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float outerRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float innerRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawRing( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline

- Failure return false
- Success return true
*/
int lshapesDrawRingLines( lua_State *L ) {
	if ( !lua_istable( L, -7 ) || !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) ||
		 !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float endAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float startAngle = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float outerRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float innerRadius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawRingLines( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangle( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangle( Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleRec( rect, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters

- Failure return false
- Success return true
*/
int lshapesDrawRectanglePro( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 origin = uluaGetVector2( L );
	lua_pop( L, 1 );
	Rectangle rec = uluaGetRectangle( L );

	DrawRectanglePro( rec, origin, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientV( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color2 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color1 = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleGradientV( rect.x, rect.y, rect.width, rect.height, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientH( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color2 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color1 = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleGradientH( rect.x, rect.y, rect.width, rect.height, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientEx( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color4 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color3 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color2 = uluaGetColor( L );
	lua_pop( L, 1 );
	Color color1 = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleGradientEx( rect, color1, color2, color3, color4 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline

- Failure return false
- Success return true
*/
int lshapesDrawRectangleLines( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangle( Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleLines( rect.x, rect.y, rect.width, rect.height, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters

- Failure return false
- Success return true
*/
int lshapesDrawRectangleLinesEx( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int lineThick = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleLinesEx( rect, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges

- Failure return false
- Success return true
*/
int lshapesDrawRectangleRounded( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float roundness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleRounded( rect, roundness, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline

- Failure return false
- Success return true
*/
int lshapesDrawRectangleRoundedLines( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int lineThick = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	int segments = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	float roundness = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Rectangle rect = uluaGetRectangle( L );

	DrawRectangleRoundedLines( rect, roundness, segments, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true
*/
int lshapesDrawTriangle( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 v3 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	DrawTriangle( v1, v2, v3, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true
*/
int lshapesDrawTriangleLines( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	Vector2 v3 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 v1 = uluaGetVector2( L );

	DrawTriangleLines( v1, v2, v3, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTriangleFan( Vector2 points{}, int pointsCount, Color color )

Draw a triangle fan defined by points ( first vertex is the center )

- Failure return false
- Success return true
*/
int lshapesDrawTriangleFan( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTriangleFan( Vector2 points{}, int pointsCount, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int pointsCount = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 points[ pointsCount ];

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}

	DrawTriangleFan( points, pointsCount, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawTriangleStrip( Vector2 points{}, int pointsCount, Color color )

Draw a triangle strip defined by points

- Failure return false
- Success return true
*/
int lshapesDrawTriangleStrip( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawTriangleStrip( Vector2 points{}, int pointsCount, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	int pointsCount = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 points[ pointsCount ];

	int t = lua_gettop( L );
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}

	DrawTriangleStrip( points, pointsCount, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon ( Vector version )

- Failure return false
- Success return true
*/
int lshapesDrawPoly( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	int sides = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawPoly( center, sides, radius, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides

- Failure return false
- Success return true
*/
int lshapesDrawPolyLines( lua_State *L ) {
	if ( !lua_istable( L, -5 ) || !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	int sides = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawPolyLines( center, sides, radius, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters

- Failure return false
- Success return true
*/
int lshapesDrawPolyLinesEx( lua_State *L ) {
	if ( !lua_istable( L, -6 ) || !lua_isnumber( L, -5 ) || !lua_isnumber( L, -4 ) ||
		 !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Color color = uluaGetColor( L );
	lua_pop( L, 1 );
	float lineThick = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float rotation = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	int sides = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	DrawPolyLinesEx( center, sides, radius, rotation, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Shapes - Collision
*/

/*
> collision = RL_CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionRecs( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rect1 = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle rect2 = uluaGetRectangle( L );

	lua_pushboolean( L, CheckCollisionRecs( rect1, rect2 ) );

	return 1;
}

/*
> collision = RL_CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionCircles( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )" );
		lua_pushnil( L );
		return 1;
	}
	float radius2 = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	float radius1 = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center1 = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionCircles( center1, radius1, center2, radius2 ) );

	return 1;
}

/*
> collision = RL_CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionCircleRec( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionCircleRec( center, radius, rec ) );

	return 1;
}

/*
> collision = RL_CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointRec( lua_State *L ) {
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionPointRec( Vector2 point, Rectangle rec )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rec = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Vector2 point = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionPointRec( point, rec ) );

	return 1;
}

/*
> collision = RL_CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointCircle( lua_State *L ) {
	if ( !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )" );
		lua_pushnil( L );
		return 1;
	}
	float radius = lua_tonumber( L, -1 );
	lua_pop( L, 1 );
	Vector2 center = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 point = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionPointCircle( point, center, radius ) );

	return 1;
}

/*
> collision = RL_CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointTriangle( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 p3 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 p2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 p1 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 point = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionPointTriangle( point, p1, p2, p3 ) );

	return 1;
}

/*
> collision, position = RL_CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Failure return nil
- Success return bool, Vector2
*/
int lshapesCheckCollisionLines( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 endPos2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 endPos1 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 startPos1 = uluaGetVector2( L );

	Vector2 colPoint = { 0, 0 };

	lua_pushboolean( L, CheckCollisionLines( startPos1, endPos1, startPos2, endPos2, &colPoint ) );
	uluaPushVector2( L, colPoint );

	return 2;
}

/*
> collision = RL_CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointLine( lua_State *L ) {
	if ( !lua_istable( L, -4 ) || !lua_istable( L, -3 ) || !lua_istable( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )" );
		lua_pushnil( L );
		return 1;
	}
	int threshold = lua_tointeger( L, -1 );
	lua_pop( L, 1 );
	Vector2 p2 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 p1 = uluaGetVector2( L );
	lua_pop( L, 1 );
	Vector2 point = uluaGetVector2( L );

	lua_pushboolean( L, CheckCollisionPointLine( point, p1, p2, threshold ) );

	return 1;
}

/*
> rectangle = RL_GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Failure return nil
- Success return Rectangle
*/
int lshapesGetCollisionRec( lua_State *L ) {
	/* Rectangle rec1, Rectangle rec2 */
	if ( !lua_istable( L, -2 ) || !lua_istable( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_GetCollisionRec( Rectangle rec1, Rectangle rec2 )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rec2 = uluaGetRectangle( L );
	lua_pop( L, 1 );
	Rectangle rec1 = uluaGetRectangle( L );

	uluaPushRectangle( L, GetCollisionRec( rec1, rec2 ) );

	return 1;
}
