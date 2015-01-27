#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include <limits>

#include <vector>
#include <string>

#include "sorter.hpp"
#include "radix.h"
#include "reader.h"
#include "omp_utility.h"

static void Help( const char* bin )
{
    std::cout   << bin << "\tParallel 3-way radix quicksort for strings" << std::endl;
    std::cout   << "-f\tFile to sort" << std::endl;
    std::cout   << "-n\tNumber of OpenMP threads" << std::endl;
    std::cout   << "-N\tNumber of lines to read and sort (from begin)" << std::endl;
    std::cout   << "-r\tReverse sort or alphabetic" << std::endl;
    std::cout   << "-i\tThreshold for number of elements in iteration for Insertion Switch (may speed up sorting)" << std::endl;
    std::cout   << "-h\tShow this help message and exit" << std::endl; 
}

int main( int argc, char* argv[] )
{
    std::string sort_file("");
    bool        is_reverse = false;
    size_t      num_threads = OmpUtility::get_max_threads_num( );
    size_t      num_lines = std::numeric_limits< size_t >::max( );
    size_t      ins_threshold = 10000;

    int c;
    while ( ( c = getopt( argc, argv, "f:n:N:i:rh" ) ) != -1 )
    {
        switch ( c )
        {
            case 'f':
                sort_file.assign( optarg );
                break;
            case 'r':
                is_reverse = true;
                break;
            case 'N':
                num_lines = (size_t)atoi( optarg );
                break;
            case 'n':
                num_threads = (size_t)atoi( optarg );
                break;
            case 'i':
                ins_threshold = (size_t)atoi( optarg );
                break;
            case 'h':
            default:
                Help( argv[ 0 ] );
                exit( 0 ); 
        }
    }

    OmpUtility::set_threads_num( num_threads );

    Sorter< SimpleReader, Radix > S( sort_file, num_lines, ins_threshold, is_reverse );
    S.sort( );

    return 0;
}