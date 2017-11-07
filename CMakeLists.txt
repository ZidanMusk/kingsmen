cmake_minimum_required(VERSION 3.5)
project(kingsmen)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Board.cpp
        src/main.cpp)

add_executable(kingsmen ${SOURCE_FILES})
