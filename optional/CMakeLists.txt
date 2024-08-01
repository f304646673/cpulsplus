cmake_minimum_required(VERSION 3.12)
project(optional)

# Set the root directory to the current directory
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(optional)
add_subdirectory(pointer)
add_subdirectory(sentinel)
add_subdirectory(pair)
add_subdirectory(config)
add_subdirectory(exeception)
add_subdirectory(querydb)