#ifndef DELTA_TIME_H
#define DELTA_TIME_H

#define GLFW_INCLUDE_NONE
#include<glfw/glfw3.h>

 class DeltaTime
{
	public:
		 DeltaTime();
		 void Calculate();
		 double Time = 0;
	private:
		 double currentTime;
};

#endif
