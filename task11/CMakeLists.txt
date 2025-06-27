cmake_minimum_required(VERSION 3.28)
project(task11)

set(CMAKE_CXX_STANDARD 17)

add_executable(task11 main.cpp,
        ./include/treap.h,
        treap.cpp,
)
