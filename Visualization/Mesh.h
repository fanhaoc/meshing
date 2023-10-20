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
	Mesh(float vertices[]);
	Mesh(BoundingBox bb);
	// 网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<glm::vec3> offsets;
	// 绘制设置
	int MESH_MODE = GL_FILL;

	void addCopy(glm::vec3 offset);
	void Draw(Shader* shader);
private:
	unsigned int VAO, VBO, EBO, instanceVBO;
	void setupMesh();
};
