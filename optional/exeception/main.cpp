#include <iostream>
#include <optional>
#include <string>

// 函数尝试将字符串转换为整数
std::optional<int> parseInt(const std::string& str) {
    try {
        size_t pos;
        int value = std::stoi(str, &pos);
        if (pos == str.length()) {
            return value;
        } else {
            return std::nullopt; // 字符串包含非数字字符
        }
    } catch (const std::invalid_argument&) {
        return std::nullopt; // 字符串不是有效的整数
    } catch (const std::out_of_range&) {
        return std::nullopt; // 整数超出范围
    }
}

int main() {
    std::string input1 = "123";
    std::string input2 = "abc";
    std::string input3 = "123abc";
    std::string input4 = "999999999999999999999999999999";

    auto result1 = parseInt(input1);
    auto result2 = parseInt(input2);
    auto result3 = parseInt(input3);
    auto result4 = parseInt(input4);

    if (result1) {
        std::cout << "Parsed value: " << *result1 << std::endl;
    } else {
        std::cout << "Failed to parse: " << input1 << std::endl;
    }

    if (result2) {
        std::cout << "Parsed value: " << *result2 << std::endl;
    } else {
        std::cout << "Failed to parse: " << input2 << std::endl;
    }

    if (result3) {
        std::cout << "Parsed value: " << *result3 << std::endl;
    } else {
        std::cout << "Failed to parse: " << input3 << std::endl;
    }

    if (result4) {
        std::cout << "Parsed value: " << *result4 << std::endl;
    } else {
        std::cout << "Failed to parse: " << input4 << std::endl;
    }

    return 0;
}