#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"ScreenSize.h"

#include"ShaderClass.h"
#include"TextureClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//----------INDICES and Vertex Buffer----------
	//GlFloat to make an array of vertex points 
GLfloat vertices[] =
{	//			COORDINATES (X,Y,Z)		/	COLORS			/ TEXTURE MAP	
   -0.5f,   -0.5f,     0.0f,			1.f,  0.3f,  0.0f,		0.0f, 0.0f,// Lower left corner (0)
   -0.5f,    0.5f,     0.0f,			0.0f, 1.0f,  0.0f,		0.0f, 1.0f,// Upper left corner (1)
	0.5f,    0.5f,	   0.0f,			0.0f, 0.0f,  1.0f,		1.0f, 1.0f,// Upper right corner (2)
    0.5f,   -0.5f,	   0.0f,			1.0f, 1.0f,  1.0f,		1.0f, 0.0f// Inner left corner (3)
};

//Using the vertex points above we make a new array to use each point to make a shape
GLuint indices[] =
{
	0, 2, 1, //Upper triangle
	0, 3, 2	 //Lower triangle
};

int main()
{
	//Screen size 
	const int Screen_Width = ScreenSize::s_width;
	const int Screen_Height = ScreenSize::s_height;

	//Initalise GLFW 
	glfwInit(); 

	//Hint to version of OpenGl
	/*Here we hint the major and minor verions, 3 since its version 3.0 build*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Core profile uses "modern" openGl, other one uses old and new. This is a package of functions
	

	//Make window object
	GLFWwindow* window = glfwCreateWindow(Screen_Width, Screen_Height, "OpenGLTesting", NULL, NULL); //Width, height, title, fullscreen, share resources
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window \n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //Make this window the current context

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL to the window
	// This tells OpenGL how to map its coordinate system to the window's pixels.
	// It goes from x=0 -> x=ScreenWidth, and y=0 -> y=ScreenHeight.
	glViewport(0, 0, Screen_Width, Screen_Height);

	//----------SHADER PROGRAM----------
	Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");


	//----------BUFFER DATA----------
	//Sending stuff to GPU from CPU is slow, we send them in batches

	//----------VERTEX ARRAY OBJECT----------
	VAO VAO1;
	VAO1.Bind();

	//----------VERTEX BUFFER OBJECT----------
	//Stores pointers to one or more VBOs, tells openGL how to interpretate them
	//VAOs are used to switch between different VBOs 

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));

	//----------INDEX/ELEMENT ARRAY OBJECT----------

	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));


	//Link VBO attribites such as coordinates, color and texture to VAO
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); //Coordinates
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float))); //Color
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //Texture

	//----------Unbind data---------- (Needs to be in this order)
	VAO1.Unbind();
	VBO1.UnBind();
	EBO1.UnBind();

	//----------GL UNIFORMS----------
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//----------TEXTURES----------
	TextureClass popCat("Resources/Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//Main while lopp
	while (!glfwWindowShouldClose(window)) //Shouldnt close window
	{
		// Specify the color of the background
		// This sets the color to clear the screen to when glClear is called.
		// Arguments are red, green, blue, alpha (transparency) values ranging from 0.0 to 1.0.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clear the back buffer and assign the new color to it
		// The color buffer stores the color values of pixels.
		glClear(GL_COLOR_BUFFER_BIT);

		//Shader
		shaderProgram.Activate(); //Use this shader
		glUniform1f(uniID, 0.5f);

		//Binding
		popCat.Bind();
		VAO1.Bind(); //Tell openGL we want to use this one

		//Drawing
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //(Primitave type, num indices, type and index of indices 

		//Update image each frame
		glfwSwapBuffers(window);

		//Take core of GLFW events
		glfwPollEvents();
	}

	//Deleting objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	popCat.Delete();


	//Delete the window before ending program
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}




//Summary and notes
/*
1: Vertex Buffer Object (VBO): 
This object is responsible for storing vertex data, such as positions, colors, and texture coordinates. 
It allocates memory on the GPU and fills it with vertex data using glBufferData. 
The data from the vertices array is stored in the VBO.

2: Vertex Array Object (VAO): 
VAO encapsulates the configuration of vertex attributes. 
It specifies how vertex data stored in VBOs should be interpreted. 
glVertexAttribPointer is used to define the layout of vertex attributes, such as positions or colors. 
glEnableVertexAttribArray enables the vertex attribute array. The VAO retains this configuration.

3: Element Buffer Object (EBO): 
EBO is employed to store indices that determine the order of vertices for rendering primitives like triangles or lines. 
glBufferData is utilized to populate it with index data from the indices array. 
During glDrawElements invocation, OpenGL retrieves vertices from the VBO using these indices to construct primitives.

*/