#version 330 core

in float Intersect;

out vec4 FragColor;


void main()
{
    vec3 color = vec3(5.0f, 1.0f, 5.0f);

    if (Intersect == 0.0f)
    {
        color = vec3(0.0f, 1.0f, 0.0f);
    }
    else if (Intersect == 1.0f)
    {
        color = vec3(1.0f, 0.0f, 0.0f);
    }

    FragColor = vec4(color, 1.0f);
}