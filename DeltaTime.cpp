#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
	currentTime = glfwGetTime();
}

void DeltaTime::Calculate()
{
	Time = glfwGetTime() - currentTime;
	currentTime = glfwGetTime();
}
