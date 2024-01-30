#include "main.h"
#include "state.h"
#include "text.h"
#include "textures.h"
#include "lua_core.h"

void unloadGlyphInfo( GlyphInfo *glyph ) {
	UnloadImage( glyph->image );
}

// DrawTextBoxed is modified DrawTextBoxedSelectable from raylib [text] example - Rectangle bounds

// Draw text using font inside rectangle limits
static int DrawTextBoxed( Font font, const char *text, Rectangle rec, float fontSize, float spacing,
bool wordWrap, Color *tints, int tintCount, Color *backTints, int backTintCount )
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position
	Color tint = BLACK;
	Color backTint = BLANK;
	Vector2 mousePos = GetMousePosition();
	int mouseChar = -1;

    for ( int i = 0, k = 0; i < length; i++, k++)
    {
		if ( i < tintCount ) {
			tint = tints[i];
		}
		if ( i < backTintCount ) {
			backTint = backTints[i];
		}
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                // bool isGlyphSelected = false;
                // if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                // {
                //     DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                //     isGlyphSelected = true;
                // }

				if ( CheckCollisionPointRec( mousePos, (Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor } ) ) {
					mouseChar = i;
				}

				if ( 0 < backTint.a ) {
					DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, backTint);
				}

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    // DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                    DrawTextCodepoint( font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, tint );
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                // selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
	return mouseChar;
}

static inline void getCodepoints( lua_State *L, int codepoints[], int index ) {
	int t = index;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		codepoints[i] = lua_tointeger( L, -1 );
		i++;
		lua_pop( L, 1 );
	}
}

/*
## Text - Font loading/unloading functions
*/

/*
> font = RL.GetFontDefault()

Get the default Font. Return as lightuserdata

- Success return Font
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
> font = RL.LoadFontEx( string fileName, int fontSize, int{} codepoints )

Load font from file with extended parameters, use NULL for codepoints to load the default character set

- Failure return nil
- Success return Font
*/
int ltextLoadFontEx( lua_State *L ) {
	int fontSize = luaL_checkinteger( L, 2 );

	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		if ( lua_istable( L, 3 ) ) {
			int codepointCount = uluaGetTableLen( L, 3 );
			int codepoints[ codepointCount ];

			getCodepoints( L, codepoints, 3 );
			uluaPushFont( L, LoadFontEx( lua_tostring( L, 1 ), fontSize, codepoints, codepointCount ) );

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

Load font from Image (XNA style)

- Success return Font
*/
int ltextLoadFontFromImage( lua_State *L ) {
	Image *image = uluaGetImage( L, 1 );
	Color key = uluaGetColor( L, 2 );
	int firstChar = luaL_checkinteger( L, 3 );

	uluaPushFont( L, LoadFontFromImage( *image, key, firstChar ) );

	return 1;
}

/*
> font = RL.LoadFontFromMemory( string fileType, Buffer fileData, int fontSize, int{} codepoints )

Load font from memory buffer, fileType refers to extension: i.e. '.ttf'. NOTE: fileData type should be unsigned char

- Success return Font
*/
int ltextLoadFontFromMemory( lua_State *L ) {
	const char *fileType = luaL_checkstring( L, 1 );
	Buffer *fileData = uluaGetBuffer( L, 2 );
	int fontSize = luaL_checkinteger( L, 3 );

	if ( lua_istable( L, 4 ) ) {
		int codepointCount = uluaGetTableLen( L, 4 );
		int codepoints[ codepointCount ];

		getCodepoints( L, codepoints, 4 );
		uluaPushFont( L, LoadFontFromMemory( fileType, fileData->data, fileData->size, fontSize, codepoints, codepointCount ) );

		return 1;
	}
	/* If no codepoints provided. */
	uluaPushFont( L, LoadFontFromMemory( fileType, fileData->data, fileData->size, fontSize, NULL, 0 ) );

	return 1;
}

/*
> font = RL.LoadFontFromData( Font{} fontData )

Load Font from data

- Success return Font
*/
int ltextLoadFontFromData( lua_State *L ) {
	luaL_checktype( L, 1, LUA_TTABLE );

	Font font = { 0 };

	int t = 1;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "baseSize", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			font.baseSize = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "glyphCount", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			font.glyphCount = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "glyphPadding", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			font.glyphPadding = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "texture", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			font.texture = *uluaGetTexture( L, lua_gettop( L ) );
		}
		else if ( strcmp( "recs", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			int recCount = uluaGetTableLen( L, lua_gettop( L ) );
			font.recs = malloc( recCount * sizeof( Rectangle ) );
			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				font.recs[i] = uluaGetRectangle( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
		}
		else if ( strcmp( "glyphs", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			int glyphCount = uluaGetTableLen( L, lua_gettop( L ) );
			font.glyphs = malloc( glyphCount * sizeof( GlyphInfo ) );
			int t2 = lua_gettop( L );
			int i = 0;
			lua_pushnil( L );

			while ( lua_next( L, t2 ) != 0 ) {
				font.glyphs[i] = *uluaGetGlyphInfo( L, lua_gettop( L ) );
				i++;
				lua_pop( L, 1 );
			}
		}
		lua_pop( L, 1 );
	}
	uluaPushFont( L, font );

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
> glyphs = RL.LoadFontData( Buffer fileData, int fontSize, int{} codepoints, int type )

Load font data for further use. NOTE: fileData type should be unsigned char

- Success return GlyphInfo{}
*/
int ltextLoadFontData( lua_State *L ) {
	Buffer *fileData = uluaGetBuffer( L, 1 );
	int fontSize = luaL_checkinteger( L, 2 );
	int type = luaL_checkinteger( L, 4 );
	int codepointCount = 95; // In case no chars count provided, default to 95.

	if ( lua_istable( L, 3 ) ) {
		codepointCount = uluaGetTableLen( L, 3 );
		int codepoints[ codepointCount ];

		getCodepoints( L, codepoints, 3 );
		GlyphInfo *glyphs = LoadFontData( fileData->data, fileData->size, fontSize, codepoints, codepointCount, type );
		lua_createtable( L, codepointCount, 0 );

		for ( int i = 0; i < codepointCount; i++ ) {
			uluaPushGlyphInfo( L, glyphs[i] );
			lua_rawseti( L, -2, i + 1 );
		}
		UnloadFontData( glyphs, codepointCount );

		return 1;
	}
	/* If no codepoints provided. */
	GlyphInfo *glyphs = LoadFontData( fileData->data, fileData->size, fontSize, NULL, 0, type );
	lua_createtable( L, codepointCount, 0 );

	for ( int i = 0; i < codepointCount; i++ ) {
		uluaPushGlyphInfo( L, glyphs[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	UnloadFontData( glyphs, codepointCount );

	return 1;
}

/*
> image, rectangles = RL.GenImageFontAtlas( GlyphInfo{} glyphs, int fontSize, int padding, int packMethod )

Generate image font atlas using chars info. NOTE: Packing method: 0-Default, 1-Skyline

- Success Image, Rectangle{}
*/
int ltextGenImageFontAtlas( lua_State *L ) {
	int fontSize = luaL_checkinteger( L, 2 );
	int padding = luaL_checkinteger( L, 3 );
	int packMethod = luaL_checkinteger( L, 4 );

	int glyphCount = uluaGetTableLen( L, 1 );
	GlyphInfo glyphs[ glyphCount ];
	Rectangle *glyphRecs;

	int t = 1;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		glyphs[i] = *uluaGetGlyphInfo( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	uluaPushImage( L, GenImageFontAtlas( glyphs, &glyphRecs, glyphCount, fontSize, padding, packMethod ) );
	lua_createtable( L, glyphCount, 0 );

	for ( i = 0; i < glyphCount; i++ ) {
		uluaPushRectangle( L, glyphRecs[i] );
		lua_rawseti( L, -2, i + 1 );
	}

	return 2;
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
> RL.ExportFontAsCode( Font font, string fileName )

Export font as code file, returns true on success

- Success return bool
*/
int ltextExportFontAsCode( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	const char *fileName = luaL_checkstring( L, 2 );

	lua_pushboolean( L, ExportFontAsCode( *font, fileName ) );

	return 1;
}

/*
## Text - Text drawing functions
*/

/*
> RL.DrawFPS( Vector2 pos )

Draw current FPS
*/
int ltextDrawFPS( lua_State *L ) {
	Vector2 pos = uluaGetVector2( L, 1 );

	DrawFPS( pos.x, pos.y );

	return 0;
}

/*
> RL.DrawText( string text, Vector2 position, float fontSize, Color tint )

Draw text (using default font)
*/
int ltextDrawText( lua_State *L ) {
	Vector2 position = uluaGetVector2( L, 2 );
	float fontSize = luaL_checknumber( L, 3 );
	Color tint = uluaGetColor( L, 4 );

	DrawText( luaL_checkstring( L, 1 ), position.x, position.y, fontSize, tint );

	return 0;
}

/*
> RL.DrawTextEx( Font font, string text, Vector2 position, float fontSize, float spacing, Color tint )

Draw text using font and additional parameters
*/
int ltextDrawTextEx( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	DrawTextEx( *font, luaL_checkstring( L, 2 ), position, fontSize, spacing, tint );

	return 0;
}

/*
> RL.DrawTextPro( Font font, string text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint )

Draw text using Font and pro parameters (rotation)
*/
int ltextDrawTextPro( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2( L, 3 );
	Vector2 origin = uluaGetVector2( L, 4 );
	float rotation = luaL_checknumber( L, 5 );
	float fontSize = luaL_checknumber( L, 6 );
	float spacing = luaL_checknumber( L, 7 );
	Color tint = uluaGetColor( L, 8 );

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
	Vector2 position = uluaGetVector2( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	Color tint = uluaGetColor( L, 5 );

	DrawTextCodepoint( *font, codepoint, position, fontSize, tint );

	return 0;
}

/*
> RL.DrawTextCodepoints( Font font, int{} codepoints, Vector2 position, float fontSize, float spacing, Color tint )

Draw multiple character (codepoint)
*/
int ltextDrawTextCodepoints( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	Vector2 position = uluaGetVector2( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	Color tint = uluaGetColor( L, 6 );

	int codepointCount = uluaGetTableLen( L, 2 );
	int codepoints[ codepointCount ];

	int t = 2;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		codepoints[i] = lua_tointeger( L, -1 );

		i++;
		lua_pop( L, 1 );
	}
	DrawTextCodepoints( *font, codepoints, codepointCount, position, fontSize, spacing, tint );

	return 0;
}

/*
> mouseCharId = RL.DrawTextBoxed(Font font, string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint )

Draw text using font inside rectangle limits. Return character id from mouse position (default -1). Function from raylib [text] example - Rectangle bounds.

- Success return int
*/
int ltextDrawTextBoxed( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	const char *text = luaL_checkstring( L, 2 );
	Rectangle rec = uluaGetRectangle( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	bool wordWrap = uluaGetBoolean( L, 6 );
	Color tint = uluaGetColor( L, 7 );

	lua_pushinteger( L, DrawTextBoxed( *font, text, rec, fontSize, spacing, wordWrap, &tint, 1, NULL, 0 ) );

	return 1;
}

/*
> mouseCharId = RL.DrawTextBoxedTinted( Font font, string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tints, Color backTints )

Draw text using font inside rectangle limits with support for tint and background tint for each character. Return character id from mouse position (default -1)

- Success return int
*/
int ltextDrawTextBoxedTinted( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	const char *text = luaL_checkstring( L, 2 );
	Rectangle rec = uluaGetRectangle( L, 3 );
	float fontSize = luaL_checknumber( L, 4 );
	float spacing = luaL_checknumber( L, 5 );
	bool wordWrap = uluaGetBoolean( L, 6 );
	int tintCount = uluaGetTableLen( L, 7 );
	int backTintCount = uluaGetTableLen( L, 8 );

	Color tints[ tintCount ];
	Color backTints[ backTintCount ];

	/* Tints. */
	int t = 7, i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		tints[i] = uluaGetColor( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	/* Back tints. */
	t = 8; i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		backTints[i] = uluaGetColor( L, lua_gettop( L ) );
		i++;
		lua_pop( L, 1 );
	}
	lua_pushinteger( L, DrawTextBoxed( *font, text, rec, fontSize, spacing, wordWrap, tints, tintCount, backTints, backTintCount ) );

	return 1;
}

/*
## Text - Text font info functions
*/

/*
> size = RL.SetTextLineSpacing( int spacing )

Set vertical line spacing when drawing with line-breaks
*/
int ltextSetTextLineSpacing( lua_State *L ) {
	int spacing = luaL_checkinteger( L, 1 );

	SetTextLineSpacing( spacing );
}

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

Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found. Return as lightuserdata

- Success return GlyphInfo
*/
int ltextGetGlyphInfo( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int codepoint = luaL_checkinteger( L, 2 );

	int id = GetGlyphIndex( *font, codepoint );
	lua_pushlightuserdata( L, &font->glyphs[id] );

	return 1;
}

/*
> glyphInfo = RL.GetGlyphInfoByIndex( Font font, int index )

Get glyph font info data by index. Return as lightuserdata

- Failure return nil
- Success return GlyphInfo
*/
int ltextGetGlyphInfoByIndex( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int index = luaL_checkinteger( L, 2 );

	if ( 0 <= index && index < font->glyphCount ) {
		lua_pushlightuserdata( L, &font->glyphs[ index ] );
	}
	else {
		TraceLog( state->logLevelInvalid, "Glyph index %d out of bounds", index );
		lua_pushnil( L );
	}

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
> rect = RL.GetGlyphAtlasRecByIndex( Font font, int index )

Get glyph rectangle in font atlas by index

- Failure return nil
- Success return Rectangle
*/
int ltextGetGlyphAtlasRecByIndex( lua_State *L ) {
	Font *font = uluaGetFont( L, 1 );
	int index = luaL_checkinteger( L, 2 );

	if ( 0 <= index && index < font->glyphCount ) {
		uluaPushRectangle( L, font->recs[ index ] );
	}
	else {
		TraceLog( state->logLevelInvalid, "Glyph index %d out of bounds", index );
		lua_pushnil( L );
	}

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

	lua_pushlightuserdata( L, &font->texture );

	return 1;
}

/*
## Text - GlyphInfo management functions
*/

/*
> glyphInfo = RL.LoadGlyphInfo( GlyphInfo{} glyphInfoData )

Load GlyphInfo from data

- Success return GlyphInfo
*/
int ltextLoadGlyphInfo( lua_State *L ) {
	luaL_checktype( L, 1, LUA_TTABLE );

	GlyphInfo glyph = { 0 };

	int t = 1;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		if ( strcmp( "value", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			glyph.value = (unsigned int)luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "offsetX", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			glyph.offsetX = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "offsetY", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			glyph.offsetY = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "advanceX", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			glyph.advanceX = luaL_checkinteger( L, -1 );
		}
		else if ( strcmp( "image", (char*)lua_tostring( L, -2 ) ) == 0 ) {
			glyph.image = *uluaGetImage( L, lua_gettop( L ) );
		}
		lua_pop( L, 1 );
	}
	uluaPushGlyphInfo( L, glyph );

	return 1;
}

/*
> RL.UnloadGlyphInfo( GlyphInfo glyphInfo )

Unload glyphInfo image from CPU memory (RAM)
*/
int ltextUnloadGlyphInfo( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );

	unloadGlyphInfo( glyph );

	return 0;
}

/*
> RL.SetGlyphInfoValue( GlyphInfo glyphInfo, int value )

Set glyphInfo character value (Unicode)
*/
int ltextSetGlyphInfoValue( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );
	int value = luaL_checkinteger( L, 2 );

	glyph->value = value;

	return 0;
}

/*
> RL.SetGlyphInfoOffset( GlyphInfo glyphInfo, Vector2 offset )

Set glyphInfo character offset when drawing
*/
int ltextSetGlyphInfoOffset( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );
	Vector2 offset = uluaGetVector2( L, 2 );

	glyph->offsetX = (int)offset.x;
	glyph->offsetY = (int)offset.y;

	return 0;
}

/*
> RL.SetGlyphInfoAdvanceX( GlyphInfo glyphInfo, int advanceX )

Set glyphInfo character advance position X
*/
int ltextSetGlyphInfoAdvanceX( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );
	int advanceX = luaL_checkinteger( L, 2 );

	glyph->advanceX = advanceX;

	return 0;
}

/*
> RL.SetGlyphInfoImage( GlyphInfo glyphInfo, Image image )

Set glyphInfo character image data
*/
int ltextSetGlyphInfoImage( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );
	Image image = *uluaGetImage( L, 2 );

	glyph->image = image;

	return 0;
}

/*
> value = RL.GetGlyphInfoValue( GlyphInfo glyphInfo )

Get glyphInfo character value (Unicode)

- Success return int
*/
int ltextGetGlyphInfoValue( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );

	lua_pushinteger( L, glyph->value );

	return 1;
}

/*
> offset = RL.GetGlyphInfoOffset( GlyphInfo glyphInfo )

Get glyphInfo character offset when drawing

- Success return Vector2
*/
int ltextGetGlyphInfoOffset( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );

	uluaPushVector2( L, (Vector2){ glyph->offsetX, glyph->offsetY } );

	return 1;
}

/*
> advanceX = RL.GetGlyphInfoAdvanceX( GlyphInfo glyphInfo )

Get glyphInfo character advance position X

- Success return int
*/
int ltextGetGlyphInfoAdvanceX( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );

	lua_pushinteger( L, glyph->advanceX );

	return 1;
}

/*
> image = RL.GetGlyphInfoImage( GlyphInfo glyphInfo )

Get glyphInfo character image data. Return as lightuserdata

- Success return Image
*/
int ltextGetGlyphInfoImage( lua_State *L ) {
	GlyphInfo *glyph = uluaGetGlyphInfo( L, 1 );

	lua_pushlightuserdata( L, &glyph->image );

	return 1;
}

/*
## Text - Text codepoints management functions (unicode characters)
*/

/*
> string = RL.LoadUTF8( int{} codepoints )

Load UTF-8 text encoded from codepoints array

- Success return string
*/
int ltextLoadUTF8( lua_State *L ) {
	int codepointCount = uluaGetTableLen( L, 1 );
	int codepoints[ codepointCount ];
	getCodepoints( L, codepoints, 1 );

	char* string = LoadUTF8( codepoints, codepointCount );
	lua_pushstring( L, string );
	UnloadUTF8( string );

	return 1;
}

/*
> codepoints = RL.LoadCodepoints( string text )

Load all codepoints from a UTF-8 text string

- Success return int{}
*/
int ltextLoadCodepoints( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );

	int count = 0;
	int* codepoints = LoadCodepoints( text, &count );

	lua_createtable( L, count, 0 );

	for ( int i = 0; i < count; i++ ) {
		lua_pushinteger( L, codepoints[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	UnloadCodepoints( codepoints );

	return 1;
}

/*
> count = RL.GetCodepointCount( string text )

Get total number of codepoints in a UTF-8 encoded string

- Success return int
*/
int ltextGetCodepointCount( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );

	lua_pushinteger( L, GetCodepointCount( text ) );

	return 1;
}

/*
> codepoint, codepointSize = RL.GetCodepoint( string text )

Get codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int
*/
int ltextGetCodepoint( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );

	int codepointSize = 0;
	lua_pushinteger( L, GetCodepoint( text, &codepointSize ) );
	lua_pushinteger( L, codepointSize );

	return 2;
}

/*
> codepoint, codepointSize = RL.GetCodepointNext( string text )

Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int
*/
int ltextGetCodepointNext( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );

	int codepointSize = 0;
	lua_pushinteger( L, GetCodepointNext( text, &codepointSize ) );
	lua_pushinteger( L, codepointSize );

	return 2;
}

/*
> codepoint, codepointSize = RL.GetCodepointPrevious( string text )

Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure

- Success return int, int
*/
int ltextGetCodepointPrevious( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );

	int codepointSize = 0;
	lua_pushinteger( L, GetCodepointPrevious( text, &codepointSize ) );
	lua_pushinteger( L, codepointSize );

	return 2;
}

/*
> string = RL.CodepointToUTF8( int codepoint )

Encode one codepoint into UTF-8 byte array

- Success return string
*/
int ltextCodepointToUTF8( lua_State *L ) {
	int codepoint = luaL_checkinteger( L, 1 );

	int utf8Size = 0;
	char text[5] = { '\0' };
	const char* utf8 = CodepointToUTF8( codepoint, &utf8Size );
	memcpy( text, utf8, utf8Size );

	lua_pushstring( L, text );

	return 1;
}

/*
## Text - Text strings management functions (no UTF-8 strings, only byte chars)
*/

/*
> text = RL.TextInsert( string text, string insert, int position )

Insert text in a specific position, moves all text forward

- Success return string
*/
int ltextTextInsert( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );
	const char* insert = luaL_checkstring( L, 2 );
	int position = luaL_checkinteger( L, 3 );

	// char* result = TextInsert( text, insert, position ); // Bug in the raylib implementation.

	int textLen = TextLength( text );
	int insertLen = TextLength( insert );
	char* result = RL_MALLOC( textLen + insertLen + 1 );

	memcpy( result, text, position );
	memcpy( result + position, insert, insertLen );
	memcpy( result + position + insertLen, text + position, textLen - position );

	result[ textLen + insertLen ] = '\0';     // Make sure text string is valid!

	lua_pushstring( L, result );
	free( result );

	return 1;
}

/*
> splits = RL.TextSplit( string text, char delimiter )

Split text into multiple strings

- Success return string{}
*/
int ltextTextSplit( lua_State *L ) {
	const char* text = luaL_checkstring( L, 1 );
	const char* delimiter = luaL_checkstring( L, 2 );

	int count = 0;
	const char** splits = TextSplit( text, delimiter[0], &count );

	lua_createtable( L, count, 0 );

	for ( int i = 0; i < count; i++ ) {
		lua_pushstring( L, splits[i] );
		lua_rawseti( L, -2, i + 1 );
	}
	/* Note! No need to free. Uses static memory. */

	return 1;
}
