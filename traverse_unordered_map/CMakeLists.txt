cmake_minimum_required(VERSION 3.12)
project(TRAVERSEUNORDEREDMAP)

# 添加可执行文件
add_executable(TraverseUnorderedMap main.cpp)

target_link_libraries(TraverseUnorderedMap ${LIBCXXABI_LIB})
