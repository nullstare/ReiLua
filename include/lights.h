#pragma once

/* Light management functions. */
int llightsCreateLight( lua_State *L );
int llightsUpdateLightValues( lua_State *L );
int llightsSetLightType( lua_State *L );
int llightsSetLightPosition( lua_State *L );
int llightsSetLightTarget( lua_State *L );
int llightsSetLightColor( lua_State *L );
int llightsSetLightEnabled( lua_State *L );
int llightsGetLightType( lua_State *L );
int llightsGetLightPosition( lua_State *L );
int llightsGetLightTarget( lua_State *L );
int llightsGetLightColor( lua_State *L );
int llightsIsLightEnabled( lua_State *L );
