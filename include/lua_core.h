#pragma once

// Function specifiers in case library is build/used as a shared library
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
// NOTE: visibility("default") attribute makes symbols "visible" when compiled with -fvisibility=hidden
#if defined( _WIN32 )
    #if defined( __TINYC__ )
        #define __declspec(x) __attribute__( (x) )
    #endif
    #if defined( EXPOSE_API_SYMBOLS )
        #define REILUAPI __declspec( dllexport )     // We are building the library as a Win32 shared library (.dll)
    #elif defined( USE_LIBTYPE_SHARED )
        #define REILUAPI __declspec( dllimport )     // We are using the library as a Win32 shared library (.dll)
    #endif
#else
    #if defined( EXPOSE_API_SYMBOLS )
        #define REILUAPI __attribute__( ( visibility( "default" ) ) ) // We are building as a Unix shared library (.so/.dylib)
    #endif
#endif

#ifndef REILUAPI
    #define REILUAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

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
void luaCallMain();
void luaCallInit();
void luaCallUpdate();
void luaCallDraw();
void luaCallExit();
void luaRegister();
void platformDefineGlobals();
void luaPlatformRegister();
/* Lua get types. */
REILUAPI bool uluaGetBoolean( lua_State* L, int index );
REILUAPI Color uluaGetColor( lua_State* L, int index );
REILUAPI Vector2 uluaGetVector2( lua_State* L, int index );
REILUAPI Vector3 uluaGetVector3( lua_State* L, int index );
REILUAPI Vector4 uluaGetVector4( lua_State* L, int index );
REILUAPI Rectangle uluaGetRectangle( lua_State* L, int index );
REILUAPI Quaternion uluaGetQuaternion( lua_State* L, int index );
REILUAPI Matrix uluaGetMatrix( lua_State* L, int index );
REILUAPI BoundingBox uluaGetBoundingBox( lua_State* L, int index );
REILUAPI Ray uluaGetRay( lua_State* L, int index );
REILUAPI NPatchInfo uluaGetNPatchInfo( lua_State* L, int index );
REILUAPI BoneInfo uluaGetBoneInfo( lua_State* L, int index );
REILUAPI Transform uluaGetTransform( lua_State* L, int index );
REILUAPI Buffer* uluaGetBuffer( lua_State* L, int index );
REILUAPI Image* uluaGetImage( lua_State* L, int index );
REILUAPI Texture* uluaGetTexture( lua_State* L, int index );
REILUAPI RenderTexture* uluaGetRenderTexture( lua_State* L, int index );
REILUAPI Shader* uluaGetShader( lua_State* L, int index );
REILUAPI Mesh* uluaGetMesh( lua_State* L, int index );
REILUAPI Camera2D* uluaGetCamera2D( lua_State* L, int index );
REILUAPI Camera3D* uluaGetCamera3D( lua_State* L, int index );
REILUAPI Font* uluaGetFont( lua_State* L, int index );
REILUAPI GlyphInfo* uluaGetGlyphInfo( lua_State* L, int index );
REILUAPI Wave* uluaGetWave( lua_State* L, int index );
REILUAPI Sound* uluaGetSound( lua_State* L, int index );
REILUAPI Music* uluaGetMusic( lua_State* L, int index );
REILUAPI Light* uluaGetLight( lua_State* L, int index );
REILUAPI Material* uluaGetMaterial( lua_State* L, int index );
REILUAPI Model* uluaGetModel( lua_State* L, int index );
REILUAPI ModelAnimation* uluaGetModelAnimation( lua_State* L, int index );
REILUAPI rlRenderBatch* uluaGetRLRenderBatch( lua_State* L, int index );
REILUAPI AutomationEvent* uluaGetAutomationEvent( lua_State* L, int index );
REILUAPI AutomationEventList* uluaGetAutomationEventList( lua_State* L, int index );

REILUAPI void getVector2Array( lua_State* L, int index, Vector2 points[] );
/* Lua push types. */
REILUAPI void uluaPushColor( lua_State* L, Color color );
REILUAPI void uluaPushVector2( lua_State* L, Vector2 vector );
REILUAPI void uluaPushVector3( lua_State* L, Vector3 vector );
REILUAPI void uluaPushVector4( lua_State* L, Vector4 vector );
REILUAPI void uluaPushRectangle( lua_State* L, Rectangle rect );
REILUAPI void uluaPushQuaternion( lua_State* L, Quaternion quaternion );
REILUAPI void uluaPushMatrix( lua_State* L, Matrix matrix );
REILUAPI void uluaPushRay( lua_State* L, Ray ray );
REILUAPI void uluaPushRayCollision( lua_State* L, RayCollision rayCol );
REILUAPI void uluaPushBoundingBox( lua_State* L, BoundingBox box );
REILUAPI void uluaPushBoneInfo( lua_State* L, BoneInfo boneInfo );
REILUAPI void uluaPushTransform( lua_State* L, Transform transform );
// void uluaPushAutomationEvent( lua_State* L, AutomationEvent event );
REILUAPI void uluaPushBuffer( lua_State* L, Buffer buffer );
REILUAPI void uluaPushImage( lua_State* L, Image image );
REILUAPI void uluaPushTexture( lua_State* L, Texture texture );
REILUAPI void uluaPushRenderTexture( lua_State* L, RenderTexture renderTexture );
REILUAPI void uluaPushCamera2D( lua_State* L, Camera2D camera );
REILUAPI void uluaPushCamera3D( lua_State* L, Camera3D camera );
REILUAPI void uluaPushShader( lua_State* L, Shader shader );
REILUAPI void uluaPushFont( lua_State* L, Font font );
REILUAPI void uluaPushGlyphInfo( lua_State* L, GlyphInfo glyph );
REILUAPI void uluaPushWave( lua_State* L, Wave wave );
REILUAPI void uluaPushSound( lua_State* L, Sound sound );
REILUAPI void uluaPushMusic( lua_State* L, Music music );
REILUAPI void uluaPushLight( lua_State* L, Light light );
REILUAPI void uluaPushMaterial( lua_State* L, Material material );
REILUAPI void uluaPushMesh( lua_State* L, Mesh mesh );
REILUAPI void uluaPushModel( lua_State* L, Model model );
REILUAPI void uluaPushModelAnimation( lua_State* L, ModelAnimation modelAnimation );
REILUAPI void uluaPushRLRenderBatch( lua_State* L, rlRenderBatch renderBatch );
REILUAPI void uluaPushAutomationEvent( lua_State* L, AutomationEvent event );
REILUAPI void uluaPushAutomationEventList( lua_State* L, AutomationEventList eventList );
/* Utils. */
REILUAPI int uluaGetTableLen( lua_State* L, int index );
REILUAPI bool uluaIsNil( lua_State* L, int index );
