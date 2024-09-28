#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

void display(bool isButtonSelected, int buttonIndex) {
    const string greenBackground = "\033[42m"; // 绿色背景
    const string whiteText = "\033[37m";       // 白色字体
    const string blinkText = "\033[5m";        // 闪烁文本
    const string reset = "\033[0m";            // 重置颜色

    // 获取终端窗口大小
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;
    int terminalHeight = w.ws_row;

    // 窗口的宽度和高度
    int windowWidth = 40;
    int windowHeight = 8;

    // 计算窗口的起始位置
    int startX = (terminalWidth - windowWidth) / 2;
    int startY = (terminalHeight - windowHeight) / 2;

    cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

    // 打印顶部边框
    cout << string(startY, '\n');
    cout << string(startX, ' ') << "+" << string(windowWidth - 2, '-') << "+" << endl;

    // 打印空行
    for (int i = 0; i < windowHeight - 4; ++i) {
        cout << string(startX, ' ') << "| " << string(windowWidth - 4, ' ') << " |" << endl;
    }

    // 打印按钮行
    string okButton = "[ OK ]";
    string cancelButton = "[Cancel]";
    int totalButtonLength = okButton.length() + cancelButton.length() + 2; // 2 spaces between buttons
    int padding = (windowWidth - totalButtonLength) / 2;

    cout << string(startX, ' ') << "| " << string(padding, ' ');
    if (isButtonSelected && buttonIndex == 0) {
        cout << greenBackground << whiteText << blinkText << okButton << reset;
    } else {
        cout << okButton;
    }
    cout << "  ";
    if (isButtonSelected && buttonIndex == 1) {
        cout << greenBackground << whiteText << blinkText << cancelButton << reset;
    } else {
        cout << cancelButton;
    }
    cout << string(windowWidth - totalButtonLength - padding - 4, ' ') << " |" << endl;

    // 打印底部边框
    cout << string(startX, ' ') << "+" << string(windowWidth - 2, '-') << "+" << endl;

    cout << reset; // 重置颜色
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);   // 修改终端设置：关闭回显和规范模式
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    // 设置终端为静默模式
    ch = getchar();
    if (ch == 27) { // 如果是ESC键
        ch = getchar();
        if (ch == 91) { // 如果是'['键
            ch = getchar();
            if (ch == 67) return 1000; // 向右箭头键
            if (ch == 68) return 1001; // 向左箭头键
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    bool isButtonSelected = true;
    int buttonIndex = 0;

    while (true) {
        display(isButtonSelected, buttonIndex);

        int ch = getch();
        if (ch == 9 || ch == 1001) { // Tab 键或下箭头键
            buttonIndex = (buttonIndex + 1) % 2;
        } else if (ch == 1000) { // 上箭头键
            buttonIndex = (buttonIndex + 1) % 2;
        } else if (ch == 10 || ch == 13) { // Enter 键
            if (buttonIndex == 0) { // OK 按钮
                cout << "You selected: OK" << endl;
            } else if (buttonIndex == 1) { // Cancel 按钮
                cout << "You selected: Cancel" << endl;
            }
            break;
        } else if (ch == 27) { // Esc 键退出
            break;
        }
    }

    return 0;
}