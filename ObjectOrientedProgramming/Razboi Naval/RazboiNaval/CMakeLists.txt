cmake_minimum_required(VERSION 3.7)
project(RazboiNaval)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Utilities.cpp Utilities.h ShipWar.cpp ShipWar.h)
add_executable(RazboiNaval ${SOURCE_FILES})