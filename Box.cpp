#include "Box.h"


 void Box::Update(Camera* camera, double deltaTime)
{
	 direction.y -= gravityPull * deltaTime * speed;

	 if (detached) 
	 {
		 firstHalf->Translate(direction * (float)deltaTime * speed);
		 secondHalf->Translate(glm::vec3(-direction.x,direction.y,-direction.z) * (float)deltaTime * speed);
	 }
	 else
	 {
		 firstHalf->Translate(direction * (float)deltaTime * speed);
		 secondHalf->Translate(direction * (float)deltaTime * speed);
	 }

	 DrawBox(camera);
}

 void Box::DrawBox(Camera * camera)
 {
	 firstHalf->Draw(boxShaderProgram, camera);
	 secondHalf->Draw(boxShaderProgram, camera);
 }

 void Box::Detach()
 {
	 detached = true;
 }

 bool Box::CheckBounds() 
 {
	 if (firstHalf->Position.y < -4 || secondHalf->Position.y < -4)
	 {
		 return true;
	 }

	 return false;
 }
 void Box::RandomizeBox()
 {
	 startPosition = glm::vec3(4, -1, -4);
	 startPosition.y = glm::linearRand(-1, 0);
	 firstHalf->Translate(startPosition);
	 secondHalf->Translate(startPosition);
	 direction = glm::vec3(-1, 2, 0);
	 direction.x = glm::linearRand(-3, -2);
	 direction.y = glm::linearRand(1, 3);
	 speed = glm::linearRand(2, 4);
 }
 void Box::Destroy() 
 {
	 boxShaderProgram.Delete();
	 boxTexture.Delete();
 }