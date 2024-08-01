// main.cpp
#include "ThreadManager.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    ThreadManager manager;
    
    // Attempt to copy the ThreadManager instance (should fail)
    // ThreadManager copyManager = manager; // This line should cause a compilation error

    // Attempt to assign one ThreadManager instance to another (should fail)
    // ThreadManager anotherManager;
    // anotherManager = manager; // This line should cause a compilation error

    // Attempt to move the ThreadManager instance (should fail)
    // ThreadManager moveManager = std::move(manager); // This line should cause a compilation error

    // Start the thread
    manager.startThread();
    std::cout << "Thread started" << std::endl;

    // Let the thread run for a while
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Check if the thread is running
    if (manager.isThreadRunning()) {
        std::cout << "Thread is running" << std::endl;
    }

    // Stop the thread
    manager.stopThread();
    std::cout << "Thread stopped" << std::endl;

    // Check if the thread is running
    if (!manager.isThreadRunning()) {
        std::cout << "Thread is not running" << std::endl;
    }

    return 0;
}