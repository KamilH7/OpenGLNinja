#ifndef BOX_H
#define BOX_H
#include "Mesh.h"
#include <glm/gtc/random.hpp>

class Box
{
public:
	Box(Mesh firstHalf, Mesh secondHalf) :
		boxShaderProgram("default.vert", "default.frag"),
		boxTexture("Resources/box2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
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
	},
		ind(indices, indices + sizeof(indices) / sizeof(GLuint)),
		verts(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex)),
		verts2(vertices2, vertices2 + sizeof(vertices2) / sizeof(Vertex)),
		firstHalf(verts, ind, boxTexture),
		secondHalf(verts2, ind, boxTexture)
	{ 	
		RandomizeBox();
		firstHalf.Translate(startPosition);
		secondHalf.Translate(startPosition);
	};

	void Update(Camera* camera, double deltaTime);
	Mesh firstHalf;
	Mesh secondHalf;
	void Detach();
	void Destroy();
	bool CheckBounds();
private:
	std::vector <GLuint> ind;
	std::vector <Vertex> verts;
	std::vector <Vertex> verts2;

	bool detached = false;
	void RandomizeBox();
	void DrawBox(Camera* camera);

	glm::vec3 direction = glm::vec3(0,0,0);
	glm::vec3 startPosition = glm::vec3(4, -1, -4);
	
	float gravityPull = 0.8;
	float speed = 3;
	ShaderProgram boxShaderProgram;
	Texture boxTexture;
	Vertex vertices1[10];
	Vertex vertices2[10];
	GLuint indices[24];
};

#endif 
