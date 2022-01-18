#include "Game.h"

//runs only at the start of the program
void Game::Start(double width, double height, GLFWwindow* window)
{
	SetupCamera(width,height);
	SetupBackground();
	SetupButton();
	SetupLifeIcons();
	Pause();
}

//Update that is called every frame when the game is paused
void Game::PausedUpdate() 
{
	UpdateCamera();
	UpdateHoverDetector();
	DrawBackground();
	DrawButton();

	if (hoverDetector.IsMouseHovering(buttonMesh)) 
	{
		if (IsMouseButtonClicked()) 
		{
			Unpause();
		}
	}
}

//Update that is called every frame when the game is running
void Game::Update(double deltaTime)
{
	UpdateCamera();
	UpdateHoverDetector();
	DrawBackground();
	DrawLifeIcons();
	SpawnBoxes();
	UpdateBoxes(deltaTime);
	IncreaseDifficulty(deltaTime);
}

//function that resets the camera matrix
void Game::UpdateCamera()
{
	camera->UpdateCamera(45.0f, 0.1f, 200.0f);
}

//function that inceases the difficulty of the game over time
void Game::IncreaseDifficulty(float deltaTime) 
{
	boxSpawnTimer -= (float)deltaTime;
	currentBoxSpawnTimer = glm::pow(1.1f, difficulty) - 0.1f;
	difficulty -= deltaTime / 15;
}

//function that updates and handles the destruction on the boxes
void Game::UpdateBoxes(float deltaTime) 
{
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->Update(camera, deltaTime);

		if (hoverDetector.IsMouseHovering(boxes[i]->firstHalf))
		{
			boxes[i]->Break();
		}

		if (boxes[i]->isBroken)
		{
			AddPoint(boxes[i]);

			if (boxes[i]->IsInvisible())
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
				DecreaseLives();
				delete boxes[i];
				boxes.erase(boxes.begin() + i);
				i--;
			}
		}
	}
}

//function that creates the camera object
void Game::SetupCamera(double width, double height)
{
	camera = new Camera(width, height, glm::vec3(0.0f, 0.5f, 5.0f));
}

//funtion that generates and positions the background
void Game::SetupBackground()
{
	std::vector <GLuint> inds(bgInds, bgInds + sizeof(bgInds) / sizeof(GLuint));
	std::vector <Vertex> verts(bgVerts, bgVerts + sizeof(bgVerts) / sizeof(Vertex));
	backgroundMesh = new Mesh(verts, inds, gameBgTexture);
	backgroundMesh->Translate(glm::vec3(0, 0.4, 0));
	backgroundMesh->ChangeScale(glm::vec3(5, 5, 1));
}

//funtion that generates and positions the start button
void Game::SetupButton()
{
	std::vector <GLuint> inds(buttonInds, buttonInds + sizeof(buttonInds) / sizeof(GLuint));
	std::vector <Vertex> verts(buttonVerts, buttonVerts + sizeof(buttonVerts) / sizeof(Vertex));
	buttonMesh = new Mesh(verts, inds, buttonTexture);
	buttonMesh->Translate(glm::vec3(0,-2.5,-5.5));
}

//funtion that generates and positions the life icons
void Game::SetupLifeIcons()
{
	std::vector <GLuint> inds(lifeInds, lifeInds + sizeof(lifeInds) / sizeof(GLuint));
	std::vector <Vertex> verts(lifeVerts, lifeVerts + sizeof(lifeVerts) / sizeof(Vertex));

	lifeMeshes[0] = new Mesh(verts, inds, lifeTexture);
	lifeMeshes[0]->Translate(glm::vec3(-2, 3, -3));
	lifeMeshes[0]->ChangeScale(glm::vec3(0.5,0.5,0.5));
	lifeMeshes[1] = new Mesh(verts, inds, lifeTexture);
	lifeMeshes[1]->Translate(glm::vec3(0, 3, -3));
	lifeMeshes[1]->ChangeScale(glm::vec3(0.5, 0.5, 0.5));
	lifeMeshes[2] = new Mesh(verts, inds, lifeTexture);
	lifeMeshes[2]->Translate(glm::vec3(2, 3, -3));
	lifeMeshes[2]->ChangeScale(glm::vec3(0.5, 0.5, 0.5));
}

//function that draws the life icons
void Game::DrawLifeIcons()
{
	for (int i = 0; i < lives; i++) 
	{
		lifeMeshes[i]->Draw(UIShaderProgram, camera);
	}
}

//function that draws the background
void Game::DrawBackground()
{
	backgroundMesh->Draw(UIShaderProgram, camera);
}

//function that draws the play button
void Game::DrawButton()
{
	if (hoverDetector.IsMouseHovering(buttonMesh))
	{
		buttonMesh->SetTextue(buttonHoverTexture);
	}
	else
	{
		buttonMesh->SetTextue(buttonTexture);
	}

	buttonMesh->Draw(UIShaderProgram, camera);
}

//function that spawns the boxes
void Game::SpawnBoxes()
{
	if (boxSpawnTimer <= 0) 
	{
		boxSpawnTimer = currentBoxSpawnTimer;
		Box* box = new Box(GetRandomBoxTexture());
		boxes.push_back(box);
	}
}

//function that returns a random box texture
Texture Game::GetRandomBoxTexture()
{
	return boxTextures[glm::linearRand(0, 2)];
}

//function that adds a point
void Game::AddPoint(Box* box) 
{
	if (box -> pointAdded) 
	{
		return;
	}

	points += 1;
	box -> pointAdded = true;
}

//function that decreases lives
void Game::DecreaseLives()
{
	lives -= 1;

	if (lives == 0) 
	{
		Pause();
	}
}

//function that checks whether the left mouse button is clicked
bool Game::IsMouseButtonClicked() 
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}

//function that updates the hoverDetector class
void Game::UpdateHoverDetector() 
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	hoverDetector.Update(camera, xpos, ypos);
}

//funcion that pauses the game
void Game::Pause() 
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

	backgroundMesh->SetTextue(menuBgTexture);
	paused = true;
}

//function that unpauses the game;
void Game::Unpause() 
{
	paused = false;
	backgroundMesh->SetTextue(gameBgTexture);
}

