#version 300 es

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

uniform mat4 mvp;
uniform mat4 matModel;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 fragTexCoord;

void main() {
    fragNormal = mat3(transpose(inverse(matModel))) * vertexNormal;
    fragPos = vec3(matModel * vec4(vertexPosition, 1.0));
    fragTexCoord = vertexTexCoord;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
