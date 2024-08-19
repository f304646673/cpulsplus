#include <iostream>
#include <functional>

class Custom {
public:
    Custom() = default;
    Custom(int a) : a(a) {
        std::cout << "Custom constructor from int " << a << ".This is" << this << std::endl;
    }
    Custom(const Custom& other) : a(other.a) {
        std::cout << "Custom copy constructor from const Custom& [" << other.a << "]" << ".This is" << this << std::endl;
    }
    Custom(Custom&& other) : a(other.a) {
        std::cout << "Custom move constructor from Custom&& [" << other.a << "]" << ".This is" << this << std::endl;
    }
    Custom& operator=(const Custom& other) {
        a = other.a;
        std::cout << "Custom copy assignment" << ".This is" << this << std::endl;
        return *this;
    }
    Custom& operator=(Custom&& other) {
        a = other.a;
        std::cout << "Custom move assignment" << ".This is" << this << std::endl;
        return *this;
    }
    ~Custom() {
        std::cout << "Custom destructor" << ".This is" << this << std::endl;
    }

    bool operator==(const Custom& other) const {
        return a == other.a;
    }

    bool operator!=(const Custom& other) const {
        return a != other.a;
    }

    bool operator<(const Custom& other) const {
        return a < other.a;
    }

    bool operator>(const Custom& other) const {
        return a > other.a;
    }


    friend std::ostream& operator<<(std::ostream& os, const Custom& custom) {
        os << custom.a;
        return os;
    }

    int getA() const {
        return a;
    }

private:
    int a;
};

namespace std {
    template <>
    struct hash<Custom> {
        std::size_t operator()(const Custom& c) const {
            return std::hash<int>()(c.getA());
        }
    };
}