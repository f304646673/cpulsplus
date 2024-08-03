#include <memory> // for std::shared_ptr

#include "derived_a.h"
#include "derived_b.h"

int main() {
    Factory& factory = Factory::instance();

    std::shared_ptr<Base> a = factory.create("DerivedA");
    if (a) {
        a->display();
    } else {
        std::cout << "DerivedA not found" << std::endl;
    }

    std::shared_ptr<Base> b = factory.create("DerivedB");
    if (b) {
        b->display();
    } else {
        std::cout << "DerivedB not found" << std::endl;
    }

    return 0;
}