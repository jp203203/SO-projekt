cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(untitled main.cpp
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
        SortingEngine.h)

target_link_libraries(untitled PUBLIC
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        winMM.Lib)
