#ifndef SHADERS_H
#define SHADERS_H

// Include the necessary libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineStructs.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

// Shader class
Shader LoadAndCompileShader(string vertexPath, string fragmentPath)
{
	// Create a shader object
	Shader shader;
	shader.ShaderName = vertexPath + " " + fragmentPath;
	const char* vertexCode;
	const char* fragmentCode;
	string vertexCodeString;
	string fragmentCodeString;
	ifstream vShaderFile;
	ifstream fShaderFile;

	// Read the vertex shader file
	vShaderFile.open(vertexPath);
	stringstream vShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	vShaderFile.close();
	vertexCodeString = vShaderStream.str();
	vertexCode = vertexCodeString.c_str();

	// Read the fragment shader file
	fShaderFile.open(fragmentPath);
	stringstream fShaderStream;
	fShaderStream << fShaderFile.rdbuf();
	fShaderFile.close();
	fragmentCodeString = fShaderStream.str();
	fragmentCode = fragmentCodeString.c_str();

	// Compile the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Shader Program
	shader.ID = glCreateProgram();
	glAttachShader(shader.ID, vertex);
	glAttachShader(shader.ID, fragment);
	glLinkProgram(shader.ID);
	glGetProgramiv(shader.ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader.ID, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// Delete the shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return shader;
}

// Use the shader
void UseShader(Shader shader)
{
	glUseProgram(shader.ID);
}

// Deselect the shader
void DeselectShader()
{
	glUseProgram(0);
}

// Set the uniform int
void SetUniformInt(Shader shader, string name, bool value)
{
	glUniform1i(glGetUniformLocation(shader.ID, name.c_str()), (int)value);
}

// Set the uniform float
void SetUniformFloat(Shader shader, string name, float value)
{
	glUniform1f(glGetUniformLocation(shader.ID, name.c_str()), value);
}

// Set the uniform vec2
void SetUniformVec2(Shader shader, string name, Vec2 value)
{
	glUniform2f(glGetUniformLocation(shader.ID, name.c_str()), value.x, value.y);
}

// Set the uniform vec3
void SetUniformVec3(Shader shader, string name, Vec3 value)
{
	glUniform3f(glGetUniformLocation(shader.ID, name.c_str()), value.x, value.y, value.z);
}

void InitilizePVM(Shader shader, glm::mat4 projection, glm::mat4 view, glm::mat4 matrix, bool DeslectAfter = true) // initilize projection, view and matrix
{
	UseShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
	if (DeslectAfter)
	{
		DeselectShader();
	}
}




#endif // !SHADERS_H
