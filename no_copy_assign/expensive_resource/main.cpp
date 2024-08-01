// main.cpp
#include "ExpensiveResource.h"
#include <iostream>

int main() {
    // Create an instance of ExpensiveResource
    ExpensiveResource resource(1000);

    // Attempt to copy the ExpensiveResource instance (should fail)
    // ExpensiveResource copyResource = resource; // This line should cause a compilation error

    // Attempt to assign one ExpensiveResource instance to another (should fail)
    // ExpensiveResource anotherResource(500);
    // anotherResource = resource; // This line should cause a compilation error

    // Attempt to move the ExpensiveResource instance (should fail)
    // ExpensiveResource moveResource = std::move(resource); // This line should cause a compilation error

    // Use the ExpensiveResource to perform some work
    resource.doWork();

    return 0;
}