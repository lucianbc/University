cmake_minimum_required(VERSION 3.8)
project(LifecycleManager)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Heap.h LifecycleManager.cpp LifecycleManager.h)
add_executable(LifecycleManager ${SOURCE_FILES})