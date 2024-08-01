cmake_minimum_required(VERSION 3.12)
project(no_copy_assign)

# Set the root directory to the current directory
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(singleton)
add_subdirectory(expensive_resource)
add_subdirectory(thread_manager)
add_subdirectory(resource_manager)