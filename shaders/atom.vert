#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
    Normal = vec3((transpose(inverse(viewMatrix * modelMatrix)) * vec4(aNorm, 0.0f)));
    FragPos = vec3(viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0));
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}