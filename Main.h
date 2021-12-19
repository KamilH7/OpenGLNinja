#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"ShaderProgram.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

using namespace std;

const char* windowName = "GLNinja";
const int windowWidth = 800;
const int windowHeight = 800;
GLFWwindow* window;

const char* vertexShaderPath = "default.vert";
const char* fragmentShaderPath = "default.frag";
ShaderProgram* shaderProgram;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	2.0f, 0.0f, // back left down
	 0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f, // back right down
	 0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 2.0f, // back right up
	-0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	2.0f, 2.0f, // back left up

	-0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f, // front left down
	 0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	2.0f, 0.0f, // front right down
	 0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	2.0f, 2.0f, // front right up
	 -0.5f, 0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 2.0f  // front left up
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 3, 3, 1, 2,
	1, 5, 2, 2, 5, 6,
	5, 4, 6, 6, 4, 7,
	4, 0, 7, 7, 0, 3,
	3, 2, 7, 7, 2, 6,
	4, 5, 0, 0, 5, 1
};

#endif