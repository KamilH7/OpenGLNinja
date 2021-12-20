#include "Game.h"

void Game::Start()
{
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
	glm::vec3 rotationaxis(1.0f, 1.0f, 0.0f);

	meshes.at(0) -> Rotate(1 * deltaTime, rotationaxis);
	meshes.at(1)->Rotate(-1 * deltaTime, rotationaxis);

	for (Mesh* mesh : meshes)
		mesh->Draw(boxShaderProgram);
}

void Game::Terminate()
{
	boxShaderProgram.Delete();
	boxTexture.Delete();
}