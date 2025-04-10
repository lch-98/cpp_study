// 포인터와 참조자의 차이
#include <iostream>
using namespace std;

void reference() {
	cout << "======================================================================\n";
	
	int a = 10;
	// int &ref_a = nullptr; 참조자는 NULL을 할당할 수 없음
	int& ref_a = a; // 참조자 사용
	int b = a; // 값만 복사 + 새로운 메모리 차지
	ref_a = 20; // 참조자 값을 바꾸니 a의 값이 바뀜 (원본 값 수정가능 -> 메모리 낭비 방지)

	cout << "a:" << a << "   ref_a:" << ref_a << "   b:" << b << "\n";
	cout << "a 주소:" << &a << "   ref_a 주소:" << &ref_a << "   b주소:" << &b << "\n";

	int c = 30;
	ref_a = c; // c값을 복사만 하고 재할당을 할 수 없음
	
	cout << "\na:" << a << "   ref_a:" << ref_a << "   c:" << c << "\n";
	cout << "a 주소:" << &a << "   ref_a 주소:" << &ref_a << "   c주소:" << &c << "\n";

	cout << "=====================================================================";
}

void pointer() {
	cout << "\n\n=====================================================================\n";
	int a = 1;
	int b = 2;
	
	int* ptr_a = nullptr; // NULL 값 지정 가능
	ptr_a = &a;
	cout << "a:" << a << "   ptr_a:" << *ptr_a << "   b:" << b << "\n";
	cout << "a 주소:" << &a << "   ptr_a주소: " << ptr_a << "   b주소:" << &b << "\n";
	
	ptr_a = &b; // 다른 주소 재할당 가능
	cout << "\na:" << a << "   ptr_a:" << *ptr_a << "   b:" << b << "\n";
	cout << "a 주소:" << &a << "   ptr_a주소: " << ptr_a << "   b주소:" << &b << "\n";
	
	cout << "=====================================================================\n";
}

int main() {
	reference();
	pointer();
}