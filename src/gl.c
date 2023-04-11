#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "textures.h"
#include "lgl.h"

/*
## OpenGL - Framebuffer management
*/

/*
> success = RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )

Copy a block of pixels from one framebuffer object to another.
Use -1 RenderTexture for window framebuffer.

- Failure return false
- Success return true
*/
int lglBlitFramebuffer( lua_State *L ) {
	if ( !lua_isnumber( L, 1) || !lua_isnumber( L, 2 ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 )	|| !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int srcTexId = lua_tointeger( L, 1 );
	int dstTexId = lua_tointeger( L, 2 );
	Rectangle srcRect = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 4 );
	int mask = lua_tointeger( L, 5 );
	int filter = lua_tointeger( L, 6 );

	if ( ( !validRenderTexture( srcTexId ) && srcTexId != -1 ) && ( !validRenderTexture( dstTexId ) && dstTexId != -1 ) ) {
		lua_pushboolean( L, false );
		return 1;
	}

	if ( srcTexId == -1 ) {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	}
	else {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, state->renderTextures[ srcTexId ]->id );
	}

	if ( dstTexId == -1 ) {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	}
	else {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, state->renderTextures[ dstTexId ]->id );
	}

	glBlitFramebuffer(
		srcRect.x, srcRect.y, srcRect.width, srcRect.height,
		dstRect.x, dstRect.y, dstRect.width, dstRect.height,
		mask,
		filter
		// GL_COLOR_BUFFER_BIT, 									// mask
		// GL_NEAREST												// filter
	);

	lua_pushboolean( L, true );

	return 1;
}