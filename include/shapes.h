#pragma once

/* Drawing. */
int lshapesDrawPixel( lua_State *L );
int lshapesDrawLine( lua_State *L );
int lshapesDrawCircle( lua_State *L );
int lshapesDrawCircleLines( lua_State *L );
int lshapesDrawRectangle( lua_State *L );
int lshapesDrawRectanglePro( lua_State *L );
int lshapesDrawTriangle( lua_State *L );
int lshapesDrawTriangleLines( lua_State *L );
/* Collision. */
int lshapesCheckCollisionRecs( lua_State *L );
int lshapesCheckCollisionCircles( lua_State *L );
int lshapesCheckCollisionCircleRec( lua_State *L );
int lshapesCheckCollisionPointRec( lua_State *L );
int lshapesCheckCollisionPointCircle( lua_State *L );
int lshapesCheckCollisionPointTriangle( lua_State *L );
int lshapesCheckCollisionLines( lua_State *L );
int lshapesCheckCollisionPointLine( lua_State *L );
int lshapesGetCollisionRec( lua_State *L );
