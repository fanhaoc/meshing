#pragma once
#include <vector>
#include <string>
#include <map>
#include "Mesh.h"
#include "Shader.h"
class Model {
public:
	Model(Mesh* mesh);
	Model(std::vector<Mesh*>& meshes);
	Model(const std::vector<OctreeNode>& nodes);
	~Model();

	std::vector<Mesh*> meshes;
	unsigned int type = GL_TRIANGLES;

	void Draw(Shader* shader);
	std::vector<glm::vec3> extractPosition();
};