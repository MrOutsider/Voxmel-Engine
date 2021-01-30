#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D albedoTexture;
uniform sampler2D secondTexture;

void main()
{
	FragColor = texture(albedoTexture, texCoord);
}