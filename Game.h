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
			window(window) {};
		void Start(double width, double height, GLFWwindow* window);
		void Update(double deltaTime);
		void Terminate();
	private:
		void HandleInput();
		std::vector<Box*> boxes;
		CollisionDetector collisionDetector;
		GLFWwindow* window;
		Camera* camera;
		std::vector<Mesh*> meshes;
};

#endif
