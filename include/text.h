#pragma once

/* Validators. */
bool validFont( size_t id );
/* Loading. */
int lmodelsLoadFont( lua_State *L );
/* Drawing. */
int ltextDrawFPS( lua_State *L );
int ltextDrawText( lua_State *L );
