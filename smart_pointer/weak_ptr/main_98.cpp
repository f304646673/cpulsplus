#include <iostream>
#include <pthread.h>
#include <unistd.h>

// 假设这是全局或共享的指针
int* ptr = new int(10);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 线程A的函数
void* threadAFunc(void* arg) {
    pthread_mutex_lock(&mutex);
    // 假设这里线程A执行了一些操作，然后释放了ptr指向的内存
    delete ptr;
    ptr = NULL;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// 线程B的函数
void* threadBFunc(void* arg) {
    pthread_mutex_lock(&mutex);
    // 线程B尝试访问ptr指向的内存
    if (ptr != NULL) {
        int* temp = ptr;
        int value = *temp; // 尝试解引用悬空指针，导致未定义行为
        std::cout << "Value: " << value << std::endl;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    pthread_create(&threadA, NULL, threadAFunc, NULL);
    pthread_create(&threadB, NULL, threadBFunc, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}