#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <bitset>

using namespace std;

void updateProgress(shared_ptr<vector<int>> progress, int id, int duration) {
    const int barWidth = 50;
    for (int i = 0; i <= barWidth; ++i) {
        (*progress)[id] = i;
        this_thread::sleep_for(chrono::milliseconds(duration / barWidth));
    }
}

void printProgress(shared_ptr<vector<int>> progress, int barWidth) {
    bitset<3> finished = 0;
    
    const string red = "\033[31m";    // 红色
    const string green = "\033[32m";  // 绿色
    const string bold = "\033[1m";    // 加粗
    const string reset = "\033[0m";   // 重置颜色
    
    cout << endl << endl << endl;

    while (true) {
         cout << "\033[3F"; // 将光标移动到三行之前
        for (int id = 0; id < progress->size(); ++id) {
            cout << "Progress Bar " << id + 1 << ": [";
            for (int j = 0; j < (*progress)[id]; ++j) {
                if ((*progress)[id] == barWidth) {
                    cout << green << bold << "=" << reset;
                } else {
                    cout << red << bold << "=" << reset;
                }
            }
            for (int j = (*progress)[id]; j < barWidth; ++j) {
                cout << " ";
            }
            cout << "] ";
            if ((*progress)[id] == barWidth) {
                cout << green << bold;
                finished[id] = 1;
            } else {
                cout << red;
            }
            cout << int(((*progress)[id] / (float)barWidth) * 100.0) << "%" << reset << endl << flush;
        }
        this_thread::sleep_for(chrono::milliseconds(100)); // 每100毫秒更新一次显示

        // 检查是否所有进度条都完成
        if (finished.all()) {
            break;
        }
    }
    cout << endl;
}

int main() {
    int duration = 5000; // 进度条持续时间（毫秒）
    const int barWidth = 50;
    auto progress = make_shared<vector<int>>(3, 0); // 初始化3个进度条的进度为0

    // 创建三个线程，每个线程更新一个进度条
    thread t1(updateProgress, progress, 0, duration);
    thread t2(updateProgress, progress, 1, duration * 2);
    thread t3(updateProgress, progress, 2, duration * 3);

    // 创建一个线程打印进度条
    // thread printer(printProgress, progress, barWidth);
    printProgress(progress, barWidth);

    // 等待所有线程完成
    t1.join();
    t2.join();
    t3.join();
    // printer.join();

    return 0;
}