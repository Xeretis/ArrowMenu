cmake_minimum_required(VERSION 3.17)
project(MenuSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(MenuSystem main.cpp)

add_subdirectory(ArrowMenuLib)
target_include_directories(${PROJECT_NAME} PRIVATE ArrowMenuLib/include)
target_link_libraries(${PROJECT_NAME} ArrowMenuLib)