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
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    // FragColor = texture(ourTexture, TexCoord);
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vertexColor.rgb;
    FragColor = vec4(result, 1.0);
}
