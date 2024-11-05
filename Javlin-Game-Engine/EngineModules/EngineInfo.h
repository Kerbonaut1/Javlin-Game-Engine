#pragma once
#include <string>
#include <iostream>
#include "EngineStructs.h"
using namespace std;


// General Information about the Engine Distro

string Engine_DistroName = "Javlin Game Engine";
string Engine_DistroAuthor = "Kerbonaut";
string Engine_DistroDescription = "A game engine designed to be extendable and modifiyable";
Vec3 Engine_DistroVersion = { 1.0f, 0.0f, 0.0f };


// Function to print the Engine Info
void PrintEngineBasicInfo()
{
	cout << "Engine Author: " << Engine_DistroAuthor << endl;
	cout << "Engine Name: " << Engine_DistroName << endl;
	cout << "Engine Version: " << Engine_DistroVersion.x << "." << Engine_DistroVersion.y << "." << Engine_DistroVersion.z << endl;
	cout << "Engine Description: " << Engine_DistroDescription << endl;
}