#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <boost/python.hpp>

class PythonInterpreter {
public:
    PythonInterpreter() {
        Py_Initialize(); // Initialize Python interpreter
        gstate = PyGILState_Ensure(); // Acquire GIL
        std::cout << "Python interpreter initialized." << std::endl;
    }

    ~PythonInterpreter() {
        PyGILState_Release(gstate); // Release GIL
        Py_Finalize(); // Cleanup section
        std::cout << "Python interpreter finalized." << std::endl;
    }

private:
    PyGILState_STATE gstate;
};

void call_python_function() {
    using namespace boost::python;

    try {
        // 创建 PythonInterpreter 对象，自动初始化 Python 解释器
        PythonInterpreter pyInterp;
        
        // 导入 Python 模块
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");

        // 定义并执行 Python 代码
        std::string python_code = R"(
def add(a, b):
    return a + b

result = add(3, 4)
print(f"Result of add(3, 4) is {result}")
)";
        exec(python_code.c_str(), main_namespace);

        // 获取并打印结果
        int result = extract<int>(main_namespace["result"]);
        std::cout << "Result from Python: " << result << std::endl;
    } catch (error_already_set) {
        PyErr_Print();
    }
}

int main() {
    call_python_function();
    return 0;
}