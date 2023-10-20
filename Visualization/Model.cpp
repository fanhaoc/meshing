#include "Model.h"

Model::Model(Mesh* mesh)
{
	meshes.push_back(mesh);
}

Model::Model(std::vector<Mesh*>& meshes)
{
	this->meshes = meshes;
}

Model::Model(std::vector<OctreeNode>& nodes)
{
	
	std::map<unsigned int, Mesh*> maps;
	for (int i = 0; i < nodes.size(); i++) {
		auto haveMesh = maps.find(nodes[i].level);
		if ( haveMesh == maps.end()) {
			Mesh* mesh = new Mesh(nodes[i].bounds);
			mesh->MESH_MODE = GL_LINE; // 使用线框模式绘制八叉树
			meshes.push_back(mesh);
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
