// Singleton.h
#ifndef SINGLETON_H
#define SINGLETON_H

#include "include/macro.h"

class Singleton {
public:
    // Static method to get the single instance of the class
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    // Public method example
    void doSomething() {
        // Implementation of some functionality
    }

private:

    // Delete copy constructor and assignment operator to prevent copies
    CPP_DISABLE_COPY(Singleton)

    // Private constructor to prevent instantiation
    Singleton() {
        // Initialization code
    }

    // Private destructor
    ~Singleton() {
        // Cleanup code
    }
};

#endif // SINGLETON_H