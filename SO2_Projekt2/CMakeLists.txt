cmake_minimum_required(VERSION 3.27)
project(SO2_Projekt2)

set(CMAKE_CXX_STANDARD 17)

# Boost
find_package(Boost REQUIRED COMPONENTS system)
# Include Boost headers (just in case)
include_directories(${Boost_INCLUDE_DIRS})

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
target_link_libraries(ChatClient PRIVATE Boost::system)

# Add WinSock2 only on Windows
if(WIN32)
    target_link_libraries(ChatServer PRIVATE ws2_32 mswsock)
    target_link_libraries(ChatClient PRIVATE ws2_32 mswsock)

    if(MINGW)
        set_target_properties(ChatServer PROPERTIES LINK_FLAGS "-mconsole")
        set_target_properties(ChatClient PROPERTIES LINK_FLAGS "-mconsole")
    endif()
endif()