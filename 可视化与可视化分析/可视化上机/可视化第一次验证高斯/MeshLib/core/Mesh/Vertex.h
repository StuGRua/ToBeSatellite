/*!
*      \file Vertex.h
*      \brief Base class of vertex
*	   \author David Gu
*      \date 10/07/2010
*
*/

#ifndef  _MESHLIB_VERTEX_H_
#define  _MESHLIB_VERTEX_H_

#include <stdlib.h>
#include <string>
#include <list>
#include "../Geometry/Point.h"
#include "../Geometry/Point2.h"
#include "HalfEdge.h"

namespace MeshLib{

  class CHalfEdge;

  /*!
  \brief CVertex class, which is the base class of all kinds of vertex classes
  */

  class CVertex
  {
  public:
	  /*!
	  CVertex constructor
	  */
      CVertex(){ m_halfedge = NULL; m_boundary = false; };
	  /*!
	  CVertex destructor 
	  */
    ~CVertex(){};

	/*! The point of the vertex
	*/
    CPoint & point()    { return m_point;};
	/*! The normal of the vertex
	*/
    CPoint & normal()   { return m_normal; };
	/*! The texutre coordinates of the vertex
	*/
	CPoint2 & uv()       { return m_uv; };

	/*! The most counter clockwise outgoing halfedge of the vertex .
	*/
    CHalfEdge * most_ccw_out_halfedge();
	/*! The most clockwise outgoing halfedge of the vertex .
	*/
    CHalfEdge * most_clw_out_halfedge();
	/*! The most counter clockwise incoming halfedge of the vertex. 
	*/
    CHalfEdge * most_ccw_in_halfedge();
	/*! The most clockwise incoming halfedge of the vertex. 
	*/
    CHalfEdge * most_clw_in_halfedge();

	/*! One incoming halfedge of the vertex .
	*/
    CHalfEdge * & halfedge() { return m_halfedge; };
	/*! the string of the vertex. 
	*/
	std::string & string() { return m_string;};
	/*! Vertex id. 
	*/
    int  & id() { return m_id; };
	/*! Whether the vertex is on the boundary. 
	*/
    bool & boundary() { return m_boundary;};
    /*! Convert vertex traits to string. 
	*/
	void _to_string()   {};
	/*! Read traits from the string. 
	*/
	void _from_string() {};

	/*!	Adjacent edges, temporarily used for loading the mesh
	 */
	std::list<CEdge*> & edges() { return m_edges; };
  protected:

    /*! Vertex ID. 
	*/
    int    m_id ;
    /*! Vertex position point. 
	*/
    CPoint m_point;
	/*! Normal at the vertex. 
	*/
    CPoint m_normal;
	/*! Texture coordinates of the vertex. 
	*/
	CPoint2 m_uv;
	/*! The most CCW incoming halfedge of the vertex.
	*/
    CHalfEdge *     m_halfedge;
	/*! Indicating if the vertex is on the boundary. 
	*/
    bool            m_boundary;
	/*! The string of the vertex, which stores the traits information. 
	*/
	std::string     m_string;

	/*! List of adjacent edges, such that current vertex is the end vertex of the edge with smaller id
	 */
	std::list<CEdge*> m_edges;

  }; //class CVertex


/*! \brief The most counter clockwise incoming halfedge of the vertex
 *  \return the most CCW in halfedge
*/
inline CHalfEdge *  CVertex::most_ccw_in_halfedge()  
{ 
	//for interior vertex
	if( !m_boundary )
	{
		return m_halfedge; //current half edge is the most ccw in halfedge 
	}

	//for boundary vertex
	CHalfEdge * he = m_halfedge->ccw_rotate_about_target();
	//rotate to the most ccw in halfedge
	while( he != NULL )
	{
		m_halfedge = he;
		he = m_halfedge->ccw_rotate_about_target();
	}
	// the halfedge of the vertex becomes the most ccw in halfedge
	return m_halfedge;
};

//most clockwise in halfedge

inline CHalfEdge *  CVertex::most_clw_in_halfedge()  
{ 
	//for interior vertex 
	if( !m_boundary )
	{
		return most_ccw_in_halfedge()->ccw_rotate_about_target(); //the most ccw in halfedge rotate ccwly once to get the most clw in halfedge
	}
	//for boundary vertex
	CHalfEdge * he = m_halfedge->clw_rotate_about_target();
	//rotate to the most clw in halfedge
	while( he != NULL )
	{
		m_halfedge = he;
		he = m_halfedge->clw_rotate_about_target();
	}

	return m_halfedge;
};

//most counter clockwise out halfedge

inline CHalfEdge *  CVertex::most_ccw_out_halfedge()  
{ 
	//for interior vertex
	if( !m_boundary )
	{
		return most_ccw_in_halfedge()->he_sym(); //most ccw out halfedge is the dual of the most ccw in halfedge
	}

	//for boundary vertex
	CHalfEdge * he = m_halfedge->he_next();
	//get the out halfedge which is the next halfedge of the most ccw in halfedge
	CHalfEdge * ne = he->ccw_rotate_about_source();
	//rotate ccwly around the source vertex
	while( ne != NULL )
	{
		he = ne;
		ne = he->ccw_rotate_about_source();
	}

	return he;
};

//most clockwise out halfedge

inline CHalfEdge * CVertex::most_clw_out_halfedge()  
{ 
	//for interior vertex
	if( !m_boundary )
	{
		return most_ccw_out_halfedge()->ccw_rotate_about_source();  //most ccw out halfedge rotate ccwly once about the source
	}
	//get one out halfedge
	CHalfEdge * he = m_halfedge->he_next();
	//rotate the out halfedge clwly about the source
	CHalfEdge * ne = he->clw_rotate_about_source();
	
	while( ne != NULL )
	{
		he = ne;
		ne = he->clw_rotate_about_source();
	}

	return he;
};



}//name space MeshLib

#endif //_MESHLIB_VERTEX_H_defined