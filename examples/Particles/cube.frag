#version 410 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
    FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}