#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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
    void increment() {
        ++value;
    }

    int get_value() const {
        return value;
    }

    void set_value(int value) {
        this->value = value;
    }

private:
    int value;
};


void increment_custom_objects(std::vector<Custom>& vec) {
    std::for_each(vec.begin(), vec.end(), [](Custom& c) { c.increment(); });
}

void increment_custom_objects_with_ref(std::vector<std::reference_wrapper<Custom>>& vec) {
    std::for_each(vec.begin(), vec.end(), [](Custom& c) { c.increment(); });
}

void show_custom_objects(Custom c) {
    std::cout << "Custom object value: " << c.get_value() << std::endl;
}

int main() {
    const int num_objects = 5;
    std::vector<Custom> custom_objects;
    for (int i = 0; i < num_objects; ++i) {
        custom_objects.push_back(Custom(i));
    }


    std::cout << "Custom objects created" << std::endl << std::endl;

    // 使用 std::ref 避免拷贝
    std::vector<std::reference_wrapper<Custom>> custom_refs;
    for (auto& obj : custom_objects) {
        custom_refs.push_back(std::ref(obj));
    }

    // 测量不使用 std::ref 的性能
    auto start = std::chrono::high_resolution_clock::now();
    // increment_custom_objects(custom_objects);
    // std::for_each(custom_objects.begin(), custom_objects.end(), show_custom_objects);
    for (const auto& obj : custom_objects) {
        show_custom_objects(obj);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken without std::ref: " << duration.count() << " seconds" << std::endl << std::endl;

    // 测量使用 std::ref 的性能
    start = std::chrono::high_resolution_clock::now();
    // increment_custom_objects_with_ref(custom_refs);
    std::for_each(custom_refs.begin(), custom_refs.end(), std::ref(show_custom_objects));
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken with std::ref: " << duration.count() << " seconds" << std::endl << std::endl;

    // 输出结果
    for (const auto& obj : custom_objects) {
        std::cout << "Custom object value: " << obj.get_value() << std::endl;
    }

    return 0;
}