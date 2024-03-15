#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); //Generate buffer (One object, point to reference)
	
	/*Make an object the current object, when we change that object, it changes the current object,
	aka the binding object*/
	glBindBuffer(GL_ARRAY_BUFFER, ID); //Array buffer for vertex array

	//Store vertices to VBO (Alocate to gpu)
	/*Specify the type of buffer, total size of data in bytes, data itself and use.
	For use Stream is modifed once, used a few times; Static is modified once and used many times; Dynamic is modifed multiple times, used multiple times */
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
