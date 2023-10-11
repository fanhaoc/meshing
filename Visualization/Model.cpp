#pragma once
#include <vector>
#include "../Types.h"

/// <summary>
/// 模型才是最终保存数据的地方，其他地方的数据记得删除
/// </summary>
class Model {
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Model(std::vector<Point>& points, std::vector<unsigned int>& index) {
		for (int i = 0, len = points.size(); i < len; i++) {
			vertices.push_back(points[i].x);
			vertices.push_back(points[i].y);
			vertices.push_back(points[i].z);
		}
		indices = index;
	}
};