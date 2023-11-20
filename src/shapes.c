#include "main.h"
#include "state.h"
#include "shapes.h"
#include "lua_core.h"
#include "textures.h"

static inline void getVector2Array( lua_State *L, int index, Vector2 points[] ) {
	int t = index, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
}

/*
## Shapes - Basic shapes drawing functions
*/

/*
> RL.SetShapesTexture( Texture texture, Rectangle source )

Set texture and rectangle to be used on shapes drawing
NOTE: It can be useful when using basic shapes and one single font,
defining a font char white rectangle would allow drawing everything in a single draw call
*/
int lshapesSetShapesTexture( lua_State *L ) {
	Texture *texture = uluaGetTexture( L, 1 );
	Rectangle source = uluaGetRectangle( L, 2 );

	SetShapesTexture( *texture, source );

	return 0;
}

/*
> RL.DrawPixel( Vector2 pos, Color color )

Draw a pixel
*/
int lshapesDrawPixel( lua_State *L ) {
	Vector2 pos = uluaGetVector2( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawPixelV( pos, color );

	return 0;
}

/*
> RL.DrawLine( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line defining thickness
*/
int lshapesDrawLine( lua_State *L ) {
	Vector2 startPos = uluaGetVector2( L, 1 );
	Vector2 endPos = uluaGetVector2( L, 2 );
	float thickness = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawLineEx( startPos, endPos, thickness, color );

	return 0;
}

/*
> RL.DrawLineStrip( Vector2{} points, Color color )

Draw lines sequence
*/
int lshapesDrawLineStrip( lua_State *L ) {
	int pointsCount = uluaGetTableLen( L, 1 );
	Color color = uluaGetColor( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	DrawLineStrip( points, pointsCount, color );

	return 0;
}

/*
> RL.DrawLineBezier( Vector2 startPos, Vector2 endPos, float thickness, Color color )

Draw a line using cubic-bezier curves in-out
*/
int lshapesDrawLineBezier( lua_State *L ) {
	Vector2 startPos = uluaGetVector2( L, 1 );
	Vector2 endPos = uluaGetVector2( L, 2 );
	float thickness = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawLineBezier( startPos, endPos, thickness, color );

	return 0;
}

/*
> RL.DrawCircle( Vector2 center, float radius, Color color )

Draw a color-filled circle
*/
int lshapesDrawCircle( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawCircleV( center, radius, color );

	return 0;
}

/*
> RL.DrawCircleSector( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw a piece of a circle
*/
int lshapesDrawCircleSector( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	float startAngle = luaL_checknumber( L, 3 );
	float endAngle = luaL_checknumber( L, 4 );
	int segments = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCircleSector( center, radius, startAngle, endAngle, segments, color );

	return 0;
}

/*
> RL.DrawCircleSectorLines( Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color )

Draw circle sector outline
*/
int lshapesDrawCircleSectorLines( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	float startAngle = luaL_checknumber( L, 3 );
	float endAngle = luaL_checknumber( L, 4 );
	int segments = luaL_checkinteger( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawCircleSectorLines( center, radius, startAngle, endAngle, segments, color );

	return 0;
}

/*
> RL.DrawCircleGradient( Vector2 center, float radius, Color color1, Color color2 )

Draw a gradient-filled circle
*/
int lshapesDrawCircleGradient( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Color color1 = uluaGetColor( L, 3 );
	Color color2 = uluaGetColor( L, 4 );

	DrawCircleGradient( center.x, center.y, radius, color1, color2 );

	return 0;
}

/*
> RL.DrawCircleLines( Vector2 center, float radius, Color color )

Draw circle outline
*/
int lshapesDrawCircleLines( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawCircleLines( center.x, center.y, radius, color );

	return 0;
}

/*
> RL.DrawEllipse( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse
*/
int lshapesDrawEllipse( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radiusH = luaL_checknumber( L, 2 );
	float radiusV = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawEllipse( center.x, center.y, radiusH, radiusV, color );

	return 0;
}

/*
> RL.DrawEllipseLines( Vector2 center, float radiusH, float radiusV, Color color )

Draw ellipse outline
*/
int lshapesDrawEllipseLines( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radiusH = luaL_checknumber( L, 2 );
	float radiusV = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawEllipseLines( center.x, center.y, radiusH, radiusV, color );

	return 0;
}

/*
> RL.DrawRing( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring
*/
int lshapesDrawRing( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float innerRadius = luaL_checknumber( L, 2 );
	float outerRadius = luaL_checknumber( L, 3 );
	float startAngle = luaL_checknumber( L, 4 );
	float endAngle = luaL_checknumber( L, 5 );
	int segments = luaL_checkinteger( L, 6 );
	Color color = uluaGetColor( L, 7 );

	DrawRing( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );

	return 0;
}

/*
> RL.DrawRingLines( Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color )

Draw ring outline
*/
int lshapesDrawRingLines( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float innerRadius = luaL_checknumber( L, 2 );
	float outerRadius = luaL_checknumber( L, 3 );
	float startAngle = luaL_checknumber( L, 4 );
	float endAngle = luaL_checknumber( L, 5 );
	int segments = luaL_checkinteger( L, 6 );
	Color color = uluaGetColor( L, 7 );

	DrawRingLines( center, innerRadius, outerRadius, startAngle, endAngle, segments, color );

	return 0;
}

/*
> RL.DrawRectangle( Rectangle rec, Color color )

Draw a color-filled rectangle
*/
int lshapesDrawRectangle( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawRectangleRec( rect, color );

	return 0;
}

/*
> RL.DrawRectanglePro( Rectangle rec, Vector2 origin, float rotation, Color color )

Draw a color-filled rectangle with pro parameters
*/
int lshapesDrawRectanglePro( lua_State *L ) {
	Rectangle rec = uluaGetRectangle( L, 1 );
	Vector2 origin = uluaGetVector2( L, 2 );
	float rotation = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawRectanglePro( rec, origin, rotation, color );

	return 0;
}

/*
> RL.DrawRectangleGradientV( Rectangle rectangle, Color color1, Color color2 )

Draw a vertical-gradient-filled rectangle
*/
int lshapesDrawRectangleGradientV( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	Color color1 = uluaGetColor( L, 2 );
	Color color2 = uluaGetColor( L, 3 );

	DrawRectangleGradientV( rect.x, rect.y, rect.width, rect.height, color1, color2 );

	return 0;
}

/*
> RL.DrawRectangleGradientH( Rectangle rectangle, Color color1, Color color2 )

Draw a horizontal-gradient-filled rectangle
*/
int lshapesDrawRectangleGradientH( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	Color color1 = uluaGetColor( L, 2 );
	Color color2 = uluaGetColor( L, 3 );

	DrawRectangleGradientH( rect.x, rect.y, rect.width, rect.height, color1, color2 );

	return 0;
}

/*
> RL.DrawRectangleGradientEx( Rectangle rectangle, Color col1, Color col2, Color col3, Color col4 )

Draw a gradient-filled rectangle with custom vertex colors
*/
int lshapesDrawRectangleGradientEx( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	Color color1 = uluaGetColor( L, 2 );
	Color color2 = uluaGetColor( L, 3 );
	Color color3 = uluaGetColor( L, 4 );
	Color color4 = uluaGetColor( L, 5 );

	DrawRectangleGradientEx( rect, color1, color2, color3, color4 );

	return 0;
}

/*
> RL.DrawRectangleLines( Rectangle rec, Color color )

Draw rectangle outline
*/
int lshapesDrawRectangleLines( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	Color color = uluaGetColor( L, 2 );

	DrawRectangleLines( rect.x, rect.y, rect.width, rect.height, color );

	return 0;
}

/*
> RL.DrawRectangleLinesEx( Rectangle rec, int lineThick, Color color )

Draw rectangle outline with extended parameters
*/
int lshapesDrawRectangleLinesEx( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	int lineThick = luaL_checkinteger( L, 2 );
	Color color = uluaGetColor( L, 3 );

	DrawRectangleLinesEx( rect, lineThick, color );

	return 0;
}

/*
> RL.DrawRectangleRounded( Rectangle rec, float roundness, int segments, Color color )

Draw rectangle with rounded edges
*/
int lshapesDrawRectangleRounded( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	float roundness = luaL_checknumber( L, 2 );
	int segments = luaL_checkinteger( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawRectangleRounded( rect, roundness, segments, color );

	return 0;
}

/*
> RL.DrawRectangleRoundedLines( Rectangle rec, float roundness, int segments, int lineThick, Color color )

Draw rectangle with rounded edges outline
*/
int lshapesDrawRectangleRoundedLines( lua_State *L ) {
	Rectangle rect = uluaGetRectangle( L, 1 );
	float roundness = luaL_checknumber( L, 2 );
	int segments = luaL_checkinteger( L, 3 );
	int lineThick = luaL_checkinteger( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawRectangleRoundedLines( rect, roundness, segments, lineThick, color );

	return 0;
}

/*
> RL.DrawTriangle( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw a color-filled triangle (Vertex in counter-clockwise order!)
*/
int lshapesDrawTriangle( lua_State *L ) {
	Vector2 v1 = uluaGetVector2( L, 1 );
	Vector2 v2 = uluaGetVector2( L, 2 );
	Vector2 v3 = uluaGetVector2( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawTriangle( v1, v2, v3, color );

	return 0;
}

/*
> RL.DrawTriangleLines( Vector2 v1, Vector2 v2, Vector2 v3, Color color )

Draw triangle outline (Vertex in counter-clockwise order!)
*/
int lshapesDrawTriangleLines( lua_State *L ) {
	Vector2 v1 = uluaGetVector2( L, 1 );
	Vector2 v2 = uluaGetVector2( L, 2 );
	Vector2 v3 = uluaGetVector2( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawTriangleLines( v1, v2, v3, color );

	return 0;
}

/*
> RL.DrawTriangleFan( Vector2{} points, Color color )

Draw a triangle fan defined by points (first vertex is the center)
*/
int lshapesDrawTriangleFan( lua_State *L ) {
	int pointsCount = uluaGetTableLen( L, 1 );
	Color color = uluaGetColor( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	DrawTriangleFan( points, pointsCount, color );

	return 0;
}

/*
> RL.DrawTriangleStrip( Vector2{} points, Color color )

Draw a triangle strip defined by points
*/
int lshapesDrawTriangleStrip( lua_State *L ) {
	int pointsCount = uluaGetTableLen( L, 1 );
	Color color = uluaGetColor( L, 2 );

	Vector2 points[ pointsCount ];

	/* t = points index. */
	int t = 1, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	DrawTriangleStrip( points, pointsCount, color );

	return 0;
}

/*
> RL.DrawPoly( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a regular polygon (Vector version)
*/
int lshapesDrawPoly( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	int sides = luaL_checkinteger( L, 2 );
	float radius = luaL_checknumber( L, 3 );
	float rotation = luaL_checknumber( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawPoly( center, sides, radius, rotation, color );

	return 0;
}

/*
> RL.DrawPolyLines( Vector2 center, int sides, float radius, float rotation, Color color )

Draw a polygon outline of n sides
*/
int lshapesDrawPolyLines( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	int sides = luaL_checkinteger( L, 2 );
	float radius = luaL_checknumber( L, 3 );
	float rotation = luaL_checknumber( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawPolyLines( center, sides, radius, rotation, color );

	return 0;
}

/*
> RL.DrawPolyLinesEx( Vector2 center, int sides, float radius, float rotation, float lineThick, Color color )

Draw a polygon outline of n sides with extended parameters
*/
int lshapesDrawPolyLinesEx( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	int sides = luaL_checkinteger( L, 2 );
	float radius = luaL_checknumber( L, 3 );
	float rotation = luaL_checknumber( L, 4 );
	float lineThick = luaL_checknumber( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawPolyLinesEx( center, sides, radius, rotation, lineThick, color );

	return 0;
}

/*
## Shapes - Splines drawing functions
*/

/*
> RL.DrawSplineLinear( Vector2{} points, float thick, Color color )

Draw spline: Linear, minimum 2 points
*/
int lshapesDrawSplineLinear( lua_State *L ) {
	int pointCount = uluaGetTableLen( L, 1 );
	Vector2 points[ pointCount ];
	float thick = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	getVector2Array( L, 1, points );
	DrawSplineLinear( points, pointCount, thick, color );

	return 0;
}

/*
> RL.DrawSplineBasis( Vector2{} points, float thick, Color color )

Draw spline: B-Spline, minimum 4 points
*/
int lshapesDrawSplineBasis( lua_State *L ) {
	int pointCount = uluaGetTableLen( L, 1 );
	Vector2 points[ pointCount ];
	float thick = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	getVector2Array( L, 1, points );
	DrawSplineBasis( points, pointCount, thick, color );

	return 0;
}

/*
> RL.DrawSplineCatmullRom( Vector2{} points, float thick, Color color )

Draw spline: Catmull-Rom, minimum 4 points
*/
int lshapesDrawSplineCatmullRom( lua_State *L ) {
	int pointCount = uluaGetTableLen( L, 1 );
	Vector2 points[ pointCount ];
	float thick = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	getVector2Array( L, 1, points );
	DrawSplineCatmullRom( points, pointCount, thick, color );

	return 0;
}

/*
> RL.DrawSplineBezierQuadratic( Vector2{} points, float thick, Color color )

Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
*/
int lshapesDrawSplineBezierQuadratic( lua_State *L ) {
	int pointCount = uluaGetTableLen( L, 1 );
	Vector2 points[ pointCount ];
	float thick = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	getVector2Array( L, 1, points );
	DrawSplineBezierQuadratic( points, pointCount, thick, color );

	return 0;
}

/*
> RL.DrawSplineBezierCubic( Vector2{} points, float thick, Color color )

Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
*/
int lshapesDrawSplineBezierCubic( lua_State *L ) {
	int pointCount = uluaGetTableLen( L, 1 );
	Vector2 points[ pointCount ];
	float thick = luaL_checknumber( L, 2 );
	Color color = uluaGetColor( L, 3 );

	getVector2Array( L, 1, points );
	DrawSplineBezierCubic( points, pointCount, thick, color );

	return 0;
}

/*
> RL.DrawSplineSegmentLinear( Vector2 p1, Vector2 p2, float thick, Color color )

Draw spline segment: Linear, 2 points
*/
int lshapesDrawSplineSegmentLinear( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	float thick = luaL_checknumber( L, 3 );
	Color color = uluaGetColor( L, 4 );

	DrawSplineSegmentLinear( p1, p2, thick, color );

	return 0;
}

/*
> RL.DrawSplineSegmentBasis( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color )

Draw spline segment: B-Spline, 4 points
*/
int lshapesDrawSplineSegmentBasis( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float thick = luaL_checknumber( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawSplineSegmentBasis( p1, p2, p3, p4, thick, color );

	return 0;
}

/*
> RL.DrawSplineSegmentCatmullRom( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color )

Draw spline segment: Catmull-Rom, 4 points
*/
int lshapesDrawSplineSegmentCatmullRom( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float thick = luaL_checknumber( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawSplineSegmentCatmullRom( p1, p2, p3, p4, thick, color );

	return 0;
}

/*
> RL.DrawSplineSegmentBezierQuadratic( Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color )

Draw spline segment: Quadratic Bezier, 2 points, 1 control point
*/
int lshapesDrawSplineSegmentBezierQuadratic( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 c2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	float thick = luaL_checknumber( L, 4 );
	Color color = uluaGetColor( L, 5 );

	DrawSplineSegmentBezierQuadratic( p1, c2, p3, thick, color );

	return 0;
}

/*
> RL.DrawSplineSegmentBezierCubic( Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color )

Draw spline segment: Cubic Bezier, 2 points, 2 control points
*/
int lshapesDrawSplineSegmentBezierCubic( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 c2 = uluaGetVector2( L, 2 );
	Vector2 c3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float thick = luaL_checknumber( L, 5 );
	Color color = uluaGetColor( L, 6 );

	DrawSplineSegmentBezierCubic( p1, c2, c3, p4, thick, color );

	return 0;
}

/*
## Shapes - Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
*/

/*
> point = RL.GetSplinePointLinear( Vector2 startPos, Vector2 endPos, float t )

Get (evaluate) spline point: Linear

- Success return Vector2
*/
int lshapesGetSplinePointLinear( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	float t = luaL_checknumber( L, 3 );

	uluaPushVector2( L, GetSplinePointLinear( p1, p2, t ) );

	return 1;
}

/*
> point = RL.GetSplinePointBasis( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t )

Get (evaluate) spline point: B-Spline

- Success return Vector2
*/
int lshapesGetSplinePointBasis( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float t = luaL_checknumber( L, 5 );

	uluaPushVector2( L, GetSplinePointBasis( p1, p2, p3, p4, t ) );

	return 1;
}

/*
> point = RL.GetSplinePointCatmullRom( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t )

Get (evaluate) spline point: Catmull-Rom

- Success return Vector2
*/
int lshapesGetSplinePointCatmullRom( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 p2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float t = luaL_checknumber( L, 5 );

	uluaPushVector2( L, GetSplinePointCatmullRom( p1, p2, p3, p4, t ) );

	return 1;
}

/*
> point = RL.GetSplinePointBezierQuad( Vector2 p1, Vector2 c2, Vector2 p3, float t )

Get (evaluate) spline point: Quadratic Bezier

- Success return Vector2
*/
int lshapesGetSplinePointBezierQuad( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 c2 = uluaGetVector2( L, 2 );
	Vector2 p3 = uluaGetVector2( L, 3 );
	float t = luaL_checknumber( L, 4 );

	uluaPushVector2( L, GetSplinePointBezierQuad( p1, c2, p3, t ) );

	return 1;
}

/*
> point = RL.GetSplinePointBezierCubic( Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t )

Get (evaluate) spline point: Cubic Bezier

- Success return Vector2
*/
int lshapesGetSplinePointBezierCubic( lua_State *L ) {
	Vector2 p1 = uluaGetVector2( L, 1 );
	Vector2 c2 = uluaGetVector2( L, 2 );
	Vector2 c3 = uluaGetVector2( L, 3 );
	Vector2 p4 = uluaGetVector2( L, 4 );
	float t = luaL_checknumber( L, 5 );

	uluaPushVector2( L, GetSplinePointBezierCubic( p1, c2, c3, p4, t ) );

	return 1;
}

/*
## Shapes - Basic shapes collision detection functions
*/

/*
> collision = RL.CheckCollisionRecs( Rectangle rec1, Rectangle rec2 )

Check collision between two rectangles

- Success return bool
*/
int lshapesCheckCollisionRecs( lua_State *L ) {
	Rectangle rect1 = uluaGetRectangle( L, 1 );
	Rectangle rect2 = uluaGetRectangle( L, 2 );

	lua_pushboolean( L, CheckCollisionRecs( rect1, rect2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionCircles( Vector2 center1, float radius1, Vector2 center2, float radius2 )

Check collision between two circles

- Success return bool
*/
int lshapesCheckCollisionCircles( lua_State *L ) {
	Vector2 center1 = uluaGetVector2( L, 1 );
	float radius1 = luaL_checknumber( L, 2 );
	Vector2 center2 = uluaGetVector2( L, 3 );
	float radius2 = luaL_checknumber( L, 4 );

	lua_pushboolean( L, CheckCollisionCircles( center1, radius1, center2, radius2 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionCircleRec( Vector2 center, float radius, Rectangle rec )

Check collision between circle and rectangle

- Success return bool
*/
int lshapesCheckCollisionCircleRec( lua_State *L ) {
	Vector2 center = uluaGetVector2( L, 1 );
	float radius = luaL_checknumber( L, 2 );
	Rectangle rec = uluaGetRectangle( L, 3 );

	lua_pushboolean( L, CheckCollisionCircleRec( center, radius, rec ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointRec( Vector2 point, Rectangle rec )

Check if point is inside rectangle

- Success return bool
*/
int lshapesCheckCollisionPointRec( lua_State *L ) {
	Vector2 point = uluaGetVector2( L, 1 );
	Rectangle rec = uluaGetRectangle( L, 2 );

	lua_pushboolean( L, CheckCollisionPointRec( point, rec ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointCircle( Vector2 point, Vector2 center, float radius )

Check if point is inside circle

- Success return bool
*/
int lshapesCheckCollisionPointCircle( lua_State *L ) {
	Vector2 point = uluaGetVector2( L, 1 );
	Vector2 center = uluaGetVector2( L, 2 );
	float radius = luaL_checknumber( L, 3 );

	lua_pushboolean( L, CheckCollisionPointCircle( point, center, radius ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointTriangle( Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3 )

Check if point is inside a triangle

- Success return bool
*/
int lshapesCheckCollisionPointTriangle( lua_State *L ) {
	Vector2 point = uluaGetVector2( L, 1 );
	Vector2 p1 = uluaGetVector2( L, 2 );
	Vector2 p2 = uluaGetVector2( L, 3 );
	Vector2 p3 = uluaGetVector2( L, 4 );

	lua_pushboolean( L, CheckCollisionPointTriangle( point, p1, p2, p3 ) );

	return 1;
}

/*
> collision = RL.CheckCollisionPointPoly( Vector2 point, Vector2{} points )

Check if point is within a polygon described by array of vertices

- Success return bool
*/
int lshapesCheckCollisionPointPoly( lua_State *L ) {
	Vector2 point = uluaGetVector2( L, 1 );
	int pointCount = uluaGetTableLen( L, 2 );
	Vector2 points[ pointCount ];

	/* t = points index. */
	int t = 2, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		points[i] = uluaGetVector2( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	lua_pushboolean( L, CheckCollisionPointPoly( point, points, pointCount ) );

	return 1;
}

/*
> collision, position = RL.CheckCollisionLines( Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2 )

Check the collision between two lines defined by two points each, returns collision point by reference

- Success return bool, Vector2
*/
int lshapesCheckCollisionLines( lua_State *L ) {
	Vector2 startPos1 = uluaGetVector2( L, 1 );
	Vector2 endPos1 = uluaGetVector2( L, 2 );
	Vector2 startPos2 = uluaGetVector2( L, 3 );
	Vector2 endPos2 = uluaGetVector2( L, 4 );

	Vector2 colPoint = { 0, 0 };

	lua_pushboolean( L, CheckCollisionLines( startPos1, endPos1, startPos2, endPos2, &colPoint ) );
	uluaPushVector2( L, colPoint );

	return 2;
}

/*
> collision = RL.CheckCollisionPointLine( Vector2 point, Vector2 p1, Vector2 p2, int threshold )

Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]

- Success return bool
*/
int lshapesCheckCollisionPointLine( lua_State *L ) {
	Vector2 point = uluaGetVector2( L, 1 );
	Vector2 p1 = uluaGetVector2( L, 2 );
	Vector2 p2 = uluaGetVector2( L, 3 );
	int threshold = luaL_checkinteger( L, 4 );

	lua_pushboolean( L, CheckCollisionPointLine( point, p1, p2, threshold ) );

	return 1;
}

/*
> rectangle = RL.GetCollisionRec( Rectangle rec1, Rectangle rec2 )

Get collision rectangle for two rectangles collision

- Success return Rectangle
*/
int lshapesGetCollisionRec( lua_State *L ) {
	Rectangle rec1 = uluaGetRectangle( L, 1 );
	Rectangle rec2 = uluaGetRectangle( L, 2 );

	uluaPushRectangle( L, GetCollisionRec( rec1, rec2 ) );

	return 1;
}
