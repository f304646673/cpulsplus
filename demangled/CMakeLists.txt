cmake_minimum_required(VERSION 3.12)
project(DemangleExample)

# 添加可执行文件
add_executable(DemangleExample main.cpp)

target_link_libraries(DemangleExample ${LIBCXXABI_LIB})
