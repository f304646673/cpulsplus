#include <boost/python.hpp>
#include <iostream>

class DemoClass {
public:
    DemoClass(int value) : value(value) {
        std::cout << "Constructor: DemoClass created with value " << value << std::endl;
    }

    int getValue() const {
        std::cout << "getValue: Returning value " << value << std::endl;
        return value;
    }

    void setValue(int newValue) {
        std::cout << "setValue: Setting value to " << newValue << std::endl;
        value = newValue;
    }

private:
    int value;
};

BOOST_PYTHON_MODULE(demo_module) {
    using namespace boost::python;
    class_<DemoClass>("CplusplusClass", init<int>())
        .def("get", &DemoClass::getValue)
        .def("set", &DemoClass::setValue);
}