cmake_minimum_required(VERSION 3.6)
project(P2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp UndirectedGraph.cpp UndirectedGraph.h)
add_executable(P2 ${SOURCE_FILES})