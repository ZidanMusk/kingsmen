cmake_minimum_required(VERSION 3.8)
project(kingsmen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Search.cpp src/Search.h src/MTDF.cpp
        src/MTDF.h src/PVS.cpp src/PVS.h src/Node.cpp src/External/Extern.h
        src/External/Extern.cpp src/External/Tree.txt src/External/TreeRand.txt)
add_executable(kingsmen ${SOURCE_FILES})