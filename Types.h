#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>
struct  Point
{
	float x, y, z;
	Point(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	Point() :x(0), y(0), z(0) {}
};

struct BoundingBox
{
	Point minCoord;
	Point maxCoord;
	BoundingBox(Point& min, Point& max) {
		minCoord = min;
		maxCoord = max;
	}
	BoundingBox() {
		minCoord = Point();
		maxCoord = Point();
	}
};

struct OctreeNode
{
	BoundingBox bounds;
	std::vector<Point> points;
	OctreeNode* children[8]; // 子节点数组

	OctreeNode(const BoundingBox& bbox) {
		bounds = bbox;
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