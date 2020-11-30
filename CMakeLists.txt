cmake_minimum_required(VERSION 3.13)
project(laba_first_first)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(laba_first_first
        cafeteria.cpp
        cafeteria.h
        node.h
        linkedlist.h
        main.cpp)
