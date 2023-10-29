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

enum BufferType {
	BUFFER_UNSIGNED_CHAR,
	BUFFER_UNSIGNED_SHORT,
	BUFFER_UNSIGNED_INT,
	BUFFER_FLOAT,
};

typedef struct {
	size_t size;
	void *data;
	int x;
	int y;
} Buffer;

bool luaInit( int argn, const char **argc );
int luaTraceback( lua_State *L );
bool luaCallMain();
void luaCallProcess();
void luaCallDraw();
void luaCallExit();
void luaRegister();
/* Lua Util functions. */
bool uluaGetBoolean( lua_State *L, int index );
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
void uluaPushImage( lua_State *L, Image image );
void uluaPushTexture( lua_State *L, Texture texture );
void uluaPushRenderTexture( lua_State *L, RenderTexture renderTexture );
void uluaPushCamera2D( lua_State *L, Camera2D camera );
void uluaPushCamera3D( lua_State *L, Camera3D camera );
void uluaPushShader( lua_State *L, Shader shader );
void uluaPushFont( lua_State *L, Font font );
void uluaPushWave( lua_State *L, Wave wave );
void uluaPushSound( lua_State *L, Sound sound );
void uluaPushMusic( lua_State *L, Music music );
void uluaPushLight( lua_State *L, Light light );
void uluaPushMaterial( lua_State *L, Material material );
void uluaPushMesh( lua_State *L, Mesh mesh );
void uluaPushModel( lua_State *L, Model model );
void uluaPushModelAnimation( lua_State *L, ModelAnimation modelAnimation );

int uluaGetTableLen( lua_State *L );
int uluaGetTableLenIndex( lua_State *L, int index );
