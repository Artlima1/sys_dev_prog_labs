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
add_executable(Ex2 Ex2/Ex2.cpp)
add_executable(Ex4 Ex4/Ex4.cpp)
add_executable(Ex5 Ex5/Ex5.cpp
        Ex5/SocialNetwork.cpp
        Ex5/SocialNetwork.h)
