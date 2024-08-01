// ExpensiveResource.h
#ifndef EXPENSIVE_RESOURCE_H
#define EXPENSIVE_RESOURCE_H

#include <vector>
#include <iostream>

#include "include/macro.h"

class ExpensiveResource {
public:
    // Constructor to initialize the resource
    ExpensiveResource(size_t size) : data(size) {
        std::cout << "ExpensiveResource created with size " << size << std::endl;
    }

    // Destructor to clean up the resource
    ~ExpensiveResource() {
        std::cout << "ExpensiveResource destroyed" << std::endl;
    }

    // Public method to access the resource
    void doWork() {
        std::cout << "Doing work with ExpensiveResource" << std::endl;
        // Perform operations on the data
    }

private:
    std::vector<int> data; // Simulating an expensive resource


    // Delete copy constructor and assignment operator to prevent copies
    CPP_DISABLE_COPY(ExpensiveResource)
};

#endif // EXPENSIVE_RESOURCE_H