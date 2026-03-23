cmake_minimum_required(VERSION 4.1)
project(lab02)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex1 Ex1/main.cpp)
add_executable(Ex2 Ex2/Ex2.cpp
        Ex2/UserManager.cpp
        Ex2/UserManager.h)
