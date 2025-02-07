#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 viewProjection;

uniform vec2 uv0;
uniform vec2 uv1;

void main()
{
    gl_Position = viewProjection * model * vec4(aPos, 1.0);
    TexCoord = uv0 + aTexCoord * (uv1 - uv0);
}