cmake_minimum_required(VERSION 3.7)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GrafPonderat.cpp GrafPonderat.h DisjointSet.cpp DisjointSet.h)
add_executable(Ex1 ${SOURCE_FILES})