#include "custom.h"
#include <iostream>
#include <unordered_map>

int main() {
    std::cout << "Create unordered_map" << std::endl;

    std::unordered_map<Custom, int> unordered_map;
    unordered_map[std::move(Custom(1))] = 1;
    unordered_map[std::move(Custom(2))] = 2;
    unordered_map[std::move(Custom(3))] = 3;

    std::cout << std::endl << "Traverse unordered_map using std::pair<Custom, int>" << std::endl;

    for (const std::pair<Custom, int>& pair : unordered_map) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << std::endl << "Traverse unordered_map using std::pair<const Custom, int>" << std::endl;

    for (const std::pair<const Custom, int>& pair : unordered_map) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << std::endl << "Traverse unordered_map using auto" << std::endl;

    for (const auto& pair : unordered_map) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << std::endl;

    return 0;
}