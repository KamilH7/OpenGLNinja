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
	Vertex vertices1[] =
	{
		Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //0
		Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //1 
		Vertex{glm::vec3(-0.5f, 1.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //2
		Vertex{glm::vec3(-0.5f, 1.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //3
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //4
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),    glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //5

		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)}, //6
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)}, //7

		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)}, //8
		Vertex{glm::vec3(0.5f, 0.0f,  0.5f),     glm::vec3(0.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)}, //9
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		 0,1,2,2,1,3,
		 2,3,4,4,2,5,
		 0,1,6,6,0,7,
		 1,8,3,
		 9,2,0
	};

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
		game.Update(deltaTime.Time);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	game.Terminate();
	TerminateOpenGL();
	return 0;
}