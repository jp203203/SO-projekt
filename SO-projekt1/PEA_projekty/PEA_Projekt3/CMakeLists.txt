cmake_minimum_required(VERSION 3.27)
project(Pea_Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pea_Projekt2 main.cpp
        FileManager.cpp
        FileManager.h
        Graph.cpp
        Graph.h
        NearestNeighbor.cpp
        NearestNeighbor.h
        TabuSearch.cpp
        TabuSearch.h
        Timer.cpp
        Timer.h
        SimAnnealing.cpp
        SimAnnealing.h
        Interface.cpp
        Interface.h
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
)
