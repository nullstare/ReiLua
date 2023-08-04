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
	if ( !isValidRenderTexture( L, 1, true ) || !isValidRenderTexture( L, 2, true ) || !lua_istable( L, 3 )
	|| !lua_istable( L, 4 )	|| !lua_isnumber( L, 5 ) || !lua_isnumber( L, 6 ) ) {
		TraceLog( state->logLevelInvalid, "%s", "Bad call of function. RL.glBlitFramebuffer( RenderTexture srcTex, RenderTexture dstTex, Rectangle srcRect, Rectangle dstRect, int mask, int filter )" );
		lua_pushboolean( L, false );
		return 1;
	}
	RenderTexture2D srcTex = uluaGetRenderTexture( L, 1 );
	RenderTexture2D dstTex = uluaGetRenderTexture( L, 2 );
	Rectangle srcRect = uluaGetRectangleIndex( L, 3 );
	Rectangle dstRect = uluaGetRectangleIndex( L, 4 );
	int mask = lua_tointeger( L, 5 );
	int filter = lua_tointeger( L, 6 );

	if ( lua_tointeger( L, 1 ) == -1 ) {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	}
	else {
		glBindFramebuffer( GL_READ_FRAMEBUFFER, srcTex.id );
	}

	if ( lua_tointeger( L, 2 ) == -1 ) {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
	}
	else {
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, dstTex.id );
	}

	glBlitFramebuffer(
		srcRect.x, srcRect.y, srcRect.width, srcRect.height,
		dstRect.x, dstRect.y, dstRect.width, dstRect.height,
		mask,
		filter
	);

	glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

	lua_pushboolean( L, true );

	return 1;
}