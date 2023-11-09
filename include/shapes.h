#pragma once

/* Basic shapes drawing functions. */
int lshapesSetShapesTexture( lua_State *L );
int lshapesDrawPixel( lua_State *L );
int lshapesDrawLine( lua_State *L );
int lshapesDrawLineBezier( lua_State *L );
int lshapesDrawLineBezierQuad( lua_State *L );
int lshapesDrawLineBezierCubic( lua_State *L );
int lshapesDrawLineStrip( lua_State *L );
int lshapesDrawCircle( lua_State *L );
int lshapesDrawCircleSector( lua_State *L );
int lshapesDrawCircleSectorLines( lua_State *L );
int lshapesDrawCircleGradient( lua_State *L );
int lshapesDrawCircleLines( lua_State *L );
int lshapesDrawEllipse( lua_State *L );
int lshapesDrawEllipseLines( lua_State *L );
int lshapesDrawRing( lua_State *L );
int lshapesDrawRingLines( lua_State *L );
int lshapesDrawRectangle( lua_State *L );
int lshapesDrawRectanglePro( lua_State *L );
int lshapesDrawRectangleGradientV( lua_State *L );
int lshapesDrawRectangleGradientH( lua_State *L );
int lshapesDrawRectangleGradientEx( lua_State *L );
int lshapesDrawRectangleLines( lua_State *L );
int lshapesDrawRectangleLinesEx( lua_State *L );
int lshapesDrawRectangleRounded( lua_State *L );
int lshapesDrawRectangleRoundedLines( lua_State *L );
int lshapesDrawTriangle( lua_State *L );
int lshapesDrawTriangleLines( lua_State *L );
int lshapesDrawTriangleFan( lua_State *L );
int lshapesDrawTriangleStrip( lua_State *L );
int lshapesDrawPoly( lua_State *L );
int lshapesDrawPolyLines( lua_State *L );
int lshapesDrawPolyLinesEx( lua_State *L );
/* Basic shapes collision detection functions. */
int lshapesCheckCollisionRecs( lua_State *L );
int lshapesCheckCollisionCircles( lua_State *L );
int lshapesCheckCollisionCircleRec( lua_State *L );
int lshapesCheckCollisionPointRec( lua_State *L );
int lshapesCheckCollisionPointCircle( lua_State *L );
int lshapesCheckCollisionPointTriangle( lua_State *L );
int lshapesCheckCollisionPointPoly( lua_State *L );
int lshapesCheckCollisionLines( lua_State *L );
int lshapesCheckCollisionPointLine( lua_State *L );
int lshapesGetCollisionRec( lua_State *L );
