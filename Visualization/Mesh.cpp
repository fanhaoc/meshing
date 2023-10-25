#include "Mesh.h"


/// <summary>
/// 模型才是最终保存数据的地方，其他地方的数据记得删除
/// </summary>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	// setupMesh();
}

//Mesh::Mesh(float vertices[])
//{
//	this->vertices.resize(36);
//	memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
//	this->setupMesh();
//}

Mesh::Mesh(BoundingBox bb)
{
	std::vector<glm::vec3> points;
	points.push_back(bb.minCoord);
	points.push_back(bb.maxCoord);
	for (unsigned int i = 0; i < 2; i++) {
		for (unsigned int j = 0; j < 2; j++) {
			for (unsigned int k = 0; k < 2; k++) {
				Vertex vt;
				vt.Position = glm::vec3(points[i].x, points[j].y, points[k].z);
				vertices.push_back(vt);
			}
		}
	}
	// 生成index
	//unsigned int index[36] = {
	//	0, 2, 3, 3, 1, 0,
	//	4, 5, 7, 7, 6, 4,
	//	0, 4, 6, 6, 2, 0,
	//	1, 3, 7, 7, 5, 1,
	//	2, 6, 7, 7, 3, 2,
	//	0, 1, 5, 5, 4, 0
	//};
	unsigned int index[24] = {
		0, 2, 2, 3, 3, 1, 1, 0,
		6, 4, 4, 5, 5, 7, 7, 6,
		0, 4, 2, 6, 3, 7, 1, 5
	};
	indices.resize(24);
	memcpy(&indices[0], index, 24 * sizeof(unsigned int));
}


void Mesh::addCopy(glm::vec3 offset)
{
	offsets.push_back(offset);
}

void Mesh::Draw(Shader* shader)
{
	// 绘制设置


	setupMesh();
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse") {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->setUniform1i("material.diffuse", 0);
			// 读取贴图...
			
		}
		else if (textures[i].type == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->setUniform1i("material.specular", 1);
		}
	}

	shader->setUniform3f("objColor", color);
	shader->setUniform1f("needLight", needLight);

	glBindVertexArray(VAO);
	if (offsets.size() > 0) {
		glDrawElementsInstanced(drawType, indices.size(), GL_UNSIGNED_INT, 0, offsets.size());
	}
	else {
		glDrawElements(drawType, indices.size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}



void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));

	if (offsets.size() > 0) {
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * offsets.size(), &offsets[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(3);

		glVertexAttribDivisor(3, 1);
	}

	glBindVertexArray(0);
}
