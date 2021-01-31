#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 MVP;

uniform mat3 normalMat;
uniform vec3 lightPos;

void main()
{
    FragPos = vec3(view * model * vec4(aPos, 1.0f));
    Normal = normalMat * aNormal;

    gl_Position = MVP * vec4(aPos , 1.0f);
}