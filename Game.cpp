#include "Game.h"

void Game::Start(double width, double height, GLFWwindow* window)
{
	std::vector <GLuint> ind(bgInds, bgInds + sizeof(bgInds) / sizeof(GLuint));
	std::vector <Vertex> verts(bgVerts, bgVerts + sizeof(bgVerts) / sizeof(Vertex));
	backgroundImage = new Mesh(verts, ind, bgTexture);
	backgroundImage -> ChangeScale(glm::vec3(6, 6, 1));
	camera = new Camera(width, height, glm::vec3(0.0f, 0.5f, 5.0f));
	Box* box = new Box();
	boxes.push_back(box);
}

void Game::PausedUpdate() 
{
	backgroundImage->Draw(bgShaderProgram, camera);

	int state = glfwGetKey(window, GLFW_KEY_P);

	if (state == GLFW_PRESS)
	{
		paused = false;
	}
}

void Game::Update(double deltaTime)
{
	backgroundImage->Draw(bgShaderProgram,camera);

	boxSpawnTimer -= (float)deltaTime;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	collisionDetector.Update(camera, xpos, ypos);

	camera->UpdateMatrix(45.0f,0.1f,200.0f);

	SpawnBoxes();

	for (int i = 0; i< boxes.size(); i++) 
	{
		boxes[i]->Update(camera, deltaTime);
		collisionDetector.HandleMouseCollision(boxes[i]);

		if (boxes[i]->detached) 
		{
			AddPoint(boxes[i]);

			if (boxes[i]->ScaledToZero()) 
			{
				delete boxes[i];
				boxes.erase(boxes.begin() + i);
				i--;
			}
		}
		else 
		{
			if (boxes[i]->UnderBounds())
			{
				RemoveLife();
				delete boxes[i];
				boxes.erase(boxes.begin() + i);
				i--;
			}
		}
	}

	currentBoxSpawnTimer = glm::pow(1.1f, difficulty) - 0.1f;

	difficulty -= deltaTime/15;
}

void Game::SpawnBoxes()
{
	if (boxSpawnTimer <= 0) 
	{
		boxSpawnTimer = currentBoxSpawnTimer;
		Box* box = new Box();
		boxes.push_back(box);

	}
}

void Game::AddPoint(Box* box) 
{
	if (box -> pointAdded) 
	{
		return;
	}

	points += 1;
	box -> pointAdded = true;
}

void Game::RemoveLife()
{
	lives -= 1;

	if (lives == 0) 
	{
		Restart();
	}
}

void Game::Restart() 
{
	points = 0;
	lives = 3;
	difficulty = 1;
	boxSpawnTimer = 1;
	currentBoxSpawnTimer = 1;

	//clear boxes
	for (int i = 0; i < boxes.size(); i++)
	{
		delete boxes[i];
		boxes.erase(boxes.begin() + i);
	}

	paused = true;
}

void Game::Terminate()
{
	delete camera;
}

