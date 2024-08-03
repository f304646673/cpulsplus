#ifndef MACRO_H
#define MACRO_H

#include "class_factory.h"

#define REGISTER_CLASS(className) \
    REGISTER_CLASS_INTER(className, __COUNTER__)

#define REGISTER_CLASS_INTER(className, index) \
    DECLARE_GLOBAL(className, index)

#define DECLARE_GLOBAL(className, index) \
    static ClassFactory<className, index> global_##index;

#endif // MACRO_H
