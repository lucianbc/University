cmake_minimum_required(VERSION 3.6)
project(Probleme)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp GrafNeorientatMatrice.cpp GrafNeorientatMatrice.h GrafNeorientatLista.cpp GrafNeorientatLista.h GrafOrientatMatrice.cpp GrafOrientatMatrice.h GrafOrientatLista.cpp GrafOrientatLista.h)
add_executable(Probleme ${SOURCE_FILES})