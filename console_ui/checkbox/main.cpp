#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

void display(const vector<string>& options, int selected, bool isButtonSelected, int buttonIndex) {
    const string redBackground = "\033[41m"; // 红色背景
    const string greenBackground = "\033[42m"; // 绿色背景
    const string whiteText = "\033[37m";     // 白色字体
    const string blinkText = "\033[5m";      // 闪烁文本
    const string reset = "\033[0m";          // 重置颜色

    // 获取终端窗口大小
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;
    int terminalHeight = w.ws_row;

    // 窗口的宽度和高度
    int windowWidth = 40;
    int windowHeight = options.size() + 8;

    // 计算窗口的起始位置
    int startX = (terminalWidth - windowWidth) / 2;
    int startY = (terminalHeight - windowHeight) / 2;

    cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

    // 打印顶部边框
    cout << string(startY, '\n');
    cout << string(startX, ' ') << "+" << string(windowWidth - 2, '-') << "+" << endl;

    for (int i = 0; i < options.size(); ++i) {
        cout << string(startX, ' ') << "| ";
        cout << redBackground << whiteText; // 设置红色背景和白色字体
        if (i == selected && !isButtonSelected) {
            cout << "> "; // 用于指示当前选中的选项
        } else {
            cout << "  ";
        }
        cout << options[i] << string(windowWidth - 6 - options[i].size(), ' ') << reset << " |" << endl;
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
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) { // 如果是ESC键
        ch = getchar();
        if (ch == 91) { // 如果是'['键
            ch = getchar();
            if (ch == 65) ch = 1000; // 上箭头键
            if (ch == 66) ch = 1001; // 下箭头键
            if (ch == 67) ch = 1002; // 右箭头键
            if (ch == 68) ch = 1003; // 左箭头键
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    vector<string> options = {"Option 1 [ ]", "Option 2 [ ]", "Option 3 [ ]"};
    int selected = 0;
    bool isButtonSelected = false;
    int buttonIndex = 0;

    while (true) {
        display(options, selected, isButtonSelected, buttonIndex);

        int ch = getch();
        if (ch == 9) { // Tab 键
            if (isButtonSelected) {
                if (buttonIndex == 1) {
                    isButtonSelected = false;
                    selected = 0;
                } else {
                    buttonIndex = (buttonIndex + 1) % 2;
                }
            } else {
                if (selected == options.size() - 1) {
                    isButtonSelected = true;
                    buttonIndex = 0;
                } else {
                    selected = (selected + 1) % options.size();
                }
            }
        } else if (ch == 10 || ch == 13) { // Enter 键
            if (isButtonSelected) {
                if (buttonIndex == 0) { // OK 按钮
                    cout << "Selected options: ";
                    for (const auto& option : options) {
                        if (option[option.size() - 2] == 'X') {
                            cout << option << " ";
                        }
                    }
                    cout << endl;
                    break;
                } else if (buttonIndex == 1) { // Cancel 按钮
                    break;
                }
            } else {
                if (options[selected][options[selected].size() - 2] == 'X') {
                    options[selected][options[selected].size() - 2] = ' ';
                } else {
                    options[selected][options[selected].size() - 2] = 'X';
                }
            }
        }  else if (ch == 1000) { // 上箭头键
            if (!isButtonSelected) {
                selected = (selected - 1 + options.size()) % options.size();
            }
        } else if (ch == 1001) { // 下箭头键
            if (!isButtonSelected) {
                selected = (selected + 1) % options.size();
            }
        } else if (ch == 1002) { // 右箭头键
            if (isButtonSelected) {
                buttonIndex = (buttonIndex + 1) % 2;
            }
        } else if (ch == 1003) { // 左箭头键
            if (isButtonSelected) {
                buttonIndex = (buttonIndex + 1) % 2;
            }
        } else if (ch == 27) { // Esc 键退出
            break;
        }
    }

    return 0;
}