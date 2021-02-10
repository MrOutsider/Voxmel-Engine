#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aIntersect;

flat out int Intersect;

uniform mat4 MVP;

void main()
{
    Intersect = int(aIntersect);

    gl_Position = MVP * vec4(aPos, 1.0f);    // (MVP * aPos) done on CPU once - Projection Space
}