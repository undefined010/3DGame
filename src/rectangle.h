/*
 * @author :- Ahmad Odeh (undefined010)
 * @date   :- 3rd May, 2024
 * @about  :- rectangle structure header
 */


#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdint.h>

typedef struct {
	uint32_t VBO,EBO;
	uint32_t VAO;

	float* position_and_color;
	int* indecies;

	uint32_t shader_program;
} Rectangle;

Rectangle* new_rectangle(float* pos_and_clr , int* indecies );
void draw_rectangle(Rectangle* rectangle);
void destroy_rectangle(Rectangle* rectangle);


#endif
