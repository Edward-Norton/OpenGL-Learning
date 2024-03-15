#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
public:
    GLuint ID;

    // Constructor to create and initialize a VBO
    VBO(GLfloat* vertices, GLsizeiptr size);

    // Bind the VBO
    void Bind();

    // Unbind the VBO
    void UnBind();

    // Delete the VBO, freeing up GPU memory
    void Delete();
};

#endif

