#include "HoverDetector.h"

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

	rayDirection = glm::vec3(worldCoords.x,worldCoords.y,worldCoords.z);
	rayDirection = glm::normalize(rayDirection);

	glm::vec4 cameraPosition(camera->Position.x, camera->Position.y, camera->Position.z,0);
	rayOrigin = cameraPosition;
}

void CollisionDetector::HandleMouseCollision(Box* box)
{
	glm::vec3 sphereCenter = box->firstHalf->Position;
	float sphereRadius = 1;
	float pd = glm::dot(sphereCenter - rayOrigin, rayDirection);
	glm::vec3 p = rayOrigin + rayDirection * pd;

	float distance = glm::length(glm::abs(sphereCenter - p));

	if (distance < sphereRadius) 
	{
		box -> Detach();
	}

}