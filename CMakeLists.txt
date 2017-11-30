cmake_minimum_required(VERSION 3.5)
project(kingsmen)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Board.cpp
        src/Evaluate.cpp
        src/Evaluate.h
        src/main.cpp
        src/Search.cpp src/Search.h
        src/AlphaBeta.h src/AlphaBeta.cpp
        src/enumss.hpp
        src/MTDF.h src/MTDF.cpp
        src/PVS.h  src/PVS.cpp)

add_executable(kingsmen ${SOURCE_FILES})


#
#src/External/Extern.h  src/External/Extern.cpp src/External/Tree.txt src/External/TreeRand.txt src/External/ExternBig.cpp src/External/ExternBig.h