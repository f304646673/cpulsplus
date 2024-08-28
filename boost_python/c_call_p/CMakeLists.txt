cmake_minimum_required(VERSION 3.12)

# 项目信息
# 最后一级目录为项目名称
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName})

# 设置 CMP0148 政策
if(POLICY CMP0148)
    cmake_policy(SET CMP0148 NEW)
endif()

# 查找 Python 解释器和库
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# 查找 Boost 库。使用 Python3_VERSION_MAJOR 和 Python3_VERSION_MINOR 变量来查找对应版本的 Boost.Python 库
find_package(Boost REQUIRED COMPONENTS python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR})

# 添加可执行文件
add_executable(${ProjectName} main.cpp)

# 包含 Python 头文件
include_directories(${Python3_INCLUDE_DIRS})

# 链接 Boost.Python 和 Python 库
target_link_libraries(${ProjectName} ${Boost_LIBRARIES} ${Python3_LIBRARIES})