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

	// Generates Shader object using shaders default.vert and default.frag
	shaderProgram = new ShaderProgram(vertexShaderPath, fragmentShaderPath);

	return true;
}

int main()
{
	if (!InitializeOpenGL()) 
	{
		TerminateOpenGL();
		return -1;
	}

	// Generates Vertex Array Object and binds it
	VAO VAO1;

	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	std::string texPath = "Resources/";

	// Texture
	Texture popCat((texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(*shaderProgram, "tex0", 0);

	// Tell OpenGL which Shader Program we want to use
	shaderProgram -> Activate();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram->ID, "scale");
	// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
	glUniform1f(uniID, 0.5f);

	// Main while loop
	while (Running())
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Binds texture so that is appears in rendering
		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram->Delete();

	TerminateOpenGL();
	return 0;
}