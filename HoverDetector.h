#ifndef HOVER_DETECTOR_H
#define HOVER_DETECTOR

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include "Camera.h"
#include "Box.h"

class CollisionDetector
{
	public:
		void Update(Camera* camera, double mouseX, double mouseY);
		bool IsMouseHovering(Mesh* mesh);

	private:
		glm::vec3 rayDirection;
		glm::vec3 rayOrigin;
};

#endif


