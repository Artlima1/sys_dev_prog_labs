cmake_minimum_required(VERSION 4.1)
project(class_exercises)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

add_executable(list_of_vectors list_of_vectors/main.cpp
        list_of_vectors/PersonDataManager.cpp
        list_of_vectors/PersonDataManager.h
        list_of_vectors/Person.cpp
        list_of_vectors/Person.h)

add_executable(thread_election threads/thread_election.cpp)
add_executable(adder threads/adder.cpp)
add_executable(writer_worker_command threads/writer_worker_command.cpp)
