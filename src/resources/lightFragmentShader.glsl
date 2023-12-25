#version 330 core

// Materials structure
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Light structure
struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 FragPos;

// Color of each vertex.
out vec4 FragColor;
// Texture sampler.
uniform sampler2D ourTexture;
// Normal vector.
in vec3 Normal;

// Light parameters
uniform int lightType;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir;

    // diffuse
    if (lightType == 0)     // calculating direcitonal light
    {
        lightDir = normalize(-light.direction);
    }
    else
    {
        lightDir = normalize(light.position - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;  

    // calculating a pointlight
    if (lightType == 1)
    {
        // attenuation
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    }
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
