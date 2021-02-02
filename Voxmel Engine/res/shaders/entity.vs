#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec3 Normals;
out vec2 UVs;

void main()
{
    gl_Position = vec4 (aPos, 1.0f);    // (MVP * aPos) done on CPU once - Projection Space

    Normals = aNorm;                    // (MV * aNorm) done on CPU once - View Space
    UVs = aUV;                          // (MV * aUV) done on CPU once - View Space
}