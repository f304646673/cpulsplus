cmake_minimum_required(VERSION 3.12)
project(counter)

# Set the root directory to the current directory
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

# 自定义函数：遍历所有子目录并添加包含CMakeLists.txt的子目录
function(add_all_subdirectories)
    file(GLOB_RECURSE SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} */CMakeLists.txt)
    foreach(SUBDIR ${SUBDIRS})
        get_filename_component(DIR ${SUBDIR} DIRECTORY)
        add_subdirectory(${DIR})
    endforeach()
endfunction()

# 调用自定义函数
add_all_subdirectories()
