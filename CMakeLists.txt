cmake_minimum_required(VERSION 3.23)
project(magic)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(magic main.cpp
        src/math_handler.cpp
        src/math_handler.h
        src/object_creator.cpp
        src/object_creator.h
        src/magic_show.cpp
        src/magic_show.h)
