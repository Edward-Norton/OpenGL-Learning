#include "VAO.h"

VAO::VAO()
{
	//Generate VAO 
	glGenVertexArrays(1, &ID); //Generate Vertex Array(num object, point to reference) **Generate VAO BEFORE VBO
}

void VAO::linkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	/*Pass index of vertex attribute we want to use, vertex attribute is a way of comminicating with a vertex shader from outside
	//How many values per vertex
	//Type of value
	//Normalise, only if values are ints 
	//Stride: ammount of data between each vertex in bytes (12 for XYZ since each one is 4 bytes)
	Offset: point to where vertices begin in array*/
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

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
