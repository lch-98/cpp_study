#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <windows.h> // Sleep함수

using namespace std;

int counter = 0; // 공유 자원
mutex mtx;

void increment() {
	for (int i = 0; i < 100000; i++) {
		mtx.lock(); // 뮤텍스를 통한 공유 자원을 한 스레드만 접근 가능하게 해서 경쟁상태 헤체
		counter++;
		mtx.unlock();
		// cout << "Thread " << this_thread::get_id() << ": " << i << " counter: " << counter << endl; //thread id 출력
		// Sleep(1000); // 타임 딜레이 함수
	}
}

int main() {
	vector<thread> threads;

	// 10개의 스레드를 생성해서 동시에 실행
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(increment));
	}

	// 모든 스레드가 종료될 때까지 기다림
	for (auto& t : threads) {
		t.join();
	}

	cout << "Counter: " << counter << endl; // 1000000이 무조건 출력
	return 0;
}
