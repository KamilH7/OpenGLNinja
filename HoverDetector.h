#ifndef HOVER_DETECTOR_H
#define HOVER_DETECTOR

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Camera.h"

class HoverDetector
{
	public:
		void Update(Camera* camera, double mouseX, double mouseY);
		glm::vec3 rayDirection;
		glm::vec3 rayOrigin;
};

#endif


