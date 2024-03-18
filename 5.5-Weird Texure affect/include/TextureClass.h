#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"ShaderClass.h"


class TextureClass
{
public:
    GLuint ID; // This member variable will store the ID of the texture object.
    GLenum type; // This member variable will store the type of the texture (e.g., GL_TEXTURE_2D).

    // Constructor for TextureClass.
    // Parameters:
    // - image: Path to the image file.
    // - texType: Type of texture (e.g., GL_TEXTURE_2D).
    // - slot: Texture unit slot to which the texture will be bound.
    // - format: Format of the image data (e.g., GL_RGB, GL_RGBA).
    // - pixelType: Data type of the pixel data (e.g., GL_UNSIGNED_BYTE). used for precision e.g for color accuracy 
    TextureClass(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Method to bind the texture unit to a shader uniform.
    // Parameters:
    // - shader: Shader object to which the texture will be bound.
    // - uniform: Name of the uniform variable in the shader.
    // - unit: Texture unit index.
    void textureIDUni(Shader& shader, const char* uniform, GLuint unit);

    // Method to bind the texture object.
    void Bind(); //Binds the VAO using glBindVertexArray.

    // Method to unbind the texture object.
    void Unbind();

    // Method to delete the texture object.
    void Delete();
};

