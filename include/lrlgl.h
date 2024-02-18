#pragma once

/* Matrix operations */
int lrlglMatrixMode( lua_State* L );
int lrlglPushMatrix( lua_State* L );
int lrlglPopMatrix( lua_State* L );
int lrlglLoadIdentity( lua_State* L );
int lrlglTranslatef( lua_State* L );
int lrlglRotatef( lua_State* L );
int lrlglScalef( lua_State* L );
int lrlglMultMatrixf( lua_State* L );
int lrlglFrustum( lua_State* L );
int lrlglOrtho( lua_State* L );
int lrlglViewport( lua_State* L );
/* Vertex level operations */
int lrlglBegin( lua_State* L );
int lrlglEnd( lua_State* L );
int lrlglVertex2f( lua_State* L );
int lrlglVertex3f( lua_State* L );
int lrlglTexCoord2f( lua_State* L );
int lrlglNormal3f( lua_State* L );
int lrlglColor4ub( lua_State* L );
int lrlglColor3f( lua_State* L );
int lrlglColor4f( lua_State* L );
/* Vertex buffers state */
int lrlglEnableVertexArray( lua_State* L );
int lrlglDisableVertexArray( lua_State* L );
int lrlglEnableVertexBuffer( lua_State* L );
int lrlglDisableVertexBuffer( lua_State* L );
int lrlglEnableVertexBufferElement( lua_State* L );
int lrlglDisableVertexBufferElement( lua_State* L );
int lrlglEnableVertexAttribute( lua_State* L );
int lrlglDisableVertexAttribute( lua_State* L );
/* Textures state */
int lrlglActiveTextureSlot( lua_State* L );
int lrlglEnableTexture( lua_State* L );
int lrlglDisableTexture( lua_State* L );
int lrlglEnableTextureCubemap( lua_State* L );
int lrlglDisableTextureCubemap( lua_State* L );
int lrlglTextureParameters( lua_State* L );
int lrlglCubemapParameters( lua_State* L );
/* Shader state. */
int lrlglEnableShader( lua_State* L );
int lrlglDisableShader( lua_State* L );
/* Framebuffer state. */
int lrlglEnableFramebuffer( lua_State* L );
int lrlglDisableFramebuffer( lua_State* L );
int lrlglActiveDrawBuffers( lua_State* L );
/* General render state. */
int lrlglEnableColorBlend( lua_State* L );
int lrlglDisableColorBlend( lua_State* L );
int lrlglEnableDepthTest( lua_State* L );
int lrlglDisableDepthTest( lua_State* L );
int lrlglEnableDepthMask( lua_State* L );
int lrlglDisableDepthMask( lua_State* L );
int lrlglEnableBackfaceCulling( lua_State* L );
int lrlglDisableBackfaceCulling( lua_State* L );
int lrlglSetCullFace( lua_State* L );
int lrlglEnableScissorTest( lua_State* L );
int lrlglDisableScissorTest( lua_State* L );
int lrlglScissor( lua_State* L );
int lrlglEnableWireMode( lua_State* L );
int lrlglDisableWireMode( lua_State* L );
int lrlglSetLineWidth( lua_State* L );
int lrlglGetLineWidth( lua_State* L );
int lrlglEnableSmoothLines( lua_State* L );
int lrlglDisableSmoothLines( lua_State* L );
int lrlglEnableStereoRender( lua_State* L );
int lrlglDisableStereoRender( lua_State* L );
int lrlglIsStereoRenderEnabled( lua_State* L );
int lrlglClearColor( lua_State* L );
int lrlglClearScreenBuffers( lua_State* L );
int lrlglCheckErrors( lua_State* L );
int lrlglSetBlendMode( lua_State* L );
int lrlglSetBlendFactors( lua_State* L );
int lrlglSetBlendFactorsSeparate( lua_State* L );
/* Initialization functions */
int lrlglGetVersion( lua_State* L );
int lrlglSetFramebufferWidth( lua_State* L );
int lrlglGetFramebufferWidth( lua_State* L );
int lrlglSetFramebufferHeight( lua_State* L );
int lrlglGetFramebufferHeight( lua_State* L );
int lrlglGetTextureIdDefault( lua_State* L );
int lrlglGetShaderIdDefault( lua_State* L );
int lrlglGetShaderLocsDefault( lua_State* L );
/* Render batch management */
int lrlglLoadRenderBatch( lua_State* L );
int lrlglUnloadRenderBatch( lua_State* L );
int lrlglDrawRenderBatch( lua_State* L );
int lrlglSetRenderBatchActive( lua_State* L );
int lrlglDrawRenderBatchActive( lua_State* L );
int lrlglCheckRenderBatchLimit( lua_State* L );
int lrlglSetTexture( lua_State* L );
/* Vertex buffers management */
int lrlglLoadVertexArray( lua_State* L );
int lrlglLoadVertexBuffer( lua_State* L );
int lrlglLoadVertexBufferElement( lua_State* L );
int lrlglUpdateVertexBuffer( lua_State* L );
int lrlglUpdateVertexBufferElements( lua_State* L );
int lrlglUnloadVertexArray( lua_State* L );
int lrlglUnloadVertexBuffer( lua_State* L );
int lrlglSetVertexAttribute( lua_State* L );
int lrlglSetVertexAttributeDivisor( lua_State* L );
int lrlglSetVertexAttributeDefault( lua_State* L );
int lrlglDrawVertexArray( lua_State* L );
int lrlglDrawVertexArrayElements( lua_State* L );
int lrlglDrawVertexArrayInstanced( lua_State* L );
int lrlglDrawVertexArrayElementsInstanced( lua_State* L );
/* Textures management */
int lrlglLoadTexture( lua_State* L );
int lrlglLoadTextureDepth( lua_State* L );
int lrlglLoadTextureCubemap( lua_State* L );
int lrlglUpdateTexture( lua_State* L );
int lrlglGetGlTextureFormats( lua_State* L );
int lrlglGetPixelFormatName( lua_State* L );
int lrlglUnloadTexture( lua_State* L );
int lrlglGenTextureMipmaps( lua_State* L );
int lrlglReadTexturePixels( lua_State* L );
int lrlglReadScreenPixels( lua_State* L );
/* Framebuffer management (fbo) */
int lrlglLoadFramebuffer( lua_State* L );
int lrlglFramebufferAttach( lua_State* L );
int lrlglFramebufferComplete( lua_State* L );
int lrlglUnloadFramebuffer( lua_State* L );
/* Shaders management */
int lrlglLoadShaderCode( lua_State* L );
int lrlglCompileShader( lua_State* L );
int lrlglLoadShaderProgram( lua_State* L );
int lrlglUnloadShaderProgram( lua_State* L );
int lrlglGetLocationUniform( lua_State* L );
int lrlglGetLocationAttrib( lua_State* L );
int lrlglSetUniform( lua_State* L );
int lrlglSetUniformMatrix( lua_State* L );
int lrlglSetUniformSampler( lua_State* L );
int lrlglSetShader( lua_State* L );
/* Compute shader management */
int lrlglLoadComputeShaderProgram( lua_State* L );
int lrlglComputeShaderDispatch( lua_State* L );
/* Shader buffer storage object management (ssbo) */
int lrlglLoadShaderBuffer( lua_State* L );
int lrlglUnloadShaderBuffer( lua_State* L );
int lrlglUpdateShaderBuffer( lua_State* L );
int lrlglBindShaderBuffer( lua_State* L );
int lrlglReadShaderBuffer( lua_State* L );
int lrlglCopyShaderBuffer( lua_State* L );
int lrlglGetShaderBufferSize( lua_State* L );
/* Buffer management */
int lrlglBindImageTexture( lua_State* L );
/* Matrix state management */
int lrlglGetMatrixModelview( lua_State* L );
int lrlglGetMatrixProjection( lua_State* L );
int lrlglGetMatrixTransform( lua_State* L );
int lrlglGetMatrixProjectionStereo( lua_State* L );
int lrlglGetMatrixViewOffsetStereo( lua_State* L );
int lrlglSetMatrixProjection( lua_State* L );
int lrlglSetMatrixModelview( lua_State* L );
int lrlglSetMatrixProjectionStereo( lua_State* L );
int lrlglSetMatrixViewOffsetStereo( lua_State* L );
