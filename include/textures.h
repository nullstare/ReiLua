#pragma once

enum TEXTURE_SOURCES { TEXTURE_SOURCE_TEXTURE, TEXTURE_SOURCE_RENDER_TEXTURE };

/* Validators. */
bool validImage( size_t id );
bool validTexture( size_t id );
bool validRenderTexture( size_t id );
bool validSourceTexture( size_t id );
Texture2D* texturesGetSourceTexture( size_t index );
/* File. */
int ltexturesLoadImage( lua_State *L );
int ltexturesGenImageColor( lua_State *L );
int ltexturesUnloadImage( lua_State *L );
int ltexturesLoadTexture( lua_State *L );
int ltexturesLoadTextureFromImage( lua_State *L );
int ltexturesUnloadTexture( lua_State *L );
int ltexturesLoadRenderTexture( lua_State *L );
int ltexturesUnloadRenderTexture( lua_State *L );
/* Image Drawing. */
int ltexturesImageClearBackground( lua_State *L );
int ltexturesImageDrawPixel( lua_State *L );
int ltexturesImageDrawLine( lua_State *L );
int ltexturesImageDrawCircle( lua_State *L );
int ltexturesImageDrawRectangle( lua_State *L );
int ltexturesImageDrawRectangleLines( lua_State *L );
int ltexturesImageDraw( lua_State *L );
int ltexturesImageDrawTextEx( lua_State *L );
/* Texture Drawing. */
int ltexturesDrawTexture( lua_State *L );
int ltexturesDrawTextureRec( lua_State *L );
int ltexturesDrawTextureTiled( lua_State *L );
int ltexturesDrawTexturePro( lua_State *L );
int ltexturesDrawTextureNPatch( lua_State *L );
int ltexturesDrawTexturePoly( lua_State *L );
int ltexturesBeginTextureMode( lua_State *L );
int ltexturesEndTextureMode( lua_State *L );
int ltexturesSetTextureSource( lua_State *L );
int ltexturesGetTextureSource( lua_State *L );
/* Conf. */
int ltexturesGenTextureMipmaps( lua_State *L );
int ltexturesSetTextureFilter( lua_State *L );
int ltexturesSetTextureWrap( lua_State *L );
int ltexturesGetTextureSize( lua_State *L );
/* Color/pixel */
int ltexturesColorFromHSV( lua_State *L );
