cmake_minimum_required(VERSION 3.28)
project(task6)

set(CMAKE_CXX_STANDARD 17)

add_executable(task6 main.cpp
        include/priority_queue.h
        include/binary_priority_queue.h
        binary_priority_queue.cpp)
