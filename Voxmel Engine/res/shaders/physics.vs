#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aIntersect;

out float Intersect;

uniform mat4 MVP;

void main()
{
    Intersect = aIntersect;

    gl_Position = MVP * vec4(aPos, 1.0f);    // (MVP * aPos) done on CPU once - Projection Space
}