#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& texture) : vertices(vertices), indices(indices), texture(texture)
{
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

void Mesh::Draw(ShaderProgram& shader, Camera* camera)
{
	shader.Activate();
	VAO.Bind();

	AssignMatrices(shader);
	camera -> AssignMatrix(shader, "camMatrix");

	texture.texUnit(shader, "tex0", 0);
	texture.Bind();

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	VAO.Unbind();
	texture.Unbind();

}

void Mesh::AssignMatrices(ShaderProgram& shaderProgram)
{
	//clear any rotation;
	glm::mat4 rotationMatrix(1.0f);
	glm::vec4 rotationVector(-1.0f, 0.0f, 0.0f, 0.0f);

	//rotate the rotation matrix
	rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//calculate facing direction
	glm::vec4 facingVector = rotationMatrix * rotationVector;
	Rotation = glm::vec3(facingVector.x, facingVector.y, facingVector.z);

	//translate the translation matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

	//sclale the scale matrix
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

	//calculate the model matrix
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	//update the model matrix uniform for the shader to use
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Mesh::SetTextue(Texture& texture)
{
	Mesh::texture = texture;
}

void Mesh::Rotate(glm::vec3 rotation)
{
	Mesh::rotation += rotation;
}

void Mesh::Translate(glm::vec3 position)
{
	Mesh::Position += position;
}

void Mesh::ChangeScale(glm::vec3 scale)
{
	Mesh::Scale = scale;
}