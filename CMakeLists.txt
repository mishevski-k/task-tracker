cmake_minimum_required(VERSION 3.29)
project(task_tracker)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

# Handle different compiler flags based on platform
if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "")
elseif(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(task-cli
        src/main.cpp
        src/core/Task.cpp
        src/core/TaskStatus.cpp
        src/core/TaskManager.cpp
        src/cli/Commands.cpp
)

# Set different output directories based on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
else()
    set_target_properties(task-cli PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()