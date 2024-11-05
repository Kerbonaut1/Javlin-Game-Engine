// include glad and GLFW
// include the EngineInfo.h file
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "EngineModules/EngineStructs.h"
#include "EngineModules/EngineInfo.h"
#include "EngineModules/ModelLoader.h"
#include "ApplicationInfo.h"

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
	GLFWwindow* window = glfwCreateWindow(round(ApplicationWindowSize.x), round(ApplicationWindowSize.y), ApplicationName.c_str(), NULL, NULL);

	// make it fullscreen if the user wants it
	if (ApplicationFullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}

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

	// load a model
	Model myModel = LoadObj("Assets/Ico.obj");

	// print the model vertices
	for (int i = 0; i < myModel.vertices.size(); i++)
	{
		cout << "Vertex " << i << " Position: " << myModel.vertices[i].Position.x << " " << myModel.vertices[i].Position.y << " " << myModel.vertices[i].Position.z << endl;
		cout << "Vertex " << i << " Normal: " << myModel.vertices[i].Normal.x << " " << myModel.vertices[i].Normal.y << " " << myModel.vertices[i].Normal.z << endl;
		cout << "Vertex " << i << " TexCoords: " << myModel.vertices[i].TexCoords.x << " " << myModel.vertices[i].TexCoords.y << endl;
	}

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