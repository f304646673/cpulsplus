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

    Custom(Custom&& custom) noexcept : value(custom.value) {
        std::cout << "Move constructor Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
        custom.value = 0;
    }

    Custom& operator=(Custom&& custom) {
        if (this != &custom) {
            value = custom.value;
            std::cout << "Move assignment operator Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
            return *this;
        }
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

void func(Custom&& custom) {
    std::cout << "func(Custom custom) custom = " << custom << " from " << &custom << std::endl;
}

void func_const(const Custom&& custom) {
    std::cout << "func(Custom custom) custom = " << custom << " from " << &custom << std::endl;
}

int main(int argc, char* argv[]) {
    Custom custom(1);
    Custom& custom2 = custom;
    const Custom& custom3 = custom;
    // func(custom); // error: cannot bind rvalue reference of type 'Custom&&' to lvalue of type 'Custom'
    // func(custom2); // error
    // func(custom3); // error
    func(std::move(custom));

    Custom custom4 = std::move(custom); // move constructor

    // func_const(custom); // error: cannot bind rvalue reference of type 'const Custom&&' to lvalue of type 'Custom'
    // func_const(custom2); // error
    // func_const(custom3); // error
    func_const(std::move(custom));
    std::cout << "main end" << std::endl;
    return 0;
}