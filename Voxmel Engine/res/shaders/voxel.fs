#version 330 core

in vec2 UVs;
in float Light;

out vec4 FragColor;

uniform sampler2D albedo;

void main()
{
    FragColor = texture(albedo, UVs) * (Light / 15.0f);
}