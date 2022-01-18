cmake_minimum_required(VERSION 3.21)
project(solve)

set(CMAKE_CXX_STANDARD 20)

add_executable(solve main.cpp cmake-build-debug/main.cpp)
