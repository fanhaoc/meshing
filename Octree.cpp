#pragma once
#include <vector>
#include <iostream>
#include "Types.h"


class Octree {
public:
	int MAX_DEPTH = 0;
	int MAX_POINTS = 0;
	OctreeNode* root;
	Octree(int depth, int size, BoundingBox& bbox) {
		MAX_DEPTH = depth;
		MAX_POINTS = size;
		root = new OctreeNode(bbox, 1);
	}
	// 计算点是否在边界框内
	bool isPointInBox(const glm::vec3 point, const BoundingBox& box) {
		return (point.x >= box.minCoord.x && point.x <= box.maxCoord.x &&
			point.y >= box.minCoord.y && point.y <= box.maxCoord.y &&
			point.z >= box.minCoord.z && point.z <= box.maxCoord.z);
	}
	//插入点到八叉树中
	void insertPoint(OctreeNode* node,glm::vec3 point, int depth) {
		//if (!isPointInBox(point, node->bounds)) {
		//	return;
		//}
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

		
		//if (node->children[0] == nullptr) {
		//	subdivideOctree(node);
		//}
		//int index = pointIndices(point, node);
		//insertPoint(node->children[index], point, depth + 1);
	}
	// 计算点在节点中的索引
	int pointIndices(glm::vec3 point, OctreeNode* node) {
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
		bd.push_back(BoundingBox(node->bounds.minCoord, glm::vec3(centerX, centerY, centerZ))); // 第一个
		bd.push_back(BoundingBox(glm::vec3(centerX, minY, minZ), glm::vec3(maxX, centerY, centerZ))); // 2
		bd.push_back(BoundingBox(glm::vec3(minX, centerY, minZ), glm::vec3(centerX, maxY, centerZ))); // 3
		bd.push_back(BoundingBox(glm::vec3(centerX, centerY, minZ), glm::vec3(maxX, maxY, centerZ))); // 4

		bd.push_back(BoundingBox(glm::vec3(minX, minY, centerZ), glm::vec3(centerX, centerY, maxZ))); // 5
		bd.push_back(BoundingBox(glm::vec3(centerX, minY, centerZ), glm::vec3(maxX, centerY, maxZ))); // 6
		bd.push_back(BoundingBox(glm::vec3(minX, centerY, centerZ), glm::vec3(centerX, maxY, maxZ))); // 7
		bd.push_back(BoundingBox(glm::vec3(centerX, centerY, centerZ), node->bounds.maxCoord)); // 8

		for (int i = 0; i < 8; i++) {
			node->children[i] = new OctreeNode(bd[i], node->level + 1);
		}
	}
	// 遍历八叉树，获取所有的数据
	void getAllPoints(OctreeNode* node,int depth, std::vector< glm::vec3>& points) {
		if (node == nullptr) return;
		for (int i = 0; i < node->points.size(); i++) {
			points.push_back(node->points[i]);
		}
		// 递归八个子节点
		for (int i = 0; i < 8; i++) {
			getAllPoints(node->children[i], depth + 1, points);
		}
	}

	// 遍历八叉树， 获取有数据的节点
	void getBoxHavePoints(OctreeNode* node, int depth, std::vector<OctreeNode>& box) {
		if (node == nullptr) return;
		if (node->points.size() > 0) {
			box.push_back(*node);
			return;
		}
		// 递归八个子节点
		for (int i = 0; i < 8; i++) {
			getBoxHavePoints(node->children[i], depth + 1, box);
		}
	}
	
	// 遍历八叉树，得到所有的叶子节点
	void getBoxOfLeaf(OctreeNode* node, int depth, std::vector<OctreeNode>& box) {
		if (node == nullptr) return;
		if (node->children[0] == nullptr) {
			box.push_back(*node);
			return;
		}
		// 递归八个子节点
		for (int i = 0; i < 8; i++) {
			getBoxOfLeaf(node->children[i], depth + 1, box);
		}
	}

};