#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "lgl.h"

/*
## OpenGL - Framebuffer management
*/

/*
> RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use -1 RenderTexture for window framebuffer.
*/
int lglBlitFramebuffer( lua_State *L ) {
	if ( !( lua_isuserdata( L, 1 ) || lua_isnil( L, 1 ) ) || !( lua_isuserdata( L, 2 ) || lua_isnil( L, 2 ) ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Argument needs to be RenderTexture or nil" );
		lua_pushnil( L );
		return 1;
	}
	Rectangle srcRect = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 4 );
	int mask = luaL_checkinteger( L, 5 );
	int filter = luaL_checkinteger( L, 6 );

	if ( lua_isnil( L, 1 ) ) {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	}
	else {
		RenderTexture *srcTex = luaL_checkudata( L, 1, "RenderTexture" );
		glBindFramebuffer( GL_READ_FRAMEBUFFER, srcTex->id );
	}

	if ( lua_isnil( L, 2 ) ) {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	}
	else {
		RenderTexture *dstTex = luaL_checkudata( L, 2, "RenderTexture" );
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
}
