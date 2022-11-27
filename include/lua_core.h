#pragma once

bool luaInit();
int luaTraceback( lua_State *L );
bool luaCallMain();
void luaCallProcess();
void luaCallDraw();
void luaCallExit();
void luaRegister();
/* Lua Util functions */
Color uluaGetColor( lua_State *L );
Vector2 uluaGetVector2( lua_State *L );
Vector3 uluaGetVector3( lua_State *L );
Vector4 uluaGetVector4( lua_State *L );
Rectangle uluaGetRectangle( lua_State *L );
Quaternion uluaGetQuaternion( lua_State *L );
Matrix uluaGetMatrix( lua_State *L );
BoundingBox uluaGetBoundingBox( lua_State *L );
Ray uluaGetRay( lua_State *L );
NPatchInfo uluaGetNPatchInfo( lua_State *L );

void uluaPushColor( lua_State *L, Color color );
void uluaPushVector2( lua_State *L, Vector2 vector );
void uluaPushVector3( lua_State *L, Vector3 vector );
void uluaPushVector4( lua_State *L, Vector4 vector );
void uluaPushRectangle( lua_State *L, Rectangle rect );
void uluaPushQuaternion( lua_State *L, Quaternion quaternion );
void uluaPushMatrix( lua_State *L, Matrix matrix );
void uluaPushRay( lua_State *L, Ray ray );
void uluaPushRayCollision( lua_State *L, RayCollision rayCol );
void uluaPushBoundingBox( lua_State *L, BoundingBox box );

int uluaGetTableLen( lua_State *L );
