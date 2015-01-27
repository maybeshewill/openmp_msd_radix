#pragma once

#include <string>
#include <vector>

class StringCompare
{
public:
    StringCompare( size_t depth ) : m_depth( depth ) {}

    inline bool operator()( const std::string& first, const std::string& second )
    {
        return first.compare( m_depth, first.length() - m_depth, second, m_depth, second.length( ) - m_depth ) < 0;
    }
private:
    size_t m_depth;
};

class Radix
{
public:
    typedef std::string::value_type char_type; 

	void sort( const std::vector< std::string >& lines, size_t switch_to_insertion );

    const std::vector< size_t >& get_sorted_pos( ) const { return m_original_pos; }

private:
    void init( size_t num_lines, size_t switch_to_insertion );
    void step( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth );
    void radix_sort( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth );
    void insertion_sort( const std::vector< std::string >& lines, size_t begin, size_t end, size_t depth );

    size_t                                 m_switch_to_insertion_sort;
	std::vector< std::string::value_type > m_alphabet;
	std::vector< size_t >                  m_original_pos;
    std::vector< size_t >                  m_sorted_pos;
};
