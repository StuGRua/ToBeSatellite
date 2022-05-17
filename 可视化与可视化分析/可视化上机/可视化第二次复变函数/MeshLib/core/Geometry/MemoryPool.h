#ifndef  _MEMORY_POOL_H_
#define  _MEMORY_POOL_H_

namespace MeshLib
{

template<typename T>
class CMPool
{
public:
	
	CMPool<T>( size_t size=4096 )
	{
		m_size = size;
		T* pT = new T[m_size];
		if( pT == NULL )
		{
			std::cout << "Error in allocation in memory pool" << std::endl;
		}
		else
		{
			m_pool.push_back( pT );
		}

		m_free = NULL;

		for( size_t i = 0; i < size; i ++ )
		{
			pT[i].next() = &pT[(i+1)%size]; pT[(i+1)%size].prev() = &pT[i];
		}
		m_free = &pT[0];	
		m_used = NULL;
	};

	~CMPool<T>()
	{
		if( m_pool.empty()) return;

		for( size_t i = 0; i < m_pool.size(); i ++ )
		{
			T * pT = m_pool[i];
			delete []pT;
		}
		m_pool.clear();
		
		m_free = NULL;
		m_used = NULL;

	};

	T * allocate()
	{
		if( m_free->next() != m_free && m_free->prev() != m_free )
		{
			T * pT = m_free;
			pT->next()->prev() = pT->prev();
			pT->prev()->next() = pT->next();
			m_free = m_free->next();
			
			if( m_used == NULL )
			{
				m_used = pT;
				m_used->prev() = m_used;
				m_used->next() = m_used;
			}
			else
			{
				pT->next() = m_used->next();
				pT->prev() = m_used;
				pT->next()->prev() = pT;
				pT->prev()->next() = pT;
			}
			return pT;
		}

		std::cout << ">>>>>>>>>> Memory allocation again! <<<<<<<<<<" << std::endl;
		m_size *= 2;
		T* pT = new T[m_size];
		if( pT == NULL )
		{
			std::cout << "Error in allocation in memory pool" << std::endl;
		}
		else
		{
			m_pool.push_back( pT );
		}
		
		for( size_t i = 0; i < m_size; i ++ )
		{
			T * pC = & pT[i];
			pC->next() = m_free;
			pC->prev() = m_free->prev();
			pC->next()->prev() = pC;
			pC->prev()->next() = pC;
			m_free = pC;
		}

		{
			T * pT = m_free;
			pT->next()->prev() = pT->prev();
			pT->prev()->next() = pT->next();
			m_free = m_free->next();
			
			if( m_used == NULL )
			{
				m_used = pT;
				m_used->prev() = m_used;
				m_used->next() = m_used;
			}
			else
			{
				pT->next() = m_used->next();
				pT->prev() = m_used;
				pT->next()->prev() = pT;
				pT->prev()->next() = pT;
			}
		}
		return pT;


	};

	void delocate( T * t)
	{

		if( m_used->next() != m_used && m_used->prev() != m_used )
		{
			if( t == m_used ) m_used = t->next();

			//more than one element in the list of m_used
			t->next()->prev() = t->prev();
			t->prev()->next() = t->next();
		}
		else
		{	
			//only one element in the list of m_used
			assert( m_used == t );
			m_used = NULL;
		}

		if( m_free != NULL )
		{
			t->next() = m_free->next();
			t->prev() = m_free;
			t->next()->prev() = t;
			t->prev()->next() = t;
		}
		else
		{
			m_free = t;
			m_free->next() = m_free;
			m_free->prev() = m_free;
		}
	};

protected:

	T * m_free;
	T * m_used;
	size_t m_size;
	std::vector<T*> m_pool;
};

}

#endif