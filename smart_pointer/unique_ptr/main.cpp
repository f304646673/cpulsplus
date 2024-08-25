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

void process(std::unique_ptr<Custom> ptr) {
    std::cout << "Processing value: " << ptr->get_value() << std::endl;
}

void process_raw(Custom* ptr) {
    std::cout << "Processing value: " << ptr->get_value() << std::endl;
}

int main() {
    {
        Custom* custom_raw_ptr = new Custom(10);
        std::cout << "Starting thread" << std::endl;
        std::thread t1(process_raw, custom_raw_ptr);
        t1.join();

        // custom_raw_ptr is still pointing to the allocated memory
        if (custom_raw_ptr) {
            std::cout << "custom_raw_ptr is still valid" << std::endl;
        }

        // Manually delete the pointer to avoid memory leak
        delete custom_raw_ptr;
        custom_raw_ptr = NULL;
    }

    {
        std::unique_ptr<Custom> unique_ptr_custom = std::make_unique<Custom>(20);
        process(std::move(unique_ptr_custom));

        // unique_ptr_custom is now nullptr
        if (!unique_ptr_custom) {
            std::cout << "unique_ptr_custom is now nullptr" << std::endl;
        }
    }

    {
        std::unique_ptr<Custom> unique_ptr_custom = std::make_unique<Custom>(30);
        std::thread t1(process, std::move(unique_ptr_custom));

        // unique_ptr_custom is now nullptr
        if (!unique_ptr_custom) {
            std::cout << "unique_ptr_custom is now nullptr" << std::endl;
        }

        t1.join();
    }

    return 0;
}