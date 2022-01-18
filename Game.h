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
		Game(GLFWwindow* window) :
			window(window),
			UIShaderProgram("default.vert", "default.frag"),
			gameBgTexture("Resources/backgroundGame.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			menuBgTexture("Resources/backgroundMenu.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			buttonTexture("Resources/button.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			buttonHoverTexture("Resources/buttonHover.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			lifeTexture("Resources/bamboo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			boxTextures{
				Texture("Resources/box1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
				Texture("Resources/box2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
				Texture("Resources/box3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			},
			bgVerts
			{
				Vertex{ glm::vec3(-1.0f, -1.0f, -6.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) }, //0
				Vertex{ glm::vec3(1.0f, -1.0f,  -6.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }, //1 
				Vertex{ glm::vec3(-1.0f, 1.0f,  -6.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) }, //2
				Vertex{ glm::vec3(1.0f, 1.0f, -6.5f),    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) }, //3
			},
			bgInds
			{
				0,1,2,2,1,3
			},
			buttonVerts
			{
				Vertex{ glm::vec3(1.5f, 1.0f,   0),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //0
				Vertex{ glm::vec3(1.5f, -0.5f,  0),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //1 
				Vertex{ glm::vec3(-1.5f, 1.0f,  0),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //2
				Vertex{ glm::vec3(-1.5f, -0.5f, 0),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //3
			},
			buttonInds
			{
				0,1,2,2,1,3
			},
			lifeVerts
			{
				Vertex{ glm::vec3(1.0f, 1.0f,   -5.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //0
				Vertex{ glm::vec3(1.0f, -0.5f,  -5.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //1 
				Vertex{ glm::vec3(-1.0f, 1.0f,  -5.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //2
				Vertex{ glm::vec3(-1.0f, -0.5f, -5.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //3
			},
			lifeInds
			{
				0,1,2,2,1,3
			}
		{ };

		~Game() 
		{
			delete camera;
		}

		bool paused;

		void Start(double width, double height, GLFWwindow* window);
		void Update(double deltaTime);
		void PausedUpdate();

	private:
		GLFWwindow* window;
		Camera* camera;

		//updates
		void UpdateCamera();
		void UpdateHoverDetector();
		void DrawBackground();
		void DrawButton();
		void DrawLifeIcons();
		void UpdateBoxes(float deltaTime);

		//game control
		CollisionDetector hoverDetector;
		float points = 0;
		float lives = 3;
		void Pause();
		void Unpause();
		void AddPoint(Box* box);
		void DecreaseLives();
		void IncreaseDifficulty(float deltaTime);


		//diffliculty
		float difficulty = 1;
		float boxSpawnTimer = 1;
		float currentBoxSpawnTimer = 1;

		//setup
		ShaderProgram UIShaderProgram;

		void SetupCamera(double width, double height);

		void SetupBackground();
			Mesh* buttonMesh;
			Texture buttonTexture;
			Texture buttonHoverTexture;
			Vertex buttonVerts[4];
			GLuint buttonInds[6];

		void SetupButton();
			Mesh* backgroundMesh;
			Texture gameBgTexture;
			Texture menuBgTexture;
			Vertex bgVerts[4];
			GLuint bgInds[6];

		void SetupLifeIcons();
			Mesh* lifeMeshes[3];
			Texture lifeTexture;
			Vertex lifeVerts[4];
			GLuint lifeInds[6];

		//box control
		std::vector<Box*> boxes;
		Texture boxTextures[3];
		Texture GetRandomBoxTexture();
		void SpawnBoxes();

		//utilities
		bool IsMouseButtonClicked();

};

#endif
