cmake_minimum_required(VERSION 3.7)
project(SecondMST)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DisjointSet.cpp DisjointSet.h GrafPonderat.cpp GrafPonderat.h)
add_executable(SecondMST ${SOURCE_FILES})