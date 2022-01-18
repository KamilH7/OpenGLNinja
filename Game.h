#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

#include "Vertex.h"
#include "Texture.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "HoverDetector.h"
#include "Box.h"
class Game
{
	public:
		bool paused;
		Game(GLFWwindow* window) :
			window(window),
			UIShaderProgram("default.vert", "default.frag"),
			bgTexture("Resources/dojo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			buttonTexture("Resources/button.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			buttonHoverTexture("Resources/buttonHover.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			bgVerts
			{
				Vertex{ glm::vec3(1.0f, 1.0f,   -6.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //0
				Vertex{ glm::vec3(1.0f, -1.0f,  -6.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //1 
				Vertex{ glm::vec3(-1.0f, 1.0f,  -6.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //2
				Vertex{ glm::vec3(-1.0f, -1.0f, -6.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //3
			},
			bgInds
			{
				0,1,2,2,1,3
			},
			buttonVerts
			{
				Vertex{ glm::vec3(1.0f, 1.0f,   -6.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //0
				Vertex{ glm::vec3(1.0f, -1.0f,  -6.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //1 
				Vertex{ glm::vec3(-1.0f, 1.0f,  -6.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //2
				Vertex{ glm::vec3(-1.0f, -1.0f, -6.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //3
			},
			buttonInds
			{
				0,1,2,2,1,3
			}
		{ };
		void Start(double width, double height, GLFWwindow* window);
		void Update(double deltaTime);
		void PausedUpdate();
		void Terminate();

	private:
		float points=0;
		void AddPoint(Box* box);
		float lives=3;
		void RemoveLife();
		void Restart();
		void SpawnBoxes();
		float difficulty = 1;
		float boxSpawnTimer = 1;
		float currentBoxSpawnTimer = 1;
		std::vector<Box*> boxes;

		//background and button variables
		ShaderProgram UIShaderProgram;

			//button
			Mesh* backgroundMesh;
			Texture bgTexture;
			Vertex bgVerts[4];
			GLuint bgInds[6];

			//background
			Mesh* buttonMesh;
			Texture buttonTexture;
			Texture buttonHoverTexture;
			Vertex buttonVerts[4];
			GLuint buttonInds[6];

		CollisionDetector collisionDetector;
		GLFWwindow* window;
		Camera* camera;
		std::vector<Mesh*> meshes;
};

#endif
