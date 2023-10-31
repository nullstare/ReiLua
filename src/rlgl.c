#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "lrlgl.h"

/*
## RLGL - Matrix operations
*/

/*
> RL.rlMatrixMode( int mode )

Choose the current matrix to be transformed
*/
int lrlglMatrixMode( lua_State *L ) {
	rlMatrixMode( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlPushMatrix()

Push the current matrix to stack
*/
int lrlglPushMatrix( lua_State *L ) {
	rlPushMatrix();

	return 0;
}

/*
> RL.rlPopMatrix()

Pop latest inserted matrix from stack
*/
int lrlglPopMatrix( lua_State *L ) {
	rlPopMatrix();

	return 0;
}

/*
> RL.rlLoadIdentity()

Reset current matrix to identity matrix
*/
int lrlglLoadIdentity( lua_State *L ) {
	rlLoadIdentity();

	return 0;
}

/*
> RL.rlTranslatef( Vector3 translation )

Multiply the current matrix by a translation matrix
*/
int lrlglTranslatef( lua_State *L ) {
	Vector3 translation = uluaGetVector3Index( L, 1 );

	rlTranslatef( translation.x, translation.y, translation.z );

	return 0;
}

/*
> RL.rlRotatef( float angle, Vector3 rotation )

Multiply the current matrix by a rotation matrix
*/
int lrlglRotatef( lua_State *L ) {
	float angle = luaL_checknumber( L, 1 );
	Vector3 rotation = uluaGetVector3Index( L, 2 );

	rlRotatef( angle, rotation.x, rotation.y, rotation.z );

	return 0;
}

/*
> RL.rlScalef( Vector3 scale )

Multiply the current matrix by a scaling matrix
*/
int lrlglScalef( lua_State *L ) {
	Vector3 scale = uluaGetVector3Index( L, 1 );

	rlScalef( scale.x, scale.y, scale.z );

	return 0;
}

/*
> RL.rlMultMatrixf( Matrix matrix )

Multiply the current matrix by another matrix
*/
int lrlglMultMatrixf( lua_State *L ) {
	Matrix matrix = uluaGetMatrixIndex( L, 1 );

	float matf[16] = {
		matrix.m0, matrix.m4, matrix.m8, matrix.m12,
		matrix.m1, matrix.m5, matrix.m9, matrix.m13,
		matrix.m2, matrix.m6, matrix.m10, matrix.m14,
		matrix.m3, matrix.m7, matrix.m11, matrix.m15
	};
	rlMultMatrixf( matf );

	return 0;
}

/*
> RL.rlFrustum( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by a perspective matrix generated by parameters
*/
int lrlglFrustum( lua_State *L ) {
	double left = luaL_checknumber( L, 1 );
	double right = luaL_checknumber( L, 2 );
	double bottom = luaL_checknumber( L, 3 );
	double top = luaL_checknumber( L, 4 );
	double znear = luaL_checknumber( L, 5 );
	double zfar = luaL_checknumber( L, 6 );

	rlFrustum( left, right, bottom, top, znear, zfar );

	return 0;
}

/*
> RL.rlOrtho( float left, float right, float bottom, float top, float znear, float zfar )

Multiply the current matrix by an orthographic matrix generated by parameters
*/
int lrlglOrtho( lua_State *L ) {
	double left = luaL_checknumber( L, 1 );
	double right = luaL_checknumber( L, 2 );
	double bottom = luaL_checknumber( L, 3 );
	double top = luaL_checknumber( L, 4 );
	double znear = luaL_checknumber( L, 5 );
	double zfar = luaL_checknumber( L, 6 );

	rlOrtho( left, right, bottom, top, znear, zfar );

	return 0;
}

/*
> RL.rlViewport( Rectangle viewport )

Set the viewport area (transformation from normalized device coordinates to window coordinates)
NOTE: We store current viewport dimensions
*/
int lrlglViewport( lua_State *L ) {
	Rectangle rect = uluaGetRectangleIndex( L, 1 );

	rlViewport( rect.x, rect.y, rect.width, rect.height );

	return 0;
}

/*
## RLGL - Vertex level operations
*/

/*
> RL.rlBegin( int mode )

Initialize drawing mode (how to organize vertex)
*/
int lrlglBegin( lua_State *L ) {
	rlBegin( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlEnd()

Finish vertex providing
*/
int lrlglEnd( lua_State *L ) {
	rlEnd();

	return 0;
}

/*
> RL.rlVertex2f( Vector2 position )

Define one vertex (position)
*/
int lrlglVertex2f( lua_State *L ) {
	Vector2 position = uluaGetVector2Index( L, 1 );

	rlVertex2f( position.x, position.y );

	return 0;
}

/*
> RL.rlVertex3f( Vector3 position )

Define one vertex (position)
*/
int lrlglVertex3f( lua_State *L ) {
	Vector3 position = uluaGetVector3Index( L, 1 );

	rlVertex3f( position.x, position.y, position.z );

	return 0;
}

/*
> RL.rlTexCoord2f( Vector2 texCoord )

Define one vertex (texture coordinate) - 2 float
*/
int lrlglTexCoord2f( lua_State *L ) {
	Vector2 texCoord = uluaGetVector2Index( L, 1 );

	rlTexCoord2f( texCoord.x, texCoord.y );

	return 0;
}

/*
> RL.rlNormal3f( Vector3 normal )

Define one vertex (normal) - 3 float
*/
int lrlglNormal3f( lua_State *L ) {
	Vector3 normal = uluaGetVector3Index( L, 1 );

	rlNormal3f( normal.x, normal.y, normal.z );

	return 0;
}

/*
> RL.rlColor4ub( Color color )

Define one vertex (color) - 4 byte
*/
int lrlglColor4ub( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );

	rlColor4ub( color.r, color.g, color.b, color.a );

	return 0;
}

/*
> RL.rlColor3f( Vector3 color )

Define one vertex (color) - 3 float
*/
int lrlglColor3f( lua_State *L ) {
	Vector3 color = uluaGetVector3Index( L, 1 );

	rlColor3f( color.x, color.y, color.z );

	return 0;
}

/*
> RL.rlColor4f( Vector4 color )

Define one vertex (color) - 4 float
*/
int lrlglColor4f( lua_State *L ) {
	Vector4 color = uluaGetVector4Index( L, 1 );

	rlColor4f( color.x, color.y, color.z, color.w );

	return 0;
}

/*
## RLGL - Vertex buffers state
*/

/*
> supported = RL.rlEnableVertexArray( int vaoId )

Enable vertex array (VAO, if supported)

- Success return bool
*/
int lrlglEnableVertexArray( lua_State *L ) {
	lua_pushboolean( L, rlEnableVertexArray( luaL_checkinteger( L, 1 ) ) );

	return 1;
}

/*
> RL.rlDisableVertexArray()

Disable vertex array (VAO, if supported)
*/
int lrlglDisableVertexArray( lua_State *L ) {
	rlDisableVertexArray();

	return 0;
}

/*
> RL.rlEnableVertexBuffer( int id )

Enable vertex buffer (VBO)

- Failure return false
- Success return true
*/
int lrlglEnableVertexBuffer( lua_State *L ) {
	rlEnableVertexBuffer( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableVertexBuffer()

Disable vertex buffer (VBO)
*/
int lrlglDisableVertexBuffer( lua_State *L ) {
	rlDisableVertexBuffer();

	return 0;
}

/*
> RL.rlEnableVertexBufferElement( int id )

Enable vertex buffer element (VBO element)
*/
int lrlglEnableVertexBufferElement( lua_State *L ) {
	rlEnableVertexBufferElement( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableVertexBufferElement()

Disable vertex buffer element (VBO element)
*/
int lrlglDisableVertexBufferElement( lua_State *L ) {
	rlDisableVertexBufferElement();

	return 0;
}

/*
> RL.rlEnableVertexAttribute( int index )

Enable vertex attribute index
*/
int lrlglEnableVertexAttribute( lua_State *L ) {
	rlEnableVertexAttribute( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableVertexAttribute( int index )

Disable vertex attribute index
*/
int lrlglDisableVertexAttribute( lua_State *L ) {
	rlDisableVertexAttribute( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
## RLGL - Textures state
*/

/*
> RL.rlActiveTextureSlot( int slot )

Select and active a texture slot
*/
int lrlglActiveTextureSlot( lua_State *L ) {
	rlActiveTextureSlot( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlEnableTexture( int id )

Enable texture
*/
int lrlglEnableTexture( lua_State *L ) {
	rlEnableTexture( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableTexture()

Disable texture
*/
int lrlglDisableTexture( lua_State *L ) {
	rlDisableTexture();

	return 0;
}

/*
> RL.rlEnableTextureCubemap( int id )

Enable texture cubemap
*/
int lrlglEnableTextureCubemap( lua_State *L ) {
	rlEnableTextureCubemap( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableTextureCubemap()

Disable texture cubemap
*/
int lrlglDisableTextureCubemap( lua_State *L ) {
	rlDisableTextureCubemap();

	return 0;
}

/*
> RL.rlTextureParameters( int id, int param, int value )

Set texture parameters (filter, wrap)
*/
int lrlglTextureParameters( lua_State *L ) {
	unsigned int id = luaL_checkinteger( L, 1 );
	int param = luaL_checkinteger( L, 2 );
	int value = luaL_checkinteger( L, 3 );

	rlTextureParameters( id, param, value );

	return 0;
}

/*
> RL.rlCubemapParameters( int id, int param, int value )

Set cubemap parameters (filter, wrap)
*/
int lrlglCubemapParameters( lua_State *L ) {
	unsigned int id = luaL_checkinteger( L, 1 );
	int param = luaL_checkinteger( L, 2 );
	int value = luaL_checkinteger( L, 3 );

	rlCubemapParameters( id, param, value );

	return 0;
}

/*
## RLGL - Shader state
*/

/*
> RL.rlEnableShader( int id )

Enable shader program
*/
int lrlglEnableShader( lua_State *L ) {
	rlEnableShader( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableShader()

Disable shader program
*/
int lrlglDisableShader( lua_State *L ) {
	rlDisableShader();

	return 0;
}

/*
## RLGL - Framebuffer state
*/

/*
> RL.rlEnableFramebuffer( int id )

Enable render texture (fbo)
*/
int lrlglEnableFramebuffer( lua_State *L ) {
	rlEnableFramebuffer( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlDisableFramebuffer()

Disable render texture (fbo), return to default framebuffer
*/
int lrlglDisableFramebuffer( lua_State *L ) {
	rlDisableFramebuffer();

	return 0;
}

/*
> RL.rlActiveDrawBuffers( int count )

Activate multiple draw color buffers
*/
int lrlglActiveDrawBuffers( lua_State *L ) {
	rlActiveDrawBuffers( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
## RLGL - General render state
*/

/*
> RL.rlEnableColorBlend()

Enable color blending
*/
int lrlglEnableColorBlend( lua_State *L ) {
	rlEnableColorBlend();

	return 0;
}

/*
> RL.rlDisableColorBlend()

Disable color blending
*/
int lrlglDisableColorBlend( lua_State *L ) {
	rlDisableColorBlend();

	return 0;
}

/*
> RL.rlEnableDepthTest()

Enable depth test
*/
int lrlglEnableDepthTest( lua_State *L ) {
	rlEnableDepthTest();

	return 0;
}

/*
> RL.rlDisableDepthTest()

Disable depth test
*/
int lrlglDisableDepthTest( lua_State *L ) {
	rlDisableDepthTest();

	return 0;
}

/*
> RL.rlEnableDepthMask()

Enable depth write
*/
int lrlglEnableDepthMask( lua_State *L ) {
	rlEnableDepthMask();

	return 0;
}

/*
> RL.rlDisableDepthMask()

Disable depth write
*/
int lrlglDisableDepthMask( lua_State *L ) {
	rlDisableDepthMask();

	return 0;
}

/*
> RL.rlEnableBackfaceCulling()

Enable backface culling
*/
int lrlglEnableBackfaceCulling( lua_State *L ) {
	rlEnableBackfaceCulling();

	return 0;
}

/*
> RL.rlDisableBackfaceCulling()

Disable backface culling
*/
int lrlglDisableBackfaceCulling( lua_State *L ) {
	rlDisableBackfaceCulling();

	return 0;
}

/*
> RL.rlSetCullFace( int mode )

Set face culling mode
*/
int lrlglSetCullFace( lua_State *L ) {
	rlSetCullFace( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlEnableScissorTest()

Enable scissor test
*/
int lrlglEnableScissorTest( lua_State *L ) {
	rlEnableScissorTest();

	return 0;
}

/*
> RL.rlDisableScissorTest()

Disable scissor test
*/
int lrlglDisableScissorTest( lua_State *L ) {
	rlDisableScissorTest();

	return 0;
}

/*
> RL.rlScissor( Rectangle area )

Scissor test
*/
int lrlglScissor( lua_State *L ) {
	Rectangle area = uluaGetRectangleIndex( L, 1 );
	
	rlScissor( area.x, area.y, area.width, area.height );

	return 0;
}

/*
> RL.rlEnableWireMode()

Enable wire mode
*/
int lrlglEnableWireMode( lua_State *L ) {
	rlEnableWireMode();

	return 0;
}

/*
> RL.rlDisableWireMode()

Disable wire mode
*/
int lrlglDisableWireMode( lua_State *L ) {
	rlDisableWireMode();

	return 0;
}

/*
> RL.rlSetLineWidth( float width )

Set the line drawing width
*/
int lrlglSetLineWidth( lua_State *L ) {
	rlSetLineWidth( luaL_checknumber( L, 1 ) );

	return 0;
}

/*
> width = RL.rlGetLineWidth()

Get the line drawing width

- Success return float
*/
int lrlglGetLineWidth( lua_State *L ) {
	lua_pushnumber( L, rlGetLineWidth() );

	return 1;
}

/*
> RL.rlEnableSmoothLines()

Enable line aliasing
*/
int lrlglEnableSmoothLines( lua_State *L ) {
	rlEnableSmoothLines();

	return 0;
}

/*
> RL.rlDisableSmoothLines()

Disable line aliasing
*/
int lrlglDisableSmoothLines( lua_State *L ) {
	rlDisableSmoothLines();

	return 0;
}

/*
> RL.rlEnableStereoRender()

Enable stereo rendering
*/
int lrlglEnableStereoRender( lua_State *L ) {
	rlEnableStereoRender();

	return 0;
}

/*
> RL.rlDisableStereoRender()

Enable stereo rendering
*/
int lrlglDisableStereoRender( lua_State *L ) {
	rlDisableStereoRender();

	return 0;
}

/*
> enabled = RL.rlIsStereoRenderEnabled()

Check if stereo render is enabled

- Success return bool
*/
int lrlglIsStereoRenderEnabled( lua_State *L ) {
	lua_pushboolean( L, rlIsStereoRenderEnabled() );

	return 1;
}

/*
> RL.rlClearColor( Color color )

Clear color buffer with color
*/
int lrlglClearColor( lua_State *L ) {
	Color color = uluaGetColorIndex( L, 1 );

	rlClearColor( color.r, color.g, color.b, color.a );

	return 0;
}

/*
> RL.rlClearScreenBuffers()

Clear used screen buffers (color and depth)
*/
int lrlglClearScreenBuffers( lua_State *L ) {
	rlClearScreenBuffers();

	return 0;
}

/*
> RL.rlCheckErrors()

Check and log OpenGL error codes
*/
int lrlglCheckErrors( lua_State *L ) {
	rlCheckErrors();

	return 0;
}

/*
> RL.rlSetBlendMode( int mode )

Set blending mode
*/
int lrlglSetBlendMode( lua_State *L ) {
	rlSetBlendMode( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlSetBlendFactors( int glSrcFactor, int glDstFactor, int glEquation )

Set blending mode factor and equation (using OpenGL factors)
*/
int lrlglSetBlendFactors( lua_State *L ) {
	int glSrcFactor = luaL_checkinteger( L, 1 );
	int glDstFactor = luaL_checkinteger( L, 2 );
	int glEquation = luaL_checkinteger( L, 3 );

	rlSetBlendFactors( glSrcFactor, glDstFactor, glEquation );

	return 0;
}

/*
> RL.rlSetBlendFactorsSeparate( int glSrcRGB, int glDstRGB, int glSrcAlpha, int glDstAlpha, int glEqRGB, int glEqAlpha )

Set blending mode factors and equations separately (using OpenGL factors)
*/
int lrlglSetBlendFactorsSeparate( lua_State *L ) {
	int glSrcRGB = luaL_checkinteger( L, 1 );
	int glDstRGB = luaL_checkinteger( L, 2 );
	int glSrcAlpha = luaL_checkinteger( L, 3 );
	int glDstAlpha = luaL_checkinteger( L, 4 );
	int glEqRGB = luaL_checkinteger( L, 5 );
	int glEqAlpha = luaL_checkinteger( L, 6 );

	rlSetBlendFactorsSeparate( glSrcRGB, glDstRGB, glSrcAlpha, glDstAlpha, glEqRGB, glEqAlpha );

	return 0;
}


/*
## RLGL - Initialization functions
*/

/*
> version = RL.rlGetVersion()

Get current OpenGL version

- Success return int
*/
int lrlglGetVersion( lua_State *L ) {
	lua_pushinteger( L, rlGetVersion() );

	return 1;
}

/*
## RLGL - Render batch management
*/

/*
> RL.rlDrawRenderBatchActive()

Update and draw internal render batch
*/
int lrlglDrawRenderBatchActive( lua_State *L ) {
	rlDrawRenderBatchActive();

	return 0;
}

/*
> overflow = RL.rlCheckRenderBatchLimit( int vCount )

Check internal buffer overflow for a given number of vertex and force a rlRenderBatch draw call if required

- Success return bool
*/
int lrlglCheckRenderBatchLimit( lua_State *L ) {
	lua_pushboolean( L, rlCheckRenderBatchLimit( luaL_checkinteger( L, 1 ) ) );

	return 1;
}

/*
> RL.rlSetTexture( int id )

Set current texture for render batch and check buffers limits
*/
int lrlglSetTexture( lua_State *L ) {
	rlSetTexture( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
## RLGL - Vertex buffers management
*/

/*
> vaoId = RL.rlLoadVertexArray()

Load vertex array (vao) if supported

- Success return int
*/
int lrlglLoadVertexArray( lua_State *L ) {
	lua_pushinteger( L, rlLoadVertexArray() );

	return 1;
}

/*
> vboId = RL.rlLoadVertexBuffer( Buffer buffer, bool dynamic )

Load a vertex buffer attribute

- Success return int
*/
int lrlglLoadVertexBuffer( lua_State *L ) {
	Buffer *buffer = uluaGetBuffer( L, 1 );
	bool dynamic = uluaGetBoolean( L, 2 );

	lua_pushinteger( L, rlLoadVertexBuffer( buffer->data, buffer->size, dynamic ) );

	return 1;
}

/*
> vboId = RL.rlLoadVertexBufferElement( Buffer buffer, bool dynamic )

Load a new attributes element buffer

- Success return int
*/
int lrlglLoadVertexBufferElement( lua_State *L ) {
	Buffer *buffer = uluaGetBuffer( L, 1 );
	bool dynamic = uluaGetBoolean( L, 2 );

	lua_pushinteger( L, rlLoadVertexBufferElement( buffer->data, buffer->size, dynamic ) );

	return 1;
}

/*
> RL.rlUpdateVertexBuffer( int bufferId, Buffer buffer, int offset )

Update GPU buffer with new data
*/
int lrlglUpdateVertexBuffer( lua_State *L ) {
	int bufferId = luaL_checkinteger( L, 1 );
	Buffer *buffer = uluaGetBuffer( L, 2 );
	int offset = luaL_checkinteger( L, 3 );

	rlUpdateVertexBuffer( bufferId, buffer->data, buffer->size, offset );

	return 0;
}

/*
> RL.rlUpdateVertexBufferElements( int id, Buffer buffer, int offset )

Update vertex buffer elements with new data
*/
int lrlglUpdateVertexBufferElements( lua_State *L ) {
	int bufferId = luaL_checkinteger( L, 1 );
	Buffer *buffer = uluaGetBuffer( L, 2 );
	int offset = luaL_checkinteger( L, 3 );

	rlUpdateVertexBufferElements( bufferId, buffer->data, buffer->size, offset );

	return 0;
}

/*
> RL.rlUnloadVertexArray( int vaoId )

Unload vertex array object (VAO)
*/
int lrlglUnloadVertexArray( lua_State *L ) {
	rlUnloadVertexArray( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlUnloadVertexBuffer( int vboId )

Unload vertex buffer (VBO)
*/
int lrlglUnloadVertexBuffer( lua_State *L ) {
	rlUnloadVertexBuffer( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
> RL.rlSetVertexAttribute( int index, int compSize, int type, bool normalized, int stride, int pointer )

Set vertex attribute
*/
int lrlglSetVertexAttribute( lua_State *L ) {
	int index = luaL_checkinteger( L, 1 );
	int compSize = luaL_checkinteger( L, 2 );
	int type = luaL_checkinteger( L, 3 );
	bool normalized = uluaGetBoolean( L, 4 );
	int stride = luaL_checkinteger( L, 5 );
	int pointer = luaL_checkinteger( L, 6 );

	rlSetVertexAttribute( index, compSize, type, normalized, stride, &pointer );

	return 0;
}

/*
> RL.rlSetVertexAttributeDivisor( int index, int divisor )

Set vertex attribute divisor
*/
int lrlglSetVertexAttributeDivisor( lua_State *L ) {
	unsigned int index = (unsigned int)luaL_checkinteger( L, 1 );
	int divisor = luaL_checkinteger( L, 2 );

	rlSetVertexAttributeDivisor( index, divisor );

	return 0;
}

/*
> RL.rlSetVertexAttributeDefault( int locIndex, float{} value, int attribType )

Set vertex attribute default value
*/
int lrlglSetVertexAttributeDefault( lua_State *L ) {
	int locIndex = luaL_checkinteger( L, 1 );
	int attribType = luaL_checkinteger( L, 3 );
	int count = uluaGetTableLenIndex( L, 2 );
	float value[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	int t = 2;
	int i = 0;
	lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
		value[i] = luaL_checknumber( L, -1 );
		lua_pop( L, 1 );
		i++;
	}
	rlSetVertexAttributeDefault( locIndex, value, attribType, count );

	return 0;
}

/*
> RL.rlDrawVertexArray( int offset, int count )

Draw vertex array
*/
int lrlglDrawVertexArray( lua_State *L ) {
	int offset = luaL_checkinteger( L, 1 );
	int count = luaL_checkinteger( L, 2 );

	rlDrawVertexArray( offset, count );

	return 0;
}

/*
> RL.rlDrawVertexArrayElements( int offset, int count, Buffer buffer )

Draw vertex array elements
*/
int lrlglDrawVertexArrayElements( lua_State *L ) {
	int offset = luaL_checkinteger( L, 1 );
	int count = luaL_checkinteger( L, 2 );
	Buffer *buffer = uluaGetBuffer( L, 3 );

	rlDrawVertexArrayElements( offset, count, buffer->data );

	return 0;
}

/*
> RL.rlDrawVertexArrayInstanced( int offset, int count, int instances )

Draw vertex array instanced
*/
int lrlglDrawVertexArrayInstanced( lua_State *L ) {
	int offset = luaL_checkinteger( L, 1 );
	int count = luaL_checkinteger( L, 2 );
	int instances = luaL_checkinteger( L, 3 );

	rlDrawVertexArrayInstanced( offset, count, instances );

	return 0;
}

/*
> RL.rlDrawVertexArrayElementsInstanced( int offset, int count, Buffer buffer, int instances )

Draw vertex array elements instanced
*/
int lrlglDrawVertexArrayElementsInstanced( lua_State *L ) {
	int offset = luaL_checkinteger( L, 1 );
	int count = luaL_checkinteger( L, 2 );
	Buffer *buffer = uluaGetBuffer( L, 3 );
	int instances = luaL_checkinteger( L, 4 );

	rlDrawVertexArrayElementsInstanced( offset, count, buffer->data, instances );

	return 0;
}

/*
## RLGL - Textures management
*/

/*
> id = RL.rlLoadTexture( Vector2 size, int format, int mipmapCount )

Load texture in GPU

- Success return int
*/
int lrlglLoadTexture( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	int format = luaL_checkinteger( L, 2 );
	int mipmapCount = luaL_checkinteger( L, 3 );

	lua_pushinteger( L, rlLoadTexture( NULL, size.x, size.y, format, mipmapCount ) );

	return 1;
}

/*
> id = RL.rlLoadTextureDepth( Vector2 size, bool useRenderBuffer )

Load depth texture/renderbuffer (to be attached to fbo)

- Success return int
*/
int lrlglLoadTextureDepth( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );
	bool useRenderBuffer = uluaGetBoolean( L, 2 );

	lua_pushinteger( L, rlLoadTextureDepth( size.x, size.y, useRenderBuffer ) );

	return 1;
}

/*
> RL.rlUnloadTexture( int id )

Unload texture from GPU memory
*/
int lrlglUnloadTexture( lua_State *L ) {
	rlUnloadTexture( luaL_checkinteger( L, 1 ) );

	return 0;
}

/*
## RLGL - Framebuffer management (fbo)
*/

/*
> fboId = RL.rlLoadFramebuffer( Vector2 size )

Load an empty framebuffer

- Success return int
*/
int lrlglLoadFramebuffer( lua_State *L ) {
	Vector2 size = uluaGetVector2Index( L, 1 );

	lua_pushinteger( L, rlLoadFramebuffer( size.x, size.y ) );

	return 1;
}

/*
> RL.rlFramebufferAttach( int fboId, int texId, int attachType, int texType, int mipLevel )

Attach texture/renderbuffer to a framebuffer
*/
int lrlglFramebufferAttach( lua_State *L ) {
	unsigned int fboId = luaL_checkinteger( L, 1 );
	unsigned int texId = luaL_checkinteger( L, 2 );
	int attachType = luaL_checkinteger( L, 3 );
	int texType = luaL_checkinteger( L, 4 );
	int mipLevel = luaL_checkinteger( L, 5 );

	rlFramebufferAttach( fboId, texId, attachType, texType, mipLevel );

	return 0;
}

/*
> isComplete = RL.rlFramebufferComplete( int id )

Verify framebuffer is complete

- Success return bool
*/
int lrlglFramebufferComplete( lua_State *L ) {
	unsigned int id = luaL_checkinteger( L, 1 );

	lua_pushboolean( L, rlFramebufferComplete( id ) );

	return 1;
}

/*
> RL.rlUnloadFramebuffer( int id )

Delete framebuffer from GPU
*/
int lrlglUnloadFramebuffer( lua_State *L ) {
	unsigned int id = luaL_checkinteger( L, 1 );

	rlUnloadFramebuffer( id );

	return 0;
}

/*
## RLGL - Shaders management
*/

/*
> shaderId = RL.rlLoadShaderCode( string vsCode, string fsCode )

Load shader from code strings

- Success return int
*/
int lrlglLoadShaderCode( lua_State *L ) {
	lua_pushinteger( L, rlLoadShaderCode( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> shaderId = RL.rlCompileShader( string shaderCode, int type )

Compile custom shader and return shader id (type: RL_VERTEX_SHADER, RL_FRAGMENT_SHADER, RL_COMPUTE_SHADER)

- Success return int
*/
int lrlglCompileShader( lua_State *L ) {
	int type = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, rlCompileShader( luaL_checkstring( L, 1 ), type ) );

	return 1;
}

/*
> shaderProgramId = RL.rlLoadShaderProgram( int vShaderId, int fShaderId )

Load custom shader program

- Success return int
*/
int lrlglLoadShaderProgram( lua_State *L ) {
	unsigned int vShaderId = (unsigned int)luaL_checkinteger( L, 1 );
	unsigned int fShaderId = (unsigned int)luaL_checkinteger( L, 2 );

	lua_pushinteger( L, rlLoadShaderProgram( vShaderId, fShaderId ) );

	return 1;
}

/*
> RL.rlUnloadShaderProgram( int id )

Unload shader program
*/
int lrlglUnloadShaderProgram( lua_State *L ) {
	unsigned int id = (unsigned int)luaL_checkinteger( L, 1 );

	rlUnloadShaderProgram( id );

	return 0;
}

/*
> location = RL.rlGetLocationUniform( int shaderId, string uniformName )

Get shader location uniform

- Success return int
*/
int lrlglGetLocationUniform( lua_State *L ) {
	unsigned int shaderId = (unsigned int)luaL_checkinteger( L, 1 );

	lua_pushinteger( L, rlGetLocationUniform( shaderId, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> location = RL.rlGetLocationAttrib( int shaderId, string attribName )

Get shader location attribute

- Success return int
*/
int lrlglGetLocationAttrib( lua_State *L ) {
	unsigned int shaderId = (unsigned int)luaL_checkinteger( L, 1 );

	lua_pushinteger( L, rlGetLocationAttrib( shaderId, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> RL.rlSetUniform( int locIndex, Buffer value, int uniformType, int count )

Set shader value uniform
*/
int lrlglSetUniform( lua_State *L ) {
	int locIndex = luaL_checkinteger( L, 1 );
	Buffer *value = uluaGetBuffer( L, 2 );
	int uniformType = luaL_checkinteger( L, 3 );
	int count = luaL_checkinteger( L, 4 );

	rlSetUniform( locIndex, value->data, uniformType, count );

	return 0;
}

/*
> RL.rlSetUniformMatrix( int locIndex, Matrix mat )

Set shader value matrix
*/
int lrlglSetUniformMatrix( lua_State *L ) {
	int locIndex = luaL_checkinteger( L, 1 );
	Matrix mat = uluaGetMatrixIndex( L, 2 );

	rlSetUniformMatrix( locIndex, mat );

	return 0;
}

/*
> RL.rlSetUniformSampler( int locIndex, int textureId )

Set shader value sampler
*/
int lrlglSetUniformSampler( lua_State *L ) {
	int locIndex = luaL_checkinteger( L, 1 );
	unsigned int textureId = (unsigned int)luaL_checkinteger( L, 2 );

	rlSetUniformSampler( locIndex, textureId );

	return 0;
}

/*
> RL.rlSetShader( int id, int{} locs )

Set shader currently active (id and locations)
*/
int lrlglSetShader( lua_State *L ) {
	unsigned int id = (unsigned int)luaL_checkinteger( L, 1 );

	int t = 2, i = 0;
    lua_pushnil( L );

	while ( lua_next( L, t ) != 0 ) {
        if ( lua_isnumber( L, -1 ) ) {
			if ( i < RL_MAX_SHADER_LOCATIONS ) {
				state->RLGLcurrentShaderLocs[i] = lua_tointeger( L, -1 );
			}
        }
        i++;
        lua_pop( L, 1 );
    }
	rlSetShader( id, state->RLGLcurrentShaderLocs );

	return 0;
}

/*
## RLGL - Compute shader management
*/

/*
> programId = RL.rlLoadComputeShaderProgram( int shaderId )

Load compute shader program

- Success return int
*/
int lrlglLoadComputeShaderProgram( lua_State *L ) {
	unsigned int shaderId = (unsigned int)luaL_checkinteger( L, 1 );

	lua_pushinteger( L, rlLoadComputeShaderProgram( shaderId ) );

	return 1;
}

/*
> RL.rlComputeShaderDispatch( int groupX, int groupY, int groupZ )

Dispatch compute shader (equivalent to *draw* for graphics pipeline)
*/
int lrlglComputeShaderDispatch( lua_State *L ) {
	unsigned int groupX = (unsigned int)luaL_checkinteger( L, 1 );
	unsigned int groupY = (unsigned int)luaL_checkinteger( L, 2 );
	unsigned int groupZ = (unsigned int)luaL_checkinteger( L, 3 );

	rlComputeShaderDispatch( groupX, groupY, groupZ );

	return 0;
}

/*
## RLGL - Buffer management
*/

/*
> RL.rlBindImageTexture( int id, int index, int format, bool readonly )

Bind image texture
*/
int lrlglBindImageTexture( lua_State *L ) {
	unsigned int id = (unsigned int)luaL_checkinteger( L, 1 );
	unsigned int index = (unsigned int)luaL_checkinteger( L, 2 );
	int format = luaL_checkinteger( L, 3 );
	bool readonly = uluaGetBoolean( L, 4 );

	rlBindImageTexture( id, index, format, readonly );

	return 0;
}

/*
## RLGL - Matrix state management
*/

/*
> modelview = RL.rlGetMatrixModelview()

Get internal modelview matrix

- Success return Matrix
*/
int lrlglGetMatrixModelview( lua_State *L ) {
	uluaPushMatrix( L, rlGetMatrixModelview() );

	return 1;
}

/*
> projection = RL.rlGetMatrixProjection()

Get internal projection matrix

- Success return Matrix
*/
int lrlglGetMatrixProjection( lua_State *L ) {
	uluaPushMatrix( L, rlGetMatrixProjection() );

	return 1;
}

/*
> transform = RL.rlGetMatrixTransform()

Get internal accumulated transform matrix

- Success return Matrix
*/
int lrlglGetMatrixTransform( lua_State *L ) {
	uluaPushMatrix( L, rlGetMatrixTransform() );

	return 1;
}

/*
> projection = RL.rlGetMatrixProjectionStereo( int eye )

Get internal projection matrix for stereo render (selected eye)

- Success return Matrix
*/
int lrlglGetMatrixProjectionStereo( lua_State *L ) {
	uluaPushMatrix( L, rlGetMatrixProjectionStereo( luaL_checkinteger( L, 1 ) ) );

	return 1;
}

/*
> viewOffset = RL.rlGetMatrixViewOffsetStereo( int eye )

Get internal view offset matrix for stereo render (selected eye)

- Success return Matrix
*/
int lrlglGetMatrixViewOffsetStereo( lua_State *L ) {
	uluaPushMatrix( L, rlGetMatrixViewOffsetStereo( luaL_checkinteger( L, 1 ) ) );

	return 1;
}

/*
> RL.rlSetMatrixProjection( Matrix proj )

Set a custom projection matrix (replaces internal projection matrix)
*/
int lrlglSetMatrixProjection( lua_State *L ) {
	rlSetMatrixProjection( uluaGetMatrixIndex( L, 1 ) );

	return 0;
}

/*
> RL.rlSetMatrixModelview( Matrix view )

Set a custom modelview matrix (replaces internal modelview matrix)
*/
int lrlglSetMatrixModelview( lua_State *L ) {
	rlSetMatrixModelview( uluaGetMatrixIndex( L, 1 ) );

	return 0;
}

/*
> RL.rlSetMatrixProjectionStereo( Matrix right, Matrix left )

Set eyes projection matrices for stereo rendering
*/
int lrlglSetMatrixProjectionStereo( lua_State *L ) {
	rlSetMatrixProjectionStereo( uluaGetMatrixIndex( L, 1 ), uluaGetMatrixIndex( L, 2 ) );

	return 0;
}

/*
> RL.rlSetMatrixViewOffsetStereo( Matrix right, Matrix left )

Set eyes view offsets matrices for stereo rendering
*/
int lrlglSetMatrixViewOffsetStereo( lua_State *L ) {
	rlSetMatrixViewOffsetStereo( uluaGetMatrixIndex( L, 1 ), uluaGetMatrixIndex( L, 2 ) );

	return 0;
}
