#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 0) in vec2 aTexCoord;

out vec4 vertexColor;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos, 1.0f);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}