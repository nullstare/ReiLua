#include "main.h"
#include "shapes.h"
#include "lua_core.h"
#include "textures.h"

/*
## Shapes - Drawing
*/

/*
> success = RL.SetShapesTexture( Texture2D texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call

- Failure return false
- Success return true
*/
int lshapesSetShapesTexture( lua_State *L ) {
	if ( !isValidTexture( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetShapesTexture( Texture2D texture, Rectangle source )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Texture texture = uluaGetTexture( L, 1 );
	Rectangle source = uluaGetRectangleIndex( L, 2 );

	SetShapesTexture( texture, source );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawPixel( Vector2 pos, Color color )

Draw a pixel

- Failure return false
- Success return true
*/
int lshapesDrawPixel( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawPixel( Vector2 pos, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 pos = uluaGetVector2Index( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	DrawPixelV( pos, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness

- Failure return false
- Success return true
*/
int lshapesDrawLine( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 startPos = uluaGetVector2Index( L, 1 );
	Vector2 endPos = uluaGetVector2Index( L, 2 );
	float thickness = lua_tonumber( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawLineEx( startPos, endPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out

- Failure return false
- Success return true
*/
int lshapesDrawLineBezier( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 startPos = uluaGetVector2Index( L, 1 );
	Vector2 endPos = uluaGetVector2Index( L, 2 );
	float thickness = lua_tonumber( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawLineBezier( startPos, endPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawLineBezierQuad( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true
*/
int lshapesDrawLineBezierQuad( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 startPos = uluaGetVector2Index( L, 1 );
	Vector2 endPos = uluaGetVector2Index( L, 2 );
	Vector2 controlPos = uluaGetVector2Index( L, 3 );
	float thickness = lua_tonumber( L, 4 );
	Color color = uluaGetColorIndex( L, 5 );

	DrawLineBezierQuad( startPos, endPos, controlPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )

Draw line using quadratic bezier curves with a control point

- Failure return false
- Success return true
*/
int lshapesDrawLineBezierCubic( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ||
		 !lua_istable( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawLineBezierCubic( Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thickness, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 startPos = uluaGetVector2Index( L, 1 );
	Vector2 endPos = uluaGetVector2Index( L, 2 );
	Vector2 startControlPos = uluaGetVector2Index( L, 3 );
	Vector2 endControlPos = uluaGetVector2Index( L, 4 );
	float thickness = lua_tonumber( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	DrawLineBezierCubic( startPos, endPos, startControlPos, endControlPos, thickness, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawLineStrip( Vector2{} points, Color color )

Draw lines sequence

- Failure return false
- Success return true
*/
int lshapesDrawLineStrip( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawLineStrip( Vector2{} points, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int pointsCount = uluaGetTableLenIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
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
> success = RL.DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle

- Failure return false
- Success return true
*/
int lshapesDrawCircle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawCircle( Vector2 center, float radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	DrawCircleV( center, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle

- Failure return false
- Success return true
*/
int lshapesDrawCircleSector( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ||
		 !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	float startAngle = lua_tonumber( L, 3 );
	float endAngle = lua_tonumber( L, 4 );
	int segments = lua_tointeger( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	DrawCircleSector( center, radius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline

- Failure return false
- Success return true
*/
int lshapesDrawCircleSectorLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ||
		 !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	float startAngle = lua_tonumber( L, 3 );
	float endAngle = lua_tonumber( L, 4 );
	int segments = lua_tointeger( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	DrawCircleSectorLines( center, radius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle

- Failure return false
- Success return true
*/
int lshapesDrawCircleGradient( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	Color color1 = uluaGetColorIndex( L, 3 );
	Color color2 = uluaGetColorIndex( L, 4 );

	DrawCircleGradient( center.x, center.y, radius, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline

- Failure return false
- Success return true
*/
int lshapesDrawCircleLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawCircleLines( Vector2 center, float radius, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	DrawCircleLines( center.x, center.y, radius, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse

- Failure return false
- Success return true
*/
int lshapesDrawEllipse( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radiusH = lua_tonumber( L, 2 );
	float radiusV = lua_tonumber( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawEllipse( center.x, center.y, radiusH, radiusV, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline

- Failure return false
- Success return true
*/
int lshapesDrawEllipseLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radiusH = lua_tonumber( L, 2 );
	float radiusV = lua_tonumber( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawEllipseLines( center.x, center.y, radiusH, radiusV, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring

- Failure return false
- Success return true
*/
int lshapesDrawRing( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ||
		 !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) || !lua_istable( L, 7 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float innerRadius = lua_tonumber( L, 2 );
	float outerRadius = lua_tonumber( L, 3 );
	float startAngle = lua_tonumber( L, 4 );
	float endAngle = lua_tonumber( L, 5 );
	int segments = lua_tointeger( L, 6 );
	Color color = uluaGetColorIndex( L, 7 );

	DrawRing( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline

- Failure return false
- Success return true
*/
int lshapesDrawRingLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ||
		 !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) || !lua_istable( L, 7 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float innerRadius = lua_tonumber( L, 2 );
	float outerRadius = lua_tonumber( L, 3 );
	float startAngle = lua_tonumber( L, 4 );
	float endAngle = lua_tonumber( L, 5 );
	int segments = lua_tointeger( L, 6 );
	Color color = uluaGetColorIndex( L, 7 );

	DrawRingLines( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangle( Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	DrawRectangleRec( rect, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters

- Failure return false
- Success return true
*/
int lshapesDrawRectanglePro( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rec = uluaGetRectangleIndex( L, 1 );
	Vector2 origin = uluaGetVector2Index( L, 2 );
	float rotation = lua_tonumber( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawRectanglePro( rec, origin, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientV( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	Color color1 = uluaGetColorIndex( L, 2 );
	Color color2 = uluaGetColorIndex( L, 3 );

	DrawRectangleGradientV( rect.x, rect.y, rect.width, rect.height, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientH( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	Color color1 = uluaGetColorIndex( L, 2 );
	Color color2 = uluaGetColorIndex( L, 3 );

	DrawRectangleGradientH( rect.x, rect.y, rect.width, rect.height, color1, color2 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors

- Failure return false
- Success return true
*/
int lshapesDrawRectangleGradientEx( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	Color color1 = uluaGetColorIndex( L, 2 );
	Color color2 = uluaGetColorIndex( L, 3 );
	Color color3 = uluaGetColorIndex( L, 4 );
	Color color4 = uluaGetColorIndex( L, 5 );

	DrawRectangleGradientEx( rect, color1, color2, color3, color4 );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline

- Failure return false
- Success return true
*/
int lshapesDrawRectangleLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleLines( Rectangle rec, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	DrawRectangleLines( rect.x, rect.y, rect.width, rect.height, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters

- Failure return false
- Success return true
*/
int lshapesDrawRectangleLinesEx( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	int lineThick = lua_tointeger( L, 2 );
	Color color = uluaGetColorIndex( L, 3 );

	DrawRectangleLinesEx( rect, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges

- Failure return false
- Success return true
*/
int lshapesDrawRectangleRounded( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	float roundness = lua_tonumber( L, 2 );
	int segments = lua_tointeger( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawRectangleRounded( rect, roundness, segments, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline

- Failure return false
- Success return true
*/
int lshapesDrawRectangleRoundedLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Rectangle rect = uluaGetRectangleIndex( L, 1 );
	float roundness = lua_tonumber( L, 2 );
	int segments = lua_tointeger( L, 3 );
	int lineThick = lua_tointeger( L, 4 );
	Color color = uluaGetColorIndex( L, 5 );

	DrawRectangleRoundedLines( rect, roundness, segments, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true
*/
int lshapesDrawTriangle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );
	Vector2 v3 = uluaGetVector2Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawTriangle( v1, v2, v3, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline ( Vertex in counter-clockwise order! )

- Failure return false
- Success return true
*/
int lshapesDrawTriangleLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 v1 = uluaGetVector2Index( L, 1 );
	Vector2 v2 = uluaGetVector2Index( L, 2 );
	Vector2 v3 = uluaGetVector2Index( L, 3 );
	Color color = uluaGetColorIndex( L, 4 );

	DrawTriangleLines( v1, v2, v3, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawTriangleFan( Vector2{} points, Color color )

Draw a triangle fan defined by points ( first vertex is the center )

- Failure return false
- Success return true
*/
int lshapesDrawTriangleFan( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTriangleFan( Vector2{} points, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int pointsCount = uluaGetTableLenIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
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
> success = RL.DrawTriangleStrip( Vector2{} points, Color color )

Draw a triangle strip defined by points

- Failure return false
- Success return true
*/
int lshapesDrawTriangleStrip( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawTriangleStrip( Vector2{} points, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int pointsCount = uluaGetTableLenIndex( L, 1 );
	Color color = uluaGetColorIndex( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
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
> success = RL.DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon ( Vector version )

- Failure return false
- Success return true
*/
int lshapesDrawPoly( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	int sides = lua_tointeger( L, 2 );
	float radius = lua_tonumber( L, 3 );
	float rotation = lua_tonumber( L, 4 );
	Color color = uluaGetColorIndex( L, 5 );

	DrawPoly( center, sides, radius, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides

- Failure return false
- Success return true
*/
int lshapesDrawPolyLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_istable( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	int sides = lua_tointeger( L, 2 );
	float radius = lua_tonumber( L, 3 );
	float rotation = lua_tonumber( L, 4 );
	Color color = uluaGetColorIndex( L, 5 );

	DrawPolyLines( center, sides, radius, rotation, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters

- Failure return false
- Success return true
*/
int lshapesDrawPolyLinesEx( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ||
		 !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) || !lua_istable( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )" );
		lua_pushboolean( L, false );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	int sides = lua_tointeger( L, 2 );
	float radius = lua_tonumber( L, 3 );
	float rotation = lua_tonumber( L, 4 );
	float lineThick = lua_tonumber( L, 5 );
	Color color = uluaGetColorIndex( L, 6 );

	DrawPolyLinesEx( center, sides, radius, rotation, lineThick, color );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Shapes - Collision
*/

/*
> collision = RL.CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionRecs( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rect1 = uluaGetRectangleIndex( L, 1 );
	Rectangle rect2 = uluaGetRectangleIndex( L, 2 );

	lua_pushboolean( L, CheckCollisionRecs( rect1, rect2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionCircles( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 center1 = uluaGetVector2Index( L, 1 );
	float radius1 = lua_tonumber( L, 2 );
	Vector2 center2 = uluaGetVector2Index( L, 3 );
	float radius2 = lua_tonumber( L, 4 );

	lua_pushboolean( L, CheckCollisionCircles( center1, radius1, center2, radius2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionCircleRec( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 center = uluaGetVector2Index( L, 1 );
	float radius = lua_tonumber( L, 2 );
	Rectangle rec = uluaGetRectangleIndex( L, 3 );

	lua_pushboolean( L, CheckCollisionCircleRec( center, radius, rec ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointRec( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionPointRec( Vector2 point, Rectangle rec )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 point = uluaGetVector2Index( L, 1 );
	Rectangle rec = uluaGetRectangleIndex( L, 2 );

	lua_pushboolean( L, CheckCollisionPointRec( point, rec ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointCircle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 point = uluaGetVector2Index( L, 1 );
	Vector2 center = uluaGetVector2Index( L, 2 );
	float radius = lua_tonumber( L, 3 );

	lua_pushboolean( L, CheckCollisionPointCircle( point, center, radius ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointTriangle( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 point = uluaGetVector2Index( L, 1 );
	Vector2 p1 = uluaGetVector2Index( L, 2 );
	Vector2 p2 = uluaGetVector2Index( L, 3 );
	Vector2 p3 = uluaGetVector2Index( L, 4 );

	lua_pushboolean( L, CheckCollisionPointTriangle( point, p1, p2, p3 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointPoly( Vector2 point, Vector2{} points )

Check if point is within a polygon described by array of vertices

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointPoly( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionPointPoly( Vector2 point, Vector2{} points )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 point = uluaGetVector2Index( L, 1 );
	int pointCount = uluaGetTableLenIndex( L, 2 );
	Vector2 points[ pointCount ];

	/* t = points index. */
	int t = 2, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L );
		i++;
		lua_pop( L, 1 );
	}
	
	lua_pushboolean( L, CheckCollisionPointPoly( point, points, pointCount ) );

	return 1;
}

/*
> collision, position = RL.CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Failure return nil
- Success return bool, Vector2
*/
int lshapesCheckCollisionLines( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_istable( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 startPos1 = uluaGetVector2Index( L, 1 );
	Vector2 endPos1 = uluaGetVector2Index( L, 2 );
	Vector2 startPos2 = uluaGetVector2Index( L, 3 );
	Vector2 endPos2 = uluaGetVector2Index( L, 4 );

	Vector2 colPoint = { 0, 0 };

	lua_pushboolean( L, CheckCollisionLines( startPos1, endPos1, startPos2, endPos2, &colPoint ) );
	uluaPushVector2( L, colPoint );

	return 2;
}

/*
> collision = RL.CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Failure return nil
- Success return bool
*/
int lshapesCheckCollisionPointLine( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) || !lua_istable( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )" );
		lua_pushnil( L );
		return 1;
	}
	Vector2 point = uluaGetVector2Index( L, 1 );
	Vector2 p1 = uluaGetVector2Index( L, 2 );
	Vector2 p2 = uluaGetVector2Index( L, 3 );
	int threshold = lua_tointeger( L, 4 );

	lua_pushboolean( L, CheckCollisionPointLine( point, p1, p2, threshold ) );

	return 1;
}

/*
> rectangle = RL.GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Failure return nil
- Success return Rectangle
*/
int lshapesGetCollisionRec( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_istable( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.GetCollisionRec( Rectangle rec1, Rectangle rec2 )" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle rec1 = uluaGetRectangleIndex( L, 1 );
	Rectangle rec2 = uluaGetRectangleIndex( L, 2 );

	uluaPushRectangle( L, GetCollisionRec( rec1, rec2 ) );

	return 1;
}
