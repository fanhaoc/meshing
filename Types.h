#pragma once
#include <vector>
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