#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 atomColor;

void main()
{
    float ambient = 0.2f;
    
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(3.0f, 1.0f, 2.0f));
    float diffuse = 0.7f * max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.1f;
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    float specular = specularLight * specAmount;
    
    FragColor = (diffuse + ambient + specular) * vec4(atomColor, 1.0f);
}