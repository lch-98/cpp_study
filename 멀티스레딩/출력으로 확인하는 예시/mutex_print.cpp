#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h> // Sleep함수

using namespace std;

mutex mtx; // 뮤텍스 객체 생성

void printNumbers(int n) {
    for (int i = 1; i <= n; i++) {
        lock_guard<mutex> lock(mtx); // 뮤텍스 잠금 (자동 해제) mtx.lock(); mtx.unlock()과 동일
        cout << "Thread " << this_thread::get_id() << ": " << i << endl;
        //Sleep(1000);
    }
}

int main() {
    // 두 개의 스레드를 실행
    thread t1(printNumbers, 100000);
    thread t2(printNumbers, 100000);

    // 두 스레드가 끝날 때까지 기다림
    t1.join();
    t2.join();

    cout << "All threads finished!" << endl;
    return 0;
}
