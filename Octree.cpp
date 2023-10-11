#pragma once
#include <vector>
#include <iostream>
#include "Types.h"

const int MAX_DEPTH = 5; // 最大树深度
const int MAX_PINTS = 1; // 每个立方体最多含有一个点

class Octree {
public:
	int MAX_DEPTH = 0;
	int MAX_POINTS = 0;
	OctreeNode* root;
	Octree(int depth, int size, BoundingBox& bbox) {
		MAX_DEPTH = depth;
		MAX_POINTS = size;
		root = new OctreeNode(bbox);
	}
	// 计算点是否在边界框内
	bool isPointInBox(const Point& point, const BoundingBox& box) {
		return (point.x >= box.minCoord.x && point.x <= box.maxCoord.x &&
			point.y >= box.minCoord.y && point.y <= box.maxCoord.y &&
			point.z >= box.minCoord.z && point.z <= box.maxCoord.z);
	}
	//插入点到八叉树中
	void insertPoint(OctreeNode* node, const Point& point, int depth) {
		if (depth == MAX_DEPTH) {
			node->points.push_back(point);
			return;
		}
		
		// 数据插入到节点中
		if (node->children[0] == nullptr) {
			// 如果没有子节点
			node->points.push_back(point);
			if (node->points.size() <= MAX_PINTS) {
				return; // 数据量没超过阈值，完成插入
			}
			else {
				// 数据量超出阈值，剖分为八个节点，递归对应节点
				subdivideOctree(node);
				for (int i = 0; i <= MAX_POINTS; i++) {
					int index = pointIndices(node->points[i], node);
					insertPoint(node->children[index], node->points[i], depth + 1);
				}
				// 删除本节点中的数据
				node->points.clear();
			}
		}
		else {
			// 如果有子节点，直接递归进入对应的子节点中
			int index = pointIndices(point, node);
			insertPoint(node->children[index], point, depth + 1);
		}
	}
	// 计算点在节点中的索引
	int pointIndices(Point point, OctreeNode* node) {
		// 计算子节点的索引
		int index = 0;
		double centerX = (node->bounds.minCoord.x + node->bounds.maxCoord.x) / 2.0;
		double centerY = (node->bounds.minCoord.y + node->bounds.maxCoord.y) / 2.0;
		double centerZ = (node->bounds.minCoord.z + node->bounds.maxCoord.z) / 2.0;
		if (point.x > centerX) index |= 1;
		if (point.y > centerY) index |= 2;
		if (point.z > centerZ) index |= 4;
		return index;
	}
	// 生成子八叉节点
	void subdivideOctree(OctreeNode*  node) {
		double minX = node->bounds.minCoord.x;
		double minY = node->bounds.minCoord.y;
		double minZ = node->bounds.minCoord.z;
		double centerX = (node->bounds.minCoord.x + node->bounds.maxCoord.x) / 2.0;
		double centerY = (node->bounds.minCoord.y + node->bounds.maxCoord.y) / 2.0;
		double centerZ = (node->bounds.minCoord.z + node->bounds.maxCoord.z) / 2.0;
		double maxX = node->bounds.maxCoord.x;
		double maxY = node->bounds.maxCoord.y;
		double maxZ = node->bounds.maxCoord.z;
		std::vector<BoundingBox> bd;
		bd.push_back(BoundingBox(node->bounds.minCoord, Point(centerX, centerY, centerZ))); // 第一个
		bd.push_back(BoundingBox(Point(centerX, minY, minZ), Point(maxX, centerY, centerZ))); // 2
		bd.push_back(BoundingBox(Point(minX, centerY, minZ), Point(centerX, maxY, centerZ))); // 3
		bd.push_back(BoundingBox(Point(centerX, centerY, minZ), Point(maxX, maxY, centerZ))); // 4

		bd.push_back(BoundingBox(Point(minX, minY, centerZ), Point(centerX, centerY, maxZ))); // 5
		bd.push_back(BoundingBox(Point(centerX, minY, centerZ), Point(maxX, centerY, maxZ))); // 6
		bd.push_back(BoundingBox(Point(minX, centerY, centerZ), Point(centerX, maxY, maxZ))); // 7
		bd.push_back(BoundingBox(Point(centerX, centerY, centerZ), node->bounds.maxCoord)); // 8

		for (int i = 0; i < 8; i++) {
			node->children[i] = new OctreeNode(bd[i]);
		}
	}
	// 遍历八叉树，获取所有的数据
	void getAllPoints(OctreeNode* node,int depth, std::vector<Point>& points) {
		if (node == nullptr) return;
		for (int i = 0; i < node->points.size(); i++) {
			points.push_back(node->points[i]);
		}
		// 递归八个子节点
		for (int i = 0; i < 8; i++) {
			getAllPoints(node->children[i], depth + 1, points);
		}
	}
};