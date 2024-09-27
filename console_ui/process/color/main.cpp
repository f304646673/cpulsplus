#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void showProgressBar(int duration) {
    const int barWidth = 50;
    const string red = "\033[31m";    // 红色
    const string green = "\033[32m";  // 绿色
    const string reset = "\033[0m";   // 重置颜色
    const string bold = "\033[1m";    // 加粗

    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        cout << " ";
    }
    cout << "]" << flush;

    for (int i = 0; i <= barWidth; ++i) {
        cout << "\r[";
        for (int j = 0; j < i; ++j) {
            if (i == barWidth) {
                cout << green << "=" << reset;
            } else {
                cout << red << "=" << reset;
            }
        }
        for (int j = i; j < barWidth; ++j) {
            cout << " ";
        }

        cout << "] ";
        if (i == barWidth) {
            cout << green << bold;
        } else {
            cout << red;
        }        
        cout << int((i / (float)barWidth) * 100.0) << "%" << reset << flush;
        this_thread::sleep_for(chrono::milliseconds(duration / barWidth));
    }
    cout << endl;
}

int main() {
    int duration = 5000; // 进度条持续时间（毫秒）
    showProgressBar(duration);
    return 0;
}