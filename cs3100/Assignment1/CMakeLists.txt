cmake_minimum_required(VERSION 3.6)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    stack.h stack.c)

add_executable(Assignment1 ${SOURCE_FILES})