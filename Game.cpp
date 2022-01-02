#include "Game.h"

void Game::Start(double width, double height, GLFWwindow* window)
{
	camera = new Camera(width, height, glm::vec3(0.0f, 0.5f, 5.0f));
}

void Game::Update(double deltaTime)
{
	camera->UpdateMatrix(45.0f,0.1f,200.0f);
	HandleInput();

	for (int i = 0; i< boxes.size(); i++) 
	{
		boxes[i]->Update(camera, deltaTime);
		//collisionDetector.IsColliding(boxes[i]);

		//if (boxes[i]->CheckBounds()) 
		//{
		//	delete boxes[i];
		//	//remove box from a vector
		//	boxes.erase(boxes.begin()+i);
		//	i--;
		//}
	}
}

void Game::HandleInput()
{
	camera->Inputs(window);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	collisionDetector.Update(camera, xpos, ypos);

	int zero = glfwGetKey(window, GLFW_KEY_0);
	if (zero == GLFW_PRESS)
	{
		Box* box = new Box(boxShaderProgram,boxTexture);
		boxes.push_back(box);
	}
}
void Game::Terminate()
{
	delete camera;
}

