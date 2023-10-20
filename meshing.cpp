// meshing.cpp: 定义应用程序的入口点。
//

#include "Octree.cpp"
#include "ReadModel.cpp"
#include "Visualization/Scene.cpp"
#include "Visualization/Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


int main(int argc, char* argv[])
{
	std::string exePath = argv[0];
	

	ReadModel* rm = new ReadModel();
	rm->read(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit\\nanosuit.obj");
	Model* model = new Model(rm->meshes);

	std::vector<glm::vec3> positions = model->extractPosition();

	// 创建八叉树根节点
	Octree* otr = new Octree(MAX_DEPTH, MAX_PINTS, BoundingBox(glm::vec3(-10, -10, -10), glm::vec3(10, 10, 10)));
	for (int i = 0; i < positions.size(); i++) {
		otr->insertPoint(otr->root, positions[i], 0);
	}
	std::vector<Mesh> meshes;
	std::vector<OctreeNode> boxs;
	otr->getBoxHavePoints(otr->root, 0, boxs);
	//for (int i = 0; i < boxs.size(); i++) {
	//	meshes.push_back(Mesh(boxs[i].bounds));
	//}
	Model* model0 = new Model(boxs);
	// 图形显示模块
	Scene* sc = new Scene();
	camera->Position = glm::vec3(0, 10, 10);
	sc->add(model0);
	sc->add(model);
	sc->renderLoop();
	// 文件读取模块
	//ReadModel* rm = new ReadModel();
	//rm->read("C:/Users/19288/Desktop/coding/cxx/meshing/models/cylinder.obj");
	//std::vector<Point> vertex = rm->processVertex(rm->meshes[0]);
	//std::vector<unsigned int> indices = rm->processFace(rm->meshes[0]);
	//Model* shape = new Model(vertex, indices);

	//sc->add(shape);


	//std::cout << "vertex count" << vertex.size() << std::endl;
	//// 创建八叉树根节点
	//Octree* otr = new Octree(6, 1, BoundingBox(Point(-10, -10, -10), Point(10, 10, 10)));
	//for (int i = 0; i < vertex.size(); i++) {
	//	otr->insertPoint(otr->root, Point(vertex[i].x, vertex[i].y, vertex[i].z), 0);
	//}
	//std::vector<Point> points;
	//otr->getAllPoints(otr->root, 0, points);
	//std::cout << "mesh count: " << points.size() << std::endl;

	system("pause");
	return 0;
}
