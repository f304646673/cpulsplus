#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

void printCircularProgress(int duration) {
    const int radius = 10;
    const int steps = 100;
    const double aspectRatio = 2.0; // 调整宽高比
    const string red = "\033[31m";    // 红色
    const string green = "\033[32m";  // 绿色
    const string reset = "\033[0m";   // 重置颜色

    for (int step = 0; step <= steps; ++step) {
        cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

        for (int y = -radius; y <= radius; ++y) {   // 循环绘制圆形的每一行
            for (int x = -radius * aspectRatio; x <= radius * aspectRatio; ++x) {   // 循环绘制圆形的每一列
                double distance = sqrt((x / aspectRatio) * (x / aspectRatio) + y * y);  // 计算当前点到圆心的距离
                if (distance >= radius - 0.5 && distance <= radius + 0.5) {  // 判断当前点是否在圆形边界上
                    double angle = atan2(y, x / aspectRatio) + M_PI;    // 计算当前点的角度
                    double progressAngle = 2 * M_PI * step / steps;   // 计算当前进度的角度
                    if (angle <= progressAngle) {
                        cout << green << "@" << reset;
                    } else {
                        cout << red << "@" << reset;
                    }
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "Progress: " << int((step / (float)steps) * 100.0) << "%" << endl;
        this_thread::sleep_for(chrono::milliseconds(duration / steps));
    }
}

int main() {
    int duration = 5000; // 进度指示器持续时间（毫秒）

    // 创建并启动进度指示器线程
    thread progressThread(printCircularProgress, duration);

    // 等待进度指示器线程完成
    progressThread.join();

    return 0;
}