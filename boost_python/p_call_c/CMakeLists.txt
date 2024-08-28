cmake_minimum_required(VERSION 3.12)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")

# 查找 Boost 库
find_package(Boost REQUIRED COMPONENTS python)

# 查找 Python 库
find_package(PythonLibs REQUIRED)

# 包含 Boost 和 Python 头文件
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

# 添加可执行文件
add_library(demo_module SHARED main.cpp)

# 链接 Boost 和 Python 库
target_link_libraries(demo_module ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

# 设置输出目录
set_target_properties(demo_module PROPERTIES PREFIX "" SUFFIX ".so")