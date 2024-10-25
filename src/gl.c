#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "lgl.h"

/*
## OpenGL - Rendering
*/

/*
> RL.glClear( int mask )

Clear buffers to preset values
*/
int lglClear( lua_State* L ) {
	unsigned int mask = luaL_checkinteger( L, 1 );

	glClear( mask );

	return 0;
}

/*
## OpenGL - Frame Buffers
*/

/*
> RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use nil RenderTexture for window framebuffer
*/
int lglBlitFramebuffer( lua_State* L ) {
#if defined( PLATFORM_DESKTOP ) || defined( PLATFORM_DESKTOP_SDL )
	if ( !( lua_isuserdata( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isuserdata( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Argument needs to be RenderTexture or nil" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle srcRect = uluaGetRectangle( L, 3 );
	Rectangle dstRect = uluaGetRectangle( L, 4 );
	int mask = luaL_checkinteger( L, 5 );
	int filter = luaL_checkinteger( L, 6 );

	if ( lua_isnil( L, 1 ) ) {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	}
	else {
		RenderTexture* srcTex = uluaGetRenderTexture( L, 1 );
		glBindFramebuffer( GL_READ_FRAMEBUFFER, srcTex->id );
	}

	if ( lua_isnil( L, 2 ) ) {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	}
	else {
		RenderTexture* dstTex = uluaGetRenderTexture( L, 2 );
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, dstTex->id );
	}

	glBlitFramebuffer(
		srcRect.x, srcRect.y, srcRect.width, srcRect.height,
		dstRect.x, dstRect.y, dstRect.width, dstRect.height,
		mask,
		filter
	);

	glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

	return 1;
#endif
}

/*
## OpenGL - State Management
*/

/*
> RL.glDepthRange( float nearVal, float farVal )

Specify mapping of depth values from normalized device coordinates to window coordinates
*/
int lglDepthRange( lua_State* L ) {
	float nearVal = luaL_checknumber( L, 1 );
	float farVal = luaL_checknumber( L, 2 );

	glDepthRange( nearVal, farVal );

	return 0;
}

/*
> RL.glEnable( int cap )

Enable server-side GL capabilities
*/
int lglEnable( lua_State* L ) {
	int cap = luaL_checkinteger( L, 1 );

	glEnable( cap );

	return 0;
}

/*
> RL.glDisable( int cap )

Disable server-side GL capabilities
*/
int lglDisable( lua_State* L ) {
	int cap = luaL_checkinteger( L, 1 );

	glDisable( cap );

	return 0;
}

/*
> RL.glPolygonOffset( float factor, float units )

Set the scale and units used to calculate depth values
*/
int lglPolygonOffset( lua_State* L ) {
	float factor = luaL_checknumber( L, 1 );
	float units = luaL_checknumber( L, 2 );

	glPolygonOffset( factor, units );

	return 0;
}

/*
> RL.glStencilFunc( int func, int ref, int mask )

Set front and back function and reference value for stencil testing
*/
int lglStencilFunc( lua_State* L ) {
	int func = luaL_checkinteger( L, 1 );
	int ref = luaL_checkinteger( L, 2 );
	unsigned int mask = luaL_checkinteger( L, 3 );

	glStencilFunc( func, ref, mask );

	return 0;
}

/*
> RL.glStencilFuncSeparate( int face, int func, int ref, int mask )

Set front and/or back function and reference value for stencil testing
*/
int lglStencilFuncSeparate( lua_State* L ) {
	int face = luaL_checkinteger( L, 1 );
	int func = luaL_checkinteger( L, 2 );
	int ref = luaL_checkinteger( L, 3 );
	unsigned int mask = luaL_checkinteger( L, 4 );

	glStencilFuncSeparate( face, func, ref, mask );

	return 0;
}

/*
> RL.glStencilMask( int mask )

Control the front and back writing of individual bits in the stencil planes
*/
int lglStencilMask( lua_State* L ) {
	unsigned int mask = luaL_checkinteger( L, 1 );

	glStencilMask( mask );

	return 0;
}

/*
> RL.glStencilMaskSeparate( int face, int mask )

Control the front and/or back writing of individual bits in the stencil planes
*/
int lglStencilMaskSeparate( lua_State* L ) {
	int face = luaL_checkinteger( L, 1 );
	unsigned int mask = luaL_checkinteger( L, 2 );

	glStencilMaskSeparate( face, mask );

	return 0;
}

/*
> RL.glStencilOp( int sfail, int dpfail, int dppass )

Set front and back stencil test actions
*/
int lglStencilOp( lua_State* L ) {
	int sfail = luaL_checkinteger( L, 1 );
	int dpfail = luaL_checkinteger( L, 2 );
	int dppass = luaL_checkinteger( L, 3 );

	glStencilOp( sfail, dpfail, dppass );

	return 0;
}

/*
> RL.glStencilOpSeparate( int face, int sfail, int dpfail, int dppass )

Set front and back stencil test actions
*/
int lglStencilOpSeparate( lua_State* L ) {
	int face = luaL_checkinteger( L, 1 );
	int sfail = luaL_checkinteger( L, 2 );
	int dpfail = luaL_checkinteger( L, 3 );
	int dppass = luaL_checkinteger( L, 4 );

	glStencilOpSeparate( face, sfail, dpfail, dppass );

	return 0;
}

/*
## OpenGL - Utility
*/

/*
> connection = RL.glGetString( int name, int|nil index )

Return a string describing the current GL connection. GL_EXTENSIONS returns the extension string supported by the implementation at index

- Success return string
*/
int lglGetString( lua_State* L ) {
	int name = luaL_checkinteger( L, 1 );

	if ( uluaIsNil( L, 2 ) ) {
		lua_pushstring( L, glGetString( name ) );
	}
	else {
		int index = luaL_checkinteger( L, 2 );

		lua_pushstring( L, glGetStringi( name, index ) );
	}

	return 1;
}
