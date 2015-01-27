CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

ADD_LIBRARY( radix radix.cpp)

SET( CMAKE_CXX_FLAGS "-O2 --std=c++0x -Wall -fPIC -pedantic -fopenmp" )

ADD_EXECUTABLE( sort main.cpp reader.cpp )
TARGET_LINK_LIBRARIES( sort radix)