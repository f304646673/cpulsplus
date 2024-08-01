#include <iostream>
#include <string>

// 使用空字符串作为哨兵变量
const std::string SENTINEL = "";

std::string getValue(bool condition) {
    if (condition) {
        return "Hello, World!";
    } else {
        return SENTINEL;
    }
}

int main() {
    std::string value = getValue(true);
    if (value != SENTINEL) {
        std::cout << "Value: " << value << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    value = getValue(false);
    if (value != SENTINEL) {
        std::cout << "Value: " << value << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}