
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
	/*Specifies how the data stored in the VBO should be interpreted.
	//(Vbo object to link to, layout is index to bind, numCompontents is how many indices, 
	type is what primative oepnGL type, stride is byte offset between start of each attibute, offset is where this data beings)*/
	void linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind(); //Binds the VAO using glBindVertexArray.
	void Unbind();
	void Delete();
};

#endif 

