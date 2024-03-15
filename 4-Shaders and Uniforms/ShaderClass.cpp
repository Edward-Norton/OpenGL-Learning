#include "ShaderClass.h"

std::string get_file_contents(const char* fileName)
{
    // Open the file specified by fileName in binary mode for reading 
	/*Binary mode its not platform specific, so it doesnt take \n,\r. Reads byte data wihout modification by input/ouput stream*/
    std::ifstream in(fileName, std::ios::binary);

    // Check if the file was successfully opened
    if (in)
    {
        // Declare a string named contents to store the file contents
        std::string contents;

        // Seek to the end of the file to determine its size
        in.seekg(0, std::ios::end);

        // Resize the contents string to match the file size
        contents.resize(in.tellg());

        // Seek back to the beginning of the file
        in.seekg(0, std::ios::beg);

        // Read the entire contents of the file into the contents string
        in.read(&contents[0], contents.size());

        // Close the file
        in.close();

        // Return the contents of the file as a string
        return(contents);
    }

    // If the file cannot be opened, throw an exception with the error number
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Get contents as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Then convert to character arrays
	const char* vertexSource = vertexCode.c_str(); //c_str() returns a char*, convert c++ string to c style string
	const char* fragmentSource = fragmentCode.c_str();

	//----------VERTEX SHADER----------
	//Value / reference to store our vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Make shader, specify type
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //(Reference to shader, 1 string, point to source code, Null)
	glCompileShader(vertexShader); //GPU doesnt understand, need to be compiled as machine code now

	//----------FRAGMENT SHADER----------
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//----------SHADER PROGRAM----------
	ID = glCreateProgram(); //Make a progam to "wrap" shaders
	//Attach these shaders to the program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	//CHECK COMPILE ERRORS
	compileErrors(vertexShader, "VERTEX");
	compileErrors(fragmentShader, "FRAGMENT");
	compileErrors(ID, "PROGRAM");

	//Delete the shaders since they are now in the program itself
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//Turing on and off the program
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}


//Check shader has compiled
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") //Shader check
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else //Program check
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}
