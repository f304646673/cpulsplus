#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <memory> // for std::shared_ptr

#include "base.h"

class Factory {
public:
    using CreateFunc = std::function<std::shared_ptr<Base>()>;

    static Factory& instance() {
        static Factory instance;
        return instance;
    }

    void registerClass(const std::string& className, CreateFunc createFunc) {
        registry_[className] = std::move(createFunc);
    }

    std::shared_ptr<Base> create(const std::string& className) {
        auto it = registry_.find(className);
        if (it != registry_.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<std::string, CreateFunc> registry_;
};

#endif // FACTORY_H