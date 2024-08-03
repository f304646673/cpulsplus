#ifndef DERIVED_A_H
#define DERIVED_A_H

#include <iostream>

#include "macro.h"
#include "base.h"

class DerivedA : public Base {
public:
    void display() const override {
        std::cout << "DerivedA instance" << std::endl;
    }
};


REGISTER_CLASS(DerivedA)
#endif // DERIVED_A_H