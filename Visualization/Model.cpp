#include "Model.h"

Model::Model(Mesh* mesh)
{
	meshes.push_back(mesh);
}

Model::Model(std::vector<Mesh*>& meshes)
{
	this->meshes = meshes;
}

Model::Model(const std::vector<OctreeNode>& nodes)
{
	
	glm::vec3 colors[8] = {
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(235.0 / 255.0, 126.0 / 255.0, 94.0 / 255.0),
		glm::vec3(107.0/255.0, 221.0 / 255.0, 137.0 / 255.0),
		glm::vec3(0.46, 0.56, 0.83),
	};

	std::map<unsigned int, Mesh*> maps;
	for (int i = 0; i < nodes.size(); i++) {
		auto haveMesh = maps.find(nodes[i].level);
		if ( haveMesh == maps.end()) {
			Mesh* mesh = new Mesh(nodes[i].bounds);
			mesh->shaderType = 1; // 使用octree的着色器
			mesh->color = colors[nodes[i].level-1];
			mesh->needLight = 0.0;
			mesh->drawType = GL_LINES;
			meshes.push_back(mesh);
			maps[nodes[i].level] = mesh;
		}
		else {
			Mesh* mesh = haveMesh->second;
			glm::vec3 offset = nodes[i].bounds.minCoord - mesh->vertices[0].Position;
			mesh->addCopy(offset);
		}
	}
}


void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i]->Draw(shader);
	}
}

std::vector<glm::vec3> Model::extractPosition()
{
	std::vector<glm::vec3> positions;
	for (int i=0; i < meshes.size(); i++) {
		for (int j=0; j < meshes[i]->vertices.size(); j++) {
			positions.push_back(meshes[i]->vertices[j].Position);
		}
	}
	return positions;
}
