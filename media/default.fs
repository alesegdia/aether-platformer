#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

uniform vec3 color;

void main()
{
    FragColor = (texture(texture1, TexCoord)) * vec4(color, 1);
}
