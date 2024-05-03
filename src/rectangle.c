#include "rectangle.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>


static void* debug_rect(void* ptr,char* msg) {
	
	if (ptr == NULL)
	{
		fprintf(stderr ,"error : %s\n",msg);
		exit(-1);
	}
	
	return ptr;
}


Rectangle* new_rectangle(float* pos_and_clr , int* indecies)
{
	if (pos_and_clr == NULL || indecies == NULL)
	{
		fprintf
			(
				stderr , 
				"posirion and color pointer or indecies pointer or both is null\n"
			);
		return NULL;
	}
	
	Rectangle* r = (Rectangle*)debug_rect(malloc(sizeof(Rectangle)),"can not create rect ptr");
	
	r->position_and_color = (float*)debug_rect(malloc(sizeof(float)),"can not create rect pos and clr ptr");
	r->indecies			  = (int*)debug_rect(malloc(sizeof(int)),"can not create indecies ptr"); 

	

	r->position_and_color = pos_and_clr;
	r->indecies			  = indecies;
	
	return r;
		
}

void draw(Rectangle* rectangle)
{
		
}

void destroy_rectangle(Rectangle* rectangle)
{
	free(rectangle->position_and_color);
	free(rectangle->indecies);

	glDeleteProgram(rectangle->shader_program);

	free(rectangle);
}
