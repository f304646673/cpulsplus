#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include <string>
#include <memory>
#include <cxxabi.h> // for abi::__cxa_demangle

#include "factory.h"
#include "base.h"

template<class T, int N> 
class ClassFactory { 
public: 
    ClassFactory() { 
        Factory::instance().registerClass(getClassName(), []() -> std::shared_ptr<Base> { return std::make_shared<T>(); }); \
    } 
private:
    std::string getClassName() {
        const char* name = typeid(T).name();
        int status = 0;
        char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
        std::string className = (status == 0) ? demangled : name;
        free(demangled);
        return className;
    }
}; 

#endif // CLASS_FACTORY_H