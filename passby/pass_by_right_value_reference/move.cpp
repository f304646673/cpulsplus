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

Custom createCustom() {
    Custom custom = Custom(2);
    return custom;
}

int main(int argc, char* argv[]) {
    std::cout << "construct custom" << std::endl;
    Custom custom = Custom(1);

    std::cout << "copy custom" << std::endl;
    Custom custom2 = custom; // copy constructor

    const Custom& custom3 = std::move(custom);  // no constructor called
    Custom&& custom4 = std::move(custom);   // no constructor called
    const Custom&& custom5 = std::move(custom); // no constructor called

    std::cout << "move custom" << std::endl;
    Custom custom6 = std::move(custom); // move constructor
    Custom custom7 = createCustom(); // move constructor

    std::cout << "main end" << std::endl;
    return 0;
}
    
