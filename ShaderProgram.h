#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

using namespace std;

class ShaderProgram
{
	public:
		GLuint ID;
		ShaderProgram(const char* vertexFile, const char* fragmentFile);
		void Activate();
		void Delete();

	private:
		void PrintShaderErrors(GLuint ID, const char* shaderName);
		void PrintProgramErrors(GLuint ID);
};


#endif