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
#include"Mesh.h"
#include"DeltaTime.h"

using namespace std;

const char* windowName = "GLNinja";
const int windowWidth = 800;
const int windowHeight = 800;
GLFWwindow* window;

const char* vertexShaderPath = "default.vert";
const char* fragmentShaderPath = "default.frag";

Vertex vertices1[] =
{
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
	Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
	Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
	Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
	Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9
};

Vertex vertices2[] =
{
	Vertex{glm::vec3( 0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
	Vertex{glm::vec3( 0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
	Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
	Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
	Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
	Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5

	Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
	Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7

	Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
	Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9
};

GLuint indices[] =
{
	 0,1,2,2,1,3,
	 2,3,4,4,2,5,
	 0,1,6,6,0,7,
	 1,8,3,
	 9,2,0
};

#endif