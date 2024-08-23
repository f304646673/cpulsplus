#include <iostream>

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
        custom.value = 0;
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

void func(Custom custom) {
    std::cout << "func(Custom custom) custom = " << custom << " from " << &custom << std::endl;
}

int main(int argc, char* argv[]) {
    Custom custom(1);
    std::cout << "build custom in main" << std::endl;

    std::cout << "call func(custom)" << std::endl;
    func(custom);

    std::cout << "call func(std::move(custom))" << std::endl;
    func(std::move(custom));

    std::cout << "main end" << std::endl;
    return 0;
}