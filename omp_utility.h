#pragma once

#ifdef _OPENMP
	#include <omp.h>
#endif

class OmpUtility
{
public:
	static int get_max_threads_num() 
	{
		#ifdef _OPENMP
		  return omp_get_max_threads();
		#else
		  return 1;
		#endif
	}

	static void set_threads_num( int num_threads )
	{
		#ifdef _OPENMP
  			omp_set_num_threads(num_threads);
		#endif
	}

	static int get_thread_id() 
	{
		#ifdef _OPENMP
		  return omp_get_thread_num();
		#else
		  return 0;
		#endif
	}
};