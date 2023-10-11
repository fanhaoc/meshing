#pragma once
#include <vector>
#include <iostream>
#include "Types.h"

const int MAX_DEPTH = 5; // ��������
const int MAX_PINTS = 1; // ÿ����������ຬ��һ����

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
	// ������Ƿ��ڱ߽����
	bool isPointInBox(const Point& point, const BoundingBox& box) {
		return (point.x >= box.minCoord.x && point.x <= box.maxCoord.x &&
			point.y >= box.minCoord.y && point.y <= box.maxCoord.y &&
			point.z >= box.minCoord.z && point.z <= box.maxCoord.z);
	}
	//����㵽�˲�����
	void insertPoint(OctreeNode* node, const Point& point, int depth) {
		if (depth == MAX_DEPTH) {
			node->points.push_back(point);
			return;
		}
		
		// ���ݲ��뵽�ڵ���
		if (node->children[0] == nullptr) {
			// ���û���ӽڵ�
			node->points.push_back(point);
			if (node->points.size() <= MAX_PINTS) {
				return; // ������û������ֵ����ɲ���
			}
			else {
				// ������������ֵ���ʷ�Ϊ�˸��ڵ㣬�ݹ��Ӧ�ڵ�
				subdivideOctree(node);
				for (int i = 0; i <= MAX_POINTS; i++) {
					int index = pointIndices(node->points[i], node);
					insertPoint(node->children[index], node->points[i], depth + 1);
				}
				// ɾ�����ڵ��е�����
				node->points.clear();
			}
		}
		else {
			// ������ӽڵ㣬ֱ�ӵݹ�����Ӧ���ӽڵ���
			int index = pointIndices(point, node);
			insertPoint(node->children[index], point, depth + 1);
		}
	}
	// ������ڽڵ��е�����
	int pointIndices(Point point, OctreeNode* node) {
		// �����ӽڵ������
		int index = 0;
		double centerX = (node->bounds.minCoord.x + node->bounds.maxCoord.x) / 2.0;
		double centerY = (node->bounds.minCoord.y + node->bounds.maxCoord.y) / 2.0;
		double centerZ = (node->bounds.minCoord.z + node->bounds.maxCoord.z) / 2.0;
		if (point.x > centerX) index |= 1;
		if (point.y > centerY) index |= 2;
		if (point.z > centerZ) index |= 4;
		return index;
	}
	// �����Ӱ˲�ڵ�
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
		bd.push_back(BoundingBox(node->bounds.minCoord, Point(centerX, centerY, centerZ))); // ��һ��
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
	// �����˲�������ȡ���е�����
	void getAllPoints(OctreeNode* node,int depth, std::vector<Point>& points) {
		if (node == nullptr) return;
		for (int i = 0; i < node->points.size(); i++) {
			points.push_back(node->points[i]);
		}
		// �ݹ�˸��ӽڵ�
		for (int i = 0; i < 8; i++) {
			getAllPoints(node->children[i], depth + 1, points);
		}
	}
};