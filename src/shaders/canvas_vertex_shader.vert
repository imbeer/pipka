#version 330 core

// Input vertex attributes
layout(location = 0) in vec2 aPosition; // Position (e.g., -1.0 to 1.0)
layout(location = 1) in vec2 aTexCoord; // Texture coordinates (e.g., 0.0 to 1.0)

// Output to the fragment shader
out vec2 vTexCoord;

void main() {
    // Pass the texture coordinate to the fragment shader
    vTexCoord = aTexCoord;

    // Set the vertex position in clip space
    gl_Position = vec4(aPosition, 0.0, 1.0);
}
