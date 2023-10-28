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
	// TODO Currently doesn't support setting window render target because of luaL_checkudata.
	RenderTexture *srcTex = luaL_checkudata( L, 1, "RenderTexture" );
	RenderTexture *dstTex = luaL_checkudata( L, 2, "RenderTexture" );
	Rectangle srcRect = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 4 );
	int mask = luaL_checkinteger( L, 5 );
	int filter = luaL_checkinteger( L, 6 );

	if ( lua_tointeger( L, 1 ) == -1 ) {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	}
	else {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, srcTex->id );
	}

	if ( lua_tointeger( L, 2 ) == -1 ) {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	}
	else {
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
