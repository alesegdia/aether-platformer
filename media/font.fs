#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec4 textColor;

uniform float bias;

void main()
{
    vec4 color = texture(texture1, TexCoord);
    if(color.a < 0.1)
        discard;

    FragColor = color * textColor;
}
