#version 330 core

layout(location = 0) in vec3 aPosition; // Position (e.g., -1.0 to 1.0 and "1" for trandform)
layout(location = 1) in vec2 aTexCoord; // Texture coordinates (e.g., 0.0 to 1.0)

uniform mat3 uTransform;
out vec2 vTexCoord;

void main() {
    vTexCoord = aTexCoord;
    vec3 transformedPosition = uTransform * aPosition;
    gl_Position = vec4(transformedPosition, 0.0, 1.0);
}
