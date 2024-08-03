#include <iostream>
#include <string>

// 定义日志宏，使用 __COUNTER__ 生成唯一的日志条目编号
#define LOG_DEBUG(msg) \
    std::cout << "Log Entry [" << __COUNTER__ << "]: " << msg << std::endl;

void exampleFunction(int value) {
    LOG_DEBUG("Entering exampleFunction with value: " + std::to_string(value));

    if (value < 0) {
        LOG_DEBUG("Value is negative, returning early.");
        return;
    }

    LOG_DEBUG("Performing some operations...");
    // 模拟一些操作
    for (int i = 0; i < value; ++i) {
        LOG_DEBUG("Operation " + std::to_string(i));
    }

    LOG_DEBUG("Exiting exampleFunction.");
}

int main() {
    exampleFunction(3);
    exampleFunction(-1);
    exampleFunction(5);

    return 0;
}