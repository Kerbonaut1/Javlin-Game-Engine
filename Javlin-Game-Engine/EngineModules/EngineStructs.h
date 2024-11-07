#ifndef ENGINESTRUCTS_H
#define ENGINESTRUCTS_H

#include <string>
#include <vector>
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

struct Vertex
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 TexCoords;
};

struct Texture
{
	string TextureName;
	unsigned int id;
	string type;
	string path;
};

struct Model
{
	string ModelName;
	unsigned int VAO;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
};

// shader
struct Shader
{
	string ShaderName;
	unsigned int ID;
};

#endif // ENGINESTRUCTS_H