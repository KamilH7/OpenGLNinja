#ifndef VERTEX_H
#define VERTEX_H

#include<glm/glm.hpp>

// This structure holds all of the vertex information
struct Vertex
{
	glm::vec3 postion;
	glm::vec3 color;
	glm::vec2 textureCoordinates;
};

#endif