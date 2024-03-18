#include"EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    // Generate buffer object
    glGenBuffers(1, &ID);

    // Bind the buffer object so it becomes the active buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    // Copy index data to the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
