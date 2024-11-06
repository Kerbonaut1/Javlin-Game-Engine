#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
// using the engine struct and use tiny obj loader to load the model
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "EngineStructs.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


Model LoadOBJ(string path)
{
	Model model;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str()))
	{
		throw runtime_error(warn + err);
	}

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			Vertex vertex;
			vertex.Position = { attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2] };
			vertex.Normal = { attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1], attrib.normals[3 * index.normal_index + 2] };
			vertex.TexCoords = { attrib.texcoords[2 * index.texcoord_index + 0], 1.0f - attrib.texcoords[2 * index.texcoord_index + 1] };
			vertices.push_back(vertex);
			indices.push_back(indices.size());
		}
	}

	model.vertices = vertices;
	model.indices = indices;
	model.textures = textures;

	return model;
}

#endif // !MODEL_LOADER_H

