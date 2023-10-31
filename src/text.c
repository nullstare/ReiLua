#include "main.h"
#include "state.h"
#include "text.h"
#include "textures.h"
#include "lua_core.h"

/*
## Text - Loading
*/

/*
> RL.GetFontDefault()

Get the default Font. Return as lightuserdata
*/
int ltextGetFontDefault( lua_State *L ) {
	lua_pushlightuserdata( L, &state->defaultFont );

	return 1;
}

/*
> font = RL.LoadFont( string fileName )

Load font from file into GPU memory (VRAM)

- Failure return nil
- Success return Font
*/
int ltextLoadFont( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushFont( L, LoadFont( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> font = RL.LoadFontEx( string fileName, int fontSize, int{} fontChars )

Load font from file with extended parameters, use NULL for fontChars to load the default character set

- Failure return nil
- Success return Font
*/
int ltextLoadFontEx( lua_State *L ) {
	int fontSize = luaL_checkinteger( L, 2 );

	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		if ( lua_istable( L, 3 ) ) {
			int glyphCount = uluaGetTableLenIndex( L, 3 );
			int fontChars[ glyphCount ];
		
			int t = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t ) != 0 ) {
				fontChars[i] = lua_tointeger( L, -1 );

				i++;
				lua_pop( L, 1 );
			}
			uluaPushFont( L, LoadFontEx( lua_tostring( L, 1 ), fontSize, fontChars, glyphCount ) );

			return 1;
		}
		uluaPushFont( L, LoadFontEx( lua_tostring( L, 1 ), fontSize, NULL, 0 ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> font = RL.LoadFontFromImage( Image image, Color key, int firstChar )

Load font from Image ( XNA style)

- Success return Font
*/
int ltextLoadFontFromImage( lua_State *L ) {
	Image *image = uluaGetImage( L, 1 );
	Color key = uluaGetColorIndex( L, 2 );
	int firstChar = luaL_checkinteger( L, 3 );

	uluaPushFont( L, LoadFontFromImage( *image, key, firstChar ) );

	return 1;
}

/*
> isReady = RL.IsFontReady( Font font )

Check if a font is ready

- Success return bool
*/
int ltextIsFontReady( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	lua_pushboolean( L, IsFontReady( *font ) );

	return 1;
}

/*
> RL.UnloadFont( Font font )

Unload font from GPU memory (VRAM)
*/
int ltextUnloadFont( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	UnloadFont( *font );

	return 0;
}

/*
## Text - Draw
*/

/*
> RL.DrawFPS( Vector2 pos )

Draw current FPS
*/
int ltextDrawFPS( lua_State *L ) {
	Vector2 pos = uluaGetVector2Index( L, 1 );

	DrawFPS( pos.x, pos.y );

	return 0;
}

/*
> RL.DrawText( string text, Vector2 position, float fontSize, Color tint )

Draw text (using default font)
*/
int ltextDrawText( lua_State *L ) {
	Vector2 position = uluaGetVector2Index( L, 2 );
	float fontSize = luaL_checknumber( L, 3 );
	Color tint = uluaGetColorIndex( L, 4 );

	DrawText( luaL_checkstring( L, 1 ), position.x, position.y, fontSize, tint );

	return 0;
}

/*
> RL.DrawTextEx( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters
*/
int ltextDrawTextEx( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2Index( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	Color tint = uluaGetColorIndex( L, 6 );

	DrawTextEx( *font, luaL_checkstring( L, 2 ), position, fontSize, spacing, tint );

	return 0;
}

/*
> RL.DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters (rotation)
*/
int ltextDrawTextPro( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2Index( L, 3 );
	Vector2 origin = uluaGetVector2Index( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	float fontSize = luaL_checknumber( L, 6 );
	float spacing = luaL_checknumber( L, 7 );
	Color tint = uluaGetColorIndex( L, 8 );

	DrawTextPro( *font, luaL_checkstring( L, 2 ), position, origin, rotation, fontSize, spacing, tint );

	return 0;
}

/*
> RL.DrawTextCodepoint( Font font, int codepoint, Vector2 position, float fontSize, Color tint )

Draw one character (codepoint)
*/
int ltextDrawTextCodepoint( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int codepoint = luaL_checkinteger( L, 2 );
	Vector2 position = uluaGetVector2Index( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	Color tint = uluaGetColorIndex( L, 5 );

	DrawTextCodepoint( *font, codepoint, position, fontSize, tint );

	return 0;
}

/*
> RL.DrawTextCodepoints( Font font, int{} codepoints, Vector2 position, float fontSize, float spacing, Color tint )

Draw multiple character (codepoint)
*/
int ltextDrawTextCodepoints( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2Index( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	Color tint = uluaGetColorIndex( L, 6 );

	int count = uluaGetTableLenIndex( L, 2 );
	int codepoints[ count ];

	int t = 2;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		codepoints[i] = lua_tointeger( L, -1 );

		i++;
		lua_pop( L, 1 );
	}
	DrawTextCodepoints( *font, codepoints, count, position, fontSize, spacing, tint );

	return 0;
}

/*
## Text - Font info functions
*/

/*
> size = RL.MeasureText( Font font, string text, float fontSize, float spacing )

Measure string size for Font

- Success return Vector2
*/
int ltextMeasureText( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	float fontSize = luaL_checknumber( L, 3 );
	float spacing = luaL_checknumber( L, 4 );

	uluaPushVector2( L, MeasureTextEx( *font, luaL_checkstring( L, 2 ), fontSize, spacing ) );

	return 1;
}

/*
> index = RL.GetGlyphIndex( Font font, int codepoint )

Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found

- Success return int
*/
int ltextGetGlyphIndex( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int codepoint = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, GetGlyphIndex( *font, codepoint ) );

	return 1;
}

/*
> glyphInfo = RL.GetGlyphInfo( Font font, int codepoint )

Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found.
Return Image as lightuserdata

- Success return GlyphInfo
*/
int ltextGetGlyphInfo( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int codepoint = luaL_checkinteger( L, 2 );

	int id = GetGlyphIndex( *font, codepoint );
	uluaPushGlyphInfo( L, font->glyphs[id], &font->glyphs[id].image );

	return 1;
}

/*
> rect = RL.GetGlyphAtlasRec( Font font, int codepoint )

Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

- Success return Rectangle
*/
int ltextGetGlyphAtlasRec( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int codepoint = luaL_checkinteger( L, 2 );

	uluaPushRectangle( L, GetGlyphAtlasRec( *font, codepoint ) );

	return 1;
}

/*
> baseSize = RL.GetFontBaseSize( Font font )

Get font base size (default chars height)

- Success return int
*/
int ltextGetFontBaseSize( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	lua_pushinteger( L, font->baseSize );

	return 1;
}

/*
> glyphCount = RL.GetFontGlyphCount( Font font )

Get font number of glyph characters

- Success return int
*/
int ltextGetFontGlyphCount( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	lua_pushinteger( L, font->glyphCount );

	return 1;
}

/*
> glyphPadding = RL.GetFontGlyphPadding( Font font )

Get font padding around the glyph characters

- Success return int
*/
int ltextGetFontGlyphPadding( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	lua_pushinteger( L, font->glyphPadding );

	return 1;
}

/*
> texture = RL.GetFontTexture( Font font )

Get font texture atlas containing the glyphs. Return as lightuserdata

- Success return Texture
*/
int ltextGetFontTexture( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );

	// uluaPushTexture( L, font->texture );
	lua_pushlightuserdata( L, &font->texture );

	return 1;
}
