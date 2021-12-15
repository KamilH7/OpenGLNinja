#include"ShaderProgram.h"
using namespace std;

// Returns everything in the specified file as text
const char* ReadFile(const char* path)
{
	ifstream file(path, ios::binary);

	if (file)
	{
		string contents;
		file.seekg(0, ios::end);
		contents.resize(file.tellg());
		file.seekg(0, ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return contents.c_str();
	}
	throw(errno);
}

// Constructor that creates a shader program from the vertex and fragment shaders. Configures OpenGL accordingly.
ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	// Get source code from both shaders
	const char* vertexSource = ReadFile(vertexFile);
	const char* fragmentSource = ReadFile(fragmentFile);

	// Create shader objects
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Tell shaders what their source code is
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	// Compile shaders
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Print compilation errors (if there were any) to the console
	PrintShaderErrors(vertexShader, "Vertex Shader");
	PrintShaderErrors(fragmentShader, "Fragment Shader");
	
	// Create shader program 
	ID = glCreateProgram();

	// Attach the shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link the newly created program
	glLinkProgram(ID);

	// Print linking errors (if there were any) to the console
	PrintProgramErrors(ID);

	// Since the shaders are compiled in machine code, we dont need the objects anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Prints shader compilation errors (if there were any) to the console
void ShaderProgram::PrintShaderErrors(GLuint shaderID, const char* shaderName)
{
	GLint hasCompiled;
	char infoLog[1024];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);

	if (hasCompiled == GL_FALSE)
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		cout << shaderName << " compilation has come across errors:" << "\n" << infoLog << std::endl;
	}
}

// Prints program linking errors (if there were any) to the console
void ShaderProgram::PrintProgramErrors(GLuint ID)
{
	GLint hasCompiled;
	char infoLog[1024];

	glGetProgramiv(ID, GL_LINK_STATUS, &hasCompiled);

	if (hasCompiled == GL_FALSE)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		cout << "Program linking has come across errors:" << "\n" << infoLog << std::endl;
	}
}

// Activate the shader program
void ShaderProgram::Activate()
{
	glUseProgram(ID);
}

// Delete the shader program
void ShaderProgram::Delete()
{
	glDeleteProgram(ID);
}
	