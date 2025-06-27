cmake_minimum_required(VERSION 3.28)
project(task9)

set(CMAKE_CXX_STANDARD 17)

add_executable(task9 main.cpp
        include/leftist_priority_queue.h
        leftist_priority_queue.cpp
)
