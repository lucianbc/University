cmake_minimum_required(VERSION 3.8)
project(BallFall_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES desktop/main.cpp heap.h ball_fall.cpp ball_fall.h lifecycle_manager.cpp lifecycle_manager.h)
add_executable(BallFall_v2 ${SOURCE_FILES})