cmake_minimum_required(VERSION 3.8)
project(kingsmen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Board.cpp
        src/main.cpp)

add_executable(kingsmen ${SOURCE_FILES})