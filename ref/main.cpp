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


int add(const Custom& a, const Custom& b) {
    return a.get_value() +  b.get_value();
} 

int main() {
    Custom a = Custom(1);
    Custom b = Custom(2);
    int c = add(a, b);
    std::cout << "c = " << c << std::endl;

    auto f = std::bind(add, std::ref(a), std::ref(b));
    int d = f();
    std::cout << "d = " << d << std::endl;

    a.set_value(2);
    b.set_value(3);

    int e = f();
    std::cout << "e = " << e << std::endl;

    auto f1 = std::bind(add, a, b);
    int g = f1();
    std::cout << "g = " << g << std::endl;

    return 0;
}