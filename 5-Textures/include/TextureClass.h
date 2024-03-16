#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"ShaderClass.h"


class TextureClass
{
public:
	GLuint ID;
	GLenum type;
	
	TextureClass(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader shader, const char* uniform, GLuint unit);

	void Bind(); //Binds the VAO using glBindVertexArray.
	void Unbind();
	void Delete();

};

