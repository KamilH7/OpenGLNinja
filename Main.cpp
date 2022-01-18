#include "Main.h"

bool Running() 
{
	return !glfwWindowShouldClose(window);
}

void TerminateOpenGL() 
{
	if(window!=NULL)
		glfwDestroyWindow(window);

	glfwTerminate();
}

void SetupHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool InitializeOpenGL() 
{
	// Initialize GLFW
	glfwInit();

	// Give GLFW information about our environment 
	SetupHints();

	// Create a window object with desired parameters
	window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL); 

	// Handle an exception in which the window wasnt created
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}


	// Tell GLFW to use the newly created window
	glfwMakeContextCurrent(window);

	// Configure OpenGL using GLAD
	gladLoadGL();

	// Specify the ranging coordinates of the viewport of OpenGL
	glViewport(0, 0, windowWidth, windowHeight);

	return true;
}

int main()
{
	if (!InitializeOpenGL()) 
	{
		TerminateOpenGL();
		return -1;
	}

	DeltaTime deltaTime;
	Game game(window);
	game.Start(windowWidth,windowHeight,window);

	glEnable(GL_DEPTH_TEST);


	// Main while loop
	while (Running())
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime.Calculate();

		if (game.paused) 
		{
			game.PausedUpdate();
		}
		else 
		{
			game.Update(deltaTime.Time);
		}
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	game.Terminate();
	TerminateOpenGL();
	return 0;
}