#ifndef _TOOL_H_
#define _TOOL_H_

#include<complex>
#include<math.h>
#include<vector>

#include "ToolMesh.h"

#ifndef PI
#define PI 3.1415926535
#endif

namespace MeshLib
{
	using namespace std;

	template<typename M>
	class CTool
	{
	public:
		CTool(M* pMesh);
		~CTool(){};

		void homework1();
		void homework2();
		void _change_color();
	protected:
		typename M* m_pMesh;
	};

	template<typename M>
	CTool<M>::CTool(M* pMesh)
	{
		m_pMesh = pMesh;
	}

	template<typename M>
	void CTool<M>::homework1()//Gauss-Bonet定理验证 
	{
		cout << "网格中点的数量： " << m_pMesh->numVertices() << endl;//欧拉示性数的V
		cout << "网格中边的数量： " << m_pMesh->numEdges() << endl;//欧拉示性数的E
		cout << "网格中面的数量：" << m_pMesh->numFaces() << endl;//欧拉示性数的F
		cout << "Eulers示性数（V+F-E）：" << m_pMesh->numFaces() + m_pMesh->numVertices() - m_pMesh->numEdges() << endl;
		double ang = 0;//计算高斯曲率之和 （离散）
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)//对输入进的mesh（.m文件）中的每个点进行遍历
		{
			double temp = 0;
			M::CVertex* pVertex = mv.value();
			for (M::VertexInHalfedgeIterator vih(m_pMesh, pVertex); !vih.end(); vih++)//根据被遍历的点和整个网格找出当前点对应的所有半边结构 半边结构存储了一个小三角面片的三条边的信息。
			{
				M::CHalfEdge* pHF = vih.value();//获得当前半边结构的数据
				double a = m_pMesh->edgeLength((CToolEdge*)pHF->he_next()->edge());//获得三角面片的第一条边
				double b = m_pMesh->edgeLength((CToolEdge*)pHF->he_prev()->edge());//获得三角面片的第二条边
				double c = m_pMesh->edgeLength((CToolEdge*)pHF->edge());//获得三角面片的第三条边
				double cos = (a * a + b * b - c * c) / (2 * a * b);//根据余弦定理计算出cosα的值
				temp += acos(cos);//根据反三角函数算出α
			}
			if (m_pMesh->isBoundary(pVertex)) {
				ang += (PI - temp);//根据课上讲的原理 如果是边缘的用pi-
			}
			else
			{
				ang += (2 * PI - temp);//不是边缘的用2pi-
			}
		}
		cout << endl;
		double a1 = (m_pMesh->numFaces() + m_pMesh->numVertices() - m_pMesh->numEdges()) * 2 * PI;
		cout << "2*Pi*Eulers示性数（V+F-E）： " << a1 << endl;
		cout << "高斯曲率之和： " << ang << endl;
	}










	void f(double x, double y, double &u, double &v, int n, double a[], double b[]) {
		complex<double> S(x,y);
		for (int i = 0; i < n; i++)
		{
			complex<double> temp(a[i], b[i]);
			if (i == 0)
				S = (S- temp);
			else
				S *= (S - temp);
		}
		u = S.real();
		v = S.imag();
		return;
	}

	template<typename M>
	void CTool<M>::homework2()
	{
		int n;
		double a[100], b[100];
		cout << "输入解的数量" << endl;
		cin >> n;
		//n = 1;
		cout << "输入点坐标" << endl;
		for (int i = 0; i < n; i++)
		{
			if(i!=0)
			cout << "输入下一点的坐标" << endl;
			cin >> a[i] >> b[i];
		/*	a[i] = 1;
			b[i] = 1;*/
		}
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			//double ax = mv.begin().value()->point()[0];
			//double ay = mv.begin().value()->point()[1];
			f(pVertex->point()[0], pVertex->point()[1], pVertex->huv()[0], pVertex->huv()[1], n,a,b);
		}
	}

	void ff(double x, double y, double& u, double& v) {
		u = 0;
		v = 0;
	}

	template<typename M>
	void CTool<M>::_change_color()
	{
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			/*pVertex->point()[0] /= 12.5;
			pVertex->point()[1] /= 12.5;*/
			ff(pVertex->point()[0], pVertex->point()[1], pVertex->huv()[0], pVertex->huv()[1]);
			/*
			pVertex->rgb()[0] = 1;
			pVertex->rgb()[1] = 0;
			pVertex->rgb()[2] = 0;
			*/
		}
	}
}



#endif