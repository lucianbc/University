cmake_minimum_required(VERSION 3.8)
project(BallFall_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES desktop/main.cpp BallFall.cpp BallFall.h Heap.h LifecycleManager.cpp LifecycleManager.h)
add_executable(BallFall_v2 ${SOURCE_FILES})