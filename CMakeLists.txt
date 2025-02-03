cmake_minimum_required(VERSION 3.29)
project(NetModel)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetModel main.cpp
        DCN.cpp
        DCN.h
        Graph.cpp
        Graph.h
        BRV.cpp
        BRV.h
        LuSuGuo.cpp
        LuSuGuo.h
        IterativeGrowth.cpp
        IterativeGrowth.h
        Kronecker.cpp
        Kronecker.h)
