
/*
 * @author :- Ahmad Odeh (undefined010)
 * @date   :- 2nd May, 2024
 * @about  :- a warpper for reading and compiling GLSL files
 * */


#include "shaders.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

char* read_glsl_file(const char* file_name)
{
	if (file_name == NULL) {
		fprintf(stderr,"file name is null\n");
		return NULL;
	}

	FILE* file_ptr = fopen(file_name,"r");

	if (file_ptr == NULL) {
		fprintf(stderr, "file pointer can not be created !\n");
		return NULL;
	}

	/* TO GET SHADER FILE SIZE */
	fseek(file_ptr,0,SEEK_END);
	size_t file_size = ftell(file_ptr);
	fseek(file_ptr,0,SEEK_SET);

	char* file_content = malloc(sizeof(char) * (file_size ));
	
	if (file_content == NULL) {
		fprintf(stderr , "failed to malloc memory to file content pointer\n");
		return NULL;
	}


	/* READING FILE */
	fread(file_content,sizeof(char),file_size,file_ptr);
	file_content[file_size] = '\0'; // took 15 min to debug this shit
	fclose(file_ptr);

	return file_content;
}

void debug_shader(unsigned int shader,unsigned int shader_type) 
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (shader_type == GL_VERTEX_SHADER)
            fprintf(stderr,"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s",infoLog);
        if (shader_type == GL_FRAGMENT_SHADER)
            fprintf(stderr,"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s",infoLog);
    }

}

unsigned int compile_shaders(const char *shader_source,unsigned int shader_type)
{
    if (shader_source == NULL) {
        fprintf(stderr, "there are no shaders source!\n");
        return -1;
    }

    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader,1,&shader_source,NULL);
    glCompileShader(shader);

    debug_shader(shader,shader_type);

    return shader;
}

void debug_shader_program(unsigned int program)
{
    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr,"ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s",infoLog);
    }
}   

unsigned int compile_shader_program(unsigned int vertex_shader, unsigned int fragment_shader)
{
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
