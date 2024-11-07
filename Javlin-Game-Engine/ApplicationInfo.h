#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H
#include <string>
#include "EngineModules/EngineStructs.h"
using namespace std;

string ApplicationName = "Javlin Game Engine";
Vec3 ApplicationVersion = { 1.0f, 0.0f, 0.0f };
Vec2 ApplicationWindowSize = { 1000, 1000 }; // Starting window size
bool ApplicationFullscreen = false; // Starting window mode

// changing the name WILL break stuff
GLFWwindow* Jwindow;


#endif // !APPLICATIONINFO_H
