cmake_minimum_required(VERSION 3.27)
project(SO2_Projekt1)

set(CMAKE_CXX_STANDARD 17)

add_executable(SO2_Projekt1 main.cpp
        cmake-build-debug/Philosopher.cpp
        cmake-build-debug/Philosopher.h)
