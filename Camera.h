#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderProgram.h"
class Camera
{
	public:
		Camera(int width, int height, glm::vec3 position);
		void UpdateCamera(float FOVdeg, float nearPlane, float farPlane);
		void AssignMatrix(ShaderProgram& shader, const char* uniform);
		glm::vec3 Position;
		glm::mat4 ViewMatrix = glm::mat4(1.0f);
		glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
		int Width;
		int Height;

	private:
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif


