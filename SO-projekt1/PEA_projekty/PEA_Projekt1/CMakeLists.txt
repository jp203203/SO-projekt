cmake_minimum_required(VERSION 3.27)
project(PEA_Projekt1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Projekt1 main.cpp
        FileManager.cpp
        FileManager.h
        Graph.cpp
        Graph.h
        GraphGenerator.cpp
        GraphGenerator.h
        BruteForce.cpp
        BruteForce.h
        Interface.cpp
        Interface.h
        BnBLittle.cpp
        BnBLittle.h
        Timer.cpp
        Timer.h
        Dynamic.cpp
        Dynamic.h)
