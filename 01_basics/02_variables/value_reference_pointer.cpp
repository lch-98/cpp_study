/*
 * [Topic] Parameter Passing: Value vs Reference vs Pointer
 * 함수에 인자를 전달하는 세 가지 방식을 비교하는 예제.
 *
 *   addByValue(int x)   : 복사본을 받으므로 원본(a) 불변
 *   addByRef(int& x)    : 원본 참조 → 호출 후 a 값 변경됨
 *   addByPtr(int* x)    : 주소를 받아 역참조(*x)로 원본 변경
 *
 * 실무에서는 큰 구조체/클래스를 함수에 넘길 때 복사 비용을 줄이기 위해
 * 참조(const &) 또는 포인터를 사용한다.
 */
#include <iostream>
using namespace std;

void addByValue(int x) { // 복사본만 증가
    x++;
    cout << "x= " << x << ", ";
}
void addByRef(int &x) { // 원본 증가
    x++;
    cout << "x= " << x << ", ";
}
void addByPtr(int *x) { // 포인터가 가리키는 값 증가
    (*x)++;
    cout << "x= " << *x << ", ";
}

int main() {
    int a = 10;
    addByValue(a);   // a = 10
    cout << "a= " << a << "\n";

    addByRef(a);     // a = 11
    cout << "a= " << a << "\n";

    addByPtr(&a);    // a = 12
    cout << "a= " << a << "\n";
    return 0;
}
