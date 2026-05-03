/*
 * [Topic] Multithreading WITHOUT Mutex
 * 뮤텍스 없이 두 스레드가 동시에 cout을 사용할 때 발생하는 출력 혼재 현상.
 *
 * 문제:
 *   - cout은 스레드 안전(thread-safe)하지 않음
 *   - 두 스레드가 동시에 cout에 접근하면 출력이 뒤섞임
 *
 * 해결:
 *   → mutex_print.cpp 에서 lock_guard로 보호하는 방법 참고
 *
 * 실행 시 주목할 점:
 *   출력 순서가 실행마다 달라지고 문자열이 섞여 출력될 수 있음
 */
#include <iostream>
#include <thread>

using namespace std;

void printNumbers(int n) {
	for (int i = 1; i <= n; i++) {
		cout << "Thread " << this_thread::get_id() << ": " << i << endl;
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
