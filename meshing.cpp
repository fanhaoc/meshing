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

	// 图形显示模块
	Scene* sc = new Scene();
	
	sc->add(model);

	// 文件读取模块
	//ReadModel* rm = new ReadModel();
	//rm->read("C:/Users/19288/Desktop/coding/cxx/meshing/models/cylinder.obj");
	//std::vector<Point> vertex = rm->processVertex(rm->meshes[0]);
	//std::vector<unsigned int> indices = rm->processFace(rm->meshes[0]);
	//Model* shape = new Model(vertex, indices);

	//sc->add(shape);

	 sc->renderLoop(positions);
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
