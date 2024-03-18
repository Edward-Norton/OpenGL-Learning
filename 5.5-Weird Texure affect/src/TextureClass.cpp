#include "TextureClass.h"

// USING STB_LIB

TextureClass::TextureClass(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the texture to the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    /*Reads the image: This will read the image width and height and assign those values, 
    Color channels is the number of colors used by the image,
    Channel is the number of channels, we have 0 so the orignal channels, 1 is greyscale, 3 is RBG, 4 is RGBA */
    unsigned char* imageData = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger (Make image retain the same look when closer or further)
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all) (S=horizontal, T=Verical) //Makes it repeat texture if it passes [0,1] range
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    // Parameters:
    /* texType: Target texture type, such as GL_TEXTURE_2D.
     0: Mipmap level. 0 represents the base image level. (Higher levels result in more downscaling)
     GL_RGBA: Internal format of the texture data. Specifies the number and order of color components (red, green, blue, alpha).
     widthImg, heightImg: Dimensions of the image.
     0: Border size. Typically set to 0.
     format: Format of the pixel data in bytes. Should match the format of the image data (e.g., GL_RGB, GL_RGBA).
     pixelType: Data type of the pixel data in bytes (e.g., GL_UNSIGNED_BYTE for 8-bit unsigned bytes).
     bytes: Pointer to the image data loaded from the file. */
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, imageData);
    // Generates MipMaps
    glGenerateMipmap(texType);

    // Deletes the image data as it is already in the OpenGL Texture object
    stbi_image_free(imageData);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(texType, 0);
}

void TextureClass::textureIDUni(Shader& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void TextureClass::Bind()
{
    glBindTexture(type, ID);
}

void TextureClass::Unbind()
{
    glBindTexture(type, 0);
}

void TextureClass::Delete()
{
    glDeleteTextures(1, &ID);
}