#ifndef BOX_H
#define BOX_H
#include "Mesh.h"
#include <glm/gtc/random.hpp>

class Box
{
public:
	Mesh* firstHalf;
	Mesh* secondHalf;
	bool isBroken = false;
	bool pointAdded = false;
	Box(Texture texture) :
		meshShaderProgram("default.vert", "default.frag"),
		vertices1
	{
		Vertex{ glm::vec3(-0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //0
		Vertex{ glm::vec3(-0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //1 
		Vertex{ glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //2
		Vertex{ glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //3
		Vertex{ glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //4
		Vertex{ glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //5
		Vertex{ glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f) }, //6
		Vertex{ glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f) }, //7
		Vertex{ glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f) }, //8
		Vertex{ glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }, //9		
	},
	vertices2
	{
		Vertex{glm::vec3(0.5f, 1.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
		Vertex{glm::vec3(0.5f, 1.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
		Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
		Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9
	},
	indices
	{
		0,1,2,2,1,3,
		2,3,4,4,2,5,
		0,1,6,6,0,7,
		1,8,3,
		9,2,0
	}	
	{
		std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
		std::vector <Vertex> verts(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex));
		std::vector <Vertex> verts2(vertices2, vertices2 + sizeof(vertices2) / sizeof(Vertex));
		
		firstHalf = new Mesh(verts, ind, texture);
		secondHalf = new Mesh(verts2, ind, texture);

		RandomizeBox();
	};

	~Box()
	{
		delete firstHalf;
		delete secondHalf;
		meshShaderProgram.Delete();
	}

	void Update(Camera* camera, double deltaTime);
	void Break();
	bool UnderBounds();
	bool IsInvisible();
private:

	//settings
	glm::vec3 currentScale = glm::vec3(1, 1, 1);
	glm::vec3 moveDirection = glm::vec3(0, 0, 0);
	glm::vec3 rotationDirection = glm::vec3(0, 0, 0);
	glm::vec3 startPosition = glm::vec3(0, 0, 0);
	float gravityPull = 0.8;
	float speed = 3;

	//spawning
	void RandomizeBox();
	void SpawnLeft();
	void SpawnRight();
	void SpawnDown();
	void SpawnUp();

	Texture GetRandomTexture();
	void DrawBox(Camera* camera);
	ShaderProgram meshShaderProgram;
	Vertex vertices1[10];
	Vertex vertices2[10];
	GLuint indices[24];
};

#endif 
