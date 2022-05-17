/*!
*      \file DynamicMesh.h
*      \brief Dynamic Mesh Class for edge swap, face split, edge split
*
*      Dynamic Mesh Class for edge swap, face split, edge split
*	   \author David Gu
*      \date 10/07/2010
*
*/

#ifndef  _DYNAMIC_MESH_H_
#define  _DYNAMIC_MESH_H_

#include <map>
#include <vector>
#include <queue>

#include "Mesh/BaseMesh.h"
#include "Mesh/boundary.h"
#include "Mesh/iterators.h"


namespace MeshLib
{
  
/*-------------------------------------------------------------------------------------------------------------------------------------

	Dynamic Mesh Class

--------------------------------------------------------------------------------------------------------------------------------------*/
/*! \brief CDynamicMesh class : Dynamic mesh
* 
*  Mesh supports FaceSlit, EdgeSlit, EdgeSwap operations
*/
template<typename V, typename E, typename F, typename H>
class CDynamicMesh : public CBaseMesh<V,E,F,H>
{
public:
	/*! CDynamicMesh constructor */
	CDynamicMesh(){ m_vertex_id = 0; m_face_id = 0; };
	/*! CDynamicMesh destructor */
	~CDynamicMesh();

	//dynamic mesh editing
	/*! Split a Face to three small faces 
	 * \param pFace the face to be split
	 */
	V *  splitFace( F * pFace );
	/*! Split one edge to two edges 
	 * \param pEdge the edge to be split
	 */
	V *  splitEdge( E * pEdge );
	/*! Swap an edge
	* \param edge the edge to be swapped
	*/
	void swapEdge( E * edge );


protected:
	/*! attach halfeges to an edge
	* \param he0, he1 the halfedges
	* \param e edge
	*/
	void __attach_halfedge_to_edge( H * he0, H * he1, E * e );
	/*! next vertex id */
	int  m_vertex_id;
	/*! next face id */
	int  m_face_id;
	/*! next edge id */
	int  m_edge_id;

public:		/// added by YY

	/*!
	Read an .vef file.
	\param input the input vef file name
	*/
	void read_vef(  const char * input );
	/*!
	Write an .m file.
	\param output the output vef file name
	*/
	void write_vef( const char * output);
};

/*---------------------------------------------------------------------------*/

template<typename V, typename E, typename F, typename H>
CDynamicMesh<V,E,F,H>::~CDynamicMesh()
{
}


/*---------------------------------------------------------------------------*/

//insert a vertex in the center of a face, split the face to 3 faces

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex * CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::splitFace( CFace * pFace )
{

	m_vertex_id = 0;

	for( std::list<tVertex>::iterator viter =m_verts.begin(); viter != m_verts.end(); viter ++ )
	{
		tVertex  pV = *viter;
		m_vertex_id = ( m_vertex_id > pV->id() )?m_vertex_id:pV->id();
	}

	m_face_id   = 0;
	for( std::list<tFace>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		tFace  pF = *fiter;
		m_face_id = ( m_face_id > pF->id() )?m_face_id:pF->id();
	}


	CVertex * pV = createVertex( ++m_vertex_id );
	
	CVertex   *  v[3];
    CHalfEdge *  h[3];
	CHalfEdge *  hs[3];
	
	CEdge     *  eg[3];

	h[0] =  faceHalfedge( pFace );
	h[1] =  faceNextCcwHalfEdge( h[0] );
	h[2] =  faceNextCcwHalfEdge( h[1] );

	for( int i = 0; i < 3; i ++ )
	{
		v[i] = halfedgeTarget( h[i] );
		eg[i] = halfedgeEdge( h[i] );
		hs[i] = halfedgeSym( h[i] );
	}
	

	CFace * f = new CFace();
	assert( f != NULL );
	f->id() = ++m_face_id;
	m_faces.push_back( f );

	//create halfedges
	tHalfEdge hes[3];
	for(int i = 0; i < 3; i ++ )
	{
		hes[i] = new CHalfEdge;
		assert( hes[i] );
	}

	//linking to each other
	for(int i = 0; i < 3; i ++ )
	{
		hes[i]->he_next() = hes[(i+1)%3];
		hes[i]->he_prev() = hes[(i+2)%3];
	}

	//linking to face
	for(int i = 0; i < 3; i ++ )
	{
		hes[i]->face()   = f;
		f->halfedge()    = hes[i];
	}


	f = new CFace();
	assert( f != NULL );
	f->id() = ++m_face_id;
	m_faces.push_back( f );

	//create halfedges
	tHalfEdge hes2[3];

	for(int i = 0; i < 3; i ++ )
	{
		hes2[i] = new CHalfEdge;
		assert( hes2[i] );
	}

	//linking to each other
	for(int i = 0; i < 3; i ++ )
	{
		hes2[i]->he_next() = hes2[(i+1)%3];
		hes2[i]->he_prev() = hes2[(i+2)%3];
	}

	//linking to face
	for(int i = 0; i < 3; i ++ )
	{
		hes2[i]->face()   = f;
		f->halfedge()    = hes2[i];
	}

	CEdge * e[3];
	for( int i = 0; i < 3; i ++ )
	{
		e[i] = new CEdge();
		assert( e[i] );
		m_edges.push_back( e[i] );
	}

	__attach_halfedge_to_edge( h[1], hes[0], e[0] );
	__attach_halfedge_to_edge( hes[2], hes2[1], e[1] );
	__attach_halfedge_to_edge( h[2], hes2[0], e[2] );
	__attach_halfedge_to_edge( h[0], hs[0], eg[0] );
	__attach_halfedge_to_edge( hes[1], hs[1], eg[1] );
	__attach_halfedge_to_edge( hes2[2], hs[2], eg[2] );
	


	pV->halfedge() = h[1];


	h[1]->vertex() = pV;
	h[2]->vertex() = v[2];

	hes[0]->vertex() = v[0];
	hes[1]->vertex() = v[1];
	hes[2]->vertex() = pV;

	hes2[0]->vertex() = pV;
	hes2[1]->vertex() = v[1];
	hes2[2]->vertex() = v[2];

	v[0]->halfedge() = h[0];
	v[1]->halfedge() = hes[1];
	v[2]->halfedge() = hes2[2];
/*
	for( int i = 0; i < 3; i ++ )
	{
		v[i]->halfedge() = hs[i]->he_sym();
	}
*/
	return pV;

};
/*---------------------------------------------------------------------------*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::swapEdge( CEdge * edge )
{

  CHalfEdge * he_left   = edgeHalfedge( edge, 0 );
  CHalfEdge * he_right  = edgeHalfedge( edge, 1 );

  if( he_right == NULL ) 
  {
	  std::cerr <<"Ilegal: Boundary Edge Swap" << std::endl;
	  return;
  }

  CVertex * v1 = edgeVertex1( edge );
  CVertex * v2 = edgeVertex2( edge );
  
  if( v1 == v2 )
  {
	  std::cerr <<"Warning: Ilegal: Loop Edge Swap" << std::endl;
	  //return;
  }

  CHalfEdge * ph[6];

  ph[0] = he_left;
  ph[1] = faceNextCcwHalfEdge( ph[0] );
  ph[2] = faceNextCcwHalfEdge( ph[1] );


  ph[3] = he_right;
  ph[4] = faceNextCcwHalfEdge( ph[3] );
  ph[5] = faceNextCcwHalfEdge( ph[4] );

  CVertex * pv[4];

  pv[0] = halfedgeTarget( ph[0]);
  pv[1] = halfedgeTarget( ph[1]);
  pv[2] = halfedgeTarget( ph[2]);
  pv[3] = halfedgeTarget( ph[4]);

  int     pi[6];
  CEdge * pe[6];

  for( int i = 0; i < 6; i ++ )
  {
    CHalfEdge *   he = ph[i];
    CEdge     *   e  = halfedgeEdge( he );
    pe[i] = e;

    if( pe[i]->halfedge(0) == he )
    {
      pi[i] = 0;
    }
    else
    {
      assert( pe[i]->halfedge(1) == he );
      pi[i] = 1;
    }
  }

/*
  //remove edge from edge list of the original vertex
  CVertex * vb = (pv[0]->id() < pv[2]->id() )?pv[0]:pv[2];
  std::list<CEdge*> & ledges = (std::list<CEdge*> &) vb->edges();

  //add edge to the edge list of the new vertex
  CVertex * wb = (pv[1]->id() < pv[3]->id() )?pv[1]:pv[3];
  std::list<CEdge*> & wedges = (std::list<CEdge*> &) wb->edges();

  for( std::list<CEdge*>::iterator eiter = wedges.begin(); eiter != wedges.end(); eiter ++ )
  {
		CEdge * pE = *eiter;

		CVertex * v1 = edgeVertex1( pE );
		CVertex * v2 = edgeVertex2( pE );

		if(( v1 == pv[0] && v2 == pv[2] ) || (v1 == pv[2] )&& (v2 == pv[0]) )
		{
			std::cout << "DynamicMesh::SwapEdge::Warning Two edges share same both end vertices" << std::endl;
			//return;
		}
  }

*/

  //relink the vertices

  ph[0]->target() = pv[1];
  ph[1]->target() = pv[2];
  ph[2]->target() = pv[3];
  ph[3]->target() = pv[3];
  ph[4]->target() = pv[0];
  ph[5]->target() = pv[1];

  for( int i = 0; i < 6; i ++ )
  {
	  CHalfEdge * h = ph[i];
	  CVertex   * v = halfedgeTarget(h);
	  v->halfedge() = h;
  }
  
  
  //relink the edge-halfedge pointers

  ph[1]->edge() = pe[2];
  pe[2]->halfedge( pi[2] ) = ph[1];

  ph[2]->edge() = pe[4];
  pe[4]->halfedge( pi[4] ) = ph[2];

  ph[4]->edge() = pe[5];
  pe[5]->halfedge( pi[5] ) = ph[4];

  ph[5]->edge() = pe[1];
  pe[1]->halfedge( pi[1] ) = ph[5];
  

/*
  //remove edge from edge list of the original vertex
  std::list<CEdge*>::iterator pos = ledges.end();
  for( std::list<CEdge*>::iterator eiter = ledges.begin(); eiter != ledges.end(); eiter ++ )
  {
		CEdge * pE = *eiter;
		if( pE == edge ) 
		{
			pos = eiter;
			break;
		}
  }

  if( pos == ledges.end() )
  {
	  std::cout << "Error" << std::endl;
  }

  if( pos != ledges.end() )
	ledges.erase( pos );

  //add edge to the edge list of the new vertex
  wedges.push_back( edge );

  for(int i = 0; i < 6; i ++ )
  {
      CHalfEdge * he = ph[i];
      CHalfEdge * sh = halfedgeSym( he );
      assert( he->target() == sh->he_prev()->target() );
      assert( he->he_prev()->target() == sh->target() );
  }
*/
/*
  for(int i = 0; i < 6; i ++ )
  {
      CHalfEdge * he = ph[i];
	  CEdge     * pe = halfedgeEdge( he );
	  CVertex   * v1 = edgeVertex1( pe );
	  CVertex   * v2 = edgeVertex2( pe );
	  CEdge     * we = vertexEdge( v1, v2 );
	  if( pe != we )
	  {
		  std::cout << "Error" << std::endl;

		  for( int j = 0; j < 4; j ++ )
		  {
			  std::cout << pv[j]->id() << " ";
		  }
		  std::cout << std::endl;

		  for( std::list<CEdge*>::iterator eiter = ledges.begin(); eiter != ledges.end(); eiter ++ )
		  {
			  CEdge * e = *eiter;
			  CVertex * v1 = edgeVertex1( e );
			  CVertex * v2 = edgeVertex2( e );
			  std::cout << "(" << v1->id() << "," << v2->id() <<")" << std::endl;
		  }

		  std::cout << " Edge list " << std::endl;

		  for( std::list<CEdge*>::iterator eiter = wedges.begin(); eiter != wedges.end(); eiter ++ )
		  {
			  CEdge * e = *eiter;
			  CVertex * v1 = edgeVertex1( e );
			  CVertex * v2 = edgeVertex2( e );
			  std::cout << "(" << v1->id() << "," << v2->id() <<")" << std::endl;
		  }

		  write_m("test.m");
	  }
	  assert( pe == we );
  }
 
  static int id = 0;
  char name[1024];
  sprintf(name,"temp_%d.g", id++);

  write_g( name );
 */ 
  

};

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/


//insert a vertex in the center of an edge, split each neighboring face into 2 faces

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex * CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::splitEdge( CEdge * pEdge )
{

	CVertex * pV = createVertex( ++ m_vertex_id );


	CHalfEdge *  h[12];
	CHalfEdge *  s[6];
	CVertex   *  v[6];
	CEdge     * eg[6];
	
	h[0] = edgeHalfedge( pEdge, 0 );
	h[1] = faceNextCcwHalfEdge( h[0] );
	h[2] = faceNextCcwHalfEdge( h[1] );

	h[3] = edgeHalfedge( pEdge, 1 );
	h[4] = faceNextCcwHalfEdge( h[3] );
	h[5] = faceNextCcwHalfEdge( h[4] );


	CFace * f[4];
	f[0] = halfedgeFace( h[0] );
	f[1] = halfedgeFace( h[3] );

	for( int i = 0; i < 6; i ++ )
	{
		eg[i] = halfedgeEdge( h[i] );
		v[i] = halfedgeVertex(h[i]);
		s[i] = halfedgeSym( h[i] );
	}

	f[2] = new CFace();
	assert( f[2] != NULL );
	f[2]->id() = ++ m_face_id;
	m_faces.push_back( f[2] );

	//create halfedges
	for(int i = 6; i < 9; i ++ )
	{
		h[i] = new CHalfEdge;
		assert( h[i] );
	}

	//linking to each other
	for(int i = 0; i < 3; i ++ )
	{
		h[i+6]->he_next() = h[6+(i+1)%3];
		h[i+6]->he_prev() = h[6+(i+2)%3];
	}

	//linking to face
	for(int i = 6; i < 9; i ++ )
	{
		h[i]->face()   = f[2];
		f[2]->halfedge()= h[i];
	}


	f[3] = new CFace();
	assert( f[3] != NULL );
	f[3]->id() = ++m_face_id;
	m_faces.push_back( f[3] );

	//create halfedges
	for(int i = 9; i < 12; i ++ )
	{
		h[i] = new CHalfEdge;
		assert( h[i] );
	}

	//linking to each other
	for(int i = 0; i < 3; i ++ )
	{
		h[i+9]->he_next() = h[9+(i+1)%3];
		h[i+9]->he_prev() = h[9+(i+2)%3];
	}

	//linking to face
	for(int i = 9; i < 12; i ++ )
	{
		h[i]->face()   = f[3];
		f[3]->halfedge()    = h[i];
	}

	CEdge * e[3];

	for( int i = 0; i < 3; i ++ )
	{
		e[i] = new CEdge();
		e[i]->id() = ++ m_edge_id;
		m_edges.push_back( e[i] );
		assert( e[i] );
	}
	
	__attach_halfedge_to_edge(h[2], h[6] , e[0]);
	__attach_halfedge_to_edge(h[8], h[9] , e[1]);
	__attach_halfedge_to_edge(h[4], h[11], e[2]);

	__attach_halfedge_to_edge(h[0], h[3], eg[0]);
	__attach_halfedge_to_edge(h[1], s[1], eg[1]);
	__attach_halfedge_to_edge(h[5], s[5], eg[5]);

	__attach_halfedge_to_edge(h[7],  s[2], eg[2]);
	__attach_halfedge_to_edge(h[10], s[4], eg[4]);


	h[0]->vertex() = v[0];
	h[1]->vertex() = v[1];
	h[2]->vertex() = pV;
	h[3]->vertex() = pV;
	h[4]->vertex() = v[4];
	h[5]->vertex() = v[5];
	h[6]->vertex() = v[1];
	h[7]->vertex() = v[2];
	h[8]->vertex() = pV;
	h[9]->vertex() = v[2];
	h[10]->vertex()= v[4];
	h[11]->vertex()= pV;

	

	v[0]->halfedge() = h[0];
	v[1]->halfedge() = h[1];
	v[2]->halfedge() = h[7];
	v[4]->halfedge() = h[4];
	pV->halfedge()   = h[3];

	for( int k = 0; k < 4; k ++ )
	{
		CHalfEdge * pH = faceHalfedge( f[k] );
		for( int i = 0; i < 3; i ++ )
		{
			assert( pH->vertex() == pH->he_sym()->he_prev()->vertex() );
			pH = faceNextCcwHalfEdge( pH );
		}
	}
	return pV;	

};

/*---------------------------------------------------------------------------*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::__attach_halfedge_to_edge( CHalfEdge * he0, CHalfEdge * he1, CEdge * e )
{
	if( he0 == NULL )
	{
		e->halfedge(0 ) = he1;
		e->halfedge(1 ) = NULL;
	}
	else if( he1 == NULL )
	{
		e->halfedge(0 ) = he0;
		e->halfedge(1 ) = NULL;
	}
	else
	{
		e->halfedge(0 ) = he0;
		e->halfedge(1 ) = he1;
	}

	if( he0 != NULL )
		he0->edge() = e;
	if( he1 != NULL )
		he1->edge() = e;

};


/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::read_vef( const char * input )
{
	std::fstream is( input, std::fstream::in );

	if( is.fail() )
	{
		fprintf(stderr,"Error in opening file %s\n", input );
		return;
	}

	char buffer[MAX_LINE];
	int id;
	std::map<int, tEdge>	m_map_edge;		// map eid to edge

	while( is.getline(buffer, MAX_LINE )  )
	{		

		std::string line( buffer );
		line = strutil::trim( line );
		strutil::Tokenizer stokenizer( line, " \t\r\n" );
		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
	
		// create vertex
		if( token == "Vertex"  )		
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			id = strutil::parseString<int>(token);
			CPoint p;
			for( int i = 0 ; i < 3; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				p[i] = strutil::parseString<float>(token);
			}
		
			// create vertex
			CVertex * v = new CVertex();
			assert( v != NULL );
			m_verts.push_back( v );
			m_map_vert.insert( std::pair<int,CVertex*>(id,v));
			v->id() = id;
			v->point() = p;
			v->boundary() = false;
			v->halfedge() = NULL;

			// read attributes
			if( ! stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();
			int sp = (int) token.find("{");
			int ep = (int) token.find("}");
			if( sp >= 0 && ep >= 0 )
			{
				v->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}

		// create edge
		else if( token == "Edge" )		
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			id = strutil::parseString<int>(token);
			int	vid[2];
			CVertex * ev[2];
			stokenizer.nextToken();
			token = stokenizer.getToken();
			vid[0] = strutil::parseString<int>( token );
			ev[0] = idVertex(vid[0]);
			stokenizer.nextToken();
			token = stokenizer.getToken();
			vid[1] = strutil::parseString<int>( token );
			ev[1] = idVertex(vid[1]);

			// create edge 
			CEdge * e = new CEdge();	assert( e != NULL );
			e->id() = id;
			m_edges.push_back( e );
			m_map_edge.insert( std::pair<int,CEdge*>(id,e));

			// create halfedges & link to edge
			CHalfEdge * he[2];
			for (int k=0; k<2; k++)
			{
				he[k] = new CHalfEdge();	assert(he[k]);
				he[k]->vertex() = ev[1-k];
				he[k]->edge() = e;
				he[k]->face() = NULL;
				e->halfedge(k) = he[k];
			}

			// read attributes
			if( !stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();	
			int sp = (int) token.find("{");
			int ep = (int) token.find("}");
			if( sp >= 0 && ep >= 0 )
			{
				  e->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}

		// create face
		else if( token == "Face" )		
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			id = strutil::parseString<int>(token);
			std::vector<tHalfEdge>	f_he;		
			while( stokenizer.nextToken() )
			{
				token = stokenizer.getToken();
				int	he_ind;
				if	( strutil::startsWith( token, "+" ) )		he_ind = 0;
				else if ( strutil::startsWith( token, "-" ) )	he_ind = 1;
				else											break;
				std::string str_eid = strutil::trim( token, "+-" );
				int eid = strutil::parseString<int>(str_eid);
				tEdge e = m_map_edge[eid];		assert( e );
				f_he.push_back( edgeHalfedge(e, he_ind) );
			}

			// create face & link he
			CFace * f = new CFace();
			assert( f != NULL );
			f->id() = id;
			m_faces.push_back( f );
			m_map_face.insert( std::pair<int,tFace>(id,f) );
			size_t	nhe = f_he.size();
			for ( size_t k=0; k<nhe; k++)
			{
				CHalfEdge * he = f_he[k]; 
				if ( 0==k )	f->halfedge() = he;
				he->face() = f;
				he->he_next() = f_he[ (k+1)%nhe ];
				he->he_prev() = f_he[ (k-1+nhe)%nhe ];
				//CVertex * v = he->vertex();
				CVertex * v = halfedgeVertex(he);
				if ( NULL == v->halfedge() )	v->halfedge() = he;	// temporarily
			}

			// read attributes
			if( strutil::startsWith( token, "{" ) )
			{
				f->string() = strutil::trim( token, "{}" );
			}
			continue;
		}

		//read corner attributes
		else if( token == "Corner" ) 
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			int vid = strutil::parseString<int>( token );
			stokenizer.nextToken();
			token = stokenizer.getToken();
			int fid = strutil::parseString<int>( token );

			CVertex * v = idVertex( vid );
			CFace   * f = idFace( fid );
			tHalfEdge he = corner( v, f );

			if( !stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();	
			int sp = (int) token.find("{");
			int ep = (int) token.find("}");
			if( sp >= 0 && ep >= 0 )
			{
				he->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}

	}


	// check edge: remove non-matched he (i.e. bnd he's sym), remove singular e, and mark bnd v
	std::list<tEdge> singular_edges;
	for(std::list<tEdge>::iterator eiter= m_edges.begin() ; eiter != m_edges.end() ; ++ eiter )
	{
		tEdge e = *eiter;
		assert( NULL!=e->halfedge(0) && NULL!=e->halfedge(1) );
		for (int k=0; k<2; k++)
		{
			if ( NULL == e->halfedge(k)->face() )
			{
				delete e->halfedge(k);
				e->halfedge(k) = NULL;
			}
		}
		if ( NULL==e->halfedge(0) && NULL==e->halfedge(1) )		// singular e; remove
		{
			singular_edges.push_back( e );
		}
		else if ( NULL==e->halfedge(0) )			// bnd; but need swap [0] and [1] to make sure [0] is not null;
		{
			// this should not happen by write_vef ...
			e->halfedge(0) = edgeHalfedge(e,1);
			e->halfedge(1) = NULL;
			tHalfEdge he = edgeHalfedge(e,0);
			he->source()->boundary() = true;
			he->target()->boundary() = true;
		}
		else if ( NULL==e->halfedge(1) )			// bnd;
		{
			tHalfEdge he = edgeHalfedge(e,0);
			he->source()->boundary() = true;
			he->target()->boundary() = true;
		}
		else			// inn e; need make sure vertex(0)->id() < vertex(1)->id()
		{
			// this should not happen by write_vef ...
			tHalfEdge he = edgeHalfedge(e,0);
			if ( he->source()->id() > he->target()->id() )		// need swap [0] and [1]
			{
				e->halfedge(0) = e->halfedge(1);
				e->halfedge(1) = he;
			}
		}
	}
	for( std::list<tEdge>::iterator  eiter = singular_edges.begin() ; eiter != singular_edges.end(); ++ eiter )
	{
		tEdge e = *eiter;
		m_edges.remove( e );
		delete e;
	}

	// check vertex: remove singular v
	std::list<tVertex> dangling_verts;
	for(std::list<tVertex>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		tVertex  v = *viter;
		if( vertexHalfedge(v) != NULL ) continue;
		dangling_verts.push_back( v );
	}
	for( std::list<tVertex>::iterator  viter = dangling_verts.begin() ; viter != dangling_verts.end(); ++ viter )
	{
		tVertex v = *viter;
		m_verts.remove( v );
		delete v;
	}

	//Arrange the boundary half_edge of boundary vertices, to make its halfedge to be the most ccw in half_edge
	for(std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		CVertex *     v = *viter;
		if( !v->boundary() ) continue;
		CHalfEdge * he = vertexMostCcwInHalfEdge( v );
		while( he->he_sym() != NULL )
		{
			he =  vertexNextCcwInHalfEdge ( he );
		}
		v->halfedge() = he;
	}

	//read in the traits
	for(std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		CVertex *     v = *viter;
		v->_from_string();
	}
	for(std::list<CEdge*>::iterator eiter = m_edges.begin();  eiter != m_edges.end() ; ++ eiter )
	{
		CEdge *     e = *eiter;
		e->_from_string();
	}
	for(std::list<CFace*>::iterator fiter = m_faces.begin();  fiter != m_faces.end() ; ++ fiter )
	{
		CFace *     f = *fiter;
		f->_from_string();
	}
	for( std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;
		CHalfEdge * pH  = faceMostCcwHalfEdge( pF );
		do{
			pH->_from_string();
			pH = faceNextCcwHalfEdge( pH );
		}while( pH != faceMostCcwHalfEdge(pF ) );
	}

	is.close();
};

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CDynamicMesh<CVertex,CEdge,CFace,CHalfEdge>::write_vef( const char * output )
{
	//write traits to string
	for( std::list<CVertex*>::iterator viter=m_verts.begin(); viter != m_verts.end(); viter ++ )
	{
		CVertex * pV = *viter;
		pV->_to_string();
	}
	for( std::list<CEdge*>::iterator eiter=m_edges.begin(); eiter != m_edges.end(); eiter ++ )
	{
		CEdge * pE = *eiter;
		pE->_to_string();
	}
	for( std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;
		pF->_to_string();
	}
	for( std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;
		CHalfEdge * pH  = faceMostCcwHalfEdge( pF );
		do{
			pH->_to_string();
			pH = faceNextCcwHalfEdge( pH );
		}while( pH != faceMostCcwHalfEdge(pF ) );
	}

	std::fstream _os( output, std::fstream::out );
	if( _os.fail() )
	{
		fprintf(stderr,"Error is opening file %s\n", output );
		return;
	}

	for( std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;
		_os << "Vertex " << v->id();
		for( int i = 0; i < 3; i ++ )
		{
			_os << " " << v->point()[i];
		}
		if( v->string().size() > 0 )
		{
			_os << " " <<"{"<< v->string() << "}";
		}
		_os << std::endl;
	}
	for( std::list<CEdge*>::iterator eiter = m_edges.begin(); eiter != m_edges.end(); eiter ++ )
	{
		tEdge e = *eiter;
		_os << "Edge "<<  e->id() << " " << edgeVertex1(e)->id() <<" " << edgeVertex2(e)->id() << " ";
		if( e->string().size() > 0 )
		{
			_os << "{" << e->string() << "}" << std::endl;
		}
		_os << std::endl;
	}
	for( std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		tFace f = *fiter;
		_os << "Face " << f->id();
		tHalfEdge he = faceHalfedge( f );
		do{
			tEdge e = halfedgeEdge(he);
			if ( he == edgeHalfedge(e, 0) )		// pos
				_os << " +" <<  e->id();
			else							// neg
				_os << " -" <<  e->id();
			he = halfedgeNext( he );
		}while( he != f->halfedge() );
		if( f->string().size() > 0 )
		{
			_os << " " << "{"<< f->string() << "}";
		}
		_os << std::endl;
	}
	for( std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++  )
	{
		tFace f = *fiter;
		tHalfEdge he = faceHalfedge( f );
		do{
  			if( he->string().size() > 0 )
			  {
				  _os << "Corner "<< he->vertex()->id() << " " << f->id() << " ";
				  _os << "{" << he->string() << "}" << std::endl;
			  }
			  he = halfedgeNext( he );
		}while( he != f->halfedge() );
	}

	_os.close();


};

/*---------------------------------------------------------------------------*/


}
#endif  _DYNAMIC_MESH_H_