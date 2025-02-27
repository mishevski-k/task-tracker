cmake_minimum_required(VERSION 3.30)
project(task_tracker)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(task-cli main.cpp)
