#version 330 core
layout (location = 0) in vec3 aPos;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 viewProjection;

void main()
{
    gl_Position = viewProjection * model * vec4(aPos, 1.0);
}