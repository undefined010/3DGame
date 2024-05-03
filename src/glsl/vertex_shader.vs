#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aClr;

out vec3 outcolors;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	outcolors		= aClr;		
}
