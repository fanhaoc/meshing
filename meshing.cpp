// meshing.cpp: 定义应用程序的入口点。
//

#include "meshing.h"
#include "Octree.cpp"
#include "ReadModel.cpp"
#include "Visualization/Scene.cpp"


int main()
{
	Scene* sc = new Scene();
	sc->renderLoop();
	//ReadModel* rm = new ReadModel();
	//rm->read("C:/Users/19288/Desktop/coding/cxx/meshing/models/cylinder.obj");
	//std::vector<aiVector3D> vertex = rm->processVertex(rm->meshes[0]);
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
