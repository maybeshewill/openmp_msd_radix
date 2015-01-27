#include <limits>

#include <omp.h>

#include "radix.h"

void Radix::init( size_t num_lines, size_t switch_to_insertion )
{
    m_switch_to_insertion_sort = switch_to_insertion;

    m_alphabet = std::vector< char_type >( num_lines, '\0' );
    m_sorted_pos = std::vector< size_t >( num_lines, 0 );
    m_original_pos = std::vector< size_t >( num_lines, 0 );
        
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( size_t i = 0; i < num_lines; ++i )
    {
        m_original_pos[ i ] = i;
    }
}

void Radix::sort( const std::vector< std::string >& lines, size_t switch_to_insertion )
{
    size_t lines_num = lines.size( );
    init( lines_num, switch_to_insertion );
    radix_sort( lines, 0, lines_num, 0 );
}

void Radix::step( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth )
{
	if ( begin > end )
		return;

	if ( end - begin < m_switch_to_insertion_sort )
	{
		insertion_sort( lines, begin, end, depth );
	}
	else
	{
		radix_sort( lines, begin, end, depth );
	}

	return;
}

void Radix::radix_sort( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth )
{
    if ( begin > end )
        return;

    if ( end - begin < m_switch_to_insertion_sort )
    {
        insertion_sort( lines, begin, end, depth );
        return;
    }

    size_t counter[ std::numeric_limits< char_type >::max( ) ] = {0};

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( size_t i = begin; i < end; ++i )
    {
        m_alphabet[ i ] = lines[ m_original_pos[ i ] ][ depth ];
    }

    for ( size_t i = begin; i < end; ++i )
    {
        ++counter[ static_cast< size_t >( m_alphabet[ i ] ) ];
    }

    size_t WTF = 0;
    for ( size_t i = 0; i < static_cast< size_t >( std::numeric_limits< char_type >::max() ); ++i )
    {
        std::swap( counter[ i ], WTF );
        WTF += counter[ i ];
    }

    for ( size_t i = begin; i < end; ++i )
    {
        m_sorted_pos[ counter[ static_cast< size_t >( lines[ m_original_pos[ i ] ][ depth ] ) ]++ ] = m_original_pos[ i ];    
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( size_t i = begin; i < end; ++i )
    {
        m_original_pos[ i ] = m_sorted_pos[ i - begin ];
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(dynamic)
    #endif
    for ( size_t i = 1; i < static_cast< size_t >( std::numeric_limits< char_type >::max() ); ++i )
    {
        if ( counter[ i ] - counter[ i - 1 ] >= 1)
        {
            step( lines, begin + counter[ i - 1 ], begin + counter[ i ], depth + 1 );
        }
    }
}

void Radix::insertion_sort( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth )
{
    StringCompare comparator( depth );
    for ( size_t i = begin; i < end; ++i )
    {
        for ( size_t j = i; j > begin; --j )
        {
            if ( comparator( lines[ m_original_pos[ j ] ], lines[ m_original_pos[ j - 1 ] ] ) )
            {
                std::swap( m_original_pos[ j ], m_original_pos[ j - 1 ] );
            }
        }
    }
    }