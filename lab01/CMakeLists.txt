cmake_minimum_required(VERSION 3.14)
project(Lab01)

set (
    SOURCE_FILES_EX1
        src/ex1/ex1.cpp
        src/ex1/sort.cpp
        src/ex1/print_array.cpp
        src/ex1/allocate_and_read.cpp
    )
add_executable(Ex1 ${SOURCE_FILES_EX1})

add_executable(Ex2 src/others/ex2.cpp)
add_executable(Ex3 src/others/ex3.cpp)
add_executable(Ex4 src/others/ex4.cpp)
add_executable(Ex5 src/others/ex5.cpp)
add_executable(Ex6 src/others/ex6.cpp)


add_executable(Ex7 src/others/ex7.cpp)
target_link_libraries(Ex7 pthread)
