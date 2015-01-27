#include "reader.h"

#include <fstream>
#include <iostream>

void SimpleReader::read_lines( const std::string& filename, size_t num_lines, std::vector< std::string >& lines )
{
	std::ifstream file( filename );
	std::string line;

	while ( std::getline( file, line ) && num_lines > 0 )
	{
	    lines.push_back( line );

		if ( num_lines > 0 )
			num_lines--;
	}
}