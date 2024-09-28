#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

void printMenu(bool isButtonSelected, int buttonIndex) {
    const string greenBackground = "\033[42m"; // 绿色背景
    const string whiteText = "\033[37m";       // 白色字体
    const string blinkText = "\033[5m";        // 闪烁文本
    const string reset = "\033[0m";            // 重置颜色

    // 获取终端窗口大小
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;
    int height = w.ws_row;

    // 计算菜单的宽度和高度
    int menuWidth = 40; // 增加宽度
    int menuHeight = 8; // 增加高度

    // 计算菜单的起始位置
    int startX = (width - menuWidth) / 2;
    int startY = (height - menuHeight) / 2;

    cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

    // 打印顶部边框
    cout << string(startY, '\n');
    cout << string(startX, ' ') << "+" << string(menuWidth - 2, '-') << "+" << endl;

    // 打印空行
    for (int i = 0; i < menuHeight - 4; ++i) {
        cout << string(startX, ' ') << "| " << string(menuWidth - 4, ' ') << " |" << endl;
    }

    // 打印按钮行
    string okButton = "[ OK ]";
    string cancelButton = "[Cancel]";
    int totalButtonLength = okButton.length() + cancelButton.length() + 2; // 2 spaces between buttons
    int padding = (menuWidth - totalButtonLength) / 2;

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
    cout << string(menuWidth - totalButtonLength - padding - 4, ' ') << " |" << endl;

    // 打印底部边框
    cout << string(startX, ' ') << "+" << string(menuWidth - 2, '-') << "+" << endl;

    cout << reset; // 重置颜色
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) { // 如果是ESC键
        ch = getchar();
        if (ch == 91) { // 如果是'['键
            ch = getchar();
            if (ch == 65) return 1000; // 上箭头键
            if (ch == 66) return 1001; // 下箭头键
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    bool isButtonSelected = true;
    int buttonIndex = 0;

    while (true) {
        printMenu(isButtonSelected, buttonIndex);

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