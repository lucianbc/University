cmake_minimum_required(VERSION 3.7)
project(Clustering)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DisjointSet.cpp DisjointSet.h Clustere.cpp Clustere.h)
add_executable(Clustering ${SOURCE_FILES})