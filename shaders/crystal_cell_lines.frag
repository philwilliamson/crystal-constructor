#version 330 core

in vec3 pos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0 - (pos.z + 0.5), 1.0 - (pos.x + 0.5), pos.y + 0.5, 1.0);
}