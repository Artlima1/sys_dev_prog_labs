cmake_minimum_required(VERSION 4.1)
project(lab04)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

add_executable(Ex1 ex1/ex1.cpp
        ex1/utils.cpp)
add_executable(Ex2 ex2/ex2.cpp
        ex2/utils.cpp)
