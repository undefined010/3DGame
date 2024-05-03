#version 330 core
out vec4 FragColor;

in vec3 outcolors;

void main()
{
    FragColor = vec4(outcolors, 1.0f);
} 
