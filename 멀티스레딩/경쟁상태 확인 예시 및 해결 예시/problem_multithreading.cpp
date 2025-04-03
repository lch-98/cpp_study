#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int counter = 0; // 공유 자원

void increment() {
	for (int i = 0; i < 100000; i++) {
		counter++; // 경쟁상태(Race Condition) 발생 가능
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

	cout << "Counter: " << counter << endl; // 1000000이 아닐 수도 있음!
	return 0;
}
