cmake_minimum_required(VERSION 3.27)
project(SO2_Projekt2)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

# server
add_executable(ChatServer
        server/main.cpp
        server/ChatServer.cpp
        server/ChatServer.h
)
target_link_libraries(ChatServer PRIVATE Boost::system)

# client
add_executable(ChatClient
        client/main.cpp
        client/ChatClient.cpp
        client/ChatClient.h
)
target_link_libraries(ChatServer PRIVATE Boost::system)