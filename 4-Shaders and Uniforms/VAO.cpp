#include "VAO.h"

VAO::VAO()
{
	//Generate VAO 
	glGenVertexArrays(1, &ID); //Generate Vertex Array(num object, point to reference) **Generate VAO BEFORE VBO
}

void VAO::linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	/*Pass index of vertex attribute we want to use, vertex attribute is a way of comminicating with a vertex shader from outside
	//How many values per vertex
	//Type of value
	//Normalise, only if values are ints 
	//Stride: ammount of data between each vertex in bytes (With colors, its 6*sizeof(float) to make 24 bytes, 12 for color, skip next 12 color, numComp is 3 so we only use first 12 bytes)
	Offset: point to where vertices begin in array*/
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	//Enable attribute
	glEnableVertexAttribArray(layout); //Position of vertex attribute
	VBO.UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
