cmake_minimum_required(VERSION 3.27)
project(AIZO_Projekt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(AIZO_Projekt main.cpp
        FileManager.cpp
        FileManager.h
        ArrayManager.cpp
        ArrayManager.h
        Sorter.cpp
        Sorter.h
        Timer.cpp
        Timer.h
        ArrayTester.cpp
        ArrayTester.h
        SortingEngine.cpp
        SortingEngine.h
        Interface.cpp
        Interface.h)

target_link_libraries(AIZO_Projekt PUBLIC
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        winMM.Lib)

