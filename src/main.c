#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "shaders.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

void init_glfw()
{
    if (!glfwInit()) {
        exit(-1);
    }

    /* OPENGL HINTS*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

GLFWwindow* create_window(int32_t width, int32_t height, char* title) {

    if (title == NULL) {
        fprintf(stderr, "title is null\n");
        return NULL;
    }


    GLFWwindow* window = glfwCreateWindow(width, height,title, NULL, NULL);

    if (window == NULL) {
            fprintf(stderr, "window is null\n");
        return NULL;
    }

    return window;
}


void framebuffer_size_callback(GLFWwindow* window,int width , int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height );
}

int main() 
{
    
    init_glfw();

    /*INIT GLFW WINDOW*/
    GLFWwindow* window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    glfwMakeContextCurrent(window);
    framebuffer_size_callback(window,WINDOW_WIDTH,WINDOW_HEIGHT);

    /*INIT GLEW*/
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "failed to init glew\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    float vertices[] = {
        0.5f ,-0.5f, 0.0f,	1.0,0.0,0.0,	// bottom right
        -0.5f,-0.5f, 0.0f, 	0.0,1.0,0.0,//bottom left
        -0.5f,0.5f , 0.0f, 	0.0,0.0,1.0,//top left
        0.5f ,0.5f,  0.0f, //top right
    };
	

    unsigned int indices[] = {
        0,1,3, // first trig
        1,2,3  // second trig
    };
	

    const char *VERTEX_SHADER_SOURCE 		= read_glsl_file("src/glsl/vertex_shader.vs");

	const char *FRAGMENT_SHADER_SOURCE   	= read_glsl_file("src/glsl/fragment_shader.fs");
	
#ifndef debug
	fprintf(stdout , "fragment shader : %s\n",FRAGMENT_SHADER_SOURCE);
#endif

    GLuint vertex_shader    = compile_shaders(VERTEX_SHADER_SOURCE, GL_VERTEX_SHADER);
    GLuint fragment_shader  = compile_shaders(FRAGMENT_SHADER_SOURCE, GL_FRAGMENT_SHADER);
    GLuint shader_program   = compile_shader_program(vertex_shader, fragment_shader);

    /*INIT VBOs, EBOs AND VAOs*/

    GLuint vbo;
    GLuint vao;
    GLuint ebo;
	
	glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    glGenVertexArrays(1,&vao);
    
	glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*) 0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3, GL_FLOAT , GL_FALSE, 6 * sizeof(float),(void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
       

        glBindVertexArray(vao);
        glUseProgram(shader_program);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    
    }

    glfwDestroyWindow(window);
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&vao);
    glDeleteProgram(shader_program);
    glfwTerminate();

    

    return 0;

}
