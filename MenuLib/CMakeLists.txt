cmake_minimum_required(VERSION 3.17)
project(MenuLib)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC src/MenuLib.cpp)