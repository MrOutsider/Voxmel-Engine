#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUVs;
layout (location = 2) in float aLight;

out vec2 UVs;
out float Light;

uniform mat4 MVP;

void main()
{
    UVs = aUVs;
    Light = aLight;

    gl_Position = MVP * vec4(aPos, 1.0f);    // (MVP * aPos) done on CPU once - Projection Space
}