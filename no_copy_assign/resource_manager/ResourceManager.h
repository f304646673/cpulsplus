// ResourceManager.h
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <fstream>
#include "include/macro.h"

class ResourceManager {
public:
    // Constructor to initialize the resource
    ResourceManager(const std::string& filename) {
        openFile(filename);
    }

    // Destructor to clean up the resource
    ~ResourceManager() {
        closeFile();
    }

    // Public method to open a file
    void openFile(const std::string& filename) {
        if (file.is_open()) {
            file.close();
        }
        file.open(filename);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }

    // Public method to close the file
    void closeFile() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Public method to read from the file
    std::string readFile() {
        std::string content;
        if (file.is_open()) {
            std::getline(file, content);
        } else {
            std::cerr << "File is not open" << std::endl;
        }
        return content;
    }

private:
    std::fstream file;

    // Delete copy constructor and assignment operator to prevent copies
    CPP_DISABLE_COPY(ResourceManager)
};

#endif // RESOURCE_MANAGER_H