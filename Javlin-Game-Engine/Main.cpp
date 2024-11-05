// include glad and GLFW
// include the EngineInfo.h file
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "EngineModules/EngineStructs.h"
#include "EngineModules/EngineInfo.h"

#include <assimp/Importer.hpp>

using namespace std;
int main()
{

	// Initialize GLFW
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW" << endl;
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Javlin Game Engine", NULL, NULL);

	if (!window)
	{
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Print Engine Info
	PrintEngineBasicInfo();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}
}