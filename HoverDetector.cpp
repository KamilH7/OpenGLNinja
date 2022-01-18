#include "HoverDetector.h"

//function that transforms mouse position into world coordinates and calculates a ray origin and direction that the mouse would produce.
void CollisionDetector::Update(Camera* camera, double mouseX, double mouseY)
{
	int screenWidth = camera->Width;
	int screenHeight = camera->Height;
	glm::mat4 viewMatrix = camera -> ViewMatrix;
	glm::mat4 projectionMatrix = camera ->ProjectionMatrix;

	//normalized device coordinates
	float x = (2.0f * mouseX) / (float) screenWidth - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / (float) screenHeight;
	float z = -1.0f;

	//calculate clip coords
	glm::vec4 clipCoords(x,y,z,1.0f);

	//calculate inverted projection matrix
	glm::mat4 invertedProjectionMatrix = glm::inverse(projectionMatrix);

	//calculate eye coordinates
	glm::vec4 eyeCoords = invertedProjectionMatrix * clipCoords;
	eyeCoords.z = -1;
	eyeCoords.w = 0;

	//calculate inverted view matrix
	glm::mat4 invertedViewMatrix = glm::inverse(viewMatrix);

	//calculate world coordinates
	glm::vec4 worldCoords = invertedViewMatrix * eyeCoords;

	//assign the direction of the ray
	rayDirection = glm::vec3(worldCoords.x,worldCoords.y,worldCoords.z);
	rayDirection = glm::normalize(rayDirection);

	//assign the position of the ray
	glm::vec4 cameraPosition(camera->Position.x, camera->Position.y, camera->Position.z,0);
	rayOrigin = cameraPosition;
}

//function returns true if a mesh is colliding with the mouse ray
bool CollisionDetector::IsMouseHovering(Mesh* mesh)
{
	//ray intersection with an abstract sphere check

	float sphereRadius = 1;
	glm::vec3 sphereCenter = mesh -> Position;
	float pd = glm::dot(sphereCenter - rayOrigin, rayDirection);
	glm::vec3 p = rayOrigin + rayDirection * pd;
	float distance = glm::length(glm::abs(sphereCenter - p));

	if (distance < sphereRadius)
	{
		return true;
	}

	return false;
}