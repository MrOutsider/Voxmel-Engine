#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D albedoTexture;
uniform sampler2D roughnessTexture;

void main()
{
	gl_FragColor = mix(texture(albedoTexture, texCoord), texture(roughnessTexture, texCoord), 0.2) * vec4(ourColor, 1.0);
}