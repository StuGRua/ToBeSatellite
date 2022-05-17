/*!
*      \file parser.h
*      \brief Parse the trait strings of vertex, edge, halfedge , face etc.
*	   \author David Gu
*      \date 10/07/2010
*
*/

#ifndef _MESHLIB_PARSER_H_
#define _MESHLIB_PARSER_H_

#include <string>
#include <assert.h>
#include <list>
#include <sstream>

namespace MeshLib
{

/*!
 *	\brief CToken  class, key=(value), e.g. uv=(x y)
*/

class CToken
{
public:
	/*! key of the token */
	std::string m_key;
	/*! value of the token */
	std::string m_value;
};

/*!
 *	\brief CParser class
*/

class CParser
{
public:
	/*!
	 *	\brief CParser constructor
	 *  \param str input string
	 */
	CParser( const std::string & str)
	{
		//copy string
		unsigned int i;
		for(  i = 0; i < str.length(); i ++ )
		{
			m_line[i] = str.c_str()[i];
		}
		m_line[i] = 0;

		m_pt = m_line;
		
		//while not reaching the end
		while( !end() )
		{
			skip_blank();
			if( end() ) break;

			//copy key

			char * pkey = m_key;
			char   ch = next_char();

			while( ch != ' ' && ch != '=' && !end() )
			{
				*pkey ++ = ch;
				ch = next_char();
			}
			if( ch != '=' && ch != ' ')
				*pkey++ = ch;

			*pkey = 0;

			if( ch == ' ' )
			{
				skip_blank();
			}

			if( ch != '=' )
			{
				CToken *	tk = new CToken;
				assert(tk);
				tk->m_key  = std::string( m_key );
				
				m_tokens.push_back( tk );
				continue;
			}

			if( end() ) break;

			ch = next_char();

			while( ch != '(' ) ch = next_char();

			char * pvalue = m_value;

			while( ch != ')' && !end() )
			{
				*pvalue ++ = ch;
				ch = next_char();
			}
			*pvalue++ = ch;
			*pvalue  = 0;

			CToken *	tk = new CToken;
			assert(tk);
			tk->m_key   = std::string( m_key   );
			tk->m_value = std::string( m_value );
			
			m_tokens.push_back( tk );
			
		}

	};

	/*!
	 *	CParser Destructor
	 */
	~CParser()
	{
	  //release all the tokens

	  for( std::list<CToken*>::iterator titer = m_tokens.begin(); titer != m_tokens.end(); titer ++ )
	  {
		  CToken * pT = *titer;
		  delete pT;
	  }
	  m_tokens.clear();
	};

	/*!
	 *	List of tokens extracted from the string
	 */
	std::list<CToken*> & tokens() { return m_tokens; };
	
	/*!
	 *	Convert the list of tokens to a string
	 *  \param str the output string
	 */
	void _toString( std::string & str )
	{
		std::stringstream iss;

		for( std::list<CToken*>::iterator iter = m_tokens.begin() ; iter != m_tokens.end(); ++ iter )
		{
			  CToken * token = *iter;
			  if( iss.str().length() > 0 ) iss << " ";
			  if( token->m_value.empty() )
			  {
				iss << token->m_key;
			  }
			  else
			  {
				iss << token->m_key << "=" << token->m_value;			  
			  }
		}

		str = iss.str();
	};
	/*!
	 *	Remove the token key=(...) from the current string
	 *  \param key the key to the token to be removed
	 */
	void _removeToken( const std::string & key )	
	{
		for( std::list<CToken*>::iterator iter = m_tokens.begin() ; iter != m_tokens.end(); ++ iter )
		{
			  CToken * token = *iter;
			  if( token->m_key == key )
			  {
				  m_tokens.erase( iter );
				  return;
			  }
		}
	};

private:

	/*!
	 *	get the next char in the current string
	 */
	char next_char()
	{
		char ch= *m_pt;
		m_pt++;
		return ch;
	};
	/*!
	 *	skip blank spaces
	 */
	void skip_blank()
	{
		while( *m_pt == ' ' ) m_pt++;
	};
	/*!
	 *	verify if we 
	 */
	bool end()
	{
		return ( (*m_pt) == 0 );
	};
	/*!
	 *	list of tokens
	 */
	std::list<CToken*> m_tokens;
	
	/*!
	 * The buffer to contain the string
	 */
	char m_line[1024];
	/*!
	 *	current key
	 */
	char m_key[1024];
	/*!
	 *	current value
	 */
	char m_value[1024];
	/*!
	 *	current pointer to the char buffer
	 */
	char * m_pt;
};


}; //namespace 
#endif