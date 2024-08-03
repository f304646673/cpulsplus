#include <iostream>
#include <thread>
#include <chrono>

// 定义宏，使用 __COUNTER__ 生成唯一的线程编号
#define THREAD_ID __COUNTER__

void threadFunction(int id) {
    while (true) {
        std::cout << "Thread [" << id << "] is running." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // 创建三个线程，每个线程都有唯一的编号
    std::thread t1(threadFunction, THREAD_ID);
    std::thread t2(threadFunction, THREAD_ID);
    std::thread t3(threadFunction, THREAD_ID);

    // 等待线程完成（在这个例子中，线程会一直运行）
    t1.join();
    t2.join();
    t3.join();

    return 0;
}