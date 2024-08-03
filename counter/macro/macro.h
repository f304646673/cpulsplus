#ifndef MACRO_H
#define MACRO_H

#include "factory.h"
#include "base.h"

#define REGISTER_CLASS(className) \
    class className##Factory { \
    public: \
        className##Factory() { \
            Factory::instance().registerClass(#className, []() -> std::shared_ptr<Base> { return std::make_shared<className>(); }); \
        } \
    }; \
    static className##Factory global_##className##Factory;

#endif // MACRO_H
