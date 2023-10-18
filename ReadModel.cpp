#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <fstream>
#include "Visualization/Mesh.h"
#include "Types.h"
#include "Visualization//Mesh.h"

class ReadModel
{
public:
	const aiScene* scene = nullptr;
	//aiNode* rootNode = nullptr;
	Assimp::Importer importer;
	/*std::vector<aiMesh*> meshes;*/
	std::vector<Mesh> meshes;
	std::string directory;
	ReadModel() {

	}

	int read(std::string filePath) {
		//加载obj文件
		scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		//检查是否加载成功
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
			return -1;
		}
		directory = filePath.substr(0, filePath.find_last_of('\\'));
		std::cout << directory << std::endl;
		//获得模型根节点
		//rootNode = scene->mRootNode;
		processNode(scene->mRootNode);
		return 0;
	}
	////遍历网格的顶点
	//std::vector<Point> processVertex(aiMesh* mesh) {
	//	std::vector<Point> data;
	//	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
	//		aiVector3D vertex = mesh->mVertices[i];
	//		//std::cout << "x:" << vertex.x << "y:" << vertex.y << "z:" << vertex.z << std::endl;
	//		//std::cout << i << std::endl;
	//		data.push_back(Point(vertex.x, vertex.y, vertex.z));
	//	}
	//	return data;
	//}
	//// 遍历网格的法线
	//std::vector<Point> processNormal(aiMesh* mesh) {
	//	std::vector<Point> data;
	//	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
	//		aiVector3D normal = mesh->mNormals[i];
	//		//std::cout << "normals:" << normal.x << " + " << normal.y << " + " << normal.z << std::endl;
	//		//std::cout << "x:" << vertex.x << "y:" << vertex.y << "z:" << vertex.z << std::endl;
	//		//std::cout << i << std::endl;
	//		data.push_back(Point(normal.x, normal.y, normal.z));
	//	}
	//	return data;
	//}
	//遍历网格的面
	std::vector<unsigned int> processFace(aiMesh* mesh) {
		std::vector<unsigned int> data;
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			//std::cout << "index:" << i << std::endl;
			//遍历每个面的索引
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				unsigned int index = face.mIndices[j];
				data.push_back(index);
			}
		}
		return data;
	}

	////写入文件
	//int writeFile(aiMesh* mesh) {
	//	std::ofstream fs;
	//	fs.open("resultMesh.cmm", std::ios::out);
	//	//先写入顶点
	//	fs << "vertex" << std::endl;
	//	std::vector<aiVector3D> vertex = processVertex(mesh);
	//	for (unsigned int i = 0; i < vertex.size(); ++i) {
	//		fs << vertex[i].x << ',' << vertex[i].y << ',' << vertex[i].z << std::endl;
	//	}
	//	//写入面
	//	fs << "face" << std::endl;
	//	std::vector<aiFace> face = processFace(mesh);
	//	for (unsigned int i = 0; i < face.size(); ++i) {
	//		for (unsigned int j = 0; j < face[i].mNumIndices; ++j) {
	//			if (j == face[i].mNumIndices - 1) {
	//				fs << face[i].mIndices[j] << std::endl;
	//				break;
	//			}
	//			fs << face[i].mIndices[j] << ',';
	//		}
	//	}
	//	//写入网格
	//	fs.close();
	//	return 0;
	//}
	void free() {
		importer.FreeScene();
	}
	
	Mesh processMesh(aiMesh* mesh) {
		std::vector<Vertex> tempVertices;
		std::vector<unsigned int> tempIndices;
		std::vector<Texture> tempTextures;
		glm::vec3 tempVec;

		// 处理顶点
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex tempVertex;
			tempVertex.Position.x = mesh->mVertices[i].x;
			tempVertex.Position.y = mesh->mVertices[i].y;
			tempVertex.Position.z = mesh->mVertices[i].z;
			
			tempVertex.Normal.x = mesh->mNormals[i].x;
			tempVertex.Normal.y = mesh->mNormals[i].y;
			tempVertex.Normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0]) {
				tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else {
				tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			tempVertices.push_back(tempVertex);
		}

		// 处理面
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
				tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
			}
		}
		return Mesh(tempVertices, tempIndices, {});
	}
	
	//获取模型所有mesh
	void processNode(aiNode* node) {
		//处理当前节点的所有网格
		for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh));
		}
		//递归处理子节点
		for (unsigned int i = 0; i < node->mNumChildren; ++i) {
			processNode(node->mChildren[i]);
		}
	}

};
