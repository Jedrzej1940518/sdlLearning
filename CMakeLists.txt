cmake_minimum_required(VERSION 3.0)

project(starships VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_EXPORT_COMPILE_COMMANDS=1")

add_subdirectory(src)