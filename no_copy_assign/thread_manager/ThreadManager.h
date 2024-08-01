// ThreadManager.h
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <thread>
#include <mutex>
#include <iostream>

#include "include/macro.h"

class ThreadManager {
public:
    // Constructor to initialize the thread
    ThreadManager() : threadRunning(false) {}

    // Destructor to clean up the thread
    ~ThreadManager() {
        stopThread();
    }

    // Public method to start the thread
    void startThread() {
        if (!threadRunning) {
            threadRunning = true;
            workerThread = std::thread(&ThreadManager::threadFunction, this);
        }
    }

    // Public method to stop the thread
    void stopThread() {
        if (threadRunning) {
            threadRunning = false;
            if (workerThread.joinable()) {
                workerThread.join();
            }
        }
    }

    // Public method to check if the thread is running
    bool isThreadRunning() const {
        return threadRunning;
    }

private:
    std::thread workerThread;
    std::mutex mtx;
    bool threadRunning;

    // Delete copy constructor and assignment operator to prevent copies
    CPP_DISABLE_COPY(ThreadManager)

    // Private method that runs in the thread
    void threadFunction() {
        while (threadRunning) {
            std::lock_guard<std::mutex> lock(mtx);
            // Perform thread work here
            std::cout << "Thread is running" << std::endl;
        }
    }
};

#endif // THREAD_MANAGER_H