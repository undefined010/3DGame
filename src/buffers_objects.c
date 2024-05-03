#include <GL/glew.h>
#include "buffers_objects.h"

unsigned int gen_buffer_object(int* pos_and_clr, unsigned int buffer_type)
{
	object_buffer buffer;

	unsigned int buffer_obj;

	glGenBuffers(1,&buffer_obj);
	

	if (buffer_type == GL_ARRAY_BUFFER) {
		buffer.vbo = buffer_obj;
		glDeleteBuffers(1,&buffer_obj);

		glBindBuffer(buffer_type,buffer.vbo);
		glBufferData(buffer_type,sizeof(pos_and_clr),pos_and_clr,GL_STATIC_DRAW);

		glBindBuffer(buffer_type,0);

		return buffer.vbo;
	}
}
