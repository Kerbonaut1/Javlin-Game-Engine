#pragma once
#include <string>
using namespace std;

struct Vec2
{
	float x, y;
};
struct Vec3
{
	float x, y, z;
};
struct Vec4
{
	float x, y, z, w;
};

string Vec2toString(Vec2 MyVec)
{
	// returns a string representation of the Vec2
	return "(X: " + to_string(MyVec.x) + " Y: " + to_string(MyVec.y) + ")";
}
string Vec3toString(Vec3 MyVec)
{
	// returns a string representation of the Vec3
	return "(X: " + to_string(MyVec.x) + " Y: " + to_string(MyVec.y) + " Z: " + to_string(MyVec.z) + ")";
}
string Vec4toString(Vec4 MyVec)
{
	// returns a string representation of the Vec4
	return "(X: " + to_string(MyVec.x) + " Y: " + to_string(MyVec.y) + " Z: " + to_string(MyVec.z) + " W: " + to_string(MyVec.w) + ")";
}