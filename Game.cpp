#include "Game.h"

void Game::Start(double width, double height, GLFWwindow* window)
{
	camera = new Camera(width, height, glm::vec3(0.0f, 0.5f, 5.0f));

	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));

	std::vector <Vertex> verts(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex));
	Mesh* mesh = new Mesh(verts, ind, boxTexture);
	meshes.push_back(mesh);

	std::vector <Vertex> verts2(vertices2, vertices2 + sizeof(vertices2) / sizeof(Vertex));
	Mesh* mesh2 = new Mesh(verts2, ind, boxTexture);
	meshes.push_back(mesh2);

}

void Game::Update(double deltaTime)
{
	camera->UpdateMatrix(45.0f,0.1f,200.0f);

	HandleInput();

	glm::vec3 rotationaxis(0.0f, 0.0f, 1.0f);

	meshes.at(0) -> Translate(glm::vec3(1 * deltaTime,0,0));
	meshes.at(1) -> Translate(glm::vec3(1 * deltaTime,0,0));
	//meshes.at(0) -> Rotate( rotationaxis, -1 * deltaTime);
	//meshes.at(1) -> Rotate( rotationaxis, -1 * deltaTime);


	for (Mesh* mesh : meshes)
		mesh->Draw(boxShaderProgram, camera);
}

void Game::HandleInput()
{
	camera->Inputs(window);

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	hoverDetector.Update(camera, xpos, ypos);

	if (state == GLFW_PRESS)
	{
		//MouseButtonClicked(xpos, ypos);
	}
}

void Game::Terminate()
{
	boxShaderProgram.Delete();
	boxTexture.Delete();
	delete camera;
}

void Game::MouseButtonClicked(double xPos, double yPos) 
{
	std::cout<<"("<< xPos<<","<<yPos<<")"<<endl;
}