#ifndef SHADERS_H
#define SHADERS_H


char* read_glsl_file(const char* file_name);

/* debugging the compiled shader */
void debug_shader(unsigned int shader,unsigned int type);
/* compiling the shader */
unsigned int compile_shaders(const char* shader_source,unsigned int shader_type);

/* debugging the compiled shader program */
void debug_shader_program(unsigned int program);

/* compiling the shader program */
unsigned int compile_shader_program(unsigned int vertex_shader, unsigned int fragment_shader);

#endif 
