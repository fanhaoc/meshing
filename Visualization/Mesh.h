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
	// Íø¸ñÊý¾Ý
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader* sahder);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
