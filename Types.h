#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>

const int MAX_DEPTH = 6; // 最大树深度
const int MAX_PINTS = 5; // 每个立方体最多含有一个点

struct BoundingBox
{
	glm::vec3 minCoord;
	glm::vec3 maxCoord;
	BoundingBox(glm::vec3 min, glm::vec3 max) {
		minCoord = min;
		maxCoord = max;
	}
	BoundingBox() {
		minCoord = glm::vec3(0, 0, 0);
		maxCoord = glm::vec3(0, 0, 0);
	}
};

struct OctreeNode
{
	BoundingBox bounds;
	unsigned int level;
	std::vector<glm::vec3> points;
	OctreeNode* children[8]; // 子节点数组

	OctreeNode(const BoundingBox& bbox, unsigned int lev) {
		bounds = bbox;
		level = lev;
		for (int i = 0; i < 8; i++) {
			children[i] = nullptr;
		}
	}
};

struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};