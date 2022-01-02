#include "Game.h"

void Game::Start(double width, double height, GLFWwindow* window)
{
	camera = new Camera(width, height, glm::vec3(0.0f, 0.5f, 5.0f));
	Box* box = new Box();
	boxes.push_back(box);
}

void Game::Update(double deltaTime)
{
	timer -= (float)deltaTime;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	collisionDetector.Update(camera, xpos, ypos);

	camera->UpdateMatrix(45.0f,0.1f,200.0f);
	SpawnBoxes();

	for (int i = 0; i< boxes.size(); i++) 
	{
		boxes[i]->Update(camera, deltaTime);
		collisionDetector.IsColliding(boxes[i]);

		if (boxes[i]->CheckBounds()) 
		{
			boxes[i]->Destroy();
			delete boxes[i];
			//remove box from a vector
			boxes.erase(boxes.begin()+i);
			i--;
		}
	}
}

void Game::SpawnBoxes()
{
	if (timer <= 0) 
	{
		timer = currentTimer;
		Box* box = new Box();
		boxes.push_back(box);
	}
}
void Game::Terminate()
{
	delete camera;
}

