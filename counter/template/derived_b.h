#ifndef DERIVED_B_H
#define DERIVED_B_H

#include <iostream>

#include "macro.h"
#include "base.h"

class DerivedB : public Base {
public:
    void display() const override {
        std::cout << "DerivedB instance" << std::endl;
    }
};

REGISTER_CLASS(DerivedB)

#endif // DERIVED_B_H