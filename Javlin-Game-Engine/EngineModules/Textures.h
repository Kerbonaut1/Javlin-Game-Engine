#ifndef TEXTURES_H
#define TEXTURES_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineStructs.h"
// stbi implementation
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

Texture LoadTexture(string path)
{
	Texture texture;
	texture.TextureName = path;
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Texture format not supported" << endl;
		}
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);

	return texture;
}

// use the texture
void UseTexture(Texture texture, unsigned int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture.id);
}

// unbind the texture
void UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// delete the texture
void DeleteTexture(Texture texture)
{
	glDeleteTextures(1, &texture.id);
}

#endif // !TEXTURES_H

