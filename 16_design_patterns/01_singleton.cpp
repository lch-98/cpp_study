/*
 * [Topic] Singleton Pattern — 싱글톤
 * 클래스의 인스턴스가 전체 프로그램에서 하나뿐임을 보장한다.
 *
 * 사용 예: 설정 관리자, 로거, DB 연결 풀
 *
 * Key points:
 *   - 생성자를 private으로 막음
 *   - static 인스턴스를 반환하는 getInstance() 제공
 *   - C++11 이후 지역 static 변수는 thread-safe (Magic Statics)
 *   - 전역 상태를 만들므로 남용 주의
 *
 * Practice:
 *   - Logger 싱글톤에 로그 레벨(DEBUG/INFO/ERROR) 추가하기
 *   - 테스트 시 싱글톤을 mock으로 교체할 수 있는 구조 고민하기
 */
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;

class Logger {
    vector<string> logs;
    int level = 0;  // 0=DEBUG, 1=INFO, 2=ERROR

    Logger() { cout << "Logger 초기화\n"; }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance;  // C++11: thread-safe 초기화 (Magic Static)
        return instance;
    }

    void setLevel(int lv) { level = lv; }

    void debug(const string& msg) { if (level <= 0) log("[DEBUG] " + msg); }
    void info (const string& msg) { if (level <= 1) log("[INFO]  " + msg); }
    void error(const string& msg) { if (level <= 2) log("[ERROR] " + msg); }

    void printAll() const {
        for (const auto& l : logs) cout << l << "\n";
    }

private:
    void log(const string& msg) {
        logs.push_back(msg);
        cout << msg << "\n";
    }
};

// 여러 모듈에서 동일한 인스턴스 사용
void module_A() {
    Logger::getInstance().info("모듈 A: 작업 시작");
    Logger::getInstance().debug("모듈 A: 상세 정보");
}
void module_B() {
    Logger::getInstance().info("모듈 B: 처리 완료");
    Logger::getInstance().error("모듈 B: 경고 발생");
}

int main() {
    Logger::getInstance().setLevel(0);  // 모든 레벨 출력
    module_A();
    module_B();
    return 0;
}
