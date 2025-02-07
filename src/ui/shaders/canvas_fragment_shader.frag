#version 330 core

// Input from the vertex shader
in vec2 vTexCoord;

// Output color
out vec4 FragColor;

// Texture sampler
uniform sampler2D uTexture;

void main() {
    // Sample the texture at the interpolated texture coordinate
    FragColor = texture(uTexture, vTexCoord);
}
