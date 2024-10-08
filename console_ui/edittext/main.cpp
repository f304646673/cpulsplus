#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

void display(const string& inputText, int cursorPosition, bool isButtonSelected, int buttonIndex) {
    const string greenBackground = "\033[42m"; // 绿色背景
    const string redBackground = "\033[41m";   // 红色背景
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
    int windowHeight = 10;

    // 计算窗口的起始位置
    int startX = (terminalWidth - windowWidth) / 2;
    int startY = (terminalHeight - windowHeight) / 2;

    cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

    // 打印顶部边框
    cout << string(startY, '\n');
    cout << string(startX, ' ') << "+" << string(windowWidth - 2, '-') << "+" << endl;

    // 打印输入框行
    cout << string(startX, ' ') << "| " << redBackground << whiteText << "Input: " << inputText << string(windowWidth - 8 - inputText.size() - 3, ' ') << reset << " |" << endl;

    // 打印空行
    for (int i = 0; i < windowHeight - 6; ++i) {
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
    cout << string(windowWidth - totalButtonLength - padding - 2 - 2, ' ') << " |" << endl;

    // 打印底部边框
    cout << string(startX, ' ') << "+" << string(windowWidth - 2, '-') << "+" << endl;

    cout << reset; // 重置颜色

    // 将光标移动到输入框位置
    if (!isButtonSelected) {
        cout << "\033[" << (startY + 2) << ";" << (startX + 8 + 2 + cursorPosition) << "H";
    }
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
            if (ch == 67) ch = 1002; // 右箭头键
            if (ch == 68) ch = 1003; // 左箭头键
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    string inputText;
    int cursorPosition = 0;
    bool isButtonSelected = false;
    int buttonIndex = 0;

    while (true) {
        display(inputText, cursorPosition, isButtonSelected, buttonIndex);

        int ch = getch();
        if (ch == 9) { // Tab 键
            if (!isButtonSelected) {
                isButtonSelected = true;
                buttonIndex = 0;
            } else {
                if (buttonIndex == 1) {
                    isButtonSelected = false;
                } else {
                    buttonIndex = (buttonIndex + 1) % 2;
                }
            }
        } else if (ch == 10 || ch == 13) { // Enter 键
            if (isButtonSelected) {
                cout << "\033[2J\033[H"; // 清空画面
                if (buttonIndex == 0) { // OK 按钮
                    cout << "You entered: " << inputText << endl;
                } else if (buttonIndex == 1) { // Cancel 按钮
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
        } else if (ch == 1002) { // 右箭头键
            if (!isButtonSelected && cursorPosition < inputText.size()) {
                cursorPosition++;
            } else if (isButtonSelected) {
                buttonIndex = (buttonIndex + 1) % 2;
            }
        } else if (ch == 1003) { // 左箭头键
            if (!isButtonSelected && cursorPosition > 0) {
                cursorPosition--;
            } else if (isButtonSelected) {
                buttonIndex = (buttonIndex + 1) % 2;
            }
        } else if (!isButtonSelected && ch >= 32 && ch <= 126 && inputText.size() < 16) { // 可打印字符，限制16个字符
            inputText.insert(cursorPosition, 1, ch);
            cursorPosition++;
        } else if (!isButtonSelected && ch == 127 && cursorPosition > 0) { // 退格键
            inputText.erase(cursorPosition - 1, 1);
            cursorPosition--;
        } else if (ch == 27) { // Esc 键退出
            cout << "\033[2J\033[H"; // 清空画面
            break;
        }
    }

    return 0;
}