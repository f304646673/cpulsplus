#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <vector>

// 辅助函数：解码类型名
std::string demangle(const char* name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    std::string result = (status == 0) ? demangled : name;
    free(demangled);
    return result;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::cout << "argv[" << i << "]" << std::endl << argv[i] << " -> " << demangle(argv[i]) << std::endl << std::endl;
    }
    return 0;
}