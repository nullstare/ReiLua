#pragma once

/* Loading. */
int ltextGetFontDefault( lua_State *L );
int ltextLoadFont( lua_State *L );
int ltextLoadFontEx( lua_State *L );
int ltextLoadFontFromImage( lua_State *L );
int ltextIsFontReady( lua_State *L );
int ltextUnloadFont( lua_State *L );
/* Drawing. */
int ltextDrawFPS( lua_State *L );
int ltextDrawText( lua_State *L );
int ltextDrawTextPro( lua_State *L );
/* Misc. */
int ltextMeasureText( lua_State *L );
int ltextGetFontBaseSize( lua_State *L );
int ltextGetFontGlyphCount( lua_State *L );
int ltextGetFontGlyphPadding( lua_State *L );
int ltextGetFontTexture( lua_State *L );
