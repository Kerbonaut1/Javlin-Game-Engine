#ifndef DEVELOPERWINDOW_H
#define DEVELOPERWINDOW_H
#include <string>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include "EngineStructs.h"
#include "EngineInfo.h"
#include "Shader.h"
#include "../ApplicationInfo.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
using namespace std;

vector<string> Log;

void ConsoleWindow(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // a new imgui window that is attached to the top of the screen and is 100% of the width
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, 200));
    ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
    // set font size
    ImGui::SetWindowFontScale(1.5);
    ImGui::Text("Console Window");
    ImGui::SetWindowFontScale(1);

	// text input
	static char input[256] = "";
	ImGui::InputText("Command", input, IM_ARRAYSIZE(input));
	if (ImGui::Button("Submit"))
	{
		// submit the command (turn the input into a string)
		Log.push_back("> " + std::string(input));
	}
	

    ImGui::Text(("Log (" + std::to_string(Log.size()) + ") :").c_str());
	ImGui::Separator();

	// for each error log message
	for (int i = 0; i < Log.size(); i++)
	{
		ImGui::Text(Log[i].c_str());
	}

    ImGui::End();
}




#endif // !DEVELOPERWINDOW_H