#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO {
public:
    GLuint ID;

    // Constructor to create and initialize an EBO
    EBO(GLuint* indices, GLsizeiptr size);

    // Bind the EBO
    void Bind();

    // Unbind the EBO
    void UnBind();

    // Delete the EBO, freeing up GPU memory
    void Delete();
};

#endif



