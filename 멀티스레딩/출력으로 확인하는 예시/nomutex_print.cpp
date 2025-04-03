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
