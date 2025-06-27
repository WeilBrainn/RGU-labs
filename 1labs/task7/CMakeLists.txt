cmake_minimum_required(VERSION 3.30)
project(task7_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(task7_1
        main.cpp
        include/binomial_priority_queue.h
        binomial_priority_queue.cpp
        ../../task5/priority_queue.h
)
