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
	cout << "������" << endl;
	mesh.read_m(argv[1]);
	cout << "�������" << endl;
	CTool<CTMesh> tool(&mesh);//��argv��1����Ӧ�����������tool��
	tool.homework2();
	//tool._change_color();
	cout << "д����" << endl;
	mesh.write_m(argv[2]);
	cout << "д�����" << endl;
	getchar();
}
