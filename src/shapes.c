#include "main.h"
#include "shapes.h"
#include "lua_core.h"

/*
## Shapes - Drawing
*/

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
	Rectangle rect = { 0, 0, 0, 0 };
	Color color = { 0, 0, 0, 0 };

	color = uluaGetColor( L );
	lua_pop( L, 1 );
	rect = uluaGetRectangle( L );

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
