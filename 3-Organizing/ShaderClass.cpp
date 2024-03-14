#include "ShaderClass.h"

std::string get_file_contents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Get contents as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Then convert to character arrays
	const char* vertexSource = vertexCode.c_str();
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
