#pragma once

/* Validators. */
bool validFont( size_t id );
/* Loading. */
int ltextLoadFont( lua_State *L );
int ltextUnloadFont( lua_State *L );
/* Drawing. */
int ltextDrawFPS( lua_State *L );
int ltextDrawText( lua_State *L );
int ltextDrawTextPro( lua_State *L );
