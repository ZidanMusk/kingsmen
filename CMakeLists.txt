cmake_minimum_required(VERSION 3.8)
project(Untitled_Folder)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Board.cpp
        src/Evaluate.cpp
        src/Evaluate.h
        src/main.cpp)

add_executable(Untitled_Folder ${SOURCE_FILES})