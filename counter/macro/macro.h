#ifndef MACRO_H
#define MACRO_H

#include <memory>
#include <functional>
#include <string>

#include "factory.h"
#include "base.h"

#define REGISTER_CLASS(className) \
    REGISTER_CLASS_INTER(className, __COUNTER__)

#define REGISTER_CLASS_INTER(className, index) \
    REGISTER_CLASS_WITH_COUNTER(className, index)

#define REGISTER_CLASS_WITH_COUNTER(className, index) \
    class Factory##index { \
    public: \
        Factory##index() { \
            Factory::instance().registerClass(#className, []() -> std::shared_ptr<Base> { return std::make_shared<className>(); }); \
        } \
    }; \
    static Factory##index global_##index;

#endif // MACRO_H