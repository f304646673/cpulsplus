// main.cpp
#include "ResourceManager.h"
#include <iostream>

int main() {
    // Create an instance of ResourceManager
    ResourceManager manager("example.txt");

    // Attempt to copy the ResourceManager instance (should fail)
    // ResourceManager copyManager = manager; // This line should cause a compilation error

    // Attempt to assign one ResourceManager instance to another (should fail)
    // ResourceManager anotherManager("another.txt");
    // anotherManager = manager; // This line should cause a compilation error

    // Attempt to move the ResourceManager instance (should fail)
    // ResourceManager moveManager = std::move(manager); // This line should cause a compilation error

    // Use the ResourceManager to open a file
    manager.openFile("example.txt");

    // Read from the file
    std::string content = manager.readFile();
    std::cout << "File content: " << content << std::endl;

    // Close the file
    manager.closeFile();

    return 0;
}