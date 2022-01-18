#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) 
{
	Camera::Width = width;
	Camera::Height = height;
	Camera::Position = position;
}

//function that sends the data to the projection matrix
void Camera::UpdateCamera(float FOVdeg, float nearPlane, float farPlane)
{
	//initializes matrices since otherwise they will be the null matrix
	ViewMatrix = glm::mat4(1.0f);
	ProjectionMatrix = glm::mat4(1.0f);
	//makes camera look in the right direction from the right position
	ViewMatrix = glm::lookAt(Position, Position + Orientation, Up);
	//adds perspective to the scene
	ProjectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)Width / Height, nearPlane, farPlane);
}

//function that sends the matrix data to the designated shader
void Camera::AssignMatrix(ShaderProgram& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix));
}