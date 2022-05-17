/*!
*      \file Edge.h
*      \brief Base class of edge
*	   \author David Gu
*      \date 10/07/2010
*
*/


#ifndef _MESHLIB_EDGE_H_
#define _MESHLIB_EDGE_H_

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string>

namespace MeshLib{

class CHalfEdge;
class CVertex;

/*!
\brief CEdge class, which is the base class of all kinds of edge classes
*/
class CEdge
{
public:
	/*!
		CEdge constructor, set both halfedge pointers to be NULL.
	*/
	CEdge(){ m_halfedge[0] = NULL; m_halfedge[1] = NULL; };
	/*!
		CEdge destructor.
	*/
	~CEdge(){};
	/*!
		Edge ID
	 */
	int & id() { return m_id; };

	/*!
		The halfedge attached to the current edge
		\param id either 0 or 1
		\return the halfedge[id]
	*/
	CHalfEdge * & halfedge( int id ) { assert( 0<=id && id < 2 ); return m_halfedge[id];};
	/*!	
		whether the edge is on the boundary.
	*/
	bool		  boundary() { return (m_halfedge[0] == NULL && m_halfedge[1] != NULL ) || (m_halfedge[0] != NULL && m_halfedge[1] == NULL ); };
	/*!
		The dual halfedge to the input halfedge
		\param he halfedge attached to the current edge
		\return the other halfedge attached to the current edge
	*/
	CHalfEdge * & other( CHalfEdge * he ) { return (he != m_halfedge[0] )?m_halfedge[0]:m_halfedge[1]; };
    /*!
		The string of the current edge.
	*/
	std::string & string() { return m_string; };
	/*!
		Read the traits from the string.
	*/
	void _from_string() {};
	/*!
		Save the traits to the string.
	*/
	void _to_string() {};
protected:
	/*!
		Pointers to the two halfedges attached to the current edge.
	*/
	CHalfEdge      * m_halfedge[2];
	/*!
		The string associated to the current edge.
	*/
    std::string      m_string;
	/*!
		Edge ID
	 */
	int				 m_id;
};





}//name space MeshLib

#endif //_MESHLIB_EDGE_H_ defined