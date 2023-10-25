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
	Mesh() {};
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(std::vector<glm::vec3> positions);
	Mesh(BoundingBox bb);
	// ��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<glm::vec3> offsets;
	glm::vec3 color = glm::vec3(0.6, 0.56, 0.49);
	// ��������
	unsigned int shaderType = 0;
	int needLight = 1; // 1��Ҫ��0����Ҫ
	int drawType = GL_TRIANGLES;

	void addCopy(glm::vec3 offset);
	void Draw(Shader* shader);
private:
	unsigned int VAO, VBO, EBO, instanceVBO;
	void setupMesh();
};
