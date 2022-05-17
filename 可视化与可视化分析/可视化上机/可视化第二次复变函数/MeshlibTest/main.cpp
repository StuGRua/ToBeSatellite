#include<iostream>
#include"Tool.h"
#include"ToolMesh.h"
using namespace std;
using namespace MeshLib;

//void main(int argc, char** argv)
//{
//	CTMesh mesh;
//	mesh.read_m(argv[1]);
//	CTool<CTMesh> tool(&mesh);
//	//tool.test();
//	//tool.test_1();
//	tool._change_color();
//	mesh.write_m(argv[2]);
//
//	getchar();
//}
void main(int argc, char** argv)
{
	CTMesh mesh;
	cout << "读入中" << endl;
	mesh.read_m(argv[1]);
	cout << "读入完成" << endl;
	CTool<CTMesh> tool(&mesh);//将argv【1】对应的网格输入给tool中
	tool.homework2();
	//tool._change_color();
	cout << "写入中" << endl;
	mesh.write_m(argv[2]);
	cout << "写入完毕" << endl;
	getchar();
}
