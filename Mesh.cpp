#include "Mesh.h"

void Mesh::SetupMatrices()
{
	// Move the world away from the camera
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -0.5f, -3.0f));
	// Setup the projection matrix using perspective(fov,aspectRatio, nearPlaneDistance, farPlaneDistance)
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 400.0f);
}

void Mesh::AssignMatrices(ShaderProgram& shaderProgram)
{
	// Get shader mattix uniform locations 
	int modelMatrixLocation = glGetUniformLocation(shaderProgram.ID, "modelMatrix");
	int viewMatrixLocation = glGetUniformLocation(shaderProgram.ID, "viewMatrix");
	int projectionMatrixLocation = glGetUniformLocation(shaderProgram.ID, "projectionMatrix");

	// Assign the pointer to the matrices to the uniforms
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
}

void Mesh::SetRotation(float rotation, glm::vec3& axis)
{
	currentRotation = rotation;
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRotation), axis);
}

void Mesh::Rotate(float rotation, glm::vec3& axis)
{
	currentRotation += rotation;
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRotation), axis);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& texture) : vertices(vertices), indices(indices), texture(texture), m(1.0f), v(1.0f), p(1.0f)
{
	SetupMatrices();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);

	VAO.Bind();
	EBO.Bind();
	VBO.Bind();

	// Links VBO attributes such as coordinates and colors to VAO
	//position
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	//colors
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//tex coords
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VBO.Unbind();
	VAO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(ShaderProgram& shader)
{
	shader.Activate();
	VAO.Bind();
	AssignMatrices(shader);

	texture.texUnit(shader, "tex0", 0);
	texture.Bind();

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}