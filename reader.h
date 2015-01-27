#pragma once

#include <vector>
#include <string> 

class SimpleReader
{
public:
	static void read_lines( const std::string& filename, size_t num_lines, std::vector< std::string >& lines );
};