cmake_minimum_required(VERSION 3.8)
project(KingsMen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Board.cpp)
add_executable(KingsMen ${SOURCE_FILES})