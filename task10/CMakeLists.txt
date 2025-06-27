cmake_minimum_required(VERSION 3.28)
project(task10)

set(CMAKE_CXX_STANDARD 17)

add_executable(task10 main.cpp
        include/skew_priority_queue.h
        skew_priority_queue.cpp)
