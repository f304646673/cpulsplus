cmake_minimum_required(VERSION 3.12)
# 项目信息
# 最后一级目录为项目名称
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName})

# 添加可执行文件
add_executable(${ProjectName} main.cpp)

target_compile_options(${ProjectName} PRIVATE -fno-elide-constructors)