#pragma once
#include <vector>
#include <string>
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "../Types.h"
class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(float vertices[]);
	// Íø¸ñÊý¾Ý
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	void Draw(Shader* shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
	void setupPoint();
};
