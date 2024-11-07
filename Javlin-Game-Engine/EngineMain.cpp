// include glad and GLFW
// include the EngineInfo.h file
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "EngineModules/EngineStructs.h"
#include "EngineModules/EngineInfo.h"
#include "EngineModules/ModelLoader.h"
#include "EngineModules/Textures.h"
#include "EngineModules/Shader.h"
#include "EngineModules/DeveloperWindow.cpp"
#include "ApplicationInfo.h"


// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EngineModules/Textures.h"

// get imgui
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"


vector<string> ConsoleLog;

int main()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW" << endl;
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	Jwindow = glfwCreateWindow(round(ApplicationWindowSize.x), round(ApplicationWindowSize.y), ApplicationName.c_str(), NULL, NULL);

	// make it fullscreen if the user wants it
	if (ApplicationFullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(Jwindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}

	if (!Jwindow)
	{
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(Jwindow);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Print Engine Info
	PrintEngineBasicInfo();




	// setup the imgui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(Jwindow, true);
	ImGui_ImplOpenGL3_Init("#version 460");


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ApplicationWindowSize.x / (float)ApplicationWindowSize.y, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model = glm::mat4(1.0f);




	// load a model
	Model myModel = LoadOBJ("Assets/Knife.obj");

	//  create a vao using the ModelLoader.h
	myModel = CreateVAO(myModel);
	
	// load a shader
	Shader myShader = LoadAndCompileShader("Assets/Shaders/Texture.vert", "Assets/Shaders/Texture.frag");

	glfwWindowHint(GLFW_SAMPLES, 16);
	glEnable(GL_MULTISAMPLE);// Enable anti-aliasing
	glEnable(GL_DEPTH_TEST);

	// load a texture
	Texture myTexture = LoadTexture("Assets/knife_01.png");

	// use the shader

	// set the projection, view and model (use set PVM)
	InitilizePVM(myShader, projection, view, model, false);

	// scale
	model = glm::scale(model, glm::vec3(5.1f, 5.1f, 5.1f));

	// apply the model matrix
	glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));




	// bind the texture
	UseTexture(myTexture, 0);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(Jwindow))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		model = glm::rotate(model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));


		// tell the shader to use the texture
		glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);

		// use the shader
		glUseProgram(myShader.ID);

		// use the texture
		UseTexture(myTexture, 0);
		// draw the model using the function from ModelLoader.h
		RenderModel(myModel);




		// draw imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/*
		
		ImGui::Begin("DBG window");
		// draw the texture
        ImGui::Image((ImTextureID)(intptr_t)myTexture.id, ImVec2(200, 200));
		ImGui::End();
		*/

		// console window
		ConsoleWindow(Jwindow);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// Swap front and back buffers
		glfwSwapBuffers(Jwindow);

		// Poll for and process events
		glfwPollEvents();




	}
}