#version 330
// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec2 fragTexCoord2;
in vec3 fragPosition;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture1;

// Output fragment color
out vec4 finalColor;

void main() {
	// Texel color fetching from texture sampler
    vec4 texelColor = texture( texture0, fragTexCoord );
    vec4 texelColor2 = texture( texture1, fragTexCoord2 );
    vec3 normal = normalize( fragNormal );
	finalColor = texelColor * texelColor2;
}
