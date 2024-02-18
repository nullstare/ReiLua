#pragma once

enum BufferType {
	BUFFER_UNSIGNED_CHAR,
	BUFFER_UNSIGNED_SHORT,
	BUFFER_UNSIGNED_INT,
	BUFFER_CHAR,
	BUFFER_SHORT,
	BUFFER_INT,
	BUFFER_FLOAT,
	BUFFER_DOUBLE
};

typedef struct {
	int type;
	size_t size;
	void* data;
} Buffer;

/* Global assing functions. */
void assignGlobalInt( int value, const char* name );
void assignGlobalFloat( float value, const char* name );
void assignGlobalDouble( double value, const char* name );
void assignGlobalColor( Color color, const char* name );
void assingGlobalFunction( const char* name, int ( *functionPtr )( lua_State* ) );

bool luaInit( int argn, const char** argc );
int luaTraceback( lua_State* L );
bool luaCallMain();
void luaCallUpdate();
void luaCallDraw();
void luaCallExit();
void luaRegister();
void platformDefineGlobals();
void luaPlatformRegister();
/* Lua get types. */
bool uluaGetBoolean( lua_State* L, int index );
Color uluaGetColor( lua_State* L, int index );
Vector2 uluaGetVector2( lua_State* L, int index );
Vector3 uluaGetVector3( lua_State* L, int index );
Vector4 uluaGetVector4( lua_State* L, int index );
Rectangle uluaGetRectangle( lua_State* L, int index );
Quaternion uluaGetQuaternion( lua_State* L, int index );
Matrix uluaGetMatrix( lua_State* L, int index );
BoundingBox uluaGetBoundingBox( lua_State* L, int index );
Ray uluaGetRay( lua_State* L, int index );
NPatchInfo uluaGetNPatchInfo( lua_State* L, int index );
BoneInfo uluaGetBoneInfo( lua_State* L, int index );
Transform uluaGetTransform( lua_State* L, int index );
Buffer* uluaGetBuffer( lua_State* L, int index );
Image* uluaGetImage( lua_State* L, int index );
Texture* uluaGetTexture( lua_State* L, int index );
RenderTexture* uluaGetRenderTexture( lua_State* L, int index );
Shader* uluaGetShader( lua_State* L, int index );
Mesh* uluaGetMesh( lua_State* L, int index );
Camera2D* uluaGetCamera2D( lua_State* L, int index );
Camera3D* uluaGetCamera3D( lua_State* L, int index );
Font* uluaGetFont( lua_State* L, int index );
GlyphInfo* uluaGetGlyphInfo( lua_State* L, int index );
Wave* uluaGetWave( lua_State* L, int index );
Sound* uluaGetSound( lua_State* L, int index );
Music* uluaGetMusic( lua_State* L, int index );
Light* uluaGetLight( lua_State* L, int index );
Material* uluaGetMaterial( lua_State* L, int index );
Model* uluaGetModel( lua_State* L, int index );
ModelAnimation* uluaGetModelAnimation( lua_State* L, int index );
rlRenderBatch* uluaGetRLRenderBatch( lua_State* L, int index );
/* Lua push types. */
void uluaPushColor( lua_State* L, Color color );
void uluaPushVector2( lua_State* L, Vector2 vector );
void uluaPushVector3( lua_State* L, Vector3 vector );
void uluaPushVector4( lua_State* L, Vector4 vector );
void uluaPushRectangle( lua_State* L, Rectangle rect );
void uluaPushQuaternion( lua_State* L, Quaternion quaternion );
void uluaPushMatrix( lua_State* L, Matrix matrix );
void uluaPushRay( lua_State* L, Ray ray );
void uluaPushRayCollision( lua_State* L, RayCollision rayCol );
void uluaPushBoundingBox( lua_State* L, BoundingBox box );
void uluaPushBoneInfo( lua_State* L, BoneInfo boneInfo );
void uluaPushTransform( lua_State* L, Transform transform );
void uluaPushBuffer( lua_State* L, Buffer buffer );
void uluaPushImage( lua_State* L, Image image );
void uluaPushTexture( lua_State* L, Texture texture );
void uluaPushRenderTexture( lua_State* L, RenderTexture renderTexture );
void uluaPushCamera2D( lua_State* L, Camera2D camera );
void uluaPushCamera3D( lua_State* L, Camera3D camera );
void uluaPushShader( lua_State* L, Shader shader );
void uluaPushFont( lua_State* L, Font font );
void uluaPushGlyphInfo( lua_State* L, GlyphInfo glyph );
void uluaPushWave( lua_State* L, Wave wave );
void uluaPushSound( lua_State* L, Sound sound );
void uluaPushMusic( lua_State* L, Music music );
void uluaPushLight( lua_State* L, Light light );
void uluaPushMaterial( lua_State* L, Material material );
void uluaPushMesh( lua_State* L, Mesh mesh );
void uluaPushModel( lua_State* L, Model model );
void uluaPushModelAnimation( lua_State* L, ModelAnimation modelAnimation );
void uluaPushRLRenderBatch( lua_State* L, rlRenderBatch renderBatch );
/* Utils. */
int uluaGetTableLen( lua_State* L, int index );
