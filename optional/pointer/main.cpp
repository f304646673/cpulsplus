#include <iostream>
#include <string>

std::string* getValue(bool condition) {
    if (condition) {
        return new std::string("Hello, World!");
    } else {
        return nullptr;
    }
}

int main() {
    std::string* value = getValue(true);
    if (value) {
        std::cout << "Value: " << *value << std::endl;
        delete value; // 记得释放内存
    } else {
        std::cout << "No value" << std::endl;
    }

    value = getValue(false);
    if (value) {
        std::cout << "Value: " << *value << std::endl;
        delete value; // 记得释放内存
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}