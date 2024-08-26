#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

class Data {
public:
    void process() {
        std::cout << "Processing data\n";
    }
};

void worker(std::weak_ptr<Data> weakData) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (auto data = weakData.lock()) {
        data->process();
    } else {
        std::cout << "Data no longer exists\n";
    }
}

int main() {
    auto data = std::make_shared<Data>();
    std::thread t(worker, std::weak_ptr<Data>(data));

    data.reset(); // 销毁数据

    t.join();
    return 0;
}