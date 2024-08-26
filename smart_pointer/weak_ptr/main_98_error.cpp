#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// 假设这是全局或共享的指针
int* ptr = new int(10);
// 线程A的函数
void threadAFunc() {
    // 假设这里线程A执行了一些操作，然后释放了ptr指向的内存
    delete ptr;
    ptr = NULL; 
}
// 线程B的函数
void threadBFunc() {
    // 线程B尝试访问ptr指向的内存
    if (ptr != NULL) { // 这里的检查在ptr已经被释放且未设为NULL时是无用的
    	// 假设此时ptr被设置为NULL了，后续使用就会出错
        int* temp = ptr;
        int value = *temp; // 尝试解引用悬空指针，导致未定义行为
    }
}