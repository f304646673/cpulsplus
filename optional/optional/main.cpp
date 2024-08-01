#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> getValue(bool condition) {
    if (condition) {
        return "Hello, World!";
    } else {
        return std::nullopt;
    }
}

int main() {
    auto value = getValue(true);
    if (value) {
        std::cout << "Value: " << *value << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    value = getValue(false);
    if (value) {
        std::cout << "Value: " << *value << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}