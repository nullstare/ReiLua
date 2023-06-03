#pragma once

/* Matrix operations */
int lrlglMatrixMode( lua_State *L );
int lrlglPushMatrix( lua_State *L );
int lrlglPopMatrix( lua_State *L );
int lrlglLoadIdentity( lua_State *L );
int lrlglTranslatef( lua_State *L );
int lrlglRotatef( lua_State *L );
int lrlglScalef( lua_State *L );
int lrlglMultMatrixf( lua_State *L );
int lrlglFrustum( lua_State *L );
int lrlglOrtho( lua_State *L );
int lrlglViewport( lua_State *L );
/* Vertex level operations */
int lrlglBegin( lua_State *L );
int lrlglEnd( lua_State *L );
int lrlglVertex2f( lua_State *L );
int lrlglVertex3f( lua_State *L );
int lrlglTexCoord2f( lua_State *L );
int lrlglNormal3f( lua_State *L );
int lrlglColor4ub( lua_State *L );
int lrlglColor3f( lua_State *L );
int lrlglColor4f( lua_State *L );
/* Textures state */
int lrlglActiveTextureSlot( lua_State *L );
int lrlglEnableTexture( lua_State *L );
int lrlglDisableTexture( lua_State *L );
int lrlglEnableTextureCubemap( lua_State *L );
int lrlglDisableTextureCubemap( lua_State *L );
int lrlglTextureParameters( lua_State *L );
int lrlglCubemapParameters( lua_State *L );
/* Framebuffer state. */
int lrlglEnableFramebuffer( lua_State *L );
int lrlglDisableFramebuffer( lua_State *L );
int lrlglActiveDrawBuffers( lua_State *L );
/* General render state. */
int lrlglEnableColorBlend( lua_State *L );
int lrlglDisableColorBlend( lua_State *L );
int lrlglEnableDepthTest( lua_State *L );
int lrlglDisableDepthTest( lua_State *L );
int lrlglEnableDepthMask( lua_State *L );
int lrlglDisableDepthMask( lua_State *L );
int lrlglEnableBackfaceCulling( lua_State *L );
int lrlglDisableBackfaceCulling( lua_State *L );
int lrlglSetCullFace( lua_State *L );
int lrlglSetLineWidth( lua_State *L );
int lrlglGetLineWidth( lua_State *L );
int lrlglEnableSmoothLines( lua_State *L );
int lrlglDisableSmoothLines( lua_State *L );
/* Initialization functions */
int lrlglGetVersion( lua_State *L );
/* Render batch management */
int lrlglDrawRenderBatchActive( lua_State *L );
int lrlglCheckRenderBatchLimit( lua_State *L );
int lrlglSetTexture( lua_State *L );
/* Textures management */
int lrlglLoadTexture( lua_State *L );
int lrlglLoadTextureDepth( lua_State *L );
int lrlglUnloadTexture( lua_State *L );
/* Framebuffer management (fbo) */
int lrlglLoadFramebuffer( lua_State *L );
int lrlglFramebufferAttach( lua_State *L );
int lrlglFramebufferComplete( lua_State *L );
int lrlglUnloadFramebuffer( lua_State *L );