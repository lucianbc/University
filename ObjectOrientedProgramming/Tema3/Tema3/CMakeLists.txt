cmake_minimum_required(VERSION 3.7)
project(Tema3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Models.cpp Models.h Vector.cpp Vector.h)
add_executable(Tema3 ${SOURCE_FILES})