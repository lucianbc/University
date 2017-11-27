cmake_minimum_required(VERSION 3.6)
project(P1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Automaton.cpp Automaton.h)
add_executable(P1 ${SOURCE_FILES})