#pragma once
#include <vector>
#include <string>
#include "Mesh.h"
#include "Shader.h"
class Model {
public:
	Model(std::string path);
	Model(std::vector<Mesh> meshes);
	~Model();
	std::vector<Mesh> meshes;
	unsigned int type = GL_TRIANGLES;
	void Draw(Shader* shader);
	void loadModel(std::string const& path);
	std::vector<glm::vec3> extractPosition();
};