#include <iostream>
#include <string>
#include <utility> // for std::pair

std::pair<bool, std::string> getValue(bool condition) {
    if (condition) {
        return {true, "Hello, World!"};
    } else {
        return {false, ""};
    }
}

int main() {
    auto result = getValue(true);
    if (result.first) {
        std::cout << "Value: " << result.second << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    result = getValue(false);
    if (result.first) {
        std::cout << "Value: " << result.second << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}