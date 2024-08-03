# Collect all source files in this directory
file(GLOB SOURCES "*.cpp")

# 获取当前文件所在目录名
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 将目录名首字母大写
string(SUBSTRING ${CURRENT_DIR} 0 1 FIRST_CHAR)
string(TOUPPER ${FIRST_CHAR} FIRST_CHAR_UPPER)
string(SUBSTRING ${CURRENT_DIR} 1 -1 REMAINING_CHARS)
set(CAPITALIZED_DIR_NAME "${FIRST_CHAR_UPPER}${REMAINING_CHARS}")

# 拼接成add_executable的第一个参数
set(EXECUTABLE_NAME "${CAPITALIZED_DIR_NAME}Executable")

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${SOURCES})