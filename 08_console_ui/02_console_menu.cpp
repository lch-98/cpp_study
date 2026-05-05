/*
 * [Topic] Console Menu — 키보드 입력 기반 인터랙티브 메뉴
 * 방향키로 항목을 선택하고 Enter로 확정하는 콘솔 메뉴 시스템.
 * GUI의 핵심 개념인 이벤트 루프와 상태 기반 렌더링을 콘솔로 구현.
 *
 * Key points:
 *   - _getch()     : 엔터 없이 즉시 키 입력 받기 (conio.h)
 *   - 방향키는 두 바이트: 첫 번째 0 또는 0xE0, 두 번째 실제 키코드
 *   - \033[A/B/C/D : 커서 이동 (상/하/우/좌)
 *   - \033[2J      : 화면 전체 지우기
 *   - \033[H       : 커서를 (0,0)으로 이동
 *   - 이벤트 루프  : 입력 대기 → 상태 업데이트 → 화면 다시 그리기 반복
 *
 * Practice:
 *   - 메뉴 항목 선택 시 해당 기능을 실제로 실행하도록 확장하기
 *   - 서브메뉴(중첩 메뉴) 구현해보기
 */
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>   // _getch()
#include <windows.h>
using namespace std;

void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

void moveCursor(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}

void hideCursor() { cout << "\033[?25l"; }
void showCursor() { cout << "\033[?25h"; }

namespace Color {
    const string RESET          = "\033[0m";
    const string BOLD           = "\033[1m";
    const string BRIGHT_CYAN    = "\033[96m";
    const string BRIGHT_YELLOW  = "\033[93m";
    const string BRIGHT_WHITE   = "\033[97m";
    const string DIM            = "\033[2m";
    const string BG_BLUE        = "\033[44m";
    const string BG_DARK        = "\033[100m";
}

// 메뉴 렌더링
void drawMenu(const string& title, const vector<string>& items, int selected) {
    clearScreen();

    // 타이틀
    cout << Color::BRIGHT_CYAN << Color::BOLD;
    cout << "╔══════════════════════════════╗\n";
    cout << "║  " << title;
    for (int i = title.size(); i < 28; i++) cout << " ";
    cout << "║\n";
    cout << "╠══════════════════════════════╣\n";
    cout << Color::RESET;

    // 메뉴 항목
    for (int i = 0; i < (int)items.size(); i++) {
        if (i == selected) {
            cout << Color::BG_BLUE << Color::BRIGHT_YELLOW << Color::BOLD;
            cout << "║  ▶ " << items[i];
            for (int j = items[i].size(); j < 25; j++) cout << " ";
            cout << "║";
        } else {
            cout << Color::BRIGHT_CYAN;
            cout << "║    " << Color::RESET << items[i];
            for (int j = items[i].size(); j < 25; j++) cout << " ";
            cout << Color::BRIGHT_CYAN << "║";
        }
        cout << Color::RESET << "\n";
    }

    cout << Color::BRIGHT_CYAN << Color::BOLD;
    cout << "╚══════════════════════════════╝\n";
    cout << Color::RESET;
    cout << Color::DIM << "\n  ↑↓ 이동   Enter 선택   ESC 종료" << Color::RESET << "\n";
}

int runMenu(const string& title, const vector<string>& items) {
    int selected = 0;
    hideCursor();

    while (true) {
        drawMenu(title, items, selected);

        int key = _getch();

        // 방향키: 첫 바이트가 0 또는 0xE0
        if (key == 0 || key == 0xE0) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + items.size()) % items.size(); // ↑
            if (key == 80) selected = (selected + 1) % items.size();                // ↓
        }
        else if (key == 13) { // Enter
            showCursor();
            return selected;
        }
        else if (key == 27) { // ESC
            showCursor();
            return -1;
        }
    }
}

int main() {
    enableANSI();

    while (true) {
        vector<string> mainItems = {
            "새 파일 만들기",
            "파일 열기",
            "설정",
            "도움말",
            "종료"
        };

        int choice = runMenu("C++ Study Menu", mainItems);

        if (choice == -1 || choice == 4) {
            clearScreen();
            cout << "\033[92m프로그램을 종료합니다.\033[0m\n";
            break;
        }

        clearScreen();
        cout << "\033[93m선택: \033[97m" << mainItems[choice] << "\033[0m\n\n";

        if (choice == 2) {
            // 서브메뉴 예시
            vector<string> settingsItems = {"테마 변경", "폰트 크기", "언어 설정", "← 뒤로"};
            int sub = runMenu("설정", settingsItems);
            if (sub >= 0 && sub < 3) {
                clearScreen();
                cout << "\033[96m설정 선택: " << settingsItems[sub] << "\033[0m\n";
            }
        }

        cout << "\033[2m아무 키나 누르면 메뉴로 돌아갑니다...\033[0m";
        _getch();
    }

    return 0;
}
