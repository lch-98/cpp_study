/*
 * [Topic] Console Output — ANSI 이스케이프 코드로 색상/스타일 출력
 * 외부 라이브러리 없이 표준 cout만으로 색상, 굵기, 커서 위치를 제어한다.
 * Windows 10 버전 1511 이후부터 cmd/PowerShell에서 ANSI 코드 지원.
 *
 * Key points:
 *   - ESC = \033 (8진수) = \x1b (16진수)
 *   - \033[색상코드m  : 색상 설정
 *   - \033[0m        : 모든 스타일 초기화
 *   - 전경색: 30~37 (일반), 90~97 (밝은색)
 *   - 배경색: 40~47 (일반), 100~107 (밝은색)
 *
 * Practice:
 *   - 본인 이름을 무지개색으로 한 글자씩 출력하기
 *   - 진행률 바(progress bar)를 색상으로 표현하기
 */
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// Windows에서 ANSI 코드 활성화
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// ANSI 코드 상수
namespace Color {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string UNDER   = "\033[4m";

    // 전경색
    const string BLACK   = "\033[30m";
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
    const string WHITE   = "\033[37m";

    // 밝은 전경색
    const string BRIGHT_RED    = "\033[91m";
    const string BRIGHT_GREEN  = "\033[92m";
    const string BRIGHT_YELLOW = "\033[93m";
    const string BRIGHT_BLUE   = "\033[94m";
    const string BRIGHT_CYAN   = "\033[96m";

    // 배경색
    const string BG_RED    = "\033[41m";
    const string BG_GREEN  = "\033[42m";
    const string BG_YELLOW = "\033[43m";
    const string BG_BLUE   = "\033[44m";
}

// 진행률 바 출력
void printProgressBar(int percent, int width = 40) {
    int filled = width * percent / 100;
    cout << Color::BRIGHT_BLUE << "[";
    for (int i = 0; i < width; i++) {
        if (i < filled)      cout << Color::BRIGHT_GREEN << "█";
        else if (i == filled) cout << Color::YELLOW << "▓";
        else                  cout << Color::DIM << "░";
    }
    cout << Color::BRIGHT_BLUE << "] "
         << Color::BRIGHT_YELLOW << percent << "%" << Color::RESET;
}

int main() {
    enableANSI();

    // 기본 색상
    cout << Color::RED    << "빨간색 텍스트" << Color::RESET << "\n";
    cout << Color::GREEN  << "초록색 텍스트" << Color::RESET << "\n";
    cout << Color::YELLOW << "노란색 텍스트" << Color::RESET << "\n";
    cout << Color::BLUE   << "파란색 텍스트" << Color::RESET << "\n";
    cout << Color::CYAN   << "청록색 텍스트" << Color::RESET << "\n";
    cout << "\n";

    // 스타일
    cout << Color::BOLD  << "굵은 텍스트"     << Color::RESET << "\n";
    cout << Color::UNDER << "밑줄 텍스트"     << Color::RESET << "\n";
    cout << Color::DIM   << "흐린 텍스트"     << Color::RESET << "\n";
    cout << "\n";

    // 배경색 + 전경색 조합
    cout << Color::BG_BLUE << Color::WHITE << " 파란 배경 흰 글씨 " << Color::RESET << "\n";
    cout << Color::BG_RED  << Color::BOLD  << " 빨간 배경 굵은 글씨 " << Color::RESET << "\n";
    cout << "\n";

    // 진행률 바
    cout << "다운로드 진행 중...\n";
    for (int p : {0, 25, 50, 75, 100}) {
        cout << "\r";
        printProgressBar(p);
        cout.flush();
        Sleep(400);
    }
    cout << "\n\n";

    // 로그 레벨 스타일
    cout << Color::DIM   << "[DEBUG] " << Color::RESET << "디버그 메시지\n";
    cout << Color::CYAN  << "[INFO]  " << Color::RESET << "일반 정보\n";
    cout << Color::YELLOW<< "[WARN]  " << Color::RESET << "경고 메시지\n";
    cout << Color::RED   << "[ERROR] " << Color::RESET << "오류 발생\n";

    return 0;
}
