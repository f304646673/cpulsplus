// main.cpp
#include "Singleton.h"
#include <iostream>

int main() {
    // Get the single instance of Singleton
    Singleton& instance1 = Singleton::getInstance();
    Singleton& instance2 = Singleton::getInstance();

    // Attempt to copy the Singleton instance (should fail)
    // Singleton copyInstance = instance1; // This line should cause a compilation error
    
    // Attempt to assign one Singleton instance to another (should fail)
    // Singleton anotherInstance;
    // anotherInstance = instance1; // This line should cause a compilation error

    // Attempt to move the Singleton instance (should fail)
    // Singleton moveInstance = std::move(instance1); // This line should cause a compilation error

    // Demonstrate that both references point to the same instance
    if (&instance1 == &instance2) {
        std::cout << "Both instance1 and instance2 point to the same Singleton instance." << std::endl;
    } else {
        std::cout << "instance1 and instance2 point to different instances." << std::endl;
    }

    // Use the Singleton instance to perform some action
    instance1.doSomething();

    return 0;
}