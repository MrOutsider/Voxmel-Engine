#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    gl_FragColor = vec4(lightColor, 1.0);
}