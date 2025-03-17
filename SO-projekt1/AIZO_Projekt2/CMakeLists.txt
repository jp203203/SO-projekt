cmake_minimum_required(VERSION 3.27)
project(AIZO_Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(AIZO_Projekt2 main.cpp
        GraphList.cpp
        GraphList.h
        GraphMatrix.cpp
        GraphMatrix.h
        MST.cpp
        MST.h
        Queue.cpp
        Queue.h
        Sets.cpp
        Sets.h
        ShortestPath.cpp
        ShortestPath.h
        GEdge.cpp
        GEdge.h
        FileManager.cpp
        FileManager.h
        GraphGenerator.cpp
        GraphGenerator.h
        Interface.cpp
        Interface.h
        Timer.h
        Timer.cpp)
