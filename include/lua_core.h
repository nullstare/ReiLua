#pragma once

enum EventType {
	EVENT_WINDOW_SIZE,
	EVENT_WINDOW_MAXIMIZE,
	EVENT_WINDOW_ICONYFY,
	EVENT_WINDOW_FOCUS,
	EVENT_WINDOW_DROP,
	EVENT_KEY,
	EVENT_CHAR,
	EVENT_MOUSE_BUTTON,
	EVENT_MOUSE_CURSOR_POS,
	EVENT_MOUSE_SCROLL,
	EVENT_CURSOR_ENTER
};

bool luaInit( int argn, const char **argc );
int luaTraceback( lua_State *L );
bool luaCallMain();
void luaCallProcess();
void luaCallDraw();
void luaCallExit();
void luaRegister();
/* Type validators. */
bool isValidTexture( lua_State *L, int index, bool allowTable );
bool isValidRenderTexture( lua_State *L, int index, bool allowTable );
bool isValidCamera2D( lua_State *L, int index, bool allowTable );
bool isValidCamera3D( lua_State *L, int index, bool allowTable );
/* Lua Util functions. */
Color uluaGetColor( lua_State *L );
Color uluaGetColorIndex( lua_State *L, int index );
Vector2 uluaGetVector2( lua_State *L );
Vector2 uluaGetVector2Index( lua_State *L, int index );
Vector3 uluaGetVector3( lua_State *L );
Vector3 uluaGetVector3Index( lua_State *L, int index );
Vector4 uluaGetVector4( lua_State *L );
Vector4 uluaGetVector4Index( lua_State *L, int index );
Rectangle uluaGetRectangle( lua_State *L );
Rectangle uluaGetRectangleIndex( lua_State *L, int index );
Quaternion uluaGetQuaternion( lua_State *L );
Quaternion uluaGetQuaternionIndex( lua_State *L, int index );
Matrix uluaGetMatrix( lua_State *L );
Matrix uluaGetMatrixIndex( lua_State *L, int index );
BoundingBox uluaGetBoundingBox( lua_State *L );
BoundingBox uluaGetBoundingBoxIndex( lua_State *L, int index );
Ray uluaGetRay( lua_State *L );
Ray uluaGetRayIndex( lua_State *L, int index );
NPatchInfo uluaGetNPatchInfo( lua_State *L );
NPatchInfo uluaGetNPatchInfoIndex( lua_State *L, int index );
Texture uluaGetTexture( lua_State *L, int index );
RenderTexture uluaGetRenderTexture( lua_State *L, int index );
Camera2D uluaGetCamera2D( lua_State *L, int index );
Camera3D uluaGetCamera3D( lua_State *L, int index );
/* Push types. */
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
void uluaPushTexture( lua_State *L, Texture texture );

int uluaGetTableLen( lua_State *L );
int uluaGetTableLenIndex( lua_State *L, int index );
