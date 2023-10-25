#pragma once
#include <vector>
#include <iomanip>
#include "../Visualization/Mesh.h"
#include "../Types.h"

class Ray {
public:
	Ray(std::vector<OctreeNode> oct, std::vector<Mesh*>& meshes) {
		octree = oct;
		model = meshes;
	}

	std::vector<OctreeNode> octree;
	std::vector<Mesh*> model;

	std::vector<OctreeNode> getInnerOctree() {
		std::cout << octree.size() << ":" << std::setfill('0') << std::setw(5) << '0'; //��ʾ����
		std::vector<OctreeNode> innerOctree;
		for (int i = 0; i < octree.size(); i++) {
			if (i % 100 == 0) {
				std::cout << "\b\b\b\b\b";
				std::cout << std::setfill('0') << std::setw(5) << i;
			}

			if (isInner(octree[i])) {
				innerOctree.push_back(octree[i]);
			}
		}
		return innerOctree;
	}

	bool isInner(OctreeNode& node) {
		// �������߷���Ϊx������
		glm::vec3 rayDir = glm::vec3(1.0, 0.0, 0.0);
		// ������ʼ�㣬Ϊ�˲����ڵ���е�
		glm::vec3 rayOrigin = (node.bounds.maxCoord + node.bounds.minCoord) / 2.0f;
		// ��¼��ģ�͵Ľ���
		int count = 0;

		for (int i = 0; i < model.size(); i++) {
			
			std::vector<Vertex> vertices = model[i]->vertices;
			std::vector<unsigned int> indices = model[i]->indices;
			for (int j = 0; j < model[i]->indices.size(); j+=3){

				if (isIntersection(rayOrigin, rayDir, vertices[indices[j]].Position, vertices[indices[j + 1]].Position, vertices[indices[j + 2]].Position)
				) {
					count++;
				}
			}
		}
		if (count % 2 == 0) {
			return false;
		}
		return true;
	}

	// �ж����ߺ�������Ƭ�Ƿ��ཻ
	bool isIntersection(const glm::vec3& origin, const glm::vec3& dir,
		const glm::vec3& vertex01, const glm::vec3& vertex02, const glm::vec3& vertex03) {
		// ���������
		glm::vec3 edge01 = vertex02 - vertex01;
		glm::vec3 edge02 = vertex03 - vertex01;

		// �ж��ڲ�
		glm::vec3 s = origin - vertex01;
		glm::vec3 s1 = glm::cross(dir, edge02);
		glm::vec3 s2 = glm::cross(s, edge01);

		float a0 = 1.0f / glm::dot(s1, edge01);
		float a1 = glm::dot(s2, edge02);
		float a2 = glm::dot(s1, s);
		float a3 = glm::dot(s2, dir);

		glm::vec3 params = a0 * glm::vec3(a1, a2, a3);

		if (params[0] > 0.0 && params[1] > 0 && params[2] > 0 && params[1] + params[2] < 1) {
			return true;
		}

		return false;

		//// ���㷨����
		//glm::vec3 normal = glm::normalize(glm::cross(edge01, edge02));
		//// �������ߺ������ε�ƽ�潻��
		//float d = glm::dot(-normal, vertex01);
		//float denominator = glm::dot(normal, dir);
		//
		//if (std::abs(denominator) < 1e-6) {
		//	// ����ƽ����������
		//	return false;
		//}
		//
		//float t = -(glm::dot(normal, origin) + d) / denominator;

		//if (t < 0.0) {
		//	// ���������ߵĺ�
		//	return false;
		//}

		//// ���㽻��
		//glm::vec3 intersectionpoint = origin + t * dir;
		// �жϽ����Ƿ����������ڲ�

		//glm::vec3 edge0 = vertex02 - vertex01;
		//glm::vec3 edge1 = vertex03 - vertex02;
		//glm::vec3 edge2 = vertex01 - vertex03;

		//glm::vec3 c0 = intersectionpoint - vertex01;
		//glm::vec3 c1 = intersectionpoint - vertex02;
		//glm::vec3 c2 = intersectionpoint - vertex03;

		//if (glm::dot(normal, glm::cross(edge0, c0)) >= 0
		//	&& glm::dot(normal, glm::cross(edge1, c1)) >= 0
		//	&& glm::dot(normal, glm::cross(edge2, c2)) >= 0) {
		//	return true;
		//}

		//return false;
	}
};
