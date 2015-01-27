#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace
{
  	template< typename TIterator >
	void print_lines( std::vector< std::string >& lines, TIterator begin, TIterator end )
	{
		for ( ; begin != end; ++begin )
			std:: cout << lines[ *begin ] << std::endl;	
	}
}

template< typename TReadLinesPolicy
		, typename TSortingPolicy >
class Sorter
{
public:
	Sorter( const std::string& filename, size_t num_lines, size_t insertion_threshold, bool reverse = false ):
		m_filename( filename )
	,	m_is_reverse( reverse )
	,	m_num_lines( num_lines )
	,   m_insertion_threshold( insertion_threshold )
	{}

	~Sorter( ) {}

	void sort( )
	{
		TReadLinesPolicy::read_lines( m_filename, m_num_lines, m_lines );

		m_sort_policy.sort( m_lines, m_insertion_threshold );

		print( );
	}

	void print( )
	{
		const auto& sorted_pos = m_sort_policy.get_sorted_pos( );
		if ( ! m_is_reverse )
			print_lines( m_lines, sorted_pos.begin(), sorted_pos.end() );
		else
			print_lines( m_lines, sorted_pos.rbegin(), sorted_pos.rend( ) );
	} 

private:

	std::string 	 			m_filename;
	std::vector< std::string >  m_lines;
	bool						m_is_reverse;
	size_t 						m_num_lines;
	size_t 						m_insertion_threshold;

	TReadLinesPolicy 			m_read_policy;
	TSortingPolicy   			m_sort_policy;
};