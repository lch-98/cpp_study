/*
 * [Topic] RAII — Resource Acquisition Is Initialization
 * 자원의 획득과 해제를 객체의 생성/소멸에 묶는 C++의 핵심 관용구.
 *
 * RAII 원칙:
 *   - 생성자에서 자원 획득
 *   - 소멸자에서 자원 해제
 *   - 소멸자는 스코프 종료, 예외 발생 모든 상황에서 반드시 호출됨
 *
 * 실무 적용 예:
 *   - lock_guard  : mutex를 RAII로 관리
 *   - unique_ptr  : 힙 메모리를 RAII로 관리
 *   - ifstream    : 파일 핸들을 RAII로 관리
 *
 * Practice:
 *   - FileGuard를 수정해서 파일 열기 실패 시 예외를 던지도록 만들기
 */
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// RAII로 파일 핸들 관리
class FileGuard {
    FILE* file;
public:
    FileGuard(const char* path, const char* mode) {
        file = fopen(path, mode);
        if (!file) throw runtime_error("파일 열기 실패");
        cout << "파일 열림\n";
    }
    ~FileGuard() {
        if (file) { fclose(file); cout << "파일 닫힘 (자동)\n"; }
    }
    FILE* get() { return file; }
    // 복사 금지 (자원 중복 해제 방지)
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;
};

// RAII로 타이머 관리
class ScopeTimer {
    string label;
    clock_t start;
public:
    ScopeTimer(string lbl) : label(lbl), start(clock()) {
        cout << "[" << label << "] 시작\n";
    }
    ~ScopeTimer() {
        double ms = (clock() - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "[" << label << "] 종료: " << ms << "ms\n";
    }
};

int main() {
    {
        ScopeTimer t("작업A");
        // 무거운 작업 시뮬레이션
        volatile int sum = 0;
        for (int i = 0; i < 1000000; i++) sum += i;
    }  // 자동으로 시간 출력

    // 파일 RAII (실제 파일 없어도 예외 처리 동작 확인 가능)
    try {
        FileGuard f("test_raii.txt", "w");
        fputs("RAII 테스트\n", f.get());
    }  // 소멸자에서 fclose 자동 호출
    catch (const exception& e) {
        cout << "예외: " << e.what() << "\n";
    }

    return 0;
}
