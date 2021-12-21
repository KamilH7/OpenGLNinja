#ifndef MESH_H
#define MESH_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& texture);
	void Draw(ShaderProgram& shader, Camera* camera);
	void Rotate(glm::vec3 rotationAxis, float angle);
	void Translate(glm::vec3 translation);
	void Scale(glm::vec3 scale);

private:
	VAO VAO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Texture texture;

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	void AssignMatrices(ShaderProgram& shaderProgram);
};
#endif
