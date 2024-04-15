#pragma once

/* Rendering. */
int lglClear( lua_State* L );
/* Frame Buffers. */
int lglBlitFramebuffer( lua_State* L );
/* State Management. */
int lglEnable( lua_State* L );
int lglDisable( lua_State* L );
int lglStencilFunc( lua_State* L );
int lglStencilFuncSeparate( lua_State* L );
int lglStencilMask( lua_State* L );
int lglStencilMaskSeparate( lua_State* L );
int lglStencilOp( lua_State* L );
int lglStencilOpSeparate( lua_State* L );
/* Utility. */
int lglGetString( lua_State* L );
