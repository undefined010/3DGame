#ifndef BUFFER_OBJECTS_H
#define BUFFER_OBJECTS_H

typedef union {
	unsigned int vbo;
	unsigned int ebo;
	
} object_buffer;

unsigned int gen_buffer_object(int* pos_and_clr,unsigned int buffer_type );

#endif
