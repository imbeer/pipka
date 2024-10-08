#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 UV;

out vec2 uvCord;
uniform mat4 transformMatrix;

void main() {
        gl_Position = transformMatrix * vec4(vertex, 1.0); // Position in NDC
        uvCord = UV; // Pass UV to the fragment shader
}
