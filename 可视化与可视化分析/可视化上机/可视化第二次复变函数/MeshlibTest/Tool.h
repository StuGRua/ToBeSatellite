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
	void CTool<M>::homework1()//Gauss-Bonet������֤ 
	{
		cout << "�����е�������� " << m_pMesh->numVertices() << endl;//ŷ��ʾ������V
		cout << "�����бߵ������� " << m_pMesh->numEdges() << endl;//ŷ��ʾ������E
		cout << "���������������" << m_pMesh->numFaces() << endl;//ŷ��ʾ������F
		cout << "Eulersʾ������V+F-E����" << m_pMesh->numFaces() + m_pMesh->numVertices() - m_pMesh->numEdges() << endl;
		double ang = 0;//�����˹����֮�� ����ɢ��
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)//���������mesh��.m�ļ����е�ÿ������б���
		{
			double temp = 0;
			M::CVertex* pVertex = mv.value();
			for (M::VertexInHalfedgeIterator vih(m_pMesh, pVertex); !vih.end(); vih++)//���ݱ������ĵ�����������ҳ���ǰ���Ӧ�����а�߽ṹ ��߽ṹ�洢��һ��С������Ƭ�������ߵ���Ϣ��
			{
				M::CHalfEdge* pHF = vih.value();//��õ�ǰ��߽ṹ������
				double a = m_pMesh->edgeLength((CToolEdge*)pHF->he_next()->edge());//���������Ƭ�ĵ�һ����
				double b = m_pMesh->edgeLength((CToolEdge*)pHF->he_prev()->edge());//���������Ƭ�ĵڶ�����
				double c = m_pMesh->edgeLength((CToolEdge*)pHF->edge());//���������Ƭ�ĵ�������
				double cos = (a * a + b * b - c * c) / (2 * a * b);//�������Ҷ�������cos����ֵ
				temp += acos(cos);//���ݷ����Ǻ��������
			}
			if (m_pMesh->isBoundary(pVertex)) {
				ang += (PI - temp);//���ݿ��Ͻ���ԭ�� ����Ǳ�Ե����pi-
			}
			else
			{
				ang += (2 * PI - temp);//���Ǳ�Ե����2pi-
			}
		}
		cout << endl;
		double a1 = (m_pMesh->numFaces() + m_pMesh->numVertices() - m_pMesh->numEdges()) * 2 * PI;
		cout << "2*Pi*Eulersʾ������V+F-E���� " << a1 << endl;
		cout << "��˹����֮�ͣ� " << ang << endl;
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
		cout << "����������" << endl;
		cin >> n;
		//n = 1;
		cout << "���������" << endl;
		for (int i = 0; i < n; i++)
		{
			if(i!=0)
			cout << "������һ�������" << endl;
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