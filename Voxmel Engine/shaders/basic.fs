#version 330 core

in vec3 ourColor;

out vec4 vertexColor;

void main()
{
	vertexColor = vec4(ourColor, 1.0);
}