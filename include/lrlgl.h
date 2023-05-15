#pragma once

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