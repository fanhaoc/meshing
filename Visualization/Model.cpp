#include "Model.h"

Model::Model(std::vector<Mesh> meshes)
{
	this->meshes = meshes;
}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string const& path)
{
	
}

std::vector<glm::vec3> Model::extractPosition()
{
	std::vector<glm::vec3> positions;
	for (int i=0; i < meshes.size(); i++) {
		for (int j=0; j < meshes[i].vertices.size(); j++) {
			positions.push_back(meshes[i].vertices[j].Position);
		}
	}
	return positions;
}
