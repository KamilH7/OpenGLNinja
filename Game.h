#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glad/glad.h>
#include "Vertex.h"
#include "Texture.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class Game
{
	public:
		Game() : 
			boxShaderProgram("default.vert", "default.frag"), 
			boxTexture("Resources/box2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			vertices1
			{ 
				Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
				Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
				Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
				Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9		
			},
			vertices2
			{
				Vertex{glm::vec3(0.5f, 1.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
				Vertex{glm::vec3(0.5f, 1.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
				Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
				Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7
				Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
				Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9
			},
			indices
			{
				0,1,2,2,1,3,
				2,3,4,4,2,5,
				0,1,6,6,0,7,
				1,8,3,
				9,2,0
			}{ };

		void Start();
		void Update(double deltaTime);
		void Terminate();

	private:
		Vertex vertices1[10];
		Vertex vertices2[10];
		GLuint indices[24];
		Texture boxTexture;
		ShaderProgram boxShaderProgram;
		std::vector<Mesh*> meshes;
};

#endif
