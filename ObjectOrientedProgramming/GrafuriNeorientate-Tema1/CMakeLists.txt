cmake_minimum_required(VERSION 3.6)
project(GrafuriNeorientate_Tema1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp LinkedList.cpp LinkedList.h Graph.cpp Graph.h LinkedListTester.cpp LinkedListTester.h GraphTester.cpp GraphTester.h)
add_executable(GrafuriNeorientate_Tema1 ${SOURCE_FILES})