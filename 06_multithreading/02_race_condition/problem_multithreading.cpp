/*
 * [Topic] Race Condition (Problem)
 * 뮤텍스 없이 공유 변수를 여러 스레드가 동시에 수정할 때 발생하는 경쟁 상태.
 *
 * counter++ 는 실제로 세 단계로 실행됨:
 *   1. counter 값 읽기
 *   2. 1 더하기
 *   3. counter에 저장
 * → 두 스레드가 이 사이에 끼어들면 증가분이 유실됨
 *
 * 결과: 10개 스레드 × 100,000번 = 1,000,000이 기대값이지만
 *       실행 시마다 다른 값이 출력됨 (비결정적)
 *
 * 해결: mutex_multithreading.cpp 참고
 */
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
