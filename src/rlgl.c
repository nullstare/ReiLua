#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "lrlgl.h"

/*
## RLGL - Textures state
*/

/*
> success = RL.rlActiveTextureSlot( int slot )

Select and active a texture slot

- Failure return false
- Success return true
*/
int lrlglActiveTextureSlot( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlActiveTextureSlot( int slot )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlActiveTextureSlot( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.rlEnableTexture( int id )

Enable texture

- Failure return false
- Success return true
*/
int lrlglEnableTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlEnableTexture( int id )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlEnableTexture( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.rlDisableTexture()

Disable texture
*/
int lrlglDisableTexture( lua_State *L ) {
	rlDisableTexture();

	return 0;
}

/*
> success = RL.rlEnableTextureCubemap( int id )

Enable texture cubemap

- Failure return false
- Success return true
*/
int lrlglEnableTextureCubemap( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlEnableTextureCubemap( int id )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlEnableTextureCubemap( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.rlDisableTextureCubemap()

Disable texture cubemap
*/
int lrlglDisableTextureCubemap( lua_State *L ) {
	rlDisableTextureCubemap();

	return 0;
}

/*
> success = RL.rlTextureParameters( int id, int param, int value )

Set texture parameters ( filter, wrap )

- Failure return false
- Success return true
*/
int lrlglTextureParameters( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlTextureParameters( int id, int param, int value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int id = lua_tointeger( L, 1 );
	int param = lua_tointeger( L, 2 );
	int value = lua_tointeger( L, 3 );

	rlTextureParameters( id, param, value );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.rlCubemapParameters( int id, int param, int value )

Set cubemap parameters ( filter, wrap )

- Failure return false
- Success return true
*/
int lrlglCubemapParameters( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlCubemapParameters( int id, int param, int value )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int id = lua_tointeger( L, 1 );
	int param = lua_tointeger( L, 2 );
	int value = lua_tointeger( L, 3 );

	rlCubemapParameters( id, param, value );
	lua_pushboolean( L, true );

	return 1;
}

/*
## RLGL - Framebuffer state
*/

/*
> success = RL.rlEnableFramebuffer( int id )

Enable render texture (fbo)

- Failure return false
- Success return true
*/
int lrlglEnableFramebuffer( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlEnableFramebuffer( int id )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlEnableFramebuffer( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL.rlDisableFramebuffer()

Disable render texture (fbo), return to default framebuffer
*/
int lrlglDisableFramebuffer( lua_State *L ) {
	rlDisableFramebuffer();

	return 0;
}

/*
> success = RL.rlActiveDrawBuffers( int count )

Activate multiple draw color buffers

- Failure return false
- Success return true
*/
int lrlglActiveDrawBuffers( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlActiveDrawBuffers( int count )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlActiveDrawBuffers( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## RLGL - General render state
*/

/*
> RL.rlEnableColorBlend()

Enable color blending
*/
int lrlglEnableColorBlend( lua_State *L ) {
	rlEnableColorBlend();

	return 0;
}

/*
> RL.rlDisableColorBlend()

Disable color blending
*/
int lrlglDisableColorBlend( lua_State *L ) {
	rlDisableColorBlend();

	return 0;
}

/*
> RL.rlEnableDepthTest()

Enable depth test
*/
int lrlglEnableDepthTest( lua_State *L ) {
	rlEnableDepthTest();

	return 0;
}

/*
> RL.rlDisableDepthTest()

Disable depth test
*/
int lrlglDisableDepthTest( lua_State *L ) {
	rlDisableDepthTest();

	return 0;
}

/*
> RL.rlEnableDepthMask()

Enable depth write
*/
int lrlglEnableDepthMask( lua_State *L ) {
	rlEnableDepthMask();

	return 0;
}

/*
> RL.rlDisableDepthMask()

Disable depth write
*/
int lrlglDisableDepthMask( lua_State *L ) {
	rlDisableDepthMask();

	return 0;
}

/*
> RL.rlEnableBackfaceCulling()

Enable backface culling
*/
int lrlglEnableBackfaceCulling( lua_State *L ) {
	rlEnableBackfaceCulling();

	return 0;
}

/*
> RL.rlDisableBackfaceCulling()

Disable backface culling
*/
int lrlglDisableBackfaceCulling( lua_State *L ) {
	rlDisableBackfaceCulling();

	return 0;
}

/*
> success = RL.rlSetCullFace( int mode )

Set face culling mode

- Failure return false
- Success return true
*/
int lrlglSetCullFace( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlSetCullFace( int mode )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlSetCullFace( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.rlSetLineWidth( float width )

Set the line drawing width

- Failure return false
- Success return true
*/
int lrlglSetLineWidth( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlSetLineWidth( float width )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlSetLineWidth( lua_tonumber( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> width = RL.rlGetLineWidth()

Get the line drawing width

- Success return float
*/
int lrlglGetLineWidth( lua_State *L ) {
	lua_pushnumber( L, rlGetLineWidth() );

	return 1;
}

/*
> RL.rlEnableSmoothLines()

Enable line aliasing
*/
int lrlglEnableSmoothLines( lua_State *L ) {
	rlEnableSmoothLines();

	return 0;
}

/*
> RL.rlDisableSmoothLines()

Disable line aliasing
*/
int lrlglDisableSmoothLines( lua_State *L ) {
	rlDisableSmoothLines();

	return 0;
}

/*
## RLGL - Initialization functions
*/

/*
> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int
*/
int lrlglGetVersion( lua_State *L ) {
	lua_pushinteger( L, rlGetVersion() );

	return 1;
}

/*
## RLGL - Textures management
*/

/*
> id = RL.rlLoadTexture( Vector2 size, int format, int mipmapCount )

Load texture in GPU

- Failure return -1
- Success return int
*/
int lrlglLoadTexture( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlLoadTexture( Vector2 size, int format, int mipmapCount )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	int format = lua_tointeger( L, 2 );
	int mipmapCount = lua_tointeger( L, 3 );

	lua_pushinteger( L, rlLoadTexture( NULL, size.x, size.y, format, mipmapCount ) );

	return 1;
}

/*
> id = RL.rlLoadTextureDepth( Vector2 size, bool useRenderBuffer )

Load depth texture/renderbuffer ( to be attached to fbo )

- Failure return -1
- Success return int
*/
int lrlglLoadTextureDepth( lua_State *L ) {
	if ( !lua_istable( L, 1 ) || !lua_isboolean( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlLoadTextureDepth( Vector2 size, bool useRenderBuffer )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );
	bool useRenderBuffer = lua_toboolean( L, 2 );

	lua_pushinteger( L, rlLoadTextureDepth( size.x, size.y, useRenderBuffer ) );

	return 1;
}

/*
> success = RL.rlUnloadTexture( int id )

Unload texture from GPU memory

- Failure return false
- Success return true
*/
int lrlglUnloadTexture( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlUnloadTexture( int id )" );
		lua_pushboolean( L, false );
		return 1;
	}
	rlUnloadTexture( lua_tointeger( L, 1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## RLGL - Framebuffer management (fbo)
*/

/*
> fboId = RL.rlLoadFramebuffer( Vector2 size )

Load an empty framebuffer

- Failure return -1
- Success return int
*/
int lrlglLoadFramebuffer( lua_State *L ) {
	if ( !lua_istable( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlLoadFramebuffer( Vector2 size )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	Vector2 size = uluaGetVector2Index( L, 1 );

	lua_pushinteger( L, rlLoadFramebuffer( size.x, size.y ) );

	return 1;
}

/*
> success = RL.rlFramebufferAttach( int fboId, int texId, int attachType, int texType, int mipLevel )

Attach texture/renderbuffer to a framebuffer

- Failure return false
- Success return true
*/
int lrlglFramebufferAttach( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 )
	|| !lua_isnumber( L, 4 ) || !lua_isnumber( L, 5 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlFramebufferAttach( int fboId, int texId, int attachType, int texType, int mipLevel )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int fboId = lua_tointeger( L, 1 );
	unsigned int texId = lua_tointeger( L, 2 );
	int attachType = lua_tointeger( L, 3 );
	int texType = lua_tointeger( L, 4 );
	int mipLevel = lua_tointeger( L, 5 );

	rlFramebufferAttach( fboId, texId, attachType, texType, mipLevel );
	lua_pushboolean( L, true );

	return 1;
}

/*
> isComplete = RL.rlFramebufferComplete( int id )

Verify framebuffer is complete

- Failure return nil
- Success return bool
*/
int lrlglFramebufferComplete( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlFramebufferComplete( int id )" );
		lua_pushnil( L );
		return 1;
	}
	unsigned int id = lua_tointeger( L, 1 );

	lua_pushboolean( L, rlFramebufferComplete( id ) );

	return 1;
}

/*
> success = RL.rlUnloadFramebuffer( int id )

Delete framebuffer from GPU

- Failure return nil
- Success return bool
*/
int lrlglUnloadFramebuffer( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.rlUnloadFramebuffer( int id )" );
		lua_pushboolean( L, false );
		return 1;
	}
	unsigned int id = lua_tointeger( L, 1 );

	rlUnloadFramebuffer( id );
	lua_pushboolean( L, true );

	return 1;
}