#include <iostream>
using namespace std;

// static 변수
void func() {
    /*
        일반 지역 변수 a는 계속 새로 생성되어서 11이라는 값이 출력
        static 변수 b는 프로그램이 종료될 때까지 값이 증가 됨
    */
	int a = 10;
	static int b = 10;

	a++;
	b++;

	cout << "a: " << a << " | b: " << b << endl;
}

int main() {
	cout << "===밑에서부터 static===\n" << "\n"; // 줄바꿈
	func();
	func();
	func();
	func();
	func();
	
	cout << "\n===밑에서부터 const===\n" << "\n"; // 줄바꿈
    
	int a = 0;
	int b = 1;
	const int *ptr = &a; // 가르키는 값을 상수화 한거임 따라서 값을 바꾸는건 허용 X
    cout << "ptr: " << *ptr << " | ptr주소: " << ptr << "\n";
	ptr = &b; // 따라서 주소 변경은 가능

	cout << "a: " << a << " | a주소: " << &a << "\n";
	cout << "b: " << b << " | b주소: " << &b << "\n";
	cout << "ptr: " << *ptr << " | ptr주소: " << ptr << endl;

	return 0;
}
