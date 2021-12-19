#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "ShaderProgram.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& texture);
	void Draw(ShaderProgram& shader);
	void Rotate(float rotation, glm::vec3& axis);
	void SetRotation(float rotation, glm::vec3& axis);

private:
	VAO VAO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Texture texture;

	glm::mat4 m;
	glm::mat4 v;
	glm::mat4 p;
	glm::mat4& modelMatrix = m;
	glm::mat4& viewMatrix = v;
	glm::mat4& projectionMatrix = p;

	float currentRotation = 0.0f;

	void SetupMatrices();
	void AssignMatrices(ShaderProgram& shaderProgram);
};
#endif
