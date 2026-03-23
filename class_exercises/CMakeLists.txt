cmake_minimum_required(VERSION 4.1)
project(class_exercises)

set(CMAKE_CXX_STANDARD 20)

add_executable(list_of_vectors list_of_vectors/main.cpp
        list_of_vectors/PersonDataManager.cpp
        list_of_vectors/PersonDataManager.h
        list_of_vectors/Person.cpp
        list_of_vectors/Person.h)
