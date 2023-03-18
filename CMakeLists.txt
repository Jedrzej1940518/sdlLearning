cmake_minimum_required(VERSION 3.0)

project(starships VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -DCMAKE_EXPORT_COMPILE_COMMANDS=1")

add_subdirectory(src)