#include <iostream>

class Custom {
public:
    Custom(int value) : value(value) {
        // std::cout << "Constructor Custom(" << value << "). this = " << this << std::endl;
    }
    
    Custom(const Custom& custom) : value(custom.value) {
        // std::cout << "Copy constructor Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
    }

    Custom& operator=(const Custom& custom) {
        value = custom.value;
        // std::cout << "Copy assignment operator Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
        return *this;
    }

    Custom(Custom&& custom) : value(custom.value) {
        std::cout << "Move constructor Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
    }

    Custom& operator=(Custom&& custom) {
        value = custom.value;
        // std::cout << "Move assignment operator Custom(" << custom.value << "). this = " << this << " from " << &custom << std::endl;
        return *this;
    }

    ~Custom() {
        // std::cout << "Destructor Custom(" << value << "). this = " << this << std::endl;
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

// #define print_stack_frame_addresses(func_name) \
//     void* frame_address = __builtin_frame_address(0); \
//     std::cout << "Function: " << func_name << std::endl;  \
//     std::cout << "Frame address (FP): " << frame_address << std::endl; \
//     std::cout << std::endl;

Custom craeteCustom() {
    // print_stack_frame_addresses(__func__);
    Custom custom = Custom(1);
    return custom;
}

int main(int argc, char* argv[]) {
    // print_stack_frame_addresses(__func__);
    Custom custom = craeteCustom();
    // std::cout << "main custom = " << custom << ".Address is " << &custom << std::endl;
    return 0;
}