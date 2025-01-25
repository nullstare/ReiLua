#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

uniform vec2 atlasSize;
uniform vec2 tileTexSize;

// Output fragment color
out vec4 finalColor;

vec2 texTileSize = tileTexSize / atlasSize;
vec2 atlasTileSize = atlasSize / tileTexSize;

void main() {
	vec2 tileTexCoord = fract( vec2( fragPosition.x, fragPosition.y ) / tileTexSize );
	// Get tile texture corner.
	vec2 texOffset = floor( fragTexCoord / texTileSize ) * texTileSize;
	vec2 fragCoord = tileTexCoord / atlasTileSize + texOffset;
	vec4 texelColor = texture( texture0, fragCoord );

	finalColor = texelColor * fragColor;
}
