#pragma once

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
/* Textures management */
int lrlglLoadTexture( lua_State *L );
int lrlglLoadTextureDepth( lua_State *L );
int lrlglUnloadTexture( lua_State *L );
/* Framebuffer management (fbo) */
int lrlglLoadFramebuffer( lua_State *L );
int lrlglFramebufferAttach( lua_State *L );
int lrlglFramebufferComplete( lua_State *L );
int lrlglUnloadFramebuffer( lua_State *L );