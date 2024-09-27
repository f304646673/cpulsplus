#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void showProgressBar(int duration) {
    const int barWidth = 50;
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        cout << " ";
    }
    cout << "]" << flush;

    for (int i = 0; i <= barWidth; ++i) {
        cout << "\r[";
        for (int j = 0; j < i; ++j) {
            cout << "=";
        }
        for (int j = i; j < barWidth; ++j) {
            cout << " ";
        }
        cout << "] " << int((i / (float)barWidth) * 100.0) << "%" << flush;
        this_thread::sleep_for(chrono::milliseconds(duration / barWidth));
    }
    cout << endl;
}

int main() {
    int duration = 5000; // 进度条持续时间（毫秒）
    showProgressBar(duration);
    return 0;
}