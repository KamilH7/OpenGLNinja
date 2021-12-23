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

	for (Mesh* mesh : meshes)
		mesh->Draw(boxShaderProgram, camera);
}

void Game::HandleInput()
{
	camera->Inputs(window);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	hoverDetector.Update(camera, xpos, ypos);

	int zero = glfwGetKey(window, GLFW_KEY_0);
	if (zero == GLFW_PRESS)
	{
		glm::vec3 rotationaxis(1.0f, 0.0f, 0.0f);
		meshes.at(0)->Rotate(rotationaxis * 0.01f);
	}

	int one = glfwGetKey(window, GLFW_KEY_1);
	if (one == GLFW_PRESS)
	{
		glm::vec3 rotationaxis(0.0f, 1.0f, 0.0f);
		meshes.at(0)->Rotate(rotationaxis * 0.01f);
	}

	int two = glfwGetKey(window, GLFW_KEY_2);
	if (two == GLFW_PRESS)
	{
		glm::vec3 rotationaxis(0.0f, 0.0f, 1.0f);
		meshes.at(0)->Rotate(rotationaxis * 0.01f);
	}

	int three = glfwGetKey(window, GLFW_KEY_3);
	if (three == GLFW_PRESS)
	{
		meshes.at(0)->Translate(glm::vec3(0, 1 * 0.01f, 0));
	}

	int four = glfwGetKey(window, GLFW_KEY_4);
	if (four == GLFW_PRESS)
	{
		meshes.at(0)->Translate(glm::vec3(1 * 0.01f, 0, 0));
	}

	int five = glfwGetKey(window, GLFW_KEY_5);
	if (five == GLFW_PRESS)
	{
		meshes.at(0)->Translate(glm::vec3(0, 0, 1 * 0.01f));
	}
}

void Game::Terminate()
{
	boxShaderProgram.Delete();
	boxTexture.Delete();
	delete camera;
}