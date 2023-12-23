#version 330 core

in vec4 vertexColor;
in vec2 TexCoord;

// Color of each vertex.
out vec4 FragColor;
// Texture sampler.
uniform sampler2D ourTexture;
// Normal vector.
in vec3 Normal;
// 
in vec3 FragPos;

// Light parameters
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    // FragColor = texture(ourTexture, TexCoord);
    // FragColor = vec4(lightColor * objectColor, 1.0);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
