/*! \file Operator.h
 *  \brief algorithms for converting one structure to another
 *  \author David Gu
 *  \date   documented on 12/08/2013
 *
 *	Algorithm for structure conversions
 */

#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include <map>
#include <vector>
#include <complex>

#include "Mesh/BaseMesh.h"
#include "Mesh/Vertex.h"
#include "Mesh/HalfEdge.h"
#include "Mesh/Edge.h"
#include "Mesh/Face.h"
#include "mesh/iterators.h"
#include "mesh/boundary.h"
#include "Parser/parser.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

namespace MeshLib
{
/*! \brief Conversion class
*
*	Algorithm for converting from one structure to another
*/
template<typename Mesh>
class COperator
{
public:

    /*! \brief COperator constructor
	 *  \param pMesh the input mesh
	 */
	  COperator( Mesh * pMesh ) { m_pMesh = pMesh; };
    /*! \brief COperator destructor
	 */
	  ~COperator(){};
	
	  /*!
	   *	Convert the metric structure to angle structure
	   */
	  void _metric_2_angle( );
	  /*!
	   *	Convert the embedding structure in R3 to metric structure
	   */
	  void _embedding_2_metric();
	  /*!
	   *	Convert angle structure to vertex curvature function
	   */
	  void _angle_2_curvature( );
	  /*!
	   *	Compute Laplace-Beltrami operator from angle structure
	   */
	  /*! Compute the edge weight
	   *  \f$ w(e) = \cot \alpha + \cot \beta \f$ where \f$\alpha,\beta\f$ are 
	   *  the two corner angles against edge \f$e\f$. \f$ w(e) = \cot \alpha \f$
	   *  If the edge is on the boundary, then 
	   */

	  void _angle_2_Laplace( );
	 /*!
	   *	Compute Combinatorial Laplace-Beltrami operator 
	   */
	  /*! Compute the edge weight
	   *  \f$ w(e) = 1 \f$ for all the edges
	   */

	  void _combinatorial_Laplace( );
		
	  /*! 
	   *	Deform the angle structure by Beltrami coefficient
	   *
	   */
	  /*! 
	   *	Conformal parameteriztion is set (vertex->uv()), 
	   *	Vertex Beltrami coefficient is set (vertex->mu()),
	   *	Compute the deformed metric
	   */
	  void _parameter_mu_2_metric();
	  /*!
	   *	From Riemannian metric to compute the edge diagonal ratio
	   *    Edge diagonal ratio is another way of representing conformal structure
	   */
	  void _metric_2_diagonal_ratio();

	  /*! 
	   *	Conformal parameteriztion is set (vertex->z()), 
	   *	Face Beltrami coefficient is set (face->mu()),
	   *	Compute the deformed angle structure
	   */
	  void _parameter_mu_2_angle( );
	  /*!
	   *	Compute the Beltrami coefficient on each face
	   *	Assume the z, w are given for each vertex, the map is z->w
	   */
	 void _parameter_2_mu( );	

	 /*!
	  *	corner angle to vertex curvature
	  */
	 void _corner_angle_2_vertex_curvature();

	 /*!
	  *	compute face normal and vertex normal
	  */
	 void _calculate_face_vertex_normal();
	 /*!
	  *	compute face area, vertex weight
	  */
	 void _calculate_face_vertex_area();
	/*!
	 *	normalize the mesh
	 */
	 void _normalize();
	
	 /*!
	  *	uv2pos
	  */
	 void _uv_2_pos();

  protected:
    /*!
     *	the input mesh
	 */
    Mesh	  * m_pMesh;

	/*!	Euclidean Cosine law
	 *   
	 * 	\param a,b,c edge lengths
	 *  return angle C
	 */
	double _cosine_law( double a, double b, double c );
	/*!
	 *	Compute the diagonal ratio on edge pE of mesh pM
	 *  \param pM input mesh, pE input edge
	 *  \output the diagonal ratio of the edge
	 */
	std::complex<double> _diagonal_ratio( Mesh * pM, typename Mesh::CEdge * pE );
		/*!
	 *	Vertex A, B, C are three vertices of a triangle, sorted CCWly
	 *  A and B have been embedded on the plane, isometrically embed vertex C
	 */
	bool _embed_third_vertex( Mesh * pM, typename Mesh::CVertex * A, typename Mesh::CVertex * B, typename Mesh::CVertex * C );
	/*!
	 *	Isometrically embed two faces adjacent to an edge pE
	 * \param pM input mesh, 
	 * \param pE input edge,
	 */
	void _embed_two_faces( Mesh * PM, typename Mesh::CEdge * pE );
	/*!
	 *	Isometrically embed the face adjacent to a boundary edge pE
	 * \param pM input mesh, 
	 * \param pE input edge,
	 */
	void _embed_one_face( Mesh * PM, typename Mesh::CEdge * pE );

	/*!
	 *	Compute the intersections of two circles 
	 *  \param x0,y0,r1, x1,y1,r1 are circles ( (x0,y0), r0 ) and ( (x1,y1), r1 )
	 *  \param xi,yi,xi_prime, yi_prime are the two intersection points
	 */
	int _circle_circle_intersection(double x0, double y0, double r0,
										double x1, double y1, double r1,
										double *xi, double *yi,
										double *xi_prime, double *yi_prime);
	
};



//Euclidean cosine law
template<typename M>
double COperator<M>::_cosine_law( double a, double b, double c )
{
          double cs =  ( a*a + b * b  - c * c )/( 2.0 * a * b );
          assert( cs <= 1.0 && cs >= -1.0 );
          return acos( cs );    
};


//Calculate corner angle
template<typename M>
void COperator<M>::_metric_2_angle( )
{
  
	for ( M::MeshFaceIterator fiter( m_pMesh); ! fiter.end(); fiter ++ )
  {
	  M::CFace * f = *fiter;

	  M::CHalfEdge * he[3];

      he[0] = m_pMesh->faceMostCcwHalfEdge( f ); 

	  for( int i = 0; i < 3; i ++ )
      {
        he[(i+1)%3] = m_pMesh->	faceNextCcwHalfEdge(he[i]);
      }

      double l[3];
      for(int i = 0; i < 3; i ++ )
      {
		  M::CEdge * e = m_pMesh->halfedgeEdge( he[i] );
          l[i] = e->length();
      }

      for(int i = 0; i < 3; i ++ )
      {
          he[(i+1)%3]->angle() = _cosine_law( l[(i+1)%3] ,l[(i+2)%3] ,l[i] );
      }
  }
};

template<typename M>
void COperator<M>::_embedding_2_metric( )
{
  
	for ( M::MeshEdgeIterator eiter( m_pMesh); ! eiter.end(); eiter ++ )
	{
		M::CEdge   * e = *eiter;
		M::CVertex * v1 = m_pMesh->edgeVertex1( e );
		M::CVertex * v2 = m_pMesh->edgeVertex2( e );
		e->length() = (v1->point()-v2->point()).norm();
	}
};



//Calculate vertex curvature
template<typename M>
void COperator<M>::_angle_2_curvature( )
{

  for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); viter ++ )
  {
	  M::CVertex * v = *viter;
      double k  = (v->boundary() )? PI: PI * 2;
	  for( M::VertexInHalfedgeIterator vh( m_pMesh, v ); !vh.end();  ++vh )
      {
		  M::CHalfEdge * he = *vh;
          k -= he->angle();
      }
      v->k() = k;
  }

};


//Calculate vertex curvature
template<typename M>
void COperator<M>::_angle_2_Laplace( )
{

	for( M::MeshEdgeIterator eiter( m_pMesh ); !eiter.end();  eiter ++ )
  {
	  M::CEdge * e = *eiter;
	  
	  M::CHalfEdge * he = m_pMesh->edgeHalfedge( e, 0 );
	  M::CHalfEdge * pNh = m_pMesh->faceNextCcwHalfEdge( he ); 
	 
	  double wt = cos( pNh->angle() )/sin( pNh->angle() );

	  M::CHalfEdge * sh = m_pMesh->halfedgeSym( he );
	 if( sh != NULL )
	 {
		 pNh = m_pMesh->faceNextCcwHalfEdge( sh );
		 wt +=  cos( pNh->angle() )/sin( pNh->angle() );
	 } 
	 e->weight() = wt;
	  
  }
};


//Calculate vertex curvature
template<typename M>
void COperator<M>::_combinatorial_Laplace( )
{

	for( M::MeshEdgeIterator eiter( m_pMesh ); !eiter.end();  eiter ++ )
	{
	  M::CEdge * e = *eiter;
	  e->weight() = 1.0; 
	}
};


template<typename M>
void COperator<M>::_parameter_mu_2_metric( )
{
	for ( M::MeshEdgeIterator eiter( m_pMesh); ! eiter.end(); eiter ++ )
	{
		M::CEdge   * e = *eiter;
		M::CVertex * v1 = m_pMesh->edgeVertex1( e );
		M::CVertex * v2 = m_pMesh->edgeVertex2( e );

	  std::complex<double> z1 = v1->z();
	  std::complex<double> z2 = v2->z();

	  std::complex<double> dz = z2 - z1;

	  std::complex<double> mu1 = v1->mu();
	  std::complex<double> mu2 = v2->mu();
	  std::complex<double> mu  = (mu1 + mu2)/2.0;

	  e->length() = std::abs( dz + mu * std::conj( dz ));
	}

	for ( M::MeshFaceIterator fiter( m_pMesh); ! fiter.end(); fiter ++ )
	{
		M::CFace     * f = *fiter;

		M::CHalfEdge * he[3];

		he[0] = m_pMesh->faceMostCcwHalfEdge( f ); 

	  for( int i = 0; i < 3; i ++ )
      {
        he[(i+1)%3] = m_pMesh->	faceNextCcwHalfEdge(he[i]);
      }

      double l[3];
      for(int i = 0; i < 3; i ++ )
      {
		  M::CEdge * e = m_pMesh->halfedgeEdge( he[i] );
          l[i] = e->length();
      }

	  for( int i = 0; i < 3; i ++ )
	  {
		  if( l[(i+1)%3] + l[(i+2)%3] < l[(i+0)%3] )
			  std::cerr << "Warning: Triangle Inequality is violated" << std::endl;
	  }
	}

};






template<typename M>
void COperator<M>::_parameter_mu_2_angle( )
{
	for( M::MeshFaceIterator fiter( m_pMesh ); ! fiter.end(); fiter ++ )
	{
		M::CFace     * f = * fiter;

		M::CHalfEdge * hs[3];
		int i = 0;
		for( M::FaceHalfedgeIterator fhiter( f ); !fhiter.end(); fhiter ++ )
		{
			M::CHalfEdge * h = *fhiter;
			hs[i++] = h;
		}

		double ls[3];
		for( int i = 0; i < 3; i ++ )
		{
			M::CHalfEdge * h = hs[i];
			M::CVertex * ps = m_pMesh->halfedgeSource( h );
			M::CVertex * pt = m_pMesh->halfedgeTarget( h );

			std::complex<double> dz = pt->z() - ps->z();
			ls[i] = std::abs( dz + f->mu() * std::conj( dz ));
		}

		for( int i = 0; i < 3; i ++ )
		{
			double C = (ls[(i+1)%3] * ls[(i+1)%3] + ls[(i+2)%3] * ls[(i+2)%3] - ls[i] * ls[i])/(2*ls[(i+1)%3] * ls[(i+2)%3]);
			C = ( C > 1)? 1:C;
			C = ( C <-1)?-1:C;
			hs[(i+1)%3]->angle() = acos( C );
		}
	}
};

template<typename M>
void COperator<M>::_parameter_2_mu( )
{
	for( M::MeshFaceIterator fiter( m_pMesh ); ! fiter.end(); fiter ++ )
	{
		M::CFace * f = * fiter;

		int i = 0;
		M::CVertex * vs[3];
		for( M::FaceVertexIterator fviter( f ); !fviter.end(); fviter ++ )
		{
			M::CVertex * pV = *fviter;
			vs[i++] = pV;
		}

		std::complex<double> zs[3];
		std::complex<double> ws[3];
		
		for( int i = 0;i < 3; i ++ )
		{
			zs[i] = vs[i]->z();
			ws[i] = vs[i]->w();
		}

		std::complex<double> dz[2];
		std::complex<double> dw[2];

		for( int i = 0; i < 2 ; i ++ )
		{
			dz[i] = zs[i+1] - zs[0];
			dw[i] = ws[i+1] - ws[0];
		}

		std::complex<double> det = dz[0] * std::conj( dz[1] ) - dz[1] * std::conj( dz[0] );

		std::complex<double> a = std::conj( dz[1] ) * dw[0] - std::conj( dz[0] ) * dw[1];
		std::complex<double> b = -dz[1] * dw[0] + dz[0] * dw[1];

		f->mu() = b/a;

		//std::cout << f->mu() << std::endl;
	}
};


template<typename M>
void COperator<M>::_corner_angle_2_vertex_curvature( )
{

  for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); viter ++ )
  {
	  M::CVertex * v = *viter;
      double k  = (v->boundary() )? PI: PI * 2;
	  for( M::VertexInHalfedgeIterator vh( m_pMesh, v ); !vh.end();  ++vh )
      {
		  M::CHalfEdge * he = *vh;
          k -= he->angle();
      }
      v->k() = k;
  }
};

/*

template<typename M>
void COperator<M>::_parameter_mu_2_angle( )
{
	for( M::MeshFaceIterator fiter( m_pMesh ); ! fiter.end(); fiter ++ )
	{
		M::CFace * f = * fiter;

		M::CHalfEdge * hs[3];
		int i = 0;
		for( M::FaceHalfedgeIterator fhiter( f ); !fhiter.end(); fhiter ++ )
		{
			M::CHalfEdge * h = *fhiter;
			hs[i++] = h;
		}

		double ls[3];
		for( int i = 0; i < 3; i ++ )
		{
			M::CHalfEdge * h = hs[i];
			M::CVertex   * ps = m_pMesh->halfedgeSource( h );
			M::CVertex   * pt = m_pMesh->halfedgeTarget( h );

			std::complex<double> dz = pt->z() - ps->z();
			ls[i] = std::abs( dz + f->mu() * std::conj( dz ));
		}

		for( int i = 0; i < 3; i ++ )
		{
			double C = (ls[(i+1)%3] * ls[(i+1)%3] + ls[(i+2)%3] * ls[(i+2)%3] - ls[i] * ls[i])/(2*ls[(i+1)%3] * ls[(i+2)%3]);
			C = ( C > 1)? 1:C;
			C = ( C <-1)?-1:C;
			hs[(i+1)%3]->angle() = acos( C );
		}
	}
};

template<typename M>
void CStructure<M>::_parameter_2_mu( )
{
	for( M::MeshFaceIterator fiter( m_pMesh ); ! fiter.end(); fiter ++ )
	{
		M::CFace * f = * fiter;

		int i = 0;
		M::CVertex * vs[3];
		for( M::FaceVertexIterator fviter( f ); !fviter.end(); fviter ++ )
		{
			M::CVertex * pV = *fviter;
			vs[i++] = pV;
		}

		std::complex<double> zs[3];
		std::complex<double> ws[3];
		
		for( int i = 0;i < 3; i ++ )
		{
			zs[i] = vs[i]->z();
			ws[i] = vs[i]->w();
		}

		std::complex<double> dz[2];
		std::complex<double> dw[2];

		for( int i = 0; i < 2 ; i ++ )
		{
			dz[i] = zs[i+1] - zs[0];
			dw[i] = ws[i+1] - ws[0];
		}

		std::complex<double> det = dz[0] * std::conj( dz[1] ) - dz[1] * std::conj( dz[0] );

		std::complex<double> a = std::conj( dz[1] ) * dw[0] - std::conj( dz[0] ) * dw[1];
		std::complex<double> b = -dz[1] * dw[0] + dz[0] * dw[1];

		f->mu() = b/a;

		//std::cout << f->mu() << std::endl;
	}
};
*/

template<typename M>
void COperator<M>::_metric_2_diagonal_ratio()
{
	for( M::MeshEdgeIterator eiter( m_pMesh ); !eiter.end(); eiter ++ )
	{
		M::CEdge * pE = *eiter;			
		std::complex<double> rho = _diagonal_ratio( m_pMesh, pE );		
		pE->rho()= rho;
	}
};


template<typename M>
std::complex<double> COperator<M>::_diagonal_ratio( M* pM, typename M::CEdge * pE )
{
	std::complex<double > rho;

	if( pM->isBoundary( pE ))
	{
		_embed_one_face( pM, pE );

		M::CHalfEdge * pH = pM->edgeHalfedge( pE, 0 );
		M::CHalfEdge * pN = pM->faceNextCcwHalfEdge( pH );
		
		M::CVertex * pS = pM->halfedgeSource( pH );
		M::CVertex * pT = pM->halfedgeTarget( pH );
		M::CVertex * pL = pM->halfedgeTarget( pN );

		CPoint2 d0 = pT->huv() - pS->huv();
		CPoint2 d1 = CPoint2( 0, 2.0 * pL->huv()[1] );

		std::complex<double> c0( d0[0], d0[1] );
		std::complex<double> c1( d1[0], d1[1] );

		rho = c0/c1;
	}
	else
	{
		_embed_two_faces( pM, pE );

		M::CHalfEdge * pH = pM->edgeHalfedge( pE, 0 );
		M::CHalfEdge * pN = pM->faceNextCcwHalfEdge( pH );
		M::CHalfEdge * pD = pM->edgeHalfedge( pE, 1 );
		M::CHalfEdge * pW = pM->faceNextCcwHalfEdge( pD );
		
		M::CVertex * pS = pM->halfedgeSource( pH );
		M::CVertex * pT = pM->halfedgeTarget( pH );
		M::CVertex * pL = pM->halfedgeTarget( pN );
		M::CVertex * pR = pM->halfedgeTarget( pW );

		CPoint2 d0 = pT->huv() - pS->huv();
		CPoint2 d1 = pL->huv() - pR->huv();

		std::complex<double> c0( d0[0], d0[1] );
		std::complex<double> c1( d1[0], d1[1] );

		rho = c0/c1;
	}

	return rho;
};

//vertex A, vertex B are known, vertex C is unknown

template<typename M>
bool COperator<M>::_embed_third_vertex( M* pM, typename M::CVertex * A, typename M::CVertex * B, typename M::CVertex * C )
{
	//radius of the first circle
	double r1 = pM->vertexEdge(A,C)->length();
	//radius of the second circle
	double r2 = pM->vertexEdge(B,C)->length();
	//center of the first circle
	CPoint2 c1 = A->huv();
	//center of the second circle
	CPoint2 c2 = B->huv();


	CPoint2 i1;
	CPoint2 i2;

	int result =_circle_circle_intersection( c1[0], c1[1], r1, 
											 c2[0], c2[1], r2,
											 &i1[0], &i1[1],
											 &i2[0], &i2[1]);


	if( result )
	{
		if( cross( c2-c1, i1 - c1 ) > 0 )
			C->huv()  = i1;
		else
			C->huv()  = i2;
		return true;
	}

	
	// This should never happen, once this happends,
	// we use crude approximation

	if( ! result ) 
	{
		C->huv() = c1;
	}

	return true;
};


template<typename M>
void COperator<M>::_embed_two_faces( M * pM, typename M::CEdge * pE )
{
	M::CHalfEdge * pH = pM->edgeHalfedge( pE, 0 );
	M::CHalfEdge * pN = pM->faceNextCcwHalfEdge( pH );
	M::CHalfEdge * pD = pM->edgeHalfedge( pE, 1 );
	M::CHalfEdge * pW = pM->faceNextCcwHalfEdge( pD );
	
	M::CVertex * pS = pM->halfedgeSource( pH );
	M::CVertex * pT = pM->halfedgeTarget( pH );
	M::CVertex * pL = pM->halfedgeTarget( pN );
	M::CVertex * pR = pM->halfedgeTarget( pW );

	pS->huv() = CPoint2(0,0);
	pT->huv() = CPoint2( pE->length(), 0 );	
	_embed_third_vertex( pM, pS, pT, pL );
	_embed_third_vertex( pM, pT, pS, pR );
};

template<typename M>
void COperator<M>::_embed_one_face( M * pM, typename M::CEdge * pE )
{
	M::CHalfEdge * pH = pM->edgeHalfedge( pE, 0 );
	M::CHalfEdge * pN = pM->faceNextCcwHalfEdge( pH );
	
	M::CVertex * pS = pM->halfedgeSource( pH );
	M::CVertex * pT = pM->halfedgeTarget( pH );
	M::CVertex * pL = pM->halfedgeTarget( pN );

	pS->huv() = CPoint2(0,0);
	pT->huv() = CPoint2( pE->length(), 0 );	
	_embed_third_vertex( pM, pS, pT, pL );
};

template<typename M>
int COperator<M>::_circle_circle_intersection(double x0, double y0, double r0,
										double x1, double y1, double r1,
										double *xi, double *yi,
										double *xi_prime, double *yi_prime)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  d = sqrt((dy*dy) + (dx*dx));

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < abs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.  
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;

  return 1;
};

template<typename M>
void COperator<M>::_calculate_face_vertex_normal()
{

	for( M::MeshFaceIterator fiter( m_pMesh ); !fiter.end(); ++ fiter )
	{
		M::CFace * pF = *fiter;
		
		CPoint p[3];
		int k = 0;

		for( M::FaceVertexIterator fviter( pF ); !fviter.end(); fviter ++ )
		{
			M::CVertex * pV = *fviter;
			p[k++] = pV->point();
		}

		CPoint fn = (p[1] - p[0] )^(p[2] - p[0]);
		pF->normal() = fn/fn.norm();

	}

	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		CPoint n(0,0,0);

		for( M::VertexFaceIterator vfiter( v ); !vfiter.end(); ++ vfiter )
		{
			M::CFace * pF = *vfiter;
			n += pF->normal();
		}
		n = n/n.norm();
		v->normal() = n;
    }
};

template<typename M>
void COperator<M>::_calculate_face_vertex_area()
{

	for( M::MeshFaceIterator fiter( m_pMesh ); !fiter.end(); ++ fiter )
	{
		M::CFace * pF = *fiter;
		
		CPoint p[3];
		int k = 0;

		for( M::FaceVertexIterator fviter( pF ); !fviter.end(); fviter ++ )
		{
			M::CVertex * pV = *fviter;
			p[k++] = pV->point();
		}

		CPoint fn = (p[1] - p[0] )^(p[2] - p[0]);
		pF->area() = fn.norm()/2.0;
	}

	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		double s = 0;

		for( M::VertexFaceIterator vfiter( v ); !vfiter.end(); ++ vfiter )
		{
			M::CFace * pF = *vfiter;
			s += pF->area();
		}
		v->area() = s/3;
    }
};

template<typename M>
void COperator<M>::_normalize()
{
    CPoint s(0,0,0);
	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
      s = s + v->point();
    }

    s = s / m_pMesh->numVertices();

	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		CPoint p = v->point();
		p = p-s;
		v->point() = p;
    }
    double d = 0;

	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		CPoint p = v->point();
		for( int k = 0; k < 3; k ++ )
		{
			d = ( d > fabs(p[k]) )?d: fabs(p[k]);
		}
    }

	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		CPoint p = v->point();
		p = p/d;
		v->point() = p;
    }
};

template<typename M>
void COperator<M>::_uv_2_pos()
{
	for( M::MeshVertexIterator viter( m_pMesh ); !viter.end(); ++ viter )
    {
		M::CVertex * v = *viter;
		CPoint2 uv = v->uv();
		v->Point() = CPoint(uv[0], u[1], 0);
    }
};

};


#endif  _OPERATOR_H_
