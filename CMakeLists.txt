cmake_minimum_required(VERSION 3.29)
project(NetModel)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetModel main.cpp
        Models/DCN.cpp
        Models/DCN.h
        Models/Graph.cpp
        Models/Graph.h
        Models/BRV.cpp
        Models/BRV.h
        Models/LuSuGuo.cpp
        Models/LuSuGuo.h
        Models/IterativeGrowth.cpp
        Models/IterativeGrowth.h
        Models/Kronecker.cpp
        Models/Kronecker.h)
