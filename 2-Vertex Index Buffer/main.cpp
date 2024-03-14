#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"ScreenSize.h"

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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


	//----------VERTEX SHADER----------
	//Value / reference to store our vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Make shader, specify type
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //(Reference to shader, 1 string, point to source code, Null)
	glCompileShader(vertexShader); //GPU doesnt understand, need to be compiled as machine code now

	//----------FRAGMENT SHADER----------
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//----------SHADER PROGRAM----------
	GLuint shaderProgram = glCreateProgram(); //Make a progam to "wrap" shaders
	//Attach these shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Delete the shaders since they are now in the program itself
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//----------INDICES and Vertex Buffer----------

	//GlFloat to make an array of vertex points 
	GLfloat vertices[] =
	{	//Positions (X,Y,Z)
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower left corner (0)
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //Lower right corner (1)
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper corner (2)
		-0.5f / 2, 0.5f * float(sqrt(3)) /6, 0.0f, //Inner left (3)
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right (4)
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner Down (5)
	};

	//Using the vertex points above we make a new array to use each point to make a shape
	GLuint indices[] =
	{
		0,3,5, //Lower left triangle
		3,2,4, //Lower right triangle
		5,4,1 //Upper triangle
	};

	//----------BUFFER DATA----------
	//Sending stuff to GPU from CPU is slow, we send them in batches
	GLuint VAO, VBO, EBO; //Vertex array object, vertec buffer object, element buffer object 
	//Generate VAO and VBO
	glGenVertexArrays(1, &VAO); //Generate Vertex Array(num object, point to reference) **Generate VAO BEFORE VBO
	glGenBuffers(1, &VBO); //Generate buffer (One object, point to reference)
	glGenBuffers(1, &EBO); //Buffer for indice array elements

	//Binding
	glBindVertexArray(VAO);

	/*Make an object the current object, when we change that object, it changes the current object,
	aka the binding object*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Array buffer for vertex array

	//Store vertices to VBO (Alocate to gpu)
	/*Specify the type of buffer, total size of data in bytes, data itself and use.
	For use Stream is modifed once, used a few times; Static is modified once and used many times; Dynamic is modifed multiple times, used multiple times */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//----------INDEX/ELEMENT ARRAY OBJECT----------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//----------VERTEX ARRAY OBJECT----------
	//Stores pointers to one or more VBOs, tells openGL how to interpretate them
	//VAOs are used to switch between different VBOs 

	//Pass index of vertex attribute we want to use, vertex attribute is a way of comminicating with a vertex shader from outside
	//How many values per vertex
	//Type of value
	//Normalise, only if values are ints 
	//Stride: ammount of data between each vertex in bytes (12 for XYZ since each one is 4 bytes)
	//Offset: point to where vertices begin in array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//Enable attribute
	glEnableVertexAttribArray(0); //Position of vertex attribute

	//----------Unbind data---------- (Needs to be in this order)
	glBindBuffer(GL_ARRAY_BUFFER, 0); //VBO
	glBindVertexArray(0); //VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //EBO

	// Specify the color of the background
	// This sets the color to clear the screen to when glClear is called.
	// Arguments are red, green, blue, alpha (transparency) values ranging from 0.0 to 1.0.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear the back buffer and assign the new color to it
	// The color buffer stores the color values of pixels.
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back buffer with the front buffer
	// This updates the window with the contents of the back buffer.
	glfwSwapBuffers(window);


	//Main while lopp
	while (!glfwWindowShouldClose(window)) //Shouldnt close window
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); //Use program
		glBindVertexArray(VAO); //Tell openGL we want to use this one

		//Drawing
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //(Primitave type, num indices, type and index of indices 

		//Update image each frame
		glfwSwapBuffers(window);

		//Take core of GLFW events
		glfwPollEvents();
	}

	//Deleting objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


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