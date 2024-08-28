#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

class Data {
public:
    Data() {
        std::cout << "Data created\n";
    }

    ~Data() {
        std::cout << "Data destroyed\n";
    }

public:
    void process() {
        std::cout << "Processing data\n";
    }
};

void threadAFunc(std::shared_ptr<Data>& data) {
    std::this_thread::sleep_for(std::chrono::seconds(6)); // 模拟一些延迟
    std::cout << "Thread A use_count: " << data.use_count() << std::endl;
    data.reset(); // 销毁数据
    std::cout << "Data has been reset\n";
}

void threadBFunc(std::weak_ptr<Data> weakData) {
    if (auto data = weakData.lock()) {
        std::this_thread::sleep_for(std::chrono::seconds(10)); // 模拟一些延迟
        data->process();
    } else {
        std::cout << "Data no longer exists\n";
    }
}

int main() {
    std::shared_ptr<Data> data = std::make_shared<Data>();
    std::weak_ptr<Data> weakData = data;

    std::thread threadA(threadAFunc, std::ref(data));
    std::thread threadB(threadBFunc, weakData);

    threadA.join();
    threadB.join();

    return 0;
}