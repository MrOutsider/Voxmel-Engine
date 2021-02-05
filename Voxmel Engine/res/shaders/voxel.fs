#version 330 core

in vec2 UVs;

out vec4 FragColor;

uniform sampler2D albedo;

void main()
{
    FragColor = texture(albedo, UVs);
}