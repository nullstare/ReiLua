#pragma once

/* Font loading/unloading functions. */
int ltextGetFontDefault( lua_State *L );
int ltextLoadFont( lua_State *L );
int ltextLoadFontEx( lua_State *L );
int ltextLoadFontFromImage( lua_State *L );
int ltextIsFontReady( lua_State *L );
int ltextUnloadFont( lua_State *L );
/* Text drawing functions. */
int ltextDrawFPS( lua_State *L );
int ltextDrawText( lua_State *L );
int ltextDrawTextEx( lua_State *L );
int ltextDrawTextPro( lua_State *L );
int ltextDrawTextCodepoint( lua_State *L );
int ltextDrawTextCodepoints( lua_State *L );
int ltextDrawTextBoxed( lua_State *L );
int ltextDrawTextBoxedTinted( lua_State *L );
/* Text font info functions. */
int ltextMeasureText( lua_State *L );
int ltextGetGlyphIndex( lua_State *L );
int ltextGetGlyphInfo( lua_State *L );
int ltextGetGlyphAtlasRec( lua_State *L );
int ltextGetFontBaseSize( lua_State *L );
int ltextGetFontGlyphCount( lua_State *L );
int ltextGetFontGlyphPadding( lua_State *L );
int ltextGetFontTexture( lua_State *L );
