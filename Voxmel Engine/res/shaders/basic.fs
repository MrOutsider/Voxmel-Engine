#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D albedoTexture;

uniform int blockX;
uniform int blockY;

void main()
{
	float xOffset = 0 + blockX;
	float yOffset = 0 + blockY;

	xOffset = xOffset / 32.0f;
	yOffset = yOffset / 16.0f;

	int lightLevel = 11;
	float lightFloat = lightLevel / 20.0f;

	FragColor = texture(albedoTexture, vec2(texCoord.x + xOffset, texCoord.y + yOffset)) * lightFloat;
}