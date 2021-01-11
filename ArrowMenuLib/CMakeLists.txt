cmake_minimum_required(VERSION 3.17)
project(ArrowMenuLib)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC src/MenuLib.cpp src/MenuOptions.cpp src/MenuUtils.cpp)