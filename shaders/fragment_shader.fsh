#version 330 core

out vec4 fragColor;
in vec2 uvCord;

uniform sampler2DArray textureArray;
uniform int textureNum;

void main(void)
{
    vec4 finalColor = vec4(0.0);

    for (int layer = 0; layer < textureNum; ++layer) {
        finalColor += texture(textureArray, vec3(uvCord, layer));
    }

    fragColor = finalColor / float(textureNum)
}
