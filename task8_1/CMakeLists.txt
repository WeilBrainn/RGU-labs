cmake_minimum_required(VERSION 3.28)
project(task8_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(task8_1 main.cpp
        include/fibonacci_heap.h
        fibonacci_heap.cpp)
