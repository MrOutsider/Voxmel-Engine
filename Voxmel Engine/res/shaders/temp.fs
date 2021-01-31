#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

uniform Material material;

struct PointLight
{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3  position;
    vec3  direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform SpotLight light;

void main()
{
    //vec3 lightDir = normalize(light.position - FragPos);  // Spot
    //vec3 lightDir = normalize(-light.direction);          // Dir
    vec3 lightDir = normalize(-FragPos);                    // Spot Use light pos as cam that is vec3(0.0f, 0.0f, 0.0f)
    float theta = dot(lightDir, vec3(0.0f, 0.0f, 1.0f));
    
    vec3 ambient = vec3(0.1f, 0.1f, 0.1f) * texture(material.diffuse, TexCoords).rgb;

    if (theta > light.cutOff)
    {   
        // Normal
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

        // Specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
        diffuse  *= attenuation;
        specular *= attenuation;  

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0f);
    }
    else
    {
        FragColor = vec4(ambient, 1.0f);
    }
}