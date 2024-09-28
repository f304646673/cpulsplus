#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>

using namespace std;

void printMenu(bool isDropdownSelected, bool isDropdownOpen, const vector<string>& options, int selectedIndex, bool isButtonSelected, int buttonIndex) {
    const string greenBackground = "\033[42m"; // 绿色背景
    const string redBackground = "\033[41m";   // 红色背景
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
    int menuHeight = 10; // 增加高度

    // 计算菜单的起始位置
    int startX = (width - menuWidth) / 2;
    int startY = (height - menuHeight) / 2;

    cout << "\033[2J\033[H"; // 清屏并将光标移动到左上角

    // 打印顶部边框
    cout << string(startY, '\n');
    cout << string(startX, ' ') << "+" << string(menuWidth - 2, '-') << "+" << endl;

    // 打印下拉框行
    cout << string(startX, ' ') << "| ";
    if (isDropdownSelected) {
        cout << greenBackground << whiteText << "[Select Option]" << reset;
    } else {
        cout << "[Select Option]";
    }
    cout << string(menuWidth - 4 - 15, ' ') << " |" << endl;

    // 打印下拉框选项
    if (isDropdownOpen) {
        for (int i = 0; i < options.size(); ++i) {
            cout << string(startX, ' ') << "| ";
            if (i == selectedIndex) {
                cout << redBackground << whiteText << options[i] << reset;
            } else {
                cout << options[i];
            }
            cout << string(menuWidth - 4 - options[i].size(), ' ') << " |" << endl;
        }
    } else {
        cout << string(menuHeight - 6 - 1, '\n'); // 空行
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
    cout << string(menuWidth - totalButtonLength - padding - 2, ' ') << " |" << endl;

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
            if (ch == 67) return 1002; // 右箭头键
            if (ch == 68) return 1003; // 左箭头键
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    bool isDropdownSelected = false;
    bool isDropdownOpen = false;
    vector<string> options = {"Option 1", "Option 2", "Option 3", "Option 4"};
    int selectedIndex = 0;
    bool isButtonSelected = false;
    int buttonIndex = 0;

    while (true) {
        printMenu(isDropdownSelected, isDropdownOpen, options, selectedIndex, isButtonSelected, buttonIndex);

        int ch = getch();
        if (ch == 9) { // Tab 键
            if (!isDropdownSelected && !isButtonSelected) {
                isDropdownSelected = true;
            } else if (isDropdownSelected) {
                isDropdownSelected = false;
                isButtonSelected = true;
                buttonIndex = 0; // 默认选择 OK 按钮
            } else if (isButtonSelected) {
                buttonIndex = (buttonIndex + 1) % 2; // 在 OK 和 Cancel 按钮之间切换
            }
        } else if (ch == 10 || ch == 13) { // Enter 键
            if (isDropdownSelected) {
                isDropdownOpen = !isDropdownOpen;
            } else if (isButtonSelected) {
                cout << "\033[2J\033[H"; // 清空画面
                if (buttonIndex == 0) { // OK 按钮
                    cout << "You selected: " << options[selectedIndex] << endl;
                } else if (buttonIndex == 1) { // Cancel 按钮
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
        } else if (ch == 1000) { // 上箭头键
            if (isDropdownOpen && selectedIndex > 0) {
                selectedIndex--;
            } else if (isButtonSelected && buttonIndex > 0) {
                buttonIndex--;
            }
        } else if (ch == 1001) { // 下箭头键
            if (isDropdownOpen && selectedIndex < options.size() - 1) {
                selectedIndex++;
            } else if (isButtonSelected && buttonIndex < 1) {
                buttonIndex++;
            }
        } else if (ch == 27) { // Esc 键退出
            cout << "\033[2J\033[H"; // 清空画面
            break;
        }
    }

    return 0;
}