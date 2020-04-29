cmake_minimum_required(VERSION 3.15)
project(GasSimulation)

include(CMakeForceCompiler)
set(Intel_C_COMPILER "/home/ivanludvig/intel/compilers_and_libraries_2020/linux/bin/intel64/icc")
set(Intel_CXX_COMPILER "/home/ivanludvig/intel/compilers_and_libraries_2020/linux/bin/intel64/icpc")

set(CMAKE_C_COMPILER   ${Intel_C_COMPILER})
set(CMAKE_CXX_COMPILER ${Intel_CXX_COMPILER})
#set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)