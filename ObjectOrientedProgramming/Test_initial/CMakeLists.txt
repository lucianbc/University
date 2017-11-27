cmake_minimum_required(VERSION 3.6)
project(Test_initial)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Forme.cpp Forme.h Prajitura.cpp Prajitura.h)
add_executable(Test_initial ${SOURCE_FILES})