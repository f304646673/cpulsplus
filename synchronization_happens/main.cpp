#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>

std::atomic<int> data(0);
std::atomic<bool> ready(false);

void threadA() {
    std::this_thread::sleep_for(std::chrono::seconds(10));

    data.store(42, std::memory_order_relaxed);
    // _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&ready);
    ready.store(true, std::memory_order_release);
}

void threadB() {
    while (!ready.load(std::memory_order_acquire)) {
        std::cout << "Thread B is waiting for thread A to complete..." << std::endl;
        // 等待线程 A 完成写操作
    }
    // _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&ready);
    std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl;
}

int main() {
    std::thread tB(threadB);
    std::thread tA(threadA);

    tA.join();
    tB.join();

    return 0;
}