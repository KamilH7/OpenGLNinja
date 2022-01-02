#include "Box.h"


 void Box::Update(Camera* camera, double deltaTime)
{
	 moveDirection.y -= gravityPull * deltaTime;

	 firstHalf->Rotate(rotationDirection * (float) deltaTime);
	 secondHalf->Rotate(rotationDirection * (float) deltaTime);

	 if (detached) 
	 {
		 firstHalf->Translate(moveDirection * (float)deltaTime * speed);
		 secondHalf->Translate(moveDirection * (float)deltaTime * speed);
	 }
	 else
	 {
		 firstHalf->Translate(moveDirection * (float)deltaTime * speed);
		 secondHalf->Translate(moveDirection * (float)deltaTime * speed);
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
	 moveDirection = firstHalf->Direction;
 }

 bool Box::CheckBounds()
 {
	 if (firstHalf->Position.y < -6 || secondHalf->Position.y < -6)
	 {
		 return true;
	 }

	 return false;
 }
 void Box::RandomizeBox()
 {
	 rotationDirection.x = glm::linearRand(-1.0f, 1.0f);
	 rotationDirection.y = glm::linearRand(-1.0f, 1.0f);
	 rotationDirection.z = glm::linearRand(-1.0f, 1.0f);

	 speed = glm::linearRand(5, 7);

	 switch(glm::linearRand(0, 3)) 
	 {
		 case(0):SpawnRight(); break;
		 case(1):SpawnLeft(); break;
		 case(2):SpawnDown(); break;
		 case(3):SpawnUp(); break;
	 }

	 firstHalf->Translate(startPosition);
	 secondHalf->Translate(startPosition);
 }

 void Box::SpawnRight() 
 {
	 std::cout << "Spawning Right"<<endl;
	 startPosition = glm::vec3(4, -1, -4);
	 startPosition.y = glm::linearRand(-1.0f, 2.7f);

	 moveDirection.x = -1;
	 moveDirection.y = -1*glm::log(startPosition.y+2)+1.4;
 }

 void Box::SpawnLeft() 
 {
	 std::cout << "Spawning Left" << endl;
	 startPosition = glm::vec3(-4, -1, -4);
	 startPosition.y = glm::linearRand(-1.0f, 2.7f);

	 moveDirection.x = 1;
	 moveDirection.y = -1 * glm::log(startPosition.y + 2) + 1.4;
 }

 void Box::SpawnDown() 
 {
	 std::cout << "Spawning Down" << endl;
	 startPosition = glm::vec3(-4, -1, -4);
	 startPosition.x = glm::linearRand(-4.0f, 4.0f);
	 startPosition.y = -3.0f;

	 moveDirection.x = -glm::sin((0.333f) * startPosition.x);
	 moveDirection.y = 1.6;
 }

 void Box::SpawnUp() 
 {
	 std::cout << "Spawning Up" << endl;
	 startPosition = glm::vec3(-4, -1, -4);
	 startPosition.x = glm::linearRand(-4.0f, 4.0f);
	 startPosition.y = 3.0f;

	 moveDirection.x = -glm::sin((0.333f) * startPosition.x);
	 moveDirection.y = 0;
 }

 void Box::Destroy() 
 {
	 boxShaderProgram.Delete();
	 boxTexture.Delete();
 }