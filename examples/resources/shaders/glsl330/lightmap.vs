#version 330
// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec2 vertexTexCoord2;
in vec3 vertexNormal;
// in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

// Output vertex attributes (to fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec2 fragTexCoord2;
// out vec4 fragColor;
out vec3 fragNormal;

void main() {
    // Send vertex attributes to fragment shader
    fragPosition = vec3( matModel * vec4( vertexPosition, 1.0 ) );
    fragTexCoord = vertexTexCoord;
    fragTexCoord2 = vertexTexCoord2;
    // fragColor = vertexColor;
    fragNormal = normalize( vec3( matNormal * vec4( vertexNormal, 1.0 ) ) );

    // Calculate final vertex position
    gl_Position = mvp * vec4( vertexPosition, 1.0 );
}
