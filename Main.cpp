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

	// Texture
	Texture boxTexture("Resources/box2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));

	// Generates Shader object using shaders default.vert and default.frag
	ShaderProgram shaderProgram(vertexShaderPath, fragmentShaderPath);
	std::vector <Vertex> verts(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex));
	Mesh mesh(verts, ind, boxTexture);
	
	// Generates Shader object using shaders default.vert and default.frag
	ShaderProgram shaderProgram2(vertexShaderPath, fragmentShaderPath);
	std::vector <Vertex> verts2(vertices2, vertices2 + sizeof(vertices2) / sizeof(Vertex));
	Mesh mesh2(verts2, ind, boxTexture);

	glEnable(GL_DEPTH_TEST);

	DeltaTime deltaTime;

	// Main while loop
	while (Running())
	{
		deltaTime.Calculate();
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::vec3 rotationaxis(0.0f,1.0f,0.0f);

		mesh.Rotate(360*deltaTime.Time, rotationaxis);
		mesh.Draw(shaderProgram);
		mesh2.Draw(shaderProgram2);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	boxTexture.Delete();
	shaderProgram.Delete();

	TerminateOpenGL();
	return 0;
}