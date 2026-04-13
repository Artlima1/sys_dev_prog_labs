cmake_minimum_required(VERSION 4.1)
project(lab03)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex1
        Ex1/MyLIFO.hpp
        Ex1/MyLIFO.h
        Ex1/MyFIFO.hpp
        Ex1/MyFIFO.h
        Ex1/Ex1.cpp
)
