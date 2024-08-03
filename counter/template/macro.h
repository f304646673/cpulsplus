#ifndef MACRO_H
#define MACRO_H

#include "class_factory.h"

#define REGISTER_CLASS(className) \
    DECLARE_GLOBAL(className, __COUNTER__)

#define DECLARE_GLOBAL(className, index) \
    static ClassFactory<className, index> global_##className##index##ClassFactory;

#endif // MACRO_H
