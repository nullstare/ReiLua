#pragma once

enum TEXTURE_SOURCES { TEXTURE_SOURCE_TEXTURE, TEXTURE_SOURCE_RENDER_TEXTURE };

/* Validators. */
bool validImage( size_t id );
bool validTexture( size_t id );
bool validRenderTexture( size_t id );
bool validSourceTexture( size_t id );
Texture2D* texturesGetSourceTexture( size_t index );
/* Image Loading. */
int ltexturesLoadImage( lua_State *L );
int ltexturesLoadImageFromTexture( lua_State *L );
int ltexturesLoadImageFromScreen( lua_State *L );
int ltexturesUnloadImage( lua_State *L );
int ltexturesExportImage( lua_State *L );
int ltexturesExportImageAsCode( lua_State *L );
/* Image Generation. */
int ltexturesGenImageColor( lua_State *L );
int ltexturesGenImageGradientV( lua_State *L );
int ltexturesGenImageGradientH( lua_State *L );
int ltexturesGenImageGradientRadial( lua_State *L );
int ltexturesGenImageChecked( lua_State *L );
int ltexturesGenImageWhiteNoise( lua_State *L );
int ltexturesGenImageCellular( lua_State *L );
/* Image Manipulation Functions. */
int ltexturesImageCopy( lua_State *L );
int ltexturesImageFromImage( lua_State *L );
int ltexturesImageText( lua_State *L );
int ltexturesImageFormat( lua_State *L );
int ltexturesImageToPOT( lua_State *L );
int ltexturesImageCrop( lua_State *L );
int ltexturesImageAlphaCrop( lua_State *L );
int ltexturesImageAlphaClear( lua_State *L );
int ltexturesImageAlphaMask( lua_State *L );
int ltexturesImageAlphaPremultiply( lua_State *L );
int ltexturesImageResize( lua_State *L );
int ltexturesImageResizeNN( lua_State *L );
int ltexturesImageResizeCanvas( lua_State *L );
int ltexturesImageMipmaps( lua_State *L );
int ltexturesImageDither( lua_State *L );
int ltexturesImageFlipVertical( lua_State *L );
int ltexturesImageFlipHorizontal( lua_State *L );
int ltexturesImageRotateCW( lua_State *L );
int ltexturesImageRotateCCW( lua_State *L );
int ltexturesImageColorTint( lua_State *L );
int ltexturesImageColorInvert( lua_State *L );
int ltexturesImageColorGrayscale( lua_State *L );
int ltexturesImageColorContrast( lua_State *L );
int ltexturesImageColorBrightness( lua_State *L );
int ltexturesImageColorReplace( lua_State *L );
int ltexturesLoadImageColors( lua_State *L );
int ltexturesLoadImagePalette( lua_State *L );
int ltexturesGetImageAlphaBorder( lua_State *L );
int ltexturesGetImageColor( lua_State *L );
/* Image Drawing. */
int ltexturesImageClearBackground( lua_State *L );
int ltexturesImageDrawPixel( lua_State *L );
int ltexturesImageDrawLine( lua_State *L );
int ltexturesImageDrawCircle( lua_State *L );
int ltexturesImageDrawRectangle( lua_State *L );
int ltexturesImageDrawRectangleLines( lua_State *L );
int ltexturesImageDraw( lua_State *L );
int ltexturesImageDrawTextEx( lua_State *L );
/* Image Configuration. */
int ltexturesGetImageSize( lua_State *L );
int ltexturesGetImageMipmaps( lua_State *L );
int ltexturesGetImageFormat( lua_State *L );
/* Texture Loading. */
int ltexturesLoadTexture( lua_State *L );
int ltexturesLoadTextureFromImage( lua_State *L );
int ltexturesUnloadTexture( lua_State *L );
int ltexturesLoadRenderTexture( lua_State *L );
int ltexturesUnloadRenderTexture( lua_State *L );
int ltexturesUpdateTexture( lua_State *L );
int ltexturesUpdateTextureRec( lua_State *L );
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
/* Texture Configuration. */
int ltexturesGenTextureMipmaps( lua_State *L );
int ltexturesSetTextureFilter( lua_State *L );
int ltexturesSetTextureWrap( lua_State *L );
int ltexturesGetTextureSize( lua_State *L );
int ltexturesGetTextureMipmaps( lua_State *L );
int ltexturesGetTextureFormat( lua_State *L );
/* Color/pixel */
int ltexturesFade( lua_State *L );
int ltexturesColorToInt( lua_State *L );
int ltexturesColorNormalize( lua_State *L );
int ltexturesColorFromNormalized( lua_State *L );
int ltexturesColorToHSV( lua_State *L );
int ltexturesColorFromHSV( lua_State *L );
int ltexturesColorAlpha( lua_State *L );
int ltexturesColorAlphaBlend( lua_State *L );
int ltexturesGetColor( lua_State *L );
int ltexturesGetPixelColor( lua_State *L );
int ltexturesGetPixelDataSize( lua_State *L );
