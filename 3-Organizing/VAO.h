
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

//----------VERTEX ARRAY OBJECT----------

class VAO
{
public:
	GLuint ID;
	VAO(); //Make a new Vertex array object

	//Links the VBO to the VAO. 
	/*Specifies how the data stored in the VBO should be interpreted.*/
	void linkVBO(VBO VBO, GLuint layout); //(Vbo object to link to, layout is index to bind)

	void Bind(); //Binds the VAO using glBindVertexArray.
	void Unbind();
	void Delete();
};

#endif 

