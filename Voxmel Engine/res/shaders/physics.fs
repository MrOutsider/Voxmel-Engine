#version 330 core

flat in int Intersect;

out vec4 FragColor;


void main()
{
    vec3 color = vec3(1.0f, 1.0f, 1.0f);

    if (Intersect == 0.0f)
    {
        color = vec3(0.0f, 1.0f, 0.0f);
    }
    else if (Intersect == 1)
    {
        color = vec3(1.0f, 0.0f, 0.0f);
    }
    else if (Intersect == 2)
    {
        color = vec3(0.7f, 0.5f, 0.0f);
    }

    FragColor = vec4(color, 1.0f);
}