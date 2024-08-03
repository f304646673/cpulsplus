#ifndef BASE_H
#define BASE_H

class Base {
public:
    virtual ~Base() = default;
    virtual void display() const = 0;
};

#endif // BASE_H