#pragma once

void unloadGlyphInfo( GlyphInfo* glyph );
/* Font loading/unloading functions. */
int ltextGetFontDefault( lua_State* L );
int ltextLoadFont( lua_State* L );
int ltextLoadFontEx( lua_State* L );
int ltextLoadFontFromImage( lua_State* L );
int ltextLoadFontFromMemory( lua_State* L );
int ltextLoadFontFromData( lua_State* L );
int ltextIsFontReady( lua_State* L );
int ltextLoadFontData( lua_State* L );
int ltextGenImageFontAtlas( lua_State* L );
int ltextUnloadFont( lua_State* L );
int ltextExportFontAsCode( lua_State* L );
/* Text drawing functions. */
int ltextDrawFPS( lua_State* L );
int ltextDrawText( lua_State* L );
int ltextDrawTextEx( lua_State* L );
int ltextDrawTextPro( lua_State* L );
int ltextDrawTextCodepoint( lua_State* L );
int ltextDrawTextCodepoints( lua_State* L );
int ltextDrawTextBoxed( lua_State* L );
int ltextDrawTextBoxedTinted( lua_State* L );
/* Text font info functions. */
int ltextSetTextLineSpacing( lua_State* L );
int ltextMeasureText( lua_State* L );
int ltextGetGlyphIndex( lua_State* L );
int ltextGetGlyphInfo( lua_State* L );
int ltextGetGlyphInfoByIndex( lua_State* L );
int ltextGetGlyphAtlasRec( lua_State* L );
int ltextGetGlyphAtlasRecByIndex( lua_State* L );
int ltextGetFontBaseSize( lua_State* L );
int ltextGetFontGlyphCount( lua_State* L );
int ltextGetFontGlyphPadding( lua_State* L );
int ltextGetFontTexture( lua_State* L );
/* GlyphInfo management functions. */
int ltextLoadGlyphInfo( lua_State* L );
int ltextUnloadGlyphInfo( lua_State* L );
int ltextSetGlyphInfoValue( lua_State* L );
int ltextSetGlyphInfoOffset( lua_State* L );
int ltextSetGlyphInfoAdvanceX( lua_State* L );
int ltextSetGlyphInfoImage( lua_State* L );
int ltextGetGlyphInfoValue( lua_State* L );
int ltextGetGlyphInfoOffset( lua_State* L );
int ltextGetGlyphInfoAdvanceX( lua_State* L );
int ltextGetGlyphInfoImage( lua_State* L );
/* Text codepoints management functions (unicode characters). */
int ltextLoadUTF8( lua_State* L );
int ltextLoadCodepoints( lua_State* L );
int ltextGetCodepointCount( lua_State* L );
int ltextGetCodepoint( lua_State* L );
int ltextGetCodepointNext( lua_State* L );
int ltextGetCodepointPrevious( lua_State* L );
int ltextCodepointToUTF8( lua_State* L );
/* Text strings management functions (no UTF-8 strings, only byte chars) */
int ltextTextInsert( lua_State* L );
int ltextTextSplit( lua_State* L );
