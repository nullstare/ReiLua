#pragma once

/* Arithmetic. */
int lbitAnd( lua_State* L );
int lbitOr( lua_State* L );
int lbitXor( lua_State* L );
int lbitNot( lua_State* L );
int lbitShiftLeft( lua_State* L );
int lbitShiftRight( lua_State* L );
int lbitSet( lua_State* L );
int lbitGet( lua_State* L );
int lbitToggle( lua_State* L );
