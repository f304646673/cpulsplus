#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

class Custom {
public:
    Custom(int value) : value(value) {
        std::cout << "Constructor Custom(" << value << "). this = " << this << std::endl;
    }
    
    Custom(const Custom& custom) : value(custom.value) {
        std::cout << "Copy constructor Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
    }

    Custom& operator=(const Custom& custom) {
        value = custom.value;
        std::cout << "Copy assignment operator Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
        return *this;
    }

    Custom(Custom&& custom) : value(custom.value) {
        std::cout << "Move constructor Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
    }

    Custom& operator=(Custom&& custom) {
        value = custom.value;
        std::cout << "Move assignment operator Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
        return *this;
    }

    ~Custom() {
        std::cout << "Destructor Custom(" << value << "). this = " << this << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Custom& custom) {
        os << custom.value;
        return os;
    }

public:
    int get_value() const {
        return value;
    }

    void set_value(int value) {
        this->value = value;
    }

private:
    int value;
};

void print_use_count(std::shared_ptr<Custom> shared_ptr_custom) {
    // std::cout << "shared_ptr_custom.use_count() = " << shared_ptr_custom.use_count() << std::endl;
    auto threadId = std::this_thread::get_id();
    std::cout << __LINE__ << " " << threadId << " shared_ptr_custom.use_count() = " << shared_ptr_custom.use_count() << std::endl;
    if (shared_ptr_custom->get_value() > 10) {
        return;
    }
    shared_ptr_custom->set_value(shared_ptr_custom->get_value() + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    print_use_count(shared_ptr_custom);
    std::cout << __LINE__ << " " << threadId << " shared_ptr_custom.use_count() = " << shared_ptr_custom.use_count() << std::endl;
}

void process(std::shared_ptr<Custom> shared_ptr_custom) {
    while (shared_ptr_custom->get_value() < 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        shared_ptr_custom->set_value(shared_ptr_custom->get_value() + 1);
        std::cout << "Processing value: " << shared_ptr_custom->get_value() << std::endl;
    }
}

void start_thread() {
    std::shared_ptr<Custom> shared_ptr_custom = std::make_shared<Custom>(1);
    std::thread t1(process, shared_ptr_custom);
    std::thread t2(print_use_count, shared_ptr_custom);
    t1.join();
    t2.join();
}

int main(int argc, char* argv[]) {
    std::thread t(start_thread);
    t.join();

    return 0;
}